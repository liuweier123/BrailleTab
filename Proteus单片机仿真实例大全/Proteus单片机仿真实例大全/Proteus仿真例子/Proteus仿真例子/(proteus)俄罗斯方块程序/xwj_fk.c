//--------------------------------------------------------------------------//
//                                Դ����󹫿�                              //
//                    (c) Copyright 2001��2005 xuwenjun                     //
//                            All Rights Reserved                           //
//                                    V1.00                                 //
//--------------------------------------------------------------------------//
//�ꡡ��: ����˹�������                            �                       //
//�ļ���: xwj_fk.c                                                          //
//�桡��: V1.00                                                             //
//�޸���: ���ľ�                         E-mail:xuwenjun@21cn.com           //
//�ա���: 05-05-13                                                           //
//�衡��: ����˹�������                            �                       //
//������:                                                                   //
//        ���´��������ṩ��ѧϰ��;�������û��޸ĺ�������ļ�����������. //
//        ��������ҵ��;����������ϵ.    E-mail:xuwenjun@21cn.com           //
//        ��������mailto xuwenjun@21cn.com   ��ӭ���ҽ���!                  //
//--------------------------------------------------------------------------//
//�ϰ汾: ��                             �ϰ汾�ļ���:                      //
//������: ���ľ�                         E-mail:xuwenjun@21cn.com           //
//�ա���: 05-05-13                                                          //
//�衡��:                                                                   //
//      1������������ֱ��ʹ��                                               //
//      2��ģ�������ǿ����ֲ���㣬�ⲿ��init��move�������޸���ʾ�����뼴�� //
//      3���Լ����ڴ�ռ�á�����������Ļ���������ʵ��Ż�                     //
//      4���·������ɸ߶�����������޹���                                   //
//      5�����滷��ΪKeil7.5+Proteus6.5,��������Ҳ���ѻ�����                //
//      CODE SIZE        =   1845    ----                                   //
//      CONSTANT SIZE    =    326    ----                                   //
//      DATA SIZE        =     16      19                                   //
//      IDATA SIZE       =     50    ----                                   //
//      BIT SIZE         =      1       1                                   //
//--------------------------------------------------------------------------//
#include <stdlib.h>
#include "xwj_lcd16.h"	 			// �ַ�Һ�����ƺ�������    //
#include "xwj_lcd6963.h"			// T6963C ���ú���
#include "xwj_hlkey.h"				//  P1������ʽ����  //
#include "xwj_serial.h"				//���ں�����
#include "change.h"					//����ת��
#include "xwj_fk.h"					//����˹�������

#define ulong		unsigned long
#define uint		unsigned int
#define uchar		unsigned char

extern void delay(unsigned int x);
//----------------����˹�����ڲ�����----------------------------------------//
void fk_dot(uchar x,uchar y);		//��ʾ1�������
void fk_cldot(uchar x,uchar y);		//���1�������
void fk_show(void);					//��ʾ����
void fk_reffk(void);				//ˢ�·���
void fk_refnew(void);				//ˢ��Ԥ������
void fk_refline(yy);				//ˢ��1�б���
bit  fk_chk(void);					//��ͻ���
void fk_new(void);					//�����·���
void fk_add(void);					//����ϲ�

/*
//-----------------����˹���鹫�ú���--------------------------------------//
void fk_init(void);						//�����ʼ��
void fk_move(unsigned char mode);		//�ƶ�����
*/

//-------------------------------------------------------------------------//
#define FULLMAP	0x0fff				/*����*/
#define LINEGUAN	20				/*20�й�һ��*/
#define NEWX	15					/*Ԥ������Xλ��*/
#define NEWY	12					/*Ԥ������Yλ��*/
#define LINEMAX	21					/*��Ļ���21��*/
uint idata fk_map[LINEMAX+4];		//����ӳ��
uchar  fk_x,fk_y,fk_r;				//�������ҡ��߶ȡ�����
uchar fk_type;						//������״
uchar  fk_oldx,fk_oldy,fk_oldr;		//�����ϴ����ҡ��߶ȡ�����
uchar  fk_newtype,fk_newr;			//�·�����״������
uint score;							//�ܷ�
uint line;							//������	
uchar speed;						//�ٶ�
uchar moven;						//�ٶ���ؼ�����
uchar automapn;						//������������
bit fk_run;							//����˹�����Ϸ����
	
