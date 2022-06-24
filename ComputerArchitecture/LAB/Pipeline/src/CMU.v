`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/03/29 18:28:01
// Design Name: 
// Module Name: CMU
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


module CMU(
    input [6:0] op_code,
    output reg cache_req_wen,//cache写使能
    output reg cache_req_valid//发往cache的读写请求的有效性
//    input [31:0] mem_req_addr,
//    input [31:0] core_data_in,
//    input  mem_req_valid,
//    output reg mem_resp_valid
    );
//    always@(mem_req_addr or core_data_in)begin
//        if(mem_req_valid==1) mem_resp_valid=1;
//        else mem_resp_valid=0;
//    end
    always @(*) begin
//          cache_req_wen <= 1'b0;
//          cache_req_valid<=1'b0;
          case(op_code)
              7'b0100011:begin cache_req_wen <= 1'b1;cache_req_valid <=1'b1; end //SW
              7'b0000011:begin cache_req_wen <= 1'b0;cache_req_valid <=1'b1; end //LW
              default:begin cache_req_valid<=1'b0; cache_req_wen <= 1'b0;end
          endcase
      end

endmodule
