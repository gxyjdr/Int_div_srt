//=============================================================================
// div_srt4_synth.sv — Yosys-compatible synthesis flat file for SRT-4 Divider
//=============================================================================
// This file merges all modules with Verilog-2005-compatible constructs,
// avoiding Yosys SV limitations (no packages, no enum return types, etc.).
//=============================================================================

//=============================================================================
// Constants (from div_srt4_pkg, inlined for Yosys compat)
//=============================================================================
`define WIDTH         64
`define PR_WIDTH      68
`define Q_WIDTH       64
`define QDS_PR_BITS   7
`define QDS_DIV_BITS  3
`define LZC_BITS      7
`define MAX_ITER      32
`define ITER_CNT_BITS 6        // $clog2(33)

// QDS digit encoding
`define Q_N2 3'b101  // -2
`define Q_N1 3'b100  // -1
`define Q_Z0 3'b000  //  0
`define Q_P1 3'b001  // +1
`define Q_P2 3'b010  // +2

// State encoding
`define ST_IDLE     3'b000
`define ST_PREPARE  3'b001
`define ST_ITERATE  3'b010
`define ST_CORRECT  3'b011
`define ST_CORRECT2 3'b101
`define ST_OUTPUT   3'b100

//=============================================================================
// QDS function — inline (no enum)
//=============================================================================
// pr_est is 7-bit signed, d_hat is 3-bit.
// Returns 3-bit qds digit encoding: Q_N2/Q_N1/Q_Z0/Q_P1/Q_P2
// Selection:
//   pr_est >= M2[d_hat]   -> q = +2
//   pr_est >= M1[d_hat]   -> q = +1
//   pr_est >= -M1[d_hat]  -> q =  0
//   pr_est >= -M2[d_hat]  -> q = -1
//   otherwise             -> q = -2
//=============================================================================

//=============================================================================
// div_srt4_qds
//=============================================================================
module div_srt4_qds (
    input  wire signed [6:0] pr_est_i,
    input  wire        [2:0] d_hat_i,
    output reg         [2:0] q_digit_o
);
    reg signed [6:0] m2, m1;

    always @(*) begin
        case (d_hat_i)
            3'd0: begin m2 = 7'sd12; m1 = 7'sd4;  end
            3'd1: begin m2 = 7'sd14; m1 = 7'sd4;  end
            3'd2: begin m2 = 7'sd16; m1 = 7'sd4;  end
            3'd3: begin m2 = 7'sd16; m1 = 7'sd4;  end
            3'd4: begin m2 = 7'sd18; m1 = 7'sd6;  end
            3'd5: begin m2 = 7'sd20; m1 = 7'sd6;  end
            3'd6: begin m2 = 7'sd22; m1 = 7'sd8;  end
            3'd7: begin m2 = 7'sd24; m1 = 7'sd8;  end
        endcase

        if (pr_est_i >=  m2)       q_digit_o = `Q_P2;
        else if (pr_est_i >=  m1)  q_digit_o = `Q_P1;
        else if (pr_est_i >= -m1)  q_digit_o = `Q_Z0;
        else if (pr_est_i >= -m2)  q_digit_o = `Q_N1;
        else                       q_digit_o = `Q_N2;
    end

endmodule


