`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/06/25 10:22:28
// Design Name: 
// Module Name: MUX3T1_4
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


module MUX3T1_32(
    input [31:0] I0,
    input [31:0] I1,
    input [31:0] I2,
    input [1:0] s,
    output reg [31:0] o
    );
always @(*) begin
    case(s)
        2'b00: o = I0;
        2'b01: o = I1;
        2'b10: o = I2;
        default: ;
    endcase
end
endmodule
