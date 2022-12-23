`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: zju
// Engineer: qmj
//////////////////////////////////////////////////////////////////////////////////
module Risc5CPU(clk, reset, JumpFlag, Instruction_id, ALU_A, 
                     ALU_B, ALUResult_ex, PC, MemDout_mem,Stall);
                     
    input clk;
    input reset;
    output[1:0] JumpFlag;
    output [31:0] Instruction_id;
    output [31:0] ALU_A;
    output [31:0] ALU_B;
    output [31:0] ALUResult_ex;
    output [31:0] PC;
    output [31:0] MemDout_mem;
    output Stall;
    
    wire IFWrite, IF_flush;
    wire [31:0] JumpAddr, Instruction_if;
    IF1 IF_Module(clk, reset, JumpFlag[0], JumpFlag[1], IFWrite, JumpAddr,Instruction_if, PC, IF_flush);
    
    wire [31:0] PC_id;
    IF_ID1 pipeline_IF_ID(clk, IFWrite, IF_flush||reset, PC, Instruction_if, PC_id, Instruction_id);
    
    wire RegWrite_wb, MemRead_ex, MemtoReg_id, RegWrite_id, MemWrite_id,  ALUSrcA_id, MemRead_id;
    wire [31:0] RegWriteData_wb;
    wire [4:0] rdAddr_wb;
    wire [3:0] ALUCode_id;
    wire [1:0] ALUSrcB_id;
    wire [31:0] Imm_id,rs1Data_id,rs2Data_id;
    wire [4:0] rs1Addr_id,rs2Addr_id,rdAddr_id;
    wire [4:0] rdAddr_ex, rs1Addr_ex, rs2Addr_ex;
    ID ID_Module(clk, Instruction_id, PC_id, RegWrite_wb, rdAddr_wb, RegWriteData_wb, MemRead_ex, 
              rdAddr_ex, MemtoReg_id, RegWrite_id, MemWrite_id, MemRead_id, ALUCode_id, 
                 ALUSrcA_id, ALUSrcB_id, Stall, JumpFlag[0], JumpFlag[1], IFWrite, JumpAddr, Imm_id,
                 rs1Data_id, rs2Data_id, rs1Addr_id, rs2Addr_id, rdAddr_id);
    
    wire MemtoReg_ex, RegWrite_ex, MemWrite_ex, ALUSrcA_ex;
    wire [1:0] ALUSrcB_ex;
    wire [31:0] PC_ex, Imm_ex, rs1Data_ex, rs2Data_ex;
    wire [3:0] ALUCode_ex;
    wire [31:0] ALUResult_mem;
    wire [4:0] rdAddr_mem;
    wire RegWrite_mem;
    wire [31:0] MemWriteData_ex;
         
    ID_EX1 pipeline_ID_EX(
        clk,Stall|reset, MemtoReg_id,RegWrite_id,MemWrite_id,MemRead_id,ALUSrcA_id,ALUSrcB_id,ALUCode_id,
        PC_id, Imm_id, rs1Data_id, rs2Data_id, rdAddr_id, rs1Addr_id, rs2Addr_id,
        MemtoReg_ex, RegWrite_ex, MemWrite_ex, MemRead_ex, ALUSrcA_ex, ALUCode_ex,
        ALUSrcB_ex, PC_ex, Imm_ex, rs1Data_ex, rs2Data_ex, rdAddr_ex,
        rs1Addr_ex, rs2Addr_ex);
     
     wire [1:0] ForwardA, ForwardB;
     assign ForwardA[0]=RegWrite_wb && (rdAddr_wb!=0) && (rdAddr_mem!=rs1Addr_ex)&&(rdAddr_wb==rs1Addr_ex);
     assign ForwardA[1]=RegWrite_mem && (rdAddr_mem!=0) && (rdAddr_mem==rs1Addr_ex);
     assign ForwardB[0]=RegWrite_wb&&(rdAddr_wb!=0)&&(rdAddr_mem!=rs2Addr_ex)&&(rdAddr_wb==rs2Addr_ex);
     assign ForwardB[1]=RegWrite_mem&&(rdAddr_mem!=0)&&(rdAddr_mem==rs2Addr_ex);

     EX1 EX_Module(ALUCode_ex, ALUSrcA_ex, ALUSrcB_ex,Imm_ex, rs1Addr_ex, rs2Addr_ex, rs1Data_ex, 
                  rs2Data_ex, PC_ex, RegWriteData_wb, ALUResult_mem, rdAddr_mem, rdAddr_wb, 
                  RegWrite_mem, RegWrite_wb, ALUResult_ex, MemWriteData_ex, ALU_A, ALU_B);
     
     wire MemtoReg_mem, MemWrite_mem, MemRead_mem;
     wire [31:0] MemWriteData_mem; 
     EX_MEM1 pipeline_EX_MEM(clk, MemtoReg_ex, RegWrite_ex, MemWrite_ex, MemRead_ex,
            ALUResult_ex, MemWriteData_ex, rdAddr_ex, MemtoReg_mem, RegWrite_mem, 
            MemWrite_mem, MemRead_mem, ALUResult_mem, MemWriteData_mem, rdAddr_mem);
    
    // data memory
    
    dist_mem_gen_0 call_dist_mem_gen_0(.a(ALUResult_mem[7:2]),
    .d(MemWriteData_mem),.clk(clk),.we(MemWrite_mem),.spo(MemDout_mem));
    
     wire MemtoReg_wb;
     wire [31:0] ALUResult_wb;
     wire [31:0] memDout_wb;
     MEM_WB1 pipeline_MEM_WB(clk, MemtoReg_mem, RegWrite_mem, ALUResult_mem, MemDout_mem, rdAddr_mem,
                            MemtoReg_wb, RegWrite_wb, ALUResult_wb, memDout_wb, rdAddr_wb);
     mux2_wb mux2_Module(.MemtoReg_wb(MemtoReg_wb),.memDout_wb(memDout_wb),.ALUResult_wb(ALUResult_wb),
        .RegWriteData_wb(RegWriteData_wb));
    
endmodule
