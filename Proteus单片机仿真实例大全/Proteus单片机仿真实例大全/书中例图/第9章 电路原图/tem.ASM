ORG   0000H
		JMP   START
		ORG   0040H
START:
		LCALL  	ZHUANHUAN
      	SETB   	P3.0
      	SETB   	P3.1
      	SETB   	P3.2
      	SETB   	P2.0
      	SETB   	P2.1
      	SETB   	P2.2
      	LCALL   DELAY1
      	MOV 	34H,#05
      	MOV 	35H,#05
      	MOV 	28H,#05
      	MOV 	29H,#05
LLL:
		LCALL   ZHUANHUAN
     	MOV    	31H,A
     	LCALL   DELAY4
    	LCALL   ZHUANHUAN
    	MOV    	32H,A
     	LCALL   DELAY4
    	LCALL   ZHUANHUAN
     	MOV    	33H,A
     	LCALL   FILTER
     	LCALL   CHNTER
     	LCALL   SHOW
     	JB   	P2.4,KONGZHI1
KEY0: 
      	JB 	P2.4,LLL
      	LCALL   DELAY4
      	LCALL   ZHUANHUAN
      	LCALL   CHNTER
      	LCALL 	SHOW
      	LCALL   DELAY4
KEY1: 
	    JB      P2.5,KEY51
      	LCALL   DELAY4
      	LCALL   ZHUANHUAN
      	LCALL   CHNTER
      	LCALL 	SHOW
      	LCALL   DELAY4
KEY2:
      	JB 	P2.7,KEY3
      	LCALL   DELAY4
      	LCALL   ZHUANHUAN
      	LCALL   CHNTER
      	LCALL 	SHOW
      	LCALL 	SHOW
      	LCALL 	SHOW
      	LCALL 	SHOW
      	LCALL 	SHOW
      	LCALL 	SHOW
      	LCALL   DELAY4
      	LCALL   ZHUANHUAN
      	LCALL   CHNTER
      	LCALL 	SHOW
      	LCALL   DELAY4
      	LCALL   ZHUANHUAN
      	LCALL   CHNTER
      	LCALL 	SHOW
      	DEC 	34H
      	MOV 	A,34H
      	MOV 	35H,34H
      	CJNE 	A,#0FFH,KEY22 
      	MOV 	34H,#05H 
      	LCALL   ZHUANHUAN
      	LCALL   CHNTER
      	LCALL 	SHOW  
      	LCALL   DELAY4
KEY22: 
	    LCALL   ZHUANHUAN
      	LCALL   CHNTER
      	LCALL 	SHOW
      	AJMP 	KEY2
KONGZHI1:
	    LJMP   	KONGZHI
KEY51:
	    LJMP   	KEY5
KEY3: 
      	JB 	P2.6,KEY02
      	LCALL   DELAY4
      	LCALL   ZHUANHUAN
      	LCALL   CHNTER
      	LCALL 	SHOW
      	LCALL 	SHOW
      	LCALL 	SHOW
      	LCALL 	SHOW
      	LCALL 	SHOW
      	LCALL 	SHOW
      	LCALL   DELAY4
      	LCALL   ZHUANHUAN
      	LCALL   CHNTER
      	LCALL 	SHOW
      	LCALL   DELAY4
      	INC 	35H 
      	MOV 	A,35H
      	MOV 	34H,35H
      	LCALL   DELAY4
      	CJNE 	A,#0AH,KEY33
      	LCALL   ZHUANHUAN
      	LCALL   CHNTER
      	LCALL 	SHOW
      	LCALL   DELAY4
     	MOV 	35H,#04
      	LCALL   DELAY4
KEY33: 	
	    LCALL   ZHUANHUAN
      	LCALL   CHNTER
      	LCALL 	SHOW
      	AJMP 	KEY3
KEY02:
	    LJMP  	KEY0
