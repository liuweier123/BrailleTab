#include"REG51F.h"
#include"intrins.h"
#include"USEH1.h"
#include"24c02.h"

//读写控制命令
//const uchar WR24C02   =   0xA0;       //EEPROM地址+写命令
//const uchar RD24C02   =   0xA1;       //EEPROM地址+读命令
#define WR24C02		0xA0
#define RD24C02		0xA1
//用户变量声明
bit ErrorBit;                             //读写错误标志       1错误     0   正确
uchar ErrorCode;           	  	  //错误码

void Start(void);
void Stop(void);
void Ack(void);
void NoAck(void);
void TestAck(void);
void WriteI2c(uchar date);
uchar ReadI2c(void);
//void DelayMs(uchar time);


/***************************************
*函数名称:       void   Start(void)
*功能描述:       读写开始
*输入:               无
*输出:               无
*全局变量:       I2C_SCL，I2C_SDA
*调用模块:       无

****************************************/
void Start(void)
{
   I2C_SDA = 1;           //起始条件的数据信号
   _nop_();
   I2C_SCL = 1;           //起始条件时钟信号
   _nop_();                   //信号建立时间>4.7us
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   I2C_SDA = 0;           //起始信号
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   I2C_SCL = 0;           //钳住I2C总线,   准备发送或者接受数据
   _nop_();
   _nop_();
}
/***************************************
*函数名称:       void   Stop(void)
*功能描述:       读写结束
*输入:               无
*输出:               无
*全局变量:       I2C_SCL，I2C_SDA
*调用模块:       无

****************************************/
void Stop(void)
{
   I2C_SDA = 0;             //结束条件的数据信号
   _nop_();
   I2C_SCL = 1;             //结束条件的时钟信号
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   I2C_SDA = 1;             //结束信号
   _nop_();
   _nop_();
   _nop_();
   _nop_();
}
/***************************************
*函数名称:       void   Ack(void)
*功能描述:       正确应答,读一个字节后必须应答
*输入:               无
*输出:               无
*全局变量:       I2C_SCL，I2C_SDA
*调用模块:       无

****************************************/
void Ack(void)
{
   I2C_SDA = 0;
   _nop_();
   _nop_();
   I2C_SCL = 1;
   _nop_();
   _nop_();
   _nop_();
   //_nop_();
   //_nop_();
   I2C_SCL = 0;
   _nop_();
   _nop_();
   I2C_SDA = 1;
   _nop_();
   _nop_();
}
/***************************************
*函数名称:       void   NoAck(void)
*功能描述:       无应答
*输入:               无
*输出:               无
*全局变量:       I2C_SCL，I2C_SDA
*调用模块:       无

****************************************/
void NoAck(void)
{
   I2C_SDA = 1;
   _nop_();
   _nop_();
   I2C_SCL = 1;
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   I2C_SCL = 0;
   _nop_();
   _nop_();
}
/***************************************
*函数名称:       void   TestAck(void)
*功能描述:       读写错误测试,写一个字节应该测试应答信号
*输入:               无
*输出:               返回一个位
*全局变量:       I2C_SCL，I2C_SDA
*调用模块:       无

****************************************/
void TestAck(void)
{
   I2C_SDA = 1;
   _nop_();
   _nop_();
   I2C_SCL = 1;
   _nop_();
   _nop_();
   _nop_();
   ErrorBit = I2C_SDA;
   I2C_SCL = 0;
   _nop_();
   _nop_();
}
/***************************************
*函数名称:       void   WriteI2c(uchar   date)
*功能描述:       写I2C
*输入:               待送数据,高字节先送
*输出:               无
*全局变量:       I2C_SCL，I2C_SDA
*调用模块:       无

****************************************/
void WriteI2c(uchar date)
{
   uchar i;
   for(i=0; i<8; i++)
   {
      I2C_SDA = date & 0x80;                 //送数据到数据线上
      date <<= 1;
      _nop_();
      I2C_SCL = 1;                                     //置时钟信号为高电平,使数据有效
      _nop_();
      _nop_();
      _nop_();
      _nop_();
      _nop_();
      I2C_SCL = 0;
      _nop_();
      _nop_();
   }
}
/***************************************
*函数名称:       uchar   ReadI2c(void)
*功能描述:       读I2C
*输入:               无
*输出:               返回一个字节的数据,高字节在前
*全局变量:       I2C_SCL，I2C_SDA
*调用模块:       无

****************************************/
uchar ReadI2c(void)
{
   uchar i;
   uchar byte = 0;
   for(i=0; i<8; i++)
   {
      I2C_SCL = 0;                       //置时钟为低电平,准备接受数据
      _nop_();
      _nop_();
      _nop_();
      _nop_();
      _nop_();
      I2C_SCL = 1;                     //置时钟为高电平,使数据线数据有效
      _nop_();
      _nop_();
      byte <<= 1;
      byte |= I2C_SDA;
      _nop_();
      _nop_();
      I2C_SCL = 0;
   }
   return(byte);
}
/***************************************
*函数名称:       void   DelayMs(uchar   time)
*功能描述:       延时
*输入:               延时时间
*输出:               无
*全局变量:       无
*调用模块:       无

****************************************/
/*void DelayMs(uchar time)
{
   uchar i;
   do
   {
      for(i=0; i<125; i++);       //*延时   8us   x   125   =   1ms
   }
   while(time--);
}*/
/***************************************
*函数名称:       void     WriteDate(uchar   StartAddress,uchar   *date,uchar   bytes)
*功能描述:       写数据
*输入:               数据开始地址,保存数据指针,数据字节数
*输出:               无
*全局变量:       无
*调用模块:       Start(),WriteI2c(),Stop(),TestAck()
*注意事项:       调用之前,需要定义一个数组,用来存待发送的数据
****************************************/
void WriteDate(uchar StartAddress,  uchar *date,  uchar bytes)
{
   uchar i = 0;
   Start();
   WriteI2c(WR24C02);
   TestAck();
   WriteI2c(StartAddress);
   TestAck();
   for(i=0; i<bytes; i++)
   {
      WriteI2c(*date);
      TestAck();
      date++;
   }
   Stop();
   //DelayMs(20);
}
/***************************************
*函数名称:       void     ReadDate(uchar   StartAddress,uchar   *date,uchar   bytes)
*功能描述:       读数据
*输入:               数据开始地址,读取数据指针,数据字节数
*输出:               无
*全局变量:       无
*调用模块:       Start(),WriteI2c(),ReadI2c(),Ack(),NoAck(),Stop(),TestAck()
*注意事项:       调用之前,需要定义一个数组,用来存读取的数据
****************************************/
void   ReadDate(uchar StartAddress,  uchar *date,  uchar bytes)
{
   uchar i;
   Start();
   WriteI2c(WR24C02);
   TestAck();
   WriteI2c(StartAddress);
   TestAck();
   Start();
   WriteI2c(RD24C02);
   TestAck();
   for   (i=0; i<bytes; i++)
   {
      *date = ReadI2c();
      Ack();
      date++;
   }
   NoAck();
   Stop();
   //DelayMs(10);
}
