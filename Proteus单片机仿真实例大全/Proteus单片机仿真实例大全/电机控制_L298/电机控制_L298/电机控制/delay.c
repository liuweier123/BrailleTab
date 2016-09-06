// 文件名 delay.c 延时

#include "config.h"
/***************************************************************************
延时 M32 7.3728M 粗略计算
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
