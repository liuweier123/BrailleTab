#ifndef INIT_H
#define INIT_H

#ifdef INIT_C

void WDR(void);
void WDT_init(void);
void init_time1(void);
#else
extern void WDR(void);
extern void WDT_init(void);
extern void init_time1(void);
#endif
#endif
