// �ļ��� delay.c ��ʱ

#include "config.h"
/***************************************************************************
��ʱ M32 7.3728M ���Լ���
*/
void Delay100us(uint8 x)
{
	uint8 i;          //4clock                   
	for(i=147;x!=0;x--)	
	while(--i);      //5 * i clock
}
void Delay1ms(uint16 n)
{        
	for (;n!=0;n--){
		Delay100us(10);
	}
}
void Delay1s(uint16 m)         //  m <= 6 ,when m==7, it is 1. 
{
	m=m*40;                
	for (;m!=0;m--){
		Delay100us(250);
	}
}
