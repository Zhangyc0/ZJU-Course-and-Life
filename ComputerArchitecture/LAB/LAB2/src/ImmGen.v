`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/06/25 00:04:42
// Design Name: 
// Module Name: ImmGen
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


module ImmGen(
    input [31:0] inst,
    output reg [31:0] imm
    );
    initial imm=0;
    //wire [6:0] opcode = inst[6:0];
    always @(*)begin
    case(inst[6:0])
        7'b0010011: imm={{20{inst[31]}},inst[31:20]};
        7'b0100011: imm={{20{inst[31]}},inst[31:25],inst[11:7]};
        7'b0000011: imm={{20{inst[31]}},inst[31:20]};
        7'b1100011: imm={{19{inst[31]}},inst[31],inst[7],inst[30:25],inst[11:8],1'b0};
        7'b0110111: imm={inst[31:12],12'b0};
        7'b1101111: imm={{11{inst[31]}},inst[31],inst[19:12],inst[20],inst[30:21],1'b0};
        7'b0110011: imm=32'b0;
        7'b0010111: imm={inst[31:12],12'b0};
        7'b1100111: imm={{20{inst[31]}},inst[31:20]};
    endcase
end
endmodule
