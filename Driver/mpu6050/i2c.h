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




#ifndef I2C_GPIO_SIMULATE

void I2C_GPIO_Init(void);
void I2C_init(void);
void I2C_send(I2C_TypeDef *I2Cx, unsigned char val, unsigned char addr);
unsigned char I2C_read(I2C_TypeDef *I2Cx, unsigned char addr);

#else

#define SCL_HIGH    SCL_config(1)
#define SCL_LOW     SCL_config(0)
#define SDA_HIGH    SDA_config(1)
#define SDA_LOW     SDA_config(0)

extern void I2C_Start(void);
extern void I2C_Stop(void);
extern void I2C_send_byte(unsigned char val);
#endif
#endif