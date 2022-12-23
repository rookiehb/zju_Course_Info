//******************************************************************************
// MIPS verilog model
//
// ALU.v
//******************************************************************************

module ALU (
	// Outputs
	   ALUResult,
	// Inputs
	   ALUCode, A, B);
	input [3:0]	ALUCode;				// Operation select
	input [31:0]	A, B;
	output [31:0]	ALUResult;
	
// Decoded ALU operation select (ALUsel) signals
   parameter	 alu_add=  4'b0000;
   parameter	 alu_sub=  4'b0001;
   parameter	 alu_lui=  4'b0010;
   parameter	 alu_and=  4'b0011;
   parameter	 alu_xor=  4'b0100;
   parameter	 alu_or =  4'b0101;
   parameter 	 alu_sll=  4'b0110;
   parameter	 alu_srl=  4'b0111;
   parameter	 alu_sra=  4'b1000;
   parameter	 alu_slt=  4'b1001;
   parameter	 alu_sltu= 4'b1010; 	

    wire Binvert;
    wire [31:0] Binvert_extend;
    
    reg [31:0] B_xor=0;
    reg [31:0] sum=0;
    assign Binvert = ~(ALUCode==0);
    assign Binvert_extend = {32{Binvert}};
    always @(*)
        begin
            B_xor = B^Binvert_extend;
            sum = A+B_xor+Binvert;
        end
    
    reg [31:0] ALUResult_reg=0;
    reg signed[31:0] A_reg=0;
    
    always @(*)
        begin
            A_reg = A;
            case (ALUCode)
                alu_add: ALUResult_reg = sum;
                alu_sub: ALUResult_reg = sum;
                alu_lui: ALUResult_reg = B;
                alu_and: ALUResult_reg = A&B;
                alu_xor: ALUResult_reg = A^B;
                alu_or: ALUResult_reg = A|B;
                alu_sll: ALUResult_reg = A<<B;
                alu_srl: ALUResult_reg = A>>B;
                alu_sra:ALUResult_reg = A_reg>>>B;
                alu_slt: ALUResult_reg = (A[31]&&(~B[31])||(A[31]~^B[31])&&sum[31])?1:0;
                alu_sltu: ALUResult_reg = ((~A[31])&&B[31]||(A[31]~^B[31])&&sum[31])?1:0;
                default: ALUResult_reg = sum;
            endcase
        end
    
    assign ALUResult = ALUResult_reg;
endmodule