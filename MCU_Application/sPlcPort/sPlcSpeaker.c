#include "sPlc.h"
#include "boardConfig.h"
#include "appConfig.h"
/*****************************************************************************/
static int8_t LoudspeakerEnable = -1;//喇叭使能状态
static int8_t LoudspeakerVolume = -1;//喇叭音量
/*****************************************************************************/
extern 	void MX_TIM8_Init(void);
void sPlcSpeakerInit(void){//喇叭初始化
  HAL_TIM_Base_DeInit(&htim8);
	MX_TIM8_Init();
	RRES(SPCOIL_BEEM_ENABLE);
	sPlcSpeakerVolume(NVRAM0[DM_BEEM_VOLUME]);
	sPlcSpeakerDisable();
	sPlcSpeakerFreq(CONFIG_DEFAULT_SPK_FREQ);
}

void sPlcSpeakerDisable(void){//关闭喇叭数据流
	if(LoudspeakerEnable != false){
		SET_SPK_AP_OFF;
		SET_SPK_TIM_OFF;
		//printf("%s,%d,%s:set loadspeaker off!\n",__FILE__, __LINE__, __func__);
		LoudspeakerEnable = false;
	}
}

void sPlcSpeakerEnable(void){//打开喇叭数据流
	if(LoudspeakerEnable != true){
		SET_SPK_AP_ON;
		SET_SPK_TIM_ON;
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

#if defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP) ||\
		defined(LYPE_MCU_1V0_20260106)
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
#endif



#if defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP) ||\
		defined(LYPE_MCU_1V0_20260106)
static void setSpeakerFreq(uint16_t frequency){
  // TIM8时钟频率为168MHz (APB2时钟84MHz，定时器时钟=2*APB2时钟)
  //uint32_t timer_clock = 84000000;
  uint32_t timer_clock = HAL_RCC_GetPCLK2Freq();
  // 计算预分频器和自动重装载值
  // 目标: (PSC + 1) * (ARR + 1) = timer_clock / frequency
  uint32_t prescaler = 0;
  uint32_t arr_value;
  
  // 确保频率在有效范围内
  if (frequency == 0) frequency = 1;
  if (frequency > timer_clock / 2) frequency = timer_clock / 2;
  
  // 计算最佳的PSC和ARR组合
  // 先尝试不分频(PSC=0)
  arr_value = (timer_clock / frequency) - 1;
  
  // 如果ARR超过最大值(65535)，增加预分频
  if (arr_value > 65535)
  {
    prescaler = 167;  // 168分频
    arr_value = (timer_clock / (prescaler + 1) / frequency) - 1;
    
    // 如果仍然超过最大值，进一步增加预分频
    if (arr_value > 65535)
    {
      prescaler = 1023; // 1024分频
      arr_value = (timer_clock / (prescaler + 1) / frequency) - 1;
    }
  }
  
  // 配置定时器参数
  htim8.Init.Prescaler = prescaler;
  htim8.Init.Period = arr_value;
  // 重新初始化定时器
  if (HAL_TIM_Base_Init(&CONFIG_SPK_HANDLE) != HAL_OK){
		printf("reSet spk tim base clk fail!!!\n");
    Error_Handler();
  }
  // 配置50%占空比
  TIM_OC_InitTypeDef sConfigOC = {0};
	sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;	
  sConfigOC.Pulse = arr_value / 2;  // 50%占空比
  if (HAL_TIM_PWM_ConfigChannel(&CONFIG_SPK_HANDLE, &sConfigOC, CONFIG_SPK_PWM_CHANNEL) != HAL_OK){
		printf("reSet spk time out freq fail!!!\n");
    Error_Handler();
  }
}
#endif

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
#if defined(LDR2P1_G5_A1_20251108_DUAL)
		ftmp = volume * 127 / 100;
#else
		ftmp = volume * 255 / 100;
#endif
		if(ftmp > 0xFF){
			ftmp = 0xFF;
		}
		if(ftmp < 0){
			ftmp = 0;
		}
		writeMcp41010((int16_t)ftmp);
	}
}

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
