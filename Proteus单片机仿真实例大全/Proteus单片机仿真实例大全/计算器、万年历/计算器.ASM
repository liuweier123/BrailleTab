  ;;;;;;;;;;;;;;;;;;;;;;;;;;;端口定义;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

     CSA              EQU p2.4
     CSB              EQU p2.3
     rs               EQU P2.2
     rw               EQU P2.1
     E                EQU P2.0
;;;;;;;;;;;;;;;;;;;;;;;;;;;单元定义;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

     COM              EQU 21H
     DAT              EQU 22H
     column           EQU 23H
     pagef            EQU 24h
     cpage            EQU 25H
     ccolumn          EQU 26H

     codes            EQU 27h
     column2          EQU 28H
     pagef2           equ 29h
     cpage2           EQU 2aH
     ccolumn2         EQU 2bH
     column3          EQU 2eH
     pagef3           equ 2fh
     cpage3           EQU 30H
     ccolumn3         EQU 31H
     column4          EQU 32H
     pagef4           equ 33h
     cpage4           EQU 34H
     ccolumn4         EQU 35H
     column5          EQU 36H
     pagef5           equ 37h
     cpage5           EQU 38H
     ccolumn5         EQU 39H
ORG 0
LJMP START
START:MOV SP,#60H
LCALL INT              ;调用初始化子程序
START1:LCALL CLEAR            ;调用清屏子程序
;*********************************固定字符显示
mov column3,#0
mov pagef3,#0
mov codes,#0
lcall writeleft2
mov column3,#0
mov pagef3,#4
mov codes,#2
lcall writeleft2
mov column3,#16
mov pagef3,#4
mov codes,#3
lcall writeleft2
mov column3,#16
mov pagef3,#0
mov codes,#1
lcall writeleft2
mov column,#32
mov pagef,#0
mov codes,#1
lcall writeleft
mov column3,#0
mov pagef3,#2
mov codes,#0
lcall writeleft2
mov column,#40
mov pagef,#2
mov codes,#15
lcall writeleft
mov column,#40
mov pagef,#0
mov codes,#15
lcall writeleft
mov column3,#16
mov pagef3,#2
mov codes,#1
lcall writeleft2
mov column,#32
mov pagef,#2
mov codes,#2
lcall writeleft
MOV R0,#0
MOV R1,#255
QQQ:MOV @R0,#0
INC R0
DJNZ R1,QQQ
;************************************固定字符显示结束,键盘扫描开始
dd:mov r0,#0f7h
mov r1,#0
cc:mov a,r0
mov p1,a
mov a,p1
mov r2,a
setb c
mov r3,#4
bb:rlc a
jnc aa
ee:inc r1
djnz r3,bb
mov a,r0
setb c
rrc a
mov r0,a
jc cc
ljmp dd
KAOO:LJMP KAO
BBB2:LJMP BB2
aa:lcall mm
mov a,p1
xrl a,r2
jnz ee
ff:mov a,p1
xrl a,r2
jz ff
MOV A,51H
CJNE A,#1,BBB2        ;键盘扫描结束，加法运算开始
MOV A,R1
CJNE A,#14,KAOO
MOV 47H,R1
LCALL A31
MOV A,40H
ADD A,60H
MOV B,#10
DIV AB
MOV 40H,B
ADD A,41H
ADD A,71H
MOV B,#10
DIV AB
MOV 41H,B
ADD A,42H
ADD A,72H
MOV B,#10
DIV AB
MOV 42H,B
ADD A,44H
ADD A,74H
MOV B,#10
DIV AB
MOV 44H,B
ADD A,45H
ADD A,75H
MOV B,#10
DIV AB
MOV 45H,B
ADD A,46H
ADD A,76H
MOV B,#10
DIV AB
MOV 46H,B
ADD A,48H
ADD A,78H
MOV B,#10
DIV AB
MOV 48H,B
ADD A,49H
ADD A,79H
MOV B,#10
DIV AB
MOV 49H,B
MOV 0CEH,A
CJNE A,#0,CC0
MOV A,49H
CJNE A,#0,CC1
MOV A,48H
CJNE A,#0,CC2
MOV A,46H
CJNE A,#0,CC3
MOV A,45H
CJNE A,#0,CC4
MOV A,44H
CJNE A,#0,CC5
MOV A,42H
CJNE A,#0,CC6
MOV A,41H
CJNE A,#0,CC7
MOV A,40H
CJNE A,#0,CC8
CC0:LCALL A08
CC1:LCALL A07
CC2:LCALL A06
CC3:LCALL A05
CC4:LCALL A04
CC5:LCALL A03
CC6:LCALL A02
CC7:LCALL A01
CC8:LCALL A00
LJMP DD
KAO:CJNE A,#15,KAO1
LJMP START1
KAO1:MOV A,50H
CJNE A,#0,A1A1
MOV 60H,R1
LCALL A8
INC 50H
ljmp dd
A1A1:CJNE A,#1,A1A2
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
INC 50H
LJMP DD
A1A2:CJNE A,#2,A1A3
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
INC 50H
LJMP DD
A1A3:CJNE A,#3,A1A5
MOV 74H,72H
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
LCALL A11
INC 50H
LJMP DD
A1A5:CJNE A,#4,A1A6
MOV 75H,74H
MOV 74H,72H
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
LCALL A11
LCALL A12
INC 50H
LJMP DD
A1A6:CJNE A,#5,A1A7
MOV 76H,75H
MOV 75H,74H
MOV 74H,72H
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
LCALL A11
LCALL A12
LCALL A13
INC 50H
LJMP DD
A1A7:CJNE A,#6,A1A9
MOV 78H,76H
MOV 76H,75H
MOV 75H,74H
MOV 74H,72H
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
LCALL A11
LCALL A12
LCALL A13
LCALL A14
INC 50H
LJMP DD
A1A9:CJNE A,#7,A1A10
MOV 79H,78H
MOV 78H,76H
MOV 76H,75H
MOV 75H,74H
MOV 74H,72H
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
LCALL A11
LCALL A12
LCALL A13
LCALL A14
LCALL A15
INC 50H
A1A10:LJMP DD
BBB3:LJMP BB33
KAOO2:LJMP KAO2
BB2:CJNE A,#2,BBB3    ;加法运算结束，减法运算开始
MOV A,R1
CJNE A,#14,KAOO2
MOV 47H,R1
LCALL A31
MOV A,49H
CJNE A,79H,NEXT0
mov A,48H
CJNE A,78H,NEXT1
mov A,46H
CJNE A,76H,NEXT2
mov A,45H
CJNE A,75H,NEXT3
mov A,44H
CJNE A,74H,NEXT4
mov A,42H
CJNE A,72H,NEXT5
mov A,41H
CJNE A,71H,NEXT6
mov A,40H
CJNE A,60H,NEXT7
OO:LJMP MMM
NEXT0:CLR C
SUBB A,79H
JNC OO
LJMP LAJI
NEXT1:CLR C
SUBB A,78H
JNC OO
LJMP LAJI
NEXT2:CLR C
SUBB A,76H
JNC OO
LJMP LAJI
NEXT3:CLR C
SUBB A,75H
JNC OO
LJMP LAJI
NEXT4:CLR C
SUBB A,74H
JNC OO
LJMP LAJI
NEXT5:CLR C
SUBB A,72H
JNC OO
LJMP LAJI
NEXT6:CLR C
SUBB A,71H
JNC OO
LJMP LAJI
NEXT7:CLR C
SUBB A,60H
JNC OO
LAJI:LCALL A32
DEC 79H
MOV A,60H
ADD A,#10
MOV 60H,A
MOV A,71H
ADD A,#9
MOV 71H,A
MOV A,72H
ADD A,#9
MOV 72H,A
MOV A,74H
ADD A,#9
MOV 74H,A
MOV A,75H
ADD A,#9
MOV 75H,A
MOV A,76H
ADD A,#9
MOV 76H,A
MOV A,78H
ADD A,#9
MOV 78H,A
CLR C
MOV A,60H
SUBB A,40H
MOV B,#10
DIV AB
MOV 40H,B
ADD A,71H
SUBB A,41H
MOV B,#10
DIV AB
MOV 41H,B
ADD A,72H
SUBB A,42H
MOV B,#10
DIV AB
MOV 42H,B
ADD A,74H
SUBB A,44H
MOV B,#10
DIV AB
MOV 44H,B
ADD A,75H
SUBB A,45H
MOV B,#10
DIV AB
MOV 45H,B
ADD A,76H
SUBB A,46H
MOV B,#10
DIV AB
MOV 46H,B
ADD A,78H
SUBB A,48H
MOV B,#10
DIV AB
MOV 48H,B
ADD A,79H
CJNE A,#0,xxx1
MOV A,48H
CJNE A,#0,C00C1
MOV A,46H
CJNE A,#0,C00C2
MOV A,45H
CJNE A,#0,C00C3
MOV A,44H
CJNE A,#0,C00C4
MOV A,42H
CJNE A,#0,C00C5
MOV A,41H
CJNE A,#0,C00C6
MOV A,40H
CJNE A,#0,C00C7
XxX1:SUBB A,49H
MOV B,#10
DIV AB
MOV 49H,B
MOV A,49H
CJNE A,#0,C00C0
LJMP C00C1
C00C0:LCALL A07
C00C1:LCALL A06
C00C2:LCALL A05
C00C3:LCALL A04
C00C4:LCALL A03
C00C5:LCALL A02
C00C6:LCALL A01
C00C7:LCALL A00
LJMP DD
MMM:DEC 49H
MOV A,40H
ADD A,#10
MOV 40H,A
MOV A,41H
ADD A,#9
MOV 41H,A
MOV A,42H
ADD A,#9
MOV 42H,A
MOV A,44H
ADD A,#9
MOV 44H,A
MOV A,45H
ADD A,#9
MOV 45H,A
MOV A,46H
ADD A,#9
MOV 46H,A
MOV A,48H
ADD A,#9
MOV 48H,A
CLR C
MOV A,40H
SUBB A,60H
MOV B,#10
DIV AB
MOV 40H,B
ADD A,41H
SUBB A,71H
MOV B,#10
DIV AB
MOV 41H,B
ADD A,42H
SUBB A,72H
MOV B,#10
DIV AB
MOV 42H,B
ADD A,44H
SUBB A,74H
MOV B,#10
DIV AB
MOV 44H,B
ADD A,45H
SUBB A,75H
MOV B,#10
DIV AB
MOV 45H,B
ADD A,46H
SUBB A,76H
MOV B,#10
DIV AB
MOV 46H,B
ADD A,48H
SUBB A,78H
MOV B,#10
DIV AB
MOV 48H,B
ADD A,49H
CJNE A,#0,xx1
MOV A,48H
CJNE A,#0,C0C1
MOV A,46H
CJNE A,#0,C0C2
MOV A,45H
CJNE A,#0,C0C3
MOV A,44H
CJNE A,#0,C0C4
MOV A,42H
CJNE A,#0,C0C5
MOV A,41H
CJNE A,#0,C0C6
MOV A,40H
CJNE A,#0,C0C7
XX1:SUBB A,79H
MOV B,#10
DIV AB
MOV 49H,B
MOV A,49H
CJNE A,#0,C0C0
LJMP C0C1
C0C0:LCALL A07
C0C1:LCALL A06
C0C2:LCALL A05
C0C3:LCALL A04
C0C4:LCALL A03
C0C5:LCALL A02
C0C6:LCALL A01
C0C7:LCALL A00
LJMP DD
KAO2:CJNE A,#15,KAOO1
LJMP START1
KAOO1:
MOV A,50H
CJNE A,#0,A11A1
MOV 60H,R1
LCALL A8
INC 50H
ljmp dd
A11A1:CJNE A,#1,A11A2
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
INC 50H
LJMP DD
A11A2:CJNE A,#2,A11A3
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
INC 50H
LJMP DD
A11A3:CJNE A,#3,A11A5
MOV 74H,72H
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
LCALL A11
INC 50H
LJMP DD
A11A5:CJNE A,#4,A11A6
MOV 75H,74H
MOV 74H,72H
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
LCALL A11
LCALL A12
INC 50H
LJMP DD
A11A6:CJNE A,#5,A11A7
MOV 76H,75H
MOV 75H,74H
MOV 74H,72H
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
LCALL A11
LCALL A12
LCALL A13
INC 50H
LJMP DD
A11A7:CJNE A,#6,A11A9
MOV 78H,76H
MOV 76H,75H
MOV 75H,74H
MOV 74H,72H
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
LCALL A11
LCALL A12
LCALL A13
LCALL A14
INC 50H
LJMP DD
A11A9:CJNE A,#7,A11A10
MOV 79H,78H
MOV 78H,76H
MOV 76H,75H
MOV 75H,74H
MOV 74H,72H
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
LCALL A11
LCALL A12
LCALL A13
LCALL A14
LCALL A15
INC 50H
A11A10:LJMP DD
BBBB2:LJMP YY1
KAOOO:LJMP KAO3
BB33:CJNE A,#3,BBBB2        ;减法运算结束，乘法运算开始
MOV A,R1
CJNE A,#14,KAOOO
MOV 47H,R1
LCALL A31
MOV B,40H
MOV A,60H
MUL AB
MOV B,#10
DIV AB
MOV 3AH,B
MOV 91H,A
MOV A,60H
MOV B,41H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 3BH,B
MOV 91H,A
MOV A,60H
MOV B,42H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 3CH,B
MOV 91H,A
MOV A,60H
MOV B,44H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 3DH,B
MOV 91H,A
MOV A,60H
MOV B,45H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 3EH,B
MOV 91H,A
MOV A,60H
MOV B,46H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 3FH,B
MOV 91H,A
MOV A,60H
MOV B,48H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 52H,B
MOV 91H,A
MOV A,60H
MOV B,49H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 53H,B
MOV 0E1H,A
;**************************第一次乘法结束，第二次乘法运算开始
MOV A,71H
MOV B,40H
MUL AB
MOV B,#10
DIV AB
MOV 58H,B
MOV 91H,A
MOV A,71H
MOV B,41H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 59H,B
MOV 91H,A
MOV A,71H
MOV B,42H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 5AH,B
MOV 91H,A
MOV A,71H
MOV B,44H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 5BH,B
MOV 91H,A
MOV A,71H
MOV B,45H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 5CH,B
MOV 91H,A
MOV A,71H
MOV B,46H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 5DH,B
MOV 91H,A
MOV A,71H
MOV B,48H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 5EH,B
MOV 91H,A
MOV A,71H
MOV B,49H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 5FH,B
MOV 0E2H,A
;*********************************第二次乘法结束，第三次乘法运算开始
MOV A,72H
MOV B,40H
MUL AB
MOV B,#10
DIV AB
MOV 54H,B
MOV 91H,A
MOV A,72H
MOV B,41H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 61H,B
MOV 91H,A
MOV A,72H
MOV B,42H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 62H,B
MOV 91H,A
MOV A,72H
MOV B,44H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 63H,B
MOV 91H,A
MOV A,72H
MOV B,45H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 64H,B
MOV 91H,A
MOV A,72H
MOV B,46H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 65H,B
MOV 91H,A
MOV A,72H
MOV B,48H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 66H,B
MOV 91H,A
MOV A,72H
MOV B,49H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 67H,B
MOV 0E3H,A
;*********************************第三次乘法结束，第四次乘法运算开始
MOV A,74H
MOV B,40H
MUL AB
MOV B,#10
DIV AB
MOV 55H,B
MOV 91H,A
MOV A,74H
MOV B,41H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 56H,B
MOV 91H,A
MOV A,74H
MOV B,42H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 57H,B
MOV 91H,A
MOV A,74H
MOV B,44H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 68H,B
MOV 91H,A
MOV A,74H
MOV B,45H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 6AH,B
MOV 91H,A
MOV A,74H
MOV B,46H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 6BH,B
MOV 91H,A
MOV A,74H
MOV B,48H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 6CH,B
MOV 91H,A
MOV A,74H
MOV B,49H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 6DH,B
MOV 0E4H,A
;****************************第四次乘法结束，第五次乘法运算开始
MOV A,75H
MOV B,40H
MUL AB
MOV B,#10
DIV AB
MOV 6EH,B
MOV 91H,A
MOV A,75H
MOV B,41H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 7AH,B
MOV 91H,A
MOV A,75H
MOV B,42H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 7BH,B
MOV 91H,A
MOV A,75H
MOV B,44H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 7CH,B
MOV 91H,A
MOV A,75H
MOV B,45H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 7DH,B
MOV 91H,A
MOV A,75H
MOV B,46H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 7EH,B
MOV 91H,A
MOV A,75H
MOV B,48H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 7FH,B
MOV 91H,A
MOV A,75H
MOV B,49H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 92H,B
MOV 0E5H,A
;**************************************第五次乘法结束，第六次乘法运算开始
MOV A,76H
MOV B,40H
MUL AB
MOV B,#10
DIV AB
MOV 93H,B
MOV 91H,A
MOV A,76H
MOV B,41H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 94H,B
MOV 91H,A
MOV A,76H
MOV B,42H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 95H,B
MOV 91H,A
MOV A,76H
MOV B,44H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 96H,B
MOV 91H,A
MOV A,76H
MOV B,45H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 97H,B
MOV 91H,A
MOV A,76H
MOV B,46H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 9AH,B
MOV 91H,A
MOV A,76H
MOV B,48H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 9BH,B
MOV 91H,A
MOV A,76H
MOV B,49H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 9CH,B
MOV 0E6H,A
;***********************************第六次乘法结束，第七次乘法运算开始
MOV A,78H
MOV B,40H
MUL AB
MOV B,#10
DIV AB
MOV 9DH,B
MOV 91H,A
MOV A,78H
MOV B,41H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 9EH,B
MOV 91H,A
MOV A,78H
MOV B,42H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 9FH,B
MOV 91H,A
MOV A,78H
MOV B,44H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 0C0H,B
MOV 91H,A
MOV A,78H
MOV B,45H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 0C1H,B
MOV 91H,A
MOV A,78H
MOV B,46H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 0C2H,B
MOV 91H,A
MOV A,78H
MOV B,48H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 0C3H,B
MOV 91H,A
MOV A,78H
MOV B,49H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 0C4H,B
MOV 0E7H,A
;***********************************第七次乘法结束，第八次乘法运算开始
MOV A,79H
MOV B,40H
MUL AB
MOV B,#10
DIV AB
MOV 0C5H,B
MOV 91H,A
MOV A,79H
MOV B,41H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 0C6H,B
MOV 91H,A
MOV A,79H
MOV B,42H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 0C7H,B
MOV 91H,A
MOV A,79H
MOV B,44H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 0C8H,B
MOV 91H,A
MOV A,79H
MOV B,45H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 0C9H,B
MOV 91H,A
MOV A,79H
MOV B,46H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 0CAH,B
MOV 91H,A
MOV A,79H
MOV B,48H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 0CBH,B
MOV 91H,A
MOV A,79H
MOV B,49H
MUL AB
MOV B,#10
ADD A,91H
DIV AB
MOV 0CCH,B
MOV 0E8H,A
;***************************第八次乘法结束，全加求和开始
MOV 40H,3AH
MOV A,3BH
ADD A,58H
MOV B,#10
DIV AB
MOV 91H,A
MOV 41H,B
MOV A,3CH
ADD A,59H
ADD A,54H
ADD A,91H
MOV B,#10
DIV AB
MOV 91H,A
MOV 42H,B
MOV A,3DH
ADD A,5AH
ADD A,61H
ADD A,55H
ADD A,91H
MOV B,#10
DIV AB
MOV 91H,A
MOV 44H,B
MOV A,3EH
ADD A,5BH
ADD A,62H
ADD A,56H
ADD A,6EH
ADD A,91H
MOV B,#10
DIV AB
MOV 91H,A
MOV 45H,B
MOV A,3FH
ADD A,5CH
ADD A,63H
ADD A,57H
ADD A,7AH
ADD A,93H
ADD A,91H
MOV B,#10
DIV AB
MOV 91H,A
MOV 46H,B
MOV A,52H
ADD A,5DH
ADD A,64H
ADD A,68H
ADD A,7BH
ADD A,94H
ADD A,9DH
ADD A,91H
MOV B,#10
DIV AB
MOV 91H,A
MOV 48H,B
MOV A,53H
ADD A,5EH
ADD A,65H
ADD A,6AH
ADD A,7CH
ADD A,95H
ADD A,9EH
ADD A,0C5H
ADD A,91H
MOV B,#10
DIV AB
MOV 91H,A
MOV 49H,B
MOV A,5FH
ADD A,66H
ADD A,6BH
ADD A,7DH
ADD A,96H
ADD A,9FH
ADD A,0C6H
ADD A,91H
ADD A,0E1H
MOV B,#10
DIV AB
MOV 91H,A
MOV 4AH,B
MOV A,67H
ADD A,6CH
ADD A,7EH
ADD A,97H
ADD A,0C0H
ADD A,0C7H
ADD A,91H
ADD A,0E2H
MOV B,#10
DIV AB
MOV 91H,A
MOV 4BH,B
MOV A,6DH
ADD A,7FH
ADD A,9AH
ADD A,0C1H
ADD A,0C8H
ADD A,91H
ADD A,0E3H
MOV B,#10
DIV AB
MOV 91H,A
MOV 4CH,B
MOV A,92H
ADD A,9BH
ADD A,0C2H
ADD A,0C9H
ADD A,91H
ADD A,0E4H
MOV B,#10
DIV AB
MOV 91H,A
MOV 4DH,B
MOV A,9CH
ADD A,0C3H
ADD A,0CAH
ADD A,91H
ADD A,0E5H
MOV B,#10
DIV AB
MOV 91H,A
MOV 4EH,B
MOV A,0C4H
ADD A,0CBH
ADD A,91H
ADD A,0E6H
MOV B,#10
DIV AB
MOV 91H,A
MOV 4FH,B
MOV A,0CCH
ADD A,91H
ADD A,0E7H
MOV B,#10
DIV AB
MOV 91H,A
MOV 6FH,B
MOV A,91H
ADD A,0E8H
MOV 69H,A
;********************************全加求和结束,消零程序开始
MOV A,69H
CJNE A,#0,DD0
MOV A,6FH
CJNE A,#0,DD1
MOV A,4FH
CJNE A,#0,DD2
MOV A,4EH
CJNE A,#0,DD3
MOV A,4DH
CJNE A,#0,DD4
MOV A,4CH
CJNE A,#0,DD5
MOV A,4BH
CJNE A,#0,DD6
MOV A,4AH
CJNE A,#0,DD7
MOV A,49H
CJNE A,#0,DD8
MOV A,48H
CJNE A,#0,DD9
MOV A,46H
CJNE A,#0,DD10
MOV A,45H
CJNE A,#0,DD11
MOV A,44H
CJNE A,#0,DD12
MOV A,42H
CJNE A,#0,DD13
MOV A,41H
CJNE A,#0,DD14
MOV A,40H
CJNE A,#0,DD15
LJMP DD15
DD0:LCALL A0020
DD1:LCALL A0014
DD2:LCALL A0013
DD3:LCALL A0012
DD4:LCALL A0011
DD5:LCALL A0010
DD6:LCALL A009
DD7:LCALL A008
DD8:LCALL A007
DD9:LCALL A006
DD10:LCALL A005
DD11:LCALL A004
DD12:LCALL A003
DD13:LCALL A002
DD14:LCALL A001
DD15:LCALL A000
LJMP DD
KAO3:CJNE A,#15,KA0OO1
LJMP START1
KA0OO1:
MOV A,50H
CJNE A,#0,A011A1
MOV 60H,R1
LCALL A8
INC 50H
ljmp dd
A011A1:CJNE A,#1,A011A2
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
INC 50H
LJMP DD
A011A2:CJNE A,#2,A011A3
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
INC 50H
LJMP DD
A011A3:CJNE A,#3,A011A5
MOV 74H,72H
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
LCALL A11
INC 50H
LJMP DD
A011A5:CJNE A,#4,A011A6
MOV 75H,74H
MOV 74H,72H
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
LCALL A11
LCALL A12
INC 50H
LJMP DD
A011A6:CJNE A,#5,A011A7
MOV 76H,75H
MOV 75H,74H
MOV 74H,72H
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
LCALL A11
LCALL A12
LCALL A13
INC 50H
LJMP DD
A011A7:CJNE A,#6,A011A9
MOV 78H,76H
MOV 76H,75H
MOV 75H,74H
MOV 74H,72H
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
LCALL A11
LCALL A12
LCALL A13
LCALL A14
INC 50H
LJMP DD
A011A9:CJNE A,#7,A011A10
MOV 79H,78H
MOV 78H,76H
MOV 76H,75H
MOV 75H,74H
MOV 74H,72H
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
LCALL A11
LCALL A12
LCALL A13
LCALL A14
LCALL A15
INC 50H
A011A10:LJMP DD
BBBB3:LJMP BB3
KAOOO8:LJMP KAO4
YY1:CJNE A,#4,BBBB3        ;乘法运算结束，除法运算开始
MOV A,R1
CJNE A,#14,KAOOO8
MOV 47H,R1
LCALL A31
MOV A,49H
CJNE A,60H,HH
LJMP HHH
HH:CLR C
SUBB A,60H
JNC HHH
MOV A,49H
MOV B,#10
LJMP HHH1
HHH:MOV A,49H
MOV B,60H
DIV AB
MOV 69H,A
MOV A,#10
HHH1:MUL AB
ADD A,48H
MOV B,60H
DIV AB
MOV 6FH,A
MOV A,#10
MUL AB
ADD A,46H
MOV B,60H
DIV AB
MOV 4FH,A
MOV A,#10
MUL AB
ADD A,45H
MOV B,60H
DIV AB
MOV 4EH,A
MOV A,#10
MUL AB
ADD A,44H
MOV B,60H
DIV AB
MOV 4DH,A
MOV A,#10
MUL AB
ADD A,42H
MOV B,60H
DIV AB
MOV 4CH,A
MOV A,#10
MUL AB
ADD A,41H
MOV B,60H
DIV AB
MOV 4BH,A
MOV A,#10
MUL AB
ADD A,40H
MOV B,60H
DIV AB
MOV 4AH,A
MOV A,69H
CJNE A,#0,KKK0
MOV A,6FH
CJNE A,#0,KKK1
MOV A,4FH
CJNE A,#0,KKK2
MOV A,4EH
CJNE A,#0,KKK3
MOV A,4DH
CJNE A,#0,KKK4
MOV A,4CH
CJNE A,#0,KKK5
MOV A,4BH
CJNE A,#0,KKK6
MOV A,4AH
CJNE A,#0,KKK7
KK8:
MOV 69H,#0
MOV R0,#0FH
MOV R1,#14
LL8:MOV A,#10
MUL AB
MOV B,60H
DIV AB
MOV @R0,A
DEC R0
DJNZ R1,LL8
MOV 6FH,#16
MOV 4FH,0FH
MOV 4EH,0EH
MOV 4DH,0DH
MOV 4CH,0CH
MOV 4BH,0BH
MOV 4AH,0AH
MOV 49H,9
MOV 48H,8
MOV 46H,7
MOV 45H,6
MOV 44H,5
MOV 42H,4
MOV 41H,3
MOV 40H,2
MOV 0FEH,#0
LCALL A0016
LJMP DDD0
KKK0:LJMP KK0
KKK1:LJMP KK1
KKK2:LJMP KK2
KKK3:LJMP KK3
KKK4:LJMP KK4
KKK5:LJMP KK5
KKK6:LJMP KK6
KKK7:LJMP KK7
KK0:
MOV R0,#0FH
MOV R1,#7
LL0:MOV A,#10
MUL AB
MOV B,60H
DIV AB
MOV @R0,A
DEC R0
DJNZ R1,LL0
MOV 49H,#16
MOV 48H,0FH
MOV 46H,0EH
MOV 45H,0DH
MOV 44H,0CH
MOV 42H,0BH
MOV 41H,0AH
MOV 40H,9
LCALL A0017
LJMP DDD0
KK1:MOV 69H,6FH
MOV 6FH,4FH
MOV 4FH,4EH
MOV 4EH,4DH
MOV 4DH,4CH
MOV 4CH,4BH
MOV 4BH,4AH
MOV 4AH,#16
MOV R0,#0FH
MOV R1,#8
LL1:MOV A,#10
MUL AB
MOV B,60H
DIV AB
MOV @R0,A
DEC R0
DJNZ R1,LL1
MOV 49H,0FH
MOV 48H,0EH
MOV 46H,0DH
MOV 45H,0CH
MOV 44H,0BH
MOV 42H,0AH
MOV 41H,9
MOV 40H,8
MOV 0FEH,#56
LCALL A0016
LJMP DDD0
KK2:MOV 69H,4FH
MOV 6FH,4EH
MOV 4FH,4DH
MOV 4EH,4CH
MOV 4DH,4BH
MOV 4CH,4AH
MOV 4BH,#16
MOV R0,#0FH
MOV R1,#9
LL2:MOV A,#10
MUL AB
MOV B,60H
DIV AB
MOV @R0,A
DEC R0
DJNZ R1,LL2
MOV 4AH,0FH
MOV 49H,0EH
MOV 48H,0DH
MOV 46H,0CH
MOV 45H,0BH
MOV 44H,0AH
MOV 42H,9
MOV 41H,8
MOV 40H,7
MOV 0FEH,#48
LCALL A0016
LJMP DDD0
KK3:MOV 69H,4EH
MOV 6FH,4DH
MOV 4FH,4CH
MOV 4EH,4BH
MOV 4DH,4AH
MOV 4CH,#16
MOV R0,#0FH
MOV R1,#10
LL3:MOV A,#10
MUL AB
MOV B,60H
DIV AB
MOV @R0,A
DEC R0
DJNZ R1,LL3
MOV 4BH,0FH
MOV 4AH,0EH
MOV 49H,0DH
MOV 48H,0CH
MOV 46H,0BH
MOV 45H,0AH
MOV 44H,9
MOV 42H,8
MOV 41H,7
MOV 40H,6
MOV 0FEH,#40
LCALL A0016
LJMP DDD0
KK4:MOV 69H,4DH
MOV 6FH,4CH
MOV 4FH,4BH
MOV 4EH,4AH
MOV 4DH,#16
MOV R0,#0FH
MOV R1,#11
LL4:MOV A,#10
MUL AB
MOV B,60H
DIV AB
MOV @R0,A
DEC R0
DJNZ R1,LL4
MOV 4CH,0FH
MOV 4BH,0EH
MOV 4AH,0DH
MOV 49H,0CH
MOV 48H,0BH
MOV 46H,0AH
MOV 45H,9
MOV 44H,8
MOV 42H,7
MOV 41H,6
MOV 40H,5
MOV 0FEH,#32
LCALL A0016
LJMP DDD0
KK5:MOV 69H,4CH
MOV 6FH,4BH
MOV 4FH,4AH
MOV 4EH,#16
MOV R0,#0FH
MOV R1,#12
LL5:MOV A,#10
MUL AB
MOV B,60H
DIV AB
MOV @R0,A
DEC R0
DJNZ R1,LL5
MOV 4DH,0FH
MOV 4CH,0EH
MOV 4BH,0DH
MOV 4AH,0CH
MOV 49H,0BH
MOV 48H,0AH
MOV 46H,9
MOV 45H,8
MOV 44H,7
MOV 42H,6
MOV 41H,5
MOV 40H,4
MOV 0FEH,#24
LCALL A0016
LJMP DDD0
KK6:MOV 69H,4BH
MOV 6FH,4AH
MOV 4FH,#16
MOV R0,#0FH
MOV R1,#13
LL6:MOV A,#10
MUL AB
MOV B,60H
DIV AB
MOV @R0,A
DEC R0
DJNZ R1,LL6
MOV 4EH,0FH
MOV 4DH,0EH
MOV 4CH,0DH
MOV 4BH,0CH
MOV 4AH,0BH
MOV 49H,0AH
MOV 48H,9
MOV 46H,8
MOV 45H,7
MOV 44H,6
MOV 42H,5
MOV 41H,4
MOV 40H,3
MOV 0FEH,#16
LCALL A0016
LJMP DDD0
KK7:MOV 69H,4AH
MOV 6FH,#16
MOV R0,#0FH
MOV R1,#14
LL7:MOV A,#10
MUL AB
MOV B,60H
DIV AB
MOV @R0,A
DEC R0
DJNZ R1,LL7
MOV 4FH,0FH
MOV 4EH,0EH
MOV 4DH,0DH
MOV 4CH,0CH
MOV 4BH,0BH
MOV 4AH,0AH
MOV 49H,9
MOV 48H,8
MOV 46H,7
MOV 45H,6
MOV 44H,5
MOV 42H,4
MOV 41H,3
MOV 40H,2
MOV 0FEH,#8
LCALL A0016


