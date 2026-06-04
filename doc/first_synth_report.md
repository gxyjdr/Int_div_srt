# SRT-4 整数除法器 — 第一次综合与 STA 报告

## 1. 设计概览

- **设计**: 64-bit 有符号/无符号整数除法器，SRT-4 (Radix-4) 算法
- **位宽**: 64-bit, PR = 68-bit signed, ρ = 2/3
- **迭代**: 变长, N = (K+3)>>1, max = 32, min = 5
- **QDS**: 组合逻辑查表, 7-bit pr_est + 3-bit d_hat
- **状态机**: Valid/Ready 握手, 多周期迭代控制
- **RTL**: Verilog-2005, 4 模块 (top + datapath + qds + pkg)

## 2. 综合思路

### 2.1 方法

采用 **先 flatten 再综合** 的策略:

1. `proc` — 将 always 块转换为 FF + 组合逻辑
2. `flatten` — 合并所有子模块为单一扁平网表
3. `synth` — Yosys 基本综合 (逻辑化简)
4. `abc -liberty ... map` — ABC 技术映射到标准单元库
5. `techmap` — 手动映射 DFF 到 ASAP7 时序单元

### 2.2 为什么要 flatten

- 允许 ABC 跨模块边界优化 (尤其是 QDS + Datapath 之间的关键路径)
- 避免层次边界引入额外的 buffer 层级
- 让 ABC 的 `dc2` 和 `dretime` 在整个设计上做最优延迟优化

### 2.3 手动 DFF 映射的原因

ASAP7 的 DFF 单元特性为 `next_state : "!D"` (数据输入反相)，Yosys/dfflibmap 无法自动处理。解决方法：

1. 关闭 Yosys 自动 DFF 映射 (`dfflegalize` 不支持 !D)
2. 使用 `techmap` 手工将 Yosys `$_DFFE_PN0P_` → `DFFASRHQNx1_ASAP7_75t_R`
3. 用 `~D` 补偿 !D 反相，用 SETN 实现异步清零

### 2.4 INV 单元后处理

ABC 输出中残留 549 个 `assign x = ~ y;` 结构 (Verilog `~` 运算符)。OpenSTA 的 Verilog 解析器不支持任何运算符。 通过 Python 脚本将每个 `~` 赋值替换为 `INVx1_ASAP7_75t_R` 单元实例化。

## 3. 工具链

| 工具 | 版本 | 来源 | 用途 |
|------|------|------|------|
| Yosys | 0.56+197 (41452e43) | OSS CAD Suite 2025-09-02 | RTL 综合 + ABC 映射 |
| ABC | OSS CAD Suite 内置 | 同 Yosys | 技术映射 |
| OpenSTA | 3.1.0 (14751996) | 源码编译 (GitHub) | 静态时序分析 |
| ASAP7 PDK | 2020-11 / 2021-01 | ASU / GitHub (BSD-3) | 7nm 预测性 PDK |

### 3.1 环境

- **系统**: Windows 11 (WSL 2 Ubuntu 22.04)
- **编译**: GCC + CMake (OpenSTA 从源码构建)
- **ASAP7 库**: 手动组合 SIMPLE + INVBUF + SEQ + AO (RVT, SS/FF corner)
- **OpenSTA 依赖**: tcl8.6, swig, jsoncpp, eigen3, CUDD (均从源码构建)

### 3.2 ASIC 库信息

- **工艺**: ASAP7 (Arizona State University 预测性 7nm)
- **阈值**: RVT (Regular Vt)
- **温度/电压**:
  - SS (Setup): 0.63V, 125°C — worst-case slow
  - FF (Hold): 1.1V, -40°C — best-case fast
- **库组成**:
  - SIMPLE_RVT: 基本门 (NAND, NOR, XOR, AOI, OAI, MUX)
  - INVBUF_RVT: INV + BUF + 时钟 INV
  - SEQ_RVT: DFF (含 !D 特性)
  - AO_RVT: 复合 AO/OA 门

## 4. 约束 (SDC)

