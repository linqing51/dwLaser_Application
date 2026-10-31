/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "sPlc.h"
/*****************************************************************************/
/* adcDmaBuffer0/1 是 ADC1 DMA2_Stream0 的目标缓冲。CCM(0x10000000)不支持DMA，
   必须通过 dma_ram 段强制留在 SRAM（scatter 文件 RW_IRAM1 显式承接）。 */
__IO static uint16_t adcDmaBuffer0[CONFIG_ADC1_CHANNEL] __attribute__((section("dma_ram")));//ADC DMA采集储存池
__IO static uint16_t adcDmaBuffer1[CONFIG_ADC1_CHANNEL] __attribute__((section("dma_ram")));//ADC DMA采集储存池
__IO static float adcFilterBuf[CONFIG_ADC1_CHANNEL] = {0.0f};  // ADC1浮点滤波缓存
__IO static uint8_t adcBufferAselect;//ADC BUFFER选择指示
__IO static uint8_t adcBufferAdone;//ADC 采集完毕
/*****************************************************************************/
void sPlcAdcInit(void){//ADC模块初始化
	uint8_t i;
	adcBufferAselect = 0;
	adcBufferAdone = 0;
	memset((uint8_t*)adcDmaBuffer0, 0x0, (CONFIG_ADC1_CHANNEL * 2));
	memset((uint8_t*)adcDmaBuffer1, 0x0, (CONFIG_ADC1_CHANNEL * 2));
	for (i = 0; i < CONFIG_ADC1_CHANNEL; i++){
    adcFilterBuf[i] = 0.0f;
	}
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adcDmaBuffer0, CONFIG_ADC1_CHANNEL); //启用DMA的ADC转换，AD_DMA 0~3 对应ADC 0~3，这里注意最后一个参数的大小
	printf("%s,%d,%s:start adc init......\n",__FILE__, __LINE__, __func__);
#if CONFIG_DEBUG_ADC == 1
	printf("%s,%d,%s:ADC1 DMA启动 len=%d buffer0=%08X buffer1=%08X alpha=%d%%\n",__FILE__, __LINE__, __func__, CONFIG_ADC1_DMA_BUFFER_SIZE, (uint32_t)adcDmaBuffer0, (uint32_t)adcDmaBuffer1, (int)(ADC_FILTER_ALPHA * 100.0f));
#endif
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){    //ADC转换完成回调
  if(hadc->Instance == ADC1){
		adcBufferAdone = 1;
	}
}

