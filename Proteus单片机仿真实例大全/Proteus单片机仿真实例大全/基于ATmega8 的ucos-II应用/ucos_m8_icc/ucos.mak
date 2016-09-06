CC = iccavr
CFLAGS =  -IF:\ICC\project\ucos_m8_icc\source -IF:\ICC\project\ucos_m8_icc\test -ID:\icc\include -e  -l -g -Mavr_enhanced_small -Wa-W -Wf-r20_23 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -Ld:\ICC\lib\ -g -Wl-W -bfunc_lit:0x26.0x2000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:16 -beeprom:1.512 -fihx_coff -S2
FILES = test2.o Ucos_ii.o os_cpu_a.o 

ucos:	$(FILES)
	$(CC) -o ucos $(LFLAGS) @ucos.lk   -lcavrgr
test2.o: F:\ICC\project\ucos_m8_icc\test/includes.h D:/icc/include/iom8v.h F:\ICC\project\ucos_m8_icc\test/OS_CPU.H D:/icc/include/macros.h F:\ICC\project\ucos_m8_icc\test/OS_CFG.H F:/ICC/project/ucos_m8_icc/source/UCOS_II.H D:/icc/include/eeprom.h\
 D:/icc/include/iom8v.h D:/icc/include/macros.h D:/icc/include/stdio.h D:/icc/include/stdarg.h D:/icc/include/_const.h
test2.o:	F:\ICC\project\ucos_m8_icc\test\test2.c
	$(CC) -c $(CFLAGS) F:\ICC\project\ucos_m8_icc\test\test2.c
Ucos_ii.o: F:/ICC/project/ucos_m8_icc/test/includes.h D:/icc/include/iom8v.h F:/ICC/project/ucos_m8_icc/test/OS_CPU.H D:/icc/include/macros.h F:/ICC/project/ucos_m8_icc/test/OS_CFG.H F:\ICC\project\ucos_m8_icc\source/UCOS_II.H D:/icc/include/eeprom.h\
 F:\ICC\project\ucos_m8_icc\source/os_core.c F:\ICC\project\ucos_m8_icc\source/os_task.c F:\ICC\project\ucos_m8_icc\source/os_time.c F:\ICC\project\ucos_m8_icc\source/74164.c
Ucos_ii.o:	F:\ICC\project\ucos_m8_icc\source\Ucos_ii.c
	$(CC) -c $(CFLAGS) F:\ICC\project\ucos_m8_icc\source\Ucos_ii.c
os_cpu_a.o:	F:\ICC\project\ucos_m8_icc\test\os_cpu_a.s
	$(CC) -c $(ASFLAGS) F:\ICC\project\ucos_m8_icc\test\os_cpu_a.s
