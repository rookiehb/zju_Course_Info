`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/11/22 09:14:27
// Design Name: 
// Module Name: mux2_wb
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

module mux2_wb(
    input MemtoReg_wb,
    input [31:0] memDout_wb, ALUResult_wb,
    output [31:0] RegWriteData_wb
    );
    assign RegWriteData_wb = MemtoReg_wb?memDout_wb:ALUResult_wb;
endmodule
