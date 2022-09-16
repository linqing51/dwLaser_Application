#include "sPlcSpeaker.h"
/*****************************************************************************/
uint16_t audioSineTable[256] = {0};
static int8_t LoudspeakerEnable = -1;//喇叭使能状态
static int8_t LoudspeakerVolume = -1;//喇叭音量
/*****************************************************************************/
extern TIM_HandleTypeDef htim7;//DAC DMA 计时器
extern DAC_HandleTypeDef hdac;
static float32_t linearToLog(int16_t volume);
/*****************************************************************************/
void sPlcSpeakerInit(void){//喇叭初始化	
	SET_SPEAK_ENA(GPIO_PIN_RESET);
	RRES(SPCOIL_BEEM_ENABLE);
	sPlcSpeakerVolume(NVRAM0[EM_SPEAK_VOLUME]);
	sPlcSpeakerDisable();
	sPlcSpeakerFreq(CONFIG_SPLC_DEFAULT_SPK_FREQ);
	printf("%s,%d,%s:speaker dma init......\n",__FILE__, __LINE__, __func__);
}
void sPlcSpeakerDisable(void){//关闭喇叭数据流
	if(LoudspeakerEnable != false){
		SET_SPEAK_ENA(GPIO_PIN_RESET);
		HAL_TIM_Base_Stop(&htim7);
		HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1);
		printf("%s,%d,%s:set speaker off!\n",__FILE__, __LINE__, __func__);
		LoudspeakerEnable = false;
	}
}
void sPlcSpeakerEnable(void){//打开喇叭数据流
	if(LoudspeakerEnable != true){
		SET_SPEAK_ENA(GPIO_PIN_SET);
		HAL_TIM_Base_Start(&htim7);
		HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t *)audioSineTable, 256, DAC_ALIGN_12B_R);
		printf("%s,%d,%s:set speaker on!\n",__FILE__, __LINE__, __func__);
		LoudspeakerEnable = true;
	}
}
void sPlcSpeakerFreq(int16_t freq){//设置蜂鸣器频率
	float32_t f1;
	if(LoudspeakerEnable){//蜂鸣器打开
		HAL_TIM_Base_Stop(&htim7);
		HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1);
	}
	if(freq > CONFIG_SPLC_MAX_SPK_FREQ){
		freq = CONFIG_SPLC_MAX_SPK_FREQ;
	}
	if(freq < CONFIG_SPLC_MIN_SPK_FREQ){
		freq = CONFIG_SPLC_MIN_SPK_FREQ;
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
	printf("%s,%d,%s:set audio freq:%d\n",__FILE__, __LINE__, __func__, freq);
	HAL_TIM_Base_Start(&htim7);
	HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t *)audioSineTable, 256, DAC_ALIGN_12B_R);
}
void sPlcSpeakerVolume(int16_t volume){//设置喇叭音量
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
		printf("%s,%d,%s:audio wave table initialization done...\n",__FILE__, __LINE__, __func__);
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



