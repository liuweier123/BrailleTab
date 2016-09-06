PL     	BIT    	P1.0
		ORG   	00H
START:	CLR	PL
		SETB	PL			 	;发送移位脉冲
		MOV   	SCON,#10H		;允许串行口接收数据
WAIT: 	JNB    	RI,WAIT
		MOV    	A,SBUF   		;读取数据
		CLR    	RI				;清除接收中断标志
		MOV   	P0,A			;接收到的数据送P0口显示
		ACALL  	DELAY
		SJMP    START
DELAY:  MOV   	R4,#0FFH
AA1:	MOV   	R5,#0FFH
AA:		NOP
    	NOP   
		DJNZ    R5,AA
		DJNZ    R4,AA1
		RET
		END