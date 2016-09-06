//*.h file
#ifndef __SHURU_H__
#define __SHURU_H__
bit pkey();    //判断有没有键按下
unsigned char kbscan(void);          //键盘扫描
void input(void); //号码输入
void delay(void); //消抖动
extern unsigned char key;
#endif   