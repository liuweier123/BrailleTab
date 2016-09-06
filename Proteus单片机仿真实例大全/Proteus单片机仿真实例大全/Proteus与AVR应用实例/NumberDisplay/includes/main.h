#ifndef MAIN_H
#define MAIN_H

#define ENABLE_BIT_DEFINITIONS   
#define OutPort  PORTA   
#define ConPort  PORTC





#ifdef MAIN_C
unsigned char data[4] = {0,0,0,0};
unsigned char CNT = 0;  //¼ÇÊý³õÖµ
unsigned char KeyUp;
unsigned char KeyDown;

#else
//extern unsigned char table[10];
#endif

#endif
