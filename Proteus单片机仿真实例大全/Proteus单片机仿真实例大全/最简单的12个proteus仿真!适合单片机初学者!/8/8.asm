		ORG 0
START:		MOV R1,#00H		//初始化R7为0，表示从0开始计数
		MOV A,R1		//
		CPL A			//取反指令
		MOV P1,A		//送出P1端口由发光二极管显示
REL:		JNB P3.7,REL		//判断SP1是否按下
		LCALL DELAY10MS		//若按下，则延时10ms左右
		JNB P3.7,REL		//再判断SP1是否真得按下
		INC R7			//若真得按下，则进行按键处理，使
		MOV A,R7		//计数内容加1，并送出P1端口由
		CPL A			//发光二极管显示
		MOV P1,A		//
		JNB P3.7,$		//等待SP1释放
		SJMP REL		//继续对K1按键扫描
DELAY10MS:	MOV R6,#20				//延时10ms子程序
L1:		MOV R7,#248
		DJNZ R7,$
		DJNZ R6,L1
		RET
		END
