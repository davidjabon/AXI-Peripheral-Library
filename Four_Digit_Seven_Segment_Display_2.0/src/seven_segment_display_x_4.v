`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/26/2015 09:30:33 PM
// Design Name: 
// Module Name: seven_segment_display_x_4
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments: Note that the segments are a_to_g with a in position 0, b in position 1, etc.
//                      The reverse assignments are commented out to the right.
//			            To turn off decimal point set the corresponding bit low.
// 
//////////////////////////////////////////////////////////////////////////////////


module seven_segment_display_x_4(
    input [15:0] bcd_in,
    input [3:0] decimal_points,
    input clk,
    output reg [6:0] a_to_g,
    output reg decimal_point,
    output reg [3:0] anode
    );
    
wire [1:0] counter;
reg [3:0] digit;
reg [19:0] clkdiv;    
         
assign counter = clkdiv[19:18];   //count every 2.6 ms  (with 100 MHz clock)
    
//4 to 1 MUX
always @(posedge clk)
    case(counter)
        0: {digit, decimal_point, anode} = {bcd_in[3:0], ~decimal_points[0],  4'b1110};
        1: {digit, decimal_point, anode} = {bcd_in[7:4], ~decimal_points[1],  4'b1101};
        2: {digit, decimal_point, anode} = {bcd_in[11:8], ~decimal_points[2], 4'b1011};
        3: {digit, decimal_point, anode} = {bcd_in[15:12], ~decimal_points[3],4'b0111};
     endcase
    
//7-segment decoder 
always @(posedge clk)
     case(digit)
        0: a_to_g = 8'b1000000;  // 8'b0000001;
        1: a_to_g = 8'b1111001;  // 8'b1001111;
        2: a_to_g = 8'b0100100;  // 8'b0010010;
        3: a_to_g = 8'b0110000;  // 8'b0000110;
        4: a_to_g = 8'b0011001;  // 8'b1001100;
        5: a_to_g = 8'b0010010;  // 8'b0100100;
        6: a_to_g = 8'b0000010;  // 8'b0100000;
        7: a_to_g = 8'b1111000;  // 8'b0001111;
        8: a_to_g = 8'b0000000;  // 8'b0000000;
        9: a_to_g = 8'b0010000;  // 8'b0000100;
        default: a_to_g = 8'b11111111;  //default to blank
    endcase
          
         
//clock divider 
always  @ (posedge clk)
       begin
        clkdiv <= clkdiv + 20'b1;
       end 
           
endmodule
