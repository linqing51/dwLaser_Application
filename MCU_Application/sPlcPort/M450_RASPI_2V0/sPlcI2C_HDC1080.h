#ifndef __SPLCI2C_HDC1080_H__
#define __SPLCI2C_HDC1080_H__
/*****************************************************************************/
#include "sPlc.h"
#include "boardConfig.h"
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

uint8_t hdc1080_init(void);//初始化HDC1080
void hdc1080_read(int16_t *temp, int16_t *humi);//读取温湿度数据

#ifdef __cplusplus
}
#endif
#endif






