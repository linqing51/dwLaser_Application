#include "sPlc.h"
/*****************************************************************************/
static void writeMcp41010(uint8_t dat){//MCP41010 模拟SPI写入
	uint16_t tmp, i, wdat;
	SET_MCP41010_CS(GPIO_PIN_SET);//CS = 1
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	SET_MCP41010_CS(GPIO_PIN_RESET);//CS = 0
	wdat = 0x1100;
	wdat += dat;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	for(i = 0;i < 16;i ++){
		tmp = (uint8_t)(wdat >> (15 - i)) & 0x01;
		SET_MCP41010_SDI((GPIO_PinState)tmp);//dat -> SDI
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		SET_MCP41010_SCK(GPIO_PIN_SET);//SCK -> 1
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		SET_MCP41010_SCK(GPIO_PIN_RESET);//SCK -> 0
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	}
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	SET_MCP41010_CS(GPIO_PIN_SET);
}


static void setSpeakerFreq(uint16_t freq){
  TIM_OC_InitTypeDef sConfigOC = {0};
	uint32_t uwPrescalerValue = (uint32_t)((HAL_RCC_GetPCLK1Freq() / (9+1) / freq) - 1);  
	htim5.Instance = TIM5;
  htim5.Init.Period        			= uwPrescalerValue;
  htim5.Init.Prescaler     			= 9;
  htim5.Init.ClockDivision 			= 0;
  htim5.Init.CounterMode   			= TIM_COUNTERMODE_UP;
  htim5.Init.AutoReloadPreload 	= TIM_AUTORELOAD_PRELOAD_DISABLE;
  if(HAL_TIM_OC_Init(&htim5) 		!= HAL_OK){
		printf("reSet TIM5 base clk fail!!!\n");
  }
	
	sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
  //sConfigOC.Pulse = 11;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
  if(HAL_TIM_OC_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_1) != HAL_OK){
    printf("reSet TIM5 out freq fail!!!\n");
  }
}

void sPlcSpeakerInit(void){//喇叭初始化
	SET_SPEAKER_OFF;
	RRES(SPCOIL_BEEM_ENABLE);
	sPlcSpeakerVolume(NVRAM0[DM_BEEM_VOLUME]);
	sPlcSpeakerDisable();
	sPlcSpeakerFreq(CONFIG_SPLC_DEFAULT_SPK_FREQ);
	printf("%s,%d,%s:speaker dma init......\n",__FILE__, __LINE__, __func__);
}
void sPlcSpeakerDisable(void){//关闭喇叭数据流
	SET_SPEAKER_OFF;
}
void sPlcSpeakerEnable(void){//打开喇叭数据流
	SET_SPEAKER_ON;
}
void sPlcSpeakerFreq(int16_t freq){//设置蜂鸣器频率
	if(freq > CONFIG_SPLC_MAX_SPK_FREQ){
		freq = CONFIG_SPLC_MAX_SPK_FREQ;
	}
	if(freq < CONFIG_SPLC_MIN_SPL_FREQ){
		freq = CONFIG_SPLC_MIN_SPL_FREQ;
	}
	setSpeakerFreq(freq);
}
void sPlcSpeakerVolume(int16_t volume){//设置喇叭音量
	float ftmp;
	ftmp = volume * 255 / 100;
	if(ftmp >255){
		ftmp = 0;
	}
	if(ftmp < 0){
		ftmp = 0;
	}
	writeMcp41010((int16_t)ftmp);
}



