	.module device_init.c
	.area text(rom, con, rel)
	.dbfile E:\avr\电机控制\电机控制\device_init.c
	.dbfunc e port_init _port_init fV
	.even
_port_init::
	.dbline -1
	.dbline 8
; //ICC-AVR application builder : 2006-11-1 0:27:10
; // Target : M32
; // Crystal: 7.3728Mhz
; //文件名：device_init.c 各种参数初始化
; #include "config.h"
; 
; void port_init(void)
; {
	.dbline 9
;  PORTA = 0x00;
	clr R2
	out 0x1b,R2
	.dbline 10
;  DDRA  = 0x00; 
	out 0x1a,R2
	.dbline 11
;  PORTB = 0x00;
	out 0x18,R2
	.dbline 12
;  DDRB  = 0x00; 
	out 0x17,R2
	.dbline 13
;  PORTC = 0x00; 
	out 0x15,R2
	.dbline 14
;  DDRC  = 0x00;
	out 0x14,R2
	.dbline 15
;  PORTD = 0x00;
	out 0x12,R2
	.dbline 16
;  DDRD  = 0xB0; // D7 PWM   //参考芯片手册
	ldi R24,176
	out 0x11,R24
	.dbline -2
L1:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e timer2_init _timer2_init fV
	.even
_timer2_init::
	.dbline -1
	.dbline 22
; }
; 
; /**************************采用timer2 产生波形***********************/
; // PWM频率 = 系统时钟频率/（分频系数*2*计数器上限值）） 
; void timer2_init(void)
; {
	.dbline 23
;  TCCR2 = 0x00;  //stop
	clr R2
	out 0x25,R2
	.dbline 24
;  TCNT2= 0x01;  //set count
	ldi R24,1
	out 0x24,R24
	.dbline 25
;  OCR2 = 0x66;  //set compare
	ldi R24,102
	out 0x23,R24
	.dbline 26
;  TCCR2 = (1<<WGM20)|(1<<WGM21)|(1<<COM21)|0x06; //  start timer 快速pwm模式，匹配清零，溢出置位 256分频
	ldi R24,110
	out 0x25,R24
	.dbline -2
L2:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e init_devices _init_devices fV
	.even
_init_devices::
	.dbline -1
	.dbline 33
; //占空比＝高比低为：(OCR2-0X01)/(0XFF-OCR2)    OX01++++++(OCR2)__________OXFF (+表示输出高，_表示输出低)
; //即OCR2越大，输出越大
; }
; 
; //call this routine to initialize all peripherals
; void init_devices(void)
; {
	.dbline 35
;  //stop errant interrupts until set up
;  CLI(); //disable all interrupts
	cli
	.dbline 36
;  port_init();
	xcall _port_init
	.dbline 37
;  timer2_init();
	xcall _timer2_init
	.dbline 38
;  TIMSK = 0x00; //timer interrupt sources
	clr R2
	out 0x39,R2
	.dbline 39
;  SEI(); //re-enable interrupts
	sei
	.dbline -2
L3:
	.dbline 0 ; func end
	ret
	.dbend
;  //all peripherals are now initialized
; }
