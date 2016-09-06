#ifndef AD_H
#define AD_H
#ifdef AD_C
unsigned char  adc_mux ;
void init_adc(void);
#else
extern unsigned char adc_mux;
extern void init_adc(void);
#endif
#endif
