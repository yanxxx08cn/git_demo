#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stdint.h>

typedef struct __circular_queue CIRCULAR_QUEUE, *PCIRCULAR_QUEUE;

struct __circular_queue
{
    uint8_t *buffer; // 缓冲区
    uint16_t head;   // 头索引
    uint16_t tail;   // 尾索引
    uint16_t length; // 数据长度
    uint16_t size;   // 缓冲区大小
    uint32_t loss;   // 丢失字节
};

void CircularQueue_Init(CIRCULAR_QUEUE *p, uint8_t *buffer, uint16_t size);
uint8_t CircularQueue_IsFull(CIRCULAR_QUEUE *p);
uint8_t CircularQueue_IsEmpty(CIRCULAR_QUEUE *p);
uint16_t CircularQueue_GetLength(CIRCULAR_QUEUE *p);
uint8_t CircularQueue_SendByte(CIRCULAR_QUEUE *p, uint8_t data);
uint8_t CircularQueue_GiveByte(CIRCULAR_QUEUE *p, uint8_t *data);
uint16_t CircularQueue_SendBuffer(CIRCULAR_QUEUE *p, uint8_t *data, uint16_t size);
uint16_t CircularQueue_GiveBuffer(CIRCULAR_QUEUE *p, uint8_t *data, uint16_t size);

#endif /* CIRCULAR_QUEUE_H */
