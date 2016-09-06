#ifndef _UNIT_H__
#define _UNIT_H__ 1  
//100us
extern void Delay100us(uint8 n);
//1s
extern void Delay1s(uint16 n); //  n <= 6 ,when n==7, it is 1. 
//1ms
extern void Delay1ms(uint16 n);

#endif