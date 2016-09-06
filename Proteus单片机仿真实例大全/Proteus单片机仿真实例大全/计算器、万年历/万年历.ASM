TEMPER_L EQU 40H;用于保存读出温度的高8位
TEMPER_H EQU 41H;用于保存读出温度的低8位
FLAG1 EQU 42H;是否检测到DS18B20标志位
a_bit equ 43h ;数码管个位数存放内存位置
b_bit equ 44h ;数码管十位数存放内存位置
T_RST Bit P3.6 ;实时时钟复位线引脚
T_CLK Bit P3.4 ;实时时钟时钟线引脚
T_IO Bit P3.5 ;实时时钟数据线引脚
SECOND EQU 45H
MINUTE EQU 46H
HOUR EQU 47H
DAY EQU 48H
MONTH EQU 49H
WEEK EQU 4AH
YEARL EQU 4BH
CSA EQU p2.4
CSB EQU p2.3
rs  EQU P2.2
rw  EQU P2.1
E   EQU P2.0
COM     EQU 21H
DAT     EQU 22H
column  EQU 23H
pagef   EQU 24h
cpage   EQU 25H
ccolumn EQU 26H
codes   EQU 27h
column2 EQU 28H
pagef2  equ 29h
cpage2  EQU 2aH
ccolumn2 EQU 2bH
column3 EQU 2eH
pagef3  equ 2fh
cpage3  EQU 30H
ccolumn3 EQU 31H
column4 EQU 32H
pagef4  equ 33h
cpage4  EQU 34H
ccolumn4 EQU 35H
column5 EQU 36H
pagef5  equ 37h
cpage5  EQU 38H
ccolumn5 EQU 39H
      ORG 0
      LJMP START
      ORG 3
      LJMP XX0
      ORG 13H
      LJMP XX1
;*********************************************主程序开始
START:  MOV TMOD,#01H
        MOV TH0,#03CH   ;置定时器初值(定时50ms)
        MOV TL0,#0B0H
        SETB TR0        ;启动定时器0
        MOV SP,#60H     ;修改堆栈
        LCALL INT       ;调用初始化子程序
        LCALL CLEAR     ;调用清屏子程序

;*********************************************固定显示字符
mov column3,#48
mov pagef3,#0
mov codes,#8           ;年
lcall writeleft2
mov column4,#16
mov pagef4,#0
mov codes,#9          ;;;;;月
lcall writeright2
mov column4,#48
mov pagef4,#0             ;;;;;;日
mov codes,#10
lcall writeright2
mov column3,#0
mov pagef3,#2          ;;;星
mov codes,#11
lcall writeleft2
mov column3,#16
mov pagef3,#2        ;;;;;;期
mov codes,#12
lcall writeleft2
mov column4,#0
mov pagef4,#2     ;;;;;;  :
mov codes,#13
lcall writeright2
mov column4,#32
mov pagef4,#2
mov codes,#13      ;;;;;;  :
lcall writeright2
mov column4,#48
mov pagef4,#4
mov codes,#15     ;;;;;;;度
lcall writeright2
mov column,#16
mov pagef,#0
mov codes,#2           ;;;;;;;2
lcall writeleft
mov column,#24
mov pagef,#0
mov codes,#0        ;;;;;0
lcall writeleft
mov column4,#0
mov pagef4,#4
mov codes,#17       ;;;;;;;; 日
lcall writeright2
;************************** 笨小孩制作，860822
lcall a26
lcall a27
lcall a28
lcall a29
lcall a30
lcall a31
lcall a32
lcall a33
lcall a34
lcall a35
lcall a36
;*************************************************固定显示字符结束
        MOV DAY,#01H                ;初始日期设为08年1月1日星期一
        MOV MONTH,#01H
        MOV YEARL,#08H
        LCALL SETDS1302    ;设置DS1302初始时间
        LCALL GET1302      ;从DS1302读取时间
        LCALL DISPLAY     ;数码显示子程序
        MOV R3,#4        ;循环20次到一秒
        SETB EA
        SETB EX0
        setb IT0
        SETB EX1
        SETB IT1
LP1:    JNB P3.1 ,QQ0     ;当p3.1口为低电平时跳过读取时间子程序
        lJMP QQ2
QQ0:    MOV TH0,#03CH
        MOV TL0,#0B0H
        SETB TR0
        MOV 93H,#0
        LCALL NIU ;将调整后的时间放入时 分 秒 星期 年 月 日寄存器中
        LCALL SETDS1302    ;设置DS1302初始时间
        LCALL GET1302      ;从DS1302读取时间
        LCALL DISPLAY     ;用12864显示
QQ2:    JBC TF0,QQ1
        lJMP LP1
QQ1:    MOV TH0,#03CH
        MOV TL0,#0B0H
        LCALL GET1302                 ;每过50Ms从DS1302读取一次时间
        LCALL DISPLAY
;************************************节日控制程序开始，所有公历节日都能显示
MOV A,49H
CJNE A,#01H,ZZ0
MOV A,48H
CJNE A,#01H,VV0
MOV 71H,#19
LCALL A8
MOV 70H,#18
LCALL A7
MOV 92H,#210
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
VV0:CJNE A,#15H,SS0
MOV 70H,#20
LCALL A7
MOV 71H,#21
LCALL A8
MOV 92H,#210
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
SS0:LCALL HAHA
LJMP QQQ
ZZ0:CJNE A,#02H,ZZ1
MOV A,48H
CJNE A,#14H,vv4
MOV 70H,#22
LCALL A7
MOV 71H,#23
LCALL A8
MOV 92H,#210
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
vv4:CJNE A,#02H,vv5
MOV 70H,#53
LCALL A7
MOV 71H,#54
LCALL A8
MOV 92H,#55
LCALL A40
MOV 91H,#56
LCALL A41
LJMP QQQ
vv5:CJNE A,#10H,SS99
MOV 70H,#41
LCALL A7
MOV 71H,#57
LCALL A8
MOV 92H,#58
LCALL A40
MOV 91H,#59
LCALL A41
LJMP QQQ
SS99:LCALL HAHA
LJMP QQQ
YOU0:LJMP ZZ2
ZZ1:CJNE A,#03H,YOU0
MOV A,48H
CJNE A,#08H,VV6
MOV 70H,#24
LCALL A7
MOV 71H,#25
LCALL A8
MOV 92H,#210
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
VV6:CJNE A,#01H,VV7
MOV 70H,#41
LCALL A7
MOV 71H,#57
LCALL A8
MOV 92H,#60
LCALL A40
MOV 91H,#61
LCALL A41
LJMP QQQ
VV7:CJNE A,#03H,VV8
MOV 70H,#62
LCALL A7
MOV 71H,#41
LCALL A8
MOV 92H,#63
LCALL A40
MOV 91H,#64
LCALL A41
LJMP QQQ
VV8:CJNE A,#05H,VV9
MOV 70H,#65
LCALL A7
MOV 71H,#66
LCALL A8
MOV 92H,#67
LCALL A40
MOV 91H,#68
LCALL A41
LJMP QQQ
VV9:CJNE A,#12H,VV10
MOV 70H,#69
LCALL A7
MOV 71H,#70
LCALL A8
MOV 92H,#210
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
VV10:CJNE A,#14H,VV11
MOV 70H,#41
LCALL A7
MOV 71H,#57
LCALL A8
MOV 92H,#71
LCALL A40
MOV 91H,#72
LCALL A41
LJMP QQQ
VV11:CJNE A,#15H,VV12
MOV 70H,#73
LCALL A7
MOV 71H,#74
LCALL A8
MOV 92H,#75
LCALL A40
MOV 91H,#76
LCALL A41
LJMP QQQ
VV12:CJNE A,#17H,VV13
MOV 70H,#41
LCALL A7
MOV 71H,#57
LCALL A8
MOV 92H,#77
LCALL A40
MOV 91H,#60
LCALL A41
LJMP QQQ
VV13:CJNE A,#21H,VV14
MOV 70H,#53
LCALL A7
MOV 71H,#54
LCALL A8
MOV 92H,#78
LCALL A40
MOV 91H,#79
LCALL A41
LJMP QQQ
VV14:CJNE A,#22H,VV15
MOV 70H,#53
LCALL A7
MOV 71H,#54
LCALL A8
MOV 92H,#80
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
VV15:CJNE A,#23H,VV16
MOV 70H,#81
LCALL A7
MOV 71H,#82
LCALL A8
MOV 92H,#210
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
VV16:CJNE A,#24H,VV17
MOV 70H,#83
LCALL A7
MOV 71H,#84
LCALL A8
MOV 92H,#85
LCALL A40
MOV 91H,#86
LCALL A41
LJMP QQQ
VV17:CJNE A,#25H,SS1
MOV 70H,#87
LCALL A7
MOV 71H,#62
LCALL A8
MOV 92H,#39
LCALL A40
MOV 91H,#88
LCALL A41
LJMP QQQ
SS1:LCALL HAHA
LJMP QQQ
YOU1:LJMP ZZ3
ZZ2:CJNE A,#04H,YOU1
MOV A,48H
CJNE A,#01H,VV1
MOV 70H,#26
LCALL A7
MOV 71H,#27
LCALL A8
MOV 92H,#210
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
VV1:CJNE A,#04H,VV18
MOV 70H,#28
LCALL A7
MOV 71H,#29
LCALL A8
MOV 92H,#210
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
VV18:CJNE A,#07H,VV19
MOV 70H,#53
LCALL A7
MOV 71H,#54
LCALL A8
MOV 92H,#89
LCALL A40
MOV 91H,#90
LCALL A41
LJMP QQQ
VV19:CJNE A,#22H,VV20
MOV 70H,#53
LCALL A7
MOV 71H,#54
LCALL A8
MOV 92H,#56
LCALL A40
MOV 91H,#91
LCALL A41
LJMP QQQ
VV20:CJNE A,#23H,SS2
MOV 70H,#92
LCALL A7
MOV 71H,#93
LCALL A8
MOV 92H,#94
LCALL A40
MOV 91H,#75
LCALL A41
LJMP QQQ
SS2:LCALL HAHA
LJMP QQQ
YOU2:LJMP ZZ4
ZZ3:CJNE A,#05H,YOU2
MOV A,48H
CJNE A,#01H,VV2
MOV 70H,#30
LCALL A7
MOV 71H,#31
LCALL A8
MOV 92H,#210
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
VV2:CJNE A,#04H,VV3
MOV 70H,#32
LCALL A7
MOV 71H,#33
LCALL A8
MOV 92H,#210
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
VV3:CJNE A,#11H,VV21
MOV 70H,#34
LCALL A7
MOV 71H,#35
LCALL A8
MOV 92H,#210
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
VV21:CJNE A,#05H,VV22
MOV 70H,#95
LCALL A7
MOV 71H,#96
LCALL A8
MOV 92H,#83
LCALL A40
MOV 91H,#204
LCALL A41
LJMP QQQ
VV22:CJNE A,#08H,VV23
MOV 70H,#97
LCALL A7
MOV 71H,#98
LCALL A8
MOV 92H,#99
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
VV23:CJNE A,#12H,VV24
MOV 70H,#41
LCALL A7
MOV 71H,#57
LCALL A8
MOV 92H,#100
LCALL A40
MOV 91H,#101
LCALL A41
LJMP QQQ
VV24:CJNE A,#15H,VV25
MOV 70H,#41
LCALL A7
MOV 71H,#57
LCALL A8
MOV 92H,#102
LCALL A40
MOV 91H,#103
LCALL A41
LJMP QQQ
VV25:CJNE A,#17H,VV26
MOV 70H,#41
LCALL A7
MOV 71H,#57
LCALL A8
MOV 92H,#119
LCALL A40
MOV 91H,#120
LCALL A41
LJMP QQQ
VV26:CJNE A,#18H,VV27
MOV 70H,#62
LCALL A7
MOV 71H,#41
LCALL A8
MOV 92H,#121
LCALL A40
MOV 91H,#122
LCALL A41
LJMP QQQ
VV27:CJNE A,#20H,VV28
MOV 70H,#123
LCALL A7
MOV 71H,#90
LCALL A8
MOV 92H,#124
LCALL A40
MOV 91H,#125
LCALL A41
LJMP QQQ
VV28:CJNE A,#23H,VV29
MOV 70H,#41
LCALL A7
MOV 71H,#57
LCALL A8
MOV 92H,#126
LCALL A40
MOV 91H,#127
LCALL A41
LJMP QQQ
VV29:CJNE A,#31H,ss3
MOV 70H,#53
LCALL A7
MOV 71H,#54
LCALL A8
MOV 92H,#128
LCALL A40
MOV 91H,#129
LCALL A41
LJMP QQQ
SS3:LCALL HAHA
LJMP QQQ
YOU3:LJMP ZZ10
ZZ4:CJNE A,#06H,YOU3
MOV A,48H
CJNE A,#15H,VV30
MOV 70H,#36
LCALL A7
MOV 71H,#35
LCALL A8
MOV 92H,#210
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
VV30:CJNE A,#01H,VV31
MOV 70H,#41
LCALL A7
MOV 71H,#57
LCALL A8
MOV 92H,#131
LCALL A40
MOV 91H,#132
LCALL A41
LJMP QQQ
VV31:CJNE A,#17H,VV32
MOV 70H,#83
LCALL A7
MOV 71H,#204
LCALL A8
MOV 92H,#133
LCALL A40
MOV 91H,#134
LCALL A41
LJMP QQQ
VV32:CJNE A,#23H,VV33
MOV 70H,#135
LCALL A7
MOV 71H,#79
LCALL A8
MOV 92H,#136
LCALL A40
MOV 91H,#137
LCALL A41
LJMP QQQ
VV33:CJNE A,#25H,VV34
MOV 70H,#62
LCALL A7
MOV 71H,#41
LCALL A8
MOV 92H,#138
LCALL A40
MOV 91H,#56
LCALL A41
LJMP QQQ
VV34:CJNE A,#26H,SS4
MOV 70H,#41
LCALL A7
MOV 71H,#57
LCALL A8
MOV 92H,#139
LCALL A40
MOV 91H,#140
LCALL A41
LJMP QQQ
SS4:LCALL HAHA
LJMP QQQ
YOU4:LJMP ZZ5
ZZ10:CJNE A,#07H,YOU4
MOV A,48H
CJNE A,#01H,VV35
MOV 70H,#141
LCALL A7
MOV 71H,#142
LCALL A8
MOV 92H,#106
LCALL A40
MOV 91H,#107
LCALL A41
LJMP QQQ
VV35:CJNE A,#02H,VV36
MOV 70H,#143
LCALL A7
MOV 71H,#88
LCALL A8
MOV 92H,#144
LCALL A40
MOV 91H,#145
LCALL A41
LJMP QQQ
VV36:CJNE A,#07H,VV37
MOV 70H,#146
LCALL A7
MOV 71H,#147
LCALL A8
MOV 92H,#67
LCALL A40
MOV 91H,#68
LCALL A41
LJMP QQQ
VV37:CJNE A,#11H,VV38
MOV 70H,#53
LCALL A7
MOV 71H,#54
LCALL A8
MOV 92H,#23
LCALL A40
MOV 91H,#148
LCALL A41
LJMP QQQ
VV38:CJNE A,#30H,SS10
MOV 70H,#149
LCALL A7
MOV 71H,#150
LCALL A8
MOV 92H,#24
LCALL A40
MOV 91H,#25
LCALL A41
LJMP QQQ
SS10:LCALL HAHA
LJMP QQQ
YOU5:LJMP ZZ6
ZZ5:CJNE A,#08H,YOU5
MOV A,48H
CJNE A,#01H,VV39
MOV 70H,#37
LCALL A7
MOV 71H,#38
LCALL A8
MOV 92H,#210
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
VV39:CJNE A,#08H,VV40
MOV 70H,#153
LCALL A7
MOV 71H,#153
LCALL A8
MOV 92H,#210
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
VV40:CJNE A,#15H,SS5
MOV 70H,#146
LCALL A7
MOV 71H,#147
LCALL A8
MOV 92H,#154
LCALL A40
MOV 91H,#155
LCALL A41
LJMP QQQ
SS5:LCALL HAHA
LJMP QQQ
YOU6:LJMP ZZ7
ZZ6:CJNE A,#09H,YOU6
MOV A,48H
CJNE A,#10H,VV41
MOV 70H,#39
LCALL A7
MOV 71H,#40
LCALL A8
MOV 92H,#210
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
VV41:CJNE A,#08H,VV42
MOV 70H,#41
LCALL A7
MOV 71H,#57
LCALL A8
MOV 92H,#109
LCALL A40
MOV 91H,#110
LCALL A41
LJMP QQQ
VV42:CJNE A,#16H,VV43
MOV 70H,#41
LCALL A7
MOV 71H,#57
LCALL A8
MOV 92H,#111
LCALL A40
MOV 91H,#112
LCALL A41
LJMP QQQ
VV43:CJNE A,#20H,VV44
MOV 70H,#41
LCALL A7
MOV 71H,#57
LCALL A8
MOV 92H,#63
LCALL A40
MOV 91H,#113
LCALL A41
LJMP QQQ
VV44:CJNE A,#27H,VV45
MOV 70H,#53
LCALL A7
MOV 71H,#54
LCALL A8
MOV 92H,#114
LCALL A40
MOV 91H,#115
LCALL A41
LJMP QQQ
VV45:CJNE A,#28H,vv75
MOV 70H,#116
LCALL A7
MOV 71H,#117
LCALL A8
MOV 92H,#46
LCALL A40
MOV 91H,#90
LCALL A41
LJMP QQQ
VV75:CJNE A,#18H,ss6
LCALL A42
LCALL A43
LCALL A44
LCALL A45
MOV 92H,#205
LCALL A40
MOV 91H,#199
LCALL A41
LJMP QQQ
SS6:LCALL HAHA
LJMP QQQ
YOU7:LJMP ZZ8
ZZ7:CJNE A,#10H,YOU7
MOV A,48H
CJNE A,#01H,VV46
MOV 70H,#41
LCALL A7
MOV 71H,#42
LCALL A8
MOV 92H,#210
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
VV46:CJNE A,#04H,VV47
MOV 70H,#53
LCALL A7
MOV 71H,#54
LCALL A8
MOV 92H,#31
LCALL A40
MOV 91H,#118
LCALL A41
LJMP QQQ
VV47:CJNE A,#06H,VV48
MOV 70H,#156
LCALL A7
MOV 71H,#23
LCALL A8
MOV 92H,#210
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
VV48:CJNE A,#08H,VV49
MOV 70H,#53
LCALL A7
MOV 71H,#54
LCALL A8
MOV 92H,#157
LCALL A40
MOV 91H,#158
LCALL A41
LJMP QQQ
VV49:CJNE A,#09H,VV50
MOV 70H,#53
LCALL A7
MOV 71H,#54
LCALL A8
MOV 92H,#159
LCALL A40
MOV 91H,#160
LCALL A41
LJMP QQQ
VV50:CJNE A,#10H,VV51
MOV 70H,#161
LCALL A7
MOV 71H,#162
LCALL A8
MOV 92H,#163
LCALL A40
MOV 91H,#164
LCALL A41
LJMP QQQ
VV51:CJNE A,#13H,VV52
MOV 70H,#53
LCALL A7
MOV 71H,#54
LCALL A8
MOV 92H,#165
LCALL A40
MOV 91H,#166
LCALL A41
LJMP QQQ
VV52:CJNE A,#14H,VV53
MOV 70H,#53
LCALL A7
MOV 71H,#54
LCALL A8
MOV 92H,#167
LCALL A40
MOV 91H,#168
LCALL A41
LJMP QQQ
VV53:CJNE A,#15H,VV54
MOV 70H,#41
LCALL A7
MOV 71H,#57
LCALL A8
MOV 92H,#110
LCALL A40
MOV 91H,#23
LCALL A41
LJMP QQQ
VV54:CJNE A,#16H,VV55
MOV 70H,#53
LCALL A7
MOV 71H,#54
LCALL A8
MOV 92H,#169
LCALL A40
MOV 91H,#170
LCALL A41
LJMP QQQ
VV55:CJNE A,#17H,VV56
MOV 70H,#73
LCALL A7
MOV 71H,#171
LCALL A8
MOV 92H,#172
LCALL A40
MOV 91H,#173
LCALL A41
LJMP QQQ
VV56:CJNE A,#22H,VV57
MOV 70H,#174
LCALL A7
MOV 71H,#175
LCALL A8
MOV 92H,#176
LCALL A40
MOV 91H,#177
LCALL A41
LJMP QQQ
VV57:CJNE A,#24H,VV58
MOV 70H,#178
LCALL A7
MOV 71H,#179
LCALL A8
MOV 92H,#41
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
VV58:CJNE A,#31H,SS7
MOV 70H,#53
LCALL A7
MOV 71H,#54
LCALL A8
MOV 92H,#180
LCALL A40
MOV 91H,#181
LCALL A41
LJMP QQQ
SS7:LCALL HAHA
LJMP QQQ
YOU8:LJMP ZZ9
ZZ8:CJNE A,#11H,YOU8
MOV A,48H
CJNE A,#27H,VV59
MOV 70H,#43
LCALL A7
MOV 71H,#44
LCALL A8
MOV 92H,#210
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
VV59:CJNE A,#08H,VV60
MOV 70H,#182
LCALL A7
MOV 71H,#41
LCALL A8
MOV 92H,#144
LCALL A40
MOV 91H,#145
LCALL A41
LJMP QQQ
VV60:CJNE A,#09H,VV61
MOV 70H,#73
LCALL A7
MOV 71H,#83
LCALL A8
MOV 92H,#87
LCALL A40
MOV 91H,#62
LCALL A41
LJMP QQQ
VV61:CJNE A,#10H,VV62
MOV 70H,#53
LCALL A7
MOV 71H,#54
LCALL A8
MOV 92H,#32
LCALL A40
MOV 91H,#8
LCALL A41
LJMP QQQ
VV62:CJNE A,#14H,VV63
MOV 70H,#183
LCALL A7
MOV 71H,#184
LCALL A8
MOV 92H,#86
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
VV63:CJNE A,#17H,VV64
MOV 70H,#53
LCALL A7
MOV 71H,#54
LCALL A8
MOV 92H,#123
LCALL A40
MOV 91H,#90
LCALL A41
LJMP QQQ
VV64:CJNE A,#20H,SS8
MOV 70H,#185
LCALL A7
MOV 71H,#186
LCALL A8
MOV 92H,#8
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
SS8:LCALL HAHA
LJMP QQQ
YOU9:LJMP SS9
ZZ9:CJNE A,#12H,YOU9
MOV A,48H
CJNE A,#25H,VV65
MOV 70H,#45
LCALL A7
MOV 71H,#46
LCALL A8
MOV 92H,#210
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
VV65:CJNE A,#01H,VV66
MOV 70H,#191
LCALL A7
MOV 71H,#192
LCALL A8
MOV 92H,#86
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
VV66:CJNE A,#03H,VV67
MOV 70H,#122
LCALL A7
MOV 71H,#193
LCALL A8
MOV 92H,#23
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
VV67:CJNE A,#08H,VV68
MOV 70H,#131
LCALL A7
MOV 71H,#132
LCALL A8
MOV 92H,#194
LCALL A40
MOV 91H,#157
LCALL A41
LJMP QQQ
VV68:CJNE A,#09H,VV69
MOV 70H,#53
LCALL A7
MOV 71H,#54
LCALL A8
MOV 92H,#196
LCALL A40
MOV 91H,#91
LCALL A41
LJMP QQQ
VV69:CJNE A,#10H,VV70
MOV 70H,#53
LCALL A7
MOV 71H,#54
LCALL A8
MOV 92H,#23
LCALL A40
MOV 91H,#197
LCALL A41
LJMP QQQ
VV70:CJNE A,#12H,VV71
MOV 70H,#198
LCALL A7
MOV 71H,#87
LCALL A8
MOV 92H,#205
LCALL A40
MOV 91H,#199
LCALL A41
LJMP QQQ
VV71:CJNE A,#13H,VV72
MOV 70H,#200
LCALL A7
MOV 71H,#201
LCALL A8
MOV 92H,#202
LCALL A40
MOV 91H,#203
LCALL A41
LJMP QQQ
VV72:CJNE A,#20H,VV73
MOV 70H,#104
LCALL A7
MOV 71H,#105
LCALL A8
MOV 92H,#106
LCALL A40
MOV 91H,#107
LCALL A41
LJMP QQQ
VV73:CJNE A,#21H,VV74
MOV 70H,#41
LCALL A7
MOV 71H,#57
LCALL A8
MOV 92H,#108
LCALL A40
MOV 91H,#91
LCALL A41
LJMP QQQ
VV74:CJNE A,#24H,ss9
MOV 70H,#151
LCALL A7
MOV 71H,#87
LCALL A8
MOV 92H,#152
LCALL A40
MOV 91H,#210
LCALL A41
LJMP QQQ
ri1:ljmp lp1
ss9:LCALL HAHA
;******************************************节日设置结束
QQQ:    DJNZ R3,SS100                   ;未到1 S继续循环
        LCALL GET_TEMPER              ;每过1s从DS18B20读取一次温度
        mov     R3,#4
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;整点闹铃1分钟同时在最左上角显示铃铛符号,合上闹铃开关可以提前关掉闹铃
        MOV A,46H
        CJNE A,#0,SS100
        LCALL NAO
        LCALL NAO
        LCALL NAO
        LCALL NAO
        LCALL NAO
        mov column3,#0
        mov pagef3,#0
        mov codes,#206          ;开闹铃符号
        lcall writeleft2
        SS100:MOV A,45H
        CJNE A,#59H,RI1
        mov column3,#0
        mov pagef3,#0
        mov codes,#210          ;关闹铃符号
        lcall writeleft2
        LJMP lp1
