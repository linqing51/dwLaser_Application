#include "sPlcAdc.h"
/*****************************************************************************/
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
/*****************************************************************************/
__IO uint16_t adcDmaBuffer0[CONFIG_ADC_DMA_BUFFER_SIZE];//ADC DMA采集储存池
__IO uint16_t adcDmaBuffer1[CONFIG_ADC_DMA_BUFFER_SIZE];//ADC DMA采集储存池
__IO uint8_t adcBufferSelect;//ADC BUFFER选择指示
__IO uint8_t adcBufferDone;//ADC 采集完毕
/*****************************************************************************/
void initChipAdc(void){//ADC模块初始化
	adcBufferSelect = 0;
	memset((uint8_t*)adcDmaBuffer0, 0x0, (CONFIG_ADC_DMA_BUFFER_SIZE * 2));
	memset((uint8_t*)adcDmaBuffer1, 0x0, (CONFIG_ADC_DMA_BUFFER_SIZE * 2));
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adcDmaBuffer0, CONFIG_ADC_DMA_BUFFER_SIZE); //启用DMA的ADC转换，AD_DMA 0~3 对应ADC 0~3，这里注意最后一个参数的大小
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){    //ADC转换完成回调
    if(hadc->Instance == ADC1){
		adcBufferDone = 1;
	}
	
}
void chipAdcProcess(void){//循环采集ADC
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
		NVRAM0[SPREG_ADC_0] = (uint16_t)((fp32_t)sum[0] / (fp32_t)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_1] = (uint16_t)((fp32_t)sum[1] / (fp32_t)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_2] = (uint16_t)((fp32_t)sum[2] / (fp32_t)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_3] = (uint16_t)((fp32_t)sum[3] / (fp32_t)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_4] = (uint16_t)((fp32_t)sum[4] / (fp32_t)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_5] = (uint16_t)((fp32_t)sum[5] / (fp32_t)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_6] = (uint16_t)((fp32_t)sum[6] / (fp32_t)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_7] = (uint16_t)((fp32_t)sum[7] / (fp32_t)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_8] = (uint16_t)((fp32_t)sum[8] / (fp32_t)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_9] = (uint16_t)((fp32_t)sum[9] / (fp32_t)CONFIG_SPLC_ADC_AVERAGE_NUM);
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
		NVRAM0[SPREG_ADC_0] = (uint16_t)((fp32_t)sum[0] / (fp32_t)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_1] = (uint16_t)((fp32_t)sum[1] / (fp32_t)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_2] = (uint16_t)((fp32_t)sum[2] / (fp32_t)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_3] = (uint16_t)((fp32_t)sum[3] / (fp32_t)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_4] = (uint16_t)((fp32_t)sum[4] / (fp32_t)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_5] = (uint16_t)((fp32_t)sum[5] / (fp32_t)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_6] = (uint16_t)((fp32_t)sum[6] / (fp32_t)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_7] = (uint16_t)((fp32_t)sum[7] / (fp32_t)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_8] = (uint16_t)((fp32_t)sum[8] / (fp32_t)CONFIG_SPLC_ADC_AVERAGE_NUM);
		NVRAM0[SPREG_ADC_9] = (uint16_t)((fp32_t)sum[9] / (fp32_t)CONFIG_SPLC_ADC_AVERAGE_NUM);
	}
}




