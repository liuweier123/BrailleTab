/*---------------------------------------------------------------------
                         LCD1602.H�ļ� LCD1602��һЩ�����
  ���ߣ�Computer-lov     ��������:2004.11.12    ����޸�����:2004.11.22
  �汾��1.0
----------------------------------------------------------------------*/

#ifndef __LCD_H__
#define __LCD_H__

#define LCD_GO_HOME               0x02         //AC=0����ꡢ�����HOMEλ

//���뷽ʽ����
#define LCD_AC_AUTO_INCREMENT     0x06         //���ݶ���д������AC�Զ���һ
#define LCD_AC_AUTO_DECREASE      0x04         //���ݶ���д������AC�Զ���һ
#define LCD_MOVE_ENABLE           0x05         //���ݶ���д����������ƽ��
#define LCD_MOVE_DISENABLE        0x04         //���ݶ���д���������治��

//������ʾ����꼰��˸������
#define LCD_DISPLAY_ON            0x0C         //��ʾ��
#define LCD_DISPLAY_OFF           0x08         //��ʾ��
#define LCD_CURSOR_ON             0x0A         //�����ʾ
#define LCD_CURSOR_OFF            0x08         //��겻��ʾ
#define LCD_CURSOR_BLINK_ON       0x09         //�����˸
#define LCD_CURSOR_BLINK_OFF      0x08         //��겻��˸

//��ꡢ�����ƶ�����Ӱ��DDRAM
#define LCD_LEFT_MOVE             0x18         //LCD��ʾ����һλ
#define LCD_RIGHT_MOVE            0x1C         //LCD��ʾ����һλ
#define LCD_CURSOR_LEFT_MOVE      0x10         //�������һλ
#define LCD_CURSOR_RIGHT_MOVE     0x14         //�������һλ

//������ʽ����
#define LCD_DISPLAY_DOUBLE_LINE   0x38         //������ʾ
#define LCD_DISPLAY_SINGLE_LINE   0x30         //������ʾ
void LCD_cls(void);
void LCD_write_data(unsigned char);
void LCD_initial(void);
void LCD_set_position(unsigned char);
void LCD_prints(unsigned char *);
void LCD_printc(unsigned char); 

#endif
