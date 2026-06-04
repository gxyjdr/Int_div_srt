#!/usr/bin/env python3
"""
SRT-4 Bit-Level Model — 68-bit PR, revised 2026-05-30
=====================================================
Changes:
  - PR_0 = A_norm (no >>1), eliminates unsigned MSB=1 LSB loss bug
  - D_scaled = D_norm << 2 (was <<1), keeps PR_math/D_math invariant
  - pr_est from pr_q[66:60] directly (was pr_4x[67:61])
  - N = ceil((K+2)/2) = (K+3)//2 (removed +1 from float SRT GRS margin)
  - R = PR-based recovery (no 64x64 multiplier)
  - Q_WIDTH = 64 (was 66), MAX_ITER = 32 (was 34)

Mapping (new):
  PR_math = PR_int / 2^65
  D_math  = D_norm / 2^63
  D_scaled = D_norm << 2  (so D_scaled/2^65 = D_math)
  pr_est = floor(32*PR_math) = PR_int >> 60, bits [66:60]
  d_hat  = D_norm[62:60]
"""

MASK68 = (1 << 68) - 1
MASK64 = (1 << 64) - 1
MASK7  = (1 << 7) - 1

M2_TBL = [12, 14, 16, 16, 18, 20, 22, 24]
M1_TBL = [ 4,  4,  4,  4,  6,  6,  8,  8]

Q_P2, Q_P1, Q_Z0, Q_N1, Q_N2 = 0b010, 0b001, 0b000, 0b100, 0b101


def clz64(v):
    if v == 0: return 64
    for i in range(63, -1, -1):
        if v & (1 << i): return 63 - i
    return 64


def to_signed68(v):
    v &= MASK68
    return v if v < (1 << 67) else v - (1 << 68)


def to_signed7(v):
    v &= MASK7
    return v if v < 64 else v - 128


def otf_update(q_digit, Q, QM):
    if q_digit == Q_P2:
        return ((Q << 2) | 2) & MASK64, ((Q << 2) | 1) & MASK64
    elif q_digit == Q_P1:
        return ((Q << 2) | 1) & MASK64, ((Q << 2) | 0) & MASK64
    elif q_digit == Q_Z0:
        return ((Q << 2) | 0) & MASK64, ((QM << 2) | 3) & MASK64
    elif q_digit == Q_N1:
        return ((QM << 2) | 3) & MASK64, ((QM << 2) | 2) & MASK64
    elif q_digit == Q_N2:
        return ((QM << 2) | 2) & MASK64, ((QM << 2) | 1) & MASK64
    return Q, QM


def srt4_divide(abs_A, abs_D, verbose=False):
    if abs_A == 0: return 0, 0
    if abs_D == 0: return (1 << 64) - 1, abs_A
    if abs_D == 1: return abs_A, 0

    lzc_A = clz64(abs_A)
    lzc_D = clz64(abs_D)
    K = lzc_D - lzc_A

    if K < 0: return 0, abs_A

    A_norm = (abs_A << lzc_A) & MASK64
    D_norm = (abs_D << lzc_D) & MASK64

    N = (K + 3) >> 1  # ceil((K+2)/2), no +1

    # PR_0 = A_norm (zero-extended to 68 bits, no right shift)
    PR_int = A_norm

    # D_scaled = D_norm << 2
    D_scaled     = (D_norm << 2) & MASK68
    D_scaled_2x  = (D_norm << 3) & MASK68

    Q = 0
    QM = 0

    for i in range(N):
        pr_4x = PR_int << 2

        # QDS: pr_est = pr_q[66:60] (directly from PR, not pr_4x)
        pr_est_raw = (PR_int >> 60) & MASK7
        pr_est_s = to_signed7(pr_est_raw)

        d_hat = (D_norm >> 60) & 0x7

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

        if q_val == +2:   mult = (-D_scaled_2x) & MASK68
        elif q_val == +1: mult = (-D_scaled) & MASK68
        elif q_val == 0:  mult = 0
        elif q_val == -1: mult = D_scaled
        else:             mult = D_scaled_2x

        PR_int = (pr_4x + mult) & MASK68
        Q, QM = otf_update(q_digit, Q, QM)

        if verbose:
            print(f"  i={i}: pr_est={pr_est_raw:07b}({pr_est_s:+d}) d_hat={d_hat:03b} q={q_val:+d}")

    # CORRECT — modify PR (needed for PR-based R recovery)
    PR_signed = to_signed68(PR_int)
    if PR_signed < 0:
        Q_corrected = QM
        PR_int = (PR_int + D_scaled) & MASK68
    else:
        Q_corrected = Q

    shift = 2 * N - 2 - K
    Q_int = Q_corrected >> shift

    # R = PR-based recovery
    if shift == 0:
        R = PR_int >> (lzc_D + 2)
    else:
        b = Q_corrected & 1
        R = ((PR_int >> 2) + b * D_norm) >> (lzc_D + 1)

    if verbose:
        print(f"  K={K} N={N} shift={shift}")
        print(f"  Q_corrected={Q_corrected} Q_int={Q_int} R={R}")

    return Q_int, R