DDD0:
LCALL A0020
LCALL A0014
LCALL A0013
LCALL A0012
LCALL A0011
LCALL A0010
LCALL A009
LCALL A008
LCALL A007
LCALL A006
LCALL A005
LCALL A004
LCALL A003
LCALL A002
LCALL A001
LCALL A000
LJMP DD













KAO4:CJNE A,#15,K1A0OO1
LJMP START1
K1A0OO1:
MOV A,50H
CJNE A,#0,A1011A1
MOV 60H,R1
LCALL A8
INC 50H
ljmp dd
A1011A1:CJNE A,#1,A1011A2
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
INC 50H
LJMP DD
A1011A2:CJNE A,#2,A1011A3
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
INC 50H
LJMP DD
A1011A3:CJNE A,#3,A1011A5
MOV 74H,72H
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
LCALL A11
INC 50H
LJMP DD
A1011A5:CJNE A,#4,A1011A6
MOV 75H,74H
MOV 74H,72H
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
LCALL A11
LCALL A12
INC 50H
LJMP DD
A1011A6:CJNE A,#5,A1011A7
MOV 76H,75H
MOV 75H,74H
MOV 74H,72H
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
LCALL A11
LCALL A12
LCALL A13
INC 50H
LJMP DD
A1011A7:CJNE A,#6,A1011A9
MOV 78H,76H
MOV 76H,75H
MOV 75H,74H
MOV 74H,72H
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
LCALL A11
LCALL A12
LCALL A13
LCALL A14
INC 50H
LJMP DD
A1011A9:CJNE A,#7,A1011A10
MOV 79H,78H
MOV 78H,76H
MOV 76H,75H
MOV 75H,74H
MOV 74H,72H
MOV 72H,71H
MOV 71H,60H
MOV  60H,R1
LCALL A8
LCALL A9
LCALL A10
LCALL A11
LCALL A12
LCALL A13
LCALL A14
LCALL A15
INC 50H
A1011A10:LJMP DD
BB3:MOV A,R1
CJNE A,#10,AAA1
INC 51H
MOV 50H,#0
LJMP AA15
AAA1:CJNE A,#11,AAA2
INC 51H
INC 51H
MOV 50H,#0
LJMP AA15
AAA2:CJNE A,#12,AAA3
INC 51H
INC 51H
INC 51H
MOV 50H,#0
LJMP AA15
AAA3:CJNE A,#13,AAA4
INC 51H
INC 51H
INC 51H
INC 51H
MOV 50H,#0
LJMP AA15
AAA4:CJNE A,#14,AAA5
MOV 47H,R1
LCALL A31
LJMP DD
AAA5:CJNE A,#15,AAA6
LJMP START1
AAA6:MOV A,50H
CJNE A,#0,AA1
MOV 40H,R1
LCALL A0
INC 50H
ljmp dd
AA1:CJNE A,#1,AA2
MOV 41H,40H
MOV  40H,R1
LCALL A0
LCALL A1
INC 50H
LJMP DD
AA2:CJNE A,#2,AA3
MOV 42H,41H
MOV 41H,40H
MOV  40H,R1
LCALL A0
LCALL A1
LCALL A2
INC 50H
LJMP DD
AA3:CJNE A,#3,AA5
MOV 44H,42H
MOV 42H,41H
MOV 41H,40H
MOV  40H,R1
LCALL A0
LCALL A1
LCALL A2
LCALL A3
INC 50H
LJMP DD
AA5:CJNE A,#4,AA6
MOV 45H,44H
MOV 44H,42H
MOV 42H,41H
MOV 41H,40H
MOV  40H,R1
LCALL A0
LCALL A1
LCALL A2
LCALL A3
LCALL A4
INC 50H
LJMP DD
AA6:CJNE A,#5,AA7
MOV 46H,45H
MOV 45H,44H
MOV 44H,42H
MOV 42H,41H
MOV 41H,40H
MOV  40H,R1
LCALL A0
LCALL A1
LCALL A2
LCALL A3
LCALL A4
LCALL A5
INC 50H
LJMP DD
AA7:CJNE A,#6,AA9
MOV 48H,46H
MOV 46H,45H
MOV 45H,44H
MOV 44H,42H
MOV 42H,41H
MOV 41H,40H
MOV  40H,R1
LCALL A0
LCALL A1
LCALL A2
LCALL A3
LCALL A4
LCALL A5
LCALL A6
INC 50H
LJMP DD
AA9:CJNE A,#7,AA10
MOV 49H,48H
MOV 48H,46H
MOV 46H,45H
MOV 45H,44H
MOV 44H,42H
MOV 42H,41H
MOV 41H,40H
MOV  40H,R1
LCALL A0
LCALL A1
LCALL A2
LCALL A3
LCALL A4
LCALL A5
LCALL A6
LCALL A7
INC 50H
AA10:LJMP DD
;****************************************
AA15:MOV  43H,R1
LCALL A30
LJMP DD
A0:mov column2,#56
mov pagef2,#0
mov codes,40H
lcall writeright
RET
A1:mov column2,#48
mov pagef2,#0
mov codes,41H
lcall writeright
RET
A2:mov column2,#40
mov pagef2,#0
mov codes,42H
lcall writeright
RET
A3:mov column2,#32
mov pagef2,#0
mov codes,44H
lcall writeright
RET
A4:mov column2,#24
mov pagef2,#0
mov codes,45H
lcall writeright
RET
A5:mov column2,#16
mov pagef2,#0
mov codes,46H
lcall writeright
RET
A6:mov column2,#8
mov pagef2,#0
mov codes,48H
lcall writeright
RET
A7:mov column2,#0
mov pagef2,#0
mov codes,49H
lcall writeright
RET
 A8:mov column2,#56
