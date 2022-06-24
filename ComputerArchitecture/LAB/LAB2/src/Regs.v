`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/06/23 17:54:45
// Design Name: 
// Module Name: Regs
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


module Regs(
    input clk,
    input rst,
    input we,
    input csr_write,
    input [31:0] csr_dout,
    input [4:0] reg_addr,
    input [4:0] read_addr_1,
    input [4:0] read_addr_2,
    input [4:0] write_addr,
    input [31:0] write_data,
    output reg [31:0] read_data_1,
    output reg [31:0] read_data_2,
    output reg [31:0] gp,
    output reg [31:0] register_data
);

    integer i;
    reg [31:0] register [1:31]; //x1 - x31, x0 keeps zero
    

   
    always @(posedge clk or posedge rst) begin
        if (rst == 1) for (i = 1; i < 32; i = i + 1) begin register[i] <= 0; end//reset 
        else if (we == 1 && csr_write == 1 && write_addr != 0) register[write_addr] <= csr_dout;
        else if (we == 1 && write_addr != 0) register[write_addr] <= write_data;
        
//        read_data_1 <= (read_addr_1 == 0) ? 0 : register[read_addr_1]; //read
//        read_data_2 <= (read_addr_2 == 0) ? 0 : register[read_addr_2]; //read
        //gp<=register[3];
    end
    always @(*) begin
        if(rst==1)begin
            read_data_1 <=  0 ; //read
            read_data_2 <=  0 ; //read
            gp<=0;
            register_data<=0;
        end
        else begin
        gp<=register[3];
        register_data<=register[reg_addr];
            if(read_addr_1==write_addr && we==1&&write_addr!=0) read_data_1<=write_data;
            else read_data_1 <= (read_addr_1 == 0) ? 0 : register[read_addr_1]; //read
            if(read_addr_2==write_addr && we==1&&write_addr!=0) read_data_2<=write_data;
            else read_data_2 <= (read_addr_2 == 0) ? 0 : register[read_addr_2]; //read
            //gp<=32'h00000102;
            
        end
    end
//    always @(posedge rst) begin
//        read_data_1 <=  0 ; //read
//        read_data_2 <=  0 ; //read
//    end

endmodule
