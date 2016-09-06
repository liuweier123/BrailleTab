; COLLEGAMENTI:
;
; LCD DB7 (14)   	-->     PIC RB7 (13)
; LCD DB6 (13)   	-->     PIC RB6 (12)
; LCD DB5 (12)   	-->     PIC RB5 (11)
; LCD DB4 (11)  	-->     PIC RB4 (10)
; LCD EN  (6)     	-->     PIC RB2 (8)
; LCD RS  (4)    	-->     PIC RB3 (9)
;
; INTESTAZIONE:
;
; PROCESSOR	16F84
; RADIX		DEC
; INCLUDE	"p16f84.inc"
;
; PIN11		EQU     4       
; PIN12		EQU     5       
; PIN13		EQU     6       
; PIN14		EQU     7       
; EN		EQU     2       
; RS		EQU     3       
;
; 		ORG	0CH
;
; lsb		RES	1
; msb		RES	1
; tmp		RES	1
; tmp1		RES	1
;
;		ORG	00H
;
; bsf		STATUS,RP0	;BANCO 1
;
; movlw		0x00
; movwf		TRISB
;
; bcf		STATUS,RP0	;BANCO 0
;
; ...
				

; ********************************************************
; init
; Da usare all'inizio del programma per inizializzare l'LCD
; Registri usati:
; \
; Subroutine richiamate:
; rit
; enable
; sc
; ********************************************************

init	movlw	30
	call	rit		; Ritardo 30 ms

	bcf	PORTB,RS	; RS = 0 --> Dati

	bsf     PORTB,PIN11
	bsf     PORTB,PIN12
	bcf     PORTB,PIN13
	bcf     PORTB,PIN14	; PORTB --> 0011XXXX
		
	bsf	PORTB,EN
	movlw	5
	call	rit		; Ritardo 5 ms
	bcf	PORTB,EN
	movlw	1
	call	rit		; Ritardo 1 ms

	call	enable
		
	call	enable

	bcf     PORTB,PIN11
        bsf     PORTB,PIN12
        bcf     PORTB,PIN13
        bcf     PORTB,PIN14	; PORTB --> 0010XXXX

	call	enable

	movlw	0x28		; 4-bit
	call	sc

	movlw	0x06		
	call	sc

	movlw	0x0C
	call	sc
		
	call	cl

	return

; ********************************************************
; cp
; Cursor Position - Mette il cursore in una certa posizione
; Registri usati:
; W	-->	D7-D4 righe,	D3,D0 colonne
; tmp
; tmp1
; Subroutine richiamate:
; sc
; ********************************************************
cp	movwf	tmp

	movlw	0x80
	movwf	tmp1		; Metti 10000000 in tmp1

	movf    tmp,W		; Metti tmp in W
        andlw   0x0F		; W --> 0000DDDD
        iorwf   tmp1,F		; tmp1 --> 1000DDDD

        btfsc   tmp,4		; Se il bit 4 di tmp = 0 salta
        bsf     tmp1,6		; altrimenti tmp1 diventa 1100DDDD

        movf    tmp1,W		; Metti tmp1 in W
        call    sc		; Manda il comando 1X00DDDD

        return		

; ********************************************************
; cl
; Clear - Pulisce il display e mette il cursore all'inizio
; Registri usati:
; \
; Subroutine richiamate:
; sc
; rit
; ********************************************************

cl	movlw	0x01
	call	sc	; CLEAR

	movlw	2
	call	rit	; Ritardo 2 ms

	movlw	80H	
	call	sc	; Posizione Iniziale

	return

; ********************************************************
; sd
; Send data - Invia un dato al display
; Registri usati:
; W	-->	dato da inviare
; Subroutine richiamate:
; sb
; ********************************************************

sd	bsf	PORTB,RS
	call	sb
	return


; ********************************************************
; sc
; Send Command - Invia un comando al display
; Registri usati:
; W	-->	Comando da inviare
; Subroutine richiamate:
; sb
; ********************************************************

sc	bcf	PORTB,RS
	call	sb
	return

; ********************************************************
; sb
; Send byte - Invia un byte sull'msb di PORTB
; Registri usati:
; tmp
; Subroutine richiamate:
; enable
; ********************************************************

sb	movwf	tmp
	movlw	B'00001111'
	andwf	PORTB,F		;Metto a 0 i 4 bit MSB di PORTB
	movf	tmp,W
	andlw	B'11110000'	;Metto a 0 i 4 bit LSB del byte da inviare in W
	iorwf	PORTB,F		;OR fra PORTB (0000XXXX) e W (DDDD0000)
	call	enable		;Impulso di Enable
	movlw	B'00001111'
	andwf	PORTB,F		;Metto a 0 i 4 bit MSB di PORTB
	swapf	tmp,W		;Metto tmp1 in W con LSB invertito con MSB
	andlw	B'11110000'	;Metto a 0 i 4 bit LSB del byte da inviare in W
	iorwf	PORTB,F		;OR fra PORTB (0000XXXX) e W (DDDD0000) 
	call	enable		;Impulso di Enable

	return

; ********************************************************
; enable
; Manda un impulso di ENABLE della durata di 1ms
; Registri usati:
; \
; Subroutine richiamate:
; rit
; ********************************************************

enable	bcf	STATUS,RP0	;banco 0
	bsf	PORTB,EN	;metto a 1 enable
	movlw	1		;metto 1 in w
	call	rit		;ritardo
	bcf	PORTB,EN	;rimetto a 0 enable
	movlw	1
	call	rit
	
	return

; ********************************************************
; rit
; Ciclo di ritardo programmabile
; Registri usati:
; W	-->	Numero di ms (per CLK = 4MHz)
; msb	-->	(uso interno)
; lsb	-->	(uso interno)
; Subroutine richiamate:
; \
; ********************************************************

rit	movwf   msb
        clrf    lsb
rit_loop
	nop
        decfsz  lsb,F
        goto    rit_loop
        nop
        decfsz  msb,F
        goto    rit_loop

        return
