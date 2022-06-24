`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/03/29 18:27:42
// Design Name: 
// Module Name: Cache
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


module ICache(
    input [31:0] cache_req_addr,//流水线发出的读/写地址
    output reg [31:0] cache_resp_data,//向流水线提交的数据内容
    output reg [31:0] mem_req_addr,//发往Memory的读/写地址
    input [31:0] mem_resp_data//内存返回数据
    );
    reg [31:0] cache_data[0:127];
    reg [22:0] cache_tag[0:127];
    reg [6:0] cache_index[0:127];
    reg [1:0] cache_offset[0:127];
    reg cache_V[0:127];
    reg cache_D[0:127];
    integer i;
    initial begin
        cache_resp_data<=0;
        for (i = 0; i < 128; i = i + 1) begin 
             cache_data[i] <= 0;
             cache_tag[i] <= 0;
             cache_index[i]<=i;
             cache_V[i]<=0;
             cache_D[i]<=0;
             cache_offset[i]<=0;
        end
    end
    always@(*)begin
        if(cache_req_addr=={cache_tag[cache_req_addr[8:2]],cache_req_addr[8:2],cache_offset[cache_req_addr[8:2]]}&&cache_V[cache_req_addr[8:2]]==1'b1)begin//hit
            cache_resp_data<=cache_data[cache_req_addr[8:2]];
        end
        else begin//miss
            cache_resp_data<=mem_resp_data;
            cache_data[cache_req_addr[8:2]]<=mem_resp_data;
            cache_tag[cache_req_addr[8:2]]<=cache_req_addr[31:9];
            cache_offset[cache_req_addr[8:2]]<=cache_req_addr[1:0];
            cache_V[cache_req_addr[8:2]]<=1'b1;
            cache_D[cache_req_addr[8:2]]<=1'b0;
        end
    end
endmodule
