#ifndef __LED_H__
#define __LED_H__

#define OS_TASK_LED_STK_SIZE    32      // led������Ҫ��ô��Ķ�ջ�ռ�128

void LED_gpio_init(void);
void LED_GPIO_set(unsigned char gpio_num, unsigned char value);

#endif