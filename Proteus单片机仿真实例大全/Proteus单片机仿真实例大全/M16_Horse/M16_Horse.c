#include<iom16v.h>
#define uchar unsigned char
#define uint unsigned int

void Delay(uchar i)
{
 uchar j;
 for(;i!=0;i--)
 {
  for(j=250;j!=0;j--);
 }
}

void Horse(uchar i)
{
 switch(i)
 {
  case 0:PORTA=0x00;break;
  case 1:PORTA=0x01;break;
  case 2:PORTA=0x03;break;
  case 3:PORTA=0x07;break;
  case 4:PORTA=0x0f;break;
  case 5:PORTA=0x1f;break;
  case 6:PORTA=0x3f;break;
  case 7:PORTA=0x7f;break;
  case 8:PORTA=0xff;break;
  default:break;
 }
}

void main()
{
 uchar i;
 DDRA=0xff;
 PORTA=0xff;
 Delay(10);
 PORTA=0x00;
 while(1)
 {
  for(i=0;i<9;i++)
  {
   Horse(i);
   Delay(100);
  }
  for(i=8;i!=0;i--)
  {
   Horse(i);
   Delay(100);
  }
 }
}