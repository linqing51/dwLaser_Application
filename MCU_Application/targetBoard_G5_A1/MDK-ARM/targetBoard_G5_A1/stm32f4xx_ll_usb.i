#line 1 "../Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.c"






































 

 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h"

















  

 







 
#line 1 "../Core/Inc/stm32f4xx_hal_conf.h"
 


















 
 

 







 
 

 


 


   

 

 

 
 
 
 
 
 
 
 
 
 

 
 
 

 
 
 
 
 


 
 
 
 
 
 

 
 
 
 
 
 
 
 
 
#line 91 "../Core/Inc/stm32f4xx_hal_conf.h"

 




 












 






 







 












 





 

 


 
#line 156 "../Core/Inc/stm32f4xx_hal_conf.h"

#line 196 "../Core/Inc/stm32f4xx_hal_conf.h"

 



 
 

 

 

 
#line 215 "../Core/Inc/stm32f4xx_hal_conf.h"

 





 

 

 

 





 




#line 249 "../Core/Inc/stm32f4xx_hal_conf.h"





 





 




 



 


 

#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"















 

 







 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_def.h"

















 

 







 
#line 1 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"


























 



 



 










 



 






 
#line 94 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"



 
#line 106 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"



 
#line 118 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"



 



 

#line 1 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"






















 



 



 










 



 








 



 




 
typedef enum
{
   
  NonMaskableInt_IRQn         = -14,     
  MemoryManagement_IRQn       = -12,     
  BusFault_IRQn               = -11,     
  UsageFault_IRQn             = -10,     
  SVCall_IRQn                 = -5,      
  DebugMonitor_IRQn           = -4,      
  PendSV_IRQn                 = -2,      
  SysTick_IRQn                = -1,      
   
  WWDG_IRQn                   = 0,       
  PVD_IRQn                    = 1,       
  TAMP_STAMP_IRQn             = 2,       
  RTC_WKUP_IRQn               = 3,       
  FLASH_IRQn                  = 4,       
  RCC_IRQn                    = 5,       
  EXTI0_IRQn                  = 6,       
  EXTI1_IRQn                  = 7,       
  EXTI2_IRQn                  = 8,       
  EXTI3_IRQn                  = 9,       
  EXTI4_IRQn                  = 10,      
  DMA1_Stream0_IRQn           = 11,      
  DMA1_Stream1_IRQn           = 12,      
  DMA1_Stream2_IRQn           = 13,      
  DMA1_Stream3_IRQn           = 14,      
  DMA1_Stream4_IRQn           = 15,      
  DMA1_Stream5_IRQn           = 16,      
  DMA1_Stream6_IRQn           = 17,      
  ADC_IRQn                    = 18,      
  CAN1_TX_IRQn                = 19,      
  CAN1_RX0_IRQn               = 20,      
  CAN1_RX1_IRQn               = 21,      
  CAN1_SCE_IRQn               = 22,      
  EXTI9_5_IRQn                = 23,      
  TIM1_BRK_TIM9_IRQn          = 24,      
  TIM1_UP_TIM10_IRQn          = 25,      
  TIM1_TRG_COM_TIM11_IRQn     = 26,      
  TIM1_CC_IRQn                = 27,      
  TIM2_IRQn                   = 28,      
  TIM3_IRQn                   = 29,      
  TIM4_IRQn                   = 30,      
  I2C1_EV_IRQn                = 31,      
  I2C1_ER_IRQn                = 32,      
  I2C2_EV_IRQn                = 33,      
  I2C2_ER_IRQn                = 34,      
  SPI1_IRQn                   = 35,      
  SPI2_IRQn                   = 36,      
  USART1_IRQn                 = 37,      
  USART2_IRQn                 = 38,      
  USART3_IRQn                 = 39,      
  EXTI15_10_IRQn              = 40,      
  RTC_Alarm_IRQn              = 41,      
  OTG_FS_WKUP_IRQn            = 42,      
  TIM8_BRK_TIM12_IRQn         = 43,      
  TIM8_UP_TIM13_IRQn          = 44,      
  TIM8_TRG_COM_TIM14_IRQn     = 45,      
  TIM8_CC_IRQn                = 46,      
  DMA1_Stream7_IRQn           = 47,      
  FSMC_IRQn                   = 48,      
  SDIO_IRQn                   = 49,      
  TIM5_IRQn                   = 50,      
  SPI3_IRQn                   = 51,      
  UART4_IRQn                  = 52,      
  UART5_IRQn                  = 53,      
  TIM6_DAC_IRQn               = 54,      
  TIM7_IRQn                   = 55,      
  DMA2_Stream0_IRQn           = 56,      
  DMA2_Stream1_IRQn           = 57,      
  DMA2_Stream2_IRQn           = 58,      
  DMA2_Stream3_IRQn           = 59,      
  DMA2_Stream4_IRQn           = 60,      
  CAN2_TX_IRQn                = 63,      
  CAN2_RX0_IRQn               = 64,      
  CAN2_RX1_IRQn               = 65,      
  CAN2_SCE_IRQn               = 66,      
  OTG_FS_IRQn                 = 67,      
  DMA2_Stream5_IRQn           = 68,      
  DMA2_Stream6_IRQn           = 69,      
  DMA2_Stream7_IRQn           = 70,      
  USART6_IRQn                 = 71,      
  I2C3_EV_IRQn                = 72,      
  I2C3_ER_IRQn                = 73,      
  OTG_HS_EP1_OUT_IRQn         = 74,      
  OTG_HS_EP1_IN_IRQn          = 75,      
  OTG_HS_WKUP_IRQn            = 76,      
  OTG_HS_IRQn                 = 77,      
  RNG_IRQn                    = 80,      
  FPU_IRQn                    = 81       
} IRQn_Type;
 




 

#line 1 "../Drivers/CMSIS/Include/core_cm4.h"
 




 
















 










#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
 
 





 









     
#line 27 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
     











#line 46 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"





 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     




typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;


     
typedef   signed     long long intmax_t;
typedef unsigned     long long uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     






     






     






     

     


     


     


     

     
#line 216 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     



     






     
    
 



#line 241 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     







     










     











#line 305 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"






 
#line 35 "../Drivers/CMSIS/Include/core_cm4.h"

















 




 



 

#line 1 "../Drivers/CMSIS/Include/cmsis_version.h"
 




 
















 










 
#line 64 "../Drivers/CMSIS/Include/core_cm4.h"

 









 
#line 87 "../Drivers/CMSIS/Include/core_cm4.h"

#line 161 "../Drivers/CMSIS/Include/core_cm4.h"

#line 1 "../Drivers/CMSIS/Include/cmsis_compiler.h"
 




 
















 




#line 29 "../Drivers/CMSIS/Include/cmsis_compiler.h"



 
#line 1 "../Drivers/CMSIS/Include/cmsis_armcc.h"
 




 
















 









 













   
   
   

 




 
#line 111 "../Drivers/CMSIS/Include/cmsis_armcc.h"

 





















 



 




 






 







 






 








 






 






 








 








 

__attribute__((section(".rev16_text"))) static __inline __asm uint32_t __REV16(uint32_t value)
{
  rev16 r0, r0
  bx lr
}








 

__attribute__((section(".revsh_text"))) static __inline __asm int16_t __REVSH(int16_t value)
{
  revsh r0, r0
  bx lr
}









 









 








 
#line 277 "../Drivers/CMSIS/Include/cmsis_armcc.h"







 











 












 












 














 














 














 










 









 









 









 

__attribute__((section(".rrx_text"))) static __inline __asm uint32_t __RRX(uint32_t value)
{
  rrx r0, r0
  bx lr
}








 








 








 








 








 








 


#line 525 "../Drivers/CMSIS/Include/cmsis_armcc.h"

   


 



 





 
 






 
 





 
static __inline uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __asm("control");
  return(__regControl);
}






 
static __inline void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __asm("control");
  __regControl = control;
  __isb(0xF);
}






 
static __inline uint32_t __get_IPSR(void)
{
  register uint32_t __regIPSR          __asm("ipsr");
  return(__regIPSR);
}






 
static __inline uint32_t __get_APSR(void)
{
  register uint32_t __regAPSR          __asm("apsr");
  return(__regAPSR);
}






 
static __inline uint32_t __get_xPSR(void)
{
  register uint32_t __regXPSR          __asm("xpsr");
  return(__regXPSR);
}






 
static __inline uint32_t __get_PSP(void)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  return(__regProcessStackPointer);
}






 
static __inline void __set_PSP(uint32_t topOfProcStack)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  __regProcessStackPointer = topOfProcStack;
}






 
static __inline uint32_t __get_MSP(void)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  return(__regMainStackPointer);
}






 
static __inline void __set_MSP(uint32_t topOfMainStack)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  __regMainStackPointer = topOfMainStack;
}






 
static __inline uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __asm("primask");
  return(__regPriMask);
}






 
static __inline void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __asm("primask");
  __regPriMask = (priMask);
}









 







 







 
static __inline uint32_t  __get_BASEPRI(void)
{
  register uint32_t __regBasePri         __asm("basepri");
  return(__regBasePri);
}






 
static __inline void __set_BASEPRI(uint32_t basePri)
{
  register uint32_t __regBasePri         __asm("basepri");
  __regBasePri = (basePri & 0xFFU);
}







 
static __inline void __set_BASEPRI_MAX(uint32_t basePri)
{
  register uint32_t __regBasePriMax      __asm("basepri_max");
  __regBasePriMax = (basePri & 0xFFU);
}






 
static __inline uint32_t __get_FAULTMASK(void)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  return(__regFaultMask);
}






 
static __inline void __set_FAULTMASK(uint32_t faultMask)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  __regFaultMask = (faultMask & (uint32_t)1U);
}









 
static __inline uint32_t __get_FPSCR(void)
{


  register uint32_t __regfpscr         __asm("fpscr");
  return(__regfpscr);



}






 
static __inline void __set_FPSCR(uint32_t fpscr)
{


  register uint32_t __regfpscr         __asm("fpscr");
  __regfpscr = (fpscr);



}


 


 



 



#line 870 "../Drivers/CMSIS/Include/cmsis_armcc.h"















 


#line 35 "../Drivers/CMSIS/Include/cmsis_compiler.h"




 
#line 280 "../Drivers/CMSIS/Include/cmsis_compiler.h"




#line 163 "../Drivers/CMSIS/Include/core_cm4.h"

















 
#line 212 "../Drivers/CMSIS/Include/core_cm4.h"

 






 
#line 228 "../Drivers/CMSIS/Include/core_cm4.h"

 




 













 



 






 



 
typedef union
{
  struct
  {
    uint32_t _reserved0:16;               
    uint32_t GE:4;                        
    uint32_t _reserved1:7;                
    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} APSR_Type;

 





















 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:23;               
  } b;                                    
  uint32_t w;                             
} IPSR_Type;

 






 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:1;                
    uint32_t ICI_IT_1:6;                  
    uint32_t GE:4;                        
    uint32_t _reserved1:4;                
    uint32_t T:1;                         
    uint32_t ICI_IT_2:2;                  
    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} xPSR_Type;

 

































 
typedef union
{
  struct
  {
    uint32_t nPRIV:1;                     
    uint32_t SPSEL:1;                     
    uint32_t FPCA:1;                      
    uint32_t _reserved0:29;               
  } b;                                    
  uint32_t w;                             
} CONTROL_Type;

 









 







 



 
typedef struct
{
  volatile uint32_t ISER[8U];                
        uint32_t RESERVED0[24U];
  volatile uint32_t ICER[8U];                
        uint32_t RESERVED1[24U];
  volatile uint32_t ISPR[8U];                
        uint32_t RESERVED2[24U];
  volatile uint32_t ICPR[8U];                
        uint32_t RESERVED3[24U];
  volatile uint32_t IABR[8U];                
        uint32_t RESERVED4[56U];
  volatile uint8_t  IP[240U];                
        uint32_t RESERVED5[644U];
  volatile  uint32_t STIR;                    
}  NVIC_Type;

 



 







 



 
typedef struct
{
  volatile const  uint32_t CPUID;                   
  volatile uint32_t ICSR;                    
  volatile uint32_t VTOR;                    
  volatile uint32_t AIRCR;                   
  volatile uint32_t SCR;                     
  volatile uint32_t CCR;                     
  volatile uint8_t  SHP[12U];                
  volatile uint32_t SHCSR;                   
  volatile uint32_t CFSR;                    
  volatile uint32_t HFSR;                    
  volatile uint32_t DFSR;                    
  volatile uint32_t MMFAR;                   
  volatile uint32_t BFAR;                    
  volatile uint32_t AFSR;                    
  volatile const  uint32_t PFR[2U];                 
  volatile const  uint32_t DFR;                     
  volatile const  uint32_t ADR;                     
  volatile const  uint32_t MMFR[4U];                
  volatile const  uint32_t ISAR[5U];                
        uint32_t RESERVED0[5U];
  volatile uint32_t CPACR;                   
} SCB_Type;

 















 






























 



 





















 









 


















 










































 









 


















 





















 


















 









 















 







 



 
typedef struct
{
        uint32_t RESERVED0[1U];
  volatile const  uint32_t ICTR;                    
  volatile uint32_t ACTLR;                   
} SCnSCB_Type;

 



 















 







 



 
typedef struct
{
  volatile uint32_t CTRL;                    
  volatile uint32_t LOAD;                    
  volatile uint32_t VAL;                     
  volatile const  uint32_t CALIB;                   
} SysTick_Type;

 












 



 



 









 







 



 
typedef struct
{
  volatile  union
  {
    volatile  uint8_t    u8;                  
    volatile  uint16_t   u16;                 
    volatile  uint32_t   u32;                 
  }  PORT [32U];                          
        uint32_t RESERVED0[864U];
  volatile uint32_t TER;                     
        uint32_t RESERVED1[15U];
  volatile uint32_t TPR;                     
        uint32_t RESERVED2[15U];
  volatile uint32_t TCR;                     
        uint32_t RESERVED3[32U];
        uint32_t RESERVED4[43U];
  volatile  uint32_t LAR;                     
  volatile const  uint32_t LSR;                     
        uint32_t RESERVED5[6U];
  volatile const  uint32_t PID4;                    
  volatile const  uint32_t PID5;                    
  volatile const  uint32_t PID6;                    
  volatile const  uint32_t PID7;                    
  volatile const  uint32_t PID0;                    
  volatile const  uint32_t PID1;                    
  volatile const  uint32_t PID2;                    
  volatile const  uint32_t PID3;                    
  volatile const  uint32_t CID0;                    
  volatile const  uint32_t CID1;                    
  volatile const  uint32_t CID2;                    
  volatile const  uint32_t CID3;                    
} ITM_Type;

 



 



























 









   







 



 
typedef struct
{
  volatile uint32_t CTRL;                    
  volatile uint32_t CYCCNT;                  
  volatile uint32_t CPICNT;                  
  volatile uint32_t EXCCNT;                  
  volatile uint32_t SLEEPCNT;                
  volatile uint32_t LSUCNT;                  
  volatile uint32_t FOLDCNT;                 
  volatile const  uint32_t PCSR;                    
  volatile uint32_t COMP0;                   
  volatile uint32_t MASK0;                   
  volatile uint32_t FUNCTION0;               
        uint32_t RESERVED0[1U];
  volatile uint32_t COMP1;                   
  volatile uint32_t MASK1;                   
  volatile uint32_t FUNCTION1;               
        uint32_t RESERVED1[1U];
  volatile uint32_t COMP2;                   
  volatile uint32_t MASK2;                   
  volatile uint32_t FUNCTION2;               
        uint32_t RESERVED2[1U];
  volatile uint32_t COMP3;                   
  volatile uint32_t MASK3;                   
  volatile uint32_t FUNCTION3;               
} DWT_Type;

 






















































 



 



 



 



 



 



 



























   







 



 
typedef struct
{
  volatile const  uint32_t SSPSR;                   
  volatile uint32_t CSPSR;                   
        uint32_t RESERVED0[2U];
  volatile uint32_t ACPR;                    
        uint32_t RESERVED1[55U];
  volatile uint32_t SPPR;                    
        uint32_t RESERVED2[131U];
  volatile const  uint32_t FFSR;                    
  volatile uint32_t FFCR;                    
  volatile const  uint32_t FSCR;                    
        uint32_t RESERVED3[759U];
  volatile const  uint32_t TRIGGER;                 
  volatile const  uint32_t FIFO0;                   
  volatile const  uint32_t ITATBCTR2;               
        uint32_t RESERVED4[1U];
  volatile const  uint32_t ITATBCTR0;               
  volatile const  uint32_t FIFO1;                   
  volatile uint32_t ITCTRL;                  
        uint32_t RESERVED5[39U];
  volatile uint32_t CLAIMSET;                
  volatile uint32_t CLAIMCLR;                
        uint32_t RESERVED7[8U];
  volatile const  uint32_t DEVID;                   
  volatile const  uint32_t DEVTYPE;                 
} TPI_Type;

 



 



 












 






 



 





















 






 





















 






 



 


















 






   








 



 
typedef struct
{
  volatile const  uint32_t TYPE;                    
  volatile uint32_t CTRL;                    
  volatile uint32_t RNR;                     
  volatile uint32_t RBAR;                    
  volatile uint32_t RASR;                    
  volatile uint32_t RBAR_A1;                 
  volatile uint32_t RASR_A1;                 
  volatile uint32_t RBAR_A2;                 
  volatile uint32_t RASR_A2;                 
  volatile uint32_t RBAR_A3;                 
  volatile uint32_t RASR_A3;                 
} MPU_Type;



 









 









 



 









 






























 








 



 
typedef struct
{
        uint32_t RESERVED0[1U];
  volatile uint32_t FPCCR;                   
  volatile uint32_t FPCAR;                   
  volatile uint32_t FPDSCR;                  
  volatile const  uint32_t MVFR0;                   
  volatile const  uint32_t MVFR1;                   
  volatile const  uint32_t MVFR2;                   
} FPU_Type;

 



























 



 












 
























 












 




 







 



 
typedef struct
{
  volatile uint32_t DHCSR;                   
  volatile  uint32_t DCRSR;                   
  volatile uint32_t DCRDR;                   
  volatile uint32_t DEMCR;                   
} CoreDebug_Type;

 




































 






 







































 







 






 







 


 







 

 
#line 1558 "../Drivers/CMSIS/Include/core_cm4.h"

#line 1567 "../Drivers/CMSIS/Include/core_cm4.h"









 










 


 



 





 

#line 1621 "../Drivers/CMSIS/Include/core_cm4.h"

#line 1631 "../Drivers/CMSIS/Include/core_cm4.h"




 
#line 1642 "../Drivers/CMSIS/Include/core_cm4.h"










 
static __inline void __NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);              

  reg_value  =  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR;                                                    
  reg_value &= ~((uint32_t)((0xFFFFUL << 16U) | (7UL << 8U)));  
  reg_value  =  (reg_value                                   |
                ((uint32_t)0x5FAUL << 16U) |
                (PriorityGroupTmp << 8U)  );               
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR =  reg_value;
}






 
static __inline uint32_t __NVIC_GetPriorityGrouping(void)
{
  return ((uint32_t)((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8U)) >> 8U));
}







 
static __inline void __NVIC_EnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    __memory_changed();
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    __memory_changed();
  }
}









 
static __inline uint32_t __NVIC_GetEnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}







 
static __inline void __NVIC_DisableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    __dsb(0xF);
    __isb(0xF);
  }
}









 
static __inline uint32_t __NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}







 
static __inline void __NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}







 
static __inline void __NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}









 
static __inline uint32_t __NVIC_GetActive(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IABR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}










 
static __inline void __NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[((uint32_t)IRQn)]               = (uint8_t)((priority << (8U - 4U)) & (uint32_t)0xFFUL);
  }
  else
  {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[(((uint32_t)IRQn) & 0xFUL)-4UL] = (uint8_t)((priority << (8U - 4U)) & (uint32_t)0xFFUL);
  }
}










 
static __inline uint32_t __NVIC_GetPriority(IRQn_Type IRQn)
{

  if ((int32_t)(IRQn) >= 0)
  {
    return(((uint32_t)((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[((uint32_t)IRQn)]               >> (8U - 4U)));
  }
  else
  {
    return(((uint32_t)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[(((uint32_t)IRQn) & 0xFUL)-4UL] >> (8U - 4U)));
  }
}












 
static __inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);    
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(4U)) ? (uint32_t)(4U) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits     = ((PriorityGroupTmp + (uint32_t)(4U)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(4U));

  return (
           ((PreemptPriority & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL)) << SubPriorityBits) |
           ((SubPriority     & (uint32_t)((1UL << (SubPriorityBits    )) - 1UL)))
         );
}












 
static __inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* const pPreemptPriority, uint32_t* const pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);    
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(4U)) ? (uint32_t)(4U) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits     = ((PriorityGroupTmp + (uint32_t)(4U)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(4U));

  *pPreemptPriority = (Priority >> SubPriorityBits) & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL);
  *pSubPriority     = (Priority                   ) & (uint32_t)((1UL << (SubPriorityBits    )) - 1UL);
}










 
static __inline void __NVIC_SetVector(IRQn_Type IRQn, uint32_t vector)
{
  uint32_t *vectors = (uint32_t *)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->VTOR;
  vectors[(int32_t)IRQn + 16] = vector;
   
}









 
static __inline uint32_t __NVIC_GetVector(IRQn_Type IRQn)
{
  uint32_t *vectors = (uint32_t *)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->VTOR;
  return vectors[(int32_t)IRQn + 16];
}





 
__declspec(noreturn) static __inline void __NVIC_SystemReset(void)
{
  __dsb(0xF);                                                          
 
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR  = (uint32_t)((0x5FAUL << 16U)    |
                           (((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8U)) |
                            (1UL << 2U)    );          
  __dsb(0xF);                                                           

  for(;;)                                                            
  {
    __nop();
  }
}

 


 



#line 1 "../Drivers/CMSIS/Include/mpu_armv7.h"





 
















 
 





 



#line 62 "../Drivers/CMSIS/Include/mpu_armv7.h"

#line 69 "../Drivers/CMSIS/Include/mpu_armv7.h"





 












   














 
#line 110 "../Drivers/CMSIS/Include/mpu_armv7.h"












                          









  










  












  




 




 




 




 





 
typedef struct {
  uint32_t RBAR; 
  uint32_t RASR; 
} ARM_MPU_Region_t;
    


 
static __inline void ARM_MPU_Enable(uint32_t MPU_Control)
{
  __dmb(0xF);
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->CTRL = MPU_Control | (1UL );

  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHCSR |= (1UL << 16U);

  __dsb(0xF);
  __isb(0xF);
}


 
static __inline void ARM_MPU_Disable(void)
{
  __dmb(0xF);

  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHCSR &= ~(1UL << 16U);

  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->CTRL  &= ~(1UL );
  __dsb(0xF);
  __isb(0xF);
}



 
static __inline void ARM_MPU_ClrRegion(uint32_t rnr)
{
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RNR = rnr;
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RASR = 0U;
}




    
static __inline void ARM_MPU_SetRegion(uint32_t rbar, uint32_t rasr)
{
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RBAR = rbar;
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RASR = rasr;
}





    
static __inline void ARM_MPU_SetRegionEx(uint32_t rnr, uint32_t rbar, uint32_t rasr)
{
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RNR = rnr;
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RBAR = rbar;
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RASR = rasr;
}





 
static __inline void ARM_MPU_OrderedMemcpy(volatile uint32_t* dst, const uint32_t* __restrict src, uint32_t len)
{
  uint32_t i;
  for (i = 0U; i < len; ++i) 
  {
    dst[i] = src[i];
  }
}




 
static __inline void ARM_MPU_Load(ARM_MPU_Region_t const* table, uint32_t cnt) 
{
  const uint32_t rowWordSize = sizeof(ARM_MPU_Region_t)/4U;
  while (cnt > 4U) {
    ARM_MPU_OrderedMemcpy(&(((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RBAR), &(table->RBAR), 4U*rowWordSize);
    table += 4U;
    cnt -= 4U;
  }
  ARM_MPU_OrderedMemcpy(&(((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RBAR), &(table->RBAR), cnt*rowWordSize);
}

#line 1961 "../Drivers/CMSIS/Include/core_cm4.h"




 





 








 
static __inline uint32_t SCB_GetFPUType(void)
{
  uint32_t mvfr0;

  mvfr0 = ((FPU_Type *) ((0xE000E000UL) + 0x0F30UL) )->MVFR0;
  if      ((mvfr0 & ((0xFUL << 4U) | (0xFUL << 8U))) == 0x020U)
  {
    return 1U;            
  }
  else
  {
    return 0U;            
  }
}


 



 





 













 
static __inline uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1UL) > (0xFFFFFFUL ))
  {
    return (1UL);                                                    
  }

  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD  = (uint32_t)(ticks - 1UL);                          
  __NVIC_SetPriority (SysTick_IRQn, (1UL << 4U) - 1UL);  
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL   = 0UL;                                              
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL  = (1UL << 2U) |
                   (1UL << 1U)   |
                   (1UL );                          
  return (0UL);                                                      
}



 



 





 

extern volatile int32_t ITM_RxBuffer;                               










 
static __inline uint32_t ITM_SendChar (uint32_t ch)
{
  if (((((ITM_Type *) (0xE0000000UL) )->TCR & (1UL )) != 0UL) &&       
      ((((ITM_Type *) (0xE0000000UL) )->TER & 1UL               ) != 0UL)   )      
  {
    while (((ITM_Type *) (0xE0000000UL) )->PORT[0U].u32 == 0UL)
    {
      __nop();
    }
    ((ITM_Type *) (0xE0000000UL) )->PORT[0U].u8 = (uint8_t)ch;
  }
  return (ch);
}







 
static __inline int32_t ITM_ReceiveChar (void)
{
  int32_t ch = -1;                            

  if (ITM_RxBuffer != ((int32_t)0x5AA55AA5U))
  {
    ch = ITM_RxBuffer;
    ITM_RxBuffer = ((int32_t)0x5AA55AA5U);        
  }

  return (ch);
}







 
static __inline int32_t ITM_CheckChar (void)
{

  if (ITM_RxBuffer == ((int32_t)0x5AA55AA5U))
  {
    return (0);                               
  }
  else
  {
    return (1);                               
  }
}

 










#line 164 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
#line 1 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/system_stm32f4xx.h"
















 



 



 



 









 



 




 







 
extern uint32_t SystemCoreClock;           

extern const uint8_t  AHBPrescTable[16];     
extern const uint8_t  APBPrescTable[8];      



 



 



 



 



 



 

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);


 









 



 
#line 165 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
#line 166 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 



 

typedef struct
{
  volatile uint32_t SR;      
  volatile uint32_t CR1;     
  volatile uint32_t CR2;     
  volatile uint32_t SMPR1;   
  volatile uint32_t SMPR2;   
  volatile uint32_t JOFR1;   
  volatile uint32_t JOFR2;   
  volatile uint32_t JOFR3;   
  volatile uint32_t JOFR4;   
  volatile uint32_t HTR;     
  volatile uint32_t LTR;     
  volatile uint32_t SQR1;    
  volatile uint32_t SQR2;    
  volatile uint32_t SQR3;    
  volatile uint32_t JSQR;    
  volatile uint32_t JDR1;    
  volatile uint32_t JDR2;    
  volatile uint32_t JDR3;    
  volatile uint32_t JDR4;    
  volatile uint32_t DR;      
} ADC_TypeDef;

typedef struct
{
  volatile uint32_t CSR;     
  volatile uint32_t CCR;     
  volatile uint32_t CDR;    
 
} ADC_Common_TypeDef;




 

typedef struct
{
  volatile uint32_t TIR;   
  volatile uint32_t TDTR;  
  volatile uint32_t TDLR;  
  volatile uint32_t TDHR;  
} CAN_TxMailBox_TypeDef;



 

typedef struct
{
  volatile uint32_t RIR;   
  volatile uint32_t RDTR;  
  volatile uint32_t RDLR;  
  volatile uint32_t RDHR;  
} CAN_FIFOMailBox_TypeDef;



 

typedef struct
{
  volatile uint32_t FR1;  
  volatile uint32_t FR2;  
} CAN_FilterRegister_TypeDef;



 

typedef struct
{
  volatile uint32_t              MCR;                  
  volatile uint32_t              MSR;                  
  volatile uint32_t              TSR;                  
  volatile uint32_t              RF0R;                 
  volatile uint32_t              RF1R;                 
  volatile uint32_t              IER;                  
  volatile uint32_t              ESR;                  
  volatile uint32_t              BTR;                  
  uint32_t                   RESERVED0[88];        
  CAN_TxMailBox_TypeDef      sTxMailBox[3];        
  CAN_FIFOMailBox_TypeDef    sFIFOMailBox[2];      
  uint32_t                   RESERVED1[12];        
  volatile uint32_t              FMR;                  
  volatile uint32_t              FM1R;                 
  uint32_t                   RESERVED2;            
  volatile uint32_t              FS1R;                 
  uint32_t                   RESERVED3;            
  volatile uint32_t              FFA1R;                
  uint32_t                   RESERVED4;            
  volatile uint32_t              FA1R;                 
  uint32_t                   RESERVED5[8];         
  CAN_FilterRegister_TypeDef sFilterRegister[28];  
} CAN_TypeDef;



 

typedef struct
{
  volatile uint32_t DR;          
  volatile uint8_t  IDR;         
  uint8_t       RESERVED0;   
  uint16_t      RESERVED1;   
  volatile uint32_t CR;          
} CRC_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;        
  volatile uint32_t SWTRIGR;   
  volatile uint32_t DHR12R1;   
  volatile uint32_t DHR12L1;   
  volatile uint32_t DHR8R1;    
  volatile uint32_t DHR12R2;   
  volatile uint32_t DHR12L2;   
  volatile uint32_t DHR8R2;    
  volatile uint32_t DHR12RD;   
  volatile uint32_t DHR12LD;   
  volatile uint32_t DHR8RD;    
  volatile uint32_t DOR1;      
  volatile uint32_t DOR2;      
  volatile uint32_t SR;        
} DAC_TypeDef;



 

