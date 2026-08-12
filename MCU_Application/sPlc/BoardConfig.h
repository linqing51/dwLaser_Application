#ifndef __BOARDCONFIG_H__
#define __BOARDCONFIG_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
#include "main.h"
#ifndef LYPE_SURGI_LDR5_20260519
#include "usbh_core.h"
#endif
/*****************************************************************************/
//定义外部资源
#if defined(LDR2P1_G5_A1_20250731_DUAL) || defined(LDR2P1_G5_A1_20250910_DUAL) || defined(LDR2P1_G5_A1_20250731_TRIP) || defined(LDR2P1_G5_A1_20250910_TRIP)
extern ADC_HandleTypeDef hadc1;
extern CRC_HandleTypeDef hcrc;
extern RNG_HandleTypeDef hrng;
extern DAC_HandleTypeDef hdac;//LAS0 LAS1
extern I2C_HandleTypeDef hi2c1;//EPROM I2C
extern I2C_HandleTypeDef hi2c2;//DEV I2C
extern SPI_HandleTypeDef hspi3;//DEV SPI3
extern TIM_HandleTypeDef htim3;//RGB LED TIM
extern TIM_HandleTypeDef htim4;//FAN TIM
extern TIM_HandleTypeDef htim7;//LASER TIM
extern TIM_HandleTypeDef htim8;//SKP TIM
extern TIM_HandleTypeDef htim10;//AIM TIM
extern TIM_HandleTypeDef htim14;//SPLC TIM
extern UART_HandleTypeDef huart1;//DBG UART
extern UART_HandleTypeDef huart2;//GDDC UART
extern UART_HandleTypeDef huart3;//BT/DEV UART
extern UART_HandleTypeDef huart6;//NFS UART
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
extern RNG_HandleTypeDef hrng;
extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim2;//AIM PWM
extern TIM_HandleTypeDef htim3;//LED PWM
extern TIM_HandleTypeDef htim7;//DAC DMA 计时器
extern TIM_HandleTypeDef htim10;//Laser Timer
extern TIM_HandleTypeDef htim12;//FAN PWM
extern TIM_HandleTypeDef htim14;//sPlc Timer
#endif

#if defined(MODEL_PVGLS_10W_1940_A1)
extern I2C_HandleTypeDef hi2c2;//EPROM
extern UART_HandleTypeDef huart1;//ANDRIOD OR DEBUG
extern UART_HandleTypeDef huart3;//DC HMI
extern UART_HandleTypeDef huart5;//NFC
extern USBH_HandleTypeDef hUsbHostFS;
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
extern CRC_HandleTypeDef hcrc;
extern RNG_HandleTypeDef hrng;
extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim2;//SPEAK
extern TIM_HandleTypeDef htim3;//FAN
extern TIM_HandleTypeDef htim4;//LED
extern TIM_HandleTypeDef htim10;//Laser Timer
extern TIM_HandleTypeDef htim12;//AIM Timer
extern TIM_HandleTypeDef htim14;//sPlc Timer
#endif

#if defined(LYPE_MCU_1V0_20260106)
extern UART_HandleTypeDef huart1;//RASPI
extern UART_HandleTypeDef huart3;//DC HMI
extern UART_HandleTypeDef huart5;//DEBUG
extern SPI_HandleTypeDef hspi3;
extern I2C_HandleTypeDef hi2c3;//IBUS I2C

extern TIM_HandleTypeDef htim5;//GAIM TIM
extern TIM_HandleTypeDef htim8;//FAN TIM
extern TIM_HandleTypeDef htim7;//LASER TIM
extern TIM_HandleTypeDef htim9;//SKP TIM
extern TIM_HandleTypeDef htim12;//RAIM  TIM
extern TIM_HandleTypeDef htim14;//SPLC  TIM
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc3;
extern DMA_HandleTypeDef hdma_adc1;
extern DMA_HandleTypeDef hdma_adc3;
extern CRC_HandleTypeDef hcrc;
extern RNG_HandleTypeDef hrng;
extern DAC_HandleTypeDef hdac;
extern USBH_HandleTypeDef hUsbHostFS;//UDISK WFS
#endif

#if defined(LYPE_SURGI_LDR5_20260519)
extern UART_HandleTypeDef huart1;//DEBUG
extern UART_HandleTypeDef huart2;//HMI
extern UART_HandleTypeDef huart6;//COMM
extern SPI_HandleTypeDef hspi2;
extern TIM_HandleTypeDef htim7;//LASER TIM
extern TIM_HandleTypeDef htim14;//SPLC  TIM
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
extern CRC_HandleTypeDef hcrc;
extern RNG_HandleTypeDef hrng;
extern DAC_HandleTypeDef hdac;
//extern USBH_HandleTypeDef hUsbHostFS;//UDISK WFS
#endif

#if defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
extern UART_HandleTypeDef huart1;//RASPI
extern UART_HandleTypeDef huart3;//BT UART
extern UART_HandleTypeDef huart4;//GDDC LCD
extern UART_HandleTypeDef huart6;//DEBUG
extern SPI_HandleTypeDef hspi3;
extern I2C_HandleTypeDef hi2c2;//MPU I2C
extern TIM_HandleTypeDef htim2;//SKP TIM
extern TIM_HandleTypeDef htim3;//FAN TIM
extern TIM_HandleTypeDef htim4;//RGB LED
extern TIM_HandleTypeDef htim7;//LASER TIM
extern TIM_HandleTypeDef htim9;//RAIM  TIM
extern TIM_HandleTypeDef htim14;//SPLC  TIM
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
extern CRC_HandleTypeDef hcrc;
extern RNG_HandleTypeDef hrng;
extern DAC_HandleTypeDef hdac;
extern USBH_HandleTypeDef hUsbHostFS;//UDISK WFS
#endif

/*****************************************************************************/
//引脚功能定义
#if defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP)
#define GET_ESTOP_NC													HAL_GPIO_ReadPin(ESTOP_NC_GPIO_Port, ESTOP_NC_Pin)
#define GET_INTERLOCK_NC											HAL_GPIO_ReadPin(INTERLOCK_NC_GPIO_Port, INTERLOCK_NC_Pin)
#define GET_FSWITCH_NO												HAL_GPIO_ReadPin(FS_NO_GPIO_Port, FS_NO_Pin)
#define GET_FSWITCH_NC												HAL_GPIO_ReadPin(FS_NC_GPIO_Port, FS_NC_Pin)

#define SET_SPK_AP_ON													HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_RESET)
#define SET_SPK_AP_OFF												HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_SET)

#define SET_DAC7311_CS(b)											HAL_GPIO_WritePin(DAC7311_CS_GPIO_Port, DAC7311_CS_Pin, b)												
#define SET_DAC7311_SCK(b)                    HAL_GPIO_WritePin(DAC7311_SCK_GPIO_Port, DAC7311_SCK_Pin, b)
#define SET_DAC7311_SDI(b)										HAL_GPIO_WritePin(DAC7311_SDI_GPIO_Port, DAC7311_SDI_Pin, b)	

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

#define SET_RED_LED_ON												HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3)
#define SET_RED_LED_OFF												HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3)
#define SET_GREEN_LED_ON											HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4)
#define SET_GREEN_LED_OFF											HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4)
#define SET_BLUE_LED_ON												HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2)
#define SET_BLUE_LED_OFF											HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2)

#define SET_RED_LED_DC(b)											__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, b)
#define SET_GREEN_LED_DC(b)										__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, b)
#define SET_BLUE_LED_DC(b)										__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, b)

#define SET_BEEM_LED_ON												HAL_GPIO_WritePin(BEEM_LED_GPIO_Port, BEEM_LED_Pin, GPIO_PIN_SET)
#define SET_BEEM_LED_OFF											HAL_GPIO_WritePin(BEEM_LED_GPIO_Port, BEEM_LED_Pin, GPIO_PIN_RESET)
#define GET_BEEM_LED													HAL_GPIO_ReadPin(BEEM_LED_GPIO_Port, BEEM_LED_Pin)
#define FLIP_BEEM_LED													HAL_GPIO_TogglePin(BEEM_LED_GPIO_Port, BEEM_LED_Pin)

#define SET_TICK_LED_ON												HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, GPIO_PIN_SET)
#define SET_TICK_LED_OFF											HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, GPIO_PIN_RESET)
#define GET_TICK_LED													HAL_GPIO_ReadPin(TICK_LED_GPIO_Port, TICK_LED_Pin)
#define FLIP_TICK_LED													HAL_GPIO_TogglePin(TICK_LED_GPIO_Port, TICK_LED_Pin)

#define SET_ERR_LED_ON												HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_SET)
#define SET_ERR_LED_OFF												HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_RESET)
#define GET_ERR_LED														HAL_GPIO_ReadPin(ERR_LED_GPIO_Port, ERR_LED_Pin)
#define FLIP_ERR_LED													HAL_GPIO_ReadPin(ERR_LED_GPIO_Port, ERR_LED_Pin)

#define SET_LASER_CH0_ON											HAL_GPIO_WritePin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin, GPIO_PIN_SET)
#define SET_LASER_CH0_OFF											HAL_GPIO_WritePin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin, GPIO_PIN_RESET)
#define SET_LASER_CH1_ON											HAL_GPIO_WritePin(LAS_PWM1_GPIO_Port, LAS_PWM1_Pin, GPIO_PIN_SET)
#define SET_LASER_CH1_OFF											HAL_GPIO_WritePin(LAS_PWM1_GPIO_Port, LAS_PWM1_Pin, GPIO_PIN_RESET)
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

#define SET_TEC_CH0_ON												HAL_GPIO_WritePin(TEC_PWM_GPIO_Port, TEC_PWM_Pin, GPIO_PIN_SET)
#define SET_TEC_CH0_OFF												HAL_GPIO_WritePin(TEC_PWM_GPIO_Port, TEC_PWM_Pin, GPIO_PIN_RESET)
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

#define FLIP_LASER_CH0												HAL_GPIO_TogglePin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin)
#define FLIP_LASER_CH1												HAL_GPIO_TogglePin(LAS_PWM1_GPIO_Port, LAS_PWM1_Pin)
#define FLIP_LASER_CH2												__nop()
#define FLIP_LASER_CH3												__nop()
#define FLIP_LASER_CH4												__nop()
#define FLIP_LASER_CH5												__nop()
#define FLIP_LASER_CH6												__nop()
#define FLIP_LASER_CH7												__nop()

#define GET_LASER_CH0													HAL_GPIO_ReadPin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin)
#define GET_LASER_CH1													HAL_GPIO_ReadPin(LAS_PWM1_GPIO_Port, LAS_PWM1_Pin)
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

#define SET_RAIM_TIM_OFF											HAL_TIM_PWM_Stop(&htim10, TIM_CHANNEL_1)
#define SET_RAIM_TIM_ON												HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1)
#define SET_RAIM_TIM_PWM(b)										__HAL_TIM_SET_COMPARE(&htim10, TIM_CHANNEL_1, b)

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

