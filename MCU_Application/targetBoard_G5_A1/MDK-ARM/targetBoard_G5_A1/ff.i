#line 1 "../Middlewares/Third_Party/FatFs/src/ff.c"

















 


#line 1 "../Middlewares/Third_Party/FatFs/src/ff.h"

















 









#line 1 "../Middlewares/Third_Party/FatFs/src/integer.h"
 
 
 




#line 16 "../Middlewares/Third_Party/FatFs/src/integer.h"

 
typedef int				INT;
typedef unsigned int	UINT;

 
typedef unsigned char	BYTE;

 
typedef short			SHORT;
typedef unsigned short	WORD;
typedef unsigned short	WCHAR;

 
typedef long			LONG;
typedef unsigned long	DWORD;

 
typedef unsigned long long QWORD;



#line 29 "../Middlewares/Third_Party/FatFs/src/ff.h"
#line 1 "../FATFS/Target/ffconf.h"
 














 
 






 
#line 1 "../Core/Inc/main.h"
 
















 
 

 







 
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







 



 
 
 


 


 
 


 


 
 
 


 



  
  







#line 31 "../Core/Inc/main.h"

 
 

 

 
 

 

 
 

 

 
 

 

 
void Error_Handler(void);

 

 

 
#line 140 "../Core/Inc/main.h"

 

 





#line 26 "../FATFS/Target/ffconf.h"
#line 27 "../FATFS/Target/ffconf.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_core.h"
















 
 







 
#line 1 "../USB_HOST/Target/usbh_conf.h"
 
















 
 

 






 

#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"
 
 
 





 






 







 




  
 








#line 47 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"


  



    typedef unsigned int size_t;    









 
 

 



    typedef struct __va_list __va_list;






   




 




typedef struct __fpos_t_struct {
    unsigned __int64 __pos;
    



 
    struct {
        unsigned int __state1, __state2;
    } __mbstate;
} fpos_t;
   


 


   

 

typedef struct __FILE FILE;
   






 

#line 136 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"


extern FILE __stdin, __stdout, __stderr;
extern FILE *__aeabi_stdin, *__aeabi_stdout, *__aeabi_stderr;

#line 166 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"
    

    

    





     



   


 


   


 

   



 

   


 




   


 





    


 






extern __declspec(__nothrow) int remove(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int rename(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) FILE *tmpfile(void);
   




 
extern __declspec(__nothrow) char *tmpnam(char *  );
   











 

extern __declspec(__nothrow) int fclose(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) int fflush(FILE *  );
   







 
extern __declspec(__nothrow) FILE *fopen(const char * __restrict  ,
                           const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   








































 
extern __declspec(__nothrow) FILE *freopen(const char * __restrict  ,
                    const char * __restrict  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(2,3)));
   








 
extern __declspec(__nothrow) void setbuf(FILE * __restrict  ,
                    char * __restrict  ) __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) int setvbuf(FILE * __restrict  ,
                   char * __restrict  ,
                   int  , size_t  ) __attribute__((__nonnull__(1)));
   















 
#pragma __printf_args
extern __declspec(__nothrow) int fprintf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   


















 
#pragma __printf_args
extern __declspec(__nothrow) int _fprintf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   




 
#pragma __printf_args
extern __declspec(__nothrow) int _printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






 
#pragma __printf_args
extern __declspec(__nothrow) int _sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

#pragma __printf_args
extern __declspec(__nothrow) int __ARM_snprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(3)));


#pragma __printf_args
extern __declspec(__nothrow) int snprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   















 

