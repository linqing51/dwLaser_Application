#ifndef __APPCONFIG_H__
#define __APPCONFIG_H__
#ifdef __cplusplus
extern "C" {
#endif
//通用配置信息
/*****************************************************************************/
#define CONFIG_CUSTIOM_SIZE														32//自定义方案数
#define CONFIG_HMI_SCHEME_NUM													32//每页分类方案数
#define CONFIG_SCHEME_NAME_SIZE												((EM_LASER_CHANNEL_SELECT - EM_LASER_SCHEME_NAME -1) * 2)//
#define CONFIG_DCHMI_DISKBUF_SIZE											256//显示缓冲区大小
#define CONFIG_USING_DEFAULT_SCHEME										1//是能预设模式
#define CONFIG_MAX_SCHEME_NAME_SIZE										40//方案名称长度
/*****************************************************************************/
#define CONFIG_MORSECODE_SPACE_TIME										3000//莫尔斯电码空时间
#define CONFIG_MORSECODE_LONG_TIME										900//莫尔斯电码长时间
#define CONFIG_MORSECODE_SHORT_TIME										300//莫尔斯电码短时间
/*****************************************************************************/
#define CONFIG_GDDC_UART_BAUDRATE											115200//LCD通信波特率
/*****************************************************************************/
//定义逻辑激光通道使能编码
#define LASER_CHANNEL_CH0															(1 << 0)//1470/1940/450
#define LASER_CHANNEL_CH1															(1 << 1)//980/       
#define LASER_CHANNEL_CH2															(1 << 2)//           
#define LASER_CHANNEL_CH3															(1 << 3)//          
#define LASER_CHANNEL_CH4															(1 << 4)//          
#define LASER_CHANNEL_CH5															(1 << 5)
#define LASER_CHANNEL_CH6															(1 << 6)
#define LASER_CHANNEL_CH7															(1 << 7)
#define LASER_CHANNEL_RAIM														(1 << 8)//红激光指示光
#define LASER_CHANNEL_GAIM														(1 << 9)//绿激光指示光
/*****************************************************************************/
//定义物理激光DAC通道编码
#define LASER_DAC_CHANNEL_CH0													(1 << 0)
#define LASER_DAC_CHANNEL_CH1													(1 << 1)
#define LASER_DAC_CHANNEL_CH2													(1 << 2)
#define LASER_DAC_CHANNEL_CH3													(1 << 3)
#define LASER_DAC_CHANNEL_CH4													(1 << 4)
#define LASER_DAC_CHANNEL_CH5													(1 << 5)
#define LASER_DAC_CHANNEL_CH6													(1 << 6)
#define LASER_DAC_CHANNEL_CH7													(1 << 7)
/*****************************************************************************/
//预设方案编码
#define SCHEME_PHLEBOLOGY															0x0001
#define SCHEME_PROCTOLOGY															0x0002
#define SCHEME_GYNECOLOGY															0x0003
#define SCHEME_ENT																		0x0004
#define SCHEME_NEUROSURGERY														0x0005
#define SCHEME_DERMATOLOGY														0x0006
#define SCHEME_LIPOSUCTION														0x0007
#define SCHEME_DENTISTRY															0x0008
#define SCHMEM_THERAPY																0x0009
#define SCHEME_ENDOLIFT																0x000A
#define SCHEME_CUSTIOM																0x0000
/*****************************************************************************/
//BOOTLOAD配置
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
//配置密码
#define CONFIG_HMI_ADMIN_PASSWORD0										0x3532//管理员密码
#define CONFIG_HMI_ADMIN_PASSWORD1										0x3038//管理员密码
#define CONFIG_HMI_ADMIN_PASSWORD2										0x3030//管理员密码
#define CONFIG_HMI_ADMIN_PASSWORD3										0x3030//管理员密码
#define CONFIG_HMI_DEFAULT_PASSWORD0									0x3030//默认密码
#define CONFIG_HMI_DEFAULT_PASSWORD1									0x3030//默认密码
#define CONFIG_HMI_DEFAULT_PASSWORD2									0x3030//默认密码
#define CONFIG_HMI_DEFAULT_PASSWORD3									0x3030//默认密码
/*****************************************************************************/
//版本配置
#define SW_VERSION																		"4.0a1b1"

#if defined(LDR2P1_G5_A1_20250731_DUAL)
#define HW_VERSION																		"LDR2P1G5A1_20250731_DUAL"
#endif
#if defined(LDR2P1_G5_A1_20250910_DUAL)
#if !defined(LDR2P1_G5_A1_20251108_DUAL)
#define HW_VERSION																		"LDR2P1G5A1_20250910_DUAL"
#endif
#endif
#if defined(LDR2P1_G5_A1_20251108_DUAL)
#define HW_VERSION																		"LDR2P1G5A1_20251108_DUAL"
#endif
#if defined(LDR2P1_G5_A1_20250731_TRIP)
#define HW_VERSION																		"LDR2P1G5A1_20250731_TRIP"
#endif
#if defined(LDR2P1_G5_A1_20250910_TRIP)
#define HW_VERSION																		"LDR2P1G5A1_20250910_TRIP"
#endif
#if defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
#define HW_VERSION																		"LDR2P1G9A1_20260322_DUAL"
#endif
#if defined(LYPE_MCU_1V0_20260106)
#define HW_VERSION																		"LYPE_MCU_1V0_20260106"
#endif
/*****************************************************************************/
//定义电源管理
#if defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP) ||\
    defined(LDR2P1_G5_A1_20250731_TRIP)
		//STM32作为PMU
#define CONFIG_PMU_STM32					
#elif defined(LYPE_MCU_1V0_20260106) ||\
			defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
	//LTC2955作为PMU
#define CONFIG_PMU_LTC2955
#else
	//无PMU 硬开关
#define CONFIG_PMU_NULL
#endif
/*****************************************************************************/
//波长配置
#if defined(MODEL_PVGLS_7W_1940_A0) || defined(MODEL_PVGLS_10W_1940_A1)
#define APP_CONFIG_WAVE_1940_650//APP为双波长 1940+650
#define GDDC_PAGE_STANDBY 														GDDC_PAGE_STANDBY_DUAL
#endif
#if defined(MODEL_PVGLS_15W_1470_A0) ||\
		defined(MODEL_PVGLS_15W_1470_A1) ||\
		defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
#define APP_CONFIG_WAVE_1470_650//APP为双波长 1470+650
#define GDDC_PAGE_STANDBY 														GDDC_PAGE_STANDBY_DUAL
#endif

#if defined(MODEL_PVGLS_TRI_A0) ||\
		defined(MODEL_PVGLS_TRI_COMBINE_A0) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP)
