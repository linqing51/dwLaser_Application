#include "sPlc.h"
/*****************************************************************************/
#define BEEM_MODE_0													0x10//连续模式
#define BEEM_MODE_1													0x11//声光同步
#define BEEM_MODE_2													0x12//激光发射固定间隔
#define BEEM_MODE_3													0x13//异常报警
#define BEEM_FREQ_0													0xF2//正常频率
#define BEEM_FREQ_1													0xF1//变调
/*****************************************************************************/
void sPlcBeemLoop(void);//蜂鸣器轮询
void sPlcAimLoop(void);//瞄准光轮询
void setBeemFreq(uint32_t freq);//设置蜂鸣器频率和占空比
void setBeemDutyCycle(uint8_t dc);//设置蜂鸣器占空比
void setLedAimFreq(uint32_t freq);//设置LED灯和瞄准光闪烁频率
void setAimDutyCycle(uint8_t dc);//设置瞄准光亮度
void setRedLedDutyCycle(uint8_t dc);//设置R LED亮度
void setGreenLedDutyCycle(uint8_t dc);//设置G LED亮度
void setBlueLedDutyCycle(uint8_t dc);//设置B LED亮度
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





