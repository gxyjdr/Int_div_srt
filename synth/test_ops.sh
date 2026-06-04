#!/bin/bash
for expr in a "(a)" "a&a" "a|a" "a^a" "a&~a" "~a"; do
  echo "module test(a,b,c);input a,b;output c;assign c=$expr;endmodule" > /tmp/t.v
  echo "read_verilog /tmp/t.v" > /tmp/s.tcl
  err=$(/tmp/OpenSTA/build/sta -no_splash -exit /tmp/s.tcl 2>&1 | grep -c "Error")
  echo "$expr -> $err errors"
done
