#ifndef __BOARDCONFIG_H__
#define __BOARDCONFIG_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
#include "main.h"
#include "usbh_core.h"
/*****************************************************************************/
//定义外部资源

extern CAN_HandleTypeDef hcan1;

extern UART_HandleTypeDef huart1;//UPLINK
extern UART_HandleTypeDef huart3;//DBG UART
extern UART_HandleTypeDef huart6;//GDDC LCD


extern SPI_HandleTypeDef hspi3;//UPLINK
extern SPI_HandleTypeDef hspi5;//EPROM

extern TIM_HandleTypeDef htim3;//FAN TIM
extern TIM_HandleTypeDef htim4;//RGB LED
extern TIM_HandleTypeDef htim7;//LASER TIM
extern TIM_HandleTypeDef htim9;//RAIM  TIM
extern TIM_HandleTypeDef htim11;//SKP TIM
extern TIM_HandleTypeDef htim14;//SPLC  TIM

extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
extern CRC_HandleTypeDef hcrc;
extern RNG_HandleTypeDef hrng;
extern DAC_HandleTypeDef hdac;

extern USBH_HandleTypeDef hUsbHostFS;//UDISK
extern USBH_HandleTypeDef hUsbHostHS;//WFS


/*****************************************************************************/
//引脚功能定义
#define GET_ESTOP_NC													0
#define GET_INTERLOCK_NC											HAL_GPIO_ReadPin(GPIO_X2_GPIO_Port, GPIO_X2_Pin)
#define GET_FSWITCH_NO												0
#define GET_FSWITCH_NC												0

#define SET_SPK_AP_ON													__nop()
#define SET_SPK_AP_OFF												__nop()

#define SET_DAC7311_CS(b)											__nop()								
#define SET_DAC7311_SCK(b)                    __nop()
#define SET_DAC7311_SDI(b)										__nop()						

#define SET_RED_LED_ON												HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1)
#define SET_RED_LED_OFF												HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1)

#define SET_GREEN_LED_ON											HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2)
#define SET_GREEN_LED_OFF											HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2)

#define SET_BLUE_LED_ON												HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3)
#define SET_BLUE_LED_OFF											HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3)

#define SET_BLUE_LED_DC(b)										__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, b)
#define SET_RED_LED_DC(b)											__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, b)
#define SET_GREEN_LED_DC(b)										__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, b)

#define SET_BEEM_LED_ON												HAL_GPIO_WritePin(BEEM_LED_GPIO_Port, BEEM_LED_Pin, GPIO_PIN_SET)
#define SET_BEEM_LED_OFF											HAL_GPIO_WritePin(BEEM_LED_GPIO_Port, BEEM_LED_Pin, GPIO_PIN_RESET)
#define GET_BEEM_LED													HAL_GPIO_ReadPin(BEEM_LED_GPIO_Port, BEEM_LED_Pin)
#define FLIP_BEEM_LED													HAL_GPIO_TogglePin(BEEM_LED_GPIO_Port, BEEM_LED_Pin)

#define SET_SPEAK_ENA_ON											HAL_GPIO_WritePin(BEEM_LED_GPIO_Port, BEEM_LED_Pin, GPIO_PIN_SET)
#define SET_SPEAK_ENA_OFF											HAL_GPIO_WritePin(BEEM_LED_GPIO_Port, BEEM_LED_Pin, GPIO_PIN_RESET)
#define SET_SPEAK_ENA(b)                      HAL_GPIO_WritePin(BEEM_LED_GPIO_Port, BEEM_LED_Pin, b) 
#define GET_SPEAK_ENA													HAL_GPIO_ReadPin(BEEM_LED_GPIO_Port, BEEM_LED_Pin)
#define FLIP_SPEAK_ENA												HAL_GPIO_TogglePin(BEEM_LED_GPIO_Port, BEEM_LED_Pin)
   
#define SET_TICK_LED_ON												HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, GPIO_PIN_RESET)
#define SET_TICK_LED_OFF											HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, GPIO_PIN_SET)
#define GET_TICK_LED													!HAL_GPIO_ReadPin(TICK_LED_GPIO_Port, TICK_LED_Pin)
#define FLIP_TICK_LED													HAL_GPIO_TogglePin(TICK_LED_GPIO_Port, TICK_LED_Pin)

