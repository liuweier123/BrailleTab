#include <reg51.H>

void main(void)
{
  while(1)
    {
      if(P1_4==0)
        {
          P1_0=0;
        }
        else
          {
            P1_0=1;
          }
      if(P1_5==0)
        {
          P1_1=0;
        }
        else
          {
            P1_1=1;
          }
      if(P1_6==0)
        {
          P1_2=0;
        }
        else
          {
            P1_2=1;
          }
      if(P1_7==0)
        {
          P1_3=0;
        }
        else
          {
            P1_3=1;
          }
    }
}
