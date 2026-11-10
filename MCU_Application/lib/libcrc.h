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
/* CRC32 纯软件实现: 不依赖 CRC 外设 / RCC / 中断 / 互斥量, 可重入, 可多任务并发
 * 算法与 STM32 硬件 CRC 外设 bit 序逐位一致(CRC-32/MPEG-2:
 * poly 0x04C11DB7 / 初值 0xFFFFFFFF / MSB-first 输入 / 输出不反转 / 无末异或),
 * 与旧硬件路径算出的值完全相同(便于与历史数据对照; 本工程烧写固件后统一整片
 * 清除 EPROM, 不依赖存量校验值, 因此不涉及迁移)。
 * 用法: CRC 中间值由调用者自己持有(初值 CRC32_SW_INIT), 通过返回值传递;
 *       不同线程各自持有一份, 并发调用互不影响(本库无任何全局可变状态)。
 */
#define CRC32_SW_INIT       0xFFFFFFFFu

uint32_t crc32SwUpdate(uint32_t crc, const void *buf, uint32_t len);//字节流分块累加(可跨调用/跨任务)
uint32_t crc32SwBlock(const void *buf, uint32_t len);//字节流一次算完
uint32_t crc32SwUpdateWords(uint32_t crc, const void *words, uint32_t nWords);//32位字累加(等价硬件WORDS语义)
uint32_t crc32SwBlockWords(const void *words, uint32_t nWords);//32位字一次算完(入参需4字节对齐)
uint32_t crc32SwUpdateFill(uint32_t crc, uint8_t val, uint32_t count);//重复同一字节累加(镜像尾部补0xFF用)
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif





