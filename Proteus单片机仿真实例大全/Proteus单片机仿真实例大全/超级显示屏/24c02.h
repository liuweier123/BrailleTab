#ifndef __24c04_H__
#define __24c04_H__

sbit I2C_SCL = P0^2;
sbit I2C_SDA = P0^3;
//StartAddress:数据开始地址,date:保存数据指针,bytes:数据字节数
void WriteDate(uchar StartAddress,  uchar *date,  uchar bytes);
//StartAddress:数据开始地址,date:读取数据指针,bytes:数据字节数
void ReadDate(uchar StartAddress,  uchar *date,  uchar bytes);
#endif