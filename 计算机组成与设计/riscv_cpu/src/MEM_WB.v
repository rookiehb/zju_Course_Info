`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/11/20 10:46:23
// Design Name: 
// Module Name: MEM_WB1
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


module MEM_WB1(
    // input
    input clk, MemtoReg_mem, RegWrite_mem,
    input [31:0] ALUResult_mem, [31:0] memDout_mem,
    input [4:0] rdAddr_mem,
    
    // output
    output MemtoReg_wb, RegWrite_wb,
    output [31:0] ALUResult_wb, [31:0] memDout_wb,
    output [4:0] rdAddr_wb  
    );
    
    reg MemtoReg_wb_reg=0, RegWrite_wb_reg=0;
    reg [31:0] ALUResult_wb_reg=0;
    reg [31:0] memDout_wb_reg=0;
    reg [4:0] rdAddr_wb_reg=0;
    
    always @(posedge clk)
        begin
            MemtoReg_wb_reg = MemtoReg_mem;
            RegWrite_wb_reg = RegWrite_mem;
            ALUResult_wb_reg = ALUResult_mem;
            memDout_wb_reg = memDout_mem;
            rdAddr_wb_reg = rdAddr_mem;
        end
    assign MemtoReg_wb = MemtoReg_wb_reg;
    assign RegWrite_wb = RegWrite_wb_reg;
    assign ALUResult_wb = ALUResult_wb_reg;
    assign memDout_wb = memDout_wb_reg;
    assign rdAddr_wb = rdAddr_wb_reg;
endmodule
