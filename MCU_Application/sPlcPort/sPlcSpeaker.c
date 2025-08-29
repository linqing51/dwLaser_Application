#include "sPlc.h"
#include "boardConfig.h"
/*****************************************************************************/
static int8_t LoudspeakerEnable = -1;//喇叭使能状态
static int8_t LoudspeakerVolume = -1;//喇叭音量
/*****************************************************************************/
void sPlcSpeakerInit(void){//喇叭初始化
	RRES(SPCOIL_BEEM_ENABLE);
	sPlcSpeakerVolume(NVRAM0[DM_BEEM_VOLUME]);
	sPlcSpeakerDisable();
	sPlcSpeakerFreq(CONFIG_DEFAULT_SPK_FREQ);
	printf("%s,%d,%s:speaker dma init......\n",__FILE__, __LINE__, __func__);
}

void sPlcSpeakerDisable(void){//关闭喇叭数据流
	if(LoudspeakerEnable != false){
		SET_SPK_AP_OFF;
		//SET_SPK_TIM_OFF;
		//printf("%s,%d,%s:set loadspeaker off!\n",__FILE__, __LINE__, __func__);
		LoudspeakerEnable = false;
	}
}

void sPlcSpeakerEnable(void){//打开喇叭数据流
	if(LoudspeakerEnable != true){
		SET_SPK_AP_ON;
		//SET_SPK_TIM_ON;
		//printf("%s,%d,%s:set loadspeaker on!\n",__FILE__, __LINE__, __func__);
		LoudspeakerEnable = true;
	}
}

#if defined(MODEL_PVGLS_15W_1470_A0) || (MODEL_PVGLS_15W_1470_A1)
uint16_t audioSineTable[256] = {0};
static float32_t linearToLog(int16_t volume);

void sPlcSpeakerFreq(int16_t freq){//设置蜂鸣器频率
	float32_t f1;
	SET_SPK_TIM_OFF;
	if(freq > CONFIG_MAX_SPK_FREQ){
		freq = CONFIG_MAX_SPK_FREQ;
	}
	if(freq < CONFIG_MIN_SPL_FREQ){
		freq = CONFIG_MIN_SPL_FREQ;
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
	//printf("%s,%d,%s:set audio freq:%d\n",__FILE__, __LINE__, __func__, freq);
	SET_SPK_TIM_ON;

}
void sPlcSpeakerVolume(int16_t volume){//设置喇叭音量
	int16_t i;
	float64_t fvolume = 0;
	//float64_t piStep;
	if(LoudspeakerVolume != volume){
		fvolume = linearToLog(volume);
		//方波声音
		for (i = 0;i < 127 ;i++){
			audioSineTable[i] = (int16_t)(2048 + fvolume * 2047);
		}
		for (i = 127; i < 256;i++){
			audioSineTable[i] = (int16_t)(2048 - fvolume * 2047);
		}
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
	
	vol = vol * CONFIG_BEEM_MAX_LIMIT;
	if(vol < 0){
		vol = 0;
	}
	if(vol > 1){
		vol = 1;
	}
	return vol;
}
#endif

#if defined(GLOAL_LDR2P1_G5_A1_20250731_DUAL) || defined(GLOAL_LDR2P1_G5_A1_20250731_TRIP)
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

static void setSpeakerFreq(uint16_t frequency){
	TIM_OC_InitTypeDef sConfigOC = {0};
  // 计算自动重载值(ARR)和预分频器值(PSC)
  uint32_t SystemCoreClock = HAL_RCC_GetPCLK1Freq();
  uint32_t psc = 84 - 1; // 预分频器值，将42MHz时钟分频为1MHz
  uint32_t arr = (SystemCoreClock / (psc + 1)) / frequency - 1;

  // TIM8初始化
  htim8.Instance = TIM8;
  htim8.Init.Prescaler = psc;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.Period = arr;
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim8) != HAL_OK){
		printf("reSet TIM8 base clk fail!!!\n");
    Error_Handler();
  }
  // 配置PWM模式 (使用CH1)
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = arr / 2; // 50%占空比
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1) != HAL_OK){
		printf("reSet TIM8 CH1 out freq fail!!!\n");
    Error_Handler();
  }
}

inline void sPlcSpeakerFreq(int16_t freq){//设置蜂鸣器频率
	if(freq > CONFIG_BEEM_MAX_FREQ){
		freq = CONFIG_BEEM_MAX_FREQ;
	}
	if(freq < CONFIG_BEEM_MIN_FREQ){
		freq = CONFIG_BEEM_MIN_FREQ;
	}
	setSpeakerFreq(freq);
}

inline void sPlcSpeakerVolume(int16_t volume){//设置喇叭音量
	float ftmp;
	if(LoudspeakerVolume != volume){
		ftmp = volume * 255 / 100;
		if(ftmp > 0xFF){
			ftmp = 0xFF;
		}
		if(ftmp < 0){
			ftmp = 0;
		}
		writeMcp41010((int16_t)ftmp);
	}
}
#endif

#if defined(MODEL_PVGLS_10W_1940_A1) 
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

static void setSpeakerFreq(uint16_t frequency){
	TIM_OC_InitTypeDef sConfigOC = {0};
  // 计算自动重载值(ARR)和预分频器值(PSC)
  uint32_t SystemCoreClock = HAL_RCC_GetPCLK1Freq();
  uint32_t psc = 84 - 1; // 预分频器值，将42MHz时钟分频为1MHz
  uint32_t arr = (SystemCoreClock / (psc + 1)) / frequency - 1;

  // TIM2初始化
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = psc;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = arr;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK){
		printf("reSet TIM2 base clk fail!!!\n");
    Error_Handler();
  }
  // 配置PWM模式 (使用CH2)
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = arr / 2; // 50%占空比
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK){
		printf("reSet TIM2 out freq fail!!!\n");
    Error_Handler();
  }
}

inline void sPlcSpeakerFreq(int16_t freq){//设置蜂鸣器频率
	if(freq > CONFIG_BEEM_MAX_FREQ){
		freq = CONFIG_BEEM_MAX_FREQ;
	}
	if(freq < CONFIG_BEEM_MIN_FREQ){
		freq = CONFIG_BEEM_MIN_FREQ;
	}
	setSpeakerFreq(freq);
}
inline void sPlcSpeakerVolume(int16_t volume){//设置喇叭音量
	float ftmp;
	if(LoudspeakerVolume != volume){
		ftmp = volume * 255 / 100;
		if(ftmp > 0xFF){
			ftmp = 0xFF;
		}
		if(ftmp < 0){
			ftmp = 0;
		}
		writeMcp41010((int16_t)ftmp);
	}
}
#endif
