#ifndef __SPLCEPROM_H__
#define __SPLCEPROM_H__
/*****************************************************************************/
#include "sPlc.h"
/*****************************************************************************/
uint8_t epromReadByte(uint16_t ReadAddr);//在AT24CXX指定地址读出一个数据
uint16_t epromReadHword(uint16_t ReadAddr);//在AT24CXX里面的指定地址开始读出16位数
uint32_t epromReadDword(int16_t ReadAddr);////在AT24CXX里面的指定地址开始读出32位数
void epromWriteByte(uint16_t WriteAddr, uint8_t *DataToWrite);//在AT24CXX指定地址写入一个数据
void epromWriteHword(uint16_t WriteAddr, uint16_t *DataToWrite);//在AT24CXX里面的指定地址开始写入16位数
void epromWriteDword(uint16_t WriteAddr, uint32_t *DataToWrite);//在AT24CXX里面的指定地址开始写入32位数
uint8_t epromTest(void);
#endif
