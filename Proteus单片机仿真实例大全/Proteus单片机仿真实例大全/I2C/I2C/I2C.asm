ACK		BIT		10H			;Ӧ���־λ
SLA		DATA	50H			;������ַ��
SUBA	DATA	51H			;�����ӵ�ַ
NUMBYTE	DATA	52H			;��/д�ֽ���
SDA		BIT		P1.5
SCL		BIT		P1.4		;I2C���߶���
MTD		EQU		30H			;�������ݻ������׵�ַ(30H-3FH)
MRD		EQU		40H			;�������ݻ������׵�ַ(40H-4FH)
		AJMP	MAIN
		ORG		80H
;*********************************************************************
;����:IWRNBYTE
;����:������ָ���ӵ�ַдN������
;��ڲ���:������ַ��SLA,�ӵ�ַSUBA,�������ݻ�����MTD,�����ֽ���NUMBYTE
;*********************************************************************
IWRNBYTE:
		MOV		R3,NUMBYTE
		LCALL	START		;��������
		MOV		A,SLA
		LCALL	WRBYTE		;����������ַ��
		LCALL	CACK
		JNB		ACK,RETWRN	;��Ӧ�����˳�
		MOV		A,SUBA		;ָ���ӵ�ַ
		LCALL	WRBYTE
		LCALL	CACK
		MOV		R1,#MTD
WRDA:	MOV		A,@R1
		LCALL	WRBYTE		;��ʼд������
		LCALL	CACK
		JNB		ACK,IWRNBYTE
		INC		R1
		DJNZ	R3,WRDA		;�ж��Ƿ�д��
RETWRN:	LCALL	STOP
		RET
;*********************************************************************
;����:IRDNBYTE
;����:������ָ���ӵ�ַ��ȡN������
;��ڲ���:������ַ��SLA,�ӵ�ַSUBA,�������ݻ�����MRD,�����ֽ���NUMBYTE
;*********************************************************************
IRDNBYTE:
		MOV		R3,NUMBYTE
		LCALL	START
		MOV		A,SLA
		LCALL	WRBYTE		;����������ַ��
		LCALL	CACK
		JNB		ACK,RETRDN
		MOV		A,SUBA		;ָ���ӵ�ַ
		LCALL	WRBYTE
		LCALL	CACK
		LCALL	START		;������������
		MOV		A,SLA
		INC		A			;׼�����ж�����
		LCALL	WRBYTE
		LCALL	CACK
		JNB		ACK,IRDNBYTE
		MOV		R1,#MRD
RON1:	LCALL	RDBYTE		;��������ʼ
		MOV		@R1,A
		DJNZ	R3,SACK
		LCALL	MNACK		;���һ�ֽڷ���Ӧ��λ
RETRDN:	LCALL	STOP
		RET
SACK:	LCALL	MACK
		INC		R1
		SJMP	RON1	
;*********************************************************************
;����:STRRT
;����:����I2C�����ӳ��򡪷���I2C������ʼ����
;*********************************************************************
START:	SETB	SDA			;������ʼ���������ź�
		NOP					;��ʼ��������ʱ�����4.7us
   		SETB	SCL			;������ʼ������ʱ���ź�
		NOP
		NOP
		NOP
		NOP
		NOP					;��ʼ��������ʱ�����4.7us
   		CLR  	SDA			;������ʼ�ź�
		NOP
		NOP
		NOP
		NOP					;��ʼ��������ʱ�����4.7us
   		CLR		SCL			;ǯסI2C����,׼�����ͻ��������
   		NOP
   		RET
;*********************************************************************
;����:STOP
;����:ֹͣI2C�����ӳ��򡪷���I2C����ֹͣ����
;*********************************************************************
STOP:	CLR  	SDA 		;����ֹͣ�����������ź�
		NOP			   	
		NOP
		SETB  	SCL 		;����ֹͣ������ʱ���ź�
		NOP
		NOP
		NOP
		NOP
		NOP					;��ʼ��������ʱ�����4.7us
		SETB 	SDA 		;����I2C����ֹͣ�ź�
		NOP
		NOP
		NOP
		NOP
		NOP					;�ӳ�ʱ�����4.7us
		RET
