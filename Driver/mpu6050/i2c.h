#ifndef __I2C_H__
#define __I2C_H__

#include "stm32f10x.h"

/*
    I2C_SCL				PB6
    I2C_SDA				PB7
*/
#define  I2C_SCL    GPIO_Pin_6
#define  I2C_SDA    GPIO_Pin_7
#define  I2C_GPIO   GPIOB


#define SCL_HIGH    SCL_config(1)
#define SCL_LOW     SCL_config(0)
#define SDA_HIGH    SDA_config(1)
#define SDA_LOW     SDA_config(0)


extern void I2C_Start(void);
extern void I2C_Stop(void);
extern void I2C_send_byte(unsigned char val);
#endif