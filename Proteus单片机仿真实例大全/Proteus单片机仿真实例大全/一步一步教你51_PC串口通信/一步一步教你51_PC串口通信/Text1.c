#include <reg51.h>
#include <intrins.h>

unsigned char key_s, key_v, tmp;
char code str[] = "I love zhu xiao ying--CUMT \n\r";

void send_int(void);
void send_str();
bit	scan_key();
void proc_key();
void delayms(unsigned char ms);
void send_char(unsigned char txd);

sbit	K1 = P1^4;

main()
{
    send_int();
	TR1 = 1;			            	// 启动定时器1
	while(1)
	{
		if(scan_key())	            	// 扫描按键
		{
			delayms(10);			// 延时去抖动
			if(scan_key())			// 再次扫描
			{
				key_v = key_s;		// 保存键值
				proc_key();			// 键处理
			}
		}
		if(RI)						// 是否有数据到来
		{
			RI = 0;
			tmp = SBUF;				// 暂存接收到的数据
			P0 = tmp;				// 数据传送到P0口
			send_char(tmp);			// 回传接收到的数据
		}	
	}

}
void send_int(void)
{     TMOD = 0x20;			// 定时器1工作于8位自动重载模式, 用于产生波特率
	TH1 = 0xF3;				// 波特率2400
	TL1 = 0xF3;
	SCON = 0x50;			// 设定串行口工作方式
	PCON&= 0xef;			// 波特率不倍增
		

	IE = 0x0;				// 禁止任何中断
}
bit scan_key()	
// 扫描按键                               
{
	key_s = 0x00;
	key_s |= K1;
	return(key_s ^ key_v);	
}

void proc_key()
// 键处理
{
	if((key_v & 0x01) == 0)
	{			// K1按下
		send_str();				// 传送字串
	}
}

void send_char(unsigned char txd)
// 传送一个字符
{
	SBUF = txd;
	while(!TI);				// 等特数据传送
	TI = 0;					// 清除数据传送标志
}

void send_str()
// 传送字串
{
	unsigned char i = 0;
	while(str[i] != '\0')
	{
		SBUF = str[i];
		while(!TI);				// 等特数据传送
		TI = 0;					// 清除数据传送标志
		i++;					// 下一个字符
	}	
}

void delayms(unsigned char ms)	
// 延时子程序
{						
	unsigned char i;
	while(ms--)
	{
		for(i = 0; i < 120; i++);
	}
}
