	 org  0000h
start:orl pcon,#80h
      mov scon,#10010000b
	  mov p2,#0ffh
loop: mov a,p2
      mov sbuf,a
wait: jbc ri,received
      jbc ti,loop
	  jmp wait
received:mov p0,sbuf
      clr ri
	  jmp wait
	  end

