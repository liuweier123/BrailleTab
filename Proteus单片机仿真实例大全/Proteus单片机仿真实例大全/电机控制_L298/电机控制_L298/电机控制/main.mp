NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0054   01BA =    442. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       002A  __text_start
       002A  __start
       004C  _exit
       004D  _for_ward
       0059  _back_ward
       0065  _motor_stop
       006B  _speed_add
       0073  _speed_subtract
       007C  _port_init
       0087  _timer2_init
       0090  _init_devices
       0097  _Delay100us
       00A4  _Delay1ms
       00B2  _Delay1s
       00C6  _main
       00ED  _timer2_comp_isr
       00EE  _timer2_ovf_isr
       00F7  empy16s
       0107  __text_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0018 =     24. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

D:\iccv7avr\lib\crtatmega.o	[ crtatmega.s ]
motor.o	[ motor.c ]
device_init.o	[ device_init.c ]
delay.o	[ delay.c ]
main.o	[ main.c ]
<library>	[ emul16s.s ]

User Global Definitions

ram_end = 0x85f
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:0.1024