//VN5016
#define SET_VN5016_INPUT(b)										HAL_GPIO_WritePin(VN5016_INPUT_GPIO_Port, VN5016_INPUT_Pin, b)
#define SET_VN5016_INPUT_ON										HAL_GPIO_WritePin(VN5016_INPUT_GPIO_Port, VN5016_INPUT_Pin, GPIO_PIN_SET)
#define SET_VN5016_INPUT_OFF									HAL_GPIO_WritePin(VN5016_INPUT_GPIO_Port, VN5016_INPUT_Pin, GPIO_PIN_RESET)
#define GET_VN5016_INPUT											HAL_GPIO_ReadPin(VN5016_INPUT_GPIO_Port, VN5016_INPUT_Pin)
#define FLIP_VN5016_INPUT											HAL_GPIO_TogglePin(VN5016_INPUT_GPIO_Port, VN5016_INPUT_Pin)

#define SET_VN5016_CSDIS(b)										HAL_GPIO_WritePin(VN5016_CSDIS_GPIO_Port, VN5016_CSDIS_Pin, b)
#define SET_VN5016_CSDIS_ON										HAL_GPIO_WritePin(VN5016_CSDIS_GPIO_Port, VN5016_CSDIS_Pin, GPIO_PIN_SET)
#define SET_VN5016_CSDIS_OFF									HAL_GPIO_WritePin(VN5016_CSDIS_GPIO_Port, VN5016_CSDIS_Pin, GPIO_PIN_RESET)
#define GET_VN5016_CSDIS											HAL_GPIO_ReadPin(VN5016_CSDIS_GPIO_Port, VN5016_CSDIS_Pin)
#define FLIP_VN5016_CSDIS											HAL_GPIO_TogglePin(VN5016_CSDIS_GPIO_Port, VN5016_CSDIS_Pin)

//POWER SWITCH
#define GET_PWR_KEY														HAL_GPIO_ReadPin(PWR_KEY_GPIO_Port, PWR_KEY_Pin)

//POWER INT MPU软关机中断信号-->LTC2955作为MPU单元
#define GET_PWR_INT														0
//POWER KILL MPU软件关机信号-->LTC2955作为MPU单元
#define SET_PWR_KILL(b)												__nop()
#define SET_PWR_KILL_ON												__nop()
#define SET_PWR_KILL_OFF											__nop()
#define FLIP_PWR_KILL													__nop()
#define GET_PWR_KILL													__nop()

//POWER LED
#define SET_PWR_LED(b)												HAL_GPIO_WritePin(PWR_LED_GPIO_Port, PWR_LED_Pin, b)
#define SET_PWR_LED_ON												HAL_GPIO_WritePin(PWR_LED_GPIO_Port, PWR_LED_Pin, GPIO_PIN_SET)
#define SET_PWR_LED_OFF												HAL_GPIO_WritePin(PWR_LED_GPIO_Port, PWR_LED_Pin, GPIO_PIN_RESET)
#define GET_PWR_LED														HAL_GPIO_ReadPin(PWR_LED_GPIO_Port, PWR_LED_Pin)
#define FLIP_PWR_LED													HAL_GPIO_TogglePin(PWR_LED_GPIO_Port, PWR_LED_Pin)

//TEC OUT
#define SET_TEC_GATE_CH0_ON										__nop()								
#define SET_TEC_GATE_CH0_OFF									__nop()
#define SET_TEC_GATE_CH1_ON										__nop()								
#define SET_TEC_GATE_CH1_OFF									__nop()

//定义USB 切换功能引脚
#if defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP)
//USB FS LEGACY MUX MCU/MPU 选择							0:MCU USB 1:MPU USB
#define SET_USB_FS_SEL_LEGACY(b)							HAL_GPIO_WritePin(USBA0_SEL_GPIO_Port, USBA0_SEL_Pin, b)
#define GET_USB_FS_SEL_LEGACY									HAL_GPIO_ReadPin(USBA0_SEL_GPIO_Port, USBA0_SEL_Pin)
#define SET_USB_FS_SEL_LEGACY_ON							HAL_GPIO_WritePin(USBA0_SEL_GPIO_Port, USBA0_SEL_Pin, GPIO_PIN_SET)
#define SET_USB_FS_SEL_LEGACY_OFF							HAL_GPIO_WritePin(USBA0_SEL_GPIO_Port, USBA0_SEL_Pin, GPIO_PIN_RESET)
#define FLIP_USB_FS_LEGACY_SEL								HAL_GPIO_TogglePin(USBA0_SEL_GPIO_Port, USBA0_SEL_Pin)

//USB_FS_PSON 外部USB供
#define SET_USB_FS_PSON_LEGACY(b)							HAL_GPIO_WritePin(USB_FS_PSON_LEGACY_GPIO_Port, USB_FS_PSON_LEGACY_Pin, b)	
#define GET_USB_FS_PSON_LEGACY								HAL_GPIO_ReadPin(USB_FS_PSON_LEGACY_GPIO_Port, USB_FS_PSON_LEGACY_Pin)
#define SET_USB_FS_PSON_LEGACY_ON							HAL_GPIO_WritePin(USB_FS_PSON_LEGACY_GPIO_Port, USB_FS_PSON_LEGACY_Pin, GPIO_PIN_SET)
#define SET_USB_FS_PSON_LEGACY_OFF						HAL_GPIO_WritePin(USB_FS_PSON_LEGACY_GPIO_Port, USB_FS_PSON_LEGACY_Pin, GPIO_PIN_RESET)
#define FLIP_USB_FS_PSON_LEGACY								HAL_GPIO_TogglePin(USB_FS_PSON_LEGACY_GPIO_Port, USB_FS_PSON_LEGACY_Pin)

//USB_HS_PSON 内部USB供电
#define SET_USB_HS_PSON_LEGACY(b)							HAL_GPIO_WritePin(USB_HS_PSON_LEGACY_GPIO_Port, USB_HS_PSON_LEGACY_Pin, b)	
#define GET_USB_HS_PSON_LEGACY								HAL_GPIO_ReadPin(USB_HS_PSON_LEGACY_GPIO_Port, USB_HS_PSON_LEGACY_Pin)
#define SET_USB_HS_PSON_LEGACY_ON							HAL_GPIO_WritePin(USB_HS_PSON_LEGACY_GPIO_Port, USB_HS_PSON_LEGACY_Pin, GPIO_PIN_SET)
#define SET_USB_HS_PSON_LEGACY_OFF						HAL_GPIO_WritePin(USB_HS_PSON_LEGACY_GPIO_Port, USB_HS_PSON_LEGACY_Pin, GPIO_PIN_RESET)
#define FLIP_USB_HS_PSON_LEGACY								HAL_GPIO_TogglePin(USB_HS_PSON_LEGACY_GPIO_Port, USB_HS_PSON_LEGACY_Pin)
#endif

#if defined (LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP)
//USBA MCU/MPU 选择														0:MPU USB 1:MCU USB
#define SET_USBA0_SEL(b)											HAL_GPIO_WritePin(USBA0_SEL_GPIO_Port, USBA0_SEL_Pin, b)
#define GET_USBA0_SEL													HAL_GPIO_ReadPin(USBA0_SEL_GPIO_Port, USBA0_SEL_Pin)
#define SET_USBA0_SEL_ON											HAL_GPIO_WritePin(USBA0_SEL_GPIO_Port, USBA0_SEL_Pin, GPIO_PIN_SET)
#define SET_USBA0_SEL_OFF											HAL_GPIO_WritePin(USBA0_SEL_GPIO_Port, USBA0_SEL_Pin, GPIO_PIN_RESET)
#define FLIP_USBA0_SEL												HAL_GPIO_TogglePin(USBA0_SEL_GPIO_Port, USBA0_SEL_Pin)

//USBA->MCU INT/EXT选择												0:EXT USB 1:INT USB
#define SET_USBA1_SEL(b)											HAL_GPIO_WritePin(USBA1_SEL_GPIO_Port, USBA1_SEL_Pin, b)	
#define GET_USBA1_SEL													HAL_GPIO_ReadPin(USBA1_SEL_GPIO_Port, USBA1_SEL_Pin)
#define SET_USBA1_SEL_ON											HAL_GPIO_WritePin(USBA1_SEL_GPIO_Port, USBA1_SEL_Pin, GPIO_PIN_SET)
#define SET_USBA1_SEL_OFF											HAL_GPIO_WritePin(USBA1_SEL_GPIO_Port, USBA1_SEL_Pin, GPIO_PIN_RESET)
#define FLIP_USBA1_SEL												HAL_GPIO_TogglePin(USBA1_SEL_GPIO_Port, USBA1_SEL_Pin)

//MPU POWER
#define SET_MPU_3V3_EN(b)											HAL_GPIO_WritePin(MPU_3V3_EN_GPIO_Port, MPU_3V3_EN_Pin, b)	
#define GET_MPU_3V3_EN												HAL_GPIO_ReadPin(MPU_3V3_EN_GPIO_Port, MPU_3V3_EN_Pin)
#define SET_MPU_3V3_EN_ON											HAL_GPIO_WritePin(MPU_3V3_EN_GPIO_Port, MPU_3V3_EN_Pin, GPIO_PIN_SET)
#define SET_MPU_3V3_EN_OFF										HAL_GPIO_WritePin(MPU_3V3_EN_GPIO_Port, MPU_3V3_EN_Pin, GPIO_PIN_RESET)

#define SET_MPU_1V8_EN(b)											HAL_GPIO_WritePin(MPU_1V8_EN_GPIO_Port, MPU_1V8_EN_Pin, b)	
#define GET_MPU_1V8_EN												HAL_GPIO_ReadPin(MPU_1V8_EN_GPIO_Port, MPU_1V8_EN_Pin)
#define SET_MPU_1V8_EN_ON											HAL_GPIO_WritePin(MPU_1V8_EN_GPIO_Port, MPU_1V8_EN_Pin, GPIO_PIN_SET)
#define SET_MPU_1V8_EN_OFF										HAL_GPIO_WritePin(MPU_1V8_EN_GPIO_Port, MPU_1V8_EN_Pin, GPIO_PIN_RESET)

#define SET_MPU_1V2_EN(b)											HAL_GPIO_WritePin(MPU_1V2_EN_GPIO_Port, MPU_1V2_EN_Pin, b)	
#define GET_MPU_1V2_EN												HAL_GPIO_ReadPin(MPU_1V2_EN_GPIO_Port, MPU_1V2_EN_Pin)
#define SET_MPU_1V2_EN_ON											HAL_GPIO_WritePin(MPU_1V2_EN_GPIO_Port, MPU_1V2_EN_Pin, GPIO_PIN_SET)
#define SET_MPU_1V2_EN_OFF										HAL_GPIO_WritePin(MPU_1V2_EN_GPIO_Port, MPU_1V2_EN_Pin, GPIO_PIN_RESET)

//MICRO USBID -> MCU
#define GET_USBD0_ID													HAL_GPIO_ReadPin(USBD0_ID_GPIO_Port, USBD0_ID_Pin)

//MPU_USB_OTG_PSON -> MCU
#define GET_MPU_USB_OTG_PSON									HAL_GPIO_ReadPin(MPU_USB_OTG_PSON_GPIO_Port, MPU_USB_OTG_PSON_Pin)

