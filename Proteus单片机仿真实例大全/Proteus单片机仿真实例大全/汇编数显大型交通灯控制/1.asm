;------------------------------------
;����ʵ�ֹ���
;���ϱ�·��ֱ����ת�佻��ͨ�У��������ʾֱ��ͨ�е���ʱ�����̻Ƶ���ʾ�������е����ڵĵ�·��ͨ״̬��
;ĳһ�����·ӵ��ʱ�������˹����Ƶ��ڶ����ϱ�����ͨ��ʱ�䡣
;�������ʱ����·�ڽ�ͨ����ʾ��ƣ�����ܱ������ݲ��䡣


;�����Ĵ������洢��Ԫ����
;1.�����Ĵ���
;R2����Ϊ��ʱ����ʱ�жϴ���,R6��R7������ʱ�����еļĴ���

;2.Ƭ�ڴ洢��Ԫ
;30H��31H��Ϊ�����������ʾ���ݴ洢��Ԫ;32H��33H��Ϊ��ͨ�Ƴ�ʼ״̬�洢��Ԫ;40H��41H��Ϊ��ͨ����ʾ���ݴ洢��Ԫ

;3.��־λ
;00H���ϱ�ͨ�б�־λ ; 01H������ͨ�б�־λ;02H�������¼���־λ   
;-----------------------------------
SNF   EQU  00H             ;;;�ϱ�ͨ�б�־λ
EWF   EQU  01H             ;;;����ͨ�б�־λ
URF   EQU  02H             ;;;�����¼���־λ
ORG   0000H
LJMP  MAIN                 ;;;�ϵ�ת������
ORG   000BH                ;;;��ʱ�ж����
LJMP  DSZD                    
ORG   0003H                ;;;�����ж����
LJMP  URZD
ORG   0030H   
MAIN: LCALL INIT           ;;;���ó�ʼ���ӳ���
LOOP: LCALL DIS            ;;;ѭ��ִ����ʾ�ӳ���
      AJMP  LOOP
;///////////��ʼ������
INIT: SETB   SNF              
      SETB   EWF           
      SETB   URF           
      MOV   R2,#20         ;;;��ʱ���ж�20��Ϊ1s
      MOV   TMOD,#01H      ;;;��ʼ����ʱ��
      MOV   TL0,#0B0H
      MOV   TH0,#3CH
      SETB  EA             ;;;����ʱ�ж�������ж�
      SETB  ET0
      SETB  TR0
      SETB  EX0
      SETB  IT0            ;;;�����жϳ̿ط�ʽ
      MOV   DPTR,#TAB      ;;;��ֵ�׵�ַ����DPTR��
      MOV   40H,#40        ;;;��������ͨ��ʱ������
      MOV   41H,#40
      MOV   30H,#40        ;;;ͨ��ʱ���ʼ��
      MOV   31H,#60
      MOV   P0,#4CH        ;;;��ʼ��ʱ�ϱ�ͨ�в��ѽ�ͨ��״̬�ֱ����32H��33H��
      MOV   32H,#4CH
      MOV   P2,#15H
      MOV   33H,#15H
      RET
;////////////��ʾ�ӳ���
DIS:  MOV   P3,#0DFH       ;;;ѡ���ϱ������ʮλ�����
      MOV   A,30H          ;;;����ʾ���������������ʾ
      MOV   B,#10
      DIV   AB
      MOVC  A,@A+DPTR
      MOV   P1,A           ;;;
      LCALL D1MS
      MOV   P3,#0EFH       ;;;ѡ���ϱ�����ĸ�λ�����
      MOV   A,B            ;;;�����������ʾ
      MOVC  A,@A+DPTR      
      MOV   P1,A
      LCALL D1MS

      MOV   P3,#7FH        ;;;ѡ�еڶ��������ʮλ�����
      MOV   A,31H          ;;;�����������ʾ
      MOV   B,#10
      DIV   AB
      MOVC  A,@A+DPTR
      MOV   P1,A
      LCALL D1MS
      MOV   P3,#0BFH       ;;;ѡ�еڶ�������ĸ�λ�����
      MOV   A,B
      MOVC  A,@A+DPTR
      MOV   P1,A
      LCALL D1MS
      SETB  P3.0
      SETB  P3.1
      JNB   P3.0,DIS_S     ;;;��ѯ�Ƿ��һ����������
      JNB   P3.1,DIS_E     ;;;��ѯ�Ƿ�ڶ�����������
      AJMP  DIS_R          ;;;û�м������򷵻�
DIS_S:LCALL D5MS           ;;;����ȥ��
      JNB   P3.0,DIS_SN
      AJMP  DIS_R   
DIS_SN:MOV   40H,#50       ;;;��ͨ��ʱ����·��䣬�ϱ�ͨ��ʱ��ӳ�
       MOV   41H,#30
       AJMP  DIS_R
DIS_E:LCALL D5MS           ;;;����ȥ��
      JNB   P3.1,DIS_EW 
      AJMP  DIS_R
DIS_EW:MOV   40H,#30       ;;;����ͨ��ʱ��ӳ�
       MOV   41H,#50