#define SET_ERR_LED_ON												HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_RESET)
#define SET_ERR_LED_OFF												HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_SET)
#define GET_ERR_LED														!HAL_GPIO_ReadPin(ERR_LED_GPIO_Port, ERR_LED_Pin)
#define FLIP_ERR_LED													HAL_GPIO_TogglePin(ERR_LED_GPIO_Port, ERR_LED_Pin)

#define SET_LINK_LED(b)                        HAL_GPIO_WritePin(GPIO_Y3_GPIO_Port, GPIO_Y3_Pin, b)
#define SET_LOCK_LED(b)                       HAL_GPIO_WritePin(GPIO_Y3_GPIO_Port, GPIO_Y3_Pin, b)
#define SET_LOCK_LED_ON												HAL_GPIO_WritePin(GPIO_Y3_GPIO_Port, GPIO_Y3_Pin, GPIO_PIN_SET)
#define SET_LOCK_LED_OFF											HAL_GPIO_WritePin(GPIO_Y3_GPIO_Port, GPIO_Y3_Pin, GPIO_PIN_RESET)
#define GET_LOCK_LED													!HAL_GPIO_ReadPin(GPIO_Y3_GPIO_Port, GPIO_Y3_Pin)
#define FLIP_LOCK_LED													HAL_GPIO_TogglePin(GPIO_Y3_GPIO_Port, GPIO_Y3_Pin)


#define SET_LASER_CH0_ON											HAL_GPIO_WritePin(MPR0_PWM_GPIO_Port, MPR0_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH0_OFF											HAL_GPIO_WritePin(MPR0_PWM_GPIO_Port, MPR0_PWM_Pin, GPIO_PIN_RESET)

#define SET_LASER_CH1_ON											HAL_GPIO_WritePin(MPR1_PWM_GPIO_Port, MPR1_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH1_OFF											HAL_GPIO_WritePin(MPR1_PWM_GPIO_Port, MPR1_PWM_Pin, GPIO_PIN_RESET)

#define SET_LASER_CH2_ON											HAL_GPIO_WritePin(MPR2_PWM_GPIO_Port, MPR2_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH2_OFF											HAL_GPIO_WritePin(MPR2_PWM_GPIO_Port, MPR2_PWM_Pin, GPIO_PIN_RESET)  

#define SET_LASER_CH3_ON											HAL_GPIO_WritePin(MPR3_PWM_GPIO_Port, MPR3_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH3_OFF											HAL_GPIO_WritePin(MPR3_PWM_GPIO_Port, MPR3_PWM_Pin, GPIO_PIN_RESET)  

#define SET_LASER_CH4_ON											HAL_GPIO_WritePin(MPR4_PWM_GPIO_Port, MPR4_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH4_OFF											HAL_GPIO_WritePin(MPR4_PWM_GPIO_Port, MPR4_PWM_Pin, GPIO_PIN_RESET)  

#define SET_LASER_CH5_ON											HAL_GPIO_WritePin(MPR5_PWM_GPIO_Port, MPR5_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH5_OFF											HAL_GPIO_WritePin(MPR5_PWM_GPIO_Port, MPR5_PWM_Pin, GPIO_PIN_RESET)

#define SET_LASER_CH6_ON											HAL_GPIO_WritePin(SLD0_PWM_GPIO_Port, SLD0_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH6_OFF											HAL_GPIO_WritePin(SLD0_PWM_GPIO_Port, SLD0_PWM_Pin, GPIO_PIN_RESET)

#define SET_LASER_CH7_ON											HAL_GPIO_WritePin(SLD1_PWM_GPIO_Port, SLD1_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH7_OFF											HAL_GPIO_WritePin(SLD1_PWM_GPIO_Port, SLD1_PWM_Pin, GPIO_PIN_RESET)

#define SET_TEC_CH0_ON												HAL_GPIO_WritePin(MPR2_PWM_GPIO_Port, MPR2_PWM_Pin, GPIO_PIN_SET)
#define SET_TEC_CH0_OFF												HAL_GPIO_WritePin(MPR2_PWM_GPIO_Port, MPR2_PWM_Pin, GPIO_PIN_RESET)

