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
                           idata   0134   0017 =     23. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0134  __idata_start
       014B  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   014C   0F88 =   3976. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       00A6  __text_start
       00A6  __start
       00C5  _exit
       00C6  _uart0_init
       00D1  _TC2_Init
       00DE  _main
       0102  _Task1
       01A4  _Task2
       0200  _OSInit
       02D5  _OSIntExit
       0339  _OSSched
       0399  _OSStart
       03D9  _OSTaskIdle
       03FC  _OSTCBInit
       048E  _OSTimeTick
       04F9  _OSTaskStkInit
       05F2  _OSTaskCreate
       066F  _OSTimeDly
       06AA  _init164
       06AF  _write164
       06C5  _OSStartHighRdy
       06F5  _OSCtxSw
       0752  _OSIntCtxSw
       0790  _OSTickISR
       07DE  mod8u
       07E0  div8u
       07E1  xdiv8u
       07F6  empy16s
       0806  pop_gset3x
       0807  popx
       0812  pop_gset4x
       0814  pop_gset5x
       0816  push_gset3x
       0819  push_gset4x
       081C  push_gset5x
       081F  _putchar
       0835  _EEPROMread
       083C  _EEPROMwrite
       084B  _puts
       086A  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0017 =     23. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  __data_start
       0077  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   0077   01DB =    475. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0077  __bss_start
       0077  _Task2Stack
       00DB  _Task1Stack
       013F  _state
       0140  _s
       0141  _m
       0142  _h
       0143  _display
       0201  _OSTime
       0205  _OSTCBPrioTbl
       0225  _OSTCBList
       0227  _OSTCBHighRdy
       0229  _OSTCBFreeList
       022B  _OSTCBCur
       022D  _OSTaskCtr
       022E  _OSRunning
       022F  _OSRdyTbl
       0231  _OSRdyGrp
       0232  _OSPrioHighRdy
       0233  _OSPrioCur
       0234  _OSLockNesting
       0235  _OSIntNesting
       0236  _OSIdleCtr
       023A  _OSEventTbl
       024A  _OSEventFreeList
       024C  _OSCtxSwCtr
       0250  __textmode
       0252  __bss_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   000A =     10. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

d:\ICC\lib\crtAVR.o	[ crtavr.s ]
test2.o	[ test2.c ]
Ucos_ii.o	[ Ucos_ii.c ]
os_cpu_a.o	[ os_cpu_a.s ]
<library>	[ div8u.s, emul16s.s, gpop3x.s, gpop4x.s, gpop5x.s, gpush3x.s, gpush4x.s, gpush5x.s, putchar.s, eepromr.s ]
[ eepromw.s, textmode.s, puts.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x26
data = 0x60
eeprom:1.512

