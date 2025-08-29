#ifndef __BOARDCONFIG_H__
#define __BOARDCONFIG_H__
/*****************************************************************************/
//#define MODEL_PVGLS_15W_1470_A0
//#define MODEL_PVGLS_TRI_A0
//#define MODEL_PVGLS_TRI_COMBINE_A0
//#define MODEL_PVGLS_15W_1470_A1
/****************************************************************************/
//#define MODEL_PVGLS_10W_1940_A1
/****************************************************************************/
//#define MODEL_PVGLS_7W_1940_A0
/*****************************************************************************/
//#define GLOAL_LDR2P1_G5_A1_20250731_DUAL
//#define GLOAL_LDR2P1_G5_A1_20250731_TRIP
/*****************************************************************************/
#include "cmsis_os.h"
#include "main.h"
#include "arm_math.h"
#include "usbh_core.h"
/*****************************************************************************/
#if defined(GLOAL_LDR2P1_G5_A1_20250731_DUAL) || defined(GLOAL_LDR2P1_G5_A1_20250731_TRIP)
extern ADC_HandleTypeDef hadc1;
extern CRC_HandleTypeDef hcrc;
extern DAC_HandleTypeDef hdac;
extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;
extern RNG_HandleTypeDef hrng;
extern SPI_HandleTypeDef hspi3;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim14;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;
extern USBH_HandleTypeDef hUsbHostHS;
extern USBH_HandleTypeDef hUsbHostFS;
#endif

#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart4;
extern USBH_HandleTypeDef hUsbHostFS;
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
extern CRC_HandleTypeDef hcrc;
extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim2;//AIM PWM
extern TIM_HandleTypeDef htim3;//LED PWM
extern TIM_HandleTypeDef htim7;//DAC DMA 计时器
extern TIM_HandleTypeDef htim10;//Laser Timer
extern TIM_HandleTypeDef htim12;//FAN PWM
extern TIM_HandleTypeDef htim14;//sPlc Timer
extern RNG_HandleTypeDef hrng;
#endif
/*****************************************************************************/
#if defined(MODEL_PVGLS_10W_1940_A1)
extern I2C_HandleTypeDef hi2c2;//EPROM
extern UART_HandleTypeDef huart1;//ANDRIOD OR DEBUG
extern UART_HandleTypeDef huart3;//DC HMI
extern UART_HandleTypeDef huart5;//NFC
extern USBH_HandleTypeDef hUsbHostFS;
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
extern CRC_HandleTypeDef hcrc;
extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim2;//SPEAK
extern TIM_HandleTypeDef htim3;//FAN
extern TIM_HandleTypeDef htim4;//LED
extern TIM_HandleTypeDef htim10;//Laser Timer
extern TIM_HandleTypeDef htim12;//AIM Timer
extern TIM_HandleTypeDef htim14;//sPlc Timer
extern RNG_HandleTypeDef hrng;
#endif
/*****************************************************************************/
//引脚功能定义
#if defined(GLOAL_LDR2P1_G5_A1_20250731_DUAL) || defined(GLOAL_LDR2P1_G5_A1_20250731_TRIP)
#define SET_EDAC0_CS(b)												
#define SET_EDAC1_CS(b)												
#define SET_EDAC2_CS(b)												
#define SET_EDAC3_CS(b)											
#define SET_EDAC4_CS(b)												
#define SET_EDAC5_CS(b)												
#define SET_EDAC6_CS(b)												
#define SET_EDAC7_CS(b)												HAL_GPIO_WritePin(EDAC7_CS_GPIO_Port, EDAC7_CS_Pin, b)											

#define SET_EDAC0_SCK(b)
#define SET_EDAC1_SCK(b)											
#define SET_EDAC2_SCK(b)											
#define SET_EDAC3_SCK(b)			
#define SET_EDAC4_SCK(b)
#define SET_EDAC5_SCK(b)											
#define SET_EDAC6_SCK(b)											
#define SET_EDAC7_SCK(b)											HAL_GPIO_WritePin(EDAC7_SCK_GPIO_Port, EDAC7_SCK_Pin, b)				

