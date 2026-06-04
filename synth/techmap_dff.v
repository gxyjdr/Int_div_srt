// Map $_DFFE_PN0P_ to DFFASRHQNx1 (using SETN as async clear, ~D to compensate for !D next_state)
module \$_DFFE_PN0P_ (input D, input E, input R, input C, output Q);
  DFFASRHQNx1_ASAP7_75t_R _TECHMAP_REPLACE_ (.CLK(C), .D(~D), .RESETN(1'b1), .SETN(R), .QN(Q));
endmodule

module \$_DFFE_PN0N_ (input D, input E, input R, input C, output Q);
  DFFASRHQNx1_ASAP7_75t_R _TECHMAP_REPLACE_ (.CLK(C), .D(~D), .RESETN(1'b1), .SETN(R), .QN(Q));
endmodule

module \$_DFFE_PP_ (input D, input E, input C, output Q);
  DFFASRHQNx1_ASAP7_75t_R _TECHMAP_REPLACE_ (.CLK(C), .D(~D), .RESETN(1'b1), .SETN(1'b1), .QN(Q));
endmodule
