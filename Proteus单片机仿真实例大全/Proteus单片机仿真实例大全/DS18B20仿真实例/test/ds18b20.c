/*--------------------------------------------------*/
/*             AVR-ARM开发网论坛                    */
/*           http://www.avrarm.com                  */
/*            AVR生成代码测试程序                   */
/*--------------------------------------------------*/
/*     程序由AVR辅助开发工具V2.1.0自动生成          */
/*     AVR系统的处理器为：   ATMega16               */
/*     AVR系统的晶振频率：   8.0000 Mhz             */
/*--------------------------------------------------*/

#include <iom16v.h>
#include <macros.h>
#include "ds18b20.h"
#include "delay.h"


unsigned char temp_buf[4];
/**********************************************************************
functionName: unsigned char resetDS18B20(void)
description ：DS18B20初始化
**********************************************************************/
unsigned char resetDS18B20(void)
{
   unsigned char errTime=0;
   RLS_DS18B20;		   //释放总线
   _NOP();
   HLD_DS18B20;		   //Maga16控制总线
   CLR_DS18B20;		   //强制拉低
   delay_nus(480);	   //209.42us
   //以上延时大于480us
   RLS_DS18B20;		   //释放总线,总线自动上拉
   _NOP();
   while(STU_DS18B20)
   {
      delay_nus(6);	   //5.15us
      errTime++;
      if(errTime>20)
         return(0x00);	   //如果等带大于约 5.15us*20就返回0x00，报告复位失败（实际上只要等待15-60us）
   }
   errTime=0;
   while(!(STU_DS18B20))
   {
      delay_nus(6);	   //5.15us
      errTime++;
      if(errTime>50)
         return(0x00);     //如果等带大于约 5.15us*50就返回0x00，报告复位失败（实际上只要等待60-240us）
   }
   return(0xff);
}

/**********************************************************************
functionName: unsigned char readByteDS18B20(void)
description ：读DS18B20一个字节
**********************************************************************/
unsigned char readByteDS18B20(void)
{
   unsigned char i;
   unsigned char retVal=0;
   RLS_DS18B20;		   //释放总线
   for(i=8;i>0;i--)
   {
      retVal>>=1;
      HLD_DS18B20;	   //Maga16控制总线
      CLR_DS18B20;	   //强制拉低
      delay_nus(8);	   //延时大于1us
      SET_DS18B20;	   //释放总线,DS18B20会将总线强制拉低
      //delay_nus(8);
	  RLS_DS18B20;		//释放总线
      if(STU_DS18B20)
         retVal|=0x80;
      delay_nus(32);	 	//31us
      HLD_DS18B20;		//释放总线
	  SET_DS18B20;	   //释放总线,DS18B20会将总线强制拉低
      //delay_nus(30);	 	//30.38us
   }
   delay_nus(5);	 	//2.71us(大于1us就行了)
   return(retVal);
}

/**********************************************************************
functionName: unsigned char readByteDS18B20(void)
description ：写DS18B20一个字节
**********************************************************************/
void writeByteDS18B20(unsigned char wb)
{
   unsigned char i;
   unsigned char temp;
   RLS_DS18B20;	         	//释放总线
   for(i=0;i<8;i++)
   {
      HLD_DS18B20;		//Maga16控制总线
      CLR_DS18B20;		//强制拉低
      delay_nus(4);	 	//14.92us
	  //SET_DS18B20;		//释放总线
	  //delay_nus(16);	 	//14.92us
      temp=wb>>i;
      temp&=0x01;
      if(temp)
         SET_DS18B20;		//释放总线
      else
         CLR_DS18B20;		//强制拉低
      delay_nus(50);	 	//30.38us
      //RLS_DS18B20;		//释放总线
	  SET_DS18B20;		//释放总线
      delay_nus(4);	 	//2.71us(大于1us就行了)
   }
}

/**********************************************************************
functionName: unsigned int readTempDS18B20(void)
description ：读DS18B20温度
**********************************************************************/
unsigned int readTempDS18B20(void)
{
   unsigned char tempL,tempH;
   unsigned int x;
   //resetDS18B20();
   //writeByteDS18B20(0xcc); 	//跳过ROM
   //writeByteDS18B20(0x44);	//启动温度转换
   delay_nms(1);          //等待1ms
   resetDS18B20();
   writeByteDS18B20(0xcc);	//跳过ROM
   writeByteDS18B20(0xbe);	//读数据
   tempL=readByteDS18B20();
   tempH=readByteDS18B20();
   x=(tempH<<8)|tempL;
   resetDS18B20();
   writeByteDS18B20(0xcc); 	//跳过ROM
   writeByteDS18B20(0x44);	//启动温度转换
   return(x);
}
//压缩BCD码转换成ASCII码
void BCDtoASCII(unsigned char cBCD,unsigned char *pstr)
{
   unsigned char i,j;
   i=cBCD>>4;
   j=cBCD&0x0F;
   *pstr++=i+0x30;
   *pstr=j+0x30;
}
//读取当前温度并解释
void Read_Temp(void)
{
   unsigned int temp=0;
   temp=readTempDS18B20();
   BCDtoASCII((temp>>8)&0x0F,&temp_buf[0]);					
   BCDtoASCII((temp>>8)&0x0F,&temp_buf[1]);
   BCDtoASCII((temp>>4)&0x0F,&temp_buf[2]);					
   BCDtoASCII(temp&0x0F,&temp_buf[3]);					
}
