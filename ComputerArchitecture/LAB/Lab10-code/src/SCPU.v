`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/28 15:11:21
// Design Name: 
// Module Name: SCPU
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


module SCPU(
    input         clk,
    input         rst,
    input  [31:0] inst,
    input  [31:0] data_in,  // data from data memory
    output [31:0] addr_out, // data memory address
    output [31:0] data_out, // data to data memory
    output [31:0] pc_out,   // connect to instruction memory
    output        mem_write
    );
    wire [3:0] alu_op;
    wire [1:0] pc_src, mem_to_reg;
    wire reg_write, alu_src, branch, b_type;

    Control control ( 
        .op_code(inst[6:0]),
        .funct3(inst[14:12]),
        .funct7_5(inst[30]),
        .pc_src(pc_src),         // 2'b00 表示pc的数据来自pc+4, 2'b01 表示数据来自JALR跳转地址, 2'b10表示数据来自JAL跳转地址(包括branch). branch 跳转根据条件决定
        .reg_write(reg_write),   // 1'b1 表示写寄存器
        .alu_src_b(alu_src_b),   // 1'b1 表示ALU B口的数据源来自imm, 1'b0表示数据来自Reg[rs2]
        .alu_op(alu_op),         // 用来控制ALU操作，具体请看AluOp.vh中对各个操作的编码
        .mem_to_reg(mem_to_reg), // 2'b00 表示写回rd的数据来自ALU, 2'b01表示数据来自imm, 2'b10表示数据来自pc+4, 2'b11 表示数据来自data memory
        .mem_write(mem_write),   // 1'b1 表示写data memory, 1'b0表示读data memory
        .branch(branch),         // 1'b1 表示是branch类型的指令
        .b_type(b_type)          // 1'b1 表示beq, 1'b0 表示bne
    );

    Datapath datapath (
        .clk(clk),
        .rst(rst),
        .pc_src(pc_src),
        .reg_write(reg_write),
        .alu_src_b(alu_src_b),
        .branch(branch),
        .b_type(b_type),
        .alu_op(alu_op),
        .mem_to_reg(mem_to_reg),
        .inst_in(inst),
        .data_in(data_in),
        .addr_out(addr_out),
        .data_out(data_out),
        .pc_out(pc_out)
    );
    
endmodule
