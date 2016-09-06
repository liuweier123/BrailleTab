按下按键，单片机向串口1发送一串数据，串口1将数据发送给串口3
并在虚拟串口上显示
串口3将数据发送给单片机，单片机回显该数据给串口3

可用程序模块

void send_int(void);  串口发送初始化
void send_str();      发送字符串
void send_char(unsigned char txd);发送单个字符