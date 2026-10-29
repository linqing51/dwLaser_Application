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
extern ADC_HandleTypeDef hadc1;
extern CRC_HandleTypeDef hcrc;
extern RNG_HandleTypeDef hrng;
extern DAC_HandleTypeDef hdac;//LAS0 LAS1
extern SPI_HandleTypeDef hspi3;//EPROM SPI3
extern TIM_HandleTypeDef htim3;//FAN TIM
extern TIM_HandleTypeDef htim4;//RGB LED TIM
extern TIM_HandleTypeDef htim5;//AIM TIM	
	
extern TIM_HandleTypeDef htim7;//LASER TIM
extern TIM_HandleTypeDef htim8;//SKP TIM

extern TIM_HandleTypeDef htim14;//SPLC TIM
extern UART_HandleTypeDef huart1;//DBG UART
extern UART_HandleTypeDef huart2;//GDDC UART
extern UART_HandleTypeDef huart3;//BT/DEV UART
extern UART_HandleTypeDef huart6;//NFS UART
extern USBH_HandleTypeDef hUsbHostHS;
extern USBH_HandleTypeDef hUsbHostFS;
/*****************************************************************************/
//定义外设总线
#define CONFIG_LASER_TIM_HANDLE								htim7
#define CONFIG_LASER_TIM											TIM7

#define CONFIG_SPLC_TIM_HANDLE								htim14//SPLC 计时器定义	
#define CONFIG_SPLC_TIM												TIM14

#define CONFIG_SPK_HANDLE											htim8//SPK 计时器定义	
#define CONFIG_SPK_TIM												TIM8
#define CONFIG_SPK_PWM_CHANNEL								TIM_CHANNEL_1

#define CONFIG_FAN0_TIM_HANDLE								htim3	
#define CONFIG_FAN0_TIM												TIM3
#define CONFIG_FAN0_PWM_CHANNEL								TIM_CHANNEL_2
#define CONFIG_FAN0_FG_CHANNEL								TIM_CHANNEL_1

#define CONFIG_RGB_LED_TIM_HANDLE             htim4
#define CONFIG_RGB_LED_TIM                    TIM4

#define CONFIG_AIM_HANDLE											htim5			
#define CONFIG_AIM_PWM_CHANNEL								TIM_CHANNEL_1

#define CONFIG_EPROM_BUS_HANDLE								hspi3//SPLC NVRAM接口定义
#define CONFIG_EPROM_BUS											SPI3	

#define CONFIG_DEBUG_UART											huart3//调试串口

#define CONFIG_GDDC_UART											huart1//GDDC串口
#define CONFIG_GDDC_UART_INSTANCE							USART1//GDDC串口中断
/*****************************************************************************/
//引脚功能定义
#define GET_ESTOP_NC													HAL_GPIO_ReadPin(ESTOP_NC_GPIO_Port, ESTOP_NC_Pin)
#define GET_INTERLOCK_NC											HAL_GPIO_ReadPin(INTERLOCK_NC_GPIO_Port, INTERLOCK_NC_Pin)
#define GET_FSWITCH_NO												HAL_GPIO_ReadPin(FS_NO_GPIO_Port, FS_NO_Pin)
#define GET_FSWITCH_NC												HAL_GPIO_ReadPin(FS_NC_GPIO_Port, FS_NC_Pin)

#define SET_SPK_AP_ON													HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_RESET)
#define SET_SPK_AP_OFF												HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_SET)

#define EPROM_SPI_NSS_SEL                     HAL_GPIO_WritePin(EPROM_NSS_GPIO_Port, EPROM_NSS_Pin, GPIO_PIN_RESET)
#define EPROM_SPI_NSS_DESEL                   HAL_GPIO_WritePin(EPROM_NSS_GPIO_Port, EPROM_NSS_Pin, GPIO_PIN_SET)

#define SET_EDAC0_CS(b)												__nop()		
#define SET_EDAC1_CS(b)												__nop()
#define SET_EDAC2_CS(b)												__nop()
#define SET_EDAC3_CS(b)												__nop()
#define SET_EDAC4_CS(b)												__nop()
#define SET_EDAC5_CS(b)												__nop()
#define SET_EDAC6_CS(b)												__nop()
#define SET_EDAC7_CS(b)												__nop()											

#define SET_EDAC0_SCK(b)											__nop()
#define SET_EDAC1_SCK(b)											__nop()
#define SET_EDAC2_SCK(b)											__nop()
#define SET_EDAC3_SCK(b)											__nop()
#define SET_EDAC4_SCK(b)											__nop()
#define SET_EDAC5_SCK(b)											__nop()
#define SET_EDAC6_SCK(b)											__nop()
#define SET_EDAC7_SCK(b)											__nop()			