typedef struct
{
  volatile uint32_t IDCODE;   
  volatile uint32_t CR;       
  volatile uint32_t APB1FZ;   
  volatile uint32_t APB2FZ;   
} DBGMCU_TypeDef;




 

typedef struct
{
  volatile uint32_t CR;      
  volatile uint32_t NDTR;    
  volatile uint32_t PAR;     
  volatile uint32_t M0AR;    
  volatile uint32_t M1AR;    
  volatile uint32_t FCR;     
} DMA_Stream_TypeDef;

typedef struct
{
  volatile uint32_t LISR;    
  volatile uint32_t HISR;    
  volatile uint32_t LIFCR;   
  volatile uint32_t HIFCR;   
} DMA_TypeDef;



 

typedef struct
{
  volatile uint32_t IMR;     
  volatile uint32_t EMR;     
  volatile uint32_t RTSR;    
  volatile uint32_t FTSR;    
  volatile uint32_t SWIER;   
  volatile uint32_t PR;      
} EXTI_TypeDef;



 

typedef struct
{
  volatile uint32_t ACR;       
  volatile uint32_t KEYR;      
  volatile uint32_t OPTKEYR;   
  volatile uint32_t SR;        
  volatile uint32_t CR;        
  volatile uint32_t OPTCR;     
  volatile uint32_t OPTCR1;    
} FLASH_TypeDef;





 

typedef struct
{
  volatile uint32_t BTCR[8];     
} FSMC_Bank1_TypeDef;



 

typedef struct
{
  volatile uint32_t BWTR[7];     
} FSMC_Bank1E_TypeDef;



 

typedef struct
{
  volatile uint32_t PCR2;        
  volatile uint32_t SR2;         
  volatile uint32_t PMEM2;       
  volatile uint32_t PATT2;       
  uint32_t      RESERVED0;   
  volatile uint32_t ECCR2;       
  uint32_t      RESERVED1;   
  uint32_t      RESERVED2;   
  volatile uint32_t PCR3;        
  volatile uint32_t SR3;         
  volatile uint32_t PMEM3;       
  volatile uint32_t PATT3;       
  uint32_t      RESERVED3;   
  volatile uint32_t ECCR3;       
} FSMC_Bank2_3_TypeDef;



 

typedef struct
{
  volatile uint32_t PCR4;        
  volatile uint32_t SR4;         
  volatile uint32_t PMEM4;       
  volatile uint32_t PATT4;       
  volatile uint32_t PIO4;        
} FSMC_Bank4_TypeDef;



 

typedef struct
{
  volatile uint32_t MODER;     
  volatile uint32_t OTYPER;    
  volatile uint32_t OSPEEDR;   
  volatile uint32_t PUPDR;     
  volatile uint32_t IDR;       
  volatile uint32_t ODR;       
  volatile uint32_t BSRR;      
  volatile uint32_t LCKR;      
  volatile uint32_t AFR[2];    
} GPIO_TypeDef;



 

typedef struct
{
  volatile uint32_t MEMRMP;        
  volatile uint32_t PMC;           
  volatile uint32_t EXTICR[4];     
  uint32_t      RESERVED[2];   
  volatile uint32_t CMPCR;         
} SYSCFG_TypeDef;



 

typedef struct
{
  volatile uint32_t CR1;         
  volatile uint32_t CR2;         
  volatile uint32_t OAR1;        
  volatile uint32_t OAR2;        
  volatile uint32_t DR;          
  volatile uint32_t SR1;         
  volatile uint32_t SR2;         
  volatile uint32_t CCR;         
  volatile uint32_t TRISE;       
} I2C_TypeDef;



 

typedef struct
{
  volatile uint32_t KR;    
  volatile uint32_t PR;    
  volatile uint32_t RLR;   
  volatile uint32_t SR;    
} IWDG_TypeDef;




 

typedef struct
{
  volatile uint32_t CR;    
  volatile uint32_t CSR;   
} PWR_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;             
  volatile uint32_t PLLCFGR;        
  volatile uint32_t CFGR;           
  volatile uint32_t CIR;            
  volatile uint32_t AHB1RSTR;       
  volatile uint32_t AHB2RSTR;       
  volatile uint32_t AHB3RSTR;       
  uint32_t      RESERVED0;      
  volatile uint32_t APB1RSTR;       
  volatile uint32_t APB2RSTR;       
  uint32_t      RESERVED1[2];   
  volatile uint32_t AHB1ENR;        
  volatile uint32_t AHB2ENR;        
  volatile uint32_t AHB3ENR;        
  uint32_t      RESERVED2;      
  volatile uint32_t APB1ENR;        
  volatile uint32_t APB2ENR;        
  uint32_t      RESERVED3[2];   
  volatile uint32_t AHB1LPENR;      
  volatile uint32_t AHB2LPENR;      
  volatile uint32_t AHB3LPENR;      
  uint32_t      RESERVED4;      
  volatile uint32_t APB1LPENR;      
  volatile uint32_t APB2LPENR;      
  uint32_t      RESERVED5[2];   
  volatile uint32_t BDCR;           
  volatile uint32_t CSR;            
  uint32_t      RESERVED6[2];   
  volatile uint32_t SSCGR;          
  volatile uint32_t PLLI2SCFGR;     
} RCC_TypeDef;



 

typedef struct
{
  volatile uint32_t TR;       
  volatile uint32_t DR;       
  volatile uint32_t CR;       
  volatile uint32_t ISR;      
  volatile uint32_t PRER;     
  volatile uint32_t WUTR;     
  volatile uint32_t CALIBR;   
  volatile uint32_t ALRMAR;   
  volatile uint32_t ALRMBR;   
  volatile uint32_t WPR;      
  volatile uint32_t SSR;      
  volatile uint32_t SHIFTR;   
  volatile uint32_t TSTR;     
  volatile uint32_t TSDR;     
  volatile uint32_t TSSSR;    
  volatile uint32_t CALR;     
  volatile uint32_t TAFCR;    
  volatile uint32_t ALRMASSR; 
  volatile uint32_t ALRMBSSR; 
  uint32_t RESERVED7;     
  volatile uint32_t BKP0R;    
  volatile uint32_t BKP1R;    
  volatile uint32_t BKP2R;    
  volatile uint32_t BKP3R;    
  volatile uint32_t BKP4R;    
  volatile uint32_t BKP5R;    
  volatile uint32_t BKP6R;    
  volatile uint32_t BKP7R;    
  volatile uint32_t BKP8R;    
  volatile uint32_t BKP9R;    
  volatile uint32_t BKP10R;   
  volatile uint32_t BKP11R;   
  volatile uint32_t BKP12R;   
  volatile uint32_t BKP13R;   
  volatile uint32_t BKP14R;   
  volatile uint32_t BKP15R;   
  volatile uint32_t BKP16R;   
  volatile uint32_t BKP17R;   
  volatile uint32_t BKP18R;   
  volatile uint32_t BKP19R;   
} RTC_TypeDef;



 

typedef struct
{
  volatile uint32_t POWER;                  
  volatile uint32_t CLKCR;                  
  volatile uint32_t ARG;                    
  volatile uint32_t CMD;                    
  volatile const uint32_t  RESPCMD;         
  volatile const uint32_t  RESP1;           
  volatile const uint32_t  RESP2;           
  volatile const uint32_t  RESP3;           
  volatile const uint32_t  RESP4;           
  volatile uint32_t DTIMER;                 
  volatile uint32_t DLEN;                   
  volatile uint32_t DCTRL;                  
  volatile const uint32_t  DCOUNT;          
  volatile const uint32_t  STA;             
  volatile uint32_t ICR;                    
  volatile uint32_t MASK;                   
  uint32_t      RESERVED0[2];           
  volatile const uint32_t  FIFOCNT;         
  uint32_t      RESERVED1[13];          
  volatile uint32_t FIFO;                   
} SDIO_TypeDef;



 

typedef struct
{
  volatile uint32_t CR1;         
  volatile uint32_t CR2;         
  volatile uint32_t SR;          
  volatile uint32_t DR;          
  volatile uint32_t CRCPR;       
  volatile uint32_t RXCRCR;      
  volatile uint32_t TXCRCR;      
  volatile uint32_t I2SCFGR;     
  volatile uint32_t I2SPR;       
} SPI_TypeDef;




 

typedef struct
{
  volatile uint32_t CR1;          
  volatile uint32_t CR2;          
  volatile uint32_t SMCR;         
  volatile uint32_t DIER;         
  volatile uint32_t SR;           
  volatile uint32_t EGR;          
  volatile uint32_t CCMR1;        
  volatile uint32_t CCMR2;        
  volatile uint32_t CCER;         
  volatile uint32_t CNT;          
  volatile uint32_t PSC;          
  volatile uint32_t ARR;          
  volatile uint32_t RCR;          
  volatile uint32_t CCR1;         
  volatile uint32_t CCR2;         
  volatile uint32_t CCR3;         
  volatile uint32_t CCR4;         
  volatile uint32_t BDTR;         
  volatile uint32_t DCR;          
  volatile uint32_t DMAR;         
  volatile uint32_t OR;           
} TIM_TypeDef;



 

typedef struct
{
  volatile uint32_t SR;          
  volatile uint32_t DR;          
  volatile uint32_t BRR;         
  volatile uint32_t CR1;         
  volatile uint32_t CR2;         
  volatile uint32_t CR3;         
  volatile uint32_t GTPR;        
} USART_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;    
  volatile uint32_t CFR;   
  volatile uint32_t SR;    
} WWDG_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;   
  volatile uint32_t SR;   
  volatile uint32_t DR;   
} RNG_TypeDef;



 
typedef struct
{
  volatile uint32_t GOTGCTL;               
  volatile uint32_t GOTGINT;               
  volatile uint32_t GAHBCFG;               
  volatile uint32_t GUSBCFG;               
  volatile uint32_t GRSTCTL;               
  volatile uint32_t GINTSTS;               
  volatile uint32_t GINTMSK;               
  volatile uint32_t GRXSTSR;               
  volatile uint32_t GRXSTSP;               
  volatile uint32_t GRXFSIZ;               
  volatile uint32_t DIEPTXF0_HNPTXFSIZ;    
  volatile uint32_t HNPTXSTS;              
  uint32_t Reserved30[2];              
  volatile uint32_t GCCFG;                 
  volatile uint32_t CID;                   
  uint32_t  Reserved40[48];            
  volatile uint32_t HPTXFSIZ;              
  volatile uint32_t DIEPTXF[0x0F];         
} USB_OTG_GlobalTypeDef;



 
typedef struct
{
  volatile uint32_t DCFG;             
  volatile uint32_t DCTL;             
  volatile uint32_t DSTS;             
  uint32_t Reserved0C;            
  volatile uint32_t DIEPMSK;          
  volatile uint32_t DOEPMSK;          
  volatile uint32_t DAINT;            
  volatile uint32_t DAINTMSK;         
  uint32_t  Reserved20;           
  uint32_t Reserved9;             
  volatile uint32_t DVBUSDIS;         
  volatile uint32_t DVBUSPULSE;       
  volatile uint32_t DTHRCTL;          
  volatile uint32_t DIEPEMPMSK;       
  volatile uint32_t DEACHINT;         
  volatile uint32_t DEACHMSK;         
  uint32_t Reserved40;            
  volatile uint32_t DINEP1MSK;        
  uint32_t  Reserved44[15];       
  volatile uint32_t DOUTEP1MSK;       
} USB_OTG_DeviceTypeDef;



 
typedef struct
{
  volatile uint32_t DIEPCTL;            
  uint32_t Reserved04;              
  volatile uint32_t DIEPINT;            
  uint32_t Reserved0C;              
  volatile uint32_t DIEPTSIZ;           
  volatile uint32_t DIEPDMA;            
  volatile uint32_t DTXFSTS;            
  uint32_t Reserved18;              
} USB_OTG_INEndpointTypeDef;



 
typedef struct
{
  volatile uint32_t DOEPCTL;        
  uint32_t Reserved04;          
  volatile uint32_t DOEPINT;        
  uint32_t Reserved0C;          
  volatile uint32_t DOEPTSIZ;       
  volatile uint32_t DOEPDMA;        
  uint32_t Reserved18[2];       
} USB_OTG_OUTEndpointTypeDef;



 
typedef struct
{
  volatile uint32_t HCFG;              
  volatile uint32_t HFIR;              
  volatile uint32_t HFNUM;             
  uint32_t Reserved40C;            
  volatile uint32_t HPTXSTS;           
  volatile uint32_t HAINT;             
  volatile uint32_t HAINTMSK;          
} USB_OTG_HostTypeDef;



 
typedef struct
{
  volatile uint32_t HCCHAR;            
  volatile uint32_t HCSPLT;            
  volatile uint32_t HCINT;             
  volatile uint32_t HCINTMSK;          
  volatile uint32_t HCTSIZ;            
  volatile uint32_t HCDMA;             
  uint32_t Reserved[2];            
} USB_OTG_HostChannelTypeDef;



 



 
#line 825 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 



 





 
#line 864 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 874 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 883 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 915 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 


 






 

 



#line 944 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"






 



 
#line 991 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 1038 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 



 



 



 



 

 
 
 

 
 
 
 
 


 


 
#line 1092 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1146 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1196 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1252 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1314 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 




 




 




 




 
#line 1385 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1435 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1485 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1524 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 




 




 
#line 1552 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1608 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 1649 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1657 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 



 
 
 
 
 
 
 
#line 1699 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 1727 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1777 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 1790 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 1803 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1817 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1831 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1876 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1887 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 1894 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 1901 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1930 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


 
 
#line 1949 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1960 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1974 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1988 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2005 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2016 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2030 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2044 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2061 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2072 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2086 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2100 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2114 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2125 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2139 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2153 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2167 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2178 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2192 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2206 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
 
#line 2215 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2304 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2393 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2482 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2571 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


 
#line 2670 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2768 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2866 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2964 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 3062 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 3160 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 3258 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 3356 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 3454 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 3552 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 3650 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 3748 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 3846 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 3944 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 4042 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 4140 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 4238 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 4336 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 4434 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 4532 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 4630 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 4728 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 4826 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 4924 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5022 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5120 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5218 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5316 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
 
 
 
 
 





 





 




 
 
 
 
 


 

 
#line 5358 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 5365 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







#line 5379 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 5395 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 5402 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







#line 5416 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 5423 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5431 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 




 




 




 




 
#line 5469 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5477 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5485 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 
#line 5503 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


 
 
 
 
 
 
#line 5583 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 5609 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5628 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5690 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5752 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5814 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5876 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 





 
 
 
 
 
 
#line 5968 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5996 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6067 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6092 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6163 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6234 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6305 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6376 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
 
 
 
 
 
#line 6394 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


#line 6411 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6434 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6469 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6477 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6518 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6535 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 6545 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
 
 
 
 
 
#line 6558 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"













#line 6607 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6615 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"













#line 6664 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6672 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"













#line 6721 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6729 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"













#line 6778 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6787 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6795 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6807 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6815 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6823 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6831 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 6846 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6854 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6866 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6874 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6882 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6890 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 6905 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6913 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6925 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6933 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6941 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6949 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 6964 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6972 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6984 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6992 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7000 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7008 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 7023 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7031 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7043 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7051 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 7066 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7074 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7086 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7094 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 7109 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7117 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7129 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7137 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 7152 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7160 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7172 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7180 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 7197 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"











#line 7215 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7223 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7230 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7241 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"











#line 7259 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7267 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7274 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7285 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"











#line 7303 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7311 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7318 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7341 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7364 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7387 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7400 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7412 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7424 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7436 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7449 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7461 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7473 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7485 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7498 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7510 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7522 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7534 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7547 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7559 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7571 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7583 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7596 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7608 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7620 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7632 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7645 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7657 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7669 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7681 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7694 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7706 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7718 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7730 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 
 
 
 
 
 
#line 7827 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7909 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7959 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7977 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8059 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8109 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8191 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8241 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8291 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8309 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8359 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 8376 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8474 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8556 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 8608 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 8665 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8707 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8765 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8807 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


 
 
 
 
 
 
#line 8857 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8868 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 8884 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 



#line 8919 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"





 
#line 8931 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 8980 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9006 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9017 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 





 
 
 
 
 
 




 
#line 9041 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 9054 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
 
 
 
 
 
#line 9078 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 9085 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9104 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 


 
#line 9130 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 


 
 
 
 
 
 
#line 9146 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 9155 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 9167 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 9186 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


 


#line 9197 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9208 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 9221 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







#line 9235 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 9243 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


 
 










 










 
#line 9276 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 9286 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9294 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 9308 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 9324 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 










#line 9342 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 9349 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 9375 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 9397 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 9416 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"





 
#line 9461 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9469 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 





 
#line 9545 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9580 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 


 
#line 9633 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 


 


#line 9645 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 


 






 
#line 9726 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9767 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9817 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 9824 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9832 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 9908 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9949 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9960 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







#line 9973 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10005 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 



 
#line 10022 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10036 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 10043 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


 
 
 
 
 
 
#line 10057 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10074 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
 
 
 
 


 


 
#line 10127 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10171 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10241 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 


 
#line 10294 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10302 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 10315 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10385 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10455 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 
#line 10473 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10516 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10546 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 10574 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10622 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 


 
#line 10637 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10649 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 



 
 
 
 
 
 






 
#line 10779 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







#line 10792 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 










#line 10830 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 




 




 




 




 




 




 
#line 10884 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 10892 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 10905 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 10984 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11025 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11099 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 
 
 
 
 


 
#line 11127 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 11134 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 11165 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11188 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11217 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 




 




 






























#line 11275 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11286 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
 
 
 
 
 





 



 


 
#line 11318 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


 
#line 11330 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11343 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11356 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11369 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11383 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11396 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11409 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11422 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11435 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11449 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11462 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11475 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11488 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11501 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11515 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11527 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11539 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11551 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11563 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11571 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
 
 
 
 
 
#line 11593 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

















 
#line 11620 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 11627 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 11652 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11660 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 11667 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"





#line 11679 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







#line 11692 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11739 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11777 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11803 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 






#line 11817 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 11824 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"











#line 11841 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 11848 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"





 







#line 11868 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







#line 11882 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 






#line 11896 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 11903 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"











#line 11920 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 11927 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"





 







#line 11947 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







#line 11961 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12008 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 




 




 




 




 




 




 
#line 12061 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







#line 12086 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12096 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 12105 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 






#line 12128 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


 
 
 
 
 
 
#line 12166 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 12179 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12226 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12249 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"











 
#line 12297 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12310 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"





 
 
 
 
 
 
#line 12331 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 12339 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"





 
#line 12355 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 12363 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"






 







 





 
 
 
 
 
 
#line 12395 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12409 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 12468 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 


 
#line 12487 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
 
 
 
 
 
#line 12524 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 

#line 12535 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 

#line 12546 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 12557 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"





















 
#line 12588 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12608 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12622 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 12644 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 12657 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




#line 12674 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12696 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 

#line 12760 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12777 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


#line 12793 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12819 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12835 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 12847 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 12890 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 12969 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13049 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13057 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 13076 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13084 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 
#line 13108 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




#line 13130 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 13141 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13149 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 13165 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 13181 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 13194 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13214 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13222 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 13256 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13285 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 13294 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 13302 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 13343 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13351 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13365 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 13374 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 13400 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




#line 13419 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"













#line 13451 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 

#line 13464 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 13475 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 13487 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13522 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13563 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13598 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 

#line 13610 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 13625 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 




 
#line 13648 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 

#line 13689 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13724 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 

#line 13732 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 13749 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
 
#line 13762 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







#line 13776 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 13784 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 13792 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


 



 



 

 








 


 


 



 
#line 13840 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13851 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 


 




 


 


 


 



 





 
#line 13899 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13913 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13923 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13931 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13939 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 



 
#line 13951 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13961 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13969 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13977 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13985 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13995 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 14005 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 



 
#line 14016 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 14079 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 14091 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 14099 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 14113 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 14126 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 14136 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 14144 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 14154 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 14164 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 



 
#line 14178 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 14185 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 



 





 
#line 14202 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 


 




 


 





 
#line 14227 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


 



 



 


 


 


 







 



#line 14265 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



















 
 
 
 
 
 
 
 


 




 



 



 





#line 129 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"
#line 176 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"



 



 
typedef enum
{
  RESET = 0U,
  SET = !RESET
} FlagStatus, ITStatus;

typedef enum
{
  DISABLE = 0U,
  ENABLE = !DISABLE
} FunctionalState;


typedef enum
{
  SUCCESS = 0U,
  ERROR = !SUCCESS
} ErrorStatus;



 




 
















 
 
#line 236 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"

 
#line 245 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"

 
#line 254 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"

 
#line 263 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"

 
#line 272 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"

 
#line 281 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"



 

#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h"

















  

 
#line 296 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h"


#line 288 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"









 



 
#line 30 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_def.h"
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

















 

 







 
 
 



 
#line 46 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 
#line 93 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 101 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"
















 



 





 



 
#line 150 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 217 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"







 



 
#line 235 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 
#line 249 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 






 



 

#line 277 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"






#line 289 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"














 



 
#line 322 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"





#line 367 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 377 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 439 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"






 



 

#line 567 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 

#line 584 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 

#line 609 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 618 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 717 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"




 




 
#line 738 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 





 



 


















#line 789 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"





#line 801 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 808 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"









#line 824 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 839 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 
#line 867 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 
#line 883 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 892 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"





#line 907 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1019 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1035 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 
#line 1060 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 





 



 






 



 















 
 







 



 








 



 














 



 










 



 







































 



 


#line 1217 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"






 



 

 
#line 1239 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

 












 



 

































#line 1300 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"
















#line 1322 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 




 















 




 
#line 1363 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 









#line 1393 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 



#line 1431 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1441 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1460 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"










#line 1487 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"







 



 




 



 

























 




 








 



 




 



 
#line 1571 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 

#line 1588 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1600 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1641 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"





 



 











 

#line 1691 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1705 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 

 



 



 



 








 




 




 



 
#line 1756 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

 





































 



 
#line 1826 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 
#line 1841 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 









#line 1874 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1885 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 

#line 1915 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1923 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"






#line 1939 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



#line 2028 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 
#line 2042 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 





 



 



 



 
#line 2081 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 



 



 






 




 



 

 



 





 



 
#line 2142 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"









 




 
#line 2170 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 2191 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 2202 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 2211 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 2224 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 2233 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 







 



 
#line 2269 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 2284 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


#line 2317 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 
#line 2485 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



#line 2495 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 

#line 2511 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 







 



 

#line 2534 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 

#line 2562 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 










 



 














 




 




 




 







 




 
#line 2640 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 




 
#line 2690 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 2704 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 




 








#line 2984 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 2998 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3215 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3234 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3241 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3262 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3410 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

 



#line 3435 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3456 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3573 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3582 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3599 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3614 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"






#line 3643 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

















#line 3669 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"





#line 3696 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"





#line 3708 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3717 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3750 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3768 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"












#line 3786 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3809 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3849 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3935 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 




 



 
#line 3961 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3989 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3996 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 4011 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"











 



 




#line 4039 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 4061 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"
 




#line 4091 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 4098 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 4110 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 

#line 4124 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"








 



 
#line 4145 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 







 



 













 




 









#line 4199 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 












#line 4225 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 4234 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 4243 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"




#line 4276 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 








#line 4303 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"







 



 

#line 4323 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"






 



 




 



 
#line 4357 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 







 



 
#line 4384 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 





 



 





 



 



 








#line 31 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_def.h"
#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"
 






 

 
 
 





 





#line 34 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"




  typedef signed int ptrdiff_t;



  



    typedef unsigned int size_t;    
#line 57 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"



   



      typedef unsigned short wchar_t;  
#line 82 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"



    




   




  typedef long double max_align_t;









#line 114 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"



 

#line 32 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_def.h"

 



   
typedef enum 
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;



 
typedef enum 
{
  HAL_UNLOCKED = 0x00U,
  HAL_LOCKED   = 0x01U  
} HAL_LockTypeDef;

 






























 


#line 104 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_def.h"







#line 126 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_def.h"


 
#line 155 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_def.h"




  









 


#line 188 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_def.h"



  



 


#line 205 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_def.h"








#line 28 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

 
 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"















 

 







 
#line 28 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"



 



 

 


 



 
typedef struct
{
  uint32_t PLLState;   
 

  uint32_t PLLSource;  
 

  uint32_t PLLM;       
 

  uint32_t PLLN;       

 

  uint32_t PLLP;       
 

  uint32_t PLLQ;       
 
#line 73 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
} RCC_PLLInitTypeDef;

#line 174 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 200 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 291 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 376 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"





 
typedef struct
{





  uint32_t PLLI2SN;    


 

  uint32_t PLLI2SR;    

 

} RCC_PLLI2SInitTypeDef;



 
typedef struct
{
  uint32_t PeriphClockSelection; 
 

  RCC_PLLI2SInitTypeDef PLLI2S;  
 

  uint32_t RTCClockSelection;      
 




} RCC_PeriphCLKInitTypeDef;



 

 


 



 
 
#line 452 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 462 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 479 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 493 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 505 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 517 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 


 






 




 





 
#line 546 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 



 
#line 560 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 



 
#line 573 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 

#line 598 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 627 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 720 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 775 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 854 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 888 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 905 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 920 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"








 






 




