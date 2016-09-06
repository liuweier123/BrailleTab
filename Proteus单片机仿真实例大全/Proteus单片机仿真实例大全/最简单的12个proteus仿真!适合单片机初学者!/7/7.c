#include <reg51.H>
unsigned char code table[]={0x3f,0x06,0x5b,0x4f,0x66,
                            0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char dispcount;

void delay02s(void)
{
  unsigned char i,j,k;
  for(i=20;i>0;i--)
  for(j=20;j>0;j--)
  for(k=248;k>0;k--);
}

void main(void)
{
  while(1)
    {
      for(dispcount=0;dispcount<10;dispcount++)
        {
          P0=table[dispcount];
          delay02s();
        }
    }
}