KEY5: 
	    JB 	P2.7,KEY6
      	LCALL   DELAY4
      	LCALL   ZHUANHUAN
      	LCALL   CHNTER
      	LCALL 	SHOW
      	LCALL 	SHOW
      	LCALL 	SHOW
      	LCALL 	SHOW
      	LCALL 	SHOW
      	LCALL 	SHOW
      	LCALL   DELAY4
      	LCALL   ZHUANHUAN
      	LCALL   CHNTER
      	LCALL 	SHOW
      	LCALL   DELAY4
      	LCALL   ZHUANHUAN
      	LCALL   CHNTER
      	LCALL 	SHOW
      	DEC 	28H
     	MOV 	A,28H
      	MOV 	29H,28H
      	CJNE 	A,#0FFH,KEY55 
      	MOV 	28H,#05 
      	LCALL   ZHUANHUAN
      	LCALL   CHNTER
      	LCALL 	SHOW  
      	LCALL   DELAY4
KEY55: 
	    LCALL   ZHUANHUAN
      	LCALL   CHNTER
      	LCALL 	SHOW
      	AJMP 	KEY5
KEY6: 
      	JB 	P2.6,KEY01
      	LCALL   DELAY4
      	LCALL   ZHUANHUAN
      	LCALL   CHNTER
      	LCALL 	SHOW
      	LCALL 	SHOW
      	LCALL 	SHOW
      	LCALL 	SHOW
      	LCALL 	SHOW
      	LCALL 	SHOW
      	LCALL   DELAY4
      	LCALL   ZHUANHUAN
      	LCALL   CHNTER
      	LCALL 	SHOW
      	LCALL   DELAY4
      	LCALL   ZHUANHUAN
      	LCALL   CHNTER
      	LCALL 	SHOW
      	LCALL   DELAY4
      	INC 	29H 
      	MOV 	A,29H
      	MOV 	28H,29H
      	LCALL   DELAY4
      	CJNE 	A,#9,KEY66
      	MOV 	29H,#04
      	LCALL   ZHUANHUAN
      	LCALL   CHNTER
      	LCALL 	SHOW
      	LCALL   DELAY4 
      	LCALL   ZHUANHUAN
      	LCALL   CHNTER
      	LCALL 	SHOW  
      	LCALL   DELAY4  
KEY66: 
	    LCALL   ZHUANHUAN
      	LCALL   CHNTER
      	LCALL 	SHOW
      	AJMP 	KEY6     
KEY01:
	    LJMP    KEY0         
KONGZHI: 
	    LCALL   ZHUANHUAN              
      	LCALL   CHNTER             
      	LCALL   WUCHA
      	MOV     A,2EH               
      	MOV     39H,A
      	LCALL   MULT1
      	LCALL   DELAY1
      	LCALL   DELAY1
      	LCALL   SHOW
      	LCALL   DELAY1
      	LCALL   DELAY1
     	LCALL   ZHUANHUAN              
      	LCALL   FILTER             
      	LCALL   CHNTER             
      	LCALL   WUCHA              
      	MOV     3AH,A
      	MOV     A,39H
      	MOV     B,3AH
      	CLR     C
      	SUBB    A,B
      	MOV     3BH,A
      	LCALL   MULT2    
ZZP:	MOV  	A,37H
    	XRL   	A,#00H
    	JB     	ACC.7,ZZP1
    	LJMP   	ZZP2
ZZP1:	
		MOV  	A,37H
     	CJNE  	A,#0FFH,ZZP3
     	LJMP  	ZZP4
ZZP2:
		MOV   	A,37H
     	CJNE   	A,#03H,ZZP5
     	LJMP   	ZZP6
ZZP3:	
		JC     	ZZP7
     	LJMP   	ZZP37
ZZP4:
		MOV   	A,36H
     	XRL    	A,#00H
 		JB     	ACC.7,ZZP8
		LJMP   	ZZP9
ZZP5:
		JC      ZZP10
     	LJMP   	ZZPP5
ZZPP5:
		MOV   	A,36H
     	XRL    	A,#00H
     	JB     	ACC.7,ZZPP51
     	LJMP   	WU5
