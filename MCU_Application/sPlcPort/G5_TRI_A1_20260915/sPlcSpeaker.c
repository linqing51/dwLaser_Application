/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "sPlc.h"
/*****************************************************************************/
static int8_t LoudspeakerEnable = -1;//鍠囧彮浣胯兘鐘舵€?
static int8_t LoudspeakerVolume = -1;//鍠囧彮闊抽噺
/*****************************************************************************/
void sPlcSpeakerInit(void){//鍠囧彮鍒濆鍖?
	RRES(SPCOIL_BEEM_ENABLE);
	sPlcSpeakerVolume(NVRAM0[DM_BEEM_VOLUME]);
	sPlcSpeakerDisable();
	sPlcSpeakerFreq(CONFIG_DEFAULT_SPK_FREQ);
	LoudspeakerEnable = false;
#if (CONFIG_DEBUG_SPK != 0)
	printf("%s,%d,%s:Init beem speak!\n",__FILE__, __LINE__, __func__);
#endif
}

void sPlcSpeakerDisable(void){//鍏抽棴鍠囧彮鏁版嵁娴?
	if(LoudspeakerEnable != false){
		SET_SPK_AP_OFF;
		SET_SPK_TIM_OFF;
#if (CONFIG_DEBUG_SPK != 0)
		printf("%s,%d,%s:set loadspeaker off!\n",__FILE__, __LINE__, __func__);
#endif
		LoudspeakerEnable = false;
	}
}

void sPlcSpeakerEnable(void){//鎵撳紑鍠囧彮鏁版嵁娴?
	if(LoudspeakerEnable != true){
		SET_SPK_AP_ON;
		SET_SPK_TIM_ON;
#if (CONFIG_DEBUG_SPK != 0)
		printf("%s,%d,%s:set loadspeaker on!\n",__FILE__, __LINE__, __func__);
#endif
		LoudspeakerEnable = true;
	}
}

#if defined(MODEL_PVGLS_15W_1470_A0) || (MODEL_PVGLS_15W_1470_A1)
uint16_t audioSineTable[256] = {0};
static float32_t linearToLog(int16_t volume);