#define APP_CONFIG_WAVE_1470_980_650//APP为三波长 1470+650
#define GDDC_PAGE_STANDBY 														GDDC_PAGE_STANDBY_TRI
#endif

#if defined(LYPE_MCU_1V0_20260106)
#define APP_CONFIG_WAVE_450_980//APP为双波长 450+980
#define GDDC_PAGE_STANDBY 														GDDC_PAGE_STANDBY_DUAL
#endif
/*****************************************************************************/
//配置激光器型号
#if defined(MODEL_PVGLS_15W_1470_A0) ||\
		defined(MODEL_PVGLS_15W_1470_A1) ||\
		defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL)
#define MODLE_M1470_640_10_15_02_D200_22_G5W_PK//1470+650 V1
#endif

#if defined(MODEL_PVGLS_TRI_A0) || defined(MODEL_PVGLS_TRI_COMBINE_A0)
#define MODLE_M1470_980_640_10_15_35_05_D200_22_G5W_PK//1470+980+650 V1
#endif 

#if defined(LDR2P1_G5_A1_20250731_TRIP)
#define MODLE_M1470_980_640_10_15_35_05_D200_22_G5W_PK//1470+980+650 V1
//#define MODLE_M1470_980_640_10_15_15_02_D200_22_G5W_PK//1470+980+650 V2
#endif

#if defined(LDR2P1_G5_A1_20250910_TRIP)
#define MODLE_M1470_980_640_10_18_35_05_D200_22_G5W_PK
#endif

#if defined(MODEL_PVGLS_10W_1940_A1)
#define MODLE_M12_1920_10_400S//吉光1940
#endif

#if defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
#define MODLE_M1470_640_10_30_05_D200_22_G9_PK//1470+650 30W 
#endif

#if defined(LYPE_MCU_1V0_20260106)
#define MODLE_M450_980_200_60_D275_22_VI1_GP//大族450-200W 980-60W
#endif
/*****************************************************************************/
//配置无线脚踏USB接口
#if defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP) ||\
		defined(LYPE_MCU_1V0_20260106) ||\
		defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
#define APP_CONFIG_WFSW_PORT													hUsbHostFS
#define CONFIG_FSWITCH_USB_VID												0x16C0
#define CONFIG_FSWITCH_USB_PID												0x05E2
#endif

/*****************************************************************************/
//定义分类方案个数
#define CONFIG_PHLEBOLOGY_SIZE												3
#define CONFIG_PROCTOLOGY_SIZE												6
#define CONFIG_GYNECOLOGY_SIZE												23
#define CONFIG_ENT_SIZE																16
#define CONFIG_ENDOLIFT_SIZE													11
#if defined(MODEL_PVGLS_TRI_A0) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP) ||\
		defined (LDR2P1_G5_A1_20250910_TRIP) ||\
		defined(LYPE_MCU_1V0_20260106)
#define CONFIG_NEUROSURGERY_SIZE											5
#endif

#if defined(MODEL_PVGLS_15W_1470_A0) ||\
		defined(MODEL_PVGLS_15W_1470_A1) ||\
		defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
#define CONFIG_NEUROSURGERY_SIZE											3
#endif

#define CONFIG_DERMATOLOGY_SIZE												9
#define CONFIG_LIPOSUCTION_SIZE												7
#define CONFIG_DENTISRTY_SIZE													23

#if defined(MODEL_PVGLS_TRI_A0) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP) ||\
		defined(LYPE_MCU_1V0_20260106)
