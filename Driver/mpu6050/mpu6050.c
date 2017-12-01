#include "mpu6050.h"


/*
    MPU-60X0的Slave地址为 b110100X， 7位字长，最低有效位 X由 AD0管脚上的逻辑电平决定
 */

void mpu6050_init(void)
{
    I2C_Start();
    I2C_send_byte((unsigned char) MPU6050_ADDR_W);
    I2C_Stop();
}