#define SET_EDAC0_SDI(b)											__nop()
#define SET_EDAC1_SDI(b)											__nop()
#define SET_EDAC2_SDI(b)											__nop()
#define SET_EDAC3_SDI(b)											__nop()
#define SET_EDAC4_SDI(b)											__nop()
#define SET_EDAC5_SDI(b)											__nop()
#define SET_EDAC6_SDI(b)											__nop()
#define SET_EDAC7_SDI(b)											__nop()

#define SET_RED_LED_ON												HAL_TIM_PWM_Start(&CONFIG_RGB_LED_TIM_HANDLE, TIM_CHANNEL_2)
#define SET_RED_LED_OFF												HAL_TIM_PWM_Stop(&CONFIG_RGB_LED_TIM_HANDLE, TIM_CHANNEL_2)
#define SET_GREEN_LED_ON											HAL_TIM_PWM_Start(&CONFIG_RGB_LED_TIM_HANDLE, TIM_CHANNEL_3)
#define SET_GREEN_LED_OFF											HAL_TIM_PWM_Stop(&CONFIG_RGB_LED_TIM_HANDLE, TIM_CHANNEL_3)
#define SET_BLUE_LED_ON												HAL_TIM_PWM_Start(&CONFIG_RGB_LED_TIM_HANDLE, TIM_CHANNEL_1)
#define SET_BLUE_LED_OFF											HAL_TIM_PWM_Stop(&CONFIG_RGB_LED_TIM_HANDLE, TIM_CHANNEL_1)

#define SET_RED_LED_DC(b)											__HAL_TIM_SET_COMPARE(&CONFIG_RGB_LED_TIM_HANDLE, TIM_CHANNEL_3, b)
#define SET_GREEN_LED_DC(b)										__HAL_TIM_SET_COMPARE(&CONFIG_RGB_LED_TIM_HANDLE, TIM_CHANNEL_4, b)
#define SET_BLUE_LED_DC(b)										__HAL_TIM_SET_COMPARE(&CONFIG_RGB_LED_TIM_HANDLE, TIM_CHANNEL_2, b)

#define SET_BEEM_LED_ON												__nop()
#define SET_BEEM_LED_OFF											__nop()
#define GET_BEEM_LED													__nop()
#define FLIP_BEEM_LED													__nop()

#define SET_TICK_LED_ON												__nop()
#define SET_TICK_LED_OFF											__nop()
#define GET_TICK_LED													__nop()
#define FLIP_TICK_LED													__nop()
//FLIP_TICK_LED
#define SET_ERR_LED_ON												__nop()
#define SET_ERR_LED_OFF												__nop()
#define GET_ERR_LED														__nop()
#define FLIP_ERR_LED													__nop()

#define SET_LASER_CH0_ON											HAL_GPIO_WritePin(LD0_PWM_GPIO_Port, LD0_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH0_OFF											HAL_GPIO_WritePin(LD0_PWM_GPIO_Port, LD0_PWM_Pin, GPIO_PIN_RESET)
#define SET_LASER_CH1_ON											HAL_GPIO_WritePin(LD1_PWM_GPIO_Port, LD1_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH1_OFF											HAL_GPIO_WritePin(LD1_PWM_GPIO_Port, LD1_PWM_Pin, GPIO_PIN_RESET)
#define SET_LASER_CH2_ON											__nop()
#define SET_LASER_CH2_OFF											__nop()
#define SET_LASER_CH3_ON											__nop()
#define SET_LASER_CH3_OFF											__nop()
#define SET_LASER_CH4_ON											__nop()
#define SET_LASER_CH4_OFF											__nop()
#define SET_LASER_CH5_ON											__nop()
#define SET_LASER_CH5_OFF											__nop()
#define SET_LASER_CH6_ON											__nop()
#define SET_LASER_CH6_OFF											__nop()
#define SET_LASER_CH7_ON											__nop()
#define SET_LASER_CH7_OFF											__nop()

#define SET_TEC_CH0_ON												__nop()
#define SET_TEC_CH0_OFF											__nop()
#define SET_TEC_CH1_ON												__nop()
#define SET_TEC_CH1_OFF												__nop()
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

#define SET_TEC_GATE_CH0_OFF                  __nop()
#define SET_TEC_GATE_CH1_OFF                  __nop()
  
#define SET_TEC_GATE_CH0_ON                   __nop()
#define SET_TEC_GATE_CH1_ON                   __nop() 

