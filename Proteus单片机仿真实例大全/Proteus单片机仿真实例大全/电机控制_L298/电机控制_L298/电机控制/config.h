#ifndef __config_H__
#define __config_H__ 1

/*********************************************/
#define M8    1
#define M16   2
#define M32   3
#define M64   4
#define M128  5
/*********************************************/
#define CPU_TYPE  M32

//定义MCU时钟频率
//#define F_CPU 14745600
#define F_CPU 7372800
//**************************************************
//包含系统头文件，请根据实际需要进行裁减
//**************************************************
//#pragma REGPARMS
#if CPU_TYPE == M128
#include <iom128v.h>
#endif
#if CPU_TYPE == M64
#include <iom64v.h>
#endif
#if CPU_TYPE == M32
#include <iom32v.h>
#endif
#if CPU_TYPE == M16
#include <iom16v.h>
#endif
#if CPU_TYPE == M8
#include <iom8v.h>
#endif
//#include <intrins.h>
//#include <absacc.h>
//#include <string.h>
//#include <FLOAT.H>
//#include <math.h>
//#include <stdlib.h>
#include <macros.h>
//#include <eeprom.h>
//#define const code

//**************************************************
//系统数据类型定义
//**************************************************
#ifndef TRUE
#define TRUE  1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef NULL
#define NULL 0
#endif
#define MIN(a,b)			((a<b)?(a):(b))
#define MAX(a,b)			((a>b)?(a):(b))
#define ABS(x)				((x>0)?(x):(-x))
typedef unsigned char  uint8;                                   /* 定义可移植的无符号8位整数关键字            */
typedef signed   char  int8;                                    /* 定义可移植的有符号8位整数关键字            */
typedef unsigned int   uint16;                                  /* 定义可移植的无符号16位整数关键字           */
typedef signed   int   int16;                                   /* 定义可移植的有符号16位整数关键字           */
typedef unsigned long  uint32;                                  /* 定义可移植的无符号32位整数关键字           */
typedef signed   long  int32;                                   /* 定义可移植的有符号32位整数关键字           */

//**************************************************
//包含工程头文件，请根据需要进行裁减
//**************************************************
#include "delay.h"
#include "device_init.h"
#include "motor.h"
//#include "lcddrive.h"
//#include "main.h"
//#include "queue.h"
//#include "TWI.h"
//#include "sio.h"
//**************************************************
//一下为工程变量、端口定义
//**************************************************

/********************************/
/*     "以下为工程配置"         */
/********************************/

#endif


/**********************end****************************************/
