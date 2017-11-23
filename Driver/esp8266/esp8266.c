#include "esp8266.h"



u8 uart2_buffer[BUFFER_SIZE];
u8 uart3_buffer[BUFFER_SIZE];

queue_t uart2_queue =
{
	.p              = uart2_buffer,
	.read_ptr       = 0,
	.write_ptr      = 0,
	.buf_len        = BUFFER_SIZE,
	.data_length    = 0,
};
queue_t uart3_queue =
{
	.p              = uart3_buffer,
	.read_ptr       = 0,
	.write_ptr      = 0,
	.buf_len        = BUFFER_SIZE,
	.data_length    = 0,
};





void init_esp8266(void)
{
	UART_config(USART3);
	UART_config(USART2);
	GPIO_SetBits(GPIOG, GPIO_Pin_7);
//    GPIO_ResetBits(GPIOG, GPIO_Pin_7);
}

void esp8266_handle(void)
{
	u8 temp = 0;

	while (!queue_is_empty(&uart3_queue))
	{
		temp = queue_get(&uart3_queue);
		USART_SendChar(USART2, temp);
		USART_SendChar(USART3, temp);
	}

	while (!queue_is_empty(&uart2_queue))
	{
		temp = queue_get(&uart2_queue);
		USART_SendChar(USART3, temp);
	}
}
