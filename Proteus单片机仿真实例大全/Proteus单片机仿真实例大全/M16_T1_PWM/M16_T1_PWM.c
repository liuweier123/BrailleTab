#include <iom16v.h>
#define uchar unsigned char
#define uint unsigned int

uchar Table[12]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x79};
uchar Data1[4]={10,0,5,0};
uchar Data2[4]={3,9,1,0};
uchar Key1,Key2;

void DelayMs(uchar i)
{
 uchar j;
 for(;i!=0;i--)
 {
  for(j=25;j!=0;j--);
 }
}

void Display(uchar *p)
{
 uchar i,sel=0x01;
 for(i=0;i<4;i++)
 {
  PORTC=sel;
  PORTA=0xff-Table[p[i]];
  DelayMs(2);
  sel=sel<<1;
 }
}

void Add_Process(uchar *p)
{
 if(p[1]!=1)
 {
  p[2]++;
  if(p[2]==10) {p[2]=0;p[1]++;}
 }
}
void Sub_Process(uchar *p)
{
 uchar temp;
 temp=p[1]*10+p[2];
 if(temp!=0)
 {
  temp=temp-1;
  p[1]=temp/10;
  p[2]=temp%10;
 }
}
void Key_Process()
{
 while((PINB&0x01)==0){Display(Data1);Key1=1;}
 while((PINB&0x02)==0){Display(Data1);Key2=1;}
 if(Key1==1)
 {
  Add_Process(Data1);
  Key1=0;
 }
 if(Key2==1)
 {
  Sub_Process(Data1);
  Key2=0;
 }
}
void Set_Process(uchar *p)
{
 uint i;
 i=p[1]*10+p[2];
 i=1023*i/10;
 OCR1AH=i>>8;
 OCR1AL=i&0x00ff;
}
void Init_IO(void)
{
 DDRA=0xff;
 PORTA=0xff;
 DDRC=0xff;
 PORTC=0xff;
 DDRB=0x00;
 PORTB=0x00;
 DDRD=0xff;
 PORTD=0xff;
}
void main(void)
{
 Init_IO();
 TCCR1A=0xc3;
 TCCR1B=0x02;
 DelayMs(50);
 while(1)
 {
  Key_Process();
  Set_Process(Data1);
  Display(Data1);
 }
}