#include "reg51.h"
unsigned int cd,dd;
unsigned char cc,ee;


sbit LED=P2^0;
void led_int() interrupt 1 using 0
{
	TH0=0xf1;
	TL0=0xf1;
	TR0=1;
	dd++;
	if(dd==11)
	{
		if((cc==0x50)&&(ee==0)){cd=0;}
		if((cc==0)&&(ee==0x50)){cd=1;}
		if(cd){cc++;ee--;}
		else {cc--;ee++;}
		dd=0;
	}
}
void delay(unsigned int i)
{
	unsigned int j;
	while(i--)
	{
		for(j=0;j<0x20;j++);
	}
}

void main()
{
	cc=0;
	ee=0x50;
	TMOD=0x01;
	TH0=0xf0;
	TL0=0xf0 ;
	EA=1;
	ET0=1;
	TR0=1;
	while(1)
	{
		LED=0;
		delay(ee);
		LED=1;
		delay(cc);
	}
}

