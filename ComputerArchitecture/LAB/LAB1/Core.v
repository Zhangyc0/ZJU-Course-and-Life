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
    input  wire [4:0]  debug_reg_addr, // register address

    output wire [31:0] address,
    output wire [31:0] data_out,
    input  wire [31:0] data_in,
    
    input  wire [31:0] chip_debug_in,
    output reg [31:0] chip_debug_out0,
    output reg [31:0] chip_debug_out1,
    output reg [31:0] chip_debug_out2,
    output reg [31:0] chip_debug_out3
);
    wire [63:0] Reg_IF_ID_i;
    wire [247:0] Reg_ID_EX_i;
    wire [333:0] Reg_EX_MEM_i;
    wire [104:0] Reg_MEM_WB_i;
    wire [63:0] Reg_IF_ID_o;
    wire [247:0] Reg_ID_EX_o;
    wire [333:0] Reg_EX_MEM_o;
    wire [104:0] Reg_MEM_WB_o;
    wire rst, mem_clk, cpu_clk;
    wire [31:0] inst, core_data_in, core_data_out, pc_out,gp,register_data,Forward_1_data1;
    wire reg_w;
    reg  [31:0] clk_div;
    assign rst = ~aresetn;
    SCPU cpu(
        .clk(cpu_clk),
        .rst(rst),
        .inst(inst),
        .data_in(core_data_in),      // data from data memory
        .Reg_IF_ID_i(Reg_IF_ID_i),
        .Reg_ID_EX_i(Reg_ID_EX_i),
        .Reg_EX_MEM_i(Reg_EX_MEM_i),
        .Reg_MEM_WB_i(Reg_MEM_WB_i),
        .Reg_IF_ID_o(Reg_IF_ID_o),
        .Reg_ID_EX_o(Reg_ID_EX_o),
        .Reg_EX_MEM_o(Reg_EX_MEM_o),
        .Reg_MEM_WB_o(Reg_MEM_WB_o),
        .reg_addr(debug_reg_addr),
        //.addr_out(addr_out),         // data memory address
        //.data_out(core_data_out),    // data to data memory
        .pc_out(pc_out),             // connect to instruction memory
        //.mem_write(mem_write),
        //.write_data(write_data),
        //.csr_pc_next(csr_pc_next),
        .gp(gp),
//        .mtvec(mtvec),
//        .mepc(mepc),
//        .mstatus(mstatus),
        .register_data(register_data),
        .Forward_1_data1(Forward_1_data1),
        .reg_w(reg_w)
    );
 
        assign Reg_IF_ID_i=Reg_IF_ID_o;
        assign Reg_ID_EX_i=Reg_ID_EX_o;
        assign Reg_EX_MEM_i=Reg_EX_MEM_o;
        assign Reg_MEM_WB_i=Reg_MEM_WB_o;    
 


    always @(posedge clk) begin
        if(rst) begin clk_div <= 0;end
        else clk_div <= clk_div + 1;
    end
    assign mem_clk = ~clk_div[0]; // 50mhz
    assign cpu_clk = debug_mode ? clk_div[0] : step;
    
    // TODO: 连接Instruction Memory
    Rom rom_unit (
        .a(pc_out/4),  // 地址输入
        .spo(inst) // 读数据输出
    );
    
    // TODO: 连接Data Memory
    Ram ram_unit (
        .clka(mem_clk),  // 时钟
        .wea(Reg_EX_MEM_i[175]),
        //.wea(mem_write),   // 是否写数据
        .addra(Reg_EX_MEM_i[100:69]),
        //.addra(addr_out), // 地址输入
        //.dina(core_data_out),  // 写数据输入
        .dina(Reg_EX_MEM_i[207:176]),
        .douta(core_data_in)  // 读数据输出
    );
    always@(*)begin
    // TODO: 添加32个寄存器组的输出
    chip_debug_out0 = pc_out;//pc
    chip_debug_out1 = register_data;//inst
    chip_debug_out2 = reg_w;
    //assign chip_debug_out2 = addr_out;//address
    chip_debug_out3 = gp;//data
    end

endmodule
