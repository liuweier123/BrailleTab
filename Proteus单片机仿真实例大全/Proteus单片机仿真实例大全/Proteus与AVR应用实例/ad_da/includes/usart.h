#ifndef USART_H
#define USART_H
#ifdef USART_C
void put_char(unsigned char ch);
void InitSerial(void);
void put_string(unsigned char *sting);
#else
extern void put_char(unsigned char ch);
extern void InitSerial(void);
extern void put_string(unsigned char *sting);
#endif
#endif
