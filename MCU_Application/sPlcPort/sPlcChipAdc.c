#include "sPlcChipAdc.h"
/*****************************************************************************/
static adcTempDat_t adcTempDat[CONFIG_SPLC_ADC_CHANNLE];
static uint8_t adcSelect;//ADC通道选择
static void initAdcData(adcTempDat_t *s);
/*****************************************************************************/
static void initAdcData(adcTempDat_t *s){//初始化ADC滤波器
    uint8_t i;
	for(i = 0;i < CONFIG_SPLC_ADC_FILTER_TAP; i++){
		s->dat[i] = 0x0;
	}
	s->out = 0;
	s->wIndex = 0;
}
void initChipAdc(void){//ADC模块初始化
#if CONFIG_SPLC_USING_ADC == 1
	uint8_t i;
	adcSelect = 0;
	for(i = 0;i < CONFIG_SPLC_ADC_CHANNLE;i ++){
		initAdcData(&adcTempDat[i]);
	}
#endif
}
void chipAdcProcess(void){//循环采集ADC
	uint16_t result = 0;
	uint8_t adcOverTime = 0;
	
	//result = (ADC0 & 0x0FFF);
	refreshAdcData(&adcTempDat[adcSelect], result);
	//NVRAM0[SPREG_ADC_0 + adcSelect] = adcTempDat[adcSelect].out;

}
void refreshAdcData(adcTempDat_t *s , uint16_t dat){//更新ADC采集值 
	uint8_t i;
	uint16_t temp;
	uint32_t sum;
	s->dat[s->wIndex] = dat;
	s->wIndex ++;
	if(s->wIndex >= CONFIG_SPLC_ADC_FILTER_TAP){
		s->wIndex = 0;
	}
	//计算总和
	sum = 0;
	for(i = 0;i < CONFIG_SPLC_ADC_FILTER_TAP;i ++){
		sum += s->dat[i];
	}
	//去掉一个最大值和一个最小值
	temp = (uint16_t)(sum / (uint32_t)CONFIG_SPLC_ADC_FILTER_TAP);
	s->out = temp;
}
