//--------------------------------------------------------------------------//
//                                源程序大公开                              //
//                    (c) Copyright 2001－2005 xuwenjun                     //
//                            All Rights Reserved                           //
//                                    V1.00                                 //
//--------------------------------------------------------------------------//
//标　题: 俄罗斯方块程序                            �                       //
//文件名: xwj_fk.c                                                          //
//版　本: V1.00                                                             //
//修改人: 徐文军                         E-mail:xuwenjun@21cn.com           //
//日　期: 05-05-13                                                           //
//描　述: 俄罗斯方块程序                            �                       //
//声　明:                                                                   //
//        以下代码仅免费提供给学习用途，但引用或修改后必须在文件中声明出处. //
//        如用于商业用途请与作者联系.    E-mail:xuwenjun@21cn.com           //
//        有问题请mailto xuwenjun@21cn.com   欢迎与我交流!                  //
//--------------------------------------------------------------------------//
//老版本: 无                             老版本文件名:                      //
//创建人: 徐文军                         E-mail:xuwenjun@21cn.com           //
//日　期: 05-05-13                                                          //
//描　述:                                                                   //
//      1、功能完整，直接使用                                               //
//      2、模块独立性强，移植方便，外部仅init和move函数，修改显示和输入即可 //
//      3、对减少内存占用、尽量减少屏幕操作进行适当优化                     //
//      4、新方块生成高度随机，绝对无规律                                   //
//      5、仿真环境为Keil7.5+Proteus6.5,可以联机也可脱机运行                //
//      CODE SIZE        =   1845    ----                                   //
//      CONSTANT SIZE    =    326    ----                                   //
//      DATA SIZE        =     16      19                                   //
//      IDATA SIZE       =     50    ----                                   //
//      BIT SIZE         =      1       1                                   //
//--------------------------------------------------------------------------//
#include <stdlib.h>
#include "xwj_lcd16.h"	 			// 字符液晶控制函数声明    //
#include "xwj_lcd6963.h"			// T6963C 公用函数
#include "xwj_hlkey.h"				//  P1口行列式键盘  //
#include "xwj_serial.h"				//串口函数集
#include "change.h"					//数制转换
#include "xwj_fk.h"					//俄罗斯方块程序

#define ulong		unsigned long
#define uint		unsigned int
#define uchar		unsigned char

extern void delay(unsigned int x);
//----------------俄罗斯方块内部函数----------------------------------------//
void fk_dot(uchar x,uchar y);		//显示1个方块点
void fk_cldot(uchar x,uchar y);		//清除1个方块点
void fk_show(void);					//显示分数
void fk_reffk(void);				//刷新方块
void fk_refnew(void);				//刷新预览方块
void fk_refline(yy);				//刷新1行背景
bit  fk_chk(void);					//冲突检查
void fk_new(void);					//产生新方块
void fk_add(void);					//方块合并

/*
//-----------------俄罗斯方块公用函数--------------------------------------//
void fk_init(void);						//方块初始化
void fk_move(unsigned char mode);		//移动方块
*/

//-------------------------------------------------------------------------//
#define FULLMAP	0x0fff				/*掩码*/
#define LINEGUAN	20				/*20行过一关*/
#define NEWX	15					/*预览方块X位置*/
#define NEWY	12					/*预览方块Y位置*/
#define LINEMAX	21					/*屏幕最高21行*/
uint idata fk_map[LINEMAX+4];		//背景映象
uchar  fk_x,fk_y,fk_r;				//方块左右、高度、方向
uchar fk_type;						//方块形状
uchar  fk_oldx,fk_oldy,fk_oldr;		//方块上次左右、高度、方向
uchar  fk_newtype,fk_newr;			//新方块形状、方向
uint score;							//总分
uint line;							//总行数	
uchar speed;						//速度
uchar moven;						//速度相关计数器
uchar automapn;						//随机方块的行数
bit fk_run;							//俄罗斯方坑蜗吩诵�
	
