NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0054   0014 =     20. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __idata_start
       0068  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0068   018E =    398. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0034  __text_start
       0034  __start
       0054  _exit
       0055  _delay_1us
       0057  _delay_nus
       0066  _delay_1ms
       0070  _delay_nms
       007F  _uart0_init
       008A  _main
       00A5  pop_gset2
       00A8  push_gset5
       00AA  push_gset4
       00AC  push_gset3
       00AE  push_gset2
       00B0  push_gset1
       00B3  pop_gset1
       00B4  pop
       00C7  _putchar
       00DE  _puts
       00FB  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0014 =     20. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  __data_start
       0074  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   0074   0002 =      2. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0074  __textmode
       0074  __bss_start
       0076  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0004 =      4. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

E:\program\icc\lib\crtatmega.o	[ crtatmega.s ]
delay.o	[ delay.c ]
main.o	[ main.c ]
<library>	[ gpop2.s, gpush.s, putchar.s, textmode.s, puts.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:1.512