#define SET_EDAC0_SDI(b)											
#define SET_EDAC1_SDI(b)											
#define SET_EDAC2_SDI(b)											
#define SET_EDAC3_SDI(b)											
#define SET_EDAC4_SDI(b)											
#define SET_EDAC5_SDI(b)											
#define SET_EDAC6_SDI(b)											
#define SET_EDAC7_SDI(b)											HAL_GPIO_WritePin(EDAC7_SDI_GPIO_Port, EDAC7_SDI_Pin, b)

#define SET_RED_LED_ON												HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3)
#define SET_RED_LED_OFF												HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3)
#define SET_GREEN_LED_ON											HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4)
#define SET_GREEN_LED_OFF											HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4)
#define SET_BLUE_LED_ON												HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2)
#define SET_BLUE_LED_OFF											HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2)

#define SET_RED_LED_DC(b)											__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, b)
#define SET_GREEN_LED_DC(b)										__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, b)
#define SET_BLUE_LED_DC(b)										__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, b)

#define SET_ERR_LED_ON												HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_SET)
#define SET_ERR_LED_OFF												HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_SET)
#define GET_ERR_LED														HAL_GPIO_ReadPin(ERR_LED_GPIO_Port, ERR_LED_Pin)
#define FLIP_ERR_LED													HAL_GPIO_ReadPin(ERR_LED_GPIO_Port, ERR_LED_Pin)

#define SET_TICK_LED_ON												HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, GPIO_PIN_SET)
#define SET_TICK_LED_OFF											HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, GPIO_PIN_RESET)
#define GET_TICK_LED													HAL_GPIO_ReadPin(TICK_LED_GPIO_Port, TICK_LED_Pin)
#define FLIP_TICK_LED													HAL_GPIO_TogglePin(TICK_LED_GPIO_Port, TICK_LED_Pin)

#define SET_LASER_CH0_ON											HAL_GPIO_WritePin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin, GPIO_PIN_SET)
#define SET_LASER_CH0_OFF											HAL_GPIO_WritePin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin, GPIO_PIN_RESET)

#define SET_LASER_CH1_ON											HAL_GPIO_WritePin(LAS_PWM1_GPIO_Port, LAS_PWM1_Pin, GPIO_PIN_SET)
#define SET_LASER_CH1_OFF											HAL_GPIO_WritePin(LAS_PWM1_GPIO_Port, LAS_PWM1_Pin, GPIO_PIN_RESET)

#define FLIP_LASER_CH0												HAL_GPIO_TogglePin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin)
#define FLIP_LASER_CH1												HAL_GPIO_TogglePin(LAS_PWM1_GPIO_Port, LAS_PWM1_Pin)

#define GET_LASER_CH0													HAL_GPIO_ReadPin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin)
#define GET_LASER_CH1													HAL_GPIO_ReadPin(LAS_PWM1_GPIO_Port, LAS_PWM1_Pin)

#define SET_BEEM_LED_ON												HAL_GPIO_WritePin(BEEM_LED_GPIO_Port, BEEM_LED_Pin, GPIO_PIN_SET)
#define SET_BEEM_LED_OFF											HAL_GPIO_WritePin(BEEM_LED_GPIO_Port, BEEM_LED_Pin, GPIO_PIN_SET)
#define GET_BEEM_LED													HAL_GPIO_ReadPin(BEEM_LED_GPIO_Port, BEEM_LED_Pin)
#define FLIP_BEEM_LED													HAL_GPIO_ReadPin(BEEM_LED_GPIO_Port, BEEM_LED_Pin)

#define SET_FAN_ON														HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2)
#define SET_FAN_OFF														HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2)
#define SET_FAN_TIM_PWM(b)										__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, b)

#define SET_SPK_TIM_ON												HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1)
#define SET_SPK_TIM_OFF												HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_1)

#define SET_AIM_TIM_OFF												HAL_TIM_PWM_Stop(&htim10, TIM_CHANNEL_1)
#define SET_AIM_TIM_ON												HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1)
#define SET_AIM_TIM_PWM(b)										__HAL_TIM_SET_COMPARE(&htim10, TIM_CHANNEL_1, b)

