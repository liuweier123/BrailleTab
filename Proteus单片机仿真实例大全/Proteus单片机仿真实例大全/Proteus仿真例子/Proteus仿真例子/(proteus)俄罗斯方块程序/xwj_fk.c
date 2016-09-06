//--------------------------------------------------------------------------//
//                                Ô´³ÌĞò´ó¹«¿ª                              //
//                    (c) Copyright 2001£­2005 xuwenjun                     //
//                            All Rights Reserved                           //
//                                    V1.00                                 //
//--------------------------------------------------------------------------//
//±ê¡¡Ìâ: ¶íÂŞË¹·½¿é³ÌĞò                            ©                       //
//ÎÄ¼şÃû: xwj_fk.c                                                          //
//°æ¡¡±¾: V1.00                                                             //
//ĞŞ¸ÄÈË: ĞìÎÄ¾ü                         E-mail:xuwenjun@21cn.com           //
//ÈÕ¡¡ÆÚ: 05-05-13                                                           //
//Ãè¡¡Êö: ¶íÂŞË¹·½¿é³ÌĞò                            ©                       //
//Éù¡¡Ã÷:                                                                   //
//        ÒÔÏÂ´úÂë½öÃâ·ÑÌá¹©¸øÑ§Ï°ÓÃÍ¾£¬µ«ÒıÓÃ»òĞŞ¸Äºó±ØĞëÔÚÎÄ¼şÖĞÉùÃ÷³ö´¦. //
//        ÈçÓÃÓÚÉÌÒµÓÃÍ¾ÇëÓë×÷ÕßÁªÏµ.    E-mail:xuwenjun@21cn.com           //
//        ÓĞÎÊÌâÇëmailto xuwenjun@21cn.com   »¶Ó­ÓëÎÒ½»Á÷!                  //
//--------------------------------------------------------------------------//
//ÀÏ°æ±¾: ÎŞ                             ÀÏ°æ±¾ÎÄ¼şÃû:                      //
//´´½¨ÈË: ĞìÎÄ¾ü                         E-mail:xuwenjun@21cn.com           //
//ÈÕ¡¡ÆÚ: 05-05-13                                                          //
//Ãè¡¡Êö:                                                                   //
//      1¡¢¹¦ÄÜÍêÕû£¬Ö±½ÓÊ¹ÓÃ                                               //
//      2¡¢Ä£¿é¶ÀÁ¢ĞÔÇ¿£¬ÒÆÖ²·½±ã£¬Íâ²¿½öinitºÍmoveº¯Êı£¬ĞŞ¸ÄÏÔÊ¾ºÍÊäÈë¼´¿É //
//      3¡¢¶Ô¼õÉÙÄÚ´æÕ¼ÓÃ¡¢¾¡Á¿¼õÉÙÆÁÄ»²Ù×÷½øĞĞÊÊµ±ÓÅ»¯                     //
//      4¡¢ĞÂ·½¿éÉú³É¸ß¶ÈËæ»ú£¬¾ø¶ÔÎŞ¹æÂÉ                                   //
//      5¡¢·ÂÕæ»·¾³ÎªKeil7.5+Proteus6.5,¿ÉÒÔÁª»úÒ²¿ÉÍÑ»úÔËĞĞ                //
//      CODE SIZE        =   1845    ----                                   //
//      CONSTANT SIZE    =    326    ----                                   //
//      DATA SIZE        =     16      19                                   //
//      IDATA SIZE       =     50    ----                                   //
//      BIT SIZE         =      1       1                                   //
//--------------------------------------------------------------------------//
#include <stdlib.h>
#include "xwj_lcd16.h"	 			// ×Ö·ûÒº¾§¿ØÖÆº¯ÊıÉùÃ÷    //
#include "xwj_lcd6963.h"			// T6963C ¹«ÓÃº¯Êı
#include "xwj_hlkey.h"				//  P1¿ÚĞĞÁĞÊ½¼üÅÌ  //
#include "xwj_serial.h"				//´®¿Úº¯Êı¼¯
#include "change.h"					//ÊıÖÆ×ª»»
#include "xwj_fk.h"					//¶íÂŞË¹·½¿é³ÌĞò

