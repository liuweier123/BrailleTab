;*******************************************************************************
;*�ļ�: 5key_volume_con.asm                                                    *
;*����: ���ܱ�  2006/8/24                                                      *
;*�汾: ver1.0                                                                 *
;*��������: ��ϼ���ģ�������������ʾ                                         *
;*          ������:�������-,�Ҽ�����+                                         *
;*          ������:�������24��,�м�����32��,�Ҽ�����05��                      *
;*��ע:                                                                        *
;*�������: PROTEUS 6                                                          *
;*******************************************************************************
    KEY_OK      BIT     00H
    VOLNUMB     EQU     22H     
    PHONE       EQU     21H
    COUNTER     EQU     23H     ;������ʾ�ļ�����
    KEYVAL      EQU     25H
    DISPBUF     EQU     5EH
    FIRST       BIT     P2.7    ;��һλ����ܵ�λ����
    SECOND      BIT     P2.6    ;�ڶ�λ����ܵ�λ����
    TMRVAR      EQU     60110   ;65536-5000*12/11.0592  ��ʱ����ֵ5����
;===============================================================================        
    ORG     0000H   
    JMP     START
    ORG     0*8+3               ;INT0�ж����
    RETI
    ORG     1*8+3               ;TIMER0�ж����
    JMP     INT_T0              ;תȥ��ʱ��0�жϷ���������
    ORG     2*8+3               ;INT1�ж����
    RETI
    ORG     3*8+3               ;TIMER1�ж����
    RETI
    ORG     4*8+3               ;�����ж����
    RETI
;===============================================================================
START:
    mov     sp,#5fh
    mov     p1,#0ffh
    mov     p3,#0ffh         
    mov     volnumb,#40h
    call    init_t0
    setb    ea
;===============================================================================
LOOP:;����
    ACALL KEY
    JB KEY_OK,KEYPROC
    ACALL DISP_VOL
    AJMP LOOP         
;===============================================================================  
disp_vol:;��ʾ����
        mov a,volnumb
        swap a
        anl a,#0fh
        mov dispbuf,a;ʮλ��DISPBUF
        mov a,volnumb
        anl a,#0fh
        mov dispbuf+1,a;��λ��DISPBUF+1
        ret
;==============================================================================
keyproc:;������ɢת
    mov a,keyval
    mov keyval,#00h
    rl a
    mov dptr,#tab_key
    jmp @a+dptr
tab_key:
    ajmp loop
    ajmp volup
    ajmp voldw
    ajmp volrsum
    ajmp vol24
    ajmp vol05
;===============================================================================
KEY:;���̳���
         clr key_ok;������±�־
         orl p3,#11000000b;���������ж�
         clr key_ok
         mov a,p3
         orl a,#00111111b
         cpl a
         jz key_1
         acall delay
         acall delay
         mov a,p3
         orl a,#00111111b
         jz key_1
         nop
         jnb acc.7,keydw1
         nop
         jb acc.6,key_ret
         setb key_ok
         mov keyval,#3
key_ret1:mov a,p3
         orl a,#00111111b
         cpl a
         jnz key_ret1;���ɿ���
         ajmp key_ret
key_ret:ret

keydw1:  
         nop
         jnb acc.6,keydw2
         setb key_ok
         mov keyval,#4
         jmp key_ret1
keydw2:  setb key_ok
         mov keyval,#5
         jmp key_ret1  

key_1:   
         setb p3.6
         clr p3.7 ;vol+����
         nop
         nop
         jnb p3.6,key01
   
         clr  p3.6;vol-����
         setb p3.7
         nop
         nop
         jnb  p3.7,key02
         
keyexit: ajmp key_ret

key01: 
         acall delay
         acall delay
         nop
         nop
         jb p3.6,key01_ret
         setb key_ok
         mov keyval,#1
         nop
         acall delay
         acall delay
key01_ret:jnb p3.6,$
         ajmp keyexit
key02:
         acall delay
         acall delay
         nop
         nop
         jb p3.7,key02_ret
         setb key_ok
         mov keyval,#2
         nop
         acall delay
         acall delay
