#include "max6675.h"
#include "pid.h"

#define cs_1    GPIO_SetBits(GPIOC, GPIO_Pin_11)
#define cs_0    GPIO_ResetBits(GPIOC, GPIO_Pin_11)

#define sck_1   GPIO_SetBits(GPIOC, GPIO_Pin_12)
#define sck_0   GPIO_ResetBits(GPIOC, GPIO_Pin_12)

#define so GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2) 

u16 read_max6675()  
{
  u16 d, i; 
  //so_1;
  cs_0;
  Delay_10us(1);
  for(i = 0; i < 16; i++)
  {
    sck_1;
    Delay_10us(1);
    sck_0;
    Delay_10us(1);
    d <<= 1;
    if(so)
     d++;
  }
  cs_1;
  return d;
}

float read_temperature()
{
  u16 d;
  d = read_max6675();
  temp = ((d >> 4) & 0x0fff) * 0.25;
  return temp;
}


void Max6675_Init()
{
 GPIO_InitTypeDef GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); 
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);  
	
	 
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_11;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_12;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}


