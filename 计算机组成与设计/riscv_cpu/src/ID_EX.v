`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/11/20 10:46:23
// Design Name: 
// Module Name: ID_EX1
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

module ID_EX1(
        input clk,Stall, MemtoReg_id, RegWrite_id, MemWrite_id, MemRead_id, ALUSrcA_id,
        [1:0] ALUSrcB_id,
        input [3:0] ALUCode_id,
        input [31:0] PC_id, Imm_id, rs1Data_id, rs2Data_id, 
        input [4:0] rdAddr_id, rs1Addr_id, rs2Addr_id,
        
        output MemtoReg_ex, RegWrite_ex, MemWrite_ex, MemRead_ex, ALUSrcA_ex,
        output [3:0] ALUCode_ex, 
        output [1:0] ALUSrcB_ex,
        output [31:0] PC_ex, Imm_ex, rs1Data_ex, rs2Data_ex, 
        output [4:0] rdAddr_ex, rs1Addr_ex, rs2Addr_ex
    );
    
    reg MemtoReg_id_reg=0, RegWrite_id_reg=0, MemWrite_id_reg=0, MemRead_id_reg=0, ALUSrcA_id_reg=0;
    reg [1:0] ALUSrcB_id_reg=0;
    reg [3:0] ALUCode_id_reg=0;
    reg [31:0] PC_id_reg=0, Imm_id_reg=0, rs1Data_id_reg=0, rs2Data_id_reg=0; 
    reg [4:0] rdAddr_id_reg=0, rs1Addr_id_reg=0, rs2Addr_id_reg=0;
    
    always @(posedge clk)
        begin
            if (Stall) begin
                MemtoReg_id_reg = 0; 
                RegWrite_id_reg = 0; 
                MemWrite_id_reg = 0; 
                MemRead_id_reg  = 0;
                ALUCode_id_reg  = 0; 
                ALUSrcA_id_reg  = 0; 
                ALUSrcB_id_reg  = 0; 
                PC_id_reg       = 0; 
                Imm_id_reg      = 0; 
                rdAddr_id_reg   = 0;
                rs1Addr_id_reg  = 0;
                rs2Addr_id_reg  = 0;
                rs1Data_id_reg  = 0;
                rs2Data_id_reg  = 0;
                end
            else begin
                MemtoReg_id_reg = MemtoReg_id;
                RegWrite_id_reg = RegWrite_id;
                MemWrite_id_reg = MemWrite_id;
                MemRead_id_reg = MemRead_id;
                ALUCode_id_reg = ALUCode_id;
                ALUSrcA_id_reg = ALUSrcA_id;
                ALUSrcB_id_reg = ALUSrcB_id;
                PC_id_reg = PC_id;
                Imm_id_reg = Imm_id;
                rs1Data_id_reg = rs1Data_id;
                rs2Data_id_reg = rs2Data_id;
                rdAddr_id_reg = rdAddr_id;
                rs1Addr_id_reg = rs1Addr_id;
                rs2Addr_id_reg = rs2Addr_id;
                end
        end
        assign MemtoReg_ex=MemtoReg_id_reg;
        assign RegWrite_ex=RegWrite_id_reg;
        assign MemWrite_ex=MemWrite_id_reg; 
        assign MemRead_ex=MemRead_id_reg;
        assign ALUCode_ex=ALUCode_id_reg;
        assign ALUSrcA_ex=ALUSrcA_id_reg;
        assign ALUSrcB_ex = ALUSrcB_id_reg;
        assign PC_ex=PC_id_reg;
        assign Imm_ex=Imm_id_reg;
        assign rs1Data_ex=rs1Data_id_reg;
        assign rs2Data_ex=rs2Data_id_reg;
        assign rdAddr_ex=rdAddr_id_reg;
        assign rs1Addr_ex=rs1Addr_id_reg;
        assign rs2Addr_ex=rs2Addr_id_reg;
endmodule
