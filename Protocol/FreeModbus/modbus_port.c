#include "modbus_port.h"

#include "uart_api.h"

#define MODBUSRTU_BUFFER_SIZE


void ModbusRTUPort_UartInit(uint32_t baudrate)
{

}

void ModbusRTUPort_UartControl(uint8_t enable)
{
    if (enable)
        __HAL_UART_ENABLE(&huart2);
    else
        __HAL_UART_DISABLE(&huart2);
}

void ModbusRTUPort_TransmitByte(uint8_t data)
{
}

uint8_t ModbusRTUPort_ReceiveByte(void)
{

    return 0;
}

void ModbusRTUPort_RXControl(uint8_t enable)
{
    if (enable)
    {
    }
    else
    {
    }
}

void ModbusRTUPort_TXControl(uint8_t enable)
{
    if (enable)
    {
    }
    else
    {
    }
}

void ModbusRTUPort_TimerInit(uint32_t us)
{
}

void ModbusRTUPort_TimerControl(uint8_t enable)
{
    if (enable)
    {
    }
    else
    {
    }
}
