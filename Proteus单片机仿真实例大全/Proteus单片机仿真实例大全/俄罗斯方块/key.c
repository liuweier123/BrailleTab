#include <AT89X52.h>
#include "typedef.h"

#define Nothing 100
//�˿ڶ���
sbit C1 = P2^3;
sbit C2 = P2^4;
sbit C3 = P3^2;
sbit C4 = P3^3;

sbit R1 = P3^4;
sbit R2 = P3^5;
sbit R3 = P3^0;
sbit R4 = P3^1;

uchar Key=Nothing;		  //���̻���Ĵ������������ݣ�
uchar Fn_Key;			 //���ܼ�

//*********************************************************************
//= ����ԭ��: void KEYPAD_Scan(char* const Key, char* const Fn_Key)
//= ��    ��: ɨ�����
//= ��    ��: ��ͨ��New_Key�����ܼ�New_FuncKey,��������ָ��
//= �� �� ֵ:
//= �������ʣ�˽�к���
//**********************************************************************

void KEYPAD_Scan(char* const Key, char* const Fn_Key)
{

   C1 = 0; 
      if (R1 == 0) *Fn_Key = 'o'; //ON��
      if (R2 == 0) *Key    =  0;
      if (R3 == 0) *Fn_Key = '=';
      if (R4 == 0) *Key    = '+';
   C1 = 1;

   C2 = 0; 
      if (R1 == 0) *Key = 1;
      if (R2 == 0) *Key = 2;
      if (R3 == 0) *Key = 3;
      if (R4 == 0) *Key = '-';
   C2 = 1;

   C3 = 0; 
      if (R1 == 0) *Key = 4;
      if (R2 == 0) *Key = 5;
      if (R3 == 0) *Key = 6;
      if (R4 == 0) *Key = '*';
   C3 = 1;

   C4 = 0; 
      if (R1 == 0) *Key = 7;
      if (R2 == 0) *Key = 8;
      if (R3 == 0) *Key = 9;
      if (R4 == 0) *Key = '/';   

   C4 = 1;

}
//*********************************************************************
//= ����ԭ��: void KEY_Update()
//= ��    ��: ���̻���Ĵ������³���. ��ͨ��Key, ���ܼ�Fn_Key
//= ��    ��: 
//= �� �� ֵ:
//= �������ʣ����к���
//**********************************************************************
void KEY_Update() 
{
   static uchar delay=20;		//ȥ������ʱ
   static bit delaying=0;		//��ʶ�Ƿ�������ʱ

   if(delaying==0)
   {
       if(Key==Nothing)		   //���Key�������е�����δ����ȡ����ɨ�����
	   {
	      KEYPAD_Scan(&Key,&Fn_Key);	   //ɨ�����
		  if(Key!=Nothing)
		  {
		     delaying=1; 
			 Key=Nothing; 

		   }
		}
   }
   else
   {
      if(delay==0)				 //��ʱ����
	  {
	     KEYPAD_Scan(&Key,&Fn_Key);	   //��ȡ����
		 delay=20;
		 delaying=0;
	  }
	  else   delay--;			//��ʱ��һ
   }
}						   


  


    
