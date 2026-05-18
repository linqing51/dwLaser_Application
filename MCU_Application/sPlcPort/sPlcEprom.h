#ifndef __SPLCEPROM_H__
#define __SPLCEPROM_H__
#include "stm32f4xx_hal.h"
#include "stdbool.h"
#include "libcpu.h"
#include "sPlcConfig.h"
#include "boardConfig.h"
#include "AppConfig.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;
extern CRC_HandleTypeDef hcrc;
extern RNG_HandleTypeDef hrng;
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
void epromInit(void);
HAL_StatusTypeDef epromReadStatusReg(uint8_t *status);
HAL_StatusTypeDef epromReadDeviceId(uint8_t *idBuf);
HAL_StatusTypeDef epromWriteEnable(bool en);
HAL_StatusTypeDef epromReadByte(uint32_t addr, uint8_t *dat);
HAL_StatusTypeDef epromWriteByte(uint32_t addr, uint8_t *dat);
HAL_StatusTypeDef epromReadHword(uint32_t addr, uint16_t *dat);
HAL_StatusTypeDef epromWriteHword(uint32_t addr, uint16_t *dat);
HAL_StatusTypeDef epromReadDword(uint32_t addr, uint32_t *dat);
HAL_StatusTypeDef epromWriteDword(uint32_t addr, uint32_t *dat);
HAL_StatusTypeDef epromRead(uint32_t addr, uint8_t *buf, uint16_t len);
HAL_StatusTypeDef epromWrite(uint32_t addr, uint8_t *buf, uint16_t len);
/*****************************************************************************/
uint8_t checkBlank(uint32_t adr, uint32_t size);//MCU Flash 查空
void clearEprom(clarmEpromCmd_t cmd);//清除EPROM内容
void listEpromTable(void);
uint8_t sPlcEpromTest(void);//EPROM 读写自测试

#ifdef __cplusplus
}
#endif

#endif




