#include <absacc.h>
#include <intrins.h>
#include <reg51.h>

//#include "adc0831.h"
#include "lcd1602.h"
sbit adcdo=P1^0;
sbit adcclk=P1^1;
sbit adccs=P1^2;
#define uchar unsigned char 

uchar bdata ch;
uchar a,b1,b2,b3;
uchar time0_count; 	//time0计数器

sbit ch_0 = ch^0;

void delay1(uchar x)
{
	uchar i;
	for(i=0;i<x;i++); 
}

void adcck(void) 
{ 
	adcclk=1; 
	delay1(1); 
	adcclk=0; 
	delay1(1); 
}

uchar readadc(void)
{ 
    uchar i;
 	ch=0;
    adccs=0;
    adcck();
    while(adcdo); 
    for (i=0; i<8; i++) 
    { 
         adcck();
         ch <<= 1;
		 ch_0 = adcdo;
    }
    adccs=1;
    return(ch);
}


//time0初始化
void time0_init(void)
{
	EA = 1;
	ET0 = 1;
//	TMOD = 0x01;
	PT0 = 1;
	TH0 = 0x3C;
	TL0 = 0xB0;
	TR0 = 1;
	SM0=0;
	SM1=1;//方式1，10位UAR
	REN=1;//允许接收
	TI=0;//发送中断标志
	RI=0;//接收中断标志位
	PCON=0;//电源控制位。
	TH1=0xF3;
	TL1=0XF3;//给初值，计算出波特；
	TMOD=0X21;//方式2,定时器0工作方式1 ；
	EA=1;//中断总允许位
	ET1=0;//T1中断允许位
	ES=1;//串行中断允许位
	TR1=1;//开启定时器
}

//void csh()
//	{

//	}


unsigned char TempBuffer[10];
void IntToStr(unsigned int t, unsigned char *str, unsigned char n) 
{
	unsigned char a[5]; char i, j;                                 	
	a[0]=(t/10000)%10;         //取得整数值到数组         	
	a[1]=(t/1000)%10;                                     	
	a[2]=(t/100)%10;                                      	
	a[3]=(t/10)%10;                                       	
	a[4]=(t/1)%10;                                        	
                                                      
	for(i=0; i<5; i++)         //转成ASCII码              	
		a[i]=a[i]+'0';                                    	
	for(i=0; a[i]=='0' && i<=3; i++);                     	
	for(j=5-n; j<i; j++)       //填充空格                 	
		{ *str=' ';  str++; }                             	
	for(; i<5; i++)                                       	
		{ *str=a[i]; str++; }  //加入有效的数字           	
	*str='\0'; 
} 

void Delay1ms(unsigned int count)
{
	unsigned int i,j;
	for(i=0;i<count;i++)
	for(j=0;j<120;j++);
}


void main(void)
{
	
	time0_init();
	LCD_Initial();
	GotoXY(0,0);
	Print("SP: 80.c");
	GotoXY(0,1);
	Print("PV:");

	while(1)
	{
       	TI=0;
		SBUF=a;
		P2 = 100;   //进行数模转换
		while(!TI);
		TI=0;
	    IntToStr(a,&TempBuffer[0],5);
		GotoXY(3,1);
		Print(&TempBuffer[0]);
		Print("of 255");
		Delay1ms(100);
	}
		
}
void time0_interrupt(void)interrupt 1
{
	TH0 = 0x3c;
	TL0 = 0xb0;
	time0_count++;
	if(time0_count==20)
	{
		time0_count=0;
//		show_date_time();
 		a = readadc();
		b1 = a/100;
		b2 = (a%100)/10;
		b3 = (a%100)%10;
//		show_ad();
	}
}

void intrr() interrupt 4
	{
	char temp;
	temp=SBUF;
//	P2=temp;
	RI=0;
}
