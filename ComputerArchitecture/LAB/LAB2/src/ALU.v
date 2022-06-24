`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/06/23 17:58:08
// Design Name: 
// Module Name: ALU
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


module ALU(
    input [31:0] a,
    input [31:0] b,
    input [3:0] alu_op,
    output reg [31:0] res,
    //output reg [31:0] res_i,
    output reg zero,
    output reg greater
    );
    `include "AluOp.vh"
    always @(*)
        case (alu_op)
            ADD: res = a + b;
            SUB: res = a - b;
            SLL: res = a << b;
            SUB: res = a - b;
            SLL: res = a << b;
            SLT: res = ($signed(a)<$signed(b))? 1:0;
            SLTU: res= a < b ? 1:0;
            XOR: res = a ^ b;
            SRL: res = a >> b;
            SRA: res = $signed(a) >>> b;
            OR: res = a | b;
            AND: res = a & b;
            default: res = 0;
        endcase
    always@(*)
    if(res==0) begin
        //res_i=0;
        zero=1;
        greater=0;
    end
    else 
        begin
            zero=0;
            //res_i=res;
            if(res[31]==0) greater=1;
            else greater=0;
        end
    
endmodule
