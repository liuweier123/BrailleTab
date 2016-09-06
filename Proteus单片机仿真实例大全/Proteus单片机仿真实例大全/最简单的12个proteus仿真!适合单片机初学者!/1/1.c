#include <REG51.H>

sbit p=P1^0;

void delay(void)
{
  unsigned int i,j,k;
  for(i=20;i>0;i--)
  for(j=20;j>0;j--)
  for(k=248;k>0;k--);
}

main()
{
 while(1)
 {
  p=0;
  delay();
  p=1;
  delay();
 }
}
