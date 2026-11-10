/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sPlcConfig.h"    /* CONFIG_FAULT_DIAG: 故障诊断开关 */
#include "BoardConfig.h"   /* CONFIG_DEBUG_UART: 调试串口句柄 */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#if (CONFIG_FAULT_DIAG == 1)
/******************************************************************************
 * HardFault 现场诊断(只读现场 + 串口输出, 不改变任何业务状态)
 * 设计要点:
 *   1) 用"轮询TXE + 直写DR"输出, 不调用 printf/HAL_UART_Transmit:
 *      不依赖库锁、HAL节拍(uwTick)、中断, 故障现场不会死等;
 *   2) 只读 SCB 故障状态寄存器与异常入栈帧, 不分配内存、不占大栈;
 *   3) 串口未初始化/异常时静默丢弃输出, 仍落到 while(1) 便于调试器挂接;
 *   4) 诊断完成后把 CONFIG_FAULT_DIAG 改0即可关闭, 不残留任何影响。
 ******************************************************************************/
#define FAULT_DIAG_TXE_TIMEOUT    200000UL      /* 单字节TXE轮询上限(与libdbg.c的fputc同量级) */
#define FAULT_DIAG_RAM_BASE       0x20000000UL  /* SRAM1 起始 */
#define FAULT_DIAG_RAM_END        0x20020000UL  /* SRAM1 结束(STM32F405 128KB) */
#define FAULT_DIAG_CODE_BASE      0x08000000UL  /* 用于判断取到的PC是否像代码地址 */
#define FAULT_DIAG_CODE_END       0x09000000UL

static void faultDiagPutChar(char ch)
{
  uint32_t wait;

  for(wait = 0; wait < FAULT_DIAG_TXE_TIMEOUT; wait ++){
    if(__HAL_UART_GET_FLAG(&CONFIG_DEBUG_UART, UART_FLAG_TXE) != RESET){
      break;
    }
  }
  if(wait >= FAULT_DIAG_TXE_TIMEOUT){
    return;                                 /* 串口异常: 丢弃字符, 绝不死等 */
  }
  CONFIG_DEBUG_UART.Instance->DR = (uint8_t)ch;
}

static void faultDiagPuts(const char *str)
{
  while(*str != '\0'){
    faultDiagPutChar(*str ++);
  }
}

static void faultDiagPutHex(uint32_t val, uint8_t digits)
{
  uint8_t i;
  uint8_t nibble;

  for(i = digits; i > 0U; i --){
    nibble = (uint8_t)((val >> ((i - 1U) * 4U)) & 0x0FU);
    faultDiagPutChar((char)((nibble < 10U) ? ('0' + nibble) : ('A' + (nibble - 10U))));
  }
}

static void faultDiagReg(const char *name, uint32_t val)
{
  faultDiagPuts(name);
  faultDiagPutHex(val, 8);
}

