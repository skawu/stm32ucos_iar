#include "mpu6050.h"


/*
    MPU-60X0��Slave��ַΪ b110100X�� 7λ�ֳ��������Чλ X�� AD0�ܽ��ϵ��߼���ƽ����
 */

void mpu6050_init(void)
{
    I2C_Start();
    I2C_send_byte((unsigned char) MPU6050_ADDR_W);
    I2C_Stop();
}
