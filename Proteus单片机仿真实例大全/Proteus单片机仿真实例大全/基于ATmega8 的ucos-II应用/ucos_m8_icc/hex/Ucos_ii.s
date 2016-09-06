	.module Ucos_ii.c
	.area lit(rom, con, rel)
_OSMapTbl::
	.byte 1,2
	.byte 4,8
	.byte 16,32
	.byte 64,128
	.dbfile D:\job\avrtest\光盘\开发板\iccavr\source/os_core.c
	.dbsym e OSMapTbl _OSMapTbl A[8:8]kc
_OSUnMapTbl::
	.byte 0,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 3,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 4,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 3,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 5,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 3,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 4,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 3,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 6,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 3,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 4,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 3,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 5,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 3,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 4,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 3,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 7,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 3,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 4,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 3,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 5,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 3,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 4,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 3,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 6,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 3,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 4,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 3,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 5,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 3,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 4,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.byte 3,0
	.byte 1,0
	.byte 2,0
	.byte 1,0
	.dbsym e OSUnMapTbl _OSUnMapTbl A[256:256]kc
	.area text(rom, con, rel)
	.dbfile D:\job\avrtest\光盘\开发板\iccavr\source/os_core.c
	.dbfunc e OSInit _OSInit fV
;              i -> R10,R11
	.even
_OSInit::
	rcall push_gset3x
	sbiw R28,3
	.dbline -1
	.dbline 77
; /*
; *********************************************************************************************************
; *                                                uC/OS-II
; *                                          The Real-Time Kernel
; *
; *                        (c) Copyright 1992-1998, Jean J. Labrosse, Plantation, FL
; *                                           All Rights Reserved
; *
; *                                                  V2.00
; *
; * File : uCOS_II.C
; * By   : Jean J. Labrosse
; *********************************************************************************************************
; */
; 
; #define  OS_GLOBALS                           /* Declare GLOBAL variables                              */
; #include "includes.h"
; 
; 
; #define  OS_MASTER_FILE                       /* Prevent the following files from including includes.h */
; #include "os_core.c"
; #include "os_task.c"
; #include "os_time.c"
; #include "74164.c"
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
	.dbline 81
; 
; 
; 
; 
	ldi R24,0
	ldi R25,0
	ldi R26,0
	ldi R27,0
	sts _OSTime+1,R25
	sts _OSTime,R24
	sts _OSTime+2+1,R27
	sts _OSTime+2,R26
	.dbline 82
; 
	clr R2
	sts _OSIntNesting,R2
	.dbline 83
; 
	sts _OSLockNesting,R2
	.dbline 85
; 
; 
	sts _OSTaskCtr,R2
	.dbline 87
; 
; 
	sts _OSRunning,R2
	.dbline 88
; 
	ldi R24,0
	ldi R25,0
	ldi R26,0
	ldi R27,0
	sts _OSIdleCtr+1,R25
	sts _OSIdleCtr,R24
	sts _OSIdleCtr+2+1,R27
	sts _OSIdleCtr+2,R26
	.dbline 90
; 
; 
	ldi R24,0
	ldi R25,0
	ldi R26,0
	ldi R27,0
	sts _OSCtxSwCtr+1,R25
	sts _OSCtxSwCtr,R24
	sts _OSCtxSwCtr+2+1,R27
	sts _OSCtxSwCtr+2,R26
	.dbline 91
; 
	sts _OSRdyGrp,R2
	.dbline 92
	clr R10
	clr R11
	rjmp L6
L3:
	.dbline 92
	.dbline 93
	ldi R24,<_OSRdyTbl
	ldi R25,>_OSRdyTbl
	movw R30,R10
	add R30,R24
	adc R31,R25
	clr R2
	std z+0,R2
	.dbline 94
L4:
	.dbline 92
	movw R24,R10
	adiw R24,1
	movw R10,R24
L6:
	.dbline 92
; 
	movw R24,R10
	cpi R24,2
	ldi R30,0
	cpc R25,R30
	brlo L3
	.dbline 96
; 
; 
; 
; 
	clr R2
	sts _OSPrioCur,R2
	.dbline 97
; 
	sts _OSPrioHighRdy,R2
	.dbline 98
; 
	clr R3
	sts _OSTCBHighRdy+1,R3
	sts _OSTCBHighRdy,R2
	.dbline 99
; 
	sts _OSTCBCur+1,R3
	sts _OSTCBCur,R2
	.dbline 100
; 
	sts _OSTCBList+1,R3
	sts _OSTCBList,R2
	.dbline 101
	clr R10
	clr R11
	rjmp L10
L7:
	.dbline 101
	.dbline 102
	ldi R16,2
	ldi R17,0
	movw R18,R10
	rcall empy16s
	movw R30,R16
	ldi R24,<_OSTCBPrioTbl
	ldi R25,>_OSTCBPrioTbl
	add R30,R24
	adc R31,R25
	clr R2
	clr R3
	std z+0,R2
	std z+1,R3
	.dbline 103
L8:
	.dbline 101
	movw R24,R10
	adiw R24,1
	movw R10,R24
L10:
	.dbline 101
