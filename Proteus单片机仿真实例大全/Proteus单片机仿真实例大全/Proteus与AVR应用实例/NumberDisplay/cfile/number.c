#define NUMBER_C
#include "includes.h"


void process(unsigned char i,unsigned char *p)
{
    p[0] = i/1000;
    i = i%1000;
    p[1] = i/100;
    i = i%100;
    p[2] = i/10;
    i = i%10;
    p[3] = i;
}