;************************主程序结束，子程序开始
HAHA:MOV 70H,#151
LCALL A7
MOV 71H,#52
LCALL A8
MOV 92H,#210
LCALL A40
MOV 91H,#210
LCALL A41
RET
NIU:
MOV A,51H
SWAP A
ADD A,50H
MOV 45H,A
mov a,53h
swap a
add a,52h
mov 46h,a
mov a,55h
swap a
add a,54h
mov 47h,a
mov a,57h
swap a
add a,56h
mov 48h,a
mov a,59h
swap a
add a,58h
mov 49h,a
mov a,5dh
swap a
add a,5ch
mov 4bh,a
mov 4ah,5ah
RET
;********************************************中断0开始
xx0:PUSH ACC
clr tr0
MOV A,93H
CJNE A,#0,ZD0000  ;秒低位
inc 50h
LCALL A13
mov A,50H
CJNE A,#10,KK0
MOV 50H,#0
kk0:POP ACC
RETI
ZD0000:CJNE A,#1,ZD001   ;秒高位
inc 51h
lcall a14
MOV A,51H
CJNE A,#10,KK1
MOV 51H,#0
kk1:POP ACC
RETI
ZD001:CJNE A,#2,ZD002      ;分低位
INC 52H
lcall a15
MOV A,52H
CJNE A,#10,KK3
MOV 52H,#0
kk3:POP ACC
RETI
ZD002:CJNE A,#3,ZD003         ;分高位
INC 53H
lcall a16
MOV A,53H
CJNE A,#10,KK4
MOV 53H,#0
inc 52h
kk4:POP ACC
RETI
zd003:CJNE A,#4,ZD004      ;时低位
INC 54H
lcall a17
MOV A,54H
CJNE A,#10,KK5
MOV 54H,#0
kk5:POP ACC
RETI
ZD004:CJNE A,#5,ZD005     ;时高位
INC 55H
lcall a18
MOV A,55H
CJNE A,#9,KK6
MOV 55H,#0
kk6:POP ACC
RETI
ZD005:CJNE A,#6,ZD006       ;星期
INC 5aH
lcall a19
MOV A,5aH
CJNE A,#7,KK7
MOV 5aH,#0
kk7:POP ACC
RETI
ZD006:CJNE A,#7,ZD007      ;日低位
INC 56H
lcall a20
MOV A,56H
CJNE A,#10,KK8
MOV 56H,#0
kk8:POP ACC
RETI
ZD007:CJNE A,#8,ZD008       ;日高位
INC 57H
lcall a21
MOV A,57H
CJNE A,#10,KK9
MOV 57H,#0
kk9:POP ACC
RETI
ZD008:CJNE A,#9,ZD009    ;月低位
INC 58H
lcall a22
MOV A,58H
CJNE A,#10,KK10
MOV 58H,#0
kk10:POP ACC
RETI
ZD009:CJNE A,#10,ZD0010   ;月高位
INC 59H
lcall a23
MOV A,59H
CJNE A,#10,KK11
MOV 59H,#0
kk11:POP ACC
RETI
ZD0010:CJNE A,#11,ZD0011  ;年低位
INC 5cH
lcall a24
MOV A,5cH
CJNE A,#10,KK12
MOV 5cH,#0
kk12:POP ACC
RETI
ZD0011:INC 5dH
lcall a25     ;年高位
MOV A,5dH
CJNE A,#10,KK13
MOV 5dH,#0
kk13:POP ACC
RETI
;******************************************************中断1开始
XX1:PUSH ACC
INC 93H
MOV A,02H
CJNE A,#13,ZD10
MOV 93H,#0
ZD10:pop acc
reti
;温度显示子程序-------------------------------------------------------------------------------
INIT_1820: SETB P3.7
CLR P3.7
MOV R1,#3
TSR1: MOV R0,#107
DJNZ R0,$
DJNZ R1,TSR1
SETB P3.7
MOV R0,#25H
TSR2: JNB P3.7,TSR3
DJNZ R0,TSR2
LJMP TSR4
TSR3: SETB FLAG1
LJMP TSR5
TSR4: CLR FLAG1
LJMP TSR7
TSR5: MOV R0,#117
TSR6: DJNZ R0,TSR6
TSR7: SETB P3.7
RET
GET_TEMPER: SETB P3.7
LCALL INIT_1820
JB FLAG1,TSS2
RET
TSS2: MOV A,#0CCH
LCALL WRITE_1820
MOV A,#44H
LCALL WRITE_1820
LCALL DISPLAY1
LCALL INIT_1820
MOV A,#0CCH
LCALL WRITE_1820
MOV A,#0BEH
LCALL WRITE_1820
LCALL READ_18200
RET
WRITE_1820: MOV R2,#8
CLR C
WR1: CLR P3.7
MOV R3,#6
DJNZ R3,$
RRC A
MOV P3.7,C
MOV R3,#23
DJNZ R3,$
SETB P3.7
NOP
DJNZ R2,WR1
SETB P3.7
RET
READ_18200: MOV R5,#2
MOV R1,#41h
RE00: MOV R2,#8
RE01: CLR C
SETB P3.7
CLR P3.7
SETB P3.7
MOV R3,#7
RE10: DJNZ R3,RE10
MOV C,P3.7
MOV R3,#23
RE20: DJNZ R3,RE20
RRC A
DJNZ R2,RE01
MOV @R1,A
DEC R1
DJNZ R5,RE00
RET
DISPLAY1:MOV A,40H
JB ACC.7,ZF1
mov column4,#16
mov pagef4,#4
mov codes,#250
lcall writeright2
ljmp zhijie
ZF1:mov column4,#16
mov pagef4,#4
mov codes,#16       ;;;;;;;;-
lcall writeright2
mov a,40h
cpl a
mov dph,a
mov a,41h
cpl a
mov dpl,a
inc dptr
mov 40h,dph
mov 41h,dpl
zhijie:MOV A,40H
SWAP A
ANL A,#0F0H
MOV 40H,A
MOV A,41H
SWAP A
ANL A,#0FH
ADD A,40H
MOV 41H,A
MOV B,#10
DIV AB
MOV b_bit,A
MOV a_bit,B
mov column2,#32
mov pagef2,#4
mov codes,b_bit      ;;;;;;;;;十位
lcall writeright
mov column2,#40
mov pagef2,#4
mov codes,a_bit       ;;;;;;;个位
lcall writeright
RET
;---------------------------------------------------------------------------------------------------
;数码显示子程序
DISPLAY:
;*******************************************
;显示秒
        MOV     A,SECOND
        ANL     A,#0FH
        MOV 50H,A
        LCALL A13
        MOV     A,SECOND
        SWAP    A
        ANL     A,#07H
        MOV 51H,A
        LCALL A14
