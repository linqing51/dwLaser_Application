#ifndef __LIBCRC_H__
#define __LIBCRC_H__
/*****************************************************************************/
#include "stm32f4xx_hal.h"
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
#endif





