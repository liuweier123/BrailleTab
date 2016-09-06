



;****************************资源分配**************************
     FLAG1  EQU 54H;是否检测到DS18B20标志位
     FLAG2  EQU 00H
     COUNT  EQU 63H
     CSA    EQU P0.4
     CSB    EQU P0.3
     RS     EQU P0.2
     RW     EQU P0.1
     E      EQU P0.0
     COM    EQU 21H       ;命令字
     DAT    EQU 22H       ;显示数据

     column EQU 23H     ;列
     pagef  EQU 24h      ;页
     cpage  EQU 25H
     ccolumn EQU 26H    ;列(0-15)

     CODE             EQU 27h
     column2          EQU 52H
     pagef2           equ 60h
     cpage2           EQU 61H
     ccolumn2         EQU 62H

     column3          EQU 2eH
     pagef3           equ 2fh
     cpage3           EQU 30H
     ccolumn3         EQU 31H
     column4          EQU 32H
     pagef4           equ 33h
     cpage4           EQU 34H
     ccolumn4         EQU 35H
     column5          EQU 36H
     pagef5           equ 37h
     cpage5           EQU 38H
     ccolumn5         EQU 39H

;*****************************主程序开始******************
ORG 0000H
LJMP START

ORG 0003H
LJMP INT0                         ;外部中断

ORG 0030H
START: MOV SP,#70H
       MOV P2,#0F0H
       CLR A
       CLR F0                     ;清设置键
       CLR FLAG2                  ;清确认键
       MOV COUNT,#0               ;中断次数计数
       SETB IT0
       SETB EX0
       SETB EA

       LCALL INT                  ;LCD12864初始化子程序
       LCALL CLEAR                ;LDC12864清屏子程序

       LCALL DISPLAY1             ;显示"温度自动控制系统"
       LCALL DISPLAY2             ;显示"设置温度"
       LCALL DISPLAY3             ;显示预设的温度
       LCALL DISPLAY4             ;显示"实际温度"
       LCALL DISPLAY5

       LCALL GET_TEMPER           ;调用读温度子程序
       ACALL DISPLAY5             ;调用显示
M:
       LCALL GET_TEMPER
       LCALL DELAY1

MM:     LCALL DISPLAY3
MM1:    JB F0,MM4                ;是否按上"设置"键
        JNB F1,M                 ;是否按下"确认"键

        MOV A,48H
        CJNE A,43H,MM5

        MOV A,55H
        CJNE A,42H,MM5

        MOV A,56H
        CJNE A,41H,MM5
        LJMP MM8



MM4:    MOV A,COUNT
        CJNE A,#1,MM2
        LCALL DISPLAY8
        LCALL DISPLAY8
        LJMP MM

MM2:    CJNE A,#2,MM3

        LCALL DISPLAY9
        LCALL DISPLAY9
MM3:    CJNE A,#3,MM
        LCALL DISPLAY10
        LCALL DISPLAY10
        LJMP MM

MM5:    JC  MM7
        LJMP MM6

MM6:    LCALL DISPLAY6
        CLR  P0.5
        SETB P0.6
        SETB P0.7
        LJMP M

MM7:   LCALL DISPLAY7
       SETB P0.5
       CLR  P0.6
       SETB P0.7
       LJMP M

MM8:   LCALL DISPLAY11
       SETB P0.5
       SETB P0.6
       CLR  P0.7
       LJMP M

;***********************外部中断0子程序**************
INT0:
      CLR EX0
      INC COUNT                 ;中断计数器加1
      CPL P3.0
      MOV DPTR,#JS

      MOV A,P2
      MOV P2,#0FH
      MOV 47H,P2
      JNB ACC.4,E1
      JNB ACC.5,E2
      JNB ACC.6,E3
      JNB ACC.7,E4
      SETB EX0
      RETI

E1:   MOV 20H,#0
      LJMP KEYH
E2:   MOV 20H,#4
      LJMP KEYH
E3:   MOV 20H,#8
      LJMP KEYH
E4:   MOV 20H,#12
      LJMP KEYH

KEYH:MOV A,47H
     JNB ACC.0,D0
     JNB ACC.1,D1
     JNB ACC.2,D2
     JNB ACC.3,D3
     SETB EX0
     RETI

D0:  MOV A,#0
     ADD A,20H
     MOV 59H,A
     MOV B,#3
     MUL AB
     JMP @A+DPTR

D1:  MOV A,#1
     ADD A,20H
     MOV 59H,A
     MOV B,#3
     MUL AB
     JMP @A+DPTR


D2:  MOV A,#2
     ADD A,20H
     MOV 59H,A
     MOV B,#3
     MUL AB
     JMP @A+DPTR


D3:  MOV A,#3
     ADD A,20H
     MOV 59H,A
     MOV B,#3
     MUL AB
     JMP @A+DPTR

JS:  LJMP LOOP0
     LJMP LOOP1
     LJMP LOOP2
     LJMP LOOP3
     LJMP LOOP4
     LJMP LOOP5
     LJMP LOOP6
     LJMP LOOP7
     LJMP LOOP8
     LJMP LOOP9
     LJMP LOOP10
     LJMP LOOP11

