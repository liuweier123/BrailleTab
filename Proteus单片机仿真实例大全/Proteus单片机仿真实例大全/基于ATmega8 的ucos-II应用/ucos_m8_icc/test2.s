	.module test2.c
	.area text(rom, con, rel)
	.dbfile F:\ICC\project\ucos_m8_icc\test\test2.c
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
	.dbfile F:\ICC\project\ucos_m8_icc\test\test2.c
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
; 	uart0_init();
	rcall _uart0_init
	.dbline 73
; 	puts("ATmega8 uc/os-II Test!");
	ldi R16,<L5
	ldi R17,>L5
	rcall _puts
	.dbline 74
; 	putchar(0x0d);
	ldi R16,13
	rcall _putchar
	.dbline 75
; 	putchar(0x0a);
	ldi R16,10
	rcall _putchar
	.dbline 77
; 	
; 	OSTaskCreate(Task1,	(void *)0, &Task1Stack[OS_TASK_DEF_STK_SIZE-1],	7);
	ldi R24,7
	std y+2,R24
	ldi R24,<_Task1Stack+99
	ldi R25,>_Task1Stack+99
	std y+1,R25
	std y+0,R24
	clr R18
	clr R19
	ldi R16,<PL_Task1
	ldi R17,>PL_Task1
	rcall _OSTaskCreate
	.dbline 79
; 	
; 	OSTaskCreate(Task2,	(void *)0, &Task2Stack[OS_TASK_DEF_STK_SIZE-1],	8); 
	ldi R24,8
	std y+2,R24
	ldi R24,<_Task2Stack+99
	ldi R25,>_Task2Stack+99
	std y+1,R25
	std y+0,R24
	clr R18
	clr R19
	ldi R16,<PL_Task2
	ldi R17,>PL_Task2
	rcall _OSTaskCreate
	.dbline 81
; 	// init und start tick
;     TC2_Init();			// Timer/Counter#2 Overflow and Comp init   
	rcall _TC2_Init
	.dbline 82
;     OSStart();		// start multitasking
	rcall _OSStart
	.dbline -2
	.dbline 83
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
	.dbline 86
