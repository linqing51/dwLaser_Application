#ifndef __SPLCCONFIG_H__
#define __SPLCCONFIG_H__
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
#ifdef MODEL_PVGLS_TRI_A0
#define CONFIG_NEUROSURGERY_SIZE											5
#endif

#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
#define CONFIG_NEUROSURGERY_SIZE											3
#endif

#define CONFIG_DERMATOLOGY_SIZE												9
#define CONFIG_LIPOSUCTION_SIZE												7
#define CONFIG_DENTISRTY_SIZE													23

#ifdef MODEL_PVGLS_TRI_A0
#define CONFIG_THERAPY_SIZE														8
#endif

#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
#define CONFIG_THERAPY_SIZE														3
#endif

#define CONFIG_CUSTIOM_SIZE														32
/*****************************************************************************/
#define CONFIG_MORSECODE_SPACE_TIME										3000
#define CONFIG_MORSECODE_LONG_TIME										900
#define CONFIG_MORSECODE_SHORT_TIME										300
/*****************************************************************************/
#define CONFIG_DEBUG_DAC															0//调试DAC驱动
#define CONFIG_DEBUB_ADC															0//调试ADC驱动
#define CONFIG_DEBUG_EPROM														0//调试EPROM驱动
#define CONFIG_DEBUG_IO																0//调试IO
#define CONFIG_DEBUG_SPK															0//调试蜂鸣器驱动
#define CONFIG_DEBUG_LED															0//调试指示灯驱动
#define CONFIG_DEBUG_AIM															0//调试指示光驱动
#define CONFIG_DEBUG_LASER														0//调试LASER驱动
#define CONFIG_DEBUG_SPLC															0//调试SPLC命令
#define CONFIG_DEBUG_WSW															0//调试无线脚踏
/*****************************************************************************/
#define CONFIG_GDDC_UART_BAUDRATE											230400//LCD通信波特率
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
#define CONFIG_SPLC_MAX_SPK_FREQ											4500L//喇叭最高频率
#define CONFIG_SPLC_MIN_SPL_FREQ											500//喇叭最低频率
#define CONFIG_SPLC_DEFAULT_SPK_FREQ									1100//蜂鸣器默认频率
#define CONFIG_SPLC_ACOUSITC_SPK_FREQ									1400//蜂鸣器变声频率
/*****************************************************************************/
#define CONFIG_INPUT_FILTER_TIME											8//输入数字滤波扫描周期 1mS * N
/*****************************************************************************/
#define CONFIG_SPLC_USING_SPWM												1//使了软件PWM功能
#define CONFIG_SPLC_FUNTEST														0//功能指令测试
/*****************************************************************************/
#define CONFIG_SPLC_ASSERT														1//检查地址范围
#define CONFIG_SPLC_CLEAR_CODE												0xA58E
#define CONFIG_SOFTPLC_TICK														200L//5mS
/*****************************************************************************/
#define CONFIG_SPLC_USING_EPROM_TEST									0//EPROM 读写测试
//EPROM自检
#define CONFIG_EPROM_SIZE 														CONFIG_AT24C64_SIZE
#define	CONFIG_AT24C64_SIZE														8192
#define	CONFIG_AT24C128_SIZE 													16384
#define	CONFIG_AT24C256_SIZE 													32768//32K*8
#define CONFIG_EPROM_WRITE_ADDR												0xA0//
#define CONFIG_EPROM_READ_ADDR												0xA1//
#define CONFIG_EPROM_TIMEOUT													1000//EPROM读写超时
#define CONFIG_EPROM_PAGE_SIZE												0x08//EPROM 页大小
#define CONFIG_EPROM_WRITE_DELAY											0//写入等待时间mS
/*****************************************************************************/
#define CONFIG_EPROM_MR_START													(0x0L)//
#define CONFIG_EPROM_MR_END														(CONFIG_EPROM_MR_START + MR_END - MR_START)
#define CONFIG_EPROM_DM_START													(CONFIG_EPROM_MR_END + 1)//NVRAM中DM在EPROM储存地址
#define CONFIG_EPROM_DM_END														(CONFIG_EPROM_DM_START + DM_END - DM_START)

#define CONFIG_EPROM_FD_SCHEME_SIZE										((FD_SCHEME_END_0 - FD_SCHEME_START_0 + 1) * 2)//单个方案占用的EPROM空间
#define CONFIG_EPROM_FD_START													(CONFIG_EPROM_DM_END + 1)
#define CONFIG_EPROM_FD_END														(CONFIG_EPROM_FD_START + FD_END - FD_START)

#define CONFIG_EPROM_MR_CRC														(7524L)//4B MR NVRAM CRC32 硬件计算
#define CONFIG_EPROM_DM_CRC														(7528L)//4B DM NVRAM CRC32 硬件计算
#define CONFIG_EPROM_FD_CRC														(7532L)//4B FD NVRAM CRC32 硬件计算
#define CONFIG_EPROM_MCU_FW_CRC												(7536L)//4B MCU固件CRC32值 软件计算
#define CONFIG_EPROM_LCD_FW_CRC												(7540L)//4B LCD固件CRC32值 软件计算
#define CONFIG_EPROM_CFG_CRC													(7544L)//4B deviceConfig CRC32值 硬件计算
#define CONFIG_EPROM_LOG_CRC													(7548L)//4B logInfo CRC32值 硬件计算