#define ulong		unsigned long
#define uint		unsigned int
#define uchar		unsigned char

extern void delay(unsigned int x);
//----------------¶íÂŞË¹·½¿éÄÚ²¿º¯Êı----------------------------------------//
void fk_dot(uchar x,uchar y);		//ÏÔÊ¾1¸ö·½¿éµã
void fk_cldot(uchar x,uchar y);		//Çå³ı1¸ö·½¿éµã
void fk_show(void);					//ÏÔÊ¾·ÖÊı
void fk_reffk(void);				//Ë¢ĞÂ·½¿é
void fk_refnew(void);				//Ë¢ĞÂÔ¤ÀÀ·½¿é
void fk_refline(yy);				//Ë¢ĞÂ1ĞĞ±³¾°
bit  fk_chk(void);					//³åÍ»¼ì²é
void fk_new(void);					//²úÉúĞÂ·½¿é
void fk_add(void);					//·½¿éºÏ²¢

/*
//-----------------¶íÂŞË¹·½¿é¹«ÓÃº¯Êı--------------------------------------//
void fk_init(void);						//·½¿é³õÊ¼»¯
void fk_move(unsigned char mode);		//ÒÆ¶¯·½¿é
*/

//-------------------------------------------------------------------------//
#define FULLMAP	0x0fff				/*ÑÚÂë*/
#define LINEGUAN	20				/*20ĞĞ¹ıÒ»¹Ø*/
#define NEWX	15					/*Ô¤ÀÀ·½¿éXÎ»ÖÃ*/
#define NEWY	12					/*Ô¤ÀÀ·½¿éYÎ»ÖÃ*/
#define LINEMAX	21					/*ÆÁÄ»×î¸ß21ĞĞ*/
uint idata fk_map[LINEMAX+4];		//±³¾°Ó³Ïó
uchar  fk_x,fk_y,fk_r;				//·½¿é×óÓÒ¡¢¸ß¶È¡¢·½Ïò
uchar fk_type;						//·½¿éĞÎ×´
uchar  fk_oldx,fk_oldy,fk_oldr;		//·½¿éÉÏ´Î×óÓÒ¡¢¸ß¶È¡¢·½Ïò
uchar  fk_newtype,fk_newr;			//ĞÂ·½¿éĞÎ×´¡¢·½Ïò
uint score;							//×Ü·Ö
uint line;							//×ÜĞĞÊı	
uchar speed;						//ËÙ¶È
uchar moven;						//ËÙ¶ÈÏà¹Ø¼ÆÊıÆ÷
uchar automapn;						//Ëæ»ú·½¿éµÄĞĞÊı
bit fk_run;							//¶íÂŞË¹·½¿ÓÎÏ·ÔËĞĞ
	
uchar code fk_mod[][4][4]={			//·½¿éÄ£ĞÍºÅ,4¸ö·½Ïò,4ĞĞ
	0,0,7,2,0,1,3,1,0,0,2,7,0,2,3,2,	//_|_
	0,0,6,3,0,1,3,2,0,0,6,3,0,1,3,2,	//_|~
	0,0,3,6,0,2,3,1,0,0,3,6,0,2,3,1,	//~|_
	0,0,7,4,0,3,1,1,0,0,1,7,0,2,2,3,	//|__
	0,0,7,1,0,1,1,3,0,0,4,7,0,3,2,2,	//__|
	0,0,0,15,1,1,1,1,0,0,0,15,1,1,1,1,	//____
	0,0,3,3,0,0,3,3,0,0,3,3,0,0,3,3,	//Ìï×Ö
};

uchar code strmap[4][9]={
	"²»´í£¡  ","Õæ°ô£¡  ","ºÃ¼«À²£¡","Ì«°ôÁË£¡",
};

//--------------------------------------------------------------------------//
void fk_dot(uchar x,uchar y)		//ÏÔÊ¾1¸ö·½¿éµã
{
	printat(x*3+1, 241-(y-4)*12,"¡ö");
}

//--------------------------------------------------------------------------//
void fk_cldot(uchar x,uchar y)		//Çå³ı1¸ö·½¿éµã
{
//	printat(x*3+1, 241-(y-4)*12,"¡õ");
	printat(x*3+1, 241-(y-4)*12,"©¼");
}