/* CFSR 三组子状态 + 逐位置位项翻译, 免去现场再翻手册 */
static void faultDiagDumpCfsr(uint32_t cfsr)
{
  faultDiagPuts("CFSR=0x");
  faultDiagPutHex(cfsr, 8);
  faultDiagPuts("  MMFSR=0x");
  faultDiagPutHex((cfsr >> 0) & 0xFFUL, 2);
  faultDiagPuts(" BUSFSR=0x");
  faultDiagPutHex((cfsr >> 8) & 0xFFUL, 2);
  faultDiagPuts(" USGFSR=0x");
  faultDiagPutHex((cfsr >> 16) & 0xFFFFUL, 4);
  faultDiagPuts("\r\n");

  if((cfsr & (1UL << 0))  != 0UL){ faultDiagPuts("  [MM ] IACCVIOL   取指访问违规(MPU/XN)\r\n"); }
  if((cfsr & (1UL << 1))  != 0UL){ faultDiagPuts("  [MM ] DACCVIOL   数据访问违规\r\n"); }
  if((cfsr & (1UL << 3))  != 0UL){ faultDiagPuts("  [MM ] MUNSTKERR  异常返回出栈失败\r\n"); }
  if((cfsr & (1UL << 4))  != 0UL){ faultDiagPuts("  [MM ] MSTKERR    异常入栈失败(多为栈溢出)\r\n"); }
  if((cfsr & (1UL << 7))  != 0UL){ faultDiagPuts("  [MM ] MMARVALID  MMFAR有效\r\n"); }

  if((cfsr & (1UL << 8))  != 0UL){ faultDiagPuts("  [BUS] IBUSERR    取指总线错误\r\n"); }
  if((cfsr & (1UL << 9))  != 0UL){ faultDiagPuts("  [BUS] PRECISERR  精确数据总线错误(坏地址见BFAR)\r\n"); }
  if((cfsr & (1UL << 10)) != 0UL){ faultDiagPuts("  [BUS] IMPRECISERR 非精确总线错误(写缓冲, 多为野指针写)\r\n"); }
  if((cfsr & (1UL << 11)) != 0UL){ faultDiagPuts("  [BUS] UNSTKERR   异常返回出栈失败\r\n"); }
  if((cfsr & (1UL << 12)) != 0UL){ faultDiagPuts("  [BUS] STKERR     异常入栈失败(多为栈溢出)\r\n"); }
  if((cfsr & (1UL << 15)) != 0UL){ faultDiagPuts("  [BUS] BFARVALID  BFAR有效\r\n"); }

  if((cfsr & (1UL << 16)) != 0UL){ faultDiagPuts("  [USG] UNDEFINSTR 未定义指令\r\n"); }
  if((cfsr & (1UL << 17)) != 0UL){ faultDiagPuts("  [USG] INVSTATE   非法状态(EPSR.T=0, 常见于跳到非Thumb地址)\r\n"); }
  if((cfsr & (1UL << 18)) != 0UL){ faultDiagPuts("  [USG] INVPC      非法EXC_RETURN\r\n"); }
  if((cfsr & (1UL << 19)) != 0UL){ faultDiagPuts("  [USG] NOCP       协处理器不存在(未使能FPU却执行浮点指令)\r\n"); }
  if((cfsr & (1UL << 24)) != 0UL){ faultDiagPuts("  [USG] UNALIGNED  非对齐访问(LDM/STM/LDRD/STRD等)\r\n"); }
  if((cfsr & (1UL << 25)) != 0UL){ faultDiagPuts("  [USG] DIVBYZERO  除零\r\n"); }
}

/* 异常入栈帧: R0,R1,R2,R3,R12,LR,PC,xPSR 共8字 */
static void faultDiagDumpFrame(uint32_t excReturn)
{
  uint32_t sp;
  uint32_t *frame;
  uint32_t *altFrame;

  sp = ((excReturn & 0x04UL) != 0UL) ? __get_PSP() : __get_MSP();
  if((sp < FAULT_DIAG_RAM_BASE) || (sp > (FAULT_DIAG_RAM_END - 0x80UL))){
    faultDiagPuts("SP不在SRAM有效范围, 跳过栈帧解析(疑似栈溢出或SP被破坏)\r\n");
    return;
  }

  frame = (uint32_t *)sp;
  if((excReturn & 0x10UL) == 0UL){
    /* 含FPU扩展帧: FPU现场压在更低地址, 标准帧相对SP上移0x48字节。
       用"PC是否像Thumb代码地址"判定实际基准, 帧格式判断有误时也不会输出错值。 */
    altFrame = (uint32_t *)(sp + 0x48UL);
    if(((altFrame[6] >= FAULT_DIAG_CODE_BASE) && (altFrame[6] < FAULT_DIAG_CODE_END) && ((altFrame[6] & 1UL) != 0UL))
       && !((frame[6] >= FAULT_DIAG_CODE_BASE) && (frame[6] < FAULT_DIAG_CODE_END) && ((frame[6] & 1UL) != 0UL))){
      frame = altFrame;
    }
  }

  faultDiagReg("R0 =0x", frame[0]);
  faultDiagPuts("  ");
  faultDiagReg("R1 =0x", frame[1]);
  faultDiagPuts("\r\n");
  faultDiagReg("R2 =0x", frame[2]);
  faultDiagPuts("  ");
  faultDiagReg("R3 =0x", frame[3]);
  faultDiagPuts("\r\n");
  faultDiagReg("R12=0x", frame[4]);
  faultDiagPuts("  ");
  faultDiagReg("LR =0x", frame[5]);
  faultDiagPuts("\r\n");
  faultDiagReg("PC =0x", frame[6]);
  faultDiagPuts("  ");
  faultDiagReg("PSR=0x", frame[7]);
  faultDiagPuts("\r\n");
}