#define CONFIG_THERAPY_SIZE														8
#endif

#if defined(MODEL_PVGLS_15W_1470_A0) ||\
		defined(MODEL_PVGLS_15W_1470_A1) ||\
		defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
#define CONFIG_THERAPY_SIZE														3
#endif

//配置蜂鸣器		
#define CONFIG_MAX_SPK_FREQ														4500L//喇叭最高频率
#define CONFIG_MIN_SPL_FREQ														500//喇叭最低频率
#define CONFIG_DEFAULT_SPK_FREQ												1100//蜂鸣器默认频率
#define CONFIG_ACOUSITC_SPK_FREQ											1400//蜂鸣器变声频率
/*****************************************************************************/
#define CONFIG_WAIT_HMI_DELAY_TIME										20
#define CONFIG_WAIT_PASSWORD_DELAY_TIME								90
#define CONFIG_KEY_REPEAT_DELAY_TIME									80
#define CONFIG_STANDBY_BEEM_DELAY_TIME								20
#define CONFIG_WFSWITCH_DISCONNECT_DELAY_TIME					10//无线脚踏掉线超时 10mS * 100
/*****************************************************************************/
//配置环境信息
#if defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP) ||\
		defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
    
#define CONFIG_USING_CLASSIC_PID												1
#define CONFIG_USING_FUZZY_PID													0
#define CONFIG_USING_SMART_PID													0

#define CONFIG_LASER_A_DIODE_SET_TEMP									280//激光器温度设定
#define CONFIG_LASER_B_DIODE_SET_TEMP									280//激光器温度设定

#define CONFIG_LASER_A_DIODE_TEMP_HIGH								400//激光器高温极限 46.0C
#define CONFIG_LASER_A_DIODE_TEMP_LOW									-100//激光器低温极限 -25.0C
#define CONFIG_LASER_A_COUPLER_TEMP_HIGH							600//耦合器高温报警
#define CONFIG_LASER_A_COUPLER_TEMP_LOW								0//耦合器低温报警
#define CONFIG_LASER_A_CRYST0_TEMP_HIGH								0
#define CONFIG_LASER_A_CRYST0_TEMP_LOW								0
#define CONFIG_LASER_A_CRYST1_TEMP_HIGH								0
#define CONFIG_LASER_A_CRYST1_TEMP_LOW								0

#define CONFIG_LASER_B_DIODE_TEMP_HIGH								450//激光器高温极限 46.0C
#define CONFIG_LASER_B_DIODE_TEMP_LOW									0//激光器低温极限 -25.0C
#define CONFIG_LASER_B_COUPLER_TEMP_HIGH							600//耦合器高温报警
#define CONFIG_LASER_B_COUPLER_TEMP_LOW								0//耦合器低温报警
#define CONFIG_LASER_B_CRYST0_TEMP_HIGH								0
#define CONFIG_LASER_B_CRYST0_TEMP_LOW								0
#define CONFIG_LASER_B_CRYST1_TEMP_HIGH								0
#define CONFIG_LASER_B_CRYST1_TEMP_LOW								0

#define CONFIG_HT0_TEMP_HIGH													750//散热器0高温报警
#define CONFIG_HT1_TEMP_HIGH													600//散热器1高温报警
#define CONFIG_HT2_TEMP_HIGH													600//散热器2高温报警
#define CONFIG_HT3_TEMP_HIGH													600//散热器3高温报警

#define CONFIG_HWATER_TEMP_HIGH												2000//热水端高温报警温度
#define CONFIG_HWATER_TEMP_LOW												-2000//热水端低温报警温度
#define CONFIG_CWATER_TEMP_HIGH												2000//冷水端高温报警温度
#define CONFIG_CWATER_TEMP_LOW												-2000//冷水管低温报警温度
#define CONFIG_AMBIENT0_TEMP_HIGH											2000//环境0高温报警
#define CONFIG_AMBIENT0_TEMP_LOW											-2000//环境0低温报警
#define CONFIG_AMBIENT1_TEMP_HIGH											2000//环境1高温报警
#define CONFIG_AMBIENT1_TEMP_LOW											-2000//环境1低温报警
#define CONFIG_AMBIENT2_TEMP_HIGH											2000//环境2高温报警
#define CONFIG_AMBIENT2_TEMP_LOW											-2000//环境2低温报警
#define CONFIG_AMBIENT3_TEMP_HIGH											2000//环境3高温报警
#define CONFIG_AMBIENT3_TEMP_LOW											-2000//环境3低温报警

#define CONFIG_HDC1080_TEMP_HIGH											650//板载环境高温报警
#define CONFIG_HDC1080_TEMP_LOW												0//板载环境低温报警
#define CONFIG_HDC1080_HUMIDITY_HIGH									850//板载环境高湿度报警
#define CONFIG_HDC1080_HUMIDITY_LOW										0//板载环境低温报警
#define CONFIG_DHT11_TEMP_HIGH												500//远程环境高温报警		
#define CONFIG_DHT11_TEMP_LOW													0//远程环境低温报警
#define CONFIG_DHT11_HUMIDITY_HIGH										850//远程高湿度报警标志
#define CONFIG_DHT11_HUMIDITY_LOW											0//远程低湿度报警标志
#define CONFIG_MCU_TEMP_HIGH													650//处理器高温标志
#define CONFIG_MCU_TEMP_LOW														-200//处理器低温标志
#define CONFIG_MBAT_TEMP_HIGH													550//主电池高温标志
#define CONFIG_MBAT_TEMP_LOW													-100//主电池低温标志