uchar code fk_mod[][4][4]={			//����ģ�ͺ�,4������,4��
	0,0,7,2,0,1,3,1,0,0,2,7,0,2,3,2,	//_|_
	0,0,6,3,0,1,3,2,0,0,6,3,0,1,3,2,	//_|~
	0,0,3,6,0,2,3,1,0,0,3,6,0,2,3,1,	//~|_
	0,0,7,4,0,3,1,1,0,0,1,7,0,2,2,3,	//|__
	0,0,7,1,0,1,1,3,0,0,4,7,0,3,2,2,	//__|
	0,0,0,15,1,1,1,1,0,0,0,15,1,1,1,1,	//____
	0,0,3,3,0,0,3,3,0,0,3,3,0,0,3,3,	//����
};

uchar code strmap[4][9]={
	"����  ","�����  ","�ü�����","̫���ˣ�",
};

//--------------------------------------------------------------------------//
void fk_dot(uchar x,uchar y)		//��ʾ1�������
{
	printat(x*3+1, 241-(y-4)*12,"��");
}

//--------------------------------------------------------------------------//
void fk_cldot(uchar x,uchar y)		//���1�������
{
//	printat(x*3+1, 241-(y-4)*12,"��");
	printat(x*3+1, 241-(y-4)*12,"��");
}

//--------------------------------------------------------------------------//
void fk_show(void)					//��ʾ����
{
	printat(50, 12,chnint(score,1));
	printat(60, 12,"00");
	printat(40, 12,"�÷�:");
	printat(54,36,chnint(line,1));
	printat(40, 36,"����:");
	printat(54,60,chnchar(speed,1));
	printat(40,60,"�ٶ�:");
	printat(54,84,chnchar(automapn,1));
	printat(40,84,"����:");		
}

//--------------------------------------------------------------------------//
void fk_reffk(void)					//ˢ�·���
{
	uchar i,j;
	uchar temp;
	//----------------------------------------------//���ԭ���ķ���
	for (i=0;i<4;i++)
	{
		temp=(fk_mod[fk_type][fk_oldr][i]);
		for (j=fk_oldx;j<fk_oldx+4;j++)
		{
			if(temp&0x01)
			{
				fk_cldot(j,fk_oldy+i);
			}
			temp>>=1;
		}
	}
	//----------------------------------------------//��ʾ�µķ���
	for (i=0;i<4;i++)
	{
		temp=(fk_mod[fk_type][fk_r][i]);
		for (j=fk_x;j<fk_x+4;j++)
		{
			if(temp&0x01)
			{
				fk_dot(j,fk_y+i);
			}
			temp>>=1;
		}
	}
	fk_oldx=fk_x;fk_oldy=fk_y;fk_oldr=fk_r;	//�����·���λ��
}

//--------------------------------------------------------------------------//
void fk_refnew(void)				//ˢ��Ԥ������
{
	uchar i,j;
	uchar temp;
	//----------------------------------------------//Ԥ������
	for (i=0;i<4;i++)
	{
		temp=(fk_mod[fk_newtype][fk_newr][i]);
		for (j=NEWX;j<NEWX+4;j++)
		{
			if(temp&0x01)
			{
				fk_dot(j,NEWY+i);
			}
			else
			{
				fk_cldot(j,NEWY+i);
			}
			temp>>=1;
		}
	}
}

//--------------------------------------------------------------------------//
void fk_refline(yy)					//ˢ��1�б���
{
	uchar i;
	uint temp;
	if (yy>=4)
	{
		temp=fk_map[yy];
		for (i=0;i<12;i++)
		{
			if ((temp&0x01) !=0)
				fk_dot(i,yy);
			else
				fk_cldot(i,yy);
			temp >>= 1;
		}
	}
}