ZZPP51:	
		MOV   	A,36H
     	CJNE   	A,#0FEH,ZZPP52
     	LJMP   	WU5
ZZPP52:
		JC   	ZZPP521
		LJMP   	WU5
ZZPP521:
		LJMP   	WU0
ZZP6:
		MOV   	A,36H
		XRL   	A,#00H
		JB     	ACC.7,ZZP11
		LJMP   	WU5
ZZP7:
		MOV   	A,37H
     	CJNE  	A,#0FEH,ZZP12
     	LJMP   	ZZP13
ZZP8:
		MOV   	A,36H
     	CJNE   	A,#0FBH,ZZP14
     	LJMP   	WU4
ZZP9:
		MOV   	A,36H
     	CJNE   	A,#00H,ZZP15
     	LJMP   	WU1
ZZP10:
		MOV   	A,37H
      	CJNE   	A,#02H,ZZP16
      	LJMP   	ZZP17
ZZP11:
		MOV   	A,36H
      	CJNE   	A,#0F8H,ZZP18
      	LJMP   	WU1
ZZP12:
		JC      ZZP19
      	LJMP    ZZP4
ZZP13:
		MOV   	A,36H                                   
      	XRL    	A,#00H
  		JB     	ACC.7,ZZP20
		LJMP   	ZZP21
ZZP14:
		JC      zzp141
      	LJMP    ZZP22
zzp141:
		LJMP   	WU4
ZZP15:
		JC      ZZP151
      	LJMP    WU0
ZZP151:
		LJMP    WU1
ZZP16:
		JC      ZZP23
      	LJMP    ZZP17
ZZP17:	
		MOV   	A,36H
      	XRL    	A,#00H
  		JB    	ACC.7,ZZP24
    	LJMP   	ZZPP17
ZZPP17:
		MOV   	A,36H
      	CJNE   	A,#01H,ZZPP171
      	LJMP   	WU5
ZZPP171:
		JC   	ZZPP1711
		LJMP   	WU5
ZZPP1711:
		LJMP   	WU0
ZZP18:
		JC      ZZP181
      	LJMP    WU0
ZZP181:
		LJMP   	WU1
ZZP19:
		MOV   	A,37H
      	CJNE   	A,#0FDH,ZZP25
      	LJMP   	ZZP26
ZZP20:
		MOV   	A,36H
      	CJNE   	A,#0FBH,ZZP27
      	LJMP   	WU4
ZZP21:	
		MOV   	A,36H
      	CJNE   	A,#00H,ZZP28
      	LJMP   	WU2
ZZP22:
		MOV   	A,36H
      	CJNE   	A,#0FFH,ZZP29
      	LJMP   	WU2
ZZP23:
		MOV   	A,37H
      	CJNE   	A,#01H,ZZP30
      	LJMP   	ZZP31
ZZP24:
		MOV   	A,36H
      	CJNE   	A,#0F7H,ZZP32
      	LJMP   	WU1
ZZP25:
		JC      ZZP33
      	LJMP    ZZP13
ZZP26:
		MOV   	A,36H
      	XRL    	A,#00H
  		JB     	ACC.7,ZZP34
		LJMP   	ZZP35
ZZP27:
		JC      ZZP271
      	LJMP    WU3
ZZP271:
		LJMP    WU4
ZZP28:
		MOV   	A,36H
      	CJNE   	A,#03H,ZZP36
      	LJMP   	WU0
ZZP29:	
		JC      ZZP291
      	LJMP    WU1
ZZP291:
		LJMP   	WU3
ZZP30:
		JNC     ZZP301
      	LJMP    ZZP37
ZZP301:
		LJMP   	ZZP31
ZZP31:
		MOV   	A,36H
      	XRL    	A,#00H
  		JB     	ACC.7,ZZP38
		LJMP   	ZZP39
ZZP32:
		JC      ZZP321
      	LJMP    ZZP40
ZZP321:
		LJMP   	WU2
ZZP33:
		MOV   	A,36H
      	XRL    	A,#00H
      	JB     	ACC.7,ZZP331
      	LJMP   	ZZP41
