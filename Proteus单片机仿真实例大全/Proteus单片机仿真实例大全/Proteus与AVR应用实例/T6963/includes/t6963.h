#ifndef T6963_H
#define T6963_H


#ifdef T6963_C
// ASCII �ַ����ƴ�����Ͷ���
#define STX 0x02
#define ETX 0x03
#define EOT 0x04
#define ENQ 0x05
#define BS 0x08
#define CR 0x0D
#define LF 0x0A
#define DLE 0x10
#define ETB 0x17
#define SPACE 0x20
#define COMMA 0x2C
#define TRUE 1
#define FALSE 0
#define HIGH 1
#define LOW 0
 
#define LCD_OUT    PORTB
#define LCD_IN     PINB
#define dir_datap  DDRB

#define dir_conp   DDRA
#define port_conp  PORTA

#define LCM 2  //���ݼĴ��������ƼĴ���ѡ��
#define RD 1
#define WR 0

// T6963C �����
#define LC_CUR_POS 0x21 // ���λ������
#define LC_CGR_POS 0x22 // CGRAM ƫ�õ�ַ����
#define LC_ADD_POS 0x24 // ��ַָ��λ��
#define LC_TXT_STP 0x40 // �ı�����ַ
#define LC_TXT_WID 0x41 // �ı������
#define LC_GRH_STP 0x42 // ͼ������ַ
#define LC_GRH_WID 0x43 // ͼ�������
#define LC_MOD_OR 0x80 // ��ʾ��ʽ�߼���
#define LC_MOD_XOR 0x81 // ��ʾ��ʽ�߼����
#define LC_MOD_AND 0x82 // ��ʾ��ʽ�߼���
#define LC_MOD_TCH 0x83 // ��ʾ��ʽ�ı�����
#define LC_DIS_SW 0x90 // ��ʾ����D0=1/0:�����˸����/����
// D1=1/0:�����ʾ����/����
// D2=1/0:�ı���ʾ����/����
// D3=1/0:ͼ����ʾ����/����
#define LC_CUR_SHP 0xA0 // �����״ѡ��0xA0-0xA7��ʾ���ռ������
#define LC_AUT_WR 0xB0 // �Զ�д����
#define LC_AUT_RD 0xB1 // �Զ�������
#define LC_AUT_OVR 0xB2 // �Զ���/д����
#define LC_INC_WR 0xC0 // ����һ��д��ַ��1
#define LC_INC_RD 0xC1 // ����һ�ζ���ַ��1
#define LC_DEC_WR 0xC2 // ����һ��д��ַ��1
#define LC_DEC_RD 0xC3 // ����һ�ζ���ַ��1
#define LC_NOC_WR 0xC4 // ����һ��д��ַ����
#define LC_NOC_RD 0xC5 // ����һ�ζ���ַ����
#define LC_SCN_RD 0xE0 // ����
#define LC_SCN_CP 0xE8 // ������
#define LC_BIT_OP 0xF0 // λ����

