`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/04/01 20:39:14
// Design Name: 
// Module Name: Inst_Mem
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


module Inst_Mem(
    input [31:0] a,
    output [31:0] spo,
    output reg rom_resp_valid
    );
    Rom rom_unit(
        .a(a),  // 地址输入
        .spo(spo) // 读数据输出
    );
    always@(spo)begin
        rom_resp_valid=1;
    end
endmodule
