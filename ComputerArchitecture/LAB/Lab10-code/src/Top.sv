`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/28 18:16:36
// Design Name: 
// Module Name: Top
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


module Top(
    input          clk,
    input          resetn,
    input  [15:0]  switch, 
    input  [ 4:0]  button,  
    
    output [15:0]  led,
    output [ 2:0]  rgb1,
    output [ 2:0]  rgb2,
    output [ 7:0]  num_csn,
    output [ 7:0]  num_an
);
    logic aresetn;
    logic step;

    logic [31:0] address;
    logic [31:0] data_out;
    logic [31:0] data_in;

    logic [31:0] chip_debug_in;
    logic [31:0] chip_debug_out0;
    logic [31:0] chip_debug_out1;
    logic [31:0] chip_debug_out2;
    logic [31:0] chip_debug_out3;

    Core chip_inst(
        .clk(clk),
        .aresetn(aresetn),
        .step(step),
        .debug_mode(switch[15]),
        // .debug_reg_addr(switch[11:7]),
        .address(address),
        .data_out(data_out),
        .data_in(data_in),
        .chip_debug_in(chip_debug_in),
        .chip_debug_out0(chip_debug_out0),
        .chip_debug_out1(chip_debug_out1),
        .chip_debug_out2(chip_debug_out2),
        .chip_debug_out3(chip_debug_out3)
    );

    IO_Manager io_manager_inst(
        .clk(clk),
        .resetn(resetn),

        // to chip
        .aresetn(aresetn),
        .step(step),
        .address(address),
        .data_out(data_out),
        .data_in(data_in),
        .chip_debug_in(chip_debug_in),
        
        // to gpio
        .switch(switch),
        .button(button),
        .led(led),
        .num_csn(num_csn),
        .num_an(num_an),
        .rgb1(rgb1),
        .rgb2(rgb2),
        
        // debug
        .debug0(32'h88888888),
        .debug1({16'b0, switch[15:0]}),
        .debug2({12'b0, 3'b0, button[4], 3'b0, button[3], 3'b0, button[2], 3'b0, button[1], 3'b0, button[0]}),
        .debug3(32'h12345678),
        .debug4(chip_debug_out0),
        .debug5(chip_debug_out1),
        .debug6(chip_debug_out2),
        .debug7(chip_debug_out3)
    );
endmodule
