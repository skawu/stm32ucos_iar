#ifndef __UART_H__
#define __UART_H__

#include "stm32f10x.h"
#include "queue.h"

#define DEBUG_PRINTF 1

extern void UART_config(USART_TypeDef *USARTx);
extern void USART_SendChar(USART_TypeDef *USARTx, u8 c);
extern void USART_SendStr(USART_TypeDef *USARTx, u8 *str);

#endif
