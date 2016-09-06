#ifndef MAIN_H
#define MAIN_H

#define ENABLE_BIT_DEFINITIONS   
#define OutPort  PORTA   
#define ConPort  PORTC
#define TIMES    5      //中断次数




#ifdef MAIN_C
unsigned char data[4] = {0,0,0,0};
unsigned char CNT = 0;  //记数初值
unsigned char KeyUp;
unsigned char KeyDown;
unsigned char timer[2] = {0x00,0x00};

#else
//extern unsigned char table[10];
#endif

#endif
