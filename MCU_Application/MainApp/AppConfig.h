#ifndef __APPCONFIG_H__
#define __APPCONFIG_H__
/*****************************************************************************/
#define SW_VERSION																		"3.1a17b8"
#define HW_VERSION																		"LDR2P1_G5_A1_20250731_DUAL"
/*****************************************************************************/
#if defined(MODEL_PVGLS_7W_1940_A0) || defined(MODEL_PVGLS_10W_1940_A1)
#define APP_CONFIG_WAVE_1940_650//APP为双波长 1940+650
#define GDDC_PAGE_STANDBY 														GDDC_PAGE_STANDBY_DUAL
#endif
#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1) || defined(GLOAL_LDR2P1_G5_A1_20250731_DUAL)
#define APP_CONFIG_WAVE_1470_650//APP为双波长 1470+650
#define GDDC_PAGE_STANDBY 														GDDC_PAGE_STANDBY_DUAL
#endif
#if defined(MODEL_PVGLS_TRI_A0) || defined(MODEL_PVGLS_TRI_COMBINE_A0) || defined(GLOAL_LDR2P1_G5_A1_20250731_TRIP)
#define APP_CONFIG_WAVE_1470_980_650//APP为三波长 1470+650
#define GDDC_PAGE_STANDBY 														GDDC_PAGE_STANDBY_TRI
#endif

//激光器选这
#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1) || defined(GLOAL_LDR2P1_G5_A1_20250731_DUAL)
#define MODLE_M1470_640_10_15_02_D200_22_G5W_PK//1470+650 V1
#endif

#if defined(MODEL_PVGLS_TRI_A0) || defined(MODEL_PVGLS_TRI_COMBINE_A0)
#define MODLE_M1470_980_640_10_15_35_05_D200_22_G5W_PK//1470+980+650 V1
#endif 

#if defined(GLOAL_LDR2P1_G5_A1_20250731_TRIP)
#define MODLE_M1470_980_640_10_15_35_05_D200_22_G5W_PK//1470+980+650 V1
//#define MODLE_M1470_980_640_10_15_15_02_D200_22_G5W_PK//1470+980+650 V2
#endif

#if defined(MODEL_PVGLS_10W_1940_A1)
#define MODLE_M12_1920_10_400S//吉光1940
#endif

#if defined(GLOAL_LDR2P1_G5_A1_20250731_DUAL) || defined(GLOAL_LDR2P1_G5_A1_20250731_TRIP)
#define APP_CONFIG_WFSW_PORT													hUsbHostFS
#else
#define APP_CONFIG_WFSW_PORT													hUsbHostFS
#endif
/*****************************************************************************/
#define LASER_CHANNEL_CH0															0x01//1470 1940
#define LASER_CHANNEL_CH1															0x02//980
#define LASER_CHANNEL_CH2															0x03
#define LASER_CHANNEL_CH3															0x04
#define LASER_CHANNEL_RED															0x05//红激光
#define LASER_CHANNEL_CH0_RED													0x06
#define LASER_CHANNEL_CH1_RED													0x07
/*****************************************************************************/
#define SCHEME_PHLEBOLOGY															0x0001
#define SCHEME_PROCTOLOGY															0x0002
#define SCHEME_GYNECOLOGY															0x0003
#define SCHEME_ENT																		0x0004
#define SCHEME_NEUROSURGERY														0x0005
#define SCHEME_DERMATOLOGY														0x0006
#define SCHEME_LIPOSUCTION														0x0007
#define SCHEME_DENTISTRY															0x0008
#define SCHMEM_THERAPY																0x0009
#define SCHEME_CUSTIOM																0x0000
/*****************************************************************************/
//定义分类方案个数
#define CONFIG_PHLEBOLOGY_SIZE												3
#define CONFIG_PROCTOLOGY_SIZE												6
#define CONFIG_GYNECOLOGY_SIZE												22
#define CONFIG_ENT_SIZE																16
#if defined(MODEL_PVGLS_TRI_A0) || defined(GLOAL_LDR2P1_G5_A1_20250731_TRIP)
#define CONFIG_NEUROSURGERY_SIZE											5
#endif

#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1) || defined(GLOAL_LDR2P1_G5_A1_20250731_DUAL)
#define CONFIG_NEUROSURGERY_SIZE											3
#endif

#define CONFIG_DERMATOLOGY_SIZE												9
#define CONFIG_LIPOSUCTION_SIZE												7
#define CONFIG_DENTISRTY_SIZE													23

#if defined(MODEL_PVGLS_TRI_A0) || defined(GLOAL_LDR2P1_G5_A1_20250731_TRIP)
#define CONFIG_THERAPY_SIZE														8
#endif

