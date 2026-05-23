#include "sPlc.h"
#include "boardConfig.h"
#include "AppConfig.h"
/*****************************************************************************/
__IO static uint16_t adcDmaBufferA0[CONFIG_ADC1_DMA_BUFFER_SIZE];//ADC DMA采集储存池
__IO static uint16_t adcDmaBufferA1[CONFIG_ADC1_DMA_BUFFER_SIZE];//ADC DMA采集储存池
__IO static float adc1FilterBuf[CONFIG_ADC1_CHANNEL] = {0.0f};  // ADC1浮点滤波缓存
__IO static uint8_t adcBufferAselect;//ADC BUFFER选择指示
__IO static uint8_t adcBufferAdone;//ADC 采集完毕

#if(LYPE_MCU_1V0_20260106)
__IO static uint16_t adcDmaBufferB0[CONFIG_ADC3_DMA_BUFFER_SIZE];//ADC DMA采集储存池
__IO static uint16_t adcDmaBufferB1[CONFIG_ADC3_DMA_BUFFER_SIZE];//ADC DMA采集储存池
__IO static float adc3FilterBuf[CONFIG_ADC3_CHANNEL] = {0.0f};  // ADC3浮点滤波缓存
__IO static uint8_t adcBufferBselect;//ADC BUFFER选择指示
__IO static uint8_t adcBufferBdone;//ADC 采集完毕
#endif
/*****************************************************************************/
void sPlcAdcInit(void){//ADC模块初始化
	uint8_t i;
	adcBufferAselect = 0;
	adcBufferAdone = 0;
#if(LYPE_MCU_1V0_20260106)
	adcBufferBselect = 0;
	adcBufferBdone = 0;
#endif
	memset((uint8_t*)adcDmaBufferA0, 0x0, (CONFIG_ADC1_DMA_BUFFER_SIZE * 2));
	memset((uint8_t*)adcDmaBufferA1, 0x0, (CONFIG_ADC1_DMA_BUFFER_SIZE * 2));
	for (i = 0; i < CONFIG_ADC1_CHANNEL; i++){
    adc1FilterBuf[i] = 0.0f;
	}
#if(LYPE_MCU_1V0_20260106)	
	memset((uint8_t*)adcDmaBufferB0, 0x0, (CONFIG_ADC3_DMA_BUFFER_SIZE * 2));
	memset((uint8_t*)adcDmaBufferB1, 0x0, (CONFIG_ADC3_DMA_BUFFER_SIZE * 2));
	for (i = 0; i < CONFIG_ADC1_CHANNEL; i++){
    adc1FilterBuf[i] = 0.0f;
	}
#endif
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adcDmaBufferA0, CONFIG_ADC1_DMA_BUFFER_SIZE); //启用DMA的ADC转换，AD_DMA 0~3 对应ADC 0~3，这里注意最后一个参数的大小
#if(LYPE_MCU_1V0_20260106)
	HAL_ADC_Start_DMA(&hadc3, (uint32_t*)&adcDmaBufferA0, CONFIG_ADC3_DMA_BUFFER_SIZE); //启用DMA的ADC转换，AD_DMA 0~3 对应ADC 0~3，这里注意最后一个参数的大小
#endif
#if (CONFIG_DEBUB_ADC == 1)
	printf("%s,%d,%s:start adc init......\n",__FILE__, __LINE__, __func__);
#endif
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){    //ADC转换完成回调
  if(hadc->Instance == ADC1){
		adcBufferAdone = 1;
	}
#if(LYPE_MCU_1V0_20260106)	
	if(hadc->Instance == ADC3){
		adcBufferBdone = 1;
	}
#endif
}