; 
	movw R24,R10
	cpi R24,16
	ldi R30,0
	cpc R25,R30
	brlo L7
	.dbline 104
	clr R10
	clr R11
	rjmp L14
L11:
	.dbline 104
	.dbline 105
	movw R18,R10
	subi R18,255  ; offset = 1
	sbci R19,255
	ldi R16,14
	ldi R17,0
	rcall empy16s
	movw R2,R16
	ldi R24,<_OSTCBTbl
	ldi R25,>_OSTCBTbl
	add R2,R24
	adc R3,R25
	ldi R16,14
	ldi R17,0
	movw R18,R10
	rcall empy16s
	movw R30,R16
	ldi R24,<_OSTCBTbl+2
	ldi R25,>_OSTCBTbl+2
	add R30,R24
	adc R31,R25
	std z+0,R2
	std z+1,R3
	.dbline 106
L12:
	.dbline 104
	movw R24,R10
	adiw R24,1
	movw R10,R24
L14:
	.dbline 104
; 
; 
; 
	movw R24,R10
	cpi R24,5
	ldi R30,0
	cpc R25,R30
	brlo L11
	.dbline 107
; 
; 
; 
	clr R2
	clr R3
	sts _OSTCBTbl+70+2+1,R3
	sts _OSTCBTbl+70+2,R2
	.dbline 108
; 
	ldi R24,<_OSTCBTbl
	ldi R25,>_OSTCBTbl
	sts _OSTCBFreeList+1,R25
	sts _OSTCBFreeList,R24
	.dbline 111
	clr R10
	clr R11
	rjmp L21
L18:
	.dbline 111
	.dbline 112
	movw R18,R10
	subi R18,255  ; offset = 1
	sbci R19,255
	ldi R16,8
	ldi R17,0
	rcall empy16s
	movw R2,R16
	ldi R24,<_OSEventTbl
	ldi R25,>_OSEventTbl
	add R2,R24
	adc R3,R25
	ldi R16,8
	ldi R17,0
	movw R18,R10
	rcall empy16s
	movw R30,R16
	ldi R24,<_OSEventTbl
	ldi R25,>_OSEventTbl
	add R30,R24
	adc R31,R25
	std z+0,R2
	std z+1,R3
	.dbline 113
L19:
	.dbline 111
	movw R24,R10
	adiw R24,1
	movw R10,R24
L21:
	.dbline 111
; 
; 
; 
	movw R24,R10
	cpi R24,1
	ldi R30,0
	cpc R25,R30
	brlo L18
	.dbline 114
; 
; 
; 
	clr R2
	clr R3
	sts _OSEventTbl+8+1,R3
	sts _OSEventTbl+8,R2
	.dbline 115
; 
	ldi R24,<_OSEventTbl
	ldi R25,>_OSEventTbl
	sts _OSEventFreeList+1,R25
	sts _OSEventFreeList,R24
	.dbline 119
; 
; 
; 
; 
	ldi R24,15
	std y+2,R24
	ldi R24,<_OSTaskIdleStk+99
	ldi R25,>_OSTaskIdleStk+99
	std y+0,R24
	std y+1,R25
	clr R18
	clr R19
	ldi R16,<PL_OSTaskIdle
	ldi R17,>PL_OSTaskIdle
	rcall _OSTaskCreate
	.dbline -2
	.dbline 124
; 
; 
; 
; 
; 
L2:
	adiw R28,3
	rcall pop_gset3x
	.dbline 0 ; func end
	ret
	.dbsym r i 10 i
	.dbend
	.dbfunc e OSIntExit _OSIntExit fV
	.even
_OSIntExit::
	.dbline -1
	.dbline 146
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
	.dbline 147
; 
	st -y,r16
	in r16,0x3F
	cli
	push r16
	ld r16,y+
	.dbline 147
	.dbline 148
; 
	lds R24,_OSIntNesting
	subi R24,1
	mov R2,R24
	sts _OSIntNesting,R2
	lds R4,_OSLockNesting
	or R2,R4
	breq X0
	rjmp L25
X0:
	.dbline 148
	.dbline 149
; 
	ldi R24,<_OSUnMapTbl
	ldi R25,>_OSUnMapTbl
	lds R30,_OSRdyGrp
	clr R31
	add R30,R24
	adc R31,R25
	lpm R30,Z
	sts _OSIntExitY,R30
	.dbline 150
; 
	ldi R24,<_OSRdyTbl
	ldi R25,>_OSRdyTbl
	clr R31
	add R30,R24
	adc R31,R25
	ldd R30,z+0
	clr R31
	ldi R24,<_OSUnMapTbl
	ldi R25,>_OSUnMapTbl
	add R30,R24
	adc R31,R25
	lpm R2,Z
	clr R3
	lds R4,_OSIntExitY
	clr R5
	lsl R4
	rol R5
	lsl R4
	rol R5
	lsl R4
	rol R5
	add R4,R2
	adc R5,R3
	sts _OSPrioHighRdy,R4
	.dbline 151
; 
	lds R2,_OSPrioCur
	cp R4,R2
	breq L27
	.dbline 151
	.dbline 152
