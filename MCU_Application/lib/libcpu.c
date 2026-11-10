/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "libcpu.h"
/*****************************************************************************/
uint32_t	UniqueId[3];//处理器序列号 
/*****************************************************************************/
/* 初始化 DWT 周期计数器。
 * DWT 是 Cortex-M3/M4 内核的标准调试单元, 其 CYCCNT 对每个 HCLK 周期
 * 自增 1, 属于硬件周期计数: 用它做忙等不依赖 Flash 等待周期、指令流水线
 * 或编译器优化等级, 精度可达单周期。STM32F1(Cortex-M3)、F4(Cortex-M4)均内置。 */
static uint8_t s_dwt_inited = 0U;
static void softDelayInit(void){
	if(s_dwt_inited == 0U){
		CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;//使能 DWT/ITM 跟踪
		DWT->CYCCNT = 0U;
		DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;           //使能周期计数器
		s_dwt_inited = 1U;
	}
}

void softDelayUs(uint32_t us){
	uint32_t hclk;
	uint32_t cycles;

	hclk = HAL_RCC_GetHCLKFreq();//动态获取当前 HCLK, 任意频率自动适配
	/* 目标周期数 = us*HCLK/1e6; 用 64 位中间值防溢出, 并兼容非整数 MHz 的时钟 */
	cycles = (uint32_t)(((uint64_t)us * (uint64_t)hclk) / 1000000ULL);
	if(cycles == 0U){
		cycles = 1U;//极短延时至少等待 1 个周期
	}

#ifdef DWT_CTRL_CYCCNTENA_Msk
	{
		uint32_t start;
		softDelayInit();
		start = DWT->CYCCNT;//初始化后取基准
		/* 无符号差值天然正确处理 CYCCNT 的 32 位回绕(168MHz 下约 25.6s 溢出) */
		while((DWT->CYCCNT - start) < cycles){
			__NOP();
		}
	}
#else
	/* 无 DWT 的内核(如 Cortex-M0/M0+): 按 HCLK 折算 NOP 循环, 仅保证随
	 * 频率等比缩放, 精度为近似值; F1/F4 走上面的精确分支, 不会进入此处。 */
	{
		volatile uint32_t n = cycles;
		while(n--){
			__NOP();
		}
	}
#endif
}

void softDelayMs(uint32_t ms){
	softDelayUs(ms * 1000U);//复用微秒级精确延时
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
	/* 纯软件CRC: FLASH是存储器映射的, 直接整段一次算完(不再逐字节软件累加, 也不再依赖CRC外设) */
	return crc32SwBlock((const void*)BOOTLOADER_FLASH_START_ADDRESS, (uint32_t)(BOOTLOADER_FLASH_END_ADDRESS - BOOTLOADER_FLASH_START_ADDRESS));	
}

uint32_t getOriginAppCrc(void){//计算MCU APP CRC32
	/* 纯软件CRC: 同上, 整段一次算完 */
	return crc32SwBlock((const void*)APPLICATION_FLASH_START_ADDRESS, (uint32_t)(APPLICATION_FLASH_END_ADDRESS - APPLICATION_FLASH_START_ADDRESS));	
}



