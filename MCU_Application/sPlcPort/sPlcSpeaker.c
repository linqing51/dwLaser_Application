#include "sPlcSpeaker.h"
/*****************************************************************************/
uint16_t audioSineTable[256] = {0};
static int8_t LoudspeakerEnable = -1;//喇叭使能状态
static int16_t LoudspeakerFreq = -1;//喇叭频率
static int8_t LoudspeakerVolume = -1;//喇叭音量
/*****************************************************************************/
extern TIM_HandleTypeDef htim7;//DAC DMA 计时器
extern DAC_HandleTypeDef hdac;
static float32_t linearToLog(int16_t volume);
/*****************************************************************************/
void initLoudspeaker(void){//喇叭初始化
	SET_SPEAKER_OFF;
	RRES(SPCOIL_BEEM_ENABLE);
	setLoudspeakerVolume(NVRAM0[DM_BEEM_VOLUME]);
	setLoudspeakerDisable();
	setLoudspeakerFreq(CONFIG_SPLC_DEFAULT_SPK_FREQ);
}
void setLoudspeakerDisable(void){//关闭喇叭数据流
	if(LoudspeakerEnable != false){
		SET_SPEAKER_OFF;
		HAL_TIM_Base_Stop(&htim7);
		HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1);
#if CONFIG_DEBUG_SPK == 1
		printf("%s,%d,%s:set loadspeaker off!\n",__FILE__, __LINE__, __func__);
#endif
		LoudspeakerEnable = false;
	}
}
void setLoudspeakerEnable(void){//打开喇叭数据流
	if(LoudspeakerEnable != true){
		SET_SPEAKER_ON;
		HAL_TIM_Base_Start(&htim7);
		HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t *)audioSineTable, 256, DAC_ALIGN_12B_R);
#if CONFIG_DEBUG_SPK == 1
		printf("%s,%d,%s:set loadspeaker on!\n",__FILE__, __LINE__, __func__);
#endif
		LoudspeakerEnable = true;
	}
}
void setLoudspeakerFreq(int16_t freq){//设置蜂鸣器频率
	float32_t f1;
	if(LoudspeakerFreq != freq){
		if(LoudspeakerEnable){//蜂鸣器打开
			HAL_TIM_Base_Stop(&htim7);
			HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1);
		}
		if(freq > CONFIG_SPLC_MAX_SPK_FREQ){
			freq = CONFIG_SPLC_MAX_SPK_FREQ;
		}
		if(freq < CONFIG_SPLC_MIN_SPL_FREQ){
			freq = CONFIG_SPLC_MIN_SPL_FREQ;
		}
		f1 = HAL_RCC_GetPCLK1Freq() / sizeof(audioSineTable) * 2 / freq;
		htim7.Instance = TIM7;
		htim7.Init.Prescaler = 1;
		htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
		htim7.Init.Period = (uint16_t)f1;
		htim7.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
		htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
		if (HAL_TIM_Base_Init(&htim7) != HAL_OK){
			printf("%s,%d,%s:tim7 init fail!\n",__FILE__, __LINE__, __func__);
			Error_Handler();
		}
#if CONFIG_DEBUG_SPK == 1
		printf("%s,%d,%s:set audio freq:%d\n",__FILE__, __LINE__, __func__, freq);
#endif
		if(LoudspeakerEnable){
			HAL_TIM_Base_Start(&htim7);
			HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t *)audioSineTable, 256, DAC_ALIGN_12B_R);
		}
		LoudspeakerFreq = freq;
	}
}
void setLoudspeakerVolume(int16_t volume){//设置喇叭音量
	int16_t i;
	float64_t  ftemp,fvolume = 0;
	float64_t piStep;
	if(LoudspeakerVolume != volume){
		fvolume = linearToLog(volume);
		piStep = 2.0F * PI / 256.0F;
		for(i = 0;i < 256;i ++){
			ftemp = 1.0F + sin(i * piStep + PI + (PI /2));
			ftemp = fvolume * ftemp * 2000.0F;
			if(ftemp >= 4095.0F){
				ftemp = 4095.0F;
			}
			if(ftemp < 0){
				ftemp = 0;
			}
			audioSineTable[i] = (uint16_t)(ftemp);            
		}
#if CONFIG_DEBUG_SPK == 1
		printf("%s,%d,%s:audio wave table initialization done...\n",__FILE__, __LINE__, __func__);
#endif
		LoudspeakerVolume = volume;
	}
}
static float32_t linearToLog(int16_t volume){//线性音量转化为对数音量  
	float64_t prr, vol;
	if(volume > 100){
		volume = 100;
	}
	if(volume < 0){
		volume = 0;
	}
	prr = (float64_t)volume / 100.0F;
	if(prr != 0){
		vol = (0.2 * prr) / (0.2 + prr - prr*prr);
	}
	else{
		vol = 0;
	}
	if(vol < 0){
		vol = 0;
	}
	if(vol > 1){
		vol = 1;
	}
	return vol;
}