; 
	mov R2,R4
	ldi R24,2
	mul R24,R2
	movw R30,R0
	ldi R24,<_OSTCBPrioTbl
	ldi R25,>_OSTCBPrioTbl
	add R30,R24
	adc R31,R25
	ldd R2,z+0
	ldd R3,z+1
	sts _OSTCBHighRdy+1,R3
	sts _OSTCBHighRdy,R2
	.dbline 153
; 
	ldi R24,1
	ldi R25,0
	ldi R26,0
	ldi R27,0
	lds R4,_OSCtxSwCtr+2
	lds R5,_OSCtxSwCtr+2+1
	lds R2,_OSCtxSwCtr
	lds R3,_OSCtxSwCtr+1
	add R2,R24
	adc R3,R25
	adc R4,R26
	adc R5,R27
	sts _OSCtxSwCtr+1,R3
	sts _OSCtxSwCtr,R2
	sts _OSCtxSwCtr+2+1,R5
	sts _OSCtxSwCtr+2,R4
	.dbline 154
; 
	rcall _OSIntCtxSw
	.dbline 155
; 
L27:
	.dbline 156
; 
L25:
	.dbline 157
; 
	st -y,r16
	pop r16
	out 0x3F,r16
	ld r16,y+
	.dbline 157
	.dbline -2
	.dbline 158
; 
L24:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e OSSched _OSSched fV
;              y -> R10
	.even
_OSSched::
	rcall push_gset3x
	.dbline -1
	.dbline 178
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
	.dbline 182
; 
; 
; 
; 
	st -y,r16
	in r16,0x3F
	cli
	push r16
	ld r16,y+
	.dbline 182
	.dbline 183
; 
	lds R2,_OSIntNesting
	lds R3,_OSLockNesting
	or R3,R2
	breq X1
	rjmp L30
X1:
	.dbline 183
	.dbline 184
; 
	ldi R24,<_OSUnMapTbl
	ldi R25,>_OSUnMapTbl
	lds R30,_OSRdyGrp
	clr R31
	add R30,R24
	adc R31,R25
	lpm R10,Z
	.dbline 185
; 
	ldi R24,<_OSRdyTbl
	ldi R25,>_OSRdyTbl
	mov R30,R10
	clr R31
	add R30,R24
	adc R31,R25
	ldd R30,z+0
	clr R31
	ldi R24,<_OSUnMapTbl
	ldi R25,>_OSUnMapTbl
	add R30,R24
	adc R31,R25
	lpm R2,Z
	clr R3
	mov R4,R10
	clr R5
	lsl R4
	rol R5
	lsl R4
	rol R5
	lsl R4
	rol R5
	add R4,R2
	adc R5,R3
	sts _OSPrioHighRdy,R4
	.dbline 186
; 
	lds R2,_OSPrioCur
	cp R4,R2
	breq L32
	.dbline 186
	.dbline 187
; 
	mov R2,R4
	ldi R24,2
	mul R24,R2
	movw R30,R0
	ldi R24,<_OSTCBPrioTbl
	ldi R25,>_OSTCBPrioTbl
	add R30,R24
	adc R31,R25
	ldd R2,z+0
	ldd R3,z+1
	sts _OSTCBHighRdy+1,R3
	sts _OSTCBHighRdy,R2
	.dbline 188
; 
	ldi R24,1
	ldi R25,0
	ldi R26,0
	ldi R27,0
	lds R4,_OSCtxSwCtr+2
	lds R5,_OSCtxSwCtr+2+1
	lds R2,_OSCtxSwCtr
	lds R3,_OSCtxSwCtr+1
	add R2,R24
	adc R3,R25
	adc R4,R26
	adc R5,R27
	sts _OSCtxSwCtr+1,R3
	sts _OSCtxSwCtr,R2
	sts _OSCtxSwCtr+2+1,R5
	sts _OSCtxSwCtr+2,R4
	.dbline 189
; 
	rcall _OSCtxSw
	.dbline 190
; 
L32:
	.dbline 191
; 
L30:
	.dbline 192
; 
	st -y,r16
	pop r16
	out 0x3F,r16
	ld r16,y+
	.dbline 192
	.dbline -2
	.dbline 193
; 
L29:
	rcall pop_gset3x
	.dbline 0 ; func end
	ret
	.dbsym r y 10 c
	.dbend
	.dbfunc e OSStart _OSStart fV
;              x -> R12
;              y -> R10
	.even
_OSStart::
	rcall push_gset4x
	.dbline -1
	.dbline 214
	.dbline 219
	lds R2,_OSRunning
	tst R2
	breq X2
	rjmp L35
