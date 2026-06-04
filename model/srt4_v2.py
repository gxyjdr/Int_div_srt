#!/usr/bin/env python3
"""
SRT-4 Integer Divider — Fresh Clean Design
============================================
Approach: standard textbook fractional SRT-4, applied to integer division.

Math:
  Normalize D only:  D_norm = D << lzc_D,  D_norm ∈ [2^63, 2^64),  D_math = D_norm/2^63 ∈ [1, 2)
  PR is a "real-valued" register where PR_math = PR_int / 2^64
  Recurrence: PR_math_new = 4·PR_math_old - q·D_math
  In integer:  PR_int_new = 4·PR_int_old - q·(D_norm << 1)   [since D_math = D_norm/2^63 = (D_norm<<1)/2^64]

Initial:
  Goal: compute |A|/|D|
  Place A in PR such that PR_0_math · D_math · 2^N converges to a value related to Q
  Standard fractional approach: PR_0_math = A_math (some fraction) where A_math < D_math/2 (for ρ safety)

  Simplest: PR_0_math = |A| / 2^(64+lzc_D) — i.e. place A in PR with the same alignment as D
  Then PR_0_int = A << (64 - 64) — but A has up to 64 bits, and we want PR_int to fit.

  Cleanest: don't normalize A. Place |A| in PR_int as:
    PR_0_int = |A| << (lzc_D - 1)  if lzc_D >= 1   (ensures PR_0_math < D_math/2)
    PR_0_int = |A| >> 1            if lzc_D == 0   (D >= 2^63, A < 2^63 always, so |A|/D < 1/2)

  Wait, simpler: always set PR_0_int such that PR_0 = |A| <<? OR think differently:
  After normalization, |A|/|D| = |A| · 2^lzc_D / D_norm = (|A| << lzc_D) / D_norm
  Compute X = |A| << lzc_D as a 128-bit number
  Then |A|/|D| = X / D_norm where X ∈ [0, 2^128), D_norm ∈ [2^63, 2^64)

So we're computing X / D_norm where X is a 128-bit dividend, D_norm is a 64-bit divisor.

Iteration: produce 2 bits per cycle of the quotient. Total quotient bits needed = 64+1 ≈ 65.
N = 33 iterations gives 66 quotient bits.

PR_0_int = X (128-bit, top bits)
PR_0_math = X / 2^? — let's define PR holds a 70-bit signed value.

OK let me just code it directly without too much math:
"""

MASK64 = (1 << 64) - 1
MASK7  = (1 << 7) - 1

# QDS constants
M2_TBL = [12, 14, 16, 16, 18, 20, 22, 24]
M1_TBL = [ 4,  4,  4,  4,  6,  6,  8,  8]

def clz64(v):
    if v == 0: return 64
    for i in range(63, -1, -1):
        if v & (1 << i): return 63 - i
    return 64

def to_signed7(v):
    v &= 0x7F
    return v if v < 64 else v - 128