#define CONFIG_EPROM_CONFIG_START											(7552L)//512B 配置信息区
#define CONFIG_EPROM_CONFIG_END												(8063L)
#define CONFIG_EPROM_LOGINFO_START										(8064L)//128B 记录信息区 
#define CONFIG_EPROM_LOGINFO_END											(8191L)
/*****************************************************************************/
#define CONFIG_SPLC_USING_ADC													1//使能ADC模块
#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
#define CONFIG_SPLC_ADC_CHANNEL												6//ADC采集通道
#endif
#if defined(MODEL_PVGLS_10W_1940_A1)
#define CONFIG_SPLC_ADC_CHANNEL												10//ADC采集通道
#endif
#define CONFIG_SPLC_ADC_AVERAGE_NUM										8//ADC平均值次数
#define CONFIG_ADC_DMA_BUFFER_SIZE										(CONFIG_SPLC_ADC_CHANNEL * CONFIG_SPLC_ADC_AVERAGE_NUM)//ADC DMA采集缓冲
#define CONFIG_AMBIENT_TEMP             							25// Ambient temp in deg C
#define CONFIG_VREF_CAL                         			*(__IO uint16_t *)(0x1FFF7A2A)//校正电压源
#define CONFIG_ADC_AVG_SLOPE													2.5F
#define CONFIG_ADC_V25																760.0F//0.76V@25D
#define CONFIG_NTC_RS																	4700L//NTC分压电阻
#define CONFIG_NTC_B																	3477.0F
#define CONFIG_NTC_R25																10000.0F//25摄氏度时电阻
#define CONFIG_NTC_VREF																3300L//
#define CONFIG_FIBER_PD_THRESHOLD											200//光纤插入时ADC阈值
/*****************************************************************************/
#define CONFIG_SPLC_USING_LASER_TEST									0
/*****************************************************************************/
#define CONFIG_DCHMI_DISKBUF_SIZE											256//显示缓冲区大小
/*****************************************************************************/
#define CONFIG_WAIT_HMI_DELAY_TIME										10
#define CONFIG_WAIT_PASSWORD_DELAY_TIME								70
#define CONFIG_KEY_REPEAT_DELAY_TIME									80
#define CONFIG_STANDBY_BEEM_DELAY_TIME								20
#define CONFIG_WFSWITCH_DISCONNECT_DELAY_TIME					10//无线脚踏掉线超时 10mS * 100
/*****************************************************************************/
#define CONFIG_DIODE_SET_TEMP													250//
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
#define CONFIG_SCHEME_NAME_SIZE											((EM_LASER_CHANNEL_SELECT - EM_LASER_SCHEME_NAME -1) * 2)//
/*****************************************************************************/
#define CONFIG_MAX_LASER_DAC_CH0											0xFFF//
#define CONFIG_MAX_LASER_DAC_CH1											0xFFF//

#define CONFIG_MAX_LASER_POWER_RED                    5//红激光最大功率 5档
#define CONFIG_MAX_LASER_POWER_AIM                    10//指示激光最大功率 10档

#define CONFIG_MIN_LASER_POWER_RED                    1//红激光最小功率
#define CONFIG_MIN_LASER_POWER_AIM                    0//指示激光最小功率

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
#define CONFIG_BLUE_LED_DEFAULT_DC										50
#define CONFIG_RED_LED_MAX_DC													100	
#define CONFIG_RED_LED_DEFAULT_DC											50
#define CONFIG_GREEN_LED_MAX_DC												100
#define CONFIG_GREEN_LED_DEFAULT_DC										50
#endif
/*****************************************************************************/
#define CONFIG_AIM_DEFAULT_GAIN												30
//定义蜂鸣器音量/频率
#define CONFIG_BEEM_MAX_VOLUME													100//蜂鸣器最大音量
#define CONFIG_BEEM_MAX_LIMIT													0.7F//
#define CONFIG_BEEM_MAX_FREQ														4500L//喇叭最高频率
#define CONFIG_BEEM_MIN_FREQ														500//喇叭最低频率
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
/*****************************************************************************/
//线圈 保持 16 * 32 = 512 
#define MR_START																			0
#define MR_END   																			31
//数据寄存器 保持 512
#define DM_START																			32
#define DM_END																				543
//线圈寄存器 非保持 16 * 32 = 512
#define R_START																				544
#define R_END																					575						
//数据寄存器 非保持 512
#define EM_START																			576
#define EM_END																				1087
//延时线圈
//1MS  16 * 4 = 64
#define T_1MS_START																		1088
#define T_1MS_END																			1091
//10MS 16 * 4 = 64
#define T_10MS_START																	1092
#define T_10MS_END																		1095
//100MS 16 * 4 = 64
#define T_100MS_START																	1096
#define T_100MS_END																		1099
//延时器使能
//1MS  16 * 4 = 64
#define T_1MS_ENA_START																1100
#define T_1MS_ENA_END																	1103
//10MS 16 * 4 = 64
#define T_10MS_ENA_START															1104
#define T_10MS_ENA_END																1107
//100MS 16 * 4 = 64
#define T_100MS_ENA_START															1108
#define T_100MS_ENA_END																1111
//延时计时器
//1MS   64
#define TD_1MS_START																	1112
#define TD_1MS_END																		1175
//10MS  64
#define TD_10MS_START																	1176											
#define TD_10MS_END																		1239
//100MS 64
#define TD_100MS_START																1240
#define TD_100MS_END																	1303
//输入位寄存器 16 * 8 = 128
#define X_START																				1304
#define X_END																					1311
//输出位寄存器 16 * 8 = 128
#define Y_START																				1312
#define Y_END																					1319
//特殊寄存器 64
#define SPREG_START																		1320
#define SPREG_END																			1383
//特殊线圈 16 * 16 = 256
#define SPCOIL_START																	1384
#define SPCOIL_END																		1399
//临时寄存器 64
#define TMP_START																			1400
#define TMP_END																				1463
/*****************************************************************************/
#define CONFIG_NVRAM_SIZE 														(TMP_END + 1)
/*****************************************************************************/
//存档寄存器
#define FD_START																			0
#define FD_END																				2047
/*****************************************************************************/
#define CONFIG_MRRAM_SIZE															(MR_END - MR_START + 1)									
#define CONFIG_DMRAM_SIZE															(DM_END - DM_START + 1)
#define CONFIG_FDRAM_SIZE															(FD_END - FD_START + 1)
/*****************************************************************************/
#define SPCOIL_ON																			(SPCOIL_START * 16 + 0)//长通线圈
#define SPCOIL_START_UP																(SPCOIL_START * 16 + 1)//初次上电
#define SPCOIL_PS10MS																	(SPCOIL_START * 16 + 2)//10mS
#define SPCOIL_PS50MS																	(SPCOIL_START * 16 + 3)//50mS
#define SPCOIL_PS100MS																(SPCOIL_START * 16 + 4)//100mS
#define SPCOIL_PS200MS																(SPCOIL_START * 16 + 5)//200mS
#define SPCOIL_PS500MS																(SPCOIL_START * 16 + 6)//500mS
#define SPCOIL_PS1000MS																(SPCOIL_START * 16 + 7)//1000mS
#define SPCOIL_PS1MINS																(SPCOIL_START * 16 + 8)//1mins
/*****************************************************************************/
#define SPCOIL_LINK_SEND_BUSY													(SPCOIL_START * 16 + 16)//发送进行中
#define SPCOIL_LINK_SEND_DONE													(SPCOIL_START * 16 + 17)//发送完成
#define SPCOIL_LINK_SEND_ERR													(SPCOIL_START * 16 + 18)//发送错误
#define SPCOIL_LINK_RECE_BUSY													(SPCOIL_START * 16 + 19)//接收进行中
#define SPCOIL_LINK_RECE_DONE													(SPCOIL_START * 16 + 20)//接收完成
#define SPCOIL_LINK_RECE_ERR													(SPCOIL_START * 16 + 21)//发送错误
/*****************************************************************************/
#define SPCOIL_BEEM_ENABLE														(SPCOIL_START * 16 + 32)//蜂鸣器使能
#define SPCOIL_BEEM_BUSY															(SPCOIL_START * 16 + 33)//蜂鸣器工作状态
/*****************************************************************************/
#define SPCOIL_WFSWITCH_PLUG													(SPCOIL_START * 16 + 40)//无线脚踏插入					
#define SPCOIL_WFSWITCH_ON														(SPCOIL_START * 16 + 41)//无线脚踏按下
/*****************************************************************************/
#define SPCOIL_SPWM_OUT_0															(SPCOIL_START * 16 + 48)//SPWM0输出状态
#define SPCOIL_SPWM_RESET_0														(SPCOIL_START * 16 + 49)//SPWM0复位
#define SPCOIL_SPWM_OUT_1															(SPCOIL_START * 16 + 50)//SPWM1输出状态
#define SPCOIL_SPWM_RESET_1														(SPCOIL_START * 16 + 51)//SPWM1复位
#define SPCOIL_SPWM_OUT_2															(SPCOIL_START * 16 + 52)//SPWM2输出状态
#define SPCOIL_SPWM_RESET_2														(SPCOIL_START * 16 + 53)//SPWM2复位
#define SPCOIL_SPWM_OUT_3															(SPCOIL_START * 16 + 54)//SPWM3输出状态
#define SPCOIL_SPWM_RESET_3														(SPCOIL_START * 16 + 55)//SPWM3复位
/*****************************************************************************/
#define SPREG_ADC_0																		(SPREG_START + 11)//采集值 CH0 CURRENT
#define SPREG_ADC_1																		(SPREG_START + 12)//采集值 CH1 CURRENT
#define SPREG_ADC_2																		(SPREG_START + 13)//采集值 CH2 CURRENT
#define SPREG_ADC_3																		(SPREG_START + 14)//采集值 CH3 CURRENT
#define SPREG_ADC_4																		(SPREG_START + 15)//采集值 CH4 CURRENT
#define SPREG_ADC_5																		(SPREG_START + 16)//采集值 CH5 CURRENT
#define SPREG_ADC_6																		(SPREG_START + 17)//采集值 CH6 CURRENT
#define SPREG_ADC_7																		(SPREG_START + 18)//采集值 TEC CURRENT
#define SPREG_ADC_8																		(SPREG_START + 19)//采集值 BAT NTC
#define SPREG_ADC_9																		(SPREG_START + 20)//采集值 LASER_FBPD
#define SPREG_ADC_10																	(SPREG_START + 21)//采集值 LASER_LPD
#define SPREG_ADC_11																	(SPREG_START + 22)//采集值 LASER_NTC
#define SPREG_ADC_12																	(SPREG_START + 23)//采集值 HT_NTC
#define SPREG_ADC_13																	(SPREG_START + 24)//CHIP TEMP片内温度传感器
#define SPREG_ADC_14																	(SPREG_START + 25)//CHIP VREFINT片内基准源
#define SPREG_ADC_15																	(SPREG_START + 26)//VBAT 掉电存储电池 

