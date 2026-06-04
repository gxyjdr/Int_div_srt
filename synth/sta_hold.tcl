#=============================================================================
# sta_hold.tcl — OpenSTA hold timing analysis (FF corner, RVT)
#=============================================================================

# Read liberty files (FF corner, best-case for hold)
read_liberty -min SIMPLE_RVT_FF.lib
read_liberty -min INVBUF_RVT_FF.lib
read_liberty -min SEQ_RVT_FF.lib
read_liberty -min AO_RVT_FF.lib

# Read synthesized gate-level netlist
read_verilog div_srt4_top_asap7_fixed.v

# Link design
link_design div_srt4_top

# Read SDC constraints
read_sdc div_srt4_top.sdc

# Set operating conditions (FF corner)
set_operating_conditions -analysis_type bc_wc -min_library SIMPLE_RVT_FF.lib

# Set propagated clock (required for realistic hold analysis)
set_propagated_clock [all_clocks]

# Hold timing report (worst 10 paths)
puts "\n===== HOLD TIMING (FF Corner, RVT) ====="
report_checks -path_delay min -endpoint_path_count 10 -slack_max 0

# Full report to file
puts "\n===== Writing hold report ====="
report_checks -path_delay min -endpoint_path_count 100 -slack_max 0 > sta_hold_rpt.rpt

puts "\nHold analysis complete."
puts "Report: sta_hold_rpt.rpt"