X2:
	.dbline 219
	.dbline 220
	ldi R24,<_OSUnMapTbl
	ldi R25,>_OSUnMapTbl
	lds R30,_OSRdyGrp
	clr R31
	add R30,R24
	adc R31,R25
	lpm R10,Z
	.dbline 221
	ldi R24,<_OSRdyTbl
	ldi R25,>_OSRdyTbl
	mov R30,R10
	clr R31
	add R30,R24
	adc R31,R25
	ldd R30,z+0
	clr R31
	ldi R24,<_OSUnMapTbl
	ldi R25,>_OSUnMapTbl
	add R30,R24
	adc R31,R25
	lpm R12,Z
	.dbline 222
	mov R2,R12
	clr R3
	mov R4,R10
	clr R5
	lsl R4
	rol R5
	lsl R4
	rol R5
	lsl R4
	rol R5
	add R4,R2
	adc R5,R3
	sts _OSPrioHighRdy,R4
	.dbline 223
	mov R2,R4
	sts _OSPrioCur,R2
	.dbline 224
	ldi R24,2
	mul R24,R2
	movw R30,R0
	ldi R24,<_OSTCBPrioTbl
	ldi R25,>_OSTCBPrioTbl
	add R30,R24
	adc R31,R25
	ldd R2,z+0
	ldd R3,z+1
	sts _OSTCBHighRdy+1,R3
	sts _OSTCBHighRdy,R2
	.dbline 225
	sts _OSTCBCur+1,R3
	sts _OSTCBCur,R2
	.dbline 226
	rcall _OSStartHighRdy
	.dbline 227
L35:
	.dbline -2
	.dbline 228
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
L34:
	rcall pop_gset4x
	.dbline 0 ; func end
	ret
	.dbsym r x 12 c
	.dbsym r y 10 c
	.dbend
	.dbfunc e OSTaskIdle _OSTaskIdle fV
;          pdata -> R16,R17
	.even
_OSTaskIdle::
	.dbline -1
	.dbline 244
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
	.dbline 245
; 
	.dbline 246
L38:
	.dbline 246
	.dbline 247
	st -y,r16
	in r16,0x3F
	cli
	push r16
	ld r16,y+
	.dbline 247
	.dbline 248
	ldi R24,1
	ldi R25,0
	ldi R26,0
	ldi R27,0
	lds R4,_OSIdleCtr+2
	lds R5,_OSIdleCtr+2+1
	lds R2,_OSIdleCtr
	lds R3,_OSIdleCtr+1
	add R2,R24
	adc R3,R25
	adc R4,R26
	adc R5,R27
	sts _OSIdleCtr+1,R3
	sts _OSIdleCtr,R2
	sts _OSIdleCtr+2+1,R5
	sts _OSIdleCtr+2,R4
	.dbline 249
	st -y,r16
	pop r16
	out 0x3F,r16
	ld r16,y+
	.dbline 249
	.dbline 250
	.dbline 246
	.dbline 246
	rjmp L38
X3:
	.dbline -2
L37:
	.dbline 0 ; func end
	ret
	.dbsym r pdata 16 pV
	.dbend
	.dbfunc e OSTCBInit _OSTCBInit fc
;           ptcb -> R10,R11
;            opt -> y+10
;           pext -> y+8
;       stk_size -> y+6
;             id -> y+4
;           pbos -> y+2
;           ptos -> R18,R19
;           prio -> R16
	.even
_OSTCBInit::
	rcall push_gset3x
	.dbline -1
	.dbline 297
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
	.dbline 301
; 
; 
; 
; 
	st -y,r16
	in r16,0x3F
	cli
	push r16
	ld r16,y+
	.dbline 301
	.dbline 302
; 
	lds R10,_OSTCBFreeList
	lds R11,_OSTCBFreeList+1
	.dbline 303
; 
	tst R10
	brne X4
	tst R11
	brne X6
	rjmp L43
X6:
X4:
	.dbline 303
	.dbline 304
; 
	movw R30,R10
	ldd R2,z+2
	ldd R3,z+3
	sts _OSTCBFreeList+1,R3
	sts _OSTCBFreeList,R2
	.dbline 305
; 
	st -y,r16
	pop r16
	out 0x3F,r16
	ld r16,y+
	.dbline 305
	.dbline 306
; 
	std z+0,R18
	std z+1,R19
	.dbline 307
; 
	std z+9,R16
	.dbline 308
; 
	clr R2
	std z+8,R2
	.dbline 309
; 
	clr R3
	std z+6,R2
	std z+7,R3
	.dbline 311
; 
; 
	.dbline 312
; 
	.dbline 313
; 
	.dbline 314
; 
	.dbline 315
; 
	.dbline 317
; 
; 
	mov R2,R16
	lsr R2
	lsr R2
	lsr R2
	std z+11,R2
	.dbline 318
; 
	ldi R24,<_OSMapTbl
	ldi R25,>_OSMapTbl
	ldd R30,z+11
	clr R31
	add R30,R24
	adc R31,R25
	lpm R30,Z
	movw R26,R10
	adiw R26,13
	st x,R30
	.dbline 319
; 
	mov R24,R16
	andi R24,7
	movw R30,R10
	std z+10,R24
	.dbline 320
; 
	ldi R24,<_OSMapTbl
	ldi R25,>_OSMapTbl
	ldd R30,z+10
	clr R31
	add R30,R24
	adc R31,R25
	lpm R30,Z
	movw R26,R10
	adiw R26,12
	st x,R30
	.dbline 322
; 
; 
	st -y,r16
	in r16,0x3F
	cli
	push r16
	ld r16,y+
	.dbline 322
	.dbline 323
