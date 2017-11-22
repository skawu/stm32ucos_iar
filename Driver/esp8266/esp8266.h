#ifndef __ESP8266_H__
#define __ESP8266_H__

#include "stm32f10x.h"
#include "ucos_ii.h"

#include "uart.h"
#include "queue.h"

extern uart_t uart2;
extern uart_t uart3;



void init_esp8266(void);

#endif