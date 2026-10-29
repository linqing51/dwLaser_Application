/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
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
//瀹氫箟澶栭儴璧勬簮
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
//瀹氫箟澶栬鎬荤嚎
#define CONFIG_LASER_TIM_HANDLE								htim7
#define CONFIG_LASER_TIM											TIM7

#define CONFIG_SPLC_TIM_HANDLE								htim14//SPLC 璁℃椂鍣ㄥ畾涔?
#define CONFIG_SPLC_TIM												TIM14

#define CONFIG_SPK_HANDLE											htim8//SPK 璁℃椂鍣ㄥ畾涔?
#define CONFIG_SPK_TIM												TIM8
#define CONFIG_SPK_PWM_CHANNEL								TIM_CHANNEL_1

#define CONFIG_FAN0_TIM_HANDLE								htim3	
#define CONFIG_FAN0_TIM												TIM3
#define CONFIG_FAN0_PWM_CHANNEL								TIM_CHANNEL_2
#define CONFIG_FAN0_FG_CHANNEL								TIM_CHANNEL_1

#define CONFIG_RGB_LED_TIM_HANDLE             htim4
#define CONFIG_RGB_LED_TIM                    TIM4
#define CONFIG_RLED_PWM_CHANNEL               TIM_CHANNEL_2
#define CONFIG_GLED_PWM_CHANNEL               TIM_CHANNEL_3
#define CONFIG_BLED_PWM_CHANNEL               TIM_CHANNEL_1

#define CONFIG_AIM_HANDLE											htim5			
#define CONFIG_AIM_PWM_CHANNEL								TIM_CHANNEL_1

#define CONFIG_EPROM_BUS_HANDLE								hspi3//SPLC NVRAM鎺ュ彛瀹氫箟
#define CONFIG_EPROM_BUS											SPI3	

#define CONFIG_DEBUG_UART											huart3//璋冭瘯涓插彛

#define CONFIG_GDDC_UART											huart1//GDDC涓插彛
#define CONFIG_GDDC_UART_INSTANCE							USART1//GDDC涓插彛涓柇
/*****************************************************************************/
//寮曡剼鍔熻兘瀹氫箟
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

#define SET_RED_LED_ON												HAL_TIM_PWM_Start(&CONFIG_RGB_LED_TIM_HANDLE, CONFIG_RLED_PWM_CHANNEL)
#define SET_RED_LED_OFF												HAL_TIM_PWM_Stop(&CONFIG_RGB_LED_TIM_HANDLE, CONFIG_RLED_PWM_CHANNEL)
#define SET_GREEN_LED_ON											HAL_TIM_PWM_Start(&CONFIG_RGB_LED_TIM_HANDLE, CONFIG_GLED_PWM_CHANNEL)
#define SET_GREEN_LED_OFF											HAL_TIM_PWM_Stop(&CONFIG_RGB_LED_TIM_HANDLE, CONFIG_GLED_PWM_CHANNEL)
#define SET_BLUE_LED_ON												HAL_TIM_PWM_Start(&CONFIG_RGB_LED_TIM_HANDLE, CONFIG_BLED_PWM_CHANNEL)
#define SET_BLUE_LED_OFF											HAL_TIM_PWM_Stop(&CONFIG_RGB_LED_TIM_HANDLE, CONFIG_BLED_PWM_CHANNEL)

#define SET_RED_LED_DC(b)											__HAL_TIM_SET_COMPARE(&CONFIG_RGB_LED_TIM_HANDLE, CONFIG_RLED_PWM_CHANNEL, b)
#define SET_GREEN_LED_DC(b)										__HAL_TIM_SET_COMPARE(&CONFIG_RGB_LED_TIM_HANDLE, CONFIG_GLED_PWM_CHANNEL, b)
#define SET_BLUE_LED_DC(b)										__HAL_TIM_SET_COMPARE(&CONFIG_RGB_LED_TIM_HANDLE, CONFIG_BLED_PWM_CHANNEL, b)

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
#define SET_TEC_CH0_OFF											  __nop()
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