mov pagef2,#2
mov codes,60H
lcall writeright
RET
A9:mov column2,#48
mov pagef2,#2
mov codes,71H
lcall writeright
RET
A10:mov column2,#40
mov pagef2,#2
mov codes,72H
lcall writeright
RET
A11:mov column2,#32
mov pagef2,#2
mov codes,74H
lcall writeright
RET
A12:mov column2,#24
mov pagef2,#2
mov codes,75H
lcall writeright
RET
A13:mov column2,#16
mov pagef2,#2
mov codes,76H
lcall writeright
RET
A14:mov column2,#8
mov pagef2,#2
mov codes,78H
lcall writeright
RET
A15:mov column2,#0
mov pagef2,#2
mov codes,79H
lcall writeright
RET
A00:mov column2,#56
mov pagef2,#4
mov codes,40H
lcall writeright
RET
A01:mov column2,#48
mov pagef2,#4
mov codes,41H
lcall writeright
RET
A02:mov column2,#40
mov pagef2,#4
mov codes,42H
lcall writeright
RET
A03:mov column2,#32
mov pagef2,#4
mov codes,44H
lcall writeright
RET
A04:mov column2,#24
mov pagef2,#4
mov codes,45H
lcall writeright
RET
A05:mov column2,#16
mov pagef2,#4
mov codes,46H
lcall writeright
RET
A06:mov column2,#8
mov pagef2,#4
mov codes,48H
lcall writeright
RET
A07:mov column2,#0
mov pagef2,#4
mov codes,49H
lcall writeright
RET
A08:mov column,#56
mov pagef,#4
mov codes,0CEH
lcall writeleft
RET