#line 952 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"



 

 


 
 
#line 2026 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 







 
#line 2168 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 







 
#line 2189 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 2222 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 







 






#line 2247 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 2258 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 2277 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 








 











#line 2307 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 







 
#line 2326 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 







 




 







 
#line 2478 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 







 
#line 2505 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 2522 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 







 
#line 2575 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 2582 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 







 
#line 2599 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 2606 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 




 
#line 2628 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 2637 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 




 
#line 2652 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"






#line 2665 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"








 




 







 




 
#line 2709 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 2726 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 




 












 








 
#line 2772 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 2789 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 








 











#line 2819 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 








 




 








 
#line 2861 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 2878 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 








 
#line 2896 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 2903 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 

 

 
#line 3288 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 3571 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 3950 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 4757 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 5795 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 5841 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"




























 
#line 5876 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 








 



#line 5959 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"














 





#line 6004 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 6027 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 6117 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 6136 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 6155 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 6167 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 











 








 



#line 6226 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 6391 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 6440 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 6674 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 6729 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 6753 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

 

#line 6780 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 6793 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"



 

 


 



 
HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);

uint32_t HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk);

#line 6818 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
HAL_StatusTypeDef HAL_RCCEx_EnablePLLI2S(RCC_PLLI2SInitTypeDef  *PLLI2SInit);
HAL_StatusTypeDef HAL_RCCEx_DisablePLLI2S(void);







 



 
 
 
 


 




 
 
#line 6852 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"






 






 
#line 6878 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

 





 







#line 6904 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 6914 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"




 



 

 


 


 





































#line 6987 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 6995 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 7015 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 7067 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 7088 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 7152 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"




















 



 



 



 






#line 32 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"



 



 

 


 



 
typedef struct
{
  uint32_t OscillatorType;       
 

  uint32_t HSEState;             
 

  uint32_t LSEState;             
 

  uint32_t HSIState;             
 

  uint32_t HSICalibrationValue;  
 

  uint32_t LSIState;             
 

  RCC_PLLInitTypeDef PLL;         
} RCC_OscInitTypeDef;



 
typedef struct
{
  uint32_t ClockType;             
 

  uint32_t SYSCLKSource;          
 

  uint32_t AHBCLKDivider;         
 

  uint32_t APB1CLKDivider;        
 

  uint32_t APB2CLKDivider;        
 

} RCC_ClkInitTypeDef;



 

 


 



 







 



 





 



 





 



 






 



 




 



 





 



 






 



 




 



 






 





 






 





 






 



 
#line 234 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 



 







 



 
#line 287 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 



 




 



 






 



 







 



 
#line 333 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 









 
 





 


 
#line 364 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 



 

 


 







 
#line 426 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 433 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 







 
#line 450 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 457 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 







 
#line 517 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 525 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 







 
#line 543 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 551 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 







 
#line 618 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 627 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 







 
#line 646 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 655 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 




 
#line 669 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 677 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 




 
#line 692 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 701 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 




 
#line 717 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 727 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 








 
#line 745 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 752 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 








 
#line 771 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 779 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 








 
#line 799 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 808 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 



 















 









 




 



 








 




 



 





















 
#line 907 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 



 


















 
#line 950 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 



 



 























 













 






 






 




 



 







 










 










 



 



 









 










 







 



 



 















 




















 




 




 











 












 













 













 




 



















 







 



 

 


 



 
 
HAL_StatusTypeDef HAL_RCC_DeInit(void);
HAL_StatusTypeDef HAL_RCC_OscConfig(const RCC_OscInitTypeDef *RCC_OscInitStruct);
HAL_StatusTypeDef HAL_RCC_ClockConfig(const RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FLatency);


 



 
 
void     HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);
void     HAL_RCC_EnableCSS(void);
void     HAL_RCC_DisableCSS(void);
uint32_t HAL_RCC_GetSysClockFreq(void);
uint32_t HAL_RCC_GetHCLKFreq(void);
uint32_t HAL_RCC_GetPCLK1Freq(void);
uint32_t HAL_RCC_GetPCLK2Freq(void);
void     HAL_RCC_GetOscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
void     HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t *pFLatency);

 
void HAL_RCC_NMI_IRQHandler(void);

 
void HAL_RCC_CSSCallback(void);



 



 

 
 
 


 




 

 
 



 


 



 
 



 



 
 




 


 


 


 












 



 

 


 



 






















#line 1408 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"































 



 



 



 







#line 276 "../Core/Inc/stm32f4xx_hal_conf.h"


#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio.h"
















  

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio.h"



 



  

 


 



  
typedef struct
{
  uint32_t Pin;       
 

  uint32_t Mode;      
 

  uint32_t Pull;      
 

  uint32_t Speed;     
 

  uint32_t Alternate;  
 
}GPIO_InitTypeDef;



 
typedef enum
{
  GPIO_PIN_RESET = 0,
  GPIO_PIN_SET
}GPIO_PinState;


 

 



  



 
#line 102 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio.h"




 









  







    



 






 




 






 

 


   





 
  


 

 


 






 







 







 







 







 



 

 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
















  

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"



 



  

 
 


 
  


 

 
#line 165 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 

 
#line 280 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 

 
#line 386 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 

 



  








  





  






  







  






  






  





  







  






  








  





  






  



 

 
#line 572 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 

 
#line 681 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"

 

 
#line 815 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"

 
#line 907 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"

 
#line 981 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"

 
#line 1101 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 

 
#line 1224 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 


  



 

 


 


 

 


 


 

 
 
 


 


 

 


 


 
#line 1276 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"

#line 1290 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"







#line 1304 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"

#line 1332 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"



 



   
 
#line 1366 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 

 
#line 1393 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 

 
#line 1417 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 

 
#line 1438 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"



 

 
#line 1460 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 
 




 
#line 1485 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 

 
#line 1517 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 

 
#line 1546 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 

 



 

 



 



  



 

 


 



 



  



  
  






#line 214 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio.h"

 


 



 
 
void  HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void  HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin);


 



 
 
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
HAL_StatusTypeDef HAL_GPIO_LockPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);



  



  
 
 
 


 
#line 272 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio.h"



 

 


 
#line 299 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio.h"


 

 


 



 



  



 







#line 280 "../Core/Inc/stm32f4xx_hal_conf.h"


#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_exti.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_exti.h"



 




 

 



 
typedef enum
{
  HAL_EXTI_COMMON_CB_ID          = 0x00U
} EXTI_CallbackIDTypeDef;



 
typedef struct
{
  uint32_t Line;                     
  void (* PendingCallback)(void);    
} EXTI_HandleTypeDef;



 
typedef struct
{
  uint32_t Line;      
 
  uint32_t Mode;      
 
  uint32_t Trigger;   
 
  uint32_t GPIOSel;   

 
} EXTI_ConfigTypeDef;



 

 


 



 
#line 124 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_exti.h"



 



 





 



 







 




 
#line 182 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_exti.h"



 



 

 


 



 

 


 


 








 




 




 




 








 

 


 














#line 309 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_exti.h"




 

 



 




 
 
HAL_StatusTypeDef HAL_EXTI_SetConfigLine(EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig);
HAL_StatusTypeDef HAL_EXTI_GetConfigLine(EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig);
HAL_StatusTypeDef HAL_EXTI_ClearConfigLine(EXTI_HandleTypeDef *hexti);
HAL_StatusTypeDef HAL_EXTI_RegisterCallback(EXTI_HandleTypeDef *hexti, EXTI_CallbackIDTypeDef CallbackID, void (*pPendingCbfn)(void));
HAL_StatusTypeDef HAL_EXTI_GetHandle(EXTI_HandleTypeDef *hexti, uint32_t ExtiLine);


 




 
 
void HAL_EXTI_IRQHandler(EXTI_HandleTypeDef *hexti);
uint32_t HAL_EXTI_GetPending(EXTI_HandleTypeDef *hexti, uint32_t Edge);
void HAL_EXTI_ClearPending(EXTI_HandleTypeDef *hexti, uint32_t Edge);
void HAL_EXTI_GenerateSWI(EXTI_HandleTypeDef *hexti);



 



 



 



 







#line 284 "../Core/Inc/stm32f4xx_hal_conf.h"


#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"
















  

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"



 



  

 




 
   


 
typedef struct
{
  uint32_t Channel;              
 

  uint32_t Direction;            

 

  uint32_t PeriphInc;            
 

  uint32_t MemInc;               
 

  uint32_t PeriphDataAlignment;  
 

  uint32_t MemDataAlignment;     
 

  uint32_t Mode;                 


 

  uint32_t Priority;             
 

  uint32_t FIFOMode;             


 

  uint32_t FIFOThreshold;        
 

  uint32_t MemBurst;             



 

  uint32_t PeriphBurst;          



 
}DMA_InitTypeDef;




 
typedef enum
{
  HAL_DMA_STATE_RESET             = 0x00U,   
  HAL_DMA_STATE_READY             = 0x01U,   
  HAL_DMA_STATE_BUSY              = 0x02U,   
  HAL_DMA_STATE_TIMEOUT           = 0x03U,   
  HAL_DMA_STATE_ERROR             = 0x04U,   
  HAL_DMA_STATE_ABORT             = 0x05U,   
}HAL_DMA_StateTypeDef;



 
typedef enum
{
  HAL_DMA_FULL_TRANSFER           = 0x00U,   
  HAL_DMA_HALF_TRANSFER           = 0x01U    
}HAL_DMA_LevelCompleteTypeDef;



 
typedef enum
{
  HAL_DMA_XFER_CPLT_CB_ID         = 0x00U,   
  HAL_DMA_XFER_HALFCPLT_CB_ID     = 0x01U,   
  HAL_DMA_XFER_M1CPLT_CB_ID       = 0x02U,   
  HAL_DMA_XFER_M1HALFCPLT_CB_ID   = 0x03U,   
  HAL_DMA_XFER_ERROR_CB_ID        = 0x04U,   
  HAL_DMA_XFER_ABORT_CB_ID        = 0x05U,   
  HAL_DMA_XFER_ALL_CB_ID          = 0x06U    
}HAL_DMA_CallbackIDTypeDef;



 
typedef struct __DMA_HandleTypeDef
{
  DMA_Stream_TypeDef         *Instance;                                                         

  DMA_InitTypeDef            Init;                                                               

  HAL_LockTypeDef            Lock;                                                                

  volatile HAL_DMA_StateTypeDef  State;                                                             

  void                       *Parent;                                                            

  void                       (* XferCpltCallback)( struct __DMA_HandleTypeDef * hdma);          

  void                       (* XferHalfCpltCallback)( struct __DMA_HandleTypeDef * hdma);      

  void                       (* XferM1CpltCallback)( struct __DMA_HandleTypeDef * hdma);        
  
  void                       (* XferM1HalfCpltCallback)( struct __DMA_HandleTypeDef * hdma);    
  
  void                       (* XferErrorCallback)( struct __DMA_HandleTypeDef * hdma);         
  
  void                       (* XferAbortCallback)( struct __DMA_HandleTypeDef * hdma);           

  volatile uint32_t              ErrorCode;                                                         
  
  uint32_t                   StreamBaseAddress;                                                 

  uint32_t                   StreamIndex;                                                       
 
}DMA_HandleTypeDef;



 

 




 




  
#line 193 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"


 




  
#line 219 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"


 




  





 
        



  




  




  




 




  





  




 





 




  





 




 






  




 




  




 






  




  






  




  






 




 







 




  
#line 382 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"


 



 
 
 




 













 






 






 


 





 
#line 447 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"





       
#line 467 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"





 
#line 487 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"





 
#line 507 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"





 
#line 527 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"













 

















 
















 














 














 




















 







 



 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma_ex.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma_ex.h"



 



  

 



 
   


  
typedef enum
{
  MEMORY0      = 0x00U,     
  MEMORY1      = 0x01U      
}HAL_DMA_MemoryTypeDef;



 

 



 




 

 
HAL_StatusTypeDef HAL_DMAEx_MultiBufferStart(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t SecondMemAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMAEx_MultiBufferStart_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t SecondMemAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMAEx_ChangeMemory(DMA_HandleTypeDef *hdma, uint32_t Address, HAL_DMA_MemoryTypeDef memory);



 


 
         
 



 


 



 



 







#line 640 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"

 




 




 
HAL_StatusTypeDef HAL_DMA_Init(DMA_HandleTypeDef *hdma); 
HAL_StatusTypeDef HAL_DMA_DeInit(DMA_HandleTypeDef *hdma);


 




 
HAL_StatusTypeDef HAL_DMA_Start (DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMA_Start_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMA_Abort(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_Abort_IT(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_PollForTransfer(DMA_HandleTypeDef *hdma, HAL_DMA_LevelCompleteTypeDef CompleteLevel, uint32_t Timeout);
void              HAL_DMA_IRQHandler(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_CleanCallbacks(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_RegisterCallback(DMA_HandleTypeDef *hdma, HAL_DMA_CallbackIDTypeDef CallbackID, void (* pCallback)(DMA_HandleTypeDef *_hdma));
HAL_StatusTypeDef HAL_DMA_UnRegisterCallback(DMA_HandleTypeDef *hdma, HAL_DMA_CallbackIDTypeDef CallbackID);



  




 
HAL_DMA_StateTypeDef HAL_DMA_GetState(DMA_HandleTypeDef *hdma);
uint32_t             HAL_DMA_GetError(DMA_HandleTypeDef *hdma);


  


  
 



 


  

 



 
#line 729 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"

















































  

 



 


 



  



 







#line 288 "../Core/Inc/stm32f4xx_hal_conf.h"


#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cortex.h"















  

 







 
#line 28 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cortex.h"



 



  
 


 





 
typedef struct
{
  uint8_t                Enable;                
 
  uint8_t                Number;                
 
  uint32_t               BaseAddress;            
  uint8_t                Size;                  
 
  uint8_t                SubRegionDisable;      
          
  uint8_t                TypeExtField;          
                  
  uint8_t                AccessPermission;      
 
  uint8_t                DisableExec;           
 
  uint8_t                IsShareable;           
 
  uint8_t                IsCacheable;           
 
  uint8_t                IsBufferable;          
 
}MPU_Region_InitTypeDef;


 




 

 



 



 
#line 98 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cortex.h"


 



 





 




 







 



 




 



 




 



 




 



 




 



 




 



 





 



 
#line 211 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cortex.h"


 
   


 
#line 224 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cortex.h"


 



 
#line 239 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cortex.h"


 




 


 

 


 
  


 
 
void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup);
void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority);
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn);
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn);
void HAL_NVIC_SystemReset(void);
uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb);


 



 
 
uint32_t HAL_NVIC_GetPriorityGrouping(void);
void HAL_NVIC_GetPriority(IRQn_Type IRQn, uint32_t PriorityGroup, uint32_t* pPreemptPriority, uint32_t* pSubPriority);
uint32_t HAL_NVIC_GetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn);
uint32_t HAL_NVIC_GetActive(IRQn_Type IRQn);
void HAL_SYSTICK_CLKSourceConfig(uint32_t CLKSource);
void HAL_SYSTICK_IRQHandler(void);
void HAL_SYSTICK_Callback(void);


void HAL_MPU_Enable(uint32_t MPU_Control);
void HAL_MPU_Disable(void);
void HAL_MPU_EnableRegion(uint32_t RegionNumber);
void HAL_MPU_DisableRegion(uint32_t RegionNumber);
void HAL_MPU_ConfigRegion(MPU_Region_InitTypeDef *MPU_Init);

void HAL_CORTEX_ClearEvent(void);


 



 

 
 
 
 


 



































#line 348 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cortex.h"

#line 357 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cortex.h"

#line 386 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cortex.h"






 

 



  



 
  





 

#line 292 "../Core/Inc/stm32f4xx_hal_conf.h"


#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"

 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"



 





 

 
 

 


 

 
 
 
 

 
 








 
 
#line 81 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"

 
 
 
 
 

 
 





 
 









 
 
 
 


 
 
 





 
 
 





 





 
 
 
 


 
 
 





 
 
 





 



 
 
 
 
 
 
 



 


 





 
 







 
 
#line 209 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"

 
 
#line 231 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"

 
 
 
 
 
 

 







 




 



 
 


 








 


 


 








 










 





 


 
#line 492 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"

 


 




 
#line 522 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 




 






 



 
 
 
 






 



 






 



 
 
 
 
 
 






 



 






 



 




 



 




 



 





 



 
#line 648 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 



 
#line 672 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 



 





 



 




 



 





 



 




 



 
#line 733 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 



 
#line 749 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 



 
#line 772 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 



 
#line 796 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 



 





 



 




 




 






 



 




 



 






 



 
#line 862 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 



 



 



 
#line 954 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 



 




 




 
#line 987 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 



 
#line 1001 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 



 
#line 1024 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 



 





 










 

 
 
 
 
 
 
 
 
 
 
 
 

 
 
 
 


 
 
 
 




 



 


 


 



 







 







 



 



 





































 







































 
#line 1205 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"














































 






























































 


























 
#line 1348 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"




















































































































 
#line 1474 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"



















 





















 
















 













 
#line 1557 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"

















 
#line 1588 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"













 




















 





















 
#line 1651 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"

























 
#line 1683 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"

 
 
 













































 
#line 1747 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"












































 
#line 1809 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"



 



 


 


 



 
 
 
 






























 

