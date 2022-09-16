#include "sPlcMisc.h"
/*****************************************************************************/
void softDelayMs(uint16_t ms){//软件延时
	uint32_t i;
	for(i = 0;i < 1000;i ++){
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	}
}
uint16_t cpuGetFlashSize(void){//获取处理器程序容量
   return *(volatile uint16_t*)(0x1FFF7A22);
}
void readStm32UniqueID(void){//获取处理器唯一序列号        
  *((uint32_t*)(&NVRAM0[SPREG_CHID0_L])) = *(volatile uint32_t*)(0x1FFF7A10);
  *((uint32_t*)(&NVRAM0[SPREG_CHID1_L])) = *(volatile uint32_t*)(0x1FFF7A14);
  *((uint32_t*)(&NVRAM0[SPREG_CHID2_L])) = *(volatile uint32_t*)(0x1FFF7A18);
}


void IWDG_Configuration(void){
	
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
void sPlcEnableIsr(void){//使能SPLC中断
}
void sPlcDisableIsr(void){//关闭SPLC中断
}
uint8_t sPlcSaveUdisk(void){//将FDRAM写入USB DISK
	//返回 1:写入成功 0:写入失败
//	FRESULT retUsbH;
//	FATFS	USBH_fatfs;
//	FIL saveFile;//FATFS File Object 下载完成信息
//	FILINFO FileInfo;//FATFS 文件信息
//	char fileName[64];
//	retUsbH = f_mount(&USBH_fatfs, FATFS_ROOT, 0);
//	if(retUsbH != FR_OK){//挂载U盘失败
//		printf("Bootloader:Mount Fatfs errror:%d!\n", retUsbH);
//		return false
//	}
//	else{//挂载U盘成功
//		printf("Bootloader:Mount Fatfs sucess!\n");
//	}
//	sprintf(fileName, "/las.cfg");
//	retUsbH = f_open(&saveFile, CFG_FIRMWARE_FILENAME, FA_CREATE_ALWAYS | FA_READ | FA_WRITE);//读取完成信息文件
//	if(retUsbH != FR_OK){//读取失败跳过固件更新直接运行程序
//		printf("BootLoader:Open %s fail,ECODE=0x%02XH\n", CFG_FIRMWARE_FILENAME, retUsbH);
//	}
//	else{//读取成功检查文件内容
//		f_lseek(&CfgFile, 0);//读取指针移动到开头
//		if(f_write(&CfgFile, fileBuff, 3, (void *)&bwByte) != FR_OK){
//				bootLoadFailHandler(BT_FAIL_WRITE_CFG);
//			}
//			f_close(&CfgFile);
//	}
	return 0;
}
uint8_t sPlcLoadUdisk(void){//从USB DISK载入FDRAM
	//返回 1:写入成功 0:写入失败
	return 0;
}

uint16_t fitLaserToCode(uint8_t ch, int16_t power, deviceConfig_t *pcfg){//功率->DAC CODE 使用校正表
	fp64_t fpower, fout, fk, fb;
	int16_t pmax, pmin;
	uint16_t *pCal;
	uint16_t out;
	switch(ch){
		case 0:{
			pmax = CONFIG_MAX_LASERPOWER_CH0;
			pmin = CONFIG_MIN_LASERPOWER_CH0;
			pCal = deviceConfig.calibrationPwr0;
			break;
		}
		case 1:{
			pmax = CONFIG_MAX_LASERPOWER_CH1;
			pmin = CONFIG_MIN_LASERPOWER_CH1;
			pCal = deviceConfig.calibrationPwr1;
			break;
		}
		case 2:{
			pmax = CONFIG_MAX_LASERPOWER_CH2;
			pmin = CONFIG_MIN_LASERPOWER_CH2;
			pCal = deviceConfig.calibrationPwr2;
			break;
		}
		case 3:{
			pmax = CONFIG_MAX_LASERPOWER_CH3;
			pmin = CONFIG_MIN_LASERPOWER_CH3;
			pCal = deviceConfig.calibrationPwr3;
			break;
		}
		default:{
			break;
		}
	}
	if(power > pmax){
		power = pmax;
	}
	if(power < pmin){
		power = pmin;
	}
	fpower = (fp32_t)power;
	printf("%s,%d,%s:Calibration input power = %d\n", __FILE__, __LINE__, __func__, power);
	printf("%s,%d,%s:Calibration max power = %d\n", __FILE__, __LINE__, __func__, pmax);
	printf("%s,%d,%s:Calibration min power = %d\n", __FILE__, __LINE__, __func__, pmin);
	if(LDB(R_CALIBRATION_MODE)){//正模式
		//通过校正表计算DAC值
		if(power > 0 && (power <= pCal[0])){
			fk = pCal[0] / 0.1F;
			fb = pCal[0] - fk * 0.1;
		}
		else if((power > pCal[0]) && (power <= pCal[1])){
			fk = (pCal[1] - pCal[0]) / 0.1F;
			fb = pCal[1] - fk * 0.2;
		}
		else if((power > pCal[1]) && (power <= pCal[2])){
			fk = (pCal[2] - pCal[1]) / 0.1F;
			fb = pCal[2] - fk * 0.3;
		}
		else if((power > pCal[2]) && (power <= pCal[3])){
			fk = (pCal[3] - pCal[2]) / 0.1F;
			fb = pCal[2] - fk * 0.4;
		}
		else if((power > pCal[3]) && (power <= pCal[4])){
			fk = (pCal[4] - pCal[3]) / 0.1F;
			fb = pCal[3] - fk * 0.5;
		}
		else if((power > pCal[4]) && (power <= pCal[5])){
			fk = (pCal[5] - pCal[4]) / 0.1F;
			fb = pCal[4] - fk * 0.6;
		}
		else if((power > pCal[5]) && (power <= pCal[6])){
			fk = (pCal[6] - pCal[5]) / 0.1F;
			fb = pCal[5] - fk * 0.7;
		}
		else if((power > pCal[6]) && (power <= pCal[7])){
			fk = (pCal[7] - pCal[6]) / 0.1F;
			fb = pCal[6] - fk * 0.8;
		}
		else if((power > pCal[7]) && (power <= pCal[8])){
			fk = (pCal[8] - pCal[7]) / 0.1F;
			fb = pCal[8] - fk * 0.9;
		}
		else if((power > pCal[8]) && (power <= pCal[9])){
			fk = (pCal[9] - pCal[8]) / 0.1F;
			fb = pCal[9] - fk * 1.0;
		}
		fout = (power - fb) / fk;
		printf("%s,%d,%s:Enable calibration mode\n", __FILE__, __LINE__, __func__);
		printf("%s,%d,%s:Calibration fK=%f, fB=%f\n", __FILE__, __LINE__, __func__, fk, fb);
		printf("%s,%d,%s:Calibration fOut=%f\n", __FILE__, __LINE__, __func__, fout);
	}
	else{//功率校正模式 ->按等比输出DAC值
		printf("%s,%d,%s:Disable calibration mode\n", __FILE__, __LINE__, __func__);
		fout = fpower / pmax;			
	}
	fout = fout * 4095.0F;
	if(fout > 4095.0F){
		fout = 4095;
	}
	if(fout < 0.0F){
		fout = 0;
	}
	out = (uint16_t)fout;
	printf("%s,%d,%s:Calibration fOut=%d\n", __FILE__, __LINE__, __func__, out);
	return out;
}




