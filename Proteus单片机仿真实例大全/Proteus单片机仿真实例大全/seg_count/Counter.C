
//******************************FileName: Counter.C**************************//
//******************************ICCAVR V6.30编译*****************************//

#include <iom16v.h>                 
#define uchar unsigned char
#define uint unsigned int

//数码管字型表，对应0，1，2，3，4，5，6，7，8，9//
uchar Table[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
uchar Data[4]={0,0,0,0};       //显示初始值：0 0 0 0
uint  CNT=0;                    //初始计数值：0 
uchar Key_Up;                  //加计数按键标志  
uchar Key_Down;                //减计数按键标志  

void DelayMs(uchar i)           //Ms级延时，参数i为延时时间
{uint j;
 for(;i!=0;i--)
  {for(j=0;j<250;j++);}
}

void Display(uchar *p)         //动态显示函数，参数p为待显示的数组名
{uchar i,sel=0x01;           
 for(i=0;i<4;i++)
  {PORTC=sel;                  //选通最右边的数码管
   PORTA=Table[p[i]];          //送字型码
   DelayMs(2);                 //显示延时    
   sel=sel<<1;                 //移位以显示前一位
  }
}

//******************************计数值处理函数******************************//
//功能：此函数用于将计数值拆分为BCD码的千，百，十，一数据，用于查表显示//
//参数说明：参数i:计数值；参数p:处理数据存放的数组名//
void Process(uint i,uchar *p) 
{p[0]=i/1000;
 i=i%1000;
 p[1]=i/100;
 i=i%100;
 p[2]=i/10;
 i=i%10;
 p[3]=i;
}

void Init_IO(void)             //初始化I/O口
{DDRA=0xff;                    //设置A口为推挽1输出
 PORTA=0xff;
 DDRB=0x00;                    //设置B口为不带上拉电阻输入
 PORTB=0x00;    
 DDRC=0xff;                    //设置C口为推挽1输出；             
 PORTC=0xff;
}

void Get_Key(void)             //按键扫描函数
{while((PINB&0x01)==0)         //若S1按下，置位加计数标志；
 {Key_Up=1;
 Display(Data);
 }
 while((PINB&0x02)==0)         //若S2按下，置位减计数标志； 
 {Key_Down=1;
 Display(Data);
 }
}

void main(void)
{uchar I;
 Init_IO();                    //初始化I/O口
 PORTA=0xff;                   //点亮测试所有的数码管
 PORTC=0x00;                   
 //DelayMs(3000);                //延时
 PORTC=0xff;                   //数码管熄灭，进入计数状态 
 while(1)
 {Get_Key();                   //按键扫描
  if(Key_Up==1)                //加计数处理
     {if(CNT!=9999)            //条件判断是否计数到9999
	    {CNT=CNT+1;            //计数值加1
		 Key_Up=0;}            //加计数标志复位
     }
  if(Key_Down==1)              //减计数处理
     {if(CNT!=0)               //条件判断是否计数到0000
	    {CNT=CNT-1;            //计数值减一
		 Key_Down=0;}          //减计数标志复位
	 }
  Process(CNT,Data);           //计数值处理
  Display(Data);               //动态扫描显示
 }
}
