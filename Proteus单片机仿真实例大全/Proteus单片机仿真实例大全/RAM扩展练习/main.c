#include<reg52.h>
#include<absacc.h>
#include<intrins.h>	 
#define uchar unsigned char
#define uint unsigned int
uchar xdata *p;		
void write();
void read();
void delay();

void main()
{

P1=0xaa;
 write();
 P1=0xbb;
 while(1)
 read();
}

void write()		 
{
 unsigned char j;//飘零：此处不能用int变量因为写入ram的只能是八位
 p=0x0000;	          
 for(j=0;j<255;j++)//飘零：此处不能等于255否则无法判断
  {*p=j+10;			  
   //delay();
   _nop_();
   _nop_();
   p++;
   }
}

void read()		
{
 unsigned char k;//飘零：此处不能用int变量，与上相同
 p=0x0000;
  for(k=0;k<255;k++)//飘零：此处不能等于255，与上相同
	{
	 P1=*p;
	 delay();
	 p++;
	
	}
}

void delay()
{uint i;
 for(i=6000;i>0;i--);//飘零:int类型变量不能大于65536
for(i=6000;i>0;i--);
for(i=6000;i>0;i--);
for(i=6000;i>0;i--);
}