#include "global.h"
#include "bsp_usart1.h"
#include "bsp_TiMbase.h" 
#include "bsp_SysTick.h"
#include "stm32f10x_it.h"
#include "string.h"
#include "LED.h"
#include "port.h"
#include "adc.h"
#include "max6675.h"
#include "pwm.h"
#include "pid.h"

int main(void) 
{
    u32 time = 0;
    SysTick_Init();
    UsartInit();
    LED_Gpioinit();
    //Port_Gpioinit();
    Max6675_Init();
    PWM_Init();
    TIM2_Configuration();
    TIM3_Configuration();
    PID_Init();
    printf("system start...\r\n");
    for(;;)
    {	
      if((T_max6675 ^ 20) == 0)  //200ms
      {
          T_max6675 = 0;
          //读取温度值放入结构体
          pid.actualnum = read_temperature();                  
         // printf("temperature is %f\r\n", pid.actualnum);
      }
      if((T_pid ^ 50) == 0)  //500ms
      {
          T_pid = 0;
          temp = realizepid(200);    
         // printf("temperature %f pid.controlmachine:%f CCR2:%d\r\n", pid.actualnum, temp, TIM4->CCR3);
          printf("%d,%f,%f,%d\r\n", time++, pid.actualnum, temp, TIM4->CCR3);
        //  printf("%c", (u16)pid.actualnum);
      }
      if((T_led ^ 100) == 0)   //1s
      {
          T_led = 0;
          bsp_LedToggle(BLUE);
      }
    }
}
/*********************************************END OF FILE**********************/
