#include <absacc.h>
#include <reg51.h>
typedef struct 
{	 
unsigned int uk,uks,uont1,uont2,bt; 	 
unsigned char pick,comand,ki,kp;
unsigned char s1,s2,ek,ek1;
}PID;	 
PID xdata PI;
typedef struct PWM_str
{
unsigned char pick,comand;
unsigned char output,set;
unsigned char num;
}PWMs;
PWMs xdata PWM;



void PWM_ss(void) interrupt 3 using 0//定时器2产生PWM波形
{                
			
	if((PWM.num>=PWM.set)&&(PWM.num<200))
	{PWM.output=0;}
	else	
	{PWM.output=1;}	
	PWM.num++;	
	if(PWM.num==200)
	{PWM.num=0x00;
	bt++;}
               
}
void PI_ss(void) interrupt 1 using 0       //PID运算结果。
{    unsigned int temph;
     unsigned int temp1,temp2;
     PI.ek1=PI.ek;
     if(PI.comand>=PI.pick)
     {PI.ek=PI.comand-PI.pick;
	 
	 temp1=(PI.kp+PI.ki)*PI.ek;
	 temp2=PI.kp*PI.ek1;
     if(temp1>=temp2)
	 {PI.uks=temp1-temp2;
	  temph=PI.uk+PI.uks;}
	 else
	 {PI.uks=temp2-temp1;
	  temph=PI.uk-PI.uks;}
	 }
	  else
     {PI.ek=PI.pick-PI.comand;
	 temp1=(PI.kp+PI.ki)*PI.ek;
     temp2=PI.kp*PI.ek1;
     PI.uks=temp1+temp2;
	 if(temp1>=temp2)
	 {PI.uks=temp1-temp2;
	 temph=PI.uk+PI.uks;}
	 else
	 {PI.uks=temp2-temp1;
	 temph=PI.uk+PI.uks;}
	 }
	 if(temph>=PI.uont1)
	  PI.uk=PI.s1;
	 if(temph<=PI.uont2)
	  PI.uk=PI.s2;
	 }
main()
{  