#define CONFIG_FAN_CURVE_POINTS 											10//定义温度-转速曲线
#endif

#if defined(LYPE_MCU_1V0_20260106)

#define CONFIG_USING_CLASSIC_PID												1
#define CONFIG_USING_FUZZY_PID													0
#define CONFIG_USING_SMART_PID													0

#define CONFIG_LASER_A_DIODE_SET_TEMP									250//激光器温度设定
#define CONFIG_LASER_B_DIODE_SET_TEMP									250//激光器温度设定

#define CONFIG_LASER_A_DIODE_TEMP_HIGH								2000//激光器高温极限 46.0C
#define CONFIG_LASER_A_DIODE_TEMP_LOW									-1000//激光器低温极限 -25.0C
#define CONFIG_LASER_A_COUPLER_TEMP_HIGH							2000//耦合器高温报警
#define CONFIG_LASER_A_COUPLER_TEMP_LOW								-1000//耦合器低温报警
#define CONFIG_LASER_A_CRYST0_TEMP_HIGH								1000
#define CONFIG_LASER_A_CRYST0_TEMP_LOW								-1000
#define CONFIG_LASER_A_CRYST1_TEMP_HIGH								1000
#define CONFIG_LASER_A_CRYST1_TEMP_LOW								-1000

#define CONFIG_LASER_B_DIODE_TEMP_HIGH								1000//
#define CONFIG_LASER_B_DIODE_TEMP_LOW									-1000//
#define CONFIG_LASER_B_COUPLER_TEMP_HIGH							1000//
#define CONFIG_LASER_B_COUPLER_TEMP_LOW								-1000//
#define CONFIG_LASER_B_CRYST0_TEMP_HIGH								1000
#define CONFIG_LASER_B_CRYST0_TEMP_LOW								-1000
#define CONFIG_LASER_B_CRYST1_TEMP_HIGH								1000
#define CONFIG_LASER_B_CRYST1_TEMP_LOW								-1000

#define CONFIG_HT0_TEMP_HIGH													600//散热器0高温报警
#define CONFIG_HT1_TEMP_HIGH													600//散热器1高温报警
#define CONFIG_HT2_TEMP_HIGH													600//散热器2高温报警
#define CONFIG_HT3_TEMP_HIGH													600//散热器3高温报警

#define CONFIG_HWATER_TEMP_HIGH												2000//热水端高温报警温度
#define CONFIG_HWATER_TEMP_LOW												-2000//热水端低温报警温度
#define CONFIG_CWATER_TEMP_HIGH												2000//冷水端高温报警温度
#define CONFIG_CWATER_TEMP_LOW												-2000//冷水管低温报警温度
#define CONFIG_AMBIENT0_TEMP_HIGH											2000//环境0高温报警
#define CONFIG_AMBIENT0_TEMP_LOW											-2000//环境0低温报警
#define CONFIG_AMBIENT1_TEMP_HIGH											2000//环境1高温报警
#define CONFIG_AMBIENT1_TEMP_LOW											-2000//环境1低温报警
#define CONFIG_AMBIENT2_TEMP_HIGH											2000//环境2高温报警
#define CONFIG_AMBIENT2_TEMP_LOW											-2000//环境2低温报警
#define CONFIG_AMBIENT3_TEMP_HIGH											2000//环境3高温报警
#define CONFIG_AMBIENT3_TEMP_LOW											-2000//环境3低温报警

#define CONFIG_HDC1080_TEMP_HIGH											650//板载环境高温报警
#define CONFIG_HDC1080_TEMP_LOW												0//板载环境低温报警
#define CONFIG_HDC1080_HUMIDITY_HIGH									850//板载环境高湿度报警
#define CONFIG_HDC1080_HUMIDITY_LOW										0//板载环境低温报警
#define CONFIG_DHT11_TEMP_HIGH												500//远程环境高温报警		
#define CONFIG_DHT11_TEMP_LOW													0//远程环境低温报警
#define CONFIG_DHT11_HUMIDITY_HIGH										850//远程高湿度报警标志
#define CONFIG_DHT11_HUMIDITY_LOW											0//远程低湿度报警标志
#define CONFIG_MCU_TEMP_HIGH													650//处理器高温标志
#define CONFIG_MCU_TEMP_LOW														50//处理器低温标志
#define CONFIG_MBAT_TEMP_HIGH													550//主电池高温标志
#define CONFIG_MBAT_TEMP_LOW													-100//主电池低温标志

