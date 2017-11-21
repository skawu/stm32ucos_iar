/***********************************************************************************
 * 文 件 名   : queue.h
 * 负 责 人   : skawu
 * 创建日期   : 2017年11月16日
 * 文件描述   : queue.c头文件
 * 版权说明   :
 * 其    他   :
 * 修改日志   :
***********************************************************************************/

#ifndef _QUEUE_H__
#define _QUEUE_H__

#include "stm32f10x.h"

/* 队列池大小，此定义为参考 */
#define BUFFER_SIZE     100

/* 以下根据实际使用修改即可，不允许直接在函数中修改 */
//typedef unsigned char u8;
//typedef unsigned short u16;
//typedef unsigned int u32;

/* 队列结构体定义 */
typedef struct queue_type
{
	u8 *p;
	u16 read_ptr;
	u16 write_ptr;
	u16 buf_len;
	u16 data_length;
} queue_t;


extern void queue_init(queue_t *q, u8 *buf_t, u16 len);
extern u8 queue_put(queue_t *q, u8 const value);
extern u8 queue_get(queue_t *q);
extern u16 queue_get_length(queue_t *q);
extern u8 queue_is_empty(queue_t *q);
extern u8 queue_is_full(queue_t *q);
extern u16 queue_get_space(queue_t *q);

#endif