//--------------------------------------------------------------------------//
void fk_show(void)					//ÏÔÊ¾·ÖÊı
{
	printat(50, 12,chnint(score,1));
	printat(60, 12,"00");
	printat(40, 12,"µÃ·Ö:");
	printat(54,36,chnint(line,1));
	printat(40, 36,"ĞĞÊı:");
	printat(54,60,chnchar(speed,1));
	printat(40,60,"ËÙ¶È:");
	printat(54,84,chnchar(automapn,1));
	printat(40,84,"¹ØÊı:");		
}

//--------------------------------------------------------------------------//
void fk_reffk(void)					//Ë¢ĞÂ·½¿é
{
	uchar i,j;
	uchar temp;
	//----------------------------------------------//Çå³ıÔ­À´µÄ·½¿é
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
	//----------------------------------------------//ÏÔÊ¾ĞÂµÄ·½¿é
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
	fk_oldx=fk_x;fk_oldy=fk_y;fk_oldr=fk_r;	//±£´æĞÂ·½¿éÎ»ÖÃ
}

//--------------------------------------------------------------------------//
void fk_refnew(void)				//Ë¢ĞÂÔ¤ÀÀ·½¿é
{
	uchar i,j;
	uchar temp;
	//----------------------------------------------//Ô¤ÀÀ·½¿é
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
void fk_refline(yy)					//Ë¢ĞÂ1ĞĞ±³¾°
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
bit fk_chk(void)					//³åÍ»¼ì²é
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
void fk_new(void)						//²úÉúĞÂ·½¿é
{
	srand(rand()+fk_x+fk_y+fk_r);
	fk_oldx=fk_x=5;
	fk_oldy=fk_y=LINEMAX;
    fk_type = fk_newtype;
	fk_oldr=fk_newr;
    fk_newtype = rand()%7;
	fk_newr=rand()%4;
	fk_refnew();			//Ë¢ĞÂÔ¤ÀÀ·½¿é
	if (fk_run)
		fk_reffk();	//Ë¢ĞÂÏÔÊ¾
}

//--------------------------------------------------------------------------//
void fk_add(void)					//·½¿éºÏ²¢
{
	uchar i,j;
	uchar full=0x00;
	uchar fulltemp;
	uchar fullline=0x00;
	for (i=0;i<4;i++)	//·½¿éºÏ²¢
	{
		fk_map[fk_y+i] |= (fk_mod[fk_type][fk_r][i])<<fk_x;
		full <<= 1;
		if ((fk_y+i >= 4) && (fk_map[fk_y+i] == 0xffff))		//ÂúĞĞ
		{
			full |= 0x01;
		}
	}
	if (full != 0)		//ÓĞÂúĞĞ
	{
		for (j=0;j<3;j++)		//ÏûĞĞÉÁË¸3´Î
		{
			delay(300);
			fulltemp=full;
			for (i=0;i<4;i++)	//4ĞĞ
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
		for (i=fk_y;i<LINEMAX+4+fullline;i++)	//ÉÏÃæĞĞÏÂÒÆ
		{
			if ((i < LINEMAX+4)&&(fk_map[i-fullline]!=fk_map[i]))
			{
				fk_map[i-fullline]=fk_map[i];
				fk_refline(i-fullline);
			}
			if ((i >= LINEMAX+4)&&(fk_map[i-fullline]!=~FULLMAP))
			{
				fk_map[i-fullline]=~FULLMAP;	//±³¾°Ó³Ïó
				fk_refline(i-fullline);
			}
			if ((fulltemp&0x08) != 0)
			{
				fullline++;
			}
			fulltemp <<= 1;
		}
		if (((line+fullline)/LINEGUAN) != (line/LINEGUAN))//Ã¿20ĞĞËÙ¶È+1
			speed ++;
		line += fullline;				//¸üĞÂ·ÖÊı¡¢ĞĞÊı
		score += (1<<fullline)-1;
		printat(46,180,strmap[fullline-1]);	//¿ä½±
		fk_show();						//ÏÔÊ¾·ÖÊı
		fk_new();			//²úÉúĞÂ·½¿é
	}
	else
	{
		if (fk_y > LINEMAX-10)	//ÔÚ×î¸ßÎ»ÖÃÅö×²ÇÒ²»ÄÜÏûĞĞÔòÓÎÏ·½áÊø
			printat(46,180,"¼ÓÓÍ°¡£¡");		//¼ÓÓÍ°¡
		if (fk_y > LINEMAX-6)	//ÔÚ×î¸ßÎ»ÖÃÅö×²ÇÒ²»ÄÜÏûĞĞÔòÓÎÏ·½áÊø
			printat(46,180,"Ôã¸âÁË£¡");		//Ôã¸âÁË

		if (fk_y==LINEMAX)		//ÔÚ×î¸ßÎ»ÖÃÅö×²ÇÒ²»ÄÜÏûĞĞÔòÓÎÏ·½áÊø
			fk_run=0;	//·½¿é³õÊ¼»¯
		else
			fk_new();	//²úÉúĞÂ·½¿é
	}
}

//--------------------------------------------------------------------------//
void fk_init(void)					//·½¿é³õÊ¼»¯
{
	uchar i;
	fk_run = 0;
	moven=0;
	Lcd6963Cls();
	Lcd6963Rec(0,0,152,255);
	Lcd6963ChHz(0);					//ÇĞ»»µ½16X16µãÕó
	printat(2, 16,"»¶Ó­¹âÁÙÎÄ¾ı¸ó");
	printat(2, 48,"Çë°´¼üÑ¡Ôñ£º");
	printat(2, 80,"-----------------");
	printat(2, 96,"7×óĞı 8ÓÒĞı 9ÓÒĞı");
	printat(2, 112,"4×óÒÆ 5ÓÒĞı 6ÓÒÒÆ");
	printat(2, 128,"4ËÙ¶È 5¿ªÊ¼ 6¹ØÊı");
	printat(2, 144,"1×óÒÆ 2ÏÂÒÆ 3ÓÒÒÆ");
	printat(2, 160,"-----------------");
	Lcd6963ChHz(1);					//ÇĞ»»µ½12X12µãÕó
	printat(46,180,"»¶Ó­Ê¹ÓÃ");
	fk_show();						//ÏÔÊ¾·ÖÊı
	while (~fk_run)
	{
		fk_move();					//µÈ´ıÉèÖÃËÙ¶È¹ØÊı¿ªÊ¼
		delay(10);
	}
	for (i=0;i<4;i++)
	{
		fk_map[i]=0xffff;	//±³¾°Ó³Ïó
	}	delay(3000);
	for (i=4;i<LINEMAX+4;i++)
	{
		if (i<(automapn+4))
			fk_map[i]=rand()-1|~FULLMAP; //±³¾°Ó³Ïó
		else
			fk_map[i]=~FULLMAP;		//±³¾°Ó³Ïó
		fk_refline(i);				//Ë¢ĞÂ1ĞĞ±³¾°
	}
	fk_show();						//ÏÔÊ¾·ÖÊı
//	fk_new();						//²úÉúĞÂ·½¿é
}   

//--------------------------------------------------------------------------//
void fk_move(void)						//ÒÆ¶¯·½¿é
{
	unsigned char temp;
	if(KeyTest())					//¼ì²éÓĞÎŞ°´¼ü
	{
		putinbuf(KeyGetCode());		//°´¼üÂëÊäÈë½ÓÊÕ»º³åÇø
	}
	if (checkin())
	{
		temp=getbyte();
		if (temp!=0) Lcd16WrCharhh(12,0,temp);
		if (temp!=0) Lcd16WrChar(15,0,temp);
		putchar(temp);
	}
	else
		temp=0xff;					//ÎŞ¼üÉèÎªÎŞĞ§¼üÓÃÓÚÏÂÒÆ·½¿é
	temp -= '0';
	switch(temp)
	{
	default:
		if (--moven)				//ÓÎÏ·ÄÑ¶È
			break;
		else
		{
			moven=(252>>speed)+2;
		}
	case 2:		//ÏÂÒÆ
		if (fk_run)					//ÓÎÏ·ÖĞÏÂÒÆ
		{
			if(fk_y>0)
			{
				fk_y--;
				if(fk_chk())
				{
					fk_y++;		//ÓĞ³åÍ»È¡Ïû²Ù×÷,Ö´ĞĞÅö×²×éºÏ
					fk_add();	//·½¿éºÏ²¢	//²úÉúĞÂ·½¿é
				}
			}
			else				//·½¿éµ½µ×Ò²Ö´ĞĞÅö×²×éºÏ
			{
				fk_add();		//·½¿éºÏ²¢
			}
		}
		else						//³õÊ¼»¯Ê±
		{
			fk_new();				//²úÉúĞÂ·½¿é
		}
		break;
	case 0:		//ÏÂÒÆµ½µ×
		while((fk_y>0)&&~(fk_chk())) //Ò»Ö±ÏÂÒÆÖ±µ½³åÍ»
		{
			fk_y--;
		}
		moven=1;
		fk_y++;				//»Ö¸´µ½Î´³åÍ»Î»ÖÃ
		break;
	case 3:		//ÓÒÒÆ
	case 6:		//ÓÒÒÆ
		if (fk_run)					//ÓÎÏ·ÖĞÓÒÒÆ
		{
			if(fk_x<12)
			{
				fk_x++;
				if(fk_chk())
					fk_x--;//ÓĞ³åÍ»È¡Ïû²Ù×÷
			}
		}
		else							//³õÊ¼»¯Ê±
		{
			automapn++;
			automapn &= 0x0f;
			fk_show();					//ÏÔÊ¾·ÖÊı
		}
		break;
	case 1:		//×óÒÆ
	case 4:		//ÒÆ
		if (fk_run)						//ÓÎÏ·ÖĞ×óÒÆ
		{
			if(fk_x>0)
			{
				fk_x--;
				if(fk_chk())
					fk_x++;//ÓĞ³åÍ»È¡Ïû²Ù×÷
			}
		}
		else							//³õÊ¼»¯Ê±
		{
			speed++;
			speed &= 0x07;
			fk_show();					//ÏÔÊ¾·ÖÊı
		}
		break;
	case 9:		//ÓÒ×ª
	case 8:		//ÓÒ×ª
	case 5:		//ÓÒ×ª
		if (fk_run)						//ÓÎÏ·ÖĞÓÒ×ª
		{
			fk_r++;
			if(fk_chk())
				fk_r--;					//ÓĞ³åÍ»È¡Ïû²Ù×÷
			fk_r &= 0x03;
		}
		else							//³õÊ¼»¯Ê±
		{
			fk_run = 1;
		}
		break;
	case 7:		//×ó×ª
		if (fk_run)						//ÓÎÏ·ÖĞÓÒ×ª
		{
			fk_r--;
			if(fk_chk())
				fk_r++;				//ÓĞ³åÍ»È¡Ïû²Ù×÷
			fk_r &= 0x03;
		}
		else							//³õÊ¼»¯Ê±
		{
			fk_run = 1;
		}
		break;
	}
	if((fk_run)&& ((fk_x!=fk_oldx)||(fk_y!=fk_oldy)||(fk_r!=fk_oldr)) )
	{
		fk_reffk();	//Ë¢ĞÂÏÔÊ¾
	}
	rand();
}

/*
// ---------------------------------------------- //	32×Ö½Ú
void delay(uint x)
{
   uint i,j;
   for (i=0; i<x;i++) {
      for (j=0;j<102; j++) ;
   }
}

//--------------------------------------------------------------------------//
void main(void)						// ²âÊÔÓÃ
{
	serial_init();
	Lcd6963Init();					//Lcd6963¸´Î»
	Lcd16Reset();					//Lcd16¸´Î»
	Serial_main();					//	´®¿Ú²âÊÔÓÃÖ÷º¯Êı  
	Lcd16main();					//Lcd16ÁÙÊ±²âÊÔÖ÷³ÌĞò
	Lcd6963main();					//Lcd6963²âÊÔÓÃ
	fk_init();						//·½¿é³õÊ¼»¯
	while(1)
	{
		if (~fk_run)
			fk_init();						//·½¿é³õÊ¼»¯
		fk_move();					//ÒÆ¶¯·½¿é
		delay(10);
	}
}
*/
