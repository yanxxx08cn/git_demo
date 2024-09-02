#ifndef UART_API_H
#define UART_API_H

#include <stdint.h>
#include "usart.h"

#include "circular_queue.h"

typedef enum
{
    UART_DEV_SHELL = 0,
    UART_DEV_MODBUS = 1,
    UDI_NUM
} UART_DEVICE_INDEX;

#define UARTX_DMA_RXBUFFER_SIZE 128
#define UARTX_RXBUFFER_SIZE     256
#define UARTX_TXBUFFER_SIZE     256

extern uint8_t Uartx_DMA_RxBuffer[UDI_NUM][UARTX_DMA_RXBUFFER_SIZE];
extern uint8_t Uartx_RxBuffer[UDI_NUM][UARTX_RXBUFFER_SIZE];
extern uint8_t Uartx_TxBuffer[UDI_NUM][UARTX_TXBUFFER_SIZE];

void Uart_RxIdleCpltCallBack(UART_HandleTypeDef *huart);
void Uart_Dev_Init(UART_DEVICE_INDEX index);

extern CIRCULAR_QUEUE Uartx_RxCircularQueue[UDI_NUM];

#endif /* UART_API_H */
