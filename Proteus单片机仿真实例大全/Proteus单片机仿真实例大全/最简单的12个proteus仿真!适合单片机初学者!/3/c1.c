#include <reg51.H>
unsigned char temp;

void main(void)
{
  while(1)
    {
      temp=P1>>4;
      temp=temp | 0xf0;
      P1=temp;
    }
}
