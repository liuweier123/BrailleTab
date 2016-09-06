	  org    0000h
      
main:  mov r3,#01h 
       mov r4,#00h
	   mov r5,#10h
      lcall  display

	   mov r3,#03h
       mov r4,#00h
	   mov r5,#20h
      lcall  display

	    mov r3,#05h
       mov r4,#00h
	   mov r5,#20h
      lcall  display

	  mov r3,#0fh
       mov r4,#00h
	   mov r5,#30h
      lcall  display

	  	mov r3,#00h
       mov r4,#00h
	   mov r5,#02h
      lcall  display

	  mov r3,#0ffh
       mov r4,#0ffh
	   mov r5,#30h
	   lcall  display
	  
	   mov r3,#00h
       mov r4,#00h
	   mov r5,#02h
       lcall  display

	   mov r3,#0ffh
       mov r4,#0ffh
	   mov r5,#40h
	   lcall  display

	   mov r3,#00h
       mov r4,#00h
	   mov r5,#04h
       lcall  display
      
	  ajmp  main

display: clr c
 go:mov a,r3
        rlc a
		mov r3,a
		mov a,r4
		rlc a
		mov r4,a
        mov p1,r3
        mov p2,r4
		lcall delay
        djnz  r5,go
		ret
delay:mov r1,#0ffh
temp1:mov r2,#0ffh
      djnz r2,$
	  djnz r1,temp1
	  ret
      end