#!/usr/bin/env python3
"""
SRT-4 — Take 3: Standard non-restoring radix-4 division
=========================================================
Computes A // D for 64-bit unsigned A, D.

Algorithm:
  1. Normalize D: D_norm = D << lzc_D, MSB at bit 63
  2. Form 128-bit X = A << lzc_D (so X / D_norm = A / D)
  3. PR_0 = (X << 2) >> 128 ... no wait

Simplest correct formulation: simulate textbook restoring division but with radix-4 SRT digits.

State:
  R: current partial remainder, signed Python int
  X: original 128-bit dividend (constant during iter, we process bits MSB-down)
  Q: accumulated quotient (Python int, signed digits)

Iteration i (from 0 to N-1):
  R = R * 4 + (top 2 bits of X not yet consumed)
  q = QDS(R, D_norm)
  R -= q * D_norm
  Q = Q*4 + q

After iteration:
  If R < 0: R += D_norm; Q -= 1
  Return Q as quotient, R >> lzc_D as remainder

Number of iterations: enough to consume all 128 bits of X (N=64 if we always shift 2 bits).
But we only need 65 quotient bits, so N=33 with smart initialization.

For simplicity, use N=64 (always safe, just slow). Optimize later.
"""

MASK64 = (1 << 64) - 1


def clz64(v):
    if v == 0: return 64
    for i in range(63, -1, -1):
        if v & (1 << i): return 63 - i
    return 64


