#ifndef __init_H__
#define __init_H__ 1


//端口初始化
extern void port_init(void);

//T2初始化
void timer2_init(void);

//各种参数初始化
extern void  init_devices(void);

#endif