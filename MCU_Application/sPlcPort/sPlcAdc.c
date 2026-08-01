#include "sPlc.h"
/*****************************************************************************/
__IO static uint16_t adcDmaBuffer0[CONFIG_ADC_DMA_BUFFER_SIZE];//ADC DMA采集储存池
__IO static uint16_t adcDmaBuffer1[CONFIG_ADC_DMA_BUFFER_SIZE];//ADC DMA采集储存池
static float adcFilterBuf[CONFIG_ADC_CHANNEL] = {0.0f};  // ADC1浮点滤波缓存
static uint8_t adcBufferSelect;//ADC BUFFER选择指示
static uint8_t adcBufferDone;//ADC 采集完毕
/*****************************************************************************/
void sPlcAdcInit(void){//ADC模块初始化
	uint8_t i;
	adcBufferSelect = 0;
	adcBufferDone = 0;
	memset((uint8_t*)adcDmaBuffer0, 0x0, (CONFIG_ADC_DMA_BUFFER_SIZE * 2));
	memset((uint8_t*)adcDmaBuffer1, 0x0, (CONFIG_ADC_DMA_BUFFER_SIZE * 2));
	for (i = 0; i < CONFIG_ADC_CHANNEL; i++){
    adcFilterBuf[i] = 0.0f;
	}
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adcDmaBuffer0, CONFIG_ADC_DMA_BUFFER_SIZE); //启用DMA的ADC转换，AD_DMA 0~3 对应ADC 0~3，这里注意最后一个参数的大小
#if (CONFIG_DEBUB_ADC == 1)
	printf("%s,%d,%s:start adc init......\n",__FILE__, __LINE__, __func__);
#endif
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){    //ADC转换完成回调
  if(hadc->Instance == ADC1){
		adcBufferDone = 1;
	}
}

