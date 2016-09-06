	.module Counter.C
	.area data(ram, con, rel)
_Table::
	.blkb 2
	.area idata
	.byte 192,249
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 164,176
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 153,146
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 130,248
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 128,144
	.area data(ram, con, rel)
	.dbfile F:\myavr\mydesign\seg_time\Counter.C
	.dbsym e Table _Table A[10:10]c
_Data::
	.blkb 2
	.area idata
	.byte 0,0
	.area data(ram, con, rel)
	.dbfile F:\myavr\mydesign\seg_time\Counter.C
	.blkb 2
	.area idata
	.byte 0,0
	.area data(ram, con, rel)
	.dbfile F:\myavr\mydesign\seg_time\Counter.C
	.dbsym e Data _Data A[4:4]c
_CNT::
	.blkb 2
	.area idata
	.word 0
	.area data(ram, con, rel)
	.dbfile F:\myavr\mydesign\seg_time\Counter.C
	.dbsym e CNT _CNT i
	.area text(rom, con, rel)
	.dbfile F:\myavr\mydesign\seg_time\Counter.C
	.dbfunc e DelayMs _DelayMs fV
;              j -> R20,R21
;              i -> R16
	.even
_DelayMs::
	rcall push_gset1
	.dbline -1
	.dbline 17
