#define ENABLE_BIT_DEFINITIONS

#include "includes.h"



//#define Vref 50000
void init_adc(void);
void WDR(void);
void WDT_init(void);

//unsigned char adc_mux = 0x01;  //通道选择

unsigned char RSend;
unsigned char RS_buf[10];
unsigned char RS_flag;
void main(void)
{       
    float j;  
    int count;
    unsigned char *test = "The Voltage is: ";
    unsigned char *value = "0.000 V";	
    unsigned char *RS;
    RS = RS_buf;
    RS_flag = 0;
    delay_nms(1);   
    //dataport=0xff;
    OSCCAL=0Xab;//系统时钟校准，不同的芯片和不的频率，
    init_adc();	
    InitSerial();    
    //init_time1();
    Init_LCD();  
   // WDT_init();
          
    LCD_DisplayString(1,1,test);    
    LCD_DisplayString(2,1,value);    
    put_string(value);  
    put_char(0x0d);
    put_char(0x0a);     
    while(1) 
    {        
       // j = (float)(((float)((Vref/1023)))*(ADCH*256+ADCL))/1000.00;
        j = (float)(((float)((Vref/1023)))*( ADC&0X3FF))/1000.00;
	count = j*100;					
        value[0] = count /1000+0x30;
        count = count %1000;
        value[2] = count /100+0x30;
        count = count %100;
        value[3] = count  /10 + 0x30;			 
        value[4] = count  %10 + 0x30;			 
      
        LCD_Cursor(0,1);
        LCD_DisplayString(2,1,value);  
        put_string(value); 
        put_char(0x0d);
        put_char(0x0a);        
        delay_nms(1000);       
         if(RS_flag)
        {
            LCD_DisplayString(2,10,RS);
            RS_flag = 0;
        }
    }
	
}

#pragma vector = USART_RXC_vect
    __interrupt void usart_isr( void )
{
    SREG &= !(1<<7);
    RS_flag = 1;
    RSend++;
    RS_buf[RSend] = UDR;
    put_char(RS_buf[RSend]);
    if(RSend>=10)
    {
        RSend = 0;
    } 
    SREG |= (1<<7);   
}