static __inline uint32_t LL_ADC_DMA_GetRegAddr(const ADC_TypeDef *ADCx, uint32_t Register)
{
  uint32_t data_reg_addr = 0UL;

  if (Register == 0x00000000UL)
  {
     
    data_reg_addr = (uint32_t) & (ADCx->DR);
  }
  else  
  {
     
    data_reg_addr = (uint32_t) & (((((ADC_Common_TypeDef *) ((0x40000000UL + 0x00010000UL) + 0x2300UL))))->CDR);
  }

  return data_reg_addr;
}
#line 1889 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"



 



 












 
static __inline void LL_ADC_SetCommonClock(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t CommonClock)
{
  (((ADCxy_COMMON->CCR)) = ((((((ADCxy_COMMON->CCR))) & (~((0x3UL << (16U))))) | (CommonClock))));
}











 
static __inline uint32_t LL_ADC_GetCommonClock(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (uint32_t)(((ADCxy_COMMON->CCR) & ((0x3UL << (16U)))));
}




























 
static __inline void LL_ADC_SetCommonPathInternalCh(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t PathInternal)
{
  (((ADCxy_COMMON->CCR)) = ((((((ADCxy_COMMON->CCR))) & (~((0x1UL << (23U)) | (0x1UL << (22U))))) | (PathInternal))));
}
















 
static __inline uint32_t LL_ADC_GetCommonPathInternalCh(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (uint32_t)(((ADCxy_COMMON->CCR) & ((0x1UL << (23U)) | (0x1UL << (22U)))));
}



 



 













 
static __inline void LL_ADC_SetResolution(ADC_TypeDef *ADCx, uint32_t Resolution)
{
  (((ADCx->CR1)) = ((((((ADCx->CR1))) & (~((0x3UL << (24U))))) | (Resolution))));
}












 
static __inline uint32_t LL_ADC_GetResolution(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR1) & ((0x3UL << (24U)))));
}











 
static __inline void LL_ADC_SetDataAlignment(ADC_TypeDef *ADCx, uint32_t DataAlignment)
{
  (((ADCx->CR2)) = ((((((ADCx->CR2))) & (~((0x1UL << (11U))))) | (DataAlignment))));
}










 
static __inline uint32_t LL_ADC_GetDataAlignment(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR2) & ((0x1UL << (11U)))));
}





















 
static __inline void LL_ADC_SetSequencersScanMode(ADC_TypeDef *ADCx, uint32_t ScanMode)
{
  (((ADCx->CR1)) = ((((((ADCx->CR1))) & (~((0x1UL << (8U))))) | (ScanMode))));
}




















 
static __inline uint32_t LL_ADC_GetSequencersScanMode(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR1) & ((0x1UL << (8U)))));
}



 



 































 
static __inline void LL_ADC_REG_SetTriggerSource(ADC_TypeDef *ADCx, uint32_t TriggerSource)
{
   
   
   
   
   
  (((ADCx->CR2)) = ((((((ADCx->CR2))) & (~((0xFUL << (24U))))) | ((TriggerSource & (0xFUL << (24U)))))));
}


































 
static __inline uint32_t LL_ADC_REG_GetTriggerSource(const ADC_TypeDef *ADCx)
{
  uint32_t TriggerSource = ((ADCx->CR2) & ((0xFUL << (24U)) | (0x3UL << (28U))));

   
   
  uint32_t ShiftExten = ((TriggerSource & (0x3UL << (28U))) >> ((28UL) - 2UL));

   
   
  return ((TriggerSource
           & ((((0x00000000UL & (0xFUL << (24U))) >> (4UL * 0UL)) | (((0xFUL << (24U))) >> (4UL * 1UL)) | (((0xFUL << (24U))) >> (4UL * 2UL)) | (((0xFUL << (24U))) >> (4UL * 3UL))) << ShiftExten) & (0xFUL << (24U)))
          | (((((0x00000000UL & (0x3UL << (28U))) >> (4UL * 0UL)) | ((((0x1UL << (28U)))) >> (4UL * 1UL)) | ((((0x1UL << (28U)))) >> (4UL * 2UL)) | ((((0x1UL << (28U)))) >> (4UL * 3UL))) << ShiftExten) & (0x3UL << (28U)))
         );
}











 
static __inline uint32_t LL_ADC_REG_IsTriggerSourceSWStart(const ADC_TypeDef *ADCx)
{
  return (((ADCx->CR2) & ((0x3UL << (28U)))) == (0x00000000UL & (0x3UL << (28U))));
}












 
static __inline uint32_t LL_ADC_REG_GetTriggerEdge(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR2) & ((0x3UL << (28U)))));
}

























































 
static __inline void LL_ADC_REG_SetSequencerLength(ADC_TypeDef *ADCx, uint32_t SequencerNbRanks)
{
  (((ADCx->SQR1)) = ((((((ADCx->SQR1))) & (~((0xFUL << (20U))))) | (SequencerNbRanks))));
}























































 
static __inline uint32_t LL_ADC_REG_GetSequencerLength(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->SQR1) & ((0xFUL << (20U)))));
}























 
static __inline void LL_ADC_REG_SetSequencerDiscont(ADC_TypeDef *ADCx, uint32_t SeqDiscont)
{
  (((ADCx->CR1)) = ((((((ADCx->CR1))) & (~((0x1UL << (11U)) | (0x7UL << (13U))))) | (SeqDiscont))));
}


















 
static __inline uint32_t LL_ADC_REG_GetSequencerDiscont(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR1) & ((0x1UL << (11U)) | (0x7UL << (13U)))));
}














































































 
static __inline void LL_ADC_REG_SetSequencerRanks(ADC_TypeDef *ADCx, uint32_t Rank, uint32_t Channel)
{
   
   
   
   
  volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->SQR1)) + (((((Rank) & ((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))) >> (__clz(__rbit(((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))))))) << 2UL))));

  (((*preg)) = ((((((*preg))) & (~(((0x1FUL << (0U))) << (Rank & (0x0000001FU))))) | ((Channel & ((0x1FUL << (0U)))) << (Rank & (0x0000001FU))))));


}




















































































 
static __inline uint32_t LL_ADC_REG_GetSequencerRanks(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  volatile uint32_t const *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->SQR1)) + (((((Rank) & ((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))) >> (__clz(__rbit(((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))))))) << 2UL))));

  return (uint32_t)(((*preg) & (((0x1FUL << (0U))) << (Rank & (0x0000001FU))))

                    >> (Rank & (0x0000001FU))
                   );
}















 
static __inline void LL_ADC_REG_SetContinuousMode(ADC_TypeDef *ADCx, uint32_t Continuous)
{
  (((ADCx->CR2)) = ((((((ADCx->CR2))) & (~((0x1UL << (1U))))) | (Continuous))));
}












 
static __inline uint32_t LL_ADC_REG_GetContinuousMode(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR2) & ((0x1UL << (1U)))));
}































 
static __inline void LL_ADC_REG_SetDMATransfer(ADC_TypeDef *ADCx, uint32_t DMATransfer)
{
  (((ADCx->CR2)) = ((((((ADCx->CR2))) & (~((0x1UL << (8U)) | (0x1UL << (9U))))) | (DMATransfer))));
}






























 
static __inline uint32_t LL_ADC_REG_GetDMATransfer(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR2) & ((0x1UL << (8U)) | (0x1UL << (9U)))));
}

















 
static __inline void LL_ADC_REG_SetFlagEndOfConversion(ADC_TypeDef *ADCx, uint32_t EocSelection)
{
  (((ADCx->CR2)) = ((((((ADCx->CR2))) & (~((0x1UL << (10U))))) | (EocSelection))));
}










 
static __inline uint32_t LL_ADC_REG_GetFlagEndOfConversion(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR2) & ((0x1UL << (10U)))));
}



 



 































 
static __inline void LL_ADC_INJ_SetTriggerSource(ADC_TypeDef *ADCx, uint32_t TriggerSource)
{
   
   
   
   
   
  (((ADCx->CR2)) = ((((((ADCx->CR2))) & (~((0xFUL << (16U))))) | ((TriggerSource & (0xFUL << (16U)))))));
}


































 
static __inline uint32_t LL_ADC_INJ_GetTriggerSource(const ADC_TypeDef *ADCx)
{
  uint32_t TriggerSource = ((ADCx->CR2) & ((0xFUL << (16U)) | (0x3UL << (20U))));

   
   
  uint32_t ShiftExten = ((TriggerSource & (0x3UL << (20U))) >> ((20UL) - 2UL));

   
   
  return ((TriggerSource
           & ((((0x00000000UL & (0xFUL << (16U))) >> (4UL * 0UL)) | (((0xFUL << (16U))) >> (4UL * 1UL)) | (((0xFUL << (16U))) >> (4UL * 2UL)) | (((0xFUL << (16U))) >> (4UL * 3UL))) << ShiftExten) & (0xFUL << (16U)))
          | (((((0x00000000UL & (0x3UL << (20U))) >> (4UL * 0UL)) | ((((0x1UL << (20U)))) >> (4UL * 1UL)) | ((((0x1UL << (20U)))) >> (4UL * 2UL)) | ((((0x1UL << (20U)))) >> (4UL * 3UL))) << ShiftExten) & (0x3UL << (20U)))
         );
}











 
static __inline uint32_t LL_ADC_INJ_IsTriggerSourceSWStart(const ADC_TypeDef *ADCx)
{
  return (((ADCx->CR2) & ((0x3UL << (20U)))) == (0x00000000UL & (0x3UL << (20U))));
}










 
static __inline uint32_t LL_ADC_INJ_GetTriggerEdge(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR2) & ((0x3UL << (20U)))));
}























 
static __inline void LL_ADC_INJ_SetSequencerLength(ADC_TypeDef *ADCx, uint32_t SequencerNbRanks)
{
  (((ADCx->JSQR)) = ((((((ADCx->JSQR))) & (~((0x3UL << (20U))))) | (SequencerNbRanks))));
}






















 
static __inline uint32_t LL_ADC_INJ_GetSequencerLength(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->JSQR) & ((0x3UL << (20U)))));
}













 
static __inline void LL_ADC_INJ_SetSequencerDiscont(ADC_TypeDef *ADCx, uint32_t SeqDiscont)
{
  (((ADCx->CR1)) = ((((((ADCx->CR1))) & (~((0x1UL << (12U))))) | (SeqDiscont))));
}










 
static __inline uint32_t LL_ADC_INJ_GetSequencerDiscont(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR1) & ((0x1UL << (12U)))));
}















































 
static __inline void LL_ADC_INJ_SetSequencerRanks(ADC_TypeDef *ADCx, uint32_t Rank, uint32_t Channel)
{
   
   
   
   
  uint32_t tmpreg1 = (((ADCx->JSQR) & ((0x3UL << (20U)))) >> (20U)) + 1UL;

  (((ADCx->JSQR)) = ((((((ADCx->JSQR))) & (~(((0x1FUL << (0U))) << (5UL * (uint8_t)(((Rank) + 3UL) - (tmpreg1)))))) | ((Channel & ((0x1FUL << (0U)))) << (5UL * (uint8_t)(((Rank) + 3UL) - (tmpreg1)))))));


}
























































 
static __inline uint32_t LL_ADC_INJ_GetSequencerRanks(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  uint32_t tmpreg1 = (((ADCx->JSQR) & ((0x3UL << (20U)))) >> (20U))  + 1UL;

  return (uint32_t)(((ADCx->JSQR) & (((0x1FUL << (0U))) << (5UL * (uint8_t)(((Rank) + 3UL) - (tmpreg1)))))

                    >> (5UL * (uint8_t)(((Rank) + 3UL) - (tmpreg1)))
                   );
}


























 
static __inline void LL_ADC_INJ_SetTrigAuto(ADC_TypeDef *ADCx, uint32_t TrigAuto)
{
  (((ADCx->CR1)) = ((((((ADCx->CR1))) & (~((0x1UL << (10U))))) | (TrigAuto))));
}









 
static __inline uint32_t LL_ADC_INJ_GetTrigAuto(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR1) & ((0x1UL << (10U)))));
}

























 
static __inline void LL_ADC_INJ_SetOffset(ADC_TypeDef *ADCx, uint32_t Rank, uint32_t OffsetLevel)
{
  volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->JOFR1)) + (((((Rank) & ((0x00000000UL | 0x00001000UL | 0x00002000UL | 0x00003000UL))) >> (__clz(__rbit(((0x00000000UL | 0x00001000UL | 0x00002000UL | 0x00003000UL))))))) << 2UL))));

  (((*preg)) = ((((((*preg))) & (~((0xFFFUL << (0U))))) | (OffsetLevel))));


}


















 
static __inline uint32_t LL_ADC_INJ_GetOffset(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  volatile uint32_t const *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->JOFR1)) + (((((Rank) & ((0x00000000UL | 0x00001000UL | 0x00002000UL | 0x00003000UL))) >> (__clz(__rbit(((0x00000000UL | 0x00001000UL | 0x00002000UL | 0x00003000UL))))))) << 2UL))));

  return (uint32_t)(((*preg) & ((0xFFFUL << (0U))))

                   );
}



 



 












































































 
static __inline void LL_ADC_SetChannelSamplingTime(ADC_TypeDef *ADCx, uint32_t Channel, uint32_t SamplingTime)
{
   
   
   
   
  volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->SMPR1)) + (((((Channel) & ((0x00000000UL | 0x02000000UL))) >> (__clz(__rbit(((0x00000000UL | 0x02000000UL))))))) << 2UL))));

  (((*preg)) = ((((((*preg))) & (~((0x7UL << (0U)) << (((Channel) & (0x01F00000UL)) >> (__clz(__rbit((0x01F00000UL)))))))) | (SamplingTime << (((Channel) & (0x01F00000UL)) >> (__clz(__rbit((0x01F00000UL)))))))));


}
































































 
static __inline uint32_t LL_ADC_GetChannelSamplingTime(const ADC_TypeDef *ADCx, uint32_t Channel)
{
  volatile uint32_t const *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->SMPR1)) + (((((Channel) & ((0x00000000UL | 0x02000000UL))) >> (__clz(__rbit(((0x00000000UL | 0x02000000UL))))))) << 2UL))));

  return (uint32_t)(((*preg) & ((0x7UL << (0U)) << (((Channel) & (0x01F00000UL)) >> (__clz(__rbit((0x01F00000UL)))))))

                    >> (((Channel) & (0x01F00000UL)) >> (__clz(__rbit((0x01F00000UL)))))
                   );
}



 



 
































































































 
static __inline void LL_ADC_SetAnalogWDMonitChannels(ADC_TypeDef *ADCx, uint32_t AWDChannelGroup)
{
  (((ADCx->CR1)) = ((((((ADCx->CR1))) & (~(((0x1UL << (23U)) | (0x1UL << (22U)) | (0x1UL << (9U)) | (0x1FUL << (0U)))))) | (AWDChannelGroup))));


}

























































































 
static __inline uint32_t LL_ADC_GetAnalogWDMonitChannels(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR1) & (((0x1UL << (23U)) | (0x1UL << (22U)) | (0x1UL << (9U)) | (0x1FUL << (0U))))));
}






















 
static __inline void LL_ADC_SetAnalogWDThresholds(ADC_TypeDef *ADCx, uint32_t AWDThresholdsHighLow, uint32_t AWDThresholdValue)
{
  volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->HTR)) + ((AWDThresholdsHighLow) << 2UL))));

  (((*preg)) = ((((((*preg))) & (~((0xFFFUL << (0U))))) | (AWDThresholdValue))));


}














 
static __inline uint32_t LL_ADC_GetAnalogWDThresholds(const ADC_TypeDef *ADCx, uint32_t AWDThresholdsHighLow)
{
  volatile uint32_t const *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->HTR)) + ((AWDThresholdsHighLow) << 2UL))));

  return (uint32_t)(((*preg) & ((0xFFFUL << (0U)))));
}



 



 



























 
static __inline void LL_ADC_SetMultimode(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t Multimode)
{
  (((ADCxy_COMMON->CCR)) = ((((((ADCxy_COMMON->CCR))) & (~((0x1FUL << (0U))))) | (Multimode))));
}

























 
static __inline uint32_t LL_ADC_GetMultimode(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (uint32_t)(((ADCxy_COMMON->CCR) & ((0x1FUL << (0U)))));
}












































 
static __inline void LL_ADC_SetMultiDMATransfer(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t MultiDMATransfer)
{
  (((ADCxy_COMMON->CCR)) = ((((((ADCxy_COMMON->CCR))) & (~((0x3UL << (14U)) | (0x1UL << (13U))))) | (MultiDMATransfer))));
}











































 
static __inline uint32_t LL_ADC_GetMultiDMATransfer(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (uint32_t)(((ADCxy_COMMON->CCR) & ((0x3UL << (14U)) | (0x1UL << (13U)))));
}





























 
static __inline void LL_ADC_SetMultiTwoSamplingDelay(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t MultiTwoSamplingDelay)
{
  (((ADCxy_COMMON->CCR)) = ((((((ADCxy_COMMON->CCR))) & (~((0xFUL << (8U))))) | (MultiTwoSamplingDelay))));
}























 
static __inline uint32_t LL_ADC_GetMultiTwoSamplingDelay(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (uint32_t)(((ADCxy_COMMON->CCR) & ((0xFUL << (8U)))));
}




 


 










 
static __inline void LL_ADC_Enable(ADC_TypeDef *ADCx)
{
  ((ADCx->CR2) |= ((0x1UL << (0U))));
}






 
static __inline void LL_ADC_Disable(ADC_TypeDef *ADCx)
{
  ((ADCx->CR2) &= ~((0x1UL << (0U))));
}






 
static __inline uint32_t LL_ADC_IsEnabled(const ADC_TypeDef *ADCx)
{
  return (((ADCx->CR2) & ((0x1UL << (0U)))) == ((0x1UL << (0U))));
}



 



 
















 
static __inline void LL_ADC_REG_StartConversionSWStart(ADC_TypeDef *ADCx)
{
  ((ADCx->CR2) |= ((0x1UL << (30U))));
}
















 
static __inline void LL_ADC_REG_StartConversionExtTrig(ADC_TypeDef *ADCx, uint32_t ExternalTriggerEdge)
{
  ((ADCx->CR2) |= (ExternalTriggerEdge));
}













 
static __inline void LL_ADC_REG_StopConversionExtTrig(ADC_TypeDef *ADCx)
{
  ((ADCx->CR2) &= ~((0x3UL << (28U))));
}









 
static __inline uint32_t LL_ADC_REG_ReadConversionData32(const ADC_TypeDef *ADCx)
{
  return (uint16_t)(((ADCx->DR) & ((0xFFFFUL << (0U)))));
}










 
static __inline uint16_t LL_ADC_REG_ReadConversionData12(const ADC_TypeDef *ADCx)
{
  return (uint16_t)(((ADCx->DR) & ((0xFFFFUL << (0U)))));
}










 
static __inline uint16_t LL_ADC_REG_ReadConversionData10(const ADC_TypeDef *ADCx)
{
  return (uint16_t)(((ADCx->DR) & ((0xFFFFUL << (0U)))));
}










 
static __inline uint8_t LL_ADC_REG_ReadConversionData8(const ADC_TypeDef *ADCx)
{
  return (uint8_t)(((ADCx->DR) & ((0xFFFFUL << (0U)))));
}










 
static __inline uint8_t LL_ADC_REG_ReadConversionData6(const ADC_TypeDef *ADCx)
{
  return (uint8_t)(((ADCx->DR) & ((0xFFFFUL << (0U)))));
}






















 
static __inline uint32_t LL_ADC_REG_ReadMultiConversionData32(const ADC_Common_TypeDef *ADCxy_COMMON, uint32_t ConversionData)
{
  return (uint32_t)(((ADCxy_COMMON->CDR) & ((0xFFFFUL << (16U))))

                    >> (__clz(__rbit(ConversionData)))
                   );
}




 



 
















 
static __inline void LL_ADC_INJ_StartConversionSWStart(ADC_TypeDef *ADCx)
{
  ((ADCx->CR2) |= ((0x1UL << (22U))));
}
















 
static __inline void LL_ADC_INJ_StartConversionExtTrig(ADC_TypeDef *ADCx, uint32_t ExternalTriggerEdge)
{
  ((ADCx->CR2) |= (ExternalTriggerEdge));
}













 
static __inline void LL_ADC_INJ_StopConversionExtTrig(ADC_TypeDef *ADCx)
{
  ((ADCx->CR2) &= ~((0x3UL << (20U))));
}

















 
static __inline uint32_t LL_ADC_INJ_ReadConversionData32(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  volatile uint32_t const *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->JDR1)) + (((((Rank) & ((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))) >> (__clz(__rbit(((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))))))) << 2UL))));

  return (uint32_t)(((*preg) & ((0xFFFFUL << (0U))))

                   );
}


















 
static __inline uint16_t LL_ADC_INJ_ReadConversionData12(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  volatile uint32_t const *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->JDR1)) + (((((Rank) & ((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))) >> (__clz(__rbit(((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))))))) << 2UL))));

  return (uint16_t)(((*preg) & ((0xFFFFUL << (0U))))

                   );
}


















 
static __inline uint16_t LL_ADC_INJ_ReadConversionData10(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  volatile uint32_t const *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->JDR1)) + (((((Rank) & ((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))) >> (__clz(__rbit(((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))))))) << 2UL))));

  return (uint16_t)(((*preg) & ((0xFFFFUL << (0U))))

                   );
}


















 
static __inline uint8_t LL_ADC_INJ_ReadConversionData8(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  volatile uint32_t const *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->JDR1)) + (((((Rank) & ((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))) >> (__clz(__rbit(((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))))))) << 2UL))));

  return (uint8_t)(((*preg) & ((0xFFFFUL << (0U))))

                  );
}


















 
static __inline uint8_t LL_ADC_INJ_ReadConversionData6(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  volatile uint32_t const *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->JDR1)) + (((((Rank) & ((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))) >> (__clz(__rbit(((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))))))) << 2UL))));

  return (uint8_t)(((*preg) & ((0xFFFFUL << (0U))))

                  );
}



 



 










 
static __inline uint32_t LL_ADC_IsActiveFlag_EOCS(const ADC_TypeDef *ADCx)
{
  return (((ADCx->SR) & ((0x1UL << (1U)))) == ((0x1UL << (1U))));
}






 
static __inline uint32_t LL_ADC_IsActiveFlag_OVR(const ADC_TypeDef *ADCx)
{
  return (((ADCx->SR) & ((0x1UL << (5U)))) == ((0x1UL << (5U))));
}







 
static __inline uint32_t LL_ADC_IsActiveFlag_JEOS(const ADC_TypeDef *ADCx)
{
   
   
   
   
  return (((ADCx->SR) & ((0x1UL << (2U)))) == ((0x1UL << (2U))));
}






 
static __inline uint32_t LL_ADC_IsActiveFlag_AWD1(const ADC_TypeDef *ADCx)
{
  return (((ADCx->SR) & ((0x1UL << (0U)))) == ((0x1UL << (0U))));
}










 
static __inline void LL_ADC_ClearFlag_EOCS(ADC_TypeDef *ADCx)
{
  ((ADCx->SR) = (~(0x1UL << (1U))));
}






 
static __inline void LL_ADC_ClearFlag_OVR(ADC_TypeDef *ADCx)
{
  ((ADCx->SR) = (~(0x1UL << (5U))));
}







 
static __inline void LL_ADC_ClearFlag_JEOS(ADC_TypeDef *ADCx)
{
   
   
   
   
  ((ADCx->SR) = (~(0x1UL << (2U))));
}






 
static __inline void LL_ADC_ClearFlag_AWD1(ADC_TypeDef *ADCx)
{
  ((ADCx->SR) = (~(0x1UL << (0U))));
}












 
static __inline uint32_t LL_ADC_IsActiveFlag_MST_EOCS(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (1U)))) == ((0x1UL << (1U))));
}











 
static __inline uint32_t LL_ADC_IsActiveFlag_SLV1_EOCS(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (9U)))) == ((0x1UL << (9U))));
}











 
static __inline uint32_t LL_ADC_IsActiveFlag_SLV2_EOCS(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (17U)))) == ((0x1UL << (17U))));
}






 
static __inline uint32_t LL_ADC_IsActiveFlag_MST_OVR(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (5U)))) == ((0x1UL << (5U))));
}







 
static __inline uint32_t LL_ADC_IsActiveFlag_SLV1_OVR(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (13U)))) == ((0x1UL << (13U))));
}







 
static __inline uint32_t LL_ADC_IsActiveFlag_SLV2_OVR(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (21U)))) == ((0x1UL << (21U))));
}








 
static __inline uint32_t LL_ADC_IsActiveFlag_MST_JEOS(const ADC_Common_TypeDef *ADCxy_COMMON)
{
   
   
   
   
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (2U)))) == ((0x1UL << (2U))));
}







 
static __inline uint32_t LL_ADC_IsActiveFlag_SLV1_JEOS(const ADC_Common_TypeDef *ADCxy_COMMON)
{
   
   
   
   
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (10U)))) == ((0x1UL << (10U))));
}







 
static __inline uint32_t LL_ADC_IsActiveFlag_SLV2_JEOS(const ADC_Common_TypeDef *ADCxy_COMMON)
{
   
   
   
   
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (18U)))) == ((0x1UL << (18U))));
}







 
static __inline uint32_t LL_ADC_IsActiveFlag_MST_AWD1(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (0U)))) == ((0x1UL << (0U))));
}







 
static __inline uint32_t LL_ADC_IsActiveFlag_SLV1_AWD1(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (8U)))) == ((0x1UL << (8U))));
}







 
static __inline uint32_t LL_ADC_IsActiveFlag_SLV2_AWD1(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (16U)))) == ((0x1UL << (16U))));
}





 



 










 
static __inline void LL_ADC_EnableIT_EOCS(ADC_TypeDef *ADCx)
{
  ((ADCx->CR1) |= ((0x1UL << (5U))));
}






 
static __inline void LL_ADC_EnableIT_OVR(ADC_TypeDef *ADCx)
{
  ((ADCx->CR1) |= ((0x1UL << (26U))));
}







 
static __inline void LL_ADC_EnableIT_JEOS(ADC_TypeDef *ADCx)
{
   
   
   
   
  ((ADCx->CR1) |= ((0x1UL << (7U))));
}






 
static __inline void LL_ADC_EnableIT_AWD1(ADC_TypeDef *ADCx)
{
  ((ADCx->CR1) |= ((0x1UL << (6U))));
}










 
static __inline void LL_ADC_DisableIT_EOCS(ADC_TypeDef *ADCx)
{
  ((ADCx->CR1) &= ~((0x1UL << (5U))));
}






 
static __inline void LL_ADC_DisableIT_OVR(ADC_TypeDef *ADCx)
{
  ((ADCx->CR1) &= ~((0x1UL << (26U))));
}







 
static __inline void LL_ADC_DisableIT_JEOS(ADC_TypeDef *ADCx)
{
   
   
   
   
  ((ADCx->CR1) &= ~((0x1UL << (7U))));
}






 
static __inline void LL_ADC_DisableIT_AWD1(ADC_TypeDef *ADCx)
{
  ((ADCx->CR1) &= ~((0x1UL << (6U))));
}











 
static __inline uint32_t LL_ADC_IsEnabledIT_EOCS(const ADC_TypeDef *ADCx)
{
  return (((ADCx->CR1) & ((0x1UL << (5U)))) == ((0x1UL << (5U))));
}







 
static __inline uint32_t LL_ADC_IsEnabledIT_OVR(const ADC_TypeDef *ADCx)
{
  return (((ADCx->CR1) & ((0x1UL << (26U)))) == ((0x1UL << (26U))));
}








 
static __inline uint32_t LL_ADC_IsEnabledIT_JEOS(const ADC_TypeDef *ADCx)
{
   
   
   
   
  return (((ADCx->CR1) & ((0x1UL << (7U)))) == ((0x1UL << (7U))));
}







 
static __inline uint32_t LL_ADC_IsEnabledIT_AWD1(const ADC_TypeDef *ADCx)
{
  return (((ADCx->CR1) & ((0x1UL << (6U)))) == ((0x1UL << (6U))));
}



 

#line 4762 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"



 



 





 







#line 32 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"



 



 

 


 













 
typedef struct
{
  uint32_t ClockPrescaler;               

 
  uint32_t Resolution;                   
 
  uint32_t DataAlign;                    

 
  uint32_t ScanConvMode;                 





 
  uint32_t EOCSelection;                 





 
  FunctionalState ContinuousConvMode;    

 
  uint32_t NbrOfConversion;              

 
  FunctionalState DiscontinuousConvMode; 


 
  uint32_t NbrOfDiscConversion;          

 
  uint32_t ExternalTrigConv;             


 
  uint32_t ExternalTrigConvEdge;         

 
  FunctionalState DMAContinuousRequests; 



 
} ADC_InitTypeDef;







 
typedef struct
{
  uint32_t Channel;                
 
  uint32_t Rank;                   
 
  uint32_t SamplingTime;           







 
  uint32_t Offset;                  
} ADC_ChannelConfTypeDef;



 
typedef struct
{
  uint32_t WatchdogMode;      
 
  uint32_t HighThreshold;     
 
  uint32_t LowThreshold;      
 
  uint32_t Channel;           

 
  FunctionalState ITMode;     

 
  uint32_t WatchdogNumber;     
} ADC_AnalogWDGConfTypeDef;



 
 





 




 





 




 




 





 



typedef struct

{
  ADC_TypeDef                   *Instance;                    

  ADC_InitTypeDef               Init;                         

  volatile uint32_t                 NbrOfCurrentConversionRank;   

  DMA_HandleTypeDef             *DMA_Handle;                  

  HAL_LockTypeDef               Lock;                         

  volatile uint32_t                 State;                        

  volatile uint32_t                 ErrorCode;                    
#line 220 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"
} ADC_HandleTypeDef;

#line 243 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"



 

 


 



 
#line 264 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"


 




 






 



 
#line 299 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"


 



 






 



 






 



 
 
 
#line 347 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"


 



 




 



 
#line 382 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"





 



 
#line 400 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"


 



 





 



 




 



 
#line 433 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"


 



 






 



 
#line 457 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"


 



 





 



 

 


 




 
#line 495 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"





 






 







 







 






 







 







 




 

 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc_ex.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc_ex.h"



 



 

 


 












 
typedef struct
{
  uint32_t InjectedChannel;                      

 
  uint32_t InjectedRank;                         

 
  uint32_t InjectedSamplingTime;                 







 
  uint32_t InjectedOffset;                       


 
  uint32_t InjectedNbrOfConversion;              



 
  FunctionalState InjectedDiscontinuousConvMode; 





 
  FunctionalState AutoInjectedConv;              






 
  uint32_t ExternalTrigInjecConv;                






 
  uint32_t ExternalTrigInjecConvEdge;            



 
} ADC_InjectionConfTypeDef;



 
typedef struct
{
  uint32_t Mode;              
 
  uint32_t DMAAccessMode;     
 
  uint32_t TwoSamplingDelay;  
 
} ADC_MultiModeTypeDef;



 

 


 



 
#line 149 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc_ex.h"


 



 






 



 






 



 
#line 195 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc_ex.h"


 



 






 



 
#line 220 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc_ex.h"








 




 

 


 
#line 253 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc_ex.h"


 

 


 



 

 
HAL_StatusTypeDef HAL_ADCEx_InjectedStart(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADCEx_InjectedStop(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADCEx_InjectedPollForConversion(ADC_HandleTypeDef *hadc, uint32_t Timeout);
HAL_StatusTypeDef HAL_ADCEx_InjectedStart_IT(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADCEx_InjectedStop_IT(ADC_HandleTypeDef *hadc);
uint32_t HAL_ADCEx_InjectedGetValue(ADC_HandleTypeDef *hadc, uint32_t InjectedRank);
HAL_StatusTypeDef HAL_ADCEx_MultiModeStart_DMA(ADC_HandleTypeDef *hadc, uint32_t *pData, uint32_t Length);
HAL_StatusTypeDef HAL_ADCEx_MultiModeStop_DMA(ADC_HandleTypeDef *hadc);
uint32_t HAL_ADCEx_MultiModeGetValue(ADC_HandleTypeDef *hadc);
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc);

 
HAL_StatusTypeDef HAL_ADCEx_InjectedConfigChannel(ADC_HandleTypeDef *hadc, ADC_InjectionConfTypeDef *sConfigInjected);
HAL_StatusTypeDef HAL_ADCEx_MultiModeConfigChannel(ADC_HandleTypeDef *hadc, ADC_MultiModeTypeDef *multimode);



 



 
 
 
 


 



 

 


 
#line 311 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc_ex.h"

#line 318 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc_ex.h"

#line 359 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc_ex.h"







 







 







 

 


 



 



 



 








#line 555 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"

 


 



 
 
HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef *hadc);
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc);
void HAL_ADC_MspDeInit(ADC_HandleTypeDef *hadc);








 



 
 
HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef *hadc, uint32_t Timeout);

HAL_StatusTypeDef HAL_ADC_PollForEvent(ADC_HandleTypeDef *hadc, uint32_t EventType, uint32_t Timeout);

HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_Stop_IT(ADC_HandleTypeDef *hadc);

void HAL_ADC_IRQHandler(ADC_HandleTypeDef *hadc);

HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef *hadc, uint32_t *pData, uint32_t Length);
HAL_StatusTypeDef HAL_ADC_Stop_DMA(ADC_HandleTypeDef *hadc);

uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef *hadc);

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc);
void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef *hadc);
void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc);


 



 
 
HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig);
HAL_StatusTypeDef HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef *hadc, ADC_AnalogWDGConfTypeDef *AnalogWDGConfig);


 



 
 
uint32_t HAL_ADC_GetState(ADC_HandleTypeDef *hadc);
uint32_t HAL_ADC_GetError(ADC_HandleTypeDef *hadc);


 



 
 
 
 


 
 
 
 

 
 
 



 

 



 

 





 









 








 









 






 




#line 772 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"

#line 781 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"





 







 







 







 







 







 






 






 






 






 






 






 




 

 


 



 



 



 








#line 296 "../Core/Inc/stm32f4xx_hal_conf.h"










#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_crc.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_crc.h"



 



 

 


 



 
typedef enum
{
  HAL_CRC_STATE_RESET     = 0x00U,   
  HAL_CRC_STATE_READY     = 0x01U,   
  HAL_CRC_STATE_BUSY      = 0x02U,   
  HAL_CRC_STATE_TIMEOUT   = 0x03U,   
  HAL_CRC_STATE_ERROR     = 0x04U    
} HAL_CRC_StateTypeDef;




 
typedef struct
{
  CRC_TypeDef                 *Instance;    

  HAL_LockTypeDef             Lock;         

  volatile HAL_CRC_StateTypeDef   State;        

} CRC_HandleTypeDef;


 

 


 



 

 


 




 






 








 







 



 


 


 



 

 


 

 


 
HAL_StatusTypeDef HAL_CRC_Init(CRC_HandleTypeDef *hcrc);
HAL_StatusTypeDef HAL_CRC_DeInit(CRC_HandleTypeDef *hcrc);
void HAL_CRC_MspInit(CRC_HandleTypeDef *hcrc);
void HAL_CRC_MspDeInit(CRC_HandleTypeDef *hcrc);


 

 


 
uint32_t HAL_CRC_Accumulate(CRC_HandleTypeDef *hcrc, uint32_t pBuffer[], uint32_t BufferLength);
uint32_t HAL_CRC_Calculate(CRC_HandleTypeDef *hcrc, uint32_t pBuffer[], uint32_t BufferLength);


 

 


 
HAL_CRC_StateTypeDef HAL_CRC_GetState(const CRC_HandleTypeDef *hcrc);


 



 



 



 





#line 308 "../Core/Inc/stm32f4xx_hal_conf.h"










#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac.h"
















 

 









 

 
#line 33 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac.h"





 

 



 



 
typedef enum
{
  HAL_DAC_STATE_RESET             = 0x00U,   
  HAL_DAC_STATE_READY             = 0x01U,   
  HAL_DAC_STATE_BUSY              = 0x02U,   
  HAL_DAC_STATE_TIMEOUT           = 0x03U,   
  HAL_DAC_STATE_ERROR             = 0x04U    

} HAL_DAC_StateTypeDef;



 



typedef struct

{
  DAC_TypeDef                 *Instance;      

  volatile HAL_DAC_StateTypeDef   State;          

  HAL_LockTypeDef             Lock;           

  DMA_HandleTypeDef           *DMA_Handle1;   

  DMA_HandleTypeDef           *DMA_Handle2;   

  volatile uint32_t               ErrorCode;      

#line 95 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac.h"

} DAC_HandleTypeDef;



 
typedef struct
{
  uint32_t DAC_Trigger;                  
 

  uint32_t DAC_OutputBuffer;             
 

} DAC_ChannelConfTypeDef;

#line 137 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac.h"



 

 



 



 
#line 161 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac.h"



 



 
#line 178 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac.h"



 



 





 



 






 



 






 



 







 



 







 



 

 



 




 
#line 262 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac.h"





 







 






 






 






 









 









 









 










 









 




 

 



 



#line 368 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac.h"









 

 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac_ex.h"
















 

 









 

 
#line 33 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac_ex.h"





 

 



 

 



 



 
#line 79 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac_ex.h"



 




 

 


 



 
#line 106 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac_ex.h"

#line 131 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac_ex.h"


 

 
 



 



 
 

HAL_StatusTypeDef HAL_DACEx_TriangleWaveGenerate(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Amplitude);
HAL_StatusTypeDef HAL_DACEx_NoiseWaveGenerate(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Amplitude);


HAL_StatusTypeDef HAL_DACEx_DualStart(DAC_HandleTypeDef *hdac);
HAL_StatusTypeDef HAL_DACEx_DualStop(DAC_HandleTypeDef *hdac);
HAL_StatusTypeDef HAL_DACEx_DualSetValue(DAC_HandleTypeDef *hdac, uint32_t Alignment, uint32_t Data1, uint32_t Data2);
uint32_t HAL_DACEx_DualGetValue(const DAC_HandleTypeDef *hdac);



