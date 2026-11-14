/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
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
/* 开机设备ID(RDID)核对结果: 由epromVerifyDeviceId在epromInit时解码并记录 */
typedef enum {
	EPROM_ID_OK = 0,												//设备ID与配置容量一致
	EPROM_ID_ERR_READ,											//RDID读取失败(SPI通信异常)
	EPROM_ID_ERR_UNKNOWN,										//厂商码不识别或密度码不支持
	EPROM_ID_ERR_MISMATCH										//解码容量与CONFIG_EPROM_SIZE不一致
}epromIdStatus_t;
/*****************************************************************************/
void epromInit(void);
uint32_t epromDecodeCapacity(const uint8_t id[4]);//按RDID密度码解码容量(字节), 不识别返回0
epromIdStatus_t epromVerifyDeviceId(void);//读取并核对设备ID, 记录/返回核对结果
epromIdStatus_t epromGetIdStatus(void);//获取最近一次开机设备ID核对结果
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




