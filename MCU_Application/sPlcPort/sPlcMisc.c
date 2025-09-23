#include "sPlc.h"
#include "boardConfig.h"
#include "appConfig.h"
#include "usbh_core.h"
/*****************************************************************************/
static int16_t FanSpeed = -1;
/*****************************************************************************/
void softDelayMs(uint16_t ms){//软件延时
    // 168MHz主频下，每个循环约4个指令周期
    // 计算每个毫秒需要的循环次数：(168,000,000 周期/秒) / (1000 毫秒/秒) / 4 周期/循环 = 42000
    const uint32_t cycles_per_ms = 42000;
    
    // 使用volatile关键字防止编译器优化掉空循环
    volatile uint32_t count;
    
    while (ms--)
    {
        count = cycles_per_ms;
        while (count--);
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
	vTaskDelay(delayMs);
}

void setFanSpeed(int16_t speed){//设置风扇转速
	if(FanSpeed != speed){
		if(speed > CONFIG_FAN_MAX_DC){
			speed = CONFIG_FAN_MAX_DC;
		}
		if(speed < CONFIG_FAN_MIN_DC){
			speed = CONFIG_FAN_MIN_DC;
		}
		__HAL_TIM_SET_COMPARE(&CONFIG_FAN_TIM_HANDLE, CONFIG_FAN_PWM_CHANNEL, speed);
		if(speed != 0){
			HAL_TIM_PWM_Start(&CONFIG_FAN_TIM_HANDLE, CONFIG_FAN_PWM_CHANNEL);//打开TIM
		}
		else{
			HAL_TIM_PWM_Stop(&CONFIG_FAN_TIM_HANDLE, CONFIG_FAN_PWM_CHANNEL);//关闭TIM
		}

		if(speed <= 0){
			SET_FAN_OFF;
		}
		else if(speed >0 && speed < 100){
			SET_FAN_ON;
			SET_FAN_TIM_PWM(speed);
		}
		else if(speed >= 100){
			SET_FAN_ON;
			SET_FAN_TIM_PWM(100);
		}
		FanSpeed = speed;
		printf("%s,%d,%s:set fan:%d\n",__FILE__, __LINE__, __func__, speed);	
	}
}

void morseCodeDiag(uint8_t diag){//蜂鸣器诊断声音 摩尔斯电码
	//关闭USB VBUS
	switch(diag){
		case '0':{
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case '1':{
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		};
		case '2':{
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		};
		case '3':{
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case '4':{
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case '5':{
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		case '6':{
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		case '7':{	
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		case '8':{
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		case '9':{
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'A':{
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'B':{
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;			
		}
		case 'C':{
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'D':{
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'E':{
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'F':{
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'G':{
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'H':{
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;			
		}
		case 'I':{
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'J':{
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'K':{
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'L':{//．━ ．．
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//.
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_SHORT_TIME);SET_RED_LED_OFF;
			break;
		}
		//
		case 'M':{//━ ━
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'N':{//━ ━
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'O':{//━ ━
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'P':{//━ ━
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'Q':{//━ ━
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'R':{//━ ━
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'S':{//━ ━
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'T':{//━ ━
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'U':{//━ ━
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'V':{//━ ━
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'W':{//━ ━
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'X':{//━ ━
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'Y':{//━ ━
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		case 'Z':{//━ ━
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;vTaskDelay(CONFIG_MORSECODE_SPACE_TIME);
			//-
			SET_RED_LED_ON;vTaskDelay(CONFIG_MORSECODE_LONG_TIME);SET_RED_LED_OFF;
			break;
		}
		default:break;
	}
	vTaskDelay(3000);
}

uint32_t getOriginBootloadCrc(void){//计算MCU Bootload CRC32
	uint8_t val;
	uint32_t i;
	uint32_t crc32;
	crc32Clear();
	for(i = BOOTLOADER_FLASH_START_ADDRESS;i < BOOTLOADER_FLASH_END_ADDRESS;i ++){
		val = *(__IO uint8_t*)(i);
		crc32 = crc32CalculateAdd(val);//CRC32计算连续字节
	}
	return crc32;	
}
uint32_t getOriginAppCrc(void){//计算MCU APP CRC32
	uint8_t val;
	uint32_t i;
	uint32_t crc32;
	crc32Clear();
	for(i = APPLICATION_FLASH_START_ADDRESS;i < APPLICATION_FLASH_END_ADDRESS;i ++){
		val = *(__IO uint8_t*)(i);
		crc32 = crc32CalculateAdd(val);//CRC32计算连续字节
	}
	return crc32;	
}

void loadDeviceConfig(void){//从EPROM载入配置文件
	uint32_t crc32_eprom_cfg, crc32_cfg;
	epromRead(CONFIG_EPROM_CONFIG_START, (uint8_t*)&deviceConfig, sizeof(deviceConfig));//从EPROM载入设备配置
	epromReadDword(CONFIG_EPROM_CFG_CRC, &crc32_eprom_cfg);
	crc32_cfg = HAL_CRC_Calculate(&hcrc,(uint32_t *)&deviceConfig, (sizeof(deviceConfig) / 4));
	if(crc32_eprom_cfg != crc32_cfg){//校验码错误使用默认配置
		printf("%s,%d,%s:load device config crc fail!!!\n",__FILE__, __LINE__, __func__);
		printf("%s,%d,%s:using default device config!\n",__FILE__, __LINE__, __func__);
		
#if defined(MODLE_M1470_640_10_15_02_D200_22_G5W_PK)//1470 V1
		deviceConfig.calibrationPwr0[0] = 9;
		deviceConfig.calibrationPwr0[1] = 28;
		deviceConfig.calibrationPwr0[2] = 48;
		deviceConfig.calibrationPwr0[3] = 68;
		deviceConfig.calibrationPwr0[4] = 87;
		deviceConfig.calibrationPwr0[5] = 105;
		deviceConfig.calibrationPwr0[6] = 120;
		deviceConfig.calibrationPwr0[7] = 133;
		deviceConfig.calibrationPwr0[8] = 144;
		deviceConfig.calibrationPwr0[9] = 153;
		deviceConfig.fiberDetect = CONFIG_FIBER_PD_THRESHOLD;		
#endif	
#if defined(MODLE_M1470_980_640_10_15_35_05_D200_22_G5W_PK) //1470-980 V1
		//1470nm
		deviceConfig.calibrationPwr0[0] = 6;
		deviceConfig.calibrationPwr0[1] = 21;
		deviceConfig.calibrationPwr0[2] = 36;
		deviceConfig.calibrationPwr0[3] = 52;
		deviceConfig.calibrationPwr0[4] = 68;
		deviceConfig.calibrationPwr0[5] = 85;
		deviceConfig.calibrationPwr0[6] = 99;
		deviceConfig.calibrationPwr0[7] = 113;
		deviceConfig.calibrationPwr0[8] = 125;
		deviceConfig.calibrationPwr0[9] = 150;
		//980nm
		deviceConfig.calibrationPwr1[0] = 9;
		deviceConfig.calibrationPwr1[1] = 27;
		deviceConfig.calibrationPwr1[2] = 45;
		deviceConfig.calibrationPwr1[3] = 62;
		deviceConfig.calibrationPwr1[4] = 79;
		deviceConfig.calibrationPwr1[5] = 96;
		deviceConfig.calibrationPwr1[6] = 112;
		deviceConfig.calibrationPwr1[7] = 127;
		deviceConfig.calibrationPwr1[8] = 140;
		deviceConfig.calibrationPwr1[9] = 150;
		deviceConfig.fiberDetect = CONFIG_FIBER_PD_THRESHOLD;
#endif

#if defined(MODLE_M1470_980_640_10_15_15_02_D200_22_G5W_PK)//1470-980-650 V2
		deviceConfig.calibrationPwr0[0] = 9;
		deviceConfig.calibrationPwr0[1] = 28;
		deviceConfig.calibrationPwr0[2] = 48;
		deviceConfig.calibrationPwr0[3] = 68;
		deviceConfig.calibrationPwr0[4] = 87;
		deviceConfig.calibrationPwr0[5] = 105;
		deviceConfig.calibrationPwr0[6] = 120;
		deviceConfig.calibrationPwr0[7] = 133;
		deviceConfig.calibrationPwr0[8] = 144;
		deviceConfig.calibrationPwr0[9] = 153;
	
		deviceConfig.calibrationPwr1[0] = 9;
		deviceConfig.calibrationPwr1[1] = 28;
		deviceConfig.calibrationPwr1[2] = 48;
		deviceConfig.calibrationPwr1[3] = 68;
		deviceConfig.calibrationPwr1[4] = 87;
		deviceConfig.calibrationPwr1[5] = 105;
		deviceConfig.calibrationPwr1[6] = 120;
		deviceConfig.calibrationPwr1[7] = 133;
		deviceConfig.calibrationPwr1[8] = 144;
		deviceConfig.calibrationPwr1[9] = 153;
		deviceConfig.fiberDetect = CONFIG_FIBER_PD_THRESHOLD;
#endif

#if defined(MODLE_M12_1920_10_400S)
		deviceConfig.calibrationPwr0[0] = 6;
		deviceConfig.calibrationPwr0[1] = 20;
		deviceConfig.calibrationPwr0[2] = 32;
		deviceConfig.calibrationPwr0[3] = 45;
		deviceConfig.calibrationPwr0[4] = 56;
		deviceConfig.calibrationPwr0[5] = 66;
		deviceConfig.calibrationPwr0[6] = 72;
		deviceConfig.calibrationPwr0[7] = 81;
		deviceConfig.calibrationPwr0[8] = 87;
		deviceConfig.calibrationPwr0[9] = 100;
		deviceConfig.fiberDetect = CONFIG_FIBER_PD_THRESHOLD;
#endif		

		deviceConfig.mfg_year = 2025;
		deviceConfig.mfg_month = 9;
		deviceConfig.mfg_day = 14;
			
		sprintf(deviceConfig.serialNumber, "XXXX-XXXX");
		deviceConfig.greenLedDc = CONFIG_GREEN_LED_DEFAULT_DC;
		deviceConfig.redLedDc = CONFIG_RED_LED_DEFAULT_DC;
		deviceConfig.blueLedDc = CONFIG_BLUE_LED_DEFAULT_DC;
		deviceConfig.aimGain = CONFIG_AIM_DEFAULT_GAIN;
		deviceConfig.fiberDetect = CONFIG_FIBER_PD_THRESHOLD;
		deviceConfig.normalOpenInterLock = 1;//默认常开联锁 
		saveDeviceConfig();
	}
	else{
		printf("%s,%d,%s:load device config done...\n",__FILE__, __LINE__, __func__);
	}
}
void saveDeviceConfig(void){//将配置写入EPROM
	uint32_t crc32_cfg;
	epromWrite(CONFIG_EPROM_CONFIG_START, (uint8_t*)&deviceConfig, sizeof(deviceConfig));//写入EPROM	
	crc32_cfg = HAL_CRC_Calculate(&hcrc,(uint32_t *)&deviceConfig, (sizeof(deviceConfig) / 4));
	epromWriteDword(CONFIG_EPROM_CFG_CRC, &crc32_cfg);//写入校验值
	printf("%s,%d,%s:save device config to eprom done...(CFG CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_cfg);
}



