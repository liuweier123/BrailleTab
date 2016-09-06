#define INIT_C
#include "includes.h"
void InitIo(void)
{
    DDRA  = 0xff;
    PORTA = 0xff;
    DDRB  = 0x00;
    //PORTB = 0x00;
    PORTB = 0xff;
    DDRC  = 0xff;
    PORTC = 0xff;    
}