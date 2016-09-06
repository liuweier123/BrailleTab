#define DELAY_C
#include "includes.h"
#define XTAL 4    //����Ƶ�ʣ���λMHz
void delay_1us(void)                 //1us��ʱ����
  {
   asm("nop");
  }

void delay_nus(unsigned int n)       //N us��ʱ����
  {
   unsigned int i=0;
   for (i=0;i<n;i++)
   delay_1us();
  }
  
void delay_1ms(void)                 //1ms��ʱ����
  {
   unsigned int i;
   for (i=0;i<(unsigned int)(XTAL*143-2);i++);
  }
  
void delay_nms(unsigned int n)       //N ms��ʱ����
  {
   unsigned int i=0;
   for (i=0;i<n;i++)
   {
      delay_1ms();
   }   
  }
        
  