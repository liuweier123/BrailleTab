#include <at89x51.h>

#define TIME0H 0x9C		//0.1ms

unsigned char uca_SinaCode[]=
							{0x7F,0x8C,0x9A,0xA6,0xB3,0xBF,0xCA,0xD4,0xDE,0xE6,
							0xED,0xF3,0xF8,0xFC,0xFE,0xFE
,0xFE,0xFC,0xF8,0xF3,0xED,0xE6,0xDE,0xD4,0xCA,0xBF,0xB3,0xA6,0x9A,0x8C,0x7F,0x72
,0x64,0x58,0x4B,0x3F,0x34,0x2A,0x20,0x18,0x11,0x0B,0x06,0x02,0x00,0x00,0x00,0x02
,0x06,0x0B,0x11,0x18,0x20,0x2A,0x34,0x3F,0x4B,0x58,0x64,0x72,0x7F};


	unsigned char ucCount=0;


void main()
{
	TMOD=0x02;
	TH0=TIME0H;

	TR0=1;
	ET0=1;
	EA=1;
	
	P2_0=0;

	while(1);
}


void Time0() interrupt 1
{
	P0=uca_SinaCode[ucCount];
	if(ucCount==61)
		ucCount=0;
	else
		ucCount++;
}
