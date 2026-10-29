/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#ifndef __LIBCRC_H__
#define __LIBCRC_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
/* 按具体型号宏探测系列(工程编译选项定义); 若HAL未定义系列宏则在此补齐 */
#if defined(STM32F100xB)  || defined(STM32F100xE)  || defined(STM32F101x6) || \
    defined(STM32F101xB)  || defined(STM32F101xE)  || defined(STM32F101xG) || \
    defined(STM32F102x6)  || defined(STM32F102xB)  || defined(STM32F103x6) || \
    defined(STM32F103xB)  || defined(STM32F103xE)  || defined(STM32F103xG) || \
    defined(STM32F105xC)  || defined(STM32F107xC)
  #include "stm32f1xx_hal.h"
  #ifndef STM32F1xx
    #define STM32F1xx
  #endif
#elif defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
      defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || \
      defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) || \
      defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F469xx) || \
      defined(STM32F479xx) || defined(STM32F412Cx) || defined(STM32F412Zx) || defined(STM32F412Rx) || \
      defined(STM32F412Vx) || defined(STM32F413xx) || defined(STM32F423xx)
  #include "stm32f4xx_hal.h"
  #ifndef STM32F4xx
    #define STM32F4xx
  #endif
#endif
/*****************************************************************************/
uint16_t crc16Calculate(uint8_t *buf, uint32_t len);//CRC16 计算数组
uint16_t crc16CalculateAdd(uint8_t dat);//CRC16 计算连续字节
void crc16Clear(void);//清空旧CRC16结果
void crc16SetCrcOld(uint16_t old);
/*****************************************************************************/
uint32_t crc32Calculate(uint8_t *buf, uint32_t len);//CRC32 计算数组
uint32_t crc32CalculateAdd(uint8_t dat);//CRC32 计算连续字节
void crc32Clear(void);//清空旧CRC32结果
void crc32SetCrcOld(uint32_t old);
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif





