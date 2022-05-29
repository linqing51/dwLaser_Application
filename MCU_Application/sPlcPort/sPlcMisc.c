//BUG 持续间断发声时出现声音短暂停顿问题原因未知
#include "sPlcMisc.h"
/*****************************************************************************/
extern UART_HandleTypeDef huart1;//调试
extern TIM_HandleTypeDef htim3;//RGB LED PWM计时器
extern TIM_HandleTypeDef htim2;//指示光PWM计时器
extern TIM_HandleTypeDef htim7;//DAC DMA 计时器
extern TIM_HandleTypeDef htim5;
extern DAC_HandleTypeDef hdac;
static int16_t AimBrg = -1;
static int8_t LoudspeakerEnable = -1;//喇叭使能状态
static int16_t LoudspeakerFreq = -1;//喇叭频率
static int8_t LoudspeakerVolume = -1;//喇叭音量
static int8_t RedLedBrg = -1;
static int8_t GreenLedBrg = -1;
static int8_t YellowLedBrg = -1;
uint16_t audioSineTable[256] = {0};
/*****************************************************************************/
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
void setLoudspeakerDisable(void){//关闭喇叭数据流
	if(LoudspeakerEnable != false){
		HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_SET);
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
		HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_RESET);
		HAL_TIM_Base_Start(&htim7);
		HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t *)audioSineTable, 256, DAC_ALIGN_12B_R);
#if CONFIG_DEBUG_SPK == 1
		printf("%s,%d,%s:set loadspeaker on!\n",__FILE__, __LINE__, __func__);
#endif
		LoudspeakerEnable = true;
	}
}
static void softDelayMs(uint16_t ms){//软件延时
	uint32_t i;
	for(i = 0;i < 1000;i ++){
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	}
}
static void UsbGpioReset(void){//模拟USB拔插动作并关闭VBUS供电
	GPIO_InitTypeDef GPIO_InitStruct;
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	/*Configure GPIO pin : PA12 */
	GPIO_InitStruct.Pin = GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);                                            
	softDelayMs(100);
	//先把PA12拉低再拉高，利用D+模拟USB的拔插动作   
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
	softDelayMs(100);
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_12);
	__HAL_RCC_GPIOA_CLK_DISABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_8, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
	softDelayMs(200);
	HAL_GPIO_DeInit(GPIOG, GPIO_PIN_12);
	__HAL_RCC_GPIOG_CLK_DISABLE();	
	__HAL_RCC_USB_OTG_FS_CLK_DISABLE();//关闭USB时钟
	HAL_NVIC_DisableIRQ(OTG_FS_IRQn);//关闭USB 中断
	HAL_NVIC_ClearPendingIRQ(OTG_FS_IRQn);//清楚 USB 中断标志
}
static void SystemClock_Reset(void){//复位系统时钟
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	__HAL_RCC_BACKUPRESET_RELEASE();
	__HAL_RCC_BACKUPRESET_FORCE();
	__HAL_RCC_PLL_DISABLE();
	__HAL_RCC_HSI_DISABLE();
	/** Configure the main internal regulator output voltage */
	__HAL_RCC_PWR_CLK_DISABLE();
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the CPU, AHB and APB busses clocks */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK){
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK){
		Error_Handler();
	}
}
void resetInit(void){//复位后初始化
	HAL_DeInit();
	//复位RCC时钟
	SystemClock_Reset();
	UsbGpioReset();
	__enable_irq();
}
void delayMs(uint32_t delayMs){//SPLC 阻塞延时
	HAL_Delay(delayMs);
}
void enableSplcIsr(void){//使能SPLC中断
}
void disableSplcIsr(void){//关闭SPLC中断
}
void enterSplcIsr(void){
}
void exitSplcIsr(void){
}
void setAimFreq(int16_t freq){//设置指示光PWM频率
	if(freq < 60){
		freq = 60;
	}
	if(freq > 500){
		freq = 500;
	}
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = (HAL_RCC_GetPCLK1Freq() * 2 / 256 / freq);
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 256;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_PWM_Init(&htim2) != HAL_OK){
		Error_Handler();
	}
#if CONFIG_DEBUG_AIM == 1
		printf("%s,%d,%s:set aim pwm freq:%d\n",__FILE__, __LINE__, __func__, freq);
#endif
	HAL_TIM_Base_Start(&htim2);
}
void setLedFreq(int16_t freq){//设置LED PWM频率	
	if(freq < 60){
		freq = 60;
	}
	if(freq > 500){
		freq = 500;
	}
	htim3.Instance = TIM3;
	htim3.Init.Prescaler = (HAL_RCC_GetPCLK1Freq() * 2 / 256 / freq);
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 256;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_PWM_Init(&htim3) != HAL_OK){
		Error_Handler();
	}
