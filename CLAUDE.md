# DIV 模块开发 — SRT 整数除法器

## 项目概述
实现整数除法 DIV 模块，使用 SRT（Sweeney-Robertson-Tocher）算法，作为 CPU 核心执行部件的一部分。

## 规格
- **版本**：SRT-4 (Radix-4)，后续扩展 SRT-8
- **位宽**：64-bit 被除数/除数/商/余数
- **符号**：补码有符号/无符号（顶层 `signed_op_i` 选择），商符号 = 被除数 XOR 除数；余数符号 = 被除数
- **控制**：状态机，**变长迭代**（N = ⌈(K+2)/2⌉ = (K+3)>>1, K = lzc_D - lzc_A）
- **工艺**：TSMC 7nm
- **接口**：Valid/Ready 握手
- **商位集**：{-2, -1, 0, +1, +2}，ρ = 2/3
- **迭代次数**：最大 N = 32（K=62，K=63 被 |D|=1 短路）
- **延迟**：max 36 拍，min 5 拍（非短路）
- **PR 宽度**：68 bit signed（PR_int = PR_math·2^65）
- **OTF 累积器**：Q/QM 各 64 bit（= 2·N_max）
- **余数**：R = PR-based 右移恢复（无 64×64 乘法器，面积优化）
- **PR_0**：{4'b0, A_norm}（不右移，修复 unsigned MSB=1 bug）
- **D_scaled**：D_norm << 2
- **短路特判**：D=0、INT64_MIN/-1、A=0、|A|<|D|、|D|=1
- **异常**：除零（商=全1，余数=被除数）、INT64_MIN/-1 溢出（商=INT64_MIN，余数=0）

## 文件结构
```
projects/div/
├── CLAUDE.md
├── doc/
│   └── design.md             — 设计文档（68-bit 方案，与模型严格对应）
├── model/
│   ├── srt4_68bit.py         — 主位级模型（PR=68 bit，已 PASS）
│   ├── srt4_bitmodel.py      — 备用 bitmodel（Q/QM=66 bit，已 PASS）
│   ├── srt4_model.py         — Fraction 参考模型（已 PASS）
│   └── srt4_clean.py         — 旧 130-bit 方案（已废弃）
├── rtl/
│   ├── div_srt4_pkg.sv       — 常量、类型、QDS 阈值表 (Q_WIDTH=64, MAX_ITER=32)
│   ├── div_srt4_qds.sv       — QDS 商位选择（组合逻辑）
│   ├── div_srt4_datapath.sv  — 数据通路（PR-based R 恢复、无乘法器）
│   └── div_srt4_top.sv       — 顶层（状态机、握手、符号、短路）
├── sim/
│   ├── Makefile              — run / wave100 / cycles 仿真入口
│   ├── sim_main.cpp          — C++ testbench（6 tiers, 35925 cases）
│   ├── wave_*.vcd            — directed / wave100 波形输出
│   └── obj_dir/              — Verilator 输出
└── tb/
    └── div_srt4_tb.sv        — SV testbench（备用）
```

## 当前状态
- **阶段**：RTL 完成，Verilator 回归 35925/35925 ALL PASS，准备综合
- **综合工具**：待安装 OSS CAD Suite（Yosys + OpenSTA + GTKWave）
- **上次进度**：2026-06-01 — 4项设计变更全部实施完毕，回归全PASS，EDA工具检测完成

## 2026-05-30 设计变更（已实施）
1. **Bug 修复**：PR_0={4'b0,A_norm} 不右移，D_scaled=D_norm<<2，pr_est=pr_q[66:60]
2. **N 去 +1**：(K+3)>>1，MAX_ITER=32，Q_WIDTH=64
3. **R PR-based**：去 64×64 乘法器，CORRECT 加回 D_scaled，右移恢复
4. **K 奇偶分支**：shift=0 和 shift=1 两路 R 恢复公式

## 已完成
- [x] Python 模型（31011 PASS：11 directed + 10000 signed + 10000 unsigned）
- [x] 设计文档重写（doc/design.md，2026-05-30）
- [x] RTL 4项变更实施（pkg/datapath/sim_main.cpp）
- [x] Verilator 回归 35925/35925 ALL PASS（含 unsigned MSB=1 + unsigned random）
- [x] EDA 工具检测（Verilator + Yosys 0.9，OSS CAD Suite 下载中）

## 待办
- [ ] 安装 OSS CAD Suite → Yosys（SV支持）+ OpenSTA + GTKWave
- [ ] Yosys 综合（RTL → netlist）
- [ ] 时序分析（STA）
- [ ] 形式验证（LEC：RTL vs netlist）
- [ ] SRT-8 版本
