#if !defined(USART_H)
#define USART_H
#if defined UCART_C
int usart_putchar(char c);
void init_usart(void);
#else
extern int usart_putchar(char c);
extern void init_usart(void);
#endif
#endif
/***************************/
