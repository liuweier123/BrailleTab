#ifndef KEY_H
#define KEY_H
#ifdef  KEY_C
#define NO_KEY 255

//#ifdef  KEY_4X4   //¼üÅÌÎª4X4
/*#define K1_1 1
#define K1_2 2
#define K1_3 3
#define K1_4 4

#define K2_1 5
#define K2_2 6
#define K2_3 7
#define K2_4 8

#define K3_1 9
#define K3_2 0
#define K3_3 10
#define K3_4 11

#define K4_1 12
#define K4_2 13
#define K4_3 14
#define K4_4 15
*/
//#else    //4X3¼üÅÌ

#define K1_1 1
#define K1_2 2
#define K1_3 3

#define K2_1 4
#define K2_2 5
#define K2_3 6

#define K3_1 7
#define K3_2 8
#define K3_3 9

#define K4_1 10
#define K4_2 11
#define K4_3 12
//#endif
//#define KEY_MASK    0x0f   //4x4¼üÅÌ
#define KEY_MASK   0x07
#define KEY_PORT   PORTA
#define KEY_PIN    PINA


unsigned char key_scan(void);
char read_keybord(void);
#else
extern unsigned char key_scan(void);
extern char read_keybord(void);
#endif
#endif
