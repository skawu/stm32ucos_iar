#ifndef __UART_H__
#define __UART_H__

#include "stm32f10x.h"
#include "queue.h"

typedef struct Uart
{
	u32 baud;
	u8  stop;
	u8  parity;
	u16 pin_tx;
	u16 pin_rx;
	u32 pin_rcc;
	u32 uart_rcc;
	u8  IRQChannel;
	u8 subPriority;
	GPIO_TypeDef *gpiorx;
	GPIO_TypeDef *gpiotx;
	USART_TypeDef *uartx;
	queue_t *uart_queue;
} uart_t;

void init_uart(uart_t *uart);
void uart_send_char(uart_t *uart, u8 value);
void uart_send_string(uart_t *uart, u8 *value);
void uart_send_array(uart_t *uart, u8 *value, u16 length);


#endif
