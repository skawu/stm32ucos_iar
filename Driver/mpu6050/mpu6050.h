#ifndef __MPU6050_H__
#define __MPU6050_H__

#include "i2c.h"

#define MPU6050_ADDR_W  11010000        // AD0Ω”µÕµÁ∆Ω
#define MPU6050_ADDR_R  11010001


extern void mpu6050_init(void);

#endif

