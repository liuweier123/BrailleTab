#include <reg51.h>

//初始化串行口
void csh()
	{
	SM0=0;
	SM1=1;
	REN=1;
	TI=0;
	RI=0;
	PCON=0;
	TH1=0xF3;
	TL1=0XF3;
	TMOD=0X20;
	EA=1;
	ET1=0;
	ES=1;
	TR1=1;
	}

void main()
	{
	csh();
	while(1)
		{
		;
		}
}

void intrr() interrupt 4
	{
	char temp;
	temp=SBUF;
	P2=temp;
	RI=0;
	temp++;
	if (temp>9)
	temp=0;
	ES=0;
	TI=0;
	P0=temp;
	SBUF=temp;
	while(!TI)
	;
	TI=0;
	ES=1;
	}