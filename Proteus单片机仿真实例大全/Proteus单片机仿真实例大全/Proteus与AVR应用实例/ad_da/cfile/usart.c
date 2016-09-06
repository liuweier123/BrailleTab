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
void InitSerial(void)	//���ڳ�ʼ��
{
	// ����Ƶ�� : 4.0MHz
	// ͨ�Ų���: 8 Data, 1 Stop, No Parity 
	// ������:
	// UBRRL= 0x0C    19200;
	// UBRRL= 0x19    9600;
	// UBRRL= 0x33    4800;
	// UBRRL= 0x67    2400	
	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);  //�����ͺͽ���
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0); //8λ����λ+1λֹͣλ
	UBRRH=0x00; 
	UBRRL=0x19;  
	//sei();
    
}

