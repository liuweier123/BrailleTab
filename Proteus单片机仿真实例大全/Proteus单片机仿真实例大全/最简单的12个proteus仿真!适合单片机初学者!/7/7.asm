		ORG 0
START:		MOV R1,#00H
NEXT:		MOV A,R1
		MOV DPTR,#TABLE
		MOVC A,@A+DPTR
		MOV P0,A
		LCALL DELAY
		INC R1
		CJNE R1,#10,NEXT
		LJMP START
DELAY:		MOV R5,#20
D2:		MOV R6,#20
D1:		MOV R7,#248
		DJNZ R7,$
		DJNZ R6,D1
		DJNZ R5,D2
		RET
TABLE:		DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H,7FH,6FH
