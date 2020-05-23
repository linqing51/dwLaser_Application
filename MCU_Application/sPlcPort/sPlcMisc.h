#include "sPlc.h"
/*****************************************************************************/
void setRedLed(uint8_t st);
void setGreenLed(uint8_t st);
void setBlueLed(uint8_t st);
void setBeem(uint8_t st);
void setAim(uint8_t st);//设置瞄准光状态
void setAimBright(uint16_t br);//设置瞄准光亮度
void initWatchDog(void);
void enableWatchDog(void);
void disableWatchDog(void);
void feedWatchDog(void);
void mucReboot(void);
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