void sPlcSpeakerFreq(int16_t freq){//璁剧疆铚傞福鍣ㄩ鐜?
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
void sPlcSpeakerVolume(int16_t volume){//璁剧疆鍠囧彮闊抽噺
	int16_t i;
	float64_t fvolume = 0;
	//float64_t piStep;
	if(LoudspeakerVolume != volume){
		fvolume = linearToLog(volume);
		//鏂规尝澹伴煶
		for (i = 0;i < 127 ;i++){
			audioSineTable[i] = (int16_t)(2048 + fvolume * 2047);
		}
		for (i = 127; i < 256;i++){
			audioSineTable[i] = (int16_t)(2048 - fvolume * 2047);
		}
	}
}
static float32_t linearToLog(int16_t volume){//绾挎€ч煶閲忚浆鍖栦负瀵规暟闊抽噺  
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
		defined(LYPE_MCU_1V0_20260106) ||\
		defined(LDR2P1_RASPI_G9_A1_20250322_DUAL) ||\
		defined(G5_TRI_A1_20260915)
static void writeMcp41010(uint8_t dat){//MCP41010 妯℃嫙SPI鍐欏叆
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
		defined(LYPE_MCU_1V0_20260106) ||\
		defined(LDR2P1_RASPI_G9_A1_20250322_DUAL) ||\
		defined(G5_TRI_A1_20260915)
static void setSpeakerFreq(uint16_t frequency){
  // TIM8鏃堕挓棰戠巼涓?68MHz (APB2鏃堕挓84MHz锛屽畾鏃跺櫒鏃堕挓=2*APB2鏃堕挓)
  //uint32_t timer_clock = 84000000;
  uint32_t timer_clock;
#if defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP) ||\
		defined(G5_TRI_A1_20260915)
    timer_clock = HAL_RCC_GetPCLK2Freq();
#endif
#if defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
    timer_clock= HAL_RCC_GetPCLK1Freq();
#endif
  // 璁＄畻棰勫垎棰戝櫒鍜岃嚜鍔ㄩ噸瑁呰浇鍊?
  // 鐩爣: (PSC + 1) * (ARR + 1) = timer_clock / frequency
  uint32_t prescaler = 0;
  uint32_t arr_value;
  
  // 纭繚棰戠巼鍦ㄦ湁鏁堣寖鍥村唴
  if (frequency == 0) frequency = 1;
  if (frequency > timer_clock / 2) frequency = timer_clock / 2;
  
  // 璁＄畻鏈€浣崇殑PSC鍜孉RR缁勫悎
  // 鍏堝皾璇曚笉鍒嗛(PSC=0)
  arr_value = (timer_clock / frequency) - 1;
  
  // 濡傛灉ARR瓒呰繃鏈€澶у€?65535)锛屽鍔犻鍒嗛
  if (arr_value > 65535)
  {
    prescaler = 167;  // 168鍒嗛
    arr_value = (timer_clock / (prescaler + 1) / frequency) - 1;
    
    // 濡傛灉浠嶇劧瓒呰繃鏈€澶у€硷紝杩涗竴姝ュ鍔犻鍒嗛
    if (arr_value > 65535)
    {
      prescaler = 1023; // 1024鍒嗛
      arr_value = (timer_clock / (prescaler + 1) / frequency) - 1;
    }
  }
  
  // 閰嶇疆瀹氭椂鍣ㄥ弬鏁?
  CONFIG_SPK_HANDLE.Init.Prescaler = prescaler;
  CONFIG_SPK_HANDLE.Init.Period = arr_value;
  // 閲嶆柊鍒濆鍖栧畾鏃跺櫒
  if (HAL_TIM_Base_Init(&CONFIG_SPK_HANDLE) != HAL_OK){
		printf("reSet spk tim base clk fail!!!\n");
    Error_Handler();
  }
  // 閰嶇疆50%鍗犵┖姣?
  TIM_OC_InitTypeDef sConfigOC = {0};
	sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;	
  sConfigOC.Pulse = arr_value / 2;  // 50%鍗犵┖姣?
  if (HAL_TIM_PWM_ConfigChannel(&CONFIG_SPK_HANDLE, &sConfigOC, CONFIG_SPK_PWM_CHANNEL) != HAL_OK){
		printf("reSet spk time out freq fail!!!\n");
    Error_Handler();
  }
}
#endif

inline void sPlcSpeakerFreq(int16_t freq){//璁剧疆铚傞福鍣ㄩ鐜?
	if(freq > CONFIG_BEEM_MAX_FREQ){
		freq = CONFIG_BEEM_MAX_FREQ;
	}
	if(freq < CONFIG_BEEM_MIN_FREQ){
		freq = CONFIG_BEEM_MIN_FREQ;
	}
	setSpeakerFreq(freq);
}

inline void sPlcSpeakerVolume(int16_t volume){//璁剧疆鍠囧彮闊抽噺
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
static void writeMcp41010(uint8_t dat){//MCP41010 妯℃嫙SPI鍐欏叆
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
  // 璁＄畻鑷姩閲嶈浇鍊?ARR)鍜岄鍒嗛鍣ㄥ€?PSC)
  uint32_t SystemCoreClock = HAL_RCC_GetPCLK1Freq();
  uint32_t psc = 84 - 1; // 棰勫垎棰戝櫒鍊硷紝灏?2MHz鏃堕挓鍒嗛涓?MHz
  uint32_t arr = (SystemCoreClock / (psc + 1)) / frequency - 1;

  // TIM2鍒濆鍖?
  htim2.Instance = CONFIG_SPK_TIM;
  htim2.Init.Prescaler = psc;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = arr;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK){
		printf("reSet TIM2 base clk fail!!!\n");
    Error_Handler();
  }
  // 閰嶇疆PWM妯″紡
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = arr / 2; // 50%鍗犵┖姣?
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&CONFIG_SPK_TIM, &sConfigOC, CONFIG_SPK_PWM_CHANNEL) != HAL_OK){
		printf("reSet TIM2 out freq fail!!!\n");
    Error_Handler();
  }
}

inline void sPlcSpeakerFreq(int16_t freq){//璁剧疆铚傞福鍣ㄩ鐜?
	if(freq > CONFIG_BEEM_MAX_FREQ){
		freq = CONFIG_BEEM_MAX_FREQ;
	}
	if(freq < CONFIG_BEEM_MIN_FREQ){
		freq = CONFIG_BEEM_MIN_FREQ;
	}
	setSpeakerFreq(freq);
}
inline void sPlcSpeakerVolume(int16_t volume){//璁剧疆鍠囧彮闊抽噺
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
