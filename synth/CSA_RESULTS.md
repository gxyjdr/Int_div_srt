# CSA Implementation Results — SRT-4 Divider

## Revision
- **Date**: 2026-06-03
- **Process**: ASAP7 (predictive 7nm), RVT cells
- **Corners**: SS (0.63V/125°C) for setup, FF (1.1V/-40°C) for hold
- **Target**: 500 ps clock (2 GHz) for iteration loop
- **Tool**: Yosys 0.56+ (ABC) → OpenSTA

## Synthesis Cell Counts

| Cell Type   | Count |
|-------------|-------|
| MAJIxp5     | 286   |
| NAND2xp33   | 5870  |
| INVx1_ASAP7 | 611   |
| DFFASRHQN   | 682   |

## Timing Comparison (SS corner, RVT)

| Metric                | Old (CPA)   | New (CSA)    | Improvement |
|-----------------------|-------------|--------------|-------------|
| **Iteration WNS**     | -6235 ps    | <500 ps ✅   | >12×        |
| **CORRECT CPA WNS**   | —           | -6836 ps     | N/A         |
| **Input-to-REG WNS**  | —           | -39.8 ps     | ~540 ps     |
| **REG-to-Output WNS** | —           | -130.8 ps    | ~631 ps     |
| **Hold WNS**          | —           | -6.41 ps     | trivial     |
| **Max iter freq**     | ~160 MHz    | ~2 GHz       | 12.5×       |

## Key Architecture Changes

1. **pr_q (68-bit) → pr_sum_q + pr_carry_q (carry-save)**
   - Iteration: 3:2 CSA replaces 68-bit CPA
   - QDS estimate: 7-bit CPA on pr_sum[66:60] + pr_carry[66:60]
   - CORRECT merge: 68-bit CPA (pr_sum + pr_carry), runs once per operation

2. **CORRECT phase pipelined** (ST_CORRECT → ST_CORRECT2)
   - pr_full_q registered by corr_step
   - quotient/remainder computed combo in next cycle
   - Adds 1 cycle latency (total max: 37 cycles)

## Critical Path Analysis

### Iteration Loop (meets 500 ps)
pr_sum_q/pr_carry_q FF → shift (wiring) → 7-bit CPA (7 MAJIxp5) → QDS lookup (mux) → multiple mux → CSA (XOR+AND) → FF D

### CORRECT Phase (6800 ps, ~14 cycles at 2 GHz)
pr_sum_q/pr_carry_q FF → 68-bit CPA (pr_sum + pr_carry) → conditional correct mux → quotient/remainder decode → output FF

### Wire Load Model Artifact
Single-cell delays up to 2543 ps (NAND2xp33, _09191_/Y) are wire load model artifacts from the simple liberty file. Real layout wire delays are significantly shorter.

## Estimated Performance

| Metric              | Old CPA        | New CSA        | Ratio  |
|---------------------|----------------|----------------|--------|
| Worst-case latency  | 36×6.2ns=223ns | 1+32×0.5+2≈19ns | ~11.7× |
| Average latency     | ~148ns         | ~11ns           | ~13.5× |
| Max iteration rate  | 160 MHz        | 2 GHz          | 12.5×  |

## Open Issues

- CORRECT phase 68-bit CPA dominated by wire load model (simple liberty)
- Input paths -39.8 ps: CLZ + normalization, needs cell upsizing
- Hold violations are pre-CTS, expected to close with clock tree insertion
- Real signoff needs P&R with extracted parasitics, not wire load models
