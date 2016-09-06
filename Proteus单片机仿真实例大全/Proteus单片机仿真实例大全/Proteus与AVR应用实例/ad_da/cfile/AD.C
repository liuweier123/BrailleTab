#define AD_C
#include "includes.h"
unsigned char  adc_mux = 0x01 ;

/******************************************************************************/
/******************************************************************************/
void init_adc(void)
{	
    //WDR();       //看门狗计数清零
    //WDTCR=0x0F;  //使能watchdog,并且，采用2048K分频，典型溢出时间5V时2.1S
    // ADCSRA=0X00;
    ADCSRA = 0x00; 
    ADMUX =(adc_mux&0x1f)|(1<<REFS0)|(1<<REFS1);  //参考电压为内部2.56
    //ADMUX =(adc_mux&0x1f)|(1<<REFS0);  //参考电压为内部AVCC
    //ADMUX =(adc_mux&0x1f);  //参考电压为引脚AREF
    ADCSRA=(1<<ADEN)|(1<<ADSC)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1) ;//64分频
    asm("sei");
    UBRRH = 25;
    UBRRL = 25;
    UCSRB=0x18;    
    UCSRC=0x86;	 
}

/******************************************************************************/

/******************************************************************************/
 //ADC完成中断
//#pragma vector = interrupt_handler adc_isr:iv_ADC  
// define the interrupt handler

#pragma vector=ADC_vect
    __interrupt void adc_isr( void )
{
    ADMUX =(adc_mux&0x1f)|(1<<REFS0)|(1<<REFS1);
    ADCSRA|=(1<<ADSC);//启动AD转换
}  