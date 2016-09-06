	.module test2.c
	.area text(rom, con, rel)
	.dbfile D:\job\avrtest\光盘\开发板\iccavr\test\test2.c
	.dbfunc e uart0_init _uart0_init fV
	.even
_uart0_init::
	.dbline -1
	.dbline 29
; 
; #define Test1_GLOBALS
; #include "includes.h"
; 
; //******************************************************************************
; // Constants
; #define TaskStartPrio	10		// Task-Prioritaeten
; //*****************************************************************************
; // Variablen
; INT8U    display[5];
; INT8U    h,m,s,state;
; OS_STK	Task1Stack[OS_TASK_DEF_STK_SIZE];		// startup task stack
; OS_STK	Task2Stack[OS_TASK_DEF_STK_SIZE];
; //ICC-AVR application builder : 2003-12-28 21:52:56
; // Target : M8
; // Crystal: 8.0000Mhz
; 
; #include <iom8v.h>
; #include <macros.h>
; #include <stdio.h>
; 
; 
; //UART0 initialisation
; // desired baud rate: 9600
; // actual: baud rate:9615 (0.2%)
; // char size: 8 bit
; // parity: Disabled
; void uart0_init(void)
; {
	.dbline 30
;  UCSRB = 0x00; //disable while setting baud rate
	clr R2
	out 0xa,R2
	.dbline 31
;  UCSRA = 0x00;
	out 0xb,R2
	.dbline 32
;  UCSRC = 0x86;
	ldi R24,134
	out 0x20,R24
	.dbline 33
;  UBRRL = 0x33; //set baud rate lo
	ldi R24,51
	out 0x9,R24
	.dbline 34
;  UBRRH = 0x00; //set baud rate hi
	out 0x20,R2
	.dbline 35
;  UCSRB = 0x08;
	ldi R24,8
	out 0xa,R24
	.dbline -2
	.dbline 36
; }
L2:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e TC2_Init _TC2_Init fV
	.even
_TC2_Init::
	.dbline -1
	.dbline 45
; 
; //*****************************************************************************
; // Prototypes
; 
; //*****************************************************************************
; //			TickISR
; //*****************************************************************************
; // Init Timer/Counter2 fuer Takterzeugung
; void TC2_Init (void){	
	.dbline 49
; 	/* Only uses TIMER2 overflow for tick interrupt. Timer compare
;      * can also be used.
;      */
; 	TIMSK &= ~(BIT(TOIE2)/* | BIT(OCIE2) */);	//disable TC2 interrupts
	in R24,0x39
	andi R24,191
	out 0x39,R24
	.dbline 50
; 	TCCR2 = 0x00;		// interner Takt, /1024
	clr R2
	out 0x25,R2
	.dbline 51
; 	TCNT2 = 0; 	// Counter ruecksetzen, 2ms @ 8MHz
	out 0x24,R2
	.dbline 52
;     TCCR2 = 0x04;   // 64
	ldi R24,4
	out 0x25,R24
	.dbline 54
; 	// OCR2 = 180;			// OutputCompareRegister
; 	TIMSK |= BIT(TOIE2);	// enable OVF-interrupt
	in R24,0x39
	ori R24,64
	out 0x39,R24
	.dbline 57
; 	                                                                                                                                //TIMSK |= OCIE2;		// enable COMP-interrupt
; 	
;     SEI();	// enable global interrupt     
	sei
	.dbline -2
	.dbline 58
; }
L3:
	.dbline 0 ; func end
	ret
	.dbend
	.area vector(rom, abs)
	.org 8
	rjmp _OSTickISR
	.area text(rom, con, rel)
	.dbfile D:\job\avrtest\光盘\开发板\iccavr\test\test2.c
	.dbfunc e main _main fV
	.even
_main::
	sbiw R28,3
	.dbline -1
	.dbline 70