void sPlcAdcProcessBuffer(void){//循环采集ADC
	uint8_t i;
	float adcRaw;
	while(adcBufferDone == 0);
	adcBufferDone = 0;
	if(adcBufferAselect == 0){	
		HAL_ADC_Stop_DMA(&hadc1);
		HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adcDmaBuffer1, CONFIG_ADC1_DMA_BUFFER_SIZE);//再次启动ADC
		adcBufferSelect = 1;
		for(i = 0;i < CONFIG_ADC1_CHANNEL;i ++){
			adcRaw = (float)adcDmaBuffer0[i];
			// 标准一阶滤波公式：Y = (1-α)*Y_last + α*X_new
			adc1FilterBuf[i] = (1.0f - ADC_FILTER_ALPHA) * adcFilterBuf[i] + ADC_FILTER_ALPHA * adcRaw;
		}			
		NVRAM0[SPREG_ADC_52] = (uint16_t)((float)adc1FilterBuf[0] / (float)CONFIG_ADC_AVERAGE_NUM);//IN6 VIN VOLTAGE
		NVRAM0[SPREG_ADC_40] = (uint16_t)((float)adc1FilterBuf[1] / (float)CONFIG_ADC_AVERAGE_NUM);//IN7 LASER_NTC
		NVRAM0[SPREG_ADC_32] = (uint16_t)((float)adc1FilterBuf[2] / (float)CONFIG_ADC_AVERAGE_NUM);//IN8 HT0_NTC
		NVRAM0[SPREG_ADC_33] = (uint16_t)((float)adc1FilterBuf[3] / (float)CONFIG_ADC_AVERAGE_NUM);//IN9 HT1_NTC
		NVRAM0[SPREG_ADC_51] = (uint16_t)((float)adc1FilterBuf[4] / (float)CONFIG_ADC_AVERAGE_NUM);//IN10 PWR_CUR		
		NVRAM0[SPREG_ADC_1] = (uint16_t)((float)adc1FilterBuf[5] / (float)CONFIG_ADC_AVERAGE_NUM);//IN11 CH1_CUR
		NVRAM0[SPREG_ADC_0] = (uint16_t)((float)adc1FilterBuf[6] / (float)CONFIG_ADC_AVERAGE_NUM);//IN12 CH0_CUR		
		NVRAM0[SPREG_ADC_16] = (uint16_t)((float)adc1FilterBuf[7] / (float)CONFIG_ADC_AVERAGE_NUM);//IN13 TEC_CUR
		NVRAM0[SPREG_ADC_55] = (uint16_t)((float)adc1FilterBuf[8] / (float)CONFIG_ADC_AVERAGE_NUM);//IN14 LPD		
		NVRAM0[SPREG_ADC_54] = (uint16_t)((float)adc1FilterBuf[9] / (float)CONFIG_ADC_AVERAGE_NUM);//IN15 FPD	
		NVRAM0[SPREG_ADC_58] = (uint16_t)((float)adc1FilterBuf[10] / (float)CONFIG_ADC_AVERAGE_NUM);//CHIP TEMP
		NVRAM0[SPREG_ADC_59] = (uint16_t)((float)adc1FilterBuf[11] / (float)CONFIG_ADC_AVERAGE_NUM);//VREFINT
		NVRAM0[SPREG_ADC_60] = (uint16_t)((float)adc1FilterBuf[12] / (float)CONFIG_ADC_AVERAGE_NUM);//VBAT
	}
	else{//adcBufferSelect = 1
		HAL_ADC_Stop_DMA(&hadc1);
		HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adcDmaBufferA0, CONFIG_ADC1_DMA_BUFFER_SIZE);//再次启动ADC
		adcBufferSelect = 0;
		for(i = 0;i < CONFIG_ADC_CHANNEL;i ++){
			adcRaw = (float)adcDmaBuffer1[i]; 
			adcFilterBuf[i] = (1.0f - ADC_FILTER_ALPHA) * adcFilterBuf[i] + ADC_FILTER_ALPHA * adcRaw;
		}
		NVRAM0[SPREG_ADC_52] = (uint16_t)((float)adc1FilterBuf[0] / (float)CONFIG_ADC_AVERAGE_NUM);//IN6 VIN VOLTAGE
		NVRAM0[SPREG_ADC_40] = (uint16_t)((float)adc1FilterBuf[1] / (float)CONFIG_ADC_AVERAGE_NUM);//IN7 LASER_NTC
		NVRAM0[SPREG_ADC_32] = (uint16_t)((float)adc1FilterBuf[2] / (float)CONFIG_ADC_AVERAGE_NUM);//IN8 HT1_NTC
		NVRAM0[SPREG_ADC_33] = (uint16_t)((float)adc1FilterBuf[3] / (float)CONFIG_ADC_AVERAGE_NUM);//IN9 HT2_NTC
		NVRAM0[SPREG_ADC_51] = (uint16_t)((float)adc1FilterBuf[4] / (float)CONFIG_ADC_AVERAGE_NUM);//IN10 PWR_CUR		
		NVRAM0[SPREG_ADC_1] = (uint16_t)((float)adc1FilterBuf[5] / (float)CONFIG_ADC_AVERAGE_NUM);//IN11 CH1_CUR
		NVRAM0[SPREG_ADC_0] = (uint16_t)((float)adc1FilterBuf[6] / (float)CONFIG_ADC_AVERAGE_NUM);//IN12 CH0_CUR		
		NVRAM0[SPREG_ADC_16] = (uint16_t)((float)adc1FilterBuf[7] / (float)CONFIG_ADC_AVERAGE_NUM);//IN13 TEC_CUR
		NVRAM0[SPREG_ADC_55] = (uint16_t)((float)adc1FilterBuf[8] / (float)CONFIG_ADC_AVERAGE_NUM);//IN14 LPD		
		NVRAM0[SPREG_ADC_54] = (uint16_t)((float)adc1FilterBuf[9] / (float)CONFIG_ADC_AVERAGE_NUM);//IN15 FPD	
		NVRAM0[SPREG_ADC_58] = (uint16_t)((float)adc1FilterBuf[10] / (float)CONFIG_ADC_AVERAGE_NUM);//CHIP TEMP
		NVRAM0[SPREG_ADC_59] = (uint16_t)((float)adc1FilterBuf[11] / (float)CONFIG_ADC_AVERAGE_NUM);//VREFINT
		NVRAM0[SPREG_ADC_60] = (uint16_t)((float)adc1FilterBuf[12] / (float)CONFIG_ADC_AVERAGE_NUM);//VBAT
	}
}






