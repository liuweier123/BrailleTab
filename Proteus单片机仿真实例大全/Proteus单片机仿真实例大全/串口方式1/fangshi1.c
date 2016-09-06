//初始化串行口
void csh(char a)
	{
	SM0=0;
	SM1=1;
	REN=1;
	TI=0;
	RI=0;
	SMOD=0;
	TH1=0xF3;
	TL1=0XF3;
	TMOD=0X20;
	EA=1;
	ET1=0;
	ES=1;
	TR1=1;
	}