;*******************************************
;显示分
        MOV     A,MINUTE
        ANL     A,#0FH
        MOV 52H,A
        LCALL A15
        MOV     A,MINUTE
        SWAP    A
        ANL     A,#07H
        MOV 53H,A
        LCALL A16
;*******************************************
;显示小时
        MOV     A,HOUR
        ANL     A,#0FH
        MOV 54H,A
        LCALL A17
        MOV     A,HOUR
        SWAP    A
        ANL     A,#03H
        MOV 55H,A
        LCALL A18
 ;显示星期
        MOV     A,WEEK
        MOV 5AH,A
        LCALL A19
 ;显示日
        MOV     A,DAY
        ANL     A,#0FH
        MOV 56H,A
        LCALL A20
        MOV     A,DAY
        SWAP    A
        ANL     A,#03H
        MOV 57H,A
        LCALL A21
 ;显示月
        MOV     A,MONTH
        ANL     A,#0FH
        MOV 58H,A
        LCALL A22
        MOV     A,MONTH
        SWAP    A
        ANL     A,#03H
        MOV 59H,A
        LCALL A23
 ;显示年
        MOV     A,YEARL
        ANL     A,#0FH
         MOV 5CH,A
        LCALL A24
        MOV     A,YEARL
        SWAP    A
        ANL     A,#0FH
         MOV 5DH,A
        LCALL A25
        RET
;---------------------------------------------------------------------------------------------------
;设置DS1302初始时间,并启动计时
SETDS1302:
        CLR     T_RST
        nop
        CLR     T_CLK
        nop
        SETB    T_RST
        nop
        MOV     B,#8EH          ;写控制命令字
        LCALL   INPUTBYTE
        MOV     B,#00H          ;写保护关闭
        LCALL   INPUTBYTE
        SETB    T_CLK
        nop
        CLR     T_RST
        MOV     R0,#SECOND      ;内存中的时间首地址
        MOV     R1,#80H         ;DS1302中的时间首地址
        MOV     R7,#7           ;字节数
SETLOOP:
        CLR     T_RST
        nop
        CLR     T_CLK
        nop
        SETB    T_RST
        nop
        MOV     B,R1            ;写命令字
        LCALL   INPUTBYTE
        MOV     A,@R0           ;设置时间
        MOV     B,A
        LCALL   INPUTBYTE
        INC     R0
        INC     R1
        INC     R1
        SETB    T_CLK
        nop
        CLR     T_RST
        nop
        DJNZ    R7,SETLOOP
        CLR     T_RST
        nop
        CLR     T_CLK
        nop
        SETB    T_RST
        nop
        MOV     B,#8EH
        LCALL   INPUTBYTE
        MOV     B,#80H          ;开写保护
        LCALL   INPUTBYTE
        SETB    T_CLK
        nop
        CLR     T_RST
        nop
        RET
;---------------------------------------------------------------------------------------------------
;从DS1302读取时间
GET1302:
        MOV     R0,#SECOND
        MOV     R1,#81H        ;DS1302中读时间的首地址
        MOV     R7,#7
GETLOOP:
        CLR     T_RST
        nop
        CLR     T_CLK
        nop
        SETB    T_RST
        nop
        MOV     B,R1
        LCALL   INPUTBYTE       ;写命令字
        LCALL   OUTPUTBYTE      ;读时间
        MOV     @R0,A           ;将从DS1302中读取的时间从内存中保存
        INC     R0              ;修改地址指针
        INC     R1
        INC     R1
        SETB    T_CLK
        nop
        CLR     T_RST
        nop
        DJNZ    R7,GETLOOP
        RET
;---------------------------------------------------------------------------------------------------
;向DS1302写一个字节
INPUTBYTE:
        MOV     R4,#8
INPUTLOOP:
        MOV     A,B
        RRC     A
        MOV     B,A
        MOV     T_IO,C
        SETB    T_CLK
        NOP
        ;NOP
        ;NOP
        CLR     T_CLK
        DJNZ    R4,INPUTLOOP
        RET
;---------------------------------------------------------------------------------------------------
;从DS1302读一个字节
OUTPUTBYTE:
        clr     a
        clr     c
        MOV     R4,#8
OUTPUTLOOP:
        NOP
        MOV     C,T_IO
        RRC     A
        SETB    T_CLK
        NOP
        CLR     T_CLK
        DJNZ    R4,OUTPUTLOOP
        RET
writeleft2:  ; 左半屏写入16*16汉字子程序
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
mov a,codes
mov b,#32
mul ab
add a,dpl
mov dpl,a
mov a,b
addc a,dph
mov dph,a
lp3:mov a,#00h
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
over3:ret
writeright2:  ; 右半屏写入16*16汉字子程序
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
mov a,codes
mov b,#32
mul ab
add a,dpl
mov dpl,a
mov a,b
addc a,dph
mov dph,a
lp4:mov a,#00h
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
over4:ret
writeleft:  ; 左半屏写入8*16数字子程序
mov dptr,#table1
push column
mov cpage,#2
mov ccolumn,#0
mov a,pagef
anl a,#07h
orl a,#0b8h
mov com,a
lcall prm0
mov a,column
anl a,#3fh
orl a,#40h
mov com,a
lcall prm0
mov a,codes
mov b,#16
mul ab
add a,dpl
mov dpl,a
mov a,b
addc a,dph
mov dph,a
lOOp1:mov a,#00h
movc a,@a+dptr
mov dat,a
lcall prm1
inc ccolumn
mov a,ccolumn
inc dptr
cjne a,#8,lOOp1
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
ljmp lOOp1
over1:
ret
writeright:  ; 右半屏写入8*16数字子程序
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
mov a,codes
mov b,#16
mul ab
add a,dpl
mov dpl,a
mov a,b
addc a,dph
mov dph,a
lOOp2:mov a,#00h
movc a,@a+dptr
mov dat,a
lcall prr1
inc ccolumn2
mov a,ccolumn2
inc dptr
cjne a,#8,lOOp2
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
ljmp lOOp2
over2:
ret
PRM0:CLR CSA  ;写指令代码子程序(左)
SETB CSB
CLR rs
SETB rw
PRM01:MOV P0,#0FFH
SETB E
MOV A,P0
CLR E
JB  ACC.7,PRM01
CLR rw
MOV P0,COM
SETB E
CLR E
RET
PRM1:CLR CSA ;写显示数据子程序(左)
SETB CSB
CLR rs
SETB rw
PRM11:MOV P0,#0FFH
SETB E
MOV A,P0
CLR E
JB  ACC.7,PRM11
SETB rs
CLR rw
MOV P0,DAT
SETB E
CLR E
RET
PRR0:CLR CSB ;写指令代码子程序(右)
SETB CSA
CLR rs
SETB rw
PRR01:MOV P0,#0FFH
SETB E
MOV A,P0
CLR E
JB  ACC.7,PRR01
CLR rw
MOV P0,COM
SETB E
CLR E
RET
PRR1:CLR CSB ;写显示数据子程序(右)
SETB CSA
CLR rs
SETB rw
PRR11:MOV P0,#0FFH
SETB E
MOV A,P0
CLR E
JB  ACC.7,PRR11
SETB rs
CLR rw
MOV P0,DAT
SETB E
CLR E
RET
INT:MOV COM,#0C0H ;初始化子程序,设置显示起始行为第一行
LCALL PRM0
LCALL PRR0
MOV COM,#3FH  ;开显示设置
LCALL PRM0
LCALL PRR0
RET
CLEAR:MOV R4,#00H ;清屏子程序
CLEAR1:MOV A,R4
ORL A,#0B8H
MOV COM,A
LCALL PRM0
LCALL PRR0
MOV COM,#40H
LCALL PRM0
LCALL PRR0
MOV R3,#40H
CLEAR2:MOV DAT,#00H
LCALL PRM1
LCALL PRR1
DJNZ R3,CLEAR2
INC R4
CJNE R4,#08H,CLEAR1
RET
;***********************************************节日子程序
A7:mov column3,#0
mov pagef3,#4
mov codes,70H
lcall writeleft2
RET
A8:mov column3,#16
mov pagef3,#4
mov codes,71H
lcall writeleft2
RET
A40:mov column3,#32
mov pagef3,#4
mov codes,92H
lcall writeleft2
RET
A41:mov column3,#48
mov pagef3,#4
mov codes,91H
lcall writeleft2
RET
A42:mov column,#0
mov pagef,#4
mov codes,#9           ;;;;;;;9
lcall writeleft
RET
A43:mov column3,#8
mov pagef3,#4
mov codes,#207        ;;;;;.
lcall writeleft2
RET
A44:mov column,#16
mov pagef,#4
mov codes,#1           ;;;;;;;1
lcall writeleft
RET
A45:mov column,#24
mov pagef,#4
mov codes,#8        ;;;;;8
lcall writeleft
RET
 ;**********************************************************
