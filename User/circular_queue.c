#include "circular_queue.h"

#include <stdio.h>
#include <string.h>

void CircularQueue_Init(CIRCULAR_QUEUE *p, uint8_t *buffer, uint16_t size)
{
    if (p == NULL ||
        size == 0)
        return;

    memset(p, 0, sizeof(CIRCULAR_QUEUE));
    p->buffer = buffer;
    p->size = size;
}

uint8_t CircularQueue_IsFull(CIRCULAR_QUEUE *p)
{
    if (p->length == p->size)
        return 1;
    else
        return 0;
}

uint8_t CircularQueue_IsEmpty(CIRCULAR_QUEUE *p)
{
    if (p->length == 0)
        return 1;
    else
        return 0;
}

uint16_t CircularQueue_GetLength(CIRCULAR_QUEUE *p)
{
    return p->length;
}

uint8_t CircularQueue_SendByte(CIRCULAR_QUEUE *p, uint8_t data)
{
    if (CircularQueue_IsFull(p))
        return 0;

    p->buffer[p->tail] = data;
    p->tail = (p->tail + 1) % p->size;
    p->length++;

    return 1;
}

uint8_t CircularQueue_GiveByte(CIRCULAR_QUEUE *p, uint8_t *data)
{
    if (CircularQueue_IsEmpty(p))
        return 0;

    *data = p->buffer[p->head];
    p->head = (p->head + 1) % p->size;
    p->length--;

    return 1;
}

uint16_t CircularQueue_SendBuffer(CIRCULAR_QUEUE *p, uint8_t *data, uint16_t size)
{
    uint8_t td;
    uint16_t count = 0, i;

    for (i = 0; i < size; i++)
    {
        td = CircularQueue_SendByte(p, *data++);
        if (td == 0)
            return count;
        else
            count += td;
    }
    return count;
}

uint16_t CircularQueue_GiveBuffer(CIRCULAR_QUEUE *p, uint8_t *data, uint16_t size)
{
    uint8_t td;
    uint16_t count = 0, i;

    for (i = 0; i < size; i++)
    {
        td = CircularQueue_GiveByte(p, data++);
        if (td == 0)
            return count;
        else
            count += td;
    }
    return count;
}
