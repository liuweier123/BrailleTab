//change.h//
//数制转换函数集,将数字转换成ASCII字符串，结果保存到outbufful缓冲区
//#ifndef __CHANGE_H__
//#define __CHANGE_H__
#define UCHAR unsigned char
#define	UINT unsigned int
#define	ULONG unsigned long
#define	LONG unsigned long

unsigned char * chnint(unsigned int ui,unsigned char j);		//输出一个无符号整型数的十进制表示，必须标示小数点的位置,自动删除前面无用的零
unsigned char * chnchar(unsigned char c,unsigned char j);//输出一个无符号字符数的十进制表示，必须标示小数点的位置,自动删除前面无用的零

/*unsigned char * chnhex(unsigned char c);			//一个字节转换成两个字节hex码

char * itoa(UINT, char *, UCHAR);

*/
