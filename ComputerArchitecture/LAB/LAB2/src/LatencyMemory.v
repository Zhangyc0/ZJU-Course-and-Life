`timescale 1ns / 1ps

module LatencyMemory(
    input clk,
    input rst,
    input en,
    input we,
    input [31:0] addr, // you can change the width
    input [31:0] data_in,
    output [31:0] data_out,
    output reg mem_resp_valid
);

	reg [31:0] clkdiv = 0; 

	always @ (posedge clk)begin
	    if (rst) clkdiv <= 0;
	    else clkdiv <= clkdiv + 1;
	end

	wire clk_latency;
	assign clk_latency = clkdiv[3]; // latency memory clock
	//always@(posedge clk_latency)
    always@(*)
    if(clkdiv[3:0]==4'h8 && en==1'b1) mem_resp_valid<=1'b1;
    else mem_resp_valid<=1'b0;
	blk_mem Memory(
	    .clka(clk_latency),
	    .ena(en),
	    .wea(we),
	    .addra(addr), // you can change the width
	    .dina(data_in),
	    .douta(data_out)
	);
endmodule
