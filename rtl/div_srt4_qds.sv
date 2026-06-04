//=============================================================================
// div_srt4_qds.sv — SRT-4 Quotient Digit Selection (QDS)
//=============================================================================
// Pure combinational lookup. Uses top 7 bits of partial remainder (assimilated)
// and top 3 bits of normalized divisor to select q_i in {-2,-1,0,+1,+2}.
// Implementation: priority encoder over m_k boundaries (synthesizes to PLA/ROM).
//=============================================================================

module div_srt4_qds (
    input  logic signed [6:0] pr_est_i,    // PR estimate (sum[67:61] + carry[67:61])
    input  logic        [2:0] d_hat_i,     // divisor_norm[62:60]
    output logic        [2:0] q_digit_o    // encoded qds_digit_t
);

    import div_srt4_pkg::*;

    always_comb begin
        q_digit_o = qds_lookup(pr_est_i, d_hat_i);
    end

endmodule