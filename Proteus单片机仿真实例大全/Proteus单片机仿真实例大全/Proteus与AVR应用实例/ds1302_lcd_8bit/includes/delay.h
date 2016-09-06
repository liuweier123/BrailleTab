#if !defined(DELAY_H)
#define DELAY_H

#if defined DELAY_C
 void delay_1us(void);                 //1us延时函数
 void delay_nus(unsigned int n);       //N us延时函数
 void delay_1ms(void) ;                //1ms延时函数
 void delay_nms(unsigned int n) ;      //N ms延时函数
#else

extern void delay_1us(void);                 //1us延时函数
extern void delay_nus(unsigned int n);       //N us延时函数
extern void delay_1ms(void) ;                //1ms延时函数
extern void delay_nms(unsigned int n) ;      //N ms延时函数

#endif
#endif

 
