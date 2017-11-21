#include "esp8266.h"
#include "uart.h"
#include "queue.h"

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



uart_t uart2 =
{
	.baud       = 115200,
	.stop       = USART_StopBits_1,
	.parity     = USART_Parity_No,
	.gpiorx     = GPIOA,
	.gpiotx     = GPIOA,
	.pin_rcc    = RCC_APB2Periph_GPIOA,
	.uart_rcc   = RCC_APB1Periph_USART2,
	.uartx      = USART2,
	.uart_queue = &uart2_queue,
	.pin_rx     = GPIO_Pin_3,
	.pin_tx     = GPIO_Pin_2,
};
uart_t uart3 =
{
	.baud       = 115200,
	.stop       = USART_StopBits_1,
	.parity     = USART_Parity_No,
	.gpiorx     = GPIOB,
	.gpiotx     = GPIOB,
	.pin_rcc    = RCC_APB2Periph_GPIOB,
	.uart_rcc   = RCC_APB1Periph_USART3,
	.uartx      = USART3,
	.uart_queue = &uart3_queue,
	.pin_rx     = GPIO_Pin_11,
	.pin_tx     = GPIO_Pin_10,

};

void init_esp8266(void)
{
	init_uart(&uart2);
	init_uart(&uart3);
}

