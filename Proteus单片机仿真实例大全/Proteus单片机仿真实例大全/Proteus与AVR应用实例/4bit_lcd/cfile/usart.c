#define USART_C
#include "includes.h"
int usart_putchar(char c)
{
	if (c == '\n')
		usart_putchar('\r');
	while(UCSRA&(1<<5));//UDRE
	//loop_until_bit_is_set(UCSRA, UDRE);
	UDR = c;
	return 0;

}

void init_usart(void)
{
	// USART initialization
	// Communication Parameters: 8 Data, 1 Stop, No Parity
	// USART Receiver: Off
	// USART Transmitter: On
	// USART Mode: Asynchronous
	// USART Baud rate: 19200
	UCSRA=0x00;
	UCSRB=0x08;
	UCSRC=0x86;
	UBRRH=0x00;
	UBRRL=0x0C;
	
	//fdevopen(usart_putchar, NULL, 0);
}


