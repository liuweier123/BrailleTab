#if !defined(DELAY_H)
#define DELAY_H

#if defined DELAY_C
 void delay_1us(void);                 //1us��ʱ����
 void delay_nus(unsigned int n);       //N us��ʱ����
 void delay_1ms(void) ;                //1ms��ʱ����
 void delay_nms(unsigned int n) ;      //N ms��ʱ����
 void WDR(void);
 void WDT_init(void);
#else
extern void delay_1us(void);                 //1us��ʱ����
extern void delay_nus(unsigned int n);       //N us��ʱ����
extern void delay_1ms(void) ;                //1ms��ʱ����
extern void delay_nms(unsigned int n) ;      //N ms��ʱ����
extern void WDR(void);
extern void WDT_init(void);

#endif
#endif

 