#define CONFIG_FAN_CURVE_POINTS 											10//定义温度-转速曲线
#endif
/*****************************************************************************/
//配置激光参数
#if defined(LDR2P1_G5_A1_20250731_DUAL) || defined(LDR2P1_G5_A1_20250731_TRIP)
#define CONFIG_MAX_LASER_POWER_CH0										150//通道1470最大激光功率
#define CONFIG_MAX_LASER_POWER_CH1										150//通道980最大激光功率
#define CONFIG_MIN_LASER_POWER_CH0										1//通道1470最小激光功率		
#define CONFIG_MIN_LASER_POWER_CH1										1//通道980最小激光功率		
#define CONFIG_MAX_LASER_DAC_CH0											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH1											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH2											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH3											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH4											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH5											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH6											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH7											0xFFF//

#define CONFIG_MAX_LASER_POWER_RED                    5//红激光最大功率 5档
#define CONFIG_MAX_LASER_POWER_AIM                    10//指示激光最大功率 10档

#define CONFIG_MIN_LASER_POWER_RED                    1//红激光最小功率
#define CONFIG_MIN_LASER_POWER_AIM                    0//指示激光最小功率

#define CONFIG_LASER_AIM_OFFSET												100
#define CONFIG_LASER_AIM_DEFAULT_GAIN									60

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
#endif

#if defined (LDR2P1_G5_A1_20250910_DUAL) || defined(LDR2P1_G5_A1_20250910_TRIP)
#define CONFIG_LOGIC_MAX_LASER_POWER_CH0							150//逻辑通道1470最大激光功率
#define CONFIG_LOGIC_MAX_LASER_POWER_CH1							300//逻辑通道980最大激光功率
#define CONFIG_LOGIC_MAX_LASER_POWER_CH2							1//逻辑通道2最大激光功率
#define CONFIG_LOGIC_MAX_LASER_POWER_CH3							1//逻辑通道3最大激光功率
#define CONFIG_LOGIC_MAX_LASER_POWER_CH4							1//逻辑通道4最大激光功率
#define CONFIG_LOGIC_MAX_LASER_POWER_CH5							1//逻辑通道5最大激光功率
#define CONFIG_LOGIC_MAX_LASER_POWER_CH6							1//逻辑通道6最大激光功率
#define CONFIG_LOGIC_MAX_LASER_POWER_CH7							1//逻辑通道7最大激光功率


#define CONFIG_LOGIC_MIN_LASER_POWER_CH0							1//逻辑通道1470最小激光功率		
#define CONFIG_LOGIC_MIN_LASER_POWER_CH1							1//逻辑通道980最小激光功率		
#define CONFIG_LOGIC_MIN_LASER_POWER_CH2							0//逻辑通道2最小激光功率
#define CONFIG_LOGIC_MIN_LASER_POWER_CH3							0//逻辑通道3最小激光功率
#define CONFIG_LOGIC_MIN_LASER_POWER_CH4							0//逻辑通道4最小激光功率
#define CONFIG_LOGIC_MIN_LASER_POWER_CH5							0//逻辑通道5最小激光功率
#define CONFIG_LOGIC_MIN_LASER_POWER_CH6							0//逻辑通道6最小激光功率
#define CONFIG_LOGIC_MIN_LASER_POWER_CH7							0//逻辑通道7最小激光功率

#define CONFIG_HARDWARE_MAX_LASER_POWER_CH0						150//硬件通道0最大激光功率
#define CONFIG_HARDWARE_MAX_LASER_POWER_CH1						300//硬件通道1最大激光功率
#define CONFIG_HARDWARE_MAX_LASER_POWER_CH2						1//硬件通道2最大激光功率
#define CONFIG_HARDWARE_MAX_LASER_POWER_CH3						1//硬件通道3最大激光功率
#define CONFIG_HARDWARE_MAX_LASER_POWER_CH4						1//硬件通道4最大激光功率
#define CONFIG_HARDWARE_MAX_LASER_POWER_CH5						1//硬件通道5最大激光功率
#define CONFIG_HARDWARE_MAX_LASER_POWER_CH6						1//硬件通道6最大激光功率
#define CONFIG_HARDWARE_MAX_LASER_POWER_CH7						1//硬件通道7最大激光功率

#define CONFIG_HARDWARE_MIN_LASER_POWER_CH0						1//硬件通道0最小激光功率
#define CONFIG_HARDWARE_MIN_LASER_POWER_CH1						1//硬件通道1最小激光功率
#define CONFIG_HARDWARE_MIN_LASER_POWER_CH2						1//硬件通道2最小激光功率
#define CONFIG_HARDWARE_MIN_LASER_POWER_CH3						1//硬件通道3最小激光功率
#define CONFIG_HARDWARE_MIN_LASER_POWER_CH4						1//硬件通道4最小激光功率
#define CONFIG_HARDWARE_MIN_LASER_POWER_CH5						1//硬件通道5最小激光功率
#define CONFIG_HARDWARE_MIN_LASER_POWER_CH6						1//硬件通道6最小激光功率
#define CONFIG_HARDWARE_MIN_LASER_POWER_CH7						1//硬件通道7最小激光功率

