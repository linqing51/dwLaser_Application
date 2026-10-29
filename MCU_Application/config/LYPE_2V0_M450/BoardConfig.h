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
extern UART_HandleTypeDef huart1;//RASPI
extern UART_HandleTypeDef huart3;//DC HMI
extern UART_HandleTypeDef huart5;//DEBUG
extern SPI_HandleTypeDef hspi3;
extern I2C_HandleTypeDef hi2c3;//IBUS I2C
extern I2C_HandleTypeDef hi2c2;//DAC5578 I2C

extern TIM_HandleTypeDef htim5;//GAIM TIM
extern TIM_HandleTypeDef htim8;//FAN TIM
extern TIM_HandleTypeDef htim7;//LASER TIM
extern TIM_HandleTypeDef htim9;//SKP TIM
extern TIM_HandleTypeDef htim10;//SPI2 TIM
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

/*****************************************************************************/
//引脚功能定义(引脚名映射CubeMX生成的main.h;本机未装通道用__nop占位)
/*****************************************************************************/
//输入
#define GET_ESTOP_NC												HAL_GPIO_ReadPin(ESTOP_NC_GPIO_Port, ESTOP_NC_Pin)//PD0 急停常闭
#define GET_INTERLOCK_NC											HAL_GPIO_ReadPin(INTERLOCK_NC_GPIO_Port, INTERLOCK_NC_Pin)//PH15 安全连锁
#define GET_FSWITCH_NO												HAL_GPIO_ReadPin(FS_NO_GPIO_Port, FS_NO_Pin)//PG5 脚踏常开
#define GET_FSWITCH_NC												HAL_GPIO_ReadPin(FS_NC_GPIO_Port, FS_NC_Pin)//PG6 脚踏常闭
#define GET_PWR_INT													HAL_GPIO_ReadPin(POWER_INT_GPIO_Port, POWER_INT_Pin)//PE2 LTC2955软关机中断
/*****************************************************************************/
//指示灯(低电平点亮): RED=PI11 GREEN=STA0(PE4) BLUE=PF0 PWR=STA1(PE5) ERR=STA2(PI8) TICK=STA3(PC13)
#define SET_RED_LED_ON												HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_RESET)
#define SET_RED_LED_OFF												HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_SET)
#define SET_RED_LED_DC(b)											__nop()
#define SET_GREEN_LED_ON											HAL_GPIO_WritePin(STA0_LED_GPIO_Port, STA0_LED_Pin, GPIO_PIN_RESET)
#define SET_GREEN_LED_OFF											HAL_GPIO_WritePin(STA0_LED_GPIO_Port, STA0_LED_Pin, GPIO_PIN_SET)
#define SET_GREEN_LED_DC(b)										__nop()
#define SET_BLUE_LED_ON												HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, GPIO_PIN_RESET)
#define SET_BLUE_LED_OFF											HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, GPIO_PIN_SET)
#define SET_BLUE_LED_DC(b)											__nop()
#define SET_TICK_LED_ON												HAL_GPIO_WritePin(STA3_LED_GPIO_Port, STA3_LED_Pin, GPIO_PIN_RESET)
#define SET_TICK_LED_OFF											HAL_GPIO_WritePin(STA3_LED_GPIO_Port, STA3_LED_Pin, GPIO_PIN_SET)
#define SET_ERR_LED_ON												HAL_GPIO_WritePin(STA2_LED_GPIO_Port, STA2_LED_Pin, GPIO_PIN_RESET)
#define SET_ERR_LED_OFF												HAL_GPIO_WritePin(STA2_LED_GPIO_Port, STA2_LED_Pin, GPIO_PIN_SET)
#define SET_PWR_LED_ON												HAL_GPIO_WritePin(STA1_LED_GPIO_Port, STA1_LED_Pin, GPIO_PIN_RESET)
#define SET_PWR_LED_OFF												HAL_GPIO_WritePin(STA1_LED_GPIO_Port, STA1_LED_Pin, GPIO_PIN_SET)
#define FLIP_TICK_LED												HAL_GPIO_TogglePin(STA3_LED_GPIO_Port, STA3_LED_Pin)
//蜂鸣器/提示音使能(与SPK_EN同一引脚PC14,高电平使能)
#define SET_BEEM_LED_ON												HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_SET)
#define SET_BEEM_LED_OFF											HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_RESET)
/*****************************************************************************/
//喇叭音频功放与PWM(htim9 CH2 -> PE6),功放使能低有效
#define SET_SPK_AP_ON												HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_RESET)
#define SET_SPK_AP_OFF												HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_SET)
#define SET_SPK_TIM_ON												HAL_TIM_PWM_Start(&CONFIG_SPK_HANDLE, CONFIG_SPK_PWM_CHANNEL)
#define SET_SPK_TIM_OFF												HAL_TIM_PWM_Stop(&CONFIG_SPK_HANDLE, CONFIG_SPK_PWM_CHANNEL)
//MCP41010数字电位器(音量) 模拟SPI
#define SET_MCP41010_CS(b)											HAL_GPIO_WritePin(MCP41010_CS_GPIO_Port, MCP41010_CS_Pin, b)
#define SET_MCP41010_SDI(b)										HAL_GPIO_WritePin(MCP41010_SDI_GPIO_Port, MCP41010_SDI_Pin, b)
#define SET_MCP41010_SCK(b)										HAL_GPIO_WritePin(MCP41010_SCK_GPIO_Port, MCP41010_SCK_Pin, b)
/*****************************************************************************/
//激光通道使能(实际装配CH0=LAS0 PE14,CH1=LAS1 PE13,高有效;CH2=635经DAC16;其余通道未装)
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
#define GET_LASER_CH0												HAL_GPIO_ReadPin(LAS0_PWM_GPIO_Port, LAS0_PWM_Pin)
#define GET_LASER_CH1												HAL_GPIO_ReadPin(LAS1_PWM_GPIO_Port, LAS1_PWM_Pin)
#define GET_LASER_CH2												0
#define GET_LASER_CH3												0
#define GET_LASER_CH4												0
#define GET_LASER_CH5												0
#define GET_LASER_CH6												0
#define GET_LASER_CH7												0
/*****************************************************************************/
//TEC使能(CH0=PB11 CH1=PB10 CH2=PH7 CH3=PH6 CH4=PH9 CH5=PH8 CH6=PH11 CH7=PH10,高有效)
#define SET_TEC_CH0_ON												HAL_GPIO_WritePin(TEC0_PWM_GPIO_Port, TEC0_PWM_Pin, GPIO_PIN_SET)
#define SET_TEC_CH0_OFF											HAL_GPIO_WritePin(TEC0_PWM_GPIO_Port, TEC0_PWM_Pin, GPIO_PIN_RESET)
#define SET_TEC_CH1_ON												HAL_GPIO_WritePin(TEC1_PWM_GPIO_Port, TEC1_PWM_Pin, GPIO_PIN_SET)
#define SET_TEC_CH1_OFF											HAL_GPIO_WritePin(TEC1_PWM_GPIO_Port, TEC1_PWM_Pin, GPIO_PIN_RESET)
#define SET_TEC_CH2_ON												HAL_GPIO_WritePin(TEC2_PWM_GPIO_Port, TEC2_PWM_Pin, GPIO_PIN_SET)
#define SET_TEC_CH2_OFF											HAL_GPIO_WritePin(TEC2_PWM_GPIO_Port, TEC2_PWM_Pin, GPIO_PIN_RESET)
#define SET_TEC_CH3_ON												HAL_GPIO_WritePin(TEC3_PWM_GPIO_Port, TEC3_PWM_Pin, GPIO_PIN_SET)
#define SET_TEC_CH3_OFF											HAL_GPIO_WritePin(TEC3_PWM_GPIO_Port, TEC3_PWM_Pin, GPIO_PIN_RESET)
#define SET_TEC_CH4_ON												HAL_GPIO_WritePin(TEC4_PWM_GPIO_Port, TEC4_PWM_Pin, GPIO_PIN_SET)
#define SET_TEC_CH4_OFF											HAL_GPIO_WritePin(TEC4_PWM_GPIO_Port, TEC4_PWM_Pin, GPIO_PIN_RESET)
#define SET_TEC_CH5_ON												HAL_GPIO_WritePin(TEC5_PWM_GPIO_Port, TEC5_PWM_Pin, GPIO_PIN_SET)
#define SET_TEC_CH5_OFF											HAL_GPIO_WritePin(TEC5_PWM_GPIO_Port, TEC5_PWM_Pin, GPIO_PIN_RESET)
#define SET_TEC_CH6_ON												HAL_GPIO_WritePin(TEC6_PWM_GPIO_Port, TEC6_PWM_Pin, GPIO_PIN_SET)
#define SET_TEC_CH6_OFF											HAL_GPIO_WritePin(TEC6_PWM_GPIO_Port, TEC6_PWM_Pin, GPIO_PIN_RESET)
#define SET_TEC_CH7_ON												HAL_GPIO_WritePin(TEC7_PWM_GPIO_Port, TEC7_PWM_Pin, GPIO_PIN_SET)
#define SET_TEC_CH7_OFF											HAL_GPIO_WritePin(TEC7_PWM_GPIO_Port, TEC7_PWM_Pin, GPIO_PIN_RESET)
//TEC功率级闸门(本机无独立闸门引脚)
#define SET_TEC_GATE_CH0_ON										__nop()
#define SET_TEC_GATE_CH0_OFF										__nop()
#define SET_TEC_GATE_CH1_ON										__nop()
#define SET_TEC_GATE_CH1_OFF										__nop()
/*****************************************************************************/
//风扇0 PWM htim8 CH3 -> PI7
#define SET_FAN0_ON													HAL_TIM_PWM_Start(&CONFIG_FAN0_TIM_HANDLE, CONFIG_FAN0_PWM_CHANNEL)
#define SET_FAN0_OFF												HAL_TIM_PWM_Stop(&CONFIG_FAN0_TIM_HANDLE, CONFIG_FAN0_PWM_CHANNEL)
#define SET_FAN0_TIM_PWM(b)										__HAL_TIM_SET_COMPARE(&CONFIG_FAN0_TIM_HANDLE, CONFIG_FAN0_PWM_CHANNEL, b)
#define SET_FAN1_ON												__nop()
#define SET_FAN1_OFF												__nop()
#define SET_FAN1_TIM_PWM(b)									__nop()
#define SET_FAN2_ON												__nop()
#define SET_FAN2_OFF												__nop()
#define SET_FAN2_TIM_PWM(b)									__nop()
/*****************************************************************************/
//红色指示光635: 本机无独立PWM调光引脚(亮度经DAC16),定时器占位
#define SET_RAIM_TIM_ON												__nop()
#define SET_RAIM_TIM_OFF											__nop()
#define SET_RAIM_TIM_PWM(b)										__nop()
#define SET_RAIM_SHDN(b)											__nop()
#define SET_RAIM_SHDN_ON											__nop()
#define SET_RAIM_SHDN_OFF											__nop()
#define GET_RAIM_SHDN												0
//绿色指示光532: htim5 CH3 -> PH12,关断脚GAIM_SHDN PB14
#define SET_GAIM_TIM_ON											HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3)
#define SET_GAIM_TIM_OFF											HAL_TIM_PWM_Stop(&htim5, TIM_CHANNEL_3)
#define SET_GAIM_TIM_PWM(b)										__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_3, b)
#define SET_GAIM_SHDN(b)											HAL_GPIO_WritePin(GAIM_SHDN_GPIO_Port, GAIM_SHDN_Pin, b)
#define SET_GAIM_SHDN_ON											HAL_GPIO_WritePin(GAIM_SHDN_GPIO_Port, GAIM_SHDN_Pin, GPIO_PIN_SET)
#define SET_GAIM_SHDN_OFF											HAL_GPIO_WritePin(GAIM_SHDN_GPIO_Port, GAIM_SHDN_Pin, GPIO_PIN_RESET)
#define GET_GAIM_SHDN												HAL_GPIO_ReadPin(GAIM_SHDN_GPIO_Port, GAIM_SHDN_Pin)
/*****************************************************************************/
//DAC8568 软件SPI(SYNC=PF13 SCK=PF14 DOUT=PF15 CLR=PG0)
#define SET_DAC8568_SYNC(b)										HAL_GPIO_WritePin(DAC8568_NSS_GPIO_Port, DAC8568_NSS_Pin, b)
#define SET_DAC8568_SCK(b)											HAL_GPIO_WritePin(DAC8568_SCK_GPIO_Port, DAC8568_SCK_Pin, b)
#define SET_DAC8568_DOUT(b)										HAL_GPIO_WritePin(DAC8568_DOUT_GPIO_Port, DAC8568_DOUT_Pin, b)
#define SET_DAC8568_CLR(b)											HAL_GPIO_WritePin(DAC8568_CLEAR_GPIO_Port, DAC8568_CLEAR_Pin, b)
/*****************************************************************************/
//FRAM SPI 片选 PA15
#define EPROM_SPI_NSS(b)											HAL_GPIO_WritePin(EPROM_NSS_GPIO_Port, EPROM_NSS_Pin, b)
#define EPROM_SPI_NSS_DESEL										HAL_GPIO_WritePin(EPROM_NSS_GPIO_Port, EPROM_NSS_Pin, GPIO_PIN_SET)
#define EPROM_SPI_NSS_SEL											HAL_GPIO_WritePin(EPROM_NSS_GPIO_Port, EPROM_NSS_Pin, GPIO_PIN_RESET)
/*****************************************************************************/
//HDC1080 软件I2C(SCL=PG14 SDA=PG13)
#define SET_HDC1080_SCL(b)											HAL_GPIO_WritePin(HDC1080_SCL_GPIO_Port, HDC1080_SCL_Pin, b)
#define SET_HDC1080_SDA(b)											HAL_GPIO_WritePin(HDC1080_SDA_GPIO_Port, HDC1080_SDA_Pin, b)
#define GET_HDC1080_SDA												HAL_GPIO_ReadPin(HDC1080_SDA_GPIO_Port, HDC1080_SDA_Pin)
/*****************************************************************************/
//安全锁接触 PH14
#define SET_SAFE_RESET(b)											HAL_GPIO_WritePin(SAFE_RESET_GPIO_Port, SAFE_RESET_Pin, b)
#define SET_SAFE_RESET_ON											HAL_GPIO_WritePin(SAFE_RESET_GPIO_Port, SAFE_RESET_Pin, GPIO_PIN_SET)
#define SET_SAFE_RESET_OFF											HAL_GPIO_WritePin(SAFE_RESET_GPIO_Port, SAFE_RESET_Pin, GPIO_PIN_RESET)
/*****************************************************************************/
//LTC2955电源管理: KILL脚PE1,拉低关机
#define SET_PWR_KILL_ON												HAL_GPIO_WritePin(POWER_KILL_GPIO_Port, POWER_KILL_Pin, GPIO_PIN_RESET)//执行软关机
#define SET_PWR_KILL_POWER_ON										HAL_GPIO_WritePin(POWER_KILL_GPIO_Port, POWER_KILL_Pin, GPIO_PIN_RESET)
#define SET_PWR_KILL_POWER_OFF										HAL_GPIO_WritePin(POWER_KILL_GPIO_Port, POWER_KILL_Pin, GPIO_PIN_SET)
#define GET_PWR_KILL													HAL_GPIO_ReadPin(POWER_KILL_GPIO_Port, POWER_KILL_Pin)
#define FLIP_PWR_KILL												HAL_GPIO_TogglePin(POWER_KILL_GPIO_Port, POWER_KILL_Pin)
/*****************************************************************************/
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

