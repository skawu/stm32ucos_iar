
#include "led.h"
#include "stm32f10x.h"

/*
 *	led相关gpio初始化
 */
void LED_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruction;
	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStruction.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
	                              GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruction.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruction);
	/* 蜂鸣器 PB5 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStruction.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruction.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruction);
}

void LED_GPIO_set(unsigned char gpio_num, unsigned char value)
{
	switch (gpio_num)
	{
		case 0:
			{
				if (value)
				{ GPIO_SetBits(GPIOC, GPIO_Pin_0); }
				else
				{ GPIO_ResetBits(GPIOC, GPIO_Pin_0); }
			}
			break;

		case 1:
			{
				if (value)
				{ GPIO_SetBits(GPIOC, GPIO_Pin_1); }
				else
				{ GPIO_ResetBits(GPIOC, GPIO_Pin_1); }
			}
			break;

		case 2:
			{
				if (value)
				{ GPIO_SetBits(GPIOC, GPIO_Pin_2); }
				else
				{ GPIO_ResetBits(GPIOC, GPIO_Pin_2); }
			}
			break;

		case 3:
			{
				if (value)
				{ GPIO_SetBits(GPIOC, GPIO_Pin_3); }
				else
				{ GPIO_ResetBits(GPIOC, GPIO_Pin_3); }
			}
			break;

		case 4:
			{
				if (value)
				{ GPIO_SetBits(GPIOC, GPIO_Pin_4); }
				else
				{ GPIO_ResetBits(GPIOC, GPIO_Pin_4); }
			}
			break;

		case 5:
			{
				if (value)
				{ GPIO_SetBits(GPIOC, GPIO_Pin_5); }
				else
				{ GPIO_ResetBits(GPIOC, GPIO_Pin_5); }
			}
			break;

		case 6:
			{
				if (value)
				{ GPIO_SetBits(GPIOC, GPIO_Pin_6); }
				else
				{ GPIO_ResetBits(GPIOC, GPIO_Pin_6); }
			}
			break;

		case 7:
			{
				if (value)
				{ GPIO_SetBits(GPIOC, GPIO_Pin_7); }
				else
				{ GPIO_ResetBits(GPIOC, GPIO_Pin_7); }
			}
			break;

		case 8:
			{
				if (value)
				{ GPIO_SetBits(GPIOB, GPIO_Pin_5); }
				else
				{ GPIO_ResetBits(GPIOB, GPIO_Pin_5); }
			}
			break;
	}
}