A13:mov column2,#56
mov pagef2,#2
MOV CODES,50H    ;秒低位
lcall writeright
RET
A14:mov column2,#48
mov pagef2,#2
MOV CODES,51H    ;秒高位
lcall writeright
RET
A15:mov column2,#24
mov pagef2,#2
MOV CODES,52H      ;分低位
lcall writeright
RET
A16:mov column2,#16
mov pagef2,#2
MOV CODES,53H      ;分高位
lcall writeright
RET
A17:mov column,#56
mov pagef,#2
MOV CODES,54H     ;时低位
lcall writeleft
RET
A18:mov column,#48
mov pagef,#2
MOV CODES,55H     ;时高位
lcall writeleft
RET
A19:mov column3,#32
mov pagef3,#2        ;星期
mov codes,5AH
lcall writeleft2
RET
A20:mov column2,#40
mov pagef2,#0       ;日低位
mov codes,56H
lcall writeright
RET
A21:mov column2,#32
mov pagef2,#0
mov codes,57H       ;日高位       
lcall writeright
RET
A22:mov column2,#8
mov pagef2,#0           ;月低位
mov codes,58H
lcall writeright
RET
A23:mov column2,#0
mov pagef2,#0        ;月高位
mov codes,59H
lcall writeright
RET
A24:mov column,#40
mov pagef,#0          ;年低位
mov codes,5CH
lcall writeleft
RET
A25:mov column,#32
mov pagef,#0
mov codes,5DH        ;年高位
lcall writeleft
RET
;*******************************第四行字显示代码
a26:mov column3,#0
mov pagef3,#6
mov codes,#47
lcall writeleft2
ret
a27:mov column3,#16
mov pagef3,#6
mov codes,#48
lcall writeleft2
ret
a28:mov column3,#32
mov pagef3,#6
mov codes,#49
lcall writeleft2
ret
a29:mov column3,#48
mov pagef3,#6
mov codes,#50
lcall writeleft2
ret
a30:mov column4,#0
mov pagef4,#6
mov codes,#51
lcall writeright2
ret
;860822
a31:mov column2,#16
mov pagef2,#6
mov codes,#8
lcall writeright
ret
a32:mov column2,#24
mov pagef2,#6
mov codes,#6
lcall writeright
ret
a33:mov column2,#32
mov pagef2,#6
mov codes,#0
lcall writeright
ret
a34:mov column2,#40
mov pagef2,#6
mov codes,#8
lcall writeright
ret
a35:mov column2,#48
mov pagef2,#6
mov codes,#2
lcall writeright
ret
a36:mov column2,#54
mov pagef2,#6
mov codes,#2
lcall writeright
ret
NAO:MOV R4,#50
SETB P3.0
LING:LCALL DELAY
CPL P3.0
DEC R4
CJNE R4,#0,LING
RET
DELAY:MOV R7,#20
DD:MOV R6,#10
DJNZ R6,$
DJNZ R7,DD
RET
;*************************************字模表
table1: ;数字字模表
DB   0F0h, 0F8h,  0Ch,  04h
DB    04h,  0Ch, 0F8h, 0F0h        ;0
DB    0Fh,  1Fh,  30h,  20h
DB    20h,  30h,  1Fh,  0Fh
DB    00h,  00h,  08h, 0F8h         ;1
DB   0FCh,  00h,  00h,  00h
DB    00h,  00h,  20h,  3Fh
DB    3Fh,  20h,  00h,  00h
DB    30h,  38h,  0Ch,  04h
DB    04h,  0Ch, 0F8h, 0F0h
DB    20h,  30h,  38h,  2Ch          ;2
DB    26h,  23h,  21h,  38h
DB    10h,  18h,  0Ch,  84h
DB    84h, 0CCh,  78h,  30h
DB    08h,  18h,  30h,  20h
DB    20h,  31h,  1Fh,  0Eh         ;3
DB    00h, 0C0h,  70h,  18h
DB   0FCh, 0FEh,  00h,  00h
DB    07h,  05h,  04h,  24h
DB    3Fh,  3Fh,  24h,  04h          ;4
DB   0FCh, 0FCh, 0C4h,  44h
DB    44h, 0C4h,  84h,  04h
DB    08h,  18h,  30h,  20h
DB    20h,  30h,  1Fh,  0Fh          ;5
DB   0F0h, 0F8h,  8Ch,  44h
DB    44h, 0CCh,  98h,  10h
DB    0Fh,  1Fh,  30h,  20h
DB    20h,  30h,  1Fh,  0Fh          ;6
DB    1Ch,  0Ch,  0Ch,  0Ch
DB   0CCh, 0ECh,  3Ch,  1Ch
DB    00h,  00h,  3Ch,  3Fh
DB    03h,  00h,  00h,  00h         ;7
DB    30h,  78h, 0CCh,  84h
DB    84h, 0CCh,  78h,  30h
DB    0Eh,  1Fh,  31h,  20h
DB    20h,  31h,  1Fh,  0Eh          ;8
DB   0F0h, 0F8h,  0Ch,  04h
DB    04h,  0Ch, 0F8h, 0F0h
DB    08h,  19h,  33h,  22h
DB    22h,  33h,  1Fh,  0Fh         ;9
DB   0F0h, 0F8h,  0Ch,  04h
DB    04h,  0Ch, 0F8h, 0F0h        ;0
DB    0Fh,  1Fh,  30h,  20h
DB    20h,  30h,  1Fh,  0Fh
table2:   ;汉字字模表
 db  80h, 80h, 80h, 80h, 80h, 80h, 80h, 80h   ; 一    0
 db  80h, 80h, 80h, 80h, 80h,0C0h, 80h, 00h
 db  00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
 db  00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
 db  00h, 00h, 08h, 08h, 08h, 08h, 08h, 08h   ; 二     1
 db  08h, 08h, 08h, 0Ch, 08h, 00h, 00h, 00h
 db  10h, 10h, 10h, 10h, 10h, 10h, 10h, 10h
 db  10h, 10h, 10h, 10h, 10h, 18h, 10h, 00h
 db  00h, 04h, 84h, 84h, 84h, 84h, 84h, 84h   ; 三            2
 db  84h, 84h, 84h,0C4h, 86h, 04h, 00h, 00h
 db  20h, 20h, 20h, 20h, 20h, 20h, 20h, 20h
 db  20h, 20h, 20h, 20h, 20h, 30h, 20h, 00h
 db  00h,0FCh, 04h, 04h, 04h,0FCh, 04h, 04h    ;四           3
 db  04h,0FCh, 04h, 04h, 04h,0FEh, 04h, 00h
 db  00h, 7Fh, 20h, 28h, 24h, 23h, 20h, 20h
 db  20h, 21h, 22h, 22h, 22h, 7Fh, 00h, 00h
 db  00h, 04h, 84h, 84h, 84h, 84h,0FCh, 84h     ;五         4
 db  84h, 84h, 84h,0C4h, 86h, 84h, 00h, 00h
 db  40h, 40h, 40h, 40h, 78h, 47h, 40h, 40h
 db  40h, 40h, 40h, 7Fh, 40h, 60h, 40h, 00h
 db  20h, 20h, 20h, 20h, 20h, 22h, 2Ch, 38h      ;六         5
 db  20h, 20h, 20h, 20h, 20h, 30h, 20h, 00h
 db  00h, 40h, 20h, 18h, 06h, 03h, 00h, 00h
 db  00h, 01h, 02h, 0Ch, 38h, 70h, 00h, 00h
 db  00h, 00h, 00h,0FEh, 82h, 82h, 82h, 82h      ;"日",         6
 db  82h, 82h, 82h,0FFh, 02h, 00h, 00h, 00h
 db  00h, 00h, 00h, 7Fh, 20h, 20h, 20h, 20h
 db  20h, 20h, 20h, 7Fh, 00h, 00h, 00h, 00h
 db  80h, 80h, 80h, 80h, 80h, 80h, 80h, 80h   ; 一    7
 db  80h, 80h, 80h, 80h, 80h,0C0h, 80h, 00h
 db  00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
 db  00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
 db  00h, 20h, 10h,0CCh, 47h, 44h, 44h,0FCh ; 年  8
 db  44h, 44h, 44h, 64h, 46h, 04h, 00h, 00h
 db  04h, 04h, 04h, 07h, 04h, 04h, 04h,0FFh
 db  04h, 04h, 04h, 04h, 04h, 06h, 04h, 00h
 db  00h, 00h, 00h, 00h,0FEh, 22h, 22h, 22h ; 月    9
 db  22h, 22h, 22h,0FFh, 02h, 00h, 00h, 00h
 db  00h, 80h, 40h, 30h, 0Fh, 02h, 02h, 02h
 db  02h, 42h, 82h, 7Fh, 00h, 00h, 00h, 00h
 db  00h, 00h, 00h,0FEh, 82h, 82h, 82h, 82h ; 日   10
 db  82h, 82h, 82h,0FFh, 02h, 00h, 00h, 00h
 db  00h, 00h, 00h, 7Fh, 20h, 20h, 20h, 20h
 db  20h, 20h, 20h, 7Fh, 00h, 00h, 00h, 00h
 db  00h, 00h,0BEh, 2Ah, 2Ah, 2Ah, 2Ah,0EAh  ;星  11
 db  2Ah, 2Ah, 2Ah, 2Ah,0BFh, 02h, 00h, 00h
 db  48h, 44h, 4Bh, 49h, 49h, 49h, 49h, 7Fh
 db  49h, 49h, 49h, 4Dh, 49h, 61h, 40h, 00h
 db  00h, 08h,0FFh,0A8h,0A8h,0A8h,0FFh, 08h   ; 期  12
 db  00h,0FEh, 22h, 22h, 22h,0FFh, 02h, 00h
 db  84h, 44h, 37h, 04h, 04h, 14h,0A7h, 44h
 db  24h, 1Fh, 02h, 42h, 82h, 7Fh, 00h, 00h
 db  00h, 00h, 00h, 00h, 00h, 00h, 00h, 30h   ;: 13
 db  30h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
 db  00h, 00h, 00h, 00h, 00h, 00h, 00h, 0Ch
 db  0Ch, 00h, 00h, 00h, 00h, 00h, 00h, 00h
 db  00h, 00h, 00h, 80h, 80h, 80h, 80h,0F0h  ; +     14
 db  80h, 80h, 80h, 80h, 00h, 00h, 00h, 00h
 db  00h, 00h, 00h, 00h, 00h, 00h, 00h, 0Fh
 db  00h, 00h, 00h, 00h, 00h, 00h, 00h, 00H
 db  00h, 00h,0FCh, 24h, 24h, 24h,0FCh,0A5h   ;度  15
 db 0A6h,0A4h,0FCh, 24h, 34h, 26h, 04h, 00h
 db  40h, 20h, 9Fh, 80h, 42h, 42h, 26h, 2Ah
 db  12h, 2Ah, 26h, 42h, 40h,0C0h, 40h, 00h
 db  00h, 00h, 00h, 80h, 80h, 80h, 80h, 80h   ;"一",  16
 db  80h, 80h, 80h, 80h, 80h, 00h, 00h, 00h
 db  00h, 00h, 00h, 01h, 01h, 01h, 01h, 01h
 db  01h, 01h, 01h, 01h, 01h, 00h, 00h, 00h
