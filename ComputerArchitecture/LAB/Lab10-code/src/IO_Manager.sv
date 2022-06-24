`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/28 18:16:05
// Design Name: 
// Module Name: IO_Manager
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


module IO_Manager(
        input  logic        clk,
    input  logic        resetn,

    // to cpu
    input  logic [31:0] address,
    input  logic [31:0] data_out,
    output logic [31:0] data_in,
    output logic        aresetn,
    output logic        step,
    output logic [31:0] chip_debug_in,
    
    // to gpio
    input  logic [15:0] switch,
    input  logic [ 4:0] button,
    output logic [15:0] led,
    output logic [ 7:0] num_csn,
    output logic [ 7:0] num_an,
    output logic [ 2:0] rgb1,
    output logic [ 2:0] rgb2,
    
    // debug
    input logic  [31:0] debug0,
    input logic  [31:0] debug1,
    input logic  [31:0] debug2,
    input logic  [31:0] debug3,
    input logic  [31:0] debug4,
    input logic  [31:0] debug5,
    input logic  [31:0] debug6,
    input logic  [31:0] debug7
);
    // Clock

    logic [31:0] clkn;
    counter counter_inst(clk, aresetn, clkn);

    // Button

    logic [4:0] button_dbnc;
    logic [4:0] button_down, button_up, button_last;
    button_debouncer bd4(clk, button[4], button_dbnc[4]);
    button_debouncer bd3(clk, button[3], button_dbnc[3]);
    button_debouncer bd2(clk, button[2], button_dbnc[2]);
    button_debouncer bd1(clk, button[1], button_dbnc[1]);
    button_debouncer bd0(clk, button[0], button_dbnc[0]);

    always_ff @ (posedge clk) begin
        if (aresetn) begin
            button_down <= ~button_last &  button_dbnc;
            button_up   <=  button_last & ~button_dbnc;
            button_last <=  button_dbnc;
        end
        else begin
            button_down <=  32'b0;
            button_up   <=  32'b0;
            button_last <=  32'b0;
        end
    end

    // chip_debug_in
    assign chip_debug_in = {21'b0,switch[10:0]};

    // Reset

    logic reset_dbnc;
    logic reset_down, reset_up, reset_last;
    button_debouncer bdr(clk, ~resetn, reset_dbnc);

    logic debug = 1'b0;
    logic [39:0] reset_cnt;

    always_ff @ (posedge clk) begin
        if (aresetn) begin
            reset_down <= ~reset_last &  reset_dbnc;
            reset_up   <=  reset_last & ~reset_dbnc;
            reset_last <=  reset_dbnc;
            
            if (reset_down) begin
                reset_cnt <= 0;
                aresetn <= 1;
            end
            else if (reset_dbnc) begin
                if (reset_cnt >= 40'h0_010_000_000) begin
                    aresetn <= 0;
                end else
                    reset_cnt <= reset_cnt + 1;
            end
            else if (reset_up) begin
                if (reset_cnt < 40'h0_010_000_000) begin
                    debug <= ~debug;
                    reset_cnt <= 0;
                end
            end
        end
        else begin
            aresetn <= resetn;
            debug <= 1'b1;
            reset_down <= 0;
            reset_up <= 0;
            reset_last <= 0;
        end
    end

    // Step

    logic step_wire = (~debug) | (debug & (button_up[0] | switch[15]));
    always_comb begin
        step <= step_wire;
    end

    // Data

    logic [31:0] data_src;
    always_comb begin
        case (switch[14:12])
            3'b000: data_src <= debug0;
            3'b001: data_src <= debug1;
            3'b010: data_src <= debug2;
            3'b011: data_src <= debug3;
            3'b100: data_src <= debug4;
            3'b101: data_src <= debug5;
            3'b110: data_src <= debug6;
            3'b111: data_src <= debug7;
        endcase
    end

    logic [63:0] shape_dec;

    hex_to_shape h2s7(data_src[31:28], shape_dec[63:56]);
    hex_to_shape h2s6(data_src[27:24], shape_dec[55:48]);
    hex_to_shape h2s5(data_src[23:20], shape_dec[47:40]);
    hex_to_shape h2s4(data_src[19:16], shape_dec[39:32]);
    hex_to_shape h2s3(data_src[15:12], shape_dec[31:24]);
    hex_to_shape h2s2(data_src[11: 8], shape_dec[23:16]);
    hex_to_shape h2s1(data_src[ 7: 4], shape_dec[15: 8]);
    hex_to_shape h2s0(data_src[ 3: 0], shape_dec[ 7: 0]);

    logic [63:0] shape_src = {64'hffff_ffff_ffff_ffff};

    // Output
    logic [63:0] shape = debug ? shape_dec : shape_src;

    segnum_manager sm(
        .clk(clkn[10]),
        .aresetn(aresetn),
        .shape(shape[63:0]),
        .num_csn(num_csn),
        .num_an(num_an)
    );

    assign led = switch;
    assign light = &clkn[12:10]; 
    assign rgb1 = {1'b0, {2{debug}}} & {3{light}};
    assign rgb2 = {3{~aresetn}} & {3{light}};

endmodule

module button_debouncer(
    input  logic  clk,
    input  logic  button,
    output logic  btn_dbnc
);

    logic [19:0] buffer = 0;

    always_ff @ (posedge clk) begin
        if (button) begin
            if (buffer == 20'hFFFFF)
                btn_dbnc <= 1'b1;
            else
                buffer += 20'h1;
        end
        else begin
            if (buffer == 20'h00000)
                btn_dbnc <= 1'b0;
            else
                buffer -= 20'h1;
        end
    end

endmodule

module hex_to_shape(
    input  logic [ 3:0] hex,
    output logic [ 7:0] shape
);

    always_comb begin
        case (hex)
            4'h0: shape <= 8'b11000000;
            4'h1: shape <= 8'b11111001;
            4'h2: shape <= 8'b10100100;
            4'h3: shape <= 8'b10110000;
            4'h4: shape <= 8'b10011001;
            4'h5: shape <= 8'b10010010;
            4'h6: shape <= 8'b10000010;
            4'h7: shape <= 8'b11111000;
            4'h8: shape <= 8'b10000000;
            4'h9: shape <= 8'b10010000;
            4'ha: shape <= 8'b10001000;
            4'hb: shape <= 8'b10000011;
            4'hc: shape <= 8'b10100111;
            4'hd: shape <= 8'b10100001;
            4'he: shape <= 8'b10000110;
            4'hf: shape <= 8'b10001110;
        endcase
    end

endmodule

module segnum_manager(
    input  logic        clk,
    input  logic        aresetn,
    input  logic [63:0] shape, 
    output logic [ 7:0] num_csn,
    output logic [ 7:0] num_an
);

    logic [7:0] state;
    assign num_an = state;

    always_ff @ (posedge clk) begin
        if (aresetn) begin
            case (state)
                8'b11111110: begin num_csn <= shape[15: 8]; state <= 8'b11111101; end  
                8'b11111101: begin num_csn <= shape[23:16]; state <= 8'b11111011; end
                8'b11111011: begin num_csn <= shape[31:24]; state <= 8'b11110111; end
                8'b11110111: begin num_csn <= shape[39:32]; state <= 8'b11101111; end
                8'b11101111: begin num_csn <= shape[47:40]; state <= 8'b11011111; end  
                8'b11011111: begin num_csn <= shape[55:48]; state <= 8'b10111111; end
                8'b10111111: begin num_csn <= shape[63:56]; state <= 8'b01111111; end
                8'b01111111: begin num_csn <= shape[ 7: 0]; state <= 8'b11111110; end
                default:     begin num_csn <= shape[ 7: 0]; state <= 8'b11111110; end
            endcase
        end else begin
            num_csn <= 8'b11000000;
            state <= 8'b00000000;
        end
    end

endmodule

module counter(
    input  logic clk,
    input  logic aresetn,
    output logic [31:0] clkn
);

    always_ff @ (posedge clk) begin
        if (aresetn)
            clkn <= clkn + 1;
        else
            clkn <= 0;
    end

endmodule
