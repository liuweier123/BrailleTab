#include "includes.h"
#define USART_C

int usart_putchar(char c)
{
	if (c == '\n')
		usart_putchar('\r');
	while(UCSRA & (1 << 5));   //loop_until_bit_is_set(UCSRA,5);
	UDR = c;
	return 0;

}

void init_usart(void)
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