A31:mov column,#32
mov pagef,#4
mov codes,47H
lcall writeLEFT
RET
A30:mov column,#56
mov pagef,#2
mov codes,43H
lcall writeLEFT
RET
A32:mov column,#56
mov pagef,#4
mov codes,#11
lcall writeLEFT
RET
A000:mov column2,#56
mov pagef2,#6
mov codes,40H
lcall writeright
RET
A001:mov column2,#48
mov pagef2,#6
mov codes,41H
lcall writeright
RET
A002:mov column2,#40
mov pagef2,#6
mov codes,42H
lcall writeright
RET
A003:mov column2,#32
mov pagef2,#6
mov codes,44H
lcall writeright
RET
A004:mov column2,#24
mov pagef2,#6
mov codes,45H
lcall writeright
RET
A005:mov column2,#16
mov pagef2,#6
mov codes,46H
lcall writeright
RET
A006:mov column2,#8
mov pagef2,#6
mov codes,48H
lcall writeright
RET
A007:mov column2,#0
mov pagef2,#6
mov codes,49H
lcall writeright
RET
A008:mov column,#56
mov pagef,#6
mov codes,4aH
lcall writeleft
RET
A009:mov column,#48
mov pagef,#6
mov codes,4bH
lcall writeleft
RET
A0010:mov column,#40
mov pagef,#6
mov codes,4cH
lcall writeleft
RET
A0011:mov column,#32
mov pagef,#6
mov codes,4dH
lcall writeleft
RET
A0012:mov column,#24
mov pagef,#6
mov codes,4EH
lcall writeleft
RET
A0013:mov column,#16
mov pagef,#6
mov codes,4FH
lcall writeleft
RET
A0014:mov column,#8
mov pagef,#6
mov codes,6FH
lcall writeleft
RET
A0015:mov column,#0
mov pagef,#6
mov codes,#14
lcall writeleft
RET
A0016:mov column,0FEH    ;左小数点
mov pagef,#6
mov codes,#16
lcall writeleft
RET
A0017:mov column2,0FEH   ;右小数点
mov pagef2,#6
mov codes,#16
lcall writeright
RET
A0020:mov column,#0
mov pagef,#6
mov codes,69H
lcall writeleft
RET
writeleft:  ; 左半屏写入8*16数字子程序
     mov dptr,#table1
     push column
     mov cpage,#2
     mov ccolumn,#0
     mov a,pagef
     anl a,#07h
     orl a,#0b8h
     mov com,a
     lcall prm0

     mov a,column
     anl a,#3fh
     orl a,#40h
     mov com,a
     lcall prm0

     mov a,codes
     mov b,#16
     mul ab
     add a,dpl
     mov dpl,a
     mov a,b
     addc a,dph
     mov dph,a

