#include "libcpu.h"
/*****************************************************************************/
uint32_t	UniqueId[3];//处理器序列号 
/*****************************************************************************/
static const char *morseTable[] = {
  "-----",  // '0'
  ".----",  // '1'
  "..---",  // '2'
  "...--",  // '3'
  "....-",  // '4'
  ".....",  // '5'
  "-....",  // '6'
  "--...",  // '7'
  "---..",  // '8'
  "----.",  // '9'
  ".-",     // 'A'
  "-...",   // 'B'
  "-.-.",   // 'C'
  "-..",    // 'D'
  ".",      // 'E'
  "..-.",   // 'F'
  "--.",    // 'G'
  "....",   // 'H'
  "..",     // 'I'
  ".---",   // 'J'
  "-.-",    // 'K'
  ".-..",   // 'L'
  "--",     // 'M'
  "-.",     // 'N'
  "---",    // 'O'
  ".--.",   // 'P'
  "--.-",   // 'Q'
  ".-.",    // 'R'
  "...",    // 'S'
  "-",      // 'T'
  "..-",    // 'U'
  "...-",   // 'V'
  ".--",    // 'W'
  "-..-",   // 'X'
  "-.--",   // 'Y'
  "--.."    // 'Z'
};
#ifndef CONFIG_MORSECODE_DOT_MS
	#define CONFIG_MORSECODE_DOT_MS     					200
#endif
#ifndef CONFIG_MORSECODE_DASH_MS
	#define CONFIG_MORSECODE_DASH_MS   						600
#endif
#ifndef CONFIG_MORSECODE_GAP_MS
	#define CONFIG_MORSECODE_GAP_MS     					200
#endif
#ifndef CONFIG_MORSECODE_REPEAT_MS
	#define CONFIG_MORSECODE_REPEAT_MS  					2000
#endif
/*****************************************************************************/
void softDelayUs(uint32_t us){
	uint32_t loops = us * 168; 
	volatile uint32_t count = loops;
	while(count--){
			__NOP();
			__NOP();
	}
}

void softDelayMs(uint32_t ms){
  volatile uint32_t count = ms;
  while(count--){
    softDelayUs(1000);
  }
}

void tickCheckTask(void){
  uint32_t tick_begin, tick_end; 
  tick_begin = HAL_GetTick();
  FLIP_TICK_LED;
  HAL_Delay(1000);
  tick_end = HAL_GetTick();
  FLIP_TICK_LED;
  uint32_t real_ms = tick_end - tick_begin;
  printf("HAL TICK:%d ms\r\n", real_ms);
}

uint16_t cpuGetFlashSize(void){
   return *(volatile uint16_t*)(0x1FFF7A22);
}

void readStm32UniqueID(void){        
    UniqueId[0] = *(volatile uint32_t*)(0x1FFF7A10);
    UniqueId[1] = *(volatile uint32_t*)(0x1FFF7A14);
    UniqueId[2] = *(volatile uint32_t*)(0x1FFF7A18);
}

void SystemClock_Reset(void){
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	__HAL_RCC_BACKUPRESET_RELEASE();
	__HAL_RCC_BACKUPRESET_FORCE();
	__HAL_RCC_PLL_DISABLE();
	__HAL_RCC_HSI_DISABLE();
	__HAL_RCC_PWR_CLK_DISABLE();
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK){
		Error_Handler();
	}
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK){
		Error_Handler();
	}
}
void resetInit(void){
	HAL_DeInit();
	SystemClock_Reset();
}

uint32_t getOriginBootloadCrc(void){
	uint8_t val;
	uint32_t i;
	uint32_t crc32;
	crc32Clear();
	for(i = BOOTLOADER_FLASH_START_ADDRESS;i < BOOTLOADER_FLASH_END_ADDRESS;i ++){
		val = *(__IO uint8_t*)(i);
		crc32 = crc32CalculateAdd(val);
	}
	return crc32;	
}

uint32_t getOriginAppCrc(void){
	uint8_t val;
	uint32_t i;
	uint32_t crc32;
	crc32Clear();
	for(i = APPLICATION_FLASH_START_ADDRESS;i < APPLICATION_FLASH_END_ADDRESS;i ++){
		val = *(__IO uint8_t*)(i);
		crc32 = crc32CalculateAdd(val);
	}
	return crc32;	
}

void morseCodeDiag(uint8_t diag){//莫尔斯电码诊断闪烁，循环不返回
  const char *pat;
  uint8_t i;
  if(diag >= '0' && diag <= '9'){
    pat = morseTable[diag - '0'];
  } else if(diag >= 'A' && diag <= 'Z'){
    pat = morseTable[10 + (diag - 'A')];
  } else {
    pat = morseTable[0];
  }
  while(1){
    for(i = 0; pat[i] != '\0'; i++){
      if(pat[i] == '.'){
        SET_RED_LED_ON;
        HAL_Delay(CONFIG_MORSECODE_DOT_MS);
      } else {
        SET_RED_LED_ON;
        HAL_Delay(CONFIG_MORSECODE_DASH_MS);
      }
      SET_RED_LED_OFF;
      HAL_Delay(CONFIG_MORSECODE_GAP_MS);
    }
    HAL_Delay(CONFIG_MORSECODE_REPEAT_MS);
  }
}





