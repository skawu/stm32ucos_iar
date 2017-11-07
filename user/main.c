#include "stm32f10x.h"
#include "led.h"
#include <ucos_ii.h>

void delay(u32 i)
{
	while (i--);
}

static OS_STK Task_led_STK[OS_TASK_STAT_STK_SIZE];

void Task_led (void *p_arg);
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	OSInit();
    OSTaskCreate(Task_led, (void*)0, &Task_led_STK[OS_TASK_STAT_STK_SIZE - 1], 0);
	OSStart();

	return 0;
}

void Task_led (void *p_arg)
{
    LED_gpio_init();
    while (1)
	{
		static unsigned char i = 0;
		LED_GPIO_set((i % 8), 1);
		delay(6000000);
		LED_GPIO_set((i % 8), 0);
		delay(6000000);
		i++;
	}
}