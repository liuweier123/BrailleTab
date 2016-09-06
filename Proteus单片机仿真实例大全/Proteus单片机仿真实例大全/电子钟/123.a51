        ORG  0000H

        MOV 30H,#1
        MOV 31H,#2
        MOV 32H,#0
        MOV 33H,#0
        MOV 34H,#0
        MOV 35H,#0

        MOV TMOD,#01
XS0:    SETB TR0
        MOV TH0,#00H
        MOV TL0,#00H

XS:

        MOV 40H,#0FEH
        MOV DPTR,#TAB
        MOV P2,40H
        MOV A,30H
        MOVC A,@A+DPTR
        MOV P0,A
        LCALL YS1MS
        MOV P0,#0FFH
        MOV A,40H
        RL A
        MOV 40H,A


        MOV P2,40H
        MOV A,31H
        ADD A,#10
        MOVC A,@A+DPTR
        MOV P0,A
        LCALL YS1MS
        MOV P0,#0FFH
        MOV A,40H
        RL A
        MOV 40H,A


        MOV P2,40H
        MOV A,32H
        MOVC A,@A+DPTR
        MOV P0,A
        LCALL YS1MS
        MOV P0,#0FFH
        MOV A,40H
        RL A
        MOV 40H,A

        MOV P2,40H
        MOV A,33H
        ADD A,#10
        MOVC A,@A+DPTR
        MOV P0,A
        LCALL YS1MS
        MOV P0,#0FFH
        MOV A,40H
        RL A
        MOV 40H,A

        MOV P2,40H
        MOV A,34H
        MOVC A,@A+DPTR
        MOV P0,A
        LCALL YS1MS
        MOV P0,#0FFH
        MOV A,40H
        RL A
        MOV 40H,A

        MOV P2,40H
        MOV A,35H
        MOVC A,@A+DPTR
        MOV P0,A
        LCALL YS1MS
        MOV P0,#0FFH
        MOV A,40H
        RL A
        MOV 40H,A
     
        JB TF0,JIA
        JNB P1.0,P100
        JNB P1.1,P1000
        JNB P1.2,P10000

        AJMP XS

  

P100:   MOV 30H,#0
        MOV 31H,#0
        MOV 32H,#0
        MOV 33H,#0
        MOV 34H,#0
        MOV 35H,#0


JIA:    CLR TF0

        MOV A,35H
        CJNE A,#9,JIA1
        MOV 35H,0

        MOV A,34H
        CJNE A,#5,JIA10
        MOV 34H,#0

P10000: JNB P1.2,P10000
        MOV A,33H
        CJNE A,#9,JIA100
        MOV 33H,#0

        MOV A,32H
        CJNE A,#5,JIA1000
        MOV 32H,#0


P1000:  JNB P1.1,P1000
        MOV A,31H
        CJNE A,#9,JIA10000        
        MOV 31H,#0
        
        MOV A,30H
        CJNE A,#2,JIA100000        
        MOV 30H,#0
        AJMP XS0




JIA100000:
        INC 30H
        AJMP XS0
JIA10000:
        CJNE A,#3,JIAJIA
        MOV A,30H
        CJNE A,#02,JIAJIA
        MOV 30H,#0
        MOV 31H,#0
        AJMP XS0


JIAJIA:
        INC 31H
        AJMP XS0 
JIA1000:INC 32H
        AJMP XS0
JIA100: INC 33H
        AJMP XS0        
JIA10:  INC 34H
        AJMP XS0
JIA1:   INC 35H
        AJMP XS0



        RET
YS1MS:  MOV R6,#9H
YL1:    MOV R7,#19H
        DJNZ R7,$
        DJNZ R6,YL1
        RET




TAB:
DB      0C0H,0F9H,0A4H,0B0H,099H,092H,082H,0F8H,080H,090H
DB      040H,079H,024H,030H,019H,012H,002H,078H,000H,010H      

        END





