void HAL_DACEx_ConvCpltCallbackCh2(DAC_HandleTypeDef *hdac);
void HAL_DACEx_ConvHalfCpltCallbackCh2(DAC_HandleTypeDef *hdac);
void HAL_DACEx_ErrorCallbackCh2(DAC_HandleTypeDef *hdac);
void HAL_DACEx_DMAUnderrunCallbackCh2(DAC_HandleTypeDef *hdac);




 



 



 



 

 
 
void DAC_DMAConvCpltCh2(DMA_HandleTypeDef *hdma);
void DAC_DMAErrorCh2(DMA_HandleTypeDef *hdma);
void DAC_DMAHalfConvCpltCh2(DMA_HandleTypeDef *hdma);



 



 





 





#line 381 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac.h"

 



 



 
 
HAL_StatusTypeDef HAL_DAC_Init(DAC_HandleTypeDef *hdac);
HAL_StatusTypeDef HAL_DAC_DeInit(DAC_HandleTypeDef *hdac);
void HAL_DAC_MspInit(DAC_HandleTypeDef *hdac);
void HAL_DAC_MspDeInit(DAC_HandleTypeDef *hdac);



 



 
 
HAL_StatusTypeDef HAL_DAC_Start(DAC_HandleTypeDef *hdac, uint32_t Channel);
HAL_StatusTypeDef HAL_DAC_Stop(DAC_HandleTypeDef *hdac, uint32_t Channel);
HAL_StatusTypeDef HAL_DAC_Start_DMA(DAC_HandleTypeDef *hdac, uint32_t Channel, const uint32_t *pData, uint32_t Length,
                                    uint32_t Alignment);
HAL_StatusTypeDef HAL_DAC_Stop_DMA(DAC_HandleTypeDef *hdac, uint32_t Channel);
void HAL_DAC_IRQHandler(DAC_HandleTypeDef *hdac);
HAL_StatusTypeDef HAL_DAC_SetValue(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Alignment, uint32_t Data);

void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef *hdac);
void HAL_DAC_ConvHalfCpltCallbackCh1(DAC_HandleTypeDef *hdac);
void HAL_DAC_ErrorCallbackCh1(DAC_HandleTypeDef *hdac);
void HAL_DAC_DMAUnderrunCallbackCh1(DAC_HandleTypeDef *hdac);

#line 424 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac.h"



 



 
 
uint32_t HAL_DAC_GetValue(const DAC_HandleTypeDef *hdac, uint32_t Channel);
HAL_StatusTypeDef HAL_DAC_ConfigChannel(DAC_HandleTypeDef *hdac,
                                        const DAC_ChannelConfTypeDef *sConfig, uint32_t Channel);


 



 
 
HAL_DAC_StateTypeDef HAL_DAC_GetState(const DAC_HandleTypeDef *hdac);
uint32_t HAL_DAC_GetError(const DAC_HandleTypeDef *hdac);



 



 



 
void DAC_DMAConvCpltCh1(DMA_HandleTypeDef *hdma);
void DAC_DMAErrorCh1(DMA_HandleTypeDef *hdma);
void DAC_DMAHalfConvCpltCh1(DMA_HandleTypeDef *hdma);


 



 





 






#line 320 "../Core/Inc/stm32f4xx_hal_conf.h"














#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash.h"















 

 







 
#line 28 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash.h"



 



 

 


 



 
typedef enum
{
  FLASH_PROC_NONE = 0U,
  FLASH_PROC_SECTERASE,
  FLASH_PROC_MASSERASE,
  FLASH_PROC_PROGRAM
} FLASH_ProcedureTypeDef;



 
typedef struct
{
  volatile FLASH_ProcedureTypeDef ProcedureOnGoing;    

  volatile uint32_t               NbSectorsToErase;    

  volatile uint8_t                VoltageForErase;     

  volatile uint32_t               Sector;              

  volatile uint32_t               Bank;                

  volatile uint32_t               Address;             

  HAL_LockTypeDef             Lock;                

  volatile uint32_t               ErrorCode;           

} FLASH_ProcessTypeDef;



 

 


 



 
#line 95 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash.h"


 



 






 




 
#line 124 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash.h"


 




 




 



 







 



 







 



 

 


 





 






 





 





 





 





 





 





 






 








 










 









 
















 















 



 

 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"















 

 







 
#line 28 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"



 



 

 


 



 
typedef struct
{
  uint32_t TypeErase;   
 

  uint32_t Banks;       
 

  uint32_t Sector;      
 

  uint32_t NbSectors;   
 

  uint32_t VoltageRange;
 

} FLASH_EraseInitTypeDef;



 
typedef struct
{
  uint32_t OptionType;   
 

  uint32_t WRPState;     
 

  uint32_t WRPSector;         
 

  uint32_t Banks;        
 

  uint32_t RDPLevel;     
 

  uint32_t BORLevel;     
 

  uint8_t  USERConfig;    

} FLASH_OBProgramInitTypeDef;



 
#line 131 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"


 

 



 



 




 



 






 



 




 



 






 



 






 



 




 



 




 




 




 



 






 

#line 247 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"



 






#line 264 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"


 



 
 
#line 291 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 





#line 309 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 



 




 
#line 325 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"

#line 334 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"


 



 





#line 354 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"


 



 
 
#line 389 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 410 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 428 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 439 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 449 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 462 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 



 



 
 
#line 500 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 522 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 541 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 553 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 564 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 578 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 


 



 
 
#line 615 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 637 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 649 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 660 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 675 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 



 



 







 



 
#line 706 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"


 



 

 

 


 



 
 
HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *SectorError);
HAL_StatusTypeDef HAL_FLASHEx_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit);
HAL_StatusTypeDef HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit);
void              HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit);

#line 742 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"







 



 
 
 
 


 
 




 




 





 




 




 






 






 

 


 



 



























#line 847 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"







#line 861 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"

#line 881 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"

#line 896 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"







#line 911 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"

#line 926 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"

#line 937 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"

#line 947 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"













#line 966 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"

























































#line 1032 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"


 



 

 


 
void FLASH_Erase_Sector(uint32_t Sector, uint8_t VoltageRange);
void FLASH_FlushCaches(void);


 



 



 







#line 296 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash.h"
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ramfunc.h"















 

 



#line 73 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ramfunc.h"




#line 297 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash.h"

 


 


 
 
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint64_t Data);
HAL_StatusTypeDef HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint64_t Data);
 
void HAL_FLASH_IRQHandler(void);
 
void HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue);
void HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue);


 



 
 
HAL_StatusTypeDef HAL_FLASH_Unlock(void);
HAL_StatusTypeDef HAL_FLASH_Lock(void);
HAL_StatusTypeDef HAL_FLASH_OB_Unlock(void);
HAL_StatusTypeDef HAL_FLASH_OB_Lock(void);
 
HAL_StatusTypeDef HAL_FLASH_OB_Launch(void);


 



 
 
uint32_t HAL_FLASH_GetError(void);
HAL_StatusTypeDef FLASH_WaitForLastOperation(uint32_t Timeout);


 



 
 
 


 



 
 


 



 



 



 



 



 




 

 


 



 






 



 

 


 



 



 



 







#line 336 "../Core/Inc/stm32f4xx_hal_conf.h"


























#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"



 



 

 


 




 
typedef struct
{
  uint32_t ClockSpeed;       
 

  uint32_t DutyCycle;        
 

  uint32_t OwnAddress1;      
 

  uint32_t AddressingMode;   
 

  uint32_t DualAddressMode;  
 

  uint32_t OwnAddress2;      
 

  uint32_t GeneralCallMode;  
 

  uint32_t NoStretchMode;    
 

} I2C_InitTypeDef;



 



























 
typedef enum
{
  HAL_I2C_STATE_RESET             = 0x00U,    
  HAL_I2C_STATE_READY             = 0x20U,    
  HAL_I2C_STATE_BUSY              = 0x24U,    
  HAL_I2C_STATE_BUSY_TX           = 0x21U,    
  HAL_I2C_STATE_BUSY_RX           = 0x22U,    
  HAL_I2C_STATE_LISTEN            = 0x28U,    
  HAL_I2C_STATE_BUSY_TX_LISTEN    = 0x29U,   
 
  HAL_I2C_STATE_BUSY_RX_LISTEN    = 0x2AU,   
 
  HAL_I2C_STATE_ABORT             = 0x60U,    
  HAL_I2C_STATE_TIMEOUT           = 0xA0U,    
  HAL_I2C_STATE_ERROR             = 0xE0U     

} HAL_I2C_StateTypeDef;



 


















 
typedef enum
{
  HAL_I2C_MODE_NONE               = 0x00U,    
  HAL_I2C_MODE_MASTER             = 0x10U,    
  HAL_I2C_MODE_SLAVE              = 0x20U,    
  HAL_I2C_MODE_MEM                = 0x40U     

} HAL_I2C_ModeTypeDef;



 




 
#line 176 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"


 




 



typedef struct

{
  I2C_TypeDef                *Instance;       

  I2C_InitTypeDef            Init;            

  uint8_t                    *pBuffPtr;       

  uint16_t                   XferSize;        

  volatile uint16_t              XferCount;       

  volatile uint32_t              XferOptions;     

  volatile uint32_t              PreviousState;  
 

  DMA_HandleTypeDef          *hdmatx;         

  DMA_HandleTypeDef          *hdmarx;         

  HAL_LockTypeDef            Lock;            

  volatile HAL_I2C_StateTypeDef  State;           

  volatile HAL_I2C_ModeTypeDef   Mode;            

  volatile uint32_t              ErrorCode;       

  volatile uint32_t              Devaddress;      

  volatile uint32_t              Memaddress;      

  volatile uint32_t              MemaddSize;      

  volatile uint32_t              EventCount;      


#line 243 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"
} I2C_HandleTypeDef;

#line 273 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"


 



 
 



 



 




 



 




 



 




 



 




 



 




 



 




 



 




 



 
#line 358 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"



 




 






 





 



 

#line 401 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"


 



 

 



 




 
#line 428 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"









 











 
























 













 






 
#line 503 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"




 
#line 515 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"




 





 




 

 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c_ex.h"
















 

 







#line 108 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c_ex.h"








#line 534 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"

 


 



 
 
HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c);

 
#line 557 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"


 



 
 
 
HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Slave_Receive(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_IsDeviceReady(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Trials, uint32_t Timeout);

 
HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Master_Receive_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Mem_Write_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Mem_Read_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);

HAL_StatusTypeDef HAL_I2C_Master_Seq_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Master_Seq_Receive_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Slave_Seq_Transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Slave_Seq_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_EnableListen_IT(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef HAL_I2C_DisableListen_IT(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef HAL_I2C_Master_Abort_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress);

 
HAL_StatusTypeDef HAL_I2C_Master_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Master_Receive_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Receive_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Mem_Write_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Mem_Read_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);

HAL_StatusTypeDef HAL_I2C_Master_Seq_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Master_Seq_Receive_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Slave_Seq_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Slave_Seq_Receive_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions);


 



 
 
void HAL_I2C_EV_IRQHandler(I2C_HandleTypeDef *hi2c);
void HAL_I2C_ER_IRQHandler(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode);
void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_AbortCpltCallback(I2C_HandleTypeDef *hi2c);


 



 
 
HAL_I2C_StateTypeDef HAL_I2C_GetState(I2C_HandleTypeDef *hi2c);
HAL_I2C_ModeTypeDef HAL_I2C_GetMode(I2C_HandleTypeDef *hi2c);
uint32_t HAL_I2C_GetError(I2C_HandleTypeDef *hi2c);



 



 
 
 
 


 





 

 


 

#line 668 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"













 
#line 704 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"








 



 

 


 



 



 



 








#line 364 "../Core/Inc/stm32f4xx_hal_conf.h"


















#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr.h"















  

 







 
#line 28 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr.h"



 



  

 



 
   


 
typedef struct
{
  uint32_t PVDLevel;   
 

  uint32_t Mode;      
 
}PWR_PVDTypeDef;



 

 


 
  


 



 



  
#line 84 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr.h"


    
 


 
#line 98 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr.h"


 




 




 
    


 






 



 





 



 







 



  
  
 


 





















 







 





 





 





 





 





 





 





 






 






 








 







 





 





 




 

 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h"















  

 







 
#line 28 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h"



 



  

  
 


 
#line 64 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h"



 
#line 78 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h"


 
#line 97 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h"



  
  
 


 










 
#line 143 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h"

#line 191 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h"


 

 


 
 


 
void HAL_PWREx_EnableFlashPowerDown(void);
void HAL_PWREx_DisableFlashPowerDown(void); 
HAL_StatusTypeDef HAL_PWREx_EnableBkUpReg(void);
HAL_StatusTypeDef HAL_PWREx_DisableBkUpReg(void); 
uint32_t HAL_PWREx_GetVoltageRange(void);
HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling);

#line 219 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h"

#line 226 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h"



 



 
 
 
 


 



 
 
 
 



 



 


    
 



 



 

 



   
 
 





 



 

 


 



 






#line 308 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h"

#line 319 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h"


 



 



  



 
  





#line 276 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr.h"

 


 
  


 
 
void HAL_PWR_DeInit(void);
void HAL_PWR_EnableBkUpAccess(void);
void HAL_PWR_DisableBkUpAccess(void);


 



 
 
 
void HAL_PWR_ConfigPVD(PWR_PVDTypeDef *sConfigPVD);
void HAL_PWR_EnablePVD(void);
void HAL_PWR_DisablePVD(void);

 
void HAL_PWR_EnableWakeUpPin(uint32_t WakeUpPinx);
void HAL_PWR_DisableWakeUpPin(uint32_t WakeUpPinx);

 
void HAL_PWR_EnterSTOPMode(uint32_t Regulator, uint8_t STOPEntry);
void HAL_PWR_EnterSLEEPMode(uint32_t Regulator, uint8_t SLEEPEntry);
void HAL_PWR_EnterSTANDBYMode(void);

 
void HAL_PWR_PVD_IRQHandler(void);
void HAL_PWR_PVDCallback(void);

 
void HAL_PWR_EnableSleepOnExit(void);
void HAL_PWR_DisableSleepOnExit(void);
void HAL_PWR_EnableSEVOnPend(void);
void HAL_PWR_DisableSEVOnPend(void);


 



 

 
 
 


 



 



 



 
 







 



 
 
 



 



 




 



 
 
 




 



 
 


 



 
#line 407 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr.h"










 



 



  



 
  





#line 384 "../Core/Inc/stm32f4xx_hal_conf.h"


#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rng.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rng.h"



 






 

 



 



 



 



 
typedef enum
{
  HAL_RNG_STATE_RESET     = 0x00U,   
  HAL_RNG_STATE_READY     = 0x01U,   
  HAL_RNG_STATE_BUSY      = 0x02U,   
  HAL_RNG_STATE_TIMEOUT   = 0x03U,   
  HAL_RNG_STATE_ERROR     = 0x04U    

} HAL_RNG_StateTypeDef;



 



 



typedef struct

{
  RNG_TypeDef                 *Instance;     

  HAL_LockTypeDef             Lock;          

  volatile HAL_RNG_StateTypeDef   State;         

  volatile  uint32_t              ErrorCode;     

  uint32_t                    RandomNumber;  

#line 98 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rng.h"

} RNG_HandleTypeDef;

#line 121 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rng.h"



 



 

 


 



 





 



 





 



 
#line 166 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rng.h"


 



 

 


 




 
#line 192 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rng.h"





 






 











 









 






 






 











 











 




 

 


 



 
HAL_StatusTypeDef HAL_RNG_Init(RNG_HandleTypeDef *hrng);
HAL_StatusTypeDef HAL_RNG_DeInit(RNG_HandleTypeDef *hrng);
void HAL_RNG_MspInit(RNG_HandleTypeDef *hrng);
void HAL_RNG_MspDeInit(RNG_HandleTypeDef *hrng);

 
#line 293 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rng.h"



 



 
uint32_t HAL_RNG_GetRandomNumber(RNG_HandleTypeDef
                                 *hrng);     
uint32_t HAL_RNG_GetRandomNumber_IT(RNG_HandleTypeDef
                                    *hrng);  
HAL_StatusTypeDef HAL_RNG_GenerateRandomNumber(RNG_HandleTypeDef *hrng, uint32_t *random32bit);
HAL_StatusTypeDef HAL_RNG_GenerateRandomNumber_IT(RNG_HandleTypeDef *hrng);
uint32_t HAL_RNG_ReadLastRandomNumber(const RNG_HandleTypeDef *hrng);

void HAL_RNG_IRQHandler(RNG_HandleTypeDef *hrng);
void HAL_RNG_ErrorCallback(RNG_HandleTypeDef *hrng);
void HAL_RNG_ReadyDataCallback(RNG_HandleTypeDef *hrng, uint32_t random32bit);



 



 
HAL_RNG_StateTypeDef HAL_RNG_GetState(const RNG_HandleTypeDef *hrng);
uint32_t             HAL_RNG_GetError(const RNG_HandleTypeDef *hrng);


 



 

 


 









 



 





 








#line 388 "../Core/Inc/stm32f4xx_hal_conf.h"


















#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"



 



 

 


 



 
typedef struct
{
  uint32_t Prescaler;         
 

  uint32_t CounterMode;       
 

  uint32_t Period;            

 

  uint32_t ClockDivision;     
 

  uint32_t RepetitionCounter;  








 

  uint32_t AutoReloadPreload;  
 
} TIM_Base_InitTypeDef;



 
typedef struct
{
  uint32_t OCMode;        
 

  uint32_t Pulse;         
 

  uint32_t OCPolarity;    
 

  uint32_t OCNPolarity;   

 

  uint32_t OCFastMode;    

 


  uint32_t OCIdleState;   

 

  uint32_t OCNIdleState;  

 
} TIM_OC_InitTypeDef;



 
typedef struct
{
  uint32_t OCMode;        
 

  uint32_t Pulse;         
 

  uint32_t OCPolarity;    
 

  uint32_t OCNPolarity;   

 

  uint32_t OCIdleState;   

 

  uint32_t OCNIdleState;  

 

  uint32_t ICPolarity;    
 

  uint32_t ICSelection;   
 

  uint32_t ICFilter;      
 
} TIM_OnePulse_InitTypeDef;



 
typedef struct
{
  uint32_t  ICPolarity;  
 

  uint32_t ICSelection;  
 

  uint32_t ICPrescaler;  
 

  uint32_t ICFilter;     
 
} TIM_IC_InitTypeDef;



 
typedef struct
{
  uint32_t EncoderMode;   
 

  uint32_t IC1Polarity;   
 

  uint32_t IC1Selection;  
 

  uint32_t IC1Prescaler;  
 

  uint32_t IC1Filter;     
 

  uint32_t IC2Polarity;   
 

  uint32_t IC2Selection;  
 

  uint32_t IC2Prescaler;  
 

  uint32_t IC2Filter;     
 
} TIM_Encoder_InitTypeDef;



 
typedef struct
{
  uint32_t ClockSource;     
 
  uint32_t ClockPolarity;   
 
  uint32_t ClockPrescaler;  
 
  uint32_t ClockFilter;     
 
} TIM_ClockConfigTypeDef;



 
typedef struct
{
  uint32_t ClearInputState;      
 
  uint32_t ClearInputSource;     
 
  uint32_t ClearInputPolarity;   
 
  uint32_t ClearInputPrescaler;  

 
  uint32_t ClearInputFilter;     
 
} TIM_ClearInputConfigTypeDef;



 
typedef struct
{
  uint32_t  MasterOutputTrigger;   
 
  uint32_t  MasterSlaveMode;       





 
} TIM_MasterConfigTypeDef;



 
typedef struct
{
  uint32_t  SlaveMode;         
 
  uint32_t  InputTrigger;      
 
  uint32_t  TriggerPolarity;   
 
  uint32_t  TriggerPrescaler;  
 
  uint32_t  TriggerFilter;     
 

} TIM_SlaveConfigTypeDef;





 
typedef struct
{
  uint32_t OffStateRunMode;       

  uint32_t OffStateIDLEMode;      

  uint32_t LockLevel;             

  uint32_t DeadTime;              

  uint32_t BreakState;            

  uint32_t BreakPolarity;         

  uint32_t BreakFilter;           

  uint32_t AutomaticOutput;       

} TIM_BreakDeadTimeConfigTypeDef;



 
typedef enum
{
  HAL_TIM_STATE_RESET             = 0x00U,     
  HAL_TIM_STATE_READY             = 0x01U,     
  HAL_TIM_STATE_BUSY              = 0x02U,     
  HAL_TIM_STATE_TIMEOUT           = 0x03U,     
  HAL_TIM_STATE_ERROR             = 0x04U      
} HAL_TIM_StateTypeDef;



 
typedef enum
{
  HAL_TIM_CHANNEL_STATE_RESET             = 0x00U,     
  HAL_TIM_CHANNEL_STATE_READY             = 0x01U,     
  HAL_TIM_CHANNEL_STATE_BUSY              = 0x02U,     
} HAL_TIM_ChannelStateTypeDef;



 
typedef enum
{
  HAL_DMA_BURST_STATE_RESET             = 0x00U,     
  HAL_DMA_BURST_STATE_READY             = 0x01U,     
  HAL_DMA_BURST_STATE_BUSY              = 0x02U,     
} HAL_TIM_DMABurstStateTypeDef;



 
typedef enum
{
  HAL_TIM_ACTIVE_CHANNEL_1        = 0x01U,     
  HAL_TIM_ACTIVE_CHANNEL_2        = 0x02U,     
  HAL_TIM_ACTIVE_CHANNEL_3        = 0x04U,     
  HAL_TIM_ACTIVE_CHANNEL_4        = 0x08U,     
  HAL_TIM_ACTIVE_CHANNEL_CLEARED  = 0x00U      
} HAL_TIM_ActiveChannel;



 



typedef struct

{
  TIM_TypeDef                        *Instance;          
  TIM_Base_InitTypeDef               Init;               
  HAL_TIM_ActiveChannel              Channel;            
  DMA_HandleTypeDef                  *hdma[7];          
 
  HAL_LockTypeDef                    Lock;               
  volatile HAL_TIM_StateTypeDef          State;              
  volatile HAL_TIM_ChannelStateTypeDef   ChannelState[4];    
  volatile HAL_TIM_ChannelStateTypeDef   ChannelNState[4];   
  volatile HAL_TIM_DMABurstStateTypeDef  DMABurstState;      

#line 380 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"
} TIM_HandleTypeDef;

#line 423 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"



 
 

 


 



 




 



 
#line 466 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"


 



 
#line 481 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"


 



 





 



 




 



 






 



 







 



 





 



 




 



 





 



 




 



 




 



 




 



 




 



 




 



 




 



 





 



 




 



 





 



 






 



 




 



 





 



 
#line 680 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"


 



 




 



 
#line 703 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"


 



 




 



 
#line 731 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"


 



 







 



 
#line 760 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"


 



 







 



 






 



 




 



 






 



 




 



 




 


 






 



 




 



 




 



 




 



 
#line 873 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"


 



 




 



 







 



 
#line 909 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"


 



 
#line 925 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"


 



 







 



 






 



 




 



 
#line 982 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"


 



 
#line 996 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"


 



 






 



 
 

 


 




 
#line 1066 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"





 






 






 
#line 1096 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"







 
#line 1114 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"






 















 















 














 














 



















 



















 
















 
















 








 







 







 






 







 










 











 
#line 1326 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"








 



















 




















 

















 
















 
















 
















 




















 




















 













 












 
















 













 





 
 

 


 

 




 
 

 


 



#line 1591 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"









































































#line 1674 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"














































#line 1728 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"













#line 1747 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"

#line 1756 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"























#line 1797 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"













































#line 1849 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"













#line 1873 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"



 
 

 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim_ex.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim_ex.h"



 



 

 


 



 

typedef struct
{
  uint32_t IC1Polarity;         
 

  uint32_t IC1Prescaler;        
 

  uint32_t IC1Filter;           
 

  uint32_t Commutation_Delay;   
 
} TIM_HallSensor_InitTypeDef;


 
 

 


 



 
#line 82 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim_ex.h"












#line 106 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim_ex.h"


 



 
 

 


 



 
 

 


 
#line 193 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim_ex.h"



 
 

 


 




 
 
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Init(TIM_HandleTypeDef *htim, const TIM_HallSensor_InitTypeDef *sConfig);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_DeInit(TIM_HandleTypeDef *htim);