; 
; //*****************************************************************************
; // Interrupt Timer/Counter0 Overflow
; // OVF_Takt:  4MHz / 1024 / 39 = 10ms
; #pragma interrupt_handler OSTickISR:5
; 
; void Task1(void *pdata);
; void Task2(void *pdata);
; 
; //*****************************************************************************
; // Start
; void main(void){
	.dbline 71
; 	OSInit();		// OS init
	rcall _OSInit
	.dbline 72
; 	OSTaskCreate(Task1,
	ldi R24,7
	std y+2,R24
	ldi R24,<_Task1Stack+99
	ldi R25,>_Task1Stack+99
	std y+0,R24
	std y+1,R25
	clr R18
	clr R19
	ldi R16,<PL_Task1
	ldi R17,>PL_Task1
	rcall _OSTaskCreate
	.dbline 76
; 				(void *)0,
; 				&Task1Stack[OS_TASK_DEF_STK_SIZE-1],
; 				7);
; 	OSTaskCreate(Task2,
	ldi R24,8
	std y+2,R24
	ldi R24,<_Task2Stack+99
	ldi R25,>_Task2Stack+99
	std y+0,R24
	std y+1,R25
	clr R18
	clr R19
	ldi R16,<PL_Task2
	ldi R17,>PL_Task2
	rcall _OSTaskCreate
	.dbline 81
; 				(void *)0,
; 				&Task2Stack[OS_TASK_DEF_STK_SIZE-1],
; 				8); 
; 	// init und start tick
;     TC2_Init();			// Timer/Counter#2 Overflow and Comp init
	rcall _TC2_Init
	.dbline 82
;     uart0_init();
	rcall _uart0_init
	.dbline 83
;     OSStart();		// start multitasking
	rcall _OSStart
	.dbline -2
	.dbline 84
; }
L4:
	adiw R28,3
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e Task1 _Task1 fV
;           key2 -> R12
;              i -> R14
;           key1 -> y+0
;           data -> R10,R11
	.even
_Task1::
	rcall push_gset5x
	movw R10,R16
	sbiw R28,1
	.dbline -1
	.dbline 87
