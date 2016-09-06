#ifndef _led_dsp_h
#define _led_dsp_h
#ifdef _led_dsp_c
#define data_port PORTB
#define scan_port PORTD
#define uchar unsigned char
#define uint unsigned int
void delay(uchar delay_t);
void scan_led(uchar *disp_p);
void change_data (int dsp_data);
uchar const led_tabel[]={  
	0x3f,   //0
  0x06,   //1
  0x5b,   //2
  0x4f,   //3
  0x66,   //4
  0x6d,   //5 
  0x7d,   //6 
  0x07,   //7 
  0x7f,   //8
  0x6f    //9
};
uchar disp_buffer[4]={0x3f,0x3f,0x3f,0x3f};

#else
extern void delay(uchar delay_t);
extern void scan_led(uchar *disp_p);
extern void change_data (int dsp_data);
extern uchar const led_tabel[];
extern uchar disp_buffer[4];
#endif
#endif