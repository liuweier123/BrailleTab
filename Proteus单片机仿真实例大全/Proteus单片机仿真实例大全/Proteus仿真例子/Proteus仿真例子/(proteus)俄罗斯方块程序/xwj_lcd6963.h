#define ulong		unsigned long
#define uint		unsigned int
#define uchar		unsigned char
			// T6963C ���ú���
void Lcd6963Cursor(unsigned char uCol,unsigned char uRow);// ���õ�ǰ��ʾ�С���
void Lcd6963ChHz(bit);					// �л�16�����12������ʾ��ʽ
char Lcd6963Init(void);					// Lcd6963 ��ʼ��
void Lcd6963Cls(void);						// ����
void print(char *uStr);			// ASCII(8*16)  ����(16*16) �� ����(12*12) ��ʾ����
void printat(uchar uCol,uchar uRow,char *uStr);	// ASCII(8*16)  ����(16*16) �� ����(12*12) ��ʾ����
//unsigned char dprintf(char *fmt, ...);	// ��ʽ�� ��ʾ����
void Lcd6963Line(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2);	//������:y=0~63:����|��y=64~127:���&��y=128~191:д�ֽ�W��y=192~255:ȡ��^��
void Lcd6963Rec(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2);	//���㻭һ�����ο�
void Lcd6963Fillrec(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2);//�������һ������
//void Lcd6963Frec(unsigned char x,unsigned char y,unsigned char lx,unsigned char ly);	//�������һ������
//void Lcd6963Wstr(unsigned char x,unsigned char y,unsigned char *str);			// 12��12������Ӣ�Ļ����ʾ����
void Lcd6963CIrcle(unsigned char x,unsigned char y,unsigned char r);			//�е㷨��Բ
//void Lcd6963Cleanx(unsigned char x);							//���1�� ����Lcd6963Cleanx()����
//--------------------------------------------------------------------------//
//void show_v(void);									//��ʾ����(ʾ��)
void Lcd6963main(void);						// Lcd6963������
//--------------------------------------------------------------------------//
