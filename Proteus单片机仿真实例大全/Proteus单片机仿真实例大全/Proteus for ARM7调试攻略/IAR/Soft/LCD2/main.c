

#include  "config.h"
#include <intrinsics.h>
//**************************************
#define rs (1<<8)
#define rw (1<<9)
#define en (1<<10)
#define busy (1<<7)

uint8 BCD[6];			//十位二进制的显示码分别是千百十个位的显示
//uint8 txt[]={"HelloWorld"};
uint8 txt[]={"LPC2106!!!"};

void ChkBusy()
{
	IODIR=0xff00;
	while(1)
	{
		IOCLR=rs;
		IOSET=rw;
		IOSET=en;
		if(!(IOPIN & busy))break;
		IOCLR=en;
	}
	IODIR=0xffff;
}

void WrOp(uint8 dat)
{
	ChkBusy();
	IOCLR=rs;		//全部清零
	IOCLR=rw;
	IOCLR=0xff;		//先清零
	IOSET=dat;		//再送数
	IOSET=en;
	IOCLR=en;
}

void WrDat(uint8 dat)	//读数据
{
	ChkBusy();
	IOSET=rs;
	IOCLR=rw;
	IOCLR=0xff;		//先清零
	IOSET=dat;		//再送数
	IOSET=en;
	IOCLR=en;
}

void lcd_init(void)
{
	WrOp(0x38);			
	WrOp(0x06);			//光标加1
	WrOp(0x0c);			//开显示
}

void DisText(uint8 addr,uint8 *p)
{
	WrOp(addr);
	while(*p !='\0')WrDat(*(p++));
}

void ShowInt(uint8 addr,uint16 num)			//在addr处显示数字num
{//将num转化成五个BCD码存放在全局数组BCD[5]中
	uint8 i;
	for(i=5;i>0;i--)       //将NUM数据转化成ASCII码,如521会转化为00521
	{
       	  BCD[i-1]=(uint8)(num%10+0x30);     //取出最低位
       	  num/=10;                           //去掉最低位
    }
    i=0;
	while(BCD[i] ==0x30 && i<4) BCD[i++]=' ';    //NUM转换成数组存放,但还没有加上小数点
	BCD[5]='\0';
	DisText(addr,BCD);
}

void ShowByte(uint8 addr,uint8 num)
{//将num转化成五个BCD码存放在全局数组BCD[5]中
	uint8 i;
	for(i=3;i>0;i--)       //将NUM数据转化成ASCII码,如521会转化为00521
	{
       	  BCD[i-1]=(uint8)(num%10+0x30);     //取出最低位
       	  num/=10;                           //去掉最低位
    }
    i=0;
	while(BCD[i] ==0x30 && i<2) BCD[i++]=' ';    //NUM转换成数组存放,但还没有加上小数点
	BCD[3]='\0';
	DisText(addr,BCD);
}



int  main(void)
{   
    lcd_init();
	IODIR=0xffff;		//设置为输出
	IOCLR=0xffff;
		
	DisText(0x86,txt);
	while(1);
}
