#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "stm32f10x.h"
#include "bsp_SysTick.h"
#include "bsp_usart1.h"


#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int

extern u32 T_led;
extern u32 T_max6675;
extern float temp;
extern u32 T_pid;


#endif