ZZP331:
		LJMP  	WU4
ZZP34:
		MOV   	A,36H
     	CJNE  	A,#0FDH,ZZP42
      	LJMP   	WU4
ZZP35:
		MOV   	A,36H
      	CJNE   	A,#00H,ZZP43
      	LJMP   	WU2
ZZP36:
		JC      ZZP361
      	LJMP    WU0
ZZP361:
		LJMP    WU1
ZZP37:	
		MOV   	A,36H
      	XRL    	A,#00H
      	JB     	ACC.7,ZZP44
      	LJMP   	ZZP39
ZZP38:
		MOV   	A,36H
      	CJNE   	A,#0FBH,ZZP45
      	LJMP   	WU3
ZZP39:
		MOV   	A,36H
      	CJNE   	A,#03H,ZZPP39
      	LJMP   	WU5
ZZPP39:	
		JC   	ZZP391
		LJMP  	WU5
ZZP391:	
		LJMP   	WU0
ZZP40:	
		MOV   	A,36H
      	CJNE   	A,#0FFH,ZZP46
      	LJMP   	WU0
ZZP41:	
		MOV   	A,36H
		CJNE   	A,#00H,ZZP47
      	LJMP   	WU3
ZZP42:
		JC      ZZP421
      	LJMP    WU3
ZZP421:
		LJMP    WU4
ZZP43:
		MOV   	A,36H
      	CJNE   	A,#05H,ZZP48
      	LJMP   	WU0
ZZP44:	
		MOV   	A,36H
      	CJNE   	A,#0FBH,ZZP49
      	LJMP   	WU4
ZZP45:
		JC      ZZP451
      	LJMP    ZZP50
ZZP451:
		LJMP    WU3
ZZP46:
		JC      ZZP461
      	LJMP    WU0
ZZP461:
		LJMP    WU1
ZZP47:
		MOV   	A,36H
      	CJNE   	A,#00H,ZZP51
      	LJMP	WU3
ZZP48:
		JC      ZZP481
      	LJMP    WU0
ZZP481:
		LJMP    WU1
ZZP49:
		JC      ZZP491
      	LJMP    ZZP52
ZZP491:
		LJMP    WU4
ZZP50:
		MOV   	A,36H
      	CJNE   	A,#0FEH,ZZP53
      	LJMP   	WU1
ZZP51:
		MOV   	A,36H
      	CJNE   	A,#01H,ZZP54
      	LJMP   	WU2
ZZP52:
		MOV   	A,36H
      	CJNE   	A,#0FEH,ZZP55
      	LJMP   	WU2
ZZP53:
		JC      ZZP531
      	LJMP    WU0
ZZP531:
		LJMP    WU2
ZZP54:
		JC      ZZP541
      	LJMP    ZZP56
ZZP541:
		LJMP    WU2
ZZP55:
		JC      ZZP551
      	LCALL	WU1
ZZP551:
		LJMP    WU3
ZZP56:
		MOV   	A,36H
      	CJNE   	A,#05H,ZZP57
      	LJMP   	WU0
ZZP57:
		JC      ZZP571
      	LJMP    WU0
ZZP571:	
		LJMP    WU1
WU0:
		MOV 	TMOD,#01H
    	MOV 	R2,#16
    	SETB  	P3.4
LOOP1:
		MOV 	TH0,#0ECH
      	MOV 	TL0,#78H
      	SETB 	TR0
LOOP2:	JBC 	TF0,LOOP3
      	SJMP 	LOOP2
LOOP3: 	
		DJNZ 	R2,LOOPZ1
       	SETB   	P3.5
       	LJMP   	LLL
LOOPZ1:
		LCALL   ZHUANHUAN
      	LCALL   CHNTER
      	LCALL   SHOW    
		LJMP   	LOOP1
WU1:
		MOV 	TMOD,#11H
    	MOV 	R2,#4
    	MOV 	R6,#12
    	CLR 	P3.4
LOOP11:
		MOV   	TH0,#0ECH
      	MOV   	TL0,#78H
     	SETB    TR0
      	SJMP 	LOOP31     
