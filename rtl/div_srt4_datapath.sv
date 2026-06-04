//=============================================================================
// div_srt4_datapath.sv — SRT-4 Divider Datapath (68-bit PR, revised 2026-05-30)
//=============================================================================
// Changes from old:
//   - PR_0 = {4'b0, A_norm} (no >>1), fixes unsigned MSB=1 LSB loss
//   - D_scaled = D_norm << 2 (was <<1)
//   - pr_est from pr_q[66:60] directly (was pr_4x[67:61])
//   - N = (K+3)>>1 (removed +1), shift in {0,1}
//   - R = PR-based recovery (no 64x64 multiplier)
//   - Q_WIDTH = 64 (was 66)
//=============================================================================

module div_srt4_datapath
    import div_srt4_pkg::*;
(
    input  logic                    clk,
    input  logic                    rst_n,

    input  logic [WIDTH-1:0]        abs_dividend_i,  // |A|
    input  logic [WIDTH-1:0]        abs_divisor_i,   // |D|

    input  logic                    prep_step,
    input  logic                    iter_step,
    input  logic                    corr_step,

    output logic                    done_o,           // asserts when iter_cnt == N-1

    output logic signed [QDS_PR_BITS-1:0] pr_est_o,
    output logic        [QDS_DIV_BITS-1:0] d_hat_o,
    input  logic        [2:0]       q_digit_i,

    output logic [WIDTH-1:0]        quotient_o,
    output logic [WIDTH-1:0]        remainder_o
);

    //=========================================================================
    // Combinational LZC + normalization (PREPARE)
    //=========================================================================
    function automatic logic [LZC_BITS-1:0] clz64(input logic [WIDTH-1:0] val);
        for (int i = WIDTH-1; i >= 0; i--)
            if (val[i]) return LZC_BITS'(WIDTH-1 - i);
        return LZC_BITS'(WIDTH);
    endfunction

    logic [LZC_BITS-1:0] lzc_a, lzc_d, k_calc, n_calc, shift_calc;
    logic [WIDTH-1:0]    a_norm_calc, d_norm_calc;

    always_comb begin
        lzc_a       = clz64(abs_dividend_i);
        lzc_d       = clz64(abs_divisor_i);
        k_calc      = lzc_d - lzc_a;
        // N = ceil((K+2)/2) = (K+3)>>1
        n_calc      = (k_calc + 7'd3) >> 1;
        // shift = 2N - 2 - K  (values: 0 or 1)
        shift_calc  = (n_calc << 1) - 7'd2 - k_calc;
        a_norm_calc = abs_dividend_i << lzc_a;
        d_norm_calc = abs_divisor_i  << lzc_d;
    end

    //=========================================================================
    // State registers
    //=========================================================================
    logic [WIDTH-1:0]    abs_a_q, abs_d_q;
    logic [WIDTH-1:0]    d_norm_q;
    logic [LZC_BITS-1:0] n_q, shift_q, lzc_d_q;

    logic [PR_WIDTH-1:0] pr_sum_q, pr_carry_q;
    logic [PR_WIDTH-1:0] pr_sum_next, pr_carry_next;
    logic [Q_WIDTH-1:0]         Q_q,  Q_next;
    logic [Q_WIDTH-1:0]         QM_q, QM_next;
    logic [ITER_CNT_BITS-1:0]   iter_cnt_q, iter_cnt_next;

    //=========================================================================
    // Multiple generator: produce  -q * D_scaled  in 68-bit signed
    //   D_scaled     = D_norm << 2 = {2'b0, D_norm, 2'b0}
    //   D_scaled_2x  = D_norm << 3 = {1'b0, D_norm, 3'b0}
    //=========================================================================
    logic [PR_WIDTH-1:0] d_pos_1x, d_pos_2x;
    logic [PR_WIDTH-1:0] d_neg_1x, d_neg_2x;
    logic [PR_WIDTH-1:0] mult;

    assign d_pos_1x = {2'b00,  d_norm_q, 2'b00};   // +D_scaled     = D_norm << 2
    assign d_pos_2x = {1'b0,   d_norm_q, 3'b00};   // +2*D_scaled   = D_norm << 3
    assign d_neg_1x = -d_pos_1x;
    assign d_neg_2x = -d_pos_2x;

    always_comb begin
        case (q_digit_i)
            Q_P2:    mult = d_neg_2x;
            Q_P1:    mult = d_neg_1x;
            Q_Z0:    mult = '0;
            Q_N1:    mult = d_pos_1x;
            Q_N2:    mult = d_pos_2x;
            default: mult = '0;
        endcase
    end

    //=========================================================================
    // CSA iteration: PR_next = (PR << 2) + mult  in carry-save (sum+carry)
    //=========================================================================
    logic [PR_WIDTH-1:0] pr_4x_sum, pr_4x_carry, carry_raw;
    assign pr_4x_sum   = pr_sum_q << 2;
    assign pr_4x_carry = pr_carry_q << 2;

    assign pr_sum_next   = pr_4x_sum ^ pr_4x_carry ^ mult;
    assign carry_raw     = (pr_4x_sum & pr_4x_carry) | (pr_4x_sum & mult) | (pr_4x_carry & mult);
    assign pr_carry_next = {carry_raw[PR_WIDTH-2:0], 1'b0};

    //=========================================================================
    // QDS estimates from pr_q directly (not pr_4x)
    //   pr_est = (pr_sum_q + pr_carry_q)[66:60]  (7-bit signed CPA)
    //   d_hat  = d_norm_q[62:60]
    //=========================================================================
    assign pr_est_o = $signed(pr_sum_q[PR_WIDTH-2 -: QDS_PR_BITS])
                    + $signed(pr_carry_q[PR_WIDTH-2 -: QDS_PR_BITS]);  // [66:60] 7-bit CPA
    assign d_hat_o  = d_norm_q[WIDTH-2 -: QDS_DIV_BITS];  // [62:60]

    //=========================================================================
    // OTF conversion (64-bit Q/QM  →  Q_WIDTH = 64)
    //=========================================================================
    always_comb begin
        case (q_digit_i)
            Q_P2: begin Q_next = {Q_q [Q_WIDTH-3:0], 2'b10}; QM_next = {Q_q [Q_WIDTH-3:0], 2'b01}; end
            Q_P1: begin Q_next = {Q_q [Q_WIDTH-3:0], 2'b01}; QM_next = {Q_q [Q_WIDTH-3:0], 2'b00}; end
            Q_Z0: begin Q_next = {Q_q [Q_WIDTH-3:0], 2'b00}; QM_next = {QM_q[Q_WIDTH-3:0], 2'b11}; end
            Q_N1: begin Q_next = {QM_q[Q_WIDTH-3:0], 2'b11}; QM_next = {QM_q[Q_WIDTH-3:0], 2'b10}; end
            Q_N2: begin Q_next = {QM_q[Q_WIDTH-3:0], 2'b10}; QM_next = {QM_q[Q_WIDTH-3:0], 2'b01}; end
            default: begin Q_next = Q_q; QM_next = QM_q; end
        endcase
    end

    //=========================================================================
    // Iteration counter and done signal
    //=========================================================================
    assign iter_cnt_next = iter_cnt_q + 1'b1;
    assign done_o        = (iter_cnt_q == ITER_CNT_BITS'(n_q) - 1'b1);

    //=========================================================================
    // CORRECT: merge sum+carry → non-redundant PR, sign → Q/QM selection
    //          Q_int = q_corrected >> shift_q
    //          R     = PR-based right-shift recovery (no multiplier)
    //
    // Timing: pr_full_q is registered by corr_step, so the 68-bit CPA spans
    //         one full cycle. q_int/r_calc from pr_full_q span another cycle.
    //=========================================================================
    logic signed [PR_WIDTH-1:0] pr_full_q;
    logic                       pr_negative;
    logic [PR_WIDTH-1:0]        pr_corrected;
    logic [Q_WIDTH-1:0]         q_corrected;
    logic [WIDTH-1:0]           q_int;
    logic [WIDTH-1:0]           r_calc;

    assign pr_negative  = pr_full_q[PR_WIDTH-1];
    assign pr_corrected = pr_negative ? (pr_full_q + $signed(d_pos_1x)) : pr_full_q;
    assign q_corrected  = pr_negative ? QM_q : Q_q;
    assign q_int        = WIDTH'(q_corrected >> shift_q);

    // R = PR-based recovery
    //   shift=0 (K even): R = pr_corrected >> (lzc_D + 2)
    //   shift=1 (K odd):  R = ((pr_corrected >> 2) + Q_red[0]*D_norm) >> (lzc_D + 1)
    always_comb begin
        if (shift_q == 7'd0)
            r_calc = WIDTH'(pr_corrected >> (lzc_d_q + 7'd2));
        else
            r_calc = WIDTH'(((pr_corrected >> 2) + (q_corrected[0] ? {4'b0, d_norm_q} : 68'b0))
                            >> (lzc_d_q + 7'd1));
    end

    assign quotient_o  = q_int;
    assign remainder_o = r_calc;

    //=========================================================================
    // Sequential
    //=========================================================================
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            abs_a_q    <= '0;
            abs_d_q    <= '0;
            d_norm_q   <= '0;
            n_q        <= '0;
            shift_q    <= '0;
            lzc_d_q    <= '0;
            pr_sum_q   <= '0;
            pr_carry_q <= '0;
            pr_full_q  <= '0;
            Q_q        <= '0;
            QM_q       <= '0;
            iter_cnt_q <= '0;
        end else begin
            if (prep_step) begin
                abs_a_q    <= abs_dividend_i;
                abs_d_q    <= abs_divisor_i;
                d_norm_q   <= d_norm_calc;
                n_q        <= n_calc;
                shift_q    <= shift_calc;
                lzc_d_q    <= lzc_d;
                pr_sum_q   <= {{(PR_WIDTH-WIDTH){1'b0}}, a_norm_calc};  // PR_0 = A_norm, no >>1
                pr_carry_q <= '0;                                       // no carry initially
                Q_q        <= '0;
                QM_q       <= '0;
                iter_cnt_q <= '0;
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
