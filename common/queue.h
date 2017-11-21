/***********************************************************************************
 * �� �� ��   : queue.h
 * �� �� ��   : skawu
 * ��������   : 2017��11��16��
 * �ļ�����   : queue.cͷ�ļ�
 * ��Ȩ˵��   :
 * ��    ��   :
 * �޸���־   :
***********************************************************************************/

#ifndef _QUEUE_H__
#define _QUEUE_H__

#include "stm32f10x.h"

/* ���гش�С���˶���Ϊ�ο� */
#define BUFFER_SIZE     100

/* ���¸���ʵ��ʹ���޸ļ��ɣ�������ֱ���ں������޸� */
//typedef unsigned char u8;
//typedef unsigned short u16;
//typedef unsigned int u32;

/* ���нṹ�嶨�� */
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