#define FLIP_LASER_CH0												HAL_GPIO_TogglePin(LD0_PWM_GPIO_Port, LD0_PWM_Pin)
#define FLIP_LASER_CH1												HAL_GPIO_TogglePin(LD1_PWM_GPIO_Port, LD1_PWM_Pin)
#define FLIP_LASER_CH2												__nop()
#define FLIP_LASER_CH3												__nop()
#define FLIP_LASER_CH4												__nop()
#define FLIP_LASER_CH5												__nop()
#define FLIP_LASER_CH6												__nop()
#define FLIP_LASER_CH7												__nop()

#define GET_LASER_CH0													HAL_GPIO_ReadPin(LD0_PWM_GPIO_Port, LD0_PWM_Pin)
#define GET_LASER_CH1													HAL_GPIO_ReadPin(LD1_PWM_GPIO_Port, LD1_PWM_Pin)
#define GET_LASER_CH2													0
#define GET_LASER_CH3													0
#define GET_LASER_CH4													0
#define GET_LASER_CH5													0
#define GET_LASER_CH6													0
#define GET_LASER_CH7													0

#define SET_FAN0_ON														HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2)
#define SET_FAN0_OFF													HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2)
#define SET_FAN0_TIM_PWM(b)										__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, b)

#define SET_FAN1_ON														__nop()
#define SET_FAN1_OFF													__nop()
#define SET_FAN1_TIM_PWM(b)										__nop()

#define SET_FAN2_ON														__nop()
#define SET_FAN2_OFF													__nop()
#define SET_FAN2_TIM_PWM(b)										__nop()

#define SET_SPK_TIM_ON												HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1)
#define SET_SPK_TIM_OFF												HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_1)

#define SET_RAIM_TIM_OFF											HAL_TIM_PWM_Stop(&CONFIG_AIM_HANDLE, CONFIG_AIM_PWM_CHANNEL)
#define SET_RAIM_TIM_ON												HAL_TIM_PWM_Start(&CONFIG_AIM_HANDLE, CONFIG_AIM_PWM_CHANNEL)
#define SET_RAIM_TIM_PWM(b)										__HAL_TIM_SET_COMPARE(&CONFIG_AIM_HANDLE, CONFIG_AIM_PWM_CHANNEL, b)

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

//MCP41010
#define SET_MCP41010_CS(b)										HAL_GPIO_WritePin(MCP41010_CS_GPIO_Port, MCP41010_CS_Pin, b)
#define SET_MCP41010_SDI(b)										HAL_GPIO_WritePin(MCP41010_SDI_GPIO_Port, MCP41010_SDI_Pin, b)
#define SET_MCP41010_SCK(b)										HAL_GPIO_WritePin(MCP41010_SCK_GPIO_Port, MCP41010_SCK_Pin, b)

//POWER INT MPU软关机中断信号-->LTC2955作为MPU单元
#define GET_PWR_INT														0
//POWER KILL MPU软件关机信号-->LTC2955作为MPU单元
#define SET_PWR_KILL_POWER(b)									__nop()
#define SET_PWR_KILL_POWER_ON									__nop()
#define SET_PWR_KILL_POWER_OFF								__nop()
#define FLIP_PWR_KILL_POWER_KILL							__nop()
#define GET_PWR_KILL_POWER_KILL								__nop()

//POWER LED
#define SET_PWR_LED(b)												__nop()
#define SET_PWR_LED_ON												__nop()
#define SET_PWR_LED_OFF												__nop()
#define GET_PWR_LED														__nop()
#define FLIP_PWR_LED													__nop()

