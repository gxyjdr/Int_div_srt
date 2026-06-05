#!/usr/bin/env python3
"""
QDS 表缩减 — 实用方法

对现有的阈值表 (M1/M2 或 SRT-8 的 M1~M4)，
求每个 d_hat 的最小 pr_est bit 数，以及整个表的最小截断。
"""
import math


# =============================================================================
# SRT-4 ρ=2/3 阈值 (当前实现)
# =============================================================================
SRT4_THRESHOLDS = {
    # d_hat -> (M2, M1)
    0: (12, 4),
    1: (14, 4),
    2: (16, 4),
    3: (16, 4),
    4: (18, 6),
    5: (20, 6),
    6: (22, 8),
    7: (24, 8),
}


# =============================================================================
# SRT-8 ρ=4/7 阈值
# 标准 P-D 图推导得出
# =============================================================================
def compute_srt8_thresholds_rho_4_7():
    """
    SRT-8 ρ=4/7 的阈值

    r=8, ρ=4/7, digit set {-4,-3,-2,-1,0,+1,+2,+3,+4}
    a_max = 4 (max |q|)

    商选公式：
    q = m  当 (m - ρ)·D ≤ r·PR ≤ (m + ρ)·D
    阈值在 m 和 m+1 的重叠区内选择

    这里取标准中点法：
    T_m = (m + 1 - ρ/2) 或者
    边界在 r·PR = (m + ρ/2)·D
    """
    r = 8
    rho = 4/7

    # D 归一化到 [1, 2)，用 δ bit 量化
    # 对每个 Z (截断 D)，计算相邻商位的分界 P 值
    #
    # 阈值 T_m 是 q=m 和 q=m+1 的分界
    # 在标准 P-D 方法中，T_m 放在重叠区内：
    # (m - ρ)·D ≤ r·PR ≤ (m+1 - ρ)·D  → 选 q=m
    # r·PR > (m+1 - ρ)·D  → 选 q=m+1
    #
    # 保守阈值（确保正确性）：
    # T_m(D) = (m+1-ρ)·D  (q=m+1 的下界，移至此值必定≥q=m+1)

    print("SRT-8 ρ=4/7: 计算阈值表...")
    thresholds = {}

    for d_int in range(1, 16):  # 4-bit d_hat: 1.0000 ~ 1.1111
        Z = 1.0 + d_int / 16.0  # D 的区间中点（近似）
        thresh = {}
        for m in range(1, 5):  # 正半轴 m=1..4
            # T_m: 从 q=m 切换到 q=m+1 的边界
            # 放在重叠区: (m+1-ρ)·D ≤ T_m ≤ (m+ρ)·D
            # 取中点: T_m = (m+0.5)·D  (标准实现)
            t = (m + 0.5) * Z
            thresh[m] = round(t, 6)
        thresholds[d_int] = thresh

    return thresholds


def compute_srt8_thresholds_rho_6_7():
    """
    SRT-8 ρ=6/7 的阈值
    digit set {-6,...,+6}
    """
    r = 8
    rho = 6/7
    thresholds = {}
    for d_int in range(1, 16):
        Z = 1.0 + d_int / 16.0
        thresh = {}
        for m in range(1, 7):  # m=1..6
            t = (m + 0.5) * Z
            thresh[m] = round(t, 6)
        thresholds[d_int] = thresh
    return thresholds


# =============================================================================
# 最小截断分析
# =============================================================================

def analyze_bit_width(thresholds_dict, digit_range, max_d_hat_bits=4):
    """
    分析每个 d_hat 需要的最小 pr_est bit 数。

    对每个 (d_hat, m)，看阈值 T_m 需要多少 bit 才能精确表示。
    阈值需要被表示为 pr_est = floor(32·PR) 或类似格式的整数。

    在 pr_est 域中，阈值 T = (m+0.5)·D，需要缩放。
    """
    print(f"\n{'='*60}")
    print("阈值表分析")
    print(f"{'='*60}")

    for d_bits in range(1, max_d_hat_bits + 1):
        num_d = 2 ** d_bits
        print(f"\nd_hat = {d_bits} bit ({num_d} 个值)")

        max_thresh = 0
        min_thresh = float('inf')
        all_thresholds = []

        for d_int in range(num_d):
            if d_int not in thresholds_dict:
                continue
            for m, t in thresholds_dict[d_int].items():
                all_thresholds.append(t)
                max_thresh = max(max_thresh, abs(t))

        print(f"  阈值范围: ±{max_thresh:.3f}")
        bits_needed = max(4, math.ceil(math.log2(max_thresh + 1)) + 1)
        print(f"  需要 {bits_needed} bit signed ([-2^{bits_needed-1}, 2^{bits_needed-1}-1])")

    # 打印缩减后的表
    print(f"\n{'='*60}")
    print("缩减后的阈值表")
    print(f"{'='*60}")

    for d_int in sorted(thresholds_dict.keys()):
        Z = 1.0 + d_int / 16.0
        th = thresholds_dict[d_int]
        th_ints = {m: int(round(t * 8)) for m, t in th.items()}  # 模拟缩放到 pr_est 域
        print(f"  D=1.{d_int:04b}(Z={Z:.4f}):  T={th_ints}  (raw={ {m:round(t,3) for m,t in th.items()} })")