#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1) || defined(GLOAL_LDR2P1_G5_A1_20250731_DUAL)
#define CONFIG_THERAPY_SIZE														3
#endif
//方案配置
/*****************************************************************************/
#define CONFIG_CUSTIOM_SIZE														32
/*****************************************************************************/
#define CONFIG_MORSECODE_SPACE_TIME										3000
#define CONFIG_MORSECODE_LONG_TIME										900
#define CONFIG_MORSECODE_SHORT_TIME										300
/*****************************************************************************/
#define CONFIG_GDDC_UART_BAUDRATE											115200//LCD通信波特率
/*****************************************************************************/
#define BOOTLOAD_MAIN_ADDRESS													0x0800FE00//主版本标识地址															
#define BOOTLAOD_MINOR_ADDRESS												0x0800FE01//次版本标识地址
#define STM32_UNIQUE_ID_SIZE 													12//MCU序列号  8*12=96Bit
#define DEVID_H																				'1'//设备ID
#define DEVID_L																				'A'//设备ID
#define BUFFER_SIZE        														((uint16_t)512*32)//512的整数倍
#define CONFIG_JUMP_DELAY															7000//检测U盘时间
#define FATFS_ROOT																		"0:"
#define BOOTLOAD_FILENAME															"/bootload.bin"//引导固件
#define LOG_FIRMWARE_FILENAME													"/log.txt"//操作记录文件
#define CFG_FIRMWARE_FILENAME													"/las.cfg"//操作配置文件
#define LMCU_FIRMWARE_FILENAME												"/ld_mcu.bin"//更新MCU固件地址
#define LLCD_FIRMWARE_FILENAME												"/ld_lcd.pkg"//更新LCD固件地址
#define SAVE_EPROM_FILENAME														"/seprom.bin"//EPROM->UDISK 储存名称
#define LOAD_EPROM_FILENAME														"/leprom.bin"//UDISK->EPROM 恢复名称
/*****************************************************************************/				
#define CONFIG_MAX_SPK_FREQ														4500L//喇叭最高频率
#define CONFIG_MIN_SPL_FREQ														500//喇叭最低频率
#define CONFIG_DEFAULT_SPK_FREQ												1100//蜂鸣器默认频率
#define CONFIG_ACOUSITC_SPK_FREQ											1400//蜂鸣器变声频率
/*****************************************************************************/
#define CONFIG_WAIT_HMI_DELAY_TIME										40
#define CONFIG_WAIT_PASSWORD_DELAY_TIME								90
#define CONFIG_KEY_REPEAT_DELAY_TIME									80
#define CONFIG_STANDBY_BEEM_DELAY_TIME								20
#define CONFIG_WFSWITCH_DISCONNECT_DELAY_TIME					10//无线脚踏掉线超时 10mS * 100
/*****************************************************************************/
#define CONFIG_DIODE_SET_TEMP													240//
#define CONFIG_DIODE_HIGH_TEMP												450//激光器高温极限 46.0C
#define CONFIG_DIODE_LOW_TEMP													-250//激光器低温极限 -25.0C
#define CONFIG_ENVI_HIGH_TEMP													750//处理器高温极限 75.0C
#define CONFIG_ENVI_LOW_TEMP													-200//处理器低温极限 -20.0C
/*****************************************************************************/
#define CONFIG_HMI_SCHEME_NUM													32//每分类方案数
#define CONFIG_HMI_ADMIN_PASSWORD0										0x3532//管理员密码
#define CONFIG_HMI_ADMIN_PASSWORD1										0x3038//管理员密码
#define CONFIG_HMI_ADMIN_PASSWORD2										0x3030//管理员密码
#define CONFIG_HMI_ADMIN_PASSWORD3										0x3030//管理员密码
#define CONFIG_HMI_DEFAULT_PASSWORD0									0x3030//默认密码
#define CONFIG_HMI_DEFAULT_PASSWORD1									0x3030//默认密码
#define CONFIG_HMI_DEFAULT_PASSWORD2									0x3030//默认密码
#define CONFIG_HMI_DEFAULT_PASSWORD3									0x3030//默认密码
#define CONFIG_SCHEME_NAME_SIZE												((EM_LASER_CHANNEL_SELECT - EM_LASER_SCHEME_NAME -1) * 2)//
/*****************************************************************************/
#define CONFIG_MAX_LASER_DAC_CH0											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH1											0xFFF//

#define CONFIG_MAX_LASER_POWER_RED                    5//红激光最大功率 5档
#define CONFIG_MAX_LASER_POWER_AIM                    10//指示激光最大功率 10档

#define CONFIG_MIN_LASER_POWER_RED                    1//红激光最小功率
#define CONFIG_MIN_LASER_POWER_AIM                    0//指示激光最小功率

