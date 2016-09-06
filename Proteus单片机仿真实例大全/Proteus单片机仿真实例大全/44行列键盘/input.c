#include<reg51.h>
unsigned char code tab[4][4]={{'1','4','7','#'},
                  			{'2','5','8','0'},
                  			{'3','6','9','*'},
                  			{'A','B','C','D'}};       //0µ½FµÄ16¸ö¼üÖ²

void delay(unsigned char a)
	{
	unsigned char i;
	while(a--)
		for(i=100;i>0;i--)
			;
	}

char kbscan()          //¼üÅÌÉ¨Ãè
	{
 	unsigned char hang,lie;
	if(P3!=0x0f)
	delay(5);
	if(P3!=0x0f)
		{
		switch(P3&0xf0)
				{
				case 0x10:hang=0;break;
				case 0x20:hang=1;break;
				case 0x40:hang=2;break;
				case 0x80:hang=3;break;
				}
		P3=0xf0;
		P3=0xf0;
		switch(P3&0x0f)
				{
				case 1:lie=0;break;
				case 2:lie=1;break;
				case 4:lie=2;break;
				case 8:lie=3;break;
				}
		P3=0x0f;
		while(P3!=0x0f);
		return (tab[hang][lie]);
		}
	return 0;
	}



