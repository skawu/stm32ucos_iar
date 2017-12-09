#include "i2c.h"
#include "mpu6050.h"
#include <stdio.h>

#ifndef  I2C_GPIO_SIMULATE
/*****************************************************************************
 * 函 数 名  : I2C_GPIO_Init
 * 负 责 人  : skawu
 * 创建日期  : 2017年12月9日
 * 函数功能  : 初始化I2C1的GPIO
 * 输入参数  : void  无
 * 输出参数  : 无
 * 返 回 值  :
 * 调用关系  :
 * 其    它  :

*****************************************************************************/
void I2C_GPIO_Init(void)
{
	GPIO_InitTypeDef    GPIO_InitTypeStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_DeInit(GPIOB);
	GPIO_InitTypeStructure.GPIO_Pin = I2C_SCL;
	GPIO_InitTypeStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitTypeStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(I2C_GPIO, &GPIO_InitTypeStructure);
	GPIO_InitTypeStructure.GPIO_Pin = I2C_SDA;
	GPIO_InitTypeStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitTypeStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(I2C_GPIO, &GPIO_InitTypeStructure);
}

/*****************************************************************************
 * 函 数 名  : I2C_init
 * 负 责 人  : skawu
 * 创建日期  : 2017年12月9日
 * 函数功能  : 初始化I2C1
 * 输入参数  : void  无
 * 输出参数  : 无
 * 返 回 值  :
 * 调用关系  :
 * 其    它  :

*****************************************************************************/
void I2C_init(void)
{
	I2C_InitTypeDef     I2C_InitTypeStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	I2C_DeInit(I2C1);
	I2C_InitTypeStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitTypeStructure.I2C_OwnAddress1 = 0x03;
	I2C_InitTypeStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitTypeStructure.I2C_ClockSpeed = 20000;       // 20k sck频率
	I2C_InitTypeStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitTypeStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_Init(I2C1, &I2C_InitTypeStructure);
	I2C_Cmd(I2C1, ENABLE);
}

/*****************************************************************************
 * 函 数 名  : I2C_send
 * 负 责 人  : skawu
 * 创建日期  : 2017年12月9日
 * 函数功能  : 向I2C设备地址写入一个数据
 * 输入参数  : I2C_TypeDef * I2Cx  选择发送的I2C设备
               unsigned char val   待写的数据
               unsigned char addr  写入的地址
 * 输出参数  : 无
 * 返 回 值  :
 * 调用关系  :
 * 其    它  :

*****************************************************************************/
void I2C_send(I2C_TypeDef *I2Cx, unsigned char val, unsigned char addr)
{
	I2C_GenerateSTART(I2Cx, ENABLE);

	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))     // I2C1->SR1 == 0x1
	{ I2C_Send7bitAddress(I2Cx, MPU6050_ADDR_W, I2C_Direction_Transmitter); }

	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))   // 发送
	{ I2C_SendData(I2Cx, addr); }

	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2Cx, val);

	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTOP(I2Cx, ENABLE);
}


/*****************************************************************************
 * 函 数 名  : I2C_read
 * 负 责 人  : skawu
 * 创建日期  : 2017年12月9日
 * 函数功能  : 从I2C设备地址中读取一个数据
 * 输入参数  : I2C_TypeDef * I2Cx  要读取的I2C设备
               unsigned char addr  要读取数据的地址
 * 输出参数  : 无
 * 返 回 值  : unsigned
 * 调用关系  :
 * 其    它  :

*****************************************************************************/
unsigned char I2C_read(I2C_TypeDef *I2Cx, unsigned char addr)
{
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
	I2C_GenerateSTART(I2Cx, ENABLE);

	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))     // I2C1->SR1 == 0x1
	{ I2C_Send7bitAddress(I2Cx, MPU6050_ADDR_W, I2C_Direction_Transmitter); }

	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))   // 发送要读的地址
	{ I2C_SendData(I2Cx, addr); }

	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTART(I2Cx, ENABLE);

	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))     // I2C1->SR1 == 0x1
	{ I2C_Send7bitAddress(I2Cx, MPU6050_ADDR_R, I2C_Direction_Receiver); }

	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

	I2C_AcknowledgeConfig(I2Cx, DISABLE);
	I2C_GenerateSTOP(I2Cx, ENABLE);

	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));

	return I2C_ReceiveData(I2Cx);
}





#else       // 以下为GPIO模拟I2C

void i2c_delay(void)
{
	unsigned int i = 500;

	while (i--);
}


void SCL_config(unsigned char val)
{
	if (val)
	{
		GPIO_SetBits(GPIOB, I2C_SCL);
	}
	else
	{
		GPIO_ResetBits(GPIOB, I2C_SCL);
	}
}

void SDA_config(unsigned char val)
{
	if (val)
	{
		GPIO_SetBits(GPIOB, I2C_SDA);
	}
	else
	{
		GPIO_ResetBits(GPIOB, I2C_SDA);
	}
}


unsigned char SCL_read(void)
{
	unsigned char value;
	value = GPIO_ReadInputDataBit(I2C_GPIO, I2C_SCL);
	return value;
}

unsigned char SDA_read(void)
{
	unsigned char value = 1;
	value = GPIO_ReadInputDataBit(I2C_GPIO, I2C_SDA);
	return value;
}
/*
    Start:
        当SCL线为高电平时，SDA由高到低的下降沿，为传输开始标志(S)
*/

void I2C_Start(void)
{
	SCL_HIGH;
	i2c_delay();
	SDA_HIGH;
	i2c_delay();
	SDA_LOW;
	i2c_delay();
	SCL_LOW;
}

/*
    Stop:
        当SCL线为高电平时，SDA由低到高的上升沿，为传输结束标志(P)
*/
void I2C_Stop(void)
{
	SCL_HIGH;
	i2c_delay();
	SDA_LOW;
	i2c_delay();
	SDA_HIGH;
}

void I2C_send_byte(unsigned char val)
{
	unsigned char i = 0;

	while (i < 7)
	{
		SCL_LOW;
		i2c_delay();

		if ((val << i) & 0x80)     // I2C发送高位在前
		{
			SDA_HIGH;
		}
		else
		{
			SDA_LOW;
		}

		i2c_delay();
		SCL_HIGH;
		i2c_delay();
		i++;
	}

	SDA_HIGH;
	i2c_delay();

	/* 等待应答，在SCL为高时，SDA为低 */
	while (SDA_read());
}

#endif