LOOP0:

     ACALL SHIFT1
     MOV P2,#0F0H
     SETB EX0
     RETI

LOOP1:

     ACALL SHIFT1
     MOV P2,#0F0H
     SETB EX0
     RETI

LOOP2:
     ACALL SHIFT1
     MOV P2,#0F0H
     SETB EX0
     RETI

LOOP3:
     ACALL SHIFT1
     MOV P2,#0F0H
     SETB EX0
     RETI

LOOP4:
     ACALL SHIFT1
     MOV P2,#0F0H
     SETB EX0
     RETI

LOOP5:
     ACALL SHIFT1
     MOV P2,#0F0H
     SETB EX0
     RETI

LOOP6:
     ACALL SHIFT1
     MOV P2,#0F0H
     SETB EX0
     RETI

LOOP7:
     ACALL SHIFT1
     MOV P2,#0F0H
     SETB EX0
     RETI

LOOP8:
     ACALL SHIFT1
     MOV P2,#0F0H
     SETB EX0
     RETI

LOOP9:
     ACALL SHIFT1
     MOV P2,#0F0H
     SETB EX0
     RETI

LOOP10:
     SETB F0              ;按下设置键
     MOV COUNT,#1
     MOV P2,#0F0H
     SETB EX0
     RETI

LOOP11:                  ;按下"确认"键
     CLR F0
     SETB F1
     MOV COUNT,#0
     MOV P2,#0F0H
     SETB EX0
     RETI

SHIFT1:
      JB F0,LLL
      LJMP EXIT

LLL:  MOV A,COUNT
      CJNE A,#2,LLL1
      MOV 48H,59H
      LJMP EXIT

LLL1: CJNE A,#3,LLL2
      MOV 55H,59H
      LJMP EXIT

LLL2: CJNE A,#4,EXIT
      MOV 56H,59H
      SETB F1
      CLR  F0

EXIT: RET




;*************************显示子程序*************************
DISPLAY1:                        ;显示"自动温度控制系统" 循环效果

       mov column4,#48
       mov pagef4,#0             ;温
       mov code,#0
       lcall writeright2
       LCALL DELAY1

       mov column4,#32
       mov pagef4,#0             ;温
       mov code,#0
       lcall writeright2

       mov column4,#48
       mov pagef4,#0             ;度
       mov code,#1
       lcall writeright2
       LCALL DELAY1

       mov column4,#16
       mov pagef4,#0             ;温
       mov code,#0
       lcall writeright2

       mov column4,#32
       mov pagef4,#0             ;度
       mov code,#1
       lcall writeright2

       mov column4,#48
       mov pagef4,#0             ;自
       mov code,#2
       lcall writeright2

       LCALL DELAY1

       mov column4,#0
       mov pagef4,#0             ;温
       mov code,#0
       lcall writeright2

       mov column4,#16
       mov pagef4,#0             ;度
       mov code,#1
       lcall writeright2

       mov column4,#32
       mov pagef4,#0             ;自
       mov code,#2
       lcall writeright2

       mov column4,#48
       mov pagef4,#0             ;动
       mov code,#3
       lcall writeright2

       LCALL DELAY1

       mov column3,#48
       mov pagef3,#0             ;温
       mov code,#0
       lcall writeleft2

       mov column4,#0
       mov pagef4,#0             ;度
       mov code,#1
       lcall writeright2

       mov column4,#16
       mov pagef4,#0             ;自
       mov code,#2
       lcall writeright2

       mov column4,#32
       mov pagef4,#0             ;动
       mov code,#3
       lcall writeright2

       mov column4,#48
       mov pagef4,#0             ;控
       mov code,#4
       lcall writeright2
       LCALL DELAY1

       mov column3,#32
       mov pagef3,#0             ;温
       mov code,#0
       lcall writeleft2

       mov column3,#48
       mov pagef3,#0             ;度
       mov code,#1
       lcall writeleft2

       mov column4,#0
       mov pagef4,#0             ;自
       mov code,#2
       lcall writeright2

       mov column4,#16
       mov pagef4,#0             ;动
       mov code,#3
       lcall writeright2

       mov column4,#32
       mov pagef4,#0             ;控
       mov code,#4
       lcall writeright2

       mov column4,#48
       mov pagef4,#0             ;制
       mov code,#5
       lcall writeright2

       LCALL DELAY1

       mov column3,#16
       mov pagef3,#0             ;温
       mov code,#0
       lcall writeleft2

       mov column3,#32
       mov pagef3,#0             ;度
       mov code,#1
       lcall writeleft2

       mov column3,#48
       mov pagef3,#0             ;自
       mov code,#2
       lcall writeleft2

       mov column4,#0
       mov pagef4,#0             ;动
       mov code,#3
       lcall writeright2

       mov column4,#16
       mov pagef4,#0             ;控
       mov code,#4
       lcall writeright2

       mov column4,#32
       mov pagef4,#0             ;制
       mov code,#5
       lcall writeright2

        mov column4,#48
       mov pagef4,#0             ;系
       mov code,#6
       lcall writeright2
       LCALL DELAY1

       mov column3,#0
       mov pagef3,#0             ;温
       mov code,#0
       lcall writeleft2

       mov column3,#16
       mov pagef3,#0             ;度
       mov code,#1
       lcall writeleft2

       mov column3,#32
       mov pagef3,#0             ;自
       mov code,#2
       lcall writeleft2

       mov column3,#48
       mov pagef3,#0             ;动
       mov code,#3
       lcall writeleft2

       mov column4,#0
       mov pagef4,#0             ;控
       mov code,#4
       lcall writeright2

       mov column4,#16
       mov pagef4,#0             ;制
       mov code,#5
       lcall writeright2

       mov column4,#32
       mov pagef4,#0             ;系
       mov code,#6
       lcall writeright2

       mov column4,#48
       mov pagef4,#0             ;统
       mov code,#7
       lcall writeright2
       LCALL DELAY1
       RET

