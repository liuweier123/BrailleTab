#include <reg51.H>

sbit P3_6=P3^6;
sbit P3_7=P3^7;
unsigned char curcount;

void delay10ms(void)
{
  unsigned char i,j;
  for(i=20;i>0;i--)
  for(j=248;j>0;j--);
}


void main(void)
{
  curcount=P3 & 0x0f;
  P1=~curcount;
  while(1)
    {
      if(P3_6==0)
        {
          delay10ms();
          if(P3_6==0)
            {
              if(curcount>=15)
                {
                  curcount=15;
                }
                else
                  {
                    curcount++;
                  }
               P1=~curcount;
               while(P3_6==0);
            }
        }
      if(P3_7==0)
        {
          delay10ms();
          if(P3_7==0)
            {
              if(curcount<=0)
                {
                  curcount=0;
                }
                else
                  {
                    curcount--;
                  }
               P1=~curcount;
               while(P3_7==0);
            }
        }
    }
}