uchar code fk_mod[][4][4]={			//方块模型号,4个方向,4行
	0,0,7,2,0,1,3,1,0,0,2,7,0,2,3,2,	//_|_
	0,0,6,3,0,1,3,2,0,0,6,3,0,1,3,2,	//_|~
	0,0,3,6,0,2,3,1,0,0,3,6,0,2,3,1,	//~|_
	0,0,7,4,0,3,1,1,0,0,1,7,0,2,2,3,	//|__
	0,0,7,1,0,1,1,3,0,0,4,7,0,3,2,2,	//__|
	0,0,0,15,1,1,1,1,0,0,0,15,1,1,1,1,	//____
	0,0,3,3,0,0,3,3,0,0,3,3,0,0,3,3,	//田字
};

uchar code strmap[4][9]={
	"不错！  ","真棒！  ","好极啦！","太棒了！",
};

//--------------------------------------------------------------------------//
void fk_dot(uchar x,uchar y)		//显示1个方块点
{
	printat(x*3+1, 241-(y-4)*12,"■");
}

//--------------------------------------------------------------------------//
void fk_cldot(uchar x,uchar y)		//清除1个方块点
{
//	printat(x*3+1, 241-(y-4)*12,"□");
	printat(x*3+1, 241-(y-4)*12,"┘");
}

//--------------------------------------------------------------------------//
void fk_show(void)					//显示分数
{
	printat(50, 12,chnint(score,1));
	printat(60, 12,"00");
	printat(40, 12,"得分:");
	printat(54,36,chnint(line,1));
	printat(40, 36,"行数:");
	printat(54,60,chnchar(speed,1));
	printat(40,60,"速度:");
	printat(54,84,chnchar(automapn,1));
	printat(40,84,"关数:");		
}

//--------------------------------------------------------------------------//
void fk_reffk(void)					//刷新方块
{
	uchar i,j;
	uchar temp;
	//----------------------------------------------//清除原来的方块
	for (i=0;i<4;i++)
	{
		temp=(fk_mod[fk_type][fk_oldr][i]);
		for (j=fk_oldx;j<fk_oldx+4;j++)
		{
			if(temp&0x01)
			{
				fk_cldot(j,fk_oldy+i);
			}
			temp>>=1;
		}
	}
	//----------------------------------------------//显示新的方块
	for (i=0;i<4;i++)
	{
		temp=(fk_mod[fk_type][fk_r][i]);
		for (j=fk_x;j<fk_x+4;j++)
		{
			if(temp&0x01)
			{
				fk_dot(j,fk_y+i);
			}
			temp>>=1;
		}
	}
	fk_oldx=fk_x;fk_oldy=fk_y;fk_oldr=fk_r;	//保存新方块位置
}

//--------------------------------------------------------------------------//
void fk_refnew(void)				//刷新预览方块
{
	uchar i,j;
	uchar temp;
	//----------------------------------------------//预览方块
	for (i=0;i<4;i++)
	{
		temp=(fk_mod[fk_newtype][fk_newr][i]);
		for (j=NEWX;j<NEWX+4;j++)
		{
			if(temp&0x01)
			{
				fk_dot(j,NEWY+i);
			}
			else
			{
				fk_cldot(j,NEWY+i);
			}
			temp>>=1;
		}
	}
}

//--------------------------------------------------------------------------//
void fk_refline(yy)					//刷新1行背景
{
	uchar i;
	uint temp;
	if (yy>=4)
	{
		temp=fk_map[yy];
		for (i=0;i<12;i++)
		{
			if ((temp&0x01) !=0)
				fk_dot(i,yy);
			else
				fk_cldot(i,yy);
			temp >>= 1;
		}
	}
}

//--------------------------------------------------------------------------//
bit fk_chk(void)					//冲突检查
{
	uchar i;
	bit neq=0;
	for (i=0;i<4;i++)
	{
		if ( (((fk_mod[fk_type][fk_r][i])<<fk_x)+(fk_map[fk_y+i])) != (((fk_mod[fk_type][fk_r][i])<<fk_x)|(fk_map[fk_y+i])) )
			neq=1;
	}
	return(neq);
}