lp1:
     mov a,#00h
     movc a,@a+dptr
     mov dat,a
     lcall prm1
     inc ccolumn
     mov a,ccolumn
     inc dptr
     cjne a,#8,lp1
     dec cpage
     inc pagef
     mov a,cpage
     jz over1
     mov a,pagef
     anl a,#07h
     orl a,#0b8h
     mov com,a
     lcall prm0
     pop column
     mov a,column
     anl a,#3fh
     orl a,#40h
     mov com,a
     lcall prm0
     mov ccolumn,#0
     ljmp lp1
over1:ret
;;;;;;;;;;;;;;;;;;;;;;;;;;
writeright:  ; 右半屏写入8*16数字子程序
     mov dptr,#table1
     push column2
     mov cpage2,#2
     mov ccolumn2,#0
     mov a,pagef2
     anl a,#07h
     orl a,#0b8h
     mov com,a
     lcall prr0

     mov a,column2
     anl a,#3fh
     orl a,#40h
     mov com,a
     lcall prr0

     mov a,codes
     mov b,#16
     mul ab
     add a,dpl
     mov dpl,a
     mov a,b
     addc a,dph
     mov dph,a

lp2:
     mov a,#00h
     movc a,@a+dptr
     mov dat,a
     lcall prr1
     inc ccolumn2
     mov a,ccolumn2
     inc dptr
     cjne a,#8,lp2
     dec cpage2
     inc pagef2
     mov a,cpage2
     jz over2
     mov a,pagef2
     anl a,#07h
     orl a,#0b8h
     mov com,a
     lcall prr0
     pop column2
     mov a,column2
     anl a,#3fh
     orl a,#40h
     mov com,a
     lcall prr0
     mov ccolumn2,#0
     ljmp lp2
