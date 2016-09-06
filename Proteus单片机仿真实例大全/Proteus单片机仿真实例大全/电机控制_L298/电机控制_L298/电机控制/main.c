//文件名 main.c 工程主文件

#include "config.h"


void main(void)
{

/******************************************************************************/
//初始工作
/******************************************************************************/
  init_devices();
  
  while(1)
  {
   for_ward(0);	 			//默认速度运转 正
   Delay1s(5); 				//延时5s
   motor_stop(); 			//停止
   Delay1s(5); 				//延时5s
   back_ward(0);			//默认速度运转 反
   Delay1s(5); 				//延时5s
   speed_add(20);			//加速
   Delay1s(5); 				//延时5s
   speed_subtract(20);		//减速
   Delay1s(5); 				//延时5s
  }
    
}

/******************************************************************************/
// T2 控制PWM输出
// timer2_comp_isr不需要用，但是必须允许中断，在中断时有信号输出变化
/******************************************************************************/

#pragma interrupt_handler timer2_comp_isr:5
void timer2_comp_isr(void)
{
   //compare occured TCNT0=OCR0
}
#pragma interrupt_handler timer2_ovf_isr:6
void timer2_ovf_isr(void)
{
 TCNT2 = 0x01;//reload counter value
}