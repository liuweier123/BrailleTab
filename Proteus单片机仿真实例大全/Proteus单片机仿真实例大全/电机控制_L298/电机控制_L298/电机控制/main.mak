CC = iccavr
CFLAGS =  -IC:\PROGRA~1\icc\include\ -e -D__ICC_VERSION="7.14C" -DATMEGA -DATMega32  -l -g -Mavr_enhanced 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -LC:\PROGRA~1\icc\lib\ -g -e:0x8000 -ucrtatmega.o -bfunc_lit:0x54.0x8000 -dram_end:0x85f -bdata:0x60.0x85f -dhwstk_size:16 -beeprom:0.1024 -fihx_coff -S2
FILES = motor.o device_init.o delay.o main.o 

MAIN:	$(FILES)
	$(CC) -o MAIN $(LFLAGS) @MAIN.lk   -lcatmega
motor.o: E:\avr\�������\�������\config.h D:\iccv7avr\include\iom32v.h D:\iccv7avr\include\macros.h E:\avr\�������\�������\delay.h E:\avr\�������\�������\device_init.h E:\avr\�������\�������\motor.h
motor.o:	E:\avr\�������\�������\motor.c
	$(CC) -c $(CFLAGS) E:\avr\�������\�������\motor.c
device_init.o: E:\avr\�������\�������\config.h D:\iccv7avr\include\iom32v.h D:\iccv7avr\include\macros.h E:\avr\�������\�������\delay.h E:\avr\�������\�������\device_init.h E:\avr\�������\�������\motor.h
device_init.o:	E:\avr\�������\�������\device_init.c
	$(CC) -c $(CFLAGS) E:\avr\�������\�������\device_init.c
delay.o: E:\avr\�������\�������\config.h D:\iccv7avr\include\iom32v.h D:\iccv7avr\include\macros.h E:\avr\�������\�������\delay.h E:\avr\�������\�������\device_init.h E:\avr\�������\�������\motor.h
delay.o:	E:\avr\�������\�������\delay.c
	$(CC) -c $(CFLAGS) E:\avr\�������\�������\delay.c
main.o: E:\avr\�������\�������\config.h D:\iccv7avr\include\iom32v.h D:\iccv7avr\include\macros.h E:\avr\�������\�������\delay.h E:\avr\�������\�������\device_init.h E:\avr\�������\�������\motor.h
main.o:	E:\avr\�������\�������\main.c
	$(CC) -c $(CFLAGS) E:\avr\�������\�������\main.c
