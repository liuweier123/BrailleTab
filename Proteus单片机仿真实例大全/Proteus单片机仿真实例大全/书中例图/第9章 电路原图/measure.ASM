.DEVICE AT90S8515                  ;最大测频值为999999
RJMP   START
.EQU B20D  =0
.EQU DDRA  =$1A
.EQU PORTA =$1B
.EQU PORTB =$18
.EQU DDRB  =$17
.EQU PINB  =$16
.EQU DDRC  =$14
.EQU PORTC =$15
.EQU DDRD  =$11
.EQU PORTD =$12
.EQU TCCR0 =$33
.EQU TIMSK =$39
.EQU TCCR1B=$2E
.EQU TCNT0 =$32
.EQU SPL   =$3D
.EQU UBRR  =$09
.EQU UCR   =$0A
.EQU USR   =$0B
.EQU UDR   =$0C                     
.DEF TEMP  =R16
.DEF CNT1D =R17                     ;存放结果的十进制数据
.DEF CNT2D =R18
.DEF CNT3D =R19
.DEF COUNT =R20
.DEF CNT   =R21
.DEF RES1  =R22                     ;存放结果的十六进制数据
.DEF RES2  =R23
.DEF RES3  =R24
.DEF DT    =R25
.DEF OVF1  =R26
.DEF AA    =R27
.DEF ZL    =R30
.DEF ZH    =R31                     
.CSEG
.org    0x003                        ;icp触发中断向量
	rjmp   captr

.org    0x007                        ;timer0触发中断向量
	rjmp   interru
captr:                               ;icp触发中断子程序
	brts  b
	inc   res1
	ldi   temp,  0b00000101
	out   tccr0, temp            ;开timer0
	ldi   temp,  0b00001010
	out   timsk, temp            ;致timer0中断和捕捉中断
	ldi   temp,  0b11000000
	out   tccr1b,temp
	set
	reti
b:
	set
	inc   res1                   ;开始计数
	brne  c
	inc   res2
	brne  c
	inc   res3
	cpse  res3,  ovf1            ;溢出处理
	rjmp  c
	rjmp  over1
c:
	ldi   temp,  0b00001010
	out   timsk, temp
	ldi   temp,  0b11000000
	out   tccr1b,temp
	reti
interru:                             ;timer0溢出中断子程序
	dec   cnt
	breq  over
	ldi   temp,   0b00001010
	out   timsk,  temp
	reti
over:
        rcall ds18b20
        rcall dsent
	rcall htd3
over1:	
	rcall sys
	reti
start:
	ldi   temp,  $5f
	out   spl,   temp
	ldi   temp,  $02             ;设置堆栈
	out   spl+1, temp
        ldi   temp,  $ff
        out   ddrd,  temp            ;初始化数码管状态
	out   ddra,  temp            ;A口:数码管数据输出
        out   ddrc,  temp
	ldi   temp,  $00
	out   porta, temp            ;共阴极,数码管全灭
	out   portc, temp
        out   portd, temp
	ldi   cnt1d, 00
	ldi   cnt2d, 00
	ldi   cnt3d, 00
	sei
	rcall sys
loop:                                 ;在数码管显出十进制数
	mov   aa,   cnt1d
	andi  aa,   $0f               ;显示个位
	rcall a
	cbi   portc, 00
	nop
	sbi   portc, 00
	mov   aa,  cnt1d
	andi  aa,  $f0                 ;显示十位
	swap  aa
	rcall a
	cbi   portc, 01
	nop
	sbi   portc, 01
	mov   aa,  cnt2d
	andi  aa,  $0f                 ;显示百位
	rcall a
	cbi   portc, 02
	nop
	sbi   portc, 02
	mov   aa,  cnt2d
	andi  aa,  $f0                 ;显示千位
	swap  aa
	rcall a
	cbi   portc, 03
	nop
	sbi   portc, 03
	mov   aa,  cnt3d
	andi  aa,  $0f                 ;显示万位
	rcall a
	cbi   portc, 04
	nop
	sbi   portc, 04
	mov   aa,  cnt3d
	andi  aa,  $f0                 ;显示十万位
	swap  aa
	rcall a
	cbi   portc, 05
	nop
	sbi   portc, 05
        sbrc  dt,    0
	ret
	rjmp  loop
sys:                                    ;初始化
	clc
	clt
	ldi   dt,    00
	ldi   ovf1,  $0f
	ldi   cnt,   31
	ldi   temp,  123
	out   tcnt0, temp
	ldi   temp,  0b00001000
	out   timsk, temp
	ldi   temp,  0b11000000
	out   tccr1b,temp
        ldi   temp ,51
        out   UBRR,temp                ;波特率确定为9600b/ s
        ldi   temp ,$98
        out   UCR ,temp                ;UART设置为发送、接收使能
	ret
DS18B20:   
         RCALL RES0           ;初始化18B20
         LDI R28,$CC          ;跳过内部ROM 命令
         RCALL W18B20
         LDI R28,$44          ;启动A/D转换命令
         RCALL W18B20
         RCALL RES0           ;18B20 初始化
         LDI R28,$CC          ;跳过内部ROM 命令
         RCALL W18B20
         LDI R28,$BE          ;读RAM 命令
         RCALL W18B20
         RCALL R18B20         ;读出温度的低字节并暂存
         MOV R0,R29
         RCALL R18B20         ;读出温度的高字节并暂存
         MOV R1,R29
         RET

