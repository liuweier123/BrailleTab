;*******************************************************************************
;                                   uC/OS-II
;                             The Real-Time Kernel
;
;                         ATmega103 Specific code
;                               (ICC V6.21)
;
;
; File:			OS_CPU_A.S
; By:			Ole Saether
; Modified by:	Joerg Meyer
; Port Version:	V1.00
;
;
;*******************************************************************************

;include 

;*******************************************************************************
;                 I/O PORT ADDRESSES
;*******************************************************************************


SREG    = 0x3F
SPH     = 0x3E
SPL     = 0x3D
RAMPZ   = 0x3B
TCNT0   = 0x32
TCNT2   = 0x24


;*******************************************************************************
;                MACROS
;*******************************************************************************

				; Push registers
				.macro PUSHRS
                ST      -Y,R0	
                ST      -Y,R1
                ST      -Y,R2
                ST      -Y,R3
                ST      -Y,R4
                ST      -Y,R5
                ST      -Y,R6
                ST      -Y,R7
                ST      -Y,R8
                ST      -Y,R9
                ST      -Y,R10
                ST      -Y,R11
                ST      -Y,R12
                ST      -Y,R13
                ST      -Y,R14
                ST      -Y,R15
                ST      -Y,R16
                ST      -Y,R17
                ST      -Y,R18
                ST      -Y,R19
                ST      -Y,R20
                ST      -Y,R21
                ST      -Y,R22
                ST      -Y,R23
                ST      -Y,R24
                ST      -Y,R25
                ST      -Y,R26
                ST      -Y,R27
                ST      -Y,R30
                ST      -Y,R31
				.endmacro

				; Pop registers
                .macro POPRS
                LD      R31,Y+
                LD      R30,Y+
                LD      R27,Y+
                LD      R26,Y+
                LD      R25,Y+
                LD      R24,Y+
                LD      R23,Y+
                LD      R22,Y+
                LD      R21,Y+
                LD      R20,Y+
                LD      R19,Y+
                LD      R18,Y+
                LD      R17,Y+
                LD      R16,Y+
                LD      R15,Y+
                LD      R14,Y+
                LD      R13,Y+
                LD      R12,Y+
                LD      R11,Y+
                LD      R10,Y+
                LD      R9,Y+
                LD      R8,Y+
                LD      R7,Y+
                LD      R6,Y+
                LD      R5,Y+
                LD      R4,Y+
                LD      R3,Y+
                LD      R2,Y+
                LD      R1,Y+
                LD      R0,Y+
                .endmacro

				; Push stack pointer
                .macro PUSHSP
                IN      R16,SPH
                ST      -Y,R16
                IN      R16,SPL
                ST      -Y,R16
                .endmacro

				; Pop stack pointer
                .macro POPSP
                LD      R16,Y+
                OUT     SPL,R16
                LD      R16,Y+
                OUT     SPH,R16
                .endmacro

				;Push SREG
		.macro PUSHSREG
                IN      R16,SREG
                ST      -Y,R16
                .endmacro

				; Pop SREG
                .macro POPSREG
                LD      R16,Y+
                OUT     SREG,R16
				.endmacro

                .area    text(rel)

;*******************************************************************************
;               START HIGHEST PRIORITY TASK READY-TO-RUN
;
; Description : This function is called by OSStart() to start the highest
; priority task that was created by your application before calling OSStart().
;
; Note(s):
;	1) The (data)stack frame is assumed to look as follows:
;
;		OSTCBHighRdy->OSTCBStkPtr --> LSB of (return) stack pointer (Low memory)
;										MSB of (return) stack pointer
;										Flags to load in status register
;										R31
;										R30
;										R7
;										.
;										.
;										.
;										R0  (High memory)
;
;		where the stack pointer points to the task start address.
;
;
;	2) OSStartHighRdy() MUST:
;		a) Call OSTaskSwHook() then,
;		b) Set OSRunning to TRUE,
;		c) Switch to the highest priority task.
;*******************************************************************************

_OSStartHighRdy:: 
	LDS     R16,_OSRunning		; Indicate that we are multitasking
	INC     R16					
	STS     _OSRunning,R16		;

	LDS     R30,_OSTCBHighRdy	; Let Z point to TCB of highest priority task
	LDS     R31,_OSTCBHighRdy+1	; ready to run
	LD      R28,Z+				; Load Y (R29:R28) pointer
	LD      R29,Z+				;

	POPSP		; restore stack pointer
	POPSREG		; restore SREG
	POPRS		; restore registers
	RET			; start task

;*******************************************************************************
;                 TASK LEVEL CONTEXT SWITCH
;
; Description : This function is called when a task makes a higher priority task
; ready-to-run.
;
; Note(s):
;	1) Upon entry,
;		OSTCBCur     points to the OS_TCB of the task to suspend
;		OSTCBHighRdy points to the OS_TCB of the task to resume
;
;	2) The stack frame of the task to suspend looks as follows:
;
;		SP	+0 --> LSB of task code address
;			+1     MSB of task code address	(High memory)
;
;	3) The saved context of the task to resume looks as follows:
;
;		OSTCBHighRdy->OSTCBStkPtr --> LSB of (return) stack pointer (Low memory)
;                                     MSB of (return) stack pointer
;                                     Flags to load in status register
;                                     R31
;                                     R30
;                                     R7
;                                     .
;                                     .
;                                     .
;                                     R0    (High memory)
;*******************************************************************************

