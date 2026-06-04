#!/bin/bash
# Batch test ABC mapping strategies
# Each test runs synthesis with a different ABC script and reports cell distribution
set -e

LIB="/mnt/c/Users/18435/Desktop/projects/div/synth/asap7_combined_SS.lib"
RTL="div_srt4_synth.sv"
YOSYS="/home/gxyjdr/oss-cad-suite/bin/yosys"

cd /mnt/c/Users/18435/Desktop/projects/div/synth

strategies=(
  "dc2; dretime; map -D 500"
  "dc2; dretime; map -D 500 -W"
  "amap -D 500"
  "dc2; mfs -D 500; map -D 500"
  "dch -d 500; map -D 500"
  "dc2; map -D 2000"
  "dc2; map -D 500 -W 2"
)

echo "=== ABC Mapping Strategy Comparison ==="
printf "%-50s %s\n" "Strategy" "Cell Mix"
echo "================================================================="

for script in "${strategies[@]}"; do
  cat > /tmp/ys_batch.ys << EOF
read_verilog -sv $RTL
hierarchy -check -top div_srt4_top
proc; opt; flatten; opt
synth -top div_srt4_top
abc -liberty $LIB -D 500 -script "+strash; &get -n; &fraig -x; &put; $script"
techmap -map techmap_dff.v
opt_clean -purge
stat -top div_srt4_top -liberty $LIB
EOF

  echo "--- Strategy: $script ---"
  $YOSYS /tmp/ys_batch.ys 2>&1 | grep -E "NAND2xp33|NAND3xp33|MAJIxp5|NOR2xp33|XNOR|x1_ASAP|xp5_ASAP|x2_ASAP|x4_ASAP|x6_ASAP|INVx|NAND4|NAND5|OR2x|OR3x" | head -20
  echo ""
done