RES0:     SBI DDRB,B20D       ;初始化子程序,将数据线B20D 拉低
          LDI R16,240         ;并延时约480μs
DELAY:    NOP
          NOP
          NOP
          NOP
          NOP
          NOP
          DEC R16
          BRNE DELAY
          LDI R16,239
DELAY1:   NOP
          NOP
          NOP
          NOP
          NOP
          NOP
          DEC R16
          BRNE DELAY1         
          CBI DDRB,B20D       ;释放B20D 信号(即将PINB7引脚拉高)
          LDI R16,240         ;并延时约480μs
DELAY2:   NOP
          NOP
          NOP
          NOP
          NOP
          NOP
          DEC R16
          BRNE DELAY2
          LDI R16,239
DELAY3:   NOP
          NOP
          NOP
          NOP
          NOP
          NOP
          DEC R16
          BRNE DELAY3
RET

W18B20:  LDI R29,8             ;写18B20 子程序
         CLC
WB201 :  CBI DDRB,B20D         ;将数据线拉高
         LDI R16,1             ;约1μs
DELAY4:  NOP
         NOP
         NOP
         NOP
         NOP
         NOP
         DEC R16
         BRNE DELAY4
         SBI DDRB,B20D         ;将数据线拉低产生写信号下降沿
         LDI R16,6             ;拉低约4*3 = 6μs
DELAY5:  NOP
         NOP
         NOP
         NOP
         NOP
         NOP
         DEC R16
         BRNE DELAY5
         ROR R28               ;将发送数据低位移到进位位发送
         BRCC WB202
         CBI DDRB,B20D         ;将数据线拉高
WB202 :  LDI R16,64            ;发送位延时约64μs
DELAY6:  NOP
         NOP
         NOP
         NOP
         NOP
         NOP
         DEC R16
         BRNE DELAY6
         DEC R29
         BRNE WB201
         CBI DDRB,B20D         ;将数据线拉高
RET      

R18B20:  LDI R29,$80           ;读18B20 子程序
RB201 :  CBI DDRB,B20D         ;将数据线拉高
         LDI R16,1             ;拉高约1μs
DELAY7:  NOP
         NOP
         NOP
         NOP
         NOP
         NOP
         DEC R16
         BRNE DELAY7
         SBI DDRB,B20D         ;将数据线拉低产生读信号下降沿
         LDI R16,6
DELAY8:  NOP
         NOP
         NOP
         NOP
         NOP
         NOP
         DEC R16
         BRNE DELAY8
         CBI DDRB,B20D         ;将数据线拉高
         LDI R16,8
DELAY9:  NOP
         NOP
         NOP
         NOP
         NOP
         NOP
         DEC R16
         BRNE DELAY9
         SEC
         SBIS PINB,B20D
         CLC
         ROR R29
         LDI R16,56
DELAY10: NOP
         NOP
         NOP
         NOP
         NOP
         NOP
         DEC R16
         BRNE DELAY10
         BRCC RB201
         CBI DDRB,B20D         ;将数据线拉高
         RET
htd3:                          ;16转10子程序
	sbr   dt,1
	ldi   count, 24
	clr   cnt1d
	clr   cnt2d
	clr   cnt3d
loopd:
	rol   res1
	rol   res2
	rol   res3

	rol   cnt1d
	rol   cnt2d
	rol   cnt3d
	dec   count
	brne  d	
	rjmp  loop
d:
	rcall adjn
	rjmp  loopd
a:
	ldi   zh,    high(zk*2)
	ldi   zl,    low(zk*2)
	add   zl,    aa
	lpm
	out   porta, r0	
	ret
adjn:
	push  count
	mov   count,  cnt1d
	rcall adjd1
	mov   cnt1d,  count
	mov   count,  cnt2d
	rcall adjd1
	mov   cnt2d,  count
	mov   count,  cnt3d
	rcall adjd1
	mov   cnt3d,  count
	pop   count
	ret
adjd1:
	ldi   temp,  3
	add   temp,  count
	sbrc  temp,  3
	mov   count, temp
	ldi   temp,  $30
	add   temp,  count
	sbrc  temp,  7
	mov   count, temp
	ret

dsent:     
Txcx:      sbis USR ,5
           rjmp Txcx          ;UART 数据寄存器空则发送帧头
           ldi R16,$7f
           out UDR ,R16
Txck:      sbis USR ,5
           rjmp Txck
           ldi R16,$00
           out UDR,R16
Txca:      sbis USR ,5
           rjmp Txca          ;UART 数据寄存器空则发送数据帧
           out UDR ,R1
Txcb:      sbis USR ,5
           rjmp Txcb
           out UDR ,R0
Txcc:      sbis USR ,5
           rjmp Txcc
           out UDR ,RES2
Txcd:      sbis USR ,5
           rjmp Txcd
           out UDR ,RES1
Txcz:      sbis USR ,5
           rjmp Txcz          ;UART 数据寄存器空则发送帧尾
           ldi R16,$f7
           out UDR,R16
Sendend:   ret

.equ   zk=0x0200
.org   zk                             ;字形表
.db    0x03f,0x006,0x05b,0x04f
.db    0x066,0x06d,0x07d,0x007
.db    0x07f,0x06f