//MCP41010
#define SET_MCP41010_CS(b)										HAL_GPIO_WritePin(MCP41010_CS_GPIO_Port, MCP41010_CS_Pin, b)
#define SET_MCP41010_SDI(b)										HAL_GPIO_WritePin(MCP41010_SDI_GPIO_Port, MCP41010_SDI_Pin, b)
#define SET_MCP41010_SCK(b)										HAL_GPIO_WritePin(MCP41010_SCK_GPIO_Port, MCP41010_SCK_Pin, b)
#endif
/*****************************************************************************/
#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
/*****************************************************************************/
#define MCP4821_NSHDN_MASK										(1 << 12)
#define MCP4821_NGA_MASK											(1 << 13)
/*****************************************************************************/
#define SET_EDAC0_CS(b)												HAL_GPIO_WritePin(EDAC0_CS_GPIO_Port, EDAC0_CS_Pin, b)
#define SET_EDAC1_CS(b)												HAL_GPIO_WritePin(EDAC1_CS_GPIO_Port, EDAC1_CS_Pin, b)
#define SET_EDAC2_CS(b)												HAL_GPIO_WritePin(EDAC2_CS_GPIO_Port, EDAC2_CS_Pin, b)
#define SET_EDAC3_CS(b)												HAL_GPIO_WritePin(EDAC3_CS_GPIO_Port, EDAC3_CS_Pin, b)
#define SET_EDAC0_SCK(b)											HAL_GPIO_WritePin(EDAC0_SCK_GPIO_Port, EDAC0_SCK_Pin, b)
#define SET_EDAC1_SCK(b)											HAL_GPIO_WritePin(EDAC1_SCK_GPIO_Port, EDAC1_SCK_Pin, b)
#define SET_EDAC2_SCK(b)											HAL_GPIO_WritePin(EDAC2_SCK_GPIO_Port, EDAC2_SCK_Pin, b)
#define SET_EDAC3_SCK(b)											HAL_GPIO_WritePin(EDAC3_SCK_GPIO_Port, EDAC3_SCK_Pin, b)
#define SET_EDAC0_SDI(b)											HAL_GPIO_WritePin(EDAC0_SDI_GPIO_Port, EDAC0_SDI_Pin, b)
#define SET_EDAC1_SDI(b)											HAL_GPIO_WritePin(EDAC1_SDI_GPIO_Port, EDAC1_SDI_Pin, b)
#define SET_EDAC2_SDI(b)											HAL_GPIO_WritePin(EDAC2_SDI_GPIO_Port, EDAC2_SDI_Pin, b)
#define SET_EDAC3_SDI(b)											HAL_GPIO_WritePin(EDAC3_SDI_GPIO_Port, EDAC3_SDI_Pin, b)
/*****************************************************************************/
#define SET_RED_LED_ON												HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2)
#define SET_RED_LED_OFF												HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2)
#define SET_GREEN_LED_ON											HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3)
#define SET_GREEN_LED_OFF											HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3)
#define SET_BLUE_LED_ON												HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1)
#define SET_BLUE_LED_OFF											HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1)

#define SET_RED_LED_DC(b)											__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, b)
#define SET_GREEN_LED_DC(b)										__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, b)
#define SET_BLUE_LED_DC(b)										__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, b)

#define SET_ERR_LED_ON												HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_SET)
#define SET_ERR_LED_OFF												HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_SET)
#define GET_ERR_LED														HAL_GPIO_ReadPin(ERR_LED_GPIO_Port, ERR_LED_Pin)
#define FLIP_ERR_LED													HAL_GPIO_ReadPin(ERR_LED_GPIO_Port, ERR_LED_Pin)
#define SET_TICK_LED_ON												HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, GPIO_PIN_SET)
#define SET_TICK_LED_OFF											HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, GPIO_PIN_RESET)
#define GET_TICK_LED													HAL_GPIO_ReadPin(TICK_LED_GPIO_Port, TICK_LED_Pin)
#define FLIP_TICK_LED													HAL_GPIO_TogglePin(TICK_LED_GPIO_Port, TICK_LED_Pin)