/* AC5的__asm函数里IMPORT需要全局符号, 故本函数不加static(仅本文件使用) */
void faultDiagDump(uint32_t excReturn)
{
  faultDiagPuts("\r\n*** HARDFAULT ***\r\n");

  faultDiagDumpCfsr(SCB->CFSR);

  faultDiagPuts("HFSR=0x");
  faultDiagPutHex(SCB->HFSR, 8);
  if((SCB->HFSR & (1UL << 30)) != 0UL){
    faultDiagPuts(" FORCED(由MemManage/BusFault/UsageFault升级)");
  }
  if((SCB->HFSR & (1UL << 1)) != 0UL){
    faultDiagPuts(" VECTTBL(向量表读取失败)");
  }
  faultDiagPuts("\r\n");

  faultDiagPuts("MMFAR=0x");
  faultDiagPutHex(SCB->MMFAR, 8);
  faultDiagPuts("  BFAR=0x");
  faultDiagPutHex(SCB->BFAR, 8);
  faultDiagPuts("\r\n");

  faultDiagPuts("EXC_RETURN=0x");
  faultDiagPutHex(excReturn, 8);
  faultDiagPuts(((excReturn & 0x04UL) != 0UL) ? " 栈:PSP" : " 栈:MSP");
  faultDiagPuts(((excReturn & 0x10UL) != 0UL) ? " 无FPU扩展帧\r\n" : " 含FPU扩展帧\r\n");

  faultDiagDumpFrame(excReturn);

  if(((SCB->CFSR & (1UL << 9)) != 0UL) && ((SCB->CFSR & (1UL << 15)) != 0UL)){
    faultDiagPuts("提示: PRECISERR+BFARVALID -> 出错数据地址=BFAR, 出错现场PC=上面的PC\r\n");
  }
  if((SCB->CFSR & (1UL << 12)) != 0UL){
    faultDiagPuts("提示: STKERR -> 异常入栈时写内存失败, 请查栈溢出/栈指针越界\r\n");
  }
  faultDiagPuts("*** END ***\r\n");
}
#endif /* CONFIG_FAULT_DIAG */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern HCD_HandleTypeDef hhcd_USB_OTG_FS;
extern HCD_HandleTypeDef hhcd_USB_OTG_HS;
extern DMA_HandleTypeDef hdma_adc1;
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim14;
extern UART_HandleTypeDef huart1;
extern TIM_HandleTypeDef htim13;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
#if (CONFIG_FAULT_DIAG == 1) && defined(__CC_ARM)
/* AC5(armcc) 不支持内联取LR: __asm volatile("MOV %0, LR" : "=r"(v)) 会报 Error #18。
 * 且 EXC_RETURN 必须在任何 BL 之前取出, 一旦调用函数 LR 即被改写,
 * 所以整个入口改用 AC5 嵌入式汇编实现: 先把 LR 送 r0, 再调用 faultDiagDump, 返回后原地挂死。 */