def srt4_divide_csa(abs_A, abs_D, verbose=False):
    """CSA-based SRT-4 divide — redundant pr_sum + pr_carry representation."""
    if abs_A == 0: return 0, 0
    if abs_D == 0: return (1 << 64) - 1, abs_A
    if abs_D == 1: return abs_A, 0

    lzc_A = clz64(abs_A)
    lzc_D = clz64(abs_D)
    K = lzc_D - lzc_A

    if K < 0: return 0, abs_A

    A_norm = (abs_A << lzc_A) & MASK64
    D_norm = (abs_D << lzc_D) & MASK64

    N = (K + 3) >> 1

    # CSA initial state: pr_sum = A_norm, pr_carry = 0
    pr_sum = A_norm
    pr_carry = 0

    D_scaled = (D_norm << 2) & MASK68
    D_scaled_2x = (D_norm << 3) & MASK68

    Q = 0
    QM = 0

    for i in range(N):
        # Shift by 2 (radix-4)
        pr_4x_sum = (pr_sum << 2) & MASK68
        pr_4x_carry = (pr_carry << 2) & MASK68

        # QDS estimate: non-redundant PR[66:60] (narrow CPA)
        PR_non_red = (pr_sum + pr_carry) & MASK68
        pr_est_raw = (PR_non_red >> 60) & MASK7
        pr_est_s = to_signed7(pr_est_raw)

        d_hat = (D_norm >> 60) & 0x7

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

        if q_val == +2:   mult = (-D_scaled_2x) & MASK68
        elif q_val == +1: mult = (-D_scaled) & MASK68
        elif q_val == 0:  mult = 0
        elif q_val == -1: mult = D_scaled
        else:             mult = D_scaled_2x

        # 3:2 CSA (XOR + majority, no carry chain)
        pr_sum_next = (pr_4x_sum ^ pr_4x_carry ^ mult) & MASK68
        carry_raw = (pr_4x_sum & pr_4x_carry) | (pr_4x_sum & mult) | (pr_4x_carry & mult)
        pr_carry_next = (carry_raw << 1) & MASK68

        pr_sum = pr_sum_next
        pr_carry = pr_carry_next
        Q, QM = otf_update(q_digit, Q, QM)

        if verbose:
            print(f"  i={i}: pr_est={pr_est_raw:07b}({pr_est_s:+d}) d_hat={d_hat:03b} q={q_val:+d}")

    # CORRECT — merge sum+carry to non-redundant PR
    PR_int = (pr_sum + pr_carry) & MASK68

    PR_signed = to_signed68(PR_int)
    if PR_signed < 0:
        Q_corrected = QM
        PR_int = (PR_int + D_scaled) & MASK68
    else:
        Q_corrected = Q

    shift = 2 * N - 2 - K
    Q_int = Q_corrected >> shift

    if shift == 0:
        R = PR_int >> (lzc_D + 2)
    else:
        b = Q_corrected & 1
        R = ((PR_int >> 2) + b * D_norm) >> (lzc_D + 1)

    if verbose:
        print(f"  K={K} N={N} shift={shift}")
        print(f"  Q_corrected={Q_corrected} Q_int={Q_int} R={R}")

    return Q_int, R


