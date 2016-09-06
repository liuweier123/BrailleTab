#define USART_C
#include "includes.h"
void UsartInit(void)
{
    // 晶振频率 : 4.0MHz
    // 通信参数: 8 Data, 1 Stop, No Parity 
    // 波特率:
    // UBRRL= 0x0C    19200;
    // UBRRL= 0x19    9600;
    // UBRRL= 0x33    4800;
    // UBRRL= 0x67    2400	
    UCSRB |= (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);  //允许发送和接收,接收中断使能
    UCSRC |= (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0); //8位数据位+1位停止位
    UBRRH = 0x00; 
    UBRRL = 0x19;  
    //sei();
}

int PutChar(char c)
{
    if(c == '\n')
    {
        PutChar('\r');
    }
    UDR = c;
    while(!(UCSRA &(1<<UDRE)));
    UCSRA |= (1<<UDRE);
    return 0;
}


void SendNbyte(unsigned char *p,unsigned char L)
{
    unsigned char w;
    for(w=0;w<L;w++)
    {
       // UDR = *(p+w);
       // while(!(UCSRA &(1<<UDRE)));
        //UCSRA |= (1<<UDRE);
        PutChar(*(p+w));
    }
    
}

void PutStr(unsigned char *Str)
{
    while(*Str != '\0')
    {
        PutChar(*Str);
        Str++;
    }
}