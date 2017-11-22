#ifndef __LED_H__
#define __LED_H__

#define OS_TASK_LED_STK_SIZE    32      // led任务不需要那么大的堆栈空间128

void LED_gpio_init(void);
void LED_GPIO_set(unsigned char gpio_num, unsigned char value);

#endif