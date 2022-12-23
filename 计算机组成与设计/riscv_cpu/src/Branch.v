`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/11/17 22:00:16
// Design Name: 
// Module Name: Branch
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
module Branch(
    rs1Data, rs2Data, Instruction, Branch
    );
//===========================
// Branch test
//===========================
    input [31:0] rs1Data;
    input [31:0] rs2Data;
    input [31:0] Instruction;
    output Branch;
//======================
// Parameter 
//======================\
    parameter SB_type_op = 7'b1100011;
    parameter beq_funct3 = 3'b000;
    parameter bne_funct3 = 3'b001;
    parameter blt_funct3 = 3'b100;
    parameter bge_funct3 = 3'b101;
    parameter bltu_funct3 = 3'b110;
    parameter bgeu_funct3 = 3'b111;
//=======================
// Code
//=======================
    wire [6:0] op;
    wire [31:0] sum;
    wire [2:0] funct3;
//    wire isLT, isLTU;
    
    assign op = Instruction[6:0];
    assign sum = rs1Data+(~rs2Data)+1;
    assign funct3 = Instruction[14:12];
    
    reg Branch_id=0;
    always @(*)
        begin
        if (op==SB_type_op)
            case (funct3)
                beq_funct3: Branch_id = ~(|sum[31:0]);
                bne_funct3: Branch_id = |sum[31:0];
                blt_funct3: Branch_id = rs1Data[31]&&(~rs2Data[31])||(rs1Data[31]~^rs2Data[31])&&sum[31];
                bge_funct3: Branch_id = ~(rs1Data[31]&&(~rs2Data[31])||(rs1Data[31]~^rs2Data[31])&&sum[31]);
                bltu_funct3: Branch_id = (~rs1Data[31])&&rs2Data[31]||(rs1Data[31]~^rs2Data[31])&&sum[31];
                bgeu_funct3: Branch_id = ~((~rs1Data[31])&&rs2Data[31]||(rs1Data[31]~^rs2Data[31])&&sum[31]);
                default: Branch_id = 0;
            endcase
         else Branch_id = 0;
//            if ((op==SB_type_op)&&(funct3==beq_funct3))
//                Branch_id = ~(|sum[31:0]);
//            else if ((op==SB_type_op)&&(funct3==bne_funct3))
//                Branch_id = |sum[31:0];
//            else if ((op==SB_type_op)&&(funct3==blt_funct3))
//                Branch_id = rs1Data[31]&&(~rs2Data[31])||(rs1Data[31]~^rs2Data[31])&&sum[31];
//            else if ((op==SB_type_op)&&(funct3==bge_funct3))
//                Branch_id = ~(rs1Data[31]&&(~rs2Data[31])||(rs1Data[31]~^rs2Data[31])&&sum[31]);
//            else if ((op==SB_type_op)&&(funct3==bltu_funct3))
//                Branch_id = (~rs1Data[31])&&rs2Data[31]||(rs1Data[31]~^rs2Data[31])&&sum[31];
//            else if ((op==SB_type_op)&&(funct3==bgeu_funct3))
//                Branch_id = ~((~rs1Data[31])&&rs2Data[31]||(rs1Data[31]~^rs2Data[31])&&sum[31]);
//            else
//                Branch_id = 0;
        end

    assign Branch = Branch_id;
endmodule