#if CONFIG_DEBUG_LED == 1
	printf("%s,%d,%s:set led pwm freq:%d\n",__FILE__, __LINE__, __func__, freq);
#endif
	HAL_TIM_Base_Start(&htim3);
}
void setFanFreq(int16_t freq){//设置FAN PWM频率
	
	
}
void initLoudspeaker(void){//喇叭初始化
	HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_SET);
	setLoudspeakerVolume(NVRAM0[DM_BEEM_VOLUME]);
	RRES(SPCOIL_BEEM_ENABLE);
	setLoudspeakerDisable();
	setLoudspeakerFreq(CONFIG_SPLC_DEFAULT_SPK_FREQ);
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
			ftemp = 1.0F + arm_sin_f32(i * piStep + PI + (PI /2));
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
void setAimBrightness(int16_t brg){//设置瞄准光亮度
	uint16_t temp;
	if(AimBrg != brg){
		if(brg > 100){
			brg = 100;
		}
		if(brg < 0){
			brg = 0;
		}
		temp = 255 * brg / 100;
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, temp);
		if(brg != 0){
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);//打开TIM
		}
		else{
			HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);//关闭TIM
		}
		AimBrg = brg;
	}
#if CONFIG_DEBUG_AIM == 1
	printf("%s,%d,%s:set aim brightness:%d\n",__FILE__, __LINE__, __func__, brg);
#endif	
}
void setYellowLedBrightness(int16_t brg){//设置蓝灯亮度
	uint16_t temp;
	if(YellowLedBrg != brg){
		if(brg > 100){
			brg = 100;
		}
		if(brg < 0){
			brg = 0;
		}
		temp = 255 * brg / 100;
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, temp);
		if(brg != 0){
			HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//打开TIM
		}
		else{
			HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);//关闭TIM
		}
		YellowLedBrg = brg;
	}
#if CONFIG_DEBUG_LED == 1
	printf("%s,%d,%s:1:%d\n",__FILE__, __LINE__, __func__, brg);
#endif
}
void setRedLedBrightness(int16_t brg){//设置红灯亮度
	uint16_t temp;
	if(RedLedBrg != brg){
		if(brg > 100){
			brg = 100;
		}
		if(brg < 0){
			brg = 0;
		}
		temp = 255 * brg / 100;
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, temp);
		if(brg != 0){
			HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//打开TIM
		}
		else{
			HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);//关闭TIM
		}
		RedLedBrg = brg;
	}
#if CONFIG_DEBUG_LED == 1
	printf("%s,%d,%s:set red led brightness:%d\n",__FILE__, __LINE__, __func__, brg);
#endif	
}
void setGreenLedBrightness(int16_t brg){//设置绿灯亮度
	uint16_t temp;
	if(GreenLedBrg != brg){
		if(brg > 100){
			brg = 100;
		}
		if(brg < 0){
			brg = 0;
		}
		temp = 255 * brg / 100;
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, temp);
		if(brg != 0){
			HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);//打开TIM
		}
		else{
			HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);//关闭TIM
		}
		GreenLedBrg = brg;
	}
#if CONFIG_DEBUG_LED == 1
	printf("%s,%d,%s:set green led brightness:%d\n",__FILE__, __LINE__, __func__, brg);
