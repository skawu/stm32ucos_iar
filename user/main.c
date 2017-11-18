#include "stm32f10x.h"
#include "led.h"
#include <ucos_ii.h>

void delay(u32 i)
{
	while (i--);
}

static OS_STK Task_led_STK[OS_TASK_STAT_STK_SIZE];
static OS_STK Task_led_STK2[OS_TASK_STAT_STK_SIZE];

void Task_led(void *p_arg);
void Task_buz(void *p_arg);

/* ����ϵͳtick systick */
void SySTick_init(void)
{
	SysTick_Config(SystemCoreClock  / OS_TICKS_PER_SEC);
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	SySTick_init();
	OSInit();
	LED_gpio_init();
	OSTaskCreate(Task_led, (void *)0, &Task_led_STK[OS_TASK_STAT_STK_SIZE - 1], 3);
	OSTaskCreate(Task_buz, (void *)0, &Task_led_STK2[OS_TASK_STAT_STK_SIZE - 1], 2);
	OSStart();
	return 0;
}

void Task_led(void *p_arg)
{
	while (1)
	{
		static unsigned char i = 0;
		LED_GPIO_set((i % 8), 1);
		OSTimeDly(500);
		LED_GPIO_set((i % 8), 0);
		OSTimeDly(500);
		i++;
	}
}

void Task_buz(void *p_arg)
{
	int i = 1;

	while (1)
	{
		for (i = 1; i < 100; i++)
		{			
			LED_GPIO_set(8, 0);
			OSTimeDly(i);
            LED_GPIO_set(8, 1);
			OSTimeDly(i);
		}
	}
}
