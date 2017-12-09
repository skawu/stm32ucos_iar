#ifndef __MPU6050_H__
#define __MPU6050_H__

#include "i2c.h"

#define MPU6050_ADDR_W  11010000        // AD0?????
#define MPU6050_ADDR_R  11010001


/* 定义MPU6050寄存器地址 */
#define SELF_TEST_X     0x0D
#define SELF_TEST_Y     0x0E
#define SELF_TEST_Z     0x0F
#define SELF_TEST_A     0x10
#define SMPRT_DIV       0x19        // 采样频率分频器 sample rate divider
#define CONFIG          0x1A        // 配置
#define WHO_AM_I        0x75        // 设备身份标识寄存器



extern void mpu6050_init(void);

#endif