over2:ret
;;;;;;;;;;;;;;;;;;;;;;;;;;
writeleft2:  ; 左半屏写入16*16汉字子程序
     mov dptr,#table2
     push column3
     mov cpage3,#2
     mov ccolumn3,#0
     mov a,pagef3
     anl a,#07h
     orl a,#0b8h
     mov com,a
     lcall prm0

     mov a,column3
     anl a,#3fh
     orl a,#40h
     mov com,a
     lcall prm0

     mov a,codes
     mov b,#32
     mul ab
     add a,dpl
     mov dpl,a
     mov a,b
     addc a,dph
     mov dph,a
lp3:
     mov a,#00h
     movc a,@a+dptr
     mov dat,a
     lcall prm1
     inc ccolumn3
     mov a,ccolumn3
     inc dptr
     cjne a,#16,lp3
     dec cpage3
     inc pagef3
     mov a,cpage3
     jz over3
     mov a,pagef3
     anl a,#07h
     orl a,#0b8h
     mov com,a
     lcall prm0
     pop column3
     mov a,column3
     anl a,#3fh
     orl a,#40h
     mov com,a
     lcall prm0
     mov ccolumn3,#0
     ljmp lp3
over3:ret
;;;;;;;;;;;;;;;;;;;;;;;;;;
writeright2:  ; 右半屏写入16*16汉字子程序
     mov dptr,#table2
     push column4
     mov cpage4,#2
     mov ccolumn4,#0
     mov a,pagef4
     anl a,#07h
     orl a,#0b8h
     mov com,a
     lcall prr0

     mov a,column4
     anl a,#3fh
     orl a,#40h
     mov com,a
     lcall prr0

     mov a,codes
     mov b,#32
     mul ab
     add a,dpl
     mov dpl,a
     mov a,b
     addc a,dph
     mov dph,a