void sPlcAdcProcessBuffer(void){//循环采集ADC
	uint8_t i;
	float adcRaw;
	while(adcBufferAdone == 0);
	adcBufferAdone = 0;
	if(adcBufferAselect == 0){	
		HAL_ADC_Stop_DMA(&hadc1);
		HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adcDmaBuffer1, CONFIG_ADC1_DMA_BUFFER_SIZE);//再次启动ADC
		adcBufferAselect = 1;
		// ===================== FPU单精度浮点一阶滤波 =====================
		for(i = 0;i < CONFIG_ADC1_CHANNEL;i ++){
			adcRaw = (float)adcDmaBuffer0[i];
			// 标准一阶滤波公式：Y = (1-α)*Y_last + α*X_new
			adcFilterBuf[i] = (1.0f - ADC_FILTER_ALPHA) * adcFilterBuf[i] + ADC_FILTER_ALPHA * adcRaw;
		}			
		NVRAM0[SPREG_ADC_52] = adcFilterBuf[0];//IN6 VIN VOLTAGE
		NVRAM0[SPREG_ADC_40] = adcFilterBuf[1];//IN7 LASER_NTC
		NVRAM0[SPREG_ADC_32] = adcFilterBuf[2];//IN8 HT0_NTC
		NVRAM0[SPREG_ADC_33] = adcFilterBuf[3];//IN9 HT1_NTC
		NVRAM0[SPREG_ADC_51] = adcFilterBuf[4];//IN10 PWR_CUR		
		NVRAM0[SPREG_ADC_1] = adcFilterBuf[5];//IN11 CH1_CUR
		NVRAM0[SPREG_ADC_0] = adcFilterBuf[6];//IN12 CH0_CUR		
		NVRAM0[SPREG_ADC_16] = adcFilterBuf[7];//IN13 TEC_CUR
		NVRAM0[SPREG_ADC_55] = adcFilterBuf[8];//IN14 LPD		
		NVRAM0[SPREG_ADC_54] = adcFilterBuf[9];//IN15 FPD	
		NVRAM0[SPREG_ADC_58] = adcFilterBuf[10];//CHIP TEMP
		NVRAM0[SPREG_ADC_59] = adcFilterBuf[11];//VREFINT
		NVRAM0[SPREG_ADC_60] = adcFilterBuf[12];//VBAT
		//温度转换(参照 M450/CORE 板): ADC原始值 -> 温度(×10整数)
		TNTLC(EM_LASER_A_DIODE_TEMP, SPREG_ADC_40, CONFIG_DIODE_NTC_RS, CONFIG_DIODE_NTC_B);//激光二极管温度
		TNTLC(EM_HT0_TEMP, SPREG_ADC_32, CONFIG_HT0_NTC_RS, CONFIG_HT0_NTC_B);//散热器0温度
		TNTLC(EM_HT1_TEMP, SPREG_ADC_33, CONFIG_HT0_NTC_RS, CONFIG_HT0_NTC_B);//散热器1温度(复用HT0参数)
		TENV(EM_MCU_TEMP, SPREG_ADC_58);//处理器温度
#if CONFIG_DEBUG_ADC == 1
		printf("%s,%d,%s:[ADC]sel=0 raw(B0):",__FILE__, __LINE__, __func__);
		for(i = 0;i < CONFIG_ADC1_CHANNEL;i ++){ printf("%d,", adcDmaBuffer0[i]); }
		printf("\n");
		printf("%s,%d,%s:[ADC]sel=0 flt:",__FILE__, __LINE__, __func__);
		for(i = 0;i < CONFIG_ADC1_CHANNEL;i ++){ printf("%d,", (int)adcFilterBuf[i]); }
		printf("\n");
#endif
	}
	else{//adcBufferSelect = 1
		HAL_ADC_Stop_DMA(&hadc1);
		HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adcDmaBuffer0, CONFIG_ADC1_DMA_BUFFER_SIZE);//再次启动ADC
		adcBufferAselect = 0;
		// ===================== FPU单精度浮点一阶滤波 =====================
		for(i = 0;i < CONFIG_ADC1_CHANNEL;i ++){
			adcRaw = (float)adcDmaBuffer1[i]; 
			adcFilterBuf[i] = (1.0f - ADC_FILTER_ALPHA) * adcFilterBuf[i] + ADC_FILTER_ALPHA * adcRaw;
		}
		NVRAM0[SPREG_ADC_52] = adcFilterBuf[0];//IN6 VIN VOLTAGE
		NVRAM0[SPREG_ADC_40] = adcFilterBuf[1];//IN7 LASER_NTC
		NVRAM0[SPREG_ADC_32] = adcFilterBuf[2];//IN8 HT1_NTC
		NVRAM0[SPREG_ADC_33] = adcFilterBuf[3];//IN9 HT2_NTC
		NVRAM0[SPREG_ADC_51] = adcFilterBuf[4];//IN10 PWR_CUR		
		NVRAM0[SPREG_ADC_1] = adcFilterBuf[5];//IN11 CH1_CUR
		NVRAM0[SPREG_ADC_0] = adcFilterBuf[6];//IN12 CH0_CUR		
		NVRAM0[SPREG_ADC_16] = adcFilterBuf[7];//IN13 TEC_CUR
		NVRAM0[SPREG_ADC_55] = adcFilterBuf[8];//IN14 LPD		
		NVRAM0[SPREG_ADC_54] = adcFilterBuf[9];//IN15 FPD	
		NVRAM0[SPREG_ADC_58] = adcFilterBuf[10];//CHIP TEMP
		NVRAM0[SPREG_ADC_59] = adcFilterBuf[11];//VREFINT
		NVRAM0[SPREG_ADC_60] = adcFilterBuf[12];//VBAT		
		//温度转换(参照 M450/CORE 板): ADC原始值 -> 温度(×10整数)
		TNTLC(EM_LASER_A_DIODE_TEMP, SPREG_ADC_40, CONFIG_DIODE_NTC_RS, CONFIG_DIODE_NTC_B);//激光二极管温度
		TNTLC(EM_HT0_TEMP, SPREG_ADC_32, CONFIG_HT0_NTC_RS, CONFIG_HT0_NTC_B);//散热器0温度
		TNTLC(EM_HT1_TEMP, SPREG_ADC_33, CONFIG_HT0_NTC_RS, CONFIG_HT0_NTC_B);//散热器1温度(复用HT0参数)
		TENV(EM_MCU_TEMP, SPREG_ADC_58);//处理器温度
#if CONFIG_DEBUG_ADC == 1
		printf("%s,%d,%s:[ADC]sel=1 raw(B1):",__FILE__, __LINE__, __func__);
		for(i = 0;i < CONFIG_ADC1_CHANNEL;i ++){ printf("%d,", adcDmaBuffer1[i]); }
		printf("\n");
		printf("%s,%d,%s:[ADC]sel=1 flt:",__FILE__, __LINE__, __func__);
		for(i = 0;i < CONFIG_ADC1_CHANNEL;i ++){ printf("%d,", (int)adcFilterBuf[i]); }
		printf("\n");
#endif
	}
}