//MCU USBID ->MPU
#define SET_MPU_USB_OTG_ID(b)									HAL_GPIO_WritePin(MPU_USB_OTG_ID_GPIO_Port, MPU_USB_OTG_ID_Pin, b)	
#define GET_MPU_USB_OTG_ID										HAL_GPIO_ReadPin(MPU_USB_OTG_ID_GPIO_Port, MPU_USB_OTG_ID_Pin)
#define SET_MPU_USB_OTG_ID_ON									HAL_GPIO_WritePin(MPU_USB_OTG_ID_GPIO_Port, MPU_USB_OTG_ID_Pin, GPIO_PIN_SET)
#define SET_MPU_USB_OTG_ID_OFF								HAL_GPIO_WritePin(MPU_USB_OTG_ID_GPIO_Port, MPU_USB_OTG_ID_Pin, GPIO_PIN_RESET)

//外部USB-A供电
#define SET_USBA0_PSON(b)											HAL_GPIO_WritePin(USBA0_PSON_GPIO_Port, USBA0_PSON_Pin, b)	
#define GET_USBA0_PSON												HAL_GPIO_ReadPin(USBA0_PSON_GPIO_Port, USBA0_PSON_Pin)
#define SET_USBA0_PSON_ON											HAL_GPIO_WritePin(USBA0_PSON_GPIO_Port, USBA0_PSON_Pin, GPIO_PIN_SET)
#define SET_USBA0_PSON_OFF										HAL_GPIO_WritePin(USBA0_PSON_GPIO_Port, USBA0_PSON_Pin, GPIO_PIN_RESET)
#define FLIP_USBA0_PSON												HAL_GPIO_TogglePin(USBA0_PSON_GPIO_Port, USBA0_PSON_Pin)
//内部USB-A供电
#define SET_USBA1_PSON(b)											HAL_GPIO_WritePin(USBA1_PSON_GPIO_Port, USBA1_PSON_Pin, b)	
#define GET_USBA1_PSON												HAL_GPIO_ReadPin(USBA1_PSON_GPIO_Port, USBA1_PSON_Pin)
#define SET_USBA1_PSON_ON											HAL_GPIO_WritePin(USBA1_PSON_GPIO_Port, USBA1_PSON_Pin, GPIO_PIN_SET)
#define SET_USBA1_PSON_OFF										HAL_GPIO_WritePin(USBA1_PSON_GPIO_Port, USBA1_PSON_Pin, GPIO_PIN_RESET)
#define FLIP_USBA1_PSON												HAL_GPIO_TogglePin(USBA1_PSON_GPIO_Port, USBA1_PSON_Pin)
//外部USB-MICRO 供电
#define SET_USBD0_PSON(b)											HAL_GPIO_WritePin(USBD0_PSON_GPIO_Port, USBD0_PSON_Pin, b)	
#define GET_USBD0_PSON												HAL_GPIO_ReadPin(USBD0_PSON_GPIO_Port, USBD0_PSON_Pin)
#define SET_USBD0_PSON_ON											HAL_GPIO_WritePin(USBD0_PSON_GPIO_Port, USBD0_PSON_Pin, GPIO_PIN_SET)
#define SET_USBD0_PSON_OFF										HAL_GPIO_WritePin(USBD0_PSON_GPIO_Port, USBD0_PSON_Pin, GPIO_PIN_RESET)
#define FLIP_USBD0_PSON												HAL_GPIO_TogglePin(USBD0_PSON_GPIO_Port, USBD0_PSON_Pin)

//MPU REFLASH 固件写入
#define SET_MPU_REFLASH(b)										HAL_GPIO_WritePin(MPU_REFLASH_GPIO_Port, MPU_REFLASH_Pin, b)	
#define GET_MPU_REFLSAH												HAL_GPIO_ReadPin(MPU_REFLASH_GPIO_Port, MPU_REFLASH_Pin)
#define SET_MPU_REFLASH_ON										HAL_GPIO_WritePin(MPU_REFLASH_GPIO_Port, MPU_REFLASH_Pin, GPIO_PIN_SET)
#define SET_MPU_REFLASH_OFF										HAL_GPIO_WritePin(MPU_REFLASH_GPIO_Port, MPU_REFLASH_Pin, GPIO_PIN_RESET)
#define FLIP_MPU_REFLASH											HAL_GPIO_TogglePin(MPU_REFLASH_GPIO_Port, MPU_REFLASH_Pin)

//MPU RESET 复位
#define SET_MPU_RESET(b)											HAL_GPIO_WritePin(MPU_RESET_GPIO_Port, MPU_RESET_Pin, b)	
#define GET_MPU_RESET													HAL_GPIO_ReadPin(MPU_RESET_GPIO_Port, MPU_RESET_Pin)
#define SET_MPU_RESET_ON											HAL_GPIO_WritePin(MPU_RESET_GPIO_Port, MPU_RESET_Pin, GPIO_PIN_SET)
#define SET_MPU_RESET_OFF											HAL_GPIO_WritePin(MPU_RESET_GPIO_Port, MPU_RESET_Pin, GPIO_PIN_RESET)
#define FLIP_MPU_RESET												HAL_GPIO_TogglePin(MPU_RESET_GPIO_Port, MPU_RESET_Pin)
#endif

//模拟HDC1080 I2C定义
#define SET_HDC1080_SCL(b)										__NOP()												
#define SET_HDC1080_SDA(b)										__NOP()
#define GET_HDC1080_SDA												0
//安全锁接触
#define SET_SAFE_RESET(b)											__nop()
#define SET_SAFE_RESET_ON                    	__nop()
#define SET_SAFE_RESET_OFF                   	__nop()
#endif

#if defined(LYPE_MCU_1V0_20260106)
#define GET_ESTOP_NC													HAL_GPIO_ReadPin(ESTOP_NC_GPIO_Port, ESTOP_NC_Pin)
#define GET_INTERLOCK_NC											HAL_GPIO_ReadPin(INTERLOCK_NC_GPIO_Port, INTERLOCK_NC_Pin)
#define GET_FSWITCH_NO												HAL_GPIO_ReadPin(FS_NO_GPIO_Port, FS_NO_Pin)
#define GET_FSWITCH_NC												HAL_GPIO_ReadPin(FS_NC_GPIO_Port, FS_NC_Pin)

#define SET_SPK_AP_ON													HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_RESET)
#define SET_SPK_AP_OFF												HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_SET)

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

#define SET_RED_LED_ON												HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_SET)
#define SET_RED_LED_OFF												HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_RESET)
#define SET_GREEN_LED_ON											
#define SET_GREEN_LED_OFF											
#define SET_BLUE_LED_ON												HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, GPIO_PIN_SET)
#define SET_BLUE_LED_OFF											HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, GPIO_PIN_RESET)

#define SET_RED_LED_DC(b)											__nop()											
#define SET_GREEN_LED_DC(b)										__nop()
#define SET_BLUE_LED_DC(b)										__nop()

#define SET_BEEM_LED_ON												HAL_GPIO_WritePin(STA0_LED_GPIO_Port, STA0_LED_Pin, GPIO_PIN_RESET)
#define SET_BEEM_LED_OFF											HAL_GPIO_WritePin(STA0_LED_GPIO_Port, STA0_LED_Pin, GPIO_PIN_SET)
#define GET_BEEM_LED													!HAL_GPIO_ReadPin(STA0_LED_GPIO_Port, STA0_LED_Pin)
#define FLIP_BEEM_LED													HAL_GPIO_TogglePin(STA0_LED_GPIO_Port, STA0_LED_Pin)

#define SET_TICK_LED_ON												HAL_GPIO_WritePin(STA2_LED_GPIO_Port, STA2_LED_Pin, GPIO_PIN_RESET)
#define SET_TICK_LED_OFF											HAL_GPIO_WritePin(STA2_LED_GPIO_Port, STA2_LED_Pin, GPIO_PIN_SET)
#define GET_TICK_LED													!HAL_GPIO_ReadPin(STA2_LED_GPIO_Port, STA2_LED_Pin)
#define FLIP_TICK_LED													HAL_GPIO_TogglePin(STA2_LED_GPIO_Port, STA2_LED_Pin)

#define SET_ERR_LED_ON												HAL_GPIO_WritePin(STA3_LED_GPIO_Port, STA3_LED_Pin, GPIO_PIN_RESET)
#define SET_ERR_LED_OFF												HAL_GPIO_WritePin(STA3_LED_GPIO_Port, STA3_LED_Pin, GPIO_PIN_SET)
#define GET_ERR_LED														!HAL_GPIO_ReadPin(STA3_LED_GPIO_Port, STA3_LED_Pin)
#define FLIP_ERR_LED													HAL_GPIO_ReadPin(STA3_LED_GPIO_Port, STA3_LED_Pin)

#define SET_LASER_CH0_ON											HAL_GPIO_WritePin(LAS0_PWM_GPIO_Port, LAS0_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH0_OFF											HAL_GPIO_WritePin(LAS0_PWM_GPIO_Port, LAS0_PWM_Pin, GPIO_PIN_RESET)

#define SET_LASER_CH1_ON											HAL_GPIO_WritePin(LAS1_PWM_GPIO_Port, LAS1_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH1_OFF											HAL_GPIO_WritePin(LAS1_PWM_GPIO_Port, LAS1_PWM_Pin, GPIO_PIN_RESET)

#define SET_LASER_CH2_ON											HAL_GPIO_WritePin(LAS2_PWM_GPIO_Port, LAS2_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH2_OFF											HAL_GPIO_WritePin(LAS2_PWM_GPIO_Port, LAS2_PWM_Pin, GPIO_PIN_RESET)

#define SET_LASER_CH3_ON											HAL_GPIO_WritePin(LAS3_PWM_GPIO_Port, LAS3_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH3_OFF											HAL_GPIO_WritePin(LAS3_PWM_GPIO_Port, LAS3_PWM_Pin, GPIO_PIN_RESET)

#define SET_LASER_CH4_ON											HAL_GPIO_WritePin(LAS4_PWM_GPIO_Port, LAS4_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH4_OFF											HAL_GPIO_WritePin(LAS4_PWM_GPIO_Port, LAS4_PWM_Pin, GPIO_PIN_RESET)

#define SET_LASER_CH5_ON											HAL_GPIO_WritePin(LAS5_PWM_GPIO_Port, LAS5_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH5_OFF											HAL_GPIO_WritePin(LAS5_PWM_GPIO_Port, LAS5_PWM_Pin, GPIO_PIN_RESET)

#define SET_LASER_CH6_ON											HAL_GPIO_WritePin(LAS6_PWM_GPIO_Port, LAS6_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH6_OFF											HAL_GPIO_WritePin(LAS6_PWM_GPIO_Port, LAS6_PWM_Pin, GPIO_PIN_RESET)

#define SET_LASER_CH7_ON											HAL_GPIO_WritePin(LAS7_PWM_GPIO_Port, LAS7_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH7_OFF											HAL_GPIO_WritePin(LAS7_PWM_GPIO_Port, LAS7_PWM_Pin, GPIO_PIN_RESET)