lp4:
     mov a,#00h
     movc a,@a+dptr
     mov dat,a
     lcall prr1
     inc ccolumn4
     mov a,ccolumn4
     inc dptr
     cjne a,#16,lp4
     dec cpage4
     inc pagef4
     mov a,cpage4
     jz over4
     mov a,pagef4
     anl a,#07h
     orl a,#0b8h
     mov com,a
     lcall prr0
     pop column4
     mov a,column4
     anl a,#3fh
     orl a,#40h
     mov com,a
     lcall prr0
     mov ccolumn4,#0
     ljmp lp4
over4:ret

;写指令代码子程序(左)
PRM0:
     CLR CSA
     SETB CSB
     CLR rs
     SETB rw
PRM01:
     MOV P0,#0FFH
     SETB E
     MOV A,P0
     CLR E
     JB  ACC.7,PRM01
     CLR rw
     MOV P0,COM
     SETB E
     CLR E
     RET
;===============================
;写显示数据子程序(左)
PRM1:
     CLR CSA
     SETB CSB
     CLR rs
     SETB rw
PRM11:
     MOV P0,#0FFH
     SETB E
     MOV A,P0
     CLR E
     JB  ACC.7,PRM11
     SETB rs
     CLR rw
     MOV P0,DAT
     SETB E
     CLR E
     RET

;=============================
;写指令代码子程序(右)
PRR0:
     CLR CSB
     SETB CSA
     CLR rs
     SETB rw
PRR01:
     MOV P0,#0FFH
     SETB E
     MOV A,P0
     CLR E
     JB  ACC.7,PRR01
     CLR rw
     MOV P0,COM
     SETB E
     CLR E
     RET
;===============================
;写显示数据子程序(右)
PRR1:
     CLR CSB
     SETB CSA
     CLR rs
     SETB rw
PRR11:
     MOV P0,#0FFH
     SETB E
     MOV A,P0
     CLR E
     JB  ACC.7,PRR11
     SETB rs
     CLR rw
     MOV P0,DAT
     SETB E
     CLR E
     RET
;================================
;初始化子程序
INT: MOV COM,#0C0H ;设置显示起始行为第一行
     LCALL PRM0
     LCALL PRR0
     MOV COM,#3FH  ;开显示设置
     LCALL PRM0
     LCALL PRR0
     RET
;================================
;清屏子程序
CLEAR:
     MOV R4,#00H
CLEAR1:
     MOV A,R4
     ORL A,#0B8H
     MOV COM,A
     LCALL PRM0
     LCALL PRR0
     MOV COM,#40H
     LCALL PRM0
     LCALL PRR0
     MOV R3,#40H
CLEAR2:
     MOV DAT,#00H
     LCALL PRM1
     LCALL PRR1
     DJNZ R3,CLEAR2
     INC R4
     CJNE R4,#08H,CLEAR1
     RET
mm:mov r4,#250
gg:mov r5,#20
djnz r5,$
djnz r4,gg
ret

table1:
DB   0F0h, 0F8h,  0Ch,  04h
DB    04h,  0Ch, 0F8h, 0F0h        ;0
DB    0Fh,  1Fh,  30h,  20h
DB    20h,  30h,  1Fh,  0Fh
DB    00h,  00h,  08h, 0F8h         ;1
DB   0FCh,  00h,  00h,  00h
DB    00h,  00h,  20h,  3Fh
DB    3Fh,  20h,  00h,  00h
DB  30h,  38h,  0Ch,  04h
DB  04h,  0Ch, 0F8h, 0F0h
DB  20h,  30h,  38h,  2Ch          ;2
DB  26h,  23h,  21h,  38h
DB   10h,  18h,  0Ch,  84h
DB   84h, 0CCh,  78h,  30h
DB   08h,  18h,  30h,  20h
DB   20h,  31h,  1Fh,  0Eh         ;3
DB   00h, 0C0h,  70h,  18h
DB  0FCh, 0FEh,  00h,  00h
DB   07h,  05h,  04h,  24h
DB   3Fh,  3Fh,  24h,  04h          ;4
DB  0FCh, 0FCh, 0C4h,  44h
DB   44h, 0C4h,  84h,  04h
DB   08h,  18h,  30h,  20h
DB   20h,  30h,  1Fh,  0Fh          ;5

