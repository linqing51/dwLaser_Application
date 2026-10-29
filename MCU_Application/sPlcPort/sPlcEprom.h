#ifndef __SPLCEPROM_H__
#define __SPLCEPROM_H__
/* 按具体型号宏探测系列(工程编译选项定义), F1/F4 通用, 与flash_if.h同模式 */
#if defined(STM32F100xB)  || defined(STM32F100xE)  || defined(STM32F101x6) || \
    defined(STM32F101xB)  || defined(STM32F101xE)  || defined(STM32F101xG) || \
    defined(STM32F102x6)  || defined(STM32F102xB)  || defined(STM32F103x6) || \
    defined(STM32F103xB)  || defined(STM32F103xE)  || defined(STM32F103xG) || \
    defined(STM32F105xC)  || defined(STM32F107xC)
  #include "stm32f1xx_hal.h"
#elif defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
      defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || \
      defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) || \
      defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F469xx) || \
      defined(STM32F479xx) || defined(STM32F412Cx) || defined(STM32F412Zx) || defined(STM32F412Rx) || \
      defined(STM32F412Vx) || defined(STM32F413xx) || defined(STM32F423xx)
  #include "stm32f4xx_hal.h"
#else
  #error "sPlcEprom.h: only supports STM32F1xx / STM32F4xx!"
#endif
#include "stdbool.h"
#include "libcpu.h"

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
typedef enum {
	CLEAR_EPROM_ALL 														= 0x01,
	CLEAR_EPROM_NVRAM														= 0x02,
	CLEAR_EPROM_FDRAM														= 0x03,
	CLEAR_EPROM_MCU_FIRMWARE_CRC								= 0x04,
	CLEAR_EPROM_LCD_FIRMWARE_CRC								= 0x05,
	CLEAR_EPROM_DEVICE_CONFIG										= 0x06,
	CLEAR_EPROM_LOG_INFO												= 0x07,
	CLEAR_EPROM_BKRAM														= 0x08,
	CLEAR_EPROM_TREATMENT											= 0x09//清除病历/治疗记录区(含CRC)
}clarmEpromCmd_t;
/*****************************************************************************/
void epromInit(void);
HAL_StatusTypeDef epromReadStatusReg(uint8_t *status);
HAL_StatusTypeDef epromWriteStatusReg(uint8_t *status);
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
uint8_t sPlcEpromTest(void);//EPROM 读写自测试

#ifdef __cplusplus
}
#endif

#endif




