`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/11/17 21:10:20
// Design Name: 
// Module Name: Register
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


module Register(
    clk, RegWrite, ReadRegister1, ReadRegister2, WriteRegister, WriteData, ReadData1, ReadData2
    // rs1Sel, rs2Sel // TODO: function of rs*Sel
    );
    input clk;
    input RegWrite;
    input [4:0] WriteRegister;
    input [31:0] WriteData;
    input [4:0] ReadRegister1;
    input [4:0] ReadRegister2;
    output [31:0] ReadData1;
    output [31:0] ReadData2;
    
//    output rs1Sel;
//    output rs2Sel;
//================
// register heap
//=================

    reg[31:0] regs[31:0];
    wire [31:0] ReadData1_tmp;
    wire [31:0] ReadData2_tmp;
    assign ReadData1_tmp = (ReadRegister1==5'b0)?32'b0:regs[ReadRegister1];
    assign ReadData2_tmp = (ReadRegister2==5'b0)?32'b0:regs[ReadRegister2];
    always @(posedge clk) if (RegWrite) 
        begin 
            regs[WriteRegister]<=WriteData;
            regs[0]<=0;
        end
    wire rs1Sel,rs2Sel;
    assign rs1Sel = (RegWrite && (WriteRegister!=0) && (WriteRegister==ReadRegister1));
    assign rs2Sel = (RegWrite && (WriteRegister!=0) && (WriteRegister==ReadRegister2));
    assign ReadData1 = rs1Sel?WriteData:ReadData1_tmp;
    assign ReadData2 = rs2Sel?WriteData:ReadData2_tmp;
endmodule
