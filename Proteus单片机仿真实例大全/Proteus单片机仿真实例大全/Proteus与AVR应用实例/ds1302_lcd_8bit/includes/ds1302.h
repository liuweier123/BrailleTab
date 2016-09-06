#if !defined(DS1302_H)
#define DS1302_H
/******************************************************************************/
#define datap       PORTC  //定义数据寄存器端口
#define dirp        DDRC
#define pinp	    PINC
#define rst  0			//definitions
#define clk  1
#define io   2 
  
#define prt_set_rst()  		 (datap |= (1<<rst))   //数据寄存器置位与清零
#define prt_set_clk()  		 (datap |= (1<<clk))
#define prt_set_io()    	 (datap |= (1<<io))
#define prt_clear_rst()	 	 (datap &= ~(1<<rst))
#define prt_clear_clk() 	 (datap &= ~(1<<clk))
#define prt_clear_io()  	 (datap &= ~(1<<io))

#define ddr_set_rst()  		 (dirp |= (1<<rst))   //方向寄存器置位与清零
#define ddr_set_clk()  		 (dirp |= (1<<clk))
#define ddr_set_io()   	         (dirp |= (1<<io))
#define ddr_clear_rst()	         (dirp &= ~(1<<rst))
#define ddr_clear_clk()  	 (dirp &= ~(1<<clk))
#define ddr_clear_io()  	 (dirp &= ~(1<<io))
/******************************************************************************/
#define mon 1
#define tue 2
#define wed 3
#define thu 4
#define fri 5
#define sat 6
#define sun 7

#define sec_w 0x80
#define sec_r 0x81
#define min_r 0x83
#define hour_r 0x85
#define date_r 0x87
#define month_r 0x89
#define day_r 0x8b
#define year_r 0x8d
#define min_w 0x82
#define hour_w 0x84
#define date_w 0x86
#define month_w 0x88
#define day_w 0x8a
#define year_w 0x8c

#define w_protect 0x8e

#if defined DS1302_C

void reset(void);		//define the functions
void write(unsigned char);
unsigned char read(void);
void write_byte(unsigned char,unsigned char);
unsigned char read_byte(unsigned char);
unsigned char get_hours(void);
#else
extern void reset(void);		//define the functions
extern void write(unsigned char);
extern unsigned char read(void);
extern void write_byte(unsigned char,unsigned char);
extern unsigned char read_byte(unsigned char);
extern unsigned char get_hours(void);

#endif
#endif
