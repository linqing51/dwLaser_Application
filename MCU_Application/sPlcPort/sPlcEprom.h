#ifndef __SPLCEPROM_H__
#define __SPLCEPROM_H__
#include "stm32f4xx_hal.h"
#include "stdbool.h"
#include "sPlcConfig.h"
#include "boardConfig.h"
#include "AppConfig.h"
/*****************************************************************************/
typedef enum {
	CLEAR_EPROM_ALL 														= 0x01,
	CLEAR_EPROM_NVRAM														= 0x02,
	CLEAR_EPROM_FDRAM														= 0x03,
	CLEAR_EPROM_MCU_FIRMWARE_CRC								= 0x04,
	CLEAR_EPROM_LCD_FIRMWARE_CRC								= 0x05,
	CLEAR_EPROM_DEVICE_CONFIG										= 0x06,
	CLEAR_EPROM_LOG_INFO												= 0x07
}clarmEpromCmd_t;
/*****************************************************************************/
HAL_StatusTypeDef epromReadByte(uint16_t ReadAddr, uint8_t *rdat);//在AT24CXX指定地址读出一个数据
HAL_StatusTypeDef epromReadHword(uint16_t ReadAddr, uint16_t *rdat);//在AT24CXX里面的指定地址开始读出16位数 
HAL_StatusTypeDef epromReadDword(uint16_t ReadAddr, uint32_t *rdat);////在AT24CXX里面的指定地址开始读出32位数
HAL_StatusTypeDef epromWriteByte(uint16_t WriteAddr, uint8_t *wdat);//在AT24CXX指定地址写入8位数据
HAL_StatusTypeDef epromWriteHword(uint16_t WriteAddr, uint16_t *wdat);//在AT24CXX里面的指定地址开始写入16位数
HAL_StatusTypeDef epromWriteDword(uint16_t WriteAddr, uint32_t *wdat);//在AT24CXX里面的指定地址开始写入32位数
HAL_StatusTypeDef epromRead(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead);
HAL_StatusTypeDef epromWrite(uint16_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite);
uint8_t checkBlank(uint32_t adr, uint32_t size);//MCU Flash 查空
void clearEprom(clarmEpromCmd_t cmd);//清除EPROM内容
void listEpromTable(void);
void I2C_ReleaseBus(I2C_TypeDef* I2Cx, GPIO_TypeDef* SDA_GPIO, uint16_t SDA_Pin, GPIO_TypeDef* SCL_GPIO, uint16_t SCL_Pin);
bool I2C_WaitFlag(I2C_TypeDef* I2Cx, uint32_t flag, uint32_t timeout);
#endif




