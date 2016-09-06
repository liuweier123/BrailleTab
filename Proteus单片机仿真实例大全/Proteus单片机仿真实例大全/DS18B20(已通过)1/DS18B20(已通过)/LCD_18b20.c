//#include <at89x51.h>//��AT89C51ʱ�������ͷ�ļ�
#include <reg52.h>//�û���W78E58Bʱ���������ͷ�ļ�
//#include <absacc.h>
//#include <ctype.h>
//#include <math.h>
//#include <stdio.h>
//#include <string.h>
#include <DS18B20.h>			//����ͷ�ļ�
#include <LCD1602.h>			//Һ����ʾͷ�ļ�
#include <keyscan.h>			//����ɨ��ͷ�ļ�
sbit alarm=P2^6;					//�����ź�
//sbit DQ = P3^7;					//����DQ����ΪP3.7
unsigned char key_value;            //��ż���ɨ��ֵ
bit up_one,down_one; 				//��1�ͼ�1��־
bit alarm_up_flag,alarm_down_flag;	//���ޱ��������ޱ������ñ�־
bit set_temper_flag;				//���ÿ��Ʊ�־�¶ȱ�־
bit alarm_switch;					//��������

unsigned char user_temper;			 //�û��궨�¶�	
unsigned char TH=110,TL=-20,RS=0x3f; //�����¶�110,����-20,�ֱ���10λ,Ҳ����0.25C
unsigned char t[2],*pt;				//��������¶�ֵ,���³������ͨ�����������������ͨ�ŵ�
unsigned char  TempBuffer1[17]={0x2b,0x20,0x30,0x30,0x2e,0x30,0x30,0x20,
								0x53,0x45,0x54,0x2b,0x20,0x30,0x30,0x43,'\0'};
								//��ʾʵʱ�¶�,�ϵ�ʱ��ʾ+ 00.00 SET+ 00C
unsigned char  TempBuffer0[17]={0x54,0x48,0x3a,0x2b,0x20,0x30,0x30,0x20,
								0x54,0x4c,0x3a,0x2b,0x20,0x30,0x30,0x43,'\0'};
								//��ʾ�¶�������,�ϵ�ʱ��ʾTH:+ 00 TL:+ 00C							
unsigned char code dotcode[4]={0,25,50,75};
/***����ʾ�ֱ���Ϊ0.25,��С������Ƚ��鷳,�ʲ��ò��ķ���*******
�ٽ���ֵ�����ʮλ�͸�λ���͵�ʮ��λ�Ͱٷ�λ********************/



/***********�û��趨�¶�ת��ΪLCD��ʾ����**************
*����:���û��趨�¶�user_temper,���������λ,�١�ʮ����λ
	  ��������ת��ΪACSII��,�͵�Һ����ʾ������
******************************************************/
void user_temper_LCD(unsigned char temper)
{
	if(temper>0x7f)				//�ж�����,���Ϊ����,����ת��Ϊ�����ֵ
	{
		TempBuffer1[11]=0x2d;	//0x2dΪ"-"��ASCII��
		temper=~temper;			//�������Ĳ���ת���ɾ���ֵ
		temper++;
	}
	else TempBuffer1[11]=0x2b;	////0x2BΪ"+"��ASCII��
	TempBuffer1[12]=temper/100+0x30;		             //�����temper�İ�ʮ��λ
  	if( TempBuffer1[12]==0x30) TempBuffer1[12]=0xfe;     //��λ������
  	TempBuffer1[13]=(temper%100)/10+0x30;				     //�����ʮλ
  	TempBuffer1[14]=(temper%100)%10+0x30;	 			     //�������λ
}



/***************�¶�������ת��ΪLCD��ʾ����************
*����:�������ޱ����¶�,���������λ,�١�ʮ����λ
	  ��������ת��ΪACSII��,�͵�Һ����ʾ������
******************************************************/
void alarm_LCD( unsigned char TH, unsigned char TL)	
{ 
   if(TH>0x7F)                    //�ж�����,���Ϊ����,����ת��Ϊ�����ֵ
   {
    TempBuffer0[3]=0x2d;	     //0x2dΪ"-"��ASCII��
	TH=~TH;						 //�������Ĳ���ת���ɾ���ֵ
	TH++;
   }
   else TempBuffer0[3]=0x2b;	//0x2BΪ"+"��ASCII��

   if(TL>0x7f)
   {
   TempBuffer0[11]=0x2d;	     //0x2dΪ"-"��ASCII��
   TL=~TL+1;
   }
   else TempBuffer0[11]=0x2b;	//0x2BΪ"+"��ASCII��

  TempBuffer0[4]=TH/100+0x30;		             //�����TH�İ�ʮ��λ
  if( TempBuffer0[4]==0x30) TempBuffer0[4]=0xfe; //��λ������
  TempBuffer0[5]=(TH%100)/10+0x30;				//�����ʮλ
  TempBuffer0[6]=(TH%100)%10+0x30;	 			//�������λ
  TempBuffer0[12]=TL/100+0x30;		             //�����TL�İ�ʮ��λ
  if( TempBuffer0[12]==0x30) TempBuffer0[12]=0xfe; //��λ������
  TempBuffer0[13]=(TL%100)/10+0x30;				//�����ʮλ
  TempBuffer0[14]=(TL%100)%10+0x30;	 			//�������λ
}

