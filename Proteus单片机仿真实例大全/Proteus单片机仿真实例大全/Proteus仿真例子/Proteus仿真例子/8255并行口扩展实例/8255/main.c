#include<regx52.h>
#include<intrins.h>
#include<absacc.h>
#define uchar unsigned char
#define uint unsigned int
#define PA XBYTE[0x3fff]
#define PB XBYTE[0x7fff]
#define PC1 XBYTE[0xbfff]
#define CTL XBYTE[0xffff]
sbit reset=P2^5;
void delay(uchar t);
void display();
void main()
{
 EA=1;
 ET0=1;
 TMOD=0x01;
 reset=1;
 _nop_();
 reset=0;
 CTL=0x80;     //写8255控制字，设置PA,PB,PC为输出口
 while(1)
 {
  display();}
}
void display()
{
 uchar outdata=0xfe,i;
 for(i=0;i<8;i++)
  {PA=outdata;
   delay(200);
   outdata=_crol_(outdata,1);
  }
  PA=0xff;
  outdata=0xfe;
 for(i=0;i<8;i++)
  {PB=outdata;
   delay(200);
   outdata=_crol_(outdata,1);}
  PB=0xff;
  outdata=0xfe;
 for(i=0;i<8;i++)
  {PC1=outdata;
   delay(200);
   outdata=_crol_(outdata,1);}
 
  PC1=0xff;
}

void delay(uchar t)
{
  for(;t>0;t--)
   {
   	 TH0=(65536-1000)/256;
	 TL0=(65536-1000)%256;
   	 TR0=1;
   	 while(TF0==0) ;
	 TF0=0;
    }
   TR0=0;
}