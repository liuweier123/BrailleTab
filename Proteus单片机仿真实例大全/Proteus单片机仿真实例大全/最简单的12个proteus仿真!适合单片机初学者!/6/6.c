#include <reg51.H>
#include <INTRINS.H>

bit flag;
sbit P1_7=P1^7;
sbit P1_0=P1^0;

unsigned char count;

void dely500(void)
{
  unsigned char i;
  for(i=250;i>0;i--)
    {
      _nop_();
    }
}

void main(void)
{
  while(1)
    {
      if(P1_7==0)
        {
          for(count=200;count>0;count--)
            {
              P1_0=~P1_0;
              dely500();
            }
          for(count=200;count>0;count--)
            {
              P1_0=~P1_0;
              dely500();
              dely500();
            }
        }
    }
}
