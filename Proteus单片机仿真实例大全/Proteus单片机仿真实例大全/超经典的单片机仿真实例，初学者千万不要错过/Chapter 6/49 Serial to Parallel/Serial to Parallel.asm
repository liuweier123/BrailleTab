		ORG   00H
		AJMP	START
START:	MOV   	SCON,#0
		MOV   	30H,#01H	;8字节待传输数据
		MOV   	31H,#02H
		MOV   	32H,#04H
		MOV   	33H,#08H
		MOV   	34H,#16
		MOV   	35H,#32
		MOV   	36H,#64
		MOV   	37H,#128
 		MOV   	R0,#30H		;R0作数据指针	   
 		MOV   	R2,#8
LOOP:   MOV   	A,@R0
		MOV   	SBUF,A		;数据送入缓存
LO:		JNB    	TI,LO		;检查发送中断标志位
		CLR    	TI
		ACALL  	DELAY
		INC     R0			;发送下一字节
		DJNZ    R2,LOOP
		SJMP    START
DELAY:  MOV   	R7,#3
DD1:	MOV   	R6,#0FFH
DD2:	MOV   	R5,#0FFH
		DJNZ    R5,$
		DJNZ    R6,DD2
		DJNZ    R7,DD1
		RET
		END