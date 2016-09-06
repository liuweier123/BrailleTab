#define uchar unsigned char
#define LCD_CHAR 0x14

sbit cd = P3^0;		/*ͨ��ѡ��*/
sbit rd = P3^1;		/*�������ź�*/
sbit wr = P3^2;		/*д�����ź�*/
sbit error0 = P1^5;  /*������ʾ1*/
sbit error1 = P1^6;  /*������ʾ2*/
sbit error2 = P1^7;  /*������ʾ3*/

/*��״̬*/
uchar read_state(){
	uchar temp;
	P2 = 0xff;
	cd = 1;
	rd = 0;
	temp = P2;
	rd = 1;
	return(temp);
}

/*STA0ָ���д״̬,STA1���ݶ�д״̬ �жϺ���*/
void lcd_enable(){
	uchar i;
	for(i = 10; i > 0; i--)
		if((read_state() & 0x03) == 0x03)
			break;
	if(i==0)error0=1;/*��i==0��˵������*/
	//else error0=0;
}

/*STA2�����Զ���״̬ �жϺ���*/
void atrd_enable(){
	uchar i;
	for(i = 10; i > 0; i--)
		if((read_state() & 0x04) == 0x04)
			break;
	if(i==0)error1=1;/*��i==0��˵������*/
	//else error1=0;
}

/*STA3�����Զ�д״̬ �жϺ���*/
void atwr_enable(){
	uchar i;
	for(i = 10; i > 0; i--)
		if((read_state() & 0x08) == 0x08)
			break;
	if(i==0)error2=1;/*��i==0��˵������*/
	//else error2=0;
}

/*д�޲�������*/
void write_cmd0(uchar cmd){
	lcd_enable();
	cd=1;
	P2=cmd;
	wr=0;
	wr=1;
}

/*д����������*/
void write_cmd1(uchar data1, uchar cmd){
	lcd_enable();
	cd=0;
	P2=data1;
	wr=0;
	wr=1;
	lcd_enable();
	cd=1;
	P2=cmd;
	wr=0;
	wr=1;
}

/*д˫��������*/
void write_cmd2(uchar data1, uchar data2, uchar cmd){
	lcd_enable();
	cd=0;
	P2=data1;
	wr=0;
	wr=1;
	lcd_enable();
	cd=0;
	P2=data2;
	wr=0;
	wr=1;	
	lcd_enable();
	cd=1;
	P2=cmd;
	wr=0;
	wr=1;	
}

/*д���ݺ���*/
void write_data(uchar data0){
	lcd_enable();
	cd=1;
	P2=data0;
	wr=0;
	wr=1;	
}

/*�����ݺ���*/
uchar read_data(){
	char temp;
	lcd_enable();
	cd = 0;
	P2 = 0xff;
	rd = 0;
	temp = P2;
	rd = 1;
	return(temp);	/*������0,���ܴ���*/
}

/*�Զ�д��ʼ*/
void auto_write(){
	write_cmd0(AUT_WR);
}

/*�Զ�����ʼ*/
void auto_read(){
	write_cmd0(AUT_RD);
}

/*�Զ�д����*/
void atwr_stop(){
	write_cmd0(AUT_WO);
}

/*�Զ�������*/
void atrd_stop(){
	write_cmd0(AUT_RO);
}

/*����һ��д����*/
void write_one(uchar data1, char way){
	atwr_enable();
	auto_write();
	write_cmd1(data1,way);
	atwr_stop();
}

/*����һ�ζ�����*/
uchar read_one(char way){
	uchar temp;
	atrd_enable();
	auto_read();
	write_cmd0(way);
	temp = read_data();
	atrd_stop();
	return(temp);
}

/*���õ�ǰ��ʾλ�ú���x,y��0��ʼ��ʾ��λΪ�ַ�*/
void set_xy(uchar x, uchar y){
	int temp;
	temp = y * LCD_CHAR + x;
	write_cmd2(temp&0xff,temp/0xff,ADR_POS);			
}

void set_adr(uchar D1, uchar D2){
	write_cmd2(D1,D2,ADR_POS);
}

/*���ù��ָ�� x,y��0��ʼ*/
void set_cur(char x, char y){
	write_cmd2(x,y,CUR_POS);
}

/*CGRAMƫ�õ�ַ���ú���*/
void set_cgram(){
	write_cmd2(0x01,0x00,CGR_POS);//0000,1100,0000,0000 0C00
}

/*Һ����ʼ������(�ı����׵�ַD1,�ı����׵�ַD2, �ı������,  ͼ�����׵�ַD1, ͼ�����׵�ַD2, ͼ�������,   �����״,  ��ʾ��ʽ,  ��ʾ����)*/
void lcd_init(uchar txtstpd1, uchar txtstpd2, uchar txtwid, uchar grhstpd1, uchar grhstpd2, uchar grhwid, uchar cur, uchar mod, uchar sw){
	write_cmd2(txtstpd1,txtstpd2,TXT_STP);								/*�ı����׵�ַ*/
	write_cmd2(txtwid,0x00,TXT_WID);			/*�ı������*/
	write_cmd2(grhstpd1,grhstpd2,GRH_STP);		/*ͼ�����׵�ַ*/
	write_cmd2(grhwid,0x00,GRH_WID);			/*ͼ�������*/
	write_cmd0(CUR_SHP | cur);					/*�����״*/
	write_cmd0(mod);							/*��ʾ��ʽ*/
	write_cmd0(DIS_SW | sw);					/*��ʾ����*/
}