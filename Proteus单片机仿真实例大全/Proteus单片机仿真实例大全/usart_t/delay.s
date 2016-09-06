	.module delay.c
	.area text(rom, con, rel)
	.dbfile D:\AVR\ICC\usart_t\delay.c
	.dbfunc e delay_1us _delay_1us fV
	.even
_delay_1us::
	.dbline -1
	.dbline 6
;    /*-----------------------------------------------------------------------
; 延时函数
; 系统时钟：8M
; -----------------------------------------------------------------------*/
; void delay_1us(void)                 //1us延时函数
;   {
	.dbline 7
;    asm("nop");
	nop
	.dbline -2
L1:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e delay_nus _delay_nus fV
;              i -> R20,R21
;              n -> R22,R23
	.even
_delay_nus::
	xcall push_gset2
	movw R22,R16
	.dbline -1
	.dbline 11
;   }
; 
; void delay_nus(unsigned int n)       //N us延时函数
;   {
	.dbline 12
;    unsigned int i=0;
	clr R20
	clr R21
	.dbline 13
;    for (i=0;i<n;i++)
	xjmp L6
L3:
	.dbline 14
	xcall _delay_1us
L4:
	.dbline 13
	subi R20,255  ; offset = 1
	sbci R21,255
L6:
	.dbline 13
	cp R20,R22
	cpc R21,R23
	brlo L3
	.dbline -2
L2:
	xcall pop_gset2
	.dbline 0 ; func end
	ret
	.dbsym r i 20 i
	.dbsym r n 22 i
	.dbend
	.dbfunc e delay_1ms _delay_1ms fV
;              i -> R16,R17
	.even
_delay_1ms::
	.dbline -1
	.dbline 18
;    delay_1us();
;   }
;   
; void delay_1ms(void)                 //1ms延时函数
;   {
	.dbline 20
	clr R16
	clr R17
	xjmp L11
L8:
	.dbline 20
L9:
	.dbline 20
	subi R16,255  ; offset = 1
	sbci R17,255
L11:
	.dbline 20
;    unsigned int i;
;    for (i=0;i<1140;i++);
	cpi R16,116
	ldi R30,4
	cpc R17,R30
	brlo L8
	.dbline -2
L7:
	.dbline 0 ; func end
	ret
	.dbsym r i 16 i
	.dbend
	.dbfunc e delay_nms _delay_nms fV
;              i -> R20,R21
;              n -> R22,R23
	.even
_delay_nms::
	xcall push_gset2
	movw R22,R16
	.dbline -1
	.dbline 24
;   }
;   
; void delay_nms(unsigned int n)       //N ms延时函数
;   {
	.dbline 25
;    unsigned int i=0;
	clr R20
	clr R21
	.dbline 26
;    for (i=0;i<n;i++)
	xjmp L16
L13:
	.dbline 27
	xcall _delay_1ms
L14:
	.dbline 26
	subi R20,255  ; offset = 1
	sbci R21,255
L16:
	.dbline 26
	cp R20,R22
	cpc R21,R23
	brlo L13
	.dbline -2
L12:
	xcall pop_gset2
	.dbline 0 ; func end
	ret
	.dbsym r i 20 i
	.dbsym r n 22 i
	.dbend