//安全锁接触
#define SET_SAFE_RESET(b)											__nop()
#define SET_SAFE_RESET_ON                    	__nop()
#define SET_SAFE_RESET_OFF                   	__nop()
/*****************************************************************************/
//配置EPROM规格
#define CONFIG_EPROM_SPI											
#define CONFIG_EPROM_SIZE 										CONFIG_MB85RS512TPN_SIZE
#define	CONFIG_AT24C64_SIZE										8192
#define	CONFIG_AT24C128_SIZE 									16384
#define	CONFIG_AT24C256_SIZE 									32768//32K*8
#define CONFIG_FM25W256G_SIZE									32768//32K
#define CONFIG_MB85RS512TPN_SIZE							65536//64K
#define CONFIG_MB85RS2MAT_SIZE								262144//256K
#define CONFIG_EPROM_WRITE_ADDR								0xA0//
#define CONFIG_EPROM_READ_ADDR								0xA1//
#define CONFIG_EPROM_TIMEOUT									1000//EPROM读写超时
#define CONFIG_EPROM_PAGE_SIZE								0x08//EPROM 页大小
#define CONFIG_EPROM_WRITE_DELAY							0//写入等待时间mS
/******************************************************************************/
//配置ADC
#define CONFIG_VREF_CAL                     	*(__IO uint16_t *)(0x1FFF7A2A)//校正电压源
#define CONFIG_ADC1_CHANNEL										13//ADC采集通道
#define ADC_FILTER_ALPHA    									0.25f//0.1f：滤波极强，超平滑 0.25f：平衡响应与滤波（推荐） 0.5f：响应快，滤波弱	
#define CONFIG_ADC1_DMA_BUFFER_SIZE						CONFIG_ADC1_CHANNEL//ADC DMA采集缓冲

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
//配置TEC温控(TIM9 CH2 PWM -> GP8101C-SH -> 模拟电压, 逻辑DAC8)
#define CONFIG_TEC_HT_FF_GAIN								20.0f//散热器温度前馈增益: 温差(×10单位)×增益=叠加计数, 散热器高设定10℃时约叠加49%满幅输出
#define CONFIG_TEC_SLEW_STEP								200//输出变化率限幅: 每500ms控制周期最多变化计数(0~4095), 0→满幅约需10s
#define CONFIG_TEC_TEMP_FILTER_ALPHA				0.5f//反馈温度一阶滤波系数(0~1), 抑制NTC噪声放大

#define HDC1080_SOFTI2C_DELAY									10//HDC1080 I2C读写频率
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

//BK 2K区块(映射硬件BKSRAM 4K掉电保持区)在EPROM储存地址
#define CONFIG_EPROM_BK_START									(CONFIG_EPROM_FD_END + 1)
#define CONFIG_EPROM_BK_END										(CONFIG_EPROM_BK_START + BK_END - BK_START)

#define CONFIG_EPROM_MR_CRC										(CONFIG_EPROM_DM_CRC - 4L)//4B MR NVRAM CRC32 硬件计算
#define CONFIG_EPROM_DM_CRC										(CONFIG_EPROM_FD_CRC - 4L)//4B DM NVRAM CRC32 硬件计算
#define CONFIG_EPROM_FD_CRC										(CONFIG_EPROM_BK_CRC - 4L)//4B FD NVRAM CRC32 硬件计算
#define CONFIG_EPROM_BK_CRC										(CONFIG_EPROM_MCU_FW_CRC - 4L)//4B BK NVRAM CRC32 硬件计算
#define CONFIG_EPROM_MCU_FW_CRC								(CONFIG_EPROM_LCD_FW_CRC - 4L)//4B MCU固件CRC32值 软件计算
#define CONFIG_EPROM_LCD_FW_CRC								(CONFIF_EPROM_TREATMENT_CRC - 4L)//4B LCD固件CRC32值 软件计算
#define CONFIF_EPROM_TREATMENT_CRC						(CONFIG_EPROM_CFG_CRC - 4L)//4B treatment CRC32值 硬件计算
#define CONFIG_EPROM_CFG_CRC									(CONFIG_EPROM_LOG_CRC - 4L)//4B deviceConfig CRC32值 硬件计算
#define CONFIG_EPROM_LOG_CRC									(CONFIG_EPROM_TREATMENT_START - 4L)//4B logInfo CRC32值 硬件计算

#define CONFIG_EPROM_TREATMENT_START					(CONFIG_EPROM_TREATMENT_END - (32L * 1536) + 1L)
#define CONFIG_EPROM_TREATMENT_END						(CONFIG_EPROM_CONFIG_START - 1L)
#define CONFIG_EPROM_TREATMENT_SIZE						(CONFIG_EPROM_TREATMENT_END - CONFIG_EPROM_TREATMENT_START + 1L)//治疗记录区块字节数(32L*1536)

#define CONFIG_EPROM_CONFIG_START							(CONFIG_EPROM_CONFIG_END - 1024L + 1L)//1024B 配置信息区
#define CONFIG_EPROM_CONFIG_END								(CONFIG_EPROM_LOGINFO_START - 1L)
#define CONFIG_EPROM_LOGINFO_START						(CONFIG_EPROM_LOGINFO_END - 256L + 1L)//256B 记录信息区 
#define CONFIG_EPROM_LOGINFO_END							(CONFIG_EPROM_SIZE - 1L)

#if (CONFIG_EPROM_MR_CRC  >= CONFIG_EPROM_FD_END)
	//#error "Please use Arm Compiler Toolchain V4.0.677 or later!"
	//#error "EPROM 容量不足：存储区域重叠，请调小分区或更换更大容量芯片"
#endif
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif






