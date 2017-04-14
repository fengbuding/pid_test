#include "pwm.h"

void PWM_Init(void)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE); 
	                                                                         	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	TIM_TimeBaseStructure.TIM_Period = 255; 	 
	TIM_TimeBaseStructure.TIM_Prescaler =72000 - 1; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
	
	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  
	
	TIM_ARRPreloadConfig(TIM4, ENABLE); 
	TIM_Cmd(TIM4, ENABLE);  
}
