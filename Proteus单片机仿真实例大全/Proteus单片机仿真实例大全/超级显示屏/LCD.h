#ifndef __LCD_H__
#define __LCD_H__

// LCD128*64 ������
#define LCD_P		P1
// LCD128*64 I/O �źŹܽ�
sbit DI = P2^0; // ����\ָ�� ѡ��
sbit RW = P2^2; // ��\д ѡ��
sbit EN = P2^1; // ��\дʹ��
sbit CS1= P2^3; // Ƭѡ1,����Ч(ǰ64��)
sbit CS2= P2^4; // Ƭѡ2,����Ч(��64��)

//��������================================
//�趨�е�ַ(ҳ)--X 0-7
void SetLine(uchar line);
//�趨�е�ַ--Y 0-63
void SetColumn(uchar column);
//�趨��ʾ��ʼ��--XX
void SetStartLine(uchar startline); //0--63
//������ʾ
void SetOnOff(uchar onoff);
//ѡ����Ļ
//screen: 0-ȫ��,1-����,2-����
void SelectScreen(uchar screen);
//����
//screen: 0-ȫ��,1-����,2-��
void ClearScreen(uchar screen);
//��ʾ8*8����
//lin:��(0-7), column: ��(0-127)
//address : ��ģ���׵�ַ
void Show8x8(uchar lin,uchar column,uchar *address);
/*//��ʾ����8*16
void ShowNumber(uchar lin,uchar column,uchar num);*/
//��ʾ����16*16
void ShowChina(uchar lin,uchar column,uchar num);
void InitLCD(void); //��ʼ��LCD
/*void r_show8x8(uchar lin,uchar column,uchar *address);
void r_ShowNumber(uchar lin,uchar column,uchar num);*/
//��ʾͼƬ
//lin:��(0-7), column: ��(0-127)
//high:�߶�, width:���(ҪΪ8�ı���)
//address : ͼƬ���׵�ַ
void ShowPicture(uchar lin, uchar column, uchar high, uchar width, uchar *address);
#endif