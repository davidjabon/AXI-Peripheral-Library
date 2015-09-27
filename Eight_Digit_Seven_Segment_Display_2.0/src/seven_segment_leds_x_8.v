`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    22:04:40 05/25/2015 
// Design Name: 
// Module Name:    seven_segment_leds_x_4 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments:   Note that the segments are a_to_g with a in position 0, b in position 1, etc.
//                        The reverse assignments are commented out to the right.
//			  To turn off decimal point set the corresponding bit low.
//
//////////////////////////////////////////////////////////////////////////////////
module seven_segment_leds_x_8(
    input [31:0] bcd_in,
    input [7:0] decimal_points,
    input clk,
    output  reg [6:0] a_to_g,
    output reg decimal_point,
    output reg [7:0] anode 
    );

wire [2:0] counter;
reg [3:0] digit;
reg [20:0] clkdiv;	
	 

assign counter = clkdiv[20:18];   //count every 2.6 ms  (with 100 MHz clock)

//quad 4 to 1 MUX
always @(posedge clk)
    case(counter)
	0: {digit, decimal_point} = {bcd_in[3:0], ~decimal_points[0]};
	1: {digit, decimal_point} = {bcd_in[7:4], ~decimal_points[1]};
	2: {digit, decimal_point} = {bcd_in[11:8], ~decimal_points[2]};
	3: {digit, decimal_point} = {bcd_in[15:12], ~decimal_points[3]};
	4: {digit, decimal_point} = {bcd_in[19:16], ~decimal_points[4]};
    	5: {digit, decimal_point} = {bcd_in[23:20], ~decimal_points[5]};
    	6: {digit, decimal_point} = {bcd_in[27:24], ~decimal_points[6]};
    	7: {digit, decimal_point} = {bcd_in[31:28], ~decimal_points[7]};
     endcase

//7-segment decoder 
always @(posedge clk)
     case(digit)
    	0: a_to_g = 8'b1000000;  //8'b0000001;
    	1: a_to_g = 8'b1111001;  //8'b1001111;
	2: a_to_g = 8'b0100100;  //8'b0010010;
	3: a_to_g = 8'b0110000;  //8'b0000110;
	4: a_to_g = 8'b0011001;  //8'b1001100;
	5: a_to_g = 8'b0010010;  //8'b0100100;
	6: a_to_g = 8'b0000010;  //8'b0100000;
	7: a_to_g = 8'b1111000;  //8'b0001111;
	8: a_to_g = 8'b0000000;  //8'b0000000;
	9: a_to_g = 8'b0010000;  //8'b0000100;
	default: a_to_g = 8'b11111111;  //default to blank
    endcase
	  
//digit selector
always @(posedge clk)
    case(counter)
        0: anode = 8'b11111110;
	1: anode = 8'b11111101;
	2: anode = 8'b11111011;
	3: anode = 8'b11110111;
	4: anode = 8'b11101111;
        5: anode = 8'b11011111;
        6: anode = 8'b10111111;
        7: anode = 8'b01111111;
	default: anode = 8'b11111111;  //all blank
     endcase
     
//clock divider 
always  @ (posedge clk)
   begin
	clkdiv <= clkdiv + 21'b1;
    end 
	  
endmodule