#define SET_LASER_CH0_ON											HAL_GPIO_WritePin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin, GPIO_PIN_SET)
#define SET_LASER_CH0_OFF											HAL_GPIO_WritePin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin, GPIO_PIN_RESET)

#define SET_LASER_CH1_ON											HAL_GPIO_WritePin(LAS_PWM1_GPIO_Port, LAS_PWM1_Pin, GPIO_PIN_SET);HAL_GPIO_WritePin(LAS_PWM2_GPIO_Port, LAS_PWM2_Pin, GPIO_PIN_SET)
#define SET_LASER_CH1_OFF											HAL_GPIO_WritePin(LAS_PWM1_GPIO_Port, LAS_PWM1_Pin, GPIO_PIN_RESET);HAL_GPIO_WritePin(LAS_PWM2_GPIO_Port, LAS_PWM2_Pin, GPIO_PIN_RESET)

#define FLIP_LASER_CH0												HAL_GPIO_TogglePin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin)
#define FLIP_LASER_CH1												HAL_GPIO_TogglePin(LAS_PWM1_GPIO_Port, LAS_PWM1_Pin);HAL_GPIO_TogglePin(LAS_PWM2_GPIO_Port, LAS_PWM2_Pin)

#define GET_LASER_CH0													HAL_GPIO_ReadPin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin)
#define GET_LASER_CH1													HAL_GPIO_ReadPin(LAS_PWM1_GPIO_Port, LAS_PWM1_Pin)

#define SET_FAN_ON														HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2)
#define SET_FAN_OFF														HAL_TIM_PWM_Stop(&htim12, TIM_CHANNEL_2)

extern uint16_t audioSineTable[]; 
#define SET_SPK_TIM_OFF												HAL_TIM_Base_Stop(&htim7);HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1)
#define SET_SPK_TIM_ON												HAL_TIM_Base_Start(&htim7);HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t *)audioSineTable, 256, DAC_ALIGN_12B_R)	

#define SET_AIM_TIM_OFF												HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1)
#define SET_AIM_TIM_ON												HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1)
#define SET_AIM_TIM_PWM(b)										__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, b)
#endif
/*****************************************************************************/
#if defined(MODEL_PVGLS_10W_1940_A1)
#define SET_RED_LED_ON												HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3)
#define SET_RED_LED_OFF												HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3)
#define SET_GREEN_LED_ON											HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2)
#define SET_GREEN_LED_OFF											HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2)
#define SET_BLUE_LED_ON												HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4)
#define SET_BLUE_LED_OFF											HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4)

#define SET_BLUE_LED_DC(b)										__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, b)
#define SET_RED_LED_DC(b)											__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, b)
#define SET_GREEN_LED_DC(b)										__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, b)

#define SET_ERR_LED_ON												HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_SET)
#define SET_ERR_LED_OFF												HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_SET)
#define GET_ERR_LED														HAL_GPIO_ReadPin(ERR_LED_GPIO_Port, ERR_LED_Pin)
#define FLIP_ERR_LED													HAL_GPIO_ReadPin(ERR_LED_GPIO_Port, ERR_LED_Pin)
#define SET_TICK_LED_ON												HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, GPIO_PIN_SET)
#define SET_TICK_LED_OFF											HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, GPIO_PIN_RESET)
#define GET_TICK_LED													HAL_GPIO_ReadPin(TICK_LED_GPIO_Port, TICK_LED_Pin)
#define FLIP_TICK_LED													HAL_GPIO_TogglePin(TICK_LED_GPIO_Port, TICK_LED_Pin)