//--------------------------------------------------------------------------//
bit fk_chk(void)					//��ͻ���
{
	uchar i;
	bit neq=0;
	for (i=0;i<4;i++)
	{
		if ( (((fk_mod[fk_type][fk_r][i])<<fk_x)+(fk_map[fk_y+i])) != (((fk_mod[fk_type][fk_r][i])<<fk_x)|(fk_map[fk_y+i])) )
			neq=1;
	}
	return(neq);
}

//--------------------------------------------------------------------------//
void fk_new(void)						//�����·���
{
	srand(rand()+fk_x+fk_y+fk_r);
	fk_oldx=fk_x=5;
	fk_oldy=fk_y=LINEMAX;
    fk_type = fk_newtype;
	fk_oldr=fk_newr;
    fk_newtype = rand()%7;
	fk_newr=rand()%4;
	fk_refnew();			//ˢ��Ԥ������
	if (fk_run)
		fk_reffk();	//ˢ����ʾ
}

//--------------------------------------------------------------------------//
void fk_add(void)					//����ϲ�
{
	uchar i,j;
	uchar full=0x00;
	uchar fulltemp;
	uchar fullline=0x00;
	for (i=0;i<4;i++)	//����ϲ�
	{
		fk_map[fk_y+i] |= (fk_mod[fk_type][fk_r][i])<<fk_x;
		full <<= 1;
		if ((fk_y+i >= 4) && (fk_map[fk_y+i] == 0xffff))		//����
		{
			full |= 0x01;
		}
	}
	if (full != 0)		//������
	{
		for (j=0;j<3;j++)		//������˸3��
		{
			delay(300);
			fulltemp=full;
			for (i=0;i<4;i++)	//4��
			{
				if ((fulltemp&0x08) != 0)
				{
					fk_map[fk_y+i] ^= FULLMAP;
				}
				fk_refline(fk_y+i);
				fulltemp <<= 1;
			}
		}
		fulltemp=full;
		for (i=fk_y;i<LINEMAX+4+fullline;i++)	//����������
		{
			if ((i < LINEMAX+4)&&(fk_map[i-fullline]!=fk_map[i]))
			{
				fk_map[i-fullline]=fk_map[i];
				fk_refline(i-fullline);
			}
			if ((i >= LINEMAX+4)&&(fk_map[i-fullline]!=~FULLMAP))
			{
				fk_map[i-fullline]=~FULLMAP;	//����ӳ��
				fk_refline(i-fullline);
			}
			if ((fulltemp&0x08) != 0)
			{
				fullline++;
			}
			fulltemp <<= 1;
		}
		if (((line+fullline)/LINEGUAN) != (line/LINEGUAN))//ÿ20���ٶ�+1
			speed ++;
		line += fullline;				//���·���������
		score += (1<<fullline)-1;
		printat(46,180,strmap[fullline-1]);	//�佱
		fk_show();						//��ʾ����
		fk_new();			//�����·���
	}
	else
	{
		if (fk_y > LINEMAX-10)	//�����λ����ײ�Ҳ�����������Ϸ����
			printat(46,180,"���Ͱ���");		//���Ͱ�
		if (fk_y > LINEMAX-6)	//�����λ����ײ�Ҳ�����������Ϸ����
			printat(46,180,"����ˣ�");		//�����

		if (fk_y==LINEMAX)		//�����λ����ײ�Ҳ�����������Ϸ����
			fk_run=0;	//�����ʼ��
		else
			fk_new();	//�����·���
	}
}

//--------------------------------------------------------------------------//
void fk_init(void)					//�����ʼ��
{
	uchar i;
	fk_run = 0;
	moven=0;
	Lcd6963Cls();
	Lcd6963Rec(0,0,152,255);
	Lcd6963ChHz(0);					//�л���16X16����
	printat(2, 16,"��ӭ�����ľ���");
	printat(2, 48,"�밴��ѡ��");
	printat(2, 80,"-----------------");
	printat(2, 96,"7���� 8���� 9����");
	printat(2, 112,"4���� 5���� 6����");
	printat(2, 128,"4�ٶ� 5��ʼ 6����");
	printat(2, 144,"1���� 2���� 3����");
	printat(2, 160,"-----------------");
	Lcd6963ChHz(1);					//�л���12X12����
	printat(46,180,"��ӭʹ��");
	fk_show();						//��ʾ����
	while (~fk_run)
	{
		fk_move();					//�ȴ������ٶȹ�����ʼ
		delay(10);
	}
	for (i=0;i<4;i++)
	{
		fk_map[i]=0xffff;	//����ӳ��
	}	delay(3000);
	for (i=4;i<LINEMAX+4;i++)
	{
		if (i<(automapn+4))
			fk_map[i]=rand()-1|~FULLMAP; //����ӳ��
		else
			fk_map[i]=~FULLMAP;		//����ӳ��
		fk_refline(i);				//ˢ��1�б���
	}
	fk_show();						//��ʾ����
//	fk_new();						//�����·���
}   