#define SET_TEC_CH1_ON												HAL_GPIO_WritePin(MPR3_PWM_GPIO_Port, MPR3_PWM_Pin, GPIO_PIN_SET)
#define SET_TEC_CH1_OFF												HAL_GPIO_WritePin(MPR3_PWM_GPIO_Port, MPR3_PWM_Pin, GPIO_PIN_RESET)

#define SET_TEC_CH2_ON												__nop()												
#define SET_TEC_CH2_OFF												__nop()

#define SET_TEC_CH3_ON												__nop()
#define SET_TEC_CH3_OFF												__nop()

#define SET_TEC_CH4_ON												__nop()
#define SET_TEC_CH4_OFF												__nop()

#define SET_TEC_CH5_ON												__nop()
#define SET_TEC_CH5_OFF												__nop()

#define SET_TEC_CH6_ON												__nop()
#define SET_TEC_CH6_OFF												__nop()

#define SET_TEC_CH7_ON												__nop()
#define SET_TEC_CH7_OFF												__nop()

#define FLIP_LASER_CH0												HAL_GPIO_TogglePin(MPR0_PWM_GPIO_Port, MPR0_PWM_Pin)
#define FLIP_LASER_CH1												HAL_GPIO_TogglePin(MPR1_PWM_GPIO_Port, MPR1_PWM_Pin)
#define FLIP_LASER_CH2												HAL_GPIO_TogglePin(MPR2_PWM_GPIO_Port, MPR2_PWM_Pin)
#define FLIP_LASER_CH3												HAL_GPIO_TogglePin(MPR3_PWM_GPIO_Port, MPR3_PWM_Pin)
#define FLIP_LASER_CH4												HAL_GPIO_TogglePin(MPR4_PWM_GPIO_Port, MPR4_PWM_Pin)
#define FLIP_LASER_CH5												HAL_GPIO_TogglePin(MPR5_PWM_GPIO_Port, MPR5_PWM_Pin)
#define FLIP_LASER_CH6												HAL_GPIO_TogglePin(SLD0_PWM_GPIO_Port, SLD0_PWM_Pin)
#define FLIP_LASER_CH7												HAL_GPIO_TogglePin(SLD1_PWM_GPIO_Port, SLD1_PWM_Pin)

#define GET_LASER_CH0													HAL_GPIO_ReadPin(MPR0_PWM_GPIO_Port, LAS0_PWM_Pin)
#define GET_LASER_CH1													HAL_GPIO_ReadPin(MPR0_PWM_GPIO_Port, LAS1_PWM_Pin)
#define GET_LASER_CH2													HAL_GPIO_ReadPin(MPR0_PWM_GPIO_Port, LAS2_PWM_Pin)
#define GET_LASER_CH3													HAL_GPIO_ReadPin(MPR0_PWM_GPIO_Port, LAS3_PWM_Pin)
#define GET_LASER_CH4													HAL_GPIO_ReadPin(MPR0_PWM_GPIO_Port, LAS4_PWM_Pin)
#define GET_LASER_CH5													HAL_GPIO_ReadPin(MPR0_PWM_GPIO_Port, LAS5_PWM_Pin)
#define GET_LASER_CH6													HAL_GPIO_ReadPin(SLD0_PWM_GPIO_Port, SLD0_PWM_Pin)
#define GET_LASER_CH7													HAL_GPIO_ReadPin(SLD1_PWM_GPIO_Port, SLD1_PWM_Pin)

#define SET_FAN0_ON														HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1)
#define SET_FAN0_OFF													HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1)
#define SET_FAN0_TIM_PWM(b)										__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, b)

#define SET_FAN1_ON														__nop()
#define SET_FAN1_OFF													__nop()
#define SET_FAN1_TIM_PWM(b)										__nop()

#define SET_FAN2_ON														__nop()
#define SET_FAN2_OFF													__nop()
#define SET_FAN2_TIM_PWM(b)										__nop()

#define SET_SPK_TIM_ON												__nop()
#define SET_SPK_TIM_OFF												__nop()

