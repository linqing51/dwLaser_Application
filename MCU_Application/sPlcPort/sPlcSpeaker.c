#include "sPlc.h"
/*****************************************************************************/
static int8_t LoudspeakerEnable = -1;//喇叭使能状态
static int8_t LoudspeakerVolume = -1;//喇叭音量
/*****************************************************************************/
void sPlcSpeakerInit(void){//喇叭初始化
	RRES(SPCOIL_BEEM_ENABLE);
	sPlcSpeakerVolume(NVRAM0[DM_BEEM_VOLUME]);
	sPlcSpeakerDisable();
	sPlcSpeakerFreq(CONFIG_DEFAULT_SPK_FREQ);
	LoudspeakerEnable = false;
#if (CONFIG_DEBUG_SPK != 0)
	printf("%s,%d,%s:Init beem speak!\n",__FILE__, __LINE__, __func__);
#endif
}

void sPlcSpeakerDisable(void){//关闭喇叭数据流
	if(LoudspeakerEnable != false){
		SET_SPK_AP_OFF;
		SET_SPK_TIM_OFF;
#if (CONFIG_DEBUG_SPK != 0)
		printf("%s,%d,%s:set loadspeaker off!\n",__FILE__, __LINE__, __func__);
#endif
		LoudspeakerEnable = false;
	}
}

void sPlcSpeakerEnable(void){//打开喇叭数据流
	if(LoudspeakerEnable != true){
		SET_SPK_AP_ON;
		SET_SPK_TIM_ON;
#if (CONFIG_DEBUG_SPK != 0)
		printf("%s,%d,%s:set loadspeaker on!\n",__FILE__, __LINE__, __func__);
#endif
		LoudspeakerEnable = true;
	}
}

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
  // TIM8时钟频率为168MHz (APB2时钟84MHz，定时器时钟=2*APB2时钟)
  //uint32_t timer_clock = 84000000;
  uint32_t timer_clock;
  timer_clock = HAL_RCC_GetPCLK2Freq();
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
  CONFIG_SPK_HANDLE.Init.Prescaler = prescaler;
  CONFIG_SPK_HANDLE.Init.Period = arr_value;
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
		ftmp = volume * 127 / 100;
		if(ftmp > 0xFF){
			ftmp = 0xFF;
		}
		if(ftmp < 0){
			ftmp = 0;
		}
		writeMcp41010((int16_t)ftmp);
	}
}




