def test():
    cases = [
        (69, 10), (1, 1), (7, 7), (1, 2), (100, 3), (255, 16),
        (1000, 7), (2**63-1, 2), (2**63-1, 2**62),
        (2**63-1, 2**63-1), (123456789, 1234),
    ]
    fails = 0
    csa_fails = 0
    for A, D in cases:
        Q, R = srt4_divide(A, D)
        Qe, Re = A // D, A % D
        ok = (Q == Qe and R == Re)
        if not ok:
            fails += 1
            print(f"FAIL CPA: {A}/{D} -> Q={Q}({Qe}) R={R}({Re})")
        else:
            print(f"PASS CPA: {A}/{D} = {Q} r {R}")

        Qc, Rc = srt4_divide_csa(A, D)
        okc = (Qc == Qe and Rc == Re)
        if not okc:
            csa_fails += 1
            print(f"FAIL CSA: {A}/{D} -> Q={Qc}({Qe}) R={Rc}({Re})")

    # Signed random (0 .. 2^63-1)
    import random
    random.seed(42)
    rand_fails = 0
    csa_rand_fails = 0
    total = 10000
    for _ in range(total):
        A = random.randint(1, (1 << 63) - 1)
        D = random.randint(2, (1 << 63) - 1)
        Q, R = srt4_divide(A, D)
        Qe, Re = A // D, A % D
        if Q != Qe or R != Re:
            rand_fails += 1
            if rand_fails <= 5:
                print(f"FAIL CPA signed: {A}/{D} -> Q={Q}({Qe}) R={R}({Re})")

        Qc, Rc = srt4_divide_csa(A, D)
        if Qc != Qe or Rc != Re:
            csa_rand_fails += 1
            if csa_rand_fails <= 5:
                print(f"FAIL CSA signed: {A}/{D} -> Q={Qc}({Qe}) R={Rc}({Re})")

    # Unsigned random (0 .. 2^64-1), including MSB=1
    urand_fails = 0
    csa_urand_fails = 0
    utotal = 10000
    for _ in range(utotal):
        A = random.randint(1, (1 << 64) - 1)
        D = random.randint(2, (1 << 64) - 1)
        Q, R = srt4_divide(A, D)
        Qe, Re = A // D, A % D
        if Q != Qe or R != Re:
            urand_fails += 1
            if urand_fails <= 5:
                print(f"FAIL CPA unsigned: {A}/{D} -> Q={Q}({Qe}) R={R}({Re})")

        Qc, Rc = srt4_divide_csa(A, D)
        if Qc != Qe or Rc != Re:
            csa_urand_fails += 1
            if csa_urand_fails <= 5:
                print(f"FAIL CSA unsigned: {A}/{D} -> Q={Qc}({Qe}) R={Rc}({Re})")

    print(f"\nCPA results:")
    print(f"  Directed: {len(cases)-fails}/{len(cases)}")
    print(f"  Random signed:   {total-rand_fails}/{total}")
    print(f"  Random unsigned: {utotal-urand_fails}/{utotal}")
    print(f"CSA results:")
    print(f"  Directed: {len(cases)-csa_fails}/{len(cases)}")
    print(f"  Random signed:   {total-csa_rand_fails}/{total}")
    print(f"  Random unsigned: {utotal-csa_urand_fails}/{utotal}")


if __name__ == "__main__":
    test()