; 
	ldi R24,2
	mul R24,R16
	movw R30,R0
	ldi R24,<_OSTCBPrioTbl
	ldi R25,>_OSTCBPrioTbl
	add R30,R24
	adc R31,R25
	std z+0,R10
	std z+1,R11
	.dbline 324
; 
	lds R2,_OSTCBList
	lds R3,_OSTCBList+1
	movw R30,R10
	std z+2,R2
	std z+3,R3
	.dbline 325
; 
	clr R2
	clr R3
	std z+4,R2
	std z+5,R3
	.dbline 326
; 
	lds R2,_OSTCBList
	lds R3,_OSTCBList+1
	tst R2
	brne X5
	tst R3
	breq L45
X5:
	.dbline 326
	.dbline 327
; 
	lds R30,_OSTCBList
	lds R31,_OSTCBList+1
	std z+4,R10
	std z+5,R11
	.dbline 328
; 
L45:
	.dbline 329
; 
	sts _OSTCBList+1,R11
	sts _OSTCBList,R10
	.dbline 330
; 
	movw R30,R10
	ldd R2,z+13
	lds R3,_OSRdyGrp
	or R3,R2
	sts _OSRdyGrp,R3
	.dbline 331
; 
	ldi R24,<_OSRdyTbl
	ldi R25,>_OSRdyTbl
	ldd R2,z+11
	clr R3
	add R2,R24
	adc R3,R25
	ldd R4,z+12
	movw R30,R2
	ldd R5,z+0
	or R5,R4
	std z+0,R5
	.dbline 332
; 
	st -y,r16
	pop r16
	out 0x3F,r16
	ld r16,y+
	.dbline 332
	.dbline 333
; 
	clr R16
	rjmp L42
L43:
	.dbline 334
; 
	.dbline 335
; 
	st -y,r16
	pop r16
	out 0x3F,r16
	ld r16,y+
	.dbline 335
	.dbline 336
; 
	ldi R16,70
	.dbline -2
L42:
	rcall pop_gset3x
	.dbline 0 ; func end
	ret
	.dbsym r ptcb 10 pX
	.dbsym l opt 10 i
	.dbsym l pext 8 pV
	.dbsym l stk_size 6 i
	.dbsym l id 4 i
	.dbsym l pbos 2 pc
	.dbsym r ptos 18 pc
	.dbsym r prio 16 c
	.dbend
	.dbfunc e OSTimeTick _OSTimeTick fV
;           ptcb -> R16,R17
	.even
_OSTimeTick::
	.dbline -1
	.dbline 355
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
; 
	.dbline 358
; 
; 
; 
	lds R16,_OSTCBList
	lds R17,_OSTCBList+1
	rjmp L49
L48:
	.dbline 359
; 
	.dbline 360
; 
	st -y,r16
	in r16,0x3F
	cli
	push r16
	ld r16,y+
	.dbline 360
	.dbline 361
; 
	movw R30,R16
	ldd R2,z+6
	ldd R3,z+7
	tst R2
	brne X7
	tst R3
	brne X9
	rjmp L51
X9:
X7:
	.dbline 361
	.dbline 362
; 
	movw R24,R16
	adiw R24,6
	movw R30,R24
	ldd R24,z+0
	ldd R25,z+1
	sbiw R24,1
	movw R4,R24
	std z+0,R4
	std z+1,R5
	cpi R24,0
	cpc R24,R25
	brne L53
X8:
	.dbline 362
	.dbline 363
; 
	movw R30,R16
	ldd R2,z+8
	sbrc R2,3
	rjmp L55
	.dbline 363
	.dbline 364
; 
	ldd R2,z+13
	lds R3,_OSRdyGrp
	or R3,R2
	sts _OSRdyGrp,R3
	.dbline 365
; 
	ldi R24,<_OSRdyTbl
	ldi R25,>_OSRdyTbl
	ldd R2,z+11
	clr R3
	add R2,R24
	adc R3,R25
	ldd R4,z+12
	movw R30,R2
	ldd R5,z+0
	or R5,R4
	std z+0,R5
	.dbline 366
	rjmp L56
L55:
	.dbline 366
; 
	.dbline 367
; 
	ldi R24,1
	ldi R25,0
	movw R30,R16
	std z+6,R24
	std z+7,R25
	.dbline 368
; 
L56:
	.dbline 369
; 
L53:
	.dbline 370
; 
L51:
	.dbline 371
	movw R30,R16
	ldd R16,z+2
	ldd R17,z+3
	.dbline 372
	st -y,r16
	pop r16
	out 0x3F,r16
	ld r16,y+
	.dbline 372
	.dbline 373
L49:
	.dbline 359
	movw R30,R16
	ldd R24,z+9
	cpi R24,15
	breq X10
	rjmp L48
X10:
	.dbline 374
; 
; 
; 
; 
	st -y,r16
	in r16,0x3F
	cli
	push r16
	ld r16,y+
	.dbline 374
	.dbline 375
; 
	ldi R24,1
	ldi R25,0
	ldi R26,0
	ldi R27,0
	lds R4,_OSTime+2
	lds R5,_OSTime+2+1
	lds R2,_OSTime
	lds R3,_OSTime+1
	add R2,R24
	adc R3,R25
	adc R4,R26
	adc R5,R27
	sts _OSTime+1,R3
	sts _OSTime,R2
	sts _OSTime+2+1,R5
	sts _OSTime+2,R4
	.dbline 376