#define SET_BEEM_LED_ON												HAL_GPIO_WritePin(BEEM_LED_GPIO_Port, BEEM_LED_Pin, GPIO_PIN_SET)
#define SET_BEEM_LED_OFF											HAL_GPIO_WritePin(BEEM_LED_GPIO_Port, BEEM_LED_Pin, GPIO_PIN_SET)
#define GET_BEEM_LED													HAL_GPIO_ReadPin(BEEM_LED_GPIO_Port, BEEM_LED_Pin)
#define FLIP_BEEM_LED													HAL_GPIO_ReadPin(BEEM_LED_GPIO_Port, BEEM_LED_Pin)

//MCP41010
#define SET_MCP41010_CS(b)										HAL_GPIO_WritePin(MCP41010_CS_GPIO_Port, MCP41010_CS_Pin, b)
#define SET_MCP41010_SDI(b)										HAL_GPIO_WritePin(MCP41010_SDI_GPIO_Port, MCP41010_SDI_Pin, b)
#define SET_MCP41010_SCK(b)										HAL_GPIO_WritePin(MCP41010_SCK_GPIO_Port, MCP41010_SCK_Pin, b)

//HGC5615
#define SET_HGC5615_CS(b)											HAL_GPIO_WritePin(HGC5615_CS_GPIO_Port, HGC5615_CS_Pin, b)
#define SET_HGC5615_SDI(b)										HAL_GPIO_WritePin(HGC5615_SDI_GPIO_Port, HGC5615_SDI_Pin, b)
#define SET_HGC5615_SCK(b)										HAL_GPIO_WritePin(HGC5615_SCK_GPIO_Port, HGC5615_SCK_Pin, b)

#define SET_LASER_CH0_ON											HAL_GPIO_WritePin(LAS_PWM_GPIO_Port, LAS_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH0_OFF											HAL_GPIO_WritePin(LAS_PWM_GPIO_Port, LAS_PWM_Pin, GPIO_PIN_RESET)
#define FLIP_LASER_CH0												HAL_GPIO_TogglePin(LAS_PWM_GPIO_Port, LAS_PWM_Pin)
#define GET_LASER_CH0													HAL_GPIO_ReadPin(LAS_PWM_GPIO_Port, LAS_PWM_Pin)

#define SET_LASER_CH1_ON											HAL_GPIO_WritePin(LAS_PWM_GPIO_Port, LAS_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH1_OFF											HAL_GPIO_WritePin(LAS_PWM_GPIO_Port, LAS_PWM_Pin, GPIO_PIN_RESET)
#define FLIP_LASER_CH1												HAL_GPIO_TogglePin(LAS_PWM_GPIO_Port, LAS_PWM_Pin)
#define GET_LASER_CH1													HAL_GPIO_ReadPin(LAS_PWM_GPIO_Port, LAS_PWM_Pin)

#define SET_FAN_ON														HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1)
#define SET_FAN_OFF														HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1)
#define SET_FAN_TIM_PWM(b)										__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, b)

#define SET_SPK_TIM_ON												HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2)
#define SET_SPK_TIM_OFF												HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2)

#define SET_AIM_TIM_OFF												HAL_TIM_PWM_Stop(&htim12, TIM_CHANNEL_2)
#define SET_AIM_TIM_ON												HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2)
#define SET_AIM_TIM_PWM(b)										__HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, b)
#endif
/*****************************************************************************/
#define GET_ESTOP_NC													HAL_GPIO_ReadPin(ESTOP_NC_GPIO_Port, ESTOP_NC_Pin)
#define GET_INTERLOCK_NC											HAL_GPIO_ReadPin(INTERLOCK_NC_GPIO_Port, INTERLOCK_NC_Pin)
#define GET_FSWITCH_NO												HAL_GPIO_ReadPin(FS_NO_GPIO_Port, FS_NO_Pin)
#define GET_FSWITCH_NC												HAL_GPIO_ReadPin(FS_NC_GPIO_Port, FS_NC_Pin)

#define SET_SPK_AP_ON													HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_RESET)
#define SET_SPK_AP_OFF												HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_SET)

