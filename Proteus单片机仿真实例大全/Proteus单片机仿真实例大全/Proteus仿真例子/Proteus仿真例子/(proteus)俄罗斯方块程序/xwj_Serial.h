//---------------- xwj_Serial.c //---------------�������
//���ں�����,�������򵥵��ü�����ɴ�����������Ĵ���,��������л���������С����������
void serial_init ();
unsigned char getbyte(void);				//�ӽ��ջ�����ȡһ��byte,�粻��ȴ����ڵ���ǰ���inbufsign�Ƿ�Ϊ1��
bit  checkin(void); 						//�����ջ������Ƿ�������
void putchar(unsigned char c);						//����һ���ֽڵ����ͻ�����
//void getline(unsigned char idata *line, unsigned char n); //��ȡһ�����ݻس����������붨����������ַ���
//void putbytes(unsigned char *outplace,unsigned char j);	//��һ�����ݵ����ͻ��������Զ��峤��
//void putstring(unsigned char code *puts);	//����һ�������ڳ���洢�����ַ���������
//void puthex(unsigned char c);				//����һ���ֽڵ�hex�룬�ֳ������ֽڷ���
//void putbyte(unsigned char c,unsigned char j);	//���һ���޷����ַ�����ʮ���Ʊ�ʾ�������ʾС�����λ��,�Զ�ɾ��ǰ�����õ���
//void putint(unsigned int ui,unsigned char j);	//���һ���޷�����������ʮ���Ʊ�ʾ�������ʾС�����λ��,�Զ�ɾ��ǰ�����õ���
//void clr(void);								// ����һ '�����Ļ' ��VT100�ն�
void putinbuf(unsigned char c);				//�˹�����һ���ַ������뻺����
void Serial_main(void);		//	���ڲ�����������  

