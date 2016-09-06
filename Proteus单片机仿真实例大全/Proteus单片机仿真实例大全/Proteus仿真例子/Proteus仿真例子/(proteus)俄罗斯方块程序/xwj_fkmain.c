#define ulong		unsigned long
#define uint		unsigned int
#define uchar		unsigned char

#include "xwj_lcd16.h"	 				// �ַ�Һ�����ƺ�������    //
#include "xwj_lcd6963.h"			// T6963C ���ú���
#include "xwj_fk.h"
#include "xwj_serial.h"		//���ں�����
#include "xwj_hlkey.h"			//  P1������ʽ����  //


// ---------------------------------------------- //	32�ֽ�
void delay(uint x)
{
   uint i,j;
   for (i=0; i<x;i++) {
      for (j=0;j<102; j++) ;
   }
}

//--------------------------------------------------------------------------//
void main(void)						// ������
{
	serial_init();
	Lcd6963Init();					//Lcd6963��λ
	Lcd16Reset();					//Lcd16��λ
	Serial_main();					//	���ڲ�����������  
	Lcd16main();					//Lcd16��ʱ����������
	delay(1000);
	Lcd6963main();					//Lcd6963������
//	Lcd6963Cls();
	fk_init();						//�����ʼ��
	while(1)
	{
		if (~fk_run)
			fk_init();				//�����ʼ��
		fk_move();					//�ƶ�����
		delay(10);
	}
}