void sPlcAdcProcessBufferA(void){//循环采集ADC
	uint8_t i;
	float adcRaw;
	while(adcBufferAdone == 0);
	adcBufferAdone = 0;
	if(adcBufferAselect == 0){	
		HAL_ADC_Stop_DMA(&hadc1);
		HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adcDmaBufferA1, CONFIG_ADC1_DMA_BUFFER_SIZE);//再次启动ADC
		adcBufferAselect = 1;
		// ===================== FPU单精度浮点一阶滤波 =====================
		for(i = 0;i < CONFIG_ADC1_CHANNEL;i ++){
			adcRaw = (float)adcDmaBufferA0[i];
			// 标准一阶滤波公式：Y = (1-α)*Y_last + α*X_new
			adc1FilterBuf[i] = (1.0f - ADC_FILTER_ALPHA) * adc1FilterBuf[i] + ADC_FILTER_ALPHA * adcRaw;
		}			
#if defined(LDR2P1_G5_A1_20250731_DUAL) || defined(LDR2P1_G5_A1_20250910_DUAL) || defined(LDR2P1_G5_A1_20250731_TRIP) || defined(LDR2P1_G5_A1_20250910_TRIP)
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
#endif	

#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
		NVRAM0[SPREG_ADC_12] = (uint16_t)((float)adc1FilterBuf[0] / (float)CONFIG_ADC_AVERAGE_NUM);//HNTC
		NVRAM0[SPREG_ADC_11] = (uint16_t)((float)adc1FilterBuf[1] / (float)CONFIG_ADC_AVERAGE_NUM);//LNTC
		NVRAM0[SPREG_ADC_10] = (uint16_t)((float)adc1FilterBuf[2] / (float)CONFIG_ADC_AVERAGE_NUM);//LPD
		NVRAM0[SPREG_ADC_9] = (uint16_t)((float)adc1FilterBuf[3] / (float)CONFIG_ADC_AVERAGE_NUM);//FPD
		NVRAM0[SPREG_ADC_13] = (uint16_t)((float)adc1FilterBuf[4] / (float)CONFIG_ADC_AVERAGE_NUM);//TMCU
		NVRAM0[SPREG_ADC_14] = (uint16_t)((float)adc1FilterBuf[5] / (float)CONFIG_ADC_AVERAGE_NUM);//VREFINT
		NVRAM0[SPREG_ADC_15] = (uint16_t)((float)adc1FilterBuf[6] / (float)CONFIG_ADC_AVERAGE_NUM);//VBAT
#endif

#if defined(MODEL_PVGLS_10W_1940_A1)
		NVRAM0[SPREG_ADC_8] = (uint16_t)((float)adc1FilterBuf[0] / (float)CONFIG_ADC_AVERAGE_NUM);//IN0 MBAT NTC
		NVRAM0[SPREG_ADC_7] = (uint16_t)((float)adc1FilterBuf[1] / (float)CONFIG_ADC_AVERAGE_NUM);//IN1 CH4 CUR ->TEC
		NVRAM0[SPREG_ADC_0] = (uint16_t)((float)adc1FilterBuf[2] / (float)CONFIG_ADC_AVERAGE_NUM);//IN2 CH0 CUR ->1940
		NVRAM0[SPREG_ADC_1] = (uint16_t)((float)adc1FilterBuf[3] / (float)CONFIG_ADC_AVERAGE_NUM);//IN3 CH1 CUR ->980
		NVRAM0[SPREG_ADC_9] = (uint16_t)((float)adc1FilterBuf[4] / (float)CONFIG_ADC_AVERAGE_NUM);//IN11 FPD
		NVRAM0[SPREG_ADC_11] = (uint16_t)((float)adc1FilterBuf[5] / (float)CONFIG_ADC_AVERAGE_NUM);//IN12 LASER NTC
		NVRAM0[SPREG_ADC_12] = (uint16_t)((float)adc1FilterBuf[6] / (float)CONFIG_ADC_AVERAGE_NUM);//IN13 HT NTC
		NVRAM0[SPREG_ADC_13] = (uint16_t)((float)adc1FilterBuf[7] / (float)CONFIG_ADC_AVERAGE_NUM);//CHIP TEMP
		NVRAM0[SPREG_ADC_14] = (uint16_t)((float)adc1FilterBuf[8] / (float)CONFIG_ADC_AVERAGE_NUM);//VREFINT
		NVRAM0[SPREG_ADC_15] = (uint16_t)((float)adc1FilterBuf[9] / (float)CONFIG_ADC_AVERAGE_NUM);//VBAT
#endif

#if defined(LYPE_MCU_1V0_20260106)
		NVRAM0[SPREG_ADC_40] = (uint16_t)((float)adc1FilterBuf[0] / (float)CONFIG_ADC_AVERAGE_NUM);//LAS NTC
		NVRAM0[SPREG_ADC_41] = (uint16_t)((float)adc1FilterBuf[1] / (float)CONFIG_ADC_AVERAGE_NUM);//NC
		NVRAM0[SPREG_ADC_55] = (uint16_t)((float)adc1FilterBuf[2] / (float)CONFIG_ADC_AVERAGE_NUM);//LAS LPD
		NVRAM0[SPREG_ADC_54] = (uint16_t)((float)adc1FilterBuf[3] / (float)CONFIG_ADC_AVERAGE_NUM);//LAS FPD
		NVRAM0[SPREG_ADC_58] = (uint16_t)((float)adc1FilterBuf[4] / (float)CONFIG_ADC_AVERAGE_NUM);//CHIP TEMP
		NVRAM0[SPREG_ADC_59] = (uint16_t)((float)adc1FilterBuf[5] / (float)CONFIG_ADC_AVERAGE_NUM);//VREF
		NVRAM0[SPREG_ADC_60] = (uint16_t)((float)adc1FilterBuf[6] / (float)CONFIG_ADC_AVERAGE_NUM);//VBAT
#endif
	}
	else{//adcBufferSelect = 1
		HAL_ADC_Stop_DMA(&hadc1);
		HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adcDmaBufferA0, CONFIG_ADC1_DMA_BUFFER_SIZE);//再次启动ADC
		adcBufferAselect = 0;
		// ===================== FPU单精度浮点一阶滤波 =====================
		for(i = 0;i < CONFIG_ADC1_CHANNEL;i ++){
			adcRaw = (float)adcDmaBufferA1[i]; 
			adc1FilterBuf[i] = (1.0f - ADC_FILTER_ALPHA) * adc1FilterBuf[i] + ADC_FILTER_ALPHA * adcRaw;
		}
