#include <reg51.H>

unsigned char code table[]={0x3f,0x06,0x5b,0x4f,0x66,
                            0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char Second;

void delay1s(void)
{
  unsigned char i,j,k;
  for(k=100;k>0;k--)
  for(i=20;i>0;i--)
  for(j=248;j>0;j--);
}


void main(void)
{
  Second=0;
  P0=table[Second/10];
  P2=table[Second%10];
  while(1)
    {
      delay1s();
      Second++;
      if(Second==60)
        {
          Second=0;
        }
      P0=table[Second/10];
      P2=table[Second%10];
    }
}
