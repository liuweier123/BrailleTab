CC = iccavr
CFLAGS =  -ID:\icc\include\ -e -DATMEGA  -l -g -Wf-intenum -Mavr_enhanced 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -LD:\icc\lib\ -g -ucrtatmega.o -bfunc_lit:0x54.0x4000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:16 -beeprom:1.512 -fihx_coff -S2
FILES = M16_T1_Compare.o 

M16_T1_Compare:	$(FILES)
	$(CC) -o M16_T1_Compare $(LFLAGS) @M16_T1_Compare.lk   -lstudio -lcatmega
M16_T1_Compare.o: D:/icc/include/iom16v.h
M16_T1_Compare.o:	F:\myavr\temp\M16_T1_Compare\M16_T1_Compare.c
	$(CC) -c $(CFLAGS) F:\myavr\temp\M16_T1_Compare\M16_T1_Compare.c
