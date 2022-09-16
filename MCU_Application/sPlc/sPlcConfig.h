#ifndef __SPLCCONFIG_H__
#define __SPLCCONFIG_H__
/*****************************************************************************/
//制冷器使能
#define SET_TEC_PWM(b)																HAL_GPIO_WritePin(TEC_OUT_GPIO_Port, TEC_OUT_Pin, b)
#define FLIP_TEC_PWM()																HAL_GPIO_TogglePin(TEC_OUT_GPIO_Port, TEC_OUT_Pin)
#define GET_TEC_PWM()																	HAL_GPIO_ReadPin(TEC_OUT_GPIO_Port, TEC_OUT_Pin)
//指令指示灯
#define SET_LINK_LED(b)																HAL_GPIO_WritePin(LINK_LED_GPIO_Port, LINK_LED_Pin, b)
#define FLIP_LINK_LED()																HAL_GPIO_TogglePin(LINK_LED_GPIO_Port, LINK_LED_Pin)
#define GET_LINK_LED()																HAL_GPIO_ReadPin(LINK_LED_GPIO_Port, LINK_LED_Pin)
//报警指示灯
#define SET_ALARM_LED(b)															HAL_GPIO_WritePin(ALARM_LED_OUT_GPIO_Port, ALARM_LED_OUT_Pin, b)
#define FLIP_ALARM_LED()															HAL_GPIO_TogglePin(ALARM_LED_OUT_GPIO_Port, ALARM_LED_OUT_Pin)
#define GET_ALARM_LED()																HAL_GPIO_ReadPin(ALARM_LED_OUT_GPIO_Port, ALARM_LED_OUT_Pin)
//通道1激光发射指示
#define SET_LASER1_LED(b)															HAL_GPIO_WritePin(LASER1_LED_OUT_GPIO_Port, LASER1_LED_OUT_Pin, b)
#define FLIP_LASER1_LED()															HAL_GPIO_TogglePin(LASER1_LED_OUT_GPIO_Port, LASER1_LED_OUT_Pin)
#define GET_LASER1_LED()															HAL_GPIO_ReadPin(LASER1_LED_OUT_GPIO_Port, LASER1_LED_OUT_Pin)
//通道2激光发射指示
#define SET_LASER2_LED(b)															HAL_GPIO_WritePin(LASER2_LED_OUT_GPIO_Port, LASER2_LED_OUT_Pin, b)
#define FLIP_LASER2_LED()															HAL_GPIO_TogglePin(LASER2_LED_OUT_GPIO_Port, LASER2_LED_OUT_Pin)
#define GET_LASER2_LED()															HAL_GPIO_ReadPin(LASER2_LED_OUT_GPIO_Port, LASER2_LED_OUT_Pin)
//板载心跳LED
#define SET_TICK_LED(b)																HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, b)
#define FLIP_TICK_LED()																HAL_GPIO_TogglePin(TICK_LED_GPIO_Port, TICK_LED_Pin)
#define GET_TICK_LED()																HAL_GPIO_ReadPin(TICK_LED_GPIO_Port, TICK_LED_Pin)
//板载错误LED
#define SET_ERR_LED(b)																HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, b)
#define FLIP_ERR_LED(b)																HAL_GPIO_TogglePin(ERR_LED_GPIO_Port, ERR_LED_Pin)
#define GET_ERR_LED()																	HAL_GPIO_ReadPin(ERR_LED_GPIO_Port, ERR_LED_Pin)
//通道1指示光
#define SET_LASER1_AIM(b)															HAL_GPIO_WritePin(LASER1_AIM_GPIO_Port, LASER1_AIM_Pin, b)
#define FLIP_LASER1_AIM()															HAL_GPIO_TogglePin(LASER1_AIM_GPIO_Port, LASER1_AIM_Pin)
#define GET_LASER1_AIM()															HAL_GPIO_ReadPin(LASER1_AIM_GPIO_Port, LASER1_AIM_Pin)
//通道2指示光
#define SET_LASER2_AIM(b)															HAL_GPIO_WritePin(LASER2_AIM_GPIO_Port, LASER2_AIM_Pin, b)
#define FLIP_LASER2_AIM()															HAL_GPIO_TogglePin(LASER2_AIM_GPIO_Port, LASER2_AIM_Pin)
#define GET_LASER2_AIM()															HAL_GPIO_ReadPin(LASER2_AIM_GPIO_Port, LASER2_AIM_Pin)
//联锁
#define GET_INTERLOCK()																HAL_GPIO_ReadPin(INTERLOCK_IN_GPIO_Port, INTERLOCK_IN_Pin)
//急停
#define GET_ESTOP()																		HAL_GPIO_ReadPin(ESTOP_NC_IN_GPIO_Port, ESTOP_NC_IN_Pin)
//外控使能				
#define GET_EXT_ENABLE()															HAL_GPIO_ReadPin(LASER_EXT_ENA_GPIO_Port, LASER_EXT_ENA_Pin)
//外控触发
#define GET_LASER_TRG()																HAL_GPIO_ReadPin(LASER_TRIG_IN_GPIO_Port, LASER_TRIG_IN_Pin)
//ULINK LED
#define SET_ULINK_LED(b)															HAL_GPIO_WritePin(LOCK_LED_GPIO_Port, LOCK_LED_Pin, b)
#define FLIP_ULINK_LED()															HAL_GPIO_TogglePin(LOCK_LED_GPIO_Port, LOCK_LED_Pin)
#define GET_ULINK_LED()																HAL_GPIO_ReadPin(LOCK_LED_GPIO_Port, LOCK_LED_Pin)
//DC-DC变换器使能
#define SET_LASER_PWM(b)															HAL_GPIO_WritePin(LASER_PWM_GPIO_Port, LASER_PWM_Pin, b)
#define FLIP_LASER_PWM()															HAL_GPIO_TogglePin(LASER_PWM_GPIO_Port, LASER_PWM_Pin)
#define GET_LASER_PWM()																HAL_GPIO_ReadPin(LASER_PWM_GPIO_Port, LASER_PWM_Pin)
//SPEAK
#define SET_SPEAK_ENA(b)															HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, b)
#define FLIP_SPEAK_ENA()															HAL_GPIO_TogglePin(SPK_EN_GPIO_Port, SPK_EN_Pin)
#define GET_SPEAK_ENA()																HAL_GPIO_ReadPin(SPK_EN_GPIO_Port, SPK_EN_Pin)
/*****************************************************************************/
#define BEEM_MODE_0																		0x10//连续模式
#define BEEM_MODE_1																		0x11//声光同步
#define BEEM_MODE_2																		0x12//激光发射固定间隔
#define BEEM_MODE_3																		0x13//异常报警
/*****************************************************************************/
#define CONFIG_MORSECODE_SPACE_TIME										3000
#define CONFIG_MORSECODE_LONG_TIME										900
#define CONFIG_MORSECODE_SHORT_TIME										300
/*****************************************************************************/
#define CONFIG_MODBUS_RTU_BAUDRATE										9600//MODBUS通信波特率
#define CONFIG_RING_BUFFER_SIZE												256//循环缓冲区大小
#define CONFIG_FREEPROTOCOL_SIZE											64
#define FP_RX_SIZE																		CONFIG_FREEPROTOCOL_SIZE//自由协议接收缓冲
#define FP_TX_SIZE																		CONFIG_FREEPROTOCOL_SIZE//自由协议发送缓冲
/*****************************************************************************/
#define STM32_UNIQUE_ID_SIZE 													12//MCU序列号  8*12=96Bit
#define DEVID_H																				'1'//设备ID
#define DEVID_L																				'A'//设备ID
#define BUFFER_SIZE        														((uint16_t)512*64)//512的整数倍
#define CONFIG_JUMP_DELAY															5000//检测U盘时间
#define FATFS_ROOT																		"0:"
#define LOG_FIRMWARE_FILENAME													"/log.txt"//操作记录文件
#define CFG_FIRMWARE_FILENAME													"/las.cfg"//操作配置文件
#define LMCU_FIRMWARE_FILENAME												"/ld_mcu.bin"//更新MCU固件地址
#define LLCD_FIRMWARE_FILENAME												"/ld_lcd.pkg"//更新LCD固件地址
#define SAVE_EPROM_FILENAME														"/seprom.bin"//EPROM->UDISK 储存名称
#define LOAD_EPROM_FILENAME														"/leprom.bin"//UDISK->EPROM 恢复名称
/*****************************************************************************/				
#define CONFIG_SPLC_DEFAULT_SPK_FREQ									1500L//蜂鸣器默认频率
#define CONFIG_SPLC_MAX_SPK_FREQ											2000L
#define CONFIG_SPLC_MIN_SPK_FREQ											800L
/*****************************************************************************/
#define CONFIG_INPUT_FILTER_TIME											8//输入数字滤波扫描周期 1mS * N
/*****************************************************************************/
#define CONFIG_SPLC_ASSERT														1//检查地址范围
#define CONFIG_SPLC_DEV																0x0A01//设备号
#define CONFIG_SPLC_CLEAR_CODE												0xA58E
#define CONFIG_SOFTPLC_TICK														200L//5mS
/*****************************************************************************/
#define CONFIG_SPLC_USING_EPROM												1//EPROM
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
#define CONFIG_SPLC_ADC_CHANNEL												10//ADC采集通道
#define CONFIG_SPLC_ADC_AVERAGE_NUM										16//ADC平均值次数
#define CONFIG_ADC_DMA_BUFFER_SIZE										(CONFIG_SPLC_ADC_CHANNEL * CONFIG_SPLC_ADC_AVERAGE_NUM)//ADC DMA采集缓冲
#define CONFIG_AMBIENT_TEMP             							25// Ambient temp in deg C
#define CONFIG_VREF_CAL                         			*(__IO uint16_t *)(0x1FFF7A2A)//校正电压源
#define CONFIG_ADC_AVG_SLOPE													2.5F
#define CONFIG_ADC_V25																760.0F//0.76V@25D
#define CONFIG_NTC_RS																	3300L//NTC分压电阻
#define CONFIG_NTC_B																	3477.0F
#define CONFIG_NTC_R25																10000.0F//25摄氏度时电阻
#define CONFIG_NTC_VREF																5000L//
#define CONFIG_ISAB_RS																0.003F
#define CONFIG_ISC_RS																	0.050F
/*****************************************************************************/
#define CONFIG_MAX_DAC_CH0														0xFFFF
#define CONFIG_MIN_DAC_CH0														0
#define CONFIG_MAX_DAC_CH1														0xFFFF
#define CONFIG_MIN_DAC_CH1														0
#define CONFIG_MAX_DAC_CH2														0xFFFF
#define CONFIG_MIN_DAC_CH2														0
#define CONFIG_MAX_DAC_CH3														0xFFFF
#define CONFIG_MIN_DAC_CH3														0
#define CONFIG_MAX_DAC_CH4														0xFFFF
#define CONFIG_MIN_DAC_CH4														0
#define CONFIG_MAX_DAC_CH5														0xFFFF
#define CONFIG_MIN_DAC_CH5														0
#define CONFIG_MAX_DAC_CH6														0xFFFF
#define CONFIG_MIN_DAC_CH6														0
#define CONFIG_MAX_DAC_CH7														0xFFFF
#define CONFIG_MIN_DAC_CH7														0
/*****************************************************************************/
#define CONFIG_SPLC_USING_LASER												1
/*****************************************************************************/
#define CONFIG_DIODE_SET_TEMP													200//激光器恒温温度 
#define CONFIG_DIODE_DIFF_TEMP												15
#define CONFIG_DIODE_HIGH_TEMP												380//激光器高温极限 46.0C
#define CONFIG_DIODE_LOW_TEMP													-100//激光器低温极限 - 10.0C
#define CONFIG_ENVI_HIGH_TEMP													750//处理器高温极限 75.0C
#define CONFIG_DIODE_THRESHOLD												600//激光发射阈值600mA
#define CONFIG_MAX_LASERPOWER_CH0											150//通道0最大激光功率
#define CONFIG_MAX_LASERPOWER_CH1											150//通道1最大激光功率
#define CONFIG_MAX_LASERPOWER_CH2											100//通道2最大激光功率
#define CONFIG_MAX_LASERPOWER_CH3											100//通道3最大激光功率
#define CONFIG_MIN_LASERPOWER_CH0											1//通道0最小激光功率
#define CONFIG_MIN_LASERPOWER_CH1											1//通道1最小激光功率
#define CONFIG_MIN_LASERPOWER_CH2											1//通道2最大激光功率
#define CONFIG_MIN_LASERPOWER_CH3											1//通道3最大激光功率
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
#define CONFIG_BEEM_ENERGY_INTERVAL_TIME							800//变音持续时间
#define CONFIG_MAX_ACOUSTIC_ENERGY										2000
#define CONFIG_MIN_ACOUSTIC_ENERGY										10
#define CONFIG_MAX_ACOUSTIC_TIME											999
#define CONFIG_MIN_ACOUSTIC_TIME											10
#define CONFIG_BEEM_MAX_VOLUME												100//蜂鸣器最大音量
#define CONFIG_BEEM_MIN_VOLUME												0//蜂鸣器最小音量
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
//特殊寄存器 256
#define SPREG_START																		1320
#define SPREG_END																			1575
//特殊线圈 16 * 16 = 256
#define SPCOIL_START																	1576
#define SPCOIL_END																		1591
//临时寄存器 64
#define TMP_START																			1592
#define TMP_END																				1655
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
#define CONFIG_LKSRAM_SIZE														1024//自由协议发送缓冲
#define CONFIG_LKRRAM_SIZE														1024//自由协议接收缓冲
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
#define SPCOIL_BEEM_ENABLE														(SPCOIL_START * 16 + 32)//蜂鸣器使能
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
#define SPREG_TICK																		(SPREG_START + 0)//TICK ++
/*****************************************************************************/
#define SPREG_ADC_0																		(SPREG_START + 11)//ADC1-IN0  采集值 LPA_ISMON0
#define SPREG_ADC_1																		(SPREG_START + 12)//ADC1-IN1  采集值 LASER NTC
#define SPREG_ADC_2																		(SPREG_START + 13)//ADC1-IN2  采集值 LASER1_PD
#define SPREG_ADC_3																		(SPREG_START + 14)//ADC1-IN3  采集值 LASER2_PD
#define SPREG_ADC_4																		(SPREG_START + 15)//ADC1-IN10 采集值 LPC_ISMON0
#define SPREG_ADC_5																		(SPREG_START + 16)//ADC1-IN11 采集值 LPB_ISMON1
#define SPREG_ADC_6																		(SPREG_START + 17)//ADC1-IN12 采集值 LPB_ISMON0
#define SPREG_ADC_7																		(SPREG_START + 18)//ADC1-IN13 采集值 LPA_ISMON1
#define SPREG_ADC_8																		(SPREG_START + 19)//ADC1 CHIP TEMP片内温度传感器
#define SPREG_ADC_9																		(SPREG_START + 20)//ADC1 CHIP VREFINT片内基准源
/*****************************************************************************/
#define SPREG_DAC_0																		(SPREG_START + 30)//DAC0设定值 激光通道0
#define SPREG_DAC_1																		(SPREG_START + 31)//DAC1设定值 激光通道1
#define SPREG_DAC_2																		(SPREG_START + 32)//DAC2设定值 激光通道2
#define SPREG_DAC_3																		(SPREG_START + 33)//DAC3设定值 激光通道3
#define SPREG_DAC_4																		(SPREG_START + 34)//DAC4设定值 激光通道4
#define SPREG_DAC_5																		(SPREG_START + 35)//DAC5设定值 激光通道5
#define SPREG_DAC_6																		(SPREG_START + 36)//DAC6设定值 激光通道6
#define SPREG_DAC_7																		(SPREG_START + 37)//DAC7设定值 激光通道7
/*****************************************************************************/
#define SPREG_SPWM_POS_0															(SPREG_START + 50)//软件PWM0正脉宽设置
#define SPREG_SPWM_POS_SHADOW_0												(SPREG_START + 51)//软件PWM0正脉宽阴影
#define SPREG_SPWM_CYCLE_0														(SPREG_START + 52)//软件PWM0周期设置
#define SPREG_SPWM_CYCLE_SHADOW_0											(SPREG_START + 53)//软件PWM0周期阴影
#define SPREG_SPWM_COUNTER_0													(SPREG_START + 54)//软件PWM0计数器
#define SPREG_SPWM_POS_1															(SPREG_START + 55)//软件PWM1正脉宽设置
#define SPREG_SPWM_POS_SHADOW_1												(SPREG_START + 56)//软件PWM1正脉宽阴影
#define SPREG_SPWM_CYCLE_1														(SPREG_START + 57)//软件PWM1周期设置
#define SPREG_SPWM_CYCLE_SHADOW_1											(SPREG_START + 58)//软件PWM1周期阴影
#define SPREG_SPWM_COUNTER_1													(SPREG_START + 59)//软件PWM1计数器
#define SPREG_SPWM_POS_2															(SPREG_START + 60)//软件PWM2正脉宽设置
#define SPREG_SPWM_POS_SHADOW_2												(SPREG_START + 61)//软件PWM2正脉宽阴影
#define SPREG_SPWM_CYCLE_2														(SPREG_START + 62)//软件PWM2周期设置
#define SPREG_SPWM_CYCLE_SHADOW_2											(SPREG_START + 63)//软件PWM2周期阴影
#define SPREG_SPWM_COUNTER_2													(SPREG_START + 64)//软件PWM2计数器
#define SPREG_SPWM_POS_3															(SPREG_START + 65)//软件PWM3正脉宽设置
#define SPREG_SPWM_POS_SHADOW_3												(SPREG_START + 66)//软件PWM3正脉宽阴影
#define SPREG_SPWM_CYCLE_3														(SPREG_START + 67)//软件PWM3周期设置
#define SPREG_SPWM_CYCLE_SHADOW_3											(SPREG_START + 68)//软件PWM3周期阴影
#define SPREG_SPWM_COUNTER_3													(SPREG_START + 69)//软件PWM3计数器
/*****************************************************************************/
#define SPREG_BEEM_VOLUME															(SPREG_START + 70)//蜂鸣器音量 0-100% 1320+55=1375
#define SPREG_BEEM_FREQ																(SPREG_START + 71)//蜂鸣器频率        1320+56=1376
#define SPREG_BEEM_MODE																(SPREG_START + 72)//蜂鸣器模式        1320+57=1377
#define SPREG_BEEM_COUNTER														(SPREG_START + 73)//蜂鸣器计时器      1320+58=1378
/*****************************************************************************/
#define SPREG_CLEAR_NVRAM															(SPREG_START + 80)//清除NVRAM后重新启动
#define SPREG_TICK_L																	(SPREG_START + 81)//累计运行时间 秒低位
#define SPREG_TICK_H																	(SPREG_START + 82)//累计运行时间 秒高位
#define SPREG_SCAN_TIME																(SPREG_START + 83)//扫描时间
#define SPREG_IDENTITY																(SPREG_START + 84)//平台ID号
/*****************************************************************************/
#define SPREG_CHID0_L																	(SPREG_START + 90)//CHIP UUID 处理器唯一ID
#define SPREG_CHID0_H																	(SPREG_START + 91)//CHIP UUID
#define SPREG_CHID1_L																	(SPREG_START + 92)//CHIP UUID
#define SPREG_CHID1_H																	(SPREG_START + 93)//CHIP UUID
#define SPREG_CHID2_L																	(SPREG_START + 94)//CHIP UUID
#define SPREG_CHID2_H																	(SPREG_START + 95)//CHIP UUID
/*****************************************************************************/
#define DM_ADC_OFFSET_0																(DM_START + 10)//ADC0偏移量
#define DM_ADC_OFFSET_1																(DM_START + 11)//ADC1偏移量
#define DM_ADC_OFFSET_2																(DM_START + 12)//ADC2偏移量
#define DM_ADC_OFFSET_3																(DM_START + 13)//ADC3偏移量
#define DM_ADC_OFFSET_4																(DM_START + 14)//ADC4偏移量
#define DM_ADC_OFFSET_5																(DM_START + 15)//ADC5偏移量
#define DM_ADC_OFFSET_6																(DM_START + 16)//ADC6偏移量
#define DM_ADC_OFFSET_7																(DM_START + 17)//ADC7偏移量
#define DM_ADC_OFFSET_8																(DM_START + 18)//ADC8偏移量
#define DM_ADC_OFFSET_9																(DM_START + 19)//ADC9偏移量
/*****************************************************************************/
#define EM_LASER_POWER_CH0														(EM_START + 10)//通道0功率 999->99.9%
#define EM_LASER_POWER_CH1														(EM_START + 11)//通道1功率 999->99.9%
#define EM_LASER_PWM_CH0															(EM_START + 12)//通道0占空比 100->100%
#define EM_LASER_PWM_CH1															(EM_START + 13)//通道1占空比 100->100%
#define EM_LASER_POSWIDTH															(EM_START + 14)//发射正脉宽 100->10.0秒
#define EM_LASER_TEMP																	(EM_START + 15)//激光器温度
#define EM_MCU_TEMP																		(EM_START + 16)//处理器温度
#define EM_LASER_CURRENT_CH0													(EM_START + 17)//通道0电流
#define EM_LASER_CURRENT_CH1													(EM_START + 18)//通道1电流
#define EM_LASER_CURRENT_CH2													(EM_START + 19)//通道2电流
#define EM_LASER_CURRENT_CH3													(EM_START + 20)//通道3电流
#define EM_LASER_CURRENT_CH4													(EM_START + 21)//通道4电流
#define EM_LASER_PD_CH0																(EM_START + 22)//通道0 PD
#define EM_LASER_PD_CH1																(EM_START + 23)//通道1 PD
#define EM_SPEAK_VOLUME																(EM_START + 24)//喇叭音量
#define EM_LASER_PULSE_MODE														(EM_START + 25)//激光模式
#define EM_LASER_TEMP_SET															(EM_START + 26)//激光冷却温度
#define EM_COOL_RATE																	(EM_START + 27)//制冷量显示
/*****************************************************************************/
#define R_PARA_LOCK																		(R_START * 16 + 10)//参数锁定
#define R_LASER_START																	(R_START * 16 + 11)//激光启动
#define R_LASER_STOP																	(R_START * 16 + 12)//激光停止
#define R_AIM_ENABLE_CH0															(R_START * 16 + 13)//通道0 指示光启动
#define R_AIM_ENABLE_CH1															(R_START * 16 + 14)//通道1 指示光启动
#define R_ALRAM																				(R_START * 16 + 15)//故障报警
#define R_LASER_TEMP_HIGH															(R_START * 16 + 16)//激光器高温报警
#define R_MCU_TEMP_HIGH																(R_START * 16 + 17)//环境保温报警
#define R_CALIBRATION_MODE														(R_START * 16 + 18)//启用功率校准
#define R_RETURN_ZERO																	(R_START * 16 + 19)//手动归零
/*****************************************************************************/
#define TMP_REG_0																			(TMP_START + 0)//临时名称储存区
#define TMP_REG_1																			(TMP_START + 1)//临时名称储存区
#define TMP_REG_2																			(TMP_START + 2)//临时名称储存区
#define TMP_REG_3																			(TMP_START + 3)//临时名称储存区
#define TMP_REG_4																			(TMP_START + 4)//临时名称储存区
#define TMP_REG_5																			(TMP_START + 5)//临时名称储存区
#define TMP_REG_6																			(TMP_START + 6)//临时名称储存区
#define TMP_REG_7																			(TMP_START + 7)//临时名称储存区
#define TMP_REG_8																			(TMP_START + 8)//临时名称储存区
#define TMP_REG_9																			(TMP_START + 9)//临时名称储存区
#define TMP_REG_10																		(TMP_START + 10)//临时名称储存区
#define TMP_REG_11																		(TMP_START + 11)//临时名称储存区
#define TMP_REG_12																		(TMP_START + 12)//临时名称储存区
#define TMP_REG_13																		(TMP_START + 13)//临时名称储存区
#define TMP_REG_14																		(TMP_START + 14)//临时名称储存区
#define TMP_REG_15																		(TMP_START + 15)//临时名称储存区
#define TMP_REG_16																		(TMP_START + 16)//临时名称储存区
#define TMP_REG_17																		(TMP_START + 17)//临时名称储存区
#define TMP_REG_18																		(TMP_START + 18)//临时名称储存区
#define TMP_REG_19																		(TMP_START + 19)//临时名称储存区
#define TMP_REG_20																		(TMP_START + 20)//临时名称储存区
#define TMP_REG_21																		(TMP_START + 21)//临时名称储存区
#define TMP_REG_22																		(TMP_START + 22)//临时名称储存区
#define TMP_REG_23																		(TMP_START + 23)//临时名称储存区
#define TMP_REG_24																		(TMP_START + 24)//临时名称储存区
#define TMP_REG_25																		(TMP_START + 25)//临时名称储存区
#define TMP_REG_26																		(TMP_START + 26)//临时名称储存区
#define TMP_REG_27																		(TMP_START + 27)//临时名称储存区
#define TMP_REG_28																		(TMP_START + 28)//临时名称储存区
#define TMP_REG_29																		(TMP_START + 29)//临时名称储存区
#define TMP_REG_30																		(TMP_START + 30)//临时名称储存区
#define TMP_REG_31																		(TMP_START + 31)//临时名称储存区

