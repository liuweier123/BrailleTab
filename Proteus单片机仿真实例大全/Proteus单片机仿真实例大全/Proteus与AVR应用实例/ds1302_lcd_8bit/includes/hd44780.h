#if !defined(HD44780_H)
#define HD44780_H
 #define dataport        PORTB  //定义数据寄存器端口
 #define dirport_data    DDRB   //定义方向寄存器端口
 #define conport 	 PORTA
 #define dirport_con	 DDRA
 
 
 #define LCD_E  (1 << 6)     //引脚定义
 #define LCD_RS (1 << 4)
 #define LCD_RW (1 << 5)
 
 #define lcd_set_e()  (conport |= LCD_E)   //置位与清零
 #define lcd_set_rs() (conport |= LCD_RS)
 #define lcd_set_rw() (conport |= LCD_RW)
 #define lcd_clear_e()  (conport &= ~LCD_E)
 #define lcd_clear_rs() (conport &= ~LCD_RS)
 #define lcd_clear_rw() (conport &= ~LCD_RW)
/*********************************************************/
 #if defined HD44780_C
 void lcd_pulse(void); 					//产生LCD所需的短脉冲
 void lcd_wait(void);							//等待
 void lcd_send(unsigned char data);				//向LCD写一个字节数据
 void clrscr(void); 		 					//清屏函数
 void gotoz(unsigned char z);					//定位坐标
 void gotoxy(unsigned char x,unsigned char y);	//定位字符位置
 void put_char(char c);	   			  	   		//向LCD写字符
 void outtext(char* text);						//向LCD写字符串
 void initgraph(void);							//初始化LCD
 #else
 extern  void lcd_pulse(void); 					//产生LCD所需的短脉冲
 extern  void lcd_wait(void);							//等待
 extern  void lcd_send(unsigned char data);				//向LCD写一个字节数据
 extern  void clrscr(void); 		 					//清屏函数
 extern  void gotoz(unsigned char z);					//定位坐标
 extern  void gotoxy(unsigned char x,unsigned char y);	//定位字符位置
 extern  void put_char(char c);	   			  	   		//向LCD写字符
 extern  void outtext(unsigned char* text);						//向LCD写字符串
 extern  void initgraph(void);		
 #endif
#endif
/**********************************************/     
