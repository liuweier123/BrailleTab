K1 EQU P2.0
K2 EQU P2.1        
        ORG 0000H
        AJMP MAIN

        ORG 0030H
MAIN:   MOV A,#33H
        SETB P2.6
        SETB P2.7
KEY1:   SETB    K1                    ;将P2.2置1
        JB      K1,  KEY2             ;有键按下P2.2=0
KEY11:  ACALL   DELAY_A                ;延时，防止抖动
        SETB    K1
        JB      K1,  KEY11            ;确认键按下
        ACALL   CLOCKWISE

KEY2:   SETB    K2                    ;将P2.2置1
        JB      K2,  KEY1             ;有键按下P2.2=0
KEY21:  ACALL   DELAY_A                ;延时，防止抖动
        SETB    K2
        JB      K2,  KEY21            ;确认键按下
        ACALL   ANTI_CLOCKWISE
        AJMP    KEY1    

CLOCKWISE:
        RL A
        MOV P3,A
        MOV P0,#0C6H
        ACALL DELAY
        RET
       
ANTI_CLOCKWISE:
        RR A
        MOV P3,A
        MOV P0,#88H
        ACALL DELAY
        RET
       
DELAY:   MOV R6,#20H
DELAY22: MOV R7,#80H
DELAY11: DJNZ R7,DELAY11
         DJNZ R6,DELAY22          
         RET

DELAY_A:MOV  R7,#88H
DELAY1: DJNZ R7,DELAY1
        RET        
        end    