#define NOP() asm("nop")
// D0-D2 ����D0-D7 λD3 1��λ0 ���
__flash  unsigned char uPowArr[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
// ASCII ��ģ��ȼ��߶ȶ���
#define ASC_CHR_WIDTH 8
#define ASC_CHR_HEIGHT 16
// ASCII ��ģ��ʾΪ8*16
__flash unsigned char  turnf[8] = {7,6,5,4,3,2,1,0};
unsigned char gCurRow,gCurCol; // ��ǰ���д洢�и�16 ���п�8��

/**************************************************************


typedef struct         // ������ģ���ݽṹ
	{
  	char Index[2];
  	char Msk[32];
	}typFNT_GB16;

**************************************************************/

/* ȡ��ǰ������*/
unsigned char fnGetRow(void);
/* ȡ��ǰ������*/
unsigned char fnGetCol(void);
/* ��״̬*/
unsigned char RD_LCM(void);
/* ������*/
unsigned char RD_DAT(void);
/* д����*/
void WR_DAT(unsigned char val);
/* д����*/
void WR_CMD(unsigned char val);
/************************************************/
/* ״̬λSTA1,STA0�ж϶�дָ��Ͷ�д����*/
/* �ڶ�д���ݻ���д������ǰ���뱣֤��Ϊ1 */
/************************************************/
unsigned char fnSTA01(void);
/********************************************/
/* ���STA2,���STA2=1 Ϊ�Զ���״̬*/
/********************************************/
unsigned char fnSTA2(void);
/***********************************************/
/* ״̬λSTA3 �ж�STA3 = 1 �����Զ�д״̬*/
/***********************************************/
unsigned char fnSTA3(void);
/************************************************/
/* ״̬λSTA6 �ж�STA6 =1 ����/������״̬*/
/************************************************/
unsigned char fnSTA6(void);
/************************/
/* д˫������ָ��*/
/************************/
unsigned char fnPR1(unsigned char uCmd,unsigned char uPar1,unsigned char uPar2);
/************************/
/* д��������ָ��*/
/************************/
unsigned char fnPR11(unsigned char uCmd,unsigned char uPar1);
/************************/
/* д�޲�����ָ��*/
/************************/
unsigned char fnPR12(unsigned char uCmd);
/************************/
/* д����*/
/************************/
unsigned char fnPR13(unsigned char uData);
/************************/
/* ������*/
/************************/
unsigned char fnPR2(void);
/************************/
/* ���õ�ǰ��ַ*/
/************************/
void fnSetPos(unsigned char urow, unsigned char ucol);
/**********************/
/* ���õ�ǰ��ʾ����*/
/**********************/
void cursor(unsigned char uRow, unsigned char uCol);
/*********************/
/* ����*/
/*********************/
void cls(void);
/************************/
/* LCM ��ʼ��*/
/************************/
char fnLCMInit(void);
/********************************************************/
/* ASCII(8*16) �� ����(16*16) ��ʾ����      */
/********************************************************/
unsigned char dprintf(unsigned char x,unsigned char y, char *ptr);
/*======================*/
/* ��ʱ*/
/*======================*/
void shortdelay(unsigned int tt);
/*************************/
/* ����*/
/*************************/
void point(unsigned char x,unsigned char y,unsigned char s);
/************************************************/
/* �������ⷽ���б��,ֱ����ѧ����aX+bY=1 */
/************************************************/
void Linexy(unsigned char x0,unsigned char y0,unsigned char xt,unsigned char yt,unsigned char s);
/********************************************/
/* ��Բ��ѧ����(X-Ox)^2+(Y-Oy)^2=Rx^2 */
/********************************************/
void circle(unsigned char Ox,unsigned char Oy,unsigned char Rx,unsigned char s);

#else

/* ȡ��ǰ������*/
extern unsigned char fnGetRow(void);
/* ȡ��ǰ������*/
extern unsigned char fnGetCol(void);
/* ��״̬*/
extern unsigned char RD_LCM(void);
/* ������*/
extern unsigned char RD_DAT(void);
/* д����*/
extern void WR_DAT(unsigned char val);
/* д����*/
extern void WR_CMD(unsigned char val);
/************************************************/
/* ״̬λSTA1,STA0�ж϶�дָ��Ͷ�д����*/
/* �ڶ�д���ݻ���д������ǰ���뱣֤��Ϊ1 */
/************************************************/
extern unsigned char fnSTA01(void);
/********************************************/
/* ���STA2,���STA2=1 Ϊ�Զ���״̬*/
/********************************************/
extern unsigned char fnSTA2(void);
/***********************************************/
/* ״̬λSTA3 �ж�STA3 = 1 �����Զ�д״̬*/
/***********************************************/
extern unsigned char fnSTA3(void);
/************************************************/
/* ״̬λSTA6 �ж�STA6 =1 ����/������״̬*/
/************************************************/
extern unsigned char fnSTA6(void);
/************************/
/* д˫������ָ��*/
/************************/
extern unsigned char fnPR1(unsigned char uCmd,unsigned char uPar1,unsigned char uPar2);
/************************/
/* д��������ָ��*/
/************************/
extern unsigned char fnPR11(unsigned char uCmd,unsigned char uPar1);
/************************/
/* д�޲�����ָ��*/
/************************/
extern unsigned char fnPR12(unsigned char uCmd);
/************************/
/* д����*/
/************************/
extern unsigned char fnPR13(unsigned char uData);
/************************/
/* ������*/
/************************/
extern unsigned char fnPR2(void);
/************************/
/* ���õ�ǰ��ַ*/
/************************/
extern void fnSetPos(unsigned char urow, unsigned char ucol);
/**********************/
/* ���õ�ǰ��ʾ����*/
/**********************/
extern void cursor(unsigned char uRow, unsigned char uCol);
/*********************/
/* ����*/
/*********************/
extern void cls(void);
/************************/
/* LCM ��ʼ��*/
/************************/
extern char fnLCMInit(void);
/********************************************************/
/* ASCII(8*16) �� ����(16*16) ��ʾ����      */
/********************************************************/
extern unsigned char dprintf(unsigned char x,unsigned char y, char *ptr);
/*======================*/
/* ��ʱ*/
/*======================*/
extern void shortdelay(unsigned int tt);
/*************************/
/* ����*/
/*************************/
extern void point(unsigned char x,unsigned char y,unsigned char s);
/************************************************/
/* �������ⷽ���б��,ֱ����ѧ����aX+bY=1 */
/************************************************/
extern void Linexy(unsigned char x0,unsigned char y0,unsigned char xt,unsigned char yt,unsigned char s);
/********************************************/
/* ��Բ��ѧ����(X-Ox)^2+(Y-Oy)^2=Rx^2 */
/********************************************/
extern void circle(unsigned char Ox,unsigned char Oy,unsigned char Rx,unsigned char s);
#endif
#endif