#define CONFIG_SPI2_TIM												TIM10

#define CONFIG_EPROM_BUS_HANDLE								hspi3//SPLC NVRAM接口定义
#define CONFIG_EPROM_BUS											SPI3									

#define CONFIG_DEBUG_UART											huart5//调试串口
#define CONFIG_GDDC_UART											huart3//GDDC串口
#define CONFIG_GDDC_UART_INSTANCE							USART3//GDDC串口中断

#define CONFIG_MBI2C_BUS											hi2c2//主板I2C总线


#define CONFIG_PMU_LTC2955											1//电源管理使用LTC2955(使能sPlcPMU_LTC2955)
#define CONFIG_EPROM_SPI											1
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


#define CONFIG_ADC1_CHANNEL										16//ADC1采集通道
#define CONFIG_ADC3_CHANNEL										3//ADC3采集通道
#define CONFIG_ADC_CHANNEL											(CONFIG_ADC1_CHANNEL)//共享代码ADC采集通道数(主ADC1)
#define ADC_FILTER_ALPHA    									0.25f//0.1f：滤波极强，超平滑 0.25f：平衡响应与滤波（推荐） 0.5f：响应快，滤波弱
#define CONFIG_ADC_AVERAGE_NUM								16//ADC平均值次数
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
/*****************************************************************************/
//配置TEC温控(共享tempCtrLoop参数)
#define CONFIG_TEC_HT_FF_GAIN								20.0f//散热器温度前馈增益
#define CONFIG_TEC_SLEW_STEP								200//输出变化率限幅: 每500ms控制周期最多变化计数(0~4095)
#define CONFIG_TEC_TEMP_FILTER_ALPHA				0.5f//反馈温度一阶滤波系数(0~1), 抑制NTC噪声放大