#define SET_TEC_CH0_ON												HAL_GPIO_WritePin(TEC0_PWM_GPIO_Port, TEC0_PWM_Pin, GPIO_PIN_SET)
#define SET_TEC_CH0_OFF												HAL_GPIO_WritePin(TEC0_PWM_GPIO_Port, TEC0_PWM_Pin, GPIO_PIN_RESET)

#define SET_TEC_CH1_ON												HAL_GPIO_WritePin(TEC1_PWM_GPIO_Port, TEC1_PWM_Pin, GPIO_PIN_SET)
#define SET_TEC_CH1_OFF												HAL_GPIO_WritePin(TEC1_PWM_GPIO_Port, TEC1_PWM_Pin, GPIO_PIN_RESET)

#define SET_TEC_CH2_ON												HAL_GPIO_WritePin(TEC2_PWM_GPIO_Port, TEC2_PWM_Pin, GPIO_PIN_SET)												
#define SET_TEC_CH2_OFF												HAL_GPIO_WritePin(TEC2_PWM_GPIO_Port, TEC2_PWM_Pin, GPIO_PIN_RESET)

#define SET_TEC_CH3_ON												HAL_GPIO_WritePin(TEC3_PWM_GPIO_Port, TEC3_PWM_Pin, GPIO_PIN_SET)
#define SET_TEC_CH3_OFF												HAL_GPIO_WritePin(TEC3_PWM_GPIO_Port, TEC3_PWM_Pin, GPIO_PIN_RESET)

#define SET_TEC_CH4_ON												HAL_GPIO_WritePin(TEC4_PWM_GPIO_Port, TEC4_PWM_Pin, GPIO_PIN_SET)
#define SET_TEC_CH4_OFF												HAL_GPIO_WritePin(TEC4_PWM_GPIO_Port, TEC4_PWM_Pin, GPIO_PIN_RESET)

#define SET_TEC_CH5_ON												HAL_GPIO_WritePin(TEC5_PWM_GPIO_Port, TEC5_PWM_Pin, GPIO_PIN_SET)
#define SET_TEC_CH5_OFF												HAL_GPIO_WritePin(TEC5_PWM_GPIO_Port, TEC5_PWM_Pin, GPIO_PIN_RESET)

#define SET_TEC_CH6_ON												HAL_GPIO_WritePin(TEC6_PWM_GPIO_Port, TEC6_PWM_Pin, GPIO_PIN_SET)
#define SET_TEC_CH6_OFF												HAL_GPIO_WritePin(TEC6_PWM_GPIO_Port, TEC6_PWM_Pin, GPIO_PIN_RESET)

#define SET_TEC_CH7_ON												HAL_GPIO_WritePin(TEC7_PWM_GPIO_Port, TEC7_PWM_Pin, GPIO_PIN_SET)
#define SET_TEC_CH7_OFF												HAL_GPIO_WritePin(TEC7_PWM_GPIO_Port, TEC7_PWM_Pin, GPIO_PIN_RESET)

#define FLIP_LASER_CH0												HAL_GPIO_TogglePin(LAS0_PWM_GPIO_Port, LAS0_PWM_Pin)
#define FLIP_LASER_CH1												HAL_GPIO_TogglePin(LAS1_PWM_GPIO_Port, LAS1_PWM_Pin)
#define FLIP_LASER_CH2												HAL_GPIO_TogglePin(LAS2_PWM_GPIO_Port, LAS2_PWM_Pin)
#define FLIP_LASER_CH3												HAL_GPIO_TogglePin(LAS3_PWM_GPIO_Port, LAS3_PWM_Pin)
#define FLIP_LASER_CH4												HAL_GPIO_TogglePin(LAS4_PWM_GPIO_Port, LAS4_PWM_Pin)
#define FLIP_LASER_CH5												HAL_GPIO_TogglePin(LAS5_PWM_GPIO_Port, LAS5_PWM_Pin)
#define FLIP_LASER_CH6												HAL_GPIO_TogglePin(LAS6_PWM_GPIO_Port, LAS6_PWM_Pin)
#define FLIP_LASER_CH7												HAL_GPIO_TogglePin(LAS7_PWM_GPIO_Port, LAS7_PWM_Pin)

#define GET_LASER_CH0													HAL_GPIO_ReadPin(LAS0_PWM_GPIO_Port, LAS0_PWM_Pin)
#define GET_LASER_CH1													HAL_GPIO_ReadPin(LAS1_PWM_GPIO_Port, LAS1_PWM_Pin)
#define GET_LASER_CH2													HAL_GPIO_ReadPin(LAS2_PWM_GPIO_Port, LAS2_PWM_Pin)
#define GET_LASER_CH3													HAL_GPIO_ReadPin(LAS3_PWM_GPIO_Port, LAS3_PWM_Pin)
#define GET_LASER_CH4													HAL_GPIO_ReadPin(LAS4_PWM_GPIO_Port, LAS4_PWM_Pin)
#define GET_LASER_CH5													HAL_GPIO_ReadPin(LAS5_PWM_GPIO_Port, LAS5_PWM_Pin)
#define GET_LASER_CH6													HAL_GPIO_ReadPin(LAS6_PWM_GPIO_Port, LAS6_PWM_Pin)
#define GET_LASER_CH7													HAL_GPIO_ReadPin(LAS7_PWM_GPIO_Port, LAS7_PWM_Pin)

#define SET_FAN0_ON														HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3)
#define SET_FAN0_OFF													HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_3)
#define SET_FAN0_TIM_PWM(b)										__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, b)

#define SET_FAN1_ON														HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2)
#define SET_FAN1_OFF													HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_2)
#define SET_FAN1_TIM_PWM(b)										__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, b)

#define SET_FAN2_ON														HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1)
#define SET_FAN2_OFF													HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_1)
#define SET_FAN2_TIM_PWM(b)										__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, b)

#define SET_SPK_TIM_ON												HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2)
#define SET_SPK_TIM_OFF												HAL_TIM_PWM_Stop(&htim9, TIM_CHANNEL_2)

#define SET_RAIM_TIM_OFF											__nop()
#define SET_RAIM_TIM_ON												__nop()
#define SET_RAIM_TIM_PWM(b)										__nop()

#define SET_RAIM_SHDN(b)			                __nop()
#define SET_RAIM_SHDN_ON                      __nop()
#define SET_RAIM_SHDN_OFF                     __nop()
#define FLIP_RAIM_SHDN                        __nop()
#define GET_RAIM_SHDN													0

#define SET_GAIM_TIM_OFF											HAL_TIM_PWM_Stop(&htim5, TIM_CHANNEL_3)
#define SET_GAIM_TIM_ON												HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3)
#define SET_GAIM_TIM_PWM(b)										__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_3, b)

#define SET_GAIM_SHDN(b)			                HAL_GPIO_WritePin(GAIM_SHDN_GPIO_Port, GAIM_SHDN_Pin, b)
#define SET_GAIM_SHDN_ON                      HAL_GPIO_WritePin(GAIM_SHDN_GPIO_Port, GAIM_SHDN_Pin, GPIO_PIN_SET)
#define SET_GAIM_SHDN_OFF                     HAL_GPIO_WritePin(GAIM_SHDN_GPIO_Port, GAIM_SHDN_Pin, GPIO_PIN_RESET)
#define FLIP_GAIM_SHDN                        HAL_GPIO_TogglePin(GAIM_SHDN_GPIO_Port, GAIM_SHDN_Pin)
#define GET_GAIM_SHDN													HAL_GPIO_ReadPin(GAIM_SHDN_GPIO_Port, GAIM_SHDN_Pin)
//MCP41010
#define SET_MCP41010_CS(b)										HAL_GPIO_WritePin(MCP41010_CS_GPIO_Port, MCP41010_CS_Pin, b)
#define SET_MCP41010_SDI(b)										HAL_GPIO_WritePin(MCP41010_SDI_GPIO_Port, MCP41010_SDI_Pin, b)
#define SET_MCP41010_SCK(b)										HAL_GPIO_WritePin(MCP41010_SCK_GPIO_Port, MCP41010_SCK_Pin, b)

//VN5016
#define SET_VN5016_INPUT(b)										__nop()
#define SET_VN5016_INPUT_ON										__nop()
#define SET_VN5016_INPUT_OFF									__nop()
#define GET_VN5016_INPUT											__nop()
#define FLIP_VN5016_INPUT											__nop()

#define SET_VN5016_CSDIS(b)										__nop()
#define SET_VN5016_CSDIS_ON										__nop()
#define SET_VN5016_CSDIS_OFF									__nop()
#define GET_VN5016_CSDIS											__nop()
#define FLIP_VN5016_CSDIS											__nop()

//POWER SWITCH 硬关机信号->MCU最为MPU单元
#define GET_PWR_KEY														0

//POWER INT MPU软关机中断信号-->LTC2955作为MPU单元
#define GET_PWR_INT														HAL_GPIO_ReadPin(POWER_INT_GPIO_Port, POWER_INT_Pin)
//POWER KILL MPU软件关机信号-->LTC2955作为MPU单元
#define SET_PWR_KILL(b)												HAL_GPIO_WritePin(POWER_KILL_GPIO_Port, POWER_KILL_Pin, b)
#define SET_PWR_KILL_ON												HAL_GPIO_WritePin(POWER_KILL_GPIO_Port, POWER_KILL_Pin, GPIO_PIN_SET)
#define SET_PWR_KILL_OFF											HAL_GPIO_WritePin(POWER_KILL_GPIO_Port, POWER_KILL_Pin, GPIO_PIN_RESET)
#define FLIP_PWR_KILL													HAL_GPIO_ReadPin(POWER_KILL_GPIO_Port, POWER_KILL_Pin)
#define GET_PWR_KILL													HAL_GPIO_ReadPin(POWER_KILL_GPIO_Port, POWER_KILL_Pin)

//POWER LED
#define SET_PWR_LED(b)												__nop()
#define SET_PWR_LED_ON												__nop()
#define SET_PWR_LED_OFF												__nop()
#define FLIP_PWR_LED													__nop()
#define GET_PWR_LED														__nop()

//TEC OUT
#define SET_TEC_GATE_CH0_ON										__nop()											
#define SET_TEC_GATE_CH0_OFF									__nop()

#define SET_TEC_GATE_CH1_ON										__nop()											
#define SET_TEC_GATE_CH1_OFF									__nop()

//PUMP
#define SET_PUMP0(b)													HAL_GPIO_WritePin(PUMP1_PWM_GPIO_Port, PUMP1_PWM_Pin, b)
#define SET_PUMP0_ON													HAL_GPIO_WritePin(PUMP1_PWM_GPIO_Port, PUMP1_PWM_Pin, GPIO_PIN_SET)
#define SET_PUMP0_OFF													HAL_GPIO_WritePin(PUMP1_PWM_GPIO_Port, PUMP1_PWM_Pin, GPIO_PIN_RESET)
#define GET_PUMP0															HAL_GPIO_ReadPin(PUMP1_PWM_GPIO_Port, PPUMP1_PWM_Pin)
#define FLIP_PUMP0														HAL_GPIO_TogglePin(PUMP1_PWM_GPIO_Port, PUMP1_PWM_Pin)