#define SET_FAN0_ON														HAL_TIM_PWM_Start(&CONFIG_FAN0_TIM_HANDLE, CONFIG_FAN0_PWM_CHANNEL)
#define SET_FAN0_OFF													HAL_TIM_PWM_Stop(&CONFIG_FAN0_TIM_HANDLE, CONFIG_FAN0_PWM_CHANNEL)
#define SET_FAN0_TIM_PWM(b)										__HAL_TIM_SET_COMPARE(&CONFIG_FAN0_TIM_HANDLE, CONFIG_FAN0_PWM_CHANNEL, b)

#define SET_FAN1_ON														__nop()
#define SET_FAN1_OFF													__nop()
#define SET_FAN1_TIM_PWM(b)										__nop()

#define SET_FAN2_ON														__nop()
#define SET_FAN2_OFF													__nop()
#define SET_FAN2_TIM_PWM(b)										__nop()

#define SET_SPK_TIM_ON												HAL_TIM_PWM_Start(&CONFIG_SPK_HANDLE, CONFIG_SPK_PWM_CHANNEL)
#define SET_SPK_TIM_OFF												HAL_TIM_PWM_Stop(&CONFIG_SPK_HANDLE, CONFIG_SPK_PWM_CHANNEL)

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

//POWER INT MPU杞叧鏈轰腑鏂俊鍙?->LTC2955浣滀负MPU鍗曞厓
#define GET_PWR_INT														0
//POWER KILL MPU杞欢鍏虫満淇″彿-->LTC2955浣滀负MPU鍗曞厓
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

//瀹夊叏閿佹帴瑙?
#define SET_SAFE_RESET(b)											__nop()
#define SET_SAFE_RESET_ON                    	__nop()
#define SET_SAFE_RESET_OFF                   	__nop()
/*****************************************************************************/
//閰嶇疆EPROM瑙勬牸
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
#define CONFIG_EPROM_TIMEOUT									1000//EPROM璇诲啓瓒呮椂
#define CONFIG_EPROM_PAGE_SIZE								0x08//EPROM 椤靛ぇ灏?
#define CONFIG_EPROM_WRITE_DELAY							0//鍐欏叆绛夊緟鏃堕棿mS
/******************************************************************************/
//閰嶇疆ADC
#define CONFIG_VREF_CAL                     	*(__IO uint16_t *)(0x1FFF7A2A)//鏍℃鐢靛帇婧?
#define CONFIG_ADC1_CHANNEL										13//ADC閲囬泦閫氶亾
#define ADC_FILTER_ALPHA    									0.25f//0.1f锛氭护娉㈡瀬寮猴紝瓒呭钩婊?0.25f锛氬钩琛″搷搴斾笌婊ゆ尝锛堟帹鑽愶級 0.5f锛氬搷搴斿揩锛屾护娉㈠急	
#define CONFIG_ADC1_DMA_BUFFER_SIZE						CONFIG_ADC1_CHANNEL//ADC DMA閲囬泦缂撳啿

#define CONFIG_VREF_ADC												SPREG_ADC_59
#define CONFIG_MCU_VREF												3300.0F
#define CONFIG_ADC_AVG_SLOPE									2.5F
#define CONFIG_ADC_V25												760.0F//0.76V@25D

#define CONFIG_DIODE_NTC_RS										3300L//婵€鍏夊櫒鐑晱鐢甸樆鍒嗗帇鐢甸樆鍊?
#define CONFIG_HT0_NTC_RS											4700L//鏁ｇ儹鍣?鐑晱鐢甸樆鍒嗗帇鐢甸樆鍊?
#define CONFIG_HT1_NTC_RS											4700L//鏁ｇ儹鍣?鐑晱鐢甸樆鍒嗗帇鐢甸樆鍊?
#define CONFIG_HT2_NTC_RS											1L	
#define CONFIG_HT3_NTC_RS											1L
#define CONFIG_WATER_HOT_NTC_RS								1L
#define CONFIG_WATER_COOL_NTC_RS							1L
#define CONFIG_AMBIENT_NTC_RS									1L
#define CONFIG_MBAT_NTC_RS										4700L//鐜鐑晱鐢甸樆鍒嗗帇鐢甸樆鍊?