; 
	st -y,r16
	pop r16
	out 0x3F,r16
	ld r16,y+
	.dbline 376
	.dbline -2
	.dbline 377
; 
L47:
	.dbline 0 ; func end
	ret
	.dbsym r ptcb 16 pX
	.dbend
	.dbfile D:\job\avrtest\光盘\开发板\iccavr\source/os_task.c
	.dbfunc e OSTaskStkInit _OSTaskStkInit fpc
;           stks -> R14,R15
;            tmp -> R12,R13
;            stk -> R10,R11
;            opt -> y+8
;           ptos -> y+6
;          pdata -> R18,R19
;           task -> R16,R17
	.even
_OSTaskStkInit::
	rcall push_gset5x
	.dbline -1
	.dbline 47
	.dbline 54
	.dbline 55
	ldd R10,y+6
	ldd R11,y+7
	.dbline 57
	ldd R24,y+6
	ldd R25,y+7
	subi R24,68
	sbci R25,0
	.dbline 62
	movw R30,R16
	lpm R12,Z+
	lpm R13,Z
	.dbline 65
	movw R2,R24
	sbiw R24,1
	movw R30,R2
	std z+0,R12
	.dbline 66
	movw R2,R24
	sbiw R24,1
	movw R14,R24
	movw R4,R12
	mov R4,R5
	clr R5
	movw R30,R2
	std z+0,R4
	.dbline 68
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	clr R4
	movw R30,R2
	std z+0,R4
	.dbline 69
	movw R2,R24
	sbiw R24,1
	movw R10,R24
	ldi R24,1
	movw R30,R2
	std z+0,R24
	.dbline 70
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,2
	movw R30,R2
	std z+0,R24
	.dbline 71
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,3
	movw R30,R2
	std z+0,R24
	.dbline 72
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,4
	movw R30,R2
	std z+0,R24
	.dbline 73
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,5
	movw R30,R2
	std z+0,R24
	.dbline 74
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,6
	movw R30,R2
	std z+0,R24
	.dbline 75
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,7
	movw R30,R2
	std z+0,R24
	.dbline 76
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,8
	movw R30,R2
	std z+0,R24
	.dbline 77
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,9
	movw R30,R2
	std z+0,R24
	.dbline 78
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,16
	movw R30,R2
	std z+0,R24
	.dbline 79
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,17
	movw R30,R2
	std z+0,R24
	.dbline 80
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,18
	movw R30,R2
	std z+0,R24
	.dbline 81
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,19
	movw R30,R2
	std z+0,R24
	.dbline 82
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,20
	movw R30,R2
	std z+0,R24
	.dbline 83
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,21
	movw R30,R2
	std z+0,R24
	.dbline 84
	movw R12,R18
	.dbline 85
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R30,R2
	std z+0,R12
	.dbline 86
	movw R2,R24
	sbiw R24,1
	movw R4,R12
	mov R4,R5
	clr R5
	movw R30,R2
	std z+0,R4
	.dbline 87
	movw R2,R24
	sbiw R24,1
	movw R10,R24
	ldi R24,24
	movw R30,R2
	std z+0,R24
	.dbline 88
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,25
	movw R30,R2
	std z+0,R24
	.dbline 89
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,32
	movw R30,R2
	std z+0,R24
	.dbline 90
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,33
	movw R30,R2
	std z+0,R24
	.dbline 91
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,34
	movw R30,R2
	std z+0,R24
	.dbline 92
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,35
	movw R30,R2
	std z+0,R24
	.dbline 93
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,36
	movw R30,R2
	std z+0,R24
	.dbline 94
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,37
	movw R30,R2
	std z+0,R24
	.dbline 95
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,38
	movw R30,R2
	std z+0,R24
	.dbline 96
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,39
	movw R30,R2
	std z+0,R24
	.dbline 98
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,48
	movw R30,R2
	std z+0,R24
	.dbline 99
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,49
	movw R30,R2
	std z+0,R24
	.dbline 101
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	ldi R24,128
	movw R30,R2
	std z+0,R24
	.dbline 103
	movw R12,R14
	.dbline 104
	movw R2,R10
	movw R24,R2
	sbiw R24,1
	movw R10,R24
	movw R4,R12
	mov R4,R5
	clr R5
	movw R30,R2
	std z+0,R4
	.dbline 105
	movw R30,R24
	std z+0,R12
	.dbline 106
	mov R16,R24
	mov R17,R25
	.dbline -2
L57:
	rcall pop_gset5x
	.dbline 0 ; func end
	ret
	.dbsym r stks 14 pc
	.dbsym r tmp 12 i
	.dbsym r stk 10 pc
	.dbsym l opt 8 i
	.dbsym l ptos 6 pc
	.dbsym r pdata 18 pV
	.dbsym r task 16 pfV
	.dbend
	.dbfunc e OSTaskCreate _OSTaskCreate fc
;            psp -> R10,R11
;            err -> R10
;           prio -> R12
;           ptos -> y+16
;          pdata -> R14,R15
;           task -> R10,R11
	.even
