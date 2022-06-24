// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1 (win64) Build 2902540 Wed May 27 19:54:49 MDT 2020
// Date        : Sat May 29 14:34:39 2021
// Host        : DESKTOP-M082HN9 running 64-bit major release  (build 9200)
// Command     : write_verilog -mode funcsim D:/Control_sim.v
// Design      : Control
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* ADD = "4'b0000" *) (* AND = "4'b0111" *) (* OR = "4'b0110" *) 
(* SLL = "4'b0001" *) (* SLT = "4'b0010" *) (* SLTU = "4'b0011" *) 
(* SRA = "4'b1101" *) (* SRL = "4'b0101" *) (* SUB = "4'b1000" *) 
(* XOR = "4'b0100" *) 
(* NotValidForBitStream *)
module Control
   (op_code,
    funct3,
    funct7_5,
    pc_src,
    reg_write,
    alu_src_b,
    alu_op,
    mem_to_reg,
    mem_write,
    branch,
    b_type);
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

  wire [3:0]alu_op;
  wire \alu_op[3]_INST_0_i_1_n_0 ;
  wire \alu_op[3]_INST_0_i_2_n_0 ;
  wire \alu_op[3]_INST_0_i_3_n_0 ;
  wire \alu_op[3]_INST_0_i_4_n_0 ;
  wire \alu_op[3]_INST_0_i_5_n_0 ;
  wire alu_src_b;
  wire b_type;
  wire branch;
  wire [2:0]funct3;
  wire funct7_5;
  wire [1:0]mem_to_reg;
  wire mem_write;
  wire [6:0]op_code;
  wire [1:0]pc_src;
  wire \pc_src[1]_INST_0_i_1_n_0 ;
  wire reg_write;

  LUT6 #(
    .INIT(64'h000000000A002020)) 
    \alu_op[0]_INST_0 
       (.I0(funct3[0]),
        .I1(op_code[3]),
        .I2(op_code[4]),
        .I3(op_code[2]),
        .I4(op_code[6]),
        .I5(\alu_op[3]_INST_0_i_5_n_0 ),
        .O(alu_op[0]));
  LUT6 #(
    .INIT(64'h000000000A002020)) 
    \alu_op[1]_INST_0 
       (.I0(funct3[1]),
        .I1(op_code[3]),
        .I2(op_code[4]),
        .I3(op_code[2]),
        .I4(op_code[6]),
        .I5(\alu_op[3]_INST_0_i_5_n_0 ),
        .O(alu_op[1]));
  LUT6 #(
    .INIT(64'h000000000A002020)) 
    \alu_op[2]_INST_0 
       (.I0(funct3[2]),
        .I1(op_code[3]),
        .I2(op_code[4]),
        .I3(op_code[2]),
        .I4(op_code[6]),
        .I5(\alu_op[3]_INST_0_i_5_n_0 ),
        .O(alu_op[2]));
  LUT6 #(
    .INIT(64'h0C0C0C0C0C0CFB08)) 
    \alu_op[3]_INST_0 
       (.I0(\alu_op[3]_INST_0_i_1_n_0 ),
        .I1(\alu_op[3]_INST_0_i_2_n_0 ),
        .I2(\alu_op[3]_INST_0_i_3_n_0 ),
        .I3(funct7_5),
        .I4(\alu_op[3]_INST_0_i_4_n_0 ),
        .I5(\alu_op[3]_INST_0_i_5_n_0 ),
        .O(alu_op[3]));
  LUT4 #(
    .INIT(16'h0080)) 
    \alu_op[3]_INST_0_i_1 
       (.I0(funct3[2]),
        .I1(funct7_5),
        .I2(funct3[0]),
        .I3(funct3[1]),
        .O(\alu_op[3]_INST_0_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT3 #(
    .INIT(8'h06)) 
    \alu_op[3]_INST_0_i_2 
       (.I0(op_code[4]),
        .I1(op_code[5]),
        .I2(op_code[2]),
        .O(\alu_op[3]_INST_0_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'hF7FFFFF7)) 
    \alu_op[3]_INST_0_i_3 
       (.I0(op_code[0]),
        .I1(op_code[1]),
        .I2(op_code[3]),
        .I3(op_code[5]),
        .I4(op_code[6]),
        .O(\alu_op[3]_INST_0_i_3_n_0 ));
  LUT4 #(
    .INIT(16'hCFBB)) 
    \alu_op[3]_INST_0_i_4 
       (.I0(op_code[3]),
        .I1(op_code[4]),
        .I2(op_code[2]),
        .I3(op_code[6]),
        .O(\alu_op[3]_INST_0_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT4 #(
    .INIT(16'h7F77)) 
    \alu_op[3]_INST_0_i_5 
       (.I0(op_code[1]),
        .I1(op_code[0]),
        .I2(op_code[5]),
        .I3(op_code[2]),
        .O(\alu_op[3]_INST_0_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000000007)) 
    alu_src_b_INST_0
       (.I0(op_code[5]),
        .I1(op_code[4]),
        .I2(op_code[3]),
        .I3(op_code[2]),
        .I4(op_code[6]),
        .I5(\pc_src[1]_INST_0_i_1_n_0 ),
        .O(alu_src_b));
  LUT1 #(
    .INIT(2'h1)) 
    b_type_INST_0
       (.I0(funct3[0]),
        .O(b_type));
  LUT6 #(
    .INIT(64'h0000000000000040)) 
    branch_INST_0
       (.I0(\pc_src[1]_INST_0_i_1_n_0 ),
        .I1(op_code[6]),
        .I2(op_code[5]),
        .I3(op_code[4]),
        .I4(op_code[3]),
        .I5(op_code[2]),
        .O(branch));
  LUT6 #(
    .INIT(64'h0000000010000001)) 
    \mem_to_reg[0]_INST_0 
       (.I0(op_code[3]),
        .I1(op_code[6]),
        .I2(op_code[4]),
        .I3(op_code[2]),
        .I4(op_code[5]),
        .I5(\pc_src[1]_INST_0_i_1_n_0 ),
        .O(mem_to_reg[0]));
  LUT6 #(
    .INIT(64'h0300000000000001)) 
    \mem_to_reg[1]_INST_0 
       (.I0(op_code[3]),
        .I1(op_code[4]),
        .I2(\pc_src[1]_INST_0_i_1_n_0 ),
        .I3(op_code[5]),
        .I4(op_code[2]),
        .I5(op_code[6]),
        .O(mem_to_reg[1]));
  LUT6 #(
    .INIT(64'h0000000000000010)) 
    mem_write_INST_0
       (.I0(op_code[4]),
        .I1(op_code[3]),
        .I2(op_code[5]),
        .I3(op_code[2]),
        .I4(op_code[6]),
        .I5(\pc_src[1]_INST_0_i_1_n_0 ),
        .O(mem_write));
  LUT6 #(
    .INIT(64'h0000000000000080)) 
    \pc_src[0]_INST_0 
       (.I0(op_code[6]),
        .I1(op_code[5]),
        .I2(op_code[2]),
        .I3(op_code[4]),
        .I4(\pc_src[1]_INST_0_i_1_n_0 ),
        .I5(op_code[3]),
        .O(pc_src[0]));
  LUT6 #(
    .INIT(64'h0000000000800000)) 
    \pc_src[1]_INST_0 
       (.I0(op_code[6]),
        .I1(op_code[5]),
        .I2(op_code[2]),
        .I3(op_code[4]),
        .I4(op_code[3]),
        .I5(\pc_src[1]_INST_0_i_1_n_0 ),
        .O(pc_src[1]));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT2 #(
    .INIT(4'h7)) 
    \pc_src[1]_INST_0_i_1 
       (.I0(op_code[0]),
        .I1(op_code[1]),
        .O(\pc_src[1]_INST_0_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0101440000010001)) 
    reg_write_INST_0
       (.I0(\pc_src[1]_INST_0_i_1_n_0 ),
        .I1(op_code[6]),
        .I2(op_code[3]),
        .I3(op_code[2]),
        .I4(op_code[4]),
        .I5(op_code[5]),
        .O(reg_write));
endmodule
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;
    parameter GRES_WIDTH = 10000;
    parameter GRES_START = 10000;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    wire GRESTORE;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;
    reg GRESTORE_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (strong1, weak0) GSR = GSR_int;
    assign (strong1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;
    assign (strong1, weak0) GRESTORE = GRESTORE_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

    initial begin 
	GRESTORE_int = 1'b0;
	#(GRES_START);
	GRESTORE_int = 1'b1;
	#(GRES_WIDTH);
	GRESTORE_int = 1'b0;
    end

endmodule
`endif