#if defined(GLOAL_LDR2P1_G5_A1_20250731_DUAL) || defined(GLOAL_LDR2P1_G5_A1_20250731_TRIP)
#define CONFIG_MAX_LASER_POWER_CH0										150//通道1470最大激光功率
#define CONFIG_MAX_LASER_POWER_CH1										150//通道980最大激光功率
#define CONFIG_MIN_LASER_POWER_CH0										1//通道1470最小激光功率		
#define CONFIG_MIN_LASER_POWER_CH1										1//通道980最小激光功率		
#endif

#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
#define CONFIG_MAX_LASER_POWER_CH0										150//通道1470最大激光功率
#define CONFIG_MAX_LASER_POWER_CH1										150//通道980最大激光功率
#define CONFIG_MIN_LASER_POWER_CH0										1//通道1470最小激光功率		
#define CONFIG_MIN_LASER_POWER_CH1										1//通道980最小激光功率								
#endif
#if defined(MODEL_PVGLS_10W_1940_A1)
#define CONFIG_MAX_LASER_POWER_CH0										100//通道1940最大激光功率
#define CONFIG_MAX_LASER_POWER_CH1										150//通道980最大激光功率
#define CONFIG_MIN_LASER_POWER_CH0										1//通道1940最小激光功率
#define CONFIG_MIN_LASER_POWER_CH1										1//通道980最小激光功率
#endif