_OSCtxSw::
		PUSHRS						; Save current task's context
		PUSHSREG
		PUSHSP

		LDS     R30,_OSTCBCur		; Z = OSTCBCur->OSTCBStkPtr
		LDS     R31,_OSTCBCur+1		;
		ST      Z+,R28				; Save Y (R29:R28) pointer
		ST      Z+,R29				;
	
		LDS     R16,_OSPrioHighRdy	; OSPrioCur = OSPrioHighRdy
		STS     _OSPrioCur,R16
	
		LDS     R30,_OSTCBHighRdy ; Let Z point to TCB of highest priority task
		LDS     R31,_OSTCBHighRdy+1	; ready to run
		STS     _OSTCBCur,R30		; OSTCBCur = OSTCBHighRdy
		STS     _OSTCBCur+1,R31 	;

		LD      R28,Z+		; Restore Y pointer
		LD      R29,Z+		;

		POPSP				; restore stack pointer
		POPSREG				; restore SREG
		POPRS				; restore registers
		RET


;*******************************************************************************
;               INTERRUPT LEVEL CONTEXT SWITCH
;
; Description : This function is called by OSIntExit() to perform a context
; switch to a task that has been made ready-to-run by an ISR.
;
; Note(s):
;	1) Upon entry,
;		OSTCBCur     points to the OS_TCB of the task to suspend
;		OSTCBHighRdy points to the OS_TCB of the task to resume
;
;	2) The stack frame of the task to suspend looks as follows:
;
;		SP	+0 --> LSB of return address of OSIntCtxSw()   (Low memory)
;			+1     MSB of return address of OSIntCtxSw()
;			+2     LSB of return address of OSIntExit()
;			+3     MSB of return address of OSIntExit()
;			+4     LSB of task code address
;			+5     MSB of task code address		(High memory)
;
;	3) The saved context of the task to resume looks as follows:
;
;		OSTCBHighRdy->OSTCBStkPtr --> 	LSB of (return) stack pointer (Low mem)
;										MSB of (return) stack pointer
;										Flags to load in status register
;										R31
;										R30
;										R7
;										.
;										.
;										.
;										R0		(High memory)
;*******************************************************************************

_OSIntCtxSw::
		IN      R30,SPL				; Z = SP
		IN      R31,SPH
	;	ADIW    R30,4	; (Uncomment if OS_CRITICAL_METHOD is 1, see OS_CPU.H)
		ADIW    R30,5				; Adjust Z to point to task return address
		ST      -Y,R31				; Save SP
		ST      -Y,R30				;
	
		LDS     R30,_OSTCBCur		; Z = OSTCBCur->OSTCBStkPtr
		LDS     R31,_OSTCBCur+1		;
		ST      Z+,R28				; Save Y pointer
		ST      Z+,R29				;

		LDS     R16,_OSPrioHighRdy	; OSPrioCur = OSPrioHighRdy
		STS     _OSPrioCur,R16	;

		LDS     R30,_OSTCBHighRdy	; Z = OSTCBHighRdy->OSTCBStkPtr
		LDS     R31,_OSTCBHighRdy+1	;
		STS     _OSTCBCur,R30		; OSTCBCur = OSTCBHighRdy
		STS     _OSTCBCur+1,R31		;

		LD      R28,Z+				; Restore Y pointer
		LD      R29,Z+				;
		POPSP						; restore stack pointer
		POPSREG						; restore SREG
		POPRS						; restore registers
		RET

;******************************************************************************
;                          SYSTEM TICK ISR
;
; Description: This function is the ISR used to notify uC/OS-II that a system
; tick has occurred.
;
;
;*******************************************************************************
; 
_OSTickISR::    
        NOP
		PUSHRS				; save all registers
		IN	R16, SREG
		SBR	R16, 0x80		; bei Aufruf dieser ISR geloeschtes I-Flag setzen 
		ST	-Y, R16

		; TimerCounter aufrischen
		LDI     R16,6; Reload TC_2, 2ms bei 8MHz
		OUT     TCNT2,R16

		LDS     R16,_OSIntNesting           ; Notify uC/OS-II of ISR
		INC     R16                         ;
		STS     _OSIntNesting,R16           ;

		CALL    _OSTimeTick		; Call uC/OS-II's tick updating function
		; bearbeitet die tasktimer, wenn 0 --> deren Prio in Aufruftab stellen

		CALL    _OSIntExit		; Notify uC/OS-II about end of ISR
		; fuehrt gegebenfalls einen Context-Switch aus

		POPSREG		; restore SREG
		POPRS		; restore all registers
		RET			; Note: RET instead of RETI

;*******************************************************************************
;
;*******************************************************************************

