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
	int i,j;
	char c=0;
	csh();
	while(1)
		{
		ES=0;
		TI=0;
		P0=c;
		SBUF=c;
		while(!TI)
		;
		TI=0;
		ES=1;
		for(j=0;j<50;j++)
		for(i=0;i<5000;i++)
		;
		c++;
		if (c>9)
		c=0;
		}
}

void intrr() interrupt 4
	{
	char temp;
	temp=SBUF;
	P2=temp;
	RI=0;
	}



