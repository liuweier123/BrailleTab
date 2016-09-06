;*******************************************************************************
;*文件: 5key_volume_con.asm                                                    *
;*作者: 张绍斌  2006/8/24                                                      *
;*版本: ver1.0                                                                 *
;*功能描述: 混合键盘模拟音量数码管显示                                         *
;*          上两键:左键音量-,右键音量+                                         *
;*          下三键:左键音量24级,中键音量32级,右键音量05级                      *
;*备注:                                                                        *
;*软件仿真: PROTEUS 6                                                          *
;*******************************************************************************
    KEY_OK      BIT     00H
    VOLNUMB     EQU     22H     
    PHONE       EQU     21H
    COUNTER     EQU     23H     ;用于显示的计数器
    KEYVAL      EQU     25H
    DISPBUF     EQU     5EH
    FIRST       BIT     P2.7    ;第一位数码管的位控制
    SECOND      BIT     P2.6    ;第二位数码管的位控制
    TMRVAR      EQU     60110   ;65536-5000*12/11.0592  定时器初值5毫秒
;===============================================================================        
    ORG     0000H   
    JMP     START
    ORG     0*8+3               ;INT0中断入口
    RETI
    ORG     1*8+3               ;TIMER0中断入口
    JMP     INT_T0              ;转去定时器0中断服务程序入口
    ORG     2*8+3               ;INT1中断入口
    RETI
    ORG     3*8+3               ;TIMER1中断入口
    RETI
    ORG     4*8+3               ;串行中断入口
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
LOOP:;主程
    ACALL KEY
    JB KEY_OK,KEYPROC
    ACALL DISP_VOL
    AJMP LOOP         
;===============================================================================  
disp_vol:;显示处理
        mov a,volnumb
        swap a
        anl a,#0fh
        mov dispbuf,a;十位到DISPBUF
        mov a,volnumb
        anl a,#0fh
        mov dispbuf+1,a;个位到DISPBUF+1
        ret
;==============================================================================
keyproc:;键处理散转
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
KEY:;键盘程序
         clr key_ok;清键按下标志
         orl p3,#11000000b;下面三键判断
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
         jnz key_ret1;键松开否
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
         clr p3.7 ;vol+按下
         nop
         nop
         jnb p3.6,key01
   
         clr  p3.6;vol-按下
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
delay:;                去键抖延时
         push psw
         setb rs0
         mov  r7,#50
     d1: mov  r6,#50
     d2: djnz r6,d2
         djnz r7,d1
         pop  psw
         ret
;===============================================================================   
volup:;键盘音量+
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
voldw:;键盘音量-
        mov phone,volnumb
        mov a,phone
        jz voldw1
        acall daa
        mov volnumb,phone
        jmp loop
voldw1: mov volnumb,#00h
        jmp loop
;===============================================================================
volrsum:;32级
        mov volnumb,#32h
        ajmp loop

vol24:;24级
       mov volnumb,#24h
       ajmp loop

vol05:;05级
       mov volnumb,#05h
       ajmp loop

;===============================================================================
uaa:;递增1
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
daa:;递减1
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
INIT_T0:                ;初始化T0为5毫秒的定时器
    MOV     TMOD,#01H
    MOV     TH0,#HIGH(TMRVAR)
    MOV     TL0,#LOW(TMRVAR)
    SETB    ET0         ;开T0中断
    SETB    TR0         ;定时器0开始运行
    RET                 ;返回
;===============================================================================
;以下是中断程序，实现数码管显示
INT_T0:                 ;定时器T0的中断响应程序
    PUSH    ACC         ;ACC入栈
    PUSH    PSW         ;PSW入栈
    MOV TH0,#HIGH(TMRVAR)
    MOV TL0,#LOW(TMRVAR)
    SETB    FIRST
    SETB    SECOND      ;关显示
    MOV     A,#DISPBUF  ;显示缓冲区首地址
    ADD     A,Counter 
    MOV     R0,A
    MOV     A,@R0       ;根据计数器的值取相应的显示缓冲区的值
    MOV     DPTR,#DISPTAB   ;字形表首地址
    MOVC    A,@A+DPTR   ;取字形码
    MOV     P0,A        ;将字形码送P0位（段口）
    MOV     A,Counter   ;取计数器的值
    JZ      DISPFIRST   ;如果是0则显示第一位
    CLR     SECOND      ;否则显示第二位
    AJMP    DISPNEXT
DISPFIRST:
    CLR     FIRST       ;显示第一位 
DISPNEXT:
    INC     Counter     ;计数器加1
    MOV     A,Counter
    DEC     A           ;如果计数器计到2,则让它回0
    DEC     A 
    JZ      RSTCOUNT 
    AJMP    DISPEXIT
RSTCOUNT:
    MOV     Counter,#0  ;计数器的值只能是0或1
DISPEXIT:   
    POP     PSW
    POP     ACC
    RETI
DISPTAB:    DB 28H,7EH,0a4H,64H,72H,61H,21H,7CH,20H,60H 
    END