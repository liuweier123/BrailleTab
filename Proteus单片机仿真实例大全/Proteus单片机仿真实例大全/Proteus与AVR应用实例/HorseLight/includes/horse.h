#ifndef HORSE_H
#define HORSE_H
#ifdef HORSE_C
void horse(unsigned char i);
#else
extern void horse(unsigned char i);
#endif
#endif