LOOP21:
		MOV 	TH1,#0ECH
      	MOV 	TL1,#78H
      	SETB 	TR1
      	SJMP 	LOOP41
LOOP31:
		JBC 	TF0,LOOP51
      	SJMP 	LOOP31
LOOP41:
		JBC 	TF1,LOOP61
      	SJMP 	LOOP41     
LOOP51:
		DJNZ 	R2,LOOPZ11
       	SETB  	P3.4
       	SJMP 	LOOP21
LOOPZ11:
		LCALL   ZHUANHUAN
        LCALL   CHNTER
        LCALL   SHOW     
        LJMP   	LOOP11      
LOOP61: 
		DJNZ 	R6,LOOPZ21 
        LJMP   	LLL
LOOPZ21 :
		LCALL   ZHUANHUAN
        LCALL   CHNTER
        LCALL   SHOW
        LJMP    LOOP21
WU2:
		MOV 	TMOD,#11H
   		MOV 	R2,#8
   		MOV 	R6,#8
   		CLR 	P3.4
LOOP12:
		MOV 	TMOD,#11H
      	MOV 	TH0,#0ECH
      	MOV 	TL0,#78H
      	SETB 	TR0
      	SJMP 	LOOP32
LOOP22:	
		MOV 	TMOD,#11H
       	MOV 	TH1,#0ECH
      	MOV 	TL1,#78H
      	SETB 	TR1
      	SJMP 	LOOP42
LOOP32:
		JBC 	TF0,LOOP52
       	SJMP 	LOOP32
LOOP42:
		JBC 	TF1,LOOP62
      	SJMP 	LOOP42
LOOP52: 
		DJNZ 	R2,LOOPZ12
       	SETB  	P3.4
       	SJMP 	LOOP22
LOOPZ12:
		LCALL   ZHUANHUAN
        LCALL   CHNTER
        LCALL   SHOW
       	LJMP    LOOP12
LOOP62:
		DJNZ 	R6,LOOPZ22
       	LJMP   	LLL  
LOOPZ22: 
		LCALL   ZHUANHUAN
        LCALL   CHNTER
        LCALL   SHOW
		LJMP    LOOP22   
WU3:
		MOV 	TMOD,#11H
   		MOV 	R2,#12
   		MOV 	R6,#4
   		CLR 	P3.4
LOOP13:
		MOV 	TH0,#0ECH
      	MOV 	TL0,#78H
      	SETB 	TR0
      	SJMP 	LOOP33
LOOP23:
		MOV 	TH1,#0ECH
      	MOV 	TL1,#78H
      	SETB 	TR1
      	SJMP 	LOOP43
LOOP33:	
		JBC 	TF0,LOOP53
       	SJMP 	LOOP33
LOOP43:
		JBC 	TF1,LOOP63
      	SJMP 	LOOP43
LOOP53: 
		DJNZ 	R2,LOOPZ13
       	SETB  	P3.4
       	SJMP 	LOOP23
LOOPZ13:
		LCALL   ZHUANHUAN
        LCALL   CHNTER
        LCALL   SHOW          
		LJMP   	LOOP13     
LOOP63: 
		DJNZ 	R6,LOOPZ23
        LJMP   	LLL
LOOPZ23:
		LCALL   ZHUANHUAN
        LCALL   CHNTER
        LCALL   SHOW 
		LJMP   	LOOP23     
WU4:
		MOV 	TMOD,#01H
    	MOV 	R2,#16
    	CLR 	P3.4
LOOP14:
		MOV 	TH0,#0ECH
       	MOV 	TL0,#78H
       	SETB 	TR0
LOOP24:
		JBC 	TF0,LOOP34
       	SJMP 	LOOP24
LOOP34:
		DJNZ 	R2,LOOPZ14 
        SETB   	P3.4
        LJMP   	LLL
LOOPZ14:
		LCALL   ZHUANHUAN
        LCALL   CHNTER
        LCALL   SHOW
		LJMP   	LOOP14 
