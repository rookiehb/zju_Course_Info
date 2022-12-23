;All rights reserved by LIANG Chen, liangchenwater@outlook.com, Zhejiang University.
;Sample program of recursion: Hanoi Tower.
;For teaching purpose. For students to understand Chapter17 in Introduction to Computing Systems, 3rd edition.
;
;
;
;
;
.ORIG x3000
;initialize sp and control link
LD R6, USER_SP
ADD R5,R6,#0
;R1,R2,R3 are three arguments passed to subroutine MOVE
;use R1 to store the "number" of disks (from 'a' to 'z', i.e. from 1 to 26)
Trap x20
ADD R1,R0,#0
LD R0,a
NOT R0,R0
ADD R0,R0,#1
ADD R0,R0,R1
BRn TERMINATE
LD R0,z
NOT R0,R0
ADD R0,R0,#1
ADD R0,R0,R1
BRp TERMINATE
;move disk(s)from R2 to R3
AND R2,R2,#0
ADD R2,R2,#1
AND R3,R3,#0
ADD R3,R3,#2
;caller passes the arguments to callee(caller saved)
ADD R6,R6,#-3
STR R3,R6,#2
STR R2,R6,#1
STR R1,R6,#0
JSR MOVE
TERMINATE Trap x25
;
;
;
;push control link(callee saved)
MOVE ADD R6,R6,#-1
STR R5,R6,#0
;control link<-sp
ADD R5,R6,#0
;push return address(callee saved)
ADD R6,R6,#-1
STR R7,R6,#0
;callee gets the arguments from caller
LDR R2,R5,#2
LDR R3,R5,#3
LDR R1,R5,#1
;calculations on tmps
ADD R3,R2,R3
ADD R3,R3,#-6
NOT R3,R3
ADD R3,R3,#1
;caller saved tmps
ADD R6,R6,#-1
STR R3,R6,#0
;judge termination condition
ADD R1,R1,#-1
LD R0,a
NOT R0,R0
ADD R0,R0,#2
ADD R0,R0,R1
BRn RETURN
;caller passes the arguments to callee(caller saved)
ADD R6,R6,#-3
STR R3,R6,#2
STR R2,R6,#1
STR R1,R6,#0
JSR MOVE
;pop(actually load) tmps(caller popped) [could that be callee popped?]
LDR R1,R5,#1 
LDR R2,R5,#2
LDR R3,R5,#3
PRINT LD R0,ZERO
ADD R0,R0,R2
Trap x21
LD R0,LINE
Trap x21
ADD R0,R1,#0
Trap x21
LD R0, LINE
Trap x21
LD R0,ZERO
ADD R0,R0,R3
Trap x21
LD R0,ENTER
Trap x21
;calculation on tmps
LDR R2,R5,#-2
ADD R1,R1,#-1
;caller passes the arguments to callee(caller saved)
ADD R6,R6,#-3
STR R3,R6,#2
STR R2,R6,#1
STR R1,R6,#0
JSR MOVE
;pop return address, control link, arguments and tmps(callee popped)
RETURN LDR R7,R5,#-1
LDR R5,R5,#0
ADD R6,R6,#6
RET
;
;
;
USER_SP .FILL XFE00
a .FILL x0061
z .FILL x007A
ZERO .FILL x0030
LINE .FILL x005F
ENTER .FILL x000A
.END