DB  0F0h, 0F8h,  8Ch,  44h
DB   44h, 0CCh,  98h,  10h
DB   0Fh,  1Fh,  30h,  20h
DB   20h,  30h,  1Fh,  0Fh          ;6
DB    1Ch,  0Ch,  0Ch,  0Ch
DB   0CCh, 0ECh,  3Ch,  1Ch
DB    00h,  00h,  3Ch,  3Fh
DB    03h,  00h,  00h,  00h         ;7
DB    30h,  78h, 0CCh,  84h
DB    84h, 0CCh,  78h,  30h
DB    0Eh,  1Fh,  31h,  20h
DB    20h,  31h,  1Fh,  0Eh          ;8
DB   0F0h, 0F8h,  0Ch,  04h
DB    04h,  0Ch, 0F8h, 0F0h
DB    08h,  19h,  33h,  22h
DB    22h,  33h,  1Fh,  0Fh         ;9
db  00h, 80h, 80h,0E0h  ; -+-
db 0E0h, 80h, 80h, 00h
db  00h, 00h, 00h, 03h
db  03h, 00h, 00h, 00h
db  80h, 80h, 80h, 80h  ; ---
db  80h, 80h, 80h, 00h
db  00h, 00h, 00h, 00h
db  00h, 00h, 00h, 00h
db  18h, 30h, 60h,0C0h  ; -*-
db 0C0h, 60h, 30h, 18h
db  0Ch, 06h, 03h, 01h
db  01h, 03h, 06h, 0Ch
db       80h, 80h, 80h,0B0h  ; -/-
db 0B0h, 80h, 80h, 80h
db  00h, 00h, 00h, 06h
db  06h, 00h, 00h, 00h
db  40h, 40h, 40h, 40h  ; -=-
db  40h, 40h, 40h, 00h
db  02h, 02h, 02h, 02h
db  02h, 02h, 02h, 00h
db  00h, 00h, 00h, 30h  ; -:-
db  30h, 00h, 00h, 00h
db  00h, 00h, 00h, 06h
db  06h, 00h, 00h, 00h
db  00h, 00h, 00h, 00h  ; -.-
db  00h, 00h, 00h, 00h
db  00h, 00h, 00h, 0Ch
db  0Ch, 00h, 00h, 00h
table2:            ; 点阵：16x16提取点阵方向：纵向
        db       10h, 92h, 54h, 30h,0FFh, 50h, 94h, 32h   ; "数",
 db 0D8h, 17h, 10h, 10h,0F0h, 18h, 10h, 00h
 db  02h, 82h, 4Eh, 33h, 22h, 52h, 8Eh, 40h
 db  23h, 14h, 08h, 16h, 61h,0C0h, 40h, 00h
 db       00h, 10h, 0Ch, 24h, 24h, 24h, 25h, 26h   ;   "字",
 db 0A4h, 64h, 24h, 04h, 14h, 0Ch, 00h, 00h
 db  02h, 02h, 02h, 02h, 02h, 42h, 82h, 7Fh
 db  02h, 02h, 02h, 02h, 02h, 03h, 02h, 00h

        db       00h, 30h, 28h,0A4h, 63h, 10h, 08h, 48h     ; "结",
 db  48h, 48h, 7Fh, 48h, 48h, 4Ch, 08h, 00h
 db  00h, 22h, 63h, 22h, 12h, 12h, 00h,0FEh
 db  42h, 42h, 42h, 42h, 42h,0FFh, 02h, 00h
 db       00h, 00h, 00h,0FEh, 92h, 92h, 92h,0FEh   ;  "果",
 db  92h, 92h, 92h,0FFh, 02h, 00h, 00h, 00h
 db  02h, 42h, 42h, 22h, 12h, 0Ah, 06h,0FFh
 db  06h, 0Ah, 12h, 22h, 62h, 23h, 02h, 00h
 db       08h, 48h, 88h, 08h,0C8h, 38h, 10h, 90h   ;  "对",
 db  10h, 10h, 10h,0FFh, 10h, 18h, 10h, 00h
 db  20h, 10h, 0Ch, 03h, 04h, 18h, 00h, 00h
 db  03h, 40h, 80h, 7Fh, 00h, 00h, 00h, 00h
 db       02h, 02h, 02h, 02h, 02h, 82h, 42h,0F2h    ; "不",
 db  0Eh, 42h, 82h, 02h, 02h, 03h, 02h, 00h
 db  00h, 08h, 04h, 02h, 01h, 00h, 00h,0FFh
 db  00h, 00h, 00h, 01h, 03h, 06h, 00h, 00h
 db       40h, 48h, 48h, 48h,0FFh, 48h, 48h, 00h   ;  "起",
 db 0C4h, 44h, 44h, 44h,0FEh, 04h, 00h, 00h
 db  40h, 20h, 1Fh, 20h, 7Fh, 42h, 42h, 40h
 db  47h, 48h, 48h, 48h, 48h, 6Eh, 20h, 00h
 db       88h, 68h, 1Fh,0C8h, 0Ch, 28h, 90h,0A8h   ;  "输",
 db 0A6h,0A1h, 26h, 28h, 10h,0B0h, 10h, 00h
 db  09h, 09h, 05h,0FFh, 05h, 00h,0FFh, 0Ah
 db  8Ah,0FFh, 00h, 1Fh, 80h,0FFh, 00h, 00h
 db       00h, 00h, 00h, 00h, 00h, 01h,0E2h, 1Ch   ;  "入",
 db 0E0h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
 db  80h, 40h, 20h, 10h, 0Ch, 03h, 00h, 00h
 db  00h, 03h, 0Ch, 30h, 40h,0C0h, 40h, 00h
 db       80h, 40h, 70h,0CFh, 48h, 48h, 48h, 48h   ;  "错",
 db  7Fh, 48h, 48h, 7Fh,0C8h, 68h, 40h, 00h
 db  00h, 02h, 02h, 7Fh, 22h, 12h, 00h,0FFh
 db  49h, 49h, 49h, 49h,0FFh, 01h, 00h, 00h
 db       40h, 42h,0C4h, 0Ch, 00h, 40h, 5Eh, 52h   ;  "误",
 db  52h,0D2h, 52h, 52h, 5Fh, 42h, 00h, 00h
 db  00h, 00h, 7Fh, 20h, 12h, 82h, 42h, 22h
 db  1Ah, 07h, 1Ah, 22h, 42h,0C3h, 42h, 00h
 db       40h, 42h, 44h,0CCh, 00h, 20h, 22h, 22h   ;  "运",
 db 0E2h, 22h, 22h, 23h, 32h, 20h, 00h, 00h
 db  00h, 40h, 20h, 1Fh, 20h, 48h, 4Ch, 4Bh
 db  48h, 48h, 4Ah, 4Ch, 58h, 60h, 20h, 00h
 db       08h, 04h, 03h,0FAh,0AEh,0AAh,0AAh,0ACh   ;  "算",
 db 0ABh,0AAh,0AEh,0FAh, 02h, 02h, 00h, 00h
 db  08h, 08h, 88h, 4Bh, 3Eh, 0Ah, 0Ah, 0Ah
 db  0Ah, 0Ah,0FEh, 0Bh, 08h, 0Ch, 08h, 00h
 db       40h, 48h, 48h,0FFh, 48h, 48h, 82h, 42h   ;  "超",
 db  3Eh, 02h, 22h, 42h, 3Fh, 02h, 00h, 00h
 db  40h, 3Fh, 10h, 1Fh, 22h, 42h, 40h, 5Fh
 db  51h, 51h, 51h, 51h, 5Fh, 60h, 20h, 00h
 db       00h, 00h,0FCh, 40h, 40h, 40h, 40h,0FFh   ;  "出",
 db  40h, 40h, 40h, 40h,0FCh, 00h, 00h, 00h
 db  00h,0FEh, 40h, 40h, 40h, 40h, 40h, 7Fh
 db  40h, 40h, 40h, 40h, 40h,0FEh, 00h, 00h
 db       04h, 44h, 94h, 24h, 6Fh, 04h,0E4h, 24h    ; "范",
 db  24h, 24h, 2Fh,0F4h, 24h, 06h, 04h, 00h
 db  04h, 04h,0FDh, 04h, 02h, 00h, 3Fh, 40h
 db  40h, 42h, 44h, 43h, 40h, 40h, 70h, 00h
 db       00h,0FEh, 02h, 12h, 52h, 52h, 52h,0FEh   ;  "围",
 db  52h, 52h, 5Ah, 12h, 02h,0FFh, 02h, 00h
 db  00h,0FFh, 40h, 41h, 41h, 41h, 41h, 7Fh
 db  41h, 49h, 51h, 4Fh, 40h,0FFh, 00h, 00h



                               END







--------------------------------------------------------------------------------
独栋别墅 230万起