//--------------------------------------------------------------------------//
void fk_new(void)						//产生新方块
{
	srand(rand()+fk_x+fk_y+fk_r);
	fk_oldx=fk_x=5;
	fk_oldy=fk_y=LINEMAX;
    fk_type = fk_newtype;
	fk_oldr=fk_newr;
    fk_newtype = rand()%7;
	fk_newr=rand()%4;
	fk_refnew();			//刷新预览方块
	if (fk_run)
		fk_reffk();	//刷新显示
}

//--------------------------------------------------------------------------//
void fk_add(void)					//方块合并
{
	uchar i,j;
	uchar full=0x00;
	uchar fulltemp;
	uchar fullline=0x00;
	for (i=0;i<4;i++)	//方块合并
	{
		fk_map[fk_y+i] |= (fk_mod[fk_type][fk_r][i])<<fk_x;
		full <<= 1;
		if ((fk_y+i >= 4) && (fk_map[fk_y+i] == 0xffff))		//满行
		{
			full |= 0x01;
		}
	}
	if (full != 0)		//有满行
	{
		for (j=0;j<3;j++)		//消行闪烁3次
		{
			delay(300);
			fulltemp=full;
			for (i=0;i<4;i++)	//4行
			{
				if ((fulltemp&0x08) != 0)
				{
					fk_map[fk_y+i] ^= FULLMAP;
				}
				fk_refline(fk_y+i);
				fulltemp <<= 1;
			}
		}
		fulltemp=full;
		for (i=fk_y;i<LINEMAX+4+fullline;i++)	//上面行下移
		{
			if ((i < LINEMAX+4)&&(fk_map[i-fullline]!=fk_map[i]))
			{
				fk_map[i-fullline]=fk_map[i];
				fk_refline(i-fullline);
			}
			if ((i >= LINEMAX+4)&&(fk_map[i-fullline]!=~FULLMAP))
			{
				fk_map[i-fullline]=~FULLMAP;	//背景映象
				fk_refline(i-fullline);
			}
			if ((fulltemp&0x08) != 0)
			{
				fullline++;
			}
			fulltemp <<= 1;
		}
		if (((line+fullline)/LINEGUAN) != (line/LINEGUAN))//每20行速度+1
			speed ++;
		line += fullline;				//更新分数、行数
		score += (1<<fullline)-1;
		printat(46,180,strmap[fullline-1]);	//夸奖
		fk_show();						//显示分数
		fk_new();			//产生新方块
	}
	else
	{
		if (fk_y > LINEMAX-10)	//在最高位置碰撞且不能消行则游戏结束
			printat(46,180,"加油啊！");		//加油啊
		if (fk_y > LINEMAX-6)	//在最高位置碰撞且不能消行则游戏结束
			printat(46,180,"糟糕了！");		//糟糕了

		if (fk_y==LINEMAX)		//在最高位置碰撞且不能消行则游戏结束
			fk_run=0;	//方块初始化
		else
			fk_new();	//产生新方块
	}
}

//--------------------------------------------------------------------------//
void fk_init(void)					//方块初始化
{
	uchar i;
	fk_run = 0;
	moven=0;
	Lcd6963Cls();
	Lcd6963Rec(0,0,152,255);
	Lcd6963ChHz(0);					//切换到16X16点阵
	printat(2, 16,"欢迎光临文君阁");
	printat(2, 48,"请按键选择：");
	printat(2, 80,"-----------------");
	printat(2, 96,"7左旋 8右旋 9右旋");
	printat(2, 112,"4左移 5右旋 6右移");
	printat(2, 128,"4速度 5开始 6关数");
	printat(2, 144,"1左移 2下移 3右移");
	printat(2, 160,"-----------------");
	Lcd6963ChHz(1);					//切换到12X12点阵
	printat(46,180,"欢迎使用");
	fk_show();						//显示分数
	while (~fk_run)
	{
		fk_move();					//等待设置速度关数开始
		delay(10);
	}
	for (i=0;i<4;i++)
	{
		fk_map[i]=0xffff;	//背景映象
	}	delay(3000);
	for (i=4;i<LINEMAX+4;i++)
	{
		if (i<(automapn+4))
			fk_map[i]=rand()-1|~FULLMAP; //背景映象
		else
			fk_map[i]=~FULLMAP;		//背景映象
		fk_refline(i);				//刷新1行背景
	}
	fk_show();						//显示分数
//	fk_new();						//产生新方块
}   