DISPLAY2:                         ;显示"设置温度"
       mov column3,#16            ;设
       mov pagef3,#2
       mov code,#8
       lcall writeleft2
       LCALL DELAY1

       mov column3,#32          ;置
       mov pagef3,#2
       mov code,#9
       LCALL writeleft2
       LCALL DELAY1

        mov column3,#48          ;温
       mov pagef3,#2
       mov code,#0
       lcall writeleft2
       LCALL DELAY1

       mov column4,#0            ;度
       mov pagef4,#2
       mov code,#1
       lcall writeright2
       LCALL DELAY1
       RET
DISPLAY3:
       mov column2,#16
       mov pagef2,#2
       mov code,#10
       lcall writeright
                                  ;显示预设的温度
       mov column2,#24
       mov pagef2,#2
       mov code,48H
       lcall writeright

       mov column2,#32
       mov pagef2,#2
       mov code,55H
       lcall writeright

       mov column2,#40
       mov pagef2,#2             ;.
       mov code,#11
       lcall writeright

       mov column2,#48
       mov pagef2,#2
       mov code,56H
       lcall writeright
       RET

DISPLAY4:                              ;显示"实际温度"
       mov column3,#16            ;实
       mov pagef3,#4
       mov code,#10
       lcall writeleft2
       LCALL DELAY1

       mov column3,#32           ;际
       mov pagef3,#4
       mov code,#11
       lcall writeleft2
       LCALL DELAY1

       mov column3,#48          ;温
       mov pagef3,#4
       mov code,#0
       lcall writeleft2
       LCALL DELAY1

       mov column3,#0          ;度
       mov pagef3,#4
       mov code,#1
       lcall writeright2
       LCALL DELAY1
        RET

DISPLAY5:                            ;显示实际的温度
      MOV A,29H
      MOV C,40H  ;28的位地址
      RRC A
      MOV C,41H
      RRC A
      MOV C,42H
      RRC A
      MOV C,43H
      RRC A
      MOV 51H,A
      ANL 29H,#0FH
      MOV A,29H
      MOV B,#6
      MUL AB
      MOV 50H,A

      mov a,51H
      mov b,#10
      div ab
      mov 43H,a
      mov 42H,b

      MOV A,50H
      MOV B,#10
      DIV AB
      MOV 41H,A
       MOV 40H,B

       mov column2,#16
       mov pagef2,#4
       mov code,#10
       lcall writeright

       mov column2,#24            ;实际温度
       mov pagef2,#4
       mov code,43h
       lcall writeright

       mov column2,#32
       mov pagef2,#4
       mov code,42h
       lcall writeright

       mov column2,#40
       mov pagef2,#4             ;.
       mov code,#11
       lcall writeright

       mov column2,#48
       mov pagef2,#4
       mov code,41h
       lcall writeright
       RET

DISPLAY6:
       mov column3,#24
       mov pagef3,#6             ;状
       mov code,#13
       lcall writeleft2
       LCALL DELAY1

       mov column3,#40
       mov pagef3,#6             ;态
       mov code,#14
       lcall writeleft2
       LCALL DELAY1

       mov column,#56
       mov pagef,#6             ; :
       mov code,#10
       lcall writeleft
       LCALL DELAY1

       mov column4,#0
       mov pagef4,#6             ;加
       mov code,#15
       lcall writeright2
       LCALL DELAY1

       mov column4,#16
       mov pagef4,#6             ;热
       mov code,#16
       lcall writeright2
       LCALL DELAY1

       mov column4,#32
       mov pagef4,#6             ; !
       mov code,#19
       lcall writeright2
       LCALL DELAY1
       RET

