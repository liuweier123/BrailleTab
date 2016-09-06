/*-----------------------------------------------------------------------
��ʱ����
ϵͳʱ�ӣ�8M
-----------------------------------------------------------------------*/
#ifndef DELAY_H
#define DELAY_H
#ifdef DELAY_C
void delay_1us(void);                 //1us��ʱ����
void delay_nus(unsigned int n);       //N us��ʱ����
void delay_1ms(void) ;                //1ms��ʱ����
void delay_nms(unsigned int n) ;      //N ms��ʱ����
#else
extern void delay_1us(void);                 //1us��ʱ����
extern void delay_nus(unsigned int n);       //N us��ʱ����
extern void delay_1ms(void) ;                //1ms��ʱ����
extern void delay_nms(unsigned int n) ;      //N ms��ʱ����
#endif
#endif