#define CONFIG_MAX_LASER_POWER_RED                    5//红激光最大功率 5档
#define CONFIG_MAX_LASER_POWER_RAIM                   10//红指示激光最大功率 10档
#define CONFIG_MAX_LASER_POWER_GAIM										0//绿指示激光最大功率档

#define CONFIG_MIN_LASER_POWER_RED                    1//红激光最小功率
#define CONFIG_MIN_LASER_POWER_RAIM                   0//指示激光最小功率
#define CONFIG_MIN_LASER_POWER_GAIM                   0//指示激光最小功率

#define CONFIG_LASER_RAIM_OFFSET											100
#define CONFIG_LASER_GAIM_OFFSET											100
#define CONFIG_LASER_RAIM_DEFAULT_GAIN								60
#define CONFIG_LASER_GAIM_DEFAULT_GAIN								60

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
#endif

#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
#define CONFIG_MAX_LASER_POWER_CH0										150//通道1470最大激光功率
#define CONFIG_MAX_LASER_POWER_CH1										150//通道980最大激光功率
#define CONFIG_MIN_LASER_POWER_CH0										1//通道1470最小激光功率		
#define CONFIG_MIN_LASER_POWER_CH1										1//通道980最小激光功率								
#define CONFIG_MAX_LASER_DAC_CH0											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH1											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH2											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH3											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH4											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH5											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH6											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH7											0xFFF//

#define CONFIG_MAX_LASER_POWER_RED                    5//红激光最大功率 5档
#define CONFIG_MAX_LASER_POWER_AIM                    10//指示激光最大功率 10档

#define CONFIG_MIN_LASER_POWER_RED                    1//红激光最小功率
#define CONFIG_MIN_LASER_POWER_AIM                    0//指示激光最小功率

#define CONFIG_LASER_RAIM_OFFSET											100
#define CONFIG_LASER_GAIM_OFFSET											100
#define CONFIG_LASER_RAIM_DEFAULT_GAIN								60
#define CONFIG_LASER_GAIM_DEFAULT_GAIN								60

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
#endif

#if defined(MODEL_PVGLS_10W_1940_A1)
#define CONFIG_MAX_LASER_POWER_CH0										100//通道1940最大激光功率
#define CONFIG_MAX_LASER_POWER_CH1										150//通道980最大激光功率
#define CONFIG_MIN_LASER_POWER_CH0										1//通道1940最小激光功率
#define CONFIG_MIN_LASER_POWER_CH1										1//通道980最小激光功率
#define CONFIG_MAX_LASER_DAC_CH0											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH1											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH2											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH3											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH4											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH5											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH6											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH7											0xFFF//

#define CONFIG_MAX_LASER_POWER_RED                    5//红激光最大功率 5档
#define CONFIG_MAX_LASER_POWER_RAIM                   10//指示激光最大功率 10档
#define CONFIG_MAX_LASER_POWER_GAIM                   10//指示激光最大功率 10档

#define CONFIG_MIN_LASER_POWER_RED                    1//红激光最小功率
#define CONFIG_MIN_LASER_POWER_RAIM                   0//指示激光最小功率
#define CONFIG_MIN_LASER_POWER_GAIM                   0//指示激光最小功率

#define CONFIG_LASER_RAIM_OFFSET											100
#define CONFIG_LASER_GAIM_OFFSET											100
#define CONFIG_LASER_RAIM_DEFAULT_GAIN								60
#define CONFIG_LASER_GAIM_DEFAULT_GAIN								60

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
#endif

#if defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
#define CONFIG_LOGIC_MAX_LASER_POWER_CH0							300//逻辑通道1470最大激光功率
#define CONFIG_LOGIC_MAX_LASER_POWER_CH1							1//逻辑通道980最大激光功率
#define CONFIG_LOGIC_MAX_LASER_POWER_CH2							1//逻辑通道2最大激光功率
#define CONFIG_LOGIC_MAX_LASER_POWER_CH3							1//逻辑通道3最大激光功率
#define CONFIG_LOGIC_MAX_LASER_POWER_CH4							1//逻辑通道4最大激光功率
#define CONFIG_LOGIC_MAX_LASER_POWER_CH5							1//逻辑通道5最大激光功率
#define CONFIG_LOGIC_MAX_LASER_POWER_CH6							1//逻辑通道6最大激光功率
#define CONFIG_LOGIC_MAX_LASER_POWER_CH7							1//逻辑通道7最大激光功率


#define CONFIG_LOGIC_MIN_LASER_POWER_CH0							1//逻辑通道1470最小激光功率		
#define CONFIG_LOGIC_MIN_LASER_POWER_CH1							1//逻辑通道980最小激光功率		
#define CONFIG_LOGIC_MIN_LASER_POWER_CH2							0//逻辑通道2最小激光功率
#define CONFIG_LOGIC_MIN_LASER_POWER_CH3							0//逻辑通道3最小激光功率
#define CONFIG_LOGIC_MIN_LASER_POWER_CH4							0//逻辑通道4最小激光功率
#define CONFIG_LOGIC_MIN_LASER_POWER_CH5							0//逻辑通道5最小激光功率
#define CONFIG_LOGIC_MIN_LASER_POWER_CH6							0//逻辑通道6最小激光功率
#define CONFIG_LOGIC_MIN_LASER_POWER_CH7							0//逻辑通道7最小激光功率

