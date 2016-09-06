

#include  "config.h"
#include <intrinsics.h>
//**************************************
#define rs (1<<8)
#define rw (1<<9)
#define en (1<<10)
#define busy (1<<7)

uint8 BCD[6];			//ʮλ�����Ƶ���ʾ��ֱ���ǧ��ʮ��λ����ʾ
//uint8 txt[]={"HelloWorld"};
uint8 txt[]={"LPC2106!!!"};

void ChkBusy()
{
	IODIR=0xff00;
	while(1)
	{
		IOCLR=rs;
		IOSET=rw;
		IOSET=en;
		if(!(IOPIN & busy))break;
		IOCLR=en;
	}
	IODIR=0xffff;
}

void WrOp(uint8 dat)
{
	ChkBusy();
	IOCLR=rs;		//ȫ������
	IOCLR=rw;
	IOCLR=0xff;		//������
	IOSET=dat;		//������
	IOSET=en;
	IOCLR=en;
}

void WrDat(uint8 dat)	//������
{
	ChkBusy();
	IOSET=rs;
	IOCLR=rw;
	IOCLR=0xff;		//������
	IOSET=dat;		//������
	IOSET=en;
	IOCLR=en;
}

void lcd_init(void)
{
	WrOp(0x38);			
	WrOp(0x06);			//����1
	WrOp(0x0c);			//����ʾ
}

void DisText(uint8 addr,uint8 *p)
{
	WrOp(addr);
	while(*p !='\0')WrDat(*(p++));
}

void ShowInt(uint8 addr,uint16 num)			//��addr����ʾ����num
{//��numת�������BCD������ȫ������BCD[5]��
	uint8 i;
	for(i=5;i>0;i--)       //��NUM����ת����ASCII��,��521��ת��Ϊ00521
	{
       	  BCD[i-1]=(uint8)(num%10+0x30);     //ȡ�����λ
       	  num/=10;                           //ȥ�����λ
    }
    i=0;
	while(BCD[i] ==0x30 && i<4) BCD[i++]=' ';    //NUMת����������,����û�м���С����
	BCD[5]='\0';
	DisText(addr,BCD);
}

void ShowByte(uint8 addr,uint8 num)
{//��numת�������BCD������ȫ������BCD[5]��
	uint8 i;
	for(i=3;i>0;i--)       //��NUM����ת����ASCII��,��521��ת��Ϊ00521
	{
       	  BCD[i-1]=(uint8)(num%10+0x30);     //ȡ�����λ
       	  num/=10;                           //ȥ�����λ
    }
    i=0;
	while(BCD[i] ==0x30 && i<2) BCD[i++]=' ';    //NUMת����������,����û�м���С����
	BCD[3]='\0';
	DisText(addr,BCD);
}



int  main(void)
{   
    lcd_init();
	IODIR=0xffff;		//����Ϊ���
	IOCLR=0xffff;
		
	DisText(0x86,txt);
	while(1);
}
