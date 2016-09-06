#define HORSE_C
#include "includes.h"
void horse(unsigned char i)
{
    switch(i)
    {
        case 0: 
            OutPort = 0x00;
            break;
        case 1: 
            OutPort = 0x01;
            break;
        case 2: 
            OutPort = 0x03;
            break;
        case 3: 
            OutPort = 0x07;
            break;
        case 4: 
            OutPort = 0x0f;
            break;
        case 5: 
            OutPort = 0x1f;
            break;
       case 6: 
            OutPort = 0x3f;
            break;
       case 7: 
            OutPort = 0x7f;
            break;
       case 8: 
            OutPort = 0xff;
            break;
       default: 
            break;
    }    
}