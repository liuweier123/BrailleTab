#include <reg51.H>

sbit P3_7=P3^7;
unsigned char code table[]={0x3f,0x06,0x5b,0x4f,0x66,
                            0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char Count;

void delay10ms(void)
{
  unsigned char i,j;
  for(i=20;i>0;i--)
  for(j=248;j>0;j--);
}

void main(void)
{
  Count=0;
  P0=table[Count/10];
  P2=table[Count%10];
  while(1)
    {
      if(P3_7==0)
        {
          delay10ms();
          if(P3_7==0)
            {
              Count++;
              if(Count==100)
                {
                  Count=0;
                }
              P0=table[Count/10];
              P2=table[Count%10];
              while(P3_7==0);
            }
        }
    }
}
