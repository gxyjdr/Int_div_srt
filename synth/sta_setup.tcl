#=============================================================================
# sta_setup.tcl — OpenSTA setup timing analysis (SS corner, RVT)
#=============================================================================

# Read liberty files (SS corner, worst-case setup)
read_liberty -max SIMPLE_RVT_SS.lib
read_liberty -max INVBUF_RVT_SS.lib
read_liberty -max SEQ_RVT_SS.lib
read_liberty -max AO_RVT_SS.lib

# Read synthesized gate-level netlist (ASAP7 mapped)
read_verilog div_srt4_top_asap7_fixed.v

# Link design
link_design div_srt4_top

# Read SDC constraints
read_sdc div_srt4_top.sdc

# Check setup violations
check_setup -verbose

# Setup timing report (top 20 paths)
puts "\n===== SETUP TIMING (SS Corner, RVT) ====="
report_checks -path_delay max -endpoint_path_count 20 -slack_max 0

# Full report to file
puts "\n===== Writing full setup report ====="
report_checks -path_delay max -endpoint_path_count 100 -slack_max 0 > sta_setup_rpt.rpt

puts "\nSetup analysis complete."
puts "Report: sta_setup_rpt.rpt"
