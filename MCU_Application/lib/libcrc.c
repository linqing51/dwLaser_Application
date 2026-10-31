/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "libcrc.h"
static void crc32HwReset(void){
    __HAL_RCC_CRC_CLK_ENABLE();             /* CRC AHB 时钟 */
    __HAL_RCC_CRC_FORCE_RESET();            /* 强制复位外设, 清除REV_IN/POLYSIZE等残留配置(与sPlcCrc32Calc同语义) */
    __HAL_RCC_CRC_RELEASE_RESET();
    CRC->CR = 0x00000000U;                  /* 默认: 不反转, 多项式固定0x04C11DB7 */
}
static uint32_t crc32HwResult(void){ return CRC->DR; }   /* 直接返回原始值，无校正 */

uint32_t crc32Calculate(uint8_t *buf, uint32_t len){     /* 逐字节送入 */
    uint32_t i;
    for (i = 0; i < len; i++){ *(volatile uint8_t *)&CRC->DR = buf[i]; }
    return crc32HwResult();
}
uint32_t crc32CalculateAdd(uint8_t dat){
    *(volatile uint8_t *)&CRC->DR = dat;
    return crc32HwResult();
}
void crc32Clear(void){ crc32HwReset(); }
void crc32SetCrcOld(uint32_t old){ (void)old; }  /* F4 无 INIT 寄存器，失效 */