#define SPREG_DAC_0																		(SPREG_START + 30)//DAC设定值 激光通道 CH0 ->1470 1940
#define SPREG_DAC_1																		(SPREG_START + 31)//DAC设定值 激光通道 CH1 ->980
#define SPREG_DAC_2																		(SPREG_START + 32)//DAC设定值 激光通道 CH2 
#define SPREG_DAC_3																		(SPREG_START + 33)//DAC设定值 激光通道 CH3
#define SPREG_DAC_4																		(SPREG_START + 34)//DAC设定值 激光通道 CH4
#define SPREG_DAC_5																		(SPREG_START + 35)//DAC设定值 激光通道 CH5
#define SPREG_DAC_6																		(SPREG_START + 36)//DAC设定值 激光通道 CH6 -> 635 PWM 占空比
#define SPREG_DAC_7																		(SPREG_START + 37)//DAC设定值 激光通道 CH7 ->TEC 
/*****************************************************************************/
#define SPREG_SPWM_POS_0															(SPREG_START + 40)//软件PWM0正脉宽设置
#define SPREG_SPWM_POS_SHADOW_0												(SPREG_START + 41)//软件PWM0正脉宽阴影
#define SPREG_SPWM_CYCLE_0														(SPREG_START + 42)//软件PWM0周期设置
#define SPREG_SPWM_CYCLE_SHADOW_0											(SPREG_START + 43)//软件PWM0周期阴影
#define SPREG_SPWM_COUNTER_0													(SPREG_START + 44)//软件PWM0计数器
#define SPREG_SPWM_POS_1															(SPREG_START + 45)//软件PWM1正脉宽设置
#define SPREG_SPWM_POS_SHADOW_1												(SPREG_START + 46)//软件PWM1正脉宽阴影
#define SPREG_SPWM_CYCLE_1														(SPREG_START + 47)//软件PWM1周期设置
#define SPREG_SPWM_CYCLE_SHADOW_1											(SPREG_START + 48)//软件PWM1周期阴影
#define SPREG_SPWM_COUNTER_1													(SPREG_START + 49)//软件PWM1计数器
#define SPREG_SPWM_POS_2															(SPREG_START + 50)//软件PWM2正脉宽设置
#define SPREG_SPWM_POS_SHADOW_2												(SPREG_START + 51)//软件PWM2正脉宽阴影
#define SPREG_SPWM_CYCLE_2														(SPREG_START + 52)//软件PWM2周期设置
#define SPREG_SPWM_CYCLE_SHADOW_2											(SPREG_START + 53)//软件PWM2周期阴影
#define SPREG_SPWM_COUNTER_2													(SPREG_START + 54)//软件PWM2计数器
#define SPREG_SPWM_POS_3															(SPREG_START + 55)//软件PWM3正脉宽设置
#define SPREG_SPWM_POS_SHADOW_3												(SPREG_START + 56)//软件PWM3正脉宽阴影
#define SPREG_SPWM_CYCLE_3														(SPREG_START + 57)//软件PWM3周期设置
#define SPREG_SPWM_CYCLE_SHADOW_3											(SPREG_START + 58)//软件PWM3周期阴影
#define SPREG_SPWM_COUNTER_3													(SPREG_START + 59)//软件PWM3计数器
/*****************************************************************************/
#define SPREG_BEEM_VOLUME											  			(SPREG_START + 60)//蜂鸣器音量 0-100% 1320+60=1380
#define SPREG_BEEM_FREQ												  			(SPREG_START + 61)//蜂鸣器频率        1320+61=1381
#define SPREG_BEEM_MODE												  			(SPREG_START + 62)//蜂鸣器模式        1320+62=1382
#define SPREG_BEEM_COUNTER										  			(SPREG_START + 63)//蜂鸣器计时器      1320+63=1383
/*****************************************************************************/
//需要存储的方案
#define EM_LASER_SCHEME_NAME													(EM_START + 0)//方案名称
#define EM_LASER_CHANNEL_SELECT												(EM_START + 55)//激光通道选择
#define EM_LASER_PULSE_MODE														(EM_START + 56)//脉冲模式
#define EM_LASER_POWER_CH0														(EM_START + 57)//通道1470/1940功率
#define EM_LASER_POWER_CH1														(EM_START + 58)//通道980功率
#define EM_LASER_POWER_CH2														(EM_START + 59)//备用通道
#define EM_LASER_POWER_CH3														(EM_START + 60)//备用通道
#define EM_LASER_POWER_635														(EM_START + 61)//红激光功率
#define EM_LASER_POSWIDTH															(EM_START + 62)//多脉冲正脉宽
#define EM_LASER_NEGWIDTH															(EM_START + 63)//多脉冲负脉宽
/*****************************************************************************/
#define EM_LASER_AVERAGE_POWER_CH0										(EM_START + 64)//当前模式平均功率 1470/1940

