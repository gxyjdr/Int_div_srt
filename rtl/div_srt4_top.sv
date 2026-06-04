//=============================================================================
// div_srt4_top.sv — SRT-4 (Radix-4) Integer Divider Top-Level (68-bit PR)
//=============================================================================
// Features:
//   - 64-bit signed/unsigned integer division
//   - Valid/Ready handshake (input and output)
//   - SRT Radix-4 algorithm, digit set {-2,-1,0,+1,+2}
//   - Variable iterations: N = ceil((K+2)/2) + 1, K = lzc_D - lzc_A
//   - Short-circuits: D=0, INT64_MIN/-1, A=0, |A|<|D|, |D|=1
//   - Latency: 1 (PREPARE) + N (ITERATE) + 2 (CORRECT) + 1 (OUTPUT)
//=============================================================================

module div_srt4_top
    import div_srt4_pkg::*;
(
    input  logic                clk,
    input  logic                rst_n,

    // Input handshake
    input  logic                valid_i,
    output logic                ready_o,
    input  logic [WIDTH-1:0]    dividend_i,
    input  logic [WIDTH-1:0]    divisor_i,
    input  logic                signed_op_i,    // 1 = signed, 0 = unsigned

    // Output handshake
    output logic                valid_o,
    input  logic                ready_i,
    output logic [WIDTH-1:0]    quotient_o,
    output logic [WIDTH-1:0]    remainder_o,

    // Status flags
    output logic                div_by_zero_o,
    output logic                overflow_o,
    output logic                busy_o
);

    //=========================================================================
    // State
    //=========================================================================
    state_t state_q, state_next;

    //=========================================================================
    // Operand registers
    //=========================================================================
    logic [WIDTH-1:0] dividend_q, divisor_q;
    logic             signed_op_q;
    logic             dividend_sign, divisor_sign;
    logic [WIDTH-1:0] abs_dividend,  abs_divisor;

    assign dividend_sign = signed_op_q & dividend_q[WIDTH-1];
    assign divisor_sign  = signed_op_q & divisor_q[WIDTH-1];
    assign abs_dividend  = dividend_sign ? (-dividend_q) : dividend_q;
    assign abs_divisor   = divisor_sign  ? (-divisor_q)  : divisor_q;

    //=========================================================================
    // Special cases (computed combinationally from registered operands)
    //=========================================================================
    logic is_div_zero, is_overflow, is_a_zero, is_a_lt_d, is_d_one;
    logic short_circuit;

    assign is_div_zero = (divisor_q == '0);
    assign is_overflow = signed_op_q
                       && (dividend_q == 64'h8000_0000_0000_0000)
                       && (divisor_q  == 64'hFFFF_FFFF_FFFF_FFFF);
    assign is_a_zero   = (abs_dividend == '0);
    assign is_a_lt_d   = (abs_dividend < abs_divisor);
    assign is_d_one    = (abs_divisor == 64'd1);

    assign short_circuit = is_div_zero | is_overflow | is_a_zero | is_a_lt_d | is_d_one;

    //=========================================================================
    // Datapath signals
    //=========================================================================
    logic                              dp_prep_step;
    logic                              dp_iter_step;
    logic                              dp_corr_step;
    logic                              dp_done;
    logic signed [QDS_PR_BITS-1:0]     pr_est;
    logic        [QDS_DIV_BITS-1:0]    d_hat;
    logic        [2:0]                 q_digit;
    logic [WIDTH-1:0]                  q_raw;
    logic [WIDTH-1:0]                  r_raw;

    //=========================================================================
    // QDS instance
    //=========================================================================
    div_srt4_qds u_qds (
        .pr_est_i (pr_est),
        .d_hat_i  (d_hat),
        .q_digit_o(q_digit)
    );

    //=========================================================================
    // Datapath instance
    //=========================================================================
    div_srt4_datapath u_datapath (
        .clk            (clk),
        .rst_n          (rst_n),
        .abs_dividend_i (abs_dividend),
        .abs_divisor_i  (abs_divisor),
        .prep_step      (dp_prep_step),
        .iter_step      (dp_iter_step),
        .corr_step      (dp_corr_step),
        .done_o         (dp_done),
        .pr_est_o       (pr_est),
        .d_hat_o        (d_hat),
        .q_digit_i      (q_digit),
        .quotient_o     (q_raw),
        .remainder_o    (r_raw)
    );

    //=========================================================================
    // Output registers
    //=========================================================================
    logic [WIDTH-1:0] quotient_o_q,   quotient_o_next;
    logic [WIDTH-1:0] remainder_o_q,  remainder_o_next;
    logic             div_by_zero_q,  div_by_zero_next;
    logic             overflow_q,     overflow_next;
    logic             valid_o_q,      valid_o_next;

    //=========================================================================
    // Sign application
    //=========================================================================
    function automatic logic [WIDTH-1:0] apply_sign(
        input logic [WIDTH-1:0] val, input logic neg
    );
        return neg ? (-val) : val;
    endfunction

    //=========================================================================
    // State machine
    //=========================================================================
    always_comb begin
        state_next       = state_q;
        dp_prep_step     = 1'b0;
        dp_iter_step     = 1'b0;
        dp_corr_step     = 1'b0;
        ready_o          = 1'b0;
        valid_o_next     = valid_o_q;

        quotient_o_next  = quotient_o_q;
        remainder_o_next = remainder_o_q;
        div_by_zero_next = div_by_zero_q;
        overflow_next    = overflow_q;

        case (state_q)
            ST_IDLE: begin
                ready_o = 1'b1;
                if (valid_i) begin
                    state_next = ST_PREPARE;
                end
            end

            ST_PREPARE: begin
                if (short_circuit) begin
                    state_next = ST_OUTPUT;
                end else begin
                    dp_prep_step = 1'b1;
                    state_next   = ST_ITERATE;
                end
            end

            ST_ITERATE: begin
                dp_iter_step = 1'b1;
                if (dp_done)
                    state_next = ST_CORRECT;
            end

            ST_CORRECT: begin
                dp_corr_step = 1'b1;    // register pr_full_q = pr_sum_q + pr_carry_q
                state_next   = ST_CORRECT2;
            end

            ST_CORRECT2: begin
                // pr_full_q stable; q_int/r_calc computed combinationally
                state_next = ST_OUTPUT;
            end

            ST_OUTPUT: begin
                // Compute results
                if (is_div_zero) begin
                    quotient_o_next  = '1;
                    remainder_o_next = dividend_q;
                    div_by_zero_next = 1'b1;
                    overflow_next    = 1'b0;
                end else if (is_overflow) begin
                    quotient_o_next  = 64'h8000_0000_0000_0000;
                    remainder_o_next = '0;
                    div_by_zero_next = 1'b0;
                    overflow_next    = 1'b1;
                end else if (is_a_zero) begin
                    quotient_o_next  = '0;
                    remainder_o_next = '0;
                    div_by_zero_next = 1'b0;
                    overflow_next    = 1'b0;
                end else if (is_a_lt_d) begin
                    quotient_o_next  = '0;
                    remainder_o_next = apply_sign(abs_dividend, dividend_sign);
                    div_by_zero_next = 1'b0;
                    overflow_next    = 1'b0;
                end else if (is_d_one) begin
                    quotient_o_next  = apply_sign(abs_dividend, dividend_sign ^ divisor_sign);
                    remainder_o_next = '0;
                    div_by_zero_next = 1'b0;
                    overflow_next    = 1'b0;
                end else begin
                    quotient_o_next  = apply_sign(q_raw, dividend_sign ^ divisor_sign);
                    remainder_o_next = apply_sign(r_raw, dividend_sign);
                    div_by_zero_next = 1'b0;
                    overflow_next    = 1'b0;
                end

                valid_o_next = 1'b1;

                if (ready_i) begin
                    valid_o_next = 1'b0;
                    state_next   = ST_IDLE;
                end
            end

            default: state_next = ST_IDLE;
        endcase
    end

    //=========================================================================
    // Sequential
    //=========================================================================
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            state_q         <= ST_IDLE;
            dividend_q      <= '0;
            divisor_q       <= '0;
            signed_op_q     <= 1'b0;
            quotient_o_q    <= '0;
            remainder_o_q   <= '0;
            div_by_zero_q   <= 1'b0;
            overflow_q      <= 1'b0;
            valid_o_q       <= 1'b0;
        end else begin
            state_q <= state_next;

            if (state_q == ST_IDLE && valid_i && ready_o) begin
                dividend_q  <= dividend_i;
                divisor_q   <= divisor_i;
                signed_op_q <= signed_op_i;
            end

            quotient_o_q  <= quotient_o_next;
            remainder_o_q <= remainder_o_next;
            div_by_zero_q <= div_by_zero_next;
            overflow_q    <= overflow_next;
            valid_o_q     <= valid_o_next;
        end
    end

    //=========================================================================
    // Outputs
    //=========================================================================
    assign valid_o       = valid_o_q;
    assign quotient_o    = quotient_o_q;
    assign remainder_o   = remainder_o_q;
    assign div_by_zero_o = div_by_zero_q;
    assign overflow_o    = overflow_q;
    assign busy_o        = (state_q != ST_IDLE);

endmodule
