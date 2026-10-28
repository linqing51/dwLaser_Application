#include "libcrc.h"
static void crc32HwReset(void){
    __HAL_RCC_CRC_CLK_ENABLE();             /* CRC AHB 时钟 */
    CRC->CR = CRC_CR_RESET;                 /* DR=0xFFFFFFFF */
    CRC->CR = (0x1U << 2U) | (0x1U << 5U);  /* REV_IN=BYTE, REV_OUT=1 */
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






