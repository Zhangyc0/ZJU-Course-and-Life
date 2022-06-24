`timescale 1ns / 1ps
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
module Control(
/* synthesis syn_black_box black_box_pad_pin="op_code[6:0],funct3[2:0],funct7_5,pc_src[1:0],reg_write,alu_src_b,alu_op[3:0],mem_to_reg[1:0],mem_write,branch,b_type" */
  input [6:0]op_code,
  input [2:0]funct3,
  input funct7_5,
  output reg [1:0]pc_src,
  output reg reg_write,
  output reg alu_src_b,
  output reg [3:0]alu_op,
  output reg [1:0]mem_to_reg,
  output reg mem_write,
  output reg branch,
  output reg b_type
  );
  `include "AluOp.vh"
//  reg [1:0] pre_mem_to_reg;
//  reg pre_mem_write;
//  always@(posedge clk)
//  initial begin
//    mem_to_reg<=0;
//    mem_write<=0;
//  end 
  always @(*) begin
      pc_src = 2'b00;
      reg_write = 1'b0;
      alu_src_b = 1'b0;
      alu_op = 4'b0000;
      mem_to_reg = 2'b00;
      mem_write = 1'b0;
      branch = 1'b0;
      if(op_code==7'b1100011 && funct3==3'b001)
      begin
        b_type = 1'b0;//BNE
      end
      else 
        begin 
            b_type = 1'b1;//BEQ
//            if(op_code==7'b1100011 && funct3==3'b111) b_type_bge = 1'b1;//BGEU
//            else b_type_bge = 1'b0;
        end
      case(op_code)
          7'b0010011:begin reg_write = 1'b1; alu_src_b = 1'b1;
                         case(funct3)
                             3'b000: alu_op = 4'b0000; //ADDI
                             3'b010: alu_op = 4'b0010; //SLTI
                             3'b111: alu_op = 4'b0111; //ANDI
                             3'b110: alu_op = 4'b0110; //ORI
                             3'b100: alu_op = 4'b0100; //XORI
                             3'b101: alu_op = 4'b0101; //SRLI
                             3'b001: alu_op = 4'b0001; //SLLI
                         endcase
                      end
          7'b0100011:begin alu_src_b = 1'b1; mem_write = 1'b1; end //SW
          7'b0000011:begin reg_write = 1'b1;alu_src_b = 1'b1; mem_to_reg = 2'b11; end //LW
          7'b1100011:begin alu_op = 4'b1000; branch = 1'b1; end //BNE & BEQ & BGEU
          7'b0110111:begin reg_write = 1'b1; mem_to_reg = 2'b01; end //LUI
          7'b1101111:begin pc_src = 2'b10; reg_write = 1'b1; mem_to_reg = 2'b10; end //JAL
          7'b0110011:begin reg_write = 1'b1;
                         case (funct3)
                             3'b000: 
                             case(funct7_5)
                                1'b0: alu_op = 4'b0000; //ADD
                                1'b1: alu_op = 4'b1000; //SUB
                             endcase
                             3'b010: alu_op = 4'b0010; //SLT
                             3'b111: alu_op = 4'b0111; //AND
                             3'b110: alu_op = 4'b0110; //OR
                             3'b001: alu_op = 4'b0001; //SLL
                             3'b101: alu_op = 4'b0101; //SRL
                             3'b011: alu_op = 4'b0011; //SLTU
                         endcase
                     end
          7'b0010111:begin reg_write = 1'b1; alu_src_b = 1'b1; end //AUIPC
          7'b1100111:begin pc_src = 2'b01; reg_write = 1'b1; alu_src_b = 1'b1; mem_to_reg = 2'b10; end //JALR
          7'b1110011:begin 
                        case (funct3)
                            3'b000:begin pc_src = 2'b10;
                                end//ECALL & EBREAK
//                            3'b011:begin
//                                        reg_write = 1'b1;
//                                        alu_op = 4'b0111;
//                                end//CSRRC
//                            3'b011:begin
//                                        reg_write = 1'b1;
//                                        alu_op = 4'b0111;
//                                        alu_src_b = 1'b1;
//                                end//CSRRCI
//                            3'b010:begin
//                                        reg_write = 1'b1;
//                                        alu_op = 4'b0110;
//                                end//CSRRS
//                            3'b110:begin
//                                        reg_write = 1'b1;
//                                        alu_op = 4'b0110;
//                                        alu_src_b = 1'b1;
//                                end//CSRRSI
//                            3'b001:begin
//                                        reg_write = 1'b1;
//                                        alu_op = ;
//                                end
                            default:reg_write = 1'b1;
                        endcase
                     end
      endcase
  end
endmodule