DISPLAY7:
       mov column3,#24
       mov pagef3,#6             ;状
       mov code,#13
       lcall writeleft2
       LCALL DELAY1

       mov column3,#40
       mov pagef3,#6             ;态
       mov code,#14
       lcall writeleft2
       LCALL DELAY1

       mov column,#56
       mov pagef,#6             ; :
       mov code,#10
       lcall writeleft
       LCALL DELAY1

       mov column4,#0
       mov pagef4,#6             ;降
       mov code,#17
       lcall writeright2
       LCALL DELAY1

       mov column4,#16
       mov pagef4,#6             ;温
       mov code,#0
       lcall writeright2
       LCALL DELAY1

       mov column4,#32
       mov pagef4,#6             ;!
       mov code,#19
       lcall writeright2
       LCALL DELAY1
       RET
DISPLAY8:
         mov column2,#24
         mov pagef2,#2
         mov code,48H
         lcall writeright

         LCALL DELAY
         LCALL DELAY

         mov column2,#24
         mov pagef2,#2
         mov code,#12
         lcall writeright
         RET

DISPLAY9:
         mov column2,#32
         mov pagef2,#2
         mov code,55H
         lcall writeright

         LCALL DELAY
         LCALL DELAY

         mov column2,#32
         mov pagef2,#2
         mov code,#12
         lcall writeright
         RET
DISPLAY10:
        mov column2,#48
         mov pagef2,#2
         mov code,56H
         lcall writeright

         LCALL DELAY
         LCALL DELAY

         mov column2,#48
         mov pagef2,#2
         mov code,#12
         lcall writeright
         RET

DISPLAY11:
       mov column3,#24
       mov pagef3,#6             ;状
       mov code,#13
       lcall writeleft2
       LCALL DELAY1

       mov column3,#40
       mov pagef3,#6             ;态
       mov code,#14
       lcall writeleft2
       LCALL DELAY1

       mov column,#56
       mov pagef,#6             ; :
       mov code,#10
       lcall writeleft
       LCALL DELAY1

       mov column4,#0
       mov pagef4,#6             ;降
       mov code,#20
       lcall writeright2
       LCALL DELAY1

       mov column4,#16
       mov pagef4,#6             ;温
       mov code,#21
       lcall writeright2
       LCALL DELAY1

       mov column4,#32
       mov pagef4,#6             ;!
       mov code,#19
       lcall writeright2
       LCALL DELAY1
       RET

DISPLAY:
       mov column2,#24
       mov pagef2,#2
       mov code,48H
       lcall writeright

       mov column2,#32
       mov pagef2,#2
       mov code,55H
       lcall writeright

       mov column2,#40
       mov pagef2,#2             ;.
       mov code,#11
       lcall writeright

       mov column2,#48
       mov pagef2,#2
       mov code,56H
       lcall writeright

      MOV A,29H
      MOV C,40H  ;28的位地址
      RRC A
      MOV C,41H
      RRC A
      MOV C,42H
      RRC A
      MOV C,43H
      RRC A
      MOV 51H,A
      ANL 29H,#0FH
      MOV A,29H
      MOV B,#6
      MUL AB
      MOV 50H,A

      mov a,51H
      mov b,#10
      div ab
      mov 43H,a
      mov 42H,b

      MOV A,50H
      MOV B,#10
      DIV AB
      MOV 41H,A
      MOV 40H,B

       mov column2,#24            ;实际温度
       mov pagef2,#4
       mov code,43h
       lcall writeright

       mov column2,#32
       mov pagef2,#4
       mov code,42h
       lcall writeright

       mov column2,#40
       mov pagef2,#4             ;.
       mov code,#11
       lcall writeright

       mov column2,#48
       mov pagef2,#4
       mov code,41h
       lcall writeright
       RET


;***********************DS18B20复位初始化子程序***********


INIT_1820:
      SETB P3.1
      NOP
      CLR P3.1;主机发出延时537微秒的复位低脉冲
      MOV R1,#3
TSR1: MOV R0,#107
      DJNZ R0,$
      DJNZ R1,TSR1
      SETB P3.1       ;然后拉高数据线
      NOP
      NOP
      NOP
      MOV R0,#25H
TSR2: JNB P3.1,TSR3  ;等待DS18B20回应
      DJNZ R0,TSR2
      LJMP TSR4      ; 延时
TSR3: SETB FLAG1     ; 置标志位,表示DS1820存在

      LJMP TSR5
TSR4: CLR FLAG1      ; 清标志位,表示DS1820不存在

      LJMP TSR7
TSR5: MOV R0,#117
TSR6: DJNZ R0,TSR6 ; 时序要求延时一段时间
TSR7: SETB P3.1
      RET    ; 读出转换后的温度值



;***********************读温度子程序*****************
GET_TEMPER:
      SETB P3.1
      LCALL INIT_1820;先复位DS18B20
      JB FLAG1,TSS2

      RET ; 判断DS1820是否存在?若DS18B20不存在则返回
TSS2:
      MOV A,#0CCH ; 跳过ROM匹配
      LCALL WRITE_1820
      MOV A,#44H ; 发出温度转换命令
      LCALL WRITE_1820;通过调用显示子程序实现延时一段时间,等待AD转换结束,12位的话750微秒
      LCALL DISPLAY
      LCALL INIT_1820;准备读温度前先复位
      MOV A,#0CCH ; 跳过ROM匹配
      LCALL WRITE_1820
      MOV A,#0BEH ; 发出读温度命令
      LCALL WRITE_1820
      LCALL READ_18200
      RET

