// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1 (win64) Build 2902540 Wed May 27 19:54:49 MDT 2020
// Date        : Sat May 29 13:57:02 2021
// Host        : DESKTOP-M082HN9 running 64-bit major release  (build 9200)
// Command     : write_verilog -mode synth_stub D:Control.v
// Design      : Control
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
module Control(op_code, funct3, funct7_5, pc_src, reg_write, 
  alu_src_b, alu_op, mem_to_reg, mem_write, branch, b_type)
/* synthesis syn_black_box black_box_pad_pin="op_code[6:0],funct3[2:0],funct7_5,pc_src[1:0],reg_write,alu_src_b,alu_op[3:0],mem_to_reg[1:0],mem_write,branch,b_type" */;
  input [6:0]op_code;
  input [2:0]funct3;
  input funct7_5;
  output [1:0]pc_src;
  output reg_write;
  output alu_src_b;
  output [3:0]alu_op;
  output [1:0]mem_to_reg;
  output mem_write;
  output branch;
  output b_type;
endmodule
