#include"reg51.h"
#include"intrins.h"
#define uchar unsigned char
#define uint  unsigned int

sbit P20=P2^0;
sbit P21=P2^1;


extern uchar flag;/***�ߵ͵�ƽ��־***/
extern bit direction;/***�����־***/

/*****�ı�ת��*****/
void reverse(void)
{
	if(direction==0)	/**˳ʱ��ת**/
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
	if(direction==1)	/**��ʱ��ת**/
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