/*
字库文件
字的纵向8点构成一字节,上方的点在字节的高位,
字符点阵四角按左上角→左下角→右上角→右下角取字
*/
/* 		ASCII 8x16 点阵    */
const char ASC_MSK[96*16] = {
/*     */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*!    */
0x00,0x00,0x00,0x00,0x1C,0x00,0x3F,0xB0,
0x3F,0xB0,0x1C,0x00,0x00,0x00,0x00,0x00,

/*"    */
0x00,0x00,0x70,0x00,0x78,0x00,0x00,0x00,
0x00,0x00,0x78,0x00,0x70,0x00,0x00,0x00,

/*#    */
0x04,0x40,0x1F,0xF0,0x1F,0xF0,0x04,0x40,
0x1F,0xF0,0x1F,0xF0,0x04,0x40,0x00,0x00,

/*$    */
0x1C,0xC0,0x3E,0x60,0x22,0x20,0xE2,0x38,
0xE2,0x38,0x33,0xE0,0x19,0xC0,0x00,0x00,

/*%    */
0x0C,0x30,0x0C,0x60,0x00,0xC0,0x01,0x80,
0x03,0x00,0x06,0x30,0x0C,0x30,0x00,0x00,

/*&    */
0x01,0xE0,0x1B,0xF0,0x3E,0x10,0x27,0x10,
0x3D,0xE0,0x1B,0xF0,0x02,0x10,0x00,0x00,

/*'    */
0x00,0x00,0x08,0x00,0x78,0x00,0x70,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*(    */
0x00,0x00,0x00,0x00,0x0F,0xC0,0x1F,0xE0,
0x30,0x30,0x20,0x10,0x00,0x00,0x00,0x00,

/*)    */
0x00,0x00,0x00,0x00,0x20,0x10,0x30,0x30,
0x1F,0xE0,0x0F,0xC0,0x00,0x00,0x00,0x00,

/**    */
0x01,0x00,0x05,0x40,0x07,0xC0,0x03,0x80,
0x03,0x80,0x07,0xC0,0x05,0x40,0x01,0x00,

/*+    */
0x00,0x00,0x01,0x00,0x01,0x00,0x07,0xC0,
0x07,0xC0,0x01,0x00,0x01,0x00,0x00,0x00,

/*,    */
0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x78,
0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,

/*-    */
0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,
0x01,0x00,0x01,0x00,0x01,0x00,0x00,0x00,

/*.    */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,
0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,

/*/    */
0x00,0x30,0x00,0x60,0x00,0xC0,0x01,0x80,
0x03,0x00,0x06,0x00,0x0C,0x00,0x00,0x00,

/*0    */
0x1F,0xE0,0x3F,0xF0,0x20,0x90,0x23,0x10,
0x24,0x10,0x3F,0xF0,0x1F,0xE0,0x00,0x00,

/*1    */
0x00,0x00,0x08,0x10,0x18,0x10,0x3F,0xF0,
0x3F,0xF0,0x00,0x10,0x00,0x10,0x00,0x00,

/*2    */
0x10,0x70,0x30,0xF0,0x21,0x90,0x23,0x10,
0x26,0x10,0x3C,0x30,0x18,0x30,0x00,0x00,

/*3    */
0x10,0x20,0x30,0x30,0x22,0x10,0x22,0x10,
0x22,0x10,0x3F,0xF0,0x1D,0xE0,0x00,0x00,

/*4    */
0x03,0x00,0x07,0x00,0x0D,0x00,0x19,0x10,
0x3F,0xF0,0x3F,0xF0,0x01,0x10,0x00,0x00,

/*5    */
0x3E,0x20,0x3E,0x30,0x22,0x10,0x22,0x10,
0x23,0x10,0x23,0xF0,0x21,0xE0,0x00,0x00,

/*6    */
0x0F,0xE0,0x1F,0xF0,0x32,0x10,0x22,0x10,
0x22,0x10,0x03,0xF0,0x01,0xE0,0x00,0x00,

/*7    */
0x30,0x00,0x30,0x00,0x20,0xF0,0x21,0xF0,
0x23,0x00,0x3E,0x00,0x3C,0x00,0x00,0x00,

/*8    */
0x1D,0xE0,0x3F,0xF0,0x22,0x10,0x22,0x10,
0x22,0x10,0x3F,0xF0,0x1D,0xE0,0x00,0x00,

/*9    */
0x1C,0x00,0x3E,0x10,0x22,0x10,0x22,0x10,
0x22,0x30,0x3F,0xE0,0x1F,0xC0,0x00,0x00,

/*:    */
0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x60,
0x0C,0x60,0x00,0x00,0x00,0x00,0x00,0x00,

/*;    */
0x00,0x00,0x00,0x00,0x00,0x10,0x0C,0x70,
0x0C,0x60,0x00,0x00,0x00,0x00,0x00,0x00,

/*<    */
0x00,0x00,0x01,0x00,0x03,0x80,0x06,0xC0,
0x0C,0x60,0x18,0x30,0x10,0x10,0x00,0x00,

/*=    */
0x02,0x40,0x02,0x40,0x02,0x40,0x02,0x40,
0x02,0x40,0x02,0x40,0x02,0x40,0x00,0x00,

/*>    */
0x00,0x00,0x10,0x10,0x18,0x30,0x0C,0x60,
0x06,0xC0,0x03,0x80,0x01,0x00,0x00,0x00,

/*?    */
0x18,0x00,0x38,0x00,0x20,0x00,0x23,0xB0,
0x27,0xB0,0x3C,0x00,0x18,0x00,0x00,0x00,

/*@    */
0x0F,0xE0,0x1F,0xF0,0x10,0x10,0x13,0xD0,
0x13,0xD0,0x1F,0xD0,0x0F,0x80,0x00,0x00,

/*A    */
0x07,0xF0,0x0F,0xF0,0x19,0x00,0x31,0x00,
0x19,0x00,0x0F,0xF0,0x07,0xF0,0x00,0x00,

/*B    */
0x20,0x10,0x3F,0xF0,0x3F,0xF0,0x22,0x10,
0x22,0x10,0x3F,0xF0,0x1D,0xE0,0x00,0x00,

/*C    */
0x0F,0xC0,0x1F,0xE0,0x30,0x30,0x20,0x10,
0x20,0x10,0x30,0x30,0x18,0x60,0x00,0x00,

/*D    */
0x20,0x10,0x3F,0xF0,0x3F,0xF0,0x20,0x10,
0x30,0x30,0x1F,0xE0,0x0F,0xC0,0x00,0x00,

/*E    */
0x20,0x10,0x3F,0xF0,0x3F,0xF0,0x22,0x10,
0x27,0x10,0x30,0x30,0x38,0x70,0x00,0x00,

/*F    */
0x20,0x10,0x3F,0xF0,0x3F,0xF0,0x22,0x10,
0x27,0x00,0x30,0x00,0x38,0x00,0x00,0x00,

/*G    */
0x0F,0xC0,0x1F,0xE0,0x30,0x30,0x21,0x10,
0x21,0x10,0x31,0xE0,0x19,0xF0,0x00,0x00,

/*H    */
0x3F,0xF0,0x3F,0xF0,0x02,0x00,0x02,0x00,
0x02,0x00,0x3F,0xF0,0x3F,0xF0,0x00,0x00,

/*I    */
0x00,0x00,0x00,0x00,0x20,0x10,0x3F,0xF0,
0x3F,0xF0,0x20,0x10,0x00,0x00,0x00,0x00,

/*J    */
0x00,0xE0,0x00,0xF0,0x00,0x10,0x20,0x10,
0x3F,0xF0,0x3F,0xE0,0x20,0x00,0x00,0x00,

/*K    */
0x20,0x10,0x3F,0xF0,0x3F,0xF0,0x03,0x00,
0x0F,0x80,0x3C,0xF0,0x30,0x70,0x00,0x00,

/*L    */
0x20,0x10,0x3F,0xF0,0x3F,0xF0,0x20,0x10,
0x00,0x10,0x00,0x30,0x00,0x70,0x00,0x00,

/*M    */
0x3F,0xF0,0x3F,0xF0,0x1C,0x00,0x0E,0x00,
0x1C,0x00,0x3F,0xF0,0x3F,0xF0,0x00,0x00,

/*N    */
0x3F,0xF0,0x3F,0xF0,0x1C,0x00,0x0E,0x00,
0x07,0x00,0x3F,0xF0,0x3F,0xF0,0x00,0x00,

/*O    */
0x0F,0xC0,0x1F,0xE0,0x30,0x30,0x20,0x10,
0x30,0x30,0x1F,0xE0,0x0F,0xC0,0x00,0x00,

/*P    */
0x20,0x10,0x3F,0xF0,0x3F,0xF0,0x22,0x10,
0x22,0x00,0x3E,0x00,0x1C,0x00,0x00,0x00,

/*Q    */
0x1F,0xE0,0x3F,0xF0,0x20,0x10,0x20,0x70,
0x20,0x3C,0x3F,0xFC,0x1F,0xE4,0x00,0x00,

/*R    */
0x20,0x10,0x3F,0xF0,0x3F,0xF0,0x22,0x00,
0x23,0x00,0x3F,0xF0,0x1C,0xF0,0x00,0x00,

/*S    */
0x18,0x60,0x3C,0x70,0x26,0x10,0x22,0x10,
0x23,0x10,0x39,0xF0,0x18,0xE0,0x00,0x00,

/*T    */
0x00,0x00,0x38,0x00,0x30,0x10,0x3F,0xF0,
0x3F,0xF0,0x30,0x10,0x38,0x00,0x00,0x00,

/*U    */
0x3F,0xE0,0x3F,0xF0,0x00,0x10,0x00,0x10,
0x00,0x10,0x3F,0xF0,0x3F,0xE0,0x00,0x00,

/*V    */
0x3F,0x80,0x3F,0xC0,0x00,0x60,0x00,0x30,
0x00,0x60,0x3F,0xC0,0x3F,0x80,0x00,0x00,

/*W    */
0x3F,0xC0,0x3F,0xF0,0x00,0x70,0x01,0xC0,
0x00,0x70,0x3F,0xF0,0x3F,0xC0,0x00,0x00,

/*X    */
0x30,0x30,0x3C,0xF0,0x0F,0xC0,0x03,0x00,
0x0F,0xC0,0x3C,0xF0,0x30,0x30,0x00,0x00,

/*Y    */
0x00,0x00,0x3C,0x00,0x3E,0x10,0x03,0xF0,
0x03,0xF0,0x3E,0x10,0x3C,0x00,0x00,0x00,

/*Z    */
0x38,0x70,0x30,0xF0,0x21,0x90,0x23,0x10,
0x26,0x10,0x3C,0x30,0x38,0x70,0x00,0x00,

/*[    */
0x00,0x00,0x00,0x00,0x3F,0xF0,0x3F,0xF0,
0x20,0x10,0x20,0x10,0x00,0x00,0x00,0x00,

/*\    */
0x1C,0x00,0x0E,0x00,0x07,0x00,0x03,0x80,
0x01,0xC0,0x00,0xE0,0x00,0x70,0x00,0x00,

/*]    */
0x00,0x00,0x00,0x00,0x20,0x10,0x20,0x10,
0x3F,0xF0,0x3F,0xF0,0x00,0x00,0x00,0x00,

/*^    */
0x10,0x00,0x30,0x00,0x60,0x00,0xC0,0x00,
0x60,0x00,0x30,0x00,0x10,0x00,0x00,0x00,

/*_    */
0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x04,
0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x04,

/*`    */
0x00,0x00,0x00,0x00,0xC0,0x00,0xE0,0x00,
0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*a    */
0x00,0xE0,0x05,0xF0,0x05,0x10,0x05,0x10,
0x07,0xE0,0x03,0xF0,0x00,0x10,0x00,0x00,

/*b    */
0x20,0x10,0x3F,0xF0,0x3F,0xE0,0x04,0x10,
0x06,0x10,0x03,0xF0,0x01,0xE0,0x00,0x00,

/*c    */
0x03,0xE0,0x07,0xF0,0x04,0x10,0x04,0x10,
0x04,0x10,0x06,0x30,0x02,0x20,0x00,0x00,

/*d    */
0x01,0xE0,0x03,0xF0,0x06,0x10,0x24,0x10,
0x3F,0xE0,0x3F,0xF0,0x00,0x10,0x00,0x00,

/*e    */
0x03,0xE0,0x07,0xF0,0x05,0x10,0x05,0x10,
0x05,0x10,0x07,0x30,0x03,0x20,0x00,0x00,

/*f    */
0x02,0x10,0x1F,0xF0,0x3F,0xF0,0x22,0x10,
0x30,0x00,0x18,0x00,0x00,0x00,0x00,0x00,

/*g    */
0x03,0xE4,0x07,0xF6,0x04,0x12,0x04,0x12,
0x03,0xFE,0x07,0xFC,0x04,0x00,0x00,0x00,

/*h    */
0x20,0x10,0x3F,0xF0,0x3F,0xF0,0x02,0x00,
0x04,0x00,0x07,0xF0,0x03,0xF0,0x00,0x00,

/*i    */
0x00,0x00,0x00,0x00,0x04,0x10,0x37,0xF0,
0x37,0xF0,0x00,0x10,0x00,0x00,0x00,0x00,

/*j    */
0x00,0x00,0x00,0x0C,0x00,0x0E,0x00,0x02,
0x04,0x02,0x37,0xFE,0x37,0xFC,0x00,0x00,

/*k    */
0x20,0x10,0x3F,0xF0,0x3F,0xF0,0x01,0x80,
0x03,0xC0,0x06,0x70,0x04,0x30,0x00,0x00,

/*l    */
0x00,0x00,0x00,0x00,0x20,0x10,0x3F,0xF0,
0x3F,0xF0,0x00,0x10,0x00,0x00,0x00,0x00,

/*m    */
0x07,0xF0,0x07,0xF0,0x06,0x00,0x03,0xF0,
0x06,0x00,0x07,0xF0,0x03,0xF0,0x00,0x00,

/*n    */
0x04,0x00,0x07,0xF0,0x03,0xF0,0x04,0x00,
0x04,0x00,0x07,0xF0,0x03,0xF0,0x00,0x00,

/*o    */
0x03,0xE0,0x07,0xF0,0x04,0x10,0x04,0x10,
0x04,0x10,0x07,0xF0,0x03,0xE0,0x00,0x00,

/*p    */
0x04,0x02,0x07,0xFE,0x03,0xFE,0x04,0x12,
0x04,0x10,0x07,0xF0,0x03,0xE0,0x00,0x00,

/*q    */
0x03,0xE0,0x07,0xF0,0x04,0x10,0x04,0x12,
0x03,0xFE,0x07,0xFE,0x04,0x02,0x00,0x00,

/*r    */
0x04,0x10,0x07,0xF0,0x03,0xF0,0x06,0x10,
0x04,0x00,0x06,0x00,0x03,0x00,0x00,0x00,

/*s    */
0x02,0x20,0x07,0x30,0x05,0x90,0x04,0x90,
0x04,0xD0,0x06,0x70,0x02,0x20,0x00,0x00,

/*t    */
0x04,0x00,0x04,0x00,0x1F,0xE0,0x3F,0xF0,
0x04,0x10,0x04,0x30,0x00,0x20,0x00,0x00,

/*u    */
0x07,0xE0,0x07,0xF0,0x00,0x10,0x00,0x10,
0x07,0xE0,0x07,0xF0,0x00,0x10,0x00,0x00,

/*v    */
0x00,0x00,0x07,0xC0,0x07,0xE0,0x00,0x30,
0x00,0x30,0x07,0xE0,0x07,0xC0,0x00,0x00,

/*w    */
0x07,0xE0,0x07,0xF0,0x00,0x30,0x00,0xE0,
0x00,0x30,0x07,0xF0,0x07,0xE0,0x00,0x00,

/*x    */
0x04,0x10,0x06,0x30,0x03,0xE0,0x01,0xC0,
0x03,0xE0,0x06,0x30,0x04,0x10,0x00,0x00,

/*y    */
0x07,0xE2,0x07,0xF2,0x00,0x12,0x00,0x12,
0x00,0x16,0x07,0xFC,0x07,0xF8,0x00,0x00,

/*z    */
0x06,0x30,0x06,0x70,0x04,0xD0,0x05,0x90,
0x07,0x10,0x06,0x30,0x04,0x30,0x00,0x00,

0x00,0x00,0x02,0x00,0x02,0x00,0x1F,0xE0,
0x3D,0xF0,0x20,0x10,0x20,0x10,0x00,0x00,

/*|    */
0x00,0x00,0x00,0x00,0x00,0x00,0x3D,0xF0,
0x3D,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,

/*}    */
0x00,0x00,0x20,0x10,0x20,0x10,0x3D,0xF0,
0x1F,0xE0,0x02,0x00,0x02,0x00,0x00,0x00,

/*~    */
0x10,0x00,0x30,0x00,0x20,0x00,0x30,0x00,
0x10,0x00,0x30,0x00,0x20,0x00,0x00,0x00,

/*.    */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,
0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00
};

typedef struct typFNT_GB16
{
	char index[2];
	char mask[32];
};
/* 		汉字 黑体 16x16 点阵    */
const struct typFNT_GB16 gb_16[ ]=
{
"自",
0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFE,
0x09,0x24,0x09,0x24,0x71,0x24,0x69,0x24,
0x09,0x24,0x09,0x24,0x09,0x24,0x09,0x24,
0x0F,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,

"己",
0x00,0x00,0x00,0x00,0x00,0x00,0x21,0xFE,
0x21,0x02,0x21,0x02,0x21,0x02,0x21,0x02,
0x21,0x02,0x21,0x02,0x21,0x02,0x21,0x02,
0x3F,0x82,0x00,0x1E,0x00,0x08,0x00,0x00,

"编",
0x00,0x00,0x02,0x26,0x0E,0x64,0x33,0xA4,
0x06,0x28,0x04,0x10,0x00,0xE0,0x1F,0xFE,
0x14,0x90,0x54,0xFC,0x74,0x90,0x14,0xFC,
0x14,0x9C,0x1C,0x92,0x00,0xFE,0x00,0x00,

"的",
0x00,0x00,0x00,0x00,0x0F,0xFE,0x08,0x88,
0x78,0x88,0x08,0x88,0x0F,0xFE,0x00,0x00,
0x03,0x00,0x1C,0x80,0x38,0xE0,0x08,0x02,
0x08,0x02,0x0F,0xFE,0x0C,0x00,0x00,0x00,

"练",
0x00,0x00,0x06,0x44,0x1E,0xEC,0x33,0xC8,
0x06,0x48,0x0C,0x48,0x10,0x46,0x13,0xCC,
0x17,0x58,0x3A,0x53,0x33,0xFE,0x13,0xFC,
0x10,0x50,0x10,0x58,0x00,0x04,0x00,0x00,

"习",
0x00,0x00,0x00,0x00,0x20,0x18,0x20,0x10,
0x24,0x10,0x26,0x30,0x23,0x20,0x21,0x20,
0x20,0x40,0x20,0x42,0x20,0x02,0x20,0x06,
0x3F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,

"程",
0x00,0x00,0x22,0x30,0x22,0x60,0x23,0x8E,
0x3F,0xFE,0x62,0xC0,0x00,0x02,0x3C,0x92,
0x3C,0x92,0x24,0x92,0x24,0xFE,0x24,0x92,
0x24,0x92,0x3C,0x92,0x00,0x02,0x00,0x00,

"序",
0x00,0x00,0x00,0x06,0x1F,0xFC,0x1F,0x80,
0x10,0x00,0x10,0x40,0x14,0x40,0x15,0x42,
0x75,0x43,0x34,0xFE,0x15,0x40,0x16,0x40,
0x16,0x40,0x14,0x60,0x10,0x40,0x00,0x00,

"显",
0x00,0x00,0x00,0x02,0x00,0x62,0x3F,0x3A,
0x25,0x12,0x25,0x02,0x25,0xFE,0x25,0x02,
0x25,0x02,0x25,0xFE,0x25,0x02,0x25,0x02,
0x3F,0x7A,0x00,0x42,0x00,0x02,0x00,0x00,

"示",
0x00,0x00,0x02,0x00,0x02,0x0C,0x22,0x30,
0x22,0x60,0x22,0x40,0x22,0x03,0x22,0x06,
0x23,0xFE,0x22,0x00,0x22,0x40,0x22,0x60,
0x22,0x30,0x02,0x18,0x02,0x08,0x00,0x00,

"效",
0x00,0x00,0x08,0x82,0x0B,0xC6,0x0E,0x4C,
0x68,0x38,0x28,0xF0,0x0F,0x8E,0x09,0x02,
0x03,0x02,0x0F,0x84,0x78,0x7C,0x48,0x38,
0x0F,0xE4,0x08,0x02,0x08,0x02,0x00,0x00,

"果",
0x00,0x00,0x00,0x44,0x00,0x44,0x3F,0x44,
0x25,0x48,0x25,0x50,0x25,0x60,0x25,0x47,
0x3F,0xFF,0x25,0x60,0x25,0x50,0x25,0x48,
0x3F,0x4C,0x00,0x44,0x00,0x44,0x00,0x00,

"与",
0x00,0x00,0x00,0x00,0x00,0x10,0x01,0x10,
0x7F,0x10,0x51,0x10,0x11,0x10,0x11,0x10,
0x11,0x10,0x11,0x10,0x11,0x13,0x11,0x02,
0x11,0xFE,0x11,0x00,0x00,0x00,0x00,0x00,

"延",
0x00,0x00,0x30,0x02,0x33,0x36,0x3F,0x18,
0x11,0xFC,0x00,0x04,0x10,0x06,0x13,0xF2,
0x10,0x12,0x30,0x12,0x3F,0xF2,0x23,0x12,
0x23,0x12,0x23,0x12,0x00,0x02,0x00,0x00,

"时",
0x00,0x00,0x00,0x00,0x1F,0xFC,0x11,0x10,
0x11,0x10,0x1F,0xF8,0x00,0x00,0x0C,0x00,
0x0D,0x80,0x0C,0xC0,0x0C,0x02,0x0C,0x02,
0x7F,0xFE,0x0C,0x00,0x0C,0x00,0x00,0x00,

"参",
0x00,0x00,0x02,0x40,0x02,0x40,0x0A,0xCB,
0x1A,0xAA,0x1B,0x2A,0x6E,0x4A,0x4A,0x52,
0x0A,0x94,0x0A,0x24,0x3B,0x08,0x1A,0x98,
0x0A,0x50,0x0A,0x40,0x02,0x60,0x00,0x00,

"数",
0x00,0x00,0x09,0x43,0x3B,0x52,0x1E,0x72,
0x7F,0xCC,0x7F,0x4C,0x1E,0x78,0x2B,0x4C,
0x09,0x02,0x0F,0x06,0x79,0xE4,0x08,0x38,
0x08,0x7C,0x0F,0x86,0x08,0x02,0x00,0x00,

"和",
0x00,0x00,0x22,0x10,0x22,0x30,0x22,0xC0,
0x3F,0xFE,0x22,0x00,0x22,0xC0,0x22,0x60,
0x00,0x00,0x1F,0xFC,0x10,0x10,0x10,0x10,
0x10,0x10,0x1F,0xFC,0x18,0x0C,0x00,0x00,

"电",
0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xF8,
0x09,0x20,0x09,0x20,0x09,0x20,0x7F,0xFE,
0x09,0x22,0x09,0x22,0x09,0x22,0x09,0x22,
0x0F,0xE2,0x00,0x06,0x00,0x04,0x00,0x00,

"脑",
0x00,0x00,0x00,0x0E,0x3F,0xF8,0x22,0x44,
0x22,0x46,0x3F,0xFC,0x08,0x00,0x09,0xFE,
0x0C,0x0A,0x0B,0x32,0x78,0xC2,0x0B,0xE2,
0x0E,0x12,0x09,0xFE,0x09,0x86,0x00,0x00,

"速",
0x00,0x00,0x01,0x02,0x31,0x04,0x19,0xFC,
0x00,0x04,0x10,0x0A,0x17,0x92,0x14,0xA2,
0x14,0xC2,0x7F,0xFA,0x14,0x82,0x14,0xC2,
0x14,0xA2,0x17,0x92,0x10,0x12,0x00,0x00,

"度",
0x00,0x00,0x00,0x06,0x1F,0xFC,0x1F,0x80,
0x12,0x03,0x12,0x22,0x1F,0xA2,0x52,0xBA,
0x72,0xAE,0x12,0xA6,0x12,0xAA,0x1F,0xB2,
0x12,0x02,0x12,0x03,0x00,0x02,0x00,0x00,

"有",
0x00,0x00,0x00,0x40,0x10,0x40,0x10,0x80,
0x13,0xFE,0x17,0xFE,0x7A,0x50,0x72,0x50,
0x12,0x50,0x12,0x50,0x12,0x53,0x12,0x52,
0x13,0xFE,0x10,0x00,0x00,0x00,0x00,0x00,

"很",
0x00,0x00,0x08,0x40,0x08,0x80,0x11,0xFE,
0x23,0x00,0x20,0x00,0x00,0x00,0x3F,0xFE,
0x25,0x06,0x25,0x0C,0x25,0xF0,0x25,0x18,
0x25,0x2C,0x3F,0x46,0x00,0x02,0x00,0x00,

"大",
0x00,0x00,0x00,0x02,0x06,0x06,0x06,0x04,
0x06,0x0C,0x06,0x18,0x06,0x70,0x7F,0xC0,
0x7F,0xC0,0x06,0x30,0x06,0x18,0x06,0x0C,
0x06,0x06,0x06,0x06,0x00,0x00,0x00,0x00,

"关",
0x00,0x00,0x00,0x82,0x08,0x43,0x08,0x42,
0x08,0x44,0x78,0x4C,0x18,0x58,0x0F,0xF0,
0x0F,0xE0,0x18,0x50,0x78,0x48,0x08,0x4C,
0x08,0x46,0x08,0x46,0x00,0x42,0x00,0x00,

"系",
0x00,0x00,0x00,0x00,0x20,0x04,0x20,0x48,
0x22,0xD8,0x26,0xC0,0x2B,0x42,0x33,0x42,
0x22,0x7E,0x26,0x40,0x24,0x40,0x29,0x50,
0x60,0xC8,0x20,0x4C,0x00,0x04,0x00,0x00,

"我",
0x00,0x00,0x12,0x20,0x12,0x20,0x12,0x22,
0x1F,0xFE,0x32,0x40,0x22,0x40,0x12,0x06,
0x7E,0x04,0x7F,0xF8,0x02,0x1C,0x32,0x34,
0x1B,0xC2,0x02,0x82,0x00,0x06,0x00,0x00,

"太",
0x00,0x00,0x00,0x02,0x06,0x02,0x06,0x06,
0x06,0x0C,0x06,0x18,0x06,0x70,0x7F,0x8C,
0x47,0xC4,0x06,0x70,0x06,0x18,0x06,0x0C,
0x06,0x06,0x06,0x06,0x00,0x00,0x00,0x00,

"差",
0x00,0x00,0x00,0x84,0x10,0x8C,0x12,0x88,
0x12,0x92,0x72,0xE2,0x33,0xD2,0x1F,0x92,
0x12,0x92,0x12,0x9E,0x72,0x92,0x12,0x92,
0x12,0x92,0x10,0x82,0x00,0x82,0x00,0x00,

"运",
0x00,0x00,0x01,0x02,0x31,0x04,0x19,0xFC,
0x01,0x04,0x02,0x04,0x02,0x12,0x22,0x32,
0x23,0xD2,0x23,0x12,0x22,0x12,0x22,0xD2,
0x22,0x72,0x22,0x32,0x02,0x02,0x00,0x00,

"行",
0x00,0x00,0x04,0x40,0x18,0xC0,0x33,0xFF,
0x66,0x00,0x04,0x00,0x00,0x00,0x23,0x00,
0x23,0x00,0x22,0x02,0x22,0x02,0x23,0xFE,
0x22,0x00,0x23,0x00,0x03,0x00,0x00,0x00,

"起",
0x00,0x00,0x01,0x0E,0x11,0x78,0x11,0x58,
0x7F,0xFC,0x11,0xFC,0x11,0x22,0x01,0x22,
0x00,0x02,0x21,0xF2,0x21,0x12,0x21,0x12,
0x21,0x12,0x3E,0x12,0x00,0x32,0x00,0x00,

"来",
0x00,0x00,0x00,0x84,0x10,0x84,0x14,0x8C,
0x13,0x98,0x10,0xB0,0x10,0xC0,0x7F,0xFE,
0x7F,0xFE,0x10,0xE0,0x13,0xB0,0x16,0x98,
0x10,0x88,0x10,0x8C,0x00,0x84,0x00,0x00,

"老",
0x00,0x00,0x01,0x08,0x01,0x18,0x09,0x10,
0x09,0x20,0x09,0x7E,0x09,0x52,0x7F,0x92,
0x09,0x92,0x0B,0x32,0x07,0x22,0x1D,0x62,
0x31,0x26,0x01,0x04,0x01,0x00,0x00,0x00,

"是",
0x00,0x00,0x00,0x80,0x00,0x86,0x00,0x9C,
0x3E,0xB8,0x2A,0x8C,0x2A,0x84,0x2A,0x84,
0x2A,0xFE,0x2A,0x92,0x2A,0x92,0x3E,0x92,
0x3E,0x92,0x00,0x82,0x00,0x82,0x00,0x00,

"一",
0x00,0x00,0x01,0x80,0x01,0x80,0x01,0x80,
0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,
0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,
0x01,0x80,0x01,0x80,0x01,0x80,0x00,0x00,

"顿",
0x00,0x00,0x0B,0xE0,0x08,0x20,0x08,0x22,
0x3F,0xFE,0x10,0x24,0x13,0xE4,0x00,0x03,
0x27,0xF2,0x24,0x06,0x3D,0x78,0x24,0xE4,
0x24,0x04,0x27,0xF6,0x20,0x02,0x00,0x00,

"相",
0x00,0x00,0x04,0x30,0x04,0xC0,0x7F,0xFE,
0x04,0x80,0x05,0xC0,0x04,0x40,0x38,0x0E,
0x3F,0xFE,0x22,0x44,0x22,0x44,0x22,0x44,
0x22,0x44,0x3F,0xFE,0x00,0x00,0x00,0x00,

"信",
0x00,0x00,0x01,0x80,0x06,0x00,0x3F,0xFF,
0x60,0x00,0x10,0x00,0x14,0xBE,0x14,0xBE,
0x14,0xA4,0x74,0xA4,0x34,0xA4,0x14,0xA4,
0x14,0xA4,0x14,0xBE,0x10,0x00,0x00,0x00,

"换",
0x00,0x00,0x04,0x62,0x04,0x42,0x7F,0xFE,
0x04,0x80,0x04,0x22,0x04,0x22,0x1B,0xE2,
0x72,0x24,0x52,0x38,0x17,0xE0,0x1E,0x38,
0x12,0x24,0x03,0xE6,0x00,0x22,0x00,0x00,

"台",
0x00,0x00,0x00,0x00,0x03,0x00,0x07,0x7E,
0x0F,0x44,0x1B,0x44,0x32,0x44,0x22,0x44,
0x02,0x44,0x02,0x44,0x1A,0x44,0x0E,0x44,
0x06,0x7E,0x03,0x00,0x00,0x00,0x00,0x00,

"好",
0x00,0x00,0x0C,0x02,0x0D,0xE6,0x1F,0x24,
0x78,0x18,0x08,0xF8,0x0F,0x88,0x00,0x00,
0x30,0x80,0x10,0x82,0x10,0x82,0x17,0xFE,
0x18,0x80,0x18,0x80,0x10,0x80,0x00,0x00,

"点",
0x00,0x00,0x00,0x02,0x00,0x0E,0x03,0xE8,
0x02,0x20,0x02,0x24,0x02,0x2E,0x7E,0x20,
0x12,0x20,0x12,0x2E,0x12,0x22,0x12,0x20,
0x13,0xE8,0x10,0x0E,0x00,0x02,0x00,0x00,

"会",
0x00,0x00,0x02,0x00,0x02,0x40,0x06,0x46,
0x0E,0x46,0x1A,0x4A,0x32,0x72,0x62,0x42,
0x72,0x42,0x1A,0x44,0x0A,0x5C,0x04,0x4C,
0x06,0x46,0x02,0x42,0x02,0x00,0x00,0x00,

"更",
0x00,0x00,0x20,0x02,0x20,0x02,0x2F,0xC2,
0x29,0x76,0x29,0x5C,0x29,0x4C,0x3F,0xFC,
0x3F,0xC4,0x29,0x46,0x29,0x46,0x29,0x42,
0x2F,0xC2,0x20,0x02,0x20,0x03,0x00,0x00,

"我",
0x00,0x00,0x12,0x20,0x12,0x20,0x12,0x22,
0x1F,0xFE,0x32,0x40,0x22,0x40,0x12,0x06,
0x7E,0x04,0x7F,0xF8,0x02,0x1C,0x32,0x34,
0x1B,0xC2,0x02,0x82,0x00,0x06,0x00,0x00,

"爱",
0x00,0x00,0x07,0x08,0x27,0x08,0x24,0x9B,
0x3C,0xB3,0x24,0xE2,0x25,0xFA,0x35,0xAE,
0x2C,0xA4,0x24,0xA6,0x24,0xBA,0x7C,0xB2,
0x64,0xA2,0x24,0x03,0x07,0x03,0x00,0x00,

"金",
0x00,0x00,0x02,0x00,0x02,0x02,0x06,0x42,
0x0E,0x5A,0x1A,0x4A,0x32,0x42,0x63,0xFE,
0x32,0x42,0x1A,0x42,0x0A,0x5E,0x06,0x5A,
0x06,0x42,0x06,0x02,0x02,0x00,0x00,0x00,

"鱼",
0x00,0x00,0x02,0x02,0x06,0x02,0x0F,0xFA,
0x1A,0x4A,0x32,0x4A,0x52,0x4A,0x13,0xFA,
0x17,0xFA,0x1E,0x4A,0x12,0x4A,0x02,0x4A,
0x03,0xFA,0x00,0x02,0x00,0x02,0x00,0x00,

"警",
0x00,0x00,0x24,0x40,0x2F,0x40,0x7D,0x77,
0x2D,0x76,0x2F,0x76,0x7B,0x76,0x2F,0xB6,
0x20,0xB6,0x11,0x76,0x6D,0x76,0x66,0x76,
0x2E,0x77,0x31,0x40,0x21,0x40,0x00,0x00,

"告",
0x00,0x00,0x01,0x00,0x05,0x00,0x0D,0x3F,
0x39,0x24,0x09,0x24,0x09,0x24,0x7F,0x24,
0x7F,0x24,0x09,0x24,0x09,0x24,0x09,0x24,
0x09,0x3E,0x01,0x00,0x01,0x00,0x00,0x00,

"史",
0x00,0x00,0x00,0x02,0x00,0x02,0x0F,0x82,
0x08,0xA6,0x08,0xB4,0x08,0x9C,0x08,0xFC,
0x7F,0xC4,0x08,0x84,0x08,0x86,0x08,0x82,
0x0F,0x82,0x00,0x02,0x00,0x02,0x00,0x00,

"上",
0x00,0x00,0x00,0x02,0x00,0x02,0x00,0x02,
0x00,0x02,0x00,0x02,0x00,0x02,0x3F,0xFE,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0x02,0x02,0x00,0x02,0x00,0x00,

"最",
0x00,0x00,0x01,0x04,0x01,0x04,0x7D,0xFC,
0x55,0x54,0x55,0x54,0x55,0x54,0x55,0xFE,
0x55,0x42,0x55,0x72,0x55,0x4C,0x55,0x4C,
0x7D,0x74,0x01,0x02,0x01,0x00,0x00,0x00,

"帅",
0x00,0x00,0x00,0x00,0x1F,0xF2,0x00,0x06,
0x20,0xF8,0x3F,0xC0,0x00,0x00,0x0F,0xF8,
0x08,0x00,0x08,0x00,0x7F,0xFE,0x08,0x00,
0x08,0x18,0x0F,0xF0,0x00,0x00,0x00,0x00,

"的",
0x00,0x00,0x00,0x00,0x0F,0xFE,0x08,0x88,
0x78,0x88,0x08,0x88,0x0F,0xFE,0x00,0x00,
0x03,0x00,0x1C,0x80,0x38,0xE0,0x08,0x02,
0x08,0x02,0x0F,0xFE,0x0C,0x00,0x00,0x00,

"哥",
0x00,0x00,0x00,0x80,0x20,0x80,0x3E,0xBC,
0x32,0xA8,0x32,0xA8,0x32,0xA8,0x32,0xA8,
0x3E,0xBC,0x3E,0x82,0x20,0x83,0x3E,0xFE,
0x3E,0xFE,0x20,0x80,0x60,0x80,0x00,0x00,

"刘",
0x00,0x00,0x08,0x00,0x08,0x04,0x09,0x08,
0x38,0xF0,0x28,0x60,0x0F,0xB0,0x0C,0x1C,
0x08,0x00,0x00,0x00,0x1F,0xF0,0x00,0x00,
0x00,0x02,0x3F,0xFE,0x00,0x00,0x00,0x00,

"伟",
0x00,0x00,0x01,0x80,0x07,0x00,0x1F,0xFE,
0x30,0x00,0x00,0x40,0x0A,0x40,0x0A,0x40,
0x0A,0x40,0x7F,0xFE,0x0A,0x40,0x0A,0x40,
0x0A,0x46,0x0A,0x7C,0x08,0x78,0x00,0x00,

"出",
0x00,0x00,0x00,0x00,0x00,0x7C,0x1F,0x04,
0x01,0x04,0x01,0x04,0x01,0x04,0x7F,0xFC,
0x61,0x04,0x01,0x04,0x01,0x04,0x01,0x04,
0x1F,0x7F,0x00,0x7F,0x00,0x00,0x00,0x00,

"没",
0x00,0x00,0x00,0x00,0x26,0x0E,0x23,0x38,
0x10,0x00,0x00,0x02,0x02,0x82,0x3E,0xC2,
0x38,0xB4,0x20,0x9C,0x20,0x9C,0x3C,0xB4,
0x06,0xC6,0x02,0x02,0x02,0x02,0x00,0x00
};