#ifndef INIT_H
#define INIT_H
#ifdef INIT_C
void InitIo(void);
#else
extern void InitIo(void);
#endif
#endif