WU5:
		MOV 	TMOD,#01H
    	MOV 	R2,#16
    	CLR  	P3.5
LOOP15:
		MOV 	TH0,#0ECH
      	MOV 	TL0,#78H
      	SETB 	TR0
LOOP25:
		JBC 	TF0,LOOP35
      	SJMP 	LOOP25
LOOP35: 
		DJNZ 	R2,LOOPZ15
       	SETB   	P3.5
       	LJMP   	LLL
LOOPZ15:
		LCALL   ZHUANHUAN
        LCALL   CHNTER
        LCALL   SHOW     
		LJMP   	LOOP15     
SHOW:	
		LCALL	SHIFT
     	MOV   	A,@R1
     	INC   	R1
     	MOV   	DPTR,#TAB
     	MOVC   	A,@A+DPTR
     	MOV    	P1,A
     	SETB   	P3.0
     	LCALL   DELAY3
     	CLR    	P3.0  
     	LCALL   DELAY3

     	MOV   	A,@R1
     	SWAP  	A
     	ANL  	A,#0FH
     	MOVC   	A,@A+DPTR
     	MOV   	P1,A
     	SETB   	P3.1
     	LCALL   DELAY3
     	CLR   	P3.1
    	LCALL   DELAY3

     	MOV  	A,@R1 
     	INC    	R1 
     	ANL   	A,#0FH
     	MOVC   	A,@A+DPTR
     	MOV   	P1,A
     	SETB   	P3.2
     	LCALL   DELAY3
     	CLR  	P3.2
     	LCALL   DELAY3
	
     	MOV   	A,@R1
     	INC    	R1
     	MOVC   	A,@A+DPTR
     	MOV    	P1,A
     	SETB   	P2.3
     	LCALL   DELAY3
     	CLR    	P2.3
     	LCALL   DELAY3

     	MOV   	A,@R1
     	SWAP   	A
     	ANL   	A,#0FH
     	MOVC   	A,@A+DPTR
     	MOV   	P1,A
     	SETB   	P2.1
     	LCALL   DELAY3
     	CLR   	P2.1
     	LCALL   DELAY3

     	MOV  	A,@R1  
     	ANL   	A,#0FH
     	MOVC   	A,@A+DPTR
     	MOV   	P1,A
     	SETB   	P2.2
     	LCALL   DELAY3
     	CLR   	P2.2
     	LCALL   DELAY3
   
      	CLR    P2.4
 		CLR    P2.5
		CLR    P2.6
		CLR    P2.7
    	SETB   P2.4
 		SETB   P2.5
		SETB   P2.6
		SETB   P2.7
     	LCALL   DELAY3
; 数字代码表
TAB:    DB  	3FH,06H,5BH,4FH,66H,6DH,7DH,07H,7FH,6FH
     	RET

SHIFT:
		MOV   	R1,#3DH
      	MOV   	A,25H
      	MOV   	B,#100
      	DIV   	AB
      	MOV   	@R1,A
      	INC   	R1
      	MOV   	A,#10
      	XCH   	A,B
      	DIV   	AB
      	SWAP   	A
      	ADD   	A,B
      	MOV   	@R1,A
      	INC    	R1
      	MOV   	A,28H
      	MOV   	@R1,A
      	INC   	R1
      	MOV   	A,34H
      	MOV   	B,#10
      	DIV   	AB
      	SWAP   	A
      	ADD   	A,B
      	MOV   	@R1,A
      	DEC   	R1
      	DEC   	R1
      	DEC   	R1
      	RET

DELAY1: 
		MOV  	R5,#10
DE11 :  
		MOV  	R4,#80
DE12:   
		DJNZ   	R4,DE12
        DJNZ   	R5,DE11
        RET

DELAY2: 
		MOV	R5,#20
DE21:   
		MOV     R4,#80
DE22:   
		DJNZ   	R4,DE22
        DJNZ  	R5,DE21
        RET

DELAY3: 
		MOV     R5,#30
DE31:   
		MOV     R4,#30
