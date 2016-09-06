#include <reg51.h>

#define x 1			//修正系数
#define p 2		//放大倍数
void main()
	{
	int i,j;
	EA=1;
	EX0=1;
	IT0=1;
	P3_0=0;
	P3_1=0;
	P0=0;
	P2=0;
	while(1)
	{
	for (j=0;j<1;j++)		//采样延迟，可以用定时器比较准确
	for (i=0;i<500;i++)
		;
	P3_0=1;					//地址锁存
	for (i=0;i<50;i++)
	;
	P3_1=1;					//启动AD
	for (i=0;i<100;i++)
	;
	P3_0=0;
	P3_1=0;
	}}

void int0() interrupt 0
	{
	char a,b,c,d;
	int out;
	EA=0;
	out=(P1*100.0/255.0)*5/p/0.1;		//计算输出值
	b=out%100/10;				//取小数点后一位
	a=out%1000/100*16;			//取个位
	if(out>=1000)				//取十位
	c=out/1000*16;
	else
	c=0;
	d=out%10;					//取小数点后两位
	P2=a|b;
	P0=c|d;
	EA=1;
	}
	

