
#ifndef  OS_MASTER_FILE
#include "includes.h"
#endif

void  init164(void){
    DDRB |= 0x01;
    DDRD |= 0xC0;
}

void  write164(unsigned char  x){
    unsigned char  i,ch;

    ch = x;
    PORTB &= ~0x01;      //  ÏûÒþ
    PORTD &= ~0x40;      //  CLK
    for(i=0; i<8; i++){
        if(ch & 0x80)
            PORTD |= 0x80;
        else
            PORTD &= ~0x80;
        ch <<= 1;
        PORTD |= 0x40;
        asm("nop");
        PORTD &= ~0x40;
    }
    PORTB |= 0x01;      //  ÏÔÊ¾
}