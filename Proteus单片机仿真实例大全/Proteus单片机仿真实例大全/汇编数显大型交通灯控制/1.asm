;------------------------------------
;程序实现功能
;西南北路口直行与转弯交替通行，数码管显示直行通行倒计时，红绿黄灯显示包括人行道在内的道路交通状态。
;某一方向道路拥挤时，可以人工控制调节东西南北方向通行时间。
;紧急情况时，各路口交通灯显示红灯，数码管保持数据不变。


;工作寄存器及存储单元分配
;1.工作寄存器
;R2设置为定时器定时中断次数,R6、R7用于延时程序中的寄存器

;2.片内存储单元
;30H、31H作为两组数码管显示数据存储单元;32H、33H作为交通灯初始状态存储单元;40H、41H作为交通灯显示数据存储单元

;3.标志位
;00H：南北通行标志位 ; 01H：东西通行标志位;02H：紧急事件标志位   
;-----------------------------------
SNF   EQU  00H             ;;;南北通行标志位
EWF   EQU  01H             ;;;东西通行标志位
URF   EQU  02H             ;;;紧急事件标志位
ORG   0000H
LJMP  MAIN                 ;;;上电转主程序
ORG   000BH                ;;;定时中断入口
LJMP  DSZD                    
ORG   0003H                ;;;紧急中断入口
LJMP  URZD
ORG   0030H   
MAIN: LCALL INIT           ;;;调用初始化子程序
LOOP: LCALL DIS            ;;;循环执行显示子程序
      AJMP  LOOP
;///////////初始化程序
INIT: SETB   SNF              
      SETB   EWF           
      SETB   URF           
      MOV   R2,#20         ;;;定时器中断20次为1s
      MOV   TMOD,#01H      ;;;初始化定时器
      MOV   TL0,#0B0H
      MOV   TH0,#3CH
      SETB  EA             ;;;开定时中断与紧急中断
      SETB  ET0
      SETB  TR0
      SETB  EX0
      SETB  IT0            ;;;设置中断程控方式
      MOV   DPTR,#TAB      ;;;数值首地址放入DPTR中
      MOV   40H,#40        ;;;东南西北通行时间设置
      MOV   41H,#40
      MOV   30H,#40        ;;;通行时间初始化
      MOV   31H,#60
      MOV   P0,#4CH        ;;;初始化时南北通行并把交通灯状态分别放在32H和33H中
      MOV   32H,#4CH
      MOV   P2,#15H
      MOV   33H,#15H
      RET
;////////////显示子程序
DIS:  MOV   P3,#0DFH       ;;;选中南北方向的十位数码管
      MOV   A,30H          ;;;把显示数据送人数码管显示
      MOV   B,#10
      DIV   AB
      MOVC  A,@A+DPTR
      MOV   P1,A           ;;;
      LCALL D1MS
      MOV   P3,#0EFH       ;;;选中南北方向的个位数码管
      MOV   A,B            ;;;送入数码管显示
      MOVC  A,@A+DPTR      
      MOV   P1,A
      LCALL D1MS

      MOV   P3,#7FH        ;;;选中第东西方向的十位数码管
      MOV   A,31H          ;;;送入数码管显示
      MOV   B,#10
      DIV   AB
      MOVC  A,@A+DPTR
      MOV   P1,A
      LCALL D1MS
      MOV   P3,#0BFH       ;;;选中第东西方向的个位数码管
      MOV   A,B
      MOVC  A,@A+DPTR
      MOV   P1,A
      LCALL D1MS
      SETB  P3.0
      SETB  P3.1
      JNB   P3.0,DIS_S     ;;;查询是否第一个按键按下
      JNB   P3.1,DIS_E     ;;;查询是否第二个按键按下
      AJMP  DIS_R          ;;;没有键按下则返回
DIS_S:LCALL D5MS           ;;;按键去抖
      JNB   P3.0,DIS_SN
      AJMP  DIS_R   
DIS_SN:MOV   40H,#50       ;;;对通行时间从新分配，南北通行时间加长
       MOV   41H,#30
       AJMP  DIS_R
DIS_E:LCALL D5MS           ;;;按键去抖
      JNB   P3.1,DIS_EW 
      AJMP  DIS_R
DIS_EW:MOV   40H,#30       ;;;东西通行时间加长
       MOV   41H,#50
DIS_R:RET                  
;///////定时中断处理程序
DS_C: LJMP  DS_R           ;;;接力跳转
DSZD: PUSH  ACC            ;;;保护现场
      PUSH  PSW
      CLR   TR0            ;;;关定时器及中断标志位并重新赋值
      CLR   TF0
      MOV   TL0,#0B0H
      MOV   TH0,#3CH
      DJNZ  R2,DS_C        ;;;判断1m时间是否到达
      MOV   R2,#20         ;;;到达重新赋值
      DEC   30H            ;;;南北方向通行时间减一
      MOV   A,30H          ;;;把减一后的时间送入显示存储单元
