#include "shell_port.h"

#include <string.h>

#include "usart.h"
#include "uart_api.h"

#include "circular_queue.h"

#define LETTERSHELL_BUFFER_SIZE 256
Shell LetterShell;
uint8_t LetterShell_Buffer[LETTERSHELL_BUFFER_SIZE];

static signed short LetterShell_Read(char *data, unsigned short length)
{
    // return HAL_UART_Receive_DMA(&huart1, (uint8_t *)data, (uint16_t)length);
    return 0;
}

static signed short LetterShell_Write(char *data, unsigned short length)
{
    while (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TC) == RESET)
    {
    }
    return HAL_UART_Transmit_DMA(&huart1, (uint8_t *)data, (unsigned short)length);
}

void LetterShell_Init(void)
{
    memset(&LetterShell, 0, sizeof(Shell));

    Uart_Dev_Init(UART_DEV_SHELL);

    LetterShell.read = LetterShell_Read;
    LetterShell.write = LetterShell_Write;

    shellInit(&LetterShell, (char *)LetterShell_Buffer, LETTERSHELL_BUFFER_SIZE);
}

void LetterShell_Manage(void)
{
    uint16_t i;
    uint16_t length;
    uint8_t data;

    if (!CircularQueue_IsEmpty(&Uartx_RxCircularQueue[UART_DEV_SHELL]))
    {
        length = CircularQueue_GetLength(&Uartx_RxCircularQueue[UART_DEV_SHELL]);
        for (i = 0; i < length; i++)
        {
            CircularQueue_GiveByte(&Uartx_RxCircularQueue[UART_DEV_SHELL], &data);
            shellHandler(&LetterShell, data);
        }
    }
}

void func(int argc, char *argv[])
{
    printf("%d parameter(s)\r\n", argc);
    for (char i = 1; i < argc; i++)
    {
        printf("%s\r\n", argv[i]);
    }
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN), func, func, test);
