//�ļ��� main.c �������ļ�

#include "config.h"


void main(void)
{

/******************************************************************************/
//��ʼ����
/******************************************************************************/
  init_devices();
  
  while(1)
  {
   for_ward(0);	 			//Ĭ���ٶ���ת ��
   Delay1s(5); 				//��ʱ5s
   motor_stop(); 			//ֹͣ
   Delay1s(5); 				//��ʱ5s
   back_ward(0);			//Ĭ���ٶ���ת ��
   Delay1s(5); 				//��ʱ5s
   speed_add(20);			//����
   Delay1s(5); 				//��ʱ5s
   speed_subtract(20);		//����
   Delay1s(5); 				//��ʱ5s
  }
    
}

/******************************************************************************/
// T2 ����PWM���
// timer2_comp_isr����Ҫ�ã����Ǳ��������жϣ����ж�ʱ���ź�����仯
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