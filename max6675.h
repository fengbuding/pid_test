#ifndef _6675_H
#define _6675_H

#include "global.h"

extern float temper;
extern void delay_us(u32  us);
u16 read_max6675(void);  
void Max6675_Init(void);
float read_temperature();

#endif