#define CONFIG_HARDWARE_MAX_LASER_POWER_CH0						150//硬件通道0最大激光功率
#define CONFIG_HARDWARE_MAX_LASER_POWER_CH1						150//硬件通道1最大激光功率
#define CONFIG_HARDWARE_MAX_LASER_POWER_CH2						1//硬件通道2最大激光功率
#define CONFIG_HARDWARE_MAX_LASER_POWER_CH3						1//硬件通道3最大激光功率
#define CONFIG_HARDWARE_MAX_LASER_POWER_CH4						1//硬件通道4最大激光功率
#define CONFIG_HARDWARE_MAX_LASER_POWER_CH5						1//硬件通道5最大激光功率
#define CONFIG_HARDWARE_MAX_LASER_POWER_CH6						1//硬件通道6最大激光功率
#define CONFIG_HARDWARE_MAX_LASER_POWER_CH7						1//硬件通道7最大激光功率

#define CONFIG_HARDWARE_MIN_LASER_POWER_CH0						1//硬件通道0最小激光功率
#define CONFIG_HARDWARE_MIN_LASER_POWER_CH1						1//硬件通道1最小激光功率
#define CONFIG_HARDWARE_MIN_LASER_POWER_CH2						1//硬件通道2最小激光功率
#define CONFIG_HARDWARE_MIN_LASER_POWER_CH3						1//硬件通道3最小激光功率
#define CONFIG_HARDWARE_MIN_LASER_POWER_CH4						1//硬件通道4最小激光功率
#define CONFIG_HARDWARE_MIN_LASER_POWER_CH5						1//硬件通道5最小激光功率
#define CONFIG_HARDWARE_MIN_LASER_POWER_CH6						1//硬件通道6最小激光功率
#define CONFIG_HARDWARE_MIN_LASER_POWER_CH7						1//硬件通道7最小激光功率

#define CONFIG_MAX_LASER_POWER_RED                    5//红激光最大功率 5档
#define CONFIG_MAX_LASER_POWER_RAIM                   10//红指示激光最大功率 10档
#define CONFIG_MAX_LASER_POWER_GAIM										0//绿指示激光最大功率档

#define CONFIG_MIN_LASER_POWER_RED                    1//红激光最小功率
#define CONFIG_MIN_LASER_POWER_RAIM                   0//指示激光最小功率
#define CONFIG_MIN_LASER_POWER_GAIM                   0//指示激光最小功率

#define CONFIG_LASER_RAIM_OFFSET											100
#define CONFIG_LASER_GAIM_OFFSET											100
#define CONFIG_LASER_RAIM_DEFAULT_GAIN								60
#define CONFIG_LASER_GAIM_DEFAULT_GAIN								60

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
#define CONFIG_STEP_LASER_ENERGY_INTERVAL							109
#define CONFIG_BEEM_ENERGY_INTERVAL_TIME							1000//变音持续时间
#endif

#if defined(LYPE_MCU_1V0_20260106)
//定义逻辑通道
#define CONFIG_LOGIC_MAX_LASER_POWER_CH0										2000//通道0-450最大激光功率
#define CONFIG_LOGIC_MAX_LASER_POWER_CH1										500//通道1-450最大激光功率
#define CONFIG_LOGIC_MAX_LASER_POWER_CH2										0//通道2-450最大激光功率
#define CONFIG_LOGIC_MAX_LASER_POWER_CH3										0//通道3-450最大激光功率
#define CONFIG_LOGIC_MAX_LASER_POWER_CH4										0//通道4-980最大激光功率
#define CONFIG_LOGIC_MAX_LASER_POWER_CH5										0//通道5最大激光功率
#define CONFIG_LOGIC_MAX_LASER_POWER_CH6										0//通道6最大激光功率
#define CONFIG_LOGIC_MAX_LASER_POWER_CH7										0//通道7最大激光功率
#define CONFIG_LOGIC_MIN_LASER_POWER_CH0										1//通道0-450最小激光功率
#define CONFIG_LOGIC_MIN_LASER_POWER_CH1										1//通道1-450最小激光功率
#define CONFIG_LOGIC_MIN_LASER_POWER_CH2										0//通道2-450最小激光功率
#define CONFIG_LOGIC_MIN_LASER_POWER_CH3										0//通道3-450最小激光功率
#define CONFIG_LOGIC_MIN_LASER_POWER_CH4										0//通道4-980最小激光功率
#define CONFIG_LOGIC_MIN_LASER_POWER_CH5										0//通道5最小激光功率
#define CONFIG_LOGIC_MIN_LASER_POWER_CH6										0//通道6最小激光功率
#define CONFIG_LOGIC_MIN_LASER_POWER_CH7										0//通道7最小激光功率

