#ifndef __SPLCEPROM_H__
#define __SPLCEPROM_H__
/*****************************************************************************/
#include "sPlc.h"
/*****************************************************************************/
HAL_StatusTypeDef epromReadByte(uint16_t ReadAddr, uint8_t *rdat);//在AT24CXX指定地址读出一个数据
HAL_StatusTypeDef epromReadHword(uint16_t ReadAddr, uint16_t *rdat);//在AT24CXX里面的指定地址开始读出16位数
HAL_StatusTypeDef epromReadDword(int16_t ReadAddr, uint32_t *rdat);////在AT24CXX里面的指定地址开始读出32位数
HAL_StatusTypeDef epromWriteByte(uint16_t WriteAddr, uint8_t DataToWrite);//在AT24CXX指定地址写入8位数据
HAL_StatusTypeDef epromWriteHword(uint16_t WriteAddr, uint16_t DataToWrite);//在AT24CXX里面的指定地址开始写入16位数
HAL_StatusTypeDef epromWriteDword(uint16_t WriteAddr, uint32_t DataToWrite);//在AT24CXX里面的指定地址开始写入32位数
HAL_StatusTypeDef epromRead(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead);
HAL_StatusTypeDef epromWrite(uint16_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite);
uint8_t epromTest(void);
#endif
