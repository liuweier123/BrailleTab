#include <reg51.H>
unsigned char i;
unsigned char temp;
unsigned char a,b;

void delay(void)
{
  unsigned char m,n,s;
  for(m=20;m>0;m--)
  for(n=20;n>0;n--)
  for(s=248;s>0;s--);
}
void main(void)
{
  while(1)
    {
      temp=0xfe;
      P1=temp;
      delay();
      for(i=1;i<8;i++)
        {
          a=temp<<i;
          b=temp>>(8-i);
          P1=a|b;
          delay();
        }
      for(i=1;i<8;i++)
        {
          a=temp>>i;
          b=temp<<(8-i);
          P1=a|b;
          delay();
        }
    }
}
