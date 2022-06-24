`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/28 18:08:36
// Design Name: 
// Module Name: Core
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


module Core(
    input  wire        clk,
    input  wire        aresetn,
    input  wire        step,
    input  wire        debug_mode,
    // input  wire [4:0]  debug_reg_addr, // register address

    output wire [31:0] address,
    output wire [31:0] data_out,
    input  wire [31:0] data_in,
    
    input  wire [31:0] chip_debug_in,
    output wire [31:0] chip_debug_out0,
    output wire [31:0] chip_debug_out1,
    output wire [31:0] chip_debug_out2,
    output wire [31:0] chip_debug_out3
);
    wire rst, mem_write, mem_clk, cpu_clk;
    wire [31:0] inst, core_data_in, addr_out, core_data_out, pc_out;
    reg  [31:0] clk_div;
    
    assign rst = ~aresetn;
    SCPU cpu(
        .clk(cpu_clk),
        .rst(rst),
        .inst(inst),
        .data_in(core_data_in),      // data from data memory
        .addr_out(addr_out),         // data memory address
        .data_out(core_data_out),    // data to data memory
        .pc_out(pc_out),             // connect to instruction memory
        .mem_write(mem_write)
    );
    
    always @(posedge clk) begin
        if(rst) clk_div <= 0;
        else clk_div <= clk_div + 1;
    end
    assign mem_clk = ~clk_div[0]; // 50mhz
    assign cpu_clk = debug_mode ? clk_div[0] : step;
    
    // TODO: 连接Instruction Memory
    Rom rom_unit (
        .a(),  // 地址输入
        .spo() // 读数据输出
    );
    
    // TODO: 连接Data Memory
    Ram ram_unit (
        .clka(),  // 时钟
        .wea(),   // 是否写数据
        .addra(), // 地址输入
        .dina(),  // 写数据输入
        .douta()  // 读数据输出
    );
    
    // TODO: 添加32个寄存器组的输出
    assign chip_debug_out0 = pc_out;
    assign chip_debug_out1 = addr_out;
    assign chip_debug_out2 = inst;
    assign chip_debug_out3 = 32'hffffaaaa;
endmodule
