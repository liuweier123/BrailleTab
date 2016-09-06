	.module main.c
	.area text(rom, con, rel)
	.dbfile D:\AVR\ICC\usart_t\main.c
	.dbfunc e uart0_init _uart0_init fV
	.even
_uart0_init::
	.dbline -1
	.dbline 17
; //ICC-AVR application builder : 2005-9-4 20:55:51
; // Target : M16
; // Crystal: 8.0000Mhz
; 
; #include <iom16v.h>
; #include <macros.h>
; #include <stdio.h>
; 
; void delay_nms(unsigned int n);
; 
; //UART0 initialize
; // desired baud rate: 9600
; // actual: baud rate:9615 (0.2%)
; // char size: 8 bit
; // parity: Disabled
; void uart0_init(void)
; {
	.dbline 18
;  UCSRB = 0x00; //disable while setting baud rate
	clr R2
	out 0xa,R2
	.dbline 19
;  UCSRA = 0x00;
	out 0xb,R2
	.dbline 20
;  UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);//8位数据+1位STOP位
	ldi R24,134
	out 0x20,R24
	.dbline 21
;  UBRRL = 0x33; //set baud rate lo
	ldi R24,51
	out 0x9,R24
	.dbline 22
;  UBRRH = 0x00; //set baud rate hi
	out 0x20,R2
	.dbline 23
;  UCSRB = (1<<RXEN)|(1<<TXEN);//允许发送和接收
	ldi R24,24
	out 0xa,R24
	.dbline -2
L1:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e main _main fV
;              i -> R20
	.even
_main::
	.dbline -1
	.dbline 27
; }
; 
; void main(void)
; {
	.dbline 29
;  unsigned char i;
;  uart0_init(); 
	xcall _uart0_init
	.dbline 30
;  puts("ATmega16 uart Test!");
	ldi R16,<L3
	ldi R17,>L3
	xcall _puts
	.dbline 31
;  putchar(0x0d);
	ldi R16,13
	xcall _putchar
	.dbline 32
;  putchar(0x0a);
	ldi R16,10
	xcall _putchar
	xjmp L5
L4:
	.dbline 34
;  while(1)
;  {
	.dbline 35
; 	for(i=0;i<20;i++)
	clr R20
	xjmp L10
L7:
	.dbline 36
	.dbline 37
	mov R16,R20
	subi R16,208    ; addi 48
	xcall _putchar
	.dbline 38
	ldi R16,1000
	ldi R17,3
	xcall _delay_nms
	.dbline 39
L8:
	.dbline 35
	inc R20
L10:
	.dbline 35
	cpi R20,20
	brlo L7
	.dbline 40
L5:
	.dbline 33
	xjmp L4
X0:
	.dbline -2
L2:
	.dbline 0 ; func end
	ret
	.dbsym r i 20 c
	.dbend
	.area data(ram, con, rel)
	.dbfile D:\AVR\ICC\usart_t\main.c
L3:
	.blkb 20
	.area idata
	.byte 'A,'T,'m,'e,'g,'a,49,54,32,'u,'a,'r,'t,32,'T,'e
	.byte 's,'t,33,0
	.area data(ram, con, rel)
	.dbfile D:\AVR\ICC\usart_t\main.c
