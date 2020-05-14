#ifndef __SPLCCHIPADC_H__
#define __SPLCCHIPADC_H__
/*****************************************************************************/
#include "sPlcPort.h"
/*****************************************************************************/
typedef struct{//ADC�˲���
	uint16_t dat[CONFIG_SPLC_ADC_FILTER_TAP];
	uint16_t out;
	uint8_t wIndex;//д��ָ��
}adcTempDat_t;
/*****************************************************************************/
void initChipAdc(void);
void chipAdcProcess(void);
void refreshAdcData(adcTempDat_t *s , uint16_t dat);
#endif