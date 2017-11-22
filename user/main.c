#include "stm32f10x.h"
#include <ucos_ii.h>

#include "led.h"
#include "esp8266.h"


void delay(u32 i)
{
	while (i--);
}

static OS_STK Task_led_STK[OS_TASK_LED_STK_SIZE];
static OS_STK Task_led_STK2[OS_TASK_LED_STK_SIZE];
static OS_STK Task_esp8266_STK[OS_TASK_STAT_STK_SIZE];


/* 定义系统tick systick */
void SySTick_init(void)
{
	SysTick_Config(SystemCoreClock  / OS_TICKS_PER_SEC);
}

/* 外设统一初始化 */
void peri_init(void)
{
	SySTick_init();     // 应该放在第一个任务while之前执行
	LED_gpio_init();
	init_esp8266();
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

void Task_esp8266(void *p_arg)
{
	while (1)
	{
		esp8266_handle();
	}
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	OSInit();
	peri_init();
	OSTaskCreate(Task_led, (void *)0, &Task_led_STK[OS_TASK_LED_STK_SIZE- 1], 3);
	OSTaskCreate(Task_buz, (void *)0, &Task_led_STK2[OS_TASK_LED_STK_SIZE - 1], 2);
    OSTaskCreate(Task_esp8266, (void *)0, &Task_esp8266_STK[OS_TASK_STAT_STK_SIZE - 1], 4);
	OSStart();
	return 0;
}