#define CONFIG_DIODE_NTC_B										3477.0F//婵€鍏夊櫒鐑晱鐢甸樆B鍊?
#define CONFIG_HT0_NTC_B											3477.0F//鏁ｇ儹鍣?鐑晱鐢甸樆B鍊?
#define CONFIG_HT1_NTC_B											3477.0F//鏁ｇ儹鍣?鐑晱鐢甸樆B鍊?
#define CONFIG_HT2_NTC_B											3477.0F//鏁ｇ儹鍣?鐑晱鐢甸樆B鍊?
#define CONFIG_HT3_NTC_B											3477.0F//鏁ｇ儹鍣?鐑晱鐢甸樆B鍊?
#define CONFIG_MBAT_NTC_B											3477.0F//鐢垫睜鐑晱鐢甸樆B鍊?

#define CONFIG_WATER_HOT_NTC_B							  3477.0F
#define CONFIG_WATER_COOL_NTC_B								3477.0F
#define CONFIG_AMBIENT_NTC_B									3477.0F

#define CONFIG_NTC_R25												10000.0F//25鎽勬皬搴︽椂鐢甸樆
#define CONFIG_NTC_VREF												3300L//
#define CONFIG_FIBER_PD_THRESHOLD							350//鍏夌氦鎻掑叆鏃禔DC闃堝€?

/*****************************************************************************/
//閰嶇疆TEC娓╂帶(TIM9 CH2 PWM -> GP8101C-SH -> 妯℃嫙鐢靛帇, 閫昏緫DAC8)
#define CONFIG_TEC_HT_FF_GAIN								  20.0f//鏁ｇ儹鍣ㄦ俯搴﹀墠棣堝鐩? 娓╁樊(脳10鍗曚綅)脳澧炵泭=鍙犲姞璁℃暟, 鏁ｇ儹鍣ㄩ珮璁惧畾10鈩冩椂绾﹀彔鍔?9%婊″箙杈撳嚭
#define CONFIG_TEC_SLEW_STEP								  200//杈撳嚭鍙樺寲鐜囬檺骞? 姣?00ms鎺у埗鍛ㄦ湡鏈€澶氬彉鍖栬鏁?0~4095), 0鈫掓弧骞呯害闇€10s
#define CONFIG_TEC_TEMP_FILTER_ALPHA			  	0.5f//鍙嶉娓╁害涓€闃舵护娉㈢郴鏁?0~1), 鎶戝埗NTC鍣０鏀惧ぇ

#define HDC1080_SOFTI2C_DELAY									10//HDC1080 I2C璇诲啓棰戠巼
//G5板未装配HDC1080温湿度传感器(6M3S同款空实现), 后续接硬件时改为真实引脚
#define SET_HDC1080_SCL(b)										__nop()
#define SET_HDC1080_SDA(b)										__nop()
#define GET_HDC1080_SDA												0
/*****************************************************************************/
//閰嶇疆DAC
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
//閰嶇疆EPROM鏁版嵁鍦板潃
#define CONFIG_EPROM_MR_START									(0x0L)//
#define CONFIG_EPROM_MR_END										(CONFIG_EPROM_MR_START + MR_END - MR_START)
#define CONFIG_EPROM_DM_START									(CONFIG_EPROM_MR_END + 1)//NVRAM涓璂M鍦‥PROM鍌ㄥ瓨鍦板潃
#define CONFIG_EPROM_DM_END										(CONFIG_EPROM_DM_START + DM_END - DM_START)

