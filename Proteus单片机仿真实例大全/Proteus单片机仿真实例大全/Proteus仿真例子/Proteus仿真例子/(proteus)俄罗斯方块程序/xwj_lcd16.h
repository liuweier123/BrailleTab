 				// 字符液晶控制函数声明    //
//--------------------------------------------------------------------------//
void Lcd16InitCg(void); 			//初始化自定义字符          //
void Lcd16WriteCg(unsigned char x, unsigned char y, unsigned char n); 	//显示自定义字符          //
void Lcd16WrDatah(unsigned char d); //1位16进制数字写入函数     //
void Lcd16WrDatahh(unsigned char d); //2位16进制数字写入函数		//
void Lcd16Pos(unsigned char xpos, unsigned char ypos); 	// 计算并写入地址，参数：列位置，第几行  //
void Lcd16WrChar(unsigned char x, unsigned char y, unsigned char c); 	// 带地址写一个字符，参数：列位置，行数，字符 //
void Lcd16WrCharn(unsigned char x, unsigned char y, unsigned char c); // 带地址写一位十六进制数字，参数：列位置，行数，数字 //
void Lcd16WrCharhh(unsigned char x, unsigned char y, unsigned char c); // 带地址写二位十六进制数字，参数：列位置，行数，数字 //
void Lcd16Fill(unsigned char cf); 	// 整屏写 cf 中字符 //
void Lcd16Display(unsigned char sx, unsigned char sy, unsigned char  *sc); 	//带地址写一个字符串，参数：列位置，行数，字符串//
void Lcd16Reset(void); 		 		//Lcd16复位                 //
void Lcd16Delay(unsigned int x);	//延时 x 毫秒               //
void Lcd16main(void);						//Lcd16临时测试主程序
//--------------------------------------------------------------------------//
