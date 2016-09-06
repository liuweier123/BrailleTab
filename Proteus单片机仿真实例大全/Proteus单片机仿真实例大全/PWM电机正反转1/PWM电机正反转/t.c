#include<reg52.h>
#define num_sec 3		   //多少秒
#define num_run 5000	   //转的圈数
#define num_cry 100		   //叫的次数
sbit bee=P1^7;
sbit m1=P1^6;
sbit m2=P1^5;
sbit key=P1^4;
unsigned char cir=0,num50ms=0;
unsigned int n=0;

void delay1ms(unsigned int count)
{
   unsigned int i,j;
   for(i=0;i<count;i++)
   for(j=0;j<120;j++);
}
void cry(unsigned char c)
{
   unsigned k;
   for(k=0;k<c;k++)
   {
     bee=0;
	 delay1ms(80);
	 bee=1;
	 delay1ms(80);
   }
}
void time0(void) interrupt 1 using 1
{
   num50ms++;				 //STC12C2052
   if(num50ms==(num_sec*20)) //20为1秒
   {
	   m1=~m1;
	   m2=~m2;
	   num50ms=0;
	   cir++;
	}
   if(cir==2)
   {
       cir=0;
	   n++;
   }
   TH0=0X4C;
   TL0=0;
}
main()
{
   m1=1;m2=1;
   bee=1;
   while(1)
   {
     if(!key&&n==0)
	 {
	   delay1ms(20);
	   if(!key)
	   {
	   TMOD=0x01;
       EA=1;
       ET0=1;
	   TH0=0X4C;
       TL0=0;
	   TR0=1; 
	   m1=1;
	   m2=0;
	   bee=0;
	   delay1ms(100);
	   bee=1;
	   }
	   while(!key);
	 }
	if(n==num_run)
	 {
	   TR0=0;
	   m1=1;
	   m2=1;
	   cry(num_cry);
	   n=0;
	 }
   }

}
