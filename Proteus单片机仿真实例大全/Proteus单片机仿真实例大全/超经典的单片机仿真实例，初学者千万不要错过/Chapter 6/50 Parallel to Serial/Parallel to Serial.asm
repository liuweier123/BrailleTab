PL     	BIT    	P1.0
		ORG   	00H
START:	CLR	PL
		SETB	PL			 	;������λ����
		MOV   	SCON,#10H		;�����пڽ�������
WAIT: 	JNB    	RI,WAIT
		MOV    	A,SBUF   		;��ȡ����
		CLR    	RI				;��������жϱ�־
		MOV   	P0,A			;���յ���������P0����ʾ
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