#define SET_RAIM_TIM_OFF											HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2)
#define SET_RAIM_TIM_ON												HAL_TIM_PWM_Stop(&htim9, TIM_CHANNEL_2)
#define SET_RAIM_TIM_PWM(b)										__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, b)

#define SET_RAIM_SHDN(b)			                __nop()
#define SET_RAIM_SHDN_ON                      __nop()
#define SET_RAIM_SHDN_OFF                     __nop()
#define FLIP_RAIM_SHDN                        __nop()
#define GET_RAIM_SHDN													0

#define SET_GAIM_TIM_OFF											__nop()
#define SET_GAIM_TIM_ON												__nop()
#define SET_GAIM_TIM_PWM(b)										__nop()

#define SET_GAIM_SHDN(b)			                __nop()
#define SET_GAIM_SHDN_ON                      __nop()
#define SET_GAIM_SHDN_OFF                     __nop()
#define FLIP_GAIM_SHDN                        __nop()
#define GET_GAIM_SHDN													0

#define SET_LASER1_AIM(b)                     HAL_GPIO_WritePin(LAS0_AIM_GPIO_Port, LAS0_AIM_Pin, b)
#define SET_LAS0_AIM_ON												HAL_GPIO_WritePin(LAS0_AIM_GPIO_Port, LAS0_AIM_Pin, GPIO_PIN_SET)
#define SET_LAS0_AIM_OFF											HAL_GPIO_WritePin(LAS0_AIM_GPIO_Port, LAS0_AIM_Pin, GPIO_PIN_RESET)
#define FLIP_LAS0_AIM													HAL_GPIO_TogglePin(LAS0_AIM_GPIO_Port, LAS0_AIM_Pin)
#define GET_LAS0_AIM													HAL_GPIO_ReadPin(LAS0_AIM_GPIO_Port, LAS0_AIM_Pin)

#define SET_LASER2_AIM(b)                     HAL_GPIO_WritePin(LAS1_AIM_GPIO_Port, LAS1_AIM_Pin, b)

#define SET_LAS1_AIM_ON												HAL_GPIO_WritePin(LAS1_AIM_GPIO_Port, LAS1_AIM_Pin, GPIO_PIN_SET)
#define SET_LAS1_AIM_OFF											HAL_GPIO_WritePin(LAS1_AIM_GPIO_Port, LAS1_AIM_Pin, GPIO_PIN_RESET)
#define FLIP_LAS1_AIM													HAL_GPIO_TogglePin(LAS1_AIM_GPIO_Port, LAS1_AIM_Pin)
#define GET_LAS1_AIM													HAL_GPIO_ReadPin(LAS1_AIM_GPIO_Port, LAS1_AIM_Pin)

//MCP41010
#define SET_MCP41010_CS(b)										HAL_GPIO_WritePin(MCP41010_CS_GPIO_Port, MCP41010_CS_Pin, b)
#define SET_MCP41010_SDI(b)										HAL_GPIO_WritePin(MCP41010_SDI_GPIO_Port, MCP41010_SDI_Pin, b)
#define SET_MCP41010_SCK(b)										HAL_GPIO_WritePin(MCP41010_SCK_GPIO_Port, MCP41010_SCK_Pin, b)

//POWER SWITCH 硬关机信号->MCU最为MPU单元
#define GET_PWR_KEY														0

//POWER INT MPU软关机中断信号-->LTC2955作为MPU单元
#define GET_PWR_INT														0
//POWER KILL MPU软件关机信号-->LTC2955作为MPU单元
#define SET_PWR_KILL(b)												__nop()
#define SET_PWR_KILL_ON												__nop()
#define SET_PWR_KILL_OFF											__nop()
#define FLIP_PWR_KILL													__nop()
#define GET_PWR_KILL													0

//POWER LED
#define SET_PWR_LED(b)												__nop()
#define SET_PWR_LED_ON												__nop()
#define SET_PWR_LED_OFF												__nop()
#define FLIP_PWR_LED													__nop()
#define GET_PWR_LED														0

//TEC OUT
#define SET_TEC_GATE_CH0_ON										__nop()											
#define SET_TEC_GATE_CH0_OFF									__nop()

