#include <reg52.h>
//#include <at89x52.h>
//unsigned char code BCD[]={0x3f,0x06,0x5b,0x4f, //此处是将0-F转换成相应的BCD码
//                          0x66,0x6d,0x7d,0x07, 
//                          0x7f,0x6f,0x77,0x7c, 
//                          0x39,0x5e,0x79,0x71};
//unsigned char code KEY[]={0x00,0x00,0x01,0x02,0x03,//此处是为使程序通用,当键值不是按
//						  	   0x04,0x05,0x06,0x07,//这个排列时,把此表更改即可
//							   0x08,0x09,0x0a,0x0b,//最前面的那个0x00是为了查表方便,
//							   0x0c,0x0d,0x0e,0x0f};//因为键值是从1开始的
							
sfr key_port=0x90;	    //定义P1口为键盘扫描口
bit key_ok=0;       	//有键按下的标志

/*************延时子程序*************
****调用一次用时18微秒,t每加1,用时增加6微秒*/
void delay(unsigned char t)
{
 while(t--);
}


unsigned char r_left(unsigned char x)//循环左移一位
{
 x<<=1;
 x++;
 return(x);
}

/*************粗判有无键按下**********
****有键按下则将key_ok置1************/
void scan_full(void)
{
	unsigned char temp;
	key_port=0xf0; 		//低半字节为行线,高半字节为列线
	temp=P1;
	if(temp!=0xf0)
	key_ok=1;
	else key_ok=0;
}
/************键盘扫描程序*************************
****功能:返回键值,当无键按下时,返回0*************/
 unsigned char key_scan(void)
{
 unsigned char temp,count=0x01,key_value;//按键返回值
 unsigned char x_scan=0xfe,y_scan=0xef;//行、列扫描码
 unsigned char i,j,y;		//行数和列数
 while(1)
 {
 	scan_full();	 		//粗判是否有键按下
 	if(key_ok==1)
 	{
   		key_ok=0;
   		delay(200);			//延时去抖动
   		scan_full();			//再次粗判是否有键按下
   		if(key_ok==1)
   		{
    		for(i=0;i<4;i++)		//扫描4行
    		{
	 			key_port=x_scan;
     			for(j=0;j<4;j++)		//每行4列
     			{
      				temp=key_port;
	  				temp=temp&0xf0;
	  				y=y_scan&0xf0;
	  				if(temp==y)
	  				{
						while(key_ok!=0)//等待按键松开
   						{
							scan_full();
   						}
	   					key_value=count;												
	   					return(key_value);//找到键值,马上返回
	  				}
	  				else 
	  				{
	   					count++;
	   					y_scan=r_left(y_scan);
	  				}	 
	 			}
				y_scan=0xef;		//扫描完一列,重新对列扫描量赋初值
	 			x_scan=r_left(x_scan);//行扫描码左移一位,扫描下一行  					
			}
		}
  	} 
    return(key_value);//没键按下,返回0
 }
}

//unsigned char key(void)
//{
 // unsigned char x;
 // unsigned char y;
 // x=key_scan();
 // return(x);
  //y=KEY[x];	
  //return y;
//}
