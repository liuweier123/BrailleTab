/*128*64液晶模块驱动程序 ,HD61202驱动
  创建时间:07.1.6
  功能描述:循环显示李白的诗歌共8行，指定反白显示*/ 
#include <at89x51.h>
//#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int
#define lcm P1 
sbit p_csl=P2^4;
sbit p_csr=P2^3;
sbit p_di=P2^2;
sbit p_rw=P2^1;
sbit p_e=P2^0;
sbit p_rst=P2^7;
uchar code HZ[];
uchar code Ez[];
/*****函数声明********/
void delay(uint k);
void wcode(uchar c,uchar csl,uchar csr);
void wdata(uchar c,uchar csl,uchar csr);
void set_statrline(uchar i);
void set_xy(uchar x,uchar y);
void dison_off(uchar o);
void reset();
void lcd_init(void);
void lw(uchar x,uchar y,uchar dd);//写数据函数
void disp_Hz(uchar xx,uchar yy,uchar n,uchar fb);//显示汉字
void disp_Ez(uchar xx,uchar yy,uchar n,uchar fb);

//延时
void delay(uint k)
{	uint i;
    for(;k>0;k--)
	 {	for(i=0;i<124;i++)
	      {;}
	  }
}

//


//LCM忙判断
void lcd_busy(void)
{	p_di=0;
    p_rw=1;
    /*lcm=0xff;
    while(1)
     {  p_e=1;
        if(lcm<0x80)
         break;
        p_e=0;
     }
    p_e=0;*/
}
//写指令到LCM
void wcode(uchar c,uchar csl,uchar csr)
{	p_csl=csl;
    p_csr=csr;
    lcd_busy();
    p_di=0;
    p_rw=0;
    lcm=c;//将变量C赋予LCM
    p_e=1;
    p_e=0;
}
//写数据到LCM子函数
void wdata(uchar c,uchar csl,uchar csr)
{	p_csl=csl;
    p_csr=csr;
    lcd_busy();
    p_di=1;
    p_rw=0;
    lcm=c;//将变量C赋予LCM
    p_e=1;
    p_e=0;
}
//设定起始行
void set_startline(uchar i)
{	i=0xc0+i;
    wcode(i,1,1);
}
//定位X方向，Y方向
void set_xy(uchar x,uchar y)
{	x=x+0x40;
    y=y+0xb8;
    wcode(x,1,1);
    wcode(y,1,1);
}
//屏幕开启、关闭
void dison_off(uchar o)
{	o=o+0x3e;  //o为1为开，为0是关
    wcode(o,1,1);
}
//复位子函数
void reset()
{//delay(1000);
   	p_rst=0;
    delay(20);
    p_rst=1;
   delay(20);
}
//LCM初始化
void lcd_init(void)
{	uchar x,y;
    reset();
    
    dison_off(0);
    for(y=0;y<8;y++) 
     { for(x=0;x<128;x++)
         lw(x,y,0);
      }
    dison_off(1);
   set_startline(0);
}
//写数据到LCM
void lw(uchar x,uchar y,uchar dd)
{	if(x>=64)
     { set_xy(x-64,y);
       wdata(dd,0,1);
      }
     else
	  { set_xy(x,y);
	    wdata(dd,1,0);
	  }
}
//显示汉字子函数
void disp_Hz(uchar xx,uchar yy,uchar n,uchar fb)//xx为该行第xx个字，共8字，yy为第几行，共8行。
{	uchar i,dx;
   
    for(i=0;i<16;i++)
	 {	dx=HZ[2*i+n*32]; //2*i为选择偶数行，因其为列扫描
	   if(fb)
		  dx=255-dx;//反白显示
		lw(xx*16+i,yy,dx);
		dx=HZ[(2*i+1)+n*32];
		if(fb)
		 dx=255-dx;
		lw(xx*16+i,yy+1,dx);
	  }
}
void disp_Ez(uchar xx,uchar yy,uchar n,uchar fb)//显示数字或英语
{  uchar i,dx;
    for(i=0;i<8;i++)
     {	dx=Ez[2*i+n*16];
	    if(fb)
		  dx=255-dx;
		lw(xx*8+i,yy,dx);//

       	dx=Ez[(2*i+1)+n*16];
		if(fb)
		 dx=255-dx;
		lw(xx*8+i,yy+1,dx);
	  }
}