#if defined(LDR2P1_G5_A1_20250731_DUAL) || defined(LDR2P1_G5_A1_20250910_DUAL) || defined(LDR2P1_G5_A1_20250731_TRIP) || defined(LDR2P1_G5_A1_20250910_TRIP)
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
#endif		
		
#if defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
		NVRAM0[SPREG_ADC_55] = (uint16_t)((float)adc1FilterBuf[0] / (float)CONFIG_ADC_AVERAGE_NUM);	//IN0 LAS0_LPD
		NVRAM0[SPREG_ADC_54] = (uint16_t)((float)adc1FilterBuf[1] / (float)CONFIG_ADC_AVERAGE_NUM);	//IN1 LAS0_FPD
		NVRAM0[SPREG_ADC_32] = (uint16_t)((float)adc1FilterBuf[2] / (float)CONFIG_ADC_AVERAGE_NUM);	//IN2 HT0_NTC
		NVRAM0[SPREG_ADC_33] = (uint16_t)((float)adc1FilterBuf[3] / (float)CONFIG_ADC_AVERAGE_NUM);	//IN3 HT1_NTC	
		NVRAM0[SPREG_ADC_52] = (uint16_t)((float)adc1FilterBuf[4] / (float)CONFIG_ADC_AVERAGE_NUM);	//IN7 IVIN_IS
		NVRAM0[SPREG_ADC_1] = (uint16_t)((float)adc1FilterBuf[5] / (float)CONFIG_ADC_AVERAGE_NUM);	//IN10 LAS1_CUR
		NVRAM0[SPREG_ADC_0] = (uint16_t)((float)adc1FilterBuf[6] / (float)CONFIG_ADC_AVERAGE_NUM);	//IN11 LAS0_CUR
		NVRAM0[SPREG_ADC_16] = (uint16_t)((float)adc1FilterBuf[7] / (float)CONFIG_ADC_AVERAGE_NUM);	//IN12 TEC0_CUR	
		NVRAM0[SPREG_ADC_40] = (uint16_t)((float)adc1FilterBuf[8] / (float)CONFIG_ADC_AVERAGE_NUM);	//IN13 LAS0_NTC
		NVRAM0[SPREG_ADC_58] = (uint16_t)((float)adc1FilterBuf[9] / (float)CONFIG_ADC_AVERAGE_NUM);//CHIP TEMP
		NVRAM0[SPREG_ADC_59] = (uint16_t)((float)adc1FilterBuf[10] / (float)CONFIG_ADC_AVERAGE_NUM);//VREFINT
		NVRAM0[SPREG_ADC_60] = (uint16_t)((float)adc1FilterBuf[11] / (float)CONFIG_ADC_AVERAGE_NUM);//VBAT		
