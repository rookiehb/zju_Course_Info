`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/11/20 10:46:23
// Design Name: 
// Module Name: EX_MEM1
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

module EX_MEM1(
    // input
    input clk, MemtoReg_ex, RegWrite_ex, MemWrite_ex, MemRead_ex,
    input [31:0] ALUResult_ex, [31:0] MemWriteData_ex,
    input [4:0] rdAddr_ex,
    
    // output
    output MemtoReg_mem, RegWrite_mem, MemWrite_mem, MemRead_mem,
    output [31:0] ALUResult_mem, [31:0] MemWriteData_mem,
    output [4:0] rdAddr_mem
    );
    
    reg MemtoReg_mem_reg=0, RegWrite_mem_reg=0, MemWrite_mem_reg=0, MemRead_mem_reg=0;
    reg [31:0] ALUResult_mem_reg=0, MemWriteData_mem_reg=0;
    reg [4:0] rdAddr_mem_reg=0;
    
    always @(posedge clk)
        begin 
            MemtoReg_mem_reg = MemtoReg_ex;
            RegWrite_mem_reg = RegWrite_ex;
            MemWrite_mem_reg = MemWrite_ex;
            MemRead_mem_reg = MemRead_ex;
            ALUResult_mem_reg = ALUResult_ex;
            MemWriteData_mem_reg = MemWriteData_ex;
            rdAddr_mem_reg = rdAddr_ex;
        end
    assign MemtoReg_mem = MemtoReg_mem_reg;
    assign RegWrite_mem = RegWrite_mem_reg;
    assign MemWrite_mem = MemWrite_mem_reg;
    assign MemRead_mem = MemRead_mem_reg;
    assign ALUResult_mem = ALUResult_mem_reg;
    assign MemWriteData_mem = MemWriteData_mem_reg;
    assign rdAddr_mem = rdAddr_mem_reg;
endmodule