//=============================================================================
// div_srt4_datapath
//=============================================================================
module div_srt4_datapath (
    input  wire                    clk,
    input  wire                    rst_n,
    input  wire [`WIDTH-1:0]       abs_dividend_i,
    input  wire [`WIDTH-1:0]       abs_divisor_i,
    input  wire                    prep_step,
    input  wire                    iter_step,
    input  wire                    corr_step,
    output wire                    done_o,
    output wire signed [`QDS_PR_BITS-1:0] pr_est_o,
    output wire        [`QDS_DIV_BITS-1:0] d_hat_o,
    input  wire        [2:0]       q_digit_i,
    output wire [`WIDTH-1:0]       quotient_o,
    output wire [`WIDTH-1:0]       remainder_o
);
    //-------------------------------------------------------------------------
    // LZC function
    //-------------------------------------------------------------------------
    function [6:0] clz64;
        input [63:0] val;
        integer i;
        begin
            clz64 = 7'd64;
            for (i = 63; i >= 0; i = i - 1)
                if (val[i]) begin
                    clz64 = 7'd63 - i;
                    i = -1;
                end
        end
    endfunction

    //-------------------------------------------------------------------------
    // Normalization (PREPARE combinational)
    //-------------------------------------------------------------------------
    wire [6:0] lzc_a;
    wire [6:0] lzc_d;
    wire [6:0] k_calc;
    wire [6:0] n_calc;
    wire [6:0] shift_calc;

    assign lzc_a    = clz64(abs_dividend_i);
    assign lzc_d    = clz64(abs_divisor_i);
    assign k_calc   = lzc_d - lzc_a;
    assign n_calc   = (k_calc + 7'd3) >> 1;
    assign shift_calc = (n_calc << 1) - 7'd2 - k_calc;

    //-------------------------------------------------------------------------
    // State registers (CSA: pr_sum_q + pr_carry_q for redundant PR)
    //-------------------------------------------------------------------------
    reg [`WIDTH-1:0]      d_norm_q;
    reg [6:0]             n_q, shift_q, lzc_d_q;
    reg [`PR_WIDTH-1:0]   pr_sum_q, pr_carry_q;
    reg [`Q_WIDTH-1:0]    Q_q, QM_q;
    reg [5:0]             iter_cnt_q;

    //-------------------------------------------------------------------------
    // Multiple generator: -q * D_scaled
    //-------------------------------------------------------------------------
    wire [`PR_WIDTH-1:0] d_pos_1x;
    wire [`PR_WIDTH-1:0] d_pos_2x;
    wire [`PR_WIDTH-1:0] d_neg_1x;
    wire [`PR_WIDTH-1:0] d_neg_2x;
    wire [`PR_WIDTH-1:0] mult;

    assign d_pos_1x = {2'b00,  d_norm_q, 2'b00};
    assign d_pos_2x = {1'b0,   d_norm_q, 3'b00};
    assign d_neg_1x = -d_pos_1x;
    assign d_neg_2x = -d_pos_2x;

    always @(*) begin
        case (q_digit_i)
            `Q_P2: mult = d_neg_2x;
            `Q_P1: mult = d_neg_1x;
            `Q_Z0: mult = 68'b0;
            `Q_N1: mult = d_pos_1x;
            `Q_N2: mult = d_pos_2x;
            default: mult = 68'b0;
        endcase
    end

    //-------------------------------------------------------------------------
    // CSA iteration: PR_next = (PR << 2) + mult  in carry-save form
    //-------------------------------------------------------------------------
    wire [`PR_WIDTH-1:0] pr_4x_sum;
    wire [`PR_WIDTH-1:0] pr_4x_carry;
    wire [`PR_WIDTH-1:0] carry_raw;
    wire [`PR_WIDTH-1:0] pr_sum_next;
    wire [`PR_WIDTH-1:0] pr_carry_next;

    assign pr_4x_sum   = pr_sum_q << 2;
    assign pr_4x_carry = pr_carry_q << 2;

    assign pr_sum_next   = pr_4x_sum ^ pr_4x_carry ^ mult;
    assign carry_raw     = (pr_4x_sum & pr_4x_carry) | (pr_4x_sum & mult) | (pr_4x_carry & mult);
    assign pr_carry_next = {carry_raw[`PR_WIDTH-2:0], 1'b0};

    //-------------------------------------------------------------------------
    // QDS estimate from carry-save: 7-bit CPA = pr_sum_q[66:60] + pr_carry_q[66:60]
    //-------------------------------------------------------------------------
    assign pr_est_o = $signed(pr_sum_q[`PR_WIDTH-2 -: `QDS_PR_BITS])
                    + $signed(pr_carry_q[`PR_WIDTH-2 -: `QDS_PR_BITS]);
    assign d_hat_o  = d_norm_q[`WIDTH-2 -: `QDS_DIV_BITS];

    //-------------------------------------------------------------------------
    // OTF conversion (64-bit Q/QM)
    //-------------------------------------------------------------------------
    reg [`Q_WIDTH-1:0] Q_next, QM_next;

    always @(*) begin
        case (q_digit_i)
            `Q_P2: begin Q_next = {Q_q [`Q_WIDTH-3:0], 2'b10}; QM_next = {Q_q [`Q_WIDTH-3:0], 2'b01}; end
            `Q_P1: begin Q_next = {Q_q [`Q_WIDTH-3:0], 2'b01}; QM_next = {Q_q [`Q_WIDTH-3:0], 2'b00}; end
            `Q_Z0: begin Q_next = {Q_q [`Q_WIDTH-3:0], 2'b00}; QM_next = {QM_q[`Q_WIDTH-3:0], 2'b11}; end
            `Q_N1: begin Q_next = {QM_q[`Q_WIDTH-3:0], 2'b11}; QM_next = {QM_q[`Q_WIDTH-3:0], 2'b10}; end
            `Q_N2: begin Q_next = {QM_q[`Q_WIDTH-3:0], 2'b10}; QM_next = {QM_q[`Q_WIDTH-3:0], 2'b01}; end
            default: begin Q_next = Q_q; QM_next = QM_q; end
        endcase
    end

    //-------------------------------------------------------------------------
    // Iteration counter and done
    //-------------------------------------------------------------------------
    wire [5:0] iter_cnt_next;
    assign iter_cnt_next = iter_cnt_q + 6'd1;
    assign done_o = (iter_cnt_q == n_q[5:0] - 6'd1);

    //-------------------------------------------------------------------------
    // CORRECT: merge sum+carry -> non-redundant PR (pipelined: pr_full_q)
    //-------------------------------------------------------------------------
    reg signed [`PR_WIDTH-1:0] pr_full_q;
    wire                        pr_negative;
    wire [`PR_WIDTH-1:0]        pr_corrected;
    wire [`Q_WIDTH-1:0]         q_corrected;
    wire [`WIDTH-1:0]           q_int;
    reg [`WIDTH-1:0]            r_calc;

    assign pr_negative  = pr_full_q[`PR_WIDTH-1];
    assign pr_corrected = pr_negative ? (pr_full_q + d_pos_1x) : pr_full_q;
    assign q_corrected  = pr_negative ? QM_q : Q_q;
    assign q_int        = q_corrected >> shift_q[4:0];

    always @(*) begin
        if (shift_q == 7'd0)
            r_calc = pr_corrected >> (lzc_d_q + 7'd2);
        else
            r_calc = ((pr_corrected >> 2) + (q_corrected[0] ? {4'b0, d_norm_q} : 68'b0))
                      >> (lzc_d_q + 7'd1);
    end

    assign quotient_o  = q_int;
    assign remainder_o = r_calc;

    //-------------------------------------------------------------------------
    // Sequential
    //-------------------------------------------------------------------------
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            d_norm_q   <= 64'b0;
            n_q        <= 7'd0;
            shift_q    <= 7'd0;
            lzc_d_q    <= 7'd0;
            pr_sum_q   <= 68'b0;
            pr_carry_q <= 68'b0;
            pr_full_q  <= 68'b0;
            Q_q        <= 64'b0;
            QM_q       <= 64'b0;
            iter_cnt_q <= 6'd0;
        end else begin
            if (prep_step) begin
                d_norm_q   <= abs_divisor_i << lzc_d;
                n_q        <= n_calc;
                shift_q    <= shift_calc;
                lzc_d_q    <= lzc_d;
                pr_sum_q   <= {{(68-64){1'b0}}, abs_dividend_i << lzc_a};
                pr_carry_q <= 68'b0;
                Q_q        <= 64'b0;
                QM_q       <= 64'b0;
                iter_cnt_q <= 6'd0;
            end else if (iter_step) begin
                pr_sum_q   <= pr_sum_next;
                pr_carry_q <= pr_carry_next;
                Q_q        <= Q_next;
                QM_q       <= QM_next;
                iter_cnt_q <= iter_cnt_next;
            end else if (corr_step) begin
                pr_full_q  <= $signed(pr_sum_q) + $signed(pr_carry_q);
            end
        end
    end

endmodule


//=============================================================================
// div_srt4_top
//=============================================================================
module div_srt4_top (
    input  wire                clk,
    input  wire                rst_n,
    input  wire                valid_i,
    output wire                ready_o,
    input  wire [`WIDTH-1:0]   dividend_i,
    input  wire [`WIDTH-1:0]   divisor_i,
    input  wire                signed_op_i,
    output wire                valid_o,
    input  wire                ready_i,
    output wire [`WIDTH-1:0]   quotient_o,
    output wire [`WIDTH-1:0]   remainder_o,
    output wire                div_by_zero_o,
    output wire                overflow_o,
    output wire                busy_o
);

    //-------------------------------------------------------------------------
    // State
    //-------------------------------------------------------------------------
    reg [2:0] state_q, state_next;

    //-------------------------------------------------------------------------
    // Operand registers
    //-------------------------------------------------------------------------
    reg [`WIDTH-1:0]  dividend_q, divisor_q;
    reg               signed_op_q;
    wire              dividend_sign, divisor_sign;
    wire [`WIDTH-1:0] abs_dividend;
    wire [`WIDTH-1:0] abs_divisor;

    assign dividend_sign = signed_op_q & dividend_q[`WIDTH-1];
    assign divisor_sign  = signed_op_q & divisor_q[`WIDTH-1];
    assign abs_dividend  = dividend_sign ? (-dividend_q) : dividend_q;
    assign abs_divisor   = divisor_sign  ? (-divisor_q)  : divisor_q;

    //-------------------------------------------------------------------------
    // Special cases
    //-------------------------------------------------------------------------
    wire is_div_zero, is_overflow, is_a_zero, is_a_lt_d, is_d_one;
    wire short_circuit;

    assign is_div_zero = (divisor_q == 64'b0);
    assign is_overflow = signed_op_q
                       && (dividend_q == 64'h8000_0000_0000_0000)
                       && (divisor_q  == 64'hFFFF_FFFF_FFFF_FFFF);
    assign is_a_zero   = (abs_dividend == 64'b0);
    assign is_a_lt_d   = (abs_dividend < abs_divisor);
    assign is_d_one    = (abs_divisor == 64'd1);

    assign short_circuit = is_div_zero | is_overflow | is_a_zero | is_a_lt_d | is_d_one;

    //-------------------------------------------------------------------------
    // Datapath signals
    //-------------------------------------------------------------------------
    wire                              dp_prep_step;
    wire                              dp_iter_step;
    wire                              dp_done;
    wire signed [`QDS_PR_BITS-1:0]    pr_est;
    wire        [`QDS_DIV_BITS-1:0]   d_hat;
    wire        [2:0]                 q_digit;
    wire [`WIDTH-1:0]                 q_raw;
    wire [`WIDTH-1:0]                 r_raw;

    //-------------------------------------------------------------------------
    // QDS instance
    //-------------------------------------------------------------------------
    div_srt4_qds u_qds (
        .pr_est_i (pr_est),
        .d_hat_i  (d_hat),
        .q_digit_o(q_digit)
    );

    //-------------------------------------------------------------------------
    // Datapath instance
    //-------------------------------------------------------------------------
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

    //-------------------------------------------------------------------------
    // Output registers
    //-------------------------------------------------------------------------
    reg [`WIDTH-1:0]  quotient_o_q,   quotient_o_next;
    reg [`WIDTH-1:0]  remainder_o_q,  remainder_o_next;
    reg               div_by_zero_q,  div_by_zero_next;
    reg               overflow_q,     overflow_next;
    reg               valid_o_q,      valid_o_next;

    //-------------------------------------------------------------------------
    // Sign application function
    //-------------------------------------------------------------------------
    function [`WIDTH-1:0] apply_sign;
        input [`WIDTH-1:0] val;
        input              neg;
        begin
            if (neg) apply_sign = -val;
            else     apply_sign = val;
        end
    endfunction

    //-------------------------------------------------------------------------
    // State machine (combinational)
    //-------------------------------------------------------------------------
    always @(*) begin
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
            `ST_IDLE: begin
                ready_o = 1'b1;
                if (valid_i) begin
                    state_next = `ST_PREPARE;
                end
            end

            `ST_PREPARE: begin
                if (short_circuit) begin
                    state_next = `ST_OUTPUT;
                end else begin
                    dp_prep_step = 1'b1;
                    state_next   = `ST_ITERATE;
                end
            end

            `ST_ITERATE: begin
                dp_iter_step = 1'b1;
                if (dp_done)
                    state_next = `ST_CORRECT;
            end

            `ST_CORRECT: begin
                dp_corr_step = 1'b1;
                state_next   = `ST_CORRECT2;
            end

            `ST_CORRECT2: begin
                state_next = `ST_OUTPUT;
            end

            `ST_OUTPUT: begin
                if (is_div_zero) begin
                    quotient_o_next  = 64'hFFFF_FFFF_FFFF_FFFF;
                    remainder_o_next = dividend_q;
                    div_by_zero_next = 1'b1;
                    overflow_next    = 1'b0;
                end else if (is_overflow) begin
                    quotient_o_next  = 64'h8000_0000_0000_0000;
                    remainder_o_next = 64'b0;
                    div_by_zero_next = 1'b0;
                    overflow_next    = 1'b1;
                end else if (is_a_zero) begin
                    quotient_o_next  = 64'b0;
                    remainder_o_next = 64'b0;
                    div_by_zero_next = 1'b0;
                    overflow_next    = 1'b0;
                end else if (is_a_lt_d) begin
                    quotient_o_next  = 64'b0;
                    remainder_o_next = apply_sign(abs_dividend, dividend_sign);
                    div_by_zero_next = 1'b0;
                    overflow_next    = 1'b0;
                end else if (is_d_one) begin
                    quotient_o_next  = apply_sign(abs_dividend, dividend_sign ^ divisor_sign);
                    remainder_o_next = 64'b0;
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
                    state_next   = `ST_IDLE;
                end
            end

            default: state_next = `ST_IDLE;
        endcase
    end

    //-------------------------------------------------------------------------
    // Sequential
    //-------------------------------------------------------------------------
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            state_q         <= `ST_IDLE;
            dividend_q      <= 64'b0;
            divisor_q       <= 64'b0;
            signed_op_q     <= 1'b0;
            quotient_o_q    <= 64'b0;
            remainder_o_q   <= 64'b0;
            div_by_zero_q   <= 1'b0;
            overflow_q      <= 1'b0;
            valid_o_q       <= 1'b0;
        end else begin
            state_q <= state_next;

            if (state_q == `ST_IDLE && valid_i && ready_o) begin
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

    //-------------------------------------------------------------------------
    // Outputs
    //-------------------------------------------------------------------------
    assign valid_o       = valid_o_q;
    assign quotient_o    = quotient_o_q;
    assign remainder_o   = remainder_o_q;
    assign div_by_zero_o = div_by_zero_q;
    assign overflow_o    = overflow_q;
    assign busy_o        = (state_q != `ST_IDLE);

endmodule
