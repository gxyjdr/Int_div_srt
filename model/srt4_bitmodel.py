#!/usr/bin/env python3
"""
SRT-4 Bit-Level Behavioral Model
==================================
68-bit integer arithmetic, matching RTL exactly.
No Fraction, no floats — pure bitwise ops.

Verified against srt4_model.py (real-arithmetic) reference.
"""

MASK68 = (1 << 68) - 1
MASK66 = (1 << 66) - 1
MASK64 = (1 << 64) - 1
MASK7  = (1 << 7)  - 1

# QDS selection constants (7-bit signed integers, value/8 = SIII.FFF)
M2_TBL  = [12, 14, 16, 16, 18, 20, 22, 24]
M1_TBL  = [ 4,  4,  4,  4,  6,  6,  8,  8]

Q_P2, Q_P1, Q_Z0, Q_N1, Q_N2 = 0b010, 0b001, 0b000, 0b100, 0b101


def clz64(val):
    if val == 0: return 64
    n = 0
    for i in range(63, -1, -1):
        if val & (1 << i): return 63 - i
    return 64


def to_signed7(v):
    v &= MASK7
    return v if v < 64 else v - 128


def otf_update(q_digit, Q, QM):
    if q_digit == Q_P2:
        return ((Q << 2) | 2) & MASK66, ((Q << 2) | 1) & MASK66
    elif q_digit == Q_P1:
        return ((Q << 2) | 1) & MASK66, ((Q << 2) | 0) & MASK66
    elif q_digit == Q_Z0:
        return ((Q << 2) | 0) & MASK66, ((QM << 2) | 3) & MASK66
    elif q_digit == Q_N1:
        return ((QM << 2) | 3) & MASK66, ((QM << 2) | 2) & MASK66
    elif q_digit == Q_N2:
        return ((QM << 2) | 2) & MASK66, ((QM << 2) | 1) & MASK66
    return Q, QM


def srt4_divide(abs_A, abs_D, verbose=False):
    """Returns (Q_int, R) for unsigned division."""
    if abs_A == 0: return 0, 0
    if abs_D == 0: return (1 << 64) - 1, abs_A  # exception
    if abs_D == 1: return abs_A, 0

    lzc_A = clz64(abs_A)
    lzc_D = clz64(abs_D)
    K = lzc_D - lzc_A

    if K < 0:
        return 0, abs_A

    A_norm = (abs_A << lzc_A) & MASK64
    D_norm = (abs_D << lzc_D) & MASK64

    N = (K + 2 + 1) // 2 + 1  # ceil((K+2)/2) + 1

    # PR_0 = A_norm >> 1, placed in [63:0], [67:64]=0000
    PR_sum   = A_norm >> 1
    PR_carry = 0

    # D_aligned = D_norm << 1 → D_aligned/2^64 = D_norm/2^63 = D_math ✓
    D_aligned     = (D_norm << 1) & MASK68
    neg_D_aligned = (-D_aligned) & MASK68
    D_aligned_2x  = (D_aligned << 1) & MASK68
    neg_D_2x      = (-D_aligned_2x) & MASK68

    Q  = 0
    QM = 0

    for i in range(N):
        # 4·PR = PR << 2
        PR_sft = (PR_sum << 2) & MASK68
        CR_sft = (PR_carry << 2) & MASK68

        # pr_est = floor(8 · 4·PR_math), 7-bit signed
        # PR_math = PR_int/2^64, so 8·(4·PR_math) = (PR<<2)/2^61
        # Extract bits [67:61] of (PR<<2)
        pr_full = (PR_sft + CR_sft) & MASK68
        pr_est_raw = (pr_full >> 61) & MASK7  # bits [67:61]
        pr_est_s = to_signed7(pr_est_raw)

        # d_hat = D_norm[62:60]
        d_hat = (D_norm >> 60) & 0x7

        # QDS lookup
        if pr_est_s >= M2_TBL[d_hat]:
            q_val, q_digit = +2, Q_P2
        elif pr_est_s >= M1_TBL[d_hat]:
            q_val, q_digit = +1, Q_P1
        elif pr_est_s >= -M1_TBL[d_hat]:
            q_val, q_digit = 0, Q_Z0
        elif pr_est_s >= -M2_TBL[d_hat]:
            q_val, q_digit = -1, Q_N1
        else:
            q_val, q_digit = -2, Q_N2

        # Multiple: -q * D_aligned
        if q_val == +2:   mult = neg_D_2x
        elif q_val == +1: mult = neg_D_aligned
        elif q_val == 0:  mult = 0
        elif q_val == -1: mult = D_aligned
        else:             mult = D_aligned_2x  # q_val == -2

        # CSA-then-assimilate (single register for simplicity)
        PR_sum   = (PR_sft + CR_sft + mult) & MASK68
        PR_carry = 0

        Q, QM = otf_update(q_digit, Q, QM)

        if verbose:
            print(f"  i={i}: pr_est={pr_est_raw:07b}({pr_est_s:+d}) d_hat={d_hat:03b} q={q_val:+d}")

    # CORRECT
    PR_signed = PR_sum if PR_sum < (1 << 67) else PR_sum - (1 << 68)
    if PR_signed < 0:
        Q_corrected = QM
    else:
        Q_corrected = Q

    # Q_int extract: shift = 2N - K - 2
    shift = 2 * N - K - 2
    Q_int = Q_corrected >> shift

    # R = A - Q*D (direct)
    R = abs_A - Q_int * abs_D

    if verbose:
        print(f"  K={K} N={N} shift={shift}")
        print(f"  Q_corrected={Q_corrected} Q_int={Q_int} R={R}")

    return Q_int, R


def run_tests():
    import random
    random.seed(42)

    # Directed
    cases = [
        (69, 10), (1, 1), (7, 7), (1, 2), (100, 3),
        (255, 16), (1000, 7), (2**63 - 1, 2), (2**63 - 1, 2**62),
        (2**63 - 1, 2**63 - 1),
    ]
    fails = 0
    for A, D in cases:
        Q, R = srt4_divide(A, D)
        Qe, Re = A // D, A % D
        ok = (Q == Qe and R == Re)
        if not ok:
            fails += 1
            print(f"FAIL directed: A={A} D={D} Q={Q}({Qe}) R={R}({Re})")
            srt4_divide(A, D, verbose=True)

    # Random
    rand_fails = 0
    total = 10000
    for _ in range(total):
        A = random.randint(1, (1 << 63) - 1)
        D = random.randint(2, (1 << 63) - 1)
        Q, R = srt4_divide(A, D)
        Qe, Re = A // D, A % D
        if Q != Qe or R != Re:
            rand_fails += 1
            if rand_fails <= 5:
                print(f"FAIL random: A={A} D={D} Q={Q}({Qe}) R={R}({Re})")

    directed_total = len(cases)
    print(f"\nDirected: {directed_total - fails}/{directed_total} pass")
    print(f"Random:   {total - rand_fails}/{total} pass")
    return fails == 0 and rand_fails == 0


if __name__ == "__main__":
    run_tests()