#define CONFIG_EPROM_FD_SCHEME_SIZE						((FD_SCHEME_END_0 - FD_SCHEME_START_0 + 1) * 2)//鍗曚釜鏂规鍗犵敤鐨凟PROM绌洪棿
#define CONFIG_EPROM_FD_START									(CONFIG_EPROM_DM_END + 1)
#define CONFIG_EPROM_FD_END										(CONFIG_EPROM_FD_START + FD_END - FD_START)

//BK 2K鍖哄潡(鏄犲皠纭欢BKSRAM 4K鎺夌數淇濇寔鍖?鍦‥PROM鍌ㄥ瓨鍦板潃
#define CONFIG_EPROM_BK_START									(CONFIG_EPROM_FD_END + 1)
#define CONFIG_EPROM_BK_END										(CONFIG_EPROM_BK_START + BK_END - BK_START)

#define CONFIG_EPROM_MR_CRC										(CONFIG_EPROM_DM_CRC - 4L)//4B MR NVRAM CRC32 纭欢璁＄畻
#define CONFIG_EPROM_DM_CRC										(CONFIG_EPROM_FD_CRC - 4L)//4B DM NVRAM CRC32 纭欢璁＄畻
#define CONFIG_EPROM_FD_CRC										(CONFIG_EPROM_BK_CRC - 4L)//4B FD NVRAM CRC32 纭欢璁＄畻
#define CONFIG_EPROM_BK_CRC										(CONFIG_EPROM_MCU_FW_CRC - 4L)//4B BK NVRAM CRC32 纭欢璁＄畻
#define CONFIG_EPROM_MCU_FW_CRC								(CONFIG_EPROM_LCD_FW_CRC - 4L)//4B MCU鍥轰欢CRC32鍊?杞欢璁＄畻
#define CONFIG_EPROM_LCD_FW_CRC								(CONFIF_EPROM_TREATMENT_CRC - 4L)//4B LCD鍥轰欢CRC32鍊?杞欢璁＄畻
#define CONFIF_EPROM_TREATMENT_CRC						(CONFIG_EPROM_CFG_CRC - 4L)//4B treatment CRC32鍊?纭欢璁＄畻
#define CONFIG_EPROM_CFG_CRC									(CONFIG_EPROM_LOG_CRC - 4L)//4B deviceConfig CRC32鍊?纭欢璁＄畻
#define CONFIG_EPROM_LOG_CRC									(CONFIG_EPROM_TREATMENT_START - 4L)//4B logInfo CRC32鍊?纭欢璁＄畻

#define CONFIG_EPROM_TREATMENT_START					(CONFIG_EPROM_TREATMENT_END - (32L * 1536) + 1L)
#define CONFIG_EPROM_TREATMENT_END						(CONFIG_EPROM_CONFIG_START - 1L)
#define CONFIG_EPROM_TREATMENT_SIZE						(CONFIG_EPROM_TREATMENT_END - CONFIG_EPROM_TREATMENT_START + 1L)//娌荤枟璁板綍鍖哄潡瀛楄妭鏁?32L*1536)

#define CONFIG_EPROM_CONFIG_START							(CONFIG_EPROM_CONFIG_END - 1024L + 1L)//1024B 閰嶇疆淇℃伅鍖?
#define CONFIG_EPROM_CONFIG_END								(CONFIG_EPROM_LOGINFO_START - 1L)
#define CONFIG_EPROM_LOGINFO_START						(CONFIG_EPROM_LOGINFO_END - 256L + 1L)//256B 璁板綍淇℃伅鍖?
#define CONFIG_EPROM_LOGINFO_END							(CONFIG_EPROM_SIZE - 1L)

#if (CONFIG_EPROM_BK_END >= CONFIG_EPROM_MR_CRC)
	#error "EPROM 瀹归噺涓嶈冻锛氬瓨鍌ㄥ尯鍩熼噸鍙狅紝璇疯皟灏忓垎鍖烘垨鏇存崲鏇村ぇ瀹归噺鑺墖"
#endif
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif






