#=============================================================================
# div_srt4_top.sdc — Timing Constraints for SRT-4 Divider
#=============================================================================
# Target: 7nm process (ASAP7 predictive PDK)
# Clock: 2GHz (500ps period) typical for CPU core divider
#=============================================================================

#-------------------------------------------------------------------------
# Clock definition
#-------------------------------------------------------------------------
create_clock -name clk -period 0.5 [get_ports clk]
set_clock_transition -rise 0.03 [get_clocks clk]
set_clock_transition -fall 0.03 [get_clocks clk]

#-------------------------------------------------------------------------
# Input delays (typical CPU core interface)
#-------------------------------------------------------------------------
set_input_delay -clock clk -max 0.15 [get_ports valid_i]
set_input_delay -clock clk -min 0.05 [get_ports valid_i]
set_input_delay -clock clk -max 0.15 [get_ports {dividend_i[*]}]
set_input_delay -clock clk -min 0.05 [get_ports {dividend_i[*]}]
set_input_delay -clock clk -max 0.15 [get_ports {divisor_i[*]}]
set_input_delay -clock clk -min 0.05 [get_ports {divisor_i[*]}]
set_input_delay -clock clk -max 0.15 [get_ports signed_op_i]
set_input_delay -clock clk -min 0.05 [get_ports signed_op_i]
set_input_delay -clock clk -max 0.15 [get_ports ready_i]
set_input_delay -clock clk -min 0.05 [get_ports ready_i]

#-------------------------------------------------------------------------
# Output delays
#-------------------------------------------------------------------------
set_output_delay -clock clk -max 0.15 [get_ports ready_o]
set_output_delay -clock clk -min 0.05 [get_ports ready_o]
set_output_delay -clock clk -max 0.15 [get_ports valid_o]
set_output_delay -clock clk -min 0.05 [get_ports valid_o]
set_output_delay -clock clk -max 0.15 [get_ports {quotient_o[*]}]
set_output_delay -clock clk -min 0.05 [get_ports {quotient_o[*]}]
set_output_delay -clock clk -max 0.15 [get_ports {remainder_o[*]}]
set_output_delay -clock clk -min 0.05 [get_ports {remainder_o[*]}]
set_output_delay -clock clk -max 0.15 [get_ports div_by_zero_o]
set_output_delay -clock clk -min 0.05 [get_ports div_by_zero_o]
set_output_delay -clock clk -max 0.15 [get_ports overflow_o]
set_output_delay -clock clk -min 0.05 [get_ports overflow_o]
set_output_delay -clock clk -max 0.15 [get_ports busy_o]
set_output_delay -clock clk -min 0.05 [get_ports busy_o]

#-------------------------------------------------------------------------
# Input transition / Output load
#-------------------------------------------------------------------------
set_input_transition -rise 0.03 [all_inputs]
set_input_transition -fall 0.03 [all_inputs]
set_load -max 0.01 [all_outputs]
set_load -min 0.003 [all_outputs]

#-------------------------------------------------------------------------
# False paths: async reset (already handled as active-low async set)
#-------------------------------------------------------------------------
set_false_path -hold -from [get_ports rst_n]
