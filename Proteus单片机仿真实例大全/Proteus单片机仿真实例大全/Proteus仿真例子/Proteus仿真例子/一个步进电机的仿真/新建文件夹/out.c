#include<reg51.h>
#include<absacc.h>
#define uint unsigned int
#define uchar unsigned char
//#define PORT XBYTE[0xffc0]
void delay(uint x);
void out(char state)
{
	code uchar table[]={0x03,0x09,0x0c,0x06}; //反转
//	code uchar table[]={0x03,0x06,0x0C,0x09};//正转
	P1=table[state];
//	PORT=table[state];
	delay(8);
}


uchar phase=0;
//out(uchar x);
void main()
{
	for(;;)
	{
			out(phase=++phase&0x03);//调用输出函数
	}
}

void delay(uint x)
{
	uchar j;
	while(x-->0)
	{
		for(j=0;j<125;j++)
		{;;}
	}
}
