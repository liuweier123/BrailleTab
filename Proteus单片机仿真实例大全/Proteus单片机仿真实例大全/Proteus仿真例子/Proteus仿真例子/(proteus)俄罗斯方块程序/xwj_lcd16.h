 				// �ַ�Һ�����ƺ�������    //
//--------------------------------------------------------------------------//
void Lcd16InitCg(void); 			//��ʼ���Զ����ַ�          //
void Lcd16WriteCg(unsigned char x, unsigned char y, unsigned char n); 	//��ʾ�Զ����ַ�          //
void Lcd16WrDatah(unsigned char d); //1λ16��������д�뺯��     //
void Lcd16WrDatahh(unsigned char d); //2λ16��������д�뺯��		//
void Lcd16Pos(unsigned char xpos, unsigned char ypos); 	// ���㲢д���ַ����������λ�ã��ڼ���  //
void Lcd16WrChar(unsigned char x, unsigned char y, unsigned char c); 	// ����ַдһ���ַ�����������λ�ã��������ַ� //
void Lcd16WrCharn(unsigned char x, unsigned char y, unsigned char c); // ����ַдһλʮ���������֣���������λ�ã����������� //
void Lcd16WrCharhh(unsigned char x, unsigned char y, unsigned char c); // ����ַд��λʮ���������֣���������λ�ã����������� //
void Lcd16Fill(unsigned char cf); 	// ����д cf ���ַ� //
void Lcd16Display(unsigned char sx, unsigned char sy, unsigned char  *sc); 	//����ַдһ���ַ�������������λ�ã��������ַ���//
void Lcd16Reset(void); 		 		//Lcd16��λ                 //
void Lcd16Delay(unsigned int x);	//��ʱ x ����               //
void Lcd16main(void);						//Lcd16��ʱ����������
//--------------------------------------------------------------------------//
