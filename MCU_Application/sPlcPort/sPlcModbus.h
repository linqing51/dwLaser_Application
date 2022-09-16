#ifndef __MODBUS__H__
#define __MODBUS__H__
/*****************************************************************************/
#include "sPlc.h"
/*****************************************************************************/
#define CONFIG_MB_RX_BUFFER_SIZE								280//发送接收缓冲区
#define CONFIG_MB_RX_TIMEOUT										1000//接收通讯超时 1000mS
/*****************************************************************************/
extern uint16_t modbusTimerValue;
extern uint16_t modbusReceiveCounter;// Collected data number
extern uint8_t modbusReceiveBuffer[CONFIG_MB_RX_BUFFER_SIZE];
/*****************************************************************************/
extern void sPlcModbusInit(uint8_t modbusSlaveAddress, uint32_t bd);
extern void sPlcModbusPorcess(void);
extern void modbusPutChar(uint8_t c);
extern uint8_t modbusPutString(uint8_t *s, uint16_t Length);
extern void modbusGetChar(uint8_t Data);
extern void modbusUartInit(uint32_t bd);
#endif
