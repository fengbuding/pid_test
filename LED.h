#ifndef _LED_H_
#define _LED_H_

#include "global.h"
#define RCC_LED 	      RCC_APB2Periph_GPIOC
#define GPIO_PORT_LED     GPIOC
#define GPIO_PIN_BLUE	  GPIO_Pin_13
typedef enum
{
  BLUE,
}LED_COLOUR_t;
void LED_Gpioinit(void);
void bsp_LedOn(LED_COLOUR_t _no);
void bsp_LedOff(LED_COLOUR_t _no);
void bsp_LedToggle(LED_COLOUR_t _no);

#endif

