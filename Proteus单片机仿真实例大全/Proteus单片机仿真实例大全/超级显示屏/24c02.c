#include"REG51F.h"
#include"intrins.h"
#include"USEH1.h"
#include"24c02.h"

//��д��������
//const uchar WR24C02   =   0xA0;       //EEPROM��ַ+д����
//const uchar RD24C02   =   0xA1;       //EEPROM��ַ+������
#define WR24C02		0xA0
#define RD24C02		0xA1
//�û���������
bit ErrorBit;                             //��д�����־       1����     0   ��ȷ
uchar ErrorCode;           	  	  //������

void Start(void);
void Stop(void);
void Ack(void);
void NoAck(void);
void TestAck(void);
void WriteI2c(uchar date);
uchar ReadI2c(void);
//void DelayMs(uchar time);


/***************************************
*��������:       void   Start(void)
*��������:       ��д��ʼ
*����:               ��
*���:               ��
*ȫ�ֱ���:       I2C_SCL��I2C_SDA
*����ģ��:       ��

****************************************/
void Start(void)
{
   I2C_SDA = 1;           //��ʼ�����������ź�
   _nop_();
   I2C_SCL = 1;           //��ʼ����ʱ���ź�
   _nop_();                   //�źŽ���ʱ��>4.7us
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   I2C_SDA = 0;           //��ʼ�ź�
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   I2C_SCL = 0;           //ǯסI2C����,   ׼�����ͻ��߽�������
   _nop_();
   _nop_();
}
/***************************************
*��������:       void   Stop(void)
*��������:       ��д����
*����:               ��
*���:               ��
*ȫ�ֱ���:       I2C_SCL��I2C_SDA
*����ģ��:       ��

****************************************/
void Stop(void)
{
   I2C_SDA = 0;             //���������������ź�
   _nop_();
   I2C_SCL = 1;             //����������ʱ���ź�
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   I2C_SDA = 1;             //�����ź�
   _nop_();
   _nop_();
   _nop_();
   _nop_();
}
/***************************************
*��������:       void   Ack(void)
*��������:       ��ȷӦ��,��һ���ֽں����Ӧ��
*����:               ��
*���:               ��
*ȫ�ֱ���:       I2C_SCL��I2C_SDA
*����ģ��:       ��

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
*��������:       void   NoAck(void)
*��������:       ��Ӧ��
*����:               ��
*���:               ��
*ȫ�ֱ���:       I2C_SCL��I2C_SDA
*����ģ��:       ��

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
*��������:       void   TestAck(void)
*��������:       ��д�������,дһ���ֽ�Ӧ�ò���Ӧ���ź�
*����:               ��
*���:               ����һ��λ
*ȫ�ֱ���:       I2C_SCL��I2C_SDA
*����ģ��:       ��

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
*��������:       void   WriteI2c(uchar   date)
*��������:       дI2C
*����:               ��������,���ֽ�����
*���:               ��
*ȫ�ֱ���:       I2C_SCL��I2C_SDA
*����ģ��:       ��

****************************************/
void WriteI2c(uchar date)
{
   uchar i;
   for(i=0; i<8; i++)
   {
      I2C_SDA = date & 0x80;                 //�����ݵ���������
      date <<= 1;
      _nop_();
      I2C_SCL = 1;                                     //��ʱ���ź�Ϊ�ߵ�ƽ,ʹ������Ч
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
*��������:       uchar   ReadI2c(void)
*��������:       ��I2C
*����:               ��
*���:               ����һ���ֽڵ�����,���ֽ���ǰ
*ȫ�ֱ���:       I2C_SCL��I2C_SDA
*����ģ��:       ��

****************************************/
uchar ReadI2c(void)
{
   uchar i;
   uchar byte = 0;
   for(i=0; i<8; i++)
   {
      I2C_SCL = 0;                       //��ʱ��Ϊ�͵�ƽ,׼����������
      _nop_();
      _nop_();
      _nop_();
      _nop_();
      _nop_();
      I2C_SCL = 1;                     //��ʱ��Ϊ�ߵ�ƽ,ʹ������������Ч
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
*��������:       void   DelayMs(uchar   time)
*��������:       ��ʱ
*����:               ��ʱʱ��
*���:               ��
*ȫ�ֱ���:       ��
*����ģ��:       ��

****************************************/
/*void DelayMs(uchar time)
{
   uchar i;
   do
   {
      for(i=0; i<125; i++);       //*��ʱ   8us   x   125   =   1ms
   }
   while(time--);
}*/
/***************************************
*��������:       void     WriteDate(uchar   StartAddress,uchar   *date,uchar   bytes)
*��������:       д����
*����:               ���ݿ�ʼ��ַ,��������ָ��,�����ֽ���
*���:               ��
*ȫ�ֱ���:       ��
*����ģ��:       Start(),WriteI2c(),Stop(),TestAck()
*ע������:       ����֮ǰ,��Ҫ����һ������,����������͵�����
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
*��������:       void     ReadDate(uchar   StartAddress,uchar   *date,uchar   bytes)
*��������:       ������
*����:               ���ݿ�ʼ��ַ,��ȡ����ָ��,�����ֽ���
*���:               ��
*ȫ�ֱ���:       ��
*����ģ��:       Start(),WriteI2c(),ReadI2c(),Ack(),NoAck(),Stop(),TestAck()
*ע������:       ����֮ǰ,��Ҫ����һ������,�������ȡ������
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