#endif		
		
#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
		NVRAM0[SPREG_ADC_12] = (uint16_t)((float)adc1FilterBuf[0] / (float)CONFIG_ADC_AVERAGE_NUM);//HNTC
		NVRAM0[SPREG_ADC_11] = (uint16_t)((float)adc1FilterBuf[1] / (float)CONFIG_ADC_AVERAGE_NUM);//LNTC
		NVRAM0[SPREG_ADC_10] = (uint16_t)((float)adc1FilterBuf[2] / (float)CONFIG_ADC_AVERAGE_NUM);//LPD
		NVRAM0[SPREG_ADC_9] = (uint16_t)((float)adc1FilterBuf[3] / (float)CONFIG_ADC_AVERAGE_NUM);//FPD
		NVRAM0[SPREG_ADC_13] = (uint16_t)((float)adc1FilterBuf[4] / (float)CONFIG_ADC_AVERAGE_NUM);//TMCU
		NVRAM0[SPREG_ADC_14] = (uint16_t)((float)adc1FilterBuf[5] / (float)CONFIG_ADC_AVERAGE_NUM);//VREFINT
		NVRAM0[SPREG_ADC_15] = (uint16_t)((float)adc1FilterBuf[6] / (float)CONFIG_ADC_AVERAGE_NUM);//VBAT
#endif

#if defined(MODEL_PVGLS_10W_1940_A1)
		NVRAM0[SPREG_ADC_8] = (uint16_t)((float)adc1FilterBuf[0] / (float)CONFIG_ADC_AVERAGE_NUM);//IN0 BAT NTC
		NVRAM0[SPREG_ADC_7] = (uint16_t)((float)adc1FilterBuf[1] / (float)CONFIG_ADC_AVERAGE_NUM);//IN1 CH4 CUR ->TEC
		NVRAM0[SPREG_ADC_0] = (uint16_t)((float)adc1FilterBuf[2] / (float)CONFIG_ADC_AVERAGE_NUM);//IN2 CH0 CUR ->1940
		NVRAM0[SPREG_ADC_1] = (uint16_t)((float)adc1FilterBuf[3] / (float)CONFIG_ADC_AVERAGE_NUM);//IN3 CH1 CUR ->980
		NVRAM0[SPREG_ADC_9] = (uint16_t)((float)adc1FilterBuf[4] / (float)CONFIG_ADC_AVERAGE_NUM);//IN11 FPD
		NVRAM0[SPREG_ADC_11] = (uint16_t)((float)adc1FilterBuf[5] / (float)CONFIG_ADC_AVERAGE_NUM);//IN12 LASER NTC
		NVRAM0[SPREG_ADC_12] = (uint16_t)((float)adc1FilterBuf[6] / (float)CONFIG_ADC_AVERAGE_NUM);//IN13 HT NTC
		NVRAM0[SPREG_ADC_13] = (uint16_t)((float)adc1FilterBuf[7] / (float)CONFIG_ADC_AVERAGE_NUM);//CHIP TEMP
		NVRAM0[SPREG_ADC_14] = (uint16_t)((float)adc1FilterBuf[8] / (float)CONFIG_ADC_AVERAGE_NUM);//VREFINT
		NVRAM0[SPREG_ADC_15] = (uint16_t)((float)adc1FilterBuf[9] / (float)CONFIG_ADC_AVERAGE_NUM);//VBAT
#endif
	
