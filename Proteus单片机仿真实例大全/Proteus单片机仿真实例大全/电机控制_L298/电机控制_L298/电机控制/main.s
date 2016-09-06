	.module main.c
	.area text(rom, con, rel)
	.dbfile E:\avr\�������\�������\main.c
	.dbfunc e main _main fV
	.even
_main::
	.dbline -1
	.dbline 7
; //�ļ��� main.c �������ļ�
; 
; #include "config.h"
; 
; 
; void main(void)
; {
	.dbline 12
; 
; /******************************************************************************/
; //��ʼ����
; /******************************************************************************/
;   init_devices();
	xcall _init_devices
	xjmp L3
L2:
	.dbline 15
;   
;   while(1)
;   {
	.dbline 16
;    for_ward(0);	 			//Ĭ���ٶ���ת ��
	clr R16
	xcall _for_ward
	.dbline 17
;    Delay1s(5); 				//��ʱ5s
	ldi R16,5
	ldi R17,0
	xcall _Delay1s
	.dbline 18
;    motor_stop(); 			//ֹͣ
	xcall _motor_stop
	.dbline 19
;    Delay1s(5); 				//��ʱ5s
	ldi R16,5
	ldi R17,0
	xcall _Delay1s
	.dbline 20
;    back_ward(0);			//Ĭ���ٶ���ת ��
	clr R16
	xcall _back_ward
	.dbline 21
;    Delay1s(5); 				//��ʱ5s
	ldi R16,5
	ldi R17,0
	xcall _Delay1s
	.dbline 22
;    speed_add(20);			//����
	ldi R16,20
	xcall _speed_add
	.dbline 23
;    Delay1s(5); 				//��ʱ5s
	ldi R16,5
	ldi R17,0
	xcall _Delay1s
	.dbline 24
;    speed_subtract(20);		//����
	ldi R16,20
	xcall _speed_subtract
	.dbline 25
;    Delay1s(5); 				//��ʱ5s
	ldi R16,5
	ldi R17,0
	xcall _Delay1s
	.dbline 26
;   }
L3:
	.dbline 14
	xjmp L2
X0:
	.dbline -2
L1:
	.dbline 0 ; func end
	ret
	.dbend
	.area vector(rom, abs)
	.org 16
	jmp _timer2_comp_isr
	.area text(rom, con, rel)
	.dbfile E:\avr\�������\�������\main.c
	.dbfunc e timer2_comp_isr _timer2_comp_isr fV
	.even
_timer2_comp_isr::
	.dbline -1
	.dbline 37
;     
; }
; 
; /******************************************************************************/
; // T2 ����PWM���
; // timer2_comp_isr����Ҫ�ã����Ǳ��������жϣ����ж�ʱ���ź�����仯
; /******************************************************************************/
; 
; #pragma interrupt_handler timer2_comp_isr:5
; void timer2_comp_isr(void)
; {
	.dbline -2
L5:
	.dbline 0 ; func end
	reti
	.dbend
	.area vector(rom, abs)
	.org 20
	jmp _timer2_ovf_isr
	.area text(rom, con, rel)
	.dbfile E:\avr\�������\�������\main.c
	.dbfunc e timer2_ovf_isr _timer2_ovf_isr fV
	.even
_timer2_ovf_isr::
	st -y,R24
	in R24,0x3f
	st -y,R24
	.dbline -1
	.dbline 42
;    //compare occured TCNT0=OCR0
; }
; #pragma interrupt_handler timer2_ovf_isr:6
; void timer2_ovf_isr(void)
; {
	.dbline 43
;  TCNT2 = 0x01;//reload counter value
	ldi R24,1
	out 0x24,R24
	.dbline -2
L6:
	.dbline 0 ; func end
	ld R24,y+
	out 0x3f,R24
	ld R24,y+
	reti
	.dbend
; }