;;;;;;;南北通行到达最后4秒时黄灯闪烁
DS_10:CJNE  A,#4,DS_11     ;;;如果通行时间剩余4秒
      JNB   SNF,DS_11      ;;;判断是否是南北通行
      MOV   P0,#8AH        
      MOV   32H, #8AH      ;;;把交通灯状态存入存储单元（后面类似）
DS_11:CJNE  A,#3,DS_12     ;;;不是剩余3秒，返回
      JNB   SNF,DS_12      ;;;不是南北通行时间，返回
      MOV   P0,#88H
      MOV   32H, #88H
DS_12:CJNE  A,#2,DS_13
      JNB   SNF,DS_13
      MOV   P0,#8AH
      MOV   32H, #8AH 
DS_13:CJNE  A,#1,DS_14
      JNB   SNF,DS_14
      MOV   P0,#88H
      MOV   32H, #88H
;------------------------
DS_14:JNZ   DS_NE          ;;;通行时间没有结束转向改变东西方向的数码管
      CPL   SNF            ;;;如果通行时间结束则对标志位取反
      JNB   SNF,DS_1       ;;;判断是否南北通行
      MOV   30H,40H        ;;;是，点亮相应的交通灯
      MOV   P0,#4CH
      MOV   32H,#4CH       ;;;存储交通灯状态
      MOV   P2,#15H
      MOV   33H, #15H      ;;;存储交通灯状态
DS_NE:DEC   31H            ;;;东西方向通行时间减一
      MOV   A,31H          ;;;把通行剩余时间送入显示存储单元
;;;;;;;;东西方向通行时间剩余4秒钟黄灯闪烁（程序注释与南北方向类似 略）
DS_20:CJNE  A,#4,DS_21    
      JB    EWF,DS_21
      MOV   P0,#51H
      MOV   32H, #51H
DS_21:CJNE  A,#3,DS_22
      JB    EWF,DS_22
      MOV   P0,#41H
      MOV   32H, #41H
DS_22:CJNE  A,#2,DS_23
      JB    EWF,DS_23
      MOV   P0,#51H
      MOV   32H, #51H
DS_23:CJNE  A,#1,DS_24
      JB    EWF,DS_24
      MOV   P0,#41H
      MOV   32H, #41H
;-----------------------------
DS_24:JNZ   DS_R             ;;;东西方向时间没有结束，返回
      CPL   EWF              ;;;对通行状态取反
      JNB   EWF,DS_2         ;;;东西方向通行时间到来，跳转
      MOV   31H,#80          ;;;东西方向通行结束，重新显示时间
      MOV   P0,#89H          ;;;点亮相应的交通灯
      MOV   32H, #89H
      MOV   P2,#29H
      MOV   33H, #29H
      AJMP  DS_R     
DS_1: MOV   30H,#80          ;;;南北通行时间结束，重新对显示存储单元赋值     
      MOV   P0,#89H          ;;;执行转弯状态1
      MOV   32H, #89H
      MOV   P2,#26H
      MOV   33H, #26H
      AJMP  DS_NE            
DS_2: MOV   31H,41H         ;;;东西方向开始通行，赋值予显示存储单元
      MOV   P0,#61H         ;;;点亮相应的交通灯
      MOV   32H, #61H
      MOV   P2,#15H
      MOV   33H, #15H
DS_R: SETB  TR0 
      POP   PSW             ;;;恢复现场
      POP   ACC
      RETI
;/////////////紧急中断处理程序
URZD: PUSH  ACC             ;;;保护现场
      PUSH  PSW
      CLR   IE0             ;;;清除中断标志位
      CLR   TR0             ;;;关定时器
      CPL   URF             ;;;紧急事件标志位
      JB    URF,UR_CON      ;;;紧急结束；跳转
      MOV   P0,#49H         ;;;各路口灯全显示红灯亮
      MOV   P2,#15H
      AJMP  UR_R
UR_CON:SETB  TR0            ;;;恢复正常交通
      MOV   A,32H
      MOV   P0,A
      MOV   A,33H
      MOV   P2,A
UR_R: POP   PSW             ;;;恢复现场
      POP   ACC
      RETI      
;////////////查表指令0,1,2,3,4,5,6,7,8,9
TAB:  DB  3FH,  06H,  5BH,  4FH,  66H,  6DH
      DB  7DH,  07H,  7FH,  6FH

;//////////延时5ms与1ms
D5MS:  MOV    R7,#5
D1MS:  MOV    R7,#10
       MOV    R6,#50 
L1:    DJNZ   R6,$
       DJNZ   R7,L1
       RET
       END

