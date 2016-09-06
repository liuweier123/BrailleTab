NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                        func_lit   0026   0006 =      6. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0026  __func_lit_start
       002C  __func_lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   002C   0108 =    264. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       002C  __lit_start
       002C  _OSMapTbl
       0034  _OSUnMapTbl
       0134  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0134   0F18 =   3864. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       009A  __text_start
       009A  __start
       00B9  _exit
       00BA  _uart0_init
       00C5  _TC2_Init
       00D2  _main
       00EF  _Task1
       0192  _Task2
       01EA  _OSInit
       02BF  _OSIntExit
       0323  _OSSched
       0383  _OSStart
       03C3  _OSTaskIdle
       03E6  _OSTCBInit
       046F  _OSTimeTick
       04D6  _OSTaskStkInit
       05D1  _OSTaskCreate
       064E  _OSTimeDly
       0685  _init164
       068A  _write164
       06A0  _OSStartHighRdy
       06D0  _OSCtxSw
       072D  _OSIntCtxSw
       076B  _OSTickISR
       07B9  mod8u
       07BB  div8u
       07BC  xdiv8u
       07CD  empy16s
       07DD  pop_gset3x
       07DE  popx
       07E9  pop_gset4x
       07EB  pop_gset5x
       07ED  push_gset3x
       07F0  push_gset4x
       07F3  push_gset5x
       07F6  _putchar
       080C  _EEPROMread
       0815  _EEPROMwrite
       0826  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   0060   01DB =    475. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  __bss_start
       0060  _Task2Stack
       00C4  _Task1Stack
       0128  _state
       0129  _s
       012A  _m
       012B  _h
       012C  _display
       01EA  _OSTime
       01EE  _OSTCBPrioTbl
       020E  _OSTCBList
       0210  _OSTCBHighRdy
       0212  _OSTCBFreeList
       0214  _OSTCBCur
       0216  _OSTaskCtr
       0217  _OSRunning
       0218  _OSRdyTbl
       021A  _OSRdyGrp
       021B  _OSPrioHighRdy
       021C  _OSPrioCur
       021D  _OSLockNesting
       021E  _OSIntNesting
       021F  _OSIdleCtr
       0223  _OSEventTbl
       0233  _OSEventFreeList
       0235  _OSCtxSwCtr
       0239  __textmode
       023B  __bss_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   000A =     10. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\AVR\ICC\lib\crtAVR.o	[ crtavr.s ]
test2.o	[ test2.c ]
Ucos_ii.o	[ Ucos_ii.c ]
os_cpu_a.o	[ os_cpu_a.s ]
<library>	[ div8u.s, emul16s.s, gpop3x.s, gpop4x.s, gpop5x.s, gpush3x.s, gpush4x.s, gpush5x.s, putchar.s, eepromr.s ]
[ eepromw.s, textmode.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x26
data = 0x60
eeprom:1.512

