`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:  zju
// Engineer: qmj
//////////////////////////////////////////////////////////////////////////////////
module IF1(clk, reset, Branch, Jump, IFWrite, JumpAddr,Instruction_if,PC,IF_flush);
    input clk;
    input reset;
    input Branch;
    input Jump;
    input IFWrite;
    input [31:0] JumpAddr;
    output [31:0] Instruction_if;
    output [31:0] PC;
    output IF_flush;
    
    reg [31:0] PC_counter=0;
    assign IF_flush=Branch||Jump;
    always @(posedge clk)
        begin
            if (reset)
                PC_counter = 0;
            else if (IFWrite==0)
                PC_counter = PC_counter; 
            else if (IF_flush==1)
                PC_counter = JumpAddr;
            else
                PC_counter=PC_counter+4;
        end
    assign PC = PC_counter;
    InstructionROM insRom(
        .addr(PC[7:2]),
        .dout(Instruction_if)
        );
endmodule
