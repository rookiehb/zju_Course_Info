        .ORIG   x3000
        ;clear register
        AND R0,R0,#0
        AND R1,R1,#0
        AND R2,R2,#0
        AND R3,R3,#0
        AND R4,R4,#0
        AND R5,R5,#0
        LD R1,Name      ;r1<-x3100 
        LEA R0,Prompt   ;get the first address of prompt and make R0 equal to it
        trap x22 ; puts the " enter a name: "
        
LOOP1   trap x20  ; get a ascii into R0
        trap x21  ; put the ascii
        STR R0,R1,#0    ;put r0 into the address of users' name    
        ADD R1,R1,#1     
        LD  R2,Enter    
        ADD R2,R0,R2    ;if ascii is x000A , then finish the inputs
        BRz Process     
        BRnzp LOOP1

Process LD R0,Name      ; this function is to eliminate the space in front of the name
        ADD R0,R0,#-1   
Del_S   ADD R0,R0,#1
        LDR R2,R0,#0
        LD R1,Space    
        ADD R1,R2,R1    
        BRz Del_S       ; if the character is " ",then continue to eliminate
        ST R0,Name      ; update the new beginning of the string of users' name
        ADD R0,R0,#0    
        BRnzp COMPARE

COMPARE LD R0,PTR     ;  r1<-x4000    make r0 equal to the head
LOOP2   LDR R0,R0,#0  ; node of link list   ;make r0 go to the next node
        ADD R0,R0,#0  ; jugde the node whether comes to an end
        BRz Break
        
        ST  R0,SaveR0  ; store the r0
        LDR R1,R0,#2   ; make r1 point to the first name
        LD  R2,Name    ; make r2 point to the users' name
        BRnzp JUDGE_F  

NEXT_0  LD R0,SaveR0
        LDR R1,R0,#3  ; make r1 point to the last name
        LD  R2,Name   
        BRnzp JUDGE_L

NEXT_1  LD R0,SaveR0
        ADD R5,R5,#0
        BRp Output    ; if r5 is positive ,then we should output the information of this guy

NEXT_2  AND R5,R5,#0  ; initialize the flag r5
        BRnzp LOOP2

JUDGE_F LDR R3,R1,#0    ;R3 is the character of the first name
        LDR R4,R2,#0    ;R4 is the character of the users' name
        
        LD  R0,Space    ;check whether r4 is equal to " "
        ADD R0,R4,R0
        BRz judge_0     ;if r4 is " ",then we should check whether the first name comes to an end
        
        LD  R0,Enter    
        ADD R0,R4,R0    ;check whether r4 is equal to "\n"
        BRz judge_0     ;if r4 is "\n",then we should check whether the first name comes to an end
        
        NOT R3,R3
        ADD R3,R3,#1
        ADD R4,R3,R4
        BRnp NEXT_0     ;check whether r3 equals to r4
        
        ADD R1,R1,#1    ;move on to next character 
        ADD R2,R2,#1    
        BRnzp JUDGE_F

JUDGE_L LDR R3,R1,#0
        LDR R4,R2,#0
        
        LD  R0,Space
        ADD R0,R4,R0
        BRz judge_0
        
        LD  R0,Enter
        ADD R0,R4,R0
        BRz judge_0
        
        NOT R3,R3
        ADD R3,R3,#1
        ADD R4,R3,R4
        BRnp NEXT_1 
        
        ADD R1,R1,#1
        ADD R2,R2,#1 
        BRnzp JUDGE_L

judge_0 ADD R3,R3,#0  ;check whether name comes to an end 
        BRz change_R5 
        BRnzp NEXT_1  

change_R5   ADD R5,R5,#1  ; yes,then we make flag r5 equals to 1
            BRnzp NEXT_1

Output  ST R0,SaveR0   ; output the first name
        LDR R0,R0,#2
        trap x22
        LEA R0,SPACE_OUTPUT
        trap x22
        LD R0,SaveR0
        
        ST R0,SaveR0  ; output the last name
        LDR R0,R0,#3
        trap x22
        LEA R0,SPACE_OUTPUT
        trap x22
        LD R0,SaveR0
        
        ST R0,SaveR0   ; output the room number
        LDR R0,R0,#1
        trap x22
        LEA R0,SPACE_OUTPUT
        trap x22
        LD R0,SaveR0
        
        ST R0,SaveR0   ; output the Enter
        LEA R0,Save_Enter
        trap x22
        LD R0,SaveR0
        
        AND R1,R1,#0   ;use r1 temporarily to store the information whether there is corresponded answer 
        ADD R1,R1,#1    
        ST R1,SaveR1  ;if r1 is 1 ,then there is no need to output "Not Found"
        
        BRnzp NEXT_2

Break   LD R1,SaveR1
        ADD R1,R1,#0
        BRp EOF       
        
        LEA R0,Not_F   ; if r1 equals to 0 ,then output "Not found"
        trap x22

EOF     Halt


Prompt  .STRINGZ "Enter a name: "
Not_F   .STRINGZ "Not found"
SPACE_OUTPUT   .STRINGZ " "
Save_Enter .STRINGZ "\n"
Name    .FILL x3100
Space   .FILL xFFE0  ;NOT SPACE
Enter   .FILL xFFF6  ;NOT ENTER
PTR     .FILL x4000  ;the beginning of the link list
SaveR0  .BLKW 1
SaveR1  .BLKW 1

           
        .END