#ifndef _t6963c_h //��ֹ��ͬһģ���ΰ���
  #define _t6963c_h 

#include "typedef.h"  


void hanzhi(uchar row,uchar col, uchar m,uchar n);		 //д�뺺��
void Init_LCD_Graphic(void);			   //t6963c��ʼ��
void ClrGraphic(void);		 //����ʾRAM
void Point(uchar x,uchar y, bit Mode);	   //���㺯��
void Wr_line(uchar type,uchar x1,uchar y1, uchar Long,uchar mode);	   // ��һ�����߻�����
void image(uchar x1,uchar y1,uchar x2,uchar y2,uchar *p,bit mode);	// ���趨����������д�����ֽڣ���ͼ����ʾ��
void negShow(uchar x1,uchar y1,uchar x2,uchar y2,bit mode) ; //= ��    ��: ��������x1,y1) (x2,y2)
void Show_num(uchar x1,uchar y1,uchar num);	 //���趨λ��д��һ������
void Show_Image(uchar x1,uchar y1,uchar x2,uchar y2,bit mode); //��ʾһ�������ɾ��һ������
void Init_LCD();
void char_wr(uchar row,uchar col, uchar *p,uchar dataa,uchar n);   //д���ַ�

#endif
