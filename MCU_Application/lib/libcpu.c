/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "libcpu.h"
/*****************************************************************************/
uint32_t	UniqueId[3];//处理器序列号 
/*****************************************************************************/
void softDelayUs(uint32_t us){
	// 粗略估算：1us 大约需要 hclk_mhz 个周期
	// 这里的 0.9 是经验修正系数，用于补偿 Flash 预取和流水线带来的加速效应
	// 具体系数需根据实际示波器测量调整
	uint32_t loops = us * 168; 
	// 使用 volatile 防止优化
	volatile uint32_t count = loops;
	while(count--){
			__NOP(); // 插入空指令，强制消耗时钟周期
			__NOP(); // 可以多加几个来增加精度
	}
}

void softDelayMs(uint32_t ms){
  volatile uint32_t count = ms;
  while(count--){
    softDelayUs(1000);
  }
}

void tickCheckTask(void){//TICK 检测程序
  uint32_t tick_begin, tick_end; 
  tick_begin = HAL_GetTick();
  FLIP_TICK_LED;
  HAL_Delay(1000);
  tick_end = HAL_GetTick();
  FLIP_TICK_LED;
  // 计算实际间隔
  uint32_t real_ms = tick_end - tick_begin;
  // 串口打印数值
  printf("HAL TICK:%d ms\r\n", real_ms);
}

uint16_t cpuGetFlashSize(void){//获取处理器程序容量
#if defined(STM32F1xx)
	/* F1容量寄存器: 互联型F105/F107(DEV_ID=0x411)在0x1FFFF7CC, 其余F1在0x1FFFF7E0 */
	if((DBGMCU->IDCODE & 0xFFFU) == 0x411U){
		return *(volatile uint16_t*)(0x1FFFF7CC);
	}
	return *(volatile uint16_t*)(0x1FFFF7E0);
#else
	return *(volatile uint16_t*)(0x1FFF7A22);
#endif
}

void readStm32UniqueID(void){//获取处理器唯一序列号        
	UniqueId[0] = *(volatile uint32_t*)(0x1FFF7A10);
	UniqueId[1] = *(volatile uint32_t*)(0x1FFF7A14);
	UniqueId[2] = *(volatile uint32_t*)(0x1FFF7A18);
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
	//NVIC_SystemReset();
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





