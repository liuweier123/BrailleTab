#include <reg51.h>
#include "data.h"
#include "order.h"
#include "lcdinit.c"
#include "function.c"

void int1(void) interrupt 2
{
	keyboard();
}

int main(){
	uchar i=1;
	error0=0;
	error1=0;
	error2=0;
	delay(50);
	EA=1;
	IT1=1;
	EX1=1;
//	wirte_bg();
	/*Һ����ʼ������(�ı����׵�ַD1,�ı����׵�ַD2, �ı������,  ͼ�����׵�ַD1, ͼ�����׵�ַD2, ͼ�������,   �����״,  ��ʾ��ʽ,  ��ʾ����)*/
	lcd_init(0x00,0x00,0x14,0x50,0x01,0x14,0x00,MOD_XOR,0x0c);
//	wirte_bg();
	set_cgram();
	wirte_cgrom();
	cls();
	start();
	cls();
	pushbox();
	guan();
	while(1){
	}
	return(0);
}