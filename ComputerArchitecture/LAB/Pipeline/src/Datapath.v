`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/06/20 23:00:18
// Design Name: 
// Module Name: Datapath
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


module Datapath(
    input clk,
    input rst,
    input wire [1:0] pc_src,
    input reg_write,
    input alu_src_b,
    input branch,
    input b_type,
    input wire [3:0] alu_op,
    input wire [1:0] mem_to_reg,
    input  [31:0] inst,
    input  [31:0] data_in,
    input  mem_write,
    input  [4:0] reg_addr,
    input  [63:0] Reg_IF_ID_i,
    input  [247:0] Reg_ID_EX_i,
    input  [333:0] Reg_EX_MEM_i,
    input  [104:0] Reg_MEM_WB_i,
    input cache_resp_stall,
    output  reg [63:0] Reg_IF_ID_o,
    output  reg [247:0] Reg_ID_EX_o,
    output  reg [333:0] Reg_EX_MEM_o,
    output  reg [104:0] Reg_MEM_WB_o,
    //output [31:0] addr_out,
    //output [31:0] data_out,
    output reg [31:0] pc_out,
    //output [31:0] write_data,
    //output [31:0] csr_pc_next,
    output  [31:0] gp,
//    output [31:0] mtvec,
//    output [31:0] mepc,
//    output [31:0] mstatus,
    output  [31:0] register_data,
    output reg [31:0] Forward_1_data1
);
wire [31:0] pc_next, pc_plus_4, add_res, mux_res, imm, tmp_pc_next,addr_out,data_out,write_data,csr_pc_next;
wire [31:0] read_data_1, read_data_2, alu_a, alu_b, ALU_A, ALU_B,csr_dout,Forward1_data1,Forward1_data2;
reg [1:0] mux_src;
wire zero;
wire greater;
reg b_type_bge;
reg alu_src_a;
reg [31:0] pc;
wire csr_pc_write,csr_write;
//reg [31:0] Forward1_data1,Forward1_data2;

//  output reg [1:0]pc_src;
//output reg reg_write;
//output reg alu_src_b;
//output reg [3:0]alu_op;
//output reg [1:0]mem_to_reg;
//output reg mem_write;
//output reg branch;
//output reg b_type;


//reg [63:0] Reg_IF_ID=0;
//reg [127:0] Reg_ID_EX=0;
//reg [101:0] Reg_EX_MEM=0;
//reg [68:0] Reg_MEM_WB=0;
initial begin
    pc_out<=0;
    pc<=0;
    Reg_IF_ID_o<=0;
    Reg_ID_EX_o<=0; 
    Reg_EX_MEM_o<=0;
    Reg_MEM_WB_o<=0;
end
assign pc_plus_4 = pc + 8'h00000004;
assign add_res = Reg_ID_EX_i[164:133]+ Reg_ID_EX_i[68:37];
//reg stall;
wire [1:0]ForwardA,ForwardB;
//assign stall = (((Reg_MEM_WB[71]==1&&Reg_MEM_WB[4:0]!=0)||(Reg_EX_MEM[140]==1&&Reg_EX_MEM[4:0]!=0)||(Reg_ID_EX[177]==1&&Reg_ID_EX[4:0]!=0))&&(inst[19:15]==Reg_EX_MEM[4:0]||inst[19:15]==Reg_ID_EX[4:0]||inst[24:20]==Reg_EX_MEM[4:0]||inst[24:20]==Reg_ID_EX[4:0])) ? 1:0;
//assign stall = (((Reg_EX_MEM[140]==1&&Reg_EX_MEM[4:0]!=0)||(Reg_ID_EX[177]==1&&Reg_ID_EX[4:0]!=0))&&(inst[19:15]==Reg_EX_MEM[4:0]||inst[19:15]==Reg_ID_EX[4:0]||inst[24:20]==Reg_EX_MEM[4:0]||inst[24:20]==Reg_ID_EX[4:0])) ? 1:0;
//always@(posedge clk)begin
////if(Reg_MEM_WB[71]==1&&Reg_MEM_WB[4:0]!=0&&(inst[19:15]==Reg_EX_MEM[4:0]||inst[19:15]==Reg_ID_EX[4:0]||inst[24:20]==Reg_EX_MEM[4:0]||inst[24:20]==Reg_ID_EX[4:0]))
//if(((Reg_EX_MEM[140]==1&&Reg_EX_MEM[4:0]!=0)||(Reg_ID_EX[177]==1&&Reg_ID_EX[4:0]!=0)||(reg_write==1&&Reg_IF_ID[11:7]!=0))&&(inst[19:15]==Reg_EX_MEM[4:0]||inst[19:15]==Reg_ID_EX[4:0]||inst[24:20]==Reg_EX_MEM[4:0]||inst[24:20]==Reg_ID_EX[4:0]||inst[19:15]==Reg_IF_ID[11:7]||inst[24:20]==Reg_IF_ID[11:7]))
//    stall<=1;
//else stall<=0;
//end
//if(Reg_ID_EX[]==)
/* assign add_res = pc + imm; */
always@(*)
begin if((Reg_ID_EX_i[166] & zero & Reg_ID_EX_i[165] & ~Reg_ID_EX_i[181]) | (Reg_ID_EX_i[166] & ~zero & ~Reg_ID_EX_i[165] & ~Reg_ID_EX_i[181]) | (Reg_ID_EX_i[179:178]==2'b10) | (Reg_ID_EX_i[166] & Reg_ID_EX_i[181] & (zero | greater)))
          mux_src = 2'b01;
      else if(Reg_ID_EX_i[179:178] == 2'b01)
          mux_src = 2'b10;
      else mux_src = 2'b00;
end
always@(*)begin
if(Reg_IF_ID_i[6:0]==7'b1100011 && Reg_IF_ID_i[14:12]==3'b111) b_type_bge = 1'b1;//BGEU
else b_type_bge = 1'b0;
end
//always@(*)
//begin if((Reg_EX_MEM[135] & Reg_EX_MEM[101] & Reg_EX_MEM[134]) | (Reg_EX_MEM[135] & ~Reg_EX_MEM[101] & ~Reg_EX_MEM[134]) | (Reg_EX_MEM[142:141]==2'b10))
//          mux_src = 2'b01;
//      else if(Reg_EX_MEM[142:141] == 2'b01)
//          mux_src = 2'b10;
//      else mux_src = 2'b00;
//end
/*
always@(*)
begin if((branch & zero & b_type) | (branch & ~zero & ~b_type) | (pc_src==2'b10) | (branch & b_type_bge & (zero | greater)))
          mux_src = 2'b01;
      else if(pc_src == 2'b01)
          mux_src = 2'b10;
      else mux_src = 2'b00;
end
*/
always@(*) Forward_1_data1=Forward1_data1;
always@(*)
    if(Reg_IF_ID_i[6:0]==7'b0010111) alu_src_a = 1'b1;
    else alu_src_a = 1'b0;
 
    always@(posedge clk or posedge rst) begin
        if(rst)begin
            pc<=0;
            pc_out<=0;
            Reg_IF_ID_o<=0;
            Reg_ID_EX_o<=0; 
            Reg_EX_MEM_o<=0;
            Reg_MEM_WB_o<=0;
        end
        else if (cache_resp_stall!=1) begin
        //alu_a_data<=alu_a;
        Reg_MEM_WB_o<={Reg_EX_MEM_i[240:209],Reg_EX_MEM_i[241],Reg_EX_MEM_i[140],Reg_EX_MEM_i[139:138],write_data,Reg_EX_MEM_i[100:69],Reg_EX_MEM_i[4:0]};
        /*Reg_MEM_WB<={csr_dout,csr_write,reg_write,mem_to_reg[1:0],write_data,addr_out,Reg_EX_MEM[4:0]};*/
        //Reg_EX_MEM[4],Reg_EX_MEM[3],Reg_EX_MEM[2],Reg_EX_MEM[1],Reg_EX_MEM[0]};
        Reg_EX_MEM_o<={Reg_ID_EX_i[11:5],Reg_ID_EX_i[24:20],Reg_ID_EX_i[36:25],Reg_ID_EX_i[19:17],ALU_A,Reg_ID_EX_i[245:214],Reg_ID_EX_i[246],Reg_ID_EX_i[247],Reg_ID_EX_i[213:182],greater,data_out,Reg_ID_EX_i[180],Reg_ID_EX_i[164:133],Reg_ID_EX_i[179:178],Reg_ID_EX_i[177],Reg_ID_EX_i[168:167],Reg_ID_EX_i[176:175],Reg_ID_EX_i[166],Reg_ID_EX_i[165],add_res,zero,addr_out,Reg_ID_EX_i[100:69],Reg_ID_EX_i[68:37],Reg_ID_EX_i[16:12]};
        /*Reg_EX_MEM<={pc,pc_src[1:0],reg_write,mem_to_reg[1:0],mux_src,branch,b_type,add_res,zero,addr_out,read_data_2,imm,Reg_ID_EX[4:0]};*/
        //if(Reg_EX_MEM[242]!=0)begin
        if(csr_pc_write!=0)begin
            Reg_ID_EX_o<=0;
            Reg_IF_ID_o<=0;
            //pc<=Reg_EX_MEM[274:243];
            //pc_out<=Reg_EX_MEM[274:243];
            //pc<=Reg_EX_MEM[338:307];
            //pc_out<=Reg_EX_MEM[338:307];
            pc<=csr_pc_next;//ex_mem
            pc_out<=csr_pc_next;
        end
        else if(mux_src!=0) begin
            Reg_ID_EX_o<=0;
            Reg_IF_ID_o<=0;
            pc<=pc_next;
            pc_out<=pc_next;
        end
        else if ((Reg_IF_ID_i[19:15]==Reg_ID_EX_i[16:12]||Reg_IF_ID_i[24:20]==Reg_ID_EX_i[16:12])&&Reg_ID_EX_i[168:167]==2'b11)//(IF_ID_Rs1==ID_EX_Rd||IF_ID_Rs2==ID_EX_Rd)&&ID_EX_mem_to_reg==2'b11
            begin
                Reg_ID_EX_o<=0;
            end
        else begin
        Reg_ID_EX_o<={csr_write,csr_pc_write,csr_pc_next,csr_dout,b_type_bge,mem_write,pc_src[1:0],reg_write,mux_src,alu_src_a,alu_src_b,alu_op[3:0],mem_to_reg[1:0],branch,b_type,Reg_IF_ID_i[63:32],read_data_1,read_data_2,imm,Reg_IF_ID_i[31:0],{5'b00000}};/*37-68*/
//        if(stall==1)begin
        //Reg_IF_ID<={pc,32'h00000013};
        //Reg_IF_ID<=(Reg_MEM_WB[71]==1&&Reg_MEM_WB[4:0]!=0&&(inst[19:15]==Reg_EX_MEM[4:0]||inst[19:15]==Reg_ID_EX[4:0]||inst[24:20]==Reg_EX_MEM[4:0]||inst[24:20]==Reg_ID_EX[4:0])) ? {pc,8'h00000013}:{pc,inst};
//        end
//        else begin
            Reg_IF_ID_o<={pc,inst};
             pc<=pc_next;
             pc_out <= pc_next;
           end
//           pc<=(Reg_MEM_WB[71]==1&&Reg_MEM_WB[4:0]!=0&&(inst[19:15]==Reg_EX_MEM[4:0]||inst[19:15]==Reg_ID_EX[4:0]||inst[24:20]==Reg_EX_MEM[4:0]||inst[24:20]==Reg_ID_EX[4:0]))? pc:pc_next;
//           pc_out<=(Reg_MEM_WB[71]==1&&Reg_MEM_WB[4:0]!=0&&(inst[19:15]==Reg_EX_MEM[4:0]||inst[19:15]==Reg_ID_EX[4:0]||inst[24:20]==Reg_EX_MEM[4:0]||inst[24:20]==Reg_ID_EX[4:0]))? pc_out:pc_next;
           
           
//         end
        end
//      else begin
//      Reg_MEM_WB_o<=0;
//      end
    end

Forwarding_Unit forwarding(
    .Rs1(Reg_ID_EX_i[24:20]),
    .Rs2(Reg_ID_EX_i[29:25]),
    .EX_MEM_Rd(Reg_EX_MEM_i[4:0]),
    .MEM_WB_Rd(Reg_MEM_WB_i[4:0]),
    .mem_to_reg(Reg_EX_MEM_i[139:138]),
    .ex_mem_reg_write(Reg_EX_MEM_i[140]),
    .mem_wb_reg_write(Reg_MEM_WB_i[71]),
    .ForwardA(ForwardA),
    .ForwardB(ForwardB)
    );
CSR csr(
    .clk(clk),
    .rst(rst),
    .inst(Reg_IF_ID_i[31:0]),
    .op_code(Reg_EX_MEM_i[333:327]),
    .funct3(Reg_EX_MEM_i[309:307]),
    .csr_addr(Reg_EX_MEM_i[321:310]),
    .zimm(Reg_EX_MEM_i[326:322]),
    .csr_din(Reg_EX_MEM_i[306:275]),
    //.csr_din(ALU_A),//ex_mem
    .pc_out(Reg_EX_MEM_i[174:143]),//ex_mem
    .csr_dout(csr_dout),//if_id->id_ex
    .csr_pc_next(csr_pc_next),//if_id->id_ex
    .csr_pc_write(csr_pc_write),//if_id->id_ex
    .csr_write(csr_write)//if_id->id_ex
//    .mtvec(mtvec),
//    .mepc(mepc),
//    .mstatus(mstatus)
    );
//MUX3T1_32 mux4(
//    .I0(pc_plus_4),
//    .I1(Reg_EX_MEM[142:101]),
//    //.I1(pc),
//    .I2(Reg_EX_MEM[133:102]),/*.I2(add_res),*/
//    .s(Reg_EX_MEM[142:141]),/*.s(pc_src),*/   /*EX_MEM*/
//    .o(mux_res)
//     );
Regs regs(
    .clk(clk),
    .rst(rst),
    .we(Reg_MEM_WB_i[71]),/*.we(reg_write),*/      
    .csr_write(Reg_MEM_WB_i[72]),
    .csr_dout(Reg_MEM_WB_i[104:73]),
    .reg_addr(reg_addr),
    .read_addr_1(Reg_IF_ID_i[19:15]),/*.read_addr_1(inst[19:15]),*/
    .read_addr_2(Reg_IF_ID_i[24:20]),/*.read_addr_2(inst[24:20]),*/
    .write_addr(Reg_MEM_WB_i[4:0]),/*.write_addr(inst[11:7]),*/
    .write_data(Reg_MEM_WB_i[68:37]),/*.write_data(write_data),*/
    .read_data_1(read_data_1),//output
    .read_data_2(read_data_2),//output
    .gp(gp),
    .register_data(register_data)
);
ImmGen imm_gen(
    .inst(Reg_IF_ID_i[31:0]),
    .imm(imm[31:0])
);
MUX2T1_32 mux5(
    .I0(Reg_ID_EX_i[132:101]),
    /*.I0(read_data_1),*/
    .I1(Reg_ID_EX_i[164:133]),//.I1(pc),/*???lab1-1好像用不到*/
    .s(Reg_ID_EX_i[174]),
    /*.s(alu_src_a),*//*ID_EX*/
    .o(alu_a)
    );
MUX2T1_32 mux1(
    .I0(Reg_ID_EX_i[100:69]),/*.I0(read_data_2),*/
    .I1(Reg_ID_EX_i[68:37]),/*.I1(imm),*/
    .s(Reg_ID_EX_i[173]),
    //.s(alu_src_b),
    .o(alu_b)//output
    );
MUX2T1_32 mux6(
    .I0(Reg_EX_MEM_i[100:69]),
    .I1(csr_dout),
    //.I1(Reg_EX_MEM[240:209]),
    .s(Reg_EX_MEM_i[241]&Reg_EX_MEM_i[140]),
    .o(Forward1_data1)
    );
 MUX2T1_32 mux7(
    .I0(Reg_MEM_WB_i[68:37]),
    .I1(Reg_MEM_WB_i[104:73]),
    .s(Reg_MEM_WB_i[72]&Reg_MEM_WB_i[71]),
    .o(Forward1_data2)
    );
//MUX2T1_32 mux8(
//    .I0(Reg_EX_MEM[36:5]),
//    .I1(),
//    .s(),
//    .o(Forward1_data3)
//    );
Forward_mux Forward1(
    .I0(alu_a),
    .I1(Forward1_data1),
    //.I1(Reg_EX_MEM[100:69]),
    .I2(Forward1_data2),
    //.I2(Reg_MEM_WB[68:37]),
    .I3(Reg_EX_MEM_i[36:5]),
    .e(Reg_ID_EX_i[174]),//ID_EX_alu_src_a
    .s(ForwardA),
    .o(ALU_A)
);
Forward_mux Forward2(
    .I0(alu_b),
    .I1(Reg_EX_MEM_i[100:69]),
    //.I1(addr_out),
    .I2(Reg_MEM_WB_i[68:37]),
    .I3(Reg_EX_MEM_i[36:5]),
    .e(Reg_ID_EX_i[173]),
    .s(ForwardB),
    .o(ALU_B)
);
Forward_mux Forward3(
    .I0(Reg_ID_EX_i[100:69]),//read_data_2
    .I1(Reg_EX_MEM_i[100:69]),//addr_out
    //.I1(addr_out),
    .I2(Reg_MEM_WB_i[68:37]),//write_data
    .I3(Reg_EX_MEM_i[36:5]),//imm
    .e(0),
    .s(ForwardB),
    .o(data_out)
);
ALU alu(
    .a(ALU_A[31:0]),
    .b(ALU_B[31:0]),
    .alu_op(Reg_ID_EX_i[172:169]),/*.alu_op(alu_op[3:0]),*/
    .res(addr_out),//output
    //.res_i(addr_out_i),
    .zero(zero),//output
    .greater(greater)
    );
//MUX3T1_32 mux3(/*lab2控制冒险，有点难，需要加一个stall*/
//    .I0(pc_plus_4),
//    .I1(Reg_EX_MEM[133:102]),/*.I1(add_res),*//*EX_MEM*/
//    .I2(Reg_EX_MEM[100:69]&~1),/*.I2(addr_out&~1),*/
//    //.s(Reg_EX_MEM[137:136]),
//    .s(mux_src),
//    .o(tmp_pc_next)
//    );
MUX3T1_32 mux3(/*lab2控制冒险，有点难，需要加一个stall*/
    .I0(pc_plus_4),
    .I1(add_res),/*.I1(add_res),*//*ID_EX*/
    .I2(addr_out&~1),/*.I2(addr_out&~1),*/
    //.s(Reg_EX_MEM[137:136]),
    .s(mux_src),
    .o(pc_next)
    );
//MUX2T1_32 mux4(
//    .I0(tmp_pc_next),
//    .I1(csr_pc_next),
//    .s(Reg_EX_MEM[242]),
//    //.s(csr_pc_write),
//    .o(pc_next)
//    );
MUX4T1_32 mux2(
    .I0(Reg_EX_MEM_i[100:69]),/*.I0(addr_out),*/ /*EX_MEM*/ 
    .I1(Reg_EX_MEM_i[36:5]),/*.I1(imm),*/
    .I2(Reg_EX_MEM_i[174:143]+8'h00000004),//.I2(pc_plus_4),
    .I3(data_in),
    .s(Reg_EX_MEM_i[139:138]),/*.s(mem_to_reg),*/ 
    .o(write_data)
    );
//always@(posedge clk or posedge rst) begin
//    if(rst)begin
//        pc<=0;
//        pc_out<=0;
//    end
//    else begin
//    pc<=pc_next;
//    pc_out <= pc_next;
//    end
//end
endmodule