; 
; //*****************************************************************************
; void Task1(void *data){
	.dbline 89
;     unsigned char i,key1,key2;
; 	data = data;
	.dbline 90
; 	PORTD |= 0x1C;    //  key
	in R24,0x12
	ori R24,28
	out 0x12,R24
	.dbline 91
; 	DDRD  &= ~0x1C;
	in R24,0x11
	andi R24,227
	out 0x11,R24
	.dbline 92
; 	PORTD |= 0x20;    //  bell
	sbi 0x12,5
	.dbline 93
; 	DDRD  |= 0x20;
	sbi 0x11,5
	.dbline 94
; 	init164();        //  显示  初始化
	rcall _init164
	.dbline 95
; 	state = 1;
	ldi R24,1
	sts _state,R24
	.dbline 96
L8:
	.dbline 96
; 	for (;;){
	.dbline 98
; //  key
;         key1 = PIND & 0x1C;
	in R24,0x10
	andi R24,28
	std y+0,R24
	.dbline 99
; 		if(key1 == 0x1C){
	cpi R24,28
	brne L12
	.dbline 99
	.dbline 100
; 		    PORTD &= ~0x20;
	cbi 0x12,5
	.dbline 101
; 			if(key2 == 0x0C){
	mov R24,R12
	cpi R24,12
	brne L14
	.dbline 101
	.dbline 102
; 				state ^= 0x01;
	ldi R24,1
	lds R2,_state
	eor R2,R24
	sts _state,R2
	.dbline 103
; 			}
L14:
	.dbline 104
; 			if(state == 0){
	lds R2,_state
	tst R2
	brne L13
	.dbline 104
	.dbline 105
; 			    if(key2 == 0x18){
	mov R24,R12
	cpi R24,24
	brne L18
	.dbline 105
	.dbline 106
; 			        if(++s == 60) s = 0;
	lds R24,_s
	subi R24,255    ; addi 1
	mov R2,R24
	sts _s,R2
	cpi R24,60
	brne L20
	.dbline 106
	clr R2
	sts _s,R2
L20:
	.dbline 107
; 			    }
L18:
	.dbline 108
; 			    if(key2 == 0x14){
	mov R24,R12
	cpi R24,20
	brne L13
	.dbline 108
	.dbline 109
; 				    if(++m == 60) m = 0;
	lds R24,_m
	subi R24,255    ; addi 1
	mov R2,R24
	sts _m,R2
	cpi R24,60
	brne L13
	.dbline 109
	clr R2
	sts _m,R2
	.dbline 110
; 			    }
	.dbline 111
; 			}
	.dbline 112
; 		}
	rjmp L13
L12:
	.dbline 113
; 		else{
	.dbline 114
; 			PORTD |= 0x20;
	sbi 0x12,5
	.dbline 115
; 		}
L13:
	.dbline 116
; 		key2 = key1;
	ldd R12,y+0
	.dbline 120
; //  end  key
; 
; //  display
;         display[0] = s%10;
	ldi R17,10
	lds R16,_s
	rcall mod8u
	sts _display,R16
	.dbline 121
; 		display[1] = s/10;
	ldi R17,10
	lds R16,_s
	rcall div8u
	sts _display+1,R16
	.dbline 122
; 		display[2] = m%10;
	ldi R17,10
	lds R16,_m
	rcall mod8u
	sts _display+2,R16
	.dbline 123
; 		display[3] = m/10;
	ldi R17,10
	lds R16,_m
	rcall div8u
	sts _display+3,R16
	.dbline 124
	mov R10,R14
	clr R11
	tst R10
	brne X0
	tst R11
	breq L32
X0:
	movw R24,R10
	cpi R24,1
	ldi R30,0
	cpc R25,R30
	breq L33
	cpi R24,2
	ldi R30,0
	cpc R25,R30
	breq L34
	cpi R24,3
	ldi R30,0
	cpc R25,R30
	breq L35
	rjmp L29
X1:
	.dbline 124
; 		switch(i){
L32:
	.dbline 125
; 		    case  0:  write164(display[i] | 0x70);  break;
	ldi R24,<_display
	ldi R25,>_display
	mov R30,R14
	clr R31
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	ori R16,112
	rcall _write164
	.dbline 125
	rjmp L30
L33:
	.dbline 126
; 		    case  1:  write164(display[i] | 0xB0);  break;
	ldi R24,<_display
	ldi R25,>_display
	mov R30,R14
	clr R31
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	ori R16,176
	rcall _write164
	.dbline 126
	rjmp L30
L34:
	.dbline 127
; 		    case  2:  write164(display[i] | 0xD0);  break;
	ldi R24,<_display
	ldi R25,>_display
	mov R30,R14
	clr R31
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	ori R16,208
	rcall _write164
	.dbline 127
	rjmp L30
L35:
	.dbline 128
; 		    case  3:  write164(display[i] | 0xE0);  break;
	ldi R24,<_display
	ldi R25,>_display
	mov R30,R14
	clr R31
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	ori R16,224
	rcall _write164
	.dbline 128
L29:
L30:
	.dbline 130
; 		}
; 		if(++i > 3) i = 0;
	mov R24,R14
	subi R24,255    ; addi 1
	mov R2,R24
	mov R14,R24
	ldi R24,3
	cp R24,R2
	brsh L36
	.dbline 130
	clr R14
L36:
	.dbline 132
	ldi R16,2
	ldi R17,0
	rcall _OSTimeDly
	.dbline 133
	.dbline 96
	.dbline 96
	rjmp L8
X2:
	.dbline -2
L7:
	adiw R28,1
	rcall pop_gset5x
	.dbline 0 ; func end
	ret
	.dbsym r key2 12 c
	.dbsym r i 14 c
	.dbsym l key1 0 c
	.dbsym r data 10 pV
	.dbend
	.dbfunc e Task2 _Task2 fV
;           data -> R10,R11
	.even
_Task2::
	rcall push_gset3x
	movw R10,R16
	.dbline -1
	.dbline 135
; //end  display		
; 		OSTimeDly (2);
; 	}
; }
; void Task2(void *data){
	.dbline 136
;     data = data;
	.dbline 137
; 	OSTimeDly(5);
	ldi R16,5
	ldi R17,0
	rcall _OSTimeDly
	.dbline 138
; 	s = EEPROMread(1);
	ldi R16,1
	ldi R17,0
	rcall _EEPROMread
	sts _s,R16
	.dbline 139
; 	m = EEPROMread(2);
	ldi R16,2
	ldi R17,0
	rcall _EEPROMread
	sts _m,R16
	.dbline 140
L39:
	.dbline 140
; 	for (;;){
	.dbline 141
; 	    if(state == 1){
	lds R24,_state
	cpi R24,1
	brne L43
	.dbline 141
	.dbline 142
; 	        if(++s == 60){
	lds R24,_s
	subi R24,255    ; addi 1
	mov R2,R24
	sts _s,R2
	cpi R24,60
	brne L45
	.dbline 142
	.dbline 143
; 		        s = 0;
	clr R2
	sts _s,R2
	.dbline 144
; 			    if(++m == 60){
	lds R24,_m
	subi R24,255    ; addi 1
	mov R2,R24
	sts _m,R2
	cpi R24,60
	brne L47
	.dbline 144
	.dbline 145
; 			        m = 0;
	clr R2
	sts _m,R2
	.dbline 146
; 				    if(++h == 24) h=0;
	lds R24,_h
	subi R24,255    ; addi 1
	mov R2,R24
	sts _h,R2
	cpi R24,24
	brne L49
	.dbline 146
	clr R2
	sts _h,R2
L49:
	.dbline 147
; 			    }
L47:
	.dbline 148
; 		    }
L45:
	.dbline 149
; 			EEPROMwrite(1,s);
	lds R18,_s
	ldi R16,1
	ldi R17,0
	rcall _EEPROMwrite
	.dbline 150
; 			EEPROMwrite(2,m);
	lds R18,_m
	ldi R16,2
	ldi R17,0
	rcall _EEPROMwrite
	.dbline 151
; 		}
L43:
	.dbline 152
	ldi R16,10
	rcall _putchar
	.dbline 153
	lds R16,_display+3
	subi R16,208    ; addi 48
	rcall _putchar
	.dbline 154
	lds R16,_display+2
	subi R16,208    ; addi 48
	rcall _putchar
	.dbline 155
	ldi R16,58
	rcall _putchar
	.dbline 156
	lds R16,_display+1
	subi R16,208    ; addi 48
	rcall _putchar
	.dbline 157
	lds R16,_display
	subi R16,208    ; addi 48
	rcall _putchar
	.dbline 158
	ldi R16,500
	ldi R17,1
	rcall _OSTimeDly
	.dbline 159
	.dbline 140
	.dbline 140
	rjmp L39
X3:
	.dbline -2
L38:
	rcall pop_gset3x
	.dbline 0 ; func end
	ret
	.dbsym r data 10 pV
	.dbend
	.area bss(ram, con, rel)
	.dbfile D:\job\avrtest\光盘\开发板\iccavr\test\test2.c
_Task2Stack::
	.blkb 100
	.dbsym e Task2Stack _Task2Stack A[100:100]c
_Task1Stack::
	.blkb 100
	.dbsym e Task1Stack _Task1Stack A[100:100]c
_state::
	.blkb 1
	.dbsym e state _state c
_s::
	.blkb 1
	.dbsym e s _s c
_m::
	.blkb 1
	.dbsym e m _m c
_h::
	.blkb 1
	.dbsym e h _h c
_display::
	.blkb 5
	.dbsym e display _display A[5:5]c
	.area func_lit
PL_Task2:	.word `_Task2
PL_Task1:	.word `_Task1
