	.module motor.c
	.area text(rom, con, rel)
	.dbfile E:\avr\电机控制\电机控制\motor.c
	.dbfunc e for_ward _for_ward fV
;          speed -> R16
	.even
_for_ward::
	.dbline -1
	.dbline 9
; /****************************************************************
; ** 文件名：motor.c   电机驱动函数
; ****************************************************************/
; #include "config.h"
; 
; /******************************************************************************/
; //正转，速度
; void for_ward(uint8 speed)
; {
	.dbline 10
;  	 if(speed!=0)
	tst R16
	breq L2
X0:
	.dbline 11
;  	  {
	.dbline 12
;   	   OCR2 = speed;
	out 0x23,R16
L4:
	.dbline 13
;   	   while(ASSR&(1<<TCR2UB)==1) ; //启动TC2 pwm 输出，异步操作需要等待 OCR2写入完毕
L5:
	.dbline 13
	in R2,0x22
	sbrc R2,0
	rjmp L4
X1:
	.dbline 14
;   	  }
L2:
	.dbline 15
;  	 TC2_EN;   //pwm_start
	in R24,0x39
	ori R24,192
	out 0x39,R24
	.dbline 16
;  	 moto_en1;
	sbi 0x12,4
	.dbline 17
;  	 moto_uen2;
	cbi 0x12,5
	.dbline -2
L1:
	.dbline 0 ; func end
	ret
	.dbsym r speed 16 c
	.dbend
	.dbfunc e back_ward _back_ward fV
;          speed -> R16
	.even
_back_ward::
	.dbline -1
	.dbline 22
; }
; /******************************************************************************/
; //反转，速度
; void back_ward(uint8 speed)
; {
	.dbline 23
;  	 if(speed!=0)
	tst R16
	breq L8
X2:
	.dbline 24
;   	{
	.dbline 25
;        OCR2 = speed;
	out 0x23,R16
L10:
	.dbline 26
;   	   while(ASSR&(1<<TCR2UB)==1) ;// 启动TC2 pwm 输出，异步操作需要等待OCR2写入完毕
L11:
	.dbline 26
	in R2,0x22
	sbrc R2,0
	rjmp L10
X3:
	.dbline 27
;     }
L8:
	.dbline 28
;    TC2_EN;   //pwm start
	in R24,0x39
	ori R24,192
	out 0x39,R24
	.dbline 29
;    moto_uen1;
	cbi 0x12,4
	.dbline 30
;    moto_en2;
	sbi 0x12,5
	.dbline -2
L7:
	.dbline 0 ; func end
	ret
	.dbsym r speed 16 c
	.dbend
	.dbfunc e motor_stop _motor_stop fV
	.even
_motor_stop::
	.dbline -1
	.dbline 35
; }
; /******************************************************************************/
; //停止
; void motor_stop(void)
; {
	.dbline 36
;  moto_en1;   //同时置一停止
	sbi 0x12,4
	.dbline 37
;  moto_en2;
	sbi 0x12,5
	.dbline 38
;  TC2_DIS;    //pwm stop
	in R24,0x39
	andi R24,127
	out 0x39,R24
	.dbline -2
L13:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e speed_add _speed_add fV
;            add -> R16
	.even
_speed_add::
	.dbline -1
	.dbline 44
; }
; /******************************************************************************/
; 
; //加速
; void speed_add(uint8 add)
; {
	.dbline 45
;  if(OCR2 + add < 240) //防止出现极大情况时候跳跃到很小。
	in R24,0x23
	add R24,R16
	cpi R24,240
	brsh L15
X4:
	.dbline 46
;  {
	.dbline 47
;    OCR2 = OCR2 + add;
	in R2,0x23
	add R2,R16
	out 0x23,R2
	.dbline 48
;  }
L15:
	.dbline -2
L14:
	.dbline 0 ; func end
	ret
	.dbsym r add 16 c
	.dbend
	.dbfunc e speed_subtract _speed_subtract fV
;       subtract -> R16
	.even
_speed_subtract::
	.dbline -1
	.dbline 54
; }
; /******************************************************************************/
; 
; //加速
; void speed_subtract(uint8 subtract)
; {
	.dbline 55
;  if(OCR2 - subtract > 10) //防止到很小之后跳跃到很大。
	in R2,0x23
	sub R2,R16
	ldi R24,10
	cp R24,R2
	brsh L18
X5:
	.dbline 56
;  {
	.dbline 57
;   OCR2 = OCR2 - subtract;
	in R2,0x23
	sub R2,R16
	out 0x23,R2
	.dbline 58
;  }
L18:
	.dbline -2
L17:
	.dbline 0 ; func end
	ret
	.dbsym r subtract 16 c
	.dbend
; }
; /******************************************************************************/
; 