;*************************写命令子程序**********
WRITE_1820:
      MOV R2,#8
      CLR C
WR1:  CLR P3.1
      MOV R3,#6
      DJNZ R3,$
      RRC A
      MOV P3.1,C

      MOV R3,#23
      DJNZ R3,$
      SETB P3.1
      NOP
      DJNZ R2,WR1
      SETB P3.1
      RET


;***********************读命令子程序***********
READ_18200:
      MOV R4,#2
      MOV R1,#29H
RE00: MOV R2,#8
RE01: CLR C
      SETB P3.1
      NOP
      NOP
      CLR P3.1
      NOP
      NOP
      NOP
      SETB P3.1
      MOV R3,#9
RE10: DJNZ R3,RE10
      MOV C,P3.1
      MOV R3,#23
RE20: DJNZ R3,RE20
      RRC A
      DJNZ R2,RE01
      MOV @R1,A
      DEC R1
      DJNZ R4,RE00
      RET


;**********************左半屏写入数字子程序**************8
writeleft:
mov dptr,#table1
push column
mov cpage,#2
mov ccolumn,#0
mov a,pagef
anl a,#07h
orl a,#0b8h            ;页地址,第0页
mov com,a
lcall prm0

mov a,column
anl a,#3fh
orl a,#40h             ;列地址,第0列
mov com,a
lcall prm0

mov a,code
mov b,#16
mul ab
add a,dpl
mov dpl,a
mov a,b
addc a,dph
mov dph,a

lp1:
mov a,#00h
movc a,@a+dptr
mov dat,a
lcall prm1
inc ccolumn
mov a,ccolumn
inc dptr
cjne a,#8,lp1
dec cpage
inc pagef
mov a,cpage
jz over1
mov a,pagef
anl a,#07h
orl a,#0b8h
mov com,a
lcall prm0
pop column
mov a,column
anl a,#3fh
orl a,#40h
mov com,a
lcall prm0
mov ccolumn,#0
ljmp lp1
over1:
ret

;************右半屏写入数字子程序*******************
writeright:
mov dptr,#table1
push column2
mov cpage2,#2
mov ccolumn2,#0
mov a,pagef2
anl a,#07h
orl a,#0b8h
mov com,a
lcall prr0

mov a,column2
anl a,#3fh
orl a,#40h
mov com,a
lcall prr0

mov a,code
mov b,#16
mul ab
add a,dpl
mov dpl,a
mov a,b
addc a,dph
mov dph,a

lp2:
mov a,#00h
movc a,@a+dptr
mov dat,a
lcall prr1
inc ccolumn2
mov a,ccolumn2
inc dptr
cjne a,#8,lp2
dec cpage2
inc pagef2
mov a,cpage2
jz over2
mov a,pagef2
anl a,#07h
orl a,#0b8h
mov com,a
lcall prr0
pop column2
mov a,column2
anl a,#3fh
orl a,#40h
mov com,a
lcall prr0
mov ccolumn2,#0
ljmp lp2
over2:
ret


;*****************左半屏写入汉字子程序*****************
writeleft2:
mov dptr,#table2
push column3
mov cpage3,#2
mov ccolumn3,#0
mov a,pagef3
anl a,#07h
orl a,#0b8h
mov com,a
lcall prm0

mov a,column3
anl a,#3fh
orl a,#40h
mov com,a
lcall prm0

mov a,code
mov b,#32
mul ab
add a,dpl
mov dpl,a
mov a,b
addc a,dph
mov dph,a

lp3:
mov a,#00h
movc a,@a+dptr
mov dat,a
lcall prm1
inc ccolumn3
mov a,ccolumn3
inc dptr
cjne a,#16,lp3
dec cpage3
inc pagef3
mov a,cpage3
jz over3
mov a,pagef3
anl a,#07h
orl a,#0b8h
mov com,a
lcall prm0
pop column3
mov a,column3
anl a,#3fh
orl a,#40h
mov com,a
lcall prm0
mov ccolumn3,#0
ljmp lp3
over3:
ret
;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;
writeright2:  ; 右半屏写入汉字子程序
mov dptr,#table2
push column4
mov cpage4,#2
mov ccolumn4,#0
mov a,pagef4
anl a,#07h
orl a,#0b8h
mov com,a
lcall prr0

mov a,column4
anl a,#3fh
orl a,#40h
mov com,a
lcall prr0

mov a,code
mov b,#32
mul ab
add a,dpl
mov dpl,a
mov a,b
addc a,dph
mov dph,a

lp4:
mov a,#00h
movc a,@a+dptr
mov dat,a
lcall prr1
inc ccolumn4
mov a,ccolumn4
inc dptr
cjne a,#16,lp4
dec cpage4
inc pagef4
mov a,cpage4
jz over4
mov a,pagef4
anl a,#07h
orl a,#0b8h
mov com,a
lcall prr0
pop column4
mov a,column4
anl a,#3fh
orl a,#40h
mov com,a
lcall prr0
mov ccolumn4,#0
ljmp lp4
over4:
ret


