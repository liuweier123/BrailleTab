#if !defined(HD44780_H)
#define HD44780_H
 #define dataport        PORTB  //�������ݼĴ����˿�
 #define dirport_data    DDRB   //���巽��Ĵ����˿�
 #define conport 	 PORTA
 #define dirport_con	 DDRA
 
 
 #define LCD_E  (1 << 6)     //���Ŷ���
 #define LCD_RS (1 << 4)
 #define LCD_RW (1 << 5)
 
 #define lcd_set_e()  (conport |= LCD_E)   //��λ������
 #define lcd_set_rs() (conport |= LCD_RS)
 #define lcd_set_rw() (conport |= LCD_RW)
 #define lcd_clear_e()  (conport &= ~LCD_E)
 #define lcd_clear_rs() (conport &= ~LCD_RS)
 #define lcd_clear_rw() (conport &= ~LCD_RW)
/*********************************************************/
 #if defined HD44780_C
 void lcd_pulse(void); 					//����LCD����Ķ�����
 void lcd_wait(void);							//�ȴ�
 void lcd_send(unsigned char data);				//��LCDдһ���ֽ�����
 void clrscr(void); 		 					//��������
 void gotoz(unsigned char z);					//��λ����
 void gotoxy(unsigned char x,unsigned char y);	//��λ�ַ�λ��
 void put_char(char c);	   			  	   		//��LCDд�ַ�
 void outtext(char* text);						//��LCDд�ַ���
 void initgraph(void);							//��ʼ��LCD
 #else
 extern  void lcd_pulse(void); 					//����LCD����Ķ�����
 extern  void lcd_wait(void);							//�ȴ�
 extern  void lcd_send(unsigned char data);				//��LCDдһ���ֽ�����
 extern  void clrscr(void); 		 					//��������
 extern  void gotoz(unsigned char z);					//��λ����
 extern  void gotoxy(unsigned char x,unsigned char y);	//��λ�ַ�λ��
 extern  void put_char(char c);	   			  	   		//��LCDд�ַ�
 extern  void outtext(unsigned char* text);						//��LCDд�ַ���
 extern  void initgraph(void);		
 #endif
#endif
/**********************************************/     
