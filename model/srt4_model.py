#!/usr/bin/env python3
"""
SRT-4 Behavioral Model — Clean Rewrite
======================================
Convention (single source of truth):
  - PR_int is the integer value in PR register (68-bit signed)
  - D_int is D_norm (64-bit unsigned, MSB=bit 63 = always 1)
  - Recurrence: PR_int_new = 4·PR_int - q · D_int_aligned
    where D_int_aligned = D_int << 2 (so its data MSB at bit 65 aligns with 4·PR_int's MSB)
  - But wait: this makes D_int_aligned represent value 4·D_int.
    Math: PR_new_math = 4·PR_math - q·(4·D_int)/2^?
  - Simpler: use floats internally, then map to int at the end.

Let's redo from pure math:
  Define PR_math, D_math both as REAL numbers, do SRT in real arithmetic.
  Then map back to bit-level.

SRT-4 fractional algorithm:
  Pre:  PR_0 = A_frac, D = D_frac, both in [1/2, 1) or [1, 2)
        |PR_0| ≤ ρ·D  (ρ=2/3)
  Iter: q_i = QDS(4·PR_{i-1}, D)
        PR_i = 4·PR_{i-1} - q_i·D
        Q_red accumulates q_i with weight 4^(N-i)
  Post: PR_N satisfies |PR_N| ≤ ρ·D
        Q_OTF = Σ q_i · 4^(N-i)  (integer)
        A_frac/D = Q_OTF / 4^(N-1) approximately (with PR_N residual)

Integer mapping for 64-bit divide:
  A_norm = A << lzc_A,  D_norm = D << lzc_D    (both have MSB at bit 63)
  Define A_math = A_norm / 2^64  ∈ [1/2, 1)
  Define D_math = D_norm / 2^63  ∈ [1, 2)
  Then A_math/D_math = (A_norm/D_norm) / 2  = A/D · 2^(K-1)  where K=lzc_D-lzc_A
  So  A/D = (A_math/D_math) · 2^(1-K)

  PR_0_math = A_math  (assume PR_0 = A_math, OK since |A_math/D_math| ≤ 1/2 < ρ ✓)

  After N iters, Q_red ≈ 4^N · A_math/D_math
  So Q_int ≈ floor(Q_red · 2^(1-K) / 4^... ) — need careful derivation

For clean implementation, I'll do REAL-valued SRT and verify, then bit-map.
"""

from fractions import Fraction

# QDS table — m_k constants in 1/8 units (real values m_k/8)
# d_hat 3-bit: D_math ∈ [1 + d_hat/8, 1 + (d_hat+1)/8)
M2_TBL  = [12, 14, 16, 16, 18, 20, 22, 24]
M1_TBL  = [ 4,  4,  4,  4,  6,  6,  8,  8]

def qds_real(pr_4x, D):
    """Inputs: real numbers 4·PR and D. Returns q ∈ {-2..+2}."""
    # 1/8 grid: pr_est_int = floor(8·(4·PR))  (signed)
    import math
    pr_est = math.floor(8 * pr_4x)
    # Clip pr_est to 7-bit signed [-64, +63]
    if pr_est > 63: pr_est = 63
    if pr_est < -64: pr_est = -64
    # d_hat from D
    d_hat = int(8 * (D - 1))  # D = 1 + d_hat/8
    if d_hat > 7: d_hat = 7
    if d_hat < 0: d_hat = 0
    m2 = M2_TBL[d_hat]
    m1 = M1_TBL[d_hat]
    if pr_est >= m2:
        return +2
    elif pr_est >= m1:
        return +1
    elif pr_est >= -m1:
        return 0
    elif pr_est >= -m2:
        return -1
    else:
        return -2

def srt4_real(A, D, verbose=False):
    """Pure real-arithmetic SRT-4 for verification.
    Inputs: A, D positive integers, A/D well-defined.
    Returns: Q_int, R."""
    if A == 0: return 0, 0
    if D == 0: return None, A  # exception
    if A < D: return 0, A
    if D == 1: return A, 0

    # Normalize
    def clz(x):
        for i in range(63, -1, -1):
            if x & (1 << i): return 63 - i
        return 64
    lzc_A = clz(A)
    lzc_D = clz(D)
    K = lzc_D - lzc_A
    N = max(1, (K + 2 + 1) // 2)

    A_norm = A << lzc_A
    D_norm = D << lzc_D
    # math values
    A_math = Fraction(A_norm, 1 << 64)  # ∈ [1/2, 1)
    D_math = Fraction(D_norm, 1 << 63)  # ∈ [1, 2)

    # PR_0 = A_math/2 to guarantee |PR_0/D| < 1/2 < ρ
    # (A_math can be near 1, D_math near 1, so A_math/D_math near 1 — violates ρ)
    PR = A_math / 2  # extra factor 1/2

    Q_red = 0
    q_list = []
    # N needs +1 extra iteration to compensate for PR_0 = A_math/2
    N = N + 1
    for i in range(N):
        pr_4x = 4 * PR
        q = qds_real(pr_4x, D_math)
        PR = pr_4x - q * D_math
        Q_red = 4 * Q_red + q
        q_list.append(q)
        if verbose:
            print(f"  i={i}: 4·PR={float(pr_4x):.4f}, D={float(D_math):.4f}, q={q:+d}, "
                  f"PR_new={float(PR):.4f}, Q_red={Q_red}")

    # CORRECT
    if PR < 0:
        Q_red -= 1
        PR += D_math
    # Now |PR| < D, R_math = PR · D_norm·? hmm

    # Extract Q_int:
    # PR_0 = A_math/2, so A/D = (PR_0/D_math) · 2^(K+2)
    # Q_red ≈ 4^N · PR_0/D_math = (A/D) · 4^N / 2^(K+2) = (A/D) · 2^(2N - K - 2)
    # → A/D ≈ Q_red / 2^(2N - K - 2)
    shift = 2*N - K - 2
    if shift < 0:
        Q_int = Q_red << (-shift)
    elif shift > 64:
        Q_int = 0
    else:
        Q_int = Q_red >> shift
    R = A - Q_int * D
    if verbose:
        print(f"  Q_red={Q_red}, shift={shift}, Q_int={Q_int}, R={R}")
    return Q_int, R


def test():
    cases = [
        (69, 10), (1, 1), (7, 7), (1, 2), (100, 3),
        (2**62, 3), (2**63 - 1, 2), (255, 16), (1000, 7),
    ]
    fails = []
    for A, D in cases:
        Q, R = srt4_real(A, D, verbose=True)
        Qe = A // D
        Re = A % D
        ok = (Q == Qe and R == Re)
        status = "PASS" if ok else "FAIL"
        print(f"{status}: A={A} D={D} Q={Q}({Qe}) R={R}({Re})")
        if not ok: fails.append((A, D))
    print(f"\n{len(cases)-len(fails)}/{len(cases)} pass")
    return fails

if __name__ == "__main__":
    test()
