CC = iccavr
CFLAGS =  -ID:\icc\include\ -e  -l -g -Wf-intenum -Wa-W 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -LD:\icc\lib\ -g -Wl-W -bfunc_lit:0x22.0x2000 -dram_end:0x25f -bdata:0x60.0x25f -dhwstk_size:16 -beeprom:1.512 -fihx_coff -S2
FILES = Counter.o 

seg_time:	$(FILES)
	$(CC) -o seg_time $(LFLAGS) @seg_time.lk   -lstudio
Counter.o: D:/icc/include/iom16v.h
Counter.o:	F:\myavr\temp\seg_count\Counter.C
	$(CC) -c $(CFLAGS) F:\myavr\temp\seg_count\Counter.C
