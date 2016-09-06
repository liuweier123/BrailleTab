CC = iccavr
CFLAGS =  -IE:\program\icc\include\ -e -DATMEGA -DATMega16  -l -g -Mavr_enhanced 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -LE:\program\icc\lib\ -g -ucrtatmega.o -bfunc_lit:0x54.0x4000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:16 -beeprom:1.512 -fihx_coff -S2
FILES = delay.o main.o 

main:	$(FILES)
	$(CC) -o main $(LFLAGS) @main.lk   -lcatmega
delay.o:	D:\AVR\ICC\usart_t\delay.c
	$(CC) -c $(CFLAGS) D:\AVR\ICC\usart_t\delay.c
main.o: E:/program/icc/include/iom16v.h E:/program/icc/include/macros.h E:/program/icc/include/stdio.h E:/program/icc/include/stdarg.h E:/program/icc/include/_const.h
main.o:	D:\AVR\ICC\usart_t\main.c
	$(CC) -c $(CFLAGS) D:\AVR\ICC\usart_t\main.c
