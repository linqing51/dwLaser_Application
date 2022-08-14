//BUG 持续间断发声时出现声音短暂停顿问题原因未知
#include "sPlcMisc.h"
/*****************************************************************************/
static int16_t AimBrg = -1;
static int8_t RedLedBrg = -1;
static int8_t GreenLedBrg = -1;
static int8_t YellowLedBrg = -1;
/*****************************************************************************/
void softDelayMs(uint16_t ms){//软件延时
	uint32_t i;
	for(i = 0;i < 1000;i ++){
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	}
}
void UsbGpioReset(void){//模拟USB拔插动作并关闭VBUS供电
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
void SystemClock_Reset(void){//复位系统时钟
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
int16_t getAimBrightness(void){//获取瞄准光亮度
	return 0;
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
void setFanSpeed(int16_t speed){//设置风扇转速
}





void setTecDutyCycle(int16_t dc){//设置TEC导通占空比
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, dc);
		if(dc != 0){
			HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);//打开TIM
		}
		else{
			HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);//关闭TIM
		}

}
int16_t getTecDutyCycle(void){//获取TEC导通占空比
	return 0;
}
int16_t getFanSpeed(void){//获取风扇转速
	return 0;
}

void morseCodeDiag(uint8_t diag){//蜂鸣器诊断声音 摩尔斯电码
	//关闭USB VBUS
	switch(diag){
		case '0':{
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case '1':{
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		};
		case '2':{
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		};
		case '3':{
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case '4':{
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case '5':{
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		case '6':{
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		case '7':{	
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		case '8':{
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		case '9':{
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'A':{
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'B':{
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;			
		}
		case 'C':{
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'D':{
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'E':{
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'F':{
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'G':{
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'H':{
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;			
		}
		case 'I':{
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'J':{
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'K':{
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'L':{//．━ ．．
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'M':{//━ ━
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;HAL_Delay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;HAL_Delay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		default:break;
	}
	HAL_Delay(3000);
}
