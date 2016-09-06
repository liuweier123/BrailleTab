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

//����MCUʱ��Ƶ��
//#define F_CPU 14745600
#define F_CPU 7372800
//**************************************************
//����ϵͳͷ�ļ��������ʵ����Ҫ���вü�
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
//ϵͳ�������Ͷ���
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
typedef unsigned char  uint8;                                   /* �������ֲ���޷���8λ�����ؼ���            */
typedef signed   char  int8;                                    /* �������ֲ���з���8λ�����ؼ���            */
typedef unsigned int   uint16;                                  /* �������ֲ���޷���16λ�����ؼ���           */
typedef signed   int   int16;                                   /* �������ֲ���з���16λ�����ؼ���           */
typedef unsigned long  uint32;                                  /* �������ֲ���޷���32λ�����ؼ���           */
typedef signed   long  int32;                                   /* �������ֲ���з���32λ�����ؼ���           */

//**************************************************
//��������ͷ�ļ����������Ҫ���вü�
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
//һ��Ϊ���̱������˿ڶ���
//**************************************************

/********************************/
/*     "����Ϊ��������"         */
/********************************/

#endif


/**********************end****************************************/
