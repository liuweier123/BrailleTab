#define ISR_C
#include "includes.h"
//ADC完成中断
//#pragma vector = interrupt_handler adc_isr:iv_ADC  
// define the interrupt handler
unsigned char  adc_mux ;
#pragma vector=ADC_vect
    __interrupt void adc_isr( void )
{
    ADMUX =(adc_mux&0x1f)|(1<<REFS0);
    ADCSRA|=(1<<ADSC);//启动AD转换
}  