#define SET_TEC_ON														HAL_GPIO_WritePin(TEC_PWM_GPIO_Port, TEC_PWM_Pin, GPIO_PIN_SET)
#define SET_TEC_OFF														HAL_GPIO_WritePin(TEC_PWM_GPIO_Port, TEC_PWM_Pin, GPIO_PIN_RESET)
/*****************************************************************************/
#if defined(GLOAL_LDR2P1_G5_A1_20250731_DUAL) || defined(GLOAL_LDR2P1_G5_A1_20250731_TRIP)
#define CONFIG_LASER_TIM_HANDLE								htim7
#define CONFIG_SPLC_TIM_HANDLE								htim14//SPLC 计时器定义	
#define CONFIG_RPROM_BUS											hi2c1//SPLC NVRAM接口定义
#define CONFIG_GDDC_UART											huart2//GDDC串口
#define CONFIG_GDDC_UART_INSTANCE							USART2//GDDC串口中断
#define CONFIG_EPROM_SIZE 										CONFIG_AT24C64_SIZE
#define CONFIG_SPLC_ADC_CHANNEL								13//ADC采集通道
#define CONFIG_SPLC_ADC_AVERAGE_NUM						8//ADC平均值次数
#endif

#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
#define CONFIG_LASER_TIM_HANDLE								htim10//LASER 定时器
#define CONFIG_SPLC_TIM_HANDLE								htim14//SPLC 计时器定义	
#define CONFIG_RPROM_BUS											hi2c1//SPLC NVRAM接口定义
#define CONFIG_GDDC_UART											huart4
#define CONFIG_GDDC_UART_INSTANCE							UART4
#define CONFIG_EPROM_SIZE 										CONFIG_AT24C64_SIZE
#define CONFIG_SPLC_ADC_CHANNEL								7//ADC采集通道
#define CONFIG_SPLC_ADC_AVERAGE_NUM						8//ADC平均值次数
#endif

#if defined(MODEL_PVGLS_10W_1940_A1)
#define CONFIG_LASER_TIM_HANDLE								htim10//LASER 定时器
#define CONFIG_SPLC_TIM_HANDLE								htim14//SPLC 计时器定义	
#define CONFIG_RPROM_BUS											hi2c2//SPLC NVRAM接口定义
#define CONFIG_GDDC_UART											huart3
#define CONFIG_GDDC_UART_INSTANCE							USART3
#define CONFIG_EPROM_SIZE 										CONFIG_AT24C64_SIZE
#define CONFIG_SPLC_ADC_CHANNEL								10//ADC采集通道
#define CONFIG_SPLC_ADC_AVERAGE_NUM						8//ADC平均值次数
#endif

//NVRAM EPROM 定义
#define	CONFIG_AT24C64_SIZE										8192
#define	CONFIG_AT24C128_SIZE 									16384
#define	CONFIG_AT24C256_SIZE 									32768//32K*8
#define CONFIG_EPROM_WRITE_ADDR								0xA0//
#define CONFIG_EPROM_READ_ADDR								0xA1//
#define CONFIG_EPROM_TIMEOUT									1000//EPROM读写超时
#define CONFIG_EPROM_PAGE_SIZE								0x08//EPROM 页大小
#define CONFIG_EPROM_WRITE_DELAY							0//写入等待时间mS
/*****************************************************************************/
#define CONFIG_ADC_DMA_BUFFER_SIZE						(CONFIG_SPLC_ADC_CHANNEL * CONFIG_SPLC_ADC_AVERAGE_NUM)//ADC DMA采集缓冲
#define CONFIG_AMBIENT_TEMP             			25// Ambient temp in deg C
#define CONFIG_VREF_CAL                     	*(__IO uint16_t *)(0x1FFF7A2A)//校正电压源

#define CONFIG_VREF_ADC												SPREG_ADC_14
#define CONFIG_ADC_AVG_SLOPE									2.5F
#define CONFIG_ADC_V25												760.0F//0.76V@25D
#define CONFIG_NTC_RS													4700L//NTC分压电阻
#define CONFIG_NTC_B													3477.0F
#define CONFIG_NTC_R25												10000.0F//25摄氏度时电阻
#define CONFIG_NTC_VREF												3300L//
#define CONFIG_FIBER_PD_THRESHOLD							600//光纤插入时ADC阈值

#endif