#endif
}
void sPlcLoudspeakerLoop(void){//蜂鸣器轮询
	if(LD(SPCOIL_BEEM_ENABLE)){
		setLoudspeakerVolume(NVRAM0[SPREG_BEEM_VOLUME]);
		switch(NVRAM0[SPREG_BEEM_MODE]){//模式
			case BEEM_MODE_0:{
				if(LDB(SPCOIL_BEEM_BUSY)){
					setLoudspeakerEnable();//启动音频
					SSET(SPCOIL_BEEM_BUSY);//启动蜂鸣器
				}
				break;
			}
			case BEEM_MODE_1:{//模式1 声光同步
				if(GET_LASER_PWM0 || GET_LASER_PWM1 || GET_LASER_PWM2 || GET_LASER_PWM3){//LT3763 PWM ON
					if(LDB(SPCOIL_BEEM_BUSY)){//如果PWM无输出-> 有输出
						setLoudspeakerEnable();//启动音频
						SSET(SPCOIL_BEEM_BUSY);//启动蜂鸣器
					}
				}
				else{
					if(LD(SPCOIL_BEEM_BUSY)){
						setLoudspeakerDisable();//启动音频
						RRES(SPCOIL_BEEM_BUSY);//关闭蜂鸣器	
					}
				}
				break;
			}
			case BEEM_MODE_2:{//模式2 长间隔 激光发射音		
				if(NVRAM0[SPREG_BEEM_COUNTER] >= 0 && NVRAM0[SPREG_BEEM_COUNTER] < 20){//1
					setLoudspeakerEnable();//启动音频
					SSET(SPCOIL_BEEM_BUSY);//启动蜂鸣器
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 20 && NVRAM0[SPREG_BEEM_COUNTER] < 120){//0
					setLoudspeakerDisable();//停止音频
					RRES(SPCOIL_BEEM_BUSY);//关闭蜂鸣器
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 120){
					NVRAM0[SPREG_BEEM_COUNTER] = -1;
				}
				break;
			}
			case BEEM_MODE_3:{//模式3 滴滴两下一停 报警音
				if(NVRAM0[SPREG_BEEM_COUNTER] >= 0 && NVRAM0[SPREG_BEEM_COUNTER] < 50){//1
					setLoudspeakerEnable();//启动音频
					SSET(SPCOIL_BEEM_BUSY);//启动蜂鸣器
					
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 50 && NVRAM0[SPREG_BEEM_COUNTER] < 100){//0
					setLoudspeakerDisable();//关闭音频
					RRES(SPCOIL_BEEM_BUSY);//关闭蜂鸣器
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 100 && NVRAM0[SPREG_BEEM_COUNTER] < 150){//1
					setLoudspeakerEnable();//启动音频
					SSET(SPCOIL_BEEM_BUSY);//启动蜂鸣器
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 150 && NVRAM0[SPREG_BEEM_COUNTER] < 250){//0
					setLoudspeakerDisable();//关闭音频
					RRES(SPCOIL_BEEM_BUSY);//关闭蜂鸣器
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 250){//停1秒
					NVRAM0[SPREG_BEEM_COUNTER] = -1;
				}
				break;
			}
			default:break;
		}
	}
	else{
		setLoudspeakerDisable();//关闭音频
		RRES(SPCOIL_BEEM_BUSY);//关闭蜂鸣器
		NVRAM0[SPREG_BEEM_COUNTER]  = 0;
	}
}
void sPlcAimLoop(void){//AIM轮询程序
	if(LDP(SPCOIL_AIM_ENABEL) && (NVRAM0[DM_AIM_BRG] > 0)){
		setAimBrightness(NVRAM0[DM_AIM_BRG]);
		SSET(SPCOIL_AIM_BUSY);
	}
	if(LDN(SPCOIL_AIM_ENABEL)){
		setAimBrightness(0);
		RRES(SPCOIL_AIM_BUSY);
	}
}

void sPlcAutoFanLoop(void){//风扇速轮询程序
	if(NVRAM0[SPREG_LAS_FAN_SPEED] > 0 && NVRAM0[SPREG_LAS_FAN_SPEED] < CONFIG_SPLC_FAN_MIN_PWM){
		NVRAM0[SPREG_LAS_FAN_SPEED] = CONFIG_SPLC_FAN_MIN_PWM;
	}

	if(NVRAM0[SPREG_LAS_FAN_SPEED] <= 0){//风扇速度小于0
		HAL_GPIO_WritePin(LAS_FAN_GPIO_Port, LAS_FAN_Pin, GPIO_PIN_RESET);
	}
	else{
		HAL_GPIO_WritePin(LAS_FAN_GPIO_Port, LAS_FAN_Pin, GPIO_PIN_SET);
	}
/*
	uint8_t lasFanPwm;
	if(NVRAM0[SPREG_LAS_FAN_SPEED] <= 0){
		NVRAM0[SPREG_LAS_FAN_SPEED] = 0;
	}
	if(NVRAM0[SPREG_LAS_FAN_SPEED] >= 100){
		NVRAM0[SPREG_LAS_FAN_SPEED] = 100;
	}
	if(NVRAM0[SPREG_LAS_FAN_SPEED] > 0){
		lasFanPwm = NVRAM0[SPREG_LAS_FAN_SPEED] * 255 / 100;
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, lasFanPwm);
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);//打开TIM
	}
	else{
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);//关闭TIM
	}
#if CONFIG_DEBUG_FAN == 1
	printf("%s,%d,%s:set laser fan pwm,:%d\n",__FILE__, __LINE__, __func__, lasFanPwm);
#endif	
*/
}
//加入以下代码,支持printf函数,而不需要选择MicroLIB
#pragma import(__use_no_semihosting)
//标准库需要的支持函数
struct __FILE{
	int handle;
};
FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x){
	x = x;
}

void _ttywrch(int ch){
	ch = ch;
}

//重定义fputc函数
int fputc(int ch, FILE *f){
	uint8_t txDat;
	txDat = ch & 0xFF;
	HAL_UART_Transmit(&huart1, &txDat , 1, 100);
	return ch;
}