/*****主函数****/
void main()
{	uchar loop,i,y;//
   uchar fb;
    lcd_init();
    delay(300);
    for(loop=0;loop<2;loop++)//菜单
        {
  		  disp_Hz(loop+1,0,loop+64,1);
		  disp_Ez(13,0,10,0);
		  disp_Ez(14,0,8,0);
		 }
    while(1)
     {for(i=0;i<8;i++)
      {  disp_Ez(12,0,i+1,0);
	     if(i<3)
           { if(i!=0)fb=0;
              else fb=1;
             for(loop=0;loop<8;loop++)//行1
  		      { disp_Hz(loop,2,loop,fb);
              }  
		   }
		  if(i<4)
           { if(i!=1)fb=0;
			     else fb=1;
             if(i==3)y=2;
			     else y=4;
			  for(loop=0;loop<8;loop++)//2
  		        { 
		          disp_Hz(loop,y,loop+8,fb);
       		   } }
         if(i<5)
		   {  if(i!=2)fb=0;
			     else fb=1;
              if((i==0)||(i==1)||(i==2))
			     y=6;
             if(i==3)y=4;
			 if(i==4)y=2;
   		     for(loop=0;loop<8;loop++)//3
  		      {  
		       disp_Hz(loop,y,loop+16,fb);//第一屏结束，每屏显示3行
              }
		    }
          if(i>=3)
           { if(i!=3)fb=0;
              else fb=1;//

			 if(i==3)y=6;
			 if(i==4)y=4;
			 if(i==5)y=2;
             for(loop=0;loop<8;loop++)//行4
  		      { disp_Hz(loop,y,loop+24,fb);
              }  
		   }
		  if(i>=4)
           { if(i!=4)fb=0;
			     else fb=1;//

                if(i==4)y=6;
			    if(i==5)y=4;
			    if(i==6)y=2;
			    for(loop=0;loop<8;loop++)//5
  		        { 
		          disp_Hz(loop,y,loop+32,fb);//y=1时
       		   } }
         if(i>=5)
		   {  if(i!=5)fb=0;
			     else fb=1;

             if(i==5)y=6;
			 if(i==6)y=4;
			 if(i==7)y=2;
		     for(loop=0;loop<8;loop++)//6
  		      {  
		       disp_Hz(loop,y,loop+40,fb);
          }
		 }
		 if(i>=6)
           { if(i!=6)fb=0;
              else fb=1;
			  if(i==6)y=6;
			  if(i==7)y=4;
             for(loop=0;loop<8;loop++)//行7
  		      {disp_Hz(loop,y,loop+48,fb);
              }  
		   }
		  if(i==7)
           { if(i!=7)fb=0;
			     else fb=1;
				 
			    for(loop=0;loop<8;loop++)//8
  		        { 
		          disp_Hz(loop,6,loop+56,fb);//y=1时
       		   } }
		 delay(600);
		
		 
       }

       } 
}
uchar code HZ[]=
{0x40,0x40,0x40,0x40,0x20,0x42,0x20,0x42,0x50,0x4A,0x48,0x72,0x44,0x42,0xC3,0x7F,
0x44,0x42,0x48,0x62,0x50,0x5A,0x50,0x42,0x20,0x42,0x60,0x40,0x20,0x40,0x00,0x00,/*"金",0*/

0x00,0x00,0xFE,0xFF,0x22,0x02,0x5A,0x04,0x86,0x43,0x10,0x48,0x94,0x24,0x74,0x22,
0x94,0x15,0x1F,0x09,0x34,0x15,0x54,0x23,0x94,0x60,0x94,0xC0,0x10,0x40,0x00,0x00,/*"陵",1*/

0x04,0x00,0x64,0x00,0x24,0x81,0x24,0x41,0x24,0x21,0x2F,0x19,0xE4,0x07,0x24,0x01,
0x24,0x01,0x24,0x41,0x2F,0x81,0x24,0x7F,0x24,0x00,0x64,0x00,0x24,0x00,0x00,0x00,/*"劳",2*/

0x04,0x00,0x64,0x00,0x24,0x81,0x24,0x41,0x24,0x21,0x2F,0x19,0xE4,0x07,0x24,0x01,
0x24,0x01,0x24,0x41,0x2F,0x81,0x24,0x7F,0x24,0x00,0x64,0x00,0x24,0x00,0x00,0x00,/*"劳",3*/

0x40,0x40,0x41,0x20,0xC6,0x1F,0x00,0x20,0x40,0x40,0x48,0x48,0x49,0x44,0x4E,0x43,
0xF8,0x40,0x4C,0x41,0x4B,0x42,0x48,0x4C,0x48,0x40,0x40,0x40,0x00,0x40,0x00,0x00,/*"送",4*/

0x00,0x08,0x18,0x08,0x04,0x05,0x84,0x04,0x44,0xFC,0x7C,0x46,0xA5,0x46,0x26,0x45,
0x24,0x45,0xA4,0x46,0x64,0x46,0x24,0xFE,0x14,0x04,0x0C,0x0C,0x04,0x04,0x00,0x00,/*"客",5*/

0x00,0x00,0x40,0x40,0x30,0x48,0x12,0x48,0xDC,0x4B,0x54,0x4A,0x50,0x4A,0x5F,0x7E,
0x50,0x4A,0x50,0x4A,0xD8,0x4B,0x16,0x48,0x54,0x48,0x38,0x48,0x10,0x40,0x00,0x00,/*"堂",6*/

0x00,0x00,0x00,0x00,0x00,0x58,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"，",7*/

0x02,0x80,0x02,0x80,0x82,0x83,0xBA,0x42,0xAA,0x4A,0xAF,0x5B,0xAA,0x2A,0xBA,0x2A,
0xAA,0x2A,0xAF,0x5B,0xAA,0x4A,0xBA,0x42,0x82,0x83,0x02,0x80,0x00,0x80,0x00,0x00,/*"蔓",8*/

0x04,0x08,0x04,0x08,0x04,0x08,0xE4,0x0B,0xA4,0x0A,0xBF,0x0A,0xA4,0x0A,0xA4,0xFE,
0xA4,0x0A,0xBF,0x0A,0xA4,0x0A,0xE4,0x0B,0x04,0x08,0x04,0x08,0x04,0x08,0x00,0x00,/*"草",9*/

0x00,0x00,0x04,0x00,0x04,0xFE,0xF4,0x02,0x84,0x1A,0xCC,0x16,0xAD,0x12,0x96,0x13,
0x94,0x12,0xAC,0x16,0xCC,0x1A,0x84,0x72,0xF4,0x82,0x06,0x7E,0x04,0x00,0x00,0x00,/*"离",10*/

0x00,0x00,0x04,0x00,0x04,0xFE,0xF4,0x02,0x84,0x1A,0xCC,0x16,0xAD,0x12,0x96,0x13,
0x94,0x12,0xAC,0x16,0xCC,0x1A,0x84,0x72,0xF4,0x82,0x06,0x7E,0x04,0x00,0x00,0x00,/*"离",11*/

0x00,0x01,0x80,0x40,0x60,0x40,0x1E,0x41,0x10,0x41,0x10,0x41,0x10,0x41,0x10,0x41,
0xFF,0x7F,0x12,0x41,0x10,0x41,0x10,0x41,0x98,0x41,0x10,0x61,0x00,0x40,0x00,0x00,/*"生",12*/

0x40,0x40,0x42,0x20,0xCC,0x1F,0x00,0x20,0x04,0x40,0x04,0x40,0xE5,0x5F,0xB6,0x4A,
0xAC,0x4A,0xA4,0x4A,0xA6,0x4A,0xE5,0x5F,0x04,0x40,0x04,0x40,0x00,0x40,0x00,0x00,/*"道",13*/

0x40,0x00,0x20,0x00,0xF8,0x7F,0x07,0x00,0x82,0x00,0x64,0x41,0x2C,0x31,0x34,0x0F,
0x65,0x05,0xA6,0x05,0x34,0x25,0x2C,0x45,0xA4,0x3D,0x74,0x01,0x20,0x00,0x00,0x00,/*"傍",14*/

0x00,0x00,0x00,0x18,0x00,0x24,0x00,0x24,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"。",15*/

0x08,0x00,0x08,0x00,0x08,0x00,0x08,0x7F,0x08,0x21,0x08,0x21,0x08,0x21,0xFF,0x21,
0x08,0x21,0x08,0x21,0x08,0x21,0x08,0x7F,0x08,0x00,0x08,0x00,0x08,0x00,0x00,0x00,/*"古",16*/

0x70,0x00,0x00,0x00,0xFF,0xFF,0x08,0x00,0x50,0x00,0x44,0x00,0x54,0xFF,0x54,0x15,
0x54,0x15,0x7F,0x15,0x54,0x55,0x54,0x95,0x54,0x7F,0x44,0x00,0x40,0x00,0x00,0x00,/*"情",17*/

0x00,0x00,0x02,0x08,0x02,0x04,0x02,0x02,0x02,0x01,0x82,0x00,0x42,0x00,0xFE,0x7F,
0x06,0x00,0x42,0x00,0xC2,0x00,0x82,0x01,0x02,0x07,0x03,0x02,0x02,0x00,0x00,0x00,/*"不",18*/

0x00,0x08,0x00,0x04,0x00,0x03,0xFE,0x00,0x12,0x00,0x12,0x09,0x12,0x11,0x12,0x32,
0x72,0x66,0x92,0x00,0x12,0x01,0x12,0x02,0x1E,0x06,0x00,0x0C,0x00,0x04,0x00,0x00,/*"尽",19*/

0x00,0x00,0x04,0x00,0x04,0x20,0xC4,0x18,0xB4,0x0E,0x8C,0x04,0x87,0x20,0x84,0x40,
0xF4,0xFF,0x84,0x00,0x84,0x02,0x84,0x04,0x84,0x18,0x04,0x30,0x00,0x00,0x00,0x00,/*"东",20*/

0x10,0x04,0x60,0x04,0x01,0xFC,0x86,0x03,0x60,0x40,0x04,0x30,0x44,0x0F,0x64,0x00,
0x55,0x00,0x4E,0x7F,0x44,0x00,0x64,0x3F,0xC4,0x40,0x04,0x40,0x04,0x70,0x00,0x00,/*"流",21*/

0x00,0x10,0x10,0x10,0x10,0x08,0x10,0x06,0x90,0x01,0x70,0x40,0x00,0x80,0xFF,0x7F,
0x20,0x00,0x60,0x00,0x90,0x01,0x08,0x06,0x04,0x0C,0x00,0x18,0x00,0x08,0x00,0x00,/*"水",22*/

0x00,0x00,0x00,0x00,0x00,0x58,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"，",23*/

0x00,0x20,0x00,0x20,0xF0,0x3F,0x00,0x10,0x00,0x10,0xFF,0x0F,0x20,0x08,0x20,0x08,
0x00,0x00,0xFF,0x3F,0x40,0x40,0x20,0x40,0x20,0x40,0x10,0x40,0x10,0x78,0x00,0x00,/*"此",24*/

0x10,0x20,0x10,0x20,0x10,0x10,0xFE,0x1F,0x10,0x08,0x50,0x08,0x40,0x00,0xFE,0x3F,
0x20,0x40,0x20,0x40,0xFF,0x4F,0x10,0x42,0x10,0x44,0xF8,0x43,0x10,0x70,0x00,0x00,/*"地",25*/

0x00,0x00,0x44,0x20,0x54,0x38,0x54,0x00,0x54,0x3C,0xFF,0x41,0x00,0x40,0x00,0x42,
0x00,0x4C,0xFF,0x41,0x54,0x40,0x54,0x70,0x54,0x00,0x44,0x08,0x40,0x30,0x00,0x00,/*"悲",26*/

0x00,0x40,0x00,0x20,0x00,0x18,0xFE,0x07,0x02,0x10,0x12,0x08,0x22,0x04,0x42,0x02,
0x82,0x01,0x7A,0x06,0x12,0x1C,0x02,0x00,0xFE,0x0F,0x00,0x30,0x00,0x7C,0x00,0x00,/*"风",27*/

0x10,0x00,0x12,0x41,0xD2,0x30,0x32,0x00,0xFF,0x3B,0x31,0x40,0x51,0x42,0x10,0x4A,
0x08,0x51,0x90,0x40,0x7F,0x40,0x90,0x60,0x08,0x09,0x0C,0x33,0x00,0x01,0x00,0x00,/*"愁",28*/

0x00,0x00,0x00,0x00,0xF8,0x7F,0x08,0x21,0x08,0x21,0x0C,0x21,0x0B,0x21,0x08,0x21,
0x08,0x21,0x08,0x21,0x08,0x21,0x08,0x21,0xF8,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,/*"白",29*/

0x08,0x04,0x08,0x03,0xC8,0x00,0xFF,0xFF,0x48,0x00,0x88,0x01,0x0A,0x08,0x42,0x24,
0x62,0x13,0xD2,0x08,0x4A,0x06,0xC6,0x41,0x42,0x80,0xC0,0x7F,0x00,0x00,0x00,0x00,/*"杨",30*/

0x00,0x00,0x00,0x18,0x00,0x24,0x00,0x24,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"。",31*/

0x20,0x04,0x20,0x04,0x22,0x42,0x22,0x82,0xFE,0x7F,0x21,0x01,0x21,0x01,0x20,0x10,
0x20,0x10,0xFF,0x08,0x20,0x07,0x22,0x1A,0xAC,0x21,0x20,0x40,0x20,0xF0,0x00,0x00,/*"我",32*/

0x08,0x22,0x28,0x22,0x2A,0x11,0x2A,0x11,0xFA,0x0B,0x0A,0x0C,0x0A,0x06,0xFE,0x7F,
0x0A,0x02,0x09,0x04,0xF9,0x0D,0x49,0x19,0x29,0x31,0x2C,0x11,0x88,0x01,0x00,0x00,/*"乘",33*/

0x20,0x00,0x22,0x40,0x2A,0x44,0x2A,0x25,0x2A,0x15,0xAA,0x47,0x6A,0x85,0x3F,0x7D,
0x2A,0x05,0xAA,0x04,0x2A,0x14,0x2A,0x26,0x2A,0x4C,0x22,0x00,0x20,0x00,0x00,0x00,/*"素",34*/

0x40,0x80,0x40,0x60,0xFC,0x1F,0x56,0x01,0x65,0x46,0x44,0x80,0xFC,0x7F,0x00,0x00,
0xE4,0x07,0x24,0x02,0x24,0x02,0xE4,0x47,0x04,0x80,0xFC,0x7F,0x04,0x00,0x00,0x00,/*"舸",35*/

0x00,0x00,0xFE,0xFF,0x02,0x00,0x12,0x00,0x92,0x1F,0x92,0x08,0x92,0x08,0x92,0x08,
0x92,0x08,0x92,0x08,0x92,0x1F,0x12,0x40,0x02,0x80,0xFE,0x7F,0x00,0x00,0x00,0x00,/*"同",36*/

0x00,0x80,0x00,0x60,0xFC,0x1F,0x44,0x20,0x54,0x63,0x54,0x15,0x54,0x49,0x55,0x81,
0xFE,0x7F,0x54,0x0D,0x54,0x11,0x54,0x29,0xF4,0x6D,0x44,0xC0,0x44,0x40,0x00,0x00,/*"康",37*/

0x00,0x00,0x00,0x20,0x40,0x18,0xFC,0x0C,0x44,0x07,0x44,0x12,0x44,0x20,0x46,0x40,
0xFA,0x3F,0x42,0x00,0x43,0x00,0x43,0x02,0x42,0x0C,0x40,0x38,0x00,0x10,0x00,0x00,/*"乐",38*/

0x00,0x00,0x00,0x00,0x00,0x58,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"，",39*/

0x00,0x00,0xFC,0x3F,0x94,0x10,0x95,0x08,0x96,0x06,0x94,0x4C,0xFC,0x40,0x00,0x20,
0x00,0x18,0xFE,0x07,0x22,0x01,0x22,0x21,0x22,0x41,0xFE,0x3F,0x00,0x00,0x00,0x00,/*"朗",40*/

0xFC,0x07,0x04,0x02,0x04,0x02,0xFC,0x07,0x00,0x20,0x40,0x18,0x48,0x06,0xC9,0x41,
0x09,0x80,0xFA,0x7F,0x00,0x01,0x80,0x02,0x70,0x0C,0x20,0x18,0x00,0x08,0x00,0x00,/*"咏",41*/

0x10,0x04,0x61,0x04,0x06,0xFF,0xE0,0x00,0x18,0x00,0x20,0x00,0xAA,0xFF,0xAA,0x0A,
0xAA,0x0A,0xBF,0x0A,0xAA,0x4A,0xAA,0x8A,0xAA,0x7F,0x2A,0x00,0x00,0x00,0x00,0x00,/*"清",42*/

0x00,0x00,0x00,0x80,0x00,0x60,0xFF,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xFE,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x7F,0x00,0x00,0x00,0x00,/*"川",43*/

0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,
0x02,0x00,0xFE,0x03,0x60,0x0C,0x90,0x10,0x08,0x21,0x00,0x40,0x00,0x78,0x00,0x00,/*"飞",44*/

0x04,0x02,0x04,0x01,0x84,0x00,0xC4,0xFF,0x3C,0x00,0x14,0x82,0x85,0x41,0x66,0x22,
0xBC,0x14,0x24,0x09,0x24,0x14,0x24,0x23,0xE4,0x40,0x24,0xC0,0x04,0x40,0x00,0x00,/*"夜",45*/

0x00,0x00,0x0C,0x22,0x04,0x1A,0x55,0x06,0xD5,0xFF,0x55,0x06,0x05,0x0A,0x7F,0x00,
0x05,0xFF,0x55,0x55,0x55,0x55,0x55,0x55,0x05,0xFF,0x0C,0x00,0x04,0x00,0x00,0x00,/*"霜",46*/

0x00,0x00,0x00,0x18,0x00,0x24,0x00,0x24,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"。",47*/


0x00,0x00,0x40,0x00,0x48,0x00,0x48,0x00,0x48,0xFF,0x7F,0x49,0x48,0x49,0x48,0x49,
0x48,0x49,0x48,0x49,0x7F,0x49,0x48,0xFF,0x48,0x00,0x48,0x00,0x40,0x00,0x00,0x00,/*"昔",48*/

0x00,0x00,0xFC,0xFF,0x00,0x00,0x11,0x08,0x12,0x08,0xF0,0x0F,0x52,0x09,0x52,0x09,
0x52,0x05,0xF2,0x7F,0x12,0x04,0x12,0x44,0x02,0x80,0xFE,0x7F,0x00,0x00,0x00,0x00,/*"闻",49*/

0x00,0x00,0x40,0x01,0x30,0x01,0x0E,0x01,0x08,0x01,0x08,0x01,0x08,0x01,0x08,0x01,
0xFF,0x7F,0x08,0x01,0x08,0x01,0x08,0x01,0x08,0x01,0x08,0x01,0x00,0x01,0x00,0x00,/*"牛",50*/

0x10,0x04,0x60,0xFC,0x01,0x03,0xC6,0x00,0x00,0x02,0x20,0x02,0x24,0xFF,0x24,0x49,
0xA4,0x49,0x7F,0x49,0x24,0x49,0x34,0x49,0x28,0xFF,0x26,0x00,0x20,0x00,0x00,0x00,/*"渚",51*/

0xFE,0x07,0x02,0x01,0x02,0x01,0x02,0x01,0xFE,0x07,0x40,0x00,0x20,0x01,0x10,0x01,
0x0C,0x01,0x23,0x81,0xC4,0x61,0x08,0x19,0x10,0x07,0x30,0x01,0x60,0x00,0x00,0x00,/*"吟",52*/

0x00,0x20,0x02,0x20,0x82,0x20,0x82,0x20,0x82,0x20,0x82,0x3F,0xFE,0x20,0x82,0x20,
0x82,0x20,0x82,0x20,0xC2,0x3F,0x82,0x20,0x02,0x20,0x00,0x30,0x00,0x20,0x00,0x00,/*"五",53*/

0x10,0x10,0x10,0x10,0x12,0x10,0xD2,0x17,0x56,0x15,0x5A,0x15,0x52,0x15,0x53,0xFD,
0x52,0x15,0x5A,0x15,0x56,0x15,0xD2,0x17,0x12,0x10,0x12,0x10,0x10,0x10,0x00,0x00,/*"章",54*/

0x00,0x00,0x00,0x00,0x00,0x58,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"，",55*/

0x80,0x00,0x80,0x00,0x40,0x00,0x20,0x02,0x10,0x02,0x08,0x02,0x24,0x02,0x43,0x82,
0xC4,0x42,0x08,0x32,0x10,0x0E,0x20,0x02,0x60,0x00,0xC0,0x00,0x40,0x00,0x00,0x00,/*"今",56*/

0x00,0x20,0x80,0x20,0x84,0x10,0x84,0x10,0x94,0x08,0xA4,0x04,0xC4,0x02,0xFF,0xFF,
0x84,0x01,0xC4,0x02,0xB4,0x04,0x94,0x08,0x84,0x18,0x84,0x30,0x80,0x10,0x00,0x00,/*"来",57*/

0x80,0x00,0x40,0x00,0xF0,0x7F,0x1C,0x00,0x07,0x00,0xE2,0x07,0x24,0x02,0x24,0x02,
0x24,0x02,0xE4,0x07,0x04,0x20,0x04,0x40,0xFC,0x3F,0x04,0x00,0x04,0x00,0x00,0x00,/*"何",58*/

0x40,0x00,0x42,0x00,0xCC,0x3F,0x04,0x50,0x00,0x29,0xFC,0x11,0x56,0x4D,0x55,0x83,
0xFC,0x7F,0x50,0x00,0x90,0x41,0x10,0x80,0xFF,0x7F,0x10,0x00,0x10,0x00,0x00,0x00,/*"谢",59*/

0x10,0x20,0x10,0x20,0x14,0x10,0xD4,0x11,0x54,0xF9,0x54,0x45,0x54,0x23,0x5F,0x03,
0x54,0x05,0x54,0x09,0x54,0x11,0xD4,0x29,0x14,0x64,0x10,0xC2,0x10,0x40,0x00,0x00,/*"袁",60*/

0x00,0x00,0x18,0x29,0x04,0x29,0x14,0x15,0x94,0x14,0x94,0x4A,0xD5,0x89,0xB6,0x44,
0x14,0x3F,0x14,0x06,0x94,0x09,0x04,0x09,0x14,0x10,0x0C,0x30,0x04,0x10,0x00,0x00,/*"家",61*/

0x00,0x00,0xFC,0x7F,0x94,0x20,0x95,0x10,0x96,0x0A,0x94,0x04,0xFC,0x18,0x00,0x00,
0x00,0x00,0xFE,0xFF,0x02,0x00,0x42,0x08,0xB2,0x08,0x0E,0x11,0x02,0x0E,0x00,0x00,/*"郎",62*/

0x00,0x00,0x00,0x18,0x00,0x24,0x00,0x24,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"。",63*/

//李白
0x80,0x00,0x84,0x04,0x44,0x04,0xC4,0x04,0xA4,0x04,0x94,0x44,0x8C,0x84,0xFF,0x7E,
0x8C,0x05,0x94,0x04,0xA4,0x04,0x24,0x04,0x44,0x04,0xC4,0x04,0x40,0x04,0x00,0x00,/*"李",0*/

0x00,0x00,0x00,0x00,0xF8,0x7F,0x08,0x21,0x08,0x21,0x0C,0x21,0x0B,0x21,0x08,0x21,
0x08,0x21,0x08,0x21,0x08,0x21,0x08,0x21,0xF8,0x7F,0x00,0x00,0x00,0x00,0x00,0x00};/*"白",1*/
//数字
uchar code Ez[]={
0x00,0x00,0xE0,0x0F,0x10,0x10,0x08,0x20,0x08,0x20,0x10,0x10,0xE0,0x0F,0x00,0x00,/*"0",0*/

0x00,0x00,0x10,0x20,0x10,0x20,0xF8,0x3F,0x00,0x20,0x00,0x20,0x00,0x00,0x00,0x00,/*"1",1*/

0x00,0x00,0x70,0x30,0x08,0x28,0x08,0x24,0x08,0x22,0x88,0x21,0x70,0x30,0x00,0x00,/*"2",2*/

0x00,0x00,0x30,0x18,0x08,0x20,0x88,0x20,0x88,0x20,0x48,0x11,0x30,0x0E,0x00,0x00,/*"3",3*/

0x00,0x00,0x00,0x07,0xC0,0x04,0x20,0x24,0x10,0x24,0xF8,0x3F,0x00,0x24,0x00,0x00,/*"4",4*/

0x00,0x00,0xF8,0x19,0x08,0x21,0x88,0x20,0x88,0x20,0x08,0x11,0x08,0x0E,0x00,0x00,/*"5",5*/

0x00,0x00,0xE0,0x0F,0x10,0x11,0x88,0x20,0x88,0x20,0x18,0x11,0x00,0x0E,0x00,0x00,/*"6",6*/

0x00,0x00,0x38,0x00,0x08,0x00,0x08,0x3F,0xC8,0x00,0x38,0x00,0x08,0x00,0x00,0x00,/*"7",7*/

0x00,0x00,0x70,0x1C,0x88,0x22,0x08,0x21,0x08,0x21,0x88,0x22,0x70,0x1C,0x00,0x00,/*"8",8*/

0x00,0x00,0xE0,0x00,0x10,0x31,0x08,0x22,0x08,0x22,0x10,0x11,0xE0,0x0F,0x00,0x00,/*"9",9*/

0x00,0x00,0x00,0x60,0x00,0x18,0x00,0x06,0x80,0x01,0x60,0x00,0x18,0x00,0x04,0x00/*"/",10*/
};


