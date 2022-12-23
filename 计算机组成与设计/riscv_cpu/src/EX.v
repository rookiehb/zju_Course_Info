`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: zju
// Engineer: qmj
//////////////////////////////////////////////////////////////////////////////////
module EX1(ALUCode_ex, ALUSrcA_ex, ALUSrcB_ex,Imm_ex, rs1Addr_ex, rs2Addr_ex, rs1Data_ex, 
          rs2Data_ex, PC_ex, RegWriteData_wb, ALUResult_mem,rdAddr_mem, rdAddr_wb, 
		  RegWrite_mem, RegWrite_wb, ALUResult_ex, MemWriteData_ex, ALU_A, ALU_B);
    input [3:0] ALUCode_ex;
    input ALUSrcA_ex;
    input [1:0]ALUSrcB_ex;
    input [31:0] Imm_ex;
    input [4:0]  rs1Addr_ex;
    input [4:0]  rs2Addr_ex;
    input [31:0] rs1Data_ex;
    input [31:0] rs2Data_ex;
	input [31:0] PC_ex;
    input [31:0] RegWriteData_wb;
    input [31:0] ALUResult_mem;
	input [4:0] rdAddr_mem;
    input [4:0] rdAddr_wb;
    input RegWrite_mem;
    input RegWrite_wb;
    output [31:0] ALUResult_ex;
    output [31:0] MemWriteData_ex;
    output [31:0] ALU_A;
    output [31:0] ALU_B;
    
    // Forwarding
    wire [1:0] ForwardA, ForwardB;
    assign ForwardA[0]=RegWrite_wb && (rdAddr_wb!=0) && (rdAddr_mem!=rs1Addr_ex)&&(rdAddr_wb==rs1Addr_ex);
    assign ForwardA[1]=RegWrite_mem && (rdAddr_mem!=0) && (rdAddr_mem==rs1Addr_ex);
    assign ForwardB[0]=RegWrite_wb&&(rdAddr_wb!=0)&&(rdAddr_mem!=rs2Addr_ex)&&(rdAddr_wb==rs2Addr_ex);
    assign ForwardB[1]=RegWrite_mem&&(rdAddr_mem!=0)&&(rdAddr_mem==rs2Addr_ex);
        
    // data choice
    reg [31:0] ALU_A_reg=0, ALU_B_reg=0;
    reg [31:0] A=0, B=0;
    always @(*)
        begin
            case (ForwardA)
                2'b00: ALU_A_reg = rs1Data_ex;
                2'b01: ALU_A_reg = RegWriteData_wb;
                2'b10: ALU_A_reg = ALUResult_mem;
            endcase
            case (ForwardB)
                2'b00: ALU_B_reg = rs2Data_ex;
                2'b01: ALU_B_reg = RegWriteData_wb;
                2'b10: ALU_B_reg = ALUResult_mem;
            endcase
            
            if (!ALUSrcA_ex)
                A = ALU_A_reg;
            else
                A = PC_ex;
            
            case (ALUSrcB_ex)
                2'b00: B = ALU_B_reg;
                2'b01: B = Imm_ex;
                2'b10: B = 4;
             endcase
        end
        
    assign MemWriteData_ex = ALU_B_reg;
    ALU alu_0(
        .ALUResult(ALUResult_ex),
        .ALUCode(ALUCode_ex),
        .A(A), .B(B)
        );

    assign ALU_A = A;
    assign ALU_B = B;
    
endmodule
