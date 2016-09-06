CC = iccavr
CFLAGS =  -IC:\AVR\ICC\include\ -I.\ -I..\test\ -I..\source\ -e  -l -g -Mavr_enhanced_small -Wa-W -Wf-r20_23 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -LC:\AVR\ICC\lib\ -g -Wl-W -bfunc_lit:0x26.0x2000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:16 -beeprom:1.512 -fihx_coff -S1
FILES = test2.o Ucos_ii.o os_cpu_a.o 

ucos:	$(FILES)
	$(CC) -o ucos $(LFLAGS) @ucos.lk  -lcavrgr
test2.o: D:\job\avrtest\光盘\开发板\iccavr\test/includes.h C:/AVR/ICC/include/iom8v.h D:\job\avrtest\光盘\开发板\iccavr\test/OS_CPU.H C:/AVR/ICC/include/macros.h D:\job\avrtest\光盘\开发板\iccavr\test/OS_CFG.H ../source/UCOS_II.H\
 C:/AVR/ICC/include/eeprom.h C:/AVR/ICC/include/iom8v.h C:/AVR/ICC/include/macros.h C:/AVR/ICC/include/stdio.h C:/AVR/ICC/include/stdarg.h C:/AVR/ICC/include/_const.h
test2.o:	D:\job\avrtest\光盘\开发板\iccavr\test\test2.c
	$(CC) -c $(CFLAGS) D:\job\avrtest\光盘\开发板\iccavr\test\test2.c
Ucos_ii.o: ../test/includes.h C:/AVR/ICC/include/iom8v.h ../test/OS_CPU.H C:/AVR/ICC/include/macros.h ../test/OS_CFG.H D:\job\avrtest\光盘\开发板\iccavr\source/UCOS_II.H C:/AVR/ICC/include/eeprom.h D:\job\avrtest\光盘\开发板\iccavr\source/os_core.c\
 D:\job\avrtest\光盘\开发板\iccavr\source/os_task.c D:\job\avrtest\光盘\开发板\iccavr\source/os_time.c D:\job\avrtest\光盘\开发板\iccavr\source/74164.c
Ucos_ii.o:	D:\job\avrtest\光盘\开发板\iccavr\source\Ucos_ii.c
	$(CC) -c $(CFLAGS) D:\job\avrtest\光盘\开发板\iccavr\source\Ucos_ii.c
os_cpu_a.o:	D:\job\avrtest\光盘\开发板\iccavr\test\os_cpu_a.s
	$(CC) -c $(ASFLAGS) D:\job\avrtest\光盘\开发板\iccavr\test\os_cpu_a.s