DIS_R:RET                  
;///////��ʱ�жϴ������
DS_C: LJMP  DS_R           ;;;������ת
DSZD: PUSH  ACC            ;;;�����ֳ�
      PUSH  PSW
      CLR   TR0            ;;;�ض�ʱ�����жϱ�־λ�����¸�ֵ
      CLR   TF0
      MOV   TL0,#0B0H
      MOV   TH0,#3CH
      DJNZ  R2,DS_C        ;;;�ж�1mʱ���Ƿ񵽴�
      MOV   R2,#20         ;;;�������¸�ֵ
      DEC   30H            ;;;�ϱ�����ͨ��ʱ���һ
      MOV   A,30H          ;;;�Ѽ�һ���ʱ��������ʾ�洢��Ԫ
;;;;;;;�ϱ�ͨ�е������4��ʱ�Ƶ���˸
DS_10:CJNE  A,#4,DS_11     ;;;���ͨ��ʱ��ʣ��4��
      JNB   SNF,DS_11      ;;;�ж��Ƿ����ϱ�ͨ��
      MOV   P0,#8AH        
      MOV   32H, #8AH      ;;;�ѽ�ͨ��״̬����洢��Ԫ���������ƣ�
DS_11:CJNE  A,#3,DS_12     ;;;����ʣ��3�룬����
      JNB   SNF,DS_12      ;;;�����ϱ�ͨ��ʱ�䣬����
      MOV   P0,#88H
      MOV   32H, #88H
DS_12:CJNE  A,#2,DS_13
      JNB   SNF,DS_13
      MOV   P0,#8AH
      MOV   32H, #8AH 
DS_13:CJNE  A,#1,DS_14
      JNB   SNF,DS_14
      MOV   P0,#88H
      MOV   32H, #88H
;------------------------
DS_14:JNZ   DS_NE          ;;;ͨ��ʱ��û�н���ת��ı䶫������������
      CPL   SNF            ;;;���ͨ��ʱ�������Ա�־λȡ��
      JNB   SNF,DS_1       ;;;�ж��Ƿ��ϱ�ͨ��
      MOV   30H,40H        ;;;�ǣ�������Ӧ�Ľ�ͨ��
      MOV   P0,#4CH
      MOV   32H,#4CH       ;;;�洢��ͨ��״̬
      MOV   P2,#15H
      MOV   33H, #15H      ;;;�洢��ͨ��״̬
DS_NE:DEC   31H            ;;;��������ͨ��ʱ���һ
      MOV   A,31H          ;;;��ͨ��ʣ��ʱ��������ʾ�洢��Ԫ
;;;;;;;;��������ͨ��ʱ��ʣ��4���ӻƵ���˸������ע�����ϱ��������� �ԣ�
DS_20:CJNE  A,#4,DS_21    
      JB    EWF,DS_21
      MOV   P0,#51H
      MOV   32H, #51H
DS_21:CJNE  A,#3,DS_22
      JB    EWF,DS_22
      MOV   P0,#41H
      MOV   32H, #41H
DS_22:CJNE  A,#2,DS_23
      JB    EWF,DS_23
      MOV   P0,#51H
      MOV   32H, #51H
DS_23:CJNE  A,#1,DS_24
      JB    EWF,DS_24
      MOV   P0,#41H
      MOV   32H, #41H
;-----------------------------
DS_24:JNZ   DS_R             ;;;��������ʱ��û�н���������
      CPL   EWF              ;;;��ͨ��״̬ȡ��
      JNB   EWF,DS_2         ;;;��������ͨ��ʱ�䵽������ת
      MOV   31H,#80          ;;;��������ͨ�н�����������ʾʱ��
      MOV   P0,#89H          ;;;������Ӧ�Ľ�ͨ��
      MOV   32H, #89H
      MOV   P2,#29H
      MOV   33H, #29H
      AJMP  DS_R     
DS_1: MOV   30H,#80          ;;;�ϱ�ͨ��ʱ����������¶���ʾ�洢��Ԫ��ֵ     
      MOV   P0,#89H          ;;;ִ��ת��״̬1
      MOV   32H, #89H
      MOV   P2,#26H
      MOV   33H, #26H
      AJMP  DS_NE            
DS_2: MOV   31H,41H         ;;;��������ʼͨ�У���ֵ����ʾ�洢��Ԫ
      MOV   P0,#61H         ;;;������Ӧ�Ľ�ͨ��
      MOV   32H, #61H
      MOV   P2,#15H
      MOV   33H, #15H
DS_R: SETB  TR0 
      POP   PSW             ;;;�ָ��ֳ�
      POP   ACC
      RETI
;/////////////�����жϴ������
URZD: PUSH  ACC             ;;;�����ֳ�
      PUSH  PSW
      CLR   IE0             ;;;����жϱ�־λ
      CLR   TR0             ;;;�ض�ʱ��
      CPL   URF             ;;;�����¼���־λ
      JB    URF,UR_CON      ;;;������������ת
      MOV   P0,#49H         ;;;��·�ڵ�ȫ��ʾ�����
      MOV   P2,#15H
      AJMP  UR_R
UR_CON:SETB  TR0            ;;;�ָ�������ͨ
      MOV   A,32H
      MOV   P0,A
      MOV   A,33H
      MOV   P2,A
UR_R: POP   PSW             ;;;�ָ��ֳ�
      POP   ACC
      RETI      
;////////////���ָ��0,1,2,3,4,5,6,7,8,9
TAB:  DB  3FH,  06H,  5BH,  4FH,  66H,  6DH
      DB  7DH,  07H,  7FH,  6FH

;//////////��ʱ5ms��1ms
D5MS:  MOV    R7,#5
D1MS:  MOV    R7,#10
       MOV    R6,#50 
L1:    DJNZ   R6,$
       DJNZ   R7,L1
       RET
       END

