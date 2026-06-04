//=============================================================================
// div_srt4_pkg.sv — SRT-4 (Radix-4) Divider Package (68-bit PR version)
//=============================================================================
// Constants, types, QDS selection table.
// Digit set: {-2, -1, 0, +1, +2}, redundancy factor rho = 2/3.
// Target: 64-bit signed/unsigned integer division.
//
// Math-to-integer mapping (revised 2026-05-30):
//   PR_math   = PR_int / 2^65        (PR_int is 68-bit signed)
//   D_math    = D_norm / 2^63        (D_norm MSB at bit 63)
//   D_scaled  = D_norm << 2          (so D_scaled/2^65 = D_math)
//   PR_0      = {4'b0, A_norm}       (no right shift, fixes unsigned MSB=1 bug)
//   pr_est    = pr_q[66:60]          (7-bit signed, from pr_q directly)
//   d_hat     = D_norm[62:60]        (3-bit)
//   N         = ceil((K+2)/2)        = (K+3)>>1,  K = lzc_D - lzc_A,  max N = 32
//   shift     = 2N - 2 - K           (values: 0 or 1)
//   Q_int     = Q_corrected >> shift
//   R         = PR-based recovery    (no 64x64 multiplier)
//=============================================================================

package div_srt4_pkg;

    //-------------------------------------------------------------------------
    // Parameters
    //-------------------------------------------------------------------------
    localparam int WIDTH         = 64;
    localparam int PR_WIDTH      = 68;                 // 1 sign + 3 growth + 64 data
    localparam int Q_WIDTH       = 64;                 // OTF accumulator, 2*N_max = 64
    localparam int QDS_PR_BITS   = 7;                  // pr_est width (signed)
    localparam int QDS_DIV_BITS  = 3;                  // d_hat width
    localparam int LZC_BITS      = 7;                  // 0..64
    localparam int MAX_ITER      = 32;                 // max N (K=62, |D|=1 short-circuited)
    localparam int ITER_CNT_BITS = $clog2(MAX_ITER + 1);

    //-------------------------------------------------------------------------
    // QDS digit encoding
    //-------------------------------------------------------------------------
    typedef enum logic [2:0] {
        Q_N2 = 3'b101,  // -2
        Q_N1 = 3'b100,  // -1
        Q_Z0 = 3'b000,  //  0
        Q_P1 = 3'b001,  // +1
        Q_P2 = 3'b010   // +2
    } qds_digit_t;

    //-------------------------------------------------------------------------
    // State encoding
    //-------------------------------------------------------------------------
    typedef enum logic [2:0] {
        ST_IDLE     = 3'b000,
        ST_PREPARE  = 3'b001,
        ST_ITERATE  = 3'b010,
        ST_CORRECT  = 3'b011,
        ST_CORRECT2 = 3'b101,
        ST_OUTPUT   = 3'b100
    } state_t;

    //-------------------------------------------------------------------------
    // QDS Lookup Function (case-based, no unpacked arrays for Yosys compat)
    //-------------------------------------------------------------------------
    // pr_est is 7-bit signed, representing 32*PR_math = PR_int >> 60.
    // Selection:
    //   pr_est >= M2[d_hat]   -> q = +2
    //   pr_est >= M1[d_hat]   -> q = +1
    //   pr_est >= -M1[d_hat]  -> q =  0
    //   pr_est >= -M2[d_hat]  -> q = -1
    //   otherwise             -> q = -2
    //-------------------------------------------------------------------------
    function automatic qds_digit_t qds_lookup(
        input logic signed [QDS_PR_BITS-1:0] pr_est,
        input logic        [QDS_DIV_BITS-1:0] d_hat
    );
        logic signed [QDS_PR_BITS-1:0] m2, m1;
        case (d_hat)
            3'd0: begin m2 = 7'sd12; m1 = 7'sd4;  end
            3'd1: begin m2 = 7'sd14; m1 = 7'sd4;  end
            3'd2: begin m2 = 7'sd16; m1 = 7'sd4;  end
            3'd3: begin m2 = 7'sd16; m1 = 7'sd4;  end
            3'd4: begin m2 = 7'sd18; m1 = 7'sd6;  end
            3'd5: begin m2 = 7'sd20; m1 = 7'sd6;  end
            3'd6: begin m2 = 7'sd22; m1 = 7'sd8;  end
            3'd7: begin m2 = 7'sd24; m1 = 7'sd8;  end
        endcase
        if (pr_est >=  m2)       return Q_P2;
        else if (pr_est >=  m1)  return Q_P1;
        else if (pr_est >= -m1)  return Q_Z0;
        else if (pr_est >= -m2)  return Q_N1;
        else                     return Q_N2;
    endfunction

endpackage