#define CONFIG_MAX_LASER_POSWIDTH											16000
#define CONFIG_MIN_LASER_POSWIDTH											1
#define CONFIG_MAX_LASER_NEGWIDTH											16000
#define CONFIG_MIN_LASER_NEGWIDTH											1
#define CONFIG_MAX_LASER_TIMES												10//最大可计数脉冲数
#define CONFIG_MIN_LASER_TIMES												1//最小可计数脉冲数
#define CONFIG_MAX_LASER_GROUP_OFF										1000
#define CONFIG_MIN_LASER_GROUP_OFF										10
#define CONFIG_MAX_LASER_ENERGY_INTERVAL							200
#define CONFIG_MIN_LASER_ENERGY_INTERVAL							30
#define CONFIG_STEP_LASER_ENERGY_INTERVAL							10
#define CONFIG_BEEM_ENERGY_INTERVAL_TIME							1000//变音持续时间
//定义指示灯亮度
#if defined(GLOAL_LDR2P1_G5_A1_20250731_DUAL) || defined(GLOAL_LDR2P1_G5_A1_20250731_TRIP)
#define CONFIG_BLUE_LED_MAX_DC												100
#define CONFIG_BLUE_LED_DEFAULT_DC										25
#define CONFIG_RED_LED_MAX_DC													100	
#define CONFIG_RED_LED_DEFAULT_DC											25
#define CONFIG_GREEN_LED_MAX_DC												100
#define CONFIG_GREEN_LED_DEFAULT_DC										25
#endif
#ifdef MODEL_PVGLS_15W_1470_A0
#define CONFIG_BLUE_LED_MAX_DC												100
#define CONFIG_BLUE_LED_DEFAULT_DC										10
#define CONFIG_RED_LED_MAX_DC													100	
#define CONFIG_RED_LED_DEFAULT_DC											25
#define CONFIG_GREEN_LED_MAX_DC												100
#define CONFIG_GREEN_LED_DEFAULT_DC										10
#endif
/*****************************************************************************/
#ifdef MODEL_PVGLS_15W_1470_A1
#define CONFIG_BLUE_LED_MAX_DC												100
#define CONFIG_BLUE_LED_DEFAULT_DC										50
#define CONFIG_RED_LED_MAX_DC													100	
#define CONFIG_RED_LED_DEFAULT_DC											50
#define CONFIG_GREEN_LED_MAX_DC												100
#define CONFIG_GREEN_LED_DEFAULT_DC										50
#endif
/*****************************************************************************/
#ifdef MODEL_PVGLS_10W_1940_A1
#define CONFIG_BLUE_LED_MAX_DC												100
#define CONFIG_BLUE_LED_DEFAULT_DC										90
#define CONFIG_RED_LED_MAX_DC													100	
#define CONFIG_RED_LED_DEFAULT_DC											90
#define CONFIG_GREEN_LED_MAX_DC												100
#define CONFIG_GREEN_LED_DEFAULT_DC										90
#endif
/*****************************************************************************/
#define CONFIG_AIM_DEFAULT_GAIN												95
//定义蜂鸣器音量/频率
#define CONFIG_BEEM_MAX_VOLUME												100//蜂鸣器最大音量
#define CONFIG_BEEM_MAX_LIMIT													0.7F//
#define CONFIG_BEEM_MAX_FREQ													4500L//喇叭最高频率
#define CONFIG_BEEM_MIN_FREQ													500//喇叭最低频率
//定义屏幕亮度
#define CONFIG_LCD_MAX_DC															100//屏幕亮度最大值
#define CONFIG_LCD_MIN_DC															1//屏幕亮度最小值
//定义风扇转速
#define CONFIG_FAN_MAX_DC															100
#define CONFIG_FAN_MIN_DC															0
/*****************************************************************************/
#define CONFIG_USING_DEFAULT_SCHEME										1//是能预设模式
#define CONFIG_MAX_SCHEME_NAME_SIZE										40//方案名称长度
/*****************************************************************************/
#define CONFIG_FSWITCH_USB_VID												0x16C0
#define CONFIG_FSWITCH_USB_PID												0x05E2
/*****************************************************************************/
#define POWER_REAL_CH0_5P															200
#define POWER_REAL_CH0_10P														400
#define POWER_REAL_CH0_15P														600
#define POWER_REAL_CH0_20P														800
#define POWER_REAL_CH0_25P														1000
#define POWER_REAL_CH0_30P														1200
#define POWER_REAL_CH0_35P														1400
#define POWER_REAL_CH0_40P														1600
#define POWER_REAL_CH0_45P														1800
#define POWER_REAL_CH0_50P														2000
#define POWER_REAL_CH0_55P														2200
#define POWER_REAL_CH0_60P														2400
#define POWER_REAL_CH0_65P														2600
#define POWER_REAL_CH0_70P														2800
#define POWER_REAL_CH0_75P														3000
#define POWER_REAL_CH0_80P														3200
#define POWER_REAL_CH0_85P														3400
#define POWER_REAL_CH0_90P														3600
#define POWER_REAL_CH0_95P														3800
#define POWER_REAL_CH0_100P														4000
/*****************************************************************************/
#define POWER_REAL_CH1_5P															150
#define POWER_REAL_CH1_10P														300
#define POWER_REAL_CH1_15P														450
#define POWER_REAL_CH1_20P														800
#define POWER_REAL_CH1_25P														1000
#define POWER_REAL_CH1_30P														1200
#define POWER_REAL_CH1_35P														1400
#define POWER_REAL_CH1_40P														1600
#define POWER_REAL_CH1_45P														1800
#define POWER_REAL_CH1_50P														2000
#define POWER_REAL_CH1_55P														2200
#define POWER_REAL_CH1_60P														2400
#define POWER_REAL_CH1_65P														2600
#define POWER_REAL_CH1_70P														2800
#define POWER_REAL_CH1_75P														3000
#define POWER_REAL_CH1_80P														3200
#define POWER_REAL_CH1_85P														3400
#define POWER_REAL_CH1_90P														3600
#define POWER_REAL_CH1_95P														3800
#define POWER_REAL_CH1_100P														4000
/*****************************************************************************/
#define POWER_REAL_CH2_5P															150
#define POWER_REAL_CH2_10P														300
#define POWER_REAL_CH2_15P														450
#define POWER_REAL_CH2_20P														800
#define POWER_REAL_CH2_25P														1000
#define POWER_REAL_CH2_30P														1200
#define POWER_REAL_CH2_35P														1400
#define POWER_REAL_CH2_40P														1600
#define POWER_REAL_CH2_45P														1800
#define POWER_REAL_CH2_50P														2000
#define POWER_REAL_CH2_55P														2200
#define POWER_REAL_CH2_60P														2400
#define POWER_REAL_CH2_65P														2600
#define POWER_REAL_CH2_70P														2800
#define POWER_REAL_CH2_75P														3000
#define POWER_REAL_CH2_80P														3200
#define POWER_REAL_CH2_85P														3400
#define POWER_REAL_CH2_90P														3600
#define POWER_REAL_CH2_95P														3800
#define POWER_REAL_CH2_100P														4000
/*****************************************************************************/
#define POWER_REAL_CH3_5P															150
#define POWER_REAL_CH3_10P														300
#define POWER_REAL_CH3_15P														450
#define POWER_REAL_CH3_20P														800
#define POWER_REAL_CH3_25P														1000
#define POWER_REAL_CH3_30P														1200
#define POWER_REAL_CH3_35P														1400
#define POWER_REAL_CH3_40P														1600
#define POWER_REAL_CH3_45P														1800
#define POWER_REAL_CH3_50P														2000
#define POWER_REAL_CH3_55P														2200
#define POWER_REAL_CH3_60P														2400
#define POWER_REAL_CH3_65P														2600
#define POWER_REAL_CH3_70P														2800
#define POWER_REAL_CH3_75P														3000
#define POWER_REAL_CH3_80P														3200
#define POWER_REAL_CH3_85P														3400
#define POWER_REAL_CH3_90P														3600
#define POWER_REAL_CH3_95P														3800
#define POWER_REAL_CH3_100P														4000
#define CONFIG_DCHMI_DISKBUF_SIZE											256//显示缓冲区大小
/*****************************************************************************/

#endif