;*********************************************************************
;����:MACK
;����:����Ӧ���ź��ӳ���
;*********************************************************************
MACK:	CLR		SDA			;��SDA��0
		NOP
		NOP
		SETB	SCL
		NOP
		NOP
		NOP
		NOP
		NOP					;��������ʱ��,����4.7us
		CLR		SCL
		NOP
		NOP
		RET
;*********************************************************************
;����:MNACK
;����:���ͷ�Ӧ���ź��ӳ���
;*********************************************************************
MNACK:	SETB	SDA			;��SDA��1
		NOP
		NOP
		SETB	SCL
		NOP
		NOP
		NOP
		NOP
		NOP
		CLR		SCL			;��������ʱ��,����4.7us
		NOP
		NOP
		RET
;*********************************************************************
;����:CACK
;����:���Ӧ��λ�ӳ���,����ֵ:ACK=1ʱ��ʾ��Ӧ��
;*********************************************************************
CACK:	SETB	SDA
		NOP
		NOP
		SETB	SCL
		CLR		ACK
		NOP
		NOP
		MOV		C,SDA
		JC		CEND
		SETB	ACK			;�ж�Ӧ��λ
CEND:	NOP
		CLR		SCL
		NOP
		RET
;*********************************************************************	
;����:WRBYTE
;����:�����ֽ��ӳ���,�ֽ����ݷ���ACC
;*********************************************************************
WRBYTE:	MOV		R0,#08H
WLP:	RLC		A			;ȡ����λ
		JC		WRI
		SJMP	WRO			;�ж�����λ
WLP1:	DJNZ	R0,WLP
		NOP
		RET
WRI:	SETB	SDA			;����1
		NOP
		SETB	SCL
		NOP
		NOP
		NOP
		NOP
		NOP
		CLR		SCL
		SJMP	WLP1
WRO:	CLR		SDA			;����0
		NOP
		SETB	SCL
		NOP
		NOP
		NOP
		NOP
		NOP
		CLR		SCL
		SJMP	WLP1
;*********************************************************************
;����:RDBYTE
;����:��ȡ�ֽ��ӳ���,���������ݴ����ACC
;*********************************************************************
RDBYTE:	MOV		R0,#08H
RLP:	SETB	SDA
		NOP
		SETB	SCL			;ʱ����Ϊ��,��������λ
		NOP
		NOP
		MOV		C,SDA		;��ȡ����λ
		MOV		A,R2
		CLR		SCL			;��SCL����,ʱ�����4.7us
		RLC		A			;��������λ�Ĵ���
		MOV		R2,A
		NOP
		NOP
		NOP
		DJNZ	R0,RLP		;δ��8λ,��������
		RET
MAIN:	MOV		R4,#0F0H	;��ʱ,�ȴ�����оƬ��λ���
		DJNZ	R4,$
;�������ݻ�������ʼ��,��16�������ֽڷֱ�ֵΪ00H��0FH		
		MOV		A,#0
		MOV		R0,#30H
S1:		MOV		@R0,A
		INC		R0
		INC		A
		CJNE	R0,#40H,S1
;��24C01C��д����,���ݴ����24C01C��30H��ʼ��16���ֽ���
		MOV		SLA,#0A0H	;24C01C��ַ��,д����
		MOV		SUBA,#30H	;Ŀ���ַ
		MOV		NUMBYTE,#16	;�ֽ���
		LCALL	IWRNBYTE	;д����
DELAY:	MOV		R5,#20
D1:		MOV		R6,#248
D2:		MOV		R7,#248
		DJNZ	R7,$
		DJNZ	R6,D2
		DJNZ	R5,D1
;��24C01C�ж�����,������AT89C51��40H��ʼ��16���ֽ���
		MOV		SLA,#0A0H	;24C01C��ַ��,αд�����
		MOV		SUBA,#30H	;Ŀ���ַ
		MOV		NUMBYTE,#16	;�ֽ���
		LCALL	IRDNBYTE	;д����
		END