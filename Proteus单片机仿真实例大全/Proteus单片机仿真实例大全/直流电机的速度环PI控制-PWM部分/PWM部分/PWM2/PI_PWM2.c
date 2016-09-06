#include <absacc.h>
#include <reg51.h>
#include <stdio.h>
bit flag=1;
unsigned char pwm=0;
unsigned char a,b;
sbit P21=P2^1;
sbit P20=P2^0;
void sdf() interrupt 3 using 0    //定时255us,0.063s
{
P1=0x00;
if(flag==1)
 {a--;
  if(a==0)
    {flag=0;
	a=1;
	}
   else
   {P21=0;}
 }
if(flag==0)
 {b--;
  if(b==0)
    {flag=1;
	b=253;
	}
  else
 {P21=1;}
 }
}
main()
{TMOD=0x20;
TH1=0x06; //对TH0 TL0 赋值
TL1=0x06;
P20=1;
ET1=1;
TF1=0;
b=1;
a=253;
TR1=1;
EA=1;
while(1);

}

 
