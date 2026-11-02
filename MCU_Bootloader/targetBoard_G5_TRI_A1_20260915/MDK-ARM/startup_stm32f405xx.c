/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
/**
 * @file    startup_stm32f405xx.c
 * @brief   STM32F405xx 启动文件(C 语言实现)。
 *          同时兼容 ARM Compiler 5(armcc) 与 ARM Compiler 6(armclang):
 *          - 向量表放 RESET 段(只读), 由分散加载 *.o (RESET, +First) 置于 0x08000000;
 *          - 栈放 STACK 段(NOINIT ZI), 由 RW_IRAM1 .ANY (+RW+ZI) 收纳, 大小与原 armasm
 *            版 Stack_Size=0x2000 一致;
 *          - Reset_Handler 调 SystemInit() 后跳入 Keil C 运行库入口 __main()(微库).
 *          中断向量表与弱处理函数与原 armasm 版 startup_stm32f405xx.s 完全一致。
 */
#include <stdint.h>
#include <stddef.h>
/*****************************************************************************/
extern void SystemInit(void);//STM32F4xx 时钟初始化(CubeMX 生成, system_stm32f4xx.c)
extern void __main(void);   //Keil C 运行库入口(微库: 完成 scatterload 后调用 main())
/*****************************************************************************/
/* 栈/堆: 与 armasm 版 Stack_Size=0x2000、Heap_Size=0x2000 保持一致(各8KB)。 */
/* 段名按字母序命名(HEAP0<HEAP1<STACK0<STACK1), 使 armlink 放置顺序确定: */
/* __heap_base(堆体)->__heap_limit(堆尾)->s_startup_stack(栈体)->__initial_sp(栈顶), */
/* 双编译器(armlink5/armlink6)下 __initial_sp 恒为栈体末尾、__heap_limit 恒为堆体末尾。 */
#define STARTUP_STACK_SIZE   0x2000U
#define STARTUP_HEAP_SIZE    0x2000U
__attribute__((used, section("STACK0"), zero_init)) uint32_t s_startup_stack[STARTUP_STACK_SIZE / sizeof(uint32_t)];
__attribute__((section("STACK1"), zero_init)) uint32_t __initial_sp[1];
__attribute__((section("HEAP0"), zero_init)) uint32_t __heap_base[STARTUP_HEAP_SIZE / sizeof(uint32_t)];
__attribute__((section("HEAP1"), zero_init)) uint32_t __heap_limit[1];
/*****************************************************************************/
typedef void (* const pHandler)(void);
#define VEC(fn)   ((pHandler)(fn))
#if defined(__CC_ARM)
#pragma diag_suppress 1296 /* AC5: 向量表首项 cast 常量初始化器提示(栈顶), AC6 无此诊断 */
#endif
/*****************************************************************************/
/* 向量表引用与弱定义(实际中断处理见 stm32f4xx_it.c, 强定义自动覆盖弱定义) */
void Reset_Handler(void);
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void WWDG_IRQHandler(void);
void PVD_IRQHandler(void);
void TAMP_STAMP_IRQHandler(void);
void RTC_WKUP_IRQHandler(void);
void FLASH_IRQHandler(void);
void RCC_IRQHandler(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void DMA1_Stream0_IRQHandler(void);
void DMA1_Stream1_IRQHandler(void);
void DMA1_Stream2_IRQHandler(void);
void DMA1_Stream3_IRQHandler(void);
void DMA1_Stream4_IRQHandler(void);
void DMA1_Stream5_IRQHandler(void);
void DMA1_Stream6_IRQHandler(void);
void ADC_IRQHandler(void);
void CAN1_TX_IRQHandler(void);
void CAN1_RX0_IRQHandler(void);
void CAN1_RX1_IRQHandler(void);
void CAN1_SCE_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void TIM1_BRK_TIM9_IRQHandler(void);
void TIM1_UP_TIM10_IRQHandler(void);
void TIM1_TRG_COM_TIM11_IRQHandler(void);
void TIM1_CC_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void I2C1_EV_IRQHandler(void);
void I2C1_ER_IRQHandler(void);
void I2C2_EV_IRQHandler(void);
void I2C2_ER_IRQHandler(void);
void SPI1_IRQHandler(void);
void SPI2_IRQHandler(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
void RTC_Alarm_IRQHandler(void);
void OTG_FS_WKUP_IRQHandler(void);
void TIM8_BRK_TIM12_IRQHandler(void);
void TIM8_UP_TIM13_IRQHandler(void);
void TIM8_TRG_COM_TIM14_IRQHandler(void);
void TIM8_CC_IRQHandler(void);
void DMA1_Stream7_IRQHandler(void);
void FMC_IRQHandler(void);
void SDIO_IRQHandler(void);
void TIM5_IRQHandler(void);
void SPI3_IRQHandler(void);
void UART4_IRQHandler(void);
void UART5_IRQHandler(void);
void TIM6_DAC_IRQHandler(void);
void TIM7_IRQHandler(void);
void DMA2_Stream0_IRQHandler(void);
void DMA2_Stream1_IRQHandler(void);
void DMA2_Stream2_IRQHandler(void);
void DMA2_Stream3_IRQHandler(void);
void DMA2_Stream4_IRQHandler(void);
void CAN2_TX_IRQHandler(void);
void CAN2_RX0_IRQHandler(void);
void CAN2_RX1_IRQHandler(void);
void CAN2_SCE_IRQHandler(void);
void OTG_FS_IRQHandler(void);
void DMA2_Stream5_IRQHandler(void);
void DMA2_Stream6_IRQHandler(void);
void DMA2_Stream7_IRQHandler(void);
void USART6_IRQHandler(void);
void I2C3_EV_IRQHandler(void);
void I2C3_ER_IRQHandler(void);
void OTG_HS_EP1_OUT_IRQHandler(void);
void OTG_HS_EP1_IN_IRQHandler(void);
void OTG_HS_WKUP_IRQHandler(void);
void OTG_HS_IRQHandler(void);
void HASH_RNG_IRQHandler(void);
void FPU_IRQHandler(void);
/*****************************************************************************/
/* 向量表: 放 RESET 段, 链接后位于 0x08000000 */
__attribute__((section("RESET"))) const pHandler __Vectors[] = {
  VEC((uint32_t)&__initial_sp[0]),/* 栈顶(与 entry2.o 引用同一标号) */
  NMI_Handler,
  HardFault_Handler,
  MemManage_Handler,
  BusFault_Handler,
  UsageFault_Handler,
  0,
  0,
  0,
  0,
  SVC_Handler,
  DebugMon_Handler,
  0,
  PendSV_Handler,
  SysTick_Handler,
  WWDG_IRQHandler,
  PVD_IRQHandler,
  TAMP_STAMP_IRQHandler,
  RTC_WKUP_IRQHandler,
  FLASH_IRQHandler,
  RCC_IRQHandler,
  EXTI0_IRQHandler,
  EXTI1_IRQHandler,
  EXTI2_IRQHandler,
  EXTI3_IRQHandler,
  EXTI4_IRQHandler,
  DMA1_Stream0_IRQHandler,
  DMA1_Stream1_IRQHandler,
  DMA1_Stream2_IRQHandler,
  DMA1_Stream3_IRQHandler,
  DMA1_Stream4_IRQHandler,
  DMA1_Stream5_IRQHandler,
  DMA1_Stream6_IRQHandler,
  ADC_IRQHandler,
  CAN1_TX_IRQHandler,
  CAN1_RX0_IRQHandler,
  CAN1_RX1_IRQHandler,
  CAN1_SCE_IRQHandler,
  EXTI9_5_IRQHandler,
  TIM1_BRK_TIM9_IRQHandler,
  TIM1_UP_TIM10_IRQHandler,
  TIM1_TRG_COM_TIM11_IRQHandler,
  TIM1_CC_IRQHandler,
  TIM2_IRQHandler,
  TIM3_IRQHandler,
  TIM4_IRQHandler,
  I2C1_EV_IRQHandler,
  I2C1_ER_IRQHandler,
  I2C2_EV_IRQHandler,
  I2C2_ER_IRQHandler,
  SPI1_IRQHandler,
  SPI2_IRQHandler,
  USART1_IRQHandler,
  USART2_IRQHandler,
  USART3_IRQHandler,
  EXTI15_10_IRQHandler,
  RTC_Alarm_IRQHandler,
  OTG_FS_WKUP_IRQHandler,
  TIM8_BRK_TIM12_IRQHandler,
  TIM8_UP_TIM13_IRQHandler,
  TIM8_TRG_COM_TIM14_IRQHandler,
  TIM8_CC_IRQHandler,
  DMA1_Stream7_IRQHandler,
  FMC_IRQHandler,
  SDIO_IRQHandler,
  TIM5_IRQHandler,
  SPI3_IRQHandler,
  UART4_IRQHandler,
  UART5_IRQHandler,
  TIM6_DAC_IRQHandler,
  TIM7_IRQHandler,
  DMA2_Stream0_IRQHandler,
  DMA2_Stream1_IRQHandler,
  DMA2_Stream2_IRQHandler,
  DMA2_Stream3_IRQHandler,
  DMA2_Stream4_IRQHandler,
  0,
  0,
  CAN2_TX_IRQHandler,
  CAN2_RX0_IRQHandler,
  CAN2_RX1_IRQHandler,
  CAN2_SCE_IRQHandler,
  OTG_FS_IRQHandler,
  DMA2_Stream5_IRQHandler,
  DMA2_Stream6_IRQHandler,
  DMA2_Stream7_IRQHandler,
  USART6_IRQHandler,
  I2C3_EV_IRQHandler,
  I2C3_ER_IRQHandler,
  OTG_HS_EP1_OUT_IRQHandler,
  OTG_HS_EP1_IN_IRQHandler,
  OTG_HS_WKUP_IRQHandler,
  OTG_HS_IRQHandler,
  0,
  0,
  HASH_RNG_IRQHandler,
  FPU_IRQHandler,
};
/*****************************************************************************/
/* Reset_Handler: 上电入口, 系统时钟初始化后进入 C 运行库 */
void Reset_Handler(void){
  SystemInit();
  __main();
}
/*****************************************************************************/
/* 弱处理函数: 未实现的中断进入死循环(可被 stm32f4xx_it.c 强定义覆盖) */
static void Default_Handler(void){
  while(1U){}
}
__attribute__((weak)) void NMI_Handler(void){ Default_Handler(); }
__attribute__((weak)) void HardFault_Handler(void){ Default_Handler(); }
__attribute__((weak)) void MemManage_Handler(void){ Default_Handler(); }
__attribute__((weak)) void BusFault_Handler(void){ Default_Handler(); }
__attribute__((weak)) void UsageFault_Handler(void){ Default_Handler(); }
__attribute__((weak)) void SVC_Handler(void){ Default_Handler(); }
__attribute__((weak)) void DebugMon_Handler(void){ Default_Handler(); }
__attribute__((weak)) void PendSV_Handler(void){ Default_Handler(); }
__attribute__((weak)) void SysTick_Handler(void){ Default_Handler(); }
__attribute__((weak)) void WWDG_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void PVD_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void TAMP_STAMP_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void RTC_WKUP_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void FLASH_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void RCC_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void EXTI0_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void EXTI1_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void EXTI2_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void EXTI3_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void EXTI4_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void DMA1_Stream0_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void DMA1_Stream1_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void DMA1_Stream2_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void DMA1_Stream3_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void DMA1_Stream4_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void DMA1_Stream5_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void DMA1_Stream6_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void ADC_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void CAN1_TX_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void CAN1_RX0_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void CAN1_RX1_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void CAN1_SCE_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void EXTI9_5_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void TIM1_BRK_TIM9_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void TIM1_UP_TIM10_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void TIM1_TRG_COM_TIM11_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void TIM1_CC_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void TIM2_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void TIM3_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void TIM4_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void I2C1_EV_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void I2C1_ER_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void I2C2_EV_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void I2C2_ER_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void SPI1_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void SPI2_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void USART1_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void USART2_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void USART3_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void EXTI15_10_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void RTC_Alarm_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void OTG_FS_WKUP_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void TIM8_BRK_TIM12_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void TIM8_UP_TIM13_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void TIM8_TRG_COM_TIM14_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void TIM8_CC_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void DMA1_Stream7_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void FMC_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void SDIO_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void TIM5_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void SPI3_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void UART4_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void UART5_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void TIM6_DAC_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void TIM7_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void DMA2_Stream0_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void DMA2_Stream1_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void DMA2_Stream2_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void DMA2_Stream3_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void DMA2_Stream4_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void CAN2_TX_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void CAN2_RX0_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void CAN2_RX1_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void CAN2_SCE_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void OTG_FS_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void DMA2_Stream5_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void DMA2_Stream6_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void DMA2_Stream7_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void USART6_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void I2C3_EV_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void I2C3_ER_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void OTG_HS_EP1_OUT_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void OTG_HS_EP1_IN_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void OTG_HS_WKUP_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void OTG_HS_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void HASH_RNG_IRQHandler(void){ Default_Handler(); }
__attribute__((weak)) void FPU_IRQHandler(void){ Default_Handler(); }
/*****************************************************************************/