#define SET_PUMP1(b)													HAL_GPIO_WritePin(PUMP1_PWM_GPIO_Port, PUMP1_PWM_Pin, b)
#define SET_PUMP1_ON													HAL_GPIO_WritePin(PUMP1_PWM_GPIO_Port, PUMP1_PWM_Pin, GPIO_PIN_SET)
#define SET_PUMP1_OFF													HAL_GPIO_WritePin(PUMP1_PWM_GPIO_Port, PUMP1_PWM_Pin, GPIO_PIN_RESET)
#define GET_PUMP1															HAL_GPIO_ReadPin(PUMP1_PWM_GPIO_Port, PPUMP1_PWM_Pin)
#define FLIP_PUMP1														HAL_GPIO_TogglePin(PUMP1_PWM_GPIO_Port, PUMP1_PWM_Pin)

//EDAC
// 引脚电平控制宏
#define SET_DAC8568_SYNC(b)  									HAL_GPIO_WritePin(DAC8568_NSS_GPIO_Port, DAC8568_NSS_Pin, b)
#define SET_DAC8568_SCK(b)   									HAL_GPIO_WritePin(DAC8568_SCK_GPIO_Port, DAC8568_SCK_Pin, b)
#define SET_DAC8568_DOUT(b)   								HAL_GPIO_WritePin(DAC8568_DOUT_GPIO_Port, DAC8568_DOUT_Pin, b)
#define SET_DAC8568_LDAC(b)  									HAL_GPIO_WritePin(DAC8568_LDAC_GPIO_Port, DAC8568_LDAC_Pin, b)
#define SET_DAC8568_CLR(b)   									HAL_GPIO_WritePin(DAC8568_CLEAR_GPIO_Port, DAC8568_CLEAR_Pin, b)

//SPI EPROM
#define EPROM_SPI_NSS(b)											HAL_GPIO_WritePin(EPROM_NSS_GPIO_Port, EPROM_NSS_Pin, b)
#define EPROM_SPI_NSS_DESEL										HAL_GPIO_WritePin(EPROM_NSS_GPIO_Port, EPROM_NSS_Pin, GPIO_PIN_SET)
#define EPROM_SPI_NSS_SEL											HAL_GPIO_WritePin(EPROM_NSS_GPIO_Port, EPROM_NSS_Pin, GPIO_PIN_RESET)

//模拟HDC1080 I2C定义
#define SET_HDC1080_SCL(b)										HAL_GPIO_WritePin(HDC1080_SCL_GPIO_Port, HDC1080_SCL_Pin, b)										
#define SET_HDC1080_SDA(b)										HAL_GPIO_WritePin(HDC1080_SDA_GPIO_Port, HDC1080_SDA_Pin, b)
#define GET_HDC1080_SDA												HAL_GPIO_ReadPin(HDC1080_SDA_GPIO_Port, HDC1080_SDA_Pin)
//安全锁接触
#define SET_SAFE_RESET(b)											HAL_GPIO_WritePin(SAFE_RESET_GPIO_Port, SAFE_RESET_Pin, b)
#define SET_SAFE_RESET_ON                     HAL_GPIO_WritePin(SAFE_RESET_GPIO_Port, SAFE_RESET_Pin, GPIO_PIN_SET)
#define SET_SAFE_RESET_OFF                    HAL_GPIO_WritePin(SAFE_RESET_GPIO_Port, SAFE_RESET_Pin, GPIO_PIN_RESET)
#endif

#if defined(MODEL_PVGLS_15W_1470_A0) ||\
		defined(MODEL_PVGLS_15W_1470_A1)
#define GET_ESTOP_NC													HAL_GPIO_ReadPin(ESTOP_NC_GPIO_Port, ESTOP_NC_Pin)
#define GET_INTERLOCK_NC											HAL_GPIO_ReadPin(INTERLOCK_NC_GPIO_Port, INTERLOCK_NC_Pin)
#define GET_FSWITCH_NO												HAL_GPIO_ReadPin(FS_NO_GPIO_Port, FS_NO_Pin)
#define GET_FSWITCH_NC												HAL_GPIO_ReadPin(FS_NC_GPIO_Port, FS_NC_Pin)

#define SET_SPK_AP_ON													HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_RESET)
#define SET_SPK_AP_OFF												HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_SET)
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

#if defined(MODEL_PVGLS_10W_1940_A1)
#define GET_ESTOP_NC													HAL_GPIO_ReadPin(ESTOP_NC_GPIO_Port, ESTOP_NC_Pin)
#define GET_INTERLOCK_NC											HAL_GPIO_ReadPin(INTERLOCK_NC_GPIO_Port, INTERLOCK_NC_Pin)
#define GET_FSWITCH_NO												HAL_GPIO_ReadPin(FS_NO_GPIO_Port, FS_NO_Pin)
#define GET_FSWITCH_NC												HAL_GPIO_ReadPin(FS_NC_GPIO_Port, FS_NC_Pin)

#define SET_SPK_AP_ON													HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_RESET)
#define SET_SPK_AP_OFF												HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_SET)

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

#if defined(LDR2P1_RASPI_G9_A1_20250322_DUAL) ||\
    defined(LDR2P1_RASPI_G9_A1_20250322_TRIP)
#define GET_ESTOP_NC													HAL_GPIO_ReadPin(ESTOP_NC_GPIO_Port, ESTOP_NC_Pin)
#define GET_INTERLOCK_NC											HAL_GPIO_ReadPin(INTERLOCK_NC_GPIO_Port, INTERLOCK_NC_Pin)
#define GET_FSWITCH_NO												HAL_GPIO_ReadPin(FS_NO_GPIO_Port, FS_NO_Pin)
#define GET_FSWITCH_NC												HAL_GPIO_ReadPin(FS_NC_GPIO_Port, FS_NC_Pin)

#define SET_SPK_AP_ON													HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_RESET)
#define SET_SPK_AP_OFF												HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_SET)

#define SET_DAC7311_CS(b)											HAL_GPIO_WritePin(DAC7311_CS_GPIO_Port, DAC7311_CS_Pin, b)												
#define SET_DAC7311_SCK(b)                    HAL_GPIO_WritePin(DAC7311_SCK_GPIO_Port, DAC7311_SCK_Pin, b)
#define SET_DAC7311_SDI(b)										HAL_GPIO_WritePin(DAC7311_SDI_GPIO_Port, DAC7311_SDI_Pin, b)								

#define SET_RED_LED_ON												HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2)
#define SET_RED_LED_OFF												HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2)
#define SET_GREEN_LED_ON											HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1)
#define SET_GREEN_LED_OFF											HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1)
#define SET_BLUE_LED_ON												HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3)
#define SET_BLUE_LED_OFF											HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3)

#define SET_BLUE_LED_DC(b)										__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, b)
#define SET_RED_LED_DC(b)											__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, b)
#define SET_GREEN_LED_DC(b)										__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, b)

#define SET_BEEM_LED_ON												HAL_GPIO_WritePin(BEEM_LED_GPIO_Port, BEEM_LED_Pin, GPIO_PIN_RESET)
#define SET_BEEM_LED_OFF											HAL_GPIO_WritePin(BEEM_LED_GPIO_Port, BEEM_LED_Pin, GPIO_PIN_SET)
#define GET_BEEM_LED													!HAL_GPIO_ReadPin(BEEM_LED_GPIO_Port, BEEM_LED_Pin)
#define FLIP_BEEM_LED													HAL_GPIO_TogglePin(BEEM_LED_GPIO_Port, BEEM_LED_Pin)

#define SET_TICK_LED_ON												HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, GPIO_PIN_RESET)
#define SET_TICK_LED_OFF											HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, GPIO_PIN_SET)
#define GET_TICK_LED													!HAL_GPIO_ReadPin(TICK_LED_GPIO_Port, TICK_LED_Pin)
#define FLIP_TICK_LED													HAL_GPIO_TogglePin(TICK_LED_GPIO_Port, TICK_LED_Pin)

#define SET_ERR_LED_ON												HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_RESET)
#define SET_ERR_LED_OFF												HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_SET)
#define GET_ERR_LED														!HAL_GPIO_ReadPin(ERR_LED_GPIO_Port, ERR_LED_Pin)
#define FLIP_ERR_LED													HAL_GPIO_ReadPin(ERR_LED_GPIO_Port, ERR_LED_Pin)

#define SET_LASER_CH0_ON											HAL_GPIO_WritePin(LAS0_PWM_GPIO_Port, LAS0_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH0_OFF											HAL_GPIO_WritePin(LAS0_PWM_GPIO_Port, LAS0_PWM_Pin, GPIO_PIN_RESET)

#define SET_LASER_CH1_ON											HAL_GPIO_WritePin(LAS1_PWM_GPIO_Port, LAS1_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH1_OFF											HAL_GPIO_WritePin(LAS1_PWM_GPIO_Port, LAS1_PWM_Pin, GPIO_PIN_RESET)

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

#define SET_TEC_CH0_ON												HAL_GPIO_WritePin(TEC0_PWM_GPIO_Port, TEC0_PWM_Pin, GPIO_PIN_SET)
#define SET_TEC_CH0_OFF												HAL_GPIO_WritePin(TEC0_PWM_GPIO_Port, TEC0_PWM_Pin, GPIO_PIN_RESET)

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

#define FLIP_LASER_CH0												HAL_GPIO_TogglePin(LAS0_PWM_GPIO_Port, LAS0_PWM_Pin)
#define FLIP_LASER_CH1												HAL_GPIO_TogglePin(LAS1_PWM_GPIO_Port, LAS1_PWM_Pin)
#define FLIP_LASER_CH2												__nop()
#define FLIP_LASER_CH3												__nop()
#define FLIP_LASER_CH4												__nop()
#define FLIP_LASER_CH5												__nop()
#define FLIP_LASER_CH6												__nop()
#define FLIP_LASER_CH7												__nop()

#define GET_LASER_CH0													HAL_GPIO_ReadPin(LAS0_PWM_GPIO_Port, LAS0_PWM_Pin)
#define GET_LASER_CH1													HAL_GPIO_ReadPin(LAS1_PWM_GPIO_Port, LAS1_PWM_Pin)
#define GET_LASER_CH2													0
#define GET_LASER_CH3													0
#define GET_LASER_CH4													0
#define GET_LASER_CH5													0
#define GET_LASER_CH6													0
#define GET_LASER_CH7													0

#define SET_FAN0_ON														HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4)
#define SET_FAN0_OFF													HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4)
#define SET_FAN0_TIM_PWM(b)										__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, b)

#define SET_FAN1_ON														__nop()
#define SET_FAN1_OFF													__nop()
#define SET_FAN1_TIM_PWM(b)										__nop()

#define SET_FAN2_ON														__nop()
#define SET_FAN2_OFF													__nop()
#define SET_FAN2_TIM_PWM(b)										__nop()

#define SET_SPK_TIM_ON												HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1)
#define SET_SPK_TIM_OFF												HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1)

#define SET_RAIM_TIM_OFF											HAL_TIM_PWM_Stop(&htim9, TIM_CHANNEL_2)
#define SET_RAIM_TIM_ON												HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2)
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
#define GET_GAIM_SHDN													__nop()

