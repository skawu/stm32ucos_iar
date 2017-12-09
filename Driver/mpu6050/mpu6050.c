#include "mpu6050.h"
#include "uart.h"


/*
    MPU-60X0的Slave地址为 b110100X， 7位字长，最低有效位 X由 AD0管脚上的逻辑电平决定
 */

void mpu6050_init(void)
{
	unsigned char mac = 0;
	I2C_GPIO_Init();
	I2C_init();
	mac = I2C_read(I2C1, (unsigned char)WHO_AM_I);

	if (!mac)
	{
		USART_SendStr(USART3, "error\r\n");
		return ;
	}
	else
	{
		USART_SendChar(USART3, mac);
	}
}
