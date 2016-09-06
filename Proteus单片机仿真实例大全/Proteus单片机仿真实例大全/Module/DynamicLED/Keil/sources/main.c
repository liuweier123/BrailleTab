//*************************************************************************************************
//*************************************************************************************************
//**<程序名>：LED动态扫描显示																	 **
//**<功能>：LED动态显示1s计数。																	 **
//**<作者>：LastRitter																			 **
//**<完成时间>：2007年7月28日																	 **
//**<联系方式>：superyongzhe@163.com															 **
//*************************************************************************************************
//*************************************************************************************************


//*************************************************************************************************
//*																								  *
//*			 ******************************头文件及宏定义**************************				  *
//*																								  *
//*************************************************************************************************
#include "includes.h"

#define TIME0H 0xFC
#define TIME0L 0x18		//定时器0溢出时间：5ms,用于刷新LED。

#define TIME1H 0x40
#define TIME1L 0x98		//定时器1溢出时间：49ms，用于计时模式的计数增加。


//*************************************************************************************************
//*																								  *
//*			  ********************************全局变量******************************			  *
//*																								  *
//*************************************************************************************************

unsigned char uc_DisCount=1;		//定时器0定时刷新LED计数。

unsigned char uc_TimeCount=0;		//定时器1定时计数。

unsigned long ul_Number=0;			//LED显示数字。


//*************************************************************************************************
//*																								  *
//*			  ********************************主函数******************************				  *
//*																								  *
//*************************************************************************************************
void main()
{
	TMOD=0x11;		  //定时器0:模式一;定时器0:模式一.


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<定时器0，用于LCD刷新>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	TH0=TIME0H;
	TL0=TIME0L;
	TR0=1;			 //开启定时器0
	ET0=1;			 //开定时器0中断


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<定时器1，用于1s计时 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	TH1=TIME1H;
	TL1=TIME1L;
	TR1=1;			 //开启定时器1
	ET1=1;			 //开定时器1中断


	EA=1;			 //开启总中断

	while(1);
}


//*************************************************************************************************
//*																								  *
//*		*****************************定时器1中断，用于计时功能******************************	  *
//*																								  *
//*************************************************************************************************
void vTimer1(void) interrupt 3
{

		if(uc_TimeCount==19)
			{
			uc_TimeCount=0;
			ul_Number++;
			}
		else uc_TimeCount++;

	TH1=TIME1H;
	TL1=TIME1L;
}


//*************************************************************************************************
//*																								  *
//*		***************************定时器0，定时刷新LED*************************				  *
//*																								  *
//*************************************************************************************************
void vTimer0(void) interrupt 1
{
	vShowOneNum(*(pucLedNum(ul_Number)+uc_DisCount),uc_DisCount);	   //在LED上显示1位数字。

	if(uc_DisCount<5)
		uc_DisCount++;						//定时器0在每次被触发时，改变LED显示。
	else uc_DisCount=0;						//从第一位到第六位循环显示。

	TH0=TIME0H;		   						//恢复定时器0初始值。
	TL0=TIME0L;
}