//MCP41010
#define SET_MCP41010_CS(b)										HAL_GPIO_WritePin(MCP41010_CS_GPIO_Port, MCP41010_CS_Pin, b)
#define SET_MCP41010_SDI(b)										HAL_GPIO_WritePin(MCP41010_SDI_GPIO_Port, MCP41010_SDI_Pin, b)
#define SET_MCP41010_SCK(b)										HAL_GPIO_WritePin(MCP41010_SCK_GPIO_Port, MCP41010_SCK_Pin, b)

//VN5016
#define SET_VN5016_INPUT(b)										__nop()
#define SET_VN5016_INPUT_ON										__nop()
#define SET_VN5016_INPUT_OFF									__nop()
#define GET_VN5016_INPUT											__nop()
#define FLIP_VN5016_INPUT											__nop()

#define SET_VN5016_CSDIS(b)										__nop()
#define SET_VN5016_CSDIS_ON										__nop()
#define SET_VN5016_CSDIS_OFF									__nop()
#define GET_VN5016_CSDIS											__nop()
#define FLIP_VN5016_CSDIS											__nop()

//POWER SWITCH 硬关机信号->MCU最为MPU单元
#define GET_PWR_KEY														0

//POWER INT MPU软关机中断信号-->LTC2955作为MPU单元
#define GET_PWR_INT														HAL_GPIO_ReadPin(POWER_INT_GPIO_Port, POWER_INT_Pin)
//POWER KILL MPU软件关机信号-->LTC2955作为MPU单元
#define SET_PWR_KILL(b)												HAL_GPIO_WritePin(POWER_KILL_GPIO_Port, POWER_KILL_Pin, b)
#define SET_PWR_KILL_ON												HAL_GPIO_WritePin(POWER_KILL_GPIO_Port, POWER_KILL_Pin, GPIO_PIN_SET)
#define SET_PWR_KILL_OFF											HAL_GPIO_WritePin(POWER_KILL_GPIO_Port, POWER_KILL_Pin, GPIO_PIN_RESET)
#define FLIP_PWR_KILL													HAL_GPIO_ReadPin(POWER_KILL_GPIO_Port, POWER_KILL_Pin)
#define GET_PWR_KILL													HAL_GPIO_ReadPin(POWER_KILL_GPIO_Port, POWER_KILL_Pin)

//POWER LED
#define SET_PWR_LED(b)												__nop()
#define SET_PWR_LED_ON												__nop()
#define SET_PWR_LED_OFF												__nop()
#define FLIP_PWR_LED													__nop()
#define GET_PWR_LED														__nop()

//TEC OUT
#define SET_TEC_GATE_CH0_ON										__nop()											
#define SET_TEC_GATE_CH0_OFF									__nop()

#define SET_TEC_GATE_CH1_ON										__nop()											
#define SET_TEC_GATE_CH1_OFF									__nop()
//PUMP
#define SET_PUMP0(b)													HAL_GPIO_WritePin(PUMP1_PWM_GPIO_Port, PUMP1_PWM_Pin, b)
#define SET_PUMP0_ON													HAL_GPIO_WritePin(PUMP1_PWM_GPIO_Port, PUMP1_PWM_Pin, GPIO_PIN_SET)
#define SET_PUMP0_OFF													HAL_GPIO_WritePin(PUMP1_PWM_GPIO_Port, PUMP1_PWM_Pin, GPIO_PIN_RESET)
#define GET_PUMP0															HAL_GPIO_ReadPin(PUMP1_PWM_GPIO_Port, PPUMP1_PWM_Pin)
#define FLIP_PUMP0														HAL_GPIO_TogglePin(PUMP1_PWM_GPIO_Port, PUMP1_PWM_Pin)

#define SET_PUMP1(b)													HAL_GPIO_WritePin(PUMP1_PWM_GPIO_Port, PUMP1_PWM_Pin, b)
#define SET_PUMP1_ON													HAL_GPIO_WritePin(PUMP1_PWM_GPIO_Port, PUMP1_PWM_Pin, GPIO_PIN_SET)
#define SET_PUMP1_OFF													HAL_GPIO_WritePin(PUMP1_PWM_GPIO_Port, PUMP1_PWM_Pin, GPIO_PIN_RESET)
#define GET_PUMP1															HAL_GPIO_ReadPin(PUMP1_PWM_GPIO_Port, PPUMP1_PWM_Pin)
#define FLIP_PUMP1														HAL_GPIO_TogglePin(PUMP1_PWM_GPIO_Port, PUMP1_PWM_Pin)

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

#endif

#if defined(LYPE_SURGI_LDR5_20260519)
#define GET_ESTOP_NC													0
#define GET_INTERLOCK_NC											HAL_GPIO_ReadPin(GPIO_X2_GPIO_Port, GPIO_X2_Pin)
#define GET_FSWITCH_NO												0
#define GET_FSWITCH_NC												0

#define SET_SPK_AP_ON													__nop()
#define SET_SPK_AP_OFF												__nop()

#define SET_DAC7311_CS(b)											__nop()								
#define SET_DAC7311_SCK(b)                    __nop()
#define SET_DAC7311_SDI(b)										__nop()						

#define SET_RED_LED_ON												SET_ALARM_LED_ON
#define SET_RED_LED_OFF												SET_ALARM_LED_OFF
#define SET_GREEN_LED_ON											__nop()
#define SET_GREEN_LED_OFF											__nop()
#define SET_BLUE_LED_ON												__nop()
#define SET_BLUE_LED_OFF											__nop()

#define SET_BLUE_LED_DC(b)										__nop()
#define SET_RED_LED_DC(b)											__nop()
#define SET_GREEN_LED_DC(b)										__nop()

#define SET_BEEM_LED_ON												__nop()
#define SET_BEEM_LED_OFF											__nop()
#define GET_BEEM_LED													0
#define FLIP_BEEM_LED													__nop()

#define SET_SPEAK_ENA(b)                      __nop()

#define SET_LASER1_LED(b)                     HAL_GPIO_WritePin(GPIO_Y1_GPIO_Port, GPIO_Y1_Pin, b)         
#define SET_LASER2_LED(b)                     HAL_GPIO_WritePin(GPIO_Y2_GPIO_Port, GPIO_Y2_Pin, b)

#define SET_TICK_LED_ON												HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, GPIO_PIN_RESET)
#define SET_TICK_LED_OFF											HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, GPIO_PIN_SET)
#define GET_TICK_LED													!HAL_GPIO_ReadPin(TICK_LED_GPIO_Port, TICK_LED_Pin)
#define FLIP_TICK_LED													HAL_GPIO_TogglePin(TICK_LED_GPIO_Port, TICK_LED_Pin)

#define SET_ERR_LED_ON												HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_RESET)
#define SET_ERR_LED_OFF												HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_SET)
#define GET_ERR_LED														!HAL_GPIO_ReadPin(ERR_LED_GPIO_Port, ERR_LED_Pin)
#define FLIP_ERR_LED													HAL_GPIO_TogglePin(ERR_LED_GPIO_Port, ERR_LED_Pin)



#define SET_ALARM_LED(b)                      HAL_GPIO_WritePin(GPIO_Y0_GPIO_Port, GPIO_Y0_Pin, b)
#define SET_ALARM_LED_ON											HAL_GPIO_WritePin(GPIO_Y0_GPIO_Port, GPIO_Y0_Pin, GPIO_PIN_SET)
#define SET_ALARM_LED_OFF											HAL_GPIO_WritePin(GPIO_Y0_GPIO_Port, GPIO_Y0_Pin, GPIO_PIN_RESET)
#define GET_ALARM_LED													!HAL_GPIO_ReadPin(GPIO_Y0_GPIO_Port, GPIO_Y0_Pin)
#define FLIP_ALARM_LED												HAL_GPIO_TogglePin(GPIO_Y0_GPIO_Port, GPIO_Y0_Pin)

#define SET_LINK_LED(b)                        HAL_GPIO_WritePin(GPIO_Y3_GPIO_Port, GPIO_Y3_Pin, b)
#define SET_LOCK_LED(b)                       HAL_GPIO_WritePin(GPIO_Y3_GPIO_Port, GPIO_Y3_Pin, b)
#define SET_LOCK_LED_ON												HAL_GPIO_WritePin(GPIO_Y3_GPIO_Port, GPIO_Y3_Pin, GPIO_PIN_SET)
#define SET_LOCK_LED_OFF											HAL_GPIO_WritePin(GPIO_Y3_GPIO_Port, GPIO_Y3_Pin, GPIO_PIN_RESET)
#define GET_LOCK_LED													!HAL_GPIO_ReadPin(GPIO_Y3_GPIO_Port, GPIO_Y3_Pin)
#define FLIP_LOCK_LED													HAL_GPIO_TogglePin(GPIO_Y3_GPIO_Port, GPIO_Y3_Pin)


#define SET_LASER_PWM(b)                      HAL_GPIO_WritePin(LAS0_PWM_GPIO_Port, LAS0_PWM_Pin, b);HAL_GPIO_WritePin(LAS1_PWM_GPIO_Port, LAS1_PWM_Pin, b)

#define SET_LASER_CH0_ON											HAL_GPIO_WritePin(LAS0_PWM_GPIO_Port, LAS0_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH0_OFF											HAL_GPIO_WritePin(LAS0_PWM_GPIO_Port, LAS0_PWM_Pin, GPIO_PIN_RESET)

#define SET_LASER_CH1_ON											HAL_GPIO_WritePin(LAS1_PWM_GPIO_Port, LAS1_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH1_OFF											HAL_GPIO_WritePin(LAS1_PWM_GPIO_Port, LAS1_PWM_Pin, GPIO_PIN_RESET)

#define SET_LASER_CH2_ON											HAL_GPIO_WritePin(LAS2_PWM_GPIO_Port, LAS2_PWM_Pin, GPIO_PIN_SET)
#define SET_LASER_CH2_OFF											HAL_GPIO_WritePin(LAS2_PWM_GPIO_Port, LAS2_PWM_Pin, GPIO_PIN_RESET)  

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

#define SET_TEC_CH0_ON												HAL_GPIO_WritePin(TEC0_PWM_GPIO_Port, TEC0_PWM_Pin, GPIO_PIN_SET)
#define SET_TEC_CH0_OFF												HAL_GPIO_WritePin(TEC0_PWM_GPIO_Port, TEC0_PWM_Pin, GPIO_PIN_RESET)

#define SET_TEC_CH1_ON												HAL_GPIO_WritePin(TEC1_PWM_GPIO_Port, TEC1_PWM_Pin, GPIO_PIN_SET)
#define SET_TEC_CH1_OFF												HAL_GPIO_WritePin(TEC1_PWM_GPIO_Port, TEC1_PWM_Pin, GPIO_PIN_RESET)

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

#define FLIP_LASER_CH0												HAL_GPIO_TogglePin(LAS0_PWM_GPIO_Port, LAS0_PWM_Pin)
#define FLIP_LASER_CH1												HAL_GPIO_TogglePin(LAS1_PWM_GPIO_Port, LAS1_PWM_Pin)
#define FLIP_LASER_CH2												HAL_GPIO_TogglePin(LAS2_PWM_GPIO_Port, LAS2_PWM_Pin)
#define FLIP_LASER_CH3												__nop()
#define FLIP_LASER_CH4												__nop()
#define FLIP_LASER_CH5												__nop()
#define FLIP_LASER_CH6												__nop()
#define FLIP_LASER_CH7												__nop()

