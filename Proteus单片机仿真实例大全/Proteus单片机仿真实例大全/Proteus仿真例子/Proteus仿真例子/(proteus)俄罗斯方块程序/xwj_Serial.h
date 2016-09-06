//---------------- xwj_Serial.c //---------------串口相关
//串口函数集,仅需做简单调用即可完成串口输入输出的处理,出入均设有缓冲区，大小可任意设置
void serial_init ();
unsigned char getbyte(void);				//从接收缓冲区取一个byte,如不想等待则在调用前检测inbufsign是否为1。
bit  checkin(void); 						//检测接收缓冲区是否有数据
void putchar(unsigned char c);						//放入一个字节到发送缓冲区
//void getline(unsigned char idata *line, unsigned char n); //获取一行数据回车结束，必须定义最大输入字符数
//void putbytes(unsigned char *outplace,unsigned char j);	//放一串数据到发送缓冲区，自定义长度
//void putstring(unsigned char code *puts);	//发送一个定义在程序存储区的字符串到串口
//void puthex(unsigned char c);				//发送一个字节的hex码，分成两个字节发。
//void putbyte(unsigned char c,unsigned char j);	//输出一个无符号字符数的十进制表示，必须标示小数点的位置,自动删除前面无用的零
//void putint(unsigned int ui,unsigned char j);	//输出一个无符号整型数的十进制表示，必须标示小数点的位置,自动删除前面无用的零
//void clr(void);								// 发送一 '清除屏幕' 到VT100终端
void putinbuf(unsigned char c);				//人工输入一个字符到输入缓冲区
void Serial_main(void);		//	串口测试用主函数  