#define SET_TEC_GATE_CH1_ON										__nop()											
#define SET_TEC_GATE_CH1_OFF									__nop()
//PUMP LED
#define SET_PUMP0(b)													HAL_GPIO_WritePin(GPIO_Y1_GPIO_Port,GPIO_Y1_Pin, b)
#define SET_PUMP0_ON													HAL_GPIO_WritePin(GPIO_Y1_GPIO_Port, GPIO_Y1_Pin, GPIO_PIN_SET)
#define SET_PUMP0_OFF													HAL_GPIO_WritePin(GPIO_Y1_GPIO_Port, GPIO_Y1_Pin, GPIO_PIN_RESET)
#define GET_PUMP0															HAL_GPIO_ReadPin(GPIO_Y1_GPIO_Port, GPIO_Y1_Pin)
#define FLIP_PUMP0														HAL_GPIO_TogglePin(GPIO_Y1_GPIO_Port, GPIO_Y1_Pin)

#define SET_PUMP1(b)													HAL_GPIO_WritePin(GPIO_Y2_GPIO_Port, GPIO_Y2_Pin, b)
#define SET_PUMP1_ON													HAL_GPIO_WritePin(GPIO_Y2_GPIO_Port, GPIO_Y2_Pin, GPIO_PIN_SET)
#define SET_PUMP1_OFF													HAL_GPIO_WritePin(GPIO_Y2_GPIO_Port, GPIO_Y2_Pin, GPIO_PIN_RESET)
#define GET_PUMP1															HAL_GPIO_ReadPin(GPIO_Y2_GPIO_Port, GPIO_Y2_Pin)
#define FLIP_PUMP1														HAL_GPIO_TogglePin(GPIO_Y2_GPIO_Port, GPIO_Y2_Pin)

//SPI EPROM
#define EPROM_SPI_NSS(b)											HAL_GPIO_WritePin(EPROM_NSS_GPIO_Port, EPROM_NSS_Pin, b)
#define EPROM_SPI_NSS_DESEL										HAL_GPIO_WritePin(EPROM_NSS_GPIO_Port, EPROM_NSS_Pin, GPIO_PIN_SET)
#define EPROM_SPI_NSS_SEL											HAL_GPIO_WritePin(EPROM_NSS_GPIO_Port, EPROM_NSS_Pin, GPIO_PIN_RESET)

//模拟HDC1080 I2C定义
#define SET_HDC1080_SCL(b)										__nop()									
#define SET_HDC1080_SDA(b)										__nop()
#define GET_HDC1080_SDA												0
//安全锁接触
#define SET_SAFE_RESET(b)											__nop()
#define SET_SAFE_RESET_ON                    	__nop()
#define SET_SAFE_RESET_OFF                   	__nop()

//USB PSON
#define SET_USB_OTG_FS_PSON_ON								HAL_GPIO_WritePin(USB_OTG_FS_PSON_GPIO_Port, USB_OTG_FS_PSON_Pin, GPIO_PIN_SET)
#define SET_USB_OTG_FS_PSON_OFF								HAL_GPIO_WritePin(USB_OTG_FS_PSON_GPIO_Port, USB_OTG_FS_PSON_Pin, GPIO_PIN_RESET)

/*****************************************************************************/
//定义外设总线
#define CONFIG_LASER_TIM_HANDLE								htim7
#define CONFIG_LASER_TIM											TIM7

#define CONFIG_SPLC_TIM_HANDLE								htim14//SPLC 计时器定义	
#define CONFIG_SPLC_TIM												TIM14

#define CONFIG_SPK_HANDLE											htim9//SPK 计时器定义	
#define CONFIG_SPK_TIM												TIM9
#define CONFIG_SPK_PWM_CHANNEL								TIM_CHANNEL_2

#define CONFIG_FAN0_TIM_HANDLE								htim8	
#define CONFIG_FAN0_TIM												TIM8
#define CONFIG_FAN0_PWM_CHANNEL								TIM_CHANNEL_3
#define CONFIG_FAN0_FG_CHANNEL								

#define CONFIG_FAN1_TIM_HANDLE								htim8	
#define CONFIG_FAN1_TIM												TIM8
#define CONFIG_FAN1_PWM_CHANNEL								TIM_CHANNEL_2
#define CONFIG_FAN1_FG_CHANNEL								

