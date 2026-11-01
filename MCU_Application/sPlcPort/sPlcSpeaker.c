/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/

#include "sPlc.h"
/*****************************************************************************/
static int8_t LoudspeakerEnable = -1;//喇叭使能状态
static int8_t LoudspeakerVolume = -1;//喇叭音量
/*****************************************************************************/
/* 判断是否为高级定时器(TIM1/TIM8), 这类定时器需 BDTR.MOE 主输出使能。
 * F1 仅有 TIM1, F4 有 TIM1/TIM8; 用 #ifdef 保护以适配外设裁剪的型号。 */
static uint8_t sPlcSpeakerIsAdvanced(TIM_TypeDef *tim){
	if(tim == TIM1){
		return 1U;
	}
#ifdef TIM8
	if(tim == TIM8){
		return 1U;
	}
#endif
	return 0U;
}

/* 蜂鸣器定时器底层硬件初始化(覆盖 STM32CubeMX 生成的配置):
 * 使能定时器与 GPIO 时钟, 并把输出引脚配置为复用推挽。
 * F4 需指定复用编号(AF), F1 为固定复用、GPIO_InitTypeDef 无 Alternate 成员。 */
static void sPlcSpeakerHardwareInit(void){
	static uint8_t s_hw_inited = 0U;
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	if(s_hw_inited != 0U){
		return;
	}

	/* 使能定时器时钟与对应 GPIO 端口时钟 */
	CONFIG_SPK_TIM_CLK_ENABLE();
	CONFIG_SPK_GPIO_CLK_ENABLE();

	/* 配置输出引脚: 复用推挽、下拉、低速(与 CubeMX 原配置一致) */
	GPIO_InitStruct.Pin = SPK_PWM_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
#ifdef SPLC_STM32F1
	/* F1 固定复用, 无 Alternate 成员, 无需设置 */
#else
	GPIO_InitStruct.Alternate = CONFIG_SPK_GPIO_AF;
#endif
	HAL_GPIO_Init(SPK_PWM_GPIO_Port, &GPIO_InitStruct);

	s_hw_inited = 1U;
}
/*****************************************************************************/
void sPlcSpeakerInit(void){//喇叭初始化
	RRES(SPCOIL_BEEM_ENABLE);
	sPlcSpeakerHardwareInit();
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

/* 判断定时器实例是否挂在 APB2 高速总线。
 * STM32F1/F4 的总线归属完全一致:
 *   APB2: TIM1、TIM8、TIM9、TIM10、TIM11
 *   APB1: TIM2、TIM3、TIM4、TIM5、TIM6、TIM7、TIM12、TIM13、TIM14
 * 用 #ifdef 保护, 适配未集成对应外设的型号(如 F103 无 TIM9~TIM11)。 */
static uint8_t sPlcSpeakerIsApb2(TIM_TypeDef *tim){
	switch((uint32_t)tim)
	{
#ifdef TIM1
		case (uint32_t)TIM1:
#endif
#ifdef TIM8
		case (uint32_t)TIM8:
#endif
#ifdef TIM9
		case (uint32_t)TIM9:
#endif
#ifdef TIM10
		case (uint32_t)TIM10:
#endif
#ifdef TIM11
		case (uint32_t)TIM11:
#endif
			return 1U;
		default:
			return 0U;
	}
}

/* 获取蜂鸣器定时器的真实输入时钟(Hz)。
 * 自动识别定时器所在总线(APB1/APB2), 并根据该总线预分频修正:
 *   APBx 预分频 = 1 时, 定时器时钟 = PCLKx;
 *   APBx 预分频 > 1 时, 定时器时钟 = 2 * PCLKx。
 * 该规则 STM32F1/F4 通用, 无需为不同主频(72MHz/168MHz)写死参数。 */
static uint32_t sPlcSpeakerGetTimClk(TIM_HandleTypeDef *htim){
	uint32_t pclk;

	if(sPlcSpeakerIsApb2(htim->Instance) != 0U)
	{
		pclk = HAL_RCC_GetPCLK2Freq();
		/* PPRE2 位段全 0 表示 APB2 未分频(DIV1), 定时器时钟 = PCLK2 */
		if((RCC->CFGR & RCC_CFGR_PPRE2) == 0U){
			return pclk;
		}
	}
	else
	{
		pclk = HAL_RCC_GetPCLK1Freq();
		/* PPRE1 位段全 0 表示 APB1 未分频(DIV1), 定时器时钟 = PCLK1 */
		if((RCC->CFGR & RCC_CFGR_PPRE1) == 0U){
			return pclk;
		}
	}
	/* 总线已分频(2/4/8/16), 定时器时钟倍频为 2*PCLK */
	return pclk * 2U;
}

static void setSpeakerFreq(uint16_t frequency){
	uint32_t timer_clock;
	uint32_t half_ticks; //半周期(一次翻转)所需计数 (PSC+1)*(ARR+1)
	uint32_t psc1;       //预分频系数 PSC+1
	uint32_t arr1;       //周期系数 ARR+1
	TIM_OC_InitTypeDef sConfigOC = {0};

	timer_clock = sPlcSpeakerGetTimClk(&CONFIG_SPK_HANDLE);

	/* 频率保护: 翻转模式一个完整方波至少需要 2 个计数 */
	if(frequency == 0U){
		frequency = 1U;
	}
	if(frequency > (timer_clock / 2U)){
		frequency = (uint16_t)(timer_clock / 2U);
	}

	/* 频率输出(翻转)模式: 计数器每匹配 CCR 翻转一次 OC, 一个完整方波
	 * 含两次翻转, 故半周期计数 = timer_clock/(2*f), 四舍五入减小量化误差。
	 * 高/低电平各占 (ARR+1) 个计数, 占空比天然精确 50%。 */
	half_ticks = (timer_clock + frequency) / (2U * frequency);
	if(half_ticks < 1U){
		half_ticks = 1U;
	}

	/* 分解 half_ticks = psc1 * arr1, 二者均为 16 位(最大 65536)。
	 * 优先 PSC=0(psc1=1)使计数时钟最高、ARR 分辨率最好;
	 * 超 16 位时取最小的 psc1 让 arr1 <= 65536, 从而频率误差最小。 */
	if(half_ticks <= 65536U){
		psc1 = 1U;
	}
	else{
		psc1 = (half_ticks + 65535U) / 65536U;
		if(psc1 > 65536U){//频率过低, 16 位 PSC/ARR 无法表示, 钳到极限
			psc1 = 65536U;
		}
	}
	arr1 = (half_ticks + (psc1 / 2U)) / psc1;
	if(arr1 > 65536U){
		arr1 = 65536U;
	}

	/* 配置定时器时基(覆盖 CubeMX): 向上计数、内部时钟、自动重装不预载 */
	CONFIG_SPK_HANDLE.Init.Prescaler = psc1 - 1U;
	CONFIG_SPK_HANDLE.Init.Period = arr1 - 1U;
	CONFIG_SPK_HANDLE.Init.CounterMode = TIM_COUNTERMODE_UP;
	CONFIG_SPK_HANDLE.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	CONFIG_SPK_HANDLE.Init.RepetitionCounter = 0U;
	CONFIG_SPK_HANDLE.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if(HAL_TIM_Base_Init(&CONFIG_SPK_HANDLE) != HAL_OK){
		printf("reSet spk tim base clk fail!!!\n");
		Error_Handler();
	}

	/* 输出比较翻转(频率输出)通道配置。
	 * Pulse(CCR) 仅决定翻转相位, 不影响频率与占空比; 取 0 使翻转与更新事件对齐。 */
	sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
	sConfigOC.Pulse = 0U;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	if(HAL_TIM_OC_ConfigChannel(&CONFIG_SPK_HANDLE, &sConfigOC, CONFIG_SPK_PWM_CHANNEL) != HAL_OK){
		printf("reSet spk time out freq fail!!!\n");
		Error_Handler();
	}

	/* 高级定时器(TIM1/TIM8)使能主输出 MOE, 否则 OC 无法输出到引脚 */
	if(sPlcSpeakerIsAdvanced(CONFIG_SPK_TIM) != 0U){
		__HAL_TIM_MOE_ENABLE(&CONFIG_SPK_HANDLE);
	}

	/* HAL_TIM_OC_ConfigChannel 会关闭 CCER 通道使能且不恢复;
	 * 若喇叭正在发声, 重新启动保证改频率后声音不中断。 */
	if(LoudspeakerEnable == true){
		SET_SPK_TIM_ON;
	}
}

inline void sPlcSpeakerFreq(int16_t freq){//设置蜂鸣器频率
	if(freq > CONFIG_BEEM_MAX_FREQ){
		freq = CONFIG_BEEM_MAX_FREQ;
	}
	if(freq < CONFIG_BEEM_MIN_FREQ){
		freq = CONFIG_BEEM_MIN_FREQ;
	}
	setSpeakerFreq((uint16_t)freq);
}

/* 音量听感映射表: 0~100 线性百分比 -> MCP41010 0~255 码值。
 * 人耳对响度的感知符合对数规律(韦伯-费希纳定律): 线性码值听起来
 * 前半段音量增长过快、后半段变化不明显。本表按指数曲线(等效 40dB
 * 动态范围)重新分配码值, 使每调整一格音量的听感增量近似相等。
 * 重新生成方法(Python):
 *   code[0]=0
 *   code[v]=round(255*10**((-40*(1-v/100))/20)), v=1..100
 * 若需更宽/更窄的动态范围, 修改 40 后重新生成本表。 */
static const uint8_t SpeakerVolumeMap[101] = {
	  0,   3,   3,   3,   3,   3,   3,   4,   4,   4,
	  4,   4,   4,   5,   5,   5,   5,   6,   6,   6,
	  6,   7,   7,   7,   8,   8,   8,   9,   9,  10,
	 10,  11,  11,  12,  12,  13,  13,  14,  15,  15,
	 16,  17,  18,  18,  19,  20,  21,  22,  23,  24,
	 26,  27,  28,  29,  31,  32,  34,  35,  37,  39,
	 40,  42,  44,  46,  49,  51,  53,  56,  58,  61,
	 64,  67,  70,  74,  77,  81,  84,  88,  93,  97,
	102, 106, 111, 117, 122, 128, 134, 140, 147, 154,
	161, 168, 176, 185, 193, 203, 212, 222, 233, 244,
	255
};

inline void sPlcSpeakerVolume(int16_t volume){//设置喇叭音量
	uint8_t code;
	if(volume < 0){
		volume = 0;
	}
	if(volume > CONFIG_BEEM_MAX_VOLUME){
		volume = CONFIG_BEEM_MAX_VOLUME;
	}
	if(LoudspeakerVolume != volume){
		code = SpeakerVolumeMap[volume];
		writeMcp41010(code);
		LoudspeakerVolume = (int8_t)volume;
	}
}