#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
#define EM_LASER_AVERAGE_POWER_1470 									EM_LASER_AVERAGE_POWER_CH0
#endif
#if defined(MODEL_PVGLS_10W_1940_A1)
#define EM_LASER_AVERAGE_POWER_1940										EM_LASER_AVERAGE_POWER_CH0
#endif

#define EM_LASER_AVERAGE_POWER_CH1              			(EM_START + 65)//当前模式平均功率 980

#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
#define EM_LASER_AVERAGE_POWER_980 										EM_LASER_AVERAGE_POWER_CH1
#endif

#define EM_LASER_AVERAGE_POWER_CH2										(EM_START + 66)//当前模式平均功率 980
#define EM_LASER_AVERAGE_POWER_CH3										(EM_START + 67)//当前模式平均功率 980
#define EM_LASER_AVERAGE_POWER_635              			(EM_START + 68)//当前模式平均高功率 635
#define EM_LASER_FREQUENCY														(EM_START + 69)//当前模式频率
#define EM_LASER_DUTY_CYCLE														(EM_START + 70)//当前模式占空比 
/*****************************************************************************/
#define EM_LASER_TEMP																	(EM_START + 71)//激光二极管模块温度
#define EM_HT_TEMP																		(EM_START + 72)//散热器温度
#define EM_MCU_TEMP																		(EM_START + 73)//处理器温度
#define EM_FAN_SET_SPEED															(EM_START + 74)//激光散热风扇设定速度 0-100%
#define EM_FAN_GET_SPEED															(EM_START + 75)//激光散热风扇实际速度 转速

#define EM_ACOUSTIC_ENERGY														(EM_START + 77)//提示音能量间隔 16BIT
#define EM_ACOUSTIC_TIME															(EM_START + 78)//提示音时间间隔 16BIT
#define EM_ACOUSTIC_ENERGY_STEP												(EM_START + 79)//提示音步进能量
#define EM_ACOUSTIC_TIME_STEP													(EM_START + 80)//提示音步进时间
#define EM_ACOUSTIC_ENERGY_MAX												(EM_START + 81)//提示音能量最大值
#define EM_ACOUSTIC_ENERGY_MIN												(EM_START + 82)//提示音能量最小值
#define EM_ACOUSTIC_TIME_MAX													(EM_START + 83)//提示音时间最大值
#define EM_ACOUSTIC_TIME_MIN													(EM_START + 84)//提示音时间最小值
/*****************************************************************************/				
#define EM_LASER_POWER_TOTAL													(EM_START + 85)//发射总功率
#define EM_HMI_OPERA_STEP															(EM_START +	86)//操作步骤								
#define EM_ERROR_CODE																	(EM_START + 87)//错误码					
#define EM_SCHEME_NUM_TMP															(EM_START + 88)//临时方案编号	
#define EM_SCHEME_CLASSIFY_TMP												(EM_START + 89)//临时分类编号
/*****************************************************************************/
#define EM_DC_PAGE																		(EM_START + 90)//HMI页面编号 			
#define EM_DC_PASSCODE_INDEX													(EM_START + 91)//密码输入位索引		
#define EM_DC_NEW_PASSCODE0														(EM_START + 92)//输入新密码0			
#define EM_DC_NEW_PASSCODE1														(EM_START + 93)//输入新密码1			
#define EM_DC_NEW_PASSCODE2														(EM_START + 94)//输入新密码2			
#define EM_DC_NEW_PASSCODE3														(EM_START + 95)//输入新密码3						
/*****************************************************************************/
#define EM_LASER_RELEASE_TIME													(EM_START + 100)//实际激光发射累计时间	
#define EM_LASER_RELEASE_ENERGY												(EM_START + 102)//实际激光发射累计能量
#define EM_LASER_TRIG_TIME														(EM_START + 104)//激光触发时间
/*****************************************************************************/
#define FD_LASER_SCHEME_NAME													(FD_START +  0)//方案名称
#define FD_LASER_CHANNEL_SELECT												(FD_START +  55)//激光通道选择
#define FD_LASER_PULSE_MODE														(FD_START +  56)//脉冲模式
#define FD_LASER_POWER_CH0														(FD_START +  57)//通道1470功率
#define FD_LASER_POWER_CH1														(FD_START +  58)//通道980功率
#define FD_LASER_POWER_CH2														(FD_START +  59)//备用通道
#define FD_LASER_POWER_CH3														(FD_START +  60)//备用通道
#define FD_LASER_POWER_RED														(FD_START +  61)//红激光功率
#define FD_LASER_POSWIDTH															(FD_START +  62)//多脉冲正脉宽
#define FD_LASER_NEGWIDTH															(FD_START +  63)//多脉冲负脉宽
/*****************************************************************************/
#define FD_SCHEME_START_0															(FD_START +  0)//自定义1存储区起始 
#define FD_SCHEME_END_0																(FD_START +  63)//自定义0存储区结束		

#define FD_SCHEME_START_1															(FD_START +  64)//自定义1存储区起始		
#define FD_SCHEME_END_1																(FD_START +  127)//自定义1存储区结束

#define FD_SCHEME_START_2															(FD_START +  128)//自定义2存储区起始
#define FD_SCHEME_END_2																(FD_START +  191)//自定义2存储区结束

#define FD_SCHEME_START_3															(FD_START +  192)//自定义3存储区起始
#define FD_SCHEME_END_3																(FD_START +  255)//自定义3存储区结束

#define FD_SCHEME_START_4															(FD_START +  256)//自定义4存储区起始
#define FD_SCHEME_END_4																(FD_START +  319)//自定义4存储区结束