#define HDC1080_SOFTI2C_DELAY									10//HDC1080 I2C读写频率


/*****************************************************************************/
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
#define CONFIF_EPROM_TREATMENT_CRC						(CONFIG_EPROM_MEDICAL_CRC)//4B treatment CRC32值 硬件计算(沿用原治疗历史CRC地址)
#define CONFIG_EPROM_MR_CRC										(31470L)//4B MR NVRAM CRC32 硬件计算
#define CONFIG_EPROM_DM_CRC										(31474L)//4B DM NVRAM CRC32 硬件计算
#define CONFIG_EPROM_FD_CRC										(31478L)//4B FD NVRAM CRC32 硬件计算
#define CONFIG_EPROM_MCU_FW_CRC								(31482L)//4B MCU固件CRC32值 软件计算
#define CONFIG_EPROM_LCD_FW_CRC								(31486L)//4B LCD固件CRC32值 软件计算
#define CONFIG_EPROM_CFG_CRC									(31480L)//4B deviceConfig CRC32值 硬件计算
#define CONFIG_EPROM_LOG_CRC									(31484L)//4B logInfo CRC32值 硬件计算

//治疗记录历史病历区块: 位于FD数据区实际末址(4639)之后、治疗CRC(31466)之前,不改动任何既有地址
#define CONFIG_EPROM_TREATMENT_END						(31465L)
#define CONFIG_EPROM_TREATMENT_SIZE						(26826L)//治疗记录区块字节数(START=4640)
#define CONFIG_EPROM_TREATMENT_START					(CONFIG_EPROM_TREATMENT_END - CONFIG_EPROM_TREATMENT_SIZE + 1L)

#define CONFIG_EPROM_CONFIG_START							(31488L)//1024B 配置信息区
#define CONFIG_EPROM_CONFIG_END								(32511L)
#define CONFIG_EPROM_LOGINFO_START						(32512L)//256B 记录信息区 
#define CONFIG_EPROM_LOGINFO_END							(32767L)
/****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif






