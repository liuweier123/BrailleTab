org 00h ;��ʼ
MOV P1,#00H;������ѹ��0
SETB p2.5;�ص��������ֹ����˲���ѹ�������õ�����
SETB P3.7
SETB P3.6
SETB P3.5
SETB P3.4

start:
V15:;1.5��
LCALL DELAY2;�����I����
MOV P1,#03H;1.5V������
CLR P2.5;�պϼ̵������أ������ѹ
B1:
MOV P0,#01111001B;��ʾ1��С����
SETB P2.6
CLR  P2.7
LCALL delay
MOV P0,#00010010B;��ʾ5
CLR P2.6
SETB P2.7
LCALL delay
JNB P2.4,S1;����Ƿ��·��������
JB P3.6,T;����
JB P3.7,V3;����
JB P3.5,s1;�ػ�
JMP B1
T:LJMP V12;��Ϊ����̫��������ֱ��ת�ƣ�����Ҫ�ó��������
S1:LJMP STOP;��Ϊ����̫��������ֱ��ת�ƣ�����Ҫ�ó��������

V3:;3��
LCALL DELAY2
MOV P1,#1bH;3V������
B2:
MOV P0,#11000000B;��ʾ0
clr P2.6
CLR  P2.7
LCALL delay
MOV P0,#10110000B;��ʾ3
CLR P2.6
SETB P2.7
LCALL delay
JNB P2.4,S2;����Ƿ��·��������
JB P3.5,s2;�ػ�
JB P3.6,V15;��
JB P3.7,V42;��
JMP B2
S2:LJMP STOP


V42:;4.2��
LCALL DELAY2
MOV P1,#2FH;4.2V������
B3:
MOV P0,#00011001B;��ʾ4��С����
SETB P2.6
CLR  P2.7
LCALL delay
MOV P0,#00100100B;��ʾ2
CLR P2.6
SETB P2.7
LCALL delay
JNB P2.4,S3;����Ƿ��·��������
JB P3.5,s3;�ػ�
JB P3.6,V3;��
JB P3.7,V5;��
JMP B3
S3:LJMP STOP


V5:;5��
LCALL DELAY2
MOV P1,#3FH;5V������
B4:
MOV P0,#11000000B;��ʾ0
clr P2.6
CLR  P2.7
LCALL delay
MOV P0,#10010010B;5
CLR P2.6
SETB P2.7
LCALL delay
JNB P2.4,S4;����Ƿ��·
JB P3.5,s4;�ػ�
JB P3.6,V42;��
JB P3.7,V6;��
JMP B4
S4:LJMP STOP


V6:;6��
LCALL DELAY2
MOV P1,#4EH;6V������
B5:
MOV P0,#11000000B;��ʾ0
clr P2.6
CLR  P2.7
LCALL delay
MOV P0,#10000010B;��ʾ6
CLR P2.6
SETB P2.7
LCALL delay
JNB P2.4,S5;����Ƿ��·
JB P3.5,S5;�ػ�
JB P3.6,V5;��
JB P3.7,V84;��
JMP B5
S5:LJMP STOP

V84:;8.4��
LCALL DELAY2
MOV P1,#78H;8.4V������
B6:
MOV P0,#00000000B;��ʾ8
SETB P2.6
CLR  P2.7
LCALL delay
MOV P0,#00011001B;��ʾ4
CLR P2.6
SETB P2.7
LCALL delay
JNB P2.4,STOP;����Ƿ��·
JB P3.5,STOP;�ػ�
JB P3.6,V6;��
JB P3.7,V12;��
JMP B6

V12:;12��
LCALL DELAY2
MOV P1,#0B4H;12V������
B7:
MOV P0,#11111001B;��ʾ1
SETB P2.6
CLR  P2.7
LCALL delay
MOV P0,#10100100B;��ʾ2
CLR P2.6
SETB P2.7
LCALL delay
JNB P2.4,STOP;����Ƿ��·
JB P3.5,STOP;�ػ�
JB P3.6,V84;��
JB P3.7,T2;��
JMP B7
T2:JMP V15

STOP:;�ػ�
LCALL DELAY2
MOV P1,#00H;��LM317��ѹ���
STOP2:
SETB P2.5;�ر����
MOV P0,#11000000B;��ʾO
SETB P2.6
CLR  P2.7
LCALL delay
MOV P0,#10001110B;��ʾF
SETB P2.7
CLR  P2.6
LCALL delay
JB P3.5,ST;�ٴο���
jb p3.6,st;�ٴο���
jb p3.7,st;�ٴο���
JMP STOP2
ST:LJMP V15


delay: MOV R2,#5;��ʱ�ӳ���
L1001:  mov R3,#250
       DJNZ R3,$
       DJNZ R2, L1001
       ret

DELAY2:;��ʱ�ӳ���
MOV R6,#3
D2:MOV R4,#200 
D3:MOV R5,#248
       DJNZ R5,$
       DJNZ R4,D3
       djnz r6,d2
       RET

end 