//--------------------------------------------------------------------------//
void fk_move(void)						//�ƶ�����
{
	unsigned char temp;
	if(KeyTest())					//������ް���
	{
		putinbuf(KeyGetCode());		//������������ջ�����
	}
	if (checkin())
	{
		temp=getbyte();
		if (temp!=0) Lcd16WrCharhh(12,0,temp);
		if (temp!=0) Lcd16WrChar(15,0,temp);
		putchar(temp);
	}
	else
		temp=0xff;					//�޼���Ϊ��Ч���������Ʒ���
	temp -= '0';
	switch(temp)
	{
	default:
		if (--moven)				//��Ϸ�Ѷ�
			break;
		else
		{
			moven=(252>>speed)+2;
		}
	case 2:		//����
		if (fk_run)					//��Ϸ������
		{
			if(fk_y>0)
			{
				fk_y--;
				if(fk_chk())
				{
					fk_y++;		//�г�ͻȡ������,ִ����ײ���
					fk_add();	//����ϲ�	//�����·���
				}
			}
			else				//���鵽��Ҳִ����ײ���
			{
				fk_add();		//����ϲ�
			}
		}
		else						//��ʼ��ʱ
		{
			fk_new();				//�����·���
		}
		break;
	case 0:		//���Ƶ���
		while((fk_y>0)&&~(fk_chk())) //һֱ����ֱ����ͻ
		{
			fk_y--;
		}
		moven=1;
		fk_y++;				//�ָ���δ��ͻλ��
		break;
	case 3:		//����
	case 6:		//����
		if (fk_run)					//��Ϸ������
		{
			if(fk_x<12)
			{
				fk_x++;
				if(fk_chk())
					fk_x--;//�г�ͻȡ������
			}
		}
		else							//��ʼ��ʱ
		{
			automapn++;
			automapn &= 0x0f;
			fk_show();					//��ʾ����
		}
		break;
	case 1:		//����
	case 4:		//��
		if (fk_run)						//��Ϸ������
		{
			if(fk_x>0)
			{
				fk_x--;
				if(fk_chk())
					fk_x++;//�г�ͻȡ������
			}
		}
		else							//��ʼ��ʱ
		{
			speed++;
			speed &= 0x07;
			fk_show();					//��ʾ����
		}
		break;
	case 9:		//��ת
	case 8:		//��ת
	case 5:		//��ת
		if (fk_run)						//��Ϸ����ת
		{
			fk_r++;
			if(fk_chk())
				fk_r--;					//�г�ͻȡ������
			fk_r &= 0x03;
		}
		else							//��ʼ��ʱ
		{
			fk_run = 1;
		}
		break;
	case 7:		//��ת
		if (fk_run)						//��Ϸ����ת
		{
			fk_r--;
			if(fk_chk())
				fk_r++;				//�г�ͻȡ������
			fk_r &= 0x03;
		}
		else							//��ʼ��ʱ
		{
			fk_run = 1;
		}
		break;
	}
	if((fk_run)&& ((fk_x!=fk_oldx)||(fk_y!=fk_oldy)||(fk_r!=fk_oldr)) )
	{
		fk_reffk();	//ˢ����ʾ
	}
	rand();
}

/*
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
	Lcd6963main();					//Lcd6963������
	fk_init();						//�����ʼ��
	while(1)
	{
		if (~fk_run)
			fk_init();						//�����ʼ��
		fk_move();					//�ƶ�����
		delay(10);
	}
}
*/
