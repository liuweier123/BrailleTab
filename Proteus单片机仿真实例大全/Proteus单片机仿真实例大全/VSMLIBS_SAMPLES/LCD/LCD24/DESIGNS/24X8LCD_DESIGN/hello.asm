; Scrivo "Hello World!" sul display
		PROCESSOR	16F84
		RADIX		DEC
		INCLUDE		"p16f84.inc"

	        ERRORLEVEL      -302

PIN11		EQU	4	; PIN11 LCD --> RB4
PIN12		EQU	5	; PIN12 LCD --> RB5
PIN13		EQU	6	; PIN13 LCD --> RB6
PIN14		EQU	7	; PIN14 LCD --> RB7

RS		EQU	3	; RS LCD --> RB3
EN		EQU	2	; RS LCD --> RB2

		ORG	0CH

lsb		RES	1
msb		RES	1
tmp		RES	1
tmp1		RES	1

		ORG	00H

		nop

		bsf	STATUS,RP0	;Banco 1

		movlw	0x00
		movwf	TRISB		;PORTB TUTTA IN OUTPUT

		bcf	STATUS,RP0	;Banco 0

		call	init

		movlw	06H
		call	cp		;Riga 0 posizione 6

		movlw	'P'
		call 	sd
		movlw	'R'
		call	sd
		movlw	'O'
		call 	sd
		movlw	'T'
		call 	sd
		movlw	'E'
		call 	sd
		movlw	'U'
		call 	sd
		movlw	'S'
		call 	sd
		
		movlw	15H		;Riga 1 posizione 5
		call	cp

		movlw	'2'
		call 	sd
		movlw	'4'
		call	sd
		movlw	'X'
		call 	sd
		movlw	'2'
		call 	sd
		movlw	'L'
		call 	sd
		movlw	'C'
		call 	sd
		movlw   'D'
		call 	sd
		
		movlw   ' '
		call 	sd
		movlw   'V'
		call 	sd
		movlw   'S'
		call 	sd
		movlw   'M'
		call 	sd
		movlw	' '
		call 	sd
		movlw	'T'
		call 	sd
		movlw   'E'
		call 	sd
		movlw   'S'
		call 	sd
		movlw   'T'
		call 	sd
loop		goto	loop

		INCLUDE	"liblcd4.asm"

	end
