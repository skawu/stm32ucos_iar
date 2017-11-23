#ifndef __ESP8266_H__
#define __ESP8266_H__

#include "stm32f10x.h"
#include "ucos_ii.h"

#include "uart.h"
#include "queue.h"

extern queue_t uart2_queue;
extern queue_t uart3_queue;

void init_esp8266(void);
void esp8266_handle(void);

#endif