# =============================================================================
# 现有 SRT-4 表的效率分析
# =============================================================================

def analyze_srt4_efficiency():
    """分析当前 SRT-4 表的截断效率"""
    print(f"\n{'='*60}")
    print("SRT-4 ρ=2/3 阈值表效率分析")
    print(f"{'='*60}")

    # 当前的 pr_est = 7 bit signed -> [-64, 63]
    # 当前的 d_hat = 3 bit -> {000, ..., 111}

    print("\n当前实现:")
    print("  pr_est = 7 bit signed (值域 [-64, +63])")
    print("  d_hat  = 3 bit (8 个值)")
    print(f"  阈值数: {len(SRT4_THRESHOLDS)} d_hat × 2 阈值 = {2*len(SRT4_THRESHOLDS)}")

    # 分析每个阈值需要的 bit
    all_m2 = [v[0] for v in SRT4_THRESHOLDS.values()]
    all_m1 = [v[1] for v in SRT4_THRESHOLDS.values()]
    print(f"\n  M2 范围: [{min(all_m2)}, {max(all_m2)}] -> 需要 {max(4, max(all_m2).bit_length())} bit")
    print(f"  M1 范围: [{min(all_m1)}, {max(all_m1)}] -> 需要 {max(4, max(all_m1).bit_length())} bit")

    # 最小 pr_est bit 数
    max_val = max(max(all_m2), max(all_m1))
    min_val = min(-max(all_m2), -max(all_m1))
    print(f"  完整 pr_est 值域: [{min_val}, {max_val}]")
    bits_for_range = max(max_val.bit_length(), abs(min_val).bit_length()) + 1
    print(f"  理论上最小 pr_est bit 数: {bits_for_range} (含符号)")

    # 按 d_hat 分组
    print("\n各 d_hat 的阈值分布:")
    for d_hat, (m2, m1) in sorted(SRT4_THRESHOLDS.items()):
        print(f"  d_hat={d_hat} (D_norm[62:60]):  M2={m2:2d}  M1={m1:2d}  -M1={-m1:3d}  -M2={-m2:3d}")
        m1_bits = max(4, abs(m1).bit_length() + 1)
        m2_bits = max(4, abs(m2).bit_length() + 1)
        print(f"               M1需要{m1_bits}bit  M2需要{m2_bits}bit")

    # 冗余分析：哪些 d_hat 可以合并？
    print("\n冗余检测:")
    # M1: 0-3 都是 4, 4-5 都是 6
    # 说明 d_hat 的低 1 bit 对 M1 没影响
    for d1, (m2_1, m1_1) in SRT4_THRESHOLDS.items():
        for d2, (m2_2, m1_2) in SRT4_THRESHOLDS.items():
            if d1 < d2 and m1_1 == m1_2 and m2_1 == m2_2:
                print(f"  d_hat={d1} 和 d_hat={d2}:  阈值完全相同! 可合并")


# =============================================================================
# 主程序
# =============================================================================

if __name__ == '__main__':
    # 分析 SRT-4
    analyze_srt4_efficiency()

    # 计算并分析 SRT-8 阈值
    print()
    srt8_47 = compute_srt8_thresholds_rho_4_7()
    analyze_bit_width(srt8_47, range(1, 5), max_d_hat_bits=4)

    print()
    srt8_67 = compute_srt8_thresholds_rho_6_7()
    analyze_bit_width(srt8_67, range(1, 7), max_d_hat_bits=4)
