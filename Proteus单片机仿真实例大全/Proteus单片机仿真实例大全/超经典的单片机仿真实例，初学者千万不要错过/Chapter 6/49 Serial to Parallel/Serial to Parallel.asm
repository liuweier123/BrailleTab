		ORG   00H
		AJMP	START
START:	MOV   	SCON,#0
		MOV   	30H,#01H	;8�ֽڴ���������
		MOV   	31H,#02H
		MOV   	32H,#04H
		MOV   	33H,#08H
		MOV   	34H,#16
		MOV   	35H,#32
		MOV   	36H,#64
		MOV   	37H,#128
 		MOV   	R0,#30H		;R0������ָ��	   
 		MOV   	R2,#8
LOOP:   MOV   	A,@R0
		MOV   	SBUF,A		;�������뻺��
LO:		JNB    	TI,LO		;��鷢���жϱ�־λ
		CLR    	TI
		ACALL  	DELAY
		INC     R0			;������һ�ֽ�
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