def qds_ideal(R, D):
    """Ideal QDS: pick q ∈ {-2..2} such that |R - q·D| ≤ ρ·D (ρ=2/3).
    R is signed int, D is positive int."""
    # Pre-check: R should be in [-ρ·D · 4, ρ·D · 4] coming in (it's 4·prev_R)
    # We try each q from most-negative to most-positive, pick first that works
    rho_D_3 = 2 * D  # 3 * ρ * D = 3 * (2/3) * D = 2D, so |R - q·D| * 3 ≤ 2D
    for q in [-2, -1, 0, 1, 2]:
        diff = R - q * D
        if -2 * D <= 3 * diff <= 2 * D:
            return q
    # Should never reach here if invariant holds
    return max(-2, min(2, R // D))


def srt4_divide(A, D, verbose=False):
    """Compute (Q, R) = (A // D, A % D) for 64-bit unsigned A, D."""
    if D == 0: return (1 << 64) - 1, A
    if A == 0: return 0, 0
    if A < D: return 0, A
    if D == 1: return A, 0

    lzc_D = clz64(D)
    D_norm = (D << lzc_D) & MASK64
    X = A << lzc_D  # up to 128 bits

    X_bits = X.bit_length()  # number of significant bits in X
    # We'll process X from MSB down. To match standard SRT,
    # pad X so its MSB is at a known position.
    # Pad X up to 128 bits (or 130 with 2 guard bits)
    TOTAL_BITS = 128

    # Number of iterations needed:
    # Process 2 bits per iter. Starting from PR=0, after N iters PR contains the
    # remainder of (top 2N bits of X) / D_norm.
    # We need to process enough bits so the remainder corresponds to X/D_norm.
    # X has X_bits bits, D_norm has 64 bits.
    # Top 64 bits of X / D_norm gives the high quotient bit.
    # Total quotient bits = X_bits - 64 + (1 for guard) = up to 65.
    # So N iterations producing 2 bits each: N = ceil(65/2) = 33.
    # But we need to bring in X_bits - 64 bits of X for the integer part,
    # plus 64 more bits for the fractional part (which we discard).
    # Total bits to bring in = X_bits. N = ceil(X_bits / 2).

    # Simpler: process X from MSB, exactly X_bits/2 iters (rounded up).
    N = (X_bits + 1) // 2 + 1  # extra for guard

    # But X may have leading zeros in our 128-bit representation. We start consuming
    # from bit X_bits-1 (the MSB).

    PR = 0
    Q_red = 0

    for i in range(N):
        # Bits to consume this iter: positions [X_bits-1 - 2i, X_bits-2 - 2i]
        hi = X_bits - 1 - 2 * i
        lo = hi - 1
        if hi < 0:
            b1, b0 = 0, 0
        else:
            b1 = (X >> hi) & 1
            b0 = (X >> lo) & 1 if lo >= 0 else 0
        two_bits = (b1 << 1) | b0

        PR = PR * 4 + two_bits
        q = qds_ideal(PR, D_norm)
        PR = PR - q * D_norm
        Q_red = Q_red * 4 + q

        if verbose:
            print(f"  i={i}: bits={two_bits:02b} pre_PR_pre={PR + q*D_norm} q={q:+d} PR={PR} Q_red={Q_red}")

    # CORRECT
    if PR < 0:
        PR += D_norm
        Q_red -= 1

    # Q_red is the quotient of X/D_norm = A/D when X bits are fully consumed
    # But we may have brought in 2N bits while X only has X_bits bits.
    # Extra bits brought in (zeros) shift Q_red by 2*(N - ceil(X_bits/2)) positions.
    # We need to right-shift Q_red by that amount.

    bits_consumed = 2 * N
    extra_shift = bits_consumed - X_bits  # number of zero bits we shifted in beyond X
    if extra_shift > 0:
        # Q_red contains (correct quotient) << extra_shift
        # Truncate the low extra_shift bits
        # But we also need to handle the remainder properly
        # The remainder PR is (X << extra_shift) - Q_red·D_norm
        # → X - (Q_red >> extra_shift)·D_norm = (PR + (Q_red & mask)·D_norm) >> extra_shift
        # Final integer Q = Q_red >> extra_shift; r_low = Q_red & ((1<<extra_shift)-1)
        # Final R = (PR + r_low·D_norm) >> extra_shift
        r_low = Q_red & ((1 << extra_shift) - 1)
        Q_int = Q_red >> extra_shift
        R_norm = (PR + r_low * D_norm) >> extra_shift
    else:
        Q_int = Q_red
        R_norm = PR

    # R_norm is remainder of X/D_norm. Unshift: R = R_norm >> lzc_D
    R = R_norm >> lzc_D

    if verbose:
        print(f"  N={N} X_bits={X_bits} extra_shift={extra_shift}")
        print(f"  Q_red={Q_red} Q_int={Q_int} R_norm={R_norm} R={R}")

    return Q_int, R


def test():
    cases = [
        (69, 10), (1, 1), (7, 7), (1, 2), (100, 3), (255, 16),
        (1000, 7), (2**63-1, 2), (2**63-1, 2**62),
        (2**63-1, 2**63-1), (123456789, 1234),
    ]
    fails = 0
    for A, D in cases:
        Q, R = srt4_divide(A, D)
        Qe, Re = A // D, A % D
        ok = (Q == Qe and R == Re)
        if not ok:
            fails += 1
            print(f"FAIL: {A}/{D} → Q={Q}({Qe}) R={R}({Re})")
            srt4_divide(A, D, verbose=True)
        else:
            print(f"PASS: {A}/{D} = {Q} r {R}")

    import random
    random.seed(42)
    rand_fails = 0
    total = 10000
    for _ in range(total):
        A = random.randint(1, (1<<63)-1)
        D = random.randint(2, (1<<63)-1)
        Q, R = srt4_divide(A, D)
        Qe, Re = A // D, A % D
        if Q != Qe or R != Re:
            rand_fails += 1
            if rand_fails <= 5:
                print(f"FAIL random: {A}/{D} → Q={Q}({Qe}) R={R}({Re})")

    print(f"\nDirected: {len(cases)-fails}/{len(cases)}")
    print(f"Random:   {total-rand_fails}/{total}")


if __name__ == "__main__":
    test()
