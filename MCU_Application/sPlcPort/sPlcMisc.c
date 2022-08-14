//BUG ������Ϸ���ʱ������������ͣ������ԭ��δ֪
#include "sPlcMisc.h"
/*****************************************************************************/
static int16_t AimBrg = -1;
static int8_t RedLedBrg = -1;
static int8_t GreenLedBrg = -1;
static int8_t YellowLedBrg = -1;
/*****************************************************************************/
void softDelayMs(uint16_t ms){//�����ʱ
	uint32_t i;
	for(i = 0;i < 1000;i ++){
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	}
}
void UsbGpioReset(void){//ģ��USB�β嶯�����ر�VBUS����
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
	//�Ȱ�PA12���������ߣ�����D+ģ��USB�İβ嶯��   
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
	__HAL_RCC_USB_OTG_FS_CLK_DISABLE();//�ر�USBʱ��
	HAL_NVIC_DisableIRQ(OTG_FS_IRQn);//�ر�USB �ж�
	HAL_NVIC_ClearPendingIRQ(OTG_FS_IRQn);//��� USB �жϱ�־
}
void SystemClock_Reset(void){//��λϵͳʱ��
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
void resetInit(void){//��λ���ʼ��
	HAL_DeInit();
	//��λRCCʱ��
	SystemClock_Reset();
	UsbGpioReset();
	__enable_irq();
}
void delayMs(uint32_t delayMs){//SPLC ������ʱ
	HAL_Delay(delayMs);
}
void enableSplcIsr(void){//ʹ��SPLC�ж�
}
void disableSplcIsr(void){//�ر�SPLC�ж�
}
void enterSplcIsr(void){
}
void exitSplcIsr(void){
}
void setAimFreq(int16_t freq){//����ָʾ��PWMƵ��
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
void setLedFreq(int16_t freq){//����LED PWMƵ��	
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
void setFanFreq(int16_t freq){//����FAN PWMƵ��
	
	
}
void setAimBrightness(int16_t brg){//������׼������
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
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);//��TIM
		}
		else{
			HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);//�ر�TIM
		}
		AimBrg = brg;
	}
#if CONFIG_DEBUG_AIM == 1
	printf("%s,%d,%s:set aim brightness:%d\n",__FILE__, __LINE__, __func__, brg);
#endif	
}
int16_t getAimBrightness(void){//��ȡ��׼������
	return 0;
}
void setYellowLedBrightness(int16_t brg){//������������
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
			HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//��TIM
		}
		else{
			HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);//�ر�TIM
		}
		YellowLedBrg = brg;
	}
#if CONFIG_DEBUG_LED == 1
	printf("%s,%d,%s:1:%d\n",__FILE__, __LINE__, __func__, brg);
#endif
}
void setRedLedBrightness(int16_t brg){//���ú������
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
			HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//��TIM
		}
		else{
			HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);//�ر�TIM
		}
		RedLedBrg = brg;
	}
#if CONFIG_DEBUG_LED == 1
	printf("%s,%d,%s:set red led brightness:%d\n",__FILE__, __LINE__, __func__, brg);
#endif	
}
void setGreenLedBrightness(int16_t brg){//�����̵�����
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
			HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);//��TIM
		}
		else{
			HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);//�ر�TIM
		}
		GreenLedBrg = brg;
	}
#if CONFIG_DEBUG_LED == 1
	printf("%s,%d,%s:set green led brightness:%d\n",__FILE__, __LINE__, __func__, brg);
#endif
}
void setFanSpeed(int16_t speed){//���÷���ת��
}





void setTecDutyCycle(int16_t dc){//����TEC��ͨռ�ձ�
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, dc);
		if(dc != 0){
			HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);//��TIM
		}
		else{
			HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);//�ر�TIM
		}

}
int16_t getTecDutyCycle(void){//��ȡTEC��ͨռ�ձ�
	return 0;
}
int16_t getFanSpeed(void){//��ȡ����ת��
	return 0;
}

void morseCodeDiag(uint8_t diag){//������������� Ħ��˹����
	//�ر�USB VBUS
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
		case 'L':{//���� ����
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
		case 'M':{//�� ��
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
