#include "uart.h"


void init_uart(uart_t *uart)
{
	/* gpio口初始化 */
	GPIO_InitTypeDef GPIO_InitTypeStructure;
	RCC_APB2PeriphClockCmd(uart->pin_rcc, ENABLE);
	GPIO_InitTypeStructure.GPIO_Pin = uart->pin_rx;
	GPIO_InitTypeStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitTypeStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(uart->gpiorx, &GPIO_InitTypeStructure);
	GPIO_InitTypeStructure.GPIO_Pin = uart->pin_tx;
	GPIO_InitTypeStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(uart->gpiotx, &GPIO_InitTypeStructure);
	/* 串口初始化 */
	USART_InitTypeDef USART_InitTypeStructure;

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
	USART_Init(uart->uartx, &USART_InitTypeStructure);
}
