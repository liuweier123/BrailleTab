#ifdef NUMBER_H
#define NUMBER_H
#ifdef NUMBER_C
//void display(unsigned char *p);
void process(unsigned char i,unsigned char *p);
#else
//extern void display(unsigned char *p);
extern void process(unsigned char i,unsigned char *p);
#endif
#endif
