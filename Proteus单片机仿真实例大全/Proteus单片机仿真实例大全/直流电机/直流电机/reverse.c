#include"reg51.h"
#include"intrins.h"
#define uchar unsigned char
#define uint  unsigned int

sbit P20=P2^0;
sbit P21=P2^1;


extern uchar flag;/***高低电平标志***/
extern bit direction;/***方向标志***/

/*****改变转向*****/
void reverse(void)
{
	if(direction==0)	/**顺时针转**/
	{
		P21=0;
		if(flag==1)
		{
			flag=0;
			P20=0;
		}
		if(flag==2)
		{
			flag=0;
			P20=1;	
		}
	}
	if(direction==1)	/**逆时针转**/
	{
		P20=0;
		if(flag==1)
		{
			flag=0;
			P21=0;
		}
		if(flag==2)
		{
			flag=0;
			P21=1;	
		}
	}
	
}