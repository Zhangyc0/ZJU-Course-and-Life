`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/02/13 21:10:49
// Design Name: 
// Module Name: CSR
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


module CSR(
    input clk,
    input rst,
    input [31:0] inst,
    input [6:0] op_code,
    input [2:0] funct3,
    input [11:0] csr_addr,
    input [4:0] zimm,
    input [31:0] csr_din,
    input [31:0] pc_out,
    output reg [31:0] csr_dout,
    output reg [31:0] csr_pc_next,
    output reg csr_pc_write,
    output reg csr_write
//    output reg [31:0] mtvec,
//    output reg [31:0] mepc,
//    output reg [31:0] mstatus
    );
        reg [31:0] mtvec;
        reg [31:0] mepc;
        reg [31:0] mstatus;
        
        initial begin
            mtvec<=0;
            mepc<=0;
            mstatus<=0;
            csr_pc_next<=0;
            csr_write<=0;
            //csr_pc_write<=0;
        end
        always @(*) begin
        //csr_pc_write = 0;
        csr_write=0;
            if (rst == 1) begin
                csr_write=0;
                //csr_pc_write=0;
            end
            else if (inst==32'h00000073 || inst==32'h00100073)begin//ECALL
                   //csr_pc_write = 1;
                   csr_write = 1;
                   //csr_pc_next = mtvec;
           end else if (inst==32'h30200073)begin
            //csr_pc_write = 1;
            csr_write = 1;
            //csr_pc_next = mepc;
           end
           else begin //csr_pc_write =0;
             if (inst[6:0]==7'b1110011) begin
            csr_write =1;
            end
        end
        end
        
        
        
        always @(posedge clk or posedge rst)begin
            if(rst==1)begin
            mtvec<=0;
            mepc<=0;
            mstatus<=0;
            end
            
            else begin
            if (op_code==7'b1110011) begin
              if (csr_addr == 12'h300) begin
                  case(funct3)
                     3'b011:begin
                        mstatus <= mstatus & csr_din;
                     end
                     3'b111:begin
                         mstatus <= mstatus & {27'b0,zimm};
                     end
                     3'b010:begin
                         mstatus <= mstatus | csr_din;
                     end
                     3'b110:begin
                         mstatus <= mstatus | {27'b0,zimm};
                     end
                     3'b001:begin
                         mstatus <= csr_din;
                     end
                     3'b101:begin
                         mstatus <= {27'b0,zimm};
                     end
                  endcase
               end
               else if(csr_addr == 12'h305)begin
                   case(funct3)
                   3'b011:begin
                   mtvec <= mtvec & csr_din;
                   end
                   3'b111:begin
                       mtvec <= mtvec & {27'b0,zimm};
                    end
                   3'b010:begin
                       mtvec <= mtvec | csr_din;
                   end
                   3'b110:begin
                       mtvec <= mtvec | {27'b0,zimm};
                    end
                    3'b001:begin
                      mtvec <= csr_din;
                     end
                    3'b101:begin
                      mtvec <= {27'b0,zimm};
                     end
                   endcase
                 end 
                else if(csr_addr == 12'h341)begin
                    case(funct3)
                        3'b011:begin
                            mepc <= mepc & csr_din;
                        end
                        3'b111:begin
                            mepc <= mepc & {27'b0,zimm};
                        end
                        3'b010:begin
                            mepc <= mepc | csr_din;
                        end
                        3'b110:begin
                            mepc <= mepc | {27'b0,zimm};
                        end
                        3'b001:begin
                          mepc <= csr_din;
                        end
                        3'b101:begin
                          mepc <= {27'b0,zimm};
                        end
                     endcase
                   end
                //else if(csr_addr==12'h302)begin csr_pc_next=mepc; end
                else if(csr_addr == 12'h000 || csr_addr == 12'h001)begin mepc<=pc_out;end
                end
            end
        end

always @(*)begin
csr_pc_write=0;
    if(op_code==7'b1110011)begin
        if(csr_addr==12'h302)begin
            csr_pc_next=mepc;
            csr_pc_write=1;
        end
        else if(csr_addr==12'h000 || csr_addr==12'h001)begin
            csr_pc_next=mtvec;
            csr_pc_write=1;
        end
    end
end


        always @(*) begin

            if (rst == 1) begin
                csr_dout<=0;
            end
         
           else begin
             if (inst[6:0]==7'b1110011) begin
                if (inst[31:20] == 12'h300) begin
                    csr_dout <= mstatus;
                end
                else if(inst[31:20] == 12'h305)begin
                    csr_dout <= mtvec;
                end 
                else if(inst[31:20] == 12'h341)begin
                    csr_dout <= mepc;
                end
            end

        end
        end

endmodule