__asm void HardFault_Handler(void)
{
    IMPORT  faultDiagDump
    MOV     r0, lr
    BL      faultDiagDump
    B       .
}
#else
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */
#if (CONFIG_FAULT_DIAG == 1)
  uint32_t faultExcReturn;

  /* 必须在任何函数调用之前取LR(=EXC_RETURN): 一旦执行BL, LR即被改写 */
  __asm volatile ("MOV %0, LR" : "=r" (faultExcReturn));
  faultDiagDump(faultExcReturn);
#endif

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}
#endif

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles ADC1, ADC2 and ADC3 global interrupts.
  */
void ADC_IRQHandler(void)
{
  /* USER CODE BEGIN ADC_IRQn 0 */

  /* USER CODE END ADC_IRQn 0 */
  HAL_ADC_IRQHandler(&hadc1);
  /* USER CODE BEGIN ADC_IRQn 1 */

  /* USER CODE END ADC_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles TIM8 update interrupt and TIM13 global interrupt.
  */
void TIM8_UP_TIM13_IRQHandler(void)
{
  /* USER CODE BEGIN TIM8_UP_TIM13_IRQn 0 */

  /* USER CODE END TIM8_UP_TIM13_IRQn 0 */
  HAL_TIM_IRQHandler(&htim8);
  HAL_TIM_IRQHandler(&htim13);
  /* USER CODE BEGIN TIM8_UP_TIM13_IRQn 1 */

  /* USER CODE END TIM8_UP_TIM13_IRQn 1 */
}

/**
  * @brief This function handles TIM8 trigger and commutation interrupts and TIM14 global interrupt.
  */
void TIM8_TRG_COM_TIM14_IRQHandler(void)
{
  /* USER CODE BEGIN TIM8_TRG_COM_TIM14_IRQn 0 */

  /* USER CODE END TIM8_TRG_COM_TIM14_IRQn 0 */
  HAL_TIM_IRQHandler(&htim8);
  HAL_TIM_IRQHandler(&htim14);
  /* USER CODE BEGIN TIM8_TRG_COM_TIM14_IRQn 1 */

  /* USER CODE END TIM8_TRG_COM_TIM14_IRQn 1 */
}

/**
  * @brief This function handles TIM7 global interrupt.
  */
void TIM7_IRQHandler(void)
{
  /* USER CODE BEGIN TIM7_IRQn 0 */

  /* USER CODE END TIM7_IRQn 0 */
  HAL_TIM_IRQHandler(&htim7);
  /* USER CODE BEGIN TIM7_IRQn 1 */

  /* USER CODE END TIM7_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream0 global interrupt.
  */
void DMA2_Stream0_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream0_IRQn 0 */

  /* USER CODE END DMA2_Stream0_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc1);
  /* USER CODE BEGIN DMA2_Stream0_IRQn 1 */

  /* USER CODE END DMA2_Stream0_IRQn 1 */
}

/**
  * @brief This function handles USB On The Go FS global interrupt.
  */
void OTG_FS_IRQHandler(void)
{
  /* USER CODE BEGIN OTG_FS_IRQn 0 */

  /* USER CODE END OTG_FS_IRQn 0 */
  HAL_HCD_IRQHandler(&hhcd_USB_OTG_FS);
  /* USER CODE BEGIN OTG_FS_IRQn 1 */

  /* USER CODE END OTG_FS_IRQn 1 */
}

/**
  * @brief This function handles USB On The Go HS global interrupt.
  */
void OTG_HS_IRQHandler(void)
{
  /* USER CODE BEGIN OTG_HS_IRQn 0 */

  /* USER CODE END OTG_HS_IRQn 0 */
  HAL_HCD_IRQHandler(&hhcd_USB_OTG_HS);
  /* USER CODE BEGIN OTG_HS_IRQn 1 */

  /* USER CODE END OTG_HS_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
