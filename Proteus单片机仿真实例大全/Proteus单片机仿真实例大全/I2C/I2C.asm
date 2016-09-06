ACK		BIT		10H			;应答标志位
SLA		DATA	50H			;器件地址字
SUBA	DATA	51H			;器件子地址
NUMBYTE	DATA	52H			;读/写字节数
SDA		BIT		P1.5
SCL		BIT		P1.4		;I2C总线定义
MTD		EQU		30H			;发送数据缓存区首地址(30H-3FH)
MRD		EQU		40H			;接收数据缓存区首地址(40H-4FH)
		AJMP	MAIN
		ORG		80H
;*********************************************************************
;名称:IWRNBYTE
;描述:向器件指定子地址写N个数据
;入口参数:器件地址字SLA,子地址SUBA,发送数据缓冲区MTD,发送字节数NUMBYTE
;*********************************************************************
IWRNBYTE:
		MOV		R3,NUMBYTE
		LCALL	START		;启动总线
		MOV		A,SLA
		LCALL	WRBYTE		;发送器件地址字
		LCALL	CACK
		JNB		ACK,RETWRN	;无应答则退出
		MOV		A,SUBA		;指定子地址
		LCALL	WRBYTE
		LCALL	CACK
		MOV		R1,#MTD
WRDA:	MOV		A,@R1
		LCALL	WRBYTE		;开始写入数据
		LCALL	CACK
		JNB		ACK,IWRNBYTE
		INC		R1
		DJNZ	R3,WRDA		;判断是否写完
RETWRN:	LCALL	STOP
		RET
;*********************************************************************
;名称:IRDNBYTE
;描述:从器件指定子地址读取N个数据
;入口参数:器件地址字SLA,子地址SUBA,接收数据缓存区MRD,接收字节数NUMBYTE
;*********************************************************************
IRDNBYTE:
		MOV		R3,NUMBYTE
		LCALL	START
		MOV		A,SLA
		LCALL	WRBYTE		;发送器件地址字
		LCALL	CACK
		JNB		ACK,RETRDN
		MOV		A,SUBA		;指定子地址
		LCALL	WRBYTE
		LCALL	CACK
		LCALL	START		;重新启动总线
		MOV		A,SLA
		INC		A			;准备进行读操作
		LCALL	WRBYTE
		LCALL	CACK
		JNB		ACK,IRDNBYTE
		MOV		R1,#MRD
RON1:	LCALL	RDBYTE		;读操作开始
		MOV		@R1,A
		DJNZ	R3,SACK
		LCALL	MNACK		;最后一字节发非应答位
RETRDN:	LCALL	STOP
		RET
SACK:	LCALL	MACK
		INC		R1
		SJMP	RON1	
;*********************************************************************
;名称:STRRT
;描述:启动I2C总线子程序—发送I2C总线起始条件
;*********************************************************************
START:	SETB	SDA			;发送起始条件数据信号
		NOP					;起始条件建立时间大于4.7us
   		SETB	SCL			;发送起始条件的时钟信号
		NOP
		NOP
		NOP
		NOP
		NOP					;起始条件锁定时间大于4.7us
   		CLR  	SDA			;发送起始信号
		NOP
		NOP
		NOP
		NOP					;起始条件锁定时间大于4.7us
   		CLR		SCL			;钳住I2C总线,准备发送或接收数据
   		NOP
   		RET
;*********************************************************************
;名称:STOP
;描述:停止I2C总线子程序—发送I2C总线停止条件
;*********************************************************************
STOP:	CLR  	SDA 		;发送停止条件的数据信号
		NOP			   	
		NOP
		SETB  	SCL 		;发送停止条件的时钟信号
		NOP
		NOP
		NOP
		NOP
		NOP					;起始条件建立时间大于4.7us
		SETB 	SDA 		;发送I2C总线停止信号
		NOP
		NOP
		NOP
		NOP
		NOP					;延迟时间大于4.7us
		RET
;*********************************************************************
;名称:MACK
;描述:发送应答信号子程序
;*********************************************************************
MACK:	CLR		SDA			;将SDA置0
		NOP
		NOP
		SETB	SCL
		NOP
		NOP
		NOP
		NOP
		NOP					;保持数据时间,大于4.7us
		CLR		SCL
		NOP
		NOP
		RET
;*********************************************************************
;名称:MNACK
;描述:发送非应答信号子程序
;*********************************************************************
MNACK:	SETB	SDA			;将SDA置1
		NOP
		NOP
		SETB	SCL
		NOP
		NOP
		NOP
		NOP
		NOP
		CLR		SCL			;保持数据时间,大于4.7us
		NOP
		NOP
		RET
;*********************************************************************
;名称:CACK
;描述:检查应答位子程序,返回值:ACK=1时表示有应答
;*********************************************************************
CACK:	SETB	SDA
		NOP
		NOP
		SETB	SCL
		CLR		ACK
		NOP
		NOP
		MOV		C,SDA
		JC		CEND
		SETB	ACK			;判断应答位
CEND:	NOP
		CLR		SCL
		NOP
		RET
;*********************************************************************	
;名称:WRBYTE
;描述:发送字节子程序,字节数据放入ACC
;*********************************************************************
WRBYTE:	MOV		R0,#08H
WLP:	RLC		A			;取数据位
		JC		WRI
		SJMP	WRO			;判断数据位
WLP1:	DJNZ	R0,WLP
		NOP
		RET
WRI:	SETB	SDA			;发送1
		NOP
		SETB	SCL
		NOP
		NOP
		NOP
		NOP
		NOP
		CLR		SCL
		SJMP	WLP1
WRO:	CLR		SDA			;发送0
		NOP
		SETB	SCL
		NOP
		NOP
		NOP
		NOP
		NOP
		CLR		SCL
		SJMP	WLP1
;*********************************************************************
;名称:RDBYTE
;描述:读取字节子程序,读出的数据存放在ACC
;*********************************************************************
RDBYTE:	MOV		R0,#08H
RLP:	SETB	SDA
		NOP
		SETB	SCL			;时钟线为高,接收数据位
		NOP
		NOP
		MOV		C,SDA		;读取数据位
		MOV		A,R2
		CLR		SCL			;将SCL拉低,时间大于4.7us
		RLC		A			;进行数据位的处理
		MOV		R2,A
		NOP
		NOP
		NOP
		DJNZ	R0,RLP		;未够8位,继续读入
		RET
MAIN:	MOV		R4,#0F0H	;延时,等待其它芯片复位完成
		DJNZ	R4,$
;发送数据缓存区初始化,将16个连续字节分别赋值为00H到0FH		
		MOV		A,#0
		MOV		R0,#30H
S1:		MOV		@R0,A
		INC		R0
		INC		A
		CJNE	R0,#40H,S1
;向24C01C中写数据,数据存放在24C01C中30H开始的16个字节中
		MOV		SLA,#0A0H	;24C01C地址字,写操作
		MOV		SUBA,#30H	;目标地址
		MOV		NUMBYTE,#16	;字节数
		LCALL	IWRNBYTE	;写数据
DELAY:	MOV		R5,#20
D1:		MOV		R6,#248
D2:		MOV		R7,#248
		DJNZ	R7,$
		DJNZ	R6,D2
		DJNZ	R5,D1
;从24C01C中读数据,数据送AT89C51中40H开始的16个字节中
		MOV		SLA,#0A0H	;24C01C地址字,伪写入操作
		MOV		SUBA,#30H	;目标地址
		MOV		NUMBYTE,#16	;字节数
		LCALL	IRDNBYTE	;写数据
		END