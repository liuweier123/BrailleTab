#define USART_C
#include "includes.h"
void put_char(unsigned char ch)
{
   /* if(ch == '\n')
    {
        usart_putchar('\r');
    } */      
    while(!(UCSRA&(1<<UDRE)));   
    UDR = ch;     
}
void put_string(unsigned char *string)
{
    while(*string)
    {
        put_char(*string++);
    }    
 }
void InitSerial(void)	//串口初始化
{
	// 晶振频率 : 4.0MHz
	// 通信参数: 8 Data, 1 Stop, No Parity 
	// 波特率:
	// UBRRL= 0x0C    19200;
	// UBRRL= 0x19    9600;
	// UBRRL= 0x33    4800;
	// UBRRL= 0x67    2400	
	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);  //允许发送和接收
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0); //8位数据位+1位停止位
	UBRRH=0x00; 
	UBRRL=0x19;  
	//sei();
    
}

