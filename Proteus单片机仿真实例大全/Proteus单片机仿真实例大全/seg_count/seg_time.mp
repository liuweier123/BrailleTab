NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0022   0010 =     16. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0022  __idata_start
       0032  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0032   022E =    558. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0019  __start
       0019  __text_start
       0038  _exit
       0039  _DelayMs
       0049  _Display
       0064  _Process
       0097  _Init_IO
       00A0  _Get_Key
       00B3  _main
       00F3  mod16u
       00F5  div16u
       00F6  xdiv16u
       010F  pop_gset2
       0111  pop_gset3
       0113  push_gset1
       0116  pop_gset1
       0117  pop
       012A  push_gset2
       012D  push_gset3
       0130  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0010 =     16. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  _Table
       0060  __data_start
       006A  _Data
       006E  _CNT
       0070  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   0070   0002 =      2. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0070  __bss_start
       0070  _Key_Down
       0071  _Key_Up
       0072  __bss_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0002 =      2. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

D:\icc\lib\crtAVR.o	[ crtavr.s ]
Counter.o	[ Counter.C ]
<library>	[ div16u.s, gpop2.s, gpop3.s, gpush.s, gpush2.s, gpush3.s ]

User Global Definitions

ram_end = 0x25f
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x22
data = 0x60
eeprom:1.512

