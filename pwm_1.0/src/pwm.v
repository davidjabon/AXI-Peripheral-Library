`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/22/2015 09:35:04 AM
// Design Name: 
// Module Name: pwm
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:  Enable signal is assumed to synchronous; if enable transitions low during pwm pulse,
//                       pulse will gracefully complete
//
//////////////////////////////////////////////////////////////////////////////////


module pwm (
    input clk,
    input enable,
	input [31:0] clk_period,
    input [31:0] pwm_period,
    output out
    );
    
reg clk_out=1'b0;
reg [31:0] counter = 32'b0;

always @(posedge clk)
begin
  if (enable == 1'b1)
    begin
      if (counter < pwm_period)
        begin
         clk_out <= 1'b1;
         counter <= counter + 32'b1;
        end
      else
        begin
        if (counter < (clk_period-1))
         begin
          clk_out <= 1'b0;
          counter <= counter + 32'b1;
         end
        else 
         begin
          clk_out <= 1'b0;
          counter <= 32'b0;
         end
       end //end if counter < pwm_period
      
     end   //end if(enable)
   else
     begin
        if ((counter > 0) && (counter < pwm_period) )   //gracefully end the last pwm if it has begun
           begin
              clk_out <= 1'b1;
              counter <= counter + 32'b1;
           end
        else
           begin
             clk_out <= 1'b0;
             counter <= 32'b0;
           end
     end 
   
end 

assign out = clk_out;
    
endmodule