_OSTaskCreate::
	rcall push_gset5x
	movw R14,R18
	movw R10,R16
	sbiw R28,10
	ldd R12,y+18
	.dbline -1
	.dbline 110
	.dbline 115
	ldi R24,15
	cp R24,R12
	brsh L59
	.dbline 115
	.dbline 116
	ldi R16,42
	rjmp L58
L59:
	.dbline 118
	st -y,r16
	in r16,0x3F
	cli
	push r16
	ld r16,y+
	.dbline 118
	.dbline 119
	ldi R24,2
	mul R24,R12
	movw R30,R0
	ldi R24,<_OSTCBPrioTbl
	ldi R25,>_OSTCBPrioTbl
	add R30,R24
	adc R31,R25
	ldd R2,z+0
	ldd R3,z+1
	tst R2
	breq X12
	rjmp L61
X12:
	tst R3
	breq X13
	rjmp L61
X13:
X11:
	.dbline 119
	.dbline 120
	ldi R24,2
	mul R24,R12
	movw R30,R0
	ldi R24,<_OSTCBPrioTbl
	ldi R25,>_OSTCBPrioTbl
	add R30,R24
	adc R31,R25
	ldi R24,1
	ldi R25,0
	std z+0,R24
	std z+1,R25
	.dbline 122
	st -y,r16
	pop r16
	out 0x3F,r16
	ld r16,y+
	.dbline 122
	.dbline 123
	clr R2
	clr R3
	std y+2,R2
	std y+3,R3
	ldd R0,y+16
	ldd R1,y+17
	std y+0,R0
	std y+1,R1
	movw R18,R14
	movw R16,R10
	rcall _OSTaskStkInit
	movw R10,R16
	.dbline 124
	clr R2
	clr R3
	std y+8,R2
	std y+9,R3
	std y+6,R2
	std y+7,R3
	std y+4,R2
	std y+5,R3
	std y+2,R2
	std y+3,R3
	std y+0,R2
	std y+1,R3
	movw R18,R10
	mov R16,R12
	rcall _OSTCBInit
	mov R10,R16
	.dbline 125
	tst R16
	brne L63
	.dbline 125
	.dbline 126
	st -y,r16
	in r16,0x3F
	cli
	push r16
	ld r16,y+
	.dbline 126
	.dbline 127
	lds R24,_OSTaskCtr
	subi R24,255    ; addi 1
	sts _OSTaskCtr,R24
	.dbline 128
	st -y,r16
	pop r16
	out 0x3F,r16
	ld r16,y+
	.dbline 128
	.dbline 129
	lds R2,_OSRunning
	tst R2
	breq L64
	.dbline 129
	.dbline 130
	rcall _OSSched
	.dbline 131
	.dbline 132
	rjmp L64
L63:
	.dbline 132
	.dbline 133
	st -y,r16
	in r16,0x3F
	cli
	push r16
	ld r16,y+
	.dbline 133
	.dbline 134
	ldi R24,2
	mul R24,R12
	movw R30,R0
	ldi R24,<_OSTCBPrioTbl
	ldi R25,>_OSTCBPrioTbl
	add R30,R24
	adc R31,R25
	clr R2
	clr R3
	std z+0,R2
	std z+1,R3
	.dbline 135
	st -y,r16
	pop r16
	out 0x3F,r16
	ld r16,y+
	.dbline 135
	.dbline 136
L64:
	.dbline 137
	mov R16,R10
	rjmp L58
L61:
	.dbline 138
	.dbline 139
	st -y,r16
	pop r16
	out 0x3F,r16
	ld r16,y+
	.dbline 139
	.dbline 140
	ldi R16,40
	.dbline -2
L58:
	adiw R28,10
	rcall pop_gset5x
	.dbline 0 ; func end
	ret
	.dbsym r psp 10 pV
	.dbsym r err 10 c
	.dbsym r prio 12 c
	.dbsym l ptos 16 pc
	.dbsym r pdata 14 pV
	.dbsym r task 10 pfV
	.dbend
	.dbfile D:\job\avrtest\光盘\开发板\iccavr\source/os_time.c
	.dbfunc e OSTimeDly _OSTimeDly fV
;          ticks -> R10,R11
	.even
_OSTimeDly::
	rcall push_gset3x
	movw R10,R16
	.dbline -1
	.dbline 23
	.dbline 24
	tst R10
	brne X14
	tst R11
	brne X15
	rjmp L68
X15:
X14:
	.dbline 24
	.dbline 25
	st -y,r16
	in r16,0x3F
	cli
	push r16
	ld r16,y+
	.dbline 25
	.dbline 26
	ldi R24,<_OSRdyTbl
	ldi R25,>_OSRdyTbl
	lds R30,_OSTCBCur
	lds R31,_OSTCBCur+1
	ldd R2,z+11
	clr R3
	add R2,R24
	adc R3,R25
	ldd R4,z+12
	com R4
	movw R30,R2
	ldd R5,z+0
	and R5,R4
	mov R4,R5
	std z+0,R4
	tst R5
	brne L70
	.dbline 26
	.dbline 27
	lds R30,_OSTCBCur
	lds R31,_OSTCBCur+1
	ldd R2,z+13
	com R2
	lds R3,_OSRdyGrp
	and R3,R2
	sts _OSRdyGrp,R3
	.dbline 28