key02_ret:jnb p3.7,$
         ajmp keyexit
delay:;                ȥ������ʱ
         push psw
         setb rs0
         mov  r7,#50
     d1: mov  r6,#50
     d2: djnz r6,d2
         djnz r7,d1
         pop  psw
         ret
;===============================================================================   
volup:;��������+
        mov phone,volnumb
        mov a,phone
        xrl a,#70h
        jz volup1
        acall uaa
        mov volnumb,phone
        jmp loop
volup1: mov volnumb,#70h
        jmp loop
;===============================================================================
voldw:;��������-
        mov phone,volnumb
        mov a,phone
        jz voldw1
        acall daa
        mov volnumb,phone
        jmp loop
voldw1: mov volnumb,#00h
        jmp loop
;===============================================================================
volrsum:;32��
        mov volnumb,#32h
        ajmp loop

vol24:;24��
       mov volnumb,#24h
       ajmp loop

vol05:;05��
       mov volnumb,#05h
       ajmp loop

;===============================================================================
uaa:;����1
        mov a,phone
        swap a
        anl a,#0fh
        mov r5,a
        mov a,phone
        anl a,#0fh
        nop
        cjne a,#09h,uaa_1
        nop
        mov r4,#00h
        inc r5
        ajmp uaa_2
uaa_1:
        inc a
        mov r4,a
uaa_2:
        mov a,r5
        swap a
        add a,r4
        mov phone,a
        ret
;===============================================================================
daa:;�ݼ�1
        mov a,phone
        swap a
        anl a,#0fh
        mov r5,a
        mov a,phone;
        anl a,#0fh
        jnz daa_1
        mov r4,#09h
        dec r5
        nop
        sjmp daa_2
  daa_1:
        dec a
        mov r4,a
  daa_2:
        mov a,r5;
        swap a
        add a,r4
        mov phone,a
        ret
;===============================================================================    
INIT_T0:                ;��ʼ��T0Ϊ5����Ķ�ʱ��
    MOV     TMOD,#01H
    MOV     TH0,#HIGH(TMRVAR)
    MOV     TL0,#LOW(TMRVAR)
    SETB    ET0         ;��T0�ж�
    SETB    TR0         ;��ʱ��0��ʼ����
    RET                 ;����
;===============================================================================
;�������жϳ���ʵ���������ʾ
INT_T0:                 ;��ʱ��T0���ж���Ӧ����
    PUSH    ACC         ;ACC��ջ
    PUSH    PSW         ;PSW��ջ
    MOV TH0,#HIGH(TMRVAR)
    MOV TL0,#LOW(TMRVAR)
    SETB    FIRST
    SETB    SECOND      ;����ʾ
    MOV     A,#DISPBUF  ;��ʾ�������׵�ַ
    ADD     A,Counter 
    MOV     R0,A
    MOV     A,@R0       ;���ݼ�������ֵȡ��Ӧ����ʾ��������ֵ
    MOV     DPTR,#DISPTAB   ;���α��׵�ַ
    MOVC    A,@A+DPTR   ;ȡ������
    MOV     P0,A        ;����������P0λ���οڣ�
    MOV     A,Counter   ;ȡ��������ֵ
    JZ      DISPFIRST   ;�����0����ʾ��һλ
    CLR     SECOND      ;������ʾ�ڶ�λ
    AJMP    DISPNEXT
DISPFIRST:
    CLR     FIRST       ;��ʾ��һλ 
DISPNEXT:
    INC     Counter     ;��������1
    MOV     A,Counter
    DEC     A           ;����������Ƶ�2,��������0
    DEC     A 
    JZ      RSTCOUNT 
    AJMP    DISPEXIT
RSTCOUNT:
    MOV     Counter,#0  ;��������ֵֻ����0��1
DISPEXIT:   
    POP     PSW
    POP     ACC
    RETI
DISPTAB:    DB 28H,7EH,0a4H,64H,72H,61H,21H,7CH,20H,60H 
    END