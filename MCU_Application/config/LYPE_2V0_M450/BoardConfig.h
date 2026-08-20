#ifndef __BOARDCONFIG_H__
#define __BOARDCONFIG_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
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
//引脚功能定义
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


#define CONFIG_ADC1_CHANNEL										16//ADC采集通道
#define CONFIG_ADC3_CHANNEL										3//ADC采集通道
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

#define HDC1080_SOFTI2C_DELAY									10//HDC1080 I2C读写频率
#endif


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
/****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif






