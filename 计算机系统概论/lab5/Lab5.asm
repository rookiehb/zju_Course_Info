        .ORIG X3000
        ;R3 is current address, R4 is data of current address， R1 is a universal register， R6 is stack pointer，R7 is program counter, R2 is current length  
        JSR INITIAL         ;initial all the register 
 LOOP_ADD    ADD R3,R3,#1   ;current starting address
             LDR R4,R3,#0   ;data of current starting address
             BRz BREAK_ADD  ;if data is 0 ,then go to BREAK_ADD
             ADD R0,R3,#0   ;R0 is next address
             JSR DFS        ;start recursion
             JSR INI_ADD    ;reinitial data
             BRnzp LOOP_ADD 
 BREAK_ADD   LD  R2,SaveR2   ;load the biggest length into R2 
        HALT

DFS     ADD R6,R6,#-3       ;push R4,R3,R7 into stack    
        STR R4,R6,#2        
        STR R3,R6,#1        
        STR R7,R6,#0        
        
        ADD R3,R0,#0        ;move R3 to next address
        LDR R4,R0,#0        ;load data of next address
        
CHECK_NORTH JSR CHECK_NORTH_FRAME       ;check whether there is frame in the north    
            BRz CHECK_EAST              ;if there is frame in the north ,then go to CHECK_EAST
            JSR CHECK_GO                ;if there isn't frame in the north ,then we check data of R0 and data of R3
            ADD R1,R1,#0                    
            BRnz CHECK_EAST             ;if R0_data > R3_data ,then we go to CHECK_EAST
            ADD R2,R2,#1                ;current length++;
            JSR CHECK_BIG               ;update the biggest length
            JSR BREAD                   ;leave breadcrump in current address 
            JSR DFS                     
            JSR FLIP_BREADCRUMP         ;clear breadcrump in current address
            ADD R2,R2,#-1               ;current length--;
                
CHECK_EAST  JSR CHECK_EAST_FRAME
            ADD R1,R1,#0
            BRp CHECK_SOUTH
            JSR CHECK_GO
            ADD R1,R1,#0
            BRnz CHECK_SOUTH
            ADD R2,R2,#1
            JSR CHECK_BIG
            JSR BREAD
            JSR DFS
            JSR FLIP_BREADCRUMP
            ADD R2,R2,#-1

CHECK_SOUTH JSR CHECK_SOUTH_FRAME
            BRz CHECK_WEST
            JSR CHECK_GO
            ADD R1,R1,#0
            BRnz CHECK_WEST
            ADD R2,R2,#1
            JSR CHECK_BIG
            JSR BREAD
            JSR DFS
            JSR FLIP_BREADCRUMP
            ADD R2,R2,#-1

CHECK_WEST  JSR CHECK_WEST_FRAME
            ADD R1,R1,#0
            BRz RESTORE              ;if there is frame in west, then we go to RESTORE
            JSR CHECK_GO
            ADD R1,R1,#0
            BRnz RESTORE
            ADD R2,R2,#1
            JSR CHECK_BIG
            JSR BREAD
            JSR DFS
            JSR FLIP_BREADCRUMP
            ADD R2,R2,#-1               
                
RESTORE     ADD R0,R3,#0            ;attempt fail,then make next address equal to current address    
            LDR R7,R6,#0            ;pop R7,R3,R4
            ADD R6,R6,#1
            LDR R3,R6,#0
            ADD R6,R6,#1
            LDR R4,R6,#0
            ADD R6,R6,#1
            RET

;BREAD is a flag, which represent whether this place is visited or not.
BREAD           LD  R1,BREADCRUMB   
                ADD R4,R4,R1        
                STR R4,R3,#0
                RET
;when we is backtracking, we should clear the flag
FLIP_BREADCRUMP LD  R1,FLIP_BREAD   
                ADD R4,R4,R1
                STR R4,R3,#0
                RET
;compare data in R0 and data in R3
CHECK_GO        ADD R6,R6,#-1       
                STR R2,R6,#0
                
                LDR R1,R0,#0
                LDR R2,R3,#0
                NOT R1,R1
                ADD R1,R1,#1
                ADD R1,R1,R2
                 
                LDR R2,R6,#0
                ADD R6,R6,#1
                RET

CHECK_NORTH_FRAME   LD  R1,FLIP_LENGTH          ;
                    ADD R0,R0,R1
                    LDR R1,R0,#0                
                    RET
                    
CHECK_EAST_FRAME    LD  R1,LENGTH
                    ADD R0,R0,R1
                    ADD R6,R6,#-4
                    STR R0,R6,#3
                    STR R2,R6,#2
                    STR R3,R6,#1
                    STR R4,R6,#0
                    
                    LD  R0,FLIP_LENGTH
                    LD  R1,WIDTH
                    LD  R2,DATA_ADDRESS
                    ADD R2,R2,#-1
                    NOT R2,R2
                    ADD R2,R2,#1
                    
LOOP_EAST           ADD R3,R3,R0                    
                    ADD R4,R3,R2
                    BRnz BREAK_EAST
                    BRnzp  LOOP_EAST

BREAK_EAST          AND R1,R1,#0          
                    ADD R4,R4,#0
                    BRn #1                      ;R0是0表示并不是边界
                    ADD R1,R1,#1
                    
                    LDR R4,R6,#0
                    LDR R3,R6,#1
                    LDR R2,R6,#2
                    LDR R0,R6,#3
                    ADD R6,R6,#4
                    
                    ADD R0,R0,#1
                    RET

CHECK_SOUTH_FRAME   ADD R0,R0,#-1
                    LD  R1,LENGTH
                    ADD R0,R1,R0
                    LDR R1,R0,#0
                    RET
                    
CHECK_WEST_FRAME    LD  R1,FLIP_LENGTH
                    ADD R0,R0,R1
                    ADD R6,R6,#-4
                    STR R0,R6,#3
                    STR R2,R6,#2
                    STR R3,R6,#1
                    STR R4,R6,#0
                    
                    LD  R0,TOTAL
                    LD  R2,DATA_ADDRESS
                    ADD R2,R2,R0
                    NOT R2,R2
                    ADD R2,R2,#1            
                    LD  R0,LENGTH
                                
LOOP_WEST           ADD R3,R3,R0                                
                    ADD R4,R3,R2
                    BRzp BREAK_WEST
                    BRnzp LOOP_WEST

BREAK_WEST          AND R1,R1,#0
                    ADD R4,R4,#0
                    BRz #1
                    ADD R1,R1,#1
                    
                    LDR R4,R6,#0
                    LDR R3,R6,#1
                    LDR R2,R6,#2
                    LDR R0,R6,#3
                    ADD R6,R6,#4
                    
                    ADD R0,R0,#-1
                    RET

INITIAL AND R0,R0,#0
        AND R4,R4,#0
        LD  R6,SP
        LD  R3,DATA_ADDRESS
        LDR R1,R3,#-2
        LDR R2,R3,#-1
        ST  R1,WIDTH
        ST  R2,LENGTH
        STR R0,R3,#-2
        STR R0,R3,#-1
LOOP_TOTAL  ADD R0,R1,R0
            ADD R2,R2,#-1
            BRp LOOP_TOTAL
        ST  R0,TOTAL
        LD  R2,LENGTH
        NOT R1,R1
        ADD R1,R1,#1
        ST  R1,FLIP_WIDTH
        NOT R2,R2
        ADD R2,R2,#1
        ST  R2,FLIP_LENGTH
        AND R0,R0,#0
        AND R1,R1,#0
        ADD R1,R1,#1
        AND R2,R2,#0
        ADD R2,R2,#1
        
        ADD R3,R3,#-1
        RET

INI_ADD AND R0,R0,#0
        AND R1,R1,#0
        ADD R1,R1,#1
        AND R2,R2,#0
        ADD R2,R2,#1
        LD  R6,SP
        RET

CHECK_BIG   ADD R6,R6,#-1
            STR R1,R6,#0
            LD  R1,SaveR2
            NOT R1,R1
            ADD R1,R1,#1
            ADD R1,R1,R2
            BRnz #1
            ST  R2,SaveR2
            LDR R1,R6,#0
            ADD R6,R6,#1
            RET
            
SaveR2      .FILL   X0001
BREADCRUMB  .FILL   x0100  
FLIP_BREAD  .FILL   XFF00
WIDTH   .BLKW   1
LENGTH  .BLKW   1
FLIP_LENGTH .BLKW   1
FLIP_WIDTH  .BLKW   1
TOTAL   .BLKW   1
DATA_ADDRESS    .FILL   X4002
SP      .FILL   X8000
        .END
       
         
.ORIG X4000
.FILL #1
.FILL #1
.FILL #45
.END