		ORG 0
START:		MOV R1,#00H		//��ʼ��R7Ϊ0����ʾ��0��ʼ����
		MOV A,R1		//
		CPL A			//ȡ��ָ��
		MOV P1,A		//�ͳ�P1�˿��ɷ����������ʾ
REL:		JNB P3.7,REL		//�ж�SP1�Ƿ���
		LCALL DELAY10MS		//�����£�����ʱ10ms����
		JNB P3.7,REL		//���ж�SP1�Ƿ���ð���
		INC R7			//����ð��£�����а�������ʹ
		MOV A,R7		//�������ݼ�1�����ͳ�P1�˿���
		CPL A			//�����������ʾ
		MOV P1,A		//
		JNB P3.7,$		//�ȴ�SP1�ͷ�
		SJMP REL		//������K1����ɨ��
DELAY10MS:	MOV R6,#20				//��ʱ10ms�ӳ���
L1:		MOV R7,#248
		DJNZ R7,$
		DJNZ R6,L1
		RET
		END
