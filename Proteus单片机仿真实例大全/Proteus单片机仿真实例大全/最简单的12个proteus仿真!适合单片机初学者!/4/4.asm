			ORG 0
START:			MOV R2,#8
			MOV A,#0FEH
			SETB C
LOOP:			MOV P1,A
			LCALL DELAY
			RLC A
			DJNZ R2,LOOP
			MOV R2,#8
LOOP1:			MOV P1,A
			LCALL DELAY			
			RRC A
			DJNZ R2,LOOP1
			LJMP START
DELAY:			MOV R5,#20			;
D1:			MOV R6,#20
D2:			MOV R7,#248
			DJNZ R7,$
			DJNZ R6,D2
			DJNZ R5,D1
			RET
