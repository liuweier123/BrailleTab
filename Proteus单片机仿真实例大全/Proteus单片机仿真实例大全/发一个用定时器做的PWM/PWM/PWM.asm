ADC		EQU		35H
PWMH    EQU     37H
PWML    EQU     36H
CLOCK	BIT		P2.4			;����ADC0808ʱ��λ
ST 		BIT 	P2.5
EOC 	BIT 	P2.6
OE 		BIT 	P2.7
PWM		BIT		P3.7
		ORG 	00H
		SJMP	START
		ORG		0BH
		LJMP	INT_T0

START:	MOV		TMOD,#02H	  	;
		MOV		TH0,#0FFH
		MOV		TL0,#00H
		MOV		IE,#82H
		SETB	TR0

WAIT: 	CLR 	ST			  	
		SETB 	ST
		CLR 	ST				;����ADת��
 		JNB 	EOC,$			;�ȴ�ת������
		SETB 	OE 
		MOV 	ADC,P1			;��ȡADת�����
		CLR 	OE
		MOV 	A,ADC
		MOV     PWML,A
		CPL     A
		ADD     A,#1
		MOV     PWMH,A
        SJMP 	WAIT
INT_T0:	JNB     PWM,SGAO       ;PWM���Ǹ߾��������
        CLR     PWM			   ;PWM���
		MOV     TH0,PWML
		MOV     TL0,PWML
        RETI
SGAO:   SETB    PWM
		MOV     TH0,PWMH
		MOV     TL0,PWMH
        RETI
DELAY:	MOV		R6,#1
D1:		DJNZ	R6,D1
		DJNZ	ACC,D1
		RET

		END