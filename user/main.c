#include "stm32f10x.h"
#include "led.h"

void delay(u32 i)
{
	while (i--);
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
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

	return 0;
}