#define FD_SCHEME_START_5															(FD_START +  320)//自定义5存储区起始
#define FD_SCHEME_END_5																(FD_START +  383)//自定义5存储区结束

#define FD_SCHEME_START_6															(FD_START +  384)//自定义6存储区起始
#define FD_SCHEME_END_6																(FD_START +  447)//自定义6存储区结束

#define FD_SCHEME_START_7															(FD_START +  448)//自定义7存储区起始
#define FD_SCHEME_END_7																(FD_START +  511)//自定义7存储区结束

#define FD_SCHEME_START_8															(FD_START +  512)//自定义8存储区起始
#define FD_SCHEME_END_8																(FD_START +  575)//自定义8存储区结束

#define FD_SCHEME_START_9															(FD_START +  576)//自定义9存储区起始
#define FD_SCHEME_END_9																(FD_START +  639)//自定义9存储区结束

#define FD_SCHEME_START_10														(FD_START +  640)//自定义10存储区起始
#define FD_SCHEME_END_10															(FD_START +  703)//自定义10存储区结束

#define FD_SCHEME_START_11														(FD_START +  704)//自定义11存储区起始
#define FD_SCHEME_END_11															(FD_START +  767)//自定义11存储区结束

#define FD_SCHEME_START_12														(FD_START +  768)//自定义12存储区起始
#define FD_SCHEME_END_12															(FD_START +  831)//自定义12存储区结束

#define FD_SCHEME_START_13														(FD_START +  832)//自定义13存储区起始
#define FD_SCHEME_END_13															(FD_START +  895)//自定义13存储区结束

#define FD_SCHEME_START_14														(FD_START +  896)//自定义14存储区起始
#define FD_SCHEME_END_14															(FD_START +  959)//自定义14存储区结束

#define FD_SCHEME_START_15														(FD_START +  960)//自定义15存储区起始
#define FD_SCHEME_END_15															(FD_START + 1023)//自定义15存储区结束
/*****************************************************************************/
#define FD_SCHEME_START_16														(FD_START + 1024)//自定义16存储区起始
#define FD_SCHEME_END_16															(FD_START + 1087)//自定义16存储区结束

#define FD_SCHEME_START_17														(FD_START + 1088)//自定义17存储区起始
#define FD_SCHEME_END_17															(FD_START + 1151)//自定义17存储区结束

#define FD_SCHEME_START_18														(FD_START + 1152)//自定义18存储区起始
#define FD_SCHEME_END_18															(FD_START + 1215)//自定义18存储区结束

#define FD_SCHEME_START_19														(FD_START + 1216)//自定义19存储区起始
#define FD_SCHEME_END_19															(FD_START + 1279)//自定义19存储区结束

#define FD_SCHEME_START_20														(FD_START + 1280)//自定义20存储区起始
#define FD_SCHEME_END_20															(FD_START + 1343)//自定义20存储区结束

#define FD_SCHEME_START_21														(FD_START + 1344)//自定义21存储区起始
#define FD_SCHEME_END_21															(FD_START + 1407)//自定义21存储区结束

#define FD_SCHEME_START_22														(FD_START + 1408)//自定义22存储区起始
#define FD_SCHEME_END_22															(FD_START + 1471)//自定义22存储区结束

#define FD_SCHEME_START_23														(FD_START + 1472)//自定义23存储区起始
#define FD_SCHEME_END_23															(FD_START + 1535)//自定义23存储区结束

#define FD_SCHEME_START_24														(FD_START + 1536)//自定义24存储区起始
#define FD_SCHEME_END_24															(FD_START + 1599)//自定义24存储区结束

#define FD_SCHEME_START_25														(FD_START + 1600)//自定义25存储区起始
#define FD_SCHEME_END_25															(FD_START + 1663)//自定义25存储区结束

#define FD_SCHEME_START_26														(FD_START + 1664)//自定义26存储区起始
#define FD_SCHEME_END_26															(FD_START + 1727)//自定义26存储区结束

#define FD_SCHEME_START_27														(FD_START + 1728)//自定义27存储区起始
#define FD_SCHEME_END_27															(FD_START + 1791)//自定义27存储区结束

#define FD_SCHEME_START_28														(FD_START + 1792)//自定义28存储区起始
#define FD_SCHEME_END_28															(FD_START + 1855)//自定义28存储区结束

#define FD_SCHEME_START_29														(FD_START + 1856)//自定义29存储区起始
#define FD_SCHEME_END_29															(FD_START + 1919)//自定义29存储区结束

#define FD_SCHEME_START_30														(FD_START + 1920)//自定义30存储区起始
#define FD_SCHEME_END_30															(FD_START + 1983)//自定义30存储区结束

#define FD_SCHEME_START_31											(FD_START + 1984)//自定义31存储区起始
#define FD_SCHEME_END_31												(FD_START + 2047)//自定义31存储区结束
/*****************************************************************************/
#define TMP_REG_0																(TMP_START + 0)//临时名称储存区
#define TMP_REG_1																(TMP_START + 1)//临时名称储存区
#define TMP_REG_2																(TMP_START + 2)//临时名称储存区
#define TMP_REG_3																(TMP_START + 3)//临时名称储存区
#define TMP_REG_4																(TMP_START + 4)//临时名称储存区
#define TMP_REG_5																(TMP_START + 5)//临时名称储存区
#define TMP_REG_6																(TMP_START + 6)//临时名称储存区
#define TMP_REG_7																(TMP_START + 7)//临时名称储存区
#define TMP_REG_8																(TMP_START + 8)//临时名称储存区
#define TMP_REG_9																(TMP_START + 9)//临时名称储存区
#define TMP_REG_10															(TMP_START + 10)//临时名称储存区
#define TMP_REG_11													(TMP_START + 11)//临时名称储存区
#define TMP_REG_12													(TMP_START + 12)//临时名称储存区
#define TMP_REG_13													(TMP_START + 13)//临时名称储存区
#define TMP_REG_14													(TMP_START + 14)//临时名称储存区
#define TMP_REG_15													(TMP_START + 15)//临时名称储存区
#define TMP_REG_16													(TMP_START + 16)//临时名称储存区
#define TMP_REG_17													(TMP_START + 17)//临时名称储存区
#define TMP_REG_18													(TMP_START + 18)//临时名称储存区
#define TMP_REG_19													(TMP_START + 19)//临时名称储存区
#define TMP_REG_20													(TMP_START + 20)//临时名称储存区
#define TMP_REG_21													(TMP_START + 21)//临时名称储存区
#define TMP_REG_22													(TMP_START + 22)//临时名称储存区
#define TMP_REG_23													(TMP_START + 23)//临时名称储存区
#define TMP_REG_24													(TMP_START + 24)//临时名称储存区
#define TMP_REG_25													(TMP_START + 25)//临时名称储存区
#define TMP_REG_26													(TMP_START + 26)//临时名称储存区
#define TMP_REG_27													(TMP_START + 27)//临时名称储存区
#define TMP_REG_28													(TMP_START + 28)//临时名称储存区
#define TMP_REG_29													(TMP_START + 29)//临时名称储存区
#define TMP_REG_30													(TMP_START + 30)//临时名称储存区
#define TMP_REG_31													(TMP_START + 31)//临时名称储存区

