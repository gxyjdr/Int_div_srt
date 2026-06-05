# DIV SRT 整数除法器 — 芯片研发项目

## 项目概述
实现整数除法 DIV 模块，使用 **多模推测 SRT**（Multi-Mode Speculative SRT）算法。
核心理念：**两级推测 + 多模动态跳转**——用低基构建大基，按剩余商位数贪心选择最优基数。

## 规格
- **核心算法**：多模两级推测，5 种模式动态切换

| 模式 | 结构 | 每周期 bit | 适用剩余 |
|------|------|-----------|---------|
| SRT-32 | SRT4×SRT8 推测 | 5 | ≥5 |
| SRT-16 | SRT4×SRT4 推测 | 4 | =4 |
| SRT-8 | SRT8 单级 | 3 | =3 |
| SRT-4 | SRT4 单级 | 2 | =2 |
| SRT-2 | SRT2 单级 | 1 | =1 |

- **位宽**：64-bit 被除数/除数/商/余数
- **符号**：补码有符号/无符号（顶层 `signed_op_i` 选择）
- **工艺**：TSMC 7nm / ASAP7，频率目标 **2.5 GHz**
- **接口**：Valid/Ready 握手（非流水，单次处理一笔）
- **推测路数**：**5 路**（由第一级 SRT-4 的 5 种商位决定，与第二级基数无关）
- **最大迭代**：**13 cycles**（K=62, bits_total=64, 贪心 = 12×SRT32 + 1×SRT16）
- **最长总延迟**：**18 cycles = 7.2 ns** @ 2.5 GHz
- **PR 宽度**：68-bit signed
- **Q_WIDTH**：66（5 bit/cyc × 13 cyc = 65，向上取整）
- **OTF**：单更新（SRT2/4/8）+ 双更新（SRT16/32）
- **倍数预计算**：PREPARE 阶段算好 3D（仅一次加法），迭代中无加法器
- **余数**：PR-based 右移恢复（无 64×64 乘法器）
- **短路特判**：D=0、INT64_MIN/-1、A=0、|A|<|D|、|D|=1

## 文件结构
```
projects/div/
├── CLAUDE.md               — 项目状态
├── input_config.json        — 项目配置（Frontend Flow）
├── tool-config.json         — EDA 工具检测
├── doc/
│   ├── design.md            — 设计文档 v2.0（多模推测架构）
│   ├── stage1_spec_extraction.json — Frontend Stage 1
│   ├── stage2_spec_review.json     — Frontend Stage 2
│   ├── stage3_microarch_analysis.json — Frontend Stage 3
│   ├── stage4_rtl_architecture.json  — Frontend Stage 4
│   ├── timing_estimate.md   — 时序估算
│   └── first_synth_report.md — 第一次综合报告
├── model/                   — Python 模型
├── rtl/                     — v1.x RTL（待重命名+重写）
├── sim/                     — 仿真环境
├── tb/                      — SV testbench
└── synth/                   — 综合脚本
```

## 模块架构（新）
```
div_srt_top        — FSM + 握手 + 短路 + 符号 + 模式调度
├── div_srt_qds2   — SRT-2 QDS 查表（自含）
├── div_srt_qds4   — SRT-4 QDS 查表（被 SRT-32/16/4 共享）
├── div_srt_qds8   — SRT-8 QDS 查表（被 SRT-32/8 共享）
├── div_srt_preproc — PREPARE: CLZ + 归一化 + 倍数预计算
├── div_srt_iter    — ITERATE: 主CSA + 5路推测 + PR寄存器
├── div_srt_otf     — OTF: Q/QM 累积（单/双更新）
├── div_srt_correct — CORRECT: 68-bit CPA + R恢复
└── div_srt_pkg     — 参数/类型（无函数，无实现）
```

## 阶段状态

### ✅ Phase 1（算法探索与基础实现）
- Python 模型 + RTL + 回归 35925 PASS + 第一次综合

### ✅ Phase 2（架构规划与算法优化）← 当前
- [x] 两级推测架构设计（5 路推测，SRT-4×SRT-4 = SRT-16）
- [x] 多模扩展（SRT-32/16/8/4/2，贪心跳转）
- [x] 倍数预计算（3D 在 PREPARE 阶段，迭代中无加法器）
- [x] Frontend Flow 4 阶段产出
- [x] 设计文档 v2.0
- [ ] QDS 阈值表定稿（下阶段）

### 📋 Phase 3（RTL 实现与验证）← 待开始
- [ ] Python 模型 v2.0（多模推测）
- [ ] RTL: qds2/qds4/qds8 模块
- [ ] RTL: preproc/iter/otf/correct 模块
- [ ] RTL: top 重写（模式调度）
- [ ] Verilator 回归
- [ ] 综合 + STA（2.5 GHz）

### 🔮 Phase 4（扩展）
- SRT-8 独立版本 / 形式验证 / 流水线化