#if defined(LYPE_MCU_1V0_20260106)
		NVRAM0[SPREG_ADC_40] = (uint16_t)((float)adc1FilterBuf[0] / (float)CONFIG_ADC_AVERAGE_NUM);//LAS NTC
		NVRAM0[SPREG_ADC_41] = (uint16_t)((float)adc1FilterBuf[1] / (float)CONFIG_ADC_AVERAGE_NUM);//NC
		NVRAM0[SPREG_ADC_55] = (uint16_t)((float)adc1FilterBuf[2] / (float)CONFIG_ADC_AVERAGE_NUM);//LAS LPD
		NVRAM0[SPREG_ADC_54] = (uint16_t)((float)adc1FilterBuf[3] / (float)CONFIG_ADC_AVERAGE_NUM);//LAS FPD
		NVRAM0[SPREG_ADC_58] = (uint16_t)((float)adc1FilterBuf[4] / (float)CONFIG_ADC_AVERAGE_NUM);//CHIP TEMP
		NVRAM0[SPREG_ADC_59] = (uint16_t)((float)adc1FilterBuf[5] / (float)CONFIG_ADC_AVERAGE_NUM);//VREF
		NVRAM0[SPREG_ADC_60] = (uint16_t)((float)adc1FilterBuf[6] / (float)CONFIG_ADC_AVERAGE_NUM);//VBAT
#endif
	}
}

#if(LYPE_MCU_1V0_20260106)
void sPlcAdcProcessBufferB(void){//循环采集ADC
	uint8_t i;
	float adcRaw;
	while(adcBufferBdone == 0);
	adcBufferBdone = 0;
	if(adcBufferBselect == 0){	
		HAL_ADC_Stop_DMA(&hadc3);
		HAL_ADC_Start_DMA(&hadc3, (uint32_t*)&adcDmaBufferB1, CONFIG_ADC3_DMA_BUFFER_SIZE);//再次启动ADC
		adcBufferBselect = 1;
		// ===================== FPU单精度浮点一阶滤波 =====================
		for(i = 0;i < CONFIG_ADC3_CHANNEL;i ++){
			adcRaw = (float)adcDmaBufferB0[i];
			adc3FilterBuf[i] = (1.0f - ADC_FILTER_ALPHA) * adc3FilterBuf[i] + ADC_FILTER_ALPHA * adcRaw;
		}		

#if defined(LYPE_MCU_1V0_20260106)
		NVRAM0[SPREG_ADC_56] = (uint16_t)((float)adc3FilterBuf[0] / (float)CONFIG_ADC_AVERAGE_NUM);//AMB NTC
		NVRAM0[SPREG_ADC_36] = (uint16_t)((float)adc3FilterBuf[1] / (float)CONFIG_ADC_AVERAGE_NUM);//HOT WATER
		NVRAM0[SPREG_ADC_37] = (uint16_t)((float)adc3FilterBuf[2] / (float)CONFIG_ADC_AVERAGE_NUM);//COOL WATER
#endif
	}
	else{//adcBufferBselect = 1
		HAL_ADC_Stop_DMA(&hadc3);
		HAL_ADC_Start_DMA(&hadc3, (uint32_t*)&adcDmaBufferB0, CONFIG_ADC3_DMA_BUFFER_SIZE);//再次启动ADC
		adcBufferBselect = 0;
		// ===================== FPU单精度浮点一阶滤波 =====================
		for(i = 0;i < CONFIG_ADC3_CHANNEL;i ++){
			adcRaw = (float)adcDmaBufferB1[i];
			adc3FilterBuf[i] = (1.0f - ADC_FILTER_ALPHA) * adc3FilterBuf[i] + ADC_FILTER_ALPHA * adcRaw;
		}	

#if defined(LYPE_MCU_1V0_20260106)
		NVRAM0[SPREG_ADC_56] = (uint16_t)((float)adc3FilterBuf[0] / (float)CONFIG_ADC_AVERAGE_NUM);//AMB NTC
		NVRAM0[SPREG_ADC_36] = (uint16_t)((float)adc3FilterBuf[1] / (float)CONFIG_ADC_AVERAGE_NUM);//HOT WATER
		NVRAM0[SPREG_ADC_37] = (uint16_t)((float)adc3FilterBuf[2] / (float)CONFIG_ADC_AVERAGE_NUM);//COOL WATER
#endif
	}
}
#else
void sPlcAdcProcessBufferB(void){}
#endif