#define TMP_REG_32													(TMP_START + 32)//临时名称储存区
#define TMP_REG_33													(TMP_START + 33)//临时名称储存区
#define TMP_REG_34													(TMP_START + 34)//临时名称储存区
#define TMP_REG_35												(TMP_START + 35)//临时名称储存区
#define TMP_REG_36												(TMP_START + 36)//临时名称储存区
#define TMP_REG_37												(TMP_START + 37)//临时名称储存区
#define TMP_REG_38												(TMP_START + 38)//临时名称储存区
#define TMP_REG_39												(TMP_START + 39)//临时名称储存区
#define TMP_REG_40												(TMP_START + 40)//临时名称储存区
#define TMP_REG_41												(TMP_START + 41)//临时名称储存区
#define TMP_REG_42												(TMP_START + 42)//临时名称储存区
#define TMP_REG_43												(TMP_START + 43)//临时名称储存区
#define TMP_REG_44												(TMP_START + 44)//临时名称储存区
#define TMP_REG_45												(TMP_START + 45)//临时名称储存区
#define TMP_REG_46												(TMP_START + 46)//临时名称储存区
#define TMP_REG_47												(TMP_START + 47)//临时名称储存区
#define TMP_REG_48												(TMP_START + 48)//临时名称储存区
#define TMP_REG_49												(TMP_START + 49)//临时名称储存区
#define TMP_REG_50												(TMP_START + 50)//临时名称储存区
#define TMP_REG_51												(TMP_START + 51)//临时名称储存区
#define TMP_REG_52												(TMP_START + 52)//临时名称储存区
#define TMP_REG_53												(TMP_START + 53)//临时名称储存区
#define TMP_REG_54												(TMP_START + 54)//临时名称储存区
#define TMP_REG_55												(TMP_START + 55)//临时名称储存区
#define TMP_REG_56												(TMP_START + 56)//临时名称储存区
#define TMP_REG_57												(TMP_START + 57)//临时名称储存区
#define TMP_REG_58												(TMP_START + 58)//临时名称储存区
#define TMP_REG_59												(TMP_START + 59)//临时名称储存区
#define TMP_REG_60												(TMP_START + 60)//临时名称储存区
#define TMP_REG_61												(TMP_START + 61)//临时名称储存区
#define TMP_REG_62												(TMP_START + 62)//临时名称储存区
#define TMP_REG_63													(TMP_START + 63)//临时名称储存区
/*****************************************************************************/
#define DM_SCHEME_CLASSIFY													(DM_START + 0)//选择的方案分类 
#define DM_SCHEME_INDEX															(DM_START + 1)//选择的方案索引
#define DM_BEEM_VOLUME															(DM_START + 2)//蜂鸣器音量 0-100% 32+3=35
#define DM_AIM_BRG																	(DM_START + 3)//指示激光亮度
#define DM_LCD_BRG																	(DM_START + 4)//屏幕亮度
#define DM_DC_OLD_PASSCODE0													(DM_START + 5)//屏旧密码0-1
#define DM_DC_OLD_PASSCODE1													(DM_START + 6)//屏旧密码2-3
#define DM_DC_OLD_PASSCODE2													(DM_START + 7)//屏旧密码0-1
#define DM_DC_OLD_PASSCODE3													(DM_START + 8)//屏旧密码2-3
/*****************************************************************************/
#define X_ESTOP_NC																	(X_START * 16 + 0)//XIN0 紧急停止开关
#define X_INTERLOCK_NC															(X_START * 16 + 1)//XIN1 安全连锁
#define X_FOOTSWITCH_NO															(X_START * 16 + 2)//XIN2 脚踏常开
#define X_FOOTSWITCH_NC															(X_START * 16 + 3)//XIN3 脚踏常闭
#define X_FIBER_PROBE																(X_START * 16 + 4)//XIN5 光纤探测
/*****************************************************************************/
#define Y_GREEN_LED																	(Y_START * 16 + 0)//YOUT0 绿灯开关
#define Y_RED_LED																		(Y_START * 16 + 1)//YOUT1 红灯开关
#define Y_YELLOW_LED																(Y_START * 16 + 2)//YOUT2 蓝灯开关
#define Y_TICK_LED																	(Y_START * 16 + 3)//YOUT3 板载运行LED指示灯
#define Y_ERR_LED																		(Y_START * 16 + 4)//YOUT4 板载错误LED指示灯
#define Y_BEEM_LED																	(Y_START * 16 + 5)//YOUT5 板载错误LED指示灯
#define Y_TEC																				(Y_START * 16 + 6)//YOUT6 TEC输出
/*****************************************************************************/
#define R_ESTOP																			(R_START * 16 + 0)//急停标志
#define R_INTERLOCK																	(R_START * 16 + 1)//连锁标志
#define R_FIBER_PROBE																(R_START * 16 + 2)//光纤插入标志
#define R_RFID_PASS																	(R_START * 16 + 3)//NFC光纤插入标志
#define R_LASER_TEMP_HIGH														(R_START * 16 + 4)//激光二极管激光模块高温标志
#define R_LASER_TEMP_LOW														(R_START * 16 + 5)//激光二极管激光模块低温标志
#define R_MCU_TEMP_HIGH															(R_START * 16 + 6)//处理器高温标志
#define R_MCU_TEMP_LOW															(R_START * 16 + 7)//处理器低温标志
#define R_FOOTSWITCH_PLUG														(R_START * 16 + 8)//脚踏插入标志
#define R_FOOTSWITCH_PRESS													(R_START * 16 + 9)//脚踏按下标志
#define R_HMI_FOOTSWITCH_PRESS											(R_START * 16 + 10)//屏幕模拟脚踏按下标志
#define R_FAULT																			(R_START * 16 + 11)//故障标志
#define R_DISABLE_ESTOP															(R_START * 16 + 12)//屏蔽急停开关检测
#define R_DISABLE_TEMPERATURE												(R_START * 16 + 13)//屏蔽温度检测
#define	R_DISABLE_FOOTSWITCH												(R_START * 16 + 14)//屏蔽脚踏开关检测
#define R_DISABLE_RFID															(R_START * 16 + 15)//屏蔽NFC检测
#define R_DISABLE_FIBER_PROBE												(R_START * 16 + 16)//屏蔽光纤探测
#define R_DISABLE_FAN_SPEED													(R_START * 16 + 17)//屏蔽风扇控制
#define R_DISABLE_INTERLOCK													(R_START * 16 + 18)//屏蔽安全连锁
#define R_CLEAR_EPROM																(R_START * 16 + 19)//完全清空EPROM
#define R_SAVE_EPROM																(R_START * 16 + 20)//储存SAVE
#define R_ENGINEER_MODE															(R_START * 16 + 21)//工程师模式
#define R_CALIBRATION_MODE													(R_START * 16 + 22)//功率校正模式
#define R_ACOUSTIC_ENABLE														(R_START * 16 + 23)//使能提示音
#define R_CLEAR_CRC																	(R_START * 16 + 24)//清除固件CRC
#define R_UPDATE_BOOTLOAD_REQ												(R_START * 16 + 25)//请求更新引导固件
#define R_UPDATE_BOOTLOAD_YES												(R_START * 16 + 26)//同意更新固件
#define R_UPDATE_BOOTLOAD_NO												(R_START * 16 + 27)//否定更新固件
//HMI相关状态
#define R_DCHMI_RESET_REQ														(R_START * 16 + 30)//HMI复位请求
#define R_DCHMI_RESET_DOING													(R_START * 16 + 31)//HMI复位中
#define R_DCHMI_RESET_DONE													(R_START * 16 + 32)//HMI复位完成	
#define R_DCHMI_UPDATEUI_REQ												(R_START * 16 + 33)//HMI内容更新请求
#define R_DCHMI_UPDATEUI_DOING											(R_START * 16 + 34)//HMI内容更新中
#define R_DCHMI_UPDATEUI_DONE												(R_START * 16 + 35)//HMI内容更新请求完成
#define R_DCHMI_RESTORE_REQ													(R_START * 16 + 36)//HMI从FLASH中恢复设置请求
#define R_DCHMI_RESTORE_DOING												(R_START * 16 + 37)//HMI从FLASH中恢复中
#define R_DCHMI_RESTORE_DONE												(R_START * 16 + 38)//HMI从FLASH中恢复设置完成	
#define R_DCHMI_DISPLAY_WARN												(R_START * 16 + 39)//HMI显示报警信息
#define R_DCHMI_KEY_STANDBY_ENABLE									(R_START * 16 + 40)//STANDBY 使能
/*****************************************************************************/
#define R_STANDBY_KEY_POSWIDTH_ADD_DOWN							(R_START * 16 + 50)
#define R_STANDBY_KEY_POSWIDTH_ADD_UP								(R_START * 16 + 51)
#define R_STANDBY_KEY_POSWIDTH_DEC_DOWN							(R_START * 16 + 52)
#define R_STANDBY_KEY_POSWIDTH_DEC_UP								(R_START * 16 + 53)
#define R_STANDBY_KEY_NEGWIDTH_ADD_DOWN							(R_START * 16 + 54)
#define R_STANDBY_KEY_NEGWIDTH_ADD_UP								(R_START * 16 + 55)
#define R_STANDBY_KEY_NEGWIDTH_DEC_DOWN							(R_START * 16 + 56)
#define R_STANDBY_KEY_NEGWIDTH_DEC_UP								(R_START * 16 + 57)
#define R_STANDBY_KEY_TIMES_ADD_DOWN								(R_START * 16 + 58)
#define R_STANDBY_KEY_TIMES_DEC_DOWN								(R_START * 16 + 59)
#define R_STANDBY_KEY_STNADBY_DOWN									(R_START * 16 + 60)
#define R_STANDBY_KEY_STNADBY_UP										(R_START * 16 + 61)
#define R_STANDBY_KEY_ENTER_OPTION_DOWN							(R_START * 16 + 62)
#define R_STANDBY_KEY_SCHEME_SAVE_DOWN							(R_START * 16 + 64)
#define R_STANDBY_KEY_SCHEME_LAST_DOWN							(R_START * 16 + 65)
#define R_STANDBY_KEY_SCHEME_NEXT_DOWN							(R_START * 16 + 66)
#define R_STANDBY_KEY_AIM_BRG_ADD_DOWN							(R_START * 16 + 67)
#define R_STANDBY_KEY_AIM_BRG_DEC_DOWN							(R_START * 16 + 68)
#define R_STANDBY_KEY_POWER_ADD_DOWN								(R_START * 16 + 69)
#define R_STANDBY_KEY_POWER_DEC_DOWN								(R_START * 16 + 70)
#define R_STANDBY_KEY_MODE_CW_DOWN									(R_START * 16 + 71)
#define R_STANDBY_KEY_MODE_SP_DOWN									(R_START * 16 + 72)
#define R_STANDBY_KEY_MODE_MP_DOWN									(R_START * 16 + 73)
#define R_STANDBY_KEY_MODE_GP_DOWN									(R_START * 16 + 74)
/*****************************************************************************/
#define R_READY_KEY_READY_DOWN											(R_START * 16 + 80)
#define R_READY_KEY_READY_UP												(R_START * 16 + 81)
#define R_READY_KEY_ACOUSTIC_ENERGY_ADD_DOWN				(R_START * 16 + 82)
#define R_READY_KEY_ACOUSTIC_ENERGY_ADD_UP					(R_START * 16 + 83)
#define R_READY_KEY_ACOUSTIC_ENERGY_DEC_DOWN				(R_START * 16 + 84)
#define R_READY_KEY_ACOUSTIC_ENERGY_DEC_UP					(R_START * 16 + 85)
#define R_READY_KEY_ACOUSTIC_TIME_ADD_DOWN					(R_START * 16 + 86)
#define R_READY_KEY_ACOUSTIC_TIME_ADD_UP						(R_START * 16 + 87)
#define R_READY_KEY_ACOUSTIC_TIME_DEC_DOWN					(R_START * 16 + 88)
#define R_READY_KEY_ACOUSTIC_TIME_DEC_UP						(R_START * 16 + 89)
/*****************************************************************************/
#define R_OPTION_KEY_ENTER_INFORMATION_DOWN					(R_START * 16 + 101)
#define R_OPTION_KEY_ENTER_OK_DOWN									(R_START * 16 + 102)
#define R_OPTION_KEY_ENTER_DIAGNOSIS_DOWN						(R_START * 16 + 103)
#define R_OPTION_KEY_BEEM_VOLUME_ADD_DOWN						(R_START * 16 + 104)
#define R_OPTION_KEY_BEEM_VOLUME_DEC_DOWN						(R_START * 16 + 105)
#define R_OPTION_KEY_LCD_BRG_ADD_DOWN								(R_START * 16 + 106)
#define R_OPTION_KEY_LCD_BRG_DEC_DOWN								(R_START * 16 + 107)
/*****************************************************************************/
#define R_INFORMATION_KEY_OK_DOWN										(R_START * 16 + 110)
#define R_INFORMATION_KEY_OK_UP											(R_START * 16 + 111)
/*****************************************************************************/
#define R_SCHEME_KEY_RENAME_DOWN										(R_START * 16 + 120)
#define R_SCHEME_KEY_OK_DOWN												(R_START * 16 + 121)
#define R_SCHEME_KEY_SCHEME_SELECT_0_DOWN						(R_START * 16 + 123)		
#define R_SCHEME_KEY_SCHEME_SELECT_1_DOWN						(R_START * 16 + 124)
#define R_SCHEME_KEY_SCHEME_SELECT_2_DOWN						(R_START * 16 + 125)
#define R_SCHEME_KEY_SCHEME_SELECT_3_DOWN						(R_START * 16 + 126)
#define R_SCHEME_KEY_SCHEME_SELECT_4_DOWN						(R_START * 16 + 127)
#define R_SCHEME_KEY_SCHEME_SELECT_5_DOWN						(R_START * 16 + 128)
#define R_SCHEME_KEY_SCHEME_SELECT_6_DOWN						(R_START * 16 + 129)
#define R_SCHEME_KEY_SCHEME_SELECT_7_DOWN						(R_START * 16 + 130)
#define R_SCHEME_KEY_SCHEME_SELECT_8_DOWN						(R_START * 16 + 131)
#define R_SCHEME_KEY_SCHEME_SELECT_9_DOWN						(R_START * 16 + 132)
#define R_SCHEME_KEY_SCHEME_SELECT_10_DOWN					(R_START * 16 + 133)
#define R_SCHEME_KEY_SCHEME_SELECT_11_DOWN					(R_START * 16 + 134)
#define R_SCHEME_KEY_SCHEME_SELECT_12_DOWN					(R_START * 16 + 135)
#define R_SCHEME_KEY_SCHEME_SELECT_13_DOWN					(R_START * 16 + 136)
#define R_SCHEME_KEY_SCHEME_SELECT_14_DOWN					(R_START * 16 + 137)
#define R_SCHEME_KEY_SCHEME_SELECT_15_DOWN					(R_START * 16 + 138)
#define R_SCHEME_KEY_SCHEME_SELECT_16_DOWN					(R_START * 16 + 139)
#define R_SCHEME_KEY_SCHEME_SELECT_17_DOWN					(R_START * 16 + 140)
#define R_SCHEME_KEY_SCHEME_SELECT_18_DOWN					(R_START * 16 + 141)
#define R_SCHEME_KEY_SCHEME_SELECT_19_DOWN					(R_START * 16 + 142)
#define R_SCHEME_KEY_SCHEME_SELECT_20_DOWN					(R_START * 16 + 143)
#define R_SCHEME_KEY_SCHEME_SELECT_21_DOWN					(R_START * 16 + 144)
#define R_SCHEME_KEY_SCHEME_SELECT_22_DOWN					(R_START * 16 + 145)
#define R_SCHEME_KEY_SCHEME_SELECT_23_DOWN					(R_START * 16 + 146)
#define R_SCHEME_KEY_SCHEME_SELECT_24_DOWN					(R_START * 16 + 147)
#define R_SCHEME_KEY_SCHEME_SELECT_25_DOWN					(R_START * 16 + 148)
#define R_SCHEME_KEY_SCHEME_SELECT_26_DOWN					(R_START * 16 + 149)
#define R_SCHEME_KEY_SCHEME_SELECT_27_DOWN					(R_START * 16 + 150)
#define R_SCHEME_KEY_SCHEME_SELECT_28_DOWN					(R_START * 16 + 151)
#define R_SCHEME_KEY_SCHEME_SELECT_29_DOWN					(R_START * 16 + 152)
#define R_SCHEME_KEY_SCHEME_SELECT_30_DOWN					(R_START * 16 + 153)
#define R_SCHEME_KEY_SCHEME_SELECT_31_DOWN					(R_START * 16 + 154)

