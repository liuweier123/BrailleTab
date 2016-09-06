		ORG		00H
		JMP		MAIN
		ORG   	0BH
		LJMP	INTS_T0
		ORG		30H
MAIN:	CLR		EA
		MOV		R2,#0
		MOV		R1,#16			;16���ַ�
		MOV		R0,#40H
		MOV		DPTR,#TAB		;��ȫ���ַ����Ƶ�40H
MOVEDATA:
		MOV		A,R2
		MOVC	A,@A+DPTR
		MOV		@R0,A
		INC		R2
		INC		R0
		DJNZ	R1,MOVEDATA
		MOV		TMOD,#01H		;��ʱ��0������ʽ1
		MOV		TL0,#0FFH		;�ü�����ֵ
		MOV		TH0,#03CH		;0FFFFH-3CAFH=50000,50MS
		MOV		R7,#5			;�����������ѭ��5��
		SETB	ET0				;����T0�ж�
		CLR		ET1				;��ֹT1�ж�
		SETB	EA
		SETB	TR0 
		MOV		SCON,#00H		;���пڹ���ģʽ0
		CLR		P3.2
		MOV		SP,#60H
		MOV		R3,#080H		;��һ��
A0:		MOV		R2,#08H
		MOV		R0,#40H
LOOP:	MOV		DPTR,#TAB		;�ַ��׵�ַ
		MOV		R1,#2
		MOV		A,R3
		RR		A				;��������һλת��һ��
		MOV		R3,A
		MOV		SBUF,A			;��������
WAIT1: 	JNB		TI,WAIT1		;�ȴ�һ֡������
		CLR		TI
A1:		MOV		A,@R0
		MOV		SBUF,A
WAIT2:	JNB		TI,WAIT2
		CLR		TI
		INC		R0
		DJNZ	R1,A1
		SETB	P3.2			;��ʾһ��
		CLR		P3.2
		DJNZ	R2,LOOP			;��һ��
		JMP		A0
		JMP		$
INTS_T0:
		CLR	EA
		PUSH	00H
		PUSH	01H
		PUSH	02H
		DJNZ	R7,BACK			;��������������������� 
		MOV		R7,#5
		MOV		R0,#40H
		MOV		R1,#8
SHIFT1:
		MOV		R2,#2
		CLR		C
		PUSH	00H
		MOV		A,R0
		ADD		A,#1
		MOV		R0,A
		MOV		A,@R0
		POP		00H
		RLC		A
SHIFT2:
		MOV		A,@R0
		RLC		A
		MOV		@R0,A
		INC		R0
		DJNZ	R2,SHIFT2
		DJNZ	R1,SHIFT1
BACK:	POP		02H
		POP		01H
		POP		00H
		MOV		TMOD,#01H		;��ʱ��0������ʽ1
		MOV		TL0,#0FFH               
		MOV		TH0,#03CH		;0FFFFH-3CAFH=50000��50MS
		SETB	ET0				;��ֹT0�ж�
		CLR		ET1				;��ֹT1�ж�
		SETB	EA
		SETB	TR0
		RETI
TAB:	DB		0FFH,0FFH		;��ͷ����				
		DB		0DFH,0FFH
		DB		0BFH,0FFH														
		DB		001H,0FFH
		DB		0BFH,0FFH
		DB		0DFH,0FFH
		DB		0FFH,0FFH
		END
