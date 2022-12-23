`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/11/20 10:46:23
// Design Name: 
// Module Name: IF_ID1
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


module IF_ID1(
    // input
    input clk, EN, IF_flush,
    input [31:0] PC_if, Instruction_if,
    // output
    output [31:0] PC_id, Instruction_id
    );
    reg [31:0] PC_if_reg=0, Instruction_if_reg=0;
    
    always @(posedge clk)
        begin     
            if (EN && IF_flush==0)
                begin
                    PC_if_reg = PC_if;
                    Instruction_if_reg = Instruction_if;
                end
            else if (IF_flush==1)
                begin
                    PC_if_reg = 0;
                    Instruction_if_reg = 0;
                end
            else 
                begin     
                    PC_if_reg = PC_if_reg;
                    Instruction_if_reg = Instruction_if_reg;    
                end
        end
    assign PC_id=PC_if_reg;
    assign Instruction_id = Instruction_if_reg;
endmodule