#define R_SCHEME_KEY_NEXT_SCHEME										(R_START * 16 + 155)
#define R_SCHEME_KEY_LAST_SCHEME										(R_START * 16 + 156)
/*****************************************************************************/
#define R_DIAGNOSIS_OK_DOWN													(R_START * 16 + 160)
#define R_DIAGNOSIS_OK_UP														(R_START * 16 + 161)
/*****************************************************************************/
#define R_RENAME_KEY_ENTER_DOWN											(R_START * 16 + 170)
#define R_RENAME_KEY_EXIT_DOWN											(R_START * 16 + 171)
#define R_RENAME_TEXTDISPLAY_READ_DONE							(R_START * 16 + 172)
/*****************************************************************************/
/*****************************************************************************/
#define MR_FOOSWITCH_HAND_SWITCH										(MR_START * 16 + 10)//脚踏HandSwitch 脉冲控制
#define MR_BEEP_TONE																(MR_START * 16 + 11)//蜂鸣器模式 0:SYNC 1:BEEP
/*****************************************************************************/
#define T100MS_HMI_POWERUP_DELAY										0//HMI启动复位延时
#define T100MS_ENTER_PASSCODE_DELAY									1
#define T100MS_READY_BEEM_DELAY											2//进入READY状态后蜂鸣器响延迟
#define T100MS_PULSE_BEEM_DELAY											3//脉冲模式蜂鸣器延迟
/*****************************************************************************/
#define T10MS_POSWIDTH_ADD_KEYDOWN_DELAY						0
#define T10MS_POSWIDTH_DEC_KEYDOWN_DELAY						1
#define T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY						2
#define T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY						3
#define T10MS_TIMES_ADD_KEYDOWN_DELAY								4
#define T10MS_TIMES_DEC_KEYDOWN_DELAY								5
#define T10MS_GROUP_OFF_ADD_KEYDOWN_DELAY						6
#define T10MS_GROUP_OFF_DEC_KEYDOWN_DELAY						7
#define T10MS_ACOUSTIC_ENERGY_ADD_KEYDOWN_DELAY			8
#define T10MS_ACOUSTIC_ENERGY_DEC_KEYDOWN_DELAY			9
#define T10MS_ACOUSTIC_TIME_ADD_KEYDOWN_DELAY				10
#define T10MS_ACOUSTIC_TIME_DEC_KEYDOWN_DELAY				11	
/*****************************************************************************/
#endif