#define GET_LASER_CH0													HAL_GPIO_ReadPin(LAS0_PWM_GPIO_Port, LAS0_PWM_Pin)
#define GET_LASER_CH1													HAL_GPIO_ReadPin(LAS1_PWM_GPIO_Port, LAS1_PWM_Pin)
#define GET_LASER_CH2													HAL_GPIO_ReadPin(LAS2_PWM_GPIO_Port, LAS2_PWM_Pin)
#define GET_LASER_CH3													0
#define GET_LASER_CH4													0
#define GET_LASER_CH5													0
#define GET_LASER_CH6													0
#define GET_LASER_CH7													0

#define SET_FAN0_ON														__nop()
#define SET_FAN0_OFF													__nop()
#define SET_FAN0_TIM_PWM(b)										__nop()

#define SET_FAN1_ON														__nop()
#define SET_FAN1_OFF													__nop()
#define SET_FAN1_TIM_PWM(b)										__nop()

#define SET_FAN2_ON														__nop()
#define SET_FAN2_OFF													__nop()
#define SET_FAN2_TIM_PWM(b)										__nop()

#define SET_SPK_TIM_ON												__nop()
#define SET_SPK_TIM_OFF												__nop()

#define SET_RAIM_TIM_OFF											__nop()
#define SET_RAIM_TIM_ON												__nop()
#define SET_RAIM_TIM_PWM(b)										__nop()

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
#define SET_MCP41010_CS(b)										__nop()
#define SET_MCP41010_SDI(b)										__nop()
#define SET_MCP41010_SCK(b)										__nop()

//VN5016
#define SET_VN5016_INPUT(b)										__nop()
#define SET_VN5016_INPUT_ON										__nop()
#define SET_VN5016_INPUT_OFF									__nop()
#define GET_VN5016_INPUT											__nop()
#define FLIP_VN5016_INPUT											__nop()

#define SET_VN5016_CSDIS(b)										__nop()
#define SET_VN5016_CSDIS_ON										__nop()
#define SET_VN5016_CSDIS_OFF									__nop()
#define GET_VN5016_CSDIS											__nop()
#define FLIP_VN5016_CSDIS											__nop()

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

#endif

/*****************************************************************************/
//定义外设总线
#if defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP)
#define CONFIG_LASER_TIM_HANDLE								htim7
#define CONFIG_LASER_TIM											TIM7

#define CONFIG_SPLC_TIM_HANDLE								htim14//SPLC 计时器定义	
#define CONFIG_SPLC_TIM												TIM14

#define CONFIG_SPK_HANDLE											htim8//SPK 计时器定义	
#define CONFIG_SPK_TIM												TIM8
#define CONFIG_SPK_PWM_CHANNEL								TIM_CHANNEL_1

#define CONFIG_FAN0_TIM_HANDLE								htim4	
#define CONFIG_FAN0_TIM												TIM4
#define CONFIG_FAN0_PWM_CHANNEL								TIM_CHANNEL_2
#define CONFIG_FAN0_FG_CHANNEL								TIM_CHANNEL_1

#define CONFIG_EPROM_BUS_HANDLE								hi2c1//SPLC NVRAM接口定义
#define CONFIG_EPROM_BUS											I2C1

#define CONFIG_DEBUG_UART											huart1//调试串口
//#define CONFIG_DEBUG_DMA											DMA_HandleTypeDef hdma_uart5_rx;


#define CONFIG_GDDC_UART											huart2//GDDC串口
#define CONFIG_GDDC_UART_INSTANCE							USART2//GDDC串口中断
#endif

#if defined(MODEL_PVGLS_15W_1470_A0) ||\
		defined(MODEL_PVGLS_15W_1470_A1)
#define CONFIG_LASER_TIM_HANDLE								htim10//LASER 定时器
#define CONFIG_SPLC_TIM_HANDLE								htim14//SPLC 计时器定义	
#define CONFIG_RPROM_BUS											hi2c1//SPLC NVRAM接口定义
#define CONFIG_GDDC_UART											huart4
#define CONFIG_GDDC_UART_INSTANCE							UART4
#define CONFIG_EPROM_SIZE 										CONFIG_AT24C64_SIZE
#define CONFIG_ADC_CHANNEL										7//ADC采集通道
#define CONFIG_ADC_AVERAGE_NUM								8//ADC平均值次数
#endif

#if defined(MODEL_PVGLS_10W_1940_A1)
#define CONFIG_LASER_TIM_HANDLE								htim10//LASER 定时器
#define CONFIG_SPLC_TIM_HANDLE								htim14//SPLC 计时器定义	
#define CONFIG_RPROM_BUS											hi2c2//SPLC NVRAM接口定义
#define CONFIG_GDDC_UART											huart3
#define CONFIG_GDDC_UART_INSTANCE							USART3
#define CONFIG_EPROM_SIZE 										CONFIG_AT24C64_SIZE
#define CONFIG_ADC_CHANNEL										10//ADC采集通道
#define CONFIG_ADC_AVERAGE_NUM								8//ADC平均值次数
#endif

#if defined(LYPE_MCU_1V0_20260106)
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
#endif

#if defined(LYPE_SURGI_LDR5_20260519)
#define CONFIG_LASER_TIM_HANDLE								htim7
#define CONFIG_LASER_TIM											TIM7

#define CONFIG_SPLC_TIM_HANDLE								htim14//SPLC 计时器定义	
#define CONFIG_SPLC_TIM												TIM14

#define CONFIG_EPROM_BUS_HANDLE								hspi2//SPLC NVRAM接口定义
#define CONFIG_EPROM_BUS											SPI2									

#define CONFIG_DEBUG_UART											huart1//调试串口
#define CONFIG_HMI_UART												huart2//GDDC串口
#define CONFIG_HMI_UART_INSTANCE							USART2//GDDC串口中断
#define CONFIG_COMM_UART											huart6		
#define CONFIG_COMM_UART_INSTANCE							USART6

#define CONFIG_GDDC_UART											huart1//GDDC串口
#define CONFIG_GDDC_UART_INSTANCE							USART1//GDDC串口中断
#endif

#if defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
#define CONFIG_LASER_TIM_HANDLE								htim7
#define CONFIG_LASER_TIM											TIM7

#define CONFIG_SPLC_TIM_HANDLE								htim14//SPLC 计时器定义	
#define CONFIG_SPLC_TIM												TIM14

#define CONFIG_AIM_HANDLE											htim9
#define CONFIG_AIM_TIM												TIM9
#define CONFIG_AIM_PWM_CHANNEL								TIM_CHANNEL_2							

#define CONFIG_SPK_HANDLE											htim2//SPK 计时器定义	
#define CONFIG_SPK_TIM												TIM2
#define CONFIG_SPK_PWM_CHANNEL								TIM_CHANNEL_1

#define CONFIG_FAN0_TIM_HANDLE								htim3	
#define CONFIG_FAN0_TIM												TIM3
#define CONFIG_FAN0_PWM_CHANNEL								TIM_CHANNEL_4
#define CONFIG_FAN0_FG_CHANNEL								TIM_CHANNEL_3

#define CONFIG_FAN1_TIM_HANDLE									
#define CONFIG_FAN1_TIM												
#define CONFIG_FAN1_PWM_CHANNEL								
#define CONFIG_FAN1_FG_CHANNEL								

#define CONFIG_FAN2_TIM_HANDLE									
#define CONFIG_FAN2_TIM												
#define CONFIG_FAN2_PWM_CHANNEL								
#define CONFIG_FAN2_FG_CHANNEL								

#define CONFIG_EPROM_BUS_HANDLE								hspi3//SPLC NVRAM接口定义
#define CONFIG_EPROM_BUS											SPI3									

#define CONFIG_DEBUG_UART											huart6//调试串口
#define CONFIG_GDDC_UART											huart4//GDDC串口
#define CONFIG_GDDC_UART_INSTANCE							UART4//GDDC串口中断
#endif
/*****************************************************************************/
//配置EPROM规格
#if defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP)
#define	CONFIG_EPROM_IIC											1
#define CONFIG_EPROM_SIZE 										CONFIG_AT24C64_SIZE
#define	CONFIG_AT24C64_SIZE										8192
#define	CONFIG_AT24C128_SIZE 									16384
#define	CONFIG_AT24C256_SIZE 									32768//32K*8
#define CONFIG_FM25W256G_SIZE									32768//32K
#define CONFIG_EPROM_WRITE_ADDR								0xA0//
#define CONFIG_EPROM_READ_ADDR								0xA1//
#define CONFIG_EPROM_TIMEOUT									1000//EPROM读写超时
#define CONFIG_EPROM_PAGE_SIZE								0x08//EPROM 页大小
#define CONFIG_EPROM_WRITE_DELAY							0//写入等待时间mS
#endif

#if defined(LYPE_MCU_1V0_20260106)
#define CONFIG_EPROM_SPI											
#define CONFIG_EPROM_SIZE 										CONFIG_FM25W256G_SIZE
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
#endif

#if defined(LYPE_SURGI_LDR5_20260519)
#define CONFIG_EPROM_SPI											
#define CONFIG_EPROM_SIZE 										CONFIG_FM25W256G_SIZE
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
#endif

#if defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
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
#endif

//配置ADC
#if defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP)
#define CONFIG_VREF_CAL                     	*(__IO uint16_t *)(0x1FFF7A2A)//校正电压源
#define CONFIG_ADC1_CHANNEL										13//ADC采集通道
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

#define HDC1080_SOFTI2C_DELAY									10//HDC1080 I2C读写频率
#endif

#if defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
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

#define HDC1080_SOFTI2C_DELAY									10//HDC1080 I2C读写频率
#endif


#if defined(LYPE_MCU_1V0_20260106)
#define CONFIG_ADC1_CHANNEL										7//ADC采集通道
#define CONFIG_ADC3_CHANNEL										3//ADC采集通道
#define ADC_FILTER_ALPHA    									0.25f//0.1f：滤波极强，超平滑 0.25f：平衡响应与滤波（推荐） 0.5f：响应快，滤波弱
#define CONFIG_ADC_AVERAGE_NUM								10//ADC平均值次数
#define CONFIG_VREF_CAL                     	*(__IO uint16_t *)(0x1FFF7A2A)//校正电压源
#define CONFIG_ADC1_DMA_BUFFER_SIZE						(CONFIG_ADC1_CHANNEL * CONFIG_ADC_AVERAGE_NUM)//ADC DMA采集缓冲
#define CONFIG_ADC3_DMA_BUFFER_SIZE						(CONFIG_ADC3_CHANNEL * CONFIG_ADC_AVERAGE_NUM)//ADC DMA采集缓冲

#define CONFIG_VREF_ADC												SPREG_ADC_59
#define CONFIG_MCU_VREF												3300.0F
#define CONFIG_ADC_AVG_SLOPE									2.5F
#define CONFIG_ADC_V25												760.0F//0.76V@25D