; 
; //******************************FileName: Counter.C**************************//
; //******************************ICCAVR V6.30编译*****************************//
; 
; #include <io8535v.h>                 
; #define uchar unsigned char
; #define uint unsigned int
; 
; //数码管字型表，对应0，1，2，3，4，5，6，7，8，9//
; uchar Table[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
; uchar Data[4]={0,0,0,0};       //显示初始值：0 0 0 0
; uint  CNT=0;                    //初始计数值：0 
; uchar Key_Up;                  //加计数按键标志  
; uchar Key_Down;                //减计数按键标志  
; 
; void DelayMs(uchar i)           //Ms级延时，参数i为延时时间
; {uint j;
	.dbline 18
;  for(;i!=0;i--)
	rjmp L5
L2:
	.dbline 19
	.dbline 19
	clr R20
	clr R21
	rjmp L9
L6:
	.dbline 19
L7:
	.dbline 19
	subi R20,255  ; offset = 1
	sbci R21,255
L9:
	.dbline 19
	cpi R20,250
	ldi R30,0
	cpc R21,R30
	brlo L6
	.dbline 19
L3:
	.dbline 18
	dec R16
L5:
	.dbline 18
	tst R16
	brne L2
	.dbline -2
	.dbline 20
;   {for(j=0;j<250;j++);}
; }
L1:
	rcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r j 20 i
	.dbsym r i 16 c
	.dbend
	.dbfunc e Display _Display fV
;            sel -> R20
;              i -> R22
;              p -> R10,R11
	.even
_Display::
	rcall push_gset3
	mov R10,R16
	mov R11,R17
	.dbline -1
	.dbline 23
; 
; void Display(uchar *p)         //动态显示函数，参数p为待显示的数组名
; {uchar i,sel=0x01;           
	.dbline 23
	ldi R20,1
	.dbline 24
;  for(i=0;i<4;i++)
	clr R22
	rjmp L14
L11:
	.dbline 25
	.dbline 25
	out 0x15,R20
	.dbline 26
	mov R30,R22
	clr R31
	add R30,R10
	adc R31,R11
	ldd R30,z+0
	clr R31
	ldi R24,<_Table
	ldi R25,>_Table
	add R30,R24
	adc R31,R25
	ldd R2,z+0
	out 0x1b,R2
	.dbline 27
	ldi R16,2
	rcall _DelayMs
	.dbline 28
	lsl R20
	.dbline 29
L12:
	.dbline 24
	inc R22
L14:
	.dbline 24
	cpi R22,4
	brlo L11
	.dbline -2
	.dbline 30
;   {PORTC=sel;                  //选通最右边的数码管
;    PORTA=Table[p[i]];          //送字型码
;    DelayMs(2);                 //显示延时    
;    sel=sel<<1;                 //移位以显示前一位
;   }
; }
L10:
	rcall pop_gset3
	.dbline 0 ; func end
	ret
	.dbsym r sel 20 c
	.dbsym r i 22 c
	.dbsym r p 10 pc
	.dbend
	.dbfunc e Process _Process fV
;              p -> R20,R21
;              i -> R22,R23
	.even
_Process::
	rcall push_gset2
	mov R20,R18
	mov R21,R19
	mov R22,R16
	mov R23,R17
	.dbline -1
	.dbline 36
; 
; //******************************计数值处理函数******************************//
; //功能：此函数用于将计数值拆分为BCD码的千，百，十，一数据，用于查表显示//
; //参数说明：参数i:计数值；参数p:处理数据存放的数组名//
; void Process(uint i,uchar *p) 
; {p[0]=i/1000;
	.dbline 36
	ldi R18,1000
	ldi R19,3
	mov R16,R22
	mov R17,R23
	rcall div16u
	mov R30,R20
	mov R31,R21
	std z+0,R16
	.dbline 37
;  i=i%1000;
	.dbline 38
;  p[1]=i/100;
	ldi R18,1000
	ldi R19,3
	mov R16,R22
	mov R17,R23
	rcall mod16u
	mov R22,R16
	mov R23,R17
	ldi R18,100
	ldi R19,0
	rcall div16u
	mov R30,R20
	mov R31,R21
	std z+1,R16
	.dbline 39
;  i=i%100;
	.dbline 40
;  p[2]=i/10;
	ldi R18,100
	ldi R19,0
	mov R16,R22
	mov R17,R23
	rcall mod16u
	mov R22,R16
	mov R23,R17
	ldi R18,10
	ldi R19,0
	rcall div16u
	mov R30,R20
	mov R31,R21
	std z+2,R16
	.dbline 41
;  i=i%10;
	.dbline 42
;  p[3]=i;
	ldi R18,10
	ldi R19,0
	mov R16,R22
	mov R17,R23
	rcall mod16u
	mov R22,R16
	mov R23,R17
	mov R30,R20
	mov R31,R21
	std z+3,R22
	.dbline -2
	.dbline 43
; }
L15:
	rcall pop_gset2
	.dbline 0 ; func end
	ret
	.dbsym r p 20 pc
	.dbsym r i 22 i
	.dbend
	.dbfunc e Init_IO _Init_IO fV
	.even
_Init_IO::
	.dbline -1
	.dbline 46
; 
; void Init_IO(void)             //初始化I/O口
; {DDRA=0xff;                    //设置A口为推挽1输出
	.dbline 46
	ldi R24,255
	out 0x1a,R24
	.dbline 47
;  PORTA=0xff;
	out 0x1b,R24
	.dbline 48
;  DDRB=0x00;                    //设置B口为不带上拉电阻输入
	clr R2
	out 0x17,R2
	.dbline 49
;  PORTB=0x00;    
	out 0x18,R2
	.dbline 50
;  DDRC=0xff;                    //设置C口为推挽1输出；             
	out 0x14,R24
	.dbline 51
;  PORTC=0xff;
	out 0x15,R24
	.dbline -2
	.dbline 52
; }
L16:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e Get_Key _Get_Key fV
	.even
_Get_Key::
	.dbline -1
	.dbline 55
; 
; void Get_Key(void)             //按键扫描函数
; {while((PINB&0x01)==0)         //若S1按下，置位加计数标志；
	rjmp L19
L18:
	.dbline 56
	.dbline 56
	.dbline 57
	ldi R24,1
	sts _Key_Up,R24
	ldi R16,<_Data
	ldi R17,>_Data
	rcall _Display
	.dbline 58
L19:
	.dbline 55
	sbis 0x16,0
	rjmp L18
	rjmp L22
L21:
	.dbline 60
	.dbline 60
	.dbline 61
	ldi R24,1
	sts _Key_Down,R24
	ldi R16,<_Data
	ldi R17,>_Data
	rcall _Display
	.dbline 62
L22:
	.dbline 59
;  {Key_Up=1;
;  Display(Data);
;  }
;  while((PINB&0x02)==0)         //若S2按下，置位减计数标志； 
	sbis 0x16,1
	rjmp L21
	.dbline -2
	.dbline 63
;  {Key_Down=1;
;  Display(Data);
;  }
; }
L17:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e main _main fV
;              I -> <dead>
	.even
_main::
	.dbline -1
	.dbline 66
; 
; void main(void)
; {uchar I;
	.dbline 67
;  Init_IO();                    //初始化I/O口
	rcall _Init_IO
	.dbline 68
;  PORTA=0xff;                   //点亮测试所有的数码管
	ldi R24,255
	out 0x1b,R24
	.dbline 69
;  PORTC=0x00;                   
	clr R2
	out 0x15,R2
	.dbline 71
;  //DelayMs(3000);                //延时
;  PORTC=0xff;                   //数码管熄灭，进入计数状态 
	out 0x15,R24
	rjmp L26
L25:
	.dbline 73
;  while(1)
;  {Get_Key();                   //按键扫描
	.dbline 73
	rcall _Get_Key
	.dbline 74
;   if(Key_Up==1)                //加计数处理
	lds R24,_Key_Up
	cpi R24,1
	brne L28
	.dbline 75
;      {if(CNT!=9999)            //条件判断是否计数到9999
	.dbline 75
	lds R24,_CNT
	lds R25,_CNT+1
	cpi R24,15
	ldi R30,39
	cpc R25,R30
	breq L30
	.dbline 76
; 	    {CNT=CNT+1;            //计数值加1
	.dbline 76
	.dbline 77
; 		 Key_Up=0;}            //加计数标志复位
	adiw R24,1
	sts _CNT+1,R25
	sts _CNT,R24
	clr R2
	sts _Key_Up,R2
	.dbline 77
L30:
	.dbline 78
;      }
L28:
	.dbline 79
;   if(Key_Down==1)              //减计数处理
	lds R24,_Key_Down
	cpi R24,1
	brne L32
	.dbline 80
;      {if(CNT!=0)               //条件判断是否计数到0000
	.dbline 80
	lds R2,_CNT
	lds R3,_CNT+1
	tst R2
	brne X0
	tst R3
	breq L34
X0:
	.dbline 81
; 	    {CNT=CNT-1;            //计数值减一
	.dbline 81
	.dbline 82
; 		 Key_Down=0;}          //减计数标志复位
	lds R24,_CNT
	lds R25,_CNT+1
	sbiw R24,1
	sts _CNT+1,R25
	sts _CNT,R24
	clr R2
	sts _Key_Down,R2
	.dbline 82
L34:
	.dbline 83
; 	 }
L32:
	.dbline 84
	ldi R18,<_Data
	ldi R19,>_Data
	lds R16,_CNT
	lds R17,_CNT+1
	rcall _Process
	.dbline 85
	ldi R16,<_Data
	ldi R17,>_Data
	rcall _Display
	.dbline 86
L26:
	.dbline 72
	rjmp L25
X1:
	.dbline -2
	.dbline 87
;   Process(CNT,Data);           //计数值处理
;   Display(Data);               //动态扫描显示
;  }
; }
L24:
	.dbline 0 ; func end
	ret
	.dbsym l I 1 c
	.dbend
	.area bss(ram, con, rel)
	.dbfile F:\myavr\mydesign\seg_time\Counter.C
_Key_Down::
	.blkb 1
	.dbsym e Key_Down _Key_Down c
_Key_Up::
	.blkb 1
	.dbsym e Key_Up _Key_Up c