;*******************右半屏写入数字子程序****************

writeleft1:
mov dptr,#table1
push column2
mov cpage2,#2
mov ccolumn2,#0
mov a,pagef2
anl a,#07h
orl a,#0b8h
mov com,a
lcall prm0

mov a,column2
anl a,#3fh
orl a,#40h
mov com,a
lcall prm0

mov a,code
mov b,#16
mul ab
add a,dpl
mov dpl,a
mov a,b
addc a,dph
mov dph,a

lp9:
mov a,#00h
movc a,@a+dptr
mov dat,a
lcall prm1
inc ccolumn2
mov a,ccolumn2
inc dptr
cjne a,#8,lp9
dec cpage2
inc pagef2
mov a,cpage2
jz over9
mov a,pagef2
anl a,#07h
orl a,#0b8h
mov com,a
lcall prm0
pop column2
mov a,column2
anl a,#3fh
orl a,#40h
mov com,a
lcall prm0
mov ccolumn2,#0
ljmp lp9
over9:
ret


;*********************写指令代码子程序(左)*******************
PRM0:  CLR CSA
  SETB CSB
  CLR rs
  SETB rw
PRM01:  MOV P1,#0FFH
  SETB E
  MOV A,P1
  CLR E
  JB  ACC.7,PRM01
  CLR rw
  MOV P1,COM
  SETB E
  CLR E
  RET


;***********************写显示数据子程序(左)******************
PRM1:  CLR CSA
  SETB CSB
  CLR rs
  SETB rw
PRM11:  MOV P1,#0FFH
  SETB E
  MOV A,P1
  CLR E
  JB  ACC.7,PRM11
  SETB rs
  CLR rw
  MOV P1,DAT
  SETB E
  CLR E
  RET

;********************写指令代码子程序(右)***************
PRR0:  CLR CSB
  SETB CSA
  CLR rs
  SETB rw
PRR01:  MOV P1,#0FFH
  SETB E
  MOV A,P1
  CLR E
  JB  ACC.7,PRR01
  CLR rw
  MOV P1,COM
  SETB E
  CLR E
  RET

;************************写显示数据子程序(右)**************

PRR1:  CLR CSB
  SETB CSA
  CLR rs
  SETB rw
PRR11:  MOV P1,#0FFH
  SETB E
  MOV A,P1
  CLR E
  JB  ACC.7,PRR11
  SETB rs
  CLR rw
  MOV P1,DAT
  SETB E
  CLR E
  RET

;*********************LCD12864初始化子程序**************
INT: MOV COM,#0C0H ;设置显示起始行为第一行
  LCALL PRM0
  LCALL PRR0
  MOV COM,#3FH  ;开显示设置
  LCALL PRM0
  LCALL PRR0
  RET

;**************************LCD12864液晶清屏子程序*****************
CLEAR:  MOV R4,#00H
CLEAR1:  MOV A,R4
  ORL A,#0B8H
  MOV COM,A
  LCALL PRM0
  LCALL PRR0
  MOV COM,#40H
  LCALL PRM0
  LCALL PRR0
  MOV R3,#40H
CLEAR2:  MOV DAT,#00H
  LCALL PRM1
  LCALL PRR1
  DJNZ R3,CLEAR2
  INC R4
  CJNE R4,#08H,CLEAR1
  RET
;***********************延时子程序*************
DELAY: MOV R0,#20
SS:    MOV R1,#20
       DJNZ R1,$
       DJNZ R0,SS
       RET
DELAY1:MOV R0,#5
YY:    MOV R1,#110
QQ:    MOV R2,#200
       DJNZ R2,$
       DJNZ R1,QQ
       DJNZ R0,YY
       RET

table1:
DB    0F0h, 0F8h,  0Ch,  04h
DB    04h,  0Ch, 0F8h, 0F0h        ;0
DB    0Fh,  1Fh,  30h,  20h
DB    20h,  30h,  1Fh,  0Fh


DB    00h,  00h,  08h, 0F8h         ;1
DB    0FCh,  00h,  00h,  00h
DB    00h,  00h,  20h,  3Fh
DB    3Fh,  20h,  00h,  00h

DB  30h,  38h,  0Ch,  04h
DB  04h,  0Ch, 0F8h, 0F0h
DB  20h,  30h,  38h,  2Ch          ;2
DB  26h,  23h,  21h,  38h

DB  10h,  18h,  0Ch,  84h
DB   84h, 0CCh,  78h,  30h
DB   08h,  18h,  30h,  20h
DB   20h,  31h,  1Fh,  0Eh         ;3


DB 00h, 0C0h,  70h,  18h
DB  0FCh, 0FEh,  00h,  00h
DB   07h,  05h,  04h,  24h
DB   3Fh,  3Fh,  24h,  04h          ;4