db  00h, 00h, 00h,0FEh, 82h, 82h, 82h, 82h    ;"日",   17
db  82h, 82h, 82h,0FFh, 02h, 00h, 00h, 00h
db  00h, 00h, 00h, 7Fh, 20h, 20h, 20h, 20h
db  20h, 20h, 20h, 7Fh, 00h, 00h, 00h, 00h
db  20h, 20h, 22h, 22h, 22h,0E2h, 22h, 22h      ;  "元",  18
db  22h,0E2h, 22h, 23h, 22h, 30h, 20h, 00h
db  80h, 80h, 40h, 20h, 18h, 07h, 00h, 00h
db  00h, 3Fh, 40h, 40h, 40h, 40h, 70h, 00h
db  00h, 00h, 00h,0FEh, 42h, 42h, 42h, 42h     ;   "旦",   19
db  42h, 42h, 42h,0FFh, 02h, 00h, 00h, 00h
db  40h, 40h, 40h, 5Fh, 48h, 48h, 48h, 48h
db  48h, 48h, 48h, 5Fh, 40h, 60h, 40h, 00h
db  00h,0FEh, 22h, 22h,0FFh, 42h, 48h, 48h     ;  "腊",    20
db  7Fh, 48h, 48h, 7Fh,0C8h, 68h, 40h, 00h
db  40h, 3Fh, 02h, 82h,0FFh, 00h, 00h,0FFh
db  49h, 49h, 49h, 49h,0FFh, 01h, 00h, 00h
db  00h, 00h, 00h, 00h, 00h,0FCh, 00h, 00h      ;  "八",   21
db  00h,0FEh, 00h, 00h, 00h, 00h, 00h, 00h
db  00h, 40h, 20h, 18h, 07h, 00h, 00h, 00h
db  00h, 00h, 07h, 08h, 30h, 60h, 20h, 00h
db  80h, 70h, 00h,0FFh, 10h, 22h,0AAh,0AAh        ; "情",    22
db 0AAh,0BFh,0AAh,0AAh,0EBh,0A2h, 20h, 00h
db  00h, 00h, 00h,0FFh, 00h, 00h,0FFh, 0Ah
db  0Ah, 0Ah, 4Ah, 8Ah, 7Fh, 00h, 00h, 00h
db  00h, 00h, 00h, 00h, 00h, 00h, 80h, 7Fh       ; "人",      23
db  80h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
db  00h, 80h, 40h, 20h, 10h, 0Ch, 03h, 00h
db  03h, 0Ch, 10h, 20h, 40h,0C0h, 40h, 00h
db  10h, 10h,0F0h, 1Fh, 10h,0F0h, 08h, 08h       ; "妇",      24
db  08h, 08h, 08h, 08h, 08h,0FCh, 08h, 00h
db  40h, 22h, 15h, 08h, 16h, 61h, 20h, 21h
db  21h, 21h, 21h, 21h, 21h, 7Fh, 00h, 00h
db  20h, 20h, 20h, 20h, 20h,0E0h, 3Fh, 20h       ; "女",      25
db  20h, 20h,0E0h, 20h, 20h, 30h, 20h, 00h
db  00h, 80h, 80h, 42h, 45h, 24h, 28h, 10h
db  18h, 24h, 23h, 40h,0C0h, 00h, 00h, 00h
db  00h, 00h, 80h,0BEh,0AAh,0AAh,0AAh,0FEh       ; "愚",    26
db 0AAh,0AAh,0AAh,0BFh,0C2h, 80h, 00h, 00h
db  40h, 30h, 0Fh, 70h, 80h, 84h, 8Eh, 95h
db 0B4h, 86h, 84h,0E8h, 07h, 10h, 60h, 00h
db  00h, 00h, 00h, 00h, 00h, 00h, 80h, 7Fh     ; "人"       27
db  80h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
db  00h, 80h, 40h, 20h, 10h, 0Ch, 03h, 00h
db  03h, 0Ch, 10h, 20h, 40h,0C0h, 40h, 00h
db  10h, 22h, 64h, 0Ch,0C0h, 44h, 54h, 54h      ;   "清",   28
db  54h, 7Fh, 54h, 54h,0D6h, 44h, 40h, 00h
db  04h, 04h,0FEh, 01h, 00h, 00h,0FFh, 15h
db  15h, 15h, 55h, 95h, 7Fh, 01h, 00h, 00h
db  00h,0FCh, 44h, 44h, 44h,0FEh, 04h, 00h    ;  "明",     29
db 0FEh, 22h, 22h, 22h, 22h,0FFh, 02h, 00h
db  00h, 0Fh, 04h, 04h, 04h, 8Fh, 40h, 30h
db  0Fh, 02h, 02h, 42h, 82h, 7Fh, 00h, 00h
db  80h, 64h, 24h, 24h, 24h, 3Fh,0E4h, 24h    ;   "劳",    30
db  24h, 3Fh, 24h,0A4h, 26h,0A4h, 60h, 00h
db  00h, 00h, 80h, 41h, 31h, 0Fh, 01h, 01h
db  41h, 81h, 41h, 3Fh, 01h, 00h, 00h, 00h
db  20h, 24h, 24h,0E4h, 26h, 34h, 20h, 10h     ;  "动",    31
db  10h,0FFh, 10h, 10h, 10h,0F8h, 10h, 00h
db  08h, 1Ch, 0Bh, 08h, 08h, 8Ah, 4Ch, 30h
db  0Ch, 03h, 40h, 80h, 40h, 3Fh, 00h, 00h
db  40h, 44h, 54h, 54h, 54h, 54h, 54h, 7Fh    ;   "青",     32
db  54h, 54h, 54h,0D4h, 56h, 44h, 40h, 00h
db  00h, 00h, 00h,0FFh, 15h, 15h, 15h, 15h
db  15h, 55h, 95h, 7Fh, 01h, 00h, 00h, 00h
db  00h, 20h, 10h,0CCh, 47h, 44h, 44h,0FCh     ; "年",     33
db  44h, 44h, 44h, 64h, 46h, 04h, 00h, 00h
db  04h, 04h, 04h, 07h, 04h, 04h, 04h,0FFh
db  04h, 04h, 04h, 04h, 04h, 06h, 04h, 00h
db  80h, 80h, 80h,0FEh, 82h, 82h, 8Ah, 92h    ;  "母",       34
db 0B2h, 82h, 82h,0FFh, 82h,0C0h, 80h, 00h
db  00h, 00h, 1Fh, 10h, 10h, 10h, 12h, 14h
db  5Ch, 90h, 50h, 3Fh, 10h, 00h, 00h, 00h
db  40h, 44h, 44h, 44h, 4Ch, 54h, 65h,0C6h    ;  "亲",       35
db  64h, 54h, 4Ch, 44h, 46h, 64h, 40h, 00h
db  00h, 42h, 22h, 12h, 1Ah, 42h, 82h, 7Fh
db  02h, 02h, 0Ah, 12h, 33h, 62h, 00h, 00h
db  00h, 10h, 08h, 04h, 22h,0C1h, 00h, 00h    ;   "父",      36
db  00h,0C1h, 32h, 04h, 08h, 18h, 00h, 00h
db  80h, 80h, 40h, 40h, 20h, 10h, 0Bh, 04h
db  0Bh, 10h, 20h, 20h, 40h,0C0h, 40h, 00h
db  04h, 04h, 44h, 74h,0CCh, 10h, 54h, 54h     ;  "建",       37
db  54h,0FFh, 54h, 54h, 7Eh, 14h, 10h, 00h
db  41h, 26h, 18h, 2Eh, 41h, 88h, 89h, 89h
db  89h,0FFh, 89h, 89h, 8Dh,0C8h, 40h, 00h
db  08h, 06h, 12h, 92h, 52h, 32h, 1Eh,0D2h    ;  "军",         38
db  12h, 12h, 12h, 9Ah, 12h, 0Ah, 06h, 00h
db  08h, 08h, 09h, 09h, 09h, 09h, 09h,0FFh
db  09h, 09h, 09h, 09h, 09h, 0Ch, 08h, 00h
db  20h, 24h, 24h,0A4h,0FFh,0A4h,0B4h,0ACh     ;    "教",      39
db  20h, 9Fh, 10h, 10h,0F0h, 18h, 10h, 00h
db  02h, 12h, 51h, 90h, 7Eh, 0Ah, 89h, 40h
db  20h, 1Bh, 04h, 1Bh, 60h,0C0h, 40h, 00h
db  00h,0FCh, 00h, 00h,0FFh, 00h, 02h,0F2h     ;  "师",      40
db  12h, 12h,0FEh, 12h, 12h,0FBh, 12h, 00h
db  00h, 8Fh, 40h, 30h, 0Fh, 00h, 00h, 3Fh
db  00h, 00h,0FFh, 10h, 20h, 1Fh, 00h, 00h
db  00h,0FEh, 02h, 0Ah, 8Ah, 8Ah, 8Ah,0FAh     ;   "国",        41
db  8Ah,0CAh, 8Eh, 0Ah, 02h,0FFh, 02h, 00h
db  00h,0FFh, 40h, 50h, 50h, 50h, 50h, 5Fh
db  50h, 52h, 54h, 50h, 40h,0FFh, 00h, 00h
db  00h, 00h,0FCh, 44h, 44h, 44h, 44h, 45h     ;   "庆",       42
db 0FEh, 44h, 44h, 44h, 66h, 44h, 00h, 00h
db  40h, 20h, 9Fh, 80h, 40h, 20h, 18h, 06h
db  01h, 06h, 18h, 20h, 40h,0C0h, 40h, 00h
db  00h,0FCh, 14h,0D4h, 54h, 54h, 54h,0D4h     ;    "感",      43
db  14h,0FFh, 04h, 85h, 66h, 04h, 00h, 00h
db  04h, 43h, 30h, 07h, 72h, 82h, 8Ah, 93h
db 0B4h, 82h,0E1h, 12h, 24h, 64h, 07h, 00h
db  00h, 00h,0FEh, 02h, 12h, 92h, 52h, 3Eh     ; "恩",        44
db  52h, 9Ah, 92h, 02h,0FFh, 02h, 00h, 00h
db  40h, 30h, 07h, 72h, 83h, 82h, 8Ah, 92h
db 0B2h, 82h, 83h,0E2h, 07h, 10h, 60h, 00h
db  00h, 00h, 02h, 06h, 8Ah, 8Ah, 52h, 22h     ;  "圣",     45
db  52h, 4Ah, 8Ah, 86h, 02h, 00h, 00h, 00h
db  42h, 42h, 41h, 45h, 44h, 44h, 44h, 7Fh
db  44h, 44h, 46h, 44h, 41h, 63h, 41h, 00h
db  40h, 42h,0CCh, 00h, 44h, 64h, 54h,0CCh     ;   "诞",    46
db  00h,0C4h, 04h,0FEh, 43h, 42h, 00h, 00h
db  00h, 00h, 3Fh, 90h, 49h, 22h, 1Ch, 13h
db  20h, 4Fh, 88h, 8Fh, 88h,0C8h, 40h, 00h
db  00h, 50h, 48h, 44h, 4Fh, 54h,0C6h,0F4h    ;  "笨",        47
db 0C8h, 47h, 4Ch, 54h, 46h, 44h, 00h, 00h
db  10h, 10h, 08h, 04h, 0Ah, 09h, 08h,0FFh
db  08h, 09h, 0Ah, 04h, 08h, 18h, 08h, 00h
db  00h, 00h, 00h, 00h, 80h, 60h, 00h,0FFh     ;  "小",       48
db  00h, 20h, 40h, 80h, 00h, 00h, 00h, 00h
db  00h, 08h, 04h, 02h, 01h, 40h, 80h, 7Fh
db  00h, 00h, 00h, 00h, 01h, 06h, 00h, 00h
db  02h, 02h, 02h,0F2h, 8Ah, 46h, 88h,0C8h     ;  "孩",     49
db 0A9h, 9Ah, 88h, 88h,0C8h, 0Ch, 08h, 00h
db  02h, 42h, 81h, 7Fh, 00h, 90h, 90h, 49h
db  48h, 24h, 12h, 29h, 44h,0C6h, 00h, 00h
db  40h, 60h, 5Eh, 48h, 48h,0FFh, 48h, 4Ch    ;  "制",        50
db  68h, 40h,0F8h, 00h, 00h,0FFh, 00h, 00h
db  00h, 00h, 3Fh, 01h, 01h,0FFh, 11h, 21h
db  1Fh, 00h, 07h, 40h, 80h, 7Fh, 00h, 00h
db  80h, 40h, 20h,0F8h, 87h, 40h, 30h, 0Fh     ; "作",      51
db 0F8h, 88h, 88h,0C8h, 88h, 0Ch, 08h, 00h
db  00h, 00h, 00h,0FFh, 00h, 00h, 00h, 00h
db 0FFh, 08h, 08h, 08h, 0Ch, 08h, 00h, 00h
db  20h, 18h, 08h, 0Ah,0ECh,0A8h,0A8h,0AFh  ;"常",
db 0A8h,0A8h,0ECh, 0Ah, 08h, 28h, 18h, 00h
db  00h, 00h, 00h, 3Eh, 02h, 02h, 02h,0FFh
db  02h, 22h, 42h, 3Fh, 02h, 00h, 00h, 00h
 db  20h, 20h, 20h,0FEh, 20h, 20h, 20h,0FFh   ; "世",  53
 db  20h, 20h, 20h,0FFh, 20h, 30h, 20h, 00h
 db  00h, 00h, 00h, 7Fh, 40h, 40h, 40h, 4Fh
 db  44h, 44h, 44h, 4Fh, 60h, 40h, 00h, 00h
 db  00h, 00h, 00h,0FEh, 92h, 92h, 92h,0FEh  ;  "界",   54
 db  92h, 92h, 92h,0FFh, 02h, 00h, 00h, 00h
 db  10h, 10h, 08h, 88h, 44h, 3Eh, 01h, 00h
 db  01h,0FEh, 02h, 04h, 08h, 18h, 08h, 00h
 db  10h, 22h, 64h, 0Ch, 80h,0FEh, 92h, 92h  ; "湿",    55
 db  92h, 92h, 92h, 92h,0FFh, 02h, 00h, 00h
 db  04h, 04h,0FEh, 41h, 44h, 48h, 50h, 7Fh
 db  40h, 40h, 7Fh, 50h, 48h, 64h, 40h, 00h
 db  40h, 40h,0FEh, 40h, 40h, 80h,0FCh, 40h  ; "地",     56
 db  40h,0FFh, 20h, 20h,0F0h, 20h, 00h, 00h
 db  20h, 60h, 3Fh, 10h, 10h, 00h, 3Fh, 40h
 db  40h, 5Fh, 44h, 48h, 47h, 40h, 70h, 00h
 db  00h,0FEh, 02h, 22h,0DAh, 06h, 40h, 42h  ; "际",       57
 db  42h, 42h,0C2h, 42h, 43h, 62h, 40h, 00h
 db  00h,0FFh, 08h, 10h, 08h, 07h, 10h, 08h
 db  46h, 80h, 7Fh, 00h, 02h, 04h, 18h, 00h
 db  40h, 20h, 58h, 47h, 54h, 54h, 54h, 54h  ; "气",        58
 db  54h, 54h,0D4h, 14h, 06h, 04h, 00h, 00h
 db  00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
 db  00h, 00h, 1Fh, 20h, 40h, 80h, 70h, 00h
 db  20h, 10h, 78h, 4Ch, 4Bh,0CAh,0CAh, 7Ah  ; "象",        59
 db  4Ah, 4Eh, 4Ah,0C8h, 7Ch, 08h, 00h, 00h
 db  00h, 42h, 4Ah, 29h, 25h, 14h, 52h, 89h
 db  7Eh, 06h, 09h, 10h, 20h, 60h, 20h, 00h
 db  10h, 22h, 64h, 0Ch, 90h, 08h,0F7h, 14h  ; "海",        60
 db  34h, 54h, 14h, 14h,0F6h, 04h, 00h, 00h
 db  04h, 04h,0FEh, 01h, 01h, 1Fh, 11h, 11h
 db  13h, 15h, 51h, 91h, 7Fh, 11h, 01h, 00h
 db  88h, 98h, 64h, 2Ah,0D1h, 88h, 44h, 20h  ; "豹",        61
 db  90h, 1Fh, 10h, 10h, 10h,0F8h, 10h, 00h
 db  04h, 14h, 52h, 89h, 44h, 3Fh, 00h, 00h
 db  00h, 03h, 40h, 80h, 40h, 3Fh, 00h, 00h
 db  80h, 80h, 40h, 20h, 50h, 48h, 44h,0C3h  ; "全",         62
 db  44h, 68h, 50h, 20h, 40h,0C0h, 40h, 00h
 db  00h, 40h, 40h, 40h, 44h, 44h, 44h, 7Fh
 db  44h, 46h, 44h, 40h, 60h, 40h, 00h, 00h
 db  40h,0B0h, 92h, 96h, 9Ah, 92h,0F2h, 9Eh  ; "爱",         63
 db  92h, 91h, 99h, 95h, 91h, 50h, 30h, 00h
 db  00h, 00h, 40h, 30h, 8Ch, 83h, 46h, 2Ah
 db  12h, 2Ah, 26h, 42h,0C0h, 40h, 00h, 00h
 db  00h, 02h, 02h, 02h,0FEh, 92h, 92h, 92h  ; "耳",        64
 db  92h, 92h,0FEh, 02h, 03h, 02h, 00h, 00h
 db  08h, 08h, 08h, 08h, 0Fh, 08h, 08h, 08h
 db  08h, 08h,0FFh, 04h, 04h, 06h, 04h, 00h
 db  20h, 18h, 0Ah,0AAh,0AAh,0AAh, 0Ah,0FEh  ; "雷",        65
 db  0Ah,0AAh,0AAh,0ABh, 0Ah, 28h, 18h, 00h
 db  00h, 00h,0FEh, 92h, 92h, 92h, 92h,0FFh
 db  92h, 92h, 92h, 92h,0FEh, 00h, 00h, 00h
 db  80h, 40h, 70h,0CFh, 48h, 48h, 90h, 88h ;  "锋",         66
 db  4Fh, 54h,0A4h, 54h, 4Ch,0C4h, 40h, 00h
 db  02h, 02h, 02h, 7Fh, 22h, 12h, 00h, 14h
 db  15h, 15h,0FFh, 15h, 15h, 14h, 00h, 00h
 db  20h, 20h, 30h,0ACh, 63h, 30h, 04h, 84h  ; "纪",         67
 db  84h, 84h, 84h, 84h, 84h,0FEh, 04h, 00h
 db  22h, 66h, 23h, 12h, 12h, 12h, 00h, 3Fh
 db  40h, 40h, 40h, 40h, 40h, 41h, 70h, 00h
 db  40h, 40h, 20h, 90h, 88h, 84h, 92h,0E1h  ; "念",          68
 db  82h, 84h, 88h, 90h,0A0h, 60h, 20h, 00h
 db  40h, 30h, 00h, 38h, 40h, 44h, 48h, 58h
 db  40h, 42h, 41h, 70h, 00h, 10h, 60h, 00h
 db  10h, 10h,0D0h,0FFh, 90h, 14h,0E4h,0A4h  ; "植",          69
 db 0A4h,0BFh,0A4h,0A4h,0F6h, 24h, 00h, 00h
 db  04h, 03h, 00h,0FFh, 40h, 41h, 7Fh, 4Ah
 db  4Ah, 4Ah, 4Ah, 4Ah, 7Fh, 40h, 40h, 00h
 db  10h, 10h,0D0h,0FFh, 90h, 38h,0C8h, 08h  ; "树",         70
 db 0C8h, 38h, 90h, 10h,0FFh, 10h, 10h, 00h
 db  04h, 03h, 00h,0FFh, 20h, 10h, 0Ch, 03h
 db  04h, 18h, 40h, 81h, 7Fh, 00h, 00h, 00h
 db  80h, 92h, 8Ah,0BFh,0AAh,0BBh,0CAh,0FAh  ; "警",          71
 db  84h,0A7h,0AAh, 92h,0AEh,0E2h,0A0h, 00h
 db  00h, 00h, 00h,0EAh,0AAh,0AAh,0AAh,0AAh
 db 0AAh,0AAh,0AAh,0EAh, 00h, 00h, 00h, 00h
 db  10h, 8Ch,0C4h, 24h,0DCh, 54h, 35h, 06h   ;"察",          72
 db  34h, 54h,0D4h, 34h, 04h, 14h, 0Ch, 00h
 db  08h, 04h, 42h, 25h, 14h, 45h, 85h, 7Dh
 db  05h, 05h, 14h, 25h, 62h, 06h, 02h, 00h
 db  10h, 22h, 64h, 0Ch, 80h, 00h,0F2h, 94h  ; "消",         73
 db  90h, 9Fh, 90h, 94h,0FAh, 10h, 00h, 00h
 db  04h, 04h,0FEh, 01h, 00h, 00h,0FFh, 04h
 db  04h, 04h, 44h, 84h, 7Fh, 00h, 00h, 00h
 db  00h, 3Ah, 2Ah, 2Ah,0AAh, 7Fh, 2Ah, 2Ah  ; "费",        74
 db  2Ah,0FFh, 2Ah, 2Ah,0AFh, 22h,0E0h, 00h
 db  02h, 02h, 81h, 9Fh, 41h, 41h, 21h, 1Dh
 db  21h, 21h, 41h, 5Fh, 80h, 01h, 00h, 00h
 db  10h, 10h,0D0h,0FFh, 90h, 10h, 34h,0C4h  ; "权",         75
 db  04h, 04h, 04h, 84h, 7Ch, 00h, 00h, 00h
 db  04h, 03h, 00h,0FFh, 00h, 41h, 20h, 11h
 db  0Ah, 04h, 0Ah, 11h, 20h, 60h, 20h, 00h
 db  00h, 08h, 08h, 88h, 49h, 2Ah, 08h, 08h  ; "益",          76
 db  08h, 2Ah, 49h,0C8h, 0Ch, 08h, 00h, 00h
 db  40h, 40h, 7Eh, 42h, 42h, 7Eh, 42h, 42h
 db  42h, 7Eh, 42h, 42h, 7Eh, 40h, 40h, 00h
 db  80h, 80h,0FCh, 96h,0A5h, 84h,0FCh, 08h  ; "航",           77
 db  08h,0C9h, 4Ah, 4Eh,0E8h, 4Ch, 08h, 00h
 db  80h, 40h, 3Fh, 02h, 44h, 80h, 7Fh, 80h
 db  40h, 3Fh, 00h, 00h, 3Fh, 40h, 70h, 00h
 db  00h, 40h, 44h, 24h,0A4h, 14h, 0Ch,0FFh  ; "森",          78
 db  0Ch, 14h, 94h, 24h, 66h, 24h, 00h, 00h
 db  20h, 22h, 12h, 0Ah,0FFh, 0Ah, 12h, 20h
 db  12h, 0Ah,0FFh, 0Ah, 13h, 32h, 10h, 00h
 db  10h, 10h, 10h,0D0h,0FFh, 90h, 10h, 00h  ; "林",           79
 db  10h,0D0h,0FFh, 90h, 10h, 18h, 10h, 00h
 db  08h, 04h, 03h, 00h,0FFh, 00h, 09h, 04h
 db  03h, 00h,0FFh, 00h, 03h, 06h, 02h, 00h
 db  00h, 20h, 20h, 20h, 20h,0E0h, 00h,0FFh  ; "水",          80
 db 0C0h, 40h, 20h, 10h, 18h, 00h, 00h, 00h
 db  20h, 10h, 08h, 04h, 03h, 40h, 80h, 7Fh
 db  00h, 01h, 02h, 04h, 08h, 18h, 08h, 00h
 db  20h, 10h, 0Ch, 03h,0FAh,0AAh,0AAh,0AAh  ; "复",           81
 db 0AAh,0AAh,0AAh,0FAh, 03h, 02h, 00h, 00h
 db  00h, 20h, 90h, 88h, 86h, 47h, 2Ah, 12h
 db  12h, 2Ah, 46h, 42h, 80h, 80h, 80h, 00h
 db  10h, 21h, 62h, 06h,0C0h, 44h, 44h, 44h  ; "活",           82
 db  44h,0FCh, 42h, 43h, 42h, 60h, 40h, 00h
 db  04h, 04h,0FEh, 01h, 00h, 00h,0FEh, 42h
 db  42h, 43h, 42h, 42h,0FFh, 02h, 00h, 00h
 db  00h,0FEh, 02h, 22h,0DAh, 16h, 10h, 10h  ; "防",            83
 db 0F1h, 96h, 90h, 90h,0D0h, 98h, 10h, 00h
 db  00h,0FFh, 08h, 10h, 08h, 87h, 40h, 30h
 db  0Fh, 40h, 80h, 40h, 3Fh, 00h, 00h, 00h
 db  00h, 30h, 28h,0A4h, 63h, 10h, 08h, 48h  ; "结",            84
 db  48h, 48h, 7Fh, 48h, 48h, 4Ch, 08h, 00h
 db  00h, 22h, 63h, 22h, 12h, 12h, 00h,0FEh
 db  42h, 42h, 42h, 42h, 42h,0FFh, 02h, 00h
 db  10h, 10h,0D0h,0FFh, 50h, 90h, 88h,0C8h  ; "核",            85
 db 0A9h, 9Eh, 88h, 88h,0C8h, 0Ch, 08h, 00h
 db  04h, 03h, 00h,0FFh, 00h, 91h, 90h, 49h
 db  48h, 24h, 12h, 29h, 44h,0C6h, 00h, 00h
 db  10h, 60h, 00h,0FCh, 04h, 24h, 24h, 24h  ; "病",            86
 db  25h,0E6h, 24h, 24h, 34h,0A6h, 04h, 00h
 db  04h, 42h, 31h, 0Fh, 00h,0FFh, 01h, 11h
 db  09h, 07h, 09h, 51h, 81h, 7Fh, 01h, 00h
 db  90h, 8Ch, 84h, 84h, 84h, 84h,0F5h, 86h  ; "安",            87
 db  84h, 84h, 84h, 84h, 84h,0D4h, 8Ch, 00h
 db  00h, 00h, 80h, 84h, 46h, 49h, 28h, 10h
 db  10h, 28h, 47h,0C0h, 00h, 00h, 00h, 00h
 db  04h, 04h, 24h,0A4h,0B4h,0ACh,0A5h,0A6h  ; "育",           88
 db 0A4h,0A4h,0A4h,0B4h, 64h, 06h, 04h, 00h
 db  00h, 00h, 00h,0FFh, 0Ah, 0Ah, 0Ah, 0Ah
 db  0Ah, 4Ah, 8Ah, 7Fh, 00h, 00h, 00h, 00h
 db  00h, 04h, 04h, 04h, 04h, 04h,0FCh, 04h  ; "卫",          89
 db  04h, 04h, 04h, 04h,0FEh, 04h, 00h, 00h
 db  40h, 40h, 40h, 40h, 40h, 40h, 7Fh, 40h
 db  40h, 40h, 42h, 44h, 43h, 60h, 40h, 00h
 db  00h,0C0h, 30h, 1Eh, 10h, 10h, 10h,0FFh  ; "生",          90
 db  10h, 10h, 10h, 10h, 18h, 10h, 00h, 00h
 db  41h, 40h, 42h, 42h, 42h, 42h, 42h, 7Fh
 db  42h, 42h, 42h, 43h, 42h, 60h, 40h, 00h
 db  04h, 44h, 44h,0FCh, 46h, 44h, 28h,0C8h  ; "球",         91
 db  08h,0FFh, 08h, 8Ah, 4Ch, 68h, 08h, 00h
 db  10h, 10h, 10h, 0Fh, 08h, 18h, 08h, 44h
 db  82h, 7Fh, 01h, 06h, 08h, 18h, 08h, 00h
 db  00h,0FEh, 02h, 22h, 12h, 1Eh,0AAh, 4Ah  ; "图",          92
 db 0AAh, 1Ah, 0Ah, 02h, 02h,0FFh, 02h, 00h
 db  00h,0FFh, 44h, 44h, 42h, 49h, 49h, 52h
 db  64h, 41h, 42h, 46h, 42h,0FFh, 00h, 00h
 db  00h, 08h, 08h, 08h, 08h, 08h,0FFh, 08h  ; "书",          93
 db  08h, 08h,0F8h, 02h, 04h, 0Ch, 00h, 00h
 db  01h, 01h, 01h, 01h, 01h, 01h,0FFh, 01h
 db  01h, 01h, 21h, 41h, 21h, 1Fh, 00h, 00h
 db  00h,0FEh, 20h, 20h, 3Fh, 20h, 00h,0FCh  ; "版",          94
 db  24h,0A4h, 24h, 22h,0A3h, 62h, 00h, 00h
 db  40h, 3Fh, 01h, 01h,0FFh, 20h, 18h, 47h
 db  20h, 13h, 0Ch, 16h, 21h, 60h, 20h, 00h
 db 0A0h, 90h, 8Fh,0F8h, 88h,0CCh, 88h, 10h  ; "缺",          95
 db  10h,0FFh, 10h, 10h,0F8h, 10h, 00h, 00h
 db  00h, 7Eh, 20h, 3Fh, 20h,0FEh, 41h, 21h
 db  19h, 07h, 19h, 21h, 41h,0C1h, 41h, 00h
 db  04h, 04h,0E4h, 9Ch, 84h,0C6h, 84h,0F8h  ; "碘",           96
 db  88h,0FFh, 88h,0FFh, 88h,0FCh, 08h, 00h
 db  02h, 01h, 7Fh, 20h, 20h, 7Fh, 88h, 4Fh
 db  68h, 0Fh, 08h, 0Fh, 28h, 4Fh,0C8h, 00h
 db  20h, 30h,0ACh, 63h, 20h, 10h, 04h, 04h  ; "红",          97
 db  04h, 04h,0FCh, 04h, 06h, 04h, 00h, 00h
 db  22h, 67h, 22h, 12h, 12h, 52h, 40h, 40h
 db  40h, 40h, 7Fh, 40h, 40h, 60h, 40h, 00h
 db  40h, 40h, 40h, 40h, 40h, 40h, 40h,0FFh  ; "十",           98
 db  40h, 40h, 40h, 40h, 40h, 60h, 40h, 00h
 db  00h, 00h, 00h, 00h, 00h, 00h, 00h,0FFh
 db  00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
 db  00h, 10h, 0Ch, 24h, 24h, 24h, 25h, 26h  ; "字",           99
 db 0A4h, 64h, 24h, 04h, 14h, 0Ch, 00h, 00h
 db  02h, 02h, 02h, 02h, 02h, 42h, 82h, 7Fh
 db  02h, 02h, 02h, 02h, 02h, 03h, 02h, 00h
 db  10h, 10h, 10h,0FFh, 90h, 50h,0F8h, 88h  ; "护",          100
 db  89h, 8Ah, 8Eh, 88h, 88h,0FCh, 08h, 00h
 db  02h, 42h, 81h, 7Fh, 80h, 60h, 1Fh, 00h
 db  00h, 00h, 00h, 00h, 00h, 01h, 00h, 00h
 db  40h, 40h, 40h, 40h, 40h, 40h, 40h,0FFh  ; "士",           101
 db  40h, 40h, 40h, 40h, 40h, 60h, 40h, 00h
 db  00h, 00h, 40h, 40h, 40h, 40h, 40h, 7Fh
 db  40h, 40h, 40h, 60h, 40h, 00h, 00h, 00h
 db  10h, 0Ch, 24h,0A4h,0A4h, 64h,0A5h, 26h  ; "家",          102
 db  24h, 24h, 24h,0A4h, 24h, 14h, 0Ch, 00h
 db  00h, 49h, 49h, 24h, 24h, 52h, 89h, 7Fh
 db  04h, 0Ah, 11h, 11h, 20h, 60h, 20h, 00h
 db  00h, 00h,0FCh, 14h, 94h, 54h, 34h, 15h  ; "庭",           103
 db  06h, 24h, 24h,0F4h, 16h, 94h, 00h, 00h
 db  40h, 30h, 8Fh, 40h, 29h, 11h, 29h, 47h
 db  81h, 91h, 91h, 9Fh, 91h,0D1h, 41h, 00h
 db  10h, 22h, 64h, 0Ch, 80h,0FCh, 44h, 56h  ; "澳",           104
 db  45h,0FCh, 44h, 54h, 44h,0FEh, 04h, 00h
 db  04h, 04h,0FEh, 01h, 88h, 8Bh, 48h, 29h
 db  18h, 0Dh, 18h, 29h, 48h,0CBh, 48h, 00h
 db  00h,0FCh, 01h, 02h, 06h, 00h, 02h, 02h  ;"门",           105
 db  02h, 02h, 02h, 02h, 02h,0FFh, 02h, 00h
 db  00h,0FFh, 00h, 00h, 00h, 00h, 00h, 00h
 db  00h, 00h, 00h, 40h, 80h, 7Fh, 00h, 00h
 db  00h,0FCh, 04h, 04h, 04h,0E4h, 24h, 24h  ; "回",          106
 db  24h,0F4h, 24h, 04h, 04h,0FEh, 04h, 00h
 db  00h, 7Fh, 20h, 20h, 20h, 2Fh, 24h, 24h
 db  24h, 2Fh, 20h, 20h, 20h, 7Fh, 00h, 00h
 db  00h, 00h,0FCh, 00h, 00h,0FFh, 00h, 84h  ; "归",          107
 db  84h, 84h, 84h, 84h, 84h,0FEh, 04h, 00h
 db  00h, 40h, 47h, 20h, 10h, 0Fh, 20h, 20h
 db  20h, 20h, 20h, 20h, 20h, 7Fh, 00h, 00h
 db  10h, 08h,0E4h, 03h, 06h,0FAh, 83h, 4Ah  ; "篮",          108
 db  34h, 63h,0A6h, 2Ah, 23h, 22h, 00h, 00h
 db  40h, 40h, 7Dh, 44h, 44h, 7Fh, 44h, 44h
 db  44h, 7Ch, 45h, 44h, 7Eh, 44h, 40h, 00h
 db  10h, 10h, 10h,0FFh, 90h, 50h, 04h, 84h  ; "扫",          109
 db  84h, 84h, 84h, 84h, 84h,0FEh, 04h, 00h
 db  02h, 42h, 81h, 7Fh, 00h, 00h, 20h, 20h
 db  20h, 20h, 20h, 20h, 20h, 7Fh, 00h, 00h
 db  04h, 04h, 04h, 7Ch, 44h, 44h, 45h, 46h ;  "盲",          110
 db  44h, 44h, 44h, 64h, 44h, 06h, 04h, 00h
 db  00h, 00h, 00h,0FFh, 55h, 55h, 55h, 55h
 db  55h, 55h, 55h,0FFh, 00h, 00h, 00h, 00h
 db  00h, 00h, 00h,0FCh, 54h, 56h, 55h, 54h  ; "臭",          111
 db  54h, 54h, 54h,0FEh, 04h, 00h, 00h, 00h
 db  08h, 88h, 88h, 49h, 49h, 29h, 19h, 0Fh
 db  19h, 29h, 2Bh, 4Dh,0C8h, 4Ch, 08h, 00h
 db  20h, 10h, 2Ch, 23h, 6Ah,0AAh, 2Ah,0AAh  ; "氧",           112
 db  6Ah, 2Ah, 2Ah, 2Ah,0EAh, 02h, 00h, 00h
 db  00h, 10h, 11h, 15h, 15h, 15h,0FFh, 15h
 db  15h, 15h, 11h, 10h, 3Fh, 40h, 30h, 00h
 db  00h, 82h,0E2h, 9Ah, 82h, 82h, 82h, 82h  ; "牙",           113
 db  82h,0FEh, 82h, 82h, 83h,0C2h, 80h, 00h
 db  20h, 20h, 10h, 10h, 08h, 04h, 02h, 41h
 db  80h, 7Fh, 00h, 00h, 00h, 00h, 00h, 00h
 db  08h, 08h,0F9h, 4Eh, 48h,0C8h, 10h,0C8h  ; "旅",           114
 db  4Fh,0A8h, 28h, 18h, 8Ch,0C8h, 00h, 00h
 db  40h, 20h, 1Fh, 40h, 80h, 7Fh, 00h,0FFh
 db  40h, 21h, 06h, 19h, 20h, 60h, 20h, 00h
 db  10h, 22h, 6Ch, 00h, 08h, 08h,0F9h, 4Ah  ; "游",           115
 db 0C8h, 18h, 28h, 27h,0A4h, 66h, 24h, 00h
 db  04h, 04h,0FEh, 41h, 20h, 18h, 07h, 40h
 db  7Fh, 02h, 42h, 82h, 7Fh, 02h, 02h, 00h
 db  00h, 02h, 06h, 02h,0F2h, 12h, 8Ah, 86h  ; "孔",           116
 db  00h,0FFh, 00h, 00h, 00h, 00h, 00h, 00h
 db  02h, 02h, 42h, 81h, 7Fh, 01h, 00h, 00h
 db  00h, 3Fh, 40h, 40h, 40h, 40h, 70h, 00h
 db  80h, 80h, 82h, 82h, 82h, 82h, 82h,0E2h  ; "子",           117
 db 0A2h, 92h, 8Ah, 86h, 80h,0C0h, 80h, 00h
 db  00h, 00h, 00h, 00h, 00h, 40h, 80h, 7Fh
 db  00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
 db  40h, 3Ch, 10h,0FFh, 90h,0A0h, 10h, 1Fh  ; "物",            118
 db 0F0h, 10h,0F0h, 10h, 10h,0F8h, 10h, 00h
 db  02h, 02h, 01h,0FFh, 00h, 10h, 0Ch, 43h
 db  30h, 0Eh, 41h, 80h, 40h, 3Fh, 00h, 00h
 db  00h,0F8h, 48h, 48h, 48h, 48h,0FFh, 48h  ; "电",            119
 db  48h, 48h, 48h,0FCh, 08h, 00h, 00h, 00h
 db  00h, 07h, 02h, 02h, 02h, 02h, 3Fh, 42h
 db  42h, 42h, 42h, 47h, 40h, 70h, 00h, 00h
 db  80h, 40h, 20h,0F8h, 07h, 24h, 24h, 24h  ; "信",            120
 db  25h, 26h, 24h, 24h,0B4h, 26h, 04h, 00h
 db  00h, 00h, 00h,0FFh, 00h, 01h,0FDh, 45h
 db  45h, 45h, 45h, 45h,0FDh, 01h, 00h, 00h
 db  00h, 00h,0FEh, 22h, 22h, 22h,0FFh, 12h  ; "助",           121
 db  10h, 10h,0FFh, 10h, 10h,0F8h, 10h, 00h
 db  20h, 60h, 3Fh, 21h, 11h, 11h, 9Fh, 50h
 db  20h, 1Ch, 43h, 80h, 40h, 3Fh, 00h, 00h
 db  00h, 04h,0C4h, 3Ch, 24h, 26h,0E4h, 20h  ; "残",            122
 db  20h,0FFh, 90h, 92h,0D4h, 90h, 00h, 00h
 db  82h, 41h, 21h, 12h, 0Ch, 03h, 40h, 41h
 db  21h, 17h, 18h, 24h, 42h, 80h,0E0h, 00h
 db  40h, 30h, 11h, 96h, 90h, 90h, 91h, 96h  ; "学",             123
 db  90h, 90h, 98h, 14h, 13h, 50h, 30h, 00h
 db  04h, 04h, 04h, 04h, 04h, 44h, 84h, 7Eh
 db  06h, 05h, 04h, 04h, 04h, 06h, 04h, 00h
 db  40h, 34h, 14h, 14h,0D4h, 5Fh, 54h, 54h  ; "营",              124
 db  54h, 5Fh,0D4h, 14h, 16h, 54h, 30h, 00h
 db  00h, 00h, 00h,0F8h, 4Bh, 4Ah, 4Ah, 4Ah
 db  4Ah, 4Ah, 4Bh,0F8h, 00h, 00h, 00h, 00h
 db  80h, 88h,0A8h,0A8h,0A9h,0AAh,0ACh,0F8h  ; "养",            125
 db 0ACh,0AAh,0A9h,0A8h,0ACh, 88h, 80h, 00h
 db  08h, 08h, 04h, 84h, 42h, 3Dh, 00h, 00h
 db  00h,0FDh, 02h, 02h, 04h, 0Ch, 04h, 00h
 db  00h, 40h, 30h, 0Eh, 08h, 08h, 08h,0FFh  ; "牛",             126
 db  08h, 08h, 08h, 0Ch, 08h, 80h, 00h, 00h
 db  01h, 01h, 01h, 01h, 01h, 01h, 01h,0FFh
 db  01h, 01h, 01h, 01h, 01h, 01h, 01h, 00h
 db  10h, 10h,0F0h, 1Fh, 10h,0F2h, 02h, 02h  ; "奶",             127
 db 0FEh, 02h, 82h,0E2h, 9Fh,0C2h, 80h, 00h
 db  40h, 22h, 15h, 08h,0B6h, 41h, 30h, 0Eh
 db  01h, 00h, 40h, 80h, 40h, 3Fh, 00h, 00h
 db  00h, 40h, 42h, 42h, 42h, 42h,0FEh, 42h  ; "无",              128
 db 0C2h, 42h, 43h, 42h, 60h, 40h, 00h, 00h
 db  00h, 80h, 40h, 20h, 18h, 06h, 01h, 00h
 db  3Fh, 40h, 40h, 40h, 40h, 40h, 70h, 00h
 db 0E0h, 00h,0FFh, 20h, 10h,0FEh, 42h, 42h  ; "烟",              129
 db  42h,0FAh, 42h, 42h, 42h,0FFh, 02h, 00h
 db  40h, 30h, 0Fh, 10h, 20h,0FFh, 50h, 48h
 db  46h, 41h, 42h, 44h, 58h,0FFh, 00h, 00h
 db  00h,0FCh, 44h, 44h,0FEh, 04h,0FEh, 92h  ; "眼",            130
 db  92h, 92h, 92h, 92h,0FFh, 02h, 00h, 00h
 db  00h, 7Fh, 22h, 22h, 7Fh, 00h,0FFh, 40h
 db  23h, 04h, 08h, 14h, 22h, 61h, 20h, 00h
 db  00h, 00h, 00h, 00h, 00h,0FFh, 00h, 00h  ; "儿",            131
 db  00h,0FFh, 00h, 00h, 00h, 00h, 00h, 00h
 db  80h, 40h, 20h, 10h, 0Ch, 03h, 00h, 00h
 db  00h, 3Fh, 40h, 40h, 40h, 40h, 78h, 00h
 db  20h, 20h, 24h,0A4h,0ACh,0B4h,0A5h,0A6h  ; "童",            132
 db 0A4h,0B4h,0ACh,0E6h,0A4h, 30h, 20h, 00h
 db  00h, 80h,0A0h,0AFh,0AAh,0AAh,0AAh,0FFh
 db 0AAh,0AAh,0AAh,0AFh,0A0h, 80h, 00h, 00h
 db  20h, 24h, 24h,0E4h, 24h, 2Fh, 24h, 34h  ; "荒",            133
 db  24h, 2Fh,0A4h, 24h, 26h, 34h, 20h, 00h
 db  00h, 80h, 40h, 3Dh, 01h, 01h, 01h,0FDh
 db  01h, 01h, 01h, 7Dh, 80h, 80h,0E0h, 00h
 db  10h, 22h, 64h, 08h, 84h, 04h,0E4h,0BFh  ; "漠",              134
 db 0A4h,0A4h,0A4h,0BFh,0F4h, 26h, 04h, 00h
 db  04h, 04h,0FEh, 09h, 88h, 88h, 4Bh, 4Ah
 db  2Ah, 1Eh, 2Ah, 2Ah, 4Bh,0C8h, 48h, 00h
 db  00h, 00h, 00h,0FCh, 44h, 56h, 45h,0FCh ;  "奥",              135
 db  44h, 54h, 44h,0FEh, 04h, 00h, 00h, 00h
 db  08h, 88h, 88h, 4Bh, 48h, 29h, 18h, 0Fh
 db  18h, 29h, 28h, 4Bh,0C8h, 4Ch, 08h, 00h
 db  00h,0FCh, 04h, 04h, 04h,0FCh, 04h, 04h  ; "匹",              136
 db  04h,0FCh, 04h, 04h, 06h, 04h, 00h, 00h
 db  00h, 7Fh, 40h, 50h, 48h, 47h, 40h, 40h
 db  40h, 47h, 48h, 48h, 48h, 6Eh, 40h, 00h
 db  04h, 04h, 04h,0E4h, 24h, 24h, 24h, 3Fh  ; "克",              137
 db  24h, 24h, 24h,0F4h, 24h, 06h, 04h, 00h
 db  00h, 80h, 80h, 47h, 22h, 1Eh, 02h, 02h
 db  02h, 7Eh, 82h, 87h, 80h, 80h,0E0h, 00h
 db  00h, 40h, 40h, 40h, 40h, 40h, 40h,0FFh  ; "土",              138
 db  40h, 40h, 40h, 40h, 60h, 40h, 00h, 00h
 db  40h, 40h, 40h, 40h, 40h, 40h, 40h, 7Fh
 db  40h, 40h, 40h, 40h, 40h, 60h, 40h, 00h
 db  40h, 24h, 14h, 0Ch, 7Fh, 14h, 24h, 20h  ; "禁",             139
 db  14h, 0Ch, 7Fh, 0Ch, 16h, 24h, 40h, 00h
 db  04h, 04h, 45h, 25h, 15h, 45h, 85h, 7Dh
 db  05h, 05h, 15h, 25h, 65h, 04h, 04h, 00h
 db  00h, 20h, 22h,0AAh,0AAh,0AAh,0AAh,0BFh  ; "毒",             140
 db 0AAh,0AAh,0AAh,0ABh, 22h, 20h, 00h, 00h
 db  04h, 04h, 3Ch, 27h, 24h, 24h, 2Dh, 36h
 db  24h,0A4h,0A4h, 7Fh, 24h, 06h, 04h, 00h
 db  10h, 10h, 92h, 92h, 52h, 32h, 12h,0FEh  ; "香",            141
 db  12h, 32h, 51h, 51h, 90h, 98h, 90h, 00h
 db  01h, 01h, 00h, 00h,0FFh, 49h, 49h, 49h
 db  49h, 49h,0FFh, 00h, 00h, 01h, 00h, 00h
 db  08h, 11h, 32h, 86h, 20h, 24h,0A4h, 7Fh  ; "港",             142
 db  24h, 24h, 64h,0BFh, 24h, 34h, 20h, 00h
 db  02h, 02h,0FFh, 00h, 02h, 01h, 3Fh, 49h
 db  49h, 49h, 49h, 4Fh, 41h, 73h, 01h, 00h
 db  40h, 20h,0F8h, 07h, 10h, 90h, 70h, 10h ;  "体",              143
 db 0FFh, 10h, 70h, 90h, 18h, 10h, 00h, 00h
 db  00h, 00h,0FFh, 08h, 06h, 01h, 04h, 04h
 db 0FFh, 04h, 04h, 01h, 06h, 0Ch, 04h, 00h
 db  40h, 40h, 42h,0CCh, 00h, 04h, 84h, 84h  ; "记",             144
 db  84h, 84h, 84h, 84h,0FEh, 04h, 00h, 00h
 db  00h, 00h, 00h, 7Fh, 20h, 10h, 3Fh, 40h
 db  40h, 40h, 40h, 40h, 41h, 40h, 78h, 00h
 db  20h, 20h, 24h, 24h, 24h,0A4h, 7Fh, 24h  ; "者",              145
 db  34h, 2Ch, 24h,0A2h, 20h, 30h, 20h, 00h
 db  10h, 08h, 04h, 02h,0FFh, 49h, 49h, 49h
 db  49h, 49h, 49h,0FFh, 01h, 00h, 00h, 00h
 db  10h, 10h, 10h,0FFh, 90h, 58h, 08h,0C8h  ; "抗",            146
 db  49h, 4Eh, 48h,0E8h, 48h, 0Ch, 08h, 00h
 db  02h, 42h, 81h, 7Fh, 00h, 80h, 60h, 1Fh
 db  00h, 00h, 00h, 3Fh, 40h, 40h, 70h, 00h
 db  00h, 80h, 80h,0FFh, 88h, 88h,0ACh, 28h  ; "战",            147
 db  20h,0FFh, 10h, 12h, 1Ch, 10h, 10h, 00h
 db  00h, 7Fh, 20h, 20h, 20h, 20h,0BFh, 40h
 db  20h, 11h, 0Eh, 34h, 43h, 80h,0E0h, 00h
 db  00h, 00h,0FCh, 04h, 04h, 04h, 04h, 04h ;  "口",             148
 db  04h, 04h, 04h, 04h,0FEh, 04h, 00h, 00h
 db  00h, 00h, 3Fh, 10h, 10h, 10h, 10h, 10h
 db  10h, 10h, 10h, 10h, 3Fh, 00h, 00h, 00h
 db  08h, 88h, 88h, 88h, 88h,0FFh, 00h, 00h  ; "非",             149
 db  00h,0FFh, 88h, 88h,0C8h, 8Ch, 08h, 00h
 db  10h, 10h, 10h, 10h, 10h,0FFh, 00h, 00h
 db  00h,0FFh, 10h, 10h, 10h, 18h, 10h, 00h
 db  10h, 22h, 64h, 0Ch, 80h, 20h,0C0h,0FFh  ; "洲",               150
 db  20h,0C0h,0FCh, 20h,0C0h,0FFh, 00h, 00h
 db  04h, 04h,0FEh, 01h, 00h, 40h, 30h, 0Fh
 db  00h, 00h, 3Fh, 00h, 00h,0FFh, 00h, 00h
 db  00h, 02h, 02h, 1Ah, 62h, 02h, 02h,0FEh  ; "平",              151
 db  02h, 02h, 62h, 1Ah, 03h, 82h, 00h, 00h
 db  01h, 01h, 01h, 01h, 01h, 01h, 01h,0FFh
 db  01h, 01h, 01h, 01h, 01h, 01h, 01h, 00h
 db  04h, 04h, 84h,0E4h, 1Ch, 04h, 85h, 46h  ; "夜",             152
 db 0BCh, 24h, 24h, 24h,0E4h, 06h, 04h, 00h
 db  02h, 01h, 00h,0FFh, 82h, 81h, 41h, 22h
 db  14h, 09h, 14h, 23h, 40h,0C0h, 40h, 00h
 db  00h, 00h, 88h, 88h, 44h, 47h, 28h, 10h  ; "爸",               153
 db  28h, 45h, 42h, 84h, 8Ch, 00h, 00h, 00h
 db  01h, 01h, 00h, 7Fh, 89h, 89h, 89h, 8Fh
 db  89h, 89h, 89h, 9Fh, 80h,0E1h, 01h, 00h
 db  00h,0FEh, 22h, 22h,0FFh, 82h, 40h, 3Ch  ; "胜",              154
 db  20h, 20h,0FFh, 20h, 30h, 20h, 00h, 00h
 db  80h, 7Fh, 02h, 82h,0FFh, 00h, 40h, 42h
 db  42h, 42h, 7Fh, 42h, 43h, 62h, 40h, 00h
 db  40h, 44h, 44h, 44h,0C4h,0FEh, 42h, 63h  ; "利",               155
 db  42h, 00h,0F8h, 00h, 00h,0FFh, 00h, 00h
 db  00h, 10h, 08h, 06h, 01h,0FFh, 01h, 02h
 db  06h, 00h, 0Fh, 40h, 80h, 7Fh, 00h, 00h
 db  40h, 40h, 48h, 48h, 48h, 48h, 7Fh,0C8h  ; "老",             156
 db  4Ch, 68h, 50h, 48h, 4Ch, 60h, 40h, 00h
 db  40h, 20h, 10h, 08h, 04h, 7Eh, 91h, 90h
 db  88h, 88h, 84h, 86h, 80h,0E0h, 00h, 00h
 db  10h, 10h, 91h,0D6h, 30h, 10h,0FEh, 02h  ; "视",             157
 db  02h,0FAh, 02h, 02h,0FFh, 02h, 00h, 00h
 db  02h, 01h, 00h,0FFh, 01h, 82h, 47h, 30h
 db  0Ch, 03h, 3Eh, 40h, 47h, 40h, 70h, 00h
 db  20h, 18h, 08h,0C9h, 4Eh, 48h, 49h, 4Eh  ; "觉",            158
 db  48h, 48h, 4Ch,0EBh, 48h, 28h, 18h, 00h
 db  00h, 80h, 80h, 9Fh, 40h, 20h, 18h, 07h
 db  7Ch, 80h, 80h, 9Fh, 80h,0E0h, 00h, 00h
 db  00h,0F8h, 08h, 08h,0FFh, 08h, 08h,0FCh  ; "邮",           159
 db  08h,0FCh, 04h, 44h,0B4h, 0Ch, 00h, 00h
 db  00h, 7Fh, 21h, 21h, 3Fh, 21h, 21h, 7Fh
 db  00h,0FFh, 08h, 10h, 20h, 11h, 0Eh, 00h
 db  04h,0C4h, 04h,0FCh, 44h, 46h, 44h, 20h ;  "政",            160
 db 0D8h, 0Fh, 08h, 08h,0F8h, 0Ch, 08h, 00h
 db  10h, 3Fh, 10h, 1Fh, 08h, 08h, 88h, 40h
 db  20h, 1Bh, 04h, 1Bh, 60h,0C0h, 40h, 00h
 db  40h, 40h, 44h, 44h, 4Ch, 74h, 45h,0C6h  ; "辛",          161
 db  44h, 64h, 5Ch, 46h, 44h, 60h, 40h, 00h
 db  00h, 04h, 04h, 04h, 04h, 04h, 04h,0FFh
 db  04h, 04h, 04h, 04h, 06h, 04h, 00h, 00h
 db  08h, 08h, 08h, 08h, 88h, 48h, 29h, 1Eh  ; "亥",          162
 db  88h, 48h, 68h, 08h, 08h, 0Ch, 08h, 00h
 db  00h, 80h, 90h, 51h, 49h, 25h, 23h, 11h
 db  08h, 0Ch, 12h, 23h, 40h,0C0h, 00h, 00h
 db  00h, 04h,0C4h, 44h, 5Fh, 54h, 54h,0F4h ;  "革",         163
 db  54h, 54h, 5Fh, 44h,0E6h, 44h, 00h, 00h
 db  08h, 08h, 0Bh, 0Ah, 0Ah, 0Ah, 0Ah,0FFh
 db  0Ah, 0Ah, 0Ah, 0Ah, 0Bh, 0Ch, 08h, 00h
 db  40h, 40h,0A0h,0A0h,0B0h,0A8h,0A4h, 23h  ; "命",         164
 db 0A4h,0A8h,0B0h,0B0h,0E0h,0A0h, 20h, 00h
 db  00h, 00h, 3Fh, 10h, 10h, 10h, 3Fh, 00h
 db 0FFh, 08h, 10h, 20h, 1Fh, 00h, 00h, 00h
 db  00h, 80h, 60h,0F8h, 07h, 00h, 7Eh, 22h  ; "保",          165
 db  22h,0E2h, 22h, 22h, 3Fh, 82h, 00h, 00h
 db  01h, 00h, 00h,0FFh, 41h, 21h, 11h, 09h
 db  05h,0FFh, 05h, 09h, 31h, 61h, 21h, 00h
 db  40h, 20h,0F8h, 07h, 88h, 48h, 38h, 10h  ; "健",         166
 db  54h, 54h,0FFh, 54h, 54h, 7Ch, 10h, 00h
 db  00h, 00h,0FFh, 44h, 29h, 19h, 27h, 49h
 db  89h, 89h,0FFh, 89h, 89h,0CDh, 49h, 00h
 db  10h, 10h,0D0h,0FFh, 90h, 50h, 44h, 44h  ; "标",         167
 db  44h,0C4h, 44h, 46h, 44h, 60h, 40h, 00h
 db  04h, 03h, 00h,0FFh, 00h, 11h, 08h, 46h
 db  80h, 7Fh, 00h, 02h, 0Ch, 18h, 00h, 00h
 db  00h, 02h, 04h,0ECh, 40h, 20h,0F8h, 4Fh  ; "准",         168
 db  48h, 49h,0FEh, 48h, 68h, 4Ch, 08h, 00h
 db  02h, 02h, 7Fh, 00h, 00h, 00h,0FFh, 22h
 db  22h, 22h, 3Fh, 22h, 23h, 32h, 20h, 00h
 db  20h, 24h,0A8h,0FFh, 28h, 24h,0FCh, 24h  ; "粮",         169
 db  24h, 25h, 26h, 24h,0FEh, 04h, 00h, 00h
 db  08h, 06h, 01h,0FFh, 01h, 02h,0FFh, 41h
 db  23h, 05h, 09h, 19h, 25h, 62h, 20h, 00h
 db  20h, 20h, 10h,0F0h,0A8h,0A4h,0AAh,0B1h  ; "食",          170
 db 0A2h,0A4h,0A8h,0E8h, 10h, 30h, 10h, 00h
 db  00h, 00h, 00h,0FFh, 42h, 22h, 0Ah, 0Ah
 db  12h, 12h, 2Ah, 67h,0C2h, 00h, 00h, 00h
 db  00h,0FEh, 22h, 5Ah, 86h, 40h, 20h, 50h ;  "除",          171
 db  4Ch,0C3h, 4Ch, 50h, 20h, 60h, 20h, 00h
 db  00h,0FFh, 04h, 08h, 07h, 22h, 12h, 4Ah
 db  82h, 7Fh, 02h, 0Bh, 12h, 32h, 00h, 00h
 db  20h, 20h, 90h, 88h, 4Ch, 3Ah, 08h, 48h  ; "贫",           172
 db  88h, 7Bh, 04h, 88h, 10h, 30h, 10h, 00h
 db  00h, 00h, 80h, 9Fh, 41h, 41h, 21h, 1Dh
 db  21h, 21h, 41h, 5Fh, 81h, 00h, 00h, 00h
 db  00h,0FEh, 02h, 22h, 22h, 22h,0A2h,0FEh  ; "困",           173
 db  22h, 22h, 32h, 22h, 02h,0FFh, 02h, 00h
 db  00h,0FFh, 40h, 48h, 44h, 42h, 41h, 7Fh
 db  41h, 42h, 46h, 4Ch, 40h,0FFh, 00h, 00h
 db  80h, 40h, 20h,0F8h, 47h, 48h, 48h, 48h  ; "传",            174
 db 0C8h, 7Fh, 48h, 48h, 4Ch, 68h, 40h, 00h
 db  00h, 00h, 00h,0FFh, 00h, 00h, 02h, 0Bh
 db  12h, 62h,0D2h, 0Ah, 06h, 02h, 00h, 00h
 db  20h, 30h,0ACh, 63h, 30h, 88h,0C8h,0A8h  ; "统",           175
 db  99h, 8Eh, 88h,0A8h,0CCh, 88h, 00h, 00h
 db  22h, 67h, 22h, 12h, 92h, 40h, 30h, 0Fh
 db  00h, 00h, 3Fh, 40h, 40h, 41h, 70h, 00h
 db  00h,0FEh, 02h,0A2h, 92h, 9Eh, 92h, 92h ;  "医",          176
 db 0F2h, 92h, 92h, 9Ah,0D3h, 82h, 00h, 00h
 db  00h, 7Fh, 40h, 40h, 50h, 50h, 48h, 46h
 db  41h, 42h, 44h, 4Ch, 58h, 40h, 00h, 00h
 db  04h, 84h,0C4h,0A4h, 94h, 8Fh, 44h, 04h  ; "药",           177
 db  84h, 7Fh, 44h, 44h, 44h,0E6h, 44h, 00h
 db  00h, 24h, 64h, 26h, 15h, 14h, 14h, 01h
 db  00h, 02h, 4Ch, 80h, 40h, 3Fh, 00h, 00h
 db  02h, 02h,0FEh, 12h, 12h,0FEh, 02h, 11h  ; "联",           178
 db  12h, 16h,0F0h, 14h, 12h, 93h, 00h, 00h
 db  20h, 20h, 3Fh, 11h, 11h,0FFh, 91h, 41h
 db  21h, 19h, 07h, 19h, 61h,0C1h, 41h, 00h
 db  80h, 80h, 40h, 20h, 50h, 48h, 44h, 43h  ; "合",         179
 db  44h, 48h, 50h, 20h, 40h,0C0h, 40h, 00h
 db  00h, 00h, 00h,0FEh, 42h, 42h, 42h, 42h
 db  42h, 42h, 42h,0FFh, 02h, 00h, 00h, 00h
 db  02h,0E2h, 2Fh, 2Ah,0FAh, 2Ah, 2Fh,0E2h   ;"勤",         180
 db  12h, 10h,0FFh, 10h, 10h,0F8h, 10h, 00h
 db  40h, 45h, 55h, 55h, 7Fh, 55h, 55h,0C5h
 db  40h, 30h, 0Fh, 40h, 80h, 7Fh, 00h, 00h
 db  80h, 40h, 20h,0F8h, 87h, 40h, 20h, 50h  ; "俭",          181
 db  4Ch, 43h, 4Ch, 50h, 20h,0C0h, 40h, 00h
 db  00h, 00h, 00h,0FFh, 40h, 40h, 42h, 5Ch
 db  40h, 5Fh, 40h, 50h, 4Eh, 64h, 40h, 00h
 db  00h,0F8h, 08h, 08h, 08h, 08h, 08h,0FFh  ; "中",           182
 db  08h, 08h, 08h, 08h, 08h,0FCh, 08h, 00h
 db  00h, 03h, 01h, 01h, 01h, 01h, 01h,0FFh
 db  01h, 01h, 01h, 01h, 01h, 03h, 00h, 00h
 db  20h, 24h,0A8h,0FFh, 28h, 24h,0FCh, 54h  ; "糖",            183
 db  54h, 55h,0FEh, 54h, 54h,0F6h, 44h, 00h
 db  08h, 06h, 01h,0FFh, 41h, 32h, 0Fh,0FDh
 db  45h, 45h, 47h, 45h, 45h,0FDh, 00h, 00h
 db  00h, 00h,0FEh, 12h, 92h, 92h, 92h, 12h  ; "尿",          184
 db 0F2h, 12h, 92h, 12h, 12h,0BFh, 02h, 00h
 db  40h, 30h, 0Fh, 20h, 10h, 0Ch, 43h, 80h
 db  7Fh, 00h, 07h, 0Ah, 11h, 30h, 10h, 00h
 db  20h, 60h,0A0h, 2Ch,0EBh, 2Ah,0AAh, 6Ah  ; "彝",           185
 db  2Ah,0AAh,0FFh,0A2h,0A0h, 30h, 20h, 00h
 db  10h, 99h, 95h, 53h, 3Fh, 13h, 15h, 11h
 db  1Ah, 16h, 13h,0FEh, 12h, 17h, 1Ah, 00h
 db  10h, 10h,0F1h, 92h, 96h, 90h, 10h, 20h  ; "族",            186
 db  90h, 6Fh,0C8h, 48h, 6Ch, 48h, 00h, 00h
 db  40h, 30h, 0Fh, 40h, 80h, 7Fh, 04h, 86h
 db  45h, 34h, 0Fh, 34h, 44h,0C6h, 44h, 00h
 db  00h, 00h,0FCh, 84h, 84h, 84h, 84h,0FCh  ; "巴",             187
 db  84h, 84h, 84h, 84h,0FEh, 04h, 00h, 00h
 db  00h, 00h, 3Fh, 40h, 40h, 40h, 40h, 40h
 db  40h, 40h, 40h, 40h, 41h, 40h, 70h, 00h
 db  04h, 84h,0BFh,0A4h,0E4h,0A4h,0BFh, 84h  ; "勒",             188
 db  24h, 20h,0FFh, 20h, 20h,0F0h, 20h, 00h
 db  10h, 17h, 14h, 14h,0FFh, 14h, 94h, 57h
 db  30h, 1Ch, 03h, 40h, 80h, 7Fh, 00h, 00h
 db  00h, 04h,0FFh, 24h, 24h, 24h,0FFh, 04h  ; "斯",           189
 db  00h,0FCh, 44h, 42h,0C3h, 42h, 40h, 00h
 db  08h, 88h, 4Fh, 29h, 09h, 29h, 4Fh, 28h
 db  10h, 0Fh, 00h, 00h,0FFh, 00h, 00h, 00h
 db  20h, 20h, 20h,0FFh, 20h, 20h, 00h,0FCh  ; "坦",             190
 db  84h, 84h, 84h, 84h, 84h,0FEh, 04h, 00h
 db  10h, 30h, 10h, 1Fh, 48h, 48h, 40h, 5Fh
 db  48h, 48h, 48h, 48h, 48h, 5Fh, 40h, 00h
 db  04h, 04h, 04h, 04h, 44h, 9Fh, 04h, 04h ;  "艾",             191
 db  04h, 9Fh, 64h, 04h, 04h, 06h, 04h, 00h
 db  80h, 80h, 40h, 40h, 20h, 11h, 0Ah, 04h
 db  0Ah, 11h, 20h, 20h, 40h,0C0h, 40h, 00h
 db  10h, 61h, 06h, 80h, 08h,0C9h, 3Ah, 0Ch  ; "滋",             192
 db  88h, 08h,0CCh, 3Ah, 09h, 8Ch, 08h, 00h
 db  04h, 04h,0FEh, 01h, 31h, 29h, 25h, 73h
 db  00h, 31h, 29h, 25h, 23h, 70h, 00h, 00h
 db  10h, 60h, 00h,0FCh, 84h, 44h, 3Ch, 25h  ; "疾",             193
 db  26h,0E4h, 24h, 24h, 34h, 26h, 04h, 00h
 db  04h, 46h, 31h, 0Fh, 82h, 82h, 42h, 22h
 db  1Ah, 07h, 1Ah, 22h, 42h,0C3h, 42h, 00h
 db  00h,0F8h, 48h, 48h, 48h, 48h,0FFh, 48h  ; "电",            194
 db  48h, 48h, 48h,0FCh, 08h, 00h, 00h, 00h
 db  00h, 07h, 02h, 02h, 02h, 02h, 3Fh, 42h
 db  42h, 42h, 42h, 47h, 40h, 70h, 00h, 00h
 db  10h, 10h, 91h,0D6h, 30h, 10h,0FEh, 02h  ; "视",            195
 db  02h,0FAh, 02h, 02h,0FFh, 02h, 00h, 00h
 db  02h, 01h, 00h,0FFh, 01h, 82h, 47h, 30h
 db  0Ch, 03h, 3Eh, 40h, 47h, 40h, 70h, 00h
 db  00h, 00h, 00h,0FEh, 42h, 42h, 42h,0C2h  ; "足",           196
 db  42h, 42h, 42h,0FFh, 02h, 00h, 00h, 00h
 db  80h, 40h, 20h, 1Eh, 20h, 40h, 40h, 7Fh
 db  44h, 44h, 44h, 46h, 44h, 60h, 20h, 00h
 db  10h, 10h,0D0h,0FFh, 90h, 10h, 34h,0C4h  ; "权",           197
 db  04h, 04h, 04h, 84h, 7Ch, 00h, 00h, 00h
 db  04h, 03h, 00h,0FFh, 00h, 41h, 20h, 11h
 db  0Ah, 04h, 0Ah, 11h, 20h, 60h, 20h, 00h
 db  04h,0C4h, 44h, 44h, 44h,0FCh, 44h, 44h  ; "西",          198
 db  44h,0FCh, 44h, 44h, 44h,0E6h, 44h, 00h
 db  00h,0FFh, 40h, 50h, 48h, 47h, 40h, 40h
 db  40h, 47h, 48h, 48h, 40h,0FFh, 00h, 00h
 db  00h, 84h, 44h, 34h, 04h,0FCh, 05h, 06h  ; "变",           199
 db  04h,0FCh, 04h, 14h, 66h,0C4h, 00h, 00h
 db  00h, 00h, 80h, 81h, 43h, 45h, 29h, 11h
 db  29h, 25h, 43h, 41h,0C0h, 40h, 00h, 00h
 db  04h,0E4h, 24h, 24h, 64h,0A4h, 24h, 3Fh ;  "南",            200
 db  24h,0A4h, 64h, 24h, 24h,0F6h, 24h, 00h
 db  00h,0FFh, 00h, 09h, 09h, 09h, 09h, 7Fh
 db  09h, 09h, 09h, 49h, 80h, 7Fh, 00h, 00h
 db  08h, 08h, 08h,0E8h, 28h, 28h, 29h, 2Eh  ; "京",           201
 db  28h, 28h, 28h,0F8h, 28h, 0Ch, 08h, 00h
 db  00h, 00h, 40h, 23h, 1Ah, 42h, 82h, 7Eh
 db  02h, 0Ah, 12h, 33h, 60h, 00h, 00h, 00h
 db  00h, 00h,0FEh, 8Ah,0AAh,0AAh,0AAh,0FAh  ; "屠",           202
 db 0AAh,0EAh,0AAh, 9Ah, 8Fh,0C2h, 80h, 00h
 db  40h, 30h, 2Fh, 10h, 08h,0FCh, 56h, 55h
 db  54h, 54h, 54h, 54h,0FEh, 04h, 00h, 00h
 db  00h, 00h, 40h, 41h, 22h, 24h, 14h,0C8h  ; "杀",           203
 db  14h, 14h, 22h, 23h, 40h, 00h, 00h, 00h
 db  01h, 21h, 21h, 11h, 09h, 45h, 83h, 7Fh
 db  03h, 05h, 09h, 11h, 31h, 11h, 01h, 00h
 db  10h, 22h, 64h, 0Ch, 80h, 20h, 30h, 2Ch  ; "治",    204
 db  23h, 20h, 20h, 28h,0B0h, 20h, 00h, 00h
 db  04h, 04h,0FEh, 01h, 00h, 00h,0FFh, 41h
 db  41h, 41h, 41h, 41h,0FFh, 01h, 00h, 00h
 db  04h, 04h, 74h, 54h, 54h, 54h, 54h,0FFh  ;"事",   205
 db  54h, 54h, 54h, 54h, 74h, 06h, 04h, 00h
 db  04h, 04h, 15h, 15h, 15h, 55h, 95h, 7Fh
 db  15h, 15h, 15h, 15h, 3Fh, 04h, 04h, 00h
 db  00h, 00h, 00h, 00h, 80h, 70h, 18h, 04h  ;206
 db  04h, 18h, 70h, 80h, 00h, 00h, 00h, 00h
 db  00h, 00h, 0ch, 12h, 39h, 24h, 46h, 5ah
 db  5ah, 46h, 24h, 39h, 12h, 0ch, 00h, 00h
 db  00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h  ; -.-    207
 db  00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
 db  00h, 00h, 00h, 0Ch, 0Ch, 00h, 00h, 00h
 db  00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h

        end










