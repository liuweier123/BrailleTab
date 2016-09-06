//*************************************************************************************************
//*************************************************************************************************
//**<程序名>：模拟串口输出																		 **
//**<功能>：通过模拟串口来控制LED显示。															 **
//**<作者>：LastRitter																			 **
//**<完成时间>：2007年7月31日																	 **
//**<联系方式>：E-Mail:superyongzhe@163.com;QQ:314665345。										 **
//*************************************************************************************************
//*************************************************************************************************
#include <at89x51.h>

#define SEND P2_0	   //模拟串口的输出口。
#define CLOCK P2_1	   //模拟串口的时钟口。

unsigned  char code uca_LEDCode[]=
			{0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};	//0,1,2,3,4,5,6,7,8,9


unsigned char uca_BitPosition[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};



//*************************************************************************************************
//*																								  *
//*			***************************将8位数据输出给ＬＥＤ*****************************		  *
//*																								  *
//*************************************************************************************************
void vShowOneNum(unsigned char ucNumber)
{
	unsigned char ucCount;

	if(ucNumber<10)
		{
		for(ucCount=0;ucCount<8;ucCount++)
			{
			CLOCK=0;

			if((uca_LEDCode[ucNumber]&uca_BitPosition[ucCount])==0)
				SEND=0;
			else SEND=1;

			CLOCK=1;
			}
		}
}




void main()
{
	unsigned int uiCount;
	unsigned char ucShowNumber=0;
	
	while(1)
	{
	vShowOneNum(ucShowNumber);

	if(ucShowNumber==9)
		ucShowNumber=0;
	else
		ucShowNumber++;

	for(uiCount=0;uiCount<30000;uiCount++);
	}
}



