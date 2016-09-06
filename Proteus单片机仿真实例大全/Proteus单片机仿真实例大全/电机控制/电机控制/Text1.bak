    ;电机的驱动脉冲频率为16.6HZ,周期60MS.定时器时间30MS,初值为8AD0H.
		   HDIAN0      EQU       30H		 ;高电平延迟时间存储单元
		   LDIAN0	   EQU       31H
		   HDIAN1	   EQU       32H		;低电平延迟时间存储单元
		   LDIAN1	   EQU       33H
		   COT0        EQU       34H
		   COT1        EQU       35H
		   WAY         EQU       36H
		   DJ0         EQU       P2.6
		   DJ          EQU       P2.7
		   K1          EQU       P1.0		;启动,停止
		   K2          EQU       P1.1		;加速
		   K3          EQU       P1.2	    ;减速
		   K4          EQU       P1.3       ;方向控制
		 ORG        0000H
		 LJMP       MAIN   
 	     ORG		 0003H
	     LJMP       XINT0
         ORG        000BH
	     LJMP       IN0
		 ORG  	   0100H
MAIN:    MOV      SP,#6FH
;         SETB     F1
         MOV       WAY,#00H
         MOV      COT0,#5
		 MOV      COT1,#5
         MOV      TMOD,#21H
	     MOV      TH0,#8AH		 
   	     MOV      TL0,#0D0H
	     MOV      HDIAN0,#8AH
	     MOV      LDIAN0,#0D0H
		 MOV      HDIAN1,#8AH
		 MOV      LDIAN1,#0D0H
		 MOV      IE,#9FH
         CLR        IT0
		 CLR      EX0
STAR:    JNB      K1,NEXT1
         SJMP     STAR
NEXT1:   LCALL    YAN_1MS
		 JB       K1,STAR
		 SETB     EX0
		 SETB     F0
		 SETB     TR0
	     SJMP     $
XINT0:   CLR      ET0
         JB       K4,K11
		 LCALL    YAN_3MS
		 JB       K4,K11
		 MOV      A,WAY
		 JZ       K41
		 MOV      WAY,#00H
		 SJMP     K11
K41:	 MOV      WAY,#01H
K11:     JB       K1,K21
  		LCALL   YAN_1MS
		LCALL    YAN_1MS
        JB       K1,K21
		 JNB       F0,STAR1
STOP0:   CLR     DJ 
         CLR      F0
		 CLR      TR0
		 SJMP     FANHUI11
STAR1:   SETB     F0
         SETB     TR0
         SJMP     FANHUI
K21:     JB        K2,K33
         LCALL    YAN_3MS
		 JNB      K2,JIASU
K33:     JB        K3, FANHUI
         LCALL    YAN_3MS
		 JB        K3,FANHUI     
JIANSU: ; MOV      A,COT0
;        CJNE      A,#10,JIANSU1
;JIANSU1: JC       JIANSU2
;         SJMP     FANHUI 
;JIANSU2: DEC       COT1
;		 INC       COT0 
         MOV      A,LDIAN0
         CLR       C
         SUBB      A,#200
		 MOV       LDIAN0,A
		 MOV      A,HDIAN0
		 SUBB     A,#00H
		 MOV      HDIAN0,A
;		 CJNE     A,#0CEH,JIANSU3	   ;确保LDIAN较小
;EQQ1:	 SJMP     FANHUI
;JIANSU3: JNC	  EQQ1
         MOV      A,LDIAN1
         ADD      A,#200
		 MOV      LDIAN1,A
		 MOV      A,HDIAN1
		 ADDC     A,#00H
		 MOV      HDIAN1,A
		 SETB     P0.0
		 CLR      P2.0
		 SJMP     FANHUI
JIASU: ;  MOV      A,COT1
;         CJNE     A,#10,JIASU1
;JIASU1:  JC       JIASU2
 ;        SJMP     FANHUI
;JIASU2:  DEC      COT0
 ;        INC      COT1
         MOV      A,LDIAN0
         ADD      A,#200
         MOV      LDIAN0,A
		 MOV      A,HDIAN0
		 ADDC     A,#00H
		 MOV      HDIAN0,A
         MOV      A,LDIAN1
		 CLR       C
		 SUBB     A,#200
		 MOV      LDIAN1,A
		 MOV      A,HDIAN1
		 SUBB     A,#00H
		 MOV      HDIAN1,A	  
		 SETB     P2.0
		 CLR       C
		 MOV      P0.0,C	 
FANHUI:  SETB      ET0
FANHUI11:RETI

		      
IN0:     CLR       EX1					 ;        
         MOV       A,WAY		 		 ;
		 JZ        ZHENGX				 ;
FANX:	 SETB      DJ
          MOV      C,DJ0				   ;
           JC       LD0		             ;判断当前脉冲是高还是低
HD0:      MOV      TL0,LDIAN0            ;下一时刻为高电平
		 MOV      TH0,HDIAN0
	     SETB      DJ0
	     SJMP      FANHUI2
LD0:      MOV      TL0,LDIAN1            ;下一时刻为低电平
         MOV      TH0,HDIAN1
         CLR      DJ0
		 SJMP     FANHUI2			   ;
ZHENGX:  SETB     DJ0
          MOV      C,DJ				   ;
           JC       LD		             ;判断当前脉冲是高还是低
HD:      MOV      TL0,LDIAN0            ;下一时刻为高电平
		 MOV      TH0,HDIAN0
	     SETB      DJ
	     SJMP      FANHUI2
LD:      MOV      TL0,LDIAN1            ;下一时刻为低电平
         MOV      TH0,HDIAN1
         CLR      DJ
FANHUI2: SETB     EX1
         RETI
YAN_1MS:    MOV         R7,#2
DLAY11:     MOV         R6,#250
DLAY12:  	DJNZ        R6,DLAY12
            DJNZ        R7,DLAY11
			RET					   
YAN_3MS:    MOV         R7,#6
DLAY31:     MOV         R6,#250
DLAY32:     DJNZ        R6,DLAY32
            DJNZ        R7,DLAY31
			RET
YAN_6MS:    MOV         R7,#20				;6MS
DLAY61:    	MOV         R6,#150
DLAY62:	    DJNZ        R6,DLAY62
			DJNZ        R7,DLAY61  
            RET  
	     END