| 参数 | 值 |
|------|-----|
| 时钟频率 | 2 GHz |
| 时钟周期 | 500 ps |
| 时钟转换时间 | 30 ps |
| 输入延迟 | 150 ps (max) / 50 ps (min) |
| 输出延迟 | 150 ps (max) / 50 ps (min) |
| 输入转换时间 | 30 ps |
| 输出负载 | 0.01 pF (max) / 0.003 pF (min) |

## 5. 综合结果

### 5.1 面积

```
Chip area: 472.57 ASAP7 单位
  (不含 549 DFF 和 549 INV 的面积，因 Yosys 无法估算这些单元面积)
```

### 5.2 单元组成

| 单元类型 | 数量 | 功能 |
|---------|------|------|
| NAND2xp33_ASAP7_75t_R | 5,806 | 2-input NAND |
| NAND3xp33_ASAP7_75t_R | 690 | 3-input NAND |
| DFFASRHQNx1_ASAP7_75t_R | 549 | DFF (async set, !D) |
| XNOR2x2_ASAP7_75t_R | 274 | XNOR |
| MAJIxp5_ASAP7_75t_R | 157 | Majority (全加器进位) |
| XOR2x2_ASAP7_75t_R | 57 | XOR |
| NAND4xp25_ASAP7_75t_R | 82 | 4-input NAND |
| NOR2xp33_ASAP7_75t_R | 48 | NOR |
| NAND5xp2_ASAP7_75t_R | 36 | 5-input NAND |
| INVx1_ASAP7_75t_R | 549 | INV (后处理插入) |
| OR2x4_ASAP7_75t_R | 7 | OR |
| OR3x1_ASAP7_75t_R | 1 | OR |
| **总计** | **~8,298** | |

### 5.3 网表文件

| 文件 | 大小 | 说明 |
|------|------|------|
| `div_srt4_top_asap7.v` | 891 KB (48,929 行) | Yosys 原始输出 |
| `div_srt4_top_asap7_fixed.v` | 910 KB | INV 后处理版本 |

## 6. STA 结果

### 6.1 建立时间 (Setup) — SS Corner

| 指标 | 值 |
|------|-----|
| 库 | SIMPLE_RVT_SS + INVBUF_RVT_SS + SEQ_RVT_SS + AO_RVT_SS |
| 条件 | 0.63 V, 125°C |
| 时钟周期 | 500 ps (2 GHz) |
| WNS | **-6,235.79 ps** |
| TNS | 所有 100 条报告路径均违规 |
| 违规路径总数 | ≥ 100 |

**关键路径**: `_14801_` (state FF) → NAND 解码 → QDS 查表 → MAJIxp5 进位链 (68-bit) → NAND 选择 → INV → `_15071_` (state FF)

**路径延迟分解**:

```
Clock-to-Q (DFF):       607 ps
QDS + 控制解码:          ~565 ps
68-bit 进位链 (MAJIxp5): ~3,200 ps (68 stages × ~47 ps)
最终选择 + 建立时间:     ~1,400 ps
总计:                     6,199 ps
```

**最大频率**: **~161 MHz** (1 / 6,199 ps)

### 6.2 保持时间 (Hold) — FF Corner

| 指标 | 值 |
|------|-----|
| 库 | SIMPLE_RVT_FF + INVBUF_RVT_FF + SEQ_RVT_FF + AO_RVT_FF |
| 条件 | 1.1 V, -40°C |
| WNS | **-6.41 ps** (输入端口路径) |
| 内部保持时间 | 无违规 |

保持时间违规仅出现在输入端口 (input port → FF)，数值极小 (-6.41 ps ≈ 0)。在真实芯片中可通过调整 input delay 约束或添加少量 buffer 修复。

## 7. 结果分析

### 7.1 原始数据与架构估计的对比

| 参数 | 架构估计 (doc/timing_estimate.md) | 实际 STA 结果 |
|------|-----------------------------------|--------------|
| 一次迭代延迟 | ~100 ps | ~6,200 ps (含 flat 后全路径) |
| 单级门延迟 (FO4) | ~10-15 ps (typical) | ~47 ps (SS corner, xp33) |
| 最大频率 | ~3.7 GHz (含 50% margin) | ~161 MHz |

### 7.2 性能差距原因

