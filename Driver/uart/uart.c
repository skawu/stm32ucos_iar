#include "uart.h"
#include <stdio.h>

void init_uart(uart_t *uart)
{
	GPIO_InitTypeDef GPIO_InitTypeStructure;
	USART_InitTypeDef USART_InitTypeStructure;
	NVIC_InitTypeDef    NVIC_InitTypeStructure;
	/* gpio口初始化 */
	RCC_APB2PeriphClockCmd(uart->pin_rcc, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitTypeStructure.GPIO_Pin = uart->pin_rx;
	GPIO_InitTypeStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitTypeStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(uart->gpiorx, &GPIO_InitTypeStructure);
	GPIO_InitTypeStructure.GPIO_Pin = uart->pin_tx;
	GPIO_InitTypeStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(uart->gpiotx, &GPIO_InitTypeStructure);
	/* 串口初始化 */

	if (uart->uart_rcc == RCC_APB2Periph_USART1)
	{
		RCC_APB1PeriphClockCmd(uart->uart_rcc, ENABLE);
	}
	else
	{
		RCC_APB2PeriphClockCmd(uart->uart_rcc, ENABLE);
	}

	USART_DeInit(uart->uartx);
	USART_InitTypeStructure.USART_BaudRate = uart->baud;
	USART_InitTypeStructure.USART_StopBits = uart->stop;
	USART_InitTypeStructure.USART_Parity = uart->parity;
	USART_InitTypeStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitTypeStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitTypeStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* 中断优先级配置 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);             // 中断优先级使用NVIC_PriorityGroup_2，2bit pre; 2bit sub
	NVIC_InitTypeStructure.NVIC_IRQChannel = uart->IRQChannel;
	NVIC_InitTypeStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitTypeStructure.NVIC_IRQChannelSubPriority = uart->subPriority;
	NVIC_InitTypeStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitTypeStructure);
	USART_ITConfig(uart->uartx, USART_IT_RXNE, ENABLE);     // 使能串口接收中断
	USART_Init(uart->uartx, &USART_InitTypeStructure);
	USART_Cmd(uart->uartx, ENABLE);                         //使能串口
}


void uart_send_char(uart_t *uart, u8 value)
{
	USART_SendData(uart->uartx, (u16)value);

	while (USART_GetFlagStatus(uart->uartx, USART_FLAG_TC) == RESET);
}

void uart_send_string(uart_t *uart, u8 *value)
{
	while (*value != '\0')
	{
		uart_send_char(uart, *value);
		value++;
	}
}

void uart_send_array(uart_t *uart, u8 *value, u16 length)
{
	u16 i = 0;

	for (i = 0; i < length; i++)
	{
		uart_send_char(uart, value[i]);
	}
}

int fputc(int ch, FILE *f)
{
	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
	{}

	USART_SendData(USART3, (u8) ch);
	return ch;
}