void HAL_TIMEx_HallSensor_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIMEx_HallSensor_MspDeInit(TIM_HandleTypeDef *htim);

 
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Start(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Stop(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Start_IT(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Stop_IT(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Start_DMA(TIM_HandleTypeDef *htim, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Stop_DMA(TIM_HandleTypeDef *htim);


 




 
 
 
HAL_StatusTypeDef HAL_TIMEx_OCN_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_OCN_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

 
HAL_StatusTypeDef HAL_TIMEx_OCN_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_OCN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

 
HAL_StatusTypeDef HAL_TIMEx_OCN_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, const uint32_t *pData,
                                          uint16_t Length);
HAL_StatusTypeDef HAL_TIMEx_OCN_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
 
HAL_StatusTypeDef HAL_TIMEx_PWMN_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_PWMN_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

 
HAL_StatusTypeDef HAL_TIMEx_PWMN_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_PWMN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIMEx_PWMN_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, const uint32_t *pData,
                                           uint16_t Length);
HAL_StatusTypeDef HAL_TIMEx_PWMN_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
 
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Start(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Stop(TIM_HandleTypeDef *htim, uint32_t OutputChannel);

 
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Start_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);


 




 
 
HAL_StatusTypeDef HAL_TIMEx_ConfigCommutEvent(TIM_HandleTypeDef *htim, uint32_t  InputTrigger,
                                              uint32_t  CommutationSource);
HAL_StatusTypeDef HAL_TIMEx_ConfigCommutEvent_IT(TIM_HandleTypeDef *htim, uint32_t  InputTrigger,
                                                 uint32_t  CommutationSource);
HAL_StatusTypeDef HAL_TIMEx_ConfigCommutEvent_DMA(TIM_HandleTypeDef *htim, uint32_t  InputTrigger,
                                                  uint32_t  CommutationSource);
HAL_StatusTypeDef HAL_TIMEx_MasterConfigSynchronization(TIM_HandleTypeDef *htim,
                                                        const TIM_MasterConfigTypeDef *sMasterConfig);
HAL_StatusTypeDef HAL_TIMEx_ConfigBreakDeadTime(TIM_HandleTypeDef *htim,
                                                const TIM_BreakDeadTimeConfigTypeDef *sBreakDeadTimeConfig);
HAL_StatusTypeDef HAL_TIMEx_RemapConfig(TIM_HandleTypeDef *htim, uint32_t Remap);


 




 
 
void HAL_TIMEx_CommutCallback(TIM_HandleTypeDef *htim);
void HAL_TIMEx_CommutHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIMEx_BreakCallback(TIM_HandleTypeDef *htim);


 




 
 
HAL_TIM_StateTypeDef HAL_TIMEx_HallSensor_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_ChannelStateTypeDef HAL_TIMEx_GetChannelNState(const TIM_HandleTypeDef *htim,  uint32_t ChannelN);


 



 
 

 


 
void TIMEx_DMACommutationCplt(DMA_HandleTypeDef *hdma);
void TIMEx_DMACommutationHalfCplt(DMA_HandleTypeDef *hdma);


 
 



 



 






#line 1881 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"

 


 




 
 
HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_Base_Start(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_Stop(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_Base_Start_DMA(TIM_HandleTypeDef *htim, const uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_Base_Stop_DMA(TIM_HandleTypeDef *htim);


 




 
 
HAL_StatusTypeDef HAL_TIM_OC_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_OC_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_OC_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OC_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_OC_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OC_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_OC_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, const uint32_t *pData,
                                       uint16_t Length);
HAL_StatusTypeDef HAL_TIM_OC_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
HAL_StatusTypeDef HAL_TIM_PWM_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_PWM_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_PWM_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_PWM_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, const uint32_t *pData,
                                        uint16_t Length);
HAL_StatusTypeDef HAL_TIM_PWM_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
HAL_StatusTypeDef HAL_TIM_IC_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_IC_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_IC_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_IC_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_IC_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_IC_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
HAL_StatusTypeDef HAL_TIM_OnePulse_Init(TIM_HandleTypeDef *htim, uint32_t OnePulseMode);
HAL_StatusTypeDef HAL_TIM_OnePulse_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OnePulse_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OnePulse_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_OnePulse_Start(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIM_OnePulse_Stop(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
 
HAL_StatusTypeDef HAL_TIM_OnePulse_Start_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIM_OnePulse_Stop_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);


 




 
 
HAL_StatusTypeDef HAL_TIM_Encoder_Init(TIM_HandleTypeDef *htim, const TIM_Encoder_InitTypeDef *sConfig);
HAL_StatusTypeDef HAL_TIM_Encoder_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Encoder_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_Encoder_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_Encoder_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_Encoder_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_Encoder_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_Encoder_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData1,
                                            uint32_t *pData2, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_Encoder_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim);


 




 
 
HAL_StatusTypeDef HAL_TIM_OC_ConfigChannel(TIM_HandleTypeDef *htim, const TIM_OC_InitTypeDef *sConfig,
                                           uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_ConfigChannel(TIM_HandleTypeDef *htim, const TIM_OC_InitTypeDef *sConfig,
                                            uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_ConfigChannel(TIM_HandleTypeDef *htim, const TIM_IC_InitTypeDef *sConfig,
                                           uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OnePulse_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OnePulse_InitTypeDef *sConfig,
                                                 uint32_t OutputChannel,  uint32_t InputChannel);
HAL_StatusTypeDef HAL_TIM_ConfigOCrefClear(TIM_HandleTypeDef *htim,
                                           const TIM_ClearInputConfigTypeDef *sClearInputConfig,
                                           uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_ConfigClockSource(TIM_HandleTypeDef *htim, const TIM_ClockConfigTypeDef *sClockSourceConfig);
HAL_StatusTypeDef HAL_TIM_ConfigTI1Input(TIM_HandleTypeDef *htim, uint32_t TI1_Selection);
HAL_StatusTypeDef HAL_TIM_SlaveConfigSynchro(TIM_HandleTypeDef *htim, const TIM_SlaveConfigTypeDef *sSlaveConfig);
HAL_StatusTypeDef HAL_TIM_SlaveConfigSynchro_IT(TIM_HandleTypeDef *htim, const TIM_SlaveConfigTypeDef *sSlaveConfig);
HAL_StatusTypeDef HAL_TIM_DMABurst_WriteStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                              uint32_t BurstRequestSrc, const uint32_t  *BurstBuffer,
                                              uint32_t  BurstLength);
HAL_StatusTypeDef HAL_TIM_DMABurst_MultiWriteStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                                   uint32_t BurstRequestSrc, const uint32_t *BurstBuffer,
                                                   uint32_t BurstLength,  uint32_t DataLength);
HAL_StatusTypeDef HAL_TIM_DMABurst_WriteStop(TIM_HandleTypeDef *htim, uint32_t BurstRequestSrc);
HAL_StatusTypeDef HAL_TIM_DMABurst_ReadStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                             uint32_t BurstRequestSrc, uint32_t  *BurstBuffer, uint32_t  BurstLength);
HAL_StatusTypeDef HAL_TIM_DMABurst_MultiReadStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                                  uint32_t BurstRequestSrc, uint32_t  *BurstBuffer,
                                                  uint32_t  BurstLength, uint32_t  DataLength);
HAL_StatusTypeDef HAL_TIM_DMABurst_ReadStop(TIM_HandleTypeDef *htim, uint32_t BurstRequestSrc);
HAL_StatusTypeDef HAL_TIM_GenerateEvent(TIM_HandleTypeDef *htim, uint32_t EventSource);
uint32_t HAL_TIM_ReadCapturedValue(const TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PeriodElapsedHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_CaptureHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_TriggerCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_TriggerHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_ErrorCallback(TIM_HandleTypeDef *htim);

 








 




 
 
HAL_TIM_StateTypeDef HAL_TIM_Base_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_OC_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_PWM_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_IC_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_OnePulse_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_Encoder_GetState(const TIM_HandleTypeDef *htim);

 
HAL_TIM_ActiveChannel HAL_TIM_GetActiveChannel(const TIM_HandleTypeDef *htim);
HAL_TIM_ChannelStateTypeDef HAL_TIM_GetChannelState(const TIM_HandleTypeDef *htim,  uint32_t Channel);
HAL_TIM_DMABurstStateTypeDef HAL_TIM_DMABurstState(const TIM_HandleTypeDef *htim);


 



 
 

 


 
void TIM_Base_SetConfig(TIM_TypeDef *TIMx, const TIM_Base_InitTypeDef *Structure);
void TIM_TI1_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection, uint32_t TIM_ICFilter);
void TIM_OC2_SetConfig(TIM_TypeDef *TIMx, const TIM_OC_InitTypeDef *OC_Config);
void TIM_ETR_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ExtTRGPrescaler,
                       uint32_t TIM_ExtTRGPolarity, uint32_t ExtTRGFilter);

void TIM_DMADelayPulseHalfCplt(DMA_HandleTypeDef *hdma);
void TIM_DMAError(DMA_HandleTypeDef *hdma);
void TIM_DMACaptureCplt(DMA_HandleTypeDef *hdma);
void TIM_DMACaptureHalfCplt(DMA_HandleTypeDef *hdma);
void TIM_CCxChannelCmd(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t ChannelState);







 
 



 



 





#line 408 "../Core/Inc/stm32f4xx_hal_conf.h"


#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_uart.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_uart.h"



 



 

 


 



 
typedef struct
{
  uint32_t BaudRate;                  



 

  uint32_t WordLength;                
 

  uint32_t StopBits;                  
 

  uint32_t Parity;                    




 

  uint32_t Mode;                      
 

  uint32_t HwFlowCtl;                 
 

  uint32_t OverSampling;              
 
} UART_InitTypeDef;







































 
typedef enum
{
  HAL_UART_STATE_RESET             = 0x00U,    
 
  HAL_UART_STATE_READY             = 0x20U,    
 
  HAL_UART_STATE_BUSY              = 0x24U,    
 
  HAL_UART_STATE_BUSY_TX           = 0x21U,    
 
  HAL_UART_STATE_BUSY_RX           = 0x22U,    
 
  HAL_UART_STATE_BUSY_TX_RX        = 0x23U,    

 
  HAL_UART_STATE_TIMEOUT           = 0xA0U,    
 
  HAL_UART_STATE_ERROR             = 0xE0U     
 
} HAL_UART_StateTypeDef;







 
typedef uint32_t HAL_UART_RxTypeTypeDef;









 
typedef uint32_t HAL_UART_RxEventTypeTypeDef;



 
typedef struct __UART_HandleTypeDef
{
  USART_TypeDef                 *Instance;         

  UART_InitTypeDef              Init;              

  const uint8_t                 *pTxBuffPtr;       

  uint16_t                      TxXferSize;        

  volatile uint16_t                 TxXferCount;       

  uint8_t                       *pRxBuffPtr;       

  uint16_t                      RxXferSize;        

  volatile uint16_t                 RxXferCount;       

  volatile HAL_UART_RxTypeTypeDef ReceptionType;       

  volatile HAL_UART_RxEventTypeTypeDef RxEventType;    

  DMA_HandleTypeDef             *hdmatx;           

  DMA_HandleTypeDef             *hdmarx;           

  HAL_LockTypeDef               Lock;              

  volatile HAL_UART_StateTypeDef    gState;           

 

  volatile HAL_UART_StateTypeDef    RxState;          
 

  volatile uint32_t                 ErrorCode;         

#line 212 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_uart.h"

} UART_HandleTypeDef;

#line 243 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_uart.h"



 

 


 



 
#line 265 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_uart.h"


 



 




 



 




 



 





 



 






 



 





 



 




 



 




 



 




 



 




 





 
#line 369 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_uart.h"


 









 













 



 




 



 





 



 

 


 






 
#line 444 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_uart.h"





 



















 























 







 
#line 509 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_uart.h"






 







 







 







 

















 



















 


















 
















 



















 



















 



















 









 





 






 





 



 

 


 



 

 
HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_HalfDuplex_Init(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_LIN_Init(UART_HandleTypeDef *huart, uint32_t BreakDetectLength);
HAL_StatusTypeDef HAL_MultiProcessor_Init(UART_HandleTypeDef *huart, uint8_t Address, uint32_t WakeUpMethod);
HAL_StatusTypeDef HAL_UART_DeInit(UART_HandleTypeDef *huart);
void HAL_UART_MspInit(UART_HandleTypeDef *huart);
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart);

 
#line 735 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_uart.h"



 



 

 
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_DMAPause(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DMAResume(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DMAStop(UART_HandleTypeDef *huart);

HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint16_t *RxLen,
                                           uint32_t Timeout);
HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

HAL_UART_RxEventTypeTypeDef HAL_UARTEx_GetRxEventType(UART_HandleTypeDef *huart);

 
HAL_StatusTypeDef HAL_UART_Abort(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortTransmit(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortReceive(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_Abort_IT(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortTransmit_IT(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortReceive_IT(UART_HandleTypeDef *huart);

void HAL_UART_IRQHandler(UART_HandleTypeDef *huart);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);
void HAL_UART_AbortCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_AbortTransmitCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_AbortReceiveCpltCallback(UART_HandleTypeDef *huart);

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);



 



 
 
HAL_StatusTypeDef HAL_LIN_SendBreak(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_MultiProcessor_EnterMuteMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_MultiProcessor_ExitMuteMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_HalfDuplex_EnableTransmitter(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_HalfDuplex_EnableReceiver(UART_HandleTypeDef *huart);


 



 
 
HAL_UART_StateTypeDef HAL_UART_GetState(const UART_HandleTypeDef *huart);
uint32_t              HAL_UART_GetError(const UART_HandleTypeDef *huart);


 



 
 
 
 


 


 







 

 


 
#line 859 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_uart.h"






 









 






 

 


 

HAL_StatusTypeDef UART_Start_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef UART_Start_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);



 



 



 







#line 412 "../Core/Inc/stm32f4xx_hal_conf.h"






















#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_hcd.h"
















 

 







 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_usb.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_usb.h"




 



 

 










 

typedef enum
{
  USB_DEVICE_MODE = 0,
  USB_HOST_MODE   = 1,
  USB_DRD_MODE    = 2
} USB_ModeTypeDef;



 
typedef enum
{
  URB_IDLE = 0,
  URB_DONE,
  URB_NOTREADY,
  URB_NYET,
  URB_ERROR,
  URB_STALL
} USB_URBStateTypeDef;



 
typedef enum
{
  HC_IDLE = 0,
  HC_XFRC,
  HC_HALTED,
  HC_ACK,
  HC_NAK,
  HC_NYET,
  HC_STALL,
  HC_XACTERR,
  HC_BBLERR,
  HC_DATATGLERR
} USB_HCStateTypeDef;




 
typedef struct
{
  uint8_t dev_endpoints;            

 

  uint8_t Host_channels;            

 

  uint8_t dma_enable;              
 

  uint8_t speed;                   

 

  uint8_t ep0_mps;                  

  uint8_t phy_itface;              
 

  uint8_t Sof_enable;               

  uint8_t low_power_enable;         

  uint8_t lpm_enable;               

  uint8_t battery_charging_enable;  

  uint8_t vbus_sensing_enable;      

  uint8_t use_dedicated_ep1;        

  uint8_t use_external_vbus;        

} USB_CfgTypeDef;

typedef struct
{
  uint8_t   num;                  
 

  uint8_t   is_in;                
 

  uint8_t   is_stall;             
 

  uint8_t   is_iso_incomplete;    
 

  uint8_t   type;                 
 

  uint8_t   data_pid_start;       
 

  uint32_t  maxpacket;            
 

  uint8_t   *xfer_buff;            

  uint32_t  xfer_len;              

  uint32_t  xfer_count;            

  uint8_t   even_odd_frame;       
 

  uint16_t  tx_fifo_num;          
 

  uint32_t  dma_addr;              

  uint32_t  xfer_size;             
} USB_EPTypeDef;

typedef struct
{
  uint8_t   dev_addr;           
 

  uint8_t   ch_num;             
 

  uint8_t   ep_num;             
 

  uint8_t   ep_is_in;           
 

  uint8_t   speed;              

 

  uint8_t   do_ping;             
  uint8_t   do_ssplit;           
  uint8_t   do_csplit;           
  uint8_t   ep_ss_schedule;      
  uint32_t  iso_splt_xactPos;    

  uint8_t   hub_port_nbr;        
  uint8_t   hub_addr;            

  uint8_t   ep_type;            
 

  uint16_t  max_packet;         
 

  uint8_t   data_pid;           
 

  uint8_t   *xfer_buff;          

  uint32_t  XferSize;            

  uint32_t  xfer_len;            

  uint32_t  xfer_count;          

  uint8_t   toggle_in;          
 

  uint8_t   toggle_out;         
 

  uint32_t  dma_addr;            

  uint32_t  ErrCnt;              
  uint32_t  NyetErrCnt;          

  USB_URBStateTypeDef urb_state;  
 

  USB_HCStateTypeDef state;       
 
} USB_HCTypeDef;

typedef USB_ModeTypeDef     USB_OTG_ModeTypeDef;
typedef USB_CfgTypeDef      USB_OTG_CfgTypeDef;
typedef USB_EPTypeDef       USB_OTG_EPTypeDef;
typedef USB_URBStateTypeDef USB_OTG_URBStateTypeDef;
typedef USB_HCStateTypeDef  USB_OTG_HCStateTypeDef;
typedef USB_HCTypeDef       USB_OTG_HCTypeDef;

 



 




 




 



 





 



 





 



 




 



 
#line 295 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_usb.h"


 



 





 



 





 



 






 



 






 



 







 



 





 



 






 



 







 




 







 



 





 



 





 



 





 

















































 

 


 









 

 


 

HAL_StatusTypeDef USB_CoreInit(USB_OTG_GlobalTypeDef *USBx, USB_OTG_CfgTypeDef cfg);
HAL_StatusTypeDef USB_DevInit(USB_OTG_GlobalTypeDef *USBx, USB_OTG_CfgTypeDef cfg);
HAL_StatusTypeDef USB_EnableGlobalInt(USB_OTG_GlobalTypeDef *USBx);
HAL_StatusTypeDef USB_DisableGlobalInt(USB_OTG_GlobalTypeDef *USBx);
HAL_StatusTypeDef USB_SetTurnaroundTime(USB_OTG_GlobalTypeDef *USBx, uint32_t hclk, uint8_t speed);
HAL_StatusTypeDef USB_SetCurrentMode(USB_OTG_GlobalTypeDef *USBx, USB_OTG_ModeTypeDef mode);
HAL_StatusTypeDef USB_SetDevSpeed(const USB_OTG_GlobalTypeDef *USBx, uint8_t speed);
HAL_StatusTypeDef USB_FlushRxFifo(USB_OTG_GlobalTypeDef *USBx);
HAL_StatusTypeDef USB_FlushTxFifo(USB_OTG_GlobalTypeDef *USBx, uint32_t num);
HAL_StatusTypeDef USB_ActivateEndpoint(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep);
HAL_StatusTypeDef USB_DeactivateEndpoint(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep);
HAL_StatusTypeDef USB_ActivateDedicatedEndpoint(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep);
HAL_StatusTypeDef USB_DeactivateDedicatedEndpoint(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep);
HAL_StatusTypeDef USB_EPStartXfer(USB_OTG_GlobalTypeDef *USBx, USB_OTG_EPTypeDef *ep, uint8_t dma);
HAL_StatusTypeDef USB_WritePacket(const USB_OTG_GlobalTypeDef *USBx, uint8_t *src,
                                  uint8_t ch_ep_num, uint16_t len, uint8_t dma);

void             *USB_ReadPacket(const USB_OTG_GlobalTypeDef *USBx, uint8_t *dest, uint16_t len);
HAL_StatusTypeDef USB_EPSetStall(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep);
HAL_StatusTypeDef USB_EPClearStall(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep);
HAL_StatusTypeDef USB_EPStopXfer(const USB_OTG_GlobalTypeDef *USBx, USB_OTG_EPTypeDef *ep);
HAL_StatusTypeDef USB_SetDevAddress(const USB_OTG_GlobalTypeDef *USBx, uint8_t address);
HAL_StatusTypeDef USB_DevConnect(const USB_OTG_GlobalTypeDef *USBx);
HAL_StatusTypeDef USB_DevDisconnect(const USB_OTG_GlobalTypeDef *USBx);
HAL_StatusTypeDef USB_StopDevice(USB_OTG_GlobalTypeDef *USBx);
HAL_StatusTypeDef USB_ActivateSetup(const USB_OTG_GlobalTypeDef *USBx);
HAL_StatusTypeDef USB_EP0_OutStart(const USB_OTG_GlobalTypeDef *USBx, uint8_t dma, const uint8_t *psetup);
uint8_t           USB_GetDevSpeed(const USB_OTG_GlobalTypeDef *USBx);
uint32_t          USB_GetMode(const USB_OTG_GlobalTypeDef *USBx);
uint32_t          USB_ReadInterrupts(USB_OTG_GlobalTypeDef const *USBx);
uint32_t          USB_ReadChInterrupts(const USB_OTG_GlobalTypeDef *USBx, uint8_t chnum);
uint32_t          USB_ReadDevAllOutEpInterrupt(const USB_OTG_GlobalTypeDef *USBx);
uint32_t          USB_ReadDevOutEPInterrupt(const USB_OTG_GlobalTypeDef *USBx, uint8_t epnum);
uint32_t          USB_ReadDevAllInEpInterrupt(const USB_OTG_GlobalTypeDef *USBx);
uint32_t          USB_ReadDevInEPInterrupt(const USB_OTG_GlobalTypeDef *USBx, uint8_t epnum);
void              USB_ClearInterrupts(USB_OTG_GlobalTypeDef *USBx, uint32_t interrupt);

HAL_StatusTypeDef USB_HostInit(USB_OTG_GlobalTypeDef *USBx, USB_OTG_CfgTypeDef cfg);
HAL_StatusTypeDef USB_InitFSLSPClkSel(const USB_OTG_GlobalTypeDef *USBx, uint8_t freq);
HAL_StatusTypeDef USB_ResetPort(const USB_OTG_GlobalTypeDef *USBx);
HAL_StatusTypeDef USB_DriveVbus(const USB_OTG_GlobalTypeDef *USBx, uint8_t state);
uint32_t          USB_GetHostSpeed(USB_OTG_GlobalTypeDef const *USBx);
uint32_t          USB_GetCurrentFrame(USB_OTG_GlobalTypeDef const *USBx);
HAL_StatusTypeDef USB_HC_Init(USB_OTG_GlobalTypeDef *USBx, uint8_t ch_num,
                              uint8_t epnum, uint8_t dev_address, uint8_t speed,
                              uint8_t ep_type, uint16_t mps);
HAL_StatusTypeDef USB_HC_StartXfer(USB_OTG_GlobalTypeDef *USBx,
                                   USB_OTG_HCTypeDef *hc, uint8_t dma);

uint32_t          USB_HC_ReadInterrupt(const USB_OTG_GlobalTypeDef *USBx);
HAL_StatusTypeDef USB_HC_Halt(const USB_OTG_GlobalTypeDef *USBx, uint8_t hc_num);
HAL_StatusTypeDef USB_DoPing(const USB_OTG_GlobalTypeDef *USBx, uint8_t ch_num);
HAL_StatusTypeDef USB_StopHost(USB_OTG_GlobalTypeDef *USBx);
HAL_StatusTypeDef USB_ActivateRemoteWakeup(const USB_OTG_GlobalTypeDef *USBx);
HAL_StatusTypeDef USB_DeActivateRemoteWakeup(const USB_OTG_GlobalTypeDef *USBx);




 



 



 



 







#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_hcd.h"




 



 

 


 



 
typedef enum
{
  HAL_HCD_STATE_RESET    = 0x00,
  HAL_HCD_STATE_READY    = 0x01,
  HAL_HCD_STATE_ERROR    = 0x02,
  HAL_HCD_STATE_BUSY     = 0x03,
  HAL_HCD_STATE_TIMEOUT  = 0x04
} HCD_StateTypeDef;

typedef USB_OTG_GlobalTypeDef   HCD_TypeDef;
typedef USB_OTG_CfgTypeDef      HCD_InitTypeDef;
typedef USB_OTG_HCTypeDef       HCD_HCTypeDef;
typedef USB_OTG_URBStateTypeDef HCD_URBStateTypeDef;
typedef USB_OTG_HCStateTypeDef  HCD_HCStateTypeDef;


 



 



typedef struct

{
  HCD_TypeDef               *Instance;   
  HCD_InitTypeDef           Init;        
  HCD_HCTypeDef             hc[16];      
  HAL_LockTypeDef           Lock;        
  volatile HCD_StateTypeDef     State;       
  volatile  uint32_t            ErrorCode;   
  void                      *pData;      
#line 93 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_hcd.h"
} HCD_HandleTypeDef;


 



 

 


 



 





 



 





 



 




 




 






 



 

 



 












#line 177 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_hcd.h"


 

 


 



 
HAL_StatusTypeDef HAL_HCD_Init(HCD_HandleTypeDef *hhcd);
HAL_StatusTypeDef HAL_HCD_DeInit(HCD_HandleTypeDef *hhcd);
HAL_StatusTypeDef HAL_HCD_HC_Init(HCD_HandleTypeDef *hhcd, uint8_t ch_num,
                                  uint8_t epnum, uint8_t dev_address,
                                  uint8_t speed, uint8_t ep_type, uint16_t mps);

HAL_StatusTypeDef HAL_HCD_HC_Halt(HCD_HandleTypeDef *hhcd, uint8_t ch_num);
void              HAL_HCD_MspInit(HCD_HandleTypeDef *hhcd);
void              HAL_HCD_MspDeInit(HCD_HandleTypeDef *hhcd);

#line 245 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_hcd.h"


 

 


 
HAL_StatusTypeDef HAL_HCD_HC_SubmitRequest(HCD_HandleTypeDef *hhcd, uint8_t ch_num,
                                           uint8_t direction, uint8_t ep_type,
                                           uint8_t token, uint8_t *pbuff,
                                           uint16_t length, uint8_t do_ping);

HAL_StatusTypeDef HAL_HCD_HC_SetHubInfo(HCD_HandleTypeDef *hhcd, uint8_t ch_num,
                                        uint8_t addr, uint8_t PortNbr);

HAL_StatusTypeDef HAL_HCD_HC_ClearHubInfo(HCD_HandleTypeDef *hhcd, uint8_t ch_num);

 
void HAL_HCD_IRQHandler(HCD_HandleTypeDef *hhcd);
void HAL_HCD_WKUP_IRQHandler(HCD_HandleTypeDef *hhcd);
void HAL_HCD_SOF_Callback(HCD_HandleTypeDef *hhcd);
void HAL_HCD_Connect_Callback(HCD_HandleTypeDef *hhcd);
void HAL_HCD_Disconnect_Callback(HCD_HandleTypeDef *hhcd);
void HAL_HCD_PortEnabled_Callback(HCD_HandleTypeDef *hhcd);
void HAL_HCD_PortDisabled_Callback(HCD_HandleTypeDef *hhcd);
void HAL_HCD_HC_NotifyURBChange_Callback(HCD_HandleTypeDef *hhcd, uint8_t chnum,
                                         HCD_URBStateTypeDef urb_state);


 

 


 
HAL_StatusTypeDef HAL_HCD_ResetPort(HCD_HandleTypeDef *hhcd);
HAL_StatusTypeDef HAL_HCD_Start(HCD_HandleTypeDef *hhcd);
HAL_StatusTypeDef HAL_HCD_Stop(HCD_HandleTypeDef *hhcd);


 

 


 
HCD_StateTypeDef        HAL_HCD_GetState(HCD_HandleTypeDef const *hhcd);
HCD_URBStateTypeDef     HAL_HCD_HC_GetURBState(HCD_HandleTypeDef const *hhcd, uint8_t chnum);
HCD_HCStateTypeDef      HAL_HCD_HC_GetState(HCD_HandleTypeDef const *hhcd, uint8_t chnum);
uint32_t                HAL_HCD_HC_GetXferCount(HCD_HandleTypeDef const *hhcd, uint8_t chnum);
uint32_t                HAL_HCD_GetCurrentFrame(HCD_HandleTypeDef *hhcd);
uint32_t                HAL_HCD_GetCurrentSpeed(HCD_HandleTypeDef *hhcd);




 

 


 


 
 



 


 


 






#line 436 "../Core/Inc/stm32f4xx_hal_conf.h"






































 
#line 490 "../Core/Inc/stm32f4xx_hal_conf.h"





#line 30 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h"



 



  

 
 



 



 
typedef enum
{
  HAL_TICK_FREQ_10HZ         = 100U,
  HAL_TICK_FREQ_100HZ        = 10U,
  HAL_TICK_FREQ_1KHZ         = 1U,
  HAL_TICK_FREQ_DEFAULT      = HAL_TICK_FREQ_1KHZ
} HAL_TickFreqTypeDef;


 



 
   
 


 


 
#line 93 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h"

#line 116 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h"


 



 





 






 





#line 155 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h"

#line 185 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h"


 



 





 

 



 
extern volatile uint32_t uwTick;
extern uint32_t uwTickPrio;
extern HAL_TickFreqTypeDef uwTickFreq;


 

 


 


 
 
HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_DeInit(void);
void HAL_MspInit(void);
void HAL_MspDeInit(void);
HAL_StatusTypeDef HAL_InitTick (uint32_t TickPriority);


 



 
 
void HAL_IncTick(void);
void HAL_Delay(uint32_t Delay);
uint32_t HAL_GetTick(void);
uint32_t HAL_GetTickPrio(void);
HAL_StatusTypeDef HAL_SetTickFreq(HAL_TickFreqTypeDef Freq);
HAL_TickFreqTypeDef HAL_GetTickFreq(void);
void HAL_SuspendTick(void);
void HAL_ResumeTick(void);
uint32_t HAL_GetHalVersion(void);
uint32_t HAL_GetREVID(void);
uint32_t HAL_GetDEVID(void);
void HAL_DBGMCU_EnableDBGSleepMode(void);
void HAL_DBGMCU_DisableDBGSleepMode(void);
void HAL_DBGMCU_EnableDBGStopMode(void);
void HAL_DBGMCU_DisableDBGStopMode(void);
void HAL_DBGMCU_EnableDBGStandbyMode(void);
void HAL_DBGMCU_DisableDBGStandbyMode(void);
void HAL_EnableCompensationCell(void);
void HAL_DisableCompensationCell(void);
uint32_t HAL_GetUIDw0(void);
uint32_t HAL_GetUIDw1(void);
uint32_t HAL_GetUIDw2(void);







 



 
 
 


 


 
 


 


 
 
 


 



  
  







#line 43 "../Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.c"



 



 
 
 
 
 
 

static HAL_StatusTypeDef USB_CoreReset(USB_OTG_GlobalTypeDef *USBx);

 


 











 







 
HAL_StatusTypeDef USB_CoreInit(USB_OTG_GlobalTypeDef *USBx, USB_OTG_CfgTypeDef cfg)
{
  HAL_StatusTypeDef ret;
  if (cfg.phy_itface == 1U)
  {
    USBx->GCCFG &= ~((0x1UL << (16U)));

     
    USBx->GUSBCFG &= ~((0x1UL << (22U)) | (0x1UL << (17U)) | (0x1UL << (6U)));

     
    USBx->GUSBCFG &= ~((0x1UL << (20U)) | (0x1UL << (21U)));
    if (cfg.use_external_vbus == 1U)
    {
      USBx->GUSBCFG |= (0x1UL << (20U));
    }

     
    ret = USB_CoreReset(USBx);
  }
  else  
  {
     
    USBx->GUSBCFG |= (0x1UL << (6U));

     
    ret = USB_CoreReset(USBx);

    if (cfg.battery_charging_enable == 0U)
    {
       
      USBx->GCCFG |= (0x1UL << (16U));
    }
    else
    {
       
      USBx->GCCFG &= ~((0x1UL << (16U)));
    }
  }

  if (cfg.dma_enable == 1U)
  {
    USBx->GAHBCFG |= (0x3UL << (1U));
    USBx->GAHBCFG |= (0x1UL << (5U));
  }

  return ret;
}







 
HAL_StatusTypeDef USB_SetTurnaroundTime(USB_OTG_GlobalTypeDef *USBx,
                                        uint32_t hclk, uint8_t speed)
{
  uint32_t UsbTrd;

  


 
  if (speed == 2U)
  {
    if ((hclk >= 14200000U) && (hclk < 15000000U))
    {
       
      UsbTrd = 0xFU;
    }
    else if ((hclk >= 15000000U) && (hclk < 16000000U))
    {
       
      UsbTrd = 0xEU;
    }
    else if ((hclk >= 16000000U) && (hclk < 17200000U))
    {
       
      UsbTrd = 0xDU;
    }
    else if ((hclk >= 17200000U) && (hclk < 18500000U))
    {
       
      UsbTrd = 0xCU;
    }
    else if ((hclk >= 18500000U) && (hclk < 20000000U))
    {
       
      UsbTrd = 0xBU;
    }
    else if ((hclk >= 20000000U) && (hclk < 21800000U))
    {
       
      UsbTrd = 0xAU;
    }
    else if ((hclk >= 21800000U) && (hclk < 24000000U))
    {
       
      UsbTrd = 0x9U;
    }
    else if ((hclk >= 24000000U) && (hclk < 27700000U))
    {
       
      UsbTrd = 0x8U;
    }
    else if ((hclk >= 27700000U) && (hclk < 32000000U))
    {
       
      UsbTrd = 0x7U;
    }
    else  
    {
       
      UsbTrd = 0x6U;
    }
  }
  else if (speed == 0U)
  {
    UsbTrd = 9U;
  }
  else
  {
    UsbTrd = 9U;
  }

  USBx->GUSBCFG &= ~(0xFUL << (10U));
  USBx->GUSBCFG |= (uint32_t)((UsbTrd << 10) & (0xFUL << (10U)));

  return HAL_OK;
}






 
HAL_StatusTypeDef USB_EnableGlobalInt(USB_OTG_GlobalTypeDef *USBx)
{
  USBx->GAHBCFG |= (0x1UL << (0U));
  return HAL_OK;
}






 
HAL_StatusTypeDef USB_DisableGlobalInt(USB_OTG_GlobalTypeDef *USBx)
{
  USBx->GAHBCFG &= ~(0x1UL << (0U));
  return HAL_OK;
}









 
HAL_StatusTypeDef USB_SetCurrentMode(USB_OTG_GlobalTypeDef *USBx, USB_OTG_ModeTypeDef mode)
{
  uint32_t ms = 0U;

  USBx->GUSBCFG &= ~((0x1UL << (29U)) | (0x1UL << (30U)));

  if (mode == USB_HOST_MODE)
  {
    USBx->GUSBCFG |= (0x1UL << (29U));

    do
    {
      HAL_Delay(10U);
      ms += 10U;
    } while ((USB_GetMode(USBx) != (uint32_t)USB_HOST_MODE) && (ms < 200U));
  }
  else if (mode == USB_DEVICE_MODE)
  {
    USBx->GUSBCFG |= (0x1UL << (30U));

    do
    {
      HAL_Delay(10U);
      ms += 10U;
    } while ((USB_GetMode(USBx) != (uint32_t)USB_DEVICE_MODE) && (ms < 200U));
  }
  else
  {
    return HAL_ERROR;
  }

  if (ms == 200U)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}








 
HAL_StatusTypeDef USB_DevInit(USB_OTG_GlobalTypeDef *USBx, USB_OTG_CfgTypeDef cfg)
{
  HAL_StatusTypeDef ret = HAL_OK;
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t i;

  for (i = 0U; i < 15U; i++)
  {
    USBx->DIEPTXF[i] = 0U;
  }

#line 328 "../Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.c"
   
  if (cfg.vbus_sensing_enable == 0U)
  {
    


 
    ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DCTL |= (0x1UL << (1U));
    USBx->GCCFG |= (0x1UL << (21U));
    USBx->GCCFG &= ~(0x1UL << (19U));
    USBx->GCCFG &= ~(0x1UL << (18U));
  }
  else
  {
     
    USBx->GCCFG &= ~(0x1UL << (21U));
    USBx->GCCFG |= (0x1UL << (19U));
  }




   
  *(volatile uint32_t *)((uint32_t)USBx_BASE + 0xE00UL) = 0U;

  if (cfg.phy_itface == 1U)
  {
    if (cfg.speed == 0U)
    {
       
      (void)USB_SetDevSpeed(USBx, 0U);
    }
    else
    {
       
      (void)USB_SetDevSpeed(USBx, 1U);
    }
  }
  else
  {
     
    (void)USB_SetDevSpeed(USBx, 3U);
  }

   
  if (USB_FlushTxFifo(USBx, 0x10U) != HAL_OK)  
  {
    ret = HAL_ERROR;
  }

  if (USB_FlushRxFifo(USBx) != HAL_OK)
  {
    ret = HAL_ERROR;
  }

   
  ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DIEPMSK = 0U;
  ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DOEPMSK = 0U;
  ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DAINTMSK = 0U;

  for (i = 0U; i < cfg.dev_endpoints; i++)
  {
    if ((((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((i) * 0x20UL)))->DIEPCTL & (0x1UL << (31U))) == (0x1UL << (31U)))
    {
      if (i == 0U)
      {
        ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((i) * 0x20UL)))->DIEPCTL = (0x1UL << (27U));
      }
      else
      {
        ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((i) * 0x20UL)))->DIEPCTL = (0x1UL << (30U)) | (0x1UL << (27U));
      }
    }
    else
    {
      ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((i) * 0x20UL)))->DIEPCTL = 0U;
    }

    ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((i) * 0x20UL)))->DIEPTSIZ = 0U;
    ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((i) * 0x20UL)))->DIEPINT  = 0xFB7FU;
  }

  for (i = 0U; i < cfg.dev_endpoints; i++)
  {
    if ((((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((i) * 0x20UL)))->DOEPCTL & (0x1UL << (31U))) == (0x1UL << (31U)))
    {
      if (i == 0U)
      {
        ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((i) * 0x20UL)))->DOEPCTL = (0x1UL << (27U));
      }
      else
      {
        ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((i) * 0x20UL)))->DOEPCTL = (0x1UL << (30U)) | (0x1UL << (27U));
      }
    }
    else
    {
      ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((i) * 0x20UL)))->DOEPCTL = 0U;
    }

    ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((i) * 0x20UL)))->DOEPTSIZ = 0U;
    ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((i) * 0x20UL)))->DOEPINT  = 0xFB7FU;
  }

  ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DIEPMSK &= ~((0x1UL << (8U)));

   
  USBx->GINTMSK = 0U;

   
  USBx->GINTSTS = 0xBFFFFFFFU;

   
  if (cfg.dma_enable == 0U)
  {
    USBx->GINTMSK |= (0x1UL << (4U));
  }

   
  USBx->GINTMSK |= (0x1UL << (11U)) | (0x1UL << (12U)) |
                   (0x1UL << (13U)) | (0x1UL << (18U)) |
                   (0x1UL << (19U))   | (0x1UL << (20U)) |
                   (0x1UL << (21U)) | (0x1UL << (31U));

  if (cfg.Sof_enable != 0U)
  {
    USBx->GINTMSK |= (0x1UL << (3U));
  }

  if (cfg.vbus_sensing_enable == 1U)
  {
    USBx->GINTMSK |= ((0x1UL << (30U)) | (0x1UL << (2U)));
  }

  return ret;
}








 
HAL_StatusTypeDef USB_FlushTxFifo(USB_OTG_GlobalTypeDef *USBx, uint32_t num)
{
  volatile uint32_t count = 0U;

   
  do
  {
    count++;

    if (count > 0xF000000U)
    {
      return HAL_TIMEOUT;
    }
  } while ((USBx->GRSTCTL & (0x1UL << (31U))) == 0U);

   
  count = 0U;
  USBx->GRSTCTL = ((0x1UL << (5U)) | (num << 6));

  do
  {
    count++;

    if (count > 0xF000000U)
    {
      return HAL_TIMEOUT;
    }
  } while ((USBx->GRSTCTL & (0x1UL << (5U))) == (0x1UL << (5U)));

  return HAL_OK;
}





 
HAL_StatusTypeDef USB_FlushRxFifo(USB_OTG_GlobalTypeDef *USBx)
{
  volatile uint32_t count = 0U;

   
  do
  {
    count++;

    if (count > 0xF000000U)
    {
      return HAL_TIMEOUT;
    }
  } while ((USBx->GRSTCTL & (0x1UL << (31U))) == 0U);

   
  count = 0U;
  USBx->GRSTCTL = (0x1UL << (4U));

  do
  {
    count++;

    if (count > 0xF000000U)
    {
      return HAL_TIMEOUT;
    }
  } while ((USBx->GRSTCTL & (0x1UL << (4U))) == (0x1UL << (4U)));

  return HAL_OK;
}











 
HAL_StatusTypeDef USB_SetDevSpeed(const USB_OTG_GlobalTypeDef *USBx, uint8_t speed)
{
  uint32_t USBx_BASE = (uint32_t)USBx;

  ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DCFG |= speed;
  return HAL_OK;
}








 
uint8_t USB_GetDevSpeed(const USB_OTG_GlobalTypeDef *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint8_t speed;
  uint32_t DevEnumSpeed = ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DSTS & (0x3UL << (1U));

  if (DevEnumSpeed == (0U << 1))
  {
    speed = 0U;
  }
  else if ((DevEnumSpeed == (1U << 1)) ||
           (DevEnumSpeed == (3U << 1)))
  {
    speed = 2U;
  }
  else
  {
    speed = 0xFU;
  }

  return speed;
}






 
HAL_StatusTypeDef USB_ActivateEndpoint(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t epnum = (uint32_t)ep->num;

  if (ep->is_in == 1U)
  {
    ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DAINTMSK |= (0xFFFFUL << (0U)) & (uint32_t)(1UL << (ep->num & 0xFU));

    if ((((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPCTL & (0x1UL << (15U))) == 0U)
    {
      ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPCTL |= (ep->maxpacket & (0x7FFUL << (0U))) |
                                   ((uint32_t)ep->type << 18) | (epnum << 22) |
                                   (0x1UL << (28U)) |
                                   (0x1UL << (15U));
    }
  }
  else
  {
    ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DAINTMSK |= (0xFFFFUL << (16U)) & ((uint32_t)(1UL << (ep->num & 0xFU)) << 16);

    if (((((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPCTL) & (0x1UL << (15U))) == 0U)
    {
      ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPCTL |= (ep->maxpacket & (0x7FFUL << (0U))) |
                                    ((uint32_t)ep->type << 18) |
                                    (0x1UL << (28U)) |
                                    (0x1UL << (15U));
    }
  }
  return HAL_OK;
}






 
HAL_StatusTypeDef USB_ActivateDedicatedEndpoint(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t epnum = (uint32_t)ep->num;

   
  if (ep->is_in == 1U)
  {
    if (((((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPCTL) & (0x1UL << (15U))) == 0U)
    {
      ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPCTL |= (ep->maxpacket & (0x7FFUL << (0U))) |
                                   ((uint32_t)ep->type << 18) | (epnum << 22) |
                                   (0x1UL << (28U)) |
                                   (0x1UL << (15U));
    }

    ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DEACHMSK |= (0xFFFFUL << (0U)) & (uint32_t)(1UL << (ep->num & 0xFU));
  }
  else
  {
    if (((((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPCTL) & (0x1UL << (15U))) == 0U)
    {
      ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPCTL |= (ep->maxpacket & (0x7FFUL << (0U))) |
                                    ((uint32_t)ep->type << 18) | (epnum << 22) |
                                    (0x1UL << (15U));
    }

    ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DEACHMSK |= (0xFFFFUL << (16U)) & ((uint32_t)(1UL << (ep->num & 0xFU)) << 16);
  }

  return HAL_OK;
}






 
HAL_StatusTypeDef USB_DeactivateEndpoint(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t epnum = (uint32_t)ep->num;

   
  if (ep->is_in == 1U)
  {
    if ((((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPCTL & (0x1UL << (31U))) == (0x1UL << (31U)))
    {
      ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPCTL |= (0x1UL << (27U));
      ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPCTL |= (0x1UL << (30U));
    }

    ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DEACHMSK &= ~((0xFFFFUL << (0U)) & (uint32_t)(1UL << (ep->num & 0xFU)));
    ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DAINTMSK &= ~((0xFFFFUL << (0U)) & (uint32_t)(1UL << (ep->num & 0xFU)));
    ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPCTL &= ~((0x1UL << (15U)) |
                                   (0x7FFUL << (0U)) |
                                   (0xFUL << (22U)) |
                                   (0x1UL << (28U)) |
                                   (0x3UL << (18U)));
  }
  else
  {
    if ((((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPCTL & (0x1UL << (31U))) == (0x1UL << (31U)))
    {
      ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPCTL |= (0x1UL << (27U));
      ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPCTL |= (0x1UL << (30U));
    }

    ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DEACHMSK &= ~((0xFFFFUL << (16U)) & ((uint32_t)(1UL << (ep->num & 0xFU)) << 16));
    ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DAINTMSK &= ~((0xFFFFUL << (16U)) & ((uint32_t)(1UL << (ep->num & 0xFU)) << 16));
    ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPCTL &= ~((0x1UL << (15U)) |
                                    (0x7FFUL << (0U)) |
                                    (0x1UL << (28U)) |
                                    (0x3UL << (18U)));
  }

  return HAL_OK;
}






 
HAL_StatusTypeDef USB_DeactivateDedicatedEndpoint(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t epnum = (uint32_t)ep->num;

   
  if (ep->is_in == 1U)
  {
    if ((((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPCTL & (0x1UL << (31U))) == (0x1UL << (31U)))
    {
      ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPCTL  |= (0x1UL << (27U));
      ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPCTL  |= (0x1UL << (30U));
    }

    ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPCTL &= ~ (0x1UL << (15U));
    ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DAINTMSK &= ~((0xFFFFUL << (0U)) & (uint32_t)(1UL << (ep->num & 0xFU)));
  }
  else
  {
    if ((((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPCTL & (0x1UL << (31U))) == (0x1UL << (31U)))
    {
      ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPCTL  |= (0x1UL << (27U));
      ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPCTL  |= (0x1UL << (30U));
    }

    ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPCTL &= ~(0x1UL << (15U));
    ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DAINTMSK &= ~((0xFFFFUL << (16U)) & ((uint32_t)(1UL << (ep->num & 0xFU)) << 16));
  }

  return HAL_OK;
}










 
HAL_StatusTypeDef USB_EPStartXfer(USB_OTG_GlobalTypeDef *USBx, USB_OTG_EPTypeDef *ep, uint8_t dma)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t epnum = (uint32_t)ep->num;
  uint16_t pktcnt;

   
  if (ep->is_in == 1U)
  {
     
    if (ep->xfer_len == 0U)
    {
      ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPTSIZ &= ~((0x3FFUL << (19U)));
      ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPTSIZ |= ((0x3FFUL << (19U)) & (1U << 19));
      ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPTSIZ &= ~((0x7FFFFUL << (0U)));
    }
    else
    {
      



 
      ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPTSIZ &= ~((0x7FFFFUL << (0U)));
      ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPTSIZ &= ~((0x3FFUL << (19U)));

      if (epnum == 0U)
      {
        if (ep->xfer_len > ep->maxpacket)
        {
          ep->xfer_len = ep->maxpacket;
        }

        ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPTSIZ |= ((0x3FFUL << (19U)) & (1U << 19));
      }
      else
      {
        pktcnt = (uint16_t)((ep->xfer_len + ep->maxpacket - 1U) / ep->maxpacket);
        ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPTSIZ |= ((0x3FFUL << (19U)) & ((uint32_t)pktcnt << 19));

        if (ep->type == 1U)
        {
          ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPTSIZ &= ~((0x3UL << (29U)));
          ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPTSIZ |= ((0x3UL << (29U)) & ((uint32_t)pktcnt << 29));
        }
      }

      ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPTSIZ |= ((0x7FFFFUL << (0U)) & ep->xfer_len);
    }

    if (dma == 1U)
    {
      if ((uint32_t)ep->dma_addr != 0U)
      {
        ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPDMA = (uint32_t)(ep->dma_addr);
      }

      if (ep->type == 1U)
      {
        if ((((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DSTS & (1U << 8)) == 0U)
        {
          ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPCTL |= (0x1UL << (29U));
        }
        else
        {
          ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPCTL |= (0x1UL << (28U));
        }
      }

       
      ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPCTL |= ((0x1UL << (26U)) | (0x1UL << (31U)));
    }
    else
    {
       
      ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPCTL |= ((0x1UL << (26U)) | (0x1UL << (31U)));

      if (ep->type != 1U)
      {
         
        if (ep->xfer_len > 0U)
        {
          ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DIEPEMPMSK |= 1UL << (ep->num & 0xFU);
        }
      }
      else
      {
        if ((((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DSTS & (1U << 8)) == 0U)
        {
          ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPCTL |= (0x1UL << (29U));
        }
        else
        {
          ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPCTL |= (0x1UL << (28U));
        }

        (void)USB_WritePacket(USBx, ep->xfer_buff, ep->num, (uint16_t)ep->xfer_len, dma);
      }
    }
  }
  else  
  {
    


 
    ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPTSIZ &= ~((0x7FFFFUL << (0U)));
    ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPTSIZ &= ~((0x3FFUL << (19U)));

    if (epnum == 0U)
    {
      if (ep->xfer_len > 0U)
      {
        ep->xfer_len = ep->maxpacket;
      }

       
      ep->xfer_size = ep->maxpacket;

      ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPTSIZ |= ((0x7FFFFUL << (0U)) & ep->xfer_size);
      ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPTSIZ |= ((0x3FFUL << (19U)) & (1U << 19));
    }
    else
    {
      if (ep->xfer_len == 0U)
      {
        ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPTSIZ |= ((0x7FFFFUL << (0U)) & ep->maxpacket);
        ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPTSIZ |= ((0x3FFUL << (19U)) & (1U << 19));
      }
      else
      {
        pktcnt = (uint16_t)((ep->xfer_len + ep->maxpacket - 1U) / ep->maxpacket);
        ep->xfer_size = ep->maxpacket * pktcnt;

        ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPTSIZ |= (0x3FFUL << (19U)) & ((uint32_t)pktcnt << 19);
        ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPTSIZ |= (0x7FFFFUL << (0U)) & ep->xfer_size;
      }
    }

    if (dma == 1U)
    {
      if ((uint32_t)ep->xfer_buff != 0U)
      {
        ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPDMA = (uint32_t)(ep->xfer_buff);
      }
    }

    if (ep->type == 1U)
    {
      if ((((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DSTS & (1U << 8)) == 0U)
      {
        ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPCTL |= (0x1UL << (29U));
      }
      else
      {
        ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPCTL |= (0x1UL << (28U));
      }
    }
     
    ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPCTL |= ((0x1UL << (26U)) | (0x1UL << (31U)));
  }

  return HAL_OK;
}







 
HAL_StatusTypeDef USB_EPStopXfer(const USB_OTG_GlobalTypeDef *USBx, USB_OTG_EPTypeDef *ep)
{
  volatile uint32_t count = 0U;
  HAL_StatusTypeDef ret = HAL_OK;
  uint32_t USBx_BASE = (uint32_t)USBx;

   
  if (ep->is_in == 1U)
  {
     
    if (((((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((ep->num) * 0x20UL)))->DIEPCTL) & (0x1UL << (31U))) == (0x1UL << (31U)))
    {
      ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((ep->num) * 0x20UL)))->DIEPCTL |= ((0x1UL << (27U)));
      ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((ep->num) * 0x20UL)))->DIEPCTL |= ((0x1UL << (30U)));

      do
      {
        count++;

        if (count > 10000U)
        {
          ret = HAL_ERROR;
          break;
        }
      } while (((((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((ep->num) * 0x20UL)))->DIEPCTL) & (0x1UL << (31U))) ==  (0x1UL << (31U)));
    }
  }
  else  
  {
    if (((((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((ep->num) * 0x20UL)))->DOEPCTL) & (0x1UL << (31U))) == (0x1UL << (31U)))
    {
      ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((ep->num) * 0x20UL)))->DOEPCTL |= ((0x1UL << (27U)));
      ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((ep->num) * 0x20UL)))->DOEPCTL |= ((0x1UL << (30U)));

      do
      {
        count++;

        if (count > 10000U)
        {
          ret = HAL_ERROR;
          break;
        }
      } while (((((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((ep->num) * 0x20UL)))->DOEPCTL) & (0x1UL << (31U))) ==  (0x1UL << (31U)));
    }
  }

  return ret;
}














 
HAL_StatusTypeDef USB_WritePacket(const USB_OTG_GlobalTypeDef *USBx, uint8_t *src,
                                  uint8_t ch_ep_num, uint16_t len, uint8_t dma)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint8_t *pSrc = src;
  uint32_t count32b;
  uint32_t i;

  if (dma == 0U)
  {
    count32b = ((uint32_t)len + 3U) / 4U;
    for (i = 0U; i < count32b; i++)
    {
      *(volatile uint32_t *)(USBx_BASE + 0x1000UL + (((uint32_t)ch_ep_num) * 0x1000UL)) = (*((const __packed uint32_t *)(pSrc)));
      pSrc++;
      pSrc++;
      pSrc++;
      pSrc++;
    }
  }

  return HAL_OK;
}







 
void *USB_ReadPacket(const USB_OTG_GlobalTypeDef *USBx, uint8_t *dest, uint16_t len)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint8_t *pDest = dest;
  uint32_t pData;
  uint32_t i;
  uint32_t count32b = (uint32_t)len >> 2U;
  uint16_t remaining_bytes = len % 4U;

  for (i = 0U; i < count32b; i++)
  {
    ((*((__packed uint32_t *)(pDest))) = (*(volatile uint32_t *)(USBx_BASE + 0x1000UL + ((0U) * 0x1000UL))));
    pDest++;
    pDest++;
    pDest++;
    pDest++;
  }

   
  if (remaining_bytes != 0U)
  {
    i = 0U;
    ((*((__packed uint32_t *)(&pData))) = (*(volatile uint32_t *)(USBx_BASE + 0x1000UL + ((0U) * 0x1000UL))));

    do
    {
      *(uint8_t *)pDest = (uint8_t)(pData >> (8U * (uint8_t)(i)));
      i++;
      pDest++;
      remaining_bytes--;
    } while (remaining_bytes != 0U);
  }

  return ((void *)pDest);
}






 
HAL_StatusTypeDef USB_EPSetStall(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t epnum = (uint32_t)ep->num;

  if (ep->is_in == 1U)
  {
    if (((((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPCTL & (0x1UL << (31U))) == 0U) && (epnum != 0U))
    {
      ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPCTL &= ~((0x1UL << (30U)));
    }
    ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPCTL |= (0x1UL << (21U));
  }
  else
  {
    if (((((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPCTL & (0x1UL << (31U))) == 0U) && (epnum != 0U))
    {
      ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPCTL &= ~((0x1UL << (30U)));
    }
    ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPCTL |= (0x1UL << (21U));
  }

  return HAL_OK;
}






 
HAL_StatusTypeDef USB_EPClearStall(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t epnum = (uint32_t)ep->num;

  if (ep->is_in == 1U)
  {
    ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPCTL &= ~(0x1UL << (21U));
    if ((ep->type == 3U) || (ep->type == 2U))
    {
      ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((epnum) * 0x20UL)))->DIEPCTL |= (0x1UL << (28U));  
    }
  }
  else
  {
    ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPCTL &= ~(0x1UL << (21U));
    if ((ep->type == 3U) || (ep->type == 2U))
    {
      ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((epnum) * 0x20UL)))->DOEPCTL |= (0x1UL << (28U));  
    }
  }
  return HAL_OK;
}





 
HAL_StatusTypeDef USB_StopDevice(USB_OTG_GlobalTypeDef *USBx)
{
  HAL_StatusTypeDef ret;
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t i;

   
  for (i = 0U; i < 15U; i++)
  {
    ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((i) * 0x20UL)))->DIEPINT = 0xFB7FU;
    ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((i) * 0x20UL)))->DOEPINT = 0xFB7FU;
  }

   
  ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DIEPMSK  = 0U;
  ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DOEPMSK  = 0U;
  ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DAINTMSK = 0U;

   
  ret = USB_FlushRxFifo(USBx);
  if (ret != HAL_OK)
  {
    return ret;
  }

  ret = USB_FlushTxFifo(USBx,  0x10U);
  if (ret != HAL_OK)
  {
    return ret;
  }

  return ret;
}







 
HAL_StatusTypeDef USB_SetDevAddress(const USB_OTG_GlobalTypeDef *USBx, uint8_t address)
{
  uint32_t USBx_BASE = (uint32_t)USBx;

  ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DCFG &= ~((0x7FUL << (4U)));
  ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DCFG |= ((uint32_t)address << 4) & (0x7FUL << (4U));

  return HAL_OK;
}





 
HAL_StatusTypeDef USB_DevConnect(const USB_OTG_GlobalTypeDef *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;

   
  *(volatile uint32_t *)((uint32_t)USBx_BASE + 0xE00UL) &= ~((0x1UL << (0U)) | (0x1UL << (1U)));

  ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DCTL &= ~(0x1UL << (1U));

  return HAL_OK;
}





 
HAL_StatusTypeDef USB_DevDisconnect(const USB_OTG_GlobalTypeDef *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;

   
  *(volatile uint32_t *)((uint32_t)USBx_BASE + 0xE00UL) &= ~((0x1UL << (0U)) | (0x1UL << (1U)));

  ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DCTL |= (0x1UL << (1U));

  return HAL_OK;
}





 
uint32_t USB_ReadInterrupts(USB_OTG_GlobalTypeDef const *USBx)
{
  uint32_t tmpreg;

  tmpreg = USBx->GINTSTS;
  tmpreg &= USBx->GINTMSK;

  return tmpreg;
}






 
uint32_t USB_ReadChInterrupts(const USB_OTG_GlobalTypeDef *USBx, uint8_t chnum)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t tmpreg;

  tmpreg = ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((chnum) * 0x20UL)))->HCINT;
  tmpreg &= ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((chnum) * 0x20UL)))->HCINTMSK;

  return tmpreg;
}





 
uint32_t USB_ReadDevAllOutEpInterrupt(const USB_OTG_GlobalTypeDef *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t tmpreg;

  tmpreg  = ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DAINT;
  tmpreg &= ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DAINTMSK;

  return ((tmpreg & 0xffff0000U) >> 16);
}





 
uint32_t USB_ReadDevAllInEpInterrupt(const USB_OTG_GlobalTypeDef *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t tmpreg;

  tmpreg  = ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DAINT;
  tmpreg &= ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DAINTMSK;

  return ((tmpreg & 0xFFFFU));
}







 
uint32_t USB_ReadDevOutEPInterrupt(const USB_OTG_GlobalTypeDef *USBx, uint8_t epnum)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t tmpreg;

  tmpreg  = ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + (((uint32_t)epnum) * 0x20UL)))->DOEPINT;
  tmpreg &= ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DOEPMSK;

  return tmpreg;
}







 
uint32_t USB_ReadDevInEPInterrupt(const USB_OTG_GlobalTypeDef *USBx, uint8_t epnum)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t tmpreg;
  uint32_t msk;
  uint32_t emp;

  msk = ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DIEPMSK;
  emp = ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DIEPEMPMSK;
  msk |= ((emp >> (epnum & 0xFU)) & 0x1U) << 7;
  tmpreg = ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + (((uint32_t)epnum) * 0x20UL)))->DIEPINT & msk;

  return tmpreg;
}






 
void  USB_ClearInterrupts(USB_OTG_GlobalTypeDef *USBx, uint32_t interrupt)
{
  USBx->GINTSTS &= interrupt;
}








 
uint32_t USB_GetMode(const USB_OTG_GlobalTypeDef *USBx)
{
  return ((USBx->GINTSTS) & 0x1U);
}





 
HAL_StatusTypeDef USB_ActivateSetup(const USB_OTG_GlobalTypeDef *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;

   
  ((USB_OTG_INEndpointTypeDef *)(USBx_BASE + 0x900UL + ((0U) * 0x20UL)))->DIEPCTL &= ~(0x7FFUL << (0U));

  ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DCTL |= (0x1UL << (8U));

  return HAL_OK;
}










 
HAL_StatusTypeDef USB_EP0_OutStart(const USB_OTG_GlobalTypeDef *USBx, uint8_t dma, const uint8_t *psetup)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t gSNPSiD = *(volatile const uint32_t *)(&USBx->CID + 0x1U);

  if (gSNPSiD > 0x4F54300AU)
  {
    if ((((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((0U) * 0x20UL)))->DOEPCTL & (0x1UL << (31U))) == (0x1UL << (31U)))
    {
      return HAL_OK;
    }
  }

  ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((0U) * 0x20UL)))->DOEPTSIZ = 0U;
  ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((0U) * 0x20UL)))->DOEPTSIZ |= ((0x3FFUL << (19U)) & (1U << 19));
  ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((0U) * 0x20UL)))->DOEPTSIZ |= (3U * 8U);
  ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((0U) * 0x20UL)))->DOEPTSIZ |=  (0x3UL << (29U));

  if (dma == 1U)
  {
    ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((0U) * 0x20UL)))->DOEPDMA = (uint32_t)psetup;
     
    ((USB_OTG_OUTEndpointTypeDef *)(USBx_BASE + 0xB00UL + ((0U) * 0x20UL)))->DOEPCTL |= (0x1UL << (31U)) | (0x1UL << (15U));
  }

  return HAL_OK;
}





 
static HAL_StatusTypeDef USB_CoreReset(USB_OTG_GlobalTypeDef *USBx)
{
  volatile uint32_t count = 0U;

   
  do
  {
    count++;

    if (count > 0xF000000U)
    {
      return HAL_TIMEOUT;
    }
  } while ((USBx->GRSTCTL & (0x1UL << (31U))) == 0U);

  count = 10U;

   
  while (count > 0U)
  {
    count--;
  }

   
  USBx->GRSTCTL |= (0x1UL << (0U));

  do
  {
    count++;

    if (count > 0xF000000U)
    {
      return HAL_TIMEOUT;
    }
  } while ((USBx->GRSTCTL & (0x1UL << (0U))) == (0x1UL << (0U)));

  return HAL_OK;
}








 
HAL_StatusTypeDef USB_HostInit(USB_OTG_GlobalTypeDef *USBx, USB_OTG_CfgTypeDef cfg)
{
  HAL_StatusTypeDef ret = HAL_OK;
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t i;

   
  *(volatile uint32_t *)((uint32_t)USBx_BASE + 0xE00UL) = 0U;

#line 1468 "../Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.c"
  


 
  USBx->GCCFG |= (0x1UL << (21U));
  USBx->GCCFG &= ~(0x1UL << (19U));
  USBx->GCCFG &= ~(0x1UL << (18U));
#line 1484 "../Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.c"

  if ((USBx->GUSBCFG & (0x1UL << (6U))) == 0U)
  {
    if (cfg.speed == 1U)
    {
       
      ((USB_OTG_HostTypeDef *)(USBx_BASE + 0x400UL))->HCFG |= (0x1UL << (2U));
    }
    else
    {
       
      ((USB_OTG_HostTypeDef *)(USBx_BASE + 0x400UL))->HCFG &= ~((0x1UL << (2U)));
    }
  }
  else
  {
     
    ((USB_OTG_HostTypeDef *)(USBx_BASE + 0x400UL))->HCFG &= ~((0x1UL << (2U)));
  }

   
  if (USB_FlushTxFifo(USBx, 0x10U) != HAL_OK)  
  {
    ret = HAL_ERROR;
  }

  if (USB_FlushRxFifo(USBx) != HAL_OK)
  {
    ret = HAL_ERROR;
  }

   
  for (i = 0U; i < cfg.Host_channels; i++)
  {
    ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((i) * 0x20UL)))->HCINT = 0xFFFFFFFFU;
    ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((i) * 0x20UL)))->HCINTMSK = 0U;
  }

   
  USBx->GINTMSK = 0U;

   
  USBx->GINTSTS = 0xFFFFFFFFU;

  if (USBx == ((USB_OTG_GlobalTypeDef *) 0x40040000UL))
  {
     
    USBx->GRXFSIZ  = 0x200U;
    USBx->DIEPTXF0_HNPTXFSIZ = (uint32_t)(((0x100U << 16) & (0xFFFFUL << (16U))) | 0x200U);
    USBx->HPTXFSIZ = (uint32_t)(((0xE0U << 16) & (0xFFFFUL << (16U))) | 0x300U);
  }
  else

  {
     
    USBx->GRXFSIZ  = 0x80U;
    USBx->DIEPTXF0_HNPTXFSIZ = (uint32_t)(((0x60U << 16) & (0xFFFFUL << (16U))) | 0x80U);
    USBx->HPTXFSIZ = (uint32_t)(((0x40U << 16)& (0xFFFFUL << (16U))) | 0xE0U);
  }

   
  if (cfg.dma_enable == 0U)
  {
    USBx->GINTMSK |= (0x1UL << (4U));
  }

   
  USBx->GINTMSK |= ((0x1UL << (24U))            | (0x1UL << (25U)) |                     (0x1UL << (3U))             | (0x1UL << (29U)) |                     (0x1UL << (21U))  | (0x1UL << (31U)));



  return ret;
}










 
HAL_StatusTypeDef USB_InitFSLSPClkSel(const USB_OTG_GlobalTypeDef *USBx, uint8_t freq)
{
  uint32_t USBx_BASE = (uint32_t)USBx;

  ((USB_OTG_HostTypeDef *)(USBx_BASE + 0x400UL))->HCFG &= ~((0x3UL << (0U)));
  ((USB_OTG_HostTypeDef *)(USBx_BASE + 0x400UL))->HCFG |= (uint32_t)freq & (0x3UL << (0U));

  if (freq == 1U)
  {
    ((USB_OTG_HostTypeDef *)(USBx_BASE + 0x400UL))->HFIR = 48000U;
  }
  else if (freq == 2U)
  {
    ((USB_OTG_HostTypeDef *)(USBx_BASE + 0x400UL))->HFIR = 6000U;
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}







 
HAL_StatusTypeDef USB_ResetPort(const USB_OTG_GlobalTypeDef *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;

  volatile uint32_t hprt0 = 0U;

  hprt0 = *(volatile uint32_t *)((uint32_t)USBx_BASE + 0x440UL);

  hprt0 &= ~((0x1UL << (2U)) | (0x1UL << (1U)) |
             (0x1UL << (3U)) | (0x1UL << (5U)));

  *(volatile uint32_t *)((uint32_t)USBx_BASE + 0x440UL) = ((0x1UL << (8U)) | hprt0);
  HAL_Delay(100U);                                  
  *(volatile uint32_t *)((uint32_t)USBx_BASE + 0x440UL) = ((~(0x1UL << (8U))) & hprt0);
  HAL_Delay(10U);

  return HAL_OK;
}








 
HAL_StatusTypeDef USB_DriveVbus(const USB_OTG_GlobalTypeDef *USBx, uint8_t state)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  volatile uint32_t hprt0 = 0U;

  hprt0 = *(volatile uint32_t *)((uint32_t)USBx_BASE + 0x440UL);

  hprt0 &= ~((0x1UL << (2U)) | (0x1UL << (1U)) |
             (0x1UL << (3U)) | (0x1UL << (5U)));

  if (((hprt0 & (0x1UL << (12U))) == 0U) && (state == 1U))
  {
    *(volatile uint32_t *)((uint32_t)USBx_BASE + 0x440UL) = ((0x1UL << (12U)) | hprt0);
  }
  if (((hprt0 & (0x1UL << (12U))) == (0x1UL << (12U))) && (state == 0U))
  {
    *(volatile uint32_t *)((uint32_t)USBx_BASE + 0x440UL) = ((~(0x1UL << (12U))) & hprt0);
  }
  return HAL_OK;
}









 
uint32_t USB_GetHostSpeed(USB_OTG_GlobalTypeDef const *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  volatile uint32_t hprt0 = 0U;

  hprt0 = *(volatile uint32_t *)((uint32_t)USBx_BASE + 0x440UL);
  return ((hprt0 & (0x3UL << (17U))) >> 17);
}





 
uint32_t USB_GetCurrentFrame(USB_OTG_GlobalTypeDef const *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;

  return (((USB_OTG_HostTypeDef *)(USBx_BASE + 0x400UL))->HFNUM & (0xFFFFUL << (0U)));
}
























 
HAL_StatusTypeDef USB_HC_Init(USB_OTG_GlobalTypeDef *USBx, uint8_t ch_num,
                              uint8_t epnum, uint8_t dev_address, uint8_t speed,
                              uint8_t ep_type, uint16_t mps)
{
  HAL_StatusTypeDef ret = HAL_OK;
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t HCcharEpDir;
  uint32_t HCcharLowSpeed;
  uint32_t HostCoreSpeed;

   
  ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + (((uint32_t)ch_num) * 0x20UL)))->HCINT = 0xFFFFFFFFU;

   
  switch (ep_type)
  {
    case 0U:
    case 2U:
      ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + (((uint32_t)ch_num) * 0x20UL)))->HCINTMSK = (0x1UL << (0U))  |
                                            (0x1UL << (3U)) |
                                            (0x1UL << (7U)) |
                                            (0x1UL << (10U)) |
                                            (0x1UL << (2U)) |
                                            (0x1UL << (4U));

      if ((epnum & 0x80U) == 0x80U)
      {
        ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + (((uint32_t)ch_num) * 0x20UL)))->HCINTMSK |= (0x1UL << (8U));
      }
      else
      {

        if (USBx == ((USB_OTG_GlobalTypeDef *) 0x40040000UL))
        {
          ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + (((uint32_t)ch_num) * 0x20UL)))->HCINTMSK |= (0x1UL << (6U)) |
                                                 (0x1UL << (5U));
        }

      }
      break;

    case 3U:
      ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + (((uint32_t)ch_num) * 0x20UL)))->HCINTMSK = (0x1UL << (0U))  |
                                            (0x1UL << (3U)) |
                                            (0x1UL << (7U)) |
                                            (0x1UL << (10U)) |
                                            (0x1UL << (4U))   |
                                            (0x1UL << (2U)) |
                                            (0x1UL << (9U));

      if ((epnum & 0x80U) == 0x80U)
      {
        ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + (((uint32_t)ch_num) * 0x20UL)))->HCINTMSK |= (0x1UL << (8U));
      }

      break;

    case 1U:
      ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + (((uint32_t)ch_num) * 0x20UL)))->HCINTMSK = (0x1UL << (0U))  |
                                            (0x1UL << (5U))   |
                                            (0x1UL << (2U)) |
                                            (0x1UL << (9U));

      if ((epnum & 0x80U) == 0x80U)
      {
        ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + (((uint32_t)ch_num) * 0x20UL)))->HCINTMSK |= ((0x1UL << (7U)) | (0x1UL << (8U)));
      }
      break;

    default:
      ret = HAL_ERROR;
      break;
  }

   
  ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + (((uint32_t)ch_num) * 0x20UL)))->HCSPLT = 0U;

   
  ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + (((uint32_t)ch_num) * 0x20UL)))->HCINTMSK |= (0x1UL << (1U));

   
  ((USB_OTG_HostTypeDef *)(USBx_BASE + 0x400UL))->HAINTMSK |= 1UL << (ch_num & 0xFU);

   
  USBx->GINTMSK |= (0x1UL << (25U));

   
  if ((epnum & 0x80U) == 0x80U)
  {
    HCcharEpDir = (0x1U << 15) & (0x1UL << (15U));
  }
  else
  {
    HCcharEpDir = 0U;
  }

  HostCoreSpeed = USB_GetHostSpeed(USBx);

   
  if ((speed == 2U) && (HostCoreSpeed != 2U))
  {
    HCcharLowSpeed = (0x1U << 17) & (0x1UL << (17U));
  }
  else
  {
    HCcharLowSpeed = 0U;
  }

  ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + (((uint32_t)ch_num) * 0x20UL)))->HCCHAR = (((uint32_t)dev_address << 22) & (0x7FUL << (22U))) |
                                      ((((uint32_t)epnum & 0x7FU) << 11) & (0xFUL << (11U))) |
                                      (((uint32_t)ep_type << 18) & (0x3UL << (18U))) |
                                      ((uint32_t)mps & (0x7FFUL << (0U))) |
                                      (0x1UL << (20U)) | HCcharEpDir | HCcharLowSpeed;

  if ((ep_type == 3U) || (ep_type == 1U))
  {
    ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + (((uint32_t)ch_num) * 0x20UL)))->HCCHAR |= (0x1UL << (29U));
  }

  return ret;
}










 
HAL_StatusTypeDef USB_HC_StartXfer(USB_OTG_GlobalTypeDef *USBx, USB_OTG_HCTypeDef *hc, uint8_t dma)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t ch_num = (uint32_t)hc->ch_num;
  volatile uint32_t tmpreg;
  uint8_t  is_oddframe;
  uint16_t len_words;
  uint16_t num_packets;
  uint16_t max_hc_pkt_count = 256U;


  if (USBx == ((USB_OTG_GlobalTypeDef *) 0x40040000UL))
  {
     
    if (dma == 1U)
    {
      if (((hc->ep_type == 0U) || (hc->ep_type == 2U)) && (hc->do_ssplit == 0U))
      {

        ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + (((uint32_t)ch_num) * 0x20UL)))->HCINTMSK &= ~((0x1UL << (6U)) |
                                                 (0x1UL << (5U)) |
                                                 (0x1UL << (4U)));
      }
    }
    else
    {
      if ((hc->speed == 0U) && (hc->do_ping == 1U))
      {
        (void)USB_DoPing(USBx, hc->ch_num);
        return HAL_OK;
      }
    }
  }


  if (hc->do_ssplit == 1U)
  {
     
    num_packets = 1U;

    if (hc->ep_is_in != 0U)
    {
      hc->XferSize = (uint32_t)num_packets * hc->max_packet;
    }
    else
    {
      if (hc->ep_type == 1U)
      {
        if (hc->xfer_len > 188U)
        {
           
          hc->XferSize = hc->max_packet;
          hc->xfer_len = hc->XferSize;

          if ((hc->iso_splt_xactPos == 1U) || (hc->iso_splt_xactPos == 2U))
          {
            hc->iso_splt_xactPos = 2U;
          }
          else
          {
            hc->iso_splt_xactPos = 1U;
          }
        }
        else
        {
          hc->XferSize = hc->xfer_len;

          if ((hc->iso_splt_xactPos != 1U) && (hc->iso_splt_xactPos != 2U))
          {
            hc->iso_splt_xactPos = 4U;
          }
          else
          {
            hc->iso_splt_xactPos = 3U;
          }
        }
      }
      else
      {
        if ((dma == 1U) && (hc->xfer_len > hc->max_packet))
        {
          hc->XferSize = (uint32_t)num_packets * hc->max_packet;
        }
        else
        {
          hc->XferSize = hc->xfer_len;
        }
      }
    }
  }
  else
  {
     
    if (hc->xfer_len > 0U)
    {
      num_packets = (uint16_t)((hc->xfer_len + hc->max_packet - 1U) / hc->max_packet);

      if (num_packets > max_hc_pkt_count)
      {
        num_packets = max_hc_pkt_count;
        hc->XferSize = (uint32_t)num_packets * hc->max_packet;
      }
    }
    else
    {
      num_packets = 1U;
    }

    


 
    if (hc->ep_is_in != 0U)
    {
      hc->XferSize = (uint32_t)num_packets * hc->max_packet;
    }
    else
    {
      hc->XferSize = hc->xfer_len;
    }
  }

   
  ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((ch_num) * 0x20UL)))->HCTSIZ = (hc->XferSize & (0x7FFFFUL << (0U))) |
                            (((uint32_t)num_packets << 19) & (0x3FFUL << (19U))) |
                            (((uint32_t)hc->data_pid << 29) & (0x3UL << (29U)));

  if (dma != 0U)
  {
     
    ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((ch_num) * 0x20UL)))->HCDMA = (uint32_t)hc->xfer_buff;
  }

  is_oddframe = (((uint32_t)((USB_OTG_HostTypeDef *)(USBx_BASE + 0x400UL))->HFNUM & 0x01U) != 0U) ? 0U : 1U;
  ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((ch_num) * 0x20UL)))->HCCHAR &= ~(0x1UL << (29U));
  ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((ch_num) * 0x20UL)))->HCCHAR |= (uint32_t)is_oddframe << 29;

  if (hc->do_ssplit == 1U)
  {
     
    ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + (((uint32_t)ch_num) * 0x20UL)))->HCSPLT = ((uint32_t)hc->hub_addr << (7U)) |
                                        (uint32_t)hc->hub_port_nbr | (0x1UL << (31U));

     
    ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + (((uint32_t)ch_num) * 0x20UL)))->HCINTMSK |= ((0x1UL << (5U)) |
                                            (0x1UL << (6U)));

    if ((hc->do_csplit == 1U) && (hc->ep_is_in == 0U))
    {
      ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + (((uint32_t)ch_num) * 0x20UL)))->HCSPLT |= (0x1UL << (16U));
      ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + (((uint32_t)ch_num) * 0x20UL)))->HCINTMSK |= (0x1UL << (6U));
    }

    if (((hc->ep_type == 1U) || (hc->ep_type == 3U)) &&
        (hc->do_csplit == 1U) && (hc->ep_is_in == 1U))
    {
      ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + (((uint32_t)ch_num) * 0x20UL)))->HCSPLT |= (0x1UL << (16U));
    }

     
    if ((hc->ep_type == 1U) && (hc->ep_is_in == 0U))
    {
       
      switch (hc->iso_splt_xactPos)
      {
        case 1U:
           
          ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + (((uint32_t)ch_num) * 0x20UL)))->HCSPLT |= (0x2UL << (14U));
          break;

        case 2U:
           
          ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + (((uint32_t)ch_num) * 0x20UL)))->HCSPLT |= (14U);
          break;

        case 3U:
           
          ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + (((uint32_t)ch_num) * 0x20UL)))->HCSPLT |= (0x1UL << (14U));
          break;

        case 4U:
           
          ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + (((uint32_t)ch_num) * 0x20UL)))->HCSPLT |= (0x3UL << (14U));
          break;

        default:
          break;
      }
    }
  }
  else
  {
     
    ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + (((uint32_t)ch_num) * 0x20UL)))->HCSPLT = 0U;
  }

   
  tmpreg = ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((ch_num) * 0x20UL)))->HCCHAR;
  tmpreg &= ~(0x1UL << (30U));

   
  if (hc->ep_is_in != 0U)
  {
    tmpreg |= (0x1UL << (15U));
  }
  else
  {
    tmpreg &= ~(0x1UL << (15U));
  }
  tmpreg |= (0x1UL << (31U));
  ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((ch_num) * 0x20UL)))->HCCHAR = tmpreg;

  if (dma != 0U)  
  {
    return HAL_OK;
  }

  if ((hc->ep_is_in == 0U) && (hc->xfer_len > 0U) && (hc->do_csplit == 0U))
  {
    switch (hc->ep_type)
    {
       
      case 0U:
      case 2U:

        len_words = (uint16_t)((hc->xfer_len + 3U) / 4U);

         
        if (len_words > (USBx->HNPTXSTS & 0xFFFFU))
        {
           
          USBx->GINTMSK |= (0x1UL << (5U));
        }
        break;

       
      case 3U:
      case 1U:
        len_words = (uint16_t)((hc->xfer_len + 3U) / 4U);
         
        if (len_words > (((USB_OTG_HostTypeDef *)(USBx_BASE + 0x400UL))->HPTXSTS & 0xFFFFU))  
        {
           
          USBx->GINTMSK |= (0x1UL << (26U));
        }
        break;

      default:
        break;
    }

     
    (void)USB_WritePacket(USBx, hc->xfer_buff, hc->ch_num, (uint16_t)hc->xfer_len, 0);
  }

  return HAL_OK;
}





 
uint32_t USB_HC_ReadInterrupt(const USB_OTG_GlobalTypeDef *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;

  return ((((USB_OTG_HostTypeDef *)(USBx_BASE + 0x400UL))->HAINT) & 0xFFFFU);
}







 
HAL_StatusTypeDef USB_HC_Halt(const USB_OTG_GlobalTypeDef *USBx, uint8_t hc_num)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t hcnum = (uint32_t)hc_num;
  volatile uint32_t count = 0U;
  uint32_t HcEpType = (((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((hcnum) * 0x20UL)))->HCCHAR & (0x3UL << (18U))) >> 18;
  uint32_t ChannelEna = (((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((hcnum) * 0x20UL)))->HCCHAR & (0x1UL << (31U))) >> 31;
  uint32_t SplitEna = (((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((hcnum) * 0x20UL)))->HCSPLT & (0x1UL << (31U))) >> 31;

  

 

  if ((((USBx->GAHBCFG & (0x1UL << (5U))) == (0x1UL << (5U))) && (SplitEna == 0U)) &&
      ((ChannelEna == 0U) || (((HcEpType == 1U) || (HcEpType == 3U)))))
  {
    return HAL_OK;
  }

   
  if ((HcEpType == 0U) || (HcEpType == 2U))
  {
    ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((hcnum) * 0x20UL)))->HCCHAR |= (0x1UL << (30U));

    if ((USBx->GAHBCFG & (0x1UL << (5U))) == 0U)
    {
      if ((USBx->HNPTXSTS & (0xFFU << 16)) == 0U)
      {
        ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((hcnum) * 0x20UL)))->HCCHAR &= ~(0x1UL << (31U));
        ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((hcnum) * 0x20UL)))->HCCHAR |= (0x1UL << (31U));
        do
        {
          count++;

          if (count > 1000U)
          {
            break;
          }
        } while ((((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((hcnum) * 0x20UL)))->HCCHAR & (0x1UL << (31U))) == (0x1UL << (31U)));
      }
      else
      {
        ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((hcnum) * 0x20UL)))->HCCHAR |= (0x1UL << (31U));
      }
    }
    else
    {
      ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((hcnum) * 0x20UL)))->HCCHAR |= (0x1UL << (31U));
    }
  }
  else
  {
    ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((hcnum) * 0x20UL)))->HCCHAR |= (0x1UL << (30U));

    if ((((USB_OTG_HostTypeDef *)(USBx_BASE + 0x400UL))->HPTXSTS & (0xFFU << 16)) == 0U)
    {
      ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((hcnum) * 0x20UL)))->HCCHAR &= ~(0x1UL << (31U));
      ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((hcnum) * 0x20UL)))->HCCHAR |= (0x1UL << (31U));
      do
      {
        count++;

        if (count > 1000U)
        {
          break;
        }
      } while ((((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((hcnum) * 0x20UL)))->HCCHAR & (0x1UL << (31U))) == (0x1UL << (31U)));
    }
    else
    {
      ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((hcnum) * 0x20UL)))->HCCHAR |= (0x1UL << (31U));
    }
  }

  return HAL_OK;
}







 
HAL_StatusTypeDef USB_DoPing(const USB_OTG_GlobalTypeDef *USBx, uint8_t ch_num)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t chnum = (uint32_t)ch_num;
  uint32_t num_packets = 1U;
  uint32_t tmpreg;

  ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((chnum) * 0x20UL)))->HCTSIZ = ((num_packets << 19) & (0x3FFUL << (19U))) |
                           (0x1UL << (31U));

   
  tmpreg = ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((chnum) * 0x20UL)))->HCCHAR;
  tmpreg &= ~(0x1UL << (30U));
  tmpreg |= (0x1UL << (31U));
  ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((chnum) * 0x20UL)))->HCCHAR = tmpreg;

  return HAL_OK;
}





 
HAL_StatusTypeDef USB_StopHost(USB_OTG_GlobalTypeDef *USBx)
{
  HAL_StatusTypeDef ret = HAL_OK;
  uint32_t USBx_BASE = (uint32_t)USBx;
  volatile uint32_t count = 0U;
  uint32_t value;
  uint32_t i;

  (void)USB_DisableGlobalInt(USBx);

   
  if (USB_FlushTxFifo(USBx, 0x10U) != HAL_OK)  
  {
    ret = HAL_ERROR;
  }

  if (USB_FlushRxFifo(USBx) != HAL_OK)
  {
    ret = HAL_ERROR;
  }

   
  for (i = 0U; i <= 15U; i++)
  {
    value = ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((i) * 0x20UL)))->HCCHAR;
    value |=  (0x1UL << (30U));
    value &= ~(0x1UL << (31U));
    value &= ~(0x1UL << (15U));
    ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((i) * 0x20UL)))->HCCHAR = value;
  }

   
  for (i = 0U; i <= 15U; i++)
  {
    value = ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((i) * 0x20UL)))->HCCHAR;
    value |= (0x1UL << (30U));
    value |= (0x1UL << (31U));
    value &= ~(0x1UL << (15U));
    ((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((i) * 0x20UL)))->HCCHAR = value;

    do
    {
      count++;

      if (count > 1000U)
      {
        break;
      }
    } while ((((USB_OTG_HostChannelTypeDef *)(USBx_BASE + 0x500UL + ((i) * 0x20UL)))->HCCHAR & (0x1UL << (31U))) == (0x1UL << (31U)));
  }

   
  ((USB_OTG_HostTypeDef *)(USBx_BASE + 0x400UL))->HAINT = 0xFFFFFFFFU;
  USBx->GINTSTS = 0xFFFFFFFFU;

  (void)USB_EnableGlobalInt(USBx);

  return ret;
}





 
HAL_StatusTypeDef USB_ActivateRemoteWakeup(const USB_OTG_GlobalTypeDef *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;

  if ((((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DSTS & (0x1UL << (0U))) == (0x1UL << (0U)))
  {
     
    ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DCTL |= (0x1UL << (0U));
  }

  return HAL_OK;
}





 
HAL_StatusTypeDef USB_DeActivateRemoteWakeup(const USB_OTG_GlobalTypeDef *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;

   
  ((USB_OTG_DeviceTypeDef *)(USBx_BASE + 0x800UL))->DCTL &= ~((0x1UL << (0U)));

  return HAL_OK;
}




 



 





 