DE32:   
		DJNZ    R4,DE32
        DJNZ    R5,DE31
        RET

DELAY4: 
		MOV     R5,#100
DE41:   
		MOV     R4,#60
DE42:   
		DJNZ   	R4,DE42
        DJNZ  	R5,DE41
        RET

CHNTER: 
		MOV   	21H,#101    
        MOV   	22H,#0
        MOV   	A,@R0
        MOV   	B,21H
        MUL   	AB
        ADD   	A,22H
        MOV   	24H,A
        MOV   	A,B
        ADDC  	A,23H
        MOV   	25H,A
        RET

FILTER: 
		MOV   	A,31H
        CJNE   	A,32H,CMP1
        AJMP   	CMP2
CMP1:
		JNC	CMP2
     	XCH     A,32H
     	XCH     A,31H
CMP2:
		MOV     A,32H
     	CJNE    A,33H,CMP3
     	MOV     38H,A
     	RET
CMP3:
		JC      CMP4
     	MOV     38H,A
     	RET
CMP4: 
		MOV   	A,33H
      	CJNE    A,31H,CMP5
      	MOV     38H,A
      	RET
CMP5:
		JC      CMP6
     	XCH     A,31H
CMP6:
		MOV     38H,A
     	RET

MULT1:
		MOV	A,39H                
      	XRL    	A,#00H
      	JB     	ACC.7,NEGFU1
      	LJMP   	POS1
NEGFU1:
		MOV    	A,39H
      	CPL    	A
      	ADD    	A,#01H
      	MOV    	B,#02H
      	MUL    	AB
      	MOV    	3CH,A
		CPL    	A
      	ADD    	A,#01H
      	MOV    	36H,A
	RET
POS1: 
		MOV    	A,39H
      	MOV    	B,#02H
      	MUL   	AB
      	MOV    	36H,A 
      	RET             

MULT2:
		MOV    	A,3BH                
      	XRL    	A,#00H
      	JB     	ACC.7,NEGFU2
      	LJMP   	POS2
NEGFU2: 
		MOV    	A,3BH
        CPL    	A
        ADD     A,#01H
        MOV     B,#2
        MUL     AB
        MOV     2CH,A
        MOV     A,3BH
        CPL     A
        ADD     A,#01H
        MOV     B,#2
		DIV     AB
		MOV     2DH,A
		MOV     B,2CH
		ADD     A,B  
        MOV     3CH,A
        CPL     A
        ADD     A,#01H
		MOV     37H,A
	RET
POS2: 
		MOV     A,3BH
    	MOV     B,#2
		MUL     AB
		MOV     2CH,A
		MOV     A,3BH
		MOV     B,#2
		DIV     AB
		MOV     2DH,A
		MOV     B,2CH
		ADD     A,B  
		MOV    	37H,A
      	RET

WUCHA:  
		MOV  	A,34H
        MOV     B,#10
        MUL     AB
        MOV     2AH,A
        MOV     B,28H
        ADD     A,B
        MOV     2BH,A
        MOV     A,25H
        MOV     B,2BH
        CLR     C
        SUBB    A,B
        MOV     2EH,A
	RET

ZHUANHUAN:
 		SETB  	P3.3  
 		NOP
 		NOP
 		CLR   	P3.3 		; 将地址传送到ADC
 		NOP
 		NOP
 		SETB  	P2.0 
 		NOP
 		NOP
 		CLR   	P2.0 		; 启动转换
 		NOP
 		NOP
WAIT:
 		JB    	P3.7, MOVD 	; 结束转换
 		AJMP   	WAIT      	; 等待转换结束
MOVD:
 		CLR   	P3.6
 		NOP
 		NOP
 		SETB  	P3.6       	; 在ADC端口输出转换数据
 		NOP
 		NOP
 		MOV   	A,P0	  	; 将ADC中的数据保存到Acc
		MOV   	@R0,A	  	; 将Acc暂存到R0
		CLR   	P3.6	  	; DAC输出浮点数	
 		NOP
 	NOP
 	RET
END