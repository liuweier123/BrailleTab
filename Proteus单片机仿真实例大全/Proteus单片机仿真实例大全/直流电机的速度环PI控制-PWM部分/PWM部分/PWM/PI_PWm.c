#include <stdio.h>
#include <reg51.h>
sbit P1_1=P2^1;
sbit P1_0=P2^0;
unsigned char a;
void delay(unsigned char i)
{  unsigned char j,k;
    for(;i>0;i--)
    for(j=15;j>0;j--)
    for(k=10;k>0;k--); //��Լ0.1�����ڡ�
}
void PWM_creat()
{if(a>=231)   //��������10��231ת��
a=250;
if(a<=10) 
a=10;
P1_1=0; 
delay(255-a);
P1_1=1;
delay(a);
}
main()
{a=255;
 P1_0=1;
while(1)
{   
 PWM_creat();
}
}
