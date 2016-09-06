#include <reg51.H>

sbit P3_7=P3^7;
unsigned char count;

void delay10ms(void)
{
  unsigned char i,j;
  for(i=20;i>0;i--)
  for(j=248;j>0;j--);
}

void main(void)
{
  while(1)
    {
      if(P3_7==0)
        {
          delay10ms();
          if(P3_7==0)
            {
              count++;
              if(count==16)
                {
                  count=0;
                }
              P1=~count;
              while(P3_7==0);
            }
        }
    }
}
