#ifndef __24c04_H__
#define __24c04_H__

sbit I2C_SCL = P0^2;
sbit I2C_SDA = P0^3;
//StartAddress:���ݿ�ʼ��ַ,date:��������ָ��,bytes:�����ֽ���
void WriteDate(uchar StartAddress,  uchar *date,  uchar bytes);
//StartAddress:���ݿ�ʼ��ַ,date:��ȡ����ָ��,bytes:�����ֽ���
void ReadDate(uchar StartAddress,  uchar *date,  uchar bytes);
#endif