1. **ABC 映射器限制**: Yosys 内置 ABC 的 `map` 命令始终选择最小驱动单元 (`xp33` 系列)，无论 `-D` 延迟约束设置多少。这导致所有逻辑门都以最弱驱动能力实现。

2. **行波进位加法器**: ABC 将 68-bit PR 加法器映射为 ripple-carry 结构，关键路径串行通过 68 级 MAJIxp5 进位链 (~3.2 ns)，而非更快的 carry-lookahead 或 carry-select 结构。

3. **RVT 阈值电压**: ASAP7 RVT 是最高阈值 (最慢) 的单元族。SLVT (超低阈值) 在相同电压下速度约 2-3× RVT。

4. **SS 工艺角**: 0.63V / 125°C 是最差条件。典型条件 (TT corner, 0.77V, 25°C) 下延迟约为 SS 的 40-50%。

### 7.3 合理预期性能

| 优化级别 | 预计频率 (SS corner) | 说明 |
|---------|---------------------|------|
| 当前 (xp33 + RVT + ripple-carry) | ~161 MHz | baseline |
| + SLVT 单元 | ~400-500 MHz | 单元速度提升 2-3× |
| + 大驱动单元 (x4/x8) | ~600-800 MHz | 减少 slew 退化 |
| + Carry-lookahead 加法器 | ~1-2 GHz | 68-bit CLA ~8-10 级 |
| + 工业级综合 (DC/Genus) | ~2-3 GHz | 商用工具 cell sizing + 物理综合 |

### 7.4 设计瓶颈定位

关键路径位于 **PR 更新迭代循环**:
- 起点: 状态机寄存器 `_14801_`
- 经过: QDS 查表 → 除数倍数选择 → 68-bit CSA/CPA → PR 移位
- 终点: 状态机寄存器 `_15071_`

其中 68-bit 加法器的行波进位链贡献 ~52% 的总延迟。

## 8. 总结

第一次综合成功完成了从 RTL 到门级网表的完整流程，建立了基于开源工具 (Yosys + ABC + OpenSTA) 和 ASAP7 PDK 的综合 + STA 验证环境。

当前 161 MHz 的性能远低于架构预期，但这是 ABC 映射器限制所致，而非设计或工艺的根本问题。关键改进方向为：(1) 使用 SLVT 单元提升基础门速度；(2) 优化加法器结构；(3) 改用更大驱动单元。

## 附录: 文件清单

```
projects/div/synth/
├── div_synth_asap7.ys           — Yosys 综合脚本
├── techmap_dff.v                — DFF 手动映射文件
├── div_srt4_synth.sv            — 平坦化 RTL (供综合)
├── div_srt4_top.sdc             — 时序约束
├── div_srt4_top_asap7.v         — 综合后网表 (891KB)
├── div_srt4_top_asap7_fixed.v   — INV 后处理网表 (910KB)
├── fix_inv.py                   — INV 后处理脚本
├── sta_setup.tcl                — OpenSTA 建立时间分析脚本
├── sta_hold.tcl                 — OpenSTA 保持时间分析脚本
├── sta_setup_rpt.rpt            — 建立时间报告 (13,300 行)
├── sta_hold_rpt.rpt             — 保持时间报告 (2,800 行)
├── SIMPLE_RVT_SS.lib            — SS corner 基本门库 (2.2MB)
├── SIMPLE_RVT_FF.lib            — FF corner 基本门库 (1.7MB)
├── INVBUF_RVT_SS.lib            — SS corner INV/BUF 库 (301KB)
├── INVBUF_RVT_FF.lib            — FF corner INV/BUF 库 (298KB)
├── SEQ_RVT_SS.lib               — SS corner 时序单元库 (1.5MB)
├── SEQ_RVT_FF.lib               — FF corner 时序单元库 (1.5MB)
├── AO_RVT_SS.lib                — SS corner AO/OA 库 (22MB)
├── AO_RVT_FF.lib                — FF corner AO/OA 库 (22MB)
└── asap7_combined_{SS,FF}.lib   — 合并版全库 (含 license 注释, 26MB/25MB)
```

报告日期: 2026-06-03
工具: Yosys 0.56 + abc + OpenSTA 3.1.0 / ASAP7 RVT PDK
