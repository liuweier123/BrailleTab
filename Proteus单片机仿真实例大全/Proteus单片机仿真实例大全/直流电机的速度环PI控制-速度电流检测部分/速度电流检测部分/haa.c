#include <absacc.h>
#include <reg51.h>
#define IN0 XBYTE[0x7ff8]
unsigned char   disbit[]={0xfe,0xfd,0xfb,0xf7};
unsigned char code discode[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned int   disbuf[4]={0,0,0,0};
unsigned int  ad=100;
unsigned char q=0;
unsigned char *Adr;
unsigned char count,miaoshu;
unsigned char sec,tcnt;
sbit p26=P2^6;
void delay(unsigned char N)
{
   unsigned char i;
   for(i=0;i<N;i++);
}
void display(unsigned char ch)
{  
   unsigned char k;   //��ʾ�����õ�һ�ֳ��򣬿��԰�disbuf������һ����ʱ�������
   disbuf[0]=ch%10;
   disbuf[1]=(ch%100)/10;
   disbuf[2]=ch/100%10;
   disbuf[3]=1;
   for(k=0;k<4;k++)
          {
            P2=0xff; // p2��Ϊ������������øߵ�ƽ
            P1=discode[disbuf[k]];
            P2=disbit[k];
          }
}
   
void read_ch(void) interrupt 0 using 0
{  
   
   ad=*Adr;
   
}

void t0(void) interrupt 1 using 0 //��ʱT0�жϷ�����
{
	tcnt++; //ÿ��250ust tcnt ��һ
	if(tcnt==40) //����40 �Σ�1/100 �룩ʱ
	{		
		tcnt=0; //�����ټ�
		sec++;
		if(sec==10) //��ʱ0.1 �룬�ڴ��㿪ʼ��ʱ
		{
			sec=0;
        	TH0=0x06; //��TH0 TL0 ��ֵ
        	TL0=0x06;
			miaoshu=count;
	       	count=0;
		}
	}
}

void sdf(void) interrupt 2 using 0 //����T1�жϷ�����
{   
	count=count+1;
    
	
}
main()
{
  unsigned int m;
  unsigned char s1=0x44;
  EX0=1;
  IT1=1;
  Adr=&IN0;
  TMOD=0x02; //��ʱ��T0�����ڷ�ʽ2 �Զ���װ��ʽ,������T1�����ڷ�ʽ2 �Զ���װ��ʽ
	TH0=0x06; //��TH0 TL0 ��ֵ
	TL0=0x06;
	TR0=1; //��ʼ��ʱ
	ET0=1; //����T0 �����ж�
	EA=1;
	EX1=1;
	TR1=1;
	IT1=1;
    EA=1;
   	sec=0;
	SCON=0x90; //MODER1,REN=1;
	PCON=0x00;
	miaoshu=0;tcnt=0;count=0;
 while(1)
  { 
        *Adr=0; 
    for(m=0;m<5000;m++)
       {  
	      if(p26==1)
 	      {display(ad);
           }         
        else
		   { display(miaoshu);
		   }
       }
    do{   
        SBUF=0xff;
        while(TI==0);TI=0;
         
         while(RI==0);RI=0;
         }while(SBUF!=0xbb);
        
         SBUF=ad;
         while(TI==0);TI=0;
         
   }
 }