//--------------------------------------------------------------------------//
void fk_move(void)						//移动方块
{
	unsigned char temp;
	if(KeyTest())					//检查有无按键
	{
		putinbuf(KeyGetCode());		//按键码输入接收缓冲区
	}
	if (checkin())
	{
		temp=getbyte();
		if (temp!=0) Lcd16WrCharhh(12,0,temp);
		if (temp!=0) Lcd16WrChar(15,0,temp);
		putchar(temp);
	}
	else
		temp=0xff;					//无键设为无效键用于下移方块
	temp -= '0';
	switch(temp)
	{
	default:
		if (--moven)				//游戏难度
			break;
		else
		{
			moven=(252>>speed)+2;
		}
	case 2:		//下移
		if (fk_run)					//游戏中下移
		{
			if(fk_y>0)
			{
				fk_y--;
				if(fk_chk())
				{
					fk_y++;		//有冲突取消操作,执行碰撞组合
					fk_add();	//方块合并	//产生新方块
				}
			}
			else				//方块到底也执行碰撞组合
			{
				fk_add();		//方块合并
			}
		}
		else						//初始化时
		{
			fk_new();				//产生新方块
		}
		break;
	case 0:		//下移到底
		while((fk_y>0)&&~(fk_chk())) //一直下移直到冲突
		{
			fk_y--;
		}
		moven=1;
		fk_y++;				//恢复到未冲突位置
		break;
	case 3:		//右移
	case 6:		//右移
		if (fk_run)					//游戏中右移
		{
			if(fk_x<12)
			{
				fk_x++;
				if(fk_chk())
					fk_x--;//有冲突取消操作
			}
		}
		else							//初始化时
		{
			automapn++;
			automapn &= 0x0f;
			fk_show();					//显示分数
		}
		break;
	case 1:		//左移
	case 4:		//移
		if (fk_run)						//游戏中左移
		{
			if(fk_x>0)
			{
				fk_x--;
				if(fk_chk())
					fk_x++;//有冲突取消操作
			}
		}
		else							//初始化时
		{
			speed++;
			speed &= 0x07;
			fk_show();					//显示分数
		}
		break;
	case 9:		//右转
	case 8:		//右转
	case 5:		//右转
		if (fk_run)						//游戏中右转
		{
			fk_r++;
			if(fk_chk())
				fk_r--;					//有冲突取消操作
			fk_r &= 0x03;
		}
		else							//初始化时
		{
			fk_run = 1;
		}
		break;
	case 7:		//左转
		if (fk_run)						//游戏中右转
		{
			fk_r--;
			if(fk_chk())
				fk_r++;				//有冲突取消操作
			fk_r &= 0x03;
		}
		else							//初始化时
		{
			fk_run = 1;
		}
		break;
	}
	if((fk_run)&& ((fk_x!=fk_oldx)||(fk_y!=fk_oldy)||(fk_r!=fk_oldr)) )
	{
		fk_reffk();	//刷新显示
	}
	rand();
}

/*
// ---------------------------------------------- //	32字节
void delay(uint x)
{
   uint i,j;
   for (i=0; i<x;i++) {
      for (j=0;j<102; j++) ;
   }
}

//--------------------------------------------------------------------------//
void main(void)						// 测试用
{
	serial_init();
	Lcd6963Init();					//Lcd6963复位
	Lcd16Reset();					//Lcd16复位
	Serial_main();					//	串口测试用主函数  
	Lcd16main();					//Lcd16临时测试主程序
	Lcd6963main();					//Lcd6963测试用
	fk_init();						//方块初始化
	while(1)
	{
		if (~fk_run)
			fk_init();						//方块初始化
		fk_move();					//移动方块
		delay(10);
	}
}
*/