#define CONFIG_FAN2_TIM_HANDLE								htim8	
#define CONFIG_FAN2_TIM												TIM8
#define CONFIG_FAN2_PWM_CHANNEL								TIM_CHANNEL_1
#define CONFIG_FAN2_FG_CHANNEL								

#define CONFIG_EPROM_BUS_HANDLE								hspi3//SPLC NVRAM接口定义
#define CONFIG_EPROM_BUS											SPI3									

#define CONFIG_DEBUG_UART											huart5//调试串口
#define CONFIG_GDDC_UART											huart3//GDDC串口
#define CONFIG_GDDC_UART_INSTANCE							USART3//GDDC串口中断

#define CONFIG_MBI2C_BUS											hi2c2//主板I2C总线

/*****************************************************************************/
//配置EPROM规格
#define CONFIG_EPROM_SPI											
#define CONFIG_EPROM_SIZE 										CONFIG_MB85RS2MAT_SIZE
#define	CONFIG_AT24C64_SIZE										8192
#define	CONFIG_AT24C128_SIZE 									16384
#define	CONFIG_AT24C256_SIZE 									32768//32K*8
#define CONFIG_FM25W256G_SIZE									32768//32K
#define CONFIG_MB85RS2MAT_SIZE								0x40000//256K
#define CONFIG_EPROM_WRITE_ADDR								0xA0//
#define CONFIG_EPROM_READ_ADDR								0xA1//
#define CONFIG_EPROM_TIMEOUT									1000//EPROM读写超时
#define CONFIG_EPROM_PAGE_SIZE								0x08//EPROM 页大小
#define CONFIG_EPROM_WRITE_DELAY							0//写入等待时间mS
/*****************************************************************************/
//配置ADC
#define CONFIG_VREF_CAL                     	*(__IO uint16_t *)(0x1FFF7A2A)//校正电压源
#define CONFIG_ADC1_CHANNEL										12//ADC采集通道
#define CONFIG_ADC3_CHANNEL										0
#define ADC_FILTER_ALPHA    									0.25f//0.1f：滤波极强，超平滑 0.25f：平衡响应与滤波（推荐） 0.5f：响应快，滤波弱
#define CONFIG_ADC_AVERAGE_NUM								8//ADC平均值次数		
#define CONFIG_ADC1_DMA_BUFFER_SIZE						(CONFIG_ADC1_CHANNEL * CONFIG_ADC_AVERAGE_NUM)//ADC DMA采集缓冲
#define CONFIG_ADC3_DMA_BUFFER_SIZE						(CONFIG_ADC3_CHANNEL * CONFIG_ADC_AVERAGE_NUM)//ADC DMA采集缓冲

#define CONFIG_VREF_ADC												SPREG_ADC_59
#define CONFIG_MCU_VREF												3300.0F
#define CONFIG_ADC_AVG_SLOPE									2.5F
#define CONFIG_ADC_V25												760.0F//0.76V@25D

#define CONFIG_DIODE_NTC_RS										3300L//激光器热敏电阻分压电阻值
#define CONFIG_HT0_NTC_RS											4700L//散热器0热敏电阻分压电阻值
#define CONFIG_HT1_NTC_RS											4700L//散热器1热敏电阻分压电阻值
#define CONFIG_HT2_NTC_RS											1L	
#define CONFIG_HT3_NTC_RS											1L
#define CONFIG_WATER_HOT_NTC_RS								1L
#define CONFIG_WATER_COOL_NTC_RS							1L
#define CONFIG_AMBIENT_NTC_RS									1L
#define CONFIG_MBAT_NTC_RS										4700L//环境热敏电阻分压电阻值

#define CONFIG_DIODE_NTC_B										3477.0F//激光器热敏电阻B值
#define CONFIG_HT0_NTC_B											3477.0F//散热器0热敏电阻B值
#define CONFIG_HT1_NTC_B											3477.0F//散热器1热敏电阻B值
#define CONFIG_HT2_NTC_B											3477.0F//散热器2热敏电阻B值
#define CONFIG_HT3_NTC_B											3477.0F//散热器3热敏电阻B值
#define CONFIG_MBAT_NTC_B											3477.0F//电池热敏电阻B值