#pragma __printf_args
extern __declspec(__nothrow) int _snprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int fscanf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






























 
#pragma __scanf_args
extern __declspec(__nothrow) int _fscanf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   






 
#pragma __scanf_args
extern __declspec(__nothrow) int _scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int sscanf(const char * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   








 
#pragma __scanf_args
extern __declspec(__nothrow) int _sscanf(const char * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

 
extern __declspec(__nothrow) int vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int _vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int _vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int _vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int __ARM_vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int _vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int vfprintf(FILE * __restrict  ,
                    const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int vsprintf(char * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int __ARM_vsnprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));

extern __declspec(__nothrow) int vsnprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   







 

extern __declspec(__nothrow) int _vsprintf(char * __restrict  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vfprintf(FILE * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vsnprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   



 

#pragma __printf_args
extern __declspec(__nothrow) int asprintf(char **  , const char * __restrict  , ...) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) int vasprintf(char **  , const char * __restrict  , __va_list  ) __attribute__((__nonnull__(2)));

#pragma __printf_args
extern __declspec(__nothrow) int __ARM_asprintf(char **  , const char * __restrict  , ...) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) int __ARM_vasprintf(char **  , const char * __restrict  , __va_list  ) __attribute__((__nonnull__(2)));
   








 

extern __declspec(__nothrow) int fgetc(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) char *fgets(char * __restrict  , int  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   










 
extern __declspec(__nothrow) int fputc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   







 
extern __declspec(__nothrow) int fputs(const char * __restrict  , FILE * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int getc(FILE *  ) __attribute__((__nonnull__(1)));
   







 




    extern __declspec(__nothrow) int (getchar)(void);

   





 
extern __declspec(__nothrow) char *gets(char *  ) __attribute__((__nonnull__(1)));
   









 
extern __declspec(__nothrow) int putc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   





 




    extern __declspec(__nothrow) int (putchar)(int  );

   



 
extern __declspec(__nothrow) int puts(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int ungetc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   






















 

extern __declspec(__nothrow) size_t fread(void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   











 

extern __declspec(__nothrow) size_t __fread_bytes_avail(void * __restrict  ,
                    size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   











 

extern __declspec(__nothrow) size_t fwrite(const void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   







 

extern __declspec(__nothrow) int fgetpos(FILE * __restrict  , fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) int fseek(FILE *  , long int  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) int fsetpos(FILE * __restrict  , const fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   










 
extern __declspec(__nothrow) long int ftell(FILE *  ) __attribute__((__nonnull__(1)));
   











 
extern __declspec(__nothrow) void rewind(FILE *  ) __attribute__((__nonnull__(1)));
   





 

extern __declspec(__nothrow) void clearerr(FILE *  ) __attribute__((__nonnull__(1)));
   




 

extern __declspec(__nothrow) int feof(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) int ferror(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) void perror(const char *  );
   









 

extern __declspec(__nothrow) int _fisatty(FILE *   ) __attribute__((__nonnull__(1)));
    
 

extern __declspec(__nothrow) void __use_no_semihosting_swi(void);
extern __declspec(__nothrow) void __use_no_semihosting(void);
    





 











#line 1021 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"



 

#line 31 "../USB_HOST/Target/usbh_conf.h"
#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"
 
 
 




 
 



 






   














  


 








#line 54 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"


  



    typedef unsigned int size_t;    
#line 70 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"






    



    typedef unsigned short wchar_t;  
#line 91 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"

typedef struct div_t { int quot, rem; } div_t;
    
typedef struct ldiv_t { long int quot, rem; } ldiv_t;
    

typedef struct lldiv_t { long long quot, rem; } lldiv_t;
    


#line 112 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"
   



 

   




 
#line 131 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"
   


 
extern __declspec(__nothrow) int __aeabi_MB_CUR_MAX(void);

   




 

   




 




extern __declspec(__nothrow) double atof(const char *  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int atoi(const char *  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) long int atol(const char *  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) long long atoll(const char *  ) __attribute__((__nonnull__(1)));
   



 


extern __declspec(__nothrow) double strtod(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
   

















 

extern __declspec(__nothrow) float strtof(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) long double strtold(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
   

 

extern __declspec(__nothrow) long int strtol(const char * __restrict  ,
                        char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   



























 
extern __declspec(__nothrow) unsigned long int strtoul(const char * __restrict  ,
                                       char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   


























 

 
extern __declspec(__nothrow) long long strtoll(const char * __restrict  ,
                                  char ** __restrict  , int  )
                          __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) unsigned long long strtoull(const char * __restrict  ,
                                            char ** __restrict  , int  )
                                   __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) int rand(void);
   







 
extern __declspec(__nothrow) void srand(unsigned int  );
   






 

struct _rand_state { int __x[57]; };
extern __declspec(__nothrow) int _rand_r(struct _rand_state *);
extern __declspec(__nothrow) void _srand_r(struct _rand_state *, unsigned int);
struct _ANSI_rand_state { int __x[1]; };
extern __declspec(__nothrow) int _ANSI_rand_r(struct _ANSI_rand_state *);
extern __declspec(__nothrow) void _ANSI_srand_r(struct _ANSI_rand_state *, unsigned int);
   


 

extern __declspec(__nothrow) void *calloc(size_t  , size_t  );
   



 
extern __declspec(__nothrow) void free(void *  );
   





 
extern __declspec(__nothrow) void *malloc(size_t  );
   



 
extern __declspec(__nothrow) void *realloc(void *  , size_t  );
   













 

extern __declspec(__nothrow) int posix_memalign(void **  , size_t  , size_t  );
   









 

typedef int (*__heapprt)(void *, char const *, ...);
extern __declspec(__nothrow) void __heapstats(int (*  )(void *  ,
                                           char const *  , ...),
                        void *  ) __attribute__((__nonnull__(1)));
   










 
extern __declspec(__nothrow) int __heapvalid(int (*  )(void *  ,
                                           char const *  , ...),
                       void *  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) __declspec(__noreturn) void abort(void);
   







 

extern __declspec(__nothrow) int atexit(void (*  )(void)) __attribute__((__nonnull__(1)));
   




 
#line 436 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"


extern __declspec(__nothrow) __declspec(__noreturn) void exit(int  );
   












 

extern __declspec(__nothrow) __declspec(__noreturn) void _Exit(int  );
   







      

extern __declspec(__nothrow) char *getenv(const char *  ) __attribute__((__nonnull__(1)));
   









 

extern __declspec(__nothrow) int  system(const char *  );
   









 

extern  void *bsearch(const void *  , const void *  ,
              size_t  , size_t  ,
              int (*  )(const void *, const void *)) __attribute__((__nonnull__(1,2,5)));
   












 
#line 524 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"


extern  void qsort(void *  , size_t  , size_t  ,
           int (*  )(const void *, const void *)) __attribute__((__nonnull__(1,4)));
   









 

#line 553 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"

extern __declspec(__nothrow) __attribute__((const)) int abs(int  );
   



 

extern __declspec(__nothrow) __attribute__((const)) div_t div(int  , int  );
   









 
extern __declspec(__nothrow) __attribute__((const)) long int labs(long int  );
   



 




extern __declspec(__nothrow) __attribute__((const)) ldiv_t ldiv(long int  , long int  );
   











 







extern __declspec(__nothrow) __attribute__((const)) long long llabs(long long  );
   



 




extern __declspec(__nothrow) __attribute__((const)) lldiv_t lldiv(long long  , long long  );
   











 
#line 634 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"




 
typedef struct __sdiv32by16 { int quot, rem; } __sdiv32by16;
typedef struct __udiv32by16 { unsigned int quot, rem; } __udiv32by16;
    
typedef struct __sdiv64by32 { int rem, quot; } __sdiv64by32;

__value_in_regs extern __declspec(__nothrow) __attribute__((const)) __sdiv32by16 __rt_sdiv32by16(
     int  ,
     short int  );
   

 
__value_in_regs extern __declspec(__nothrow) __attribute__((const)) __udiv32by16 __rt_udiv32by16(
     unsigned int  ,
     unsigned short  );
   

 
__value_in_regs extern __declspec(__nothrow) __attribute__((const)) __sdiv64by32 __rt_sdiv64by32(
     int  , unsigned int  ,
     int  );
   

 




 
extern __declspec(__nothrow) unsigned int __fp_status(unsigned int  , unsigned int  );
   







 























 
extern __declspec(__nothrow) int mblen(const char *  , size_t  );
   












 
extern __declspec(__nothrow) int mbtowc(wchar_t * __restrict  ,
                   const char * __restrict  , size_t  );
   















 
extern __declspec(__nothrow) int wctomb(char *  , wchar_t  );
   













 





 
extern __declspec(__nothrow) size_t mbstowcs(wchar_t * __restrict  ,
                      const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   














 
extern __declspec(__nothrow) size_t wcstombs(char * __restrict  ,
                      const wchar_t * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   














 

extern __declspec(__nothrow) void __use_realtime_heap(void);
extern __declspec(__nothrow) void __use_realtime_division(void);
extern __declspec(__nothrow) void __use_two_region_memory(void);
extern __declspec(__nothrow) void __use_no_heap(void);
extern __declspec(__nothrow) void __use_no_heap_region(void);

extern __declspec(__nothrow) char const *__C_library_version_string(void);
extern __declspec(__nothrow) int __C_library_version_number(void);











#line 892 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"





 
#line 32 "../USB_HOST/Target/usbh_conf.h"
#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
 
 
 
 




 








 












#line 38 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"


  



    typedef unsigned int size_t;    
#line 54 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"




extern __declspec(__nothrow) void *memcpy(void * __restrict  ,
                    const void * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) void *memmove(void *  ,
                    const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   







 
extern __declspec(__nothrow) char *strcpy(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncpy(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 

extern __declspec(__nothrow) char *strcat(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncat(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 






 

extern __declspec(__nothrow) int memcmp(const void *  , const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strcmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int strncmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcasecmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strncasecmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcoll(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   







 

extern __declspec(__nothrow) size_t strxfrm(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   













 


#line 193 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) void *memchr(const void *  , int  , size_t  ) __attribute__((__nonnull__(1)));

   





 

#line 209 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   




 

extern __declspec(__nothrow) size_t strcspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 

#line 232 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strpbrk(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   




 

#line 247 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strrchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   





 

extern __declspec(__nothrow) size_t strspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   



 

#line 270 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strstr(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   





 

extern __declspec(__nothrow) char *strtok(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) char *_strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

extern __declspec(__nothrow) char *strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

   

































 

extern __declspec(__nothrow) void *memset(void *  , int  , size_t  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) char *strerror(int  );
   





 
extern __declspec(__nothrow) size_t strlen(const char *  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) size_t strlcpy(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   
















 

extern __declspec(__nothrow) size_t strlcat(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






















 

extern __declspec(__nothrow) void _membitcpybl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpybb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
    














































 







#line 502 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"



 

#line 33 "../USB_HOST/Target/usbh_conf.h"
#line 34 "../USB_HOST/Target/usbh_conf.h"

#line 36 "../USB_HOST/Target/usbh_conf.h"
#line 37 "../USB_HOST/Target/usbh_conf.h"

 

 



 




 




 



 




 

 


 


 


 


 


 


 


 


 


 
 



#line 1 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
























































































































 
 



#line 1 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"

























 






 
#line 35 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"













 
#line 50 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"





 
#line 1 "../Core/Inc/FreeRTOSConfig.h"
 


























 
 














 

 
 
 

 
#line 53 "../Core/Inc/FreeRTOSConfig.h"
  extern uint32_t SystemCoreClock;








#line 81 "../Core/Inc/FreeRTOSConfig.h"
 

 

 

 



 





 
#line 104 "../Core/Inc/FreeRTOSConfig.h"


 
#line 120 "../Core/Inc/FreeRTOSConfig.h"




 


 

  






 





 



 


 



 
 

 


 



 



 
 
 

#line 57 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"

 
#line 1 "../Middlewares/Third_Party/FreeRTOS/Source/include/projdefs.h"

























 







 
typedef void (*TaskFunction_t)( void * );



 












 




 











 
#line 110 "../Middlewares/Third_Party/FreeRTOS/Source/include/projdefs.h"


 



 








#line 60 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"

 
#line 1 "../Middlewares/Third_Party/FreeRTOS/Source/include/portable.h"

























 



 













 
#line 1 "../Middlewares/Third_Party/FreeRTOS/Source/include/deprecated_definitions.h"

























 












 











































































































































































#line 218 "../Middlewares/Third_Party/FreeRTOS/Source/include/deprecated_definitions.h"

#line 226 "../Middlewares/Third_Party/FreeRTOS/Source/include/deprecated_definitions.h"







#line 240 "../Middlewares/Third_Party/FreeRTOS/Source/include/deprecated_definitions.h"








































#line 46 "../Middlewares/Third_Party/FreeRTOS/Source/include/portable.h"




 
#line 1 "../Middlewares/Third_Party/FreeRTOS/Source/portable/RVDS/ARM_CM4F/portmacro.h"

























 

















 

 
#line 54 "../Middlewares/Third_Party/FreeRTOS/Source/portable/RVDS/ARM_CM4F/portmacro.h"

typedef uint32_t StackType_t;
typedef long BaseType_t;
typedef unsigned long UBaseType_t;





	typedef uint32_t TickType_t;


	
 


 

 




 


 

 
#line 93 "../Middlewares/Third_Party/FreeRTOS/Source/portable/RVDS/ARM_CM4F/portmacro.h"
 





 

 
extern void vPortEnterCritical( void );
extern void vPortExitCritical( void );

#line 111 "../Middlewares/Third_Party/FreeRTOS/Source/portable/RVDS/ARM_CM4F/portmacro.h"

 

 

	extern void vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime );


 

 




#line 142 "../Middlewares/Third_Party/FreeRTOS/Source/portable/RVDS/ARM_CM4F/portmacro.h"
 



 


 


	void vPortValidateInterruptPriority( void );



 








 

static __forceinline void vPortSetBASEPRI( uint32_t ulBASEPRI )
{
	__asm
	{
		
 
		msr basepri, ulBASEPRI
	}
}
 

static __forceinline void vPortRaiseBASEPRI( void )
{
uint32_t ulNewBASEPRI = ( 5 << (8 - 4U) );

	__asm
	{
		
 
		msr basepri, ulNewBASEPRI
		dsb
		isb
	}
}
 

static __forceinline void vPortClearBASEPRIFromISR( void )
{
	__asm
	{
		

 
		msr basepri, #0
	}
}
 

static __forceinline uint32_t ulPortRaiseBASEPRI( void )
{
uint32_t ulReturn, ulNewBASEPRI = ( 5 << (8 - 4U) );

	__asm
	{
		
 
		mrs ulReturn, basepri
		msr basepri, ulNewBASEPRI
		dsb
		isb
	}

	return ulReturn;
}
 

static __forceinline BaseType_t xPortIsInsideInterrupt( void )
{
uint32_t ulCurrentInterrupt;
BaseType_t xReturn;

	 
	__asm
	{
		mrs ulCurrentInterrupt, ipsr
	}

	if( ulCurrentInterrupt == 0 )
	{
		xReturn = ( ( BaseType_t ) 0 );
	}
	else
	{
		xReturn = ( ( BaseType_t ) 1 );
	}

	return xReturn;
}








#line 53 "../Middlewares/Third_Party/FreeRTOS/Source/include/portable.h"














































#line 1 "../Middlewares/Third_Party/FreeRTOS/Source/include/mpu_wrappers.h"

























 





 
#line 179 "../Middlewares/Third_Party/FreeRTOS/Source/include/mpu_wrappers.h"











#line 100 "../Middlewares/Third_Party/FreeRTOS/Source/include/portable.h"






 
#line 117 "../Middlewares/Third_Party/FreeRTOS/Source/include/portable.h"
		StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters ) ;




 
typedef struct HeapRegion
{
	uint8_t *pucStartAddress;
	size_t xSizeInBytes;
} HeapRegion_t;

 
typedef struct xHeapStats
{
	size_t xAvailableHeapSpaceInBytes;		 
	size_t xSizeOfLargestFreeBlockInBytes; 	 
	size_t xSizeOfSmallestFreeBlockInBytes;  
	size_t xNumberOfFreeBlocks;				 
	size_t xMinimumEverFreeBytesRemaining;	 
	size_t xNumberOfSuccessfulAllocations;	 
	size_t xNumberOfSuccessfulFrees;		 
} HeapStats_t;











 
void vPortDefineHeapRegions( const HeapRegion_t * const pxHeapRegions ) ;




 
void vPortGetHeapStats( HeapStats_t *pxHeapStats );



 
void *pvPortMalloc( size_t xSize ) ;
void vPortFree( void *pv ) ;
void vPortInitialiseBlocks( void ) ;
size_t xPortGetFreeHeapSize( void ) ;
size_t xPortGetMinimumEverFreeHeapSize( void ) ;




 
BaseType_t xPortStartScheduler( void ) ;





 
void vPortEndScheduler( void ) ;







 











#line 63 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"

 




 







 































































































































































#line 243 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"





 
#line 255 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"









 


















































 

	
 




	
 




	
 




	
 




	 




	 




	
 




	



 




	


 




	


 




	


 




	


 















 





















































































































































































































































































































#line 732 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"




























































































































	
 



#line 867 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"

 


















#line 896 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"
	
 







 





	








 




	
 




	
 



#line 957 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"

	
 





	
 










 





 





 





 





 













































 












 
struct xSTATIC_LIST_ITEM
{



	TickType_t xDummy2;
	void *pvDummy3[ 4 ];



};
typedef struct xSTATIC_LIST_ITEM StaticListItem_t;

 
struct xSTATIC_MINI_LIST_ITEM
{



	TickType_t xDummy2;
	void *pvDummy3[ 2 ];
};
typedef struct xSTATIC_MINI_LIST_ITEM StaticMiniListItem_t;

 
typedef struct xSTATIC_LIST
{



	UBaseType_t uxDummy2;
	void *pvDummy3;
	StaticMiniListItem_t xDummy4;



} StaticList_t;













 
typedef struct xSTATIC_TCB
{
	void				*pxDummy1;



	StaticListItem_t	xDummy3[ 2 ];
	UBaseType_t			uxDummy5;
	void				*pxDummy6;
	uint8_t				ucDummy7[ ( 16 ) ];
#line 1129 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"
		UBaseType_t		uxDummy10[ 2 ];


		UBaseType_t		uxDummy12[ 2 ];


		void			*pxDummy14;
#line 1147 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"
		uint32_t 		ulDummy18;
		uint8_t 		ucDummy19;


		uint8_t			uxDummy20;


#line 1160 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"
} StaticTask_t;














 
typedef struct xSTATIC_QUEUE
{
	void *pvDummy1[ 3 ];

	union
	{
		void *pvDummy2;
		UBaseType_t uxDummy2;
	} u;

	StaticList_t xDummy3[ 2 ];
	UBaseType_t uxDummy4[ 3 ];
	uint8_t ucDummy5[ 2 ];


		uint8_t ucDummy6;







		UBaseType_t uxDummy8;
		uint8_t ucDummy9;


} StaticQueue_t;
typedef StaticQueue_t StaticSemaphore_t;














 
typedef struct xSTATIC_EVENT_GROUP
{
	TickType_t xDummy1;
	StaticList_t xDummy2;


		UBaseType_t uxDummy3;



			uint8_t ucDummy4;


} StaticEventGroup_t;














 
typedef struct xSTATIC_TIMER
{
	void				*pvDummy1;
	StaticListItem_t	xDummy2;
	TickType_t			xDummy3;
	void 				*pvDummy5;
	TaskFunction_t		pvDummy6;

		UBaseType_t		uxDummy7;

	uint8_t 			ucDummy8;

} StaticTimer_t;














 
typedef struct xSTATIC_STREAM_BUFFER
{
	size_t uxDummy1[ 4 ];
	void * pvDummy2[ 3 ];
	uint8_t ucDummy3;

		UBaseType_t uxDummy4;

} StaticStreamBuffer_t;

 
typedef StaticStreamBuffer_t StaticMessageBuffer_t;







#line 127 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
#line 1 "../Middlewares/Third_Party/FreeRTOS/Source/include/task.h"

























 









#line 1 "../Middlewares/Third_Party/FreeRTOS/Source/include/list.h"

























 



























 



































 












 

	 
#line 134 "../Middlewares/Third_Party/FreeRTOS/Source/include/list.h"




 
struct xLIST;
struct xLIST_ITEM
{
				 
	 TickType_t xItemValue;			 
	struct xLIST_ITEM *  pxNext;		 
	struct xLIST_ITEM *  pxPrevious;	 
	void * pvOwner;										 
	struct xLIST *  pvContainer;		 
				 
};
typedef struct xLIST_ITEM ListItem_t;					 

struct xMINI_LIST_ITEM
{
				 
	 TickType_t xItemValue;
	struct xLIST_ITEM *  pxNext;
	struct xLIST_ITEM *  pxPrevious;
};
typedef struct xMINI_LIST_ITEM MiniListItem_t;



 
typedef struct xLIST
{
					 
	volatile UBaseType_t uxNumberOfItems;
	ListItem_t *  pxIndex;			 
	MiniListItem_t xListEnd;							 
					 
} List_t;







 








 








 









 








 







 







 







 








 




 





















 
#line 289 "../Middlewares/Third_Party/FreeRTOS/Source/include/list.h"

















 










 







 






 











 
void vListInitialise( List_t * const pxList ) ;









 
void vListInitialiseItem( ListItem_t * const pxItem ) ;











 
void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem ) ;



















 
void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem ) ;













 
UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove ) ;







#line 37 "../Middlewares/Third_Party/FreeRTOS/Source/include/task.h"







 







 















 
struct tskTaskControlBlock;  
typedef struct tskTaskControlBlock* TaskHandle_t;




 
typedef BaseType_t (*TaskHookFunction_t)( void * );

 
typedef enum
{
	eRunning = 0,	 
	eReady,			 
	eBlocked,		 
	eSuspended,		 
	eDeleted,		 
	eInvalid		 
} eTaskState;

 
typedef enum
{
	eNoAction = 0,				 
	eSetBits,					 
	eIncrement,					 
	eSetValueWithOverwrite,		 
	eSetValueWithoutOverwrite	 
} eNotifyAction;



 
typedef struct xTIME_OUT
{
	BaseType_t xOverflowCount;
	TickType_t xTimeOnEntering;
} TimeOut_t;



 
typedef struct xMEMORY_REGION
{
	void *pvBaseAddress;
	uint32_t ulLengthInBytes;
	uint32_t ulParameters;
} MemoryRegion_t;



 
typedef struct xTASK_PARAMETERS
{
	TaskFunction_t pvTaskCode;
	const char * const pcName;	 
	uint16_t usStackDepth;
	void *pvParameters;
	UBaseType_t uxPriority;
	StackType_t *puxStackBuffer;
	MemoryRegion_t xRegions[ 1 ];



} TaskParameters_t;


 
typedef struct xTASK_STATUS
{
	TaskHandle_t xHandle;			 
	const char *pcTaskName;			   
	UBaseType_t xTaskNumber;		 
	eTaskState eCurrentState;		 
	UBaseType_t uxCurrentPriority;	 
	UBaseType_t uxBasePriority;		 
	uint32_t ulRunTimeCounter;		 
	StackType_t *pxStackBase;		 
	uint16_t usStackHighWaterMark;	 
} TaskStatus_t;

 
typedef enum
{
	eAbortSleep = 0,		 
	eStandardSleep,			 
	eNoTasksWaitingTimeout	 
} eSleepModeStatus;





 









 













 














 









 









 




 







 





























































































 

	BaseType_t xTaskCreate(	TaskFunction_t pxTaskCode,
							const char * const pcName,	 
							const uint16_t usStackDepth,
							void * const pvParameters,
							UBaseType_t uxPriority,
							TaskHandle_t * const pxCreatedTask ) ;












































































































 

	TaskHandle_t xTaskCreateStatic(	TaskFunction_t pxTaskCode,
									const char * const pcName,  
									const uint32_t ulStackDepth,
									void * const pvParameters,
									UBaseType_t uxPriority,
									StackType_t * const puxStackBuffer,
									StaticTask_t * const pxTaskBuffer ) ;









































































 























































































 

















































 
void vTaskAllocateMPURegions( TaskHandle_t xTask, const MemoryRegion_t * const pxRegions ) ;







































 
void vTaskDelete( TaskHandle_t xTaskToDelete ) ;



 














































 
void vTaskDelay( const TickType_t xTicksToDelay ) ;

























































 
void vTaskDelayUntil( TickType_t * const pxPreviousWakeTime, const TickType_t xTimeIncrement ) ;




























 
BaseType_t xTaskAbortDelay( TaskHandle_t xTask ) ;













































 
UBaseType_t uxTaskPriorityGet( const TaskHandle_t xTask ) ;






 
UBaseType_t uxTaskPriorityGetFromISR( const TaskHandle_t xTask ) ;
















 
eTaskState eTaskGetState( TaskHandle_t xTask ) ;






















































 
void vTaskGetInfo( TaskHandle_t xTask, TaskStatus_t *pxTaskStatus, BaseType_t xGetFreeStackSpace, eTaskState eState ) ;








































 
void vTaskPrioritySet( TaskHandle_t xTask, UBaseType_t uxNewPriority ) ;

















































 
void vTaskSuspend( TaskHandle_t xTaskToSuspend ) ;















































 
void vTaskResume( TaskHandle_t xTaskToResume ) ;



























 
BaseType_t xTaskResumeFromISR( TaskHandle_t xTaskToResume ) ;



 



























 
void vTaskStartScheduler( void ) ;






















































 
void vTaskEndScheduler( void ) ;

















































 
void vTaskSuspendAll( void ) ;




















































 
BaseType_t xTaskResumeAll( void ) ;



 









 
TickType_t xTaskGetTickCount( void ) ;














 
TickType_t xTaskGetTickCountFromISR( void ) ;












 
UBaseType_t uxTaskGetNumberOfTasks( void ) ;











 
char *pcTaskGetName( TaskHandle_t xTaskToQuery ) ;  














 
TaskHandle_t xTaskGetHandle( const char *pcNameToQuery ) ;  

























 
UBaseType_t uxTaskGetStackHighWaterMark( TaskHandle_t xTask ) ;

























 
uint16_t uxTaskGetStackHighWaterMark2( TaskHandle_t xTask ) ;






 


		






 
		void vTaskSetApplicationTaskTag( TaskHandle_t xTask, TaskHookFunction_t pxHookFunction ) ;

		






 
		TaskHookFunction_t xTaskGetApplicationTaskTag( TaskHandle_t xTask ) ;

		





 
		TaskHookFunction_t xTaskGetApplicationTaskTagFromISR( TaskHandle_t xTask ) ;



#line 1521 "../Middlewares/Third_Party/FreeRTOS/Source/include/task.h"











 
BaseType_t xTaskCallApplicationTaskHook( TaskHandle_t xTask, void *pvParameter ) ;







 
TaskHandle_t xTaskGetIdleTaskHandle( void ) ;

































































































 
UBaseType_t uxTaskGetSystemState( TaskStatus_t * const pxTaskStatusArray, const UBaseType_t uxArraySize, uint32_t * const pulTotalRunTime ) ;













































 
void vTaskList( char * pcWriteBuffer ) ;  




















































 
void vTaskGetRunTimeStats( char *pcWriteBuffer ) ;  




























 
uint32_t ulTaskGetIdleRunTimeCounter( void ) ;















































































 
BaseType_t xTaskGenericNotify( TaskHandle_t xTaskToNotify, uint32_t ulValue, eNotifyAction eAction, uint32_t *pulPreviousNotificationValue ) ;

























































































 
BaseType_t xTaskGenericNotifyFromISR( TaskHandle_t xTaskToNotify, uint32_t ulValue, eNotifyAction eAction, uint32_t *pulPreviousNotificationValue, BaseType_t *pxHigherPriorityTaskWoken ) ;











































































 
BaseType_t xTaskNotifyWait( uint32_t ulBitsToClearOnEntry, uint32_t ulBitsToClearOnExit, uint32_t *pulNotificationValue, TickType_t xTicksToWait ) ;












































 






















































 
void vTaskNotifyGiveFromISR( TaskHandle_t xTaskToNotify, BaseType_t *pxHigherPriorityTaskWoken ) ;



































































 
uint32_t ulTaskNotifyTake( BaseType_t xClearCountOnExit, TickType_t xTicksToWait ) ;














 
BaseType_t xTaskNotifyStateClear( TaskHandle_t xTask );
















 
uint32_t ulTaskNotifyValueClear( TaskHandle_t xTask, uint32_t ulBitsToClear ) ;












 
void vTaskSetTimeOutState( TimeOut_t * const pxTimeOut ) ;

















































































 
BaseType_t xTaskCheckForTimeOut( TimeOut_t * const pxTimeOut, TickType_t * const pxTicksToWait ) ;



 















 
BaseType_t xTaskIncrementTick( void ) ;































 
void vTaskPlaceOnEventList( List_t * const pxEventList, const TickType_t xTicksToWait ) ;
void vTaskPlaceOnUnorderedEventList( List_t * pxEventList, const TickType_t xItemValue, const TickType_t xTicksToWait ) ;











 
void vTaskPlaceOnEventListRestricted( List_t * const pxEventList, TickType_t xTicksToWait, const BaseType_t xWaitIndefinitely ) ;
























 
BaseType_t xTaskRemoveFromEventList( const List_t * const pxEventList ) ;
void vTaskRemoveFromUnorderedEventList( ListItem_t * pxEventListItem, const TickType_t xItemValue ) ;








 
 void vTaskSwitchContext( void ) ;




 
TickType_t uxTaskResetEventItemValue( void ) ;



 
TaskHandle_t xTaskGetCurrentTaskHandle( void ) ;




 
void vTaskMissedYield( void ) ;




 
BaseType_t xTaskGetSchedulerState( void ) ;




 
BaseType_t xTaskPriorityInherit( TaskHandle_t const pxMutexHolder ) ;




 
BaseType_t xTaskPriorityDisinherit( TaskHandle_t const pxMutexHolder ) ;








 
void vTaskPriorityDisinheritAfterTimeout( TaskHandle_t const pxMutexHolder, UBaseType_t uxHighestPriorityWaitingTask ) ;



 
UBaseType_t uxTaskGetTaskNumber( TaskHandle_t xTask ) ;




 
void vTaskSetTaskNumber( TaskHandle_t xTask, const UBaseType_t uxHandle ) ;








 
void vTaskStepTick( const TickType_t xTicksToJump ) ;











 
BaseType_t xTaskCatchUpTicks( TickType_t xTicksToCatchUp ) ;














 
eSleepModeStatus eTaskConfirmSleepModeStatus( void ) ;




 
TaskHandle_t pvTaskIncrementMutexHeldCount( void ) ;




 
void vTaskInternalSetTimeOutState( TimeOut_t * const pxTimeOut ) ;









#line 128 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"







 

 
#line 146 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 
#line 154 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 
#line 1 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.h"






















 




#line 41 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.h"

#line 43 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.h"
#line 44 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.h"










typedef struct {
  uint32_t                       api;   
  uint32_t                    kernel;   
} osVersion_t;


typedef enum {
  osKernelInactive        =  0,         
  osKernelReady           =  1,         
  osKernelRunning         =  2,         
  osKernelLocked          =  3,         
  osKernelSuspended       =  4,         
  osKernelError           = -1,         
  osKernelReserved        = 0x7FFFFFFFU 
} osKernelState_t;


typedef enum {
  osThreadInactive        =  0,         
  osThreadReady           =  1,         
  osThreadRunning         =  2,         
  osThreadBlocked         =  3,         
  osThreadTerminated      =  4,         
  osThreadError           = -1,         
  osThreadReserved        = 0x7FFFFFFF  
} osThreadState_t;


typedef enum {
  osPriorityNone          =  0,         
  osPriorityIdle          =  1,         
  osPriorityLow           =  8,         
  osPriorityLow1          =  8+1,       
  osPriorityLow2          =  8+2,       
  osPriorityLow3          =  8+3,       
  osPriorityLow4          =  8+4,       
  osPriorityLow5          =  8+5,       
  osPriorityLow6          =  8+6,       
  osPriorityLow7          =  8+7,       
  osPriorityBelowNormal   = 16,         
  osPriorityBelowNormal1  = 16+1,       
  osPriorityBelowNormal2  = 16+2,       
  osPriorityBelowNormal3  = 16+3,       
  osPriorityBelowNormal4  = 16+4,       
  osPriorityBelowNormal5  = 16+5,       
  osPriorityBelowNormal6  = 16+6,       
  osPriorityBelowNormal7  = 16+7,       
  osPriorityNormal        = 24,         
  osPriorityNormal1       = 24+1,       
  osPriorityNormal2       = 24+2,       
  osPriorityNormal3       = 24+3,       
  osPriorityNormal4       = 24+4,       
  osPriorityNormal5       = 24+5,       
  osPriorityNormal6       = 24+6,       
  osPriorityNormal7       = 24+7,       
  osPriorityAboveNormal   = 32,         
  osPriorityAboveNormal1  = 32+1,       
  osPriorityAboveNormal2  = 32+2,       
  osPriorityAboveNormal3  = 32+3,       
  osPriorityAboveNormal4  = 32+4,       
  osPriorityAboveNormal5  = 32+5,       
  osPriorityAboveNormal6  = 32+6,       
  osPriorityAboveNormal7  = 32+7,       
  osPriorityHigh          = 40,         
  osPriorityHigh1         = 40+1,       
  osPriorityHigh2         = 40+2,       
  osPriorityHigh3         = 40+3,       
  osPriorityHigh4         = 40+4,       
  osPriorityHigh5         = 40+5,       
  osPriorityHigh6         = 40+6,       
  osPriorityHigh7         = 40+7,       
  osPriorityRealtime      = 48,         
  osPriorityRealtime1     = 48+1,       
  osPriorityRealtime2     = 48+2,       
  osPriorityRealtime3     = 48+3,       
  osPriorityRealtime4     = 48+4,       
  osPriorityRealtime5     = 48+5,       
  osPriorityRealtime6     = 48+6,       
  osPriorityRealtime7     = 48+7,       
  osPriorityISR           = 56,         
  osPriorityError         = -1,         
  osPriorityReserved      = 0x7FFFFFFF  
} osPriority_t;


typedef void (*osThreadFunc_t) (void *argument);


typedef void (*osTimerFunc_t) (void *argument);


typedef enum {
  osTimerOnce               = 0,          
  osTimerPeriodic           = 1           
} osTimerType_t;










#line 165 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.h"











typedef enum {
  osOK                      =  0,         
  osError                   = -1,         
  osErrorTimeout            = -2,         
  osErrorResource           = -3,         
  osErrorParameter          = -4,         
  osErrorNoMemory           = -5,         
  osErrorISR                = -6,         
  osStatusReserved          = 0x7FFFFFFF  
} osStatus_t;



typedef void *osThreadId_t;


typedef void *osTimerId_t;


typedef void *osEventFlagsId_t;


typedef void *osMutexId_t;


typedef void *osSemaphoreId_t;


typedef void *osMemoryPoolId_t;


typedef void *osMessageQueueId_t;





typedef uint32_t TZ_ModuleId_t;




typedef struct {
  const char                   *name;   
  uint32_t                 attr_bits;   
  void                      *cb_mem;    
  uint32_t                   cb_size;   
  void                   *stack_mem;    
  uint32_t                stack_size;   
  osPriority_t              priority;   
  TZ_ModuleId_t            tz_module;   
  uint32_t                  reserved;   
} osThreadAttr_t;


typedef struct {
  const char                   *name;   
  uint32_t                 attr_bits;   
  void                      *cb_mem;    
  uint32_t                   cb_size;   
} osTimerAttr_t;


typedef struct {
  const char                   *name;   
  uint32_t                 attr_bits;   
  void                      *cb_mem;    
  uint32_t                   cb_size;   
} osEventFlagsAttr_t;


typedef struct {
  const char                   *name;   
  uint32_t                 attr_bits;   
  void                      *cb_mem;    
  uint32_t                   cb_size;   
} osMutexAttr_t;


typedef struct {
  const char                   *name;   
  uint32_t                 attr_bits;   
  void                      *cb_mem;    
  uint32_t                   cb_size;   
} osSemaphoreAttr_t;


typedef struct {
  const char                   *name;   
  uint32_t                 attr_bits;   
  void                      *cb_mem;    
  uint32_t                   cb_size;   
  void                      *mp_mem;    
  uint32_t                   mp_size;   
} osMemoryPoolAttr_t;


typedef struct {
  const char                   *name;   
  uint32_t                 attr_bits;   
  void                      *cb_mem;    
  uint32_t                   cb_size;   
  void                      *mq_mem;    
  uint32_t                   mq_size;   
} osMessageQueueAttr_t;






osStatus_t osKernelInitialize (void);






osStatus_t osKernelGetInfo (osVersion_t *version, char *id_buf, uint32_t id_size);



osKernelState_t osKernelGetState (void);



osStatus_t osKernelStart (void);



int32_t osKernelLock (void);



int32_t osKernelUnlock (void);




int32_t osKernelRestoreLock (int32_t lock);



uint32_t osKernelSuspend (void);



void osKernelResume (uint32_t sleep_ticks);



uint32_t osKernelGetTickCount (void);



uint32_t osKernelGetTickFreq (void);



uint32_t osKernelGetSysTimerCount (void);



uint32_t osKernelGetSysTimerFreq (void);









osThreadId_t osThreadNew (osThreadFunc_t func, void *argument, const osThreadAttr_t *attr);




const char *osThreadGetName (osThreadId_t thread_id);



osThreadId_t osThreadGetId (void);




osThreadState_t osThreadGetState (osThreadId_t thread_id);




uint32_t osThreadGetStackSize (osThreadId_t thread_id);




uint32_t osThreadGetStackSpace (osThreadId_t thread_id);





osStatus_t osThreadSetPriority (osThreadId_t thread_id, osPriority_t priority);




osPriority_t osThreadGetPriority (osThreadId_t thread_id);



osStatus_t osThreadYield (void);




osStatus_t osThreadSuspend (osThreadId_t thread_id);




osStatus_t osThreadResume (osThreadId_t thread_id);




osStatus_t osThreadDetach (osThreadId_t thread_id);




osStatus_t osThreadJoin (osThreadId_t thread_id);


__declspec(noreturn) void osThreadExit (void);




osStatus_t osThreadTerminate (osThreadId_t thread_id);



uint32_t osThreadGetCount (void);





uint32_t osThreadEnumerate (osThreadId_t *thread_array, uint32_t array_items);








uint32_t osThreadFlagsSet (osThreadId_t thread_id, uint32_t flags);




uint32_t osThreadFlagsClear (uint32_t flags);



uint32_t osThreadFlagsGet (void);






uint32_t osThreadFlagsWait (uint32_t flags, uint32_t options, uint32_t timeout);







osStatus_t osDelay (uint32_t ticks);




osStatus_t osDelayUntil (uint32_t ticks);










osTimerId_t osTimerNew (osTimerFunc_t func, osTimerType_t type, void *argument, const osTimerAttr_t *attr);




const char *osTimerGetName (osTimerId_t timer_id);





osStatus_t osTimerStart (osTimerId_t timer_id, uint32_t ticks);




osStatus_t osTimerStop (osTimerId_t timer_id);




uint32_t osTimerIsRunning (osTimerId_t timer_id);




osStatus_t osTimerDelete (osTimerId_t timer_id);







osEventFlagsId_t osEventFlagsNew (const osEventFlagsAttr_t *attr);




const char *osEventFlagsGetName (osEventFlagsId_t ef_id);





uint32_t osEventFlagsSet (osEventFlagsId_t ef_id, uint32_t flags);





uint32_t osEventFlagsClear (osEventFlagsId_t ef_id, uint32_t flags);




uint32_t osEventFlagsGet (osEventFlagsId_t ef_id);







uint32_t osEventFlagsWait (osEventFlagsId_t ef_id, uint32_t flags, uint32_t options, uint32_t timeout);




osStatus_t osEventFlagsDelete (osEventFlagsId_t ef_id);







osMutexId_t osMutexNew (const osMutexAttr_t *attr);




const char *osMutexGetName (osMutexId_t mutex_id);





osStatus_t osMutexAcquire (osMutexId_t mutex_id, uint32_t timeout);




osStatus_t osMutexRelease (osMutexId_t mutex_id);




osThreadId_t osMutexGetOwner (osMutexId_t mutex_id);




osStatus_t osMutexDelete (osMutexId_t mutex_id);









osSemaphoreId_t osSemaphoreNew (uint32_t max_count, uint32_t initial_count, const osSemaphoreAttr_t *attr);




const char *osSemaphoreGetName (osSemaphoreId_t semaphore_id);





osStatus_t osSemaphoreAcquire (osSemaphoreId_t semaphore_id, uint32_t timeout);




osStatus_t osSemaphoreRelease (osSemaphoreId_t semaphore_id);




uint32_t osSemaphoreGetCount (osSemaphoreId_t semaphore_id);




osStatus_t osSemaphoreDelete (osSemaphoreId_t semaphore_id);









osMemoryPoolId_t osMemoryPoolNew (uint32_t block_count, uint32_t block_size, const osMemoryPoolAttr_t *attr);




const char *osMemoryPoolGetName (osMemoryPoolId_t mp_id);





void *osMemoryPoolAlloc (osMemoryPoolId_t mp_id, uint32_t timeout);





osStatus_t osMemoryPoolFree (osMemoryPoolId_t mp_id, void *block);




uint32_t osMemoryPoolGetCapacity (osMemoryPoolId_t mp_id);




uint32_t osMemoryPoolGetBlockSize (osMemoryPoolId_t mp_id);




uint32_t osMemoryPoolGetCount (osMemoryPoolId_t mp_id);




uint32_t osMemoryPoolGetSpace (osMemoryPoolId_t mp_id);




osStatus_t osMemoryPoolDelete (osMemoryPoolId_t mp_id);









osMessageQueueId_t osMessageQueueNew (uint32_t msg_count, uint32_t msg_size, const osMessageQueueAttr_t *attr);




const char *osMessageQueueGetName (osMessageQueueId_t mq_id);







osStatus_t osMessageQueuePut (osMessageQueueId_t mq_id, const void *msg_ptr, uint8_t msg_prio, uint32_t timeout);







osStatus_t osMessageQueueGet (osMessageQueueId_t mq_id, void *msg_ptr, uint8_t *msg_prio, uint32_t timeout);




uint32_t osMessageQueueGetCapacity (osMessageQueueId_t mq_id);




uint32_t osMessageQueueGetMsgSize (osMessageQueueId_t mq_id);




uint32_t osMessageQueueGetCount (osMessageQueueId_t mq_id);




uint32_t osMessageQueueGetSpace (osMessageQueueId_t mq_id);




osStatus_t osMessageQueueReset (osMessageQueueId_t mq_id);




osStatus_t osMessageQueueDelete (osMessageQueueId_t mq_id);






#line 156 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 




 
 

 

#line 181 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"


typedef void (*os_pthread) (void const *argument);
 

typedef void (*os_ptimer) (void const *argument);
 

#line 197 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 


 

#line 221 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
typedef int32_t                  osStatus;
#line 232 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 
 

 






 






 






 






 

typedef void *osPoolId;
 

typedef void *osMessageQId;
 

typedef void *osMailQId;
 
 

#line 283 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
typedef struct os_thread_def {
  os_pthread                 pthread;   
  osThreadAttr_t                attr;   
} osThreadDef_t;

 






typedef struct os_timer_def {
  os_ptimer                   ptimer;   
  osTimerAttr_t                 attr;   
} osTimerDef_t;

 

#line 309 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 

#line 318 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 

#line 327 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
typedef struct os_pool_def {
  uint32_t                   pool_sz;   
  uint32_t                   item_sz;   
  osMemoryPoolAttr_t            attr;   
} osPoolDef_t;

 

#line 341 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
typedef struct os_messageQ_def {
  uint32_t                  queue_sz;   
  osMessageQueueAttr_t          attr;   
} osMessageQDef_t;

 

#line 355 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
typedef struct os_mailQ_def {
  uint32_t                  queue_sz;   
  uint32_t                   item_sz;   
  void                         *mail;   
  osMemoryPoolAttr_t         mp_attr;   
  osMessageQueueAttr_t       mq_attr;   
} osMailQDef_t;

 
 

typedef struct {
  osStatus                    status;   
  union {
    uint32_t                       v;   
    void                          *p;   
    int32_t                  signals;   
  } value;                              
  union {
    osMailQId                mail_id;   
    osMessageQId          message_id;   
  } def;                                
} osEvent;
 
 

 





 





 





 

 







 





 








 

 
 

 





#line 451 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 




 




osThreadId_t osThreadCreate (const osThreadDef_t *thread_def, void *argument);
 





 







 






 





 






 
 

 




int32_t osSignalSet (osThreadId_t thread_id, int32_t signals);
 




int32_t osSignalClear (osThreadId_t thread_id, int32_t signals);
 




__value_in_regs osEvent osSignalWait (int32_t signals, uint32_t millisec);
 
 

 






 
#line 536 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 
 

 



#line 552 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 




 





osTimerId_t osTimerCreate (const osTimerDef_t *timer_def, osTimerType_t type, void *argument);
 







 






 






 
 

 


#line 601 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 




 



osMutexId_t osMutexCreate (const osMutexAttr_t *mutex_def);
 









 






 






 
 

 

 


#line 652 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 




 




osSemaphoreId_t osSemaphoreCreate (const osSemaphoreAttr_t *semaphore_def, int32_t count);
 




int32_t osSemaphoreWait (osSemaphoreId_t semaphore_id, uint32_t millisec);
 






 






 

 
 


#line 731 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 
 

 

  




#line 753 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 




 




osMessageQId osMessageCreate (const osMessageQDef_t *queue_def, osThreadId_t thread_id);
 





osStatus osMessagePut (osMessageQId queue_id, uint32_t info, uint32_t millisec);
 




__value_in_regs osEvent osMessageGet (osMessageQId queue_id, uint32_t millisec);
 

 
 

 
#line 840 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 
 



 
#line 99 "../USB_HOST/Target/usbh_conf.h"






 




 

 

 


 


 


 


 

#line 136 "../USB_HOST/Target/usbh_conf.h"



#line 147 "../USB_HOST/Target/usbh_conf.h"

#line 157 "../USB_HOST/Target/usbh_conf.h"



 




 



 




 

 



 



 



 

#line 28 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_core.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_def.h"
















 

 







 
#line 29 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_def.h"



 



 




 









































#line 91 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_def.h"












#line 110 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_def.h"

 




 





 





 
 
#line 141 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_def.h"

 
#line 153 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_def.h"








 
 
#line 173 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_def.h"































 











typedef union
{
  uint16_t w;
  struct BW
  {
    uint8_t msb;
    uint8_t lsb;
  }
  bw;
}
uint16_t_uint8_t;


typedef union _USB_Setup
{
  uint32_t d8[2];

  struct _SetupPkt_Struc
  {
    uint8_t           bmRequestType;
    uint8_t           bRequest;
    uint16_t_uint8_t  wValue;
    uint16_t_uint8_t  wIndex;
    uint16_t_uint8_t  wLength;
  } b;
}
USB_Setup_TypeDef;

typedef  struct  _DescHeader
{
  uint8_t  bLength;
  uint8_t  bDescriptorType;
}
USBH_DescHeader_t;

typedef struct _DeviceDescriptor
{
  uint8_t   bLength;
  uint8_t   bDescriptorType;
  uint16_t  bcdUSB;         
  uint8_t   bDeviceClass;
  uint8_t   bDeviceSubClass;
  uint8_t   bDeviceProtocol;
  

 
  uint8_t   bMaxPacketSize;
  uint16_t   idVendor;       
  uint16_t   idProduct;      
  uint16_t   bcdDevice;      
  uint8_t   iManufacturer;   
  uint8_t   iProduct;        
  uint8_t   iSerialNumber;   
  uint8_t   bNumConfigurations;  
}
USBH_DevDescTypeDef;

typedef struct _EndpointDescriptor
{
  uint8_t   bLength;
  uint8_t   bDescriptorType;
  uint8_t   bEndpointAddress;    
  uint8_t   bmAttributes;        
  uint16_t  wMaxPacketSize;      
  uint8_t   bInterval;           
}
USBH_EpDescTypeDef;

typedef struct _InterfaceDescriptor
{
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint8_t bInterfaceNumber;
  uint8_t bAlternateSetting;     
  uint8_t bNumEndpoints;         
  uint8_t bInterfaceClass;       
  uint8_t bInterfaceSubClass;    
  uint8_t bInterfaceProtocol;    
  uint8_t iInterface;            
  USBH_EpDescTypeDef               Ep_Desc[5U];
}
USBH_InterfaceDescTypeDef;


typedef struct _ConfigurationDescriptor
{
  uint8_t   bLength;
  uint8_t   bDescriptorType;
  uint16_t  wTotalLength;          
  uint8_t   bNumInterfaces;        
  uint8_t   bConfigurationValue;   
  uint8_t   iConfiguration;        
  uint8_t   bmAttributes;          
  uint8_t   bMaxPower;             
  USBH_InterfaceDescTypeDef        Itf_Desc[10U];
}
USBH_CfgDescTypeDef;


 
typedef enum
{
  USBH_OK = 0,
  USBH_BUSY,
  USBH_FAIL,
  USBH_NOT_SUPPORTED,
  USBH_UNRECOVERED_ERROR,
  USBH_ERROR_SPEED_UNKNOWN,
} USBH_StatusTypeDef;




 

typedef enum
{
  USBH_SPEED_HIGH  = 0U,
  USBH_SPEED_FULL  = 1U,
  USBH_SPEED_LOW   = 2U,

} USBH_SpeedTypeDef;

 
typedef enum
{
  HOST_IDLE = 0U,
  HOST_DEV_WAIT_FOR_ATTACHMENT,
  HOST_DEV_ATTACHED,
  HOST_DEV_DISCONNECTED,
  HOST_DETECT_DEVICE_SPEED,
  HOST_ENUMERATION,
  HOST_CLASS_REQUEST,
  HOST_INPUT,
  HOST_SET_CONFIGURATION,
  HOST_SET_WAKEUP_FEATURE,
  HOST_CHECK_CLASS,
  HOST_CLASS,
  HOST_SUSPENDED,
  HOST_ABORT_STATE,
} HOST_StateTypeDef;

 
typedef enum
{
  ENUM_IDLE = 0U,
  ENUM_GET_FULL_DEV_DESC,
  ENUM_SET_ADDR,
  ENUM_GET_CFG_DESC,
  ENUM_GET_FULL_CFG_DESC,
  ENUM_GET_MFC_STRING_DESC,
  ENUM_GET_PRODUCT_STRING_DESC,
  ENUM_GET_SERIALNUM_STRING_DESC,
} ENUM_StateTypeDef;

 
typedef enum
{
  CTRL_IDLE = 0U,
  CTRL_SETUP,
  CTRL_SETUP_WAIT,
  CTRL_DATA_IN,
  CTRL_DATA_IN_WAIT,
  CTRL_DATA_OUT,
  CTRL_DATA_OUT_WAIT,
  CTRL_STATUS_IN,
  CTRL_STATUS_IN_WAIT,
  CTRL_STATUS_OUT,
  CTRL_STATUS_OUT_WAIT,
  CTRL_ERROR,
  CTRL_STALLED,
  CTRL_COMPLETE
} CTRL_StateTypeDef;


 
typedef enum
{
  CMD_IDLE = 0U,
  CMD_SEND,
  CMD_WAIT
} CMD_StateTypeDef;

typedef enum
{
  USBH_URB_IDLE = 0U,
  USBH_URB_DONE,
  USBH_URB_NOTREADY,
  USBH_URB_NYET,
  USBH_URB_ERROR,
  USBH_URB_STALL,
  USBH_URB_NAK_WAIT
} USBH_URBStateTypeDef;

typedef enum
{
  USBH_PORT_EVENT = 1U,
  USBH_URB_EVENT,
  USBH_CONTROL_EVENT,
  USBH_CLASS_EVENT,
  USBH_STATE_CHANGED_EVENT,
}
USBH_OSEventTypeDef;

 
typedef struct
{
  uint8_t               pipe_in;
  uint8_t               pipe_out;
  uint8_t               pipe_size;
  uint8_t               *buff;
  uint16_t              length;
  uint16_t              timer;
  USB_Setup_TypeDef     setup;
  CTRL_StateTypeDef     state;
  uint8_t               errorcount;

} USBH_CtrlTypeDef;

 
typedef struct
{
  uint8_t                           CfgDesc_Raw[256U];
  uint8_t                           Data[1024U];
  uint8_t                           address;
  uint8_t                           speed;
  uint8_t                           EnumCnt;
  uint8_t                           RstCnt;
  volatile uint8_t                      is_connected;
  volatile uint8_t                      is_disconnected;
  volatile uint8_t                      is_ReEnumerated;
  volatile uint8_t                      PortEnabled;
  uint8_t                           current_interface;
  USBH_DevDescTypeDef               DevDesc;
  USBH_CfgDescTypeDef               CfgDesc;
} USBH_DeviceTypeDef;

struct _USBH_HandleTypeDef;

 
typedef struct
{
  const char          *Name;
  uint8_t              ClassCode;
  USBH_StatusTypeDef(*Init)(struct _USBH_HandleTypeDef *phost);
  USBH_StatusTypeDef(*DeInit)(struct _USBH_HandleTypeDef *phost);
  USBH_StatusTypeDef(*Requests)(struct _USBH_HandleTypeDef *phost);
  USBH_StatusTypeDef(*BgndProcess)(struct _USBH_HandleTypeDef *phost);
  USBH_StatusTypeDef(*SOFProcess)(struct _USBH_HandleTypeDef *phost);
  void                *pData;
} USBH_ClassTypeDef;

 
typedef struct _USBH_HandleTypeDef
{
  volatile HOST_StateTypeDef     gState;        
  ENUM_StateTypeDef     EnumState;     
  CMD_StateTypeDef      RequestState;
  USBH_CtrlTypeDef      Control;
  USBH_DeviceTypeDef    device;
  USBH_ClassTypeDef    *pClass[5U];
  USBH_ClassTypeDef    *pActiveClass;
  uint32_t              ClassNumber;
  uint32_t              Pipes[16];
  volatile uint32_t         Timer;




  uint32_t              Timeout;
  uint8_t               id;
  void                 *pData;
  void (* pUser)(struct _USBH_HandleTypeDef *pHandle, uint8_t id);






  osMessageQueueId_t    os_event;
  osThreadId_t          thread;

  uint32_t              os_msg;


} USBH_HandleTypeDef;


#line 512 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_def.h"








#line 29 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_core.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_ioreq.h"
















 

 







 
#line 29 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_ioreq.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_core.h"
















 
 
#line 165 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_core.h"


 



 



 



#line 30 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_ioreq.h"



 



 




 




 












 




 


 




 


 



 


 



 
USBH_StatusTypeDef USBH_CtlSendSetup(USBH_HandleTypeDef *phost,
                                     uint8_t *buff,
                                     uint8_t pipe_num);

USBH_StatusTypeDef USBH_CtlSendData(USBH_HandleTypeDef *phost,
                                    uint8_t *buff,
                                    uint16_t length,
                                    uint8_t pipe_num,
                                    uint8_t do_ping);

USBH_StatusTypeDef USBH_CtlReceiveData(USBH_HandleTypeDef *phost,
                                       uint8_t *buff,
                                       uint16_t length,
                                       uint8_t pipe_num);

USBH_StatusTypeDef USBH_BulkReceiveData(USBH_HandleTypeDef *phost,
                                        uint8_t *buff,
                                        uint16_t length,
                                        uint8_t pipe_num);

USBH_StatusTypeDef USBH_BulkSendData(USBH_HandleTypeDef *phost,
                                     uint8_t *buff,
                                     uint16_t length,
                                     uint8_t pipe_num,
                                     uint8_t do_ping);

USBH_StatusTypeDef USBH_InterruptReceiveData(USBH_HandleTypeDef *phost,
                                             uint8_t             *buff,
                                             uint8_t             length,
                                             uint8_t             pipe_num);

USBH_StatusTypeDef USBH_InterruptSendData(USBH_HandleTypeDef *phost,
                                          uint8_t *buff,
                                          uint8_t length,
                                          uint8_t pipe_num);


USBH_StatusTypeDef USBH_IsocReceiveData(USBH_HandleTypeDef *phost,
                                        uint8_t *buff,
                                        uint32_t length,
                                        uint8_t pipe_num);


USBH_StatusTypeDef USBH_IsocSendData(USBH_HandleTypeDef *phost,
                                     uint8_t *buff,
                                     uint32_t length,
                                     uint8_t pipe_num);


 









 



 



 


#line 30 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_core.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_pipes.h"
















 

 







 
#line 29 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_pipes.h"



 



 




 



 


 



 


 




 


 



 


 



 

USBH_StatusTypeDef USBH_OpenPipe(USBH_HandleTypeDef *phost,
                                 uint8_t pipe_num,
                                 uint8_t epnum,
                                 uint8_t dev_address,
                                 uint8_t speed,
                                 uint8_t ep_type,
                                 uint16_t mps);

USBH_StatusTypeDef USBH_ClosePipe(USBH_HandleTypeDef *phost,
                                  uint8_t pipe_num);

uint8_t USBH_AllocPipe(USBH_HandleTypeDef *phost,
                       uint8_t ep_addr);

USBH_StatusTypeDef USBH_FreePipe(USBH_HandleTypeDef *phost,
                                 uint8_t idx);








 











 



 



 


#line 31 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_core.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_ctlreq.h"
















 

 







 
#line 29 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_ctlreq.h"



 



 




 




 
 











 




 


 




 


 



 
extern uint8_t USBH_CfgDesc[512];


 



 
USBH_StatusTypeDef USBH_CtlReq(USBH_HandleTypeDef *phost, uint8_t *buff,
                               uint16_t length);

USBH_StatusTypeDef USBH_GetDescriptor(USBH_HandleTypeDef *phost,
                                      uint8_t  req_type, uint16_t value_idx,
                                      uint8_t *buff, uint16_t length);

USBH_StatusTypeDef USBH_Get_DevDesc(USBH_HandleTypeDef *phost, uint16_t length);

USBH_StatusTypeDef USBH_Get_StringDesc(USBH_HandleTypeDef *phost,
                                       uint8_t string_index, uint8_t *buff,
                                       uint16_t length);

USBH_StatusTypeDef USBH_SetCfg(USBH_HandleTypeDef *phost, uint16_t cfg_idx);

USBH_StatusTypeDef USBH_Get_CfgDesc(USBH_HandleTypeDef *phost, uint16_t length);

USBH_StatusTypeDef USBH_SetAddress(USBH_HandleTypeDef *phost,
                                   uint8_t DeviceAddress);

USBH_StatusTypeDef USBH_SetInterface(USBH_HandleTypeDef *phost, uint8_t ep_num,
                                     uint8_t altSetting);

USBH_StatusTypeDef USBH_SetFeature(USBH_HandleTypeDef *phost, uint8_t wValue);

USBH_StatusTypeDef USBH_ClrFeature(USBH_HandleTypeDef *phost, uint8_t ep_num);

USBH_DescHeader_t *USBH_GetNextDesc(uint8_t *pbuf, uint16_t *ptr);


 









 



 



 


#line 32 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_core.h"



 



 




 




 



 
#line 60 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_core.h"




 





 



 



 



 



 
USBH_StatusTypeDef USBH_Init(USBH_HandleTypeDef *phost,
                             void (*pUsrFunc)(USBH_HandleTypeDef *phost, uint8_t id), uint8_t id);

USBH_StatusTypeDef USBH_DeInit(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_Start(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_Stop(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_Process(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_ReEnumerate(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_RegisterClass(USBH_HandleTypeDef *phost, USBH_ClassTypeDef *pclass);
USBH_StatusTypeDef USBH_SelectInterface(USBH_HandleTypeDef *phost, uint8_t interface);

uint8_t            USBH_FindInterfaceIndex(USBH_HandleTypeDef *phost, uint8_t interface_number, uint8_t alt_settings);
uint8_t            USBH_FindInterface(USBH_HandleTypeDef *phost, uint8_t Class, uint8_t SubClass, uint8_t Protocol);
uint8_t            USBH_GetActiveClass(USBH_HandleTypeDef *phost);
uint8_t            USBH_IsPortEnabled(USBH_HandleTypeDef *phost);

 
USBH_StatusTypeDef USBH_LL_Init(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_LL_DeInit(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_LL_Start(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_LL_Stop(USBH_HandleTypeDef *phost);

USBH_StatusTypeDef USBH_LL_Connect(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_LL_Disconnect(USBH_HandleTypeDef *phost);
USBH_SpeedTypeDef  USBH_LL_GetSpeed(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_LL_ResetPort(USBH_HandleTypeDef *phost);
uint32_t           USBH_LL_GetLastXferSize(USBH_HandleTypeDef *phost, uint8_t pipe);

USBH_StatusTypeDef USBH_LL_DriverVBUS(USBH_HandleTypeDef *phost, uint8_t state);

USBH_StatusTypeDef USBH_LL_OpenPipe(USBH_HandleTypeDef *phost,
                                    uint8_t pipe,
                                    uint8_t epnum,
                                    uint8_t dev_address,
                                    uint8_t speed,
                                    uint8_t ep_type,
                                    uint16_t mps);

USBH_StatusTypeDef USBH_LL_ActivatePipe(USBH_HandleTypeDef *phost, uint8_t pipe);
USBH_StatusTypeDef USBH_LL_ClosePipe(USBH_HandleTypeDef *phost, uint8_t pipe);

USBH_StatusTypeDef USBH_LL_SubmitURB(USBH_HandleTypeDef *phost,
                                     uint8_t pipe,
                                     uint8_t direction,
                                     uint8_t ep_type,
                                     uint8_t token,
                                     uint8_t *pbuff,
                                     uint16_t length,
                                     uint8_t do_ping);

USBH_URBStateTypeDef USBH_LL_GetURBState(USBH_HandleTypeDef *phost, uint8_t pipe);


USBH_StatusTypeDef USBH_LL_NotifyURBChange(USBH_HandleTypeDef *phost);
void USBH_OS_PutMessage(USBH_HandleTypeDef *phost, USBH_OSEventTypeDef message, uint32_t timeout, uint32_t priority);


USBH_StatusTypeDef USBH_LL_SetToggle(USBH_HandleTypeDef *phost, uint8_t pipe, uint8_t toggle);

uint8_t USBH_LL_GetToggle(USBH_HandleTypeDef *phost, uint8_t pipe);

void USBH_LL_PortDisabled(USBH_HandleTypeDef *phost);
void USBH_LL_PortEnabled(USBH_HandleTypeDef *phost);

 
void USBH_LL_SetTimer(USBH_HandleTypeDef *phost, uint32_t time);
void USBH_LL_IncTimer(USBH_HandleTypeDef *phost);

void USBH_Delay(uint32_t Delay);


 








 



 



 



#line 28 "../FATFS/Target/ffconf.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc/usbh_msc.h"
















 

 







 
#line 29 "../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc/usbh_msc.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc/usbh_msc_bot.h"
















 

 







 
#line 29 "../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc/usbh_msc_bot.h"



 



 



 




 




 

typedef enum
{
  BOT_OK          = 0,
  BOT_FAIL        = 1,
  BOT_PHASE_ERROR = 2,
  BOT_BUSY        = 3
}
BOT_StatusTypeDef;

typedef enum
{
  BOT_CMD_IDLE  = 0,
  BOT_CMD_SEND,
  BOT_CMD_WAIT,
}
BOT_CMDStateTypeDef;

 
typedef enum
{

  BOT_CSW_CMD_PASSED   =        0x00,
  BOT_CSW_CMD_FAILED   =        0x01,
  BOT_CSW_PHASE_ERROR  =        0x02,
}
BOT_CSWStatusTypeDef;

typedef enum
{
  BOT_SEND_CBW  = 1,
  BOT_SEND_CBW_WAIT,
  BOT_DATA_IN,
  BOT_DATA_IN_WAIT,
  BOT_DATA_OUT,
  BOT_DATA_OUT_WAIT,
  BOT_RECEIVE_CSW,
  BOT_RECEIVE_CSW_WAIT,
  BOT_ERROR_IN,
  BOT_ERROR_OUT,
  BOT_UNRECOVERED_ERROR
}
BOT_StateTypeDef;

typedef union
{
  struct __CBW
  {
    uint32_t Signature;
    uint32_t Tag;
    uint32_t DataTransferLength;
    uint8_t  Flags;
    uint8_t  LUN;
    uint8_t  CBLength;
    uint8_t  CB[16];
  } field;
  uint8_t data[31];
}
BOT_CBWTypeDef;

typedef union
{
  struct __CSW
  {
    uint32_t Signature;
    uint32_t Tag;
    uint32_t DataResidue;
    uint8_t  Status;
  } field;
  uint8_t data[13];
}
BOT_CSWTypeDef;

typedef struct
{
  uint32_t                   data[16];
  BOT_StateTypeDef           state;
  BOT_StateTypeDef           prev_state;
  BOT_CMDStateTypeDef        cmd_state;
  BOT_CBWTypeDef             cbw;
  uint8_t                    Reserved1;
  BOT_CSWTypeDef             csw;
  uint8_t                    Reserved2[3];
  uint8_t                    *pbuf;
}
BOT_HandleTypeDef;



 





 




























 



 


 



 



 



 
USBH_StatusTypeDef USBH_MSC_BOT_REQ_Reset(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_MSC_BOT_REQ_GetMaxLUN(USBH_HandleTypeDef *phost, uint8_t *Maxlun);

USBH_StatusTypeDef USBH_MSC_BOT_Init(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_MSC_BOT_Process(USBH_HandleTypeDef *phost, uint8_t lun);
USBH_StatusTypeDef USBH_MSC_BOT_Error(USBH_HandleTypeDef *phost, uint8_t lun);





 










 



 



 



 

#line 30 "../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc/usbh_msc.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc/usbh_msc_scsi.h"
















 

 







 
#line 29 "../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc/usbh_msc_scsi.h"




 



 



 




 


 
typedef struct
{
  uint32_t block_nbr;
  uint16_t block_size;
} SCSI_CapacityTypeDef;


 
typedef struct
{
  uint8_t key;
  uint8_t asc;
  uint8_t ascq;
} SCSI_SenseTypeDef;

 
typedef struct
{
  uint8_t PeripheralQualifier;
  uint8_t DeviceType;
  uint8_t RemovableMedia;
  uint8_t vendor_id[9];
  uint8_t product_id[17];
  uint8_t revision_id[5];
} SCSI_StdInquiryDataTypeDef;



 
#line 85 "../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc/usbh_msc_scsi.h"











 
#line 111 "../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc/usbh_msc_scsi.h"


 




 
#line 127 "../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc/usbh_msc_scsi.h"


 




 






 



 


 



 



 



 
USBH_StatusTypeDef USBH_MSC_SCSI_TestUnitReady(USBH_HandleTypeDef *phost,
                                               uint8_t lun);

USBH_StatusTypeDef USBH_MSC_SCSI_ReadCapacity(USBH_HandleTypeDef *phost,
                                              uint8_t lun,
                                              SCSI_CapacityTypeDef *capacity);

USBH_StatusTypeDef USBH_MSC_SCSI_Inquiry(USBH_HandleTypeDef *phost,
                                         uint8_t lun,
                                         SCSI_StdInquiryDataTypeDef *inquiry);

USBH_StatusTypeDef USBH_MSC_SCSI_RequestSense(USBH_HandleTypeDef *phost,
                                              uint8_t lun,
                                              SCSI_SenseTypeDef *sense_data);

USBH_StatusTypeDef USBH_MSC_SCSI_Write(USBH_HandleTypeDef *phost,
                                       uint8_t lun,
                                       uint32_t address,
                                       uint8_t *pbuf,
                                       uint32_t length);

USBH_StatusTypeDef USBH_MSC_SCSI_Read(USBH_HandleTypeDef *phost,
                                      uint8_t lun,
                                      uint32_t address,
                                      uint8_t *pbuf,
                                      uint32_t length);




 










 



 



 



 

#line 31 "../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc/usbh_msc.h"



 



 



 




 




 

typedef enum
{
  MSC_INIT = 0,
  MSC_IDLE,
  MSC_TEST_UNIT_READY,
  MSC_READ_CAPACITY10,
  MSC_READ_INQUIRY,
  MSC_REQUEST_SENSE,
  MSC_READ,
  MSC_WRITE,
  MSC_UNRECOVERED_ERROR,
  MSC_PERIODIC_CHECK,
  MSC_USER_NOTIFY
}
MSC_StateTypeDef;

typedef enum
{
  MSC_OK,
  MSC_NOT_READY,
  MSC_ERROR,

}
MSC_ErrorTypeDef;

typedef enum
{
  MSC_REQ_IDLE = 0,
  MSC_REQ_RESET,
  MSC_REQ_GET_MAX_LUN,
  MSC_REQ_ERROR,
}
MSC_ReqStateTypeDef;






 
typedef struct
{
  MSC_StateTypeDef            state;
  MSC_ErrorTypeDef            error;
  USBH_StatusTypeDef          prev_ready_state;
  SCSI_CapacityTypeDef        capacity;
  SCSI_SenseTypeDef           sense;
  SCSI_StdInquiryDataTypeDef  inquiry;
  uint8_t                     state_changed;

}
MSC_LUNTypeDef;

 
typedef struct _MSC_Process
{
  uint8_t              max_lun;
  uint8_t              Reserved[3];
  uint8_t              InPipe;
  uint8_t              OutPipe;
  uint8_t              OutEp;
  uint8_t              InEp;
  uint16_t             OutEpSize;
  uint16_t             InEpSize;
  MSC_StateTypeDef     state;
  MSC_ErrorTypeDef     error;
  MSC_ReqStateTypeDef  req_state;
  MSC_ReqStateTypeDef  prev_req_state;
  BOT_HandleTypeDef    hbot;
  MSC_LUNTypeDef       unit[2U];
  uint16_t             current_lun;
  uint16_t             lun;
  uint16_t             rw_lun;
  uint32_t             timer;
}
MSC_HandleTypeDef;




 





 





 


 




 



 


 



 
extern USBH_ClassTypeDef  USBH_msc;




 



 
uint8_t USBH_MSC_IsReady(USBH_HandleTypeDef *phost);
uint8_t USBH_MSC_GetMaxLUN(USBH_HandleTypeDef *phost);
uint8_t USBH_MSC_UnitIsReady(USBH_HandleTypeDef *phost, uint8_t lun);

USBH_StatusTypeDef USBH_MSC_GetLUNInfo(USBH_HandleTypeDef *phost, uint8_t lun,
                                       MSC_LUNTypeDef *info);

USBH_StatusTypeDef USBH_MSC_Read(USBH_HandleTypeDef *phost, uint8_t lun,
                                 uint32_t address, uint8_t *pbuf, uint32_t length);

USBH_StatusTypeDef USBH_MSC_Write(USBH_HandleTypeDef *phost, uint8_t lun,
                                  uint32_t address, uint8_t *pbuf, uint32_t length);


 










 



 



 



 



#line 29 "../FATFS/Target/ffconf.h"
#line 30 "../FATFS/Target/ffconf.h"
 




 





 








 







 



 


 


 


 



 



 


 



 



























 
















 




 










 







 



 


 

 






 
 







 







 




 










 



 





 




 












 










 





















 

 





#line 30 "../Middlewares/Third_Party/FatFs/src/ff.h"







 

#line 46 "../Middlewares/Third_Party/FatFs/src/ff.h"



 

#line 62 "../Middlewares/Third_Party/FatFs/src/ff.h"
typedef char TCHAR;







 





typedef QWORD FSIZE_t;






 

typedef struct {
	BYTE	fs_type;		 
	BYTE	drv;			 
	BYTE	n_fats;			 
	BYTE	wflag;			 
	BYTE	fsi_flag;		 
	WORD	id;				 
	WORD	n_rootdir;		 
	WORD	csize;			 




	WCHAR*	lfnbuf;			 


	BYTE*	dirbuf;			 


	osMutexId_t	sobj;			 


	DWORD	last_clst;		 
	DWORD	free_clst;		 
#line 118 "../Middlewares/Third_Party/FatFs/src/ff.h"
	DWORD	n_fatent;		 
	DWORD	fsize;			 
	DWORD	volbase;		 
	DWORD	fatbase;		 
	DWORD	dirbase;		 
	DWORD	database;		 
	DWORD	winsect;		 
	BYTE	win[512];	 
} FATFS;



 

typedef struct {
	FATFS*	fs;			 
	WORD	id;			 
	BYTE	attr;		 
	BYTE	stat;		 
	DWORD	sclust;		 
	FSIZE_t	objsize;	 

	DWORD	n_cont;		 
	DWORD	n_frag;		 
	DWORD	c_scl;		 
	DWORD	c_size;		 
	DWORD	c_ofs;		 


	UINT	lockid;		 

} _FDID;



 

typedef struct {
	_FDID	obj;			 
	BYTE	flag;			 
	BYTE	err;			 
	FSIZE_t	fptr;			 
	DWORD	clust;			 
	DWORD	sect;			 

	DWORD	dir_sect;		 
	BYTE*	dir_ptr;		 


	DWORD*	cltbl;			 


	BYTE	buf[512];	 

} FIL;



 

typedef struct {
	_FDID	obj;			 
	DWORD	dptr;			 
	DWORD	clust;			 
	DWORD	sect;			 
	BYTE*	dir;			 
	BYTE	fn[12];			 

	DWORD	blk_ofs;		 


	const TCHAR* pat;		 

} DIR;



 

typedef struct {
	FSIZE_t	fsize;			 
	WORD	fdate;			 
	WORD	ftime;			 
	BYTE	fattrib;		 

	TCHAR	altname[13];			 
	TCHAR	fname[255 + 1];	 



} FILINFO;



 

typedef enum {
	FR_OK = 0,				 
	FR_DISK_ERR,			 
	FR_INT_ERR,				 
	FR_NOT_READY,			 
	FR_NO_FILE,				 
	FR_NO_PATH,				 
	FR_INVALID_NAME,		 
	FR_DENIED,				 
	FR_EXIST,				 
	FR_INVALID_OBJECT,		 
	FR_WRITE_PROTECTED,		 
	FR_INVALID_DRIVE,		 
	FR_NOT_ENABLED,			 
	FR_NO_FILESYSTEM,		 
	FR_MKFS_ABORTED,		 
	FR_TIMEOUT,				 
	FR_LOCKED,				 
	FR_NOT_ENOUGH_CORE,		 
	FR_TOO_MANY_OPEN_FILES,	 
	FR_INVALID_PARAMETER	 
} FRESULT;



 
 

FRESULT f_open (FIL* fp, const TCHAR* path, BYTE mode);				 
FRESULT f_close (FIL* fp);											 
FRESULT f_read (FIL* fp, void* buff, UINT btr, UINT* br);			 
FRESULT f_write (FIL* fp, const void* buff, UINT btw, UINT* bw);	 
FRESULT f_lseek (FIL* fp, FSIZE_t ofs);								 
FRESULT f_truncate (FIL* fp);										 
FRESULT f_sync (FIL* fp);											 
FRESULT f_opendir (DIR* dp, const TCHAR* path);						 
FRESULT f_closedir (DIR* dp);										 
FRESULT f_readdir (DIR* dp, FILINFO* fno);							 
FRESULT f_findfirst (DIR* dp, FILINFO* fno, const TCHAR* path, const TCHAR* pattern);	 
FRESULT f_findnext (DIR* dp, FILINFO* fno);							 
FRESULT f_mkdir (const TCHAR* path);								 
FRESULT f_unlink (const TCHAR* path);								 
FRESULT f_rename (const TCHAR* path_old, const TCHAR* path_new);	 
FRESULT f_stat (const TCHAR* path, FILINFO* fno);					 
FRESULT f_chmod (const TCHAR* path, BYTE attr, BYTE mask);			 
FRESULT f_utime (const TCHAR* path, const FILINFO* fno);			 
FRESULT f_chdir (const TCHAR* path);								 
FRESULT f_chdrive (const TCHAR* path);								 
FRESULT f_getcwd (TCHAR* buff, UINT len);							 
FRESULT f_getfree (const TCHAR* path, DWORD* nclst, FATFS** fatfs);	 
FRESULT f_getlabel (const TCHAR* path, TCHAR* label, DWORD* vsn);	 
FRESULT f_setlabel (const TCHAR* label);							 
FRESULT f_forward (FIL* fp, UINT(*func)(const BYTE*,UINT), UINT btf, UINT* bf);	 
FRESULT f_expand (FIL* fp, FSIZE_t szf, BYTE opt);					 
FRESULT f_mount (FATFS* fs, const TCHAR* path, BYTE opt);			 
FRESULT f_mkfs (const TCHAR* path, BYTE opt, DWORD au, void* work, UINT len);	 
FRESULT f_fdisk (BYTE pdrv, const DWORD* szt, void* work);			 
int f_putc (TCHAR c, FIL* fp);										 
int f_puts (const TCHAR* str, FIL* cp);								 
int f_printf (FIL* fp, const TCHAR* str, ...);						 
TCHAR* f_gets (TCHAR* buff, int len, FIL* fp);						 

#line 283 "../Middlewares/Third_Party/FatFs/src/ff.h"








 
 

 

DWORD get_fattime (void);


 

WCHAR ff_convert (WCHAR chr, UINT dir);	 
WCHAR ff_wtoupper (WCHAR chr);			 






 

int ff_cre_syncobj (BYTE vol, osMutexId_t* sobj);	 
int ff_req_grant (osMutexId_t sobj);				 
void ff_rel_grant (osMutexId_t sobj);				 
int ff_del_syncobj (osMutexId_t sobj);				 





 
 


 
#line 332 "../Middlewares/Third_Party/FatFs/src/ff.h"

 


 






 





 











#line 22 "../Middlewares/Third_Party/FatFs/src/ff.c"
#line 1 "../Middlewares/Third_Party/FatFs/src/diskio.h"


 











#line 16 "../Middlewares/Third_Party/FatFs/src/diskio.h"


 
typedef BYTE	DSTATUS;

 
typedef enum {
	RES_OK = 0,		 
	RES_ERROR,		 
	RES_WRPRT,		 
	RES_NOTRDY,		 
	RES_PARERR		 
} DRESULT;


 
 


DSTATUS disk_initialize (BYTE pdrv);
DSTATUS disk_status (BYTE pdrv);
DRESULT disk_read (BYTE pdrv, BYTE* buff, DWORD sector, UINT count);
DRESULT disk_write (BYTE pdrv, const BYTE* buff, DWORD sector, UINT count);
DRESULT disk_ioctl (BYTE pdrv, BYTE cmd, void* buff);
DWORD get_fattime (void);

 






 

 






 





 






 








#line 23 "../Middlewares/Third_Party/FatFs/src/ff.c"






 






 

#line 84 "../Middlewares/Third_Party/FatFs/src/ff.c"

#line 271 "../Middlewares/Third_Party/FatFs/src/ff.c"


 




#line 293 "../Middlewares/Third_Party/FatFs/src/ff.c"







 





 





 
#line 322 "../Middlewares/Third_Party/FatFs/src/ff.c"


 
#line 331 "../Middlewares/Third_Party/FatFs/src/ff.c"



 

#line 358 "../Middlewares/Third_Party/FatFs/src/ff.c"

#line 372 "../Middlewares/Third_Party/FatFs/src/ff.c"

#line 392 "../Middlewares/Third_Party/FatFs/src/ff.c"

#line 429 "../Middlewares/Third_Party/FatFs/src/ff.c"











#line 452 "../Middlewares/Third_Party/FatFs/src/ff.c"


 



 
#line 469 "../Middlewares/Third_Party/FatFs/src/ff.c"


 
#line 479 "../Middlewares/Third_Party/FatFs/src/ff.c"


 
#line 490 "../Middlewares/Third_Party/FatFs/src/ff.c"


 
#line 501 "../Middlewares/Third_Party/FatFs/src/ff.c"


 




typedef struct {
	FATFS *fs;		 
	DWORD clu;		 
	DWORD ofs;		 
	WORD ctr;		 
} FILESEM;










 



 




static FATFS *FatFs[1];	 
static WORD Fsid;				 






static FILESEM Files[255];	 


#line 554 "../Middlewares/Third_Party/FatFs/src/ff.c"

#line 574 "../Middlewares/Third_Party/FatFs/src/ff.c"

#line 591 "../Middlewares/Third_Party/FatFs/src/ff.c"


static const BYTE ExCvt[] = {0x80,0x9A,0x45,0x41,0x8E,0x41,0x8F,0x80,0x45,0x45,0x45,0x49,0x49,0x49,0x8E,0x8F, 0x90,0x92,0x92,0x4F,0x99,0x4F,0x55,0x55,0x59,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, 0x41,0x49,0x4F,0x55,0xA5,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, 0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, 0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, 0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, 0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, 0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF};	 











 


 
 
 

static
WORD ld_word (const BYTE* ptr)	 
{
	WORD rv;

	rv = ptr[1];
	rv = rv << 8 | ptr[0];
	return rv;
}

static
DWORD ld_dword (const BYTE* ptr)	 
{
	DWORD rv;

	rv = ptr[3];
	rv = rv << 8 | ptr[2];
	rv = rv << 8 | ptr[1];
	rv = rv << 8 | ptr[0];
	return rv;
}


static
QWORD ld_qword (const BYTE* ptr)	 
{
	QWORD rv;

	rv = ptr[7];
	rv = rv << 8 | ptr[6];
	rv = rv << 8 | ptr[5];
	rv = rv << 8 | ptr[4];
	rv = rv << 8 | ptr[3];
	rv = rv << 8 | ptr[2];
	rv = rv << 8 | ptr[1];
	rv = rv << 8 | ptr[0];
	return rv;
}



static
void st_word (BYTE* ptr, WORD val)	 
{
	*ptr++ = (BYTE)val; val >>= 8;
	*ptr++ = (BYTE)val;
}

static
void st_dword (BYTE* ptr, DWORD val)	 
{
	*ptr++ = (BYTE)val; val >>= 8;
	*ptr++ = (BYTE)val; val >>= 8;
	*ptr++ = (BYTE)val; val >>= 8;
	*ptr++ = (BYTE)val;
}


static
void st_qword (BYTE* ptr, QWORD val)	 
{
	*ptr++ = (BYTE)val; val >>= 8;
	*ptr++ = (BYTE)val; val >>= 8;
	*ptr++ = (BYTE)val; val >>= 8;
	*ptr++ = (BYTE)val; val >>= 8;
	*ptr++ = (BYTE)val; val >>= 8;
	*ptr++ = (BYTE)val; val >>= 8;
	*ptr++ = (BYTE)val; val >>= 8;
	*ptr++ = (BYTE)val;
}





 
 
 

 
static
void mem_cpy (void* dst, const void* src, UINT cnt) {
	BYTE *d = (BYTE*)dst;
	const BYTE *s = (const BYTE*)src;

	if (cnt) {
		do {
			*d++ = *s++;
		} while (--cnt);
	}
}

 
static
void mem_set (void* dst, int val, UINT cnt) {
	BYTE *d = (BYTE*)dst;

	do {
		*d++ = (BYTE)val;
	} while (--cnt);
}

 
static
int mem_cmp (const void* dst, const void* src, UINT cnt) {	 
	const BYTE *d = (const BYTE *)dst, *s = (const BYTE *)src;
	int r = 0;

	do {
		r = *d++ - *s++;
	} while (--cnt && r == 0);

	return r;
}

 
static
int chk_chr (const char* str, int chr) {	 
	while (*str && *str != chr) str++;
	return *str;
}





 
 
 
static
int lock_fs (
	FATFS* fs		 
)
{
	return (fs && ff_req_grant(fs->sobj)) ? 1 : 0;
}


static
void unlock_fs (
	FATFS* fs,		 
	FRESULT res		 
)
{
	if (fs && res != FR_NOT_ENABLED && res != FR_INVALID_DRIVE && res != FR_TIMEOUT) {
		ff_rel_grant(fs->sobj);
	}
}






 
 
 

static
FRESULT chk_lock (	 
	DIR* dp,		 
	int acc			 
)
{
	UINT i, be;

	 
	for (i = be = 0; i < 255; i++) {
		if (Files[i].fs) {	 
			if (Files[i].fs == dp->obj.fs &&	 	 
				Files[i].clu == dp->obj.sclust &&
				Files[i].ofs == dp->dptr) break;
		} else {			 
			be = 1;
		}
	}
	if (i == 255) {	 
		return (be || acc == 2) ? FR_OK : FR_TOO_MANY_OPEN_FILES;	 
	}

	 
	return (acc || Files[i].ctr == 0x100) ? FR_LOCKED : FR_OK;
}


static
int enq_lock (void)	 
{
	UINT i;

	for (i = 0; i < 255 && Files[i].fs; i++) ;
	return (i == 255) ? 0 : 1;
}


static
UINT inc_lock (	 
	DIR* dp,	 
	int acc		 
)
{
	UINT i;


	for (i = 0; i < 255; i++) {	 
		if (Files[i].fs == dp->obj.fs &&
			Files[i].clu == dp->obj.sclust &&
			Files[i].ofs == dp->dptr) break;
	}

	if (i == 255) {				 
		for (i = 0; i < 255 && Files[i].fs; i++) ;
		if (i == 255) return 0;	 
		Files[i].fs = dp->obj.fs;
		Files[i].clu = dp->obj.sclust;
		Files[i].ofs = dp->dptr;
		Files[i].ctr = 0;
	}

	if (acc && Files[i].ctr) return 0;	 

	Files[i].ctr = acc ? 0x100 : Files[i].ctr + 1;	 

	return i + 1;
}


static
FRESULT dec_lock (	 
	UINT i			 
)
{
	WORD n;
	FRESULT res;


	if (--i < 255) {	 
		n = Files[i].ctr;
		if (n == 0x100) n = 0;		 
		if (n > 0) n--;				 
		Files[i].ctr = n;
		if (n == 0) Files[i].fs = 0;	 
		res = FR_OK;
	} else {
		res = FR_INT_ERR;			 
	}
	return res;
}


static
void clear_lock (	 
	FATFS *fs
)
{
	UINT i;

	for (i = 0; i < 255; i++) {
		if (Files[i].fs == fs) Files[i].fs = 0;
	}
}





 
 
 

static
FRESULT sync_window (	 
	FATFS* fs			 
)
{
	DWORD wsect;
	UINT nf;
	FRESULT res = FR_OK;


	if (fs->wflag) {	 
		wsect = fs->winsect;	 
		if (disk_write(fs->drv, fs->win, wsect, 1) != RES_OK) {
			res = FR_DISK_ERR;
		} else {
			fs->wflag = 0;
			if (wsect - fs->fatbase < fs->fsize) {		 
				for (nf = fs->n_fats; nf >= 2; nf--) {	 
					wsect += fs->fsize;
					disk_write(fs->drv, fs->win, wsect, 1);
				}
			}
		}
	}
	return res;
}



static
FRESULT move_window (	 
	FATFS* fs,			 
	DWORD sector		 
)
{
	FRESULT res = FR_OK;


	if (sector != fs->winsect) {	 

		res = sync_window(fs);		 

		if (res == FR_OK) {			 
			if (disk_read(fs->drv, fs->win, sector, 1) != RES_OK) {
				sector = 0xFFFFFFFF;	 
				res = FR_DISK_ERR;
			}
			fs->winsect = sector;
		}
	}
	return res;
}





 
 
 

static
FRESULT sync_fs (	 
	FATFS* fs		 
)
{
	FRESULT res;


	res = sync_window(fs);
	if (res == FR_OK) {
		 
		if (fs->fs_type == 3 && fs->fsi_flag == 1) {
			 
			mem_set(fs->win, 0, ((UINT)512));
			st_word(fs->win + 510, 0xAA55);
			st_dword(fs->win + 0, 0x41615252);
			st_dword(fs->win + 484, 0x61417272);
			st_dword(fs->win + 488, fs->free_clst);
			st_dword(fs->win + 492, fs->last_clst);
			 
			fs->winsect = fs->volbase + 1;
			disk_write(fs->drv, fs->win, fs->winsect, 1);
			fs->fsi_flag = 0;
		}
		 
		if (disk_ioctl(fs->drv, 0, 0) != RES_OK) res = FR_DISK_ERR;
	}

	return res;
}





 
 
 

static
DWORD clust2sect (	 
	FATFS* fs,		 
	DWORD clst		 
)
{
	clst -= 2;
	if (clst >= fs->n_fatent - 2) return 0;		 
	return clst * fs->csize + fs->database;
}




 
 
 

static
DWORD get_fat (	 
	_FDID* obj,	 
	DWORD clst	 
)
{
	UINT wc, bc;
	DWORD val;
	FATFS *fs = obj->fs;


	if (clst < 2 || clst >= fs->n_fatent) {	 
		val = 1;	 

	} else {
		val = 0xFFFFFFFF;	 

		switch (fs->fs_type) {
		case 1 :
			bc = (UINT)clst; bc += bc / 2;
			if (move_window(fs, fs->fatbase + (bc / ((UINT)512))) != FR_OK) break;
			wc = fs->win[bc++ % ((UINT)512)];
			if (move_window(fs, fs->fatbase + (bc / ((UINT)512))) != FR_OK) break;
			wc |= fs->win[bc % ((UINT)512)] << 8;
			val = (clst & 1) ? (wc >> 4) : (wc & 0xFFF);
			break;

		case 2 :
			if (move_window(fs, fs->fatbase + (clst / (((UINT)512) / 2))) != FR_OK) break;
			val = ld_word(fs->win + clst * 2 % ((UINT)512));
			break;

		case 3 :
			if (move_window(fs, fs->fatbase + (clst / (((UINT)512) / 4))) != FR_OK) break;
			val = ld_dword(fs->win + clst * 4 % ((UINT)512)) & 0x0FFFFFFF;
			break;

		case 4 :
			if (obj->objsize) {
				DWORD cofs = clst - obj->sclust;	 
				DWORD clen = (DWORD)((obj->objsize - 1) / ((UINT)512)) / fs->csize;	 

				if (obj->stat == 2) {	 
					if (cofs <= clen) {
						val = (cofs == clen) ? 0x7FFFFFFF : clst + 1;	 
						break;
					}
				}
				if (obj->stat == 3 && cofs < obj->n_cont) {	 
					val = clst + 1; 	 
					break;
				}
				if (obj->stat != 2) {	 
					if (obj->n_frag != 0) {	 
						val = 0x7FFFFFFF;	 
					} else {
						if (move_window(fs, fs->fatbase + (clst / (((UINT)512) / 4))) != FR_OK) break;
						val = ld_dword(fs->win + clst * 4 % ((UINT)512)) & 0x7FFFFFFF;
					}
					break;
				}
			}
			 

		default:
			val = 1;	 
		}
	}

	return val;
}





 
 
 

static
FRESULT put_fat (	 
	FATFS* fs,		 
	DWORD clst,		 
	DWORD val		 
)
{
	UINT bc;
	BYTE *p;
	FRESULT res = FR_INT_ERR;

	if (clst >= 2 && clst < fs->n_fatent) {	 
		switch (fs->fs_type) {
		case 1 :	 
			bc = (UINT)clst; bc += bc / 2;
			res = move_window(fs, fs->fatbase + (bc / ((UINT)512)));
			if (res != FR_OK) break;
			p = fs->win + bc++ % ((UINT)512);
			*p = (clst & 1) ? ((*p & 0x0F) | ((BYTE)val << 4)) : (BYTE)val;
			fs->wflag = 1;
			res = move_window(fs, fs->fatbase + (bc / ((UINT)512)));
			if (res != FR_OK) break;
			p = fs->win + bc % ((UINT)512);
			*p = (clst & 1) ? (BYTE)(val >> 4) : ((*p & 0xF0) | ((BYTE)(val >> 8) & 0x0F));
			fs->wflag = 1;
			break;

		case 2 :	 
			res = move_window(fs, fs->fatbase + (clst / (((UINT)512) / 2)));
			if (res != FR_OK) break;
			st_word(fs->win + clst * 2 % ((UINT)512), (WORD)val);
			fs->wflag = 1;
			break;

		case 3 :	 

		case 4 :

			res = move_window(fs, fs->fatbase + (clst / (((UINT)512) / 4)));
			if (res != FR_OK) break;
			if (!1 || fs->fs_type != 4) {
				val = (val & 0x0FFFFFFF) | (ld_dword(fs->win + clst * 4 % ((UINT)512)) & 0xF0000000);
			}
			st_dword(fs->win + clst * 4 % ((UINT)512), val);
			fs->wflag = 1;
			break;
		}
	}
	return res;
}







 
 
 

 
 
 

static
DWORD find_bitmap (	 
	FATFS* fs,	 
	DWORD clst,	 
	DWORD ncl	 
)
{
	BYTE bm, bv;
	UINT i;
	DWORD val, scl, ctr;


	clst -= 2;	 
	if (clst >= fs->n_fatent - 2) clst = 0;
	scl = val = clst; ctr = 0;
	for (;;) {
		if (move_window(fs, fs->database + val / 8 / ((UINT)512)) != FR_OK) return 0xFFFFFFFF;	 
		i = val / 8 % ((UINT)512); bm = 1 << (val % 8);
		do {
			do {
				bv = fs->win[i] & bm; bm <<= 1;		 
				if (++val >= fs->n_fatent - 2) {	 
					val = 0; bm = 0; i = ((UINT)512);
				}
				if (!bv) {	 
					if (++ctr == ncl) return scl + 2;	 
				} else {
					scl = val; ctr = 0;		 
				}
				if (val == clst) return 0;	 
			} while (bm);
			bm = 1;
		} while (++i < ((UINT)512));
	}
}


 
 
 

static
FRESULT change_bitmap (
	FATFS* fs,	 
	DWORD clst,	 
	DWORD ncl,	 
	int bv		 
)
{
	BYTE bm;
	UINT i;
	DWORD sect;

	clst -= 2;	 
	sect = fs->database + clst / 8 / ((UINT)512);	 
	i = clst / 8 % ((UINT)512);						 
	bm = 1 << (clst % 8);						 
	for (;;) {
		if (move_window(fs, sect++) != FR_OK) return FR_DISK_ERR;
		do {
			do {
				if (bv == (int)((fs->win[i] & bm) != 0)) return FR_INT_ERR;	 
				fs->win[i] ^= bm;	 
				fs->wflag = 1;
				if (--ncl == 0) return FR_OK;	 
			} while (bm <<= 1);		 
			bm = 1;
		} while (++i < ((UINT)512));		 
		i = 0;
	}
}


 
 
 

static
FRESULT fill_first_frag (
	_FDID* obj	 
)
{
	FRESULT res;
	DWORD cl, n;

	if (obj->stat == 3) {	 
		for (cl = obj->sclust, n = obj->n_cont; n; cl++, n--) {	 
			res = put_fat(obj->fs, cl, cl + 1);
			if (res != FR_OK) return res;
		}
		obj->stat = 0;	 
	}
	return FR_OK;
}


 
 
 

static
FRESULT fill_last_frag (
	_FDID* obj,	 
	DWORD lcl,	 
	DWORD term	 
)
{
	FRESULT res;

	while (obj->n_frag > 0) {	 
		res = put_fat(obj->fs, lcl - obj->n_frag + 1, (obj->n_frag > 1) ? lcl - obj->n_frag + 2 : term);
		if (res != FR_OK) return res;
		obj->n_frag--;
	}
	return FR_OK;
}






 
 
 
static
FRESULT remove_chain (	 
	_FDID* obj,			 
	DWORD clst,			 
	DWORD pclst			 
)
{
	FRESULT res = FR_OK;
	DWORD nxt;
	FATFS *fs = obj->fs;

	DWORD scl = clst, ecl = clst;


	DWORD rt[2];


	if (clst < 2 || clst >= fs->n_fatent) return FR_INT_ERR;	 

	 
	if (pclst && (!1 || fs->fs_type != 4 || obj->stat != 2)) {
		res = put_fat(fs, pclst, 0xFFFFFFFF);
		if (res != FR_OK) return res;
	}

	 
	do {
		nxt = get_fat(obj, clst);			 
		if (nxt == 0) break;				 
		if (nxt == 1) return FR_INT_ERR;	 
		if (nxt == 0xFFFFFFFF) return FR_DISK_ERR;	 
		if (!1 || fs->fs_type != 4) {
			res = put_fat(fs, clst, 0);		 
			if (res != FR_OK) return res;
		}
		if (fs->free_clst < fs->n_fatent - 2) {	 
			fs->free_clst++;
			fs->fsi_flag |= 1;
		}

		if (ecl + 1 == nxt) {	 
			ecl = nxt;
		} else {				 

			if (fs->fs_type == 4) {
				res = change_bitmap(fs, scl, ecl - scl + 1, 0);	 
				if (res != FR_OK) return res;
			}


			rt[0] = clust2sect(fs, scl);					 
			rt[1] = clust2sect(fs, ecl) + fs->csize - 1;	 
			disk_ioctl(fs->drv, 4, rt);				 

			scl = ecl = nxt;
		}

		clst = nxt;					 
	} while (clst < fs->n_fatent);	 


	if (fs->fs_type == 4) {
		if (pclst == 0) {	 
			obj->stat = 0;		 
		} else {
			if (obj->stat == 3 && pclst >= obj->sclust && pclst <= obj->sclust + obj->n_cont) {	 
				obj->stat = 2;	 
			}
		}
	}

	return FR_OK;
}




 
 
 
static
DWORD create_chain (	 
	_FDID* obj,			 
	DWORD clst			 
)
{
	DWORD cs, ncl, scl;
	FRESULT res;
	FATFS *fs = obj->fs;


	if (clst == 0) {	 
		scl = fs->last_clst;				 
		if (scl == 0 || scl >= fs->n_fatent) scl = 1;
	}
	else {				 
		cs = get_fat(obj, clst);			 
		if (cs < 2) return 1;				 
		if (cs == 0xFFFFFFFF) return cs;	 
		if (cs < fs->n_fatent) return cs;	 
		scl = clst;
	}


	if (fs->fs_type == 4) {	 
		ncl = find_bitmap(fs, scl, 1);				 
		if (ncl == 0 || ncl == 0xFFFFFFFF) return ncl;	 
		res = change_bitmap(fs, ncl, 1, 1);			 
		if (res == FR_INT_ERR) return 1;
		if (res == FR_DISK_ERR) return 0xFFFFFFFF;
		if (clst == 0) {							 
			obj->stat = 2;							 
		} else {									 
			if (obj->stat == 2 && ncl != scl + 1) {	 
				obj->n_cont = scl - obj->sclust;	 
				obj->stat = 3;						 
			}
		}
		if (obj->stat != 2) {	 
			if (ncl == clst + 1) {	 
				obj->n_frag = obj->n_frag ? obj->n_frag + 1 : 2;	 
			} else {				 
				if (obj->n_frag == 0) obj->n_frag = 1;
				res = fill_last_frag(obj, clst, ncl);	 
				if (res == FR_OK) obj->n_frag = 1;
			}
		}
	} else

	{	 
		ncl = scl;	 
		for (;;) {
			ncl++;							 
			if (ncl >= fs->n_fatent) {		 
				ncl = 2;
				if (ncl > scl) return 0;	 
			}
			cs = get_fat(obj, ncl);			 
			if (cs == 0) break;				 
			if (cs == 1 || cs == 0xFFFFFFFF) return cs;	 
			if (ncl == scl) return 0;		 
		}
		res = put_fat(fs, ncl, 0xFFFFFFFF);	 
		if (res == FR_OK && clst != 0) {
			res = put_fat(fs, clst, ncl);	 
		}
	}

	if (res == FR_OK) {			 
		fs->last_clst = ncl;
		if (fs->free_clst <= fs->n_fatent - 2) fs->free_clst--;
		fs->fsi_flag |= 1;
	} else {
		ncl = (res == FR_DISK_ERR) ? 0xFFFFFFFF : 1;	 
	}

	return ncl;		 
}







 
 
 

static
DWORD clmt_clust (	 
	FIL* fp,		 
	FSIZE_t ofs		 
)
{
	DWORD cl, ncl, *tbl;
	FATFS *fs = fp->obj.fs;


	tbl = fp->cltbl + 1;	 
	cl = (DWORD)(ofs / ((UINT)512) / fs->csize);	 
	for (;;) {
		ncl = *tbl++;			 
		if (ncl == 0) return 0;	 
		if (cl < ncl) break;	 
		cl -= ncl; tbl++;		 
	}
	return cl + *tbl;	 
}






 
 
 

static
FRESULT dir_sdi (	 
	DIR* dp,		 
	DWORD ofs		 
)
{
	DWORD csz, clst;
	FATFS *fs = dp->obj.fs;


	if (ofs >= (DWORD)((1 && fs->fs_type == 4) ? 0x10000000 : 0x200000) || ofs % 32) {	 
		return FR_INT_ERR;
	}
	dp->dptr = ofs;				 
	clst = dp->obj.sclust;		 
	if (clst == 0 && fs->fs_type >= 3) {	 
		clst = fs->dirbase;
		if (1) dp->obj.stat = 0;	 
	}

	if (clst == 0) {	 
		if (ofs / 32 >= fs->n_rootdir)	return FR_INT_ERR;	 
		dp->sect = fs->dirbase;

	} else {			 
		csz = (DWORD)fs->csize * ((UINT)512);	 
		while (ofs >= csz) {				 
			clst = get_fat(&dp->obj, clst);				 
			if (clst == 0xFFFFFFFF) return FR_DISK_ERR;	 
			if (clst < 2 || clst >= fs->n_fatent) return FR_INT_ERR;	 
			ofs -= csz;
		}
		dp->sect = clust2sect(fs, clst);
	}
	dp->clust = clst;					 
	if (!dp->sect) return FR_INT_ERR;
	dp->sect += ofs / ((UINT)512);			 
	dp->dir = fs->win + (ofs % ((UINT)512));	 

	return FR_OK;
}




 
 
 

static
FRESULT dir_next (	 
	DIR* dp,		 
	int stretch		 
)
{
	DWORD ofs, clst;
	FATFS *fs = dp->obj.fs;

	UINT n;


	ofs = dp->dptr + 32;	 
	if (!dp->sect || ofs >= (DWORD)((1 && fs->fs_type == 4) ? 0x10000000 : 0x200000)) return FR_NO_FILE;	 

	if (ofs % ((UINT)512) == 0) {	 
		dp->sect++;				 

		if (!dp->clust) {		 
			if (ofs / 32 >= fs->n_rootdir) {	 
				dp->sect = 0; return FR_NO_FILE;
			}
		}
		else {					 
			if ((ofs / ((UINT)512) & (fs->csize - 1)) == 0) {		 
				clst = get_fat(&dp->obj, dp->clust);			 
				if (clst <= 1) return FR_INT_ERR;				 
				if (clst == 0xFFFFFFFF) return FR_DISK_ERR;		 
				if (clst >= fs->n_fatent) {						 

					if (!stretch) {								 
						dp->sect = 0; return FR_NO_FILE;
					}
					clst = create_chain(&dp->obj, dp->clust);	 
					if (clst == 0) return FR_DENIED;			 
					if (clst == 1) return FR_INT_ERR;			 
					if (clst == 0xFFFFFFFF) return FR_DISK_ERR;	 
					 
					if (1) dp->obj.stat |= 4;			 
					if (sync_window(fs) != FR_OK) return FR_DISK_ERR;	 
					mem_set(fs->win, 0, ((UINT)512));				 
					for (n = 0, fs->winsect = clust2sect(fs, clst); n < fs->csize; n++, fs->winsect++) {	 
						fs->wflag = 1;
						if (sync_window(fs) != FR_OK) return FR_DISK_ERR;
					}
					fs->winsect -= n;							 




				}
				dp->clust = clst;		 
				dp->sect = clust2sect(fs, clst);
			}
		}
	}
	dp->dptr = ofs;						 
	dp->dir = fs->win + ofs % ((UINT)512);	 

	return FR_OK;
}





 
 
 

static
FRESULT dir_alloc (	 
	DIR* dp,		 
	UINT nent		 
)
{
	FRESULT res;
	UINT n;
	FATFS *fs = dp->obj.fs;


	res = dir_sdi(dp, 0);
	if (res == FR_OK) {
		n = 0;
		do {
			res = move_window(fs, dp->sect);
			if (res != FR_OK) break;

			if ((fs->fs_type == 4) ? (int)((dp->dir[0] & 0x80) == 0) : (int)(dp->dir[0] == 0xE5 || dp->dir[0] == 0)) {



				if (++n == nent) break;	 
			} else {
				n = 0;					 
			}
			res = dir_next(dp, 1);
		} while (res == FR_OK);	 
	}

	if (res == FR_NO_FILE) res = FR_DENIED;	 
	return res;
}






 
 
 

static
DWORD ld_clust (	 
	FATFS* fs,		 
	const BYTE* dir	 
)
{
	DWORD cl;

	cl = ld_word(dir + 26);
	if (fs->fs_type == 3) {
		cl |= (DWORD)ld_word(dir + 20) << 16;
	}

	return cl;
}



static
void st_clust (
	FATFS* fs,	 
	BYTE* dir,	 
	DWORD cl	 
)
{
	st_word(dir + 26, (WORD)cl);
	if (fs->fs_type == 3) {
		st_word(dir + 20, (WORD)(cl >> 16));
	}
}





 
 
 
static
const BYTE LfnOfs[] = {1,3,5,7,9,14,16,18,20,22,24,28,30};	 


 
 
 
static
int cmp_lfn (				 
	const WCHAR* lfnbuf,	 
	BYTE* dir				 
)
{
	UINT i, s;
	WCHAR wc, uc;


	if (ld_word(dir + 26) != 0) return 0;	 

	i = ((dir[0] & 0x3F) - 1) * 13;	 

	for (wc = 1, s = 0; s < 13; s++) {		 
		uc = ld_word(dir + LfnOfs[s]);		 
		if (wc) {
			if (i >= 255 || ff_wtoupper(uc) != ff_wtoupper(lfnbuf[i++])) {	 
				return 0;					 
			}
			wc = uc;
		} else {
			if (uc != 0xFFFF) return 0;		 
		}
	}

	if ((dir[0] & 0x40) && wc && lfnbuf[i]) return 0;	 

	return 1;		 
}



 
 
 
static
int pick_lfn (			 
	WCHAR* lfnbuf,		 
	BYTE* dir			 
)
{
	UINT i, s;
	WCHAR wc, uc;


	if (ld_word(dir + 26) != 0) return 0;	 

	i = ((dir[0] & ~0x40) - 1) * 13;	 

	for (wc = 1, s = 0; s < 13; s++) {		 
		uc = ld_word(dir + LfnOfs[s]);		 
		if (wc) {
			if (i >= 255) return 0;	 
			lfnbuf[i++] = wc = uc;			 
		} else {
			if (uc != 0xFFFF) return 0;		 
		}
	}

	if (dir[0] & 0x40) {				 
		if (i >= 255) return 0;		 
		lfnbuf[i] = 0;
	}

	return 1;		 
}




 
 
 
static
void put_lfn (
	const WCHAR* lfn,	 
	BYTE* dir,			 
	BYTE ord,			 
	BYTE sum			 
)
{
	UINT i, s;
	WCHAR wc;


	dir[13] = sum;			 
	dir[11] = 0x0F;		 
	dir[12] = 0;
	st_word(dir + 26, 0);

	i = (ord - 1) * 13;				 
	s = wc = 0;
	do {
		if (wc != 0xFFFF) wc = lfn[i++];	 
		st_word(dir + LfnOfs[s], wc);		 
		if (wc == 0) wc = 0xFFFF;		 
	} while (++s < 13);
	if (wc == 0xFFFF || !lfn[i]) ord |= 0x40;	 
	dir[0] = ord;			 
}







 
 
 

static
void gen_numname (
	BYTE* dst,			 
	const BYTE* src,	 
	const WCHAR* lfn,	 
	UINT seq			 
)
{
	BYTE ns[8], c;
	UINT i, j;
	WCHAR wc;
	DWORD sr;


	mem_cpy(dst, src, 11);

	if (seq > 5) {	 
		sr = seq;
		while (*lfn) {	 
			wc = *lfn++;
			for (i = 0; i < 16; i++) {
				sr = (sr << 1) + (wc & 1);
				wc >>= 1;
				if (sr & 0x10000) sr ^= 0x11021;
			}
		}
		seq = (UINT)sr;
	}

	 
	i = 7;
	do {
		c = (BYTE)((seq % 16) + '0');
		if (c > '9') c += 7;
		ns[i--] = c;
		seq /= 16;
	} while (seq);
	ns[i] = '~';

	 
	for (j = 0; j < i && dst[j] != ' '; j++) {
		if (0) {
			if (j == i - 1) break;
			j++;
		}
	}
	do {
		dst[j++] = (i < 8) ? ns[i++] : ' ';
	} while (j < 8);
}





 
 
 

static
BYTE sum_sfn (
	const BYTE* dir		 
)
{
	BYTE sum = 0;
	UINT n = 11;

	do {
		sum = (sum >> 1) + (sum << 7) + *dir++;
	} while (--n);
	return sum;
}






 
 
 

static
WORD xdir_sum (			 
	const BYTE* dir		 
)
{
	UINT i, szblk;
	WORD sum;


	szblk = (dir[1] + 1) * 32;
	for (i = sum = 0; i < szblk; i++) {
		if (i == 2) {	 
			i++;
		} else {
			sum = ((sum & 1) ? 0x8000 : 0) + (sum >> 1) + dir[i];
		}
	}
	return sum;
}



static
WORD xname_sum (		 
	const WCHAR* name	 
)
{
	WCHAR chr;
	WORD sum = 0;


	while ((chr = *name++) != 0) {
		chr = ff_wtoupper(chr);		 
		sum = ((sum & 1) ? 0x8000 : 0) + (sum >> 1) + (chr & 0xFF);
		sum = ((sum & 1) ? 0x8000 : 0) + (sum >> 1) + (chr >> 8);
	}
	return sum;
}



static
DWORD xsum32 (
	BYTE  dat,	 
	DWORD sum	 
)
{
	sum = ((sum & 1) ? 0x80000000 : 0) + (sum >> 1) + dat;
	return sum;
}




 
 
 

static
void get_xdir_info (
	BYTE* dirb,			 
	FILINFO* fno		 
)
{
	UINT di, si;
	WCHAR w;

	UINT nc;


	 
	di = 0;
#line 1950 "../Middlewares/Third_Party/FatFs/src/ff.c"
	for (si = 32 * 2, nc = 0; nc < dirb[35]; si += 2, nc++) {
		if ((si % 32) == 0) si += 2;		 
		w = ff_convert(ld_word(dirb + si), 0);	 
		if (0 && w >= 0x100) {				 
			fno->fname[di++] = (char)(w >> 8);	 
		}
		if (w == 0 || di >= 255) { di = 0; break; }	 
		fno->fname[di++] = (char)w;
	}

	if (di == 0) fno->fname[di++] = '?';	 
	fno->fname[di] = 0;						 

	fno->altname[0] = 0;							 
	fno->fattrib = dirb[4];					 
	fno->fsize = (fno->fattrib & 0x10) ? 0 : ld_qword(dirb + 56);	 
	fno->ftime = ld_word(dirb + 12 + 0);	 
	fno->fdate = ld_word(dirb + 12 + 2);	 
}




 
 
 

static
FRESULT load_xdir (	 
	DIR* dp			 
)
{
	FRESULT res;
	UINT i, sz_ent;
	BYTE* dirb = dp->obj.fs->dirbuf;	 


	 
	res = move_window(dp->obj.fs, dp->sect);
	if (res != FR_OK) return res;
	if (dp->dir[0] != 0x85) return FR_INT_ERR;
	mem_cpy(dirb + 0, dp->dir, 32);
	sz_ent = (dirb[1] + 1) * 32;
	if (sz_ent < 3 * 32 || sz_ent > 19 * 32) return FR_INT_ERR;

	 
	res = dir_next(dp, 0);
	if (res != FR_OK) return res;
	res = move_window(dp->obj.fs, dp->sect);
	if (res != FR_OK) return res;
	if (dp->dir[0] != 0xC0) return FR_INT_ERR;
	mem_cpy(dirb + 32, dp->dir, 32);
	if (((dirb[35] + 44U) / 15 * 32) > sz_ent) return FR_INT_ERR;

	 
	i = 32 * 2;	 
	do {
		res = dir_next(dp, 0);
		if (res != FR_OK) return res;
		res = move_window(dp->obj.fs, dp->sect);
		if (res != FR_OK) return res;
		if (dp->dir[0] != 0xC1) return FR_INT_ERR;
		if (i < ((255 + 44U) / 15 * 32)) mem_cpy(dirb + i, dp->dir, 32);
	} while ((i += 32) < sz_ent);

	 
	if (i <= ((255 + 44U) / 15 * 32)) {
		if (xdir_sum(dirb) != ld_word(dirb + 2)) return FR_INT_ERR;
	}
	return FR_OK;
}



 
 
 
static
FRESULT load_obj_dir (
	DIR* dp,			 
	const _FDID* obj	 
)
{
	FRESULT res;

	 
	dp->obj.fs = obj->fs;
	dp->obj.sclust = obj->c_scl;
	dp->obj.stat = (BYTE)obj->c_size;
	dp->obj.objsize = obj->c_size & 0xFFFFFF00;
	dp->blk_ofs = obj->c_ofs;

	res = dir_sdi(dp, dp->blk_ofs);	 
	if (res == FR_OK) {
		res = load_xdir(dp);		 
	}
	return res;
}




 
 
 
static
FRESULT store_xdir (
	DIR* dp				 
)
{
	FRESULT res;
	UINT nent;
	BYTE* dirb = dp->obj.fs->dirbuf;	 

	 
	st_word(dirb + 2, xdir_sum(dirb));
	nent = dirb[1] + 1;

	 
	res = dir_sdi(dp, dp->blk_ofs);
	while (res == FR_OK) {
		res = move_window(dp->obj.fs, dp->sect);
		if (res != FR_OK) break;
		mem_cpy(dp->dir, dirb, 32);
		dp->obj.fs->wflag = 1;
		if (--nent == 0) break;
		dirb += 32;
		res = dir_next(dp, 0);
	}
	return (res == FR_OK || res == FR_DISK_ERR) ? res : FR_INT_ERR;
}



 
 
 

static
void create_xdir (
	BYTE* dirb,			 
	const WCHAR* lfn	 
)
{
	UINT i;
	BYTE nb, nc;
	WCHAR chr;


	 
	mem_set(dirb, 0, 2 * 32);
	dirb[0] = 0x85;
	dirb[0 + 32] = 0xC0;

	 
	nc = 0; nb = 1; chr = 1; i = 32 * 2;
	do {
		dirb[i++] = 0xC1; dirb[i++] = 0;	 
		do {	 
			if (chr && (chr = lfn[nc]) != 0) nc++;	 
			st_word(dirb + i, chr); 		 
		} while ((i += 2) % 32 != 0);
		nb++;
	} while (lfn[nc]);	 

	dirb[35] = nc;	 
	dirb[1] = nb;		 
	st_word(dirb + 36, xname_sum(lfn));	 
}







 
 
 

static
FRESULT dir_read (
	DIR* dp,		 
	int vol			 
)
{
	FRESULT res = FR_NO_FILE;
	FATFS *fs = dp->obj.fs;
	BYTE a, c;

	BYTE ord = 0xFF, sum = 0xFF;


	while (dp->sect) {
		res = move_window(fs, dp->sect);
		if (res != FR_OK) break;
		c = dp->dir[0];	 
		if (c == 0) {
			res = FR_NO_FILE; break;  
		}

		if (fs->fs_type == 4) {	 
			if (1 && vol) {
				if (c == 0x83) break;	 
			} else {
				if (c == 0x85) {		 
					dp->blk_ofs = dp->dptr;	 
					res = load_xdir(dp);	 
					if (res == FR_OK) {
						dp->obj.attr = fs->dirbuf[4] & 0x3F;	 
					}
					break;
				}
			}
		} else

		{	 
			dp->obj.attr = a = dp->dir[11] & 0x3F;	 

			if (c == 0xE5 || c == '.' || (int)((a & ~0x20) == 0x08) != vol) {	 
				ord = 0xFF;
			} else {
				if (a == 0x0F) {			 
					if (c & 0x40) {			 
						sum = dp->dir[13];
						c &= (BYTE)~0x40; ord = c;
						dp->blk_ofs = dp->dptr;
					}
					 
					ord = (c == ord && sum == dp->dir[13] && pick_lfn(fs->lfnbuf, dp->dir)) ? ord - 1 : 0xFF;
				} else {					 
					if (ord || sum != sum_sfn(dp->dir)) {	 
						dp->blk_ofs = 0xFFFFFFFF;			 
					}
					break;
				}
			}





		}
		res = dir_next(dp, 0);		 
		if (res != FR_OK) break;
	}

	if (res != FR_OK) dp->sect = 0;		 
	return res;
}





 
 
 

static
FRESULT dir_find (	 
	DIR* dp			 
)
{
	FRESULT res;
	FATFS *fs = dp->obj.fs;
	BYTE c;

	BYTE a, ord, sum;


	res = dir_sdi(dp, 0);			 
	if (res != FR_OK) return res;

	if (fs->fs_type == 4) {	 
		BYTE nc;
		UINT di, ni;
		WORD hash = xname_sum(fs->lfnbuf);		 

		while ((res = dir_read(dp, 0)) == FR_OK) {	 



			if (ld_word(fs->dirbuf + 36) != hash) continue;	 
			for (nc = fs->dirbuf[35], di = 32 * 2, ni = 0; nc; nc--, di += 2, ni++) {	 
				if ((di % 32) == 0) di += 2;
				if (ff_wtoupper(ld_word(fs->dirbuf + di)) != ff_wtoupper(fs->lfnbuf[ni])) break;
			}
			if (nc == 0 && !fs->lfnbuf[ni]) break;	 
		}
		return res;
	}

	 

	ord = sum = 0xFF; dp->blk_ofs = 0xFFFFFFFF;	 

	do {
		res = move_window(fs, dp->sect);
		if (res != FR_OK) break;
		c = dp->dir[0];
		if (c == 0) { res = FR_NO_FILE; break; }	 

		dp->obj.attr = a = dp->dir[11] & 0x3F;
		if (c == 0xE5 || ((a & 0x08) && a != 0x0F)) {	 
			ord = 0xFF; dp->blk_ofs = 0xFFFFFFFF;	 
		} else {
			if (a == 0x0F) {			 
				if (!(dp->fn[11] & 0x40)) {
					if (c & 0x40) {		 
						sum = dp->dir[13];
						c &= (BYTE)~0x40; ord = c;	 
						dp->blk_ofs = dp->dptr;	 
					}
					 
					ord = (c == ord && sum == dp->dir[13] && cmp_lfn(fs->lfnbuf, dp->dir)) ? ord - 1 : 0xFF;
				}
			} else {					 
				if (!ord && sum == sum_sfn(dp->dir)) break;	 
				if (!(dp->fn[11] & 0x01) && !mem_cmp(dp->dir, dp->fn, 11)) break;	 
				ord = 0xFF; dp->blk_ofs = 0xFFFFFFFF;	 
			}
		}




		res = dir_next(dp, 0);	 
	} while (res == FR_OK);

	return res;
}





 
 
 

static
FRESULT dir_register (	 
	DIR* dp				 
)
{
	FRESULT res;
	FATFS *fs = dp->obj.fs;

	UINT n, nlen, nent;
	BYTE sn[12], sum;


	if (dp->fn[11] & (0x20 | 0x80)) return FR_INVALID_NAME;	 
	for (nlen = 0; fs->lfnbuf[nlen]; nlen++) ;	 


	if (fs->fs_type == 4) {	 
		DIR dj;

		nent = (nlen + 14) / 15 + 2;	 
		res = dir_alloc(dp, nent);		 
		if (res != FR_OK) return res;
		dp->blk_ofs = dp->dptr - 32 * (nent - 1);	 

		if (dp->obj.sclust != 0 && (dp->obj.stat & 4)) {	 
			dp->obj.objsize += (DWORD)fs->csize * ((UINT)512);	 
			res = fill_first_frag(&dp->obj);				 
			if (res != FR_OK) return res;
			res = fill_last_frag(&dp->obj, dp->clust, 0xFFFFFFFF);	 
			if (res != FR_OK) return res;
			res = load_obj_dir(&dj, &dp->obj);				 
			if (res != FR_OK) return res;
			st_qword(fs->dirbuf + 56, dp->obj.objsize);		 
			st_qword(fs->dirbuf + 40, dp->obj.objsize);
			fs->dirbuf[33] = dp->obj.stat | 1;
			res = store_xdir(&dj);							 
			if (res != FR_OK) return res;
		}

		create_xdir(fs->dirbuf, fs->lfnbuf);	 
		return FR_OK;
	}

	 
	mem_cpy(sn, dp->fn, 12);
	if (sn[11] & 0x01) {			 
		dp->fn[11] = 0x40;		 
		for (n = 1; n < 100; n++) {
			gen_numname(dp->fn, sn, fs->lfnbuf, n);	 
			res = dir_find(dp);				 
			if (res != FR_OK) break;
		}
		if (n == 100) return FR_DENIED;		 
		if (res != FR_NO_FILE) return res;	 
		dp->fn[11] = sn[11];
	}

	 
	nent = (sn[11] & 0x02) ? (nlen + 12) / 13 + 1 : 1;	 
	res = dir_alloc(dp, nent);		 
	if (res == FR_OK && --nent) {	 
		res = dir_sdi(dp, dp->dptr - nent * 32);
		if (res == FR_OK) {
			sum = sum_sfn(dp->fn);	 
			do {					 
				res = move_window(fs, dp->sect);
				if (res != FR_OK) break;
				put_lfn(fs->lfnbuf, dp->dir, (BYTE)nent, sum);
				fs->wflag = 1;
				res = dir_next(dp, 0);	 
			} while (res == FR_OK && --nent);
		}
	}






	 
	if (res == FR_OK) {
		res = move_window(fs, dp->sect);
		if (res == FR_OK) {
			mem_set(dp->dir, 0, 32);	 
			mem_cpy(dp->dir + 0, dp->fn, 11);	 

			dp->dir[12] = dp->fn[11] & (0x08 | 0x10);	 

			fs->wflag = 1;
		}
	}

	return res;
}






 
 
 

static
FRESULT dir_remove (	 
	DIR* dp				 
)
{
	FRESULT res;
	FATFS *fs = dp->obj.fs;

	DWORD last = dp->dptr;

	res = (dp->blk_ofs == 0xFFFFFFFF) ? FR_OK : dir_sdi(dp, dp->blk_ofs);	 
	if (res == FR_OK) {
		do {
			res = move_window(fs, dp->sect);
			if (res != FR_OK) break;
			 
			if (1 && fs->fs_type == 4) {	 
				dp->dir[0] &= 0x7F;
			} else {									 
				dp->dir[0] = 0xE5;
			}
			fs->wflag = 1;
			if (dp->dptr >= last) break;	 
			res = dir_next(dp, 0);	 
		} while (res == FR_OK);
		if (res == FR_NO_FILE) res = FR_INT_ERR;
	}
#line 2430 "../Middlewares/Third_Party/FatFs/src/ff.c"

	return res;
}






 
 
 

static
void get_fileinfo (		 
	DIR* dp,			 
	FILINFO* fno	 	 
)
{
	UINT i, j;
	TCHAR c;
	DWORD tm;

	WCHAR w, lfv;
	FATFS *fs = dp->obj.fs;



	fno->fname[0] = 0;		 
	if (!dp->sect) return;	 



	if (fs->fs_type == 4) {	 
		get_xdir_info(fs->dirbuf, fno);
		return;
	} else

	{	 
		if (dp->blk_ofs != 0xFFFFFFFF) {	 
			i = j = 0;
			while ((w = fs->lfnbuf[j++]) != 0) {	 

				w = ff_convert(w, 0);		 
				if (w == 0) { i = 0; break; }	 
				if (0 && w >= 0x100) {	 
					fno->fname[i++] = (char)(w >> 8);
				}

				if (i >= 255) { i = 0; break; }	 
				fno->fname[i++] = (TCHAR)w;
			}
			fno->fname[i] = 0;	 
		}
	}

	i = j = 0;
	lfv = fno->fname[i];	 
	while (i < 11) {		 
		c = (TCHAR)dp->dir[i++];
		if (c == ' ') continue;				 
		if (c == 0x05) c = (TCHAR)0xE5;	 
		if (i == 9) {						 
			if (!lfv) fno->fname[j] = '.';
			fno->altname[j++] = '.';
		}
#line 2503 "../Middlewares/Third_Party/FatFs/src/ff.c"
		fno->altname[j] = c;
		if (!lfv) {
			if ((((c)>= 'A')&&((c)<= 'Z')) && (dp->dir[12] & ((i >= 9) ? 0x10 : 0x08))) {
				c += 0x20;			 
			}
			fno->fname[j] = c;
		}
		j++;
	}
	if (!lfv) {
		fno->fname[j] = 0;
		if (!dp->dir[12]) j = 0;	 
	}
	fno->altname[j] = 0;	 

#line 2529 "../Middlewares/Third_Party/FatFs/src/ff.c"

	fno->fattrib = dp->dir[11];				 
	fno->fsize = ld_dword(dp->dir + 28);	 
	tm = ld_dword(dp->dir + 22);			 
	fno->ftime = (WORD)tm; fno->fdate = (WORD)(tm >> 16);
}






 
 
 

static
WCHAR get_achar (		 
	const TCHAR** ptr	 
)
{

	WCHAR chr;

	chr = (BYTE)*(*ptr)++;					 
	if ((((chr)>= 'a')&&((chr)<= 'z'))) chr -= 0x20;			 

	if (chr >= 0x80) chr = ExCvt[chr - 0x80];	 





	return chr;



}


static
int pattern_matching (	 
	const TCHAR* pat,	 
	const TCHAR* nam,	 
	int skip,			 
	int inf				 
)
{
	const TCHAR *pp, *np;
	WCHAR pc, nc;
	int nm, nx;


	while (skip--) {				 
		if (!get_achar(&nam)) return 0;	 
	}
	if (!*pat && inf) return 1;		 

	do {
		pp = pat; np = nam;			 
		for (;;) {
			if (*pp == '?' || *pp == '*') {	 
				nm = nx = 0;
				do {				 
					if (*pp++ == '?') nm++; else nx = 1;
				} while (*pp == '?' || *pp == '*');
				if (pattern_matching(pp, np, nm, nx)) return 1;	 
				nc = *np; break;	 
			}
			pc = get_achar(&pp);	 
			nc = get_achar(&np);	 
			if (pc != nc) break;	 
			if (pc == 0) return 1;	 
		}
		get_achar(&nam);			 
	} while (inf && nc);			 

	return 0;
}





 
 
 

static
FRESULT create_name (	 
	DIR* dp,			 
	const TCHAR** path	 
)
{

	BYTE b, cf;
	WCHAR w, *lfn;
	UINT i, ni, si, di;
	const TCHAR *p;

	 
	p = *path; lfn = dp->obj.fs->lfnbuf; si = di = 0;
	for (;;) {
		w = p[si++];					 
		if (w < ' ') break;				 
		if (w == '/' || w == '\\') {	 
			while (p[si] == '/' || p[si] == '\\') si++;	 
			break;
		}
		if (di >= 255) return FR_INVALID_NAME;	 

		w &= 0xFF;
		if (0) {				 
			b = (BYTE)p[si++];			 
			w = (w << 8) + b;			 
			if (!0) return FR_INVALID_NAME;	 
		}
		w = ff_convert(w, 1);			 
		if (!w) return FR_INVALID_NAME;	 

		if (w < 0x80 && chk_chr("\"*:<>\?|\x7F", w)) return FR_INVALID_NAME;	 
		lfn[di++] = w;					 
	}
	*path = &p[si];						 
	cf = (w < ' ') ? 0x04 : 0;		 
#line 2664 "../Middlewares/Third_Party/FatFs/src/ff.c"
	while (di) {						 
		w = lfn[di - 1];
		if (w != ' ' && w != '.') break;
		di--;
	}
	lfn[di] = 0;						 
	if (di == 0) return FR_INVALID_NAME;	 

	 
	mem_set(dp->fn, ' ', 11);
	for (si = 0; lfn[si] == ' ' || lfn[si] == '.'; si++) ;	 
	if (si) cf |= 0x01 | 0x02;
	while (di && lfn[di - 1] != '.') di--;	 

	i = b = 0; ni = 8;
	for (;;) {
		w = lfn[si++];					 
		if (!w) break;					 
		if (w == ' ' || (w == '.' && si != di)) {	 
			cf |= 0x01 | 0x02; continue;
		}

		if (i >= ni || si == di) {		 
			if (ni == 11) {				 
				cf |= 0x01 | 0x02; break;
			}
			if (si != di) cf |= 0x01 | 0x02;	 
			if (si > di) break;			 
			si = di; i = 8; ni = 11;	 
			b <<= 2; continue;
		}

		if (w >= 0x80) {				 

			w = ff_convert(w, 0);		 
			if (w) w = ExCvt[w - 0x80];	 



			cf |= 0x02;				 
		}

		if (0 && w >= 0x100) {		 
			if (i >= ni - 1) {
				cf |= 0x01 | 0x02; i = ni; continue;
			}
			dp->fn[i++] = (BYTE)(w >> 8);
		} else {						 
			if (!w || chk_chr("+,;=[]", w)) {	 
				w = '_'; cf |= 0x01 | 0x02; 
			} else {
				if ((((w)>= 'A')&&((w)<= 'Z'))) {		 
					b |= 2;
				} else {
					if ((((w)>= 'a')&&((w)<= 'z'))) {	 
						b |= 1; w -= 0x20;
					}
				}
			}
		}
		dp->fn[i++] = (BYTE)w;
	}

	if (dp->fn[0] == 0xE5) dp->fn[0] = 0x05;	 

	if (ni == 8) b <<= 2;
	if ((b & 0x0C) == 0x0C || (b & 0x03) == 0x03) cf |= 0x02;	 
	if (!(cf & 0x02)) {						 
		if ((b & 0x03) == 0x01) cf |= 0x10;	 
		if ((b & 0x0C) == 0x04) cf |= 0x08;	 
	}

	dp->fn[11] = cf;	 

	return FR_OK;


#line 2803 "../Middlewares/Third_Party/FatFs/src/ff.c"
}




 
 
 

static
FRESULT follow_path (	 
	DIR* dp,			 
	const TCHAR* path	 
)
{
	FRESULT res;
	BYTE ns;
	_FDID *obj = &dp->obj;
	FATFS *fs = obj->fs;







	{										 
		while (*path == '/' || *path == '\\') path++;	 
		obj->sclust = 0;					 
	}

	obj->n_frag = 0;	 
#line 2849 "../Middlewares/Third_Party/FatFs/src/ff.c"

	if ((UINT)*path < ' ') {				 
		dp->fn[11] = 0x80;
		res = dir_sdi(dp, 0);

	} else {								 
		for (;;) {
			res = create_name(dp, &path);	 
			if (res != FR_OK) break;
			res = dir_find(dp);				 
			ns = dp->fn[11];
			if (res != FR_OK) {				 
				if (res == FR_NO_FILE) {	 
					if (0 && (ns & 0x20)) {	 
						if (!(ns & 0x04)) continue;	 
						dp->fn[11] = 0x80;
						res = FR_OK;
					} else {							 
						if (!(ns & 0x04)) res = FR_NO_PATH;	 
					}
				}
				break;
			}
			if (ns & 0x04) break;			 
			 
			if (!(obj->attr & 0x10)) {		 
				res = FR_NO_PATH; break;
			}

			if (fs->fs_type == 4) {		 
				obj->c_scl = obj->sclust;
				obj->c_size = ((DWORD)obj->objsize & 0xFFFFFF00) | obj->stat;
				obj->c_ofs = dp->blk_ofs;
				obj->sclust = ld_dword(fs->dirbuf + 52);	 
				obj->stat = fs->dirbuf[33] & 2;
				obj->objsize = ld_qword(fs->dirbuf + 56);
			} else

			{
				obj->sclust = ld_clust(fs, fs->win + dp->dptr % ((UINT)512));	 
			}
		}
	}

	return res;
}




 
 
 

static
int get_ldnumber (		 
	const TCHAR** path	 
)
{
	const TCHAR *tp, *tt;
	UINT i;
	int vol = -1;
#line 2917 "../Middlewares/Third_Party/FatFs/src/ff.c"


	if (*path) {	 
		for (tt = *path; (UINT)*tt >= (2 ? ' ' : '!') && *tt != ':'; tt++) ;	 
		if (*tt == ':') {	 
			tp = *path;
			i = *tp++ - '0';
			if (i < 10 && tp == tt) {	 
				if (i < 1) {	 
					vol = (int)i;
					*path = ++tt;
				}
			}
#line 2946 "../Middlewares/Third_Party/FatFs/src/ff.c"
			return vol;
		}



		vol = 0;		 

	}
	return vol;
}




 
 
 

static
BYTE check_fs (	 
	FATFS* fs,	 
	DWORD sect	 
)
{
	fs->wflag = 0; fs->winsect = 0xFFFFFFFF;		 
	if (move_window(fs, sect) != FR_OK) return 4;	 

	if (ld_word(fs->win + 510) != 0xAA55) return 3;	 

	if (fs->win[0] == 0xE9 || (fs->win[0] == 0xEB && fs->win[0 + 2] == 0x90)) {
		if ((ld_dword(fs->win + 54) & 0xFFFFFF) == 0x544146) return 0;	 
		if (ld_dword(fs->win + 82) == 0x33544146) return 0;			 
	}

	if (!mem_cmp(fs->win + 0, "\xEB\x76\x90" "EXFAT   ", 11)) return 1;

	return 2;
}




 
 
 

static
FRESULT find_volume (	 
	const TCHAR** path,	 
	FATFS** rfs,		 
	BYTE mode			 
)
{
	BYTE fmt, *pt;
	int vol;
	DSTATUS stat;
	DWORD bsect, fasize, tsect, sysect, nclst, szbfat, br[4];
	WORD nrsv;
	FATFS *fs;
	UINT i;


	 
	*rfs = 0;
	vol = get_ldnumber(path);
	if (vol < 0) return FR_INVALID_DRIVE;

	 
	fs = FatFs[vol];					 
	if (!fs) return FR_NOT_ENABLED;		 

	{ if (!lock_fs(fs)) return FR_TIMEOUT; };						 
	*rfs = fs;							 

	mode &= (BYTE)~0x01;				 
	if (fs->fs_type) {					 
		stat = disk_status(fs->drv);
		if (!(stat & 0x01)) {		 
			if (!0 && mode && (stat & 0x04)) {	 
				return FR_WRITE_PROTECTED;
			}
			return FR_OK;				 
		}
	}

	 
	 

	fs->fs_type = 0;					 
	fs->drv = (BYTE)(vol);				 
	stat = disk_initialize(fs->drv);	 
	if (stat & 0x01) { 			 
		return FR_NOT_READY;			 
	}
	if (!0 && mode && (stat & 0x04)) {  
		return FR_WRITE_PROTECTED;
	}





	 
	bsect = 0;
	fmt = check_fs(fs, bsect);			 
	if (fmt == 2 || (fmt < 2 && 0 != 0)) {	 
		for (i = 0; i < 4; i++) {		 
			pt = fs->win + (446 + i * 16);
			br[i] = pt[4] ? ld_dword(pt + 8) : 0;
		}
		i = 0;					 
		if (i) i--;
		do {							 
			bsect = br[i];
			fmt = bsect ? check_fs(fs, bsect) : 3;	 
		} while (0 == 0 && fmt >= 2 && ++i < 4);
	}
	if (fmt == 4) return FR_DISK_ERR;		 
	if (fmt >= 2) return FR_NO_FILESYSTEM;	 

	 


	if (fmt == 1) {
		QWORD maxlba;

		for (i = 11; i < 11 + 53 && fs->win[i] == 0; i++) ;	 
		if (i < 11 + 53) return FR_NO_FILESYSTEM;

		if (ld_word(fs->win + 104) != 0x100) return FR_NO_FILESYSTEM;	 

		if (1 << fs->win[108] != ((UINT)512)) {	 
			return FR_NO_FILESYSTEM;
		}

		maxlba = ld_qword(fs->win + 72) + bsect;	 
		if (maxlba >= 0x100000000) return FR_NO_FILESYSTEM;	 

		fs->fsize = ld_dword(fs->win + 84);	 

		fs->n_fats = fs->win[110];			 
		if (fs->n_fats != 1) return FR_NO_FILESYSTEM;	 

		fs->csize = 1 << fs->win[109];		 
		if (fs->csize == 0)	return FR_NO_FILESYSTEM;	 

		nclst = ld_dword(fs->win + 92);		 
		if (nclst > 0x7FFFFFFD) return FR_NO_FILESYSTEM;	 
		fs->n_fatent = nclst + 2;

		 
		fs->volbase = bsect;
		fs->database = bsect + ld_dword(fs->win + 88);
		fs->fatbase = bsect + ld_dword(fs->win + 80);
		if (maxlba < (QWORD)fs->database + nclst * fs->csize) return FR_NO_FILESYSTEM;	 
		fs->dirbase = ld_dword(fs->win + 96);

		 
		if (move_window(fs, clust2sect(fs, fs->dirbase)) != FR_OK) return FR_DISK_ERR;
		for (i = 0; i < ((UINT)512); i += 32) {
			if (fs->win[i] == 0x81 && ld_dword(fs->win + i + 20) == 2) break;	 
		}
		if (i == ((UINT)512)) return FR_NO_FILESYSTEM;

		fs->last_clst = fs->free_clst = 0xFFFFFFFF;		 

		fmt = 4;			 
	} else

	{
		if (ld_word(fs->win + 11) != ((UINT)512)) return FR_NO_FILESYSTEM;	 

		fasize = ld_word(fs->win + 22);		 
		if (fasize == 0) fasize = ld_dword(fs->win + 36);
		fs->fsize = fasize;

		fs->n_fats = fs->win[16];				 
		if (fs->n_fats != 1 && fs->n_fats != 2) return FR_NO_FILESYSTEM;	 
		fasize *= fs->n_fats;							 

		fs->csize = fs->win[13];			 
		if (fs->csize == 0 || (fs->csize & (fs->csize - 1))) return FR_NO_FILESYSTEM;	 

		fs->n_rootdir = ld_word(fs->win + 17);	 
		if (fs->n_rootdir % (((UINT)512) / 32)) return FR_NO_FILESYSTEM;	 

		tsect = ld_word(fs->win + 19);		 
		if (tsect == 0) tsect = ld_dword(fs->win + 32);

		nrsv = ld_word(fs->win + 14);		 
		if (nrsv == 0) return FR_NO_FILESYSTEM;			 

		 
		sysect = nrsv + fasize + fs->n_rootdir / (((UINT)512) / 32);	 
		if (tsect < sysect) return FR_NO_FILESYSTEM;	 
		nclst = (tsect - sysect) / fs->csize;			 
		if (nclst == 0) return FR_NO_FILESYSTEM;		 
		fmt = 3;
		if (nclst <= 0xFFF5) fmt = 2;
		if (nclst <= 0xFF5) fmt = 1;

		 
		fs->n_fatent = nclst + 2;						 
		fs->volbase = bsect;							 
		fs->fatbase = bsect + nrsv; 					 
		fs->database = bsect + sysect;					 
		if (fmt == 3) {
			if (ld_word(fs->win + 42) != 0) return FR_NO_FILESYSTEM;	 
			if (fs->n_rootdir) return FR_NO_FILESYSTEM;	 
			fs->dirbase = ld_dword(fs->win + 44);	 
			szbfat = fs->n_fatent * 4;					 
		} else {
			if (fs->n_rootdir == 0)	return FR_NO_FILESYSTEM; 
			fs->dirbase = fs->fatbase + fasize;			 
			szbfat = (fmt == 2) ?				 
				fs->n_fatent * 2 : fs->n_fatent * 3 / 2 + (fs->n_fatent & 1);
		}
		if (fs->fsize < (szbfat + (((UINT)512) - 1)) / ((UINT)512)) return FR_NO_FILESYSTEM;	 


		 
		fs->last_clst = fs->free_clst = 0xFFFFFFFF;		 
		fs->fsi_flag = 0x80;

		if (fmt == 3				 
			&& ld_word(fs->win + 48) == 1
			&& move_window(fs, bsect + 1) == FR_OK)
		{
			fs->fsi_flag = 0;
			if (ld_word(fs->win + 510) == 0xAA55	 
				&& ld_dword(fs->win + 0) == 0x41615252
				&& ld_dword(fs->win + 484) == 0x61417272)
			{

				fs->free_clst = ld_dword(fs->win + 488);


				fs->last_clst = ld_dword(fs->win + 492);

			}
		}


	}

	fs->fs_type = fmt;		 
	fs->id = ++Fsid;		 
#line 3203 "../Middlewares/Third_Party/FatFs/src/ff.c"
	clear_lock(fs);

	return FR_OK;
}




 
 
 

static
FRESULT validate (	 
	_FDID* obj,		 
	FATFS** fs		 
)
{
	FRESULT res = FR_INVALID_OBJECT;


	if (obj && obj->fs && obj->fs->fs_type && obj->id == obj->fs->id) {	 

		if (lock_fs(obj->fs)) {	 
			if (!(disk_status(obj->fs->drv) & 0x01)) {  
				res = FR_OK;
			} else {
				unlock_fs(obj->fs, FR_OK);
			}
		} else {
			res = FR_TIMEOUT;
		}





	}
	*fs = (res == FR_OK) ? obj->fs : 0;	 
	return res;
}








 



 
 
 

FRESULT f_mount (
	FATFS* fs,			 
	const TCHAR* path,	 
	BYTE opt			 
)
{
	FATFS *cfs;
	int vol;
	FRESULT res;
	const TCHAR *rp = path;


	 
	vol = get_ldnumber(&rp);
	if (vol < 0) return FR_INVALID_DRIVE;
	cfs = FatFs[vol];					 

	if (cfs) {

		clear_lock(cfs);


		if (!ff_del_syncobj(cfs->sobj)) return FR_INT_ERR;

		cfs->fs_type = 0;				 
	}

	if (fs) {
		fs->fs_type = 0;				 

		if (!ff_cre_syncobj((BYTE)vol, &fs->sobj)) return FR_INT_ERR;

	}
	FatFs[vol] = fs;					 

	if (!fs || opt != 1) return FR_OK;	 

	res = find_volume(&path, &fs, 0);	 
	{ unlock_fs(fs, res); return res; };
}




 
 
 

FRESULT f_open (
	FIL* fp,			 
	const TCHAR* path,	 
	BYTE mode			 
)
{
	FRESULT res;
	DIR dj;
	FATFS *fs;

	DWORD dw, cl, bcs, clst, sc;
	FSIZE_t ofs;

	WCHAR lbuf[255+1]; BYTE dbuf[((255 + 44U) / 15 * 32)];


	if (!fp) return FR_INVALID_OBJECT;

	 
	mode &= 0 ? 0x01 : 0x01 | 0x02 | 0x08 | 0x04 | 0x10 | 0x30 | 0x20;
	res = find_volume(&path, &fs, mode);
	if (res == FR_OK) {
		dj.obj.fs = fs;
		{ (fs)->lfnbuf = lbuf; (fs)->dirbuf = dbuf; };
		res = follow_path(&dj, path);	 

		if (res == FR_OK) {
			if (dj.fn[11] & 0x80) {	 
				res = FR_INVALID_NAME;
			}

			else {
				res = chk_lock(&dj, (mode & ~0x01) ? 1 : 0);
			}

		}
		 
		if (mode & (0x08 | 0x10 | 0x04)) {
			if (res != FR_OK) {					 
				if (res == FR_NO_FILE) {		 

					res = enq_lock() ? dir_register(&dj) : FR_TOO_MANY_OPEN_FILES;



				}
				mode |= 0x08;		 
			}
			else {								 
				if (dj.obj.attr & (0x01 | 0x10)) {	 
					res = FR_DENIED;
				} else {
					if (mode & 0x04) res = FR_EXIST;	 
				}
			}
			if (res == FR_OK && (mode & 0x08)) {	 
				dw = get_fattime();

				if (fs->fs_type == 4) {
					 
					fp->obj.fs = fs;
					fp->obj.sclust = ld_dword(fs->dirbuf + 52);
					fp->obj.objsize = ld_qword(fs->dirbuf + 56);
					fp->obj.stat = fs->dirbuf[33] & 2;
					fp->obj.n_frag = 0;
					 
					st_dword(fs->dirbuf + 8, dw);	 
					fs->dirbuf[20] = 0;
					st_dword(fs->dirbuf + 12, dw);	 
					fs->dirbuf[21] = 0;
					fs->dirbuf[4] = 0x20;				 
					st_dword(fs->dirbuf + 52, 0);		 
					st_qword(fs->dirbuf + 56, 0);
					st_qword(fs->dirbuf + 40, 0);
					fs->dirbuf[33] = 1;
					res = store_xdir(&dj);
					if (res == FR_OK && fp->obj.sclust) {		 
						res = remove_chain(&fp->obj, fp->obj.sclust, 0);
						fs->last_clst = fp->obj.sclust - 1;		 
					}
				} else

				{
					 
					st_dword(dj.dir + 14, dw);	 
					st_dword(dj.dir + 22, dw);	 
					dj.dir[11] = 0x20;			 
					cl = ld_clust(fs, dj.dir);			 
					st_clust(fs, dj.dir, 0);			 
					st_dword(dj.dir + 28, 0);
					fs->wflag = 1;

					if (cl) {							 
						dw = fs->winsect;
						res = remove_chain(&dj.obj, cl, 0);
						if (res == FR_OK) {
							res = move_window(fs, dw);
							fs->last_clst = cl - 1;		 
						}
					}
				}
			}
		}
		else {	 
			if (res == FR_OK) {					 
				if (dj.obj.attr & 0x10) {		 
					res = FR_NO_FILE;
				} else {
					if ((mode & 0x02) && (dj.obj.attr & 0x01)) {  
						res = FR_DENIED;
					}
				}
			}
		}
		if (res == FR_OK) {
			if (mode & 0x08)		 
				mode |= 0x40;
			fp->dir_sect = fs->winsect;			 
			fp->dir_ptr = dj.dir;

			fp->obj.lockid = inc_lock(&dj, (mode & ~0x01) ? 1 : 0);
			if (!fp->obj.lockid) res = FR_INT_ERR;

		}
#line 3443 "../Middlewares/Third_Party/FatFs/src/ff.c"

		if (res == FR_OK) {

			if (fs->fs_type == 4) {
				fp->obj.c_scl = dj.obj.sclust;							 
				fp->obj.c_size = ((DWORD)dj.obj.objsize & 0xFFFFFF00) | dj.obj.stat;
				fp->obj.c_ofs = dj.blk_ofs;
				fp->obj.sclust = ld_dword(fs->dirbuf + 52);	 
				fp->obj.objsize = ld_qword(fs->dirbuf + 56);
				fp->obj.stat = fs->dirbuf[33] & 2;
			} else

			{
				fp->obj.sclust = ld_clust(fs, dj.dir);					 
				fp->obj.objsize = ld_dword(dj.dir + 28);
			}

			fp->cltbl = 0;			 

			fp->obj.fs = fs;	 	 
			fp->obj.id = fs->id;
			fp->flag = mode;		 
			fp->err = 0;			 
			fp->sect = 0;			 
			fp->fptr = 0;			 


			mem_set(fp->buf, 0, 512);	 

			if ((mode & 0x20) && fp->obj.objsize > 0) {	 
				fp->fptr = fp->obj.objsize;			 
				bcs = (DWORD)fs->csize * ((UINT)512);	 
				clst = fp->obj.sclust;				 
				for (ofs = fp->obj.objsize; res == FR_OK && ofs > bcs; ofs -= bcs) {
					clst = get_fat(&fp->obj, clst);
					if (clst <= 1) res = FR_INT_ERR;
					if (clst == 0xFFFFFFFF) res = FR_DISK_ERR;
				}
				fp->clust = clst;
				if (res == FR_OK && ofs % ((UINT)512)) {	 
					if ((sc = clust2sect(fs, clst)) == 0) {
						res = FR_INT_ERR;
					} else {
						fp->sect = sc + (DWORD)(ofs / ((UINT)512));

						if (disk_read(fs->drv, fp->buf, fp->sect, 1) != RES_OK) res = FR_DISK_ERR;

					}
				}
			}

		}

		;
	}

	if (res != FR_OK) fp->obj.fs = 0;	 

	{ unlock_fs(fs, res); return res; };
}




 
 
 

FRESULT f_read (
	FIL* fp, 	 
	void* buff,	 
	UINT btr,	 
	UINT* br	 
)
{
	FRESULT res;
	FATFS *fs;
	DWORD clst, sect;
	FSIZE_t remain;
	UINT rcnt, cc, csect;
	BYTE *rbuff = (BYTE*)buff;


	*br = 0;	 
	res = validate(&fp->obj, &fs);				 
	if (res != FR_OK || (res = (FRESULT)fp->err) != FR_OK) { unlock_fs(fs, res); return res; };	 
	if (!(fp->flag & 0x01)) { unlock_fs(fs, FR_DENIED); return FR_DENIED; };  
	remain = fp->obj.objsize - fp->fptr;
	if (btr > remain) btr = (UINT)remain;		 

	for ( ;  btr;								 
		rbuff += rcnt, fp->fptr += rcnt, *br += rcnt, btr -= rcnt) {
		if (fp->fptr % ((UINT)512) == 0) {			 
			csect = (UINT)(fp->fptr / ((UINT)512) & (fs->csize - 1));	 
			if (csect == 0) {					 
				if (fp->fptr == 0) {			 
					clst = fp->obj.sclust;		 
				} else {						 

					if (fp->cltbl) {
						clst = clmt_clust(fp, fp->fptr);	 
					} else

					{
						clst = get_fat(&fp->obj, fp->clust);	 
					}
				}
				if (clst < 2) { fp->err = (BYTE)(FR_INT_ERR); { unlock_fs(fs, FR_INT_ERR); return FR_INT_ERR; }; };
				if (clst == 0xFFFFFFFF) { fp->err = (BYTE)(FR_DISK_ERR); { unlock_fs(fs, FR_DISK_ERR); return FR_DISK_ERR; }; };
				fp->clust = clst;				 
			}
			sect = clust2sect(fs, fp->clust);	 
			if (!sect) { fp->err = (BYTE)(FR_INT_ERR); { unlock_fs(fs, FR_INT_ERR); return FR_INT_ERR; }; };
			sect += csect;
			cc = btr / ((UINT)512);					 
			if (cc) {							 
				if (csect + cc > fs->csize) {	 
					cc = fs->csize - csect;
				}
				if (disk_read(fs->drv, rbuff, sect, cc) != RES_OK) { fp->err = (BYTE)(FR_DISK_ERR); { unlock_fs(fs, FR_DISK_ERR); return FR_DISK_ERR; }; };
#line 3569 "../Middlewares/Third_Party/FatFs/src/ff.c"
				if ((fp->flag & 0x80) && fp->sect - sect < cc) {
					mem_cpy(rbuff + ((fp->sect - sect) * ((UINT)512)), fp->buf, ((UINT)512));
				}


				rcnt = ((UINT)512) * cc;				 
				continue;
			}

			if (fp->sect != sect) {			 

				if (fp->flag & 0x80) {		 
					if (disk_write(fs->drv, fp->buf, fp->sect, 1) != RES_OK) { fp->err = (BYTE)(FR_DISK_ERR); { unlock_fs(fs, FR_DISK_ERR); return FR_DISK_ERR; }; };
					fp->flag &= (BYTE)~0x80;
				}

				if (disk_read(fs->drv, fp->buf, sect, 1) != RES_OK)	{ fp->err = (BYTE)(FR_DISK_ERR); { unlock_fs(fs, FR_DISK_ERR); return FR_DISK_ERR; }; };	 
			}

			fp->sect = sect;
		}
		rcnt = ((UINT)512) - (UINT)fp->fptr % ((UINT)512);	 
		if (rcnt > btr) rcnt = btr;					 




		mem_cpy(rbuff, fp->buf + fp->fptr % ((UINT)512), rcnt);	 

	}

	{ unlock_fs(fs, FR_OK); return FR_OK; };
}





 
 
 

FRESULT f_write (
	FIL* fp,			 
	const void* buff,	 
	UINT btw,			 
	UINT* bw			 
)
{
	FRESULT res;
	FATFS *fs;
	DWORD clst, sect;
	UINT wcnt, cc, csect;
	const BYTE *wbuff = (const BYTE*)buff;


	*bw = 0;	 
	res = validate(&fp->obj, &fs);			 
	if (res != FR_OK || (res = (FRESULT)fp->err) != FR_OK) { unlock_fs(fs, res); return res; };	 
	if (!(fp->flag & 0x02)) { unlock_fs(fs, FR_DENIED); return FR_DENIED; };	 

	 
	if ((!1 || fs->fs_type != 4) && (DWORD)(fp->fptr + btw) < (DWORD)fp->fptr) {
		btw = (UINT)(0xFFFFFFFF - (DWORD)fp->fptr);
	}

	for ( ;  btw;							 
		wbuff += wcnt, fp->fptr += wcnt, fp->obj.objsize = (fp->fptr > fp->obj.objsize) ? fp->fptr : fp->obj.objsize, *bw += wcnt, btw -= wcnt) {
		if (fp->fptr % ((UINT)512) == 0) {		 
			csect = (UINT)(fp->fptr / ((UINT)512)) & (fs->csize - 1);	 
			if (csect == 0) {				 
				if (fp->fptr == 0) {		 
					clst = fp->obj.sclust;	 
					if (clst == 0) {		 
						clst = create_chain(&fp->obj, 0);	 
					}
				} else {					 

					if (fp->cltbl) {
						clst = clmt_clust(fp, fp->fptr);	 
					} else

					{
						clst = create_chain(&fp->obj, fp->clust);	 
					}
				}
				if (clst == 0) break;		 
				if (clst == 1) { fp->err = (BYTE)(FR_INT_ERR); { unlock_fs(fs, FR_INT_ERR); return FR_INT_ERR; }; };
				if (clst == 0xFFFFFFFF) { fp->err = (BYTE)(FR_DISK_ERR); { unlock_fs(fs, FR_DISK_ERR); return FR_DISK_ERR; }; };
				fp->clust = clst;			 
				if (fp->obj.sclust == 0) fp->obj.sclust = clst;	 
			}



			if (fp->flag & 0x80) {		 
				if (disk_write(fs->drv, fp->buf, fp->sect, 1) != RES_OK) { fp->err = (BYTE)(FR_DISK_ERR); { unlock_fs(fs, FR_DISK_ERR); return FR_DISK_ERR; }; };
				fp->flag &= (BYTE)~0x80;
			}

			sect = clust2sect(fs, fp->clust);	 
			if (!sect) { fp->err = (BYTE)(FR_INT_ERR); { unlock_fs(fs, FR_INT_ERR); return FR_INT_ERR; }; };
			sect += csect;
			cc = btw / ((UINT)512);				 
			if (cc) {						 
				if (csect + cc > fs->csize) {	 
					cc = fs->csize - csect;
				}
				if (disk_write(fs->drv, wbuff, sect, cc) != RES_OK) { fp->err = (BYTE)(FR_DISK_ERR); { unlock_fs(fs, FR_DISK_ERR); return FR_DISK_ERR; }; };
#line 3685 "../Middlewares/Third_Party/FatFs/src/ff.c"
				if (fp->sect - sect < cc) {  
					mem_cpy(fp->buf, wbuff + ((fp->sect - sect) * ((UINT)512)), ((UINT)512));
					fp->flag &= (BYTE)~0x80;
				}


				wcnt = ((UINT)512) * cc;		 
				continue;
			}
#line 3700 "../Middlewares/Third_Party/FatFs/src/ff.c"
			if (fp->sect != sect && 		 
				fp->fptr < fp->obj.objsize &&
				disk_read(fs->drv, fp->buf, sect, 1) != RES_OK) {
					{ fp->err = (BYTE)(FR_DISK_ERR); { unlock_fs(fs, FR_DISK_ERR); return FR_DISK_ERR; }; };
			}

			fp->sect = sect;
		}
		wcnt = ((UINT)512) - (UINT)fp->fptr % ((UINT)512);	 
		if (wcnt > btw) wcnt = btw;					 





		mem_cpy(fp->buf + fp->fptr % ((UINT)512), wbuff, wcnt);	 
		fp->flag |= 0x80;

	}

	fp->flag |= 0x40;				 

	{ unlock_fs(fs, FR_OK); return FR_OK; };
}




 
 
 

FRESULT f_sync (
	FIL* fp		 
)
{
	FRESULT res;
	FATFS *fs;
	DWORD tm;
	BYTE *dir;

	DIR dj;
	WCHAR lbuf[255+1]; BYTE dbuf[((255 + 44U) / 15 * 32)];


	res = validate(&fp->obj, &fs);	 
	if (res == FR_OK) {
		if (fp->flag & 0x40) {	 

			if (fp->flag & 0x80) {	 
				if (disk_write(fs->drv, fp->buf, fp->sect, 1) != RES_OK) { unlock_fs(fs, FR_DISK_ERR); return FR_DISK_ERR; };
				fp->flag &= (BYTE)~0x80;
			}

			 
			tm = get_fattime();				 

			if (fs->fs_type == 4) {
				res = fill_first_frag(&fp->obj);	 
				if (res == FR_OK) {
					res = fill_last_frag(&fp->obj, fp->clust, 0xFFFFFFFF);	 
				}
				if (res == FR_OK) {
					{ (fs)->lfnbuf = lbuf; (fs)->dirbuf = dbuf; };
					res = load_obj_dir(&dj, &fp->obj);	 
					if (res == FR_OK) {
						fs->dirbuf[4] |= 0x20;				 
						fs->dirbuf[33] = fp->obj.stat | 1;	 
						st_dword(fs->dirbuf + 52, fp->obj.sclust);
						st_qword(fs->dirbuf + 56, fp->obj.objsize);
						st_qword(fs->dirbuf + 40, fp->obj.objsize);
						st_dword(fs->dirbuf + 12, tm);		 
						fs->dirbuf[21] = 0;
						st_dword(fs->dirbuf + 16, 0);
						res = store_xdir(&dj);	 
						if (res == FR_OK) {
							res = sync_fs(fs);
							fp->flag &= (BYTE)~0x40;
						}
					}
					;
				}
			} else

			{
				res = move_window(fs, fp->dir_sect);
				if (res == FR_OK) {
					dir = fp->dir_ptr;
					dir[11] |= 0x20;						 
					st_clust(fp->obj.fs, dir, fp->obj.sclust);		 
					st_dword(dir + 28, (DWORD)fp->obj.objsize);	 
					st_dword(dir + 22, tm);				 
					st_word(dir + 18, 0);
					fs->wflag = 1;
					res = sync_fs(fs);					 
					fp->flag &= (BYTE)~0x40;
				}
			}
		}
	}

	{ unlock_fs(fs, res); return res; };
}






 
 
 

FRESULT f_close (
	FIL* fp		 
)
{
	FRESULT res;
	FATFS *fs;


	res = f_sync(fp);					 
	if (res == FR_OK)

	{
		res = validate(&fp->obj, &fs);	 
		if (res == FR_OK) {

			res = dec_lock(fp->obj.lockid);	 
			if (res == FR_OK)

			{
				fp->obj.fs = 0;			 
			}

			unlock_fs(fs, FR_OK);		 

		}
	}
	return res;
}




#line 3993 "../Middlewares/Third_Party/FatFs/src/ff.c"




 
 
 

FRESULT f_lseek (
	FIL* fp,		 
	FSIZE_t ofs		 
)
{
	FRESULT res;
	FATFS *fs;
	DWORD clst, bcs, nsect;
	FSIZE_t ifptr;

	DWORD cl, pcl, ncl, tcl, dsc, tlen, ulen, *tbl;


	res = validate(&fp->obj, &fs);		 
	if (res == FR_OK) res = (FRESULT)fp->err;

	if (res == FR_OK && fs->fs_type == 4) {
		res = fill_last_frag(&fp->obj, fp->clust, 0xFFFFFFFF);	 
	}

	if (res != FR_OK) { unlock_fs(fs, res); return res; };


	if (fp->cltbl) {	 
		if (ofs == ((FSIZE_t)0 - 1)) {	 
			tbl = fp->cltbl;
			tlen = *tbl++; ulen = 2;	 
			cl = fp->obj.sclust;		 
			if (cl) {
				do {
					 
					tcl = cl; ncl = 0; ulen += 2;	 
					do {
						pcl = cl; ncl++;
						cl = get_fat(&fp->obj, cl);
						if (cl <= 1) { fp->err = (BYTE)(FR_INT_ERR); { unlock_fs(fs, FR_INT_ERR); return FR_INT_ERR; }; };
						if (cl == 0xFFFFFFFF) { fp->err = (BYTE)(FR_DISK_ERR); { unlock_fs(fs, FR_DISK_ERR); return FR_DISK_ERR; }; };
					} while (cl == pcl + 1);
					if (ulen <= tlen) {		 
						*tbl++ = ncl; *tbl++ = tcl;
					}
				} while (cl < fs->n_fatent);	 
			}
			*fp->cltbl = ulen;	 
			if (ulen <= tlen) {
				*tbl = 0;		 
			} else {
				res = FR_NOT_ENOUGH_CORE;	 
			}
		} else {						 
			if (ofs > fp->obj.objsize) ofs = fp->obj.objsize;	 
			fp->fptr = ofs;				 
			if (ofs) {
				fp->clust = clmt_clust(fp, ofs - 1);
				dsc = clust2sect(fs, fp->clust);
				if (!dsc) { fp->err = (BYTE)(FR_INT_ERR); { unlock_fs(fs, FR_INT_ERR); return FR_INT_ERR; }; };
				dsc += (DWORD)((ofs - 1) / ((UINT)512)) & (fs->csize - 1);
				if (fp->fptr % ((UINT)512) && dsc != fp->sect) {	 


					if (fp->flag & 0x80) {		 
						if (disk_write(fs->drv, fp->buf, fp->sect, 1) != RES_OK) { fp->err = (BYTE)(FR_DISK_ERR); { unlock_fs(fs, FR_DISK_ERR); return FR_DISK_ERR; }; };
						fp->flag &= (BYTE)~0x80;
					}

					if (disk_read(fs->drv, fp->buf, dsc, 1) != RES_OK) { fp->err = (BYTE)(FR_DISK_ERR); { unlock_fs(fs, FR_DISK_ERR); return FR_DISK_ERR; }; };	 

					fp->sect = dsc;
				}
			}
		}
	} else


	 
	{

		if (fs->fs_type != 4 && ofs >= 0x100000000) ofs = 0xFFFFFFFF;	 

		if (ofs > fp->obj.objsize && (0 || !(fp->flag & 0x02))) {	 
			ofs = fp->obj.objsize;
		}
		ifptr = fp->fptr;
		fp->fptr = nsect = 0;
		if (ofs) {
			bcs = (DWORD)fs->csize * ((UINT)512);	 
			if (ifptr > 0 &&
				(ofs - 1) / bcs >= (ifptr - 1) / bcs) {	 
				fp->fptr = (ifptr - 1) & ~(FSIZE_t)(bcs - 1);	 
				ofs -= fp->fptr;
				clst = fp->clust;
			} else {									 
				clst = fp->obj.sclust;					 

				if (clst == 0) {						 
					clst = create_chain(&fp->obj, 0);
					if (clst == 1) { fp->err = (BYTE)(FR_INT_ERR); { unlock_fs(fs, FR_INT_ERR); return FR_INT_ERR; }; };
					if (clst == 0xFFFFFFFF) { fp->err = (BYTE)(FR_DISK_ERR); { unlock_fs(fs, FR_DISK_ERR); return FR_DISK_ERR; }; };
					fp->obj.sclust = clst;
				}

				fp->clust = clst;
			}
			if (clst != 0) {
				while (ofs > bcs) {						 
					ofs -= bcs; fp->fptr += bcs;

					if (fp->flag & 0x02) {			 
						if (1 && fp->fptr > fp->obj.objsize) {	 
							fp->obj.objsize = fp->fptr;
							fp->flag |= 0x40;
						}
						clst = create_chain(&fp->obj, clst);	 
						if (clst == 0) {				 
							ofs = 0; break;
						}
					} else

					{
						clst = get_fat(&fp->obj, clst);	 
					}
					if (clst == 0xFFFFFFFF) { fp->err = (BYTE)(FR_DISK_ERR); { unlock_fs(fs, FR_DISK_ERR); return FR_DISK_ERR; }; };
					if (clst <= 1 || clst >= fs->n_fatent) { fp->err = (BYTE)(FR_INT_ERR); { unlock_fs(fs, FR_INT_ERR); return FR_INT_ERR; }; };
					fp->clust = clst;
				}
				fp->fptr += ofs;
				if (ofs % ((UINT)512)) {
					nsect = clust2sect(fs, clst);	 
					if (!nsect) { fp->err = (BYTE)(FR_INT_ERR); { unlock_fs(fs, FR_INT_ERR); return FR_INT_ERR; }; };
					nsect += (DWORD)(ofs / ((UINT)512));
				}
			}
		}
		if (!0 && fp->fptr > fp->obj.objsize) {		 
			fp->obj.objsize = fp->fptr;
			fp->flag |= 0x40;
		}
		if (fp->fptr % ((UINT)512) && nsect != fp->sect) {	 


			if (fp->flag & 0x80) {			 
				if (disk_write(fs->drv, fp->buf, fp->sect, 1) != RES_OK) { fp->err = (BYTE)(FR_DISK_ERR); { unlock_fs(fs, FR_DISK_ERR); return FR_DISK_ERR; }; };
				fp->flag &= (BYTE)~0x80;
			}

			if (disk_read(fs->drv, fp->buf, nsect, 1) != RES_OK) { fp->err = (BYTE)(FR_DISK_ERR); { unlock_fs(fs, FR_DISK_ERR); return FR_DISK_ERR; }; };	 

			fp->sect = nsect;
		}
	}

	{ unlock_fs(fs, res); return res; };
}




 
 
 

FRESULT f_opendir (
	DIR* dp,			 
	const TCHAR* path	 
)
{
	FRESULT res;
	FATFS *fs;
	_FDID *obj;
	WCHAR lbuf[255+1]; BYTE dbuf[((255 + 44U) / 15 * 32)];


	if (!dp) return FR_INVALID_OBJECT;

	 
	obj = &dp->obj;
	res = find_volume(&path, &fs, 0);
	if (res == FR_OK) {
		obj->fs = fs;
		{ (fs)->lfnbuf = lbuf; (fs)->dirbuf = dbuf; };
		res = follow_path(dp, path);			 
		if (res == FR_OK) {						 
			if (!(dp->fn[11] & 0x80)) {	 
				if (obj->attr & 0x10) {		 

					if (fs->fs_type == 4) {
						obj->c_scl = obj->sclust;							 
						obj->c_size = ((DWORD)obj->objsize & 0xFFFFFF00) | obj->stat;
						obj->c_ofs = dp->blk_ofs;
						obj->sclust = ld_dword(fs->dirbuf + 52);	 
						obj->objsize = ld_qword(fs->dirbuf + 56);
						obj->stat = fs->dirbuf[33] & 2;
					} else

					{
						obj->sclust = ld_clust(fs, dp->dir);	 
					}
				} else {						 
					res = FR_NO_PATH;
				}
			}
			if (res == FR_OK) {
				obj->id = fs->id;
				res = dir_sdi(dp, 0);			 

				if (res == FR_OK) {
					if (obj->sclust) {
						obj->lockid = inc_lock(dp, 0);	 
						if (!obj->lockid) res = FR_TOO_MANY_OPEN_FILES;
					} else {
						obj->lockid = 0;	 
					}
				}

			}
		}
		;
		if (res == FR_NO_FILE) res = FR_NO_PATH;
	}
	if (res != FR_OK) obj->fs = 0;		 

	{ unlock_fs(fs, res); return res; };
}




 
 
 

FRESULT f_closedir (
	DIR *dp		 
)
{
	FRESULT res;
	FATFS *fs;


	res = validate(&dp->obj, &fs);			 
	if (res == FR_OK) {

		if (dp->obj.lockid) {				 
			res = dec_lock(dp->obj.lockid);
		}
		if (res == FR_OK)

		{
			dp->obj.fs = 0;			 
		}

		unlock_fs(fs, FR_OK);		 

	}
	return res;
}




 
 
 

FRESULT f_readdir (
	DIR* dp,			 
	FILINFO* fno		 
)
{
	FRESULT res;
	FATFS *fs;
	WCHAR lbuf[255+1]; BYTE dbuf[((255 + 44U) / 15 * 32)];


	res = validate(&dp->obj, &fs);	 
	if (res == FR_OK) {
		if (!fno) {
			res = dir_sdi(dp, 0);			 
		} else {
			{ (fs)->lfnbuf = lbuf; (fs)->dirbuf = dbuf; };
			res = dir_read(dp, 0);			 
			if (res == FR_NO_FILE) res = FR_OK;	 
			if (res == FR_OK) {				 
				get_fileinfo(dp, fno);		 
				res = dir_next(dp, 0);		 
				if (res == FR_NO_FILE) res = FR_OK;	 
			}
			;
		}
	}
	{ unlock_fs(fs, res); return res; };
}




 
 
 

FRESULT f_findnext (
	DIR* dp,		 
	FILINFO* fno	 
)
{
	FRESULT res;


	for (;;) {
		res = f_readdir(dp, fno);		 
		if (res != FR_OK || !fno || !fno->fname[0]) break;	 
		if (pattern_matching(dp->pat, fno->fname, 0, 0)) break;		 



	}
	return res;
}



 
 
 

FRESULT f_findfirst (
	DIR* dp,				 
	FILINFO* fno,			 
	const TCHAR* path,		 
	const TCHAR* pattern	 
)
{
	FRESULT res;


	dp->pat = pattern;		 
	res = f_opendir(dp, path);		 
	if (res == FR_OK) {
		res = f_findnext(dp, fno);	 
	}
	return res;
}






 
 
 

FRESULT f_stat (
	const TCHAR* path,	 
	FILINFO* fno		 
)
{
	FRESULT res;
	DIR dj;
	WCHAR lbuf[255+1]; BYTE dbuf[((255 + 44U) / 15 * 32)];


	 
	res = find_volume(&path, &dj.obj.fs, 0);
	if (res == FR_OK) {
		{ (dj . obj . fs)->lfnbuf = lbuf; (dj . obj . fs)->dirbuf = dbuf; };
		res = follow_path(&dj, path);	 
		if (res == FR_OK) {				 
			if (dj.fn[11] & 0x80) {	 
				res = FR_INVALID_NAME;
			} else {							 
				if (fno) get_fileinfo(&dj, fno);
			}
		}
		;
	}

	{ unlock_fs(dj . obj . fs, res); return res; };
}




 
 
 

FRESULT f_getfree (
	const TCHAR* path,	 
	DWORD* nclst,		 
	FATFS** fatfs		 
)
{
	FRESULT res;
	FATFS *fs;
	DWORD nfree, clst, sect, stat;
	UINT i;
	BYTE *p;
	_FDID obj;


	 
	res = find_volume(&path, &fs, 0);
	if (res == FR_OK) {
		*fatfs = fs;				 
		 
		if (fs->free_clst <= fs->n_fatent - 2) {
			*nclst = fs->free_clst;
		} else {
			 
			nfree = 0;
			if (fs->fs_type == 1) {	 
				clst = 2; obj.fs = fs;
				do {
					stat = get_fat(&obj, clst);
					if (stat == 0xFFFFFFFF) { res = FR_DISK_ERR; break; }
					if (stat == 1) { res = FR_INT_ERR; break; }
					if (stat == 0) nfree++;
				} while (++clst < fs->n_fatent);
			} else {

				if (fs->fs_type == 4) {	 
					BYTE bm;
					UINT b;

					clst = fs->n_fatent - 2;
					sect = fs->database;
					i = 0;
					do {
						if (i == 0 && (res = move_window(fs, sect++)) != FR_OK) break;
						for (b = 8, bm = fs->win[i]; b && clst; b--, clst--) {
							if (!(bm & 1)) nfree++;
							bm >>= 1;
						}
						i = (i + 1) % ((UINT)512);
					} while (clst);
				} else

				{	 
					clst = fs->n_fatent; sect = fs->fatbase;
					i = 0; p = 0;
					do {
						if (i == 0) {
							res = move_window(fs, sect++);
							if (res != FR_OK) break;
							p = fs->win;
							i = ((UINT)512);
						}
						if (fs->fs_type == 2) {
							if (ld_word(p) == 0) nfree++;
							p += 2; i -= 2;
						} else {
							if ((ld_dword(p) & 0x0FFFFFFF) == 0) nfree++;
							p += 4; i -= 4;
						}
					} while (--clst);
				}
			}
			*nclst = nfree;			 
			fs->free_clst = nfree;	 
			fs->fsi_flag |= 1;		 
		}
	}

	{ unlock_fs(fs, res); return res; };
}




 
 
 

FRESULT f_truncate (
	FIL* fp		 
)
{
	FRESULT res;
	FATFS *fs;
	DWORD ncl;


	res = validate(&fp->obj, &fs);	 
	if (res != FR_OK || (res = (FRESULT)fp->err) != FR_OK) { unlock_fs(fs, res); return res; };
	if (!(fp->flag & 0x02)) { unlock_fs(fs, FR_DENIED); return FR_DENIED; };	 

	if (fp->fptr < fp->obj.objsize) {	 
		if (fp->fptr == 0) {	 
			res = remove_chain(&fp->obj, fp->obj.sclust, 0);
			fp->obj.sclust = 0;
		} else {				 
			ncl = get_fat(&fp->obj, fp->clust);
			res = FR_OK;
			if (ncl == 0xFFFFFFFF) res = FR_DISK_ERR;
			if (ncl == 1) res = FR_INT_ERR;
			if (res == FR_OK && ncl < fs->n_fatent) {
				res = remove_chain(&fp->obj, ncl, fp->clust);
			}
		}
		fp->obj.objsize = fp->fptr;	 
		fp->flag |= 0x40;

		if (res == FR_OK && (fp->flag & 0x80)) {
			if (disk_write(fs->drv, fp->buf, fp->sect, 1) != RES_OK) {
				res = FR_DISK_ERR;
			} else {
				fp->flag &= (BYTE)~0x80;
			}
		}

		if (res != FR_OK) { fp->err = (BYTE)(res); { unlock_fs(fs, res); return res; }; };
	}

	{ unlock_fs(fs, res); return res; };
}




 
 
 

FRESULT f_unlink (
	const TCHAR* path		 
)
{
	FRESULT res;
	DIR dj, sdj;
	DWORD dclst = 0;
	FATFS *fs;

	_FDID obj;

	WCHAR lbuf[255+1]; BYTE dbuf[((255 + 44U) / 15 * 32)];


	 
	res = find_volume(&path, &fs, 0x02);
	dj.obj.fs = fs;
	if (res == FR_OK) {
		{ (fs)->lfnbuf = lbuf; (fs)->dirbuf = dbuf; };
		res = follow_path(&dj, path);		 
		if (0 && res == FR_OK && (dj.fn[11] & 0x20)) {
			res = FR_INVALID_NAME;			 
		}

		if (res == FR_OK) res = chk_lock(&dj, 2);	 

		if (res == FR_OK) {					 
			if (dj.fn[11] & 0x80) {
				res = FR_INVALID_NAME;		 
			} else {
				if (dj.obj.attr & 0x01) {
					res = FR_DENIED;		 
				}
			}
			if (res == FR_OK) {

				obj.fs = fs;
				if (fs->fs_type == 4) {
					obj.sclust = dclst = ld_dword(fs->dirbuf + 52);
					obj.objsize = ld_qword(fs->dirbuf + 56);
					obj.stat = fs->dirbuf[33] & 2;
				} else

				{
					dclst = ld_clust(fs, dj.dir);
				}
				if (dj.obj.attr & 0x10) {			 





					{
						sdj.obj.fs = fs;						 
						sdj.obj.sclust = dclst;

						if (fs->fs_type == 4) {
							sdj.obj.objsize = obj.objsize;
							sdj.obj.stat = obj.stat;
						}

						res = dir_sdi(&sdj, 0);
						if (res == FR_OK) {
							res = dir_read(&sdj, 0);			 
							if (res == FR_OK) res = FR_DENIED;	 
							if (res == FR_NO_FILE) res = FR_OK;	 
						}
					}
				}
			}
			if (res == FR_OK) {
				res = dir_remove(&dj);			 
				if (res == FR_OK && dclst) {	 

					res = remove_chain(&obj, dclst, 0);



				}
				if (res == FR_OK) res = sync_fs(fs);
			}
		}
		;
	}

	{ unlock_fs(fs, res); return res; };
}




 
 
 

FRESULT f_mkdir (
	const TCHAR* path		 
)
{
	FRESULT res;
	DIR dj;
	FATFS *fs;
	BYTE *dir;
	UINT n;
	DWORD dsc, dcl, pcl, tm;
	WCHAR lbuf[255+1]; BYTE dbuf[((255 + 44U) / 15 * 32)];


	 
	res = find_volume(&path, &fs, 0x02);
	dj.obj.fs = fs;
	if (res == FR_OK) {
		{ (fs)->lfnbuf = lbuf; (fs)->dirbuf = dbuf; };
		res = follow_path(&dj, path);			 
		if (res == FR_OK) res = FR_EXIST;		 
		if (0 && res == FR_NO_FILE && (dj.fn[11] & 0x20)) {
			res = FR_INVALID_NAME;
		}
		if (res == FR_NO_FILE) {				 
			dcl = create_chain(&dj.obj, 0);		 
			dj.obj.objsize = (DWORD)fs->csize * ((UINT)512);
			res = FR_OK;
			if (dcl == 0) res = FR_DENIED;		 
			if (dcl == 1) res = FR_INT_ERR;
			if (dcl == 0xFFFFFFFF) res = FR_DISK_ERR;
			if (res == FR_OK) res = sync_window(fs);	 
			tm = get_fattime();
			if (res == FR_OK) {					 
				dsc = clust2sect(fs, dcl);
				dir = fs->win;
				mem_set(dir, 0, ((UINT)512));
				if (!1 || fs->fs_type != 4) {
					mem_set(dir + 0, ' ', 11);	 
					dir[0] = '.';
					dir[11] = 0x10;
					st_dword(dir + 22, tm);
					st_clust(fs, dir, dcl);
					mem_cpy(dir + 32, dir, 32); 	 
					dir[32 + 1] = '.'; pcl = dj.obj.sclust;
					if (fs->fs_type == 3 && pcl == fs->dirbase) pcl = 0;
					st_clust(fs, dir + 32, pcl);
				}
				for (n = fs->csize; n; n--) {	 
					fs->winsect = dsc++;
					fs->wflag = 1;
					res = sync_window(fs);
					if (res != FR_OK) break;
					mem_set(dir, 0, ((UINT)512));
				}
			}
			if (res == FR_OK) {
				res = dir_register(&dj);	 
			}
			if (res == FR_OK) {

				if (fs->fs_type == 4) {	 
					st_dword(fs->dirbuf + 12, tm);	 
					st_dword(fs->dirbuf + 52, dcl);	 
					st_dword(fs->dirbuf + 56, (DWORD)dj.obj.objsize);	 
					st_dword(fs->dirbuf + 40, (DWORD)dj.obj.objsize);
					fs->dirbuf[33] = 3;				 
					fs->dirbuf[4] = 0x10;				 
					res = store_xdir(&dj);
				} else

				{
					dir = dj.dir;
					st_dword(dir + 22, tm);	 
					st_clust(fs, dir, dcl);				 
					dir[11] = 0x10;				 
					fs->wflag = 1;
				}
				if (res == FR_OK) {
					res = sync_fs(fs);
				}
			} else {
				remove_chain(&dj.obj, dcl, 0);		 
			}
		}
		;
	}

	{ unlock_fs(fs, res); return res; };
}




 
 
 

FRESULT f_rename (
	const TCHAR* path_old,	 
	const TCHAR* path_new	 
)
{
	FRESULT res;
	DIR djo, djn;
	FATFS *fs;
	BYTE buf[1 ? 32 * 2 : 24], *dir;
	DWORD dw;
	WCHAR lbuf[255+1]; BYTE dbuf[((255 + 44U) / 15 * 32)];


	get_ldnumber(&path_new);						 
	res = find_volume(&path_old, &fs, 0x02);	 
	if (res == FR_OK) {
		djo.obj.fs = fs;
		{ (fs)->lfnbuf = lbuf; (fs)->dirbuf = dbuf; };
		res = follow_path(&djo, path_old);		 
		if (res == FR_OK && (djo.fn[11] & (0x20 | 0x80))) res = FR_INVALID_NAME;	 

		if (res == FR_OK) {
			res = chk_lock(&djo, 2);
		}

		if (res == FR_OK) {						 

			if (fs->fs_type == 4) {	 
				BYTE nf, nn;
				WORD nh;

				mem_cpy(buf, fs->dirbuf, 32 * 2);	 
				mem_cpy(&djn, &djo, sizeof djo);
				res = follow_path(&djn, path_new);		 
				if (res == FR_OK) {						 
					res = (djn.obj.sclust == djo.obj.sclust && djn.dptr == djo.dptr) ? FR_NO_FILE : FR_EXIST;
				}
				if (res == FR_NO_FILE) { 				 
					res = dir_register(&djn);			 
					if (res == FR_OK) {
						nf = fs->dirbuf[1]; nn = fs->dirbuf[35];
						nh = ld_word(fs->dirbuf + 36);
						mem_cpy(fs->dirbuf, buf, 32 * 2);
						fs->dirbuf[1] = nf; fs->dirbuf[35] = nn;
						st_word(fs->dirbuf + 36, nh);
 
						res = store_xdir(&djn);
					}
				}
			} else

			{	 
				mem_cpy(buf, djo.dir + 11, 21);	 
				mem_cpy(&djn, &djo, sizeof (DIR));		 
				res = follow_path(&djn, path_new);		 
				if (res == FR_OK) {						 
					res = (djn.obj.sclust == djo.obj.sclust && djn.dptr == djo.dptr) ? FR_NO_FILE : FR_EXIST;
				}
				if (res == FR_NO_FILE) { 				 
					res = dir_register(&djn);			 
					if (res == FR_OK) {
						dir = djn.dir;					 
						mem_cpy(dir + 13, buf + 2, 19);
						dir[11] = buf[0] | 0x20;
						fs->wflag = 1;
						if ((dir[11] & 0x10) && djo.obj.sclust != djn.obj.sclust) {	 
							dw = clust2sect(fs, ld_clust(fs, dir));
							if (!dw) {
								res = FR_INT_ERR;
							} else {
 
								res = move_window(fs, dw);
								dir = fs->win + 32 * 1;	 
								if (res == FR_OK && dir[1] == '.') {
									st_clust(fs, dir, djn.obj.sclust);
									fs->wflag = 1;
								}
							}
						}
					}
				}
			}
			if (res == FR_OK) {
				res = dir_remove(&djo);		 
				if (res == FR_OK) {
					res = sync_fs(fs);
				}
			}
 
		}
		;
	}

	{ unlock_fs(fs, res); return res; };
}









 
 
 

FRESULT f_chmod (
	const TCHAR* path,	 
	BYTE attr,			 
	BYTE mask			 
)
{
	FRESULT res;
	DIR dj;
	FATFS *fs;
	WCHAR lbuf[255+1]; BYTE dbuf[((255 + 44U) / 15 * 32)];


	res = find_volume(&path, &fs, 0x02);	 
	dj.obj.fs = fs;
	if (res == FR_OK) {
		{ (fs)->lfnbuf = lbuf; (fs)->dirbuf = dbuf; };
		res = follow_path(&dj, path);	 
		if (res == FR_OK && (dj.fn[11] & (0x20 | 0x80))) res = FR_INVALID_NAME;	 
		if (res == FR_OK) {
			mask &= 0x01|0x02|0x04|0x20;	 

			if (fs->fs_type == 4) {
				fs->dirbuf[4] = (attr & mask) | (fs->dirbuf[4] & (BYTE)~mask);	 
				res = store_xdir(&dj);
			} else

			{
				dj.dir[11] = (attr & mask) | (dj.dir[11] & (BYTE)~mask);	 
				fs->wflag = 1;
			}
			if (res == FR_OK) {
				res = sync_fs(fs);
			}
		}
		;
	}

	{ unlock_fs(fs, res); return res; };
}




 
 
 

FRESULT f_utime (
	const TCHAR* path,	 
	const FILINFO* fno	 
)
{
	FRESULT res;
	DIR dj;
	FATFS *fs;
	WCHAR lbuf[255+1]; BYTE dbuf[((255 + 44U) / 15 * 32)];


	res = find_volume(&path, &fs, 0x02);	 
	dj.obj.fs = fs;
	if (res == FR_OK) {
		{ (fs)->lfnbuf = lbuf; (fs)->dirbuf = dbuf; };
		res = follow_path(&dj, path);	 
		if (res == FR_OK && (dj.fn[11] & (0x20 | 0x80))) res = FR_INVALID_NAME;	 
		if (res == FR_OK) {

			if (fs->fs_type == 4) {
				st_dword(fs->dirbuf + 12, (DWORD)fno->fdate << 16 | fno->ftime);
				res = store_xdir(&dj);
			} else

			{
				st_dword(dj.dir + 22, (DWORD)fno->fdate << 16 | fno->ftime);
				fs->wflag = 1;
			}
			if (res == FR_OK) {
				res = sync_fs(fs);
			}
		}
		;
	}

	{ unlock_fs(fs, res); return res; };
}






 
 
 

FRESULT f_getlabel (
	const TCHAR* path,	 
	TCHAR* label,		 
	DWORD* vsn			 
)
{
	FRESULT res;
	DIR dj;
	FATFS *fs;
	UINT si, di;

	WCHAR w;


	 
	res = find_volume(&path, &fs, 0);

	 
	if (res == FR_OK && label) {
		dj.obj.fs = fs; dj.obj.sclust = 0;	 
		res = dir_sdi(&dj, 0);
		if (res == FR_OK) {
		 	res = dir_read(&dj, 1);			 
		 	if (res == FR_OK) {

				if (fs->fs_type == 4) {
					for (si = di = 0; si < dj.dir[1]; si++) {	 
						w = ld_word(dj.dir + 2 + si * 2);



						w = ff_convert(w, 0);	 
						if (w == 0) w = '?';	 
						if (0 && w >= 0x100) label[di++] = (char)(w >> 8);
						label[di++] = (char)w;

					}
					label[di] = 0;
				} else

				{
					si = di = 0;		 
					do {
#line 4969 "../Middlewares/Third_Party/FatFs/src/ff.c"
						label[di++] = dj.dir[si++];

					} while (di < 11);
					do {				 
						label[di] = 0;
						if (di == 0) break;
					} while (label[--di] == ' ');
				}
			}
		}
		if (res == FR_NO_FILE) {	 
			label[0] = 0;
			res = FR_OK;
		}
	}

	 
	if (res == FR_OK && vsn) {
		res = move_window(fs, fs->volbase);
		if (res == FR_OK) {
			switch (fs->fs_type) {
			case 4:
				di = 100; break;

			case 3:
				di = 67; break;

			default:
				di = 39;
			}
			*vsn = ld_dword(fs->win + di);
		}
	}

	{ unlock_fs(fs, res); return res; };
}




 
 
 

FRESULT f_setlabel (
	const TCHAR* label	 
)
{
	FRESULT res;
	DIR dj;
	FATFS *fs;
	BYTE dirvn[22];
	UINT i, j, slen;
	WCHAR w;
	static const char badchr[] = "\"*+,.:;<=>\?[]|\x7F";


	 
	res = find_volume(&label, &fs, 0x02);
	if (res != FR_OK) { unlock_fs(fs, res); return res; };
	dj.obj.fs = fs;

	 
	for (slen = 0; (UINT)label[slen] >= ' '; slen++) ;	 


	if (fs->fs_type == 4) {	 
		for (i = j = 0; i < slen; ) {	 
			w = label[i++];

			if (0) {
				w = (i < slen && 0) ? w << 8 | (BYTE)label[i++] : 0;
			}
			w = ff_convert(w, 1);

			if (w == 0 || chk_chr(badchr, w) || j == 22) {	 
				{ unlock_fs(fs, FR_INVALID_NAME); return FR_INVALID_NAME; };
			}
			st_word(dirvn + j, w); j += 2;
		}
		slen = j;
	} else

	{	 
		for ( ; slen && label[slen - 1] == ' '; slen--) ;	 
		if (slen) {		 
			dirvn[0] = 0; i = j = 0;	 
			do {



				w = (BYTE)label[i++];
				if (0) {
					w = (j < 10 && i < slen && 0) ? w << 8 | (BYTE)label[i++] : 0;
				}

				w = ff_convert(ff_wtoupper(ff_convert(w, 1)), 0);
#line 5075 "../Middlewares/Third_Party/FatFs/src/ff.c"
				if (w == 0 || chk_chr(badchr, w) || j >= (UINT)((w >= 0x100) ? 10 : 11)) {	 
					{ unlock_fs(fs, FR_INVALID_NAME); return FR_INVALID_NAME; };
				}
				if (w >= 0x100) dirvn[j++] = (BYTE)(w >> 8);
				dirvn[j++] = (BYTE)w;
			} while (i < slen);
			while (j < 11) dirvn[j++] = ' ';	 
			if (dirvn[0] == 0xE5) { unlock_fs(fs, FR_INVALID_NAME); return FR_INVALID_NAME; };	 
		}
	}

	 
	dj.obj.sclust = 0;		 
	res = dir_sdi(&dj, 0);
	if (res == FR_OK) {
		res = dir_read(&dj, 1);	 
		if (res == FR_OK) {
			if (1 && fs->fs_type == 4) {
				dj.dir[1] = (BYTE)(slen / 2);	 
				mem_cpy(dj.dir + 2, dirvn, slen);
			} else {
				if (slen) {
					mem_cpy(dj.dir, dirvn, 11);	 
				} else {
					dj.dir[0] = 0xE5;	 
				}
			}
			fs->wflag = 1;
			res = sync_fs(fs);
		} else {			 
			if (res == FR_NO_FILE) {
				res = FR_OK;
				if (slen) {	 
					res = dir_alloc(&dj, 1);	 
					if (res == FR_OK) {
						mem_set(dj.dir, 0, 32);	 
						if (1 && fs->fs_type == 4) {
							dj.dir[0] = 0x83;		 
							dj.dir[1] = (BYTE)(slen / 2);
							mem_cpy(dj.dir + 2, dirvn, slen);
						} else {
							dj.dir[11] = 0x08;		 
							mem_cpy(dj.dir, dirvn, 11);
						}
						fs->wflag = 1;
						res = sync_fs(fs);
					}
				}
			}
		}
	}

	{ unlock_fs(fs, res); return res; };
}







 
 
 

FRESULT f_expand (
	FIL* fp,		 
	FSIZE_t fsz,	 
	BYTE opt		 
)
{
	FRESULT res;
	FATFS *fs;
	DWORD n, clst, stcl, scl, ncl, tcl, lclst;


	res = validate(&fp->obj, &fs);		 
	if (res != FR_OK || (res = (FRESULT)fp->err) != FR_OK) { unlock_fs(fs, res); return res; };
	if (fsz == 0 || fp->obj.objsize != 0 || !(fp->flag & 0x02)) { unlock_fs(fs, FR_DENIED); return FR_DENIED; };

	if (fs->fs_type != 4 && fsz >= 0x100000000) { unlock_fs(fs, FR_DENIED); return FR_DENIED; };	 

	n = (DWORD)fs->csize * ((UINT)512);	 
	tcl = (DWORD)(fsz / n) + ((fsz & (n - 1)) ? 1 : 0);	 
	stcl = fs->last_clst; lclst = 0;
	if (stcl < 2 || stcl >= fs->n_fatent) stcl = 2;


	if (fs->fs_type == 4) {
		scl = find_bitmap(fs, stcl, tcl);			 
		if (scl == 0) res = FR_DENIED;				 
		if (scl == 0xFFFFFFFF) res = FR_DISK_ERR;
		if (res == FR_OK) {	 
			if (opt) {		 
				res = change_bitmap(fs, scl, tcl, 1);	 
				lclst = scl + tcl - 1;
			} else {		 
				lclst = scl - 1;
			}
		}
	} else

	{
		scl = clst = stcl; ncl = 0;
		for (;;) {	 
			n = get_fat(&fp->obj, clst);
			if (++clst >= fs->n_fatent) clst = 2;
			if (n == 1) { res = FR_INT_ERR; break; }
			if (n == 0xFFFFFFFF) { res = FR_DISK_ERR; break; }
			if (n == 0) {	 
				if (++ncl == tcl) break;	 
			} else {
				scl = clst; ncl = 0;		 
			}
			if (clst == stcl) { res = FR_DENIED; break; }	 
		}
		if (res == FR_OK) {	 
			if (opt) {		 
				for (clst = scl, n = tcl; n; clst++, n--) {	 
					res = put_fat(fs, clst, (n == 1) ? 0xFFFFFFFF : clst + 1);
					if (res != FR_OK) break;
					lclst = clst;
				}
			} else {		 
				lclst = scl - 1;
			}
		}
	}

	if (res == FR_OK) {
		fs->last_clst = lclst;		 
		if (opt) {	 
			fp->obj.sclust = scl;		 
			fp->obj.objsize = fsz;
			if (1) fp->obj.stat = 2;	 
			fp->flag |= 0x40;
			if (fs->free_clst <= fs->n_fatent - 2) {	 
				fs->free_clst -= tcl;
				fs->fsi_flag |= 1;
			}
		}
	}

	{ unlock_fs(fs, res); return res; };
}






 
 
 

FRESULT f_forward (
	FIL* fp, 						 
	UINT (*func)(const BYTE*,UINT),	 
	UINT btf,						 
	UINT* bf						 
)
{
	FRESULT res;
	FATFS *fs;
	DWORD clst, sect;
	FSIZE_t remain;
	UINT rcnt, csect;
	BYTE *dbuf;


	*bf = 0;	 
	res = validate(&fp->obj, &fs);		 
	if (res != FR_OK || (res = (FRESULT)fp->err) != FR_OK) { unlock_fs(fs, res); return res; };
	if (!(fp->flag & 0x01)) { unlock_fs(fs, FR_DENIED); return FR_DENIED; };	 

	remain = fp->obj.objsize - fp->fptr;
	if (btf > remain) btf = (UINT)remain;			 

	for ( ;  btf && (*func)(0, 0);					 
		fp->fptr += rcnt, *bf += rcnt, btf -= rcnt) {
		csect = (UINT)(fp->fptr / ((UINT)512) & (fs->csize - 1));	 
		if (fp->fptr % ((UINT)512) == 0) {				 
			if (csect == 0) {						 
				clst = (fp->fptr == 0) ?			 
					fp->obj.sclust : get_fat(&fp->obj, fp->clust);
				if (clst <= 1) { fp->err = (BYTE)(FR_INT_ERR); { unlock_fs(fs, FR_INT_ERR); return FR_INT_ERR; }; };
				if (clst == 0xFFFFFFFF) { fp->err = (BYTE)(FR_DISK_ERR); { unlock_fs(fs, FR_DISK_ERR); return FR_DISK_ERR; }; };
				fp->clust = clst;					 
			}
		}
		sect = clust2sect(fs, fp->clust);			 
		if (!sect) { fp->err = (BYTE)(FR_INT_ERR); { unlock_fs(fs, FR_INT_ERR); return FR_INT_ERR; }; };
		sect += csect;




		if (fp->sect != sect) {		 

			if (fp->flag & 0x80) {		 
				if (disk_write(fs->drv, fp->buf, fp->sect, 1) != RES_OK) { fp->err = (BYTE)(FR_DISK_ERR); { unlock_fs(fs, FR_DISK_ERR); return FR_DISK_ERR; }; };
				fp->flag &= (BYTE)~0x80;
			}

			if (disk_read(fs->drv, fp->buf, sect, 1) != RES_OK) { fp->err = (BYTE)(FR_DISK_ERR); { unlock_fs(fs, FR_DISK_ERR); return FR_DISK_ERR; }; };
		}
		dbuf = fp->buf;

		fp->sect = sect;
		rcnt = ((UINT)512) - (UINT)fp->fptr % ((UINT)512);	 
		if (rcnt > btf) rcnt = btf;					 
		rcnt = (*func)(dbuf + ((UINT)fp->fptr % ((UINT)512)), rcnt);	 
		if (!rcnt) { fp->err = (BYTE)(FR_INT_ERR); { unlock_fs(fs, FR_INT_ERR); return FR_INT_ERR; }; };
	}

	{ unlock_fs(fs, FR_OK); return FR_OK; };
}





 
 
 

FRESULT f_mkfs (
	const TCHAR* path,	 
	BYTE opt,			 
	DWORD au,			 
	void* work,			 
	UINT len			 
)
{
	const UINT n_fats = 1;		 
	const UINT n_rootdir = 512;	 
	static const WORD cst[] = {1, 4, 16, 64, 256, 512, 0};	 
	static const WORD cst32[] = {1, 2, 4, 8, 16, 32, 0};	 
	BYTE fmt, sys, *buf, *pte, pdrv, part;
	WORD ss;
	DWORD szb_buf, sz_buf, sz_blk, n_clst, pau, sect, nsect, n;
	DWORD b_vol, b_fat, b_data;				 
	DWORD sz_vol, sz_rsv, sz_fat, sz_dir;	 
	UINT i;
	int vol;
	DSTATUS stat;

	DWORD tbl[3];



	 
	vol = get_ldnumber(&path);					 
	if (vol < 0) return FR_INVALID_DRIVE;
	if (FatFs[vol]) FatFs[vol]->fs_type = 0;	 
	pdrv = (BYTE)(vol);	 
	part = 0;	 

	 
	stat = disk_initialize(pdrv);
	if (stat & 0x01) return FR_NOT_READY;
	if (stat & 0x04) return FR_WRITE_PROTECTED;
	if (disk_ioctl(pdrv, 3, &sz_blk) != RES_OK || !sz_blk || sz_blk > 32768 || (sz_blk & (sz_blk - 1))) sz_blk = 1;	 




	ss = 512;

	if ((au != 0 && au < ss) || au > 0x1000000 || (au & (au - 1))) return FR_INVALID_PARAMETER;	 
	au /= ss;	 

	 
	buf = (BYTE*)work;		 
	sz_buf = len / ss;		 
	szb_buf = sz_buf * ss;	 
	if (!szb_buf) return FR_MKFS_ABORTED;

	 
	if (0 && part != 0) {
		 
		if (disk_read(pdrv, buf, 0, 1) != RES_OK) return FR_DISK_ERR;	 
		if (ld_word(buf + 510) != 0xAA55) return FR_MKFS_ABORTED;	 
		pte = buf + (446 + (part - 1) * 16);
		if (!pte[4]) return FR_MKFS_ABORTED;	 
		b_vol = ld_dword(pte + 8);		 
		sz_vol = ld_dword(pte + 12);	 
	} else {
		 
		if (disk_ioctl(pdrv, 1, &sz_vol) != RES_OK) return FR_DISK_ERR;
		b_vol = (opt & 0x08) ? 0 : 63;		 
		if (sz_vol < b_vol) return FR_MKFS_ABORTED;
		sz_vol -= b_vol;						 
	}
	if (sz_vol < 128) return FR_MKFS_ABORTED;	 

	 
	do {
		if (1 && (opt & 0x04)) {	 
			if ((opt & 0x07) == 0x04 || sz_vol >= 0x4000000 || au > 128) {	 
				fmt = 4; break;
			}
		}
		if (au > 128) return FR_INVALID_PARAMETER;	 
		if (opt & 0x02) {	 
			if ((opt & 0x07) == 0x02 || !(opt & 0x01)) {	 
				fmt = 3; break;
			}
		}
		if (!(opt & 0x01)) return FR_INVALID_PARAMETER;	 
		fmt = 2;
	} while (0);


	if (fmt == 4) {	 
		DWORD szb_bit, szb_case, sum, nb, cl;
		WCHAR ch, si;
		UINT j, st;
		BYTE b;

		if (sz_vol < 0x1000) return FR_MKFS_ABORTED;	 

		tbl[0] = b_vol; tbl[1] = b_vol + sz_vol - 1;	 
		disk_ioctl(pdrv, 4, tbl);

		 
		if (!au) {	 
			au = 8;
			if (sz_vol >= 0x80000) au = 64;		 
			if (sz_vol >= 0x4000000) au = 256;	 
		}
		b_fat = b_vol + 32;										 
		sz_fat = ((sz_vol / au + 2) * 4 + ss - 1) / ss;			 
		b_data = (b_fat + sz_fat + sz_blk - 1) & ~(sz_blk - 1);	 
		if (b_data >= sz_vol / 2) return FR_MKFS_ABORTED;		 
		n_clst = (sz_vol - (b_data - b_vol)) / au;				 
		if (n_clst <16) return FR_MKFS_ABORTED;					 
		if (n_clst > 0x7FFFFFFD) return FR_MKFS_ABORTED;			 

		szb_bit = (n_clst + 7) / 8;						 
		tbl[0] = (szb_bit + au * ss - 1) / (au * ss);	 

		 
		sect = b_data + au * tbl[0];	 
		sum = 0;						 
		st = si = i = j = szb_case = 0;
		do {
			switch (st) {
			case 0:
				ch = ff_wtoupper(si);	 
				if (ch != si) {
					si++; break;		 
				}
				for (j = 1; (WCHAR)(si + j) && (WCHAR)(si + j) == ff_wtoupper((WCHAR)(si + j)); j++) ;	 
				if (j >= 128) {
					ch = 0xFFFF; st = 2; break;	 
				}
				st = 1;			 
				 
			case 1:
				ch = si++;		 
				if (--j == 0) st = 0;
				break;

			default:
				ch = (WCHAR)j; si += j;	 
				st = 0;
			}
			sum = xsum32(buf[i + 0] = (BYTE)ch, sum);		 
			sum = xsum32(buf[i + 1] = (BYTE)(ch >> 8), sum);
			i += 2; szb_case += 2;
			if (!si || i == szb_buf) {		 
				n = (i + ss - 1) / ss;
				if (disk_write(pdrv, buf, sect, n) != RES_OK) return FR_DISK_ERR;
				sect += n; i = 0;
			}
		} while (si);
		tbl[1] = (szb_case + au * ss - 1) / (au * ss);	 
		tbl[2] = 1;										 

		 
		sect = b_data; nsect = (szb_bit + ss - 1) / ss;	 
		nb = tbl[0] + tbl[1] + tbl[2];					 
		do {
			mem_set(buf, 0, szb_buf);
			for (i = 0; nb >= 8 && i < szb_buf; buf[i++] = 0xFF, nb -= 8) ;
			for (b = 1; nb && i < szb_buf; buf[i] |= b, b <<= 1, nb--) ;
			n = (nsect > sz_buf) ? sz_buf : nsect;		 
			if (disk_write(pdrv, buf, sect, n) != RES_OK) return FR_DISK_ERR;
			sect += n; nsect -= n;
		} while (nsect);

		 
		sect = b_fat; nsect = sz_fat;	 
		j = nb = cl = 0;
		do {
			mem_set(buf, 0, szb_buf); i = 0;	 
			if (cl == 0) {	 
				st_dword(buf + i, 0xFFFFFFF8); i += 4; cl++;
				st_dword(buf + i, 0xFFFFFFFF); i += 4; cl++;
			}
			do {			 
				while (nb && i < szb_buf) {			 
					st_dword(buf + i, (nb > 1) ? cl + 1 : 0xFFFFFFFF);
					i += 4; cl++; nb--;
				}
				if (!nb && j < 3) nb = tbl[j++];	 
			} while (nb && i < szb_buf);
			n = (nsect > sz_buf) ? sz_buf : nsect;	 
			if (disk_write(pdrv, buf, sect, n) != RES_OK) return FR_DISK_ERR;
			sect += n; nsect -= n;
		} while (nsect);

		 
		mem_set(buf, 0, szb_buf);
		buf[32 * 0 + 0] = 0x83;		 
		buf[32 * 1 + 0] = 0x81;		 
		st_dword(buf + 32 * 1 + 20, 2);
		st_dword(buf + 32 * 1 + 24, szb_bit);
		buf[32 * 2 + 0] = 0x82;		 
		st_dword(buf + 32 * 2 + 4, sum);
		st_dword(buf + 32 * 2 + 20, 2 + tbl[0]);
		st_dword(buf + 32 * 2 + 24, szb_case);
		sect = b_data + au * (tbl[0] + tbl[1]);	nsect = au;	 
		do {	 
			n = (nsect > sz_buf) ? sz_buf : nsect;
			if (disk_write(pdrv, buf, sect, n) != RES_OK) return FR_DISK_ERR;
			mem_set(buf, 0, ss);
			sect += n; nsect -= n;
		} while (nsect);

		 
		sect = b_vol;
		for (n = 0; n < 2; n++) {
			 
			mem_set(buf, 0, ss);
			mem_cpy(buf + 0, "\xEB\x76\x90" "EXFAT   ", 11);	 
			st_dword(buf + 64, b_vol);					 
			st_dword(buf + 72, sz_vol);					 
			st_dword(buf + 80, b_fat - b_vol);			 
			st_dword(buf + 84, sz_fat);					 
			st_dword(buf + 88, b_data - b_vol);			 
			st_dword(buf + 92, n_clst);					 
			st_dword(buf + 96, 2 + tbl[0] + tbl[1]);	 
			st_dword(buf + 100, get_fattime());				 
			st_word(buf + 104, 0x100);						 
			for (buf[108] = 0, i = ss; i >>= 1; buf[108]++) ;	 
			for (buf[109] = 0, i = au; i >>= 1; buf[109]++) ;	 
			buf[110] = 1;					 
			buf[111] = 0x80;				 
			st_word(buf + 120, 0xFEEB);	 
			st_word(buf + 510, 0xAA55);			 
			for (i = sum = 0; i < ss; i++) {		 
				if (i != 106 && i != 106 + 1 && i != 112) sum = xsum32(buf[i], sum);
			}
			if (disk_write(pdrv, buf, sect++, 1) != RES_OK) return FR_DISK_ERR;
			 
			mem_set(buf, 0, ss);
			st_word(buf + ss - 2, 0xAA55);	 
			for (j = 1; j < 9; j++) {
				for (i = 0; i < ss; sum = xsum32(buf[i++], sum)) ;	 
				if (disk_write(pdrv, buf, sect++, 1) != RES_OK) return FR_DISK_ERR;
			}
			 
			mem_set(buf, 0, ss);
			for ( ; j < 11; j++) {
				for (i = 0; i < ss; sum = xsum32(buf[i++], sum)) ;	 
				if (disk_write(pdrv, buf, sect++, 1) != RES_OK) return FR_DISK_ERR;
			}
			 
			for (i = 0; i < ss; i += 4) st_dword(buf + i, sum);		 
			if (disk_write(pdrv, buf, sect++, 1) != RES_OK) return FR_DISK_ERR;
		}

	} else

	{	 
		do {
			pau = au;
			 
			if (fmt == 3) {	 
				if (!pau) {	 
					n = sz_vol / 0x20000;	 
					for (i = 0, pau = 1; cst32[i] && cst32[i] <= n; i++, pau <<= 1) ;	 
				}
				n_clst = sz_vol / pau;	 
				sz_fat = (n_clst * 4 + 8 + ss - 1) / ss;	 
				sz_rsv = 32;	 
				sz_dir = 0;		 
				if (n_clst <= 0xFFF5 || n_clst > 0x0FFFFFF5) return FR_MKFS_ABORTED;
			} else {				 
				if (!pau) {	 
					n = sz_vol / 0x1000;	 
					for (i = 0, pau = 1; cst[i] && cst[i] <= n; i++, pau <<= 1) ;	 
				}
				n_clst = sz_vol / pau;
				if (n_clst > 0xFF5) {
					n = n_clst * 2 + 4;		 
				} else {
					fmt = 1;
					n = (n_clst * 3 + 1) / 2 + 3;	 
				}
				sz_fat = (n + ss - 1) / ss;		 
				sz_rsv = 1;						 
				sz_dir = (DWORD)n_rootdir * 32 / ss;	 
			}
			b_fat = b_vol + sz_rsv;						 
			b_data = b_fat + sz_fat * n_fats + sz_dir;	 

			 
			n = ((b_data + sz_blk - 1) & ~(sz_blk - 1)) - b_data;	 
			if (fmt == 3) {		 
				sz_rsv += n; b_fat += n;
			} else {					 
				sz_fat += n / n_fats;
			}

			 
			if (sz_vol < b_data + pau * 16 - b_vol) return FR_MKFS_ABORTED;	 
			n_clst = (sz_vol - sz_rsv - sz_fat * n_fats - sz_dir) / pau;
			if (fmt == 3) {
				if (n_clst <= 0xFFF5) {	 
					if (!au && (au = pau / 2) != 0) continue;	 
					return FR_MKFS_ABORTED;
				}
			}
			if (fmt == 2) {
				if (n_clst > 0xFFF5) {	 
					if (!au && (pau * 2) <= 64) {
						au = pau * 2; continue;		 
					}
					if ((opt & 0x02)) {
						fmt = 3; continue;	 
					}
					if (!au && (au = pau * 2) <= 128) continue;	 
					return FR_MKFS_ABORTED;
				}
				if  (n_clst <= 0xFF5) {	 
					if (!au && (au = pau * 2) <= 128) continue;	 
					return FR_MKFS_ABORTED;
				}
			}
			if (fmt == 1 && n_clst > 0xFF5) return FR_MKFS_ABORTED;	 

			 
			break;
		} while (1);


		tbl[0] = b_vol; tbl[1] = b_vol + sz_vol - 1;	 
		disk_ioctl(pdrv, 4, tbl);

		 
		mem_set(buf, 0, ss);
		mem_cpy(buf + 0, "\xEB\xFE\x90" "MSDOS5.0", 11); 
		st_word(buf + 11, ss);				 
		buf[13] = (BYTE)pau;				 
		st_word(buf + 14, (WORD)sz_rsv);	 
		buf[16] = (BYTE)n_fats;				 
		st_word(buf + 17, (WORD)((fmt == 3) ? 0 : n_rootdir));	 
		if (sz_vol < 0x10000) {
			st_word(buf + 19, (WORD)sz_vol);	 
		} else {
			st_dword(buf + 32, sz_vol);		 
		}
		buf[21] = 0xF8;							 
		st_word(buf + 24, 63);				 
		st_word(buf + 26, 255);				 
		st_dword(buf + 28, b_vol);				 
		if (fmt == 3) {
			st_dword(buf + 67, get_fattime());	 
			st_dword(buf + 36, sz_fat);		 
			st_dword(buf + 44, 2);			 
			st_word(buf + 48, 1);				 
			st_word(buf + 50, 6);			 
			buf[64] = 0x80;					 
			buf[66] = 0x29;					 
			mem_cpy(buf + 71, "NO NAME    " "FAT32   ", 19);	 
		} else {
			st_dword(buf + 39, get_fattime());	 
			st_word(buf + 22, (WORD)sz_fat);	 
			buf[36] = 0x80;						 
			buf[38] = 0x29;						 
			mem_cpy(buf + 43, "NO NAME    " "FAT     ", 19);	 
		}
		st_word(buf + 510, 0xAA55);					 
		if (disk_write(pdrv, buf, b_vol, 1) != RES_OK) return FR_DISK_ERR;	 

		 
		if (fmt == 3) {
			disk_write(pdrv, buf, b_vol + 6, 1);		 
			mem_set(buf, 0, ss);
			st_dword(buf + 0, 0x41615252);
			st_dword(buf + 484, 0x61417272);
			st_dword(buf + 488, n_clst - 1);	 
			st_dword(buf + 492, 2);			 
			st_word(buf + 510, 0xAA55);
			disk_write(pdrv, buf, b_vol + 7, 1);		 
			disk_write(pdrv, buf, b_vol + 1, 1);		 
		}

		 
		mem_set(buf, 0, (UINT)szb_buf);
		sect = b_fat;		 
		for (i = 0; i < n_fats; i++) {			 
			if (fmt == 3) {
				st_dword(buf + 0, 0xFFFFFFF8);	 
				st_dword(buf + 4, 0xFFFFFFFF);	 
				st_dword(buf + 8, 0x0FFFFFFF);	 
			} else {
				st_dword(buf + 0, (fmt == 1) ? 0xFFFFF8 : 0xFFFFFFF8);	 
			}
			nsect = sz_fat;		 
			do {	 
				n = (nsect > sz_buf) ? sz_buf : nsect;
				if (disk_write(pdrv, buf, sect, (UINT)n) != RES_OK) return FR_DISK_ERR;
				mem_set(buf, 0, ss);
				sect += n; nsect -= n;
			} while (nsect);
		}

		 
		nsect = (fmt == 3) ? pau : sz_dir;	 
		do {
			n = (nsect > sz_buf) ? sz_buf : nsect;
			if (disk_write(pdrv, buf, sect, (UINT)n) != RES_OK) return FR_DISK_ERR;
			sect += n; nsect -= n;
		} while (nsect);
	}

	 
	if (1 && fmt == 4) {
		sys = 0x07;			 
	} else {
		if (fmt == 3) {
			sys = 0x0C;		 
		} else {
			if (sz_vol >= 0x10000) {
				sys = 0x06;	 
			} else {
				sys = (fmt == 2) ? 0x04 : 0x01;	 
			}
		}
	}

	 
	if (0 && part != 0) {	 
		 
		if (disk_read(pdrv, buf, 0, 1) != RES_OK) return FR_DISK_ERR;	 
		buf[446 + (part - 1) * 16 + 4] = sys;		 
		if (disk_write(pdrv, buf, 0, 1) != RES_OK) return FR_DISK_ERR;	 
	} else {								 
		if (!(opt & 0x08)) {	 
			mem_set(buf, 0, ss);
			st_word(buf + 510, 0xAA55);		 
			pte = buf + 446;				 
			pte[0] = 0;					 
			pte[1] = 1;				 
			pte[2] = 1;					 
			pte[3] = 0;					 
			pte[4] = sys;				 
			n = (b_vol + sz_vol) / (63 * 255);	 
			pte[5] = 254;				 
			pte[6] = (BYTE)(n >> 2 | 63);	 
			pte[7] = (BYTE)n;			 
			st_dword(pte + 8, b_vol);	 
			st_dword(pte + 12, sz_vol);	 
			if (disk_write(pdrv, buf, 0, 1) != RES_OK) return FR_DISK_ERR;	 
		}
	}

	if (disk_ioctl(pdrv, 0, 0) != RES_OK) return FR_DISK_ERR;

	return FR_OK;
}



#line 5821 "../Middlewares/Third_Party/FatFs/src/ff.c"





 
 
 

TCHAR* f_gets (
	TCHAR* buff,	 
	int len,		 
	FIL* fp			 
)
{
	int n = 0;
	TCHAR c, *p = buff;
	BYTE s[2];
	UINT rc;


	while (n < len - 1) {	 
#line 5887 "../Middlewares/Third_Party/FatFs/src/ff.c"
		f_read(fp, s, 1, &rc);
		if (rc != 1) break;
		c = s[0];

		if (2 == 2 && c == '\r') continue;	 
		*p++ = c;
		n++;
		if (c == '\n') break;		 
	}
	*p = 0;
	return n ? buff : 0;			 
}




#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdarg.h"
 
 
 





 










#line 27 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdarg.h"








 

 
 
#line 57 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdarg.h"
    typedef struct __va_list { void *__ap; } va_list;

   






 


   










 


   















 




   

 


   




 



   





 







#line 138 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdarg.h"



#line 147 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdarg.h"

 

#line 5905 "../Middlewares/Third_Party/FatFs/src/ff.c"
 
 
 

typedef struct {
	FIL *fp;		 
	int idx, nchr;	 
	BYTE buf[64];	 
} putbuff;


static
void putc_bfd (		 
	putbuff* pb,
	TCHAR c
)
{
	UINT bw;
	int i;


	if (2 == 2 && c == '\n') {	  
		putc_bfd(pb, '\r');
	}

	i = pb->idx;		 
	if (i < 0) return;

#line 5960 "../Middlewares/Third_Party/FatFs/src/ff.c"
	pb->buf[i++] = (BYTE)c;


	if (i >= (int)(sizeof pb->buf) - 3) {	 
		f_write(pb->fp, pb->buf, (UINT)i, &bw);
		i = (bw == (UINT)i) ? 0 : -1;
	}
	pb->idx = i;
	pb->nchr++;
}


static
int putc_flush (		 
	putbuff* pb
)
{
	UINT nw;

	if (   pb->idx >= 0	 
		&& f_write(pb->fp, pb->buf, (UINT)pb->idx, &nw) == FR_OK
		&& (UINT)pb->idx == nw) return pb->nchr;
	return (-1);
}


static
void putc_init (		 
	putbuff* pb,
	FIL* fp
)
{
	pb->fp = fp;
	pb->nchr = pb->idx = 0;
}



int f_putc (
	TCHAR c,	 
	FIL* fp		 
)
{
	putbuff pb;


	putc_init(&pb, fp);
	putc_bfd(&pb, c);	 
	return putc_flush(&pb);
}




 
 
 

int f_puts (
	const TCHAR* str,	 
	FIL* fp				 
)
{
	putbuff pb;


	putc_init(&pb, fp);
	while (*str) putc_bfd(&pb, *str++);		 
	return putc_flush(&pb);
}




 
 
 

int f_printf (
	FIL* fp,			 
	const TCHAR* fmt,	 
	...					 
)
{
	va_list arp;
	putbuff pb;
	BYTE f, r;
	UINT i, j, w;
	DWORD v;
	TCHAR c, d, str[32], *p;


	putc_init(&pb, fp);

	__va_start(arp, fmt);

	for (;;) {
		c = *fmt++;
		if (c == 0) break;			 
		if (c != '%') {				 
			putc_bfd(&pb, c);
			continue;
		}
		w = f = 0;
		c = *fmt++;
		if (c == '0') {				 
			f = 1; c = *fmt++;
		} else {
			if (c == '-') {			 
				f = 2; c = *fmt++;
			}
		}
		while ((((c)>= '0')&&((c)<= '9'))) {		 
			w = w * 10 + c - '0';
			c = *fmt++;
		}
		if (c == 'l' || c == 'L') {	 
			f |= 4; c = *fmt++;
		}
		if (!c) break;
		d = c;
		if ((((d)>= 'a')&&((d)<= 'z'))) d -= 0x20;
		switch (d) {				 
		case 'S' :					 
			p = __va_arg(arp, TCHAR*);
			for (j = 0; p[j]; j++) ;
			if (!(f & 2)) {
				while (j++ < w) putc_bfd(&pb, ' ');
			}
			while (*p) putc_bfd(&pb, *p++);
			while (j++ < w) putc_bfd(&pb, ' ');
			continue;

		case 'C' :					 
			putc_bfd(&pb, (TCHAR)__va_arg(arp, int)); continue;

		case 'B' :					 
			r = 2; break;

		case 'O' :					 
			r = 8; break;

		case 'D' :					 
		case 'U' :					 
			r = 10; break;

		case 'X' :					 
			r = 16; break;

		default:					 
			putc_bfd(&pb, c); continue;
		}

		 
		v = (f & 4) ? (DWORD)__va_arg(arp, long) : ((d == 'D') ? (DWORD)(long)__va_arg(arp, int) : (DWORD)__va_arg(arp, unsigned int));
		if (d == 'D' && (v & 0x80000000)) {
			v = 0 - v;
			f |= 8;
		}
		i = 0;
		do {
			d = (TCHAR)(v % r); v /= r;
			if (d > 9) d += (c == 'x') ? 0x27 : 0x07;
			str[i++] = d + '0';
		} while (v && i < sizeof str / sizeof str[0]);
		if (f & 8) str[i++] = '-';
		j = i; d = (f & 1) ? '0' : ' ';
		while (!(f & 2) && j++ < w) putc_bfd(&pb, d);
		do {
			putc_bfd(&pb, str[--i]);
		} while (i);
		while (j++ < w) putc_bfd(&pb, d);
	}

	__va_end(arp);

	return putc_flush(&pb);
}

