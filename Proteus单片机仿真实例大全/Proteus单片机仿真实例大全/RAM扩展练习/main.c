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
 unsigned char j;//Ʈ�㣺�˴�������int������Ϊд��ram��ֻ���ǰ�λ
 p=0x0000;	          
 for(j=0;j<255;j++)//Ʈ�㣺�˴����ܵ���255�����޷��ж�
  {*p=j+10;			  
   //delay();
   _nop_();
   _nop_();
   p++;
   }
}

void read()		
{
 unsigned char k;//Ʈ�㣺�˴�������int������������ͬ
 p=0x0000;
  for(k=0;k<255;k++)//Ʈ�㣺�˴����ܵ���255��������ͬ
	{
	 P1=*p;
	 delay();
	 p++;
	
	}
}

void delay()
{uint i;
 for(i=6000;i>0;i--);//Ʈ��:int���ͱ������ܴ���65536
for(i=6000;i>0;i--);
for(i=6000;i>0;i--);
for(i=6000;i>0;i--);
}