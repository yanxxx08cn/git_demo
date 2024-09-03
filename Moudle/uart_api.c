#include "uart_api.h"

#include <stdio.h>
#include <string.h>

uint8_t Uartx_DMA_RxBuffer[UDI_NUM][UARTX_DMA_RXBUFFER_SIZE];

uint8_t Uartx_RxBuffer[UDI_NUM][UARTX_RXBUFFER_SIZE];

uint8_t Uartx_TxBuffer[UDI_NUM][UARTX_TXBUFFER_SIZE];

CIRCULAR_QUEUE Uartx_RxCircularQueue[UDI_NUM];

void Uart_RxIdleCpltCallBack(UART_HandleTypeDef *huart)
{
    uint16_t count = 0;
    UART_DEVICE_INDEX index;

    if (huart == &huart1)
    {
        index = UART_DEV_SHELL;
    }

    HAL_DMA_Abort(&hdma_usart1_rx);
    count = UARTX_DMA_RXBUFFER_SIZE - __HAL_DMA_GET_COUNTER(huart->hdmarx);
    CircularQueue_SendBuffer(&Uartx_RxCircularQueue[index], &Uartx_DMA_RxBuffer[index][0], count);
    HAL_DMA_Start(&hdma_usart1_rx,
                  (uint32_t)&huart1.Instance->DR,
                  (uint32_t)&Uartx_DMA_RxBuffer[index][0],
                  UARTX_DMA_RXBUFFER_SIZE);
}

void Uart_Dev_Init(UART_DEVICE_INDEX index)
{
    memset(&Uartx_RxBuffer[index][0], 0, UARTX_RXBUFFER_SIZE);
    memset(&Uartx_TxBuffer[index][0], 0, UARTX_TXBUFFER_SIZE);
    CircularQueue_Init(&Uartx_RxCircularQueue[index], &Uartx_RxBuffer[index][0], UARTX_RXBUFFER_SIZE);
}