#define CONFIG_WATER_HOT_NTC_B							  3477.0F
#define CONFIG_WATER_COOL_NTC_B								3477.0F
#define CONFIG_AMBIENT_NTC_B									3477.0F

#define CONFIG_NTC_R25												10000.0F//25摄氏度时电阻
#define CONFIG_NTC_VREF												3300L//
#define CONFIG_FIBER_PD_THRESHOLD							350//光纤插入时ADC阈值
/*****************************************************************************/
//配置DAC
#define CONFIG_DAC_MAXBIT_CH0									0xFFF//12BIT STM32
#define CONFIG_DAC_MAXBIT_CH1									0xFFF//12BIT STM32
#define CONFIG_DAC_MAXBIT_CH2									0xFFFF//NULL
#define CONFIG_DAC_MAXBIT_CH3									0xFFFF//NULL
#define CONFIG_DAC_MAXBIT_CH4									0xFFFF//NULL
#define CONFIG_DAC_MAXBIT_CH5									0xFFFF//NULL
#define CONFIG_DAC_MAXBIT_CH6									0xFFFF//NULL
#define CONFIG_DAC_MAXBIT_CH7									0xFFFF//NULL

#define CONFIG_DAC_MAXBIT_CH8									0xFFF//12BIT DAC7311
#define CONFIG_DAC_MAXBIT_CH9									0xFFFF//NULL
#define CONFIG_DAC_MAXBIT_CH10                0xFFFF//NULL
#define CONFIG_DAC_MAXBIT_CH11								0xFFFF//NULL
#define CONFIG_DAC_MAXBIT_CH12								0xFFFF//NULL
#define CONFIG_DAC_MAXBIT_CH13								0xFFFF//NULL
#define CONFIG_DAC_MAXBIT_CH14								0xFFFF//NULL
#define CONFIG_DAC_MAXBIT_CH15								0xFFFF//NULL

#define CONFIG_DAC_MAXBIT_CH16								5000
#define CONFIG_DAC_MAXBIT_CH17								5000//NULL
/*****************************************************************************/
//配置EPROM数据地址
#define CONFIG_EPROM_MR_START									(0x0L)//
#define CONFIG_EPROM_MR_END										(CONFIG_EPROM_MR_START + MR_END - MR_START)
#define CONFIG_EPROM_DM_START									(CONFIG_EPROM_MR_END + 1)//NVRAM中DM在EPROM储存地址
#define CONFIG_EPROM_DM_END										(CONFIG_EPROM_DM_START + DM_END - DM_START)

#define CONFIG_EPROM_FD_SCHEME_SIZE						((FD_SCHEME_END_0 - FD_SCHEME_START_0 + 1) * 2)//单个方案占用的EPROM空间
#define CONFIG_EPROM_FD_START									(CONFIG_EPROM_DM_END + 1)
#define CONFIG_EPROM_FD_END										(CONFIG_EPROM_FD_START + FD_END - FD_START)

#define CONFIG_EPROM_MEDICAL_CRC							(31466L)//4B 治疗历史 CRC32 硬件计算
#define CONFIG_EPROM_MR_CRC										(31470L)//4B MR NVRAM CRC32 硬件计算
#define CONFIG_EPROM_DM_CRC										(31474L)//4B DM NVRAM CRC32 硬件计算
#define CONFIG_EPROM_FD_CRC										(31478L)//4B FD NVRAM CRC32 硬件计算
#define CONFIG_EPROM_MCU_FW_CRC								(31482L)//4B MCU固件CRC32值 软件计算
#define CONFIG_EPROM_LCD_FW_CRC								(31486L)//4B LCD固件CRC32值 软件计算
#define CONFIG_EPROM_CFG_CRC									(31480L)//4B deviceConfig CRC32值 硬件计算
#define CONFIG_EPROM_LOG_CRC									(31484L)//4B logInfo CRC32值 硬件计算

#define CONFIG_EPROM_CONFIG_START							(31488L)//1024B 配置信息区
#define CONFIG_EPROM_CONFIG_END								(32511L)
#define CONFIG_EPROM_LOGINFO_START						(32512L)//256B 记录信息区 
#define CONFIG_EPROM_LOGINFO_END							(32767L)

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif













