#ifndef USART_H
#define USART_H
#ifdef USART_C
void UsartInit(void);
int PutChar(char c);
void SendNbyte(unsigned char *p,unsigned char L);
void PutStr(unsigned char *Str);
#else
extern void UsartInit(void);
extern int PutChar(char c);
extern void SendNbyte(unsigned char *p,unsigned char L);
extern void PutStr(unsigned char *Str);
#endif
#endif