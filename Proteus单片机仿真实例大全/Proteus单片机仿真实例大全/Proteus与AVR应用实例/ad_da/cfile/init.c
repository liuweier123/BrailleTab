#define INIT_C
#include "includes.h"
int count;
float j;  
   
unsigned char *test = "The Voltage is: ";
unsigned char *value = "0.000 V";	

void WDR(void)
{
     asm("wdr");
}

void WDT_init(void)
{
   WDR();
   WDTCR = 0x0f;
}
void init_time1(void)
{
    TIMSK = 0X02;  //T1Òç³öÖÐ¶Ï
    TCCR1B = 0X00; //Í£Ö¹T1
    TCNT1H = 0XF9; //
    TCNT1L = 0XE6;
    TCCR1A = 0X00;
    TCCR1B = 0X01; 
    asm("sei");
}



#pragma vector=TIMER1_OVF_vect
    __interrupt void time1_isr( void )
{
    TCNT1H = 0XF9; //
    TCNT1L = 0XE6;
    j = (float)(((float)((Vref/1023)))*( ADC&0X3FF))/1000.00;
    count = j*100;					
    value[0] = count /1000+0x30;
    count = count %1000;
    value[2] = count /100+0x30;
    count = count %100;
    value[3] = count  /10 + 0x30;			 
    value[4] = count  %10 + 0x30;			 
      
    LCD_Cursor(0,1);
    LCD_DisplayString(2,2,value); 
}