#define TMP_REG_32																		(TMP_START + 32)//临时名称储存区
#define TMP_REG_33																		(TMP_START + 33)//临时名称储存区
#define TMP_REG_34																		(TMP_START + 34)//临时名称储存区
#define TMP_REG_35																		(TMP_START + 35)//临时名称储存区
#define TMP_REG_36																		(TMP_START + 36)//临时名称储存区
#define TMP_REG_37																		(TMP_START + 37)//临时名称储存区
#define TMP_REG_38																		(TMP_START + 38)//临时名称储存区
#define TMP_REG_39																		(TMP_START + 39)//临时名称储存区
#define TMP_REG_40																		(TMP_START + 40)//临时名称储存区
#define TMP_REG_41																		(TMP_START + 41)//临时名称储存区
#define TMP_REG_42																		(TMP_START + 42)//临时名称储存区
#define TMP_REG_43																		(TMP_START + 43)//临时名称储存区
#define TMP_REG_44																		(TMP_START + 44)//临时名称储存区
#define TMP_REG_45																		(TMP_START + 45)//临时名称储存区
#define TMP_REG_46																		(TMP_START + 46)//临时名称储存区
#define TMP_REG_47																		(TMP_START + 47)//临时名称储存区
#define TMP_REG_48																		(TMP_START + 48)//临时名称储存区
#define TMP_REG_49																		(TMP_START + 49)//临时名称储存区
#define TMP_REG_50																		(TMP_START + 50)//临时名称储存区
#define TMP_REG_51																		(TMP_START + 51)//临时名称储存区
#define TMP_REG_52																		(TMP_START + 52)//临时名称储存区
#define TMP_REG_53																		(TMP_START + 53)//临时名称储存区
#define TMP_REG_54																		(TMP_START + 54)//临时名称储存区
#define TMP_REG_55																		(TMP_START + 55)//临时名称储存区
#define TMP_REG_56																		(TMP_START + 56)//临时名称储存区
#define TMP_REG_57																		(TMP_START + 57)//临时名称储存区
#define TMP_REG_58																		(TMP_START + 58)//临时名称储存区
#define TMP_REG_59																		(TMP_START + 59)//临时名称储存区
#define TMP_REG_60																		(TMP_START + 60)//临时名称储存区
#define TMP_REG_61																		(TMP_START + 61)//临时名称储存区
#define TMP_REG_62																		(TMP_START + 62)//临时名称储存区
#define TMP_REG_63																		(TMP_START + 63)//临时名称储存区
/*****************************************************************************/
//1304
#define X_INTERLOCK_NC																(X_START * 16 + 0)//XIN1 安全连锁
#define X_EXT_ENABLE																	(X_START * 16 + 1)//XIN2 外控使能	
#define X_LASER_TRIG																	(X_START * 16 + 2)//XIN3 外控触发
/*****************************************************************************/
#define Y_TICK_LED																		(Y_START * 16 + 0)//YOUT0 心跳灯
#define Y_ERR_LED																			(Y_START * 16 + 1)//YOUT1 错误灯
#define Y_ALARM_LED																		(Y_START * 16 + 2)//YOUT2 报警灯
#define Y_ULINK_LED																		(Y_START * 16 + 3)//YOUT3 通行指令执行指示灯
#define Y_LASER1_LED																	(Y_START * 16 + 4)//YOUT4 通道1 激光指示灯
#define Y_LASER2_LED																	(Y_START * 16 + 5)//YOUT5 通道2 激光指示灯
#define Y_AIM1_ENA																		(Y_START * 16 + 6)//YOUT6 通道1 指示光使能
#define Y_AIM2_ENA																		(Y_START * 16 + 7)//YOUT7 通道2 指示光使能
#define Y_TEC_ENA																			(Y_START * 16 + 8)//YOUT8 制冷器使能
/*****************************************************************************/


#endif






