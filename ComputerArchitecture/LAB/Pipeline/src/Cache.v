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


module DCache(
    input clk,
    input rst,
    input [6:0] debug_cache_index,
    output reg [31:0] debug_cache_out0,
    output reg [31:0] debug_cache_out1,
    output reg [31:0] debug_cache_out2,
    input [31:0] cache_req_addr,//流水线发出的读/写地址
    input [31:0] cache_req_data,//写入数据
    input cache_req_wen,//cache写使能，写1，读0
    input cache_req_valid,//发往cache的读写请求的有效性，读或写1
    output reg [31:0] cache_resp_data,//向流水线提交的数据内容
    output reg cache_resp_stall,//流水线是否需要继续stall
    output reg [31:0] mem_req_addr,//发往Memory的读/写地址
    output reg [31:0] mem_req_data,//发往Memory写入的数据
    output reg mem_req_wen,//Memory写使能
    output reg mem_req_valid,//发往Memory的读写请求的有效性,miss=1,hit=0
    input [31:0] mem_resp_data,//内存返回数据
    input mem_resp_valid//Memory数据查询完成1,未完成0
    );
    reg [31:0] cache_data[0:127];
    reg [22:0] cache_tag[0:127];
    reg [6:0] cache_index[0:127];
    reg [1:0] cache_offset[0:127];
    reg cache_V[0:127];
    reg cache_D[0:127];
    reg hit,miss,read,write;
    integer i;
//    initial begin
//        cache_resp_data<=0;
//        cache_resp_stall<=0;
//        mem_req_addr<=0;
//        mem_req_data<=0;
//        mem_req_wen<=0;
//        mem_req_valid<=1'b0;
//        miss<=0;
//        hit<=0;
//        read<=0;
//        write<=0;
//    end
    always@(*)begin
        debug_cache_out0<=cache_data[debug_cache_index];
        //debug_cache_out0<=cache_req_addr;
        //debug_cache_out1<=mem_resp_data;
        debug_cache_out1<={cache_tag[debug_cache_index],cache_index[debug_cache_index],cache_V[debug_cache_index],cache_D[debug_cache_index]};
        //debug_cache_out2<={3'b0,cache_req_wen,3'b0,cache_req_valid,3'b0,cache_resp_stall,3'b0,mem_req_wen,3'b0,mem_req_valid,3'b0,mem_resp_valid,8'hff};
    end
    always@(negedge clk or posedge rst)begin
    //always@(cache_req_addr or mem_resp_data  or cache_req_valid)begin
        if(rst==1)begin
            cache_resp_data<=0;
            cache_resp_stall<=0;
            mem_req_addr<=0;
            mem_req_data<=0;
            mem_req_wen<=0;
            mem_req_valid<=1'b0;
            miss<=0;
            hit<=0;
            read<=0;
            write<=0;
           for (i = 0; i < 128; i = i + 1) begin 
            cache_data[i]<= 0;
            cache_tag[i]<= 0;
            cache_index[i]<=i;
            cache_V[i]<=0;
            cache_D[i]<=0;
            cache_offset[i]<=0;
           end
        end
        else if(cache_req_valid==1'b1)begin
            if(cache_req_wen==0)begin//read
                read<=1;
                write<=0;
                if(cache_req_addr=={cache_tag[cache_req_addr[8:2]],cache_req_addr[8:2],cache_offset[cache_req_addr[8:2]]}&&cache_V[cache_req_addr[8:2]]==1'b1)begin//hit
                    hit<=1;
                    miss<=0;
                    cache_resp_data<=cache_data[cache_req_addr[8:2]];
                    cache_resp_stall<=0;
                    mem_req_wen<=0;
                    mem_req_valid<=1'b0;
                end
                else begin//miss
                    miss<=1;
                    hit<=0;
                    if(cache_D[cache_req_addr[8:2]]==1'b1)begin//dirty
                        if(mem_resp_valid==1'b1) begin//write->read
                            cache_resp_stall<=1;
                            mem_req_wen<=0;
                            mem_req_valid<=1'b1;
                            mem_req_addr<=cache_req_addr;
                            cache_D[cache_req_addr[8:2]]<=1'b0;
                        end
                        else begin
                            cache_resp_stall<=1;
                            mem_req_addr<={cache_tag[cache_req_addr[8:2]],cache_req_addr[8:2],cache_offset[cache_req_addr[8:2]]};
                            mem_req_data<=cache_data[cache_req_addr[8:2]];
                            mem_req_wen<=1'b1;
                            mem_req_valid<=1'b1;
                        end
                    end
                    else begin//clean
                        if(mem_resp_valid==1'b1) begin//read
                            cache_resp_data<=mem_resp_data;
                            cache_resp_stall<=1'b0;
                            mem_req_wen<=1'b0;
                            mem_req_valid<=1'b0;
                            cache_data[cache_req_addr[8:2]]<=mem_resp_data;
                            cache_tag[cache_req_addr[8:2]]<=cache_req_addr[31:9];
                            cache_offset[cache_req_addr[8:2]]<=cache_req_addr[1:0];
                            cache_V[cache_req_addr[8:2]]<=1'b1;
                            //cache_D[cache_req_addr[8:2]]<=1'b0;
                        end
                        else begin
                            cache_resp_stall<=1;
                            mem_req_addr<=cache_req_addr;
                            //mem_req_data<=cache_data[cache_req_addr[8:2]];
                            mem_req_wen<=1'b0;
                            mem_req_valid<=1'b1;
                        end
                    end
                end
            end
            else begin//write
                read<=0;
                write<=1;
                if((cache_req_addr=={cache_tag[cache_req_addr[8:2]],cache_req_addr[8:2],cache_offset[cache_req_addr[8:2]]}&&cache_V[cache_req_addr[8:2]]==1'b1)||cache_D[cache_req_addr[8:2]]==1'b0)begin//hit
                    //cache_resp_data<=mem_resp_data;
                    hit<=1;
                    miss<=0;
                    cache_resp_stall<=1'b0;
                    mem_req_wen<=1'b0;
                    mem_req_valid<=1'b0;
                    cache_data[cache_req_addr[8:2]]<=cache_req_data;
                    cache_tag[cache_req_addr[8:2]]<=cache_req_addr[31:9];
                    cache_offset[cache_req_addr[8:2]]<=cache_req_addr[1:0];
                    cache_V[cache_req_addr[8:2]]<=1'b1;
                    cache_D[cache_req_addr[8:2]]<=1'b1;
                end
                else begin//miss
                    miss<=1;
                    hit<=0;
                    if(mem_resp_valid==1'b1) begin
                        cache_resp_stall<=1'b0;
                        mem_req_wen<=1'b0;
                        mem_req_valid<=1'b0;
                        cache_data[cache_req_addr[8:2]]<=cache_req_data;
                        cache_tag[cache_req_addr[8:2]]<=cache_req_addr[31:9];
                        cache_offset[cache_req_addr[8:2]]<=cache_req_addr[1:0];
                        cache_V[cache_req_addr[8:2]]<=1'b1;
                        cache_D[cache_req_addr[8:2]]<=1'b1;
                    end
                    else begin
                        cache_resp_stall<=1;
                        mem_req_addr<={cache_tag[cache_req_addr[8:2]],cache_req_addr[8:2],cache_offset[cache_req_addr[8:2]]};
                        mem_req_data<=cache_data[cache_req_addr[8:2]];
                        mem_req_wen<=1'b1;
                        mem_req_valid<=1'b1;
                    end
                end
            end
        end
    end
endmodule