/**********�¶�ת��ΪLCD��ʾ����****************
*����:�������ֽڵ��¶�ֵ,���������λ,������С��
	  ��������ת��ΪACSII��,�͵�Һ����ʾ������
************************************************/
void temper_LCD(void)	
{
   unsigned char x=0x00,y=0x00;
   t[0]=*pt;
   pt++;
   t[1]=*pt;
   if(t[1]>0x07)                    //�ж������¶�
   {
    TempBuffer1[0]=0x2d;	     //0x2dΪ"-"��ASCII��
	t[1]=~t[1];			 /*���漸��Ѹ����Ĳ���*/
	t[0]=~t[0]; 		 /* ����ɾ���ֵ*********/
	x=t[0]+1;				 /***********************/
	t[0]=x;					 /***********************/
	if(x>255)                /**********************/
	t[1]++;				 /*********************/
   }
   else TempBuffer1[0]=0x2b;	//0xfeΪ��"+"��ASCII��
  t[1]<<=4;		//�����ֽ�����4λ
  t[1]=t[1]&0x70;		//ȡ�����ֽڵ�3����Ч����λ
  x=t[0];					//��t[0]�ݴ浽X,��ΪȡС�����ֻ�Ҫ�õ���
  x>>=4;					//����4λ
  x=x&0x0f;					//��ǰ���������ȡ��t[0]�ĸ���λ	
  t[1]=t[1]|x;			//���ߵ��ֽڵ���Чֵ����������ƴ��һ���ֽ�
  TempBuffer1[1]=t[1]/100+0x30;		             //+0x30 Ϊ�� 0~9 ASCII��
   if( TempBuffer1[1]==0x30) TempBuffer1[1]=0xfe; //��λ������
  TempBuffer1[2]=(t[1]%100)/10+0x30;				//�����ʮλ
  TempBuffer1[3]=(t[1]%100)%10+0x30;	 			//�������λ
  t[0]=t[0]&0x0c;							//ȡ��Ч����λС��
  t[0]>>=2;									//������λ,�Ա���
  x=t[0];										
  y=dotcode[x];									//������ʵ�ʵ�С��
  TempBuffer1[5]=y/10+0x30;						//�����ʮ��λ
  TempBuffer1[6]=y%10+0x30;						//������ٷ�λ
}			

/*********�����������************
*����:�Ѽ���ֵת������Ӧ�Ĺ��ܱ�־λ
*��ע:Ϊ����߳���Ľ�׳��,�ڹ��ܱ�־λ��Чʱ,
**up_one��down_one����Ч,���Ҹ����ܱ�־֮��
**���û�������,��Ȼ�����鷳,�ر��ǹ��ܱ�־�϶�ʱ
**�����鷳,�������ܱ�־֮����ͬ�����;
**Ҳ�ɲ��ö���if else����,��Ȼ��,
**�������ܱ�־֮���������Ե����ȼ����
**************************************/
void key_command(unsigned char x)			    	
{
	switch(x)
	{
		case 1: up_one=1;break;
  		case 2: down_one=1;break;
		case 5: alarm_up_flag=!alarm_up_flag;break;
		case 6: alarm_down_flag=!alarm_down_flag;break;
		case 7: set_temper_flag=!set_temper_flag;break;
		case 8: alarm_switch=!alarm_switch;break;
		default: break;
	}
	if(!(alarm_up_flag||alarm_down_flag||set_temper_flag))
	{
		up_one=0x00;		//��û����Ӧ���ܱ�־��Чʱ
		down_one=0x00;		//up_one��down_one��������
	}
	if(alarm_up_flag&&(!alarm_down_flag)&&(!set_temper_flag))//�������ޱ���
	{
		if(up_one)//���ޱ�����1
		{
			TH++;up_one=0;
			if(TH>=100)//����100��,���㵽20��
			TH=20;
		}
		if(down_one)//���ޱ�����1
		{
			TH--;down_one=0;
			if(TH<=20)//С��20��,���㵽20��
			TH=20;
		}
	}
	if((!alarm_up_flag)&&(alarm_down_flag)&&(!set_temper_flag))//�������ޱ���
	{
		if(up_one)
		{
			TL++;up_one=0;
			if(TL>=20)//����20��,���㵽0��
			TL=0;
		}
		if(down_one)
		{
			TL--;down_one=0;
			if(TL<=0)//����0��,���㵽0��
			TL=0;
		}
	}
	
	if((!alarm_up_flag)&&(!alarm_down_flag)&&(set_temper_flag))//�����û��궨�¶�
	{
		if(up_one)
		{
			user_temper++;up_one=0;
			if(user_temper>=60)//����60��,���㵽0��
			user_temper=0;
		}
		if(down_one)
		{
			user_temper--;down_one=0;
			if(user_temper<=0)//����0��,���㵽0��
			user_temper=0;
		}			
	}
	//if(alarm_switch)
				
}


main()
{												
 setds18b20(TH,TL,RS);    				//���������ޱ����¶Ⱥͷֱ���
 delay(100); 					 
 while(1)
 {											
    pt=ReadTemperature();		 		 //���º���������������ͷ��ַ
										 //��ȡ�¶�,�¶�ֵ�����һ�������ֽڵ�������,
	temper_LCD();						 //ʵ���¶�ת��ΪACSII��,����Һ����ʾ������
	user_temper_LCD(user_temper);		 //�û��趨�¶�ת��ΪACSII��,����Һ����ʾ������
	alarm_LCD(TH,TL);					 //�����ޱ����¶�ת��ΪASCII��,����Һ����ʾ������
	LCD_Initial();							//��һ�������к�,�ڶ���Ϊ�к�,Ϊ0��ʾ��һ��
											//Ϊ1��ʾ�ڶ���,����������Ϊ��ʾ���ݵ��׵�ַ
	LCD_Print(0,0,TempBuffer0);	
	LCD_Print(0,1,TempBuffer1); 
		
	scan_full();                     //�����޼�����
	if(key_ok)						//���м������򿴵����ĸ�������
	{
	key_value=key_scan();			 //���ü���ɨ�����
	key_command(key_value);			 //�����������
	}			
 }
}
  