L70:
	.dbline 29
	lds R30,_OSTCBCur
	lds R31,_OSTCBCur+1
	std z+6,R10
	std z+7,R11
	.dbline 30
	st -y,r16
	pop r16
	out 0x3F,r16
	ld r16,y+
	.dbline 30
	.dbline 31
	rcall _OSSched
	.dbline 32
L68:
	.dbline -2
	.dbline 33
L67:
	rcall pop_gset3x
	.dbline 0 ; func end
	ret
	.dbsym r ticks 10 i
	.dbend
	.dbfile D:\job\avrtest\光盘\开发板\iccavr\source/74164.c
	.dbfunc e init164 _init164 fV
	.even
_init164::
	.dbline -1
	.dbline 6
	.dbline 7
	sbi 0x17,0
	.dbline 8
	in R24,0x11
	ori R24,192
	out 0x11,R24
	.dbline -2
	.dbline 9
L72:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e write164 _write164 fV
;             ch -> R10
;              i -> R12
;              x -> R16
	.even
_write164::
	rcall push_gset4x
	.dbline -1
	.dbline 11
	.dbline 14
	mov R10,R16
	.dbline 15
	cbi 0x18,0
	.dbline 16
	cbi 0x12,6
	.dbline 17
	clr R12
	rjmp L77
L74:
	.dbline 17
	.dbline 18
	sbrs R10,7
	rjmp L78
	.dbline 19
	sbi 0x12,7
	rjmp L79
L78:
	.dbline 21
	cbi 0x12,7
L79:
	.dbline 22
	lsl R10
	.dbline 23
	sbi 0x12,6
	.dbline 24
	nop
	.dbline 25
	cbi 0x12,6
	.dbline 26
L75:
	.dbline 17
	inc R12
L77:
	.dbline 17
	mov R24,R12
	cpi R24,8
	brlo L74
	.dbline 27
	sbi 0x18,0
	.dbline -2
	.dbline 28
L73:
	rcall pop_gset4x
	.dbline 0 ; func end
	ret
	.dbsym r ch 10 c
	.dbsym r i 12 c
	.dbsym r x 16 c
	.dbend
	.area bss(ram, con, rel)
	.dbfile D:\job\avrtest\光盘\开发板\iccavr\source/74164.c
_OSTCBTbl:
	.blkb 84
	.dbfile D:\job\avrtest\光盘\开发板\iccavr\source/os_core.c
	.dbsym s OSTCBTbl _OSTCBTbl A[84:6]X
_OSTaskIdleStk:
	.blkb 100
	.dbsym s OSTaskIdleStk _OSTaskIdleStk A[100:100]c
_OSIntExitY:
	.blkb 1
	.dbsym s OSIntExitY _OSIntExitY c
_OSTime::
	.blkb 4
	.dbfile D:\job\avrtest\光盘\开发板\iccavr\source/UCOS_II.H
	.dbsym e OSTime _OSTime l
_OSTCBPrioTbl::
	.blkb 32
	.dbsym e OSTCBPrioTbl _OSTCBPrioTbl A[32:16]pX
_OSTCBList::
	.blkb 2
	.dbsym e OSTCBList _OSTCBList pX
_OSTCBHighRdy::
	.blkb 2
	.dbsym e OSTCBHighRdy _OSTCBHighRdy pX
_OSTCBFreeList::
	.blkb 2
	.dbsym e OSTCBFreeList _OSTCBFreeList pX
_OSTCBCur::
	.blkb 2
	.dbsym e OSTCBCur _OSTCBCur pX
_OSTaskCtr::
	.blkb 1
	.dbsym e OSTaskCtr _OSTaskCtr c
_OSRunning::
	.blkb 1
	.dbsym e OSRunning _OSRunning c
_OSRdyTbl::
	.blkb 2
	.dbsym e OSRdyTbl _OSRdyTbl A[2:2]c
_OSRdyGrp::
	.blkb 1
	.dbsym e OSRdyGrp _OSRdyGrp c
_OSPrioHighRdy::
	.blkb 1
	.dbsym e OSPrioHighRdy _OSPrioHighRdy c
_OSPrioCur::
	.blkb 1
	.dbsym e OSPrioCur _OSPrioCur c
_OSLockNesting::
	.blkb 1
	.dbsym e OSLockNesting _OSLockNesting c
_OSIntNesting::
	.blkb 1
	.dbsym e OSIntNesting _OSIntNesting c
_OSIdleCtr::
	.blkb 4
	.dbsym e OSIdleCtr _OSIdleCtr l
_OSEventTbl::
	.blkb 16
	.dbsym e OSEventTbl _OSEventTbl A[16:2]X
_OSEventFreeList::
	.blkb 2
	.dbsym e OSEventFreeList _OSEventFreeList pX
_OSCtxSwCtr::
	.blkb 4
	.dbsym e OSCtxSwCtr _OSCtxSwCtr l
	.area func_lit
PL_OSTaskIdle:	.word `_OSTaskIdle