DB  0FCh, 0FCh, 0C4h,  44h
DB   44h, 0C4h,  84h,  04h
DB    08h,  18h,  30h,  20h
DB   20h,  30h,  1Fh,  0Fh          ;5

DB  0F0h, 0F8h,  8Ch,  44h
DB   44h, 0CCh,  98h,  10h
DB   0Fh,  1Fh,  30h,  20h
DB   20h,  30h,  1Fh,  0Fh          ;6

DB    1Ch,  0Ch,  0Ch,  0Ch
DB  0CCh, 0ECh,  3Ch,  1Ch
DB    00h,  00h,  3Ch,  3Fh
DB   03h,  00h,  00h,  00h         ;7

DB    30h,  78h, 0CCh,  84h
DB   84h, 0CCh,  78h,  30h
DB  0Eh,  1Fh,  31h,  20h
DB   20h,  31h,  1Fh,  0Eh          ;8

DB  0F0h, 0F8h,  0Ch,  04h
DB   04h,  0Ch, 0F8h, 0F0h
DB   08h,  19h,  33h,  22h
DB   22h,  33h,  1Fh,  0Fh         ;9


DB   00h,  00h,  00h,  00h,  00h,  00h,  00h,  00h
DB   00h,  00h,  33h,  33h,  00h,  00h,  00h,  00h   ;: 10

DB 00H,00H,00H,00H,00H,00H,00H,00H               ; 11  .
DB 00H,00H,30H,30H,00H,00H,00H,00H


DB   00h,  00h,  00h,  00h,  00h,  00h,  00h,  00h
DB   00h,  00h,  00h,  00h,  00h,  00h,  00h,  00h   ;空 12

DB   80H,  80H,  80H,  80H,  80H,  80H,  80H, 80H,
DB   00H,  00H,  00H,  00H,  00H,  00H,  00H, 00H     ;一  13



table2:

DB   10h,  22h,  64h,  0Ch,  80h,  00h, 0FEh,  92h  ;0 温
DB   92h,  92h,  92h,  92h, 0FFh,  02h,  00h,  00h
DB   04h,  04h, 0FEh,  01h,  40h,  7Eh,  42h,  42h
DB   7Eh,  42h,  7Eh,  42h,  42h,  7Eh,  40h,  00h

DB   00h,  00h, 0FCh,  24h,  24h,  24h, 0FCh, 0A5h  ;1度
DB  0A6h, 0A4h, 0FCh,  24h,  34h,  26h,  04h,  00h
DB   40h,  20h,  9Fh,  80h,  42h,  42h,  26h,  2Ah
DB   12h,  2Ah,  26h,  42h,  40h, 0C0h,  40h,  00h

DB   00h,  00h,  00h, 0F8h,  48h,  4Ch,  4Ah,  49h   ;2自
DB   48h,  48h,  48h, 0FCh,  08h,  00h,  00h,  00h
DB   00h,  00h,  00h, 0FFh,  44h,  44h,  44h,  44h
DB   44h,  44h,  44h, 0FFh,  00h,  00h,  00h,  00h

DB   20h,  24h,  24h, 0E4h,  26h,  34h,  20h,  10h   ;3动
DB   10h, 0FFh,  10h,  10h,  10h, 0F8h,  10h,  00h
DB   08h,  1Ch,  0Bh,  08h,  08h,  8Ah,  4Ch,  30h
DB   0Ch,  03h,  40h,  80h,  40h,  3Fh,  00h,  00h

DB   10h,  10h,  10h, 0FFh,  90h,  50h,  0Ch,  44h   ;4控
DB   24h,  15h,  06h,  14h,  24h,  54h,  0Ch,  00h
DB   02h,  42h,  81h,  7Fh,  00h,  40h,  42h,  42h
DB   42h,  42h,  7Eh,  42h,  43h,  62h,  40h,  00h

DB   40h,  60h,  5Eh,  48h,  48h, 0FFh,  48h,  4Ch   ;5制
DB   68h,  40h, 0F8h,  00h,  00h, 0FFh,  00h,  00h
DB   00h,  00h,  3Fh,  01h,  01h, 0FFh,  11h,  21h
DB   1Fh,  00h,  07h,  40h,  80h,  7Fh,  00h,  00h

DB   00h,  02h,  22h,  22h,  32h,  2Eh, 0A2h,  62h   ;6系
DB   22h,  22h,  91h,  09h,  01h,  00h,  00h,  00h
DB   00h,  00h,  42h,  22h,  1Ah,  43h,  82h,  7Eh
DB   02h,  02h,  0Ah,  13h,  66h,  00h,  00h,  00h

DB   20h,  30h, 0ACh,  63h,  30h,  88h, 0C8h, 0A8h   ;7统
DB   99h,  8Eh,  88h, 0A8h, 0CCh,  88h,  00h,  00h
DB   22h,  67h,  22h,  12h,  92h,  40h,  30h,  0Fh
DB   00h,  00h,  3Fh,  40h,  40h,  41h,  70h,  00h

