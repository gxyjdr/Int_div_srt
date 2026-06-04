#!/usr/bin/env python3
"""Post-process Yosys Verilog output to convert ~ assignments to INV cells."""

import re
import sys

def fix_netlist(infile, outfile):
    with open(infile, 'r') as f:
        lines = f.readlines()

    out_lines = []
    inv_count = 0
    inv_inst_id = 90000  # start high to avoid conflicts

    inv_pin_re = re.compile(r'^\s+pin\s+\(([^)]+)\)')
    inv_lib_cells = []
    current_cell = None
    for line in lines:
        cm = re.match(r'\s*cell\s+\((\w+_ASAP7_75t_R)\)', line)
        if cm:
            current_cell = cm.group(1)
        if current_cell:
            pm = inv_pin_re.match(line)
            if pm:
                pin_name = pm.group(1)
                if current_cell.startswith('INV') and pin_name == 'A':
                    inv_lib_cells.append(current_cell)
                    current_cell = None

    # Pick the smallest INV
    inv_cell = 'INVx1_ASAP7_75t_R'

    for line in lines:
        # Match: assign <wire> = ~ <rhs>;
        m = re.match(r'^\s*assign\s+(\S+)\s*=\s*~\s*(.+);\s*$', line)
        if m:
            target = m.group(1)
            source = m.group(2).rstrip()
            # Skip constants (1'h0, 1'b1, etc.)
            if source.startswith("1'"):
                # assign _XXXX_ = ~ 1'h0 → tie to VDD (constant 1)
                out_lines.append(f'  assign {target} = 1\'b1;\n')
            else:
                out_lines.append(f'  {inv_cell} _inv_{inv_inst_id} (\n')
                out_lines.append(f'    .A({source}),\n')
                out_lines.append(f'    .Y({target})\n')
                out_lines.append(f'  );\n')
            inv_count += 1
            inv_inst_id += 1
        else:
            out_lines.append(line)

    with open(outfile, 'w') as f:
        f.writelines(out_lines)

    # Verify no ~ assignments remain
    remaining = 0
    for l in out_lines:
        if '= ~' in l:
            remaining += 1

    print(f"Fixed {inv_count} INV assignments.")
    if remaining:
        print(f"WARNING: {remaining} ~ assignments remain!")
    else:
        print("All ~ assignments removed.")

if __name__ == '__main__':
    infile = sys.argv[1] if len(sys.argv) > 1 else 'div_srt4_top_asap7.v'
    outfile = sys.argv[2] if len(sys.argv) > 2 else 'div_srt4_top_asap7_fixed.v'
    fix_netlist(infile, outfile)
