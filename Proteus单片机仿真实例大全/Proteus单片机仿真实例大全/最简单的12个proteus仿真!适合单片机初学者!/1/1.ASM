                 ORG 0
START:           CLR P1.0
                 LCALL DELAY
                 SETB P1.0
                 LCALL DELAY
                 LJMP START
DELAY:           MOV R5,#20
D1:              MOV R6,#20
D2:              MOV R7,248
                 DJNZ R7,$
                 DJNZ R6,D2
                 DJNZ R5,D1
                 RET
                 END