DB   40h,  40h,  42h, 0CCh,  00h,  40h, 0A0h,  9Fh  ;8设
DB   81h,  81h,  81h,  9Fh, 0A0h,  20h,  20h,  00h
DB   00h,  00h,  00h,  7Fh, 0A0h,  90h,  40h,  43h
DB   2Ch,  10h,  28h,  26h,  41h, 0C0h,  40h,  00h

DB   00h,  10h,  17h, 0D5h,  55h,  57h,  55h,  7Dh  ;9置
DB   55h,  57h,  55h, 0D5h,  17h,  10h,  00h,  00h
DB   40h,  40h,  40h,  7Fh,  55h,  55h,  55h,  55h
DB   55h,  55h,  55h,  7Fh,  40h,  60h,  40h,  00h

DB   10h,  0Ch,  04h,  44h,  8Ch,  94h,  35h,  06h  ;10实
DB  0F4h,  04h,  04h,  04h,  04h,  14h,  0Ch,  00h
DB   02h,  82h,  82h,  42h,  42h,  23h,  12h,  0Eh
DB   03h,  0Ah,  12h,  22h,  42h, 0C3h,  02h,  00h

DB   00h, 0FEh,  02h,  22h, 0DAh,  06h,  40h,  42h  ;11际
DB   42h,  42h, 0C2h,  42h,  43h,  62h,  40h,  00h
DB   00h, 0FFh,  08h,  10h,  08h,  07h,  10h,  08h
DB   46h,  80h,  7Fh,  00h,  02h,  04h,  18h,  00h

DB    00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h,         ;12 空白
DB    00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
DB    00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
DB    00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h

DB   00h,  08h,  30h,  00h, 0FFh,  20h,  20h,  20h    ;13 状
DB   20h, 0FFh,  20h,  22h,  24h,  30h,  20h,  00h
DB   08h,  0Ch,  02h,  01h, 0FFh,  40h,  20h,  1Ch
DB   03h,  00h,  03h,  0Ch,  30h,  60h,  20h,  00h

DB   04h,  04h,  84h,  84h,  44h,  24h,  54h,  8Fh   ;14态
DB   14h,  24h,  44h,  44h,  84h,  86h,  84h,  00h
DB   01h,  21h,  1Ch,  00h,  3Ch,  40h,  42h,  4Ch
DB   40h,  40h,  70h,  04h,  08h,  31h,  00h,  00h

DB   10h,  10h,  10h, 0FFh,  10h,  10h, 0F8h,  10h    ;15 加
DB   00h, 0F8h,  08h,  08h,  08h, 0FCh,  08h,  00h
DB   40h,  20h,  1Eh,  01h,  20h,  40h,  3Fh,  00h
DB   00h,  7Fh,  20h,  20h,  20h,  7Fh,  00h,  00h

DB   00h,  88h,  88h,  48h, 0FFh,  48h,  28h,  08h    ;16 热
DB   48h, 0FFh,  08h,  08h, 0FCh,  08h,  00h,  00h
DB   80h,  60h,  04h,  08h,  27h, 0C0h,  08h,  04h
DB   23h, 0C0h,  01h,  00h,  27h,  48h, 0C6h,  00h

DB   00h, 0FEh,  02h,  22h, 0DAh,  06h,  88h,  44h    ;17 降
DB   57h, 0A4h,  54h,  4Ch,  84h,  80h,  80h,  00h
DB   00h, 0FFh,  08h,  10h,  08h,  07h,  10h,  1Eh
DB   12h, 0FFh,  12h,  12h,  18h,  11h,  00h,  00h

DB   00h,  00h,  00h,  00h,  00h,  00h,  00h,  00h   ;18 :
DB   00h,  00h,  00h,  00h,  00h,  00h,  00h,  00h
DB   00h,  00h,  33h,  33h,  00h,  00h,  00h,  00h
DB   00h,  00h,  00h,  00h,  00h,  00h,  00h,  00h

DB   00h,  00h,  00h,  00h,  00h,  00h,  1Ch, 0FEh   ;19 !
DB  0FEh,  1Ch,  00h,  00h,  00h,  00h,  00h,  00h
DB   00h,  00h,  00h,  00h,  00h,  00h,  00h,  33h
DB   33h,  00h,  00h,  00h,  00h,  00h,  00h,  00h

DB   00h,  80h,  60h, 0F8h,  07h,  00h,  7Eh,  22h   ;20保
DB   22h, 0E2h,  22h,  22h,  3Fh,  82h,  00h,  00h
DB   01h,  00h,  00h, 0FFh,  41h,  21h,  11h,  09h
DB   05h, 0FFh,  05h,  09h,  31h,  61h,  21h,  00h

DB   10h,  10h,  10h, 0FFh,  90h,  50h,  48h,  48h    ;21持
DB   48h,  7Fh,  48h, 0CCh,  68h,  40h,  00h,  00h
DB   02h,  42h,  81h,  7Fh,  00h,  02h,  06h,  1Ah
DB   02h,  42h,  82h,  7Fh,  02h,  03h,  02h,  00h

END
