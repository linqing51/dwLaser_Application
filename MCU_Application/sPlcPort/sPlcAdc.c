#include "sPlc.h"
/*****************************************************************************/
__IO uint16_t adcDmaBuffer0[CONFIG_ADC_DMA_BUFFER_SIZE];//ADC DMA采集储存池
__IO uint16_t adcDmaBuffer1[CONFIG_ADC_DMA_BUFFER_SIZE];//ADC DMA采集储存池
__IO uint8_t adcBufferSelect;//ADC BUFFER选择指示
__IO uint8_t adcBufferDone;//ADC 采集完毕
/*****************************************************************************/
void sPlcAdcInit(void){//ADC模块初始化
	adcBufferSelect = 0;
	memset((uint8_t*)adcDmaBuffer0, 0x0, (CONFIG_ADC_DMA_BUFFER_SIZE * 2));
	memset((uint8_t*)adcDmaBuffer1, 0x0, (CONFIG_ADC_DMA_BUFFER_SIZE * 2));
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adcDmaBuffer0, CONFIG_ADC_DMA_BUFFER_SIZE); //启用DMA的ADC转换，AD_DMA 0~3 对应ADC 0~3，这里注意最后一个参数的大小
	printf("%s,%d,%s:start adc init......\n",__FILE__, __LINE__, __func__);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){    //ADC转换完成回调
    if(hadc->Instance == ADC1){
		adcBufferDone = 1;
	}
}
void sPlcAdcProcess(void){//循环采集ADC
	uint8_t i, j;
	uint32_t sum[CONFIG_SPLC_ADC_CHANNEL];
	while(adcBufferDone == 0);
	adcBufferDone = 0;
	if(adcBufferSelect == 0){	
		HAL_ADC_Stop_DMA(&hadc1);
		HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adcDmaBuffer1, CONFIG_ADC_DMA_BUFFER_SIZE);//再次启动ADC
		adcBufferSelect = 1;
		memset((uint8_t*)sum, 0x0, (CONFIG_SPLC_ADC_CHANNEL * 4));
		for(i = 0;i < CONFIG_SPLC_ADC_CHANNEL;i ++){
			for(j = 0;j < CONFIG_SPLC_ADC_AVERAGE_NUM ;j ++){
				sum[i] += adcDmaBuffer0[(j * CONFIG_SPLC_ADC_CHANNEL + i)];
			
			}
		}			
#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
		NVRAM0[SPREG_ADC_0] = (uint16_t)((float)sum[0] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_1] = (uint16_t)((float)sum[1] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_2] = (uint16_t)((float)sum[2] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_3] = (uint16_t)((float)sum[3] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_4] = (uint16_t)((float)sum[4] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_5] = (uint16_t)((float)sum[5] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);
#endif

#if defined(MODEL_PVGLS_10W_1940_A1)
		NVRAM0[SPREG_ADC_8] = (uint16_t)((float)sum[0] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);//IN0 BAT NTC
		NVRAM0[SPREG_ADC_7] = (uint16_t)((float)sum[1] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);//IN1 TEC CUR
		NVRAM0[SPREG_ADC_0] = (uint16_t)((float)sum[2] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);//IN2 1940 CUR
		NVRAM0[SPREG_ADC_1] = (uint16_t)((float)sum[3] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);//IN3 980 CUR
		NVRAM0[SPREG_ADC_11] = (uint16_t)((float)sum[4] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);//IN11 LASER NTC
		NVRAM0[SPREG_ADC_9] = (uint16_t)((float)sum[5] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);//IN12 FPD
		NVRAM0[SPREG_ADC_12] = (uint16_t)((float)sum[6] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);//IN13 HT NTC
		NVRAM0[SPREG_ADC_13] = (uint16_t)((float)sum[7] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);//CHIP TEMP
		NVRAM0[SPREG_ADC_14] = (uint16_t)((float)sum[8] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);//VREFINT
		NVRAM0[SPREG_ADC_15] = (uint16_t)((float)sum[9] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);//VBAT
#endif

	}
	else{//adcBufferSelect = 1
		HAL_ADC_Stop_DMA(&hadc1);
		HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adcDmaBuffer0, CONFIG_ADC_DMA_BUFFER_SIZE);//再次启动ADC
		adcBufferSelect = 0;
		memset(sum, 0x0, sizeof(sum));
		for(i = 0;i < CONFIG_SPLC_ADC_CHANNEL;i ++){
			for(j = 0;j < CONFIG_SPLC_ADC_AVERAGE_NUM ;j ++){
				sum[i] += adcDmaBuffer1[(j * CONFIG_SPLC_ADC_CHANNEL + i)];
			
			}
		}		
#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)	
		NVRAM0[SPREG_ADC_0] = (uint16_t)((float)sum[0] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_1] = (uint16_t)((float)sum[1] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_2] = (uint16_t)((float)sum[2] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_3] = (uint16_t)((float)sum[3] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_4] = (uint16_t)((float)sum[4] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_5] = (uint16_t)((float)sum[5] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);
#endif

#if defined(MODEL_PVGLS_10W_1940_A1)
		NVRAM0[SPREG_ADC_8] = (uint16_t)((float)sum[0] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);//IN0 BAT NTC
		NVRAM0[SPREG_ADC_7] = (uint16_t)((float)sum[1] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);//IN1 TEC CUR
		NVRAM0[SPREG_ADC_0] = (uint16_t)((float)sum[2] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);//IN2 1940 CUR
		NVRAM0[SPREG_ADC_1] = (uint16_t)((float)sum[3] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);//IN3 980 CUR
		NVRAM0[SPREG_ADC_11] = (uint16_t)((float)sum[4] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);//IN11 LASER NTC
		NVRAM0[SPREG_ADC_9] = (uint16_t)((float)sum[5] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);//IN12 FPD
		NVRAM0[SPREG_ADC_12] = (uint16_t)((float)sum[6] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);//IN13 HT NTC
		NVRAM0[SPREG_ADC_13] = (uint16_t)((float)sum[7] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);//CHIP TEMP
		NVRAM0[SPREG_ADC_14] = (uint16_t)((float)sum[8] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);//VREFINT
		NVRAM0[SPREG_ADC_15] = (uint16_t)((float)sum[9] / (float)CONFIG_SPLC_ADC_AVERAGE_NUM);//VBAT
#endif

	}
}




