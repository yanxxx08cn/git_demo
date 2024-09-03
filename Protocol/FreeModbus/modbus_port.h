#ifndef MODBUS_PORT_H
#define MODBUS_PORT_H

#include <stdint.h>

void ModbusRTUPort_UartInit(uint32_t baudrate);

void ModbusRTUPort_UartControl(uint8_t enable);

void ModbusRTUPort_TransmitByte(uint8_t data);

uint8_t ModbusRTUPort_ReceiveByte(void);

void ModbusRTUPort_RXControl(uint8_t enable);

void ModbusRTUPort_TXControl(uint8_t enable);

void ModbusRTUPort_TimerInit(uint32_t us);

void ModbusRTUPort_TimerControl(uint8_t enable);

#define MODBUSRTU_UART_IRQ_HANDLER TestFunc1
#define MODBUSRTU_TIMER_IRQ_HANDLER TestFunc2

#endif /* MODBUS_PORT_H */