#define CONFIG_DIODE_NTC_RS										3300L//激光器热敏电阻分压电阻值
#define CONFIG_HT0_NTC_RS											4700L//散热器0热敏电阻分压电阻值
#define CONFIG_HT1_NTC_RS											4700L//散热器1热敏电阻分压电阻值
#define CONFIG_HT2_NTC_RS											4700L//散热器2热敏电阻分压电阻值
#define CONFIG_HT3_NTC_RS											4700L//散热器3热敏电阻分压电阻值
#define CONFIG_WATER_HOT_NTC_RS								11000L//热水端热敏电阻分压电阻值
#define CONFIG_WATER_COOL_NTC_RS							11000L//冷水端热敏电阻分压电阻值
#define CONFIG_AMBIENT_NTC_RS									10000L//环境热敏电阻分压电阻值
#define CONFIG_MBAT_NTC_RS										10000L//环境热敏电阻分压电阻值

#define CONFIG_DIODE_NTC_B										3477.0F//激光器热敏电阻B值
#define CONFIG_HT0_NTC_B											3477.0F//散热器0热敏电阻B值
#define CONFIG_HT1_NTC_B											3477.0F//散热器1热敏电阻B值
#define CONFIG_HT2_NTC_B											3477.0F//散热器2热敏电阻B值
#define CONFIG_HT3_NTC_B											3477.0F//散热器3热敏电阻B值
#define CONFIG_MBAT_NTC_B											3477.0F//散热器3热敏电阻B值

#define CONFIG_WATER_HOT_NTC_B								3900.0F//热水端热敏电阻B值
#define CONFIG_WATER_COOL_NTC_B								3900.0F//冷水端热敏电阻B值
#define CONFIG_AMBIENT_NTC_B									3477.0F//环境热敏电阻B值

#define CONFIG_NTC_R25												10000.0F//25摄氏度时电阻
#define CONFIG_NTC_VREF												3300L//
#define CONFIG_FIBER_PD_THRESHOLD							350//光纤插入时ADC阈值

#define HDC1080_SOFTI2C_DELAY									10//HDC1080 I2C读写频率
#endif

#if defined(LYPE_SURGI_LDR5_20260519)
#define CONFIG_ADC1_CHANNEL										14//ADC采集通道
#define CONFIG_ADC3_CHANNEL										0//ADC采集通道
#define ADC_FILTER_ALPHA    									0.25f//0.1f：滤波极强，超平滑 0.25f：平衡响应与滤波（推荐） 0.5f：响应快，滤波弱
#define CONFIG_ADC_AVERAGE_NUM								10//ADC平均值次数
#define CONFIG_VREF_CAL                     	*(__IO uint16_t *)(0x1FFF7A2A)//校正电压源
#define CONFIG_ADC1_DMA_BUFFER_SIZE						(CONFIG_ADC1_CHANNEL * CONFIG_ADC_AVERAGE_NUM)//ADC DMA采集缓冲
#define CONFIG_ADC3_DMA_BUFFER_SIZE						(CONFIG_ADC3_CHANNEL * CONFIG_ADC_AVERAGE_NUM)//ADC DMA采集缓冲

#define CONFIG_VREF_ADC												SPREG_ADC_59
#define CONFIG_MCU_VREF												3300.0F
#define CONFIG_ADC_AVG_SLOPE									2.5F
#define CONFIG_ADC_V25												760.0F//0.76V@25D

#define CONFIG_DIODE_NTC_RS										3300L//激光器热敏电阻分压电阻值
#define CONFIG_HT0_NTC_RS											4700L//散热器0热敏电阻分压电阻值
#define CONFIG_HT1_NTC_RS											4700L//散热器1热敏电阻分压电阻值
#define CONFIG_HT2_NTC_RS											4700L//散热器2热敏电阻分压电阻值
#define CONFIG_HT3_NTC_RS											4700L//散热器3热敏电阻分压电阻值
#define CONFIG_WATER_HOT_NTC_RS								11000L//热水端热敏电阻分压电阻值
#define CONFIG_WATER_COOL_NTC_RS							11000L//冷水端热敏电阻分压电阻值
#define CONFIG_AMBIENT_NTC_RS									10000L//环境热敏电阻分压电阻值
#define CONFIG_MBAT_NTC_RS										10000L//环境热敏电阻分压电阻值

#define CONFIG_DIODE_NTC_B										3477.0F//激光器热敏电阻B值
#define CONFIG_HT0_NTC_B											3477.0F//散热器0热敏电阻B值
#define CONFIG_HT1_NTC_B											3477.0F//散热器1热敏电阻B值
#define CONFIG_HT2_NTC_B											3477.0F//散热器2热敏电阻B值
#define CONFIG_HT3_NTC_B											3477.0F//散热器3热敏电阻B值
#define CONFIG_MBAT_NTC_B											3477.0F//散热器3热敏电阻B值

#define CONFIG_WATER_HOT_NTC_B								3900.0F//热水端热敏电阻B值
#define CONFIG_WATER_COOL_NTC_B								3900.0F//冷水端热敏电阻B值
#define CONFIG_AMBIENT_NTC_B									3477.0F//环境热敏电阻B值

#define CONFIG_NTC_R25												10000.0F//25摄氏度时电阻
#define CONFIG_NTC_VREF												3300L//
#define CONFIG_FIBER_PD_THRESHOLD							350//光纤插入时ADC阈值

#define HDC1080_SOFTI2C_DELAY									10//HDC1080 I2C读写频率
#endif

/*****************************************************************************/
//配置DAC
#if defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP) ||\
		defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
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
#endif	

#if defined(LYPE_MCU_1V0_20260106)
#define CONFIG_DAC_MAXBIT_CH0									0xFFFF//12BIT STM32
#define CONFIG_DAC_MAXBIT_CH1									0xFFFF//12BIT STM32
#define CONFIG_DAC_MAXBIT_CH2									0xFFFF//12BIT DAC8569
#define CONFIG_DAC_MAXBIT_CH3									0xFFFF//12BIT DAC8568
#define CONFIG_DAC_MAXBIT_CH4									0xFFFF//12BIT DAC8568
#define CONFIG_DAC_MAXBIT_CH5									0xFFFF//12BIT DAC8568
#define CONFIG_DAC_MAXBIT_CH6									0xFFFF//12BIT DAC8568
#define CONFIG_DAC_MAXBIT_CH7									0xFFFF//12BIT DAC

#define CONFIG_DAC_MAXBIT_CH8									0xFFF//12BIT STM32
#define CONFIG_DAC_MAXBIT_CH9									0xFFF//12BIT STM32
#define CONFIG_DAC_MAXBIT_CH10                0xFFFF//NULL
#define CONFIG_DAC_MAXBIT_CH11								0xFFFF//NULL
#define CONFIG_DAC_MAXBIT_CH12								0xFFFF//NULL
#define CONFIG_DAC_MAXBIT_CH13								0xFFFF//NULL
#define CONFIG_DAC_MAXBIT_CH14								0xFFFF//NULL
#define CONFIG_DAC_MAXBIT_CH15								0xFFFF//NULL

#define CONFIG_DAC_MAXBIT_CH16								5000//RED
#define CONFIG_DAC_MAXBIT_CH17								5000//GREEN
#endif

#if defined(LYPE_SURGI_LDR5_20260519)
#define CONFIG_DAC_MAXBIT_CH0									0x0FFF//12BIT DAC7568
#define CONFIG_DAC_MAXBIT_CH1									0x0FFF//12BIT DAC7568
#define CONFIG_DAC_MAXBIT_CH2									0x0FFF//12BIT DAC7568
#define CONFIG_DAC_MAXBIT_CH3									0x0FFF//12BIT DAC7568
#define CONFIG_DAC_MAXBIT_CH4									0x0FFF//12BIT DAC7568
#define CONFIG_DAC_MAXBIT_CH5									0xFFFF//
#define CONFIG_DAC_MAXBIT_CH6									0xFFFF//
#define CONFIG_DAC_MAXBIT_CH7									0xFFFF//

#define CONFIG_DAC_MAXBIT_CH8									0x0FFF//12BIT STM32
#define CONFIG_DAC_MAXBIT_CH9									0x0FFF//12BIT STM32
#define CONFIG_DAC_MAXBIT_CH10                0xFFFF//NULL
#define CONFIG_DAC_MAXBIT_CH11								0xFFFF//NULL
#define CONFIG_DAC_MAXBIT_CH12								0xFFFF//NULL
#define CONFIG_DAC_MAXBIT_CH13								0xFFFF//NULL
#define CONFIG_DAC_MAXBIT_CH14								0xFFFF//NULL
#define CONFIG_DAC_MAXBIT_CH15								0xFFFF//NULL

#define CONFIG_DAC_MAXBIT_CH16								0xFFFF//RED
#define CONFIG_DAC_MAXBIT_CH17								0xFFFF//GREEN
#endif

/*****************************************************************************/
//配置EPROM数据地址
#if defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP)
#define CONFIG_EPROM_MR_START									(0x0L)//
#define CONFIG_EPROM_MR_END										(CONFIG_EPROM_MR_START + MR_END - MR_START)
#define CONFIG_EPROM_DM_START									(CONFIG_EPROM_MR_END + 1)//NVRAM中DM在EPROM储存地址
#define CONFIG_EPROM_DM_END										(CONFIG_EPROM_DM_START + DM_END - DM_START)

#define CONFIG_EPROM_FD_SCHEME_SIZE						((FD_SCHEME_END_0 - FD_SCHEME_START_0 + 1) * 2)//单个方案占用的EPROM空间
#define CONFIG_EPROM_FD_START									(CONFIG_EPROM_DM_END + 1)
#define CONFIG_EPROM_FD_END										(CONFIG_EPROM_FD_START + FD_END - FD_START)

#define CONFIG_EPROM_MEDICAL_CRC							(7520L)//4B 治疗历史 CRC32 硬件计算
#define CONFIG_EPROM_MR_CRC										(7524L)//4B MR NVRAM CRC32 硬件计算
#define CONFIG_EPROM_DM_CRC										(7528L)//4B DM NVRAM CRC32 硬件计算
#define CONFIG_EPROM_FD_CRC										(7532L)//4B FD NVRAM CRC32 硬件计算
#define CONFIG_EPROM_MCU_FW_CRC								(7536L)//4B MCU固件CRC32值 软件计算
#define CONFIG_EPROM_LCD_FW_CRC								(7540L)//4B LCD固件CRC32值 软件计算
#define CONFIG_EPROM_CFG_CRC									(7544L)//4B deviceConfig CRC32值 硬件计算
#define CONFIG_EPROM_LOG_CRC									(7548L)//4B logInfo CRC32值 硬件计算

#define CONFIG_EPROM_CONFIG_START							(7552L)//512B 配置信息区
#define CONFIG_EPROM_CONFIG_END								(8063L)
#define CONFIG_EPROM_LOGINFO_START						(8064L)//128B 记录信息区 
#define CONFIG_EPROM_LOGINFO_END							(8191L)
#endif

#if defined(LYPE_MCU_1V0_20260106) ||\
		defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
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
#endif

#if defined(LYPE_SURGI_LDR5_20260519)
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
#endif
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif






