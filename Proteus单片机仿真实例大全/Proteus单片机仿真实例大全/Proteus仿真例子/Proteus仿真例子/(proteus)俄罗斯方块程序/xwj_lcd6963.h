#define ulong		unsigned long
#define uint		unsigned int
#define uchar		unsigned char
			// T6963C 公用函数
void Lcd6963Cursor(unsigned char uCol,unsigned char uRow);// 设置当前显示行、列
void Lcd6963ChHz(bit);					// 切换16点阵和12点阵显示方式
char Lcd6963Init(void);					// Lcd6963 初始化
void Lcd6963Cls(void);						// 清屏
void print(char *uStr);			// ASCII(8*16)  汉字(16*16) 及 汉字(12*12) 显示函数
void printat(uchar uCol,uchar uRow,char *uStr);	// ASCII(8*16)  汉字(16*16) 及 汉字(12*12) 显示函数
//unsigned char dprintf(char *fmt, ...);	// 格式化 显示函数
void Lcd6963Line(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2);	//划线条:y=0~63:点亮|；y=64~127:清除&；y=128~191:写字节W；y=192~255:取反^；
void Lcd6963Rec(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2);	//定点画一个矩形框
void Lcd6963Fillrec(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2);//定点填充一个矩形
//void Lcd6963Frec(unsigned char x,unsigned char y,unsigned char lx,unsigned char ly);	//定点填充一个矩形
//void Lcd6963Wstr(unsigned char x,unsigned char y,unsigned char *str);			// 12＊12点阵中英文混合显示函数
void Lcd6963CIrcle(unsigned char x,unsigned char y,unsigned char r);			//中点法画圆
//void Lcd6963Cleanx(unsigned char x);							//清除1列 函数Lcd6963Cleanx()调用
//--------------------------------------------------------------------------//
//void show_v(void);									//显示波形(示例)
void Lcd6963main(void);						// Lcd6963测试用
//--------------------------------------------------------------------------//
