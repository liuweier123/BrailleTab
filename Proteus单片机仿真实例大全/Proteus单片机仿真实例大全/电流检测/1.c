#include <reg51.h>

#define x 1			//����ϵ��
#define p 2		//�Ŵ���
void main()
	{
	int i,j;
	EA=1;
	EX0=1;
	IT0=1;
	P3_0=0;
	P3_1=0;
	P0=0;
	P2=0;
	while(1)
	{
	for (j=0;j<1;j++)		//�����ӳ٣������ö�ʱ���Ƚ�׼ȷ
	for (i=0;i<500;i++)
		;
	P3_0=1;					//��ַ����
	for (i=0;i<50;i++)
	;
	P3_1=1;					//����AD
	for (i=0;i<100;i++)
	;
	P3_0=0;
	P3_1=0;
	}}

void int0() interrupt 0
	{
	char a,b,c,d;
	int out;
	EA=0;
	out=(P1*100.0/255.0)*5/p/0.1;		//�������ֵ
	b=out%100/10;				//ȡС�����һλ
	a=out%1000/100*16;			//ȡ��λ
	if(out>=1000)				//ȡʮλ
	c=out/1000*16;
	else
	c=0;
	d=out%10;					//ȡС�������λ
	P2=a|b;
	P0=c|d;
	EA=1;
	}
	