; 
; //*****************************************************************************
; void Task1(void *data){
	.dbline 88
;     unsigned char i,key1,key2;
; 	data = data;
	.dbline 89
; 	PORTD |= 0x1C;    //  key
	in R24,0x12
	ori R24,28
	out 0x12,R24
	.dbline 90
; 	DDRD  &= ~0x1C;
	in R24,0x11
	andi R24,227
	out 0x11,R24
	.dbline 91
; 	PORTD |= 0x20;    //  bell
	sbi 0x12,5
	.dbline 92
; 	DDRD  |= 0x20;
	sbi 0x11,5
	.dbline 93
; 	init164();        //  œ‘ æ  ≥ı ºªØ
	rcall _init164
	.dbline 94
; 	state = 1;
	ldi R24,1
	sts _state,R24
	.dbline 95
L9:
	.dbline 95
; 	for (;;){
	.dbline 97
; //  key
;         key1 = PIND & 0x1C;
	in R24,0x10
	andi R24,28
	std y+0,R24
	.dbline 98
; 		if(key1 == 0x1C){
	cpi R24,28
	brne L13
	.dbline 98
	.dbline 99
; 		    PORTD &= ~0x20;
	cbi 0x12,5
	.dbline 100
; 			if(key2 == 0x0C){
	mov R24,R12
	cpi R24,12
	brne L15
	.dbline 100
	.dbline 101
; 				state ^= 0x01;
	ldi R24,1
	lds R2,_state
	eor R2,R24
	sts _state,R2
	.dbline 102
; 			}
L15:
	.dbline 103
; 			if(state == 0){
	lds R2,_state
	tst R2
	brne L14
	.dbline 103
	.dbline 104
; 			    if(key2 == 0x18){
	mov R24,R12
	cpi R24,24
	brne L19
	.dbline 104
	.dbline 105
; 			        if(++s == 60) s = 0;
	lds R24,_s
	subi R24,255    ; addi 1
	mov R2,R24
	sts _s,R2
	cpi R24,60
	brne L21
	.dbline 105
	clr R2
	sts _s,R2
L21:
	.dbline 106
; 			    }
L19:
	.dbline 107
; 			    if(key2 == 0x14){
	mov R24,R12
	cpi R24,20
	brne L14
	.dbline 107
	.dbline 108
; 				    if(++m == 60) m = 0;
	lds R24,_m
	subi R24,255    ; addi 1
	mov R2,R24
	sts _m,R2
	cpi R24,60
	brne L14
	.dbline 108
	clr R2
	sts _m,R2
	.dbline 109
; 			    }
	.dbline 110
; 			}
	.dbline 111
; 		}
	rjmp L14
L13:
	.dbline 112
; 		else{
	.dbline 113
; 			PORTD |= 0x20;
	sbi 0x12,5
	.dbline 114
; 		}
L14:
	.dbline 115
; 		key2 = key1;
	ldd R12,y+0
	.dbline 119
; //  end  key
; 
; //  display
;         display[0] = s%10;
	ldi R17,10
	lds R16,_s
	rcall mod8u
	sts _display,R16
	.dbline 120
; 		display[1] = s/10;
	ldi R17,10
	lds R16,_s
	rcall div8u
	sts _display+1,R16
	.dbline 121
; 		display[2] = m%10;
	ldi R17,10
	lds R16,_m
	rcall mod8u
	sts _display+2,R16
	.dbline 122
; 		display[3] = m/10;
	ldi R17,10
	lds R16,_m
	rcall div8u
	sts _display+3,R16
	.dbline 123
	mov R10,R14
	clr R11
	tst R10
	brne X0
	tst R11
	breq L33
X0:
	movw R24,R10
	cpi R24,1
	ldi R30,0
	cpc R25,R30
	breq L34
	cpi R24,2
	ldi R30,0
	cpc R25,R30
	breq L35
	cpi R24,3
	ldi R30,0
	cpc R25,R30
	breq L36
	rjmp L30
X1:
	.dbline 123
; 		switch(i){
L33:
	.dbline 124
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
	.dbline 124
	rjmp L31
L34:
	.dbline 125
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
	.dbline 125
	rjmp L31
L35:
	.dbline 126
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
	.dbline 126
	rjmp L31
L36:
	.dbline 127
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
	.dbline 127
L30:
L31:
	.dbline 129
; 		}
; 		if(++i > 3) i = 0;
	mov R24,R14
	subi R24,255    ; addi 1
	mov R14,R24
	ldi R24,3
	cp R24,R14
	brsh L37
	.dbline 129
	clr R14
L37:
	.dbline 131
	ldi R16,2
	ldi R17,0
	rcall _OSTimeDly
	.dbline 132
	.dbline 95
	.dbline 95
	rjmp L9
X2:
	.dbline -2
L8:
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
	.dbline 134
; //end  display		
; 		OSTimeDly (2);
; 	}
; }
; void Task2(void *data){
	.dbline 135
;     data = data;
	.dbline 136
; 	OSTimeDly(5);
	ldi R16,5
	ldi R17,0
	rcall _OSTimeDly
	.dbline 137
; 	s = EEPROMread(1);
	ldi R16,1
	ldi R17,0
	rcall _EEPROMread
	sts _s,R16
	.dbline 138
; 	m = EEPROMread(2);
	ldi R16,2
	ldi R17,0
	rcall _EEPROMread
	sts _m,R16
	.dbline 139
L40:
	.dbline 139
; 	for (;;){
	.dbline 140
; 	    if(state == 1){
	lds R24,_state
	cpi R24,1
	brne L44
	.dbline 140
	.dbline 141
; 	        if(++s == 60){
	lds R24,_s
	subi R24,255    ; addi 1
	mov R2,R24
	sts _s,R2
	cpi R24,60
	brne L46
	.dbline 141
	.dbline 142
; 		        s = 0;
	clr R2
	sts _s,R2
	.dbline 143
; 			    if(++m == 60){
	lds R24,_m
	subi R24,255    ; addi 1
	mov R2,R24
	sts _m,R2
	cpi R24,60
	brne L48
	.dbline 143
	.dbline 144
; 			        m = 0;
	clr R2
	sts _m,R2
	.dbline 145
; 				    if(++h == 24) h=0;
	lds R24,_h
	subi R24,255    ; addi 1
	mov R2,R24
	sts _h,R2
	cpi R24,24
	brne L50
	.dbline 145
	clr R2
	sts _h,R2
L50:
	.dbline 146
; 			    }
L48:
	.dbline 147
; 		    }
L46:
	.dbline 148
; 			EEPROMwrite(1,s);
	lds R18,_s
	ldi R16,1
	ldi R17,0
	rcall _EEPROMwrite
	.dbline 149
; 			EEPROMwrite(2,m);
	lds R18,_m
	ldi R16,2
	ldi R17,0
	rcall _EEPROMwrite
	.dbline 150
; 		}
L44:
	.dbline 151
	ldi R16,10
	rcall _putchar
	.dbline 152
	lds R16,_display+3
	subi R16,208    ; addi 48
	rcall _putchar
	.dbline 153
	lds R16,_display+2
	subi R16,208    ; addi 48
	rcall _putchar
	.dbline 154
	ldi R16,58
	rcall _putchar
	.dbline 155
	lds R16,_display+1
	subi R16,208    ; addi 48
	rcall _putchar
	.dbline 156
	lds R16,_display
	subi R16,208    ; addi 48
	rcall _putchar
	.dbline 157
	ldi R16,13
	rcall _putchar
	.dbline 158
	ldi R16,10
	rcall _putchar
	.dbline 159
	ldi R16,500
	ldi R17,1
	rcall _OSTimeDly
	.dbline 160
	.dbline 139
	.dbline 139
	rjmp L40
X3:
	.dbline -2
L39:
	rcall pop_gset3x
	.dbline 0 ; func end
	ret
	.dbsym r data 10 pV
	.dbend
	.area bss(ram, con, rel)
	.dbfile F:\ICC\project\ucos_m8_icc\test\test2.c
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
	.area data(ram, con, rel)
	.dbfile F:\ICC\project\ucos_m8_icc\test\test2.c
L5:
	.blkb 23
	.area idata
	.byte 'A,'T,'m,'e,'g,'a,56,32,'u,'c,47,'o,'s,45,'I,'I
	.byte 32,'T,'e,'s,'t,33,0
	.area data(ram, con, rel)
	.dbfile F:\ICC\project\ucos_m8_icc\test\test2.c
	.area func_lit
PL_Task2:	.word `_Task2
PL_Task1:	.word `_Task1
