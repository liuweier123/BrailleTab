#include <reg51.H>

sbit P1_0=P1^0;
sbit P1_1=P1^1;
sbit P1_2=P1^2;
sbit P1_3=P1^3;
sbit P3_7=P3^7;
unsigned char ID;

void delay10ms(void)
{
  unsigned char i,j;
  for(i=20;i>0;i--)
  for(j=248;j>0;j--);
}

void delay02s(void)
{
  unsigned char i;
  for(i=20;i>0;i--)
    {delay10ms();
    }
}

void main(void)
{ while(1)
    { if(P3_7==0)
        {delay10ms();
          if(P3_7==0)
            {
              ID++;
              if(ID==4)
                {
                  ID=0;
                }
              while(P3_7==0);
            }
        }
      switch(ID)
        { case 0:
            P1_0=~P1_0;
            delay02s();
            break;
          case 1:
            P1_1=~P1_1;
            delay02s();
            break;
          case 2:
            P1_2=~P1_2;
            delay02s();
            break;
          case 3:
            P1_3=~P1_3;
            delay02s();
            break;
        }
    }
}
