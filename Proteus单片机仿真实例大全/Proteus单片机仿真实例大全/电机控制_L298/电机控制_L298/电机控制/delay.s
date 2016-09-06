	.module delay.c
	.area text(rom, con, rel)
	.dbfile E:\avr\电机控制\电机控制\delay.c
	.dbfunc e Delay100us _Delay100us fV
;              i -> R20
;              x -> R16
	.even
_Delay100us::
	st -y,R20
	.dbline -1
	.dbline 8
; // 文件名 delay.c 延时
; 
; #include "config.h"
; /***************************************************************************
; 延时 M32 7.3728M 粗略计算
; */
; void Delay100us(uint8 x)
; {
	.dbline 10
; 	uint8 i;          //4clock                   
; 	for(i=147;x!=0;x--)	
	ldi R20,147
	xjmp L5
L6:
	.dbline 11
; 	while(--i);      //5 * i clock
L7:
	.dbline 11
	mov R24,R20
	subi R24,1
	mov R20,R24
	tst R24
	brne L6
X0:
L3:
	.dbline 10
	dec R16
L5:
	.dbline 10
	tst R16
	brne L7
X1:
	.dbline -2
L1:
	.dbline 0 ; func end
	ld R20,y+
	ret
	.dbsym r i 20 c
	.dbsym r x 16 c
	.dbend
	.dbfunc e Delay1ms _Delay1ms fV
;              n -> R20,R21
	.even
_Delay1ms::
	st -y,R20
	st -y,R21
	movw R20,R16
	.dbline -1
	.dbline 14
; }
; void Delay1ms(uint16 n)
; {        
	.dbline 15
; 	for (;n!=0;n--){
	xjmp L13
L10:
	.dbline 15
	.dbline 16
; 		Delay100us(10);
	ldi R16,10
	xcall _Delay100us
	.dbline 17
; 	}
L11:
	.dbline 15
	subi R20,1
	sbci R21,0
L13:
	.dbline 15
	cpi R20,0
	cpc R20,R21
	brne L10
X2:
	.dbline -2
L9:
	.dbline 0 ; func end
	ld R21,y+
	ld R20,y+
	ret
	.dbsym r n 20 i
	.dbend
	.dbfunc e Delay1s _Delay1s fV
;              m -> R20,R21
	.even
_Delay1s::
	st -y,R20
	st -y,R21
	movw R20,R16
	.dbline -1
	.dbline 20
; }
; void Delay1s(uint16 m)         //  m <= 6 ,when m==7, it is 1. 
; {
	.dbline 21
; 	m=m*40;                
	ldi R16,40
	ldi R17,0
	movw R18,R20
	xcall empy16s
	movw R20,R16
	.dbline 22
; 	for (;m!=0;m--){
	xjmp L18
L15:
	.dbline 22
	.dbline 23
; 		Delay100us(250);
	ldi R16,250
	xcall _Delay100us
	.dbline 24
; 	}
L16:
	.dbline 22
	subi R20,1
	sbci R21,0
L18:
	.dbline 22
	cpi R20,0
	cpc R20,R21
	brne L15
X3:
	.dbline -2
L14:
	.dbline 0 ; func end
	ld R21,y+
	ld R20,y+
	ret
	.dbsym r m 20 i
	.dbend
; }
