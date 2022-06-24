`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/11 13:09:43
// Design Name: 
// Module Name: Forwarding_Unit
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module Forwarding_Unit(
    input [4:0] Rs1,
    input [4:0] Rs2,
    input [4:0] EX_MEM_Rd,
    input [4:0] MEM_WB_Rd,
    input [1:0] mem_to_reg,
    input ex_mem_reg_write,
    input mem_wb_reg_write,
    output [1:0] ForwardA,
    output [1:0] ForwardB
    );
    //assign ForwardA=0;
    //assign ForwardB=0;
//always@(*)begin
    assign ForwardA[0]=(ex_mem_reg_write==1&&Rs1==EX_MEM_Rd&&EX_MEM_Rd!=0);
    assign ForwardA[1]=((mem_wb_reg_write==1&&Rs1==MEM_WB_Rd&&MEM_WB_Rd!=0&&!(ex_mem_reg_write==1&&Rs1==EX_MEM_Rd&&EX_MEM_Rd!=0))||(ex_mem_reg_write==1&&Rs1==EX_MEM_Rd&&EX_MEM_Rd!=0&&mem_to_reg==2'b01));
    assign ForwardB[0]=(ex_mem_reg_write==1&&Rs2==EX_MEM_Rd&&EX_MEM_Rd!=0);
    assign ForwardB[1]=((mem_wb_reg_write==1&&Rs2==MEM_WB_Rd&&MEM_WB_Rd!=0&&!(ex_mem_reg_write==1&&Rs2==EX_MEM_Rd&&EX_MEM_Rd!=0))||(ex_mem_reg_write==1&&Rs2==EX_MEM_Rd&&EX_MEM_Rd!=0&&mem_to_reg==2'b01));
//    if(Rs1==MEM_WB_Rd&&MEM_WB_Rd!=0) ForwardA=2'b10;
//    else if(Rs1==EX_MEM_Rd&&EX_MEM_Rd!=0) ForwardA=2'b01;
//    else ForwardA=0;
//    if(Rs2==MEM_WB_Rd&&MEM_WB_Rd!=0) ForwardB=2'b10;
//    else if(Rs2==EX_MEM_Rd&&EX_MEM_Rd!=0) ForwardB=2'b01;
//    else ForwardB=0;
//    ForwardA=(Rs1==EX_MEM_Rd)? 2'b01:0;
//    ForwardA=(Rs1==MEM_WB_Rd)? 2'b10:0;
//    ForwardB=(Rs2==EX_MEM_Rd)? 2'b01:0;
//    ForwardB=(Rs2==MEM_WB_Rd)? 2'b10:0;
//end
    
endmodule