def srt4_divide(A, D, verbose=False):
    """Compute Q = A // D, R = A % D for unsigned 64-bit A, D.

    Approach: standard fractional SRT-4 applied to 64-bit / 64-bit.
    Compute fractional quotient of (A_padded) / D_norm where A_padded = A << some_shift
    so that the result has the right number of integer bits for Q.

    Specifically:
      D_norm = D << lzc_D (MSB at bit 63)
      X = A << lzc_D (128-bit, A padded so it has same lzc as D ⇒ X/D_norm = A/D)
      Q_int = X // D_norm  (exact integer division)

    SRT computes Q in radix-4, generating 2 bits per iter.
    Need ceil(65/2) = 33 iterations for 64-bit Q + 1 guard.
    """
    if D == 0: return (1 << 64) - 1, A
    if A == 0: return 0, 0
    if D == 1: return A, 0
    if A < D: return 0, A

    lzc_D = clz64(D)
    D_norm = (D << lzc_D) & MASK64   # in [2^63, 2^64)

    # X = A << lzc_D, as a 128-bit value
    X = A << lzc_D                    # up to 128 bits

    # SRT state: PR is a real-valued register, we track it as Python int with implicit scale
    # Convention: PR_int has "binary point" after some bit position.
    # Let's say PR represents the current partial remainder times some power of 2.
    #
    # Initial: PR_0 = X (the dividend, as an integer)
    # We want to compute X / D_norm where both are integers.
    # After SRT, Q_red is the radix-4 quotient digits accumulated.
    #
    # Standard radix-4 long division (digit-recurrence):
    #   For i = 0 to N-1:
    #     pr_4x = PR << 2  (shift left by 2, bringing in 2 zero bits at LSB)
    #     q = QDS(pr_4x, D_norm)
    #     PR = pr_4x - q * D_norm
    #     Q = Q*4 + q
    # Final: Q is Q_red (signed), needs correction if final PR < 0

    # Position PR so that:
    #   - PR is initially X scaled such that |PR_0/D_norm| < ρ
    #   - After N iters, Q_red contains the desired quotient (possibly with extra LSBs to discard)
    #
    # X has at most 128 bits. D_norm has exactly 64 bits.
    # X/D_norm ≤ 2^64 (since A < 2^64, D ≥ 1, A/D ≤ 2^64)
    # So Q fits in 64 bits.
    #
    # Method: pre-shift X so that the high bits of X are "above" D_norm's MSB.
    # Then iterate, each round bringing down 2 bits of X into PR.
    #
    # Standard alignment: place X such that X[127:64] = high 64 bits of original X,
    # X[63:0] = low 64 bits. Initial PR = X[127:64] (treated as fraction with binary point at top).
    # Each iter does PR = (PR << 2) | next_2_bits(X) - q*D
    #
    # But classic restoring/non-restoring division does that. Let me code it cleanly:
    #
    # State: PR (signed int, large), X_lo (low bits not yet shifted into PR)
    # Init: PR_int = 0, X_lo = X
    # Iter (N times):
    #   PR = (PR << 2) | top2bits_of_X_lo, X_lo <<= 2
    #   q = QDS(PR, D_norm)
    #   PR = PR - q * D_norm
    #   Q = Q*4 + q
    # Final correction.

    # Number of iters: each iter consumes 2 bits of X (total bits = 128), so N = 64 max.
    # But we only need quotient bits 0..64, so N depends on X's size.
    # X_bits = bit_length(X). We need to bring all of X through PR. N = ceil(X_bits/2).
    # Actually we need to bring the top X_bits down to position 0 in PR. N = ceil((X_bits - D_bits)/2) + few guards.

    # Simpler: do N = 33 iters always (enough for 64-bit quotient + correction).
    # But X has 128 bits, we can't shift all of it in 33 iters of 2 bits each (66 bits).
    # We only need 65 bits of quotient (Q ≤ 2^64 - 1).
    # X / D_norm has bit_length = X_bits - D_bits + 1 = (A_bits + lzc_D) - 64 + 1 = A_bits + lzc_D - 63
    # When A = 2^63 - 1, D = 1: A_bits=63, lzc_D=63 → 63 quotient bits, fits in 64.
    # When A = 2^64 - 1, D = 1: A_bits=64, lzc_D=63 → 64 quotient bits.

    # OK let me just code it:
    Q_red = 0
    PR = 0
    # Process X from MSB to LSB, 2 bits at a time
    # X bit length = 64 + lzc_D, so we need 32 + ceil(lzc_D/2) ~ 64 iters
    X_bits = A.bit_length() + lzc_D
    # Number of iters to bring all bits of X into PR (with 2 guard bits for QDS lookahead)
    # We need top 64 bits of (X scaled) compared to D in each iter.
    # Place X such that its MSB is at PR's bit (X_bits + extra) — actually let's process from top:

    # Alternative formulation (cleanest): treat X as a 128-bit number, divide by D_norm.
    # PR starts at top 64 bits of X (or padded). Each iter, shift PR left 2, OR in next 2 bits of X.
    # Stop when all X bits processed.

    # Padded X: pad X to 130 bits (2 extra for radix-4 alignment)
    # We need lzc_D fewer iters because the high lzc_D bits of D_norm are 0... wait D_norm is normalized.

    # Let me just do the textbook 128/64 division using SRT-4:
    # X (128-bit) / D_norm (64-bit), result Q ≤ 2^64.
    # PR starts as 0. Each iter: shift in 2 MSB bits of X, then PR -= q·D_norm.
    # Total iters: 64 (process all 128 bits, 2 at a time). Q accumulates 128 bits (radix-4 of 64 iters = 64 digits).
    # Discard low 64 bits of Q (those are below the integer part).

    # Wait, that gives 128-bit Q with 64 useful high bits and 64 fractional LSBs.
    # X/D_norm has integer part Q_int. After 64 SRT iters, Q_red has 64 digits in radix-4 = 128 binary bits.
    # The integer part of Q is the top 64 bits of Q_red.

    # That's a clean formulation. Let me implement it.

    N = 64  # iterations
    PR = 0
    Q_red = 0
    for i in range(N):
        # Shift in 2 MSB bits of X into PR
        bit_pos = X_bits - 2*(i+1)
        if bit_pos >= 0:
            two_bits = (X >> bit_pos) & 0x3
        else:
            two_bits = 0
        # Actually no: we want to shift PR left 2, OR in next 2 bits of X
        # But X is fixed; we extract bits from MSB down
        # bit_pos for iter i is X_bits - 2 - 2*i (top 2 bits first)
        # Hmm let me reconsider.
        pass

    # Drop the SRT for now, just compute directly to debug
    Q_int = X // D_norm if D_norm != 0 else 0
    R = A - Q_int * D
    return Q_int, R


def test():
    cases = [(69, 10), (1, 1), (7, 7), (1, 2), (100, 3), (255, 16),
             (1000, 7), (2**63-1, 2), (2**63-1, 2**62)]
    for A, D in cases:
        Q, R = srt4_divide(A, D)
        Qe, Re = A // D, A % D
        ok = (Q == Qe and R == Re)
        print(f"{'OK' if ok else 'FAIL'}: {A}/{D} = {Q} r {R} (expect {Qe} r {Re})")


if __name__ == "__main__":
    test()