//定义物理通道
#define CONFIG_HARDWARE_MAX_LASER_POWER_CH0									500//通道0-450最大激光功率
#define CONFIG_HARDWARE_MAX_LASER_POWER_CH1									500//通道1-450最大激光功率
#define CONFIG_HARDWARE_MAX_LASER_POWER_CH2									500//通道2-450最大激光功率
#define CONFIG_HARDWARE_MAX_LASER_POWER_CH3									500//通道3-450最大激光功率
#define CONFIG_HARDWARE_MAX_LASER_POWER_CH4									500//通道4-980最大激光功率->DAC4
#define CONFIG_HARDWARE_MAX_LASER_POWER_CH5									0//通道5最大激光功率
#define CONFIG_HARDWARE_MAX_LASER_POWER_CH6									0//通道6最大激光功率
#define CONFIG_HARDWARE_MAX_LASER_POWER_CH7									0//通道7最大激光功率
#define CONFIG_HARDWARE_MIN_LASER_POWER_CH0									1//通道0-450最小激光功率
#define CONFIG_HARDWARE_MIN_LASER_POWER_CH1									1//通道1-450最小激光功率
#define CONFIG_HARDWARE_MIN_LASER_POWER_CH2									0//通道2-450最小激光功率
#define CONFIG_HARDWARE_MIN_LASER_POWER_CH3									0//通道3-450最小激光功率
#define CONFIG_HARDWARE_MIN_LASER_POWER_CH4									0//通道4-980最小激光功率
#define CONFIG_HARDWARE_MIN_LASER_POWER_CH5									0//通道5最小激光功率
#define CONFIG_HARDWARE_MIN_LASER_POWER_CH6									0//通道6最小激光功率
#define CONFIG_HARDWARE_MIN_LASER_POWER_CH7									0//通道7最小激光功率


#define CONFIG_MAX_LASER_DAC_CH0											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH1											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH2											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH3											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH4											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH5											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH6											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH7											0xFFF//

#define CONFIG_MAX_LASER_POWER_RED                    5//红激光最大功率 5档
#define CONFIG_MAX_LASER_POWER_RAIM                   10//指示激光最大功率 10档
#define CONFIG_MAX_LASER_POWER_GAIM                   10//指示激光最大功率 10档

#define CONFIG_MIN_LASER_POWER_RED                    1//红激光最小功率
#define CONFIG_MIN_LASER_POWER_RAIM                   0//指示激光最小功率
#define CONFIG_MIN_LASER_POWER_GAIM                   0//指示激光最小功率

#define CONFIG_LASER_RAIM_OFFSET												100
#define CONFIG_LASER_GAIM_OFFSET												100
#define CONFIG_LASER_RAIM_DEFAULT_GAIN									60
#define CONFIG_LASER_GAIM_DEFAULT_GAIN									60

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
#endif

/*****************************************************************************/
//定义指示灯亮度
#if defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP) ||\
		defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
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
#if defined(LYPE_MCU_1V0_20260106)
#define CONFIG_BLUE_LED_MAX_DC												100
#define CONFIG_BLUE_LED_DEFAULT_DC										0
#define CONFIG_RED_LED_MAX_DC													100	
#define CONFIG_RED_LED_DEFAULT_DC											0
#define CONFIG_GREEN_LED_MAX_DC												100
#define CONFIG_GREEN_LED_DEFAULT_DC										0
#endif
/*****************************************************************************/
//定义蜂鸣器音量/频率
#if defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP) ||\
		defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
#define CONFIG_BEEM_MAX_VOLUME												100//蜂鸣器最大音量
#define CONFIG_BEEM_MAX_LIMIT													0.7F//
#define CONFIG_BEEM_MAX_FREQ													4500L//喇叭最高频率
#define CONFIG_BEEM_MIN_FREQ													500//喇叭最低频率
#endif

#if defined(LYPE_MCU_1V0_20260106)
#define CONFIG_BEEM_MAX_VOLUME												100//蜂鸣器最大音量
#define CONFIG_BEEM_MAX_LIMIT													0.7F//
#define CONFIG_BEEM_MAX_FREQ													4500L//喇叭最高频率
#define CONFIG_BEEM_MIN_FREQ													500//喇叭最低频率
#endif
/*****************************************************************************/
//定义屏幕亮度
#if defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP) ||\
		defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
#define CONFIG_LCD_MAX_DC															100//屏幕亮度最大值
#define CONFIG_LCD_MIN_DC															1//屏幕亮度最小值
#endif
#if defined(LYPE_MCU_1V0_20260106)
#define CONFIG_LCD_MAX_DC															100//屏幕亮度最大值
#define CONFIG_LCD_MIN_DC															1//屏幕亮度最小值
#endif
/*****************************************************************************/
//定义风扇转速
#if defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP) ||\
		defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
#define CONFIG_FAN_MAX_DC															100
#define CONFIG_FAN_MIN_DC															0
#endif

#if defined(LYPE_MCU_1V0_20260106)
#define CONFIG_FAN_MAX_DC															100
#define CONFIG_FAN_MIN_DC															0
#endif


#ifdef __cplusplus
}
#endif

#endif


