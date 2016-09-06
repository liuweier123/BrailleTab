#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

sbit SDA	=     P1^1;
sbit SHIFT_CP  =  P1^2;
sbit ST_CP     =  P1^0;
#define NOP     _nop_()

uchar ledcode[] = 
{
        0x3F,
        0x06,
        0x5B,
        0x4F,
        0x66,
        0x6D,
        0x7D,
        0x07,
        0x7F,
        0x6F,
};
uchar ledbitselect[] = {0x0fe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
//11111110 11111101 11111011 11110111 11101111 11011111 10111111 01111111
uchar i;

void InitSerialPort(void)
{
  SDA = 0;
  SHIFT_CP = 0;
  ST_CP = 0;
}

void delay(void)
{
	uchar jj;
	for(jj=0;jj<200;jj++);
	while(jj--);
}

void SerialSendData(uchar dat)
{
  uchar ii;
  uchar sdata=dat;
  for(ii=0;ii<8;ii++)
  {
    if(sdata&0x80)SDA=1;
	else SDA = 0;
    sdata<<=1;
    SHIFT_CP =0;
    NOP;
    NOP;
    SHIFT_CP = 1;
    NOP;
    NOP;
  }
  ST_CP = 1;
  NOP;
  NOP;
  ST_CP = 0;
}




//LED ¹²Òõ

void main()
{
  InitSerialPort();
  while(1){
  delay();
  delay();
  P2 = ledbitselect[i];
  SerialSendData(ledcode[i]);
  i=(i+1)%8;
  }

}