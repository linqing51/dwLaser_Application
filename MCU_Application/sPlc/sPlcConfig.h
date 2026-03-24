#ifndef __SPLCCONFIG_H__
#define __SPLCCONFIG_H__
/*****************************************************************************/
#define CONFIG_DEBUG_DAC															1//调试DAC驱动
#define CONFIG_DEBUB_ADC															1//调试ADC驱动
#define CONFIG_DEBUG_EPROM														1//调试EPROM驱动
#define CONFIG_DEBUG_IO																1//调试IO
#define CONFIG_DEBUG_SPK															0//调试蜂鸣器驱动
#define CONFIG_DEBUG_LED															1//调试指示灯驱动
#define CONFIG_DEBUG_AIM															1//调试指示光驱动
#define CONFIG_DEBUG_LASER														0//调试LASER驱动
#define CONFIG_DEBUG_SPLC															0//调试SPLC命令
#define CONFIG_DEBUG_WSW															0//调试无线脚踏
#define CONFIG_DEBUG_IIC_EXPAND												0//调试I2C总线扩展器
#define CONFIG_INPUT_FILTER_TIME											10//输入数字滤波扫描周期 1mS * N
/*****************************************************************************/
#define CONFIG_SPLC_USING_ADC													1//使能ADC模块
#define CONFIG_SPLC_USING_SPWM												1//使能软件PWM功能
#define CONFIG_SPLC_USING_FUNTEST											0//功能指令测试
#define CONFIG_SPLC_USING_EPROM_TEST									0//EPROM 读写测试
#define CONFIG_SPLC_USING_LASER_TEST									0
/*****************************************************************************/
#define CONFIG_SPLC_ASSERT														1//检查地址范围
#define CONFIG_SPLC_CLEAR_CODE												0xA58E
#define CONFIG_SOFTPLC_TICK														200L//5mS
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
//特殊寄存器 128
#define SPREG_START																		1320
#define SPREG_END																			1447
//特殊线圈 16 * 16 = 256
#define SPCOIL_START																	1448
#define SPCOIL_END																		1463
//临时寄存器 16
#define TMP_START																			1464
#define TMP_END																				1479
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
#define SPCOIL_WFSWITCH_NO														(SPCOIL_START * 16 + 41)//无线脚踏按下
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
#define SPREG_ADC_0																		(SPREG_START + 0)//采集值 CH0 CURRENT
#define SPREG_ADC_1																		(SPREG_START + 1)//采集值 CH1 CURRENT
#define SPREG_ADC_2																		(SPREG_START + 2)//采集值 CH2 CURRENT
#define SPREG_ADC_3																		(SPREG_START + 3)//采集值 CH3 CURRENT
#define SPREG_ADC_4																		(SPREG_START + 4)//采集值 CH4 CURRENT
#define SPREG_ADC_5																		(SPREG_START + 5)//采集值 CH5 CURRENT
#define SPREG_ADC_6																		(SPREG_START + 6)//采集值 CH7 CURRENT
#define SPREG_ADC_7																		(SPREG_START + 7)//采集值 CH8 CURRENT

#define SPREG_ADC_8																		(SPREG_START + 8)//采集值 CH0 VOLTAGE
#define SPREG_ADC_9																		(SPREG_START + 9)//采集值 CH1 VOLTAGE
#define SPREG_ADC_10																	(SPREG_START + 10)//采集值 CH2 VOLTAGE
#define SPREG_ADC_11																	(SPREG_START + 11)//采集值 CH3 VOLTAGE
#define SPREG_ADC_12																	(SPREG_START + 12)//采集值 CH4 VOLTAGE
#define SPREG_ADC_13																	(SPREG_START + 13)//采集值 CH5 VOLTAGE
#define SPREG_ADC_14																	(SPREG_START + 14)//采集值 CH7 VOLTAGE
#define SPREG_ADC_15																	(SPREG_START + 15)//采集值 CH8 VOLTAGE

#define SPREG_ADC_16																	(SPREG_START + 16)//采集值 TEC0 CURRENT
#define SPREG_ADC_17																	(SPREG_START + 17)//采集值 TEC1 CURRENT
#define SPREG_ADC_18																	(SPREG_START + 18)//采集值 TEC2 CURRENT
#define SPREG_ADC_19																	(SPREG_START + 19)//采集值 TEC3 CURRENT
#define SPREG_ADC_20																	(SPREG_START + 20)//采集值 TEC4 CURRENT
#define SPREG_ADC_21																	(SPREG_START + 21)//采集值 TEC5 CURRENT
#define SPREG_ADC_22																	(SPREG_START + 22)//采集值 TEC6 CURRENT
#define SPREG_ADC_23																	(SPREG_START + 23)//采集值 TEC7 CURRENT

#define SPREG_ADC_24																	(SPREG_START + 24)//采集值 TEC1 VOLTAGE
#define SPREG_ADC_25																	(SPREG_START + 25)//采集值 TEC2 VOLTAGE
#define SPREG_ADC_26																	(SPREG_START + 26)//采集值 TEC3 VOLTAGE
#define SPREG_ADC_27																	(SPREG_START + 27)//采集值 TEC4 VOLTAGE
#define SPREG_ADC_28																	(SPREG_START + 28)//采集值 TEC5 VOLTAGE
#define SPREG_ADC_29																	(SPREG_START + 29)//采集值 TEC6 VOLTAGE
#define SPREG_ADC_30																	(SPREG_START + 30)//采集值 TEC7 VOLTAGE
#define SPREG_ADC_31																	(SPREG_START + 31)//采集值 TEC8 VOLTAGE

#define SPREG_ADC_32																	(SPREG_START + 32)//采集值 散热器HT1_NTC 
#define SPREG_ADC_33																	(SPREG_START + 33)//采集值 散热器HT2_NTC 
#define SPREG_ADC_34																	(SPREG_START + 34)//采集值 散热器HT2_NTC 
#define SPREG_ADC_35																	(SPREG_START + 35)//采集值 散热器HT3_NTC
#define SPREG_ADC_36																	(SPREG_START + 36)//采集值 冷却液WATER1_NTC->HOT  
#define SPREG_ADC_37																	(SPREG_START + 37)//采集值 冷却液WATER2_NTC->COOL
#define SPREG_ADC_38																	(SPREG_START + 38)//采集值 冷却液WATER3_NTC 
#define SPREG_ADC_39																	(SPREG_START + 39)//采集值 冷却液WATER4_NTC

#define SPREG_ADC_40																	(SPREG_START + 40)//采集值 激光器DIODE0 LASER_NTC
#define SPREG_ADC_41																	(SPREG_START + 41)//采集值 激光器DIODE1 LASER_NTC
#define SPREG_ADC_42																	(SPREG_START + 42)//采集值 激光器DIODE2 LASER_NTC
#define SPREG_ADC_43																	(SPREG_START + 43)//采集值 激光器DIODE3 LASER_NTC
#define SPREG_ADC_44																	(SPREG_START + 44)//采集值 激光器DIODE4 LASER_NTC
#define SPREG_ADC_45																	(SPREG_START + 45)//采集值 激光器DIODE5 LASER_NTC
#define SPREG_ADC_46																	(SPREG_START + 46)//采集值 激光器DIODE6 LASER_NTC
#define SPREG_ADC_47																	(SPREG_START + 47)//采集值 激光器DIODE7 LASER_NTC

#define SPREG_ADC_48																	(SPREG_START + 48)//采集值 激光器耦合 FIBER_NTC
#define SPREG_ADC_49																	(SPREG_START + 49)//采集值 激光器晶体1
#define SPREG_ADC_50																	(SPREG_START + 50)//采集值 激光器晶体2

#define SPREG_ADC_51																	(SPREG_START + 51)//采集值 PWR CURRENT 母线电流
#define SPREG_ADC_52																	(SPREG_START + 52)//采集值 VIN VOLTAGE 母线电压
#define SPREG_ADC_53																	(SPREG_START + 53)//采集值 BAT NTC
#define SPREG_ADC_54																	(SPREG_START + 54)//采集值 LASER_FPD
#define SPREG_ADC_55																	(SPREG_START + 55)//采集值 LASER_LPD
#define SPREG_ADC_56																	(SPREG_START + 56)//采集值 AMB0_TEMP环境温度
#define SPREG_ADC_57																	(SPREG_START + 57)//采集值 AMB1_TEMP环境温度
#define SPREG_ADC_58																	(SPREG_START + 58)//CHIP TEMP片内温度传感器
#define SPREG_ADC_59																	(SPREG_START + 59)//CHIP VREFINT片内基准源
#define SPREG_ADC_60																	(SPREG_START + 60)//VBAT 掉电存储电池 
/*****************************************************************************/
#define SPREG_DAC_0																		(SPREG_START + 70)//DAC设定值 激光通道 CH0 ->1470 1940
#define SPREG_DAC_1																		(SPREG_START + 71)//DAC设定值 激光通道 CH1 ->980
#define SPREG_DAC_2																		(SPREG_START + 72)//DAC设定值 激光通道 CH2 
#define SPREG_DAC_3																		(SPREG_START + 73)//DAC设定值 激光通道 CH3
#define SPREG_DAC_4																		(SPREG_START + 74)//DAC设定值 激光通道 CH4
#define SPREG_DAC_5																		(SPREG_START + 75)//DAC设定值 激光通道 CH5
#define SPREG_DAC_6																		(SPREG_START + 76)//DAC设定值 激光通道 CH6 -> 635 PWM 占空比
#define SPREG_DAC_7																		(SPREG_START + 77)//DAC设定值 激光通道 CH7 
/*****************************************************************************/
#define SPREG_DAC_8																		(SPREG_START + 78)//DAC设定值 激光通道 CH8 ->TEC0
#define SPREG_DAC_9																		(SPREG_START + 79)//DAC设定值 激光通道 CH9 ->TEC1
#define SPREG_DAC_10																	(SPREG_START + 70)//DAC设定值 激光通道 CH10 ->TEC2
#define SPREG_DAC_11																	(SPREG_START + 81)//DAC设定值 激光通道 CH11 ->TEC3
#define SPREG_DAC_12																	(SPREG_START + 82)//DAC设定值 激光通道 CH12 ->TEC4
#define SPREG_DAC_13																	(SPREG_START + 83)//DAC设定值 激光通道 CH13 ->TEC5
#define SPREG_DAC_14																	(SPREG_START + 84)//DAC设定值 激光通道 CH14 ->TEC6
#define SPREG_DAC_15																	(SPREG_START + 85)//DAC设定值 激光通道 CH15 ->TEC7
/*****************************************************************************/
#define SPREG_DAC_16																	(SPREG_START + 86)//DAC设定值 激光通道 CH16 -> 635 PWM 占空比
#define SPREG_DAC_17																	(SPREG_START + 87)//DAC设定值 激光通道 CH17 -> 532 PWM 占空比
/*****************************************************************************/
#define SPREG_SPWM_POS_0															(SPREG_START + 90)//软件PWM0正脉宽设置
#define SPREG_SPWM_POS_SHADOW_0												(SPREG_START + 91)//软件PWM0正脉宽阴影
#define SPREG_SPWM_CYCLE_0														(SPREG_START + 92)//软件PWM0周期设置
#define SPREG_SPWM_CYCLE_SHADOW_0											(SPREG_START + 93)//软件PWM0周期阴影
#define SPREG_SPWM_COUNTER_0													(SPREG_START + 94)//软件PWM0计数器
#define SPREG_SPWM_POS_1															(SPREG_START + 95)//软件PWM1正脉宽设置
#define SPREG_SPWM_POS_SHADOW_1												(SPREG_START + 96)//软件PWM1正脉宽阴影
#define SPREG_SPWM_CYCLE_1														(SPREG_START + 97)//软件PWM1周期设置
#define SPREG_SPWM_CYCLE_SHADOW_1											(SPREG_START + 98)//软件PWM1周期阴影
#define SPREG_SPWM_COUNTER_1													(SPREG_START + 99)//软件PWM1计数器
#define SPREG_SPWM_POS_2															(SPREG_START + 100)//软件PWM2正脉宽设置
#define SPREG_SPWM_POS_SHADOW_2												(SPREG_START + 101)//软件PWM2正脉宽阴影
#define SPREG_SPWM_CYCLE_2														(SPREG_START + 102)//软件PWM2周期设置
#define SPREG_SPWM_CYCLE_SHADOW_2											(SPREG_START + 103)//软件PWM2周期阴影
#define SPREG_SPWM_COUNTER_2													(SPREG_START + 104)//软件PWM2计数器
#define SPREG_SPWM_POS_3															(SPREG_START + 105)//软件PWM3正脉宽设置
#define SPREG_SPWM_POS_SHADOW_3												(SPREG_START + 106)//软件PWM3正脉宽阴影
#define SPREG_SPWM_CYCLE_3														(SPREG_START + 107)//软件PWM3周期设置
#define SPREG_SPWM_CYCLE_SHADOW_3											(SPREG_START + 108)//软件PWM3周期阴影
#define SPREG_SPWM_COUNTER_3													(SPREG_START + 109)//软件PWM3计数器
/*****************************************************************************/
#define SPREG_BEEM_VOLUME											  			(SPREG_START + 110)//蜂鸣器音量 0-100% 1320+60=1380
#define SPREG_BEEM_FREQ												  			(SPREG_START + 111)//蜂鸣器频率        1320+61=1381
#define SPREG_BEEM_MODE												  			(SPREG_START + 112)//蜂鸣器模式        1320+62=1382
#define SPREG_BEEM_COUNTER										  			(SPREG_START + 113)//蜂鸣器计时器      1320+63=1383
/*****************************************************************************/
//需要存储的方案
#define EM_LASER_SCHEME_NAME													(EM_START + 0)//方案名称
#define EM_LASER_CHANNEL_SELECT												(EM_START + 51)//激光通道选择
#define EM_LASER_PULSE_MODE														(EM_START + 52)//脉冲模式
#define EM_LASER_POWER_CH0														(EM_START + 53)//通道1470/1940功率
#define EM_LASER_POWER_CH1														(EM_START + 54)//通道980功率
#define EM_LASER_POWER_CH2														(EM_START + 55)//备用通道2
#define EM_LASER_POWER_CH3														(EM_START + 56)//备用通道3
#define EM_LASER_POWER_CH4														(EM_START + 57)//备用通道4
#define EM_LASER_POWER_CH5														(EM_START + 58)//备用通道5
#define EM_LASER_POWER_CH6														(EM_START + 59)//备用通道6
#define EM_LASER_POWER_CH7														(EM_START + 60)//备用通道7
#define EM_LASER_POWER_635														(EM_START + 61)//红激光功率
#define EM_LASER_POSWIDTH															(EM_START + 62)//多脉冲正脉宽
#define EM_LASER_NEGWIDTH															(EM_START + 63)//多脉冲负脉宽
/*****************************************************************************/
#define EM_LASER_AVERAGE_POWER_CH0										(EM_START + 80)//当前模式平均功率 1470/1940
#define EM_LASER_AVERAGE_POWER_CH1              			(EM_START + 81)//当前模式平均功率 980
#define EM_LASER_AVERAGE_POWER_CH2										(EM_START + 82)//当前模式平均功率->备用通道2
#define EM_LASER_AVERAGE_POWER_CH3										(EM_START + 83)//当前模式平均功率->备用通道3
#define EM_LASER_AVERAGE_POWER_CH4              			(EM_START + 84)//当前模式平均功率->备用通道4
#define EM_LASER_AVERAGE_POWER_CH5										(EM_START + 85)//当前模式平均功率->备用通道5
#define EM_LASER_AVERAGE_POWER_CH6										(EM_START + 86)//当前模式平均功率->备用通道6
#define EM_LASER_AVERAGE_POWER_CH7              			(EM_START + 87)//当前模式平均功率->备用通道7
#define EM_LASER_AVERAGE_POWER_635              			(EM_START + 88)//当前模式平均高功率 635
#define EM_LASER_FREQUENCY														(EM_START + 89)//当前模式频率
#define EM_LASER_DUTY_CYCLE														(EM_START + 90)//当前模式占空比 
/*****************************************************************************/
#define EM_LASER_A_DIODE_TEMP													(EM_START + 100)//激光二极管模块A管芯温度
#define EM_LASER_A_COUPLER_TEMP												(EM_START + 101)//激光二极管模块A耦合温度
#define EM_LASER_A_CRYST0_TEMP												(EM_START + 102)//激光器A晶体温度->倍频1
#define EM_LASER_A_CRYST1_TEMP												(EM_START + 103)//激光器A晶体温度->倍频2
#define EM_LASER_B_DIODE_TEMP													(EM_START + 104)//激光二极管模块管B芯温度
#define EM_LASER_B_COUPLER_TEMP												(EM_START + 105)//激光二极管模块耦B合温度
#define EM_LASER_B_CRYST0_TEMP												(EM_START + 106)//激光器B晶体温度->倍频1
#define EM_LASER_B_CRYST1_TEMP												(EM_START + 107)//激光器B晶体温度->倍频2
#define EM_HT0_TEMP																		(EM_START + 108)//散热器1温度
#define EM_HT1_TEMP																		(EM_START + 109)//散热器2温度
#define EM_HT2_TEMP																		(EM_START + 110)//散热器3温度
#define EM_HT3_TEMP																		(EM_START + 111)//散热器4温度
#define EM_WATER_HOT_TEMP															(EM_START + 112)//冷却水温度->冷水
#define EM_WATER_COOL_TEMP														(EM_START + 113)//冷却水温度->热水
#define EM_AMBIENT0_TEMP															(EM_START + 114)//环境温度
#define EM_AMBIENT1_TEMP															(EM_START + 115)//环境温度
#define EM_AMBIENT2_TEMP															(EM_START + 116)//环境温度
#define EM_AMBIENT3_TEMP															(EM_START + 117)//环境温度
#define EM_RELATIVE0_HUMIDITY													(EM_START + 118)//相对湿度
#define EM_RELATIVE1_HUMIDITY													(EM_START + 119)//相对湿度
#define EM_MCU_TEMP																		(EM_START + 120)//处理器温度
#define EM_MBAT_TEMP																	(EM_START + 121)//电池温度

#define EM_LD_CH0_CURRENT															(EM_START + 130)//激光通道0->电流																
#define EM_LD_CH1_CURRENT															(EM_START + 131)//激光通道1->电流
#define EM_LD_CH2_CURRENT															(EM_START + 132)//激光通道2->电流
#define EM_LD_CH3_CURRENT															(EM_START + 133)//激光通道3->电流
#define EM_LD_CH4_CURRENT															(EM_START + 134)//激光通道4->电流
#define EM_LD_CH5_CURRENT															(EM_START + 135)//激光通道5->电流
#define EM_LD_CH6_CURRENT															(EM_START + 136)//激光通道6->电流
#define EM_LD_CH7_CURRENT															(EM_START + 137)//激光通道7->电流

#define EM_LD_CH0_VOLTAGE															(EM_START + 140)//激光通道0-电压
#define EM_LD_CH1_VOLTAGE															(EM_START + 141)//激光通道1-电压
#define EM_LD_CH2_VOLTAGE															(EM_START + 142)//激光通道2-电压
#define EM_LD_CH3_VOLTAGE															(EM_START + 143)//激光通道3-电压
#define EM_LD_CH4_VOLTAGE															(EM_START + 144)//激光通道4-电压
#define EM_LD_CH5_VOLTAGE															(EM_START + 145)//激光通道5-电压
#define EM_LD_CH6_VOLTAGE															(EM_START + 146)//激光通道6-电压
#define EM_LD_CH7_VOLTAGE															(EM_START + 147)//激光通道7-电压

#define EM_TEC_CH0_CURRENT														(EM_START + 150)//制冷通道0->电流
#define EM_TEC_CH1_CURRENT														(EM_START + 151)//制冷通道1->电流
#define EM_TEC_CH2_CURRENT														(EM_START + 152)//制冷通道2->电流
#define EM_TEC_CH3_CURRENT														(EM_START + 153)//制冷通道3->电流
#define EM_TEC_CH4_CURRENT														(EM_START + 154)//制冷通道4->电流
#define EM_TEC_CH5_CURRENT														(EM_START + 155)//制冷通道5->电流
#define EM_TEC_CH6_CURRENT														(EM_START + 156)//制冷通道6->电流
#define EM_TEC_CH7_CURRENT														(EM_START + 157)//制冷通道7->电流

#define EM_TEC_CH0_VOLTAGE														(EM_START + 160)//制冷通道0->电压
#define EM_TEC_CH1_VOLTAGE														(EM_START + 161)//制冷通道1->电压
#define EM_TEC_CH2_VOLTAGE														(EM_START + 162)//制冷通道2->电压
#define EM_TEC_CH3_VOLTAGE														(EM_START + 163)//制冷通道3->电压
#define EM_TEC_CH4_VOLTAGE														(EM_START + 164)//制冷通道3->电压
#define EM_TEC_CH5_VOLTAGE														(EM_START + 165)//制冷通道4->电压
#define EM_TEC_CH6_VOLTAGE														(EM_START + 166)//制冷通道5->电压
#define EM_TEC_CH7_VOLTAGE														(EM_START + 167)//制冷通道7->电压

#define EM_PWR_CURRENT																(EM_START + 170)//母线供电电流
#define EM_PWR_VOLTAGE																(EM_START + 171)//母线供电电压

#define EM_FAN0_SET_SPEED															(EM_START + 180)//风扇0设定速度 0-100%
#define EM_FAN1_SET_SPEED															(EM_START + 181)//风扇1设定速度 0-100%
#define EM_FAN2_SET_SPEED															(EM_START + 182)//风扇2设定速度 0-100%
#define EM_FAN3_SET_SPEED															(EM_START + 183)//风扇3设定速度 0-100%
#define EM_FAN0_GET_SPEED															(EM_START + 184)//风扇0实际速度 转速
#define EM_FAN1_GET_SPEED															(EM_START + 185)//风扇1实际速度 转速
#define EM_FAN2_GET_SPEED															(EM_START + 186)//风扇2实际速度 转速
#define EM_FAN3_GET_SPEED															(EM_START + 187)//风扇3实际速度 转速

#define EM_LASER_FPD																	(EM_START + 190)//光纤探测PD计算值
#define EM_LASER_LPD																	(EM_START + 191)//激光能量PD计算值

#define EM_TPID0_OUT																	(EM_START + 200)//温控PID-0输出值
#define EM_TPID1_OUT																	(EM_START + 201)//温控PID-1输出值
#define EM_TPID2_OUT																	(EM_START + 202)//温控PID-2输出值
#define EM_TPID3_OUT																	(EM_START + 203)//温控PID-3输出值

#define EM_ACOUSTIC_ENERGY														(EM_START + 210)//提示音能量间隔 16BIT
#define EM_ACOUSTIC_TIME															(EM_START + 211)//提示音时间间隔 16BIT
#define EM_ACOUSTIC_ENERGY_STEP												(EM_START + 212)//提示音步进能量
#define EM_ACOUSTIC_TIME_STEP													(EM_START + 213)//提示音步进时间
#define EM_ACOUSTIC_ENERGY_MAX												(EM_START + 214)//提示音能量最大值
#define EM_ACOUSTIC_ENERGY_MIN												(EM_START + 215)//提示音能量最小值
#define EM_ACOUSTIC_TIME_MAX													(EM_START + 216)//提示音时间最大值
#define EM_ACOUSTIC_TIME_MIN													(EM_START + 217)//提示音时间最小值
/*****************************************************************************/				
#define EM_LASER_POWER_TOTAL													(EM_START + 220)//发射总功率
#define EM_HMI_OPERA_STEP															(EM_START +	221)//操作步骤								
#define EM_ERROR_CODE																	(EM_START + 222)//错误码					
#define EM_SCHEME_NUM_TMP															(EM_START + 223)//临时方案编号	
#define EM_SCHEME_CLASSIFY_TMP												(EM_START + 224)//临时分类编号
/*****************************************************************************/
#define EM_DC_PAGE																		(EM_START + 230)//HMI页面编号 			
#define EM_DC_PASSCODE_INDEX													(EM_START + 231)//密码输入位索引		
#define EM_DC_NEW_PASSCODE0														(EM_START + 232)//输入新密码0			
#define EM_DC_NEW_PASSCODE1														(EM_START + 233)//输入新密码1			
#define EM_DC_NEW_PASSCODE2														(EM_START + 234)//输入新密码2			
#define EM_DC_NEW_PASSCODE3														(EM_START + 235)//输入新密码3						
/*****************************************************************************/
#define EM_LASER_RELEASE_TIME													(EM_START + 240)//实际激光发射累计时间	
#define EM_LASER_RELEASE_ENERGY												(EM_START + 241)//实际激光发射累计能量
#define EM_LASER_TRIG_TIME														(EM_START + 242)//激光触发时间
/*****************************************************************************/
#define FD_LASER_SCHEME_NAME													(FD_START +  0)//方案名称
#define FD_LASER_CHANNEL_SELECT												(FD_START +  51)//激光通道选择
#define FD_LASER_PULSE_MODE														(FD_START +  52)//脉冲模式
#define FD_LASER_POWER_CH0														(FD_START +  53)//通道1470功率
#define FD_LASER_POWER_CH1														(FD_START +  54)//通道980功率
#define FD_LASER_POWER_CH2														(FD_START +  55)//备用通道
#define FD_LASER_POWER_CH3														(FD_START +  56)//备用通道
#define FD_LASER_POWER_CH4														(FD_START +  57)//备用通道
#define FD_LASER_POWER_CH5														(FD_START +  58)//备用通道
#define FD_LASER_POWER_CH6														(FD_START +  59)//备用通道
#define FD_LASER_POWER_CH7														(FD_START +  60)//备用通道
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

#define FD_SCHEME_START_31														(FD_START + 1984)//自定义31存储区起始
#define FD_SCHEME_END_31															(FD_START + 2047)//自定义31存储区结束
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
/*****************************************************************************/
#define DM_SCHEME_CLASSIFY														(DM_START + 0)//选择的方案分类 
#define DM_SCHEME_INDEX																(DM_START + 1)//选择的方案索引
#define DM_BEEM_VOLUME																(DM_START + 2)//蜂鸣器音量 0-100% 32+3=35
#define DM_AIM_BRG																		(DM_START + 3)//指示激光亮度
#define DM_LCD_BRG																		(DM_START + 4)//屏幕亮度
#define DM_DC_OLD_PASSCODE0														(DM_START + 5)//屏旧密码0-1
#define DM_DC_OLD_PASSCODE1														(DM_START + 6)//屏旧密码2-3
#define DM_DC_OLD_PASSCODE2														(DM_START + 7)//屏旧密码0-1
#define DM_DC_OLD_PASSCODE3														(DM_START + 8)//屏旧密码2-3
/*****************************************************************************/
#define X_ESTOP_NC																		(X_START * 16 + 0)//XIN0 紧急停止开关
#define X_INTERLOCK_NC																(X_START * 16 + 1)//XIN1 安全连锁
#define X_FOOTSWITCH_NO																(X_START * 16 + 2)//XIN2 脚踏常开
#define X_FOOTSWITCH_NC																(X_START * 16 + 3)//XIN3 脚踏常闭
#define X_FIBER_PROBE																	(X_START * 16 + 4)//XIN5 光纤探测
#define X_PWR_KEY																			(X_START * 16 + 5)//XIN6 电源开关
/*****************************************************************************/
#define Y_GREEN_LED																		(Y_START * 16 + 0)//YOUT0 绿灯开关
#define Y_RED_LED																			(Y_START * 16 + 1)//YOUT1 红灯开关
#define Y_YELLOW_LED																	(Y_START * 16 + 2)//YOUT2 蓝灯开关
#define Y_TICK_LED																		(Y_START * 16 + 3)//YOUT3 板载运行LED指示灯
#define Y_ERR_LED																			(Y_START * 16 + 4)//YOUT4 板载错误LED指示灯
#define Y_BEEM_LED																		(Y_START * 16 + 5)//YOUT5 板载错误LED指示灯
#define Y_TEC																					(Y_START * 16 + 6)//YOUT6 TEC输出
#define Y_VN5016_INPUT																(Y_START * 16 + 7)//YOUT7 VN5016开通	
#define Y_VN5016_CSDIS																(Y_START * 16 + 8)//YOUT8 电源电流采集	
#define Y_PWR_LED																			(Y_START * 16 + 9)//YOUT9 电源指示灯
/*****************************************************************************/
#define R_ESTOP																				(R_START * 16 + 0)//急停标志
#define R_INTERLOCK																		(R_START * 16 + 1)//连锁标志
#define R_FIBER_PROBE																	(R_START * 16 + 2)//光纤插入标志
#define R_RFID_PASS																		(R_START * 16 + 3)//NFC光纤插入标志
																										
#define R_LASER_DIODE_TEMP_HIGH												(R_START * 16 + 10)//激光二极管激光模块高温标志
#define R_LASER_DIODE_TEMP_LOW												(R_START * 16 + 11)//激光二极管激光模块低温标志
#define R_WATER_HOT_HIGH															(R_START * 16 + 12)//热水高温报警标志
#define R_WATER_HOT_LOW																(R_START * 16 + 13)//热水低温报警标志
#define R_WATER_COOL_HIGH															(R_START * 16 + 14)//冷水高温报警标志
#define R_WATER_COOL_LOW															(R_START * 16 + 15)//冷水低温报警标志
#define R_AMBIENT_HIGH																(R_START * 16 + 16)//环境高温报警标志
#define R_AMBIENT_LOW																	(R_START * 16 + 17)//环境低温报警标志
#define R_HUMIDITY_HIGH																(R_START * 16 + 18)//环境高湿度报警标志

#define R_MCU_TEMP_HIGH																(R_START * 16 + 50)//处理器高温标志
#define R_MCU_TEMP_LOW																(R_START * 16 + 51)//处理器低温标志
#define R_FOOTSWITCH_PLUG															(R_START * 16 + 52)//脚踏插入标志
#define R_FOOTSWITCH_PRESS														(R_START * 16 + 53)//脚踏按下标志
#define R_HMI_FOOTSWITCH_PRESS												(R_START * 16 + 54)//屏幕模拟脚踏按下标志
#define R_FAULT																				(R_START * 16 + 55)//故障标志
#define R_DISABLE_ESTOP																(R_START * 16 + 56)//屏蔽急停开关检测
#define R_DISABLE_TEMPERATURE													(R_START * 16 + 57)//屏蔽温度检测
#define	R_DISABLE_FOOTSWITCH													(R_START * 16 + 58)//屏蔽脚踏开关检测
#define R_DISABLE_RFID																(R_START * 16 + 59)//屏蔽NFC检测
#define R_DISABLE_FIBER_PROBE													(R_START * 16 + 60)//屏蔽光纤探测
#define R_DISABLE_FAN_SPEED														(R_START * 16 + 61)//屏蔽风扇控制
#define R_DISABLE_INTERLOCK														(R_START * 16 + 62)//屏蔽安全连锁
#define R_CLEAR_EPROM																	(R_START * 16 + 63)//完全清空EPROM
#define R_SAVE_EPROM																	(R_START * 16 + 64)//储存SAVE
#define R_ENGINEER_MODE																(R_START * 16 + 65)//工程师模式
#define R_CALIBRATION_MODE														(R_START * 16 + 66)//功率校正模式
#define R_ACOUSTIC_ENABLE															(R_START * 16 + 67)//使能提示音
#define R_CLEAR_CRC																		(R_START * 16 + 68)//清除固件CRC
#define R_UPDATE_BOOTLOAD_REQ													(R_START * 16 + 69)//请求更新引导固件
#define R_UPDATE_BOOTLOAD_YES													(R_START * 16 + 70)//同意更新固件
#define R_UPDATE_BOOTLOAD_NO													(R_START * 16 + 71)//否定更新固件
#define R_BURNING_MODE																(R_START * 16 + 72)//老化模式
//HMI相关状态
#define R_DCHMI_RESET_REQ															(R_START * 16 + 80)//HMI复位请求
#define R_DCHMI_RESET_DOING														(R_START * 16 + 81)//HMI复位中
#define R_DCHMI_RESET_DONE														(R_START * 16 + 82)//HMI复位完成	
#define R_DCHMI_UPDATEUI_REQ													(R_START * 16 + 83)//HMI内容更新请求
#define R_DCHMI_UPDATEUI_DOING												(R_START * 16 + 84)//HMI内容更新中
#define R_DCHMI_UPDATEUI_DONE													(R_START * 16 + 85)//HMI内容更新请求完成
#define R_DCHMI_RESTORE_REQ														(R_START * 16 + 86)//HMI从FLASH中恢复设置请求
#define R_DCHMI_RESTORE_DOING													(R_START * 16 + 87)//HMI从FLASH中恢复中
#define R_DCHMI_RESTORE_DONE													(R_START * 16 + 88)//HMI从FLASH中恢复设置完成	
#define R_DCHMI_DISPLAY_WARN													(R_START * 16 + 89)//HMI显示报警信息
#define R_DCHMI_KEY_STANDBY_ENABLE										(R_START * 16 + 90)//STANDBY 使能
/*****************************************************************************/
#define R_STANDBY_KEY_POSWIDTH_ADD_DOWN								(R_START * 16 + 100)
#define R_STANDBY_KEY_POSWIDTH_ADD_UP									(R_START * 16 + 101)
#define R_STANDBY_KEY_POSWIDTH_DEC_DOWN								(R_START * 16 + 102)
#define R_STANDBY_KEY_POSWIDTH_DEC_UP									(R_START * 16 + 103)
#define R_STANDBY_KEY_NEGWIDTH_ADD_DOWN								(R_START * 16 + 104)
#define R_STANDBY_KEY_NEGWIDTH_ADD_UP									(R_START * 16 + 105)
#define R_STANDBY_KEY_NEGWIDTH_DEC_DOWN								(R_START * 16 + 106)
#define R_STANDBY_KEY_NEGWIDTH_DEC_UP									(R_START * 16 + 107)
#define R_STANDBY_KEY_TIMES_ADD_DOWN									(R_START * 16 + 108)
#define R_STANDBY_KEY_TIMES_DEC_DOWN									(R_START * 16 + 109)
#define R_STANDBY_KEY_STNADBY_DOWN										(R_START * 16 + 110)
#define R_STANDBY_KEY_STNADBY_UP											(R_START * 16 + 111)
#define R_STANDBY_KEY_ENTER_OPTION_DOWN								(R_START * 16 + 112)
#define R_STANDBY_KEY_SCHEME_SAVE_DOWN								(R_START * 16 + 113)
#define R_STANDBY_KEY_SCHEME_LAST_DOWN								(R_START * 16 + 114)
#define R_STANDBY_KEY_SCHEME_NEXT_DOWN								(R_START * 16 + 115)
#define R_STANDBY_KEY_AIM_BRG_ADD_DOWN								(R_START * 16 + 116)
#define R_STANDBY_KEY_AIM_BRG_DEC_DOWN								(R_START * 16 + 117)
#define R_STANDBY_KEY_POWER_ADD_DOWN									(R_START * 16 + 118)
#define R_STANDBY_KEY_POWER_DEC_DOWN									(R_START * 16 + 119)
#define R_STANDBY_KEY_MODE_CW_DOWN										(R_START * 16 + 120)
#define R_STANDBY_KEY_MODE_SP_DOWN										(R_START * 16 + 121)
#define R_STANDBY_KEY_MODE_MP_DOWN										(R_START * 16 + 122)
#define R_STANDBY_KEY_MODE_GP_DOWN										(R_START * 16 + 123)
/*****************************************************************************/
#define R_READY_KEY_READY_DOWN												(R_START * 16 + 130)
#define R_READY_KEY_READY_UP													(R_START * 16 + 131)
#define R_READY_KEY_ACOUSTIC_ENERGY_ADD_DOWN					(R_START * 16 + 132)
#define R_READY_KEY_ACOUSTIC_ENERGY_ADD_UP						(R_START * 16 + 133)
#define R_READY_KEY_ACOUSTIC_ENERGY_DEC_DOWN					(R_START * 16 + 134)
#define R_READY_KEY_ACOUSTIC_ENERGY_DEC_UP						(R_START * 16 + 135)
#define R_READY_KEY_ACOUSTIC_TIME_ADD_DOWN						(R_START * 16 + 136)
#define R_READY_KEY_ACOUSTIC_TIME_ADD_UP							(R_START * 16 + 137)
#define R_READY_KEY_ACOUSTIC_TIME_DEC_DOWN						(R_START * 16 + 138)
#define R_READY_KEY_ACOUSTIC_TIME_DEC_UP							(R_START * 16 + 139)
/*****************************************************************************/
#define R_OPTION_KEY_ENTER_INFORMATION_DOWN						(R_START * 16 + 140)
#define R_OPTION_KEY_ENTER_OK_DOWN										(R_START * 16 + 141)
#define R_OPTION_KEY_ENTER_DIAGNOSIS_DOWN							(R_START * 16 + 142)
#define R_OPTION_KEY_BEEM_VOLUME_ADD_DOWN							(R_START * 16 + 143)
#define R_OPTION_KEY_BEEM_VOLUME_DEC_DOWN							(R_START * 16 + 144)
#define R_OPTION_KEY_LCD_BRG_ADD_DOWN									(R_START * 16 + 145)
#define R_OPTION_KEY_LCD_BRG_DEC_DOWN									(R_START * 16 + 146)
/*****************************************************************************/
#define R_INFORMATION_KEY_OK_DOWN											(R_START * 16 + 150)
#define R_INFORMATION_KEY_OK_UP												(R_START * 16 + 151)
/*****************************************************************************/
#define R_SCHEME_KEY_RENAME_DOWN											(R_START * 16 + 160)
#define R_SCHEME_KEY_OK_DOWN													(R_START * 16 + 161)
#define R_SCHEME_KEY_SCHEME_SELECT_0_DOWN							(R_START * 16 + 162)		
#define R_SCHEME_KEY_SCHEME_SELECT_1_DOWN							(R_START * 16 + 163)
#define R_SCHEME_KEY_SCHEME_SELECT_2_DOWN							(R_START * 16 + 164)
#define R_SCHEME_KEY_SCHEME_SELECT_3_DOWN							(R_START * 16 + 165)
#define R_SCHEME_KEY_SCHEME_SELECT_4_DOWN							(R_START * 16 + 166)
#define R_SCHEME_KEY_SCHEME_SELECT_5_DOWN							(R_START * 16 + 167)
#define R_SCHEME_KEY_SCHEME_SELECT_6_DOWN							(R_START * 16 + 168)
#define R_SCHEME_KEY_SCHEME_SELECT_7_DOWN							(R_START * 16 + 169)
#define R_SCHEME_KEY_SCHEME_SELECT_8_DOWN							(R_START * 16 + 170)
#define R_SCHEME_KEY_SCHEME_SELECT_9_DOWN							(R_START * 16 + 171)
#define R_SCHEME_KEY_SCHEME_SELECT_10_DOWN						(R_START * 16 + 172)
#define R_SCHEME_KEY_SCHEME_SELECT_11_DOWN						(R_START * 16 + 173)
#define R_SCHEME_KEY_SCHEME_SELECT_12_DOWN						(R_START * 16 + 174)
#define R_SCHEME_KEY_SCHEME_SELECT_13_DOWN						(R_START * 16 + 175)
#define R_SCHEME_KEY_SCHEME_SELECT_14_DOWN						(R_START * 16 + 176)
#define R_SCHEME_KEY_SCHEME_SELECT_15_DOWN						(R_START * 16 + 177)
#define R_SCHEME_KEY_SCHEME_SELECT_16_DOWN						(R_START * 16 + 178)
#define R_SCHEME_KEY_SCHEME_SELECT_17_DOWN						(R_START * 16 + 179)
#define R_SCHEME_KEY_SCHEME_SELECT_18_DOWN						(R_START * 16 + 180)
#define R_SCHEME_KEY_SCHEME_SELECT_19_DOWN						(R_START * 16 + 181)
#define R_SCHEME_KEY_SCHEME_SELECT_20_DOWN						(R_START * 16 + 182)
#define R_SCHEME_KEY_SCHEME_SELECT_21_DOWN						(R_START * 16 + 183)
#define R_SCHEME_KEY_SCHEME_SELECT_22_DOWN						(R_START * 16 + 184)
#define R_SCHEME_KEY_SCHEME_SELECT_23_DOWN						(R_START * 16 + 185)
#define R_SCHEME_KEY_SCHEME_SELECT_24_DOWN						(R_START * 16 + 186)
#define R_SCHEME_KEY_SCHEME_SELECT_25_DOWN						(R_START * 16 + 187)
#define R_SCHEME_KEY_SCHEME_SELECT_26_DOWN						(R_START * 16 + 188)
#define R_SCHEME_KEY_SCHEME_SELECT_27_DOWN						(R_START * 16 + 189)
#define R_SCHEME_KEY_SCHEME_SELECT_28_DOWN						(R_START * 16 + 190)
#define R_SCHEME_KEY_SCHEME_SELECT_29_DOWN						(R_START * 16 + 191)
#define R_SCHEME_KEY_SCHEME_SELECT_30_DOWN						(R_START * 16 + 192)
#define R_SCHEME_KEY_SCHEME_SELECT_31_DOWN						(R_START * 16 + 193)
#define R_SCHEME_KEY_NEXT_SCHEME											(R_START * 16 + 194)
#define R_SCHEME_KEY_LAST_SCHEME											(R_START * 16 + 195)
/*****************************************************************************/
#define R_DIAGNOSIS_OK_DOWN														(R_START * 16 + 200)
#define R_DIAGNOSIS_OK_UP															(R_START * 16 + 201)
#define R_DIAGNOSIS_GOTO_RAW_DOWN											(R_START * 16 + 202)
#define R_DIAGNOSIS_GOTO_RAW_UP												(R_START * 16 + 203)
/*****************************************************************************/
#define R_DIAGNOSIS_RAW_RETURN_DOWN										(R_START * 16 + 210)
#define R_DIAGNOSIS_RAW_RETURN_UP											(R_START * 16 + 211)
/*****************************************************************************/
#define R_RENAME_KEY_ENTER_DOWN												(R_START * 16 + 220)
#define R_RENAME_KEY_EXIT_DOWN												(R_START * 16 + 221)
#define R_RENAME_TEXTDISPLAY_READ_DONE								(R_START * 16 + 222)
/*****************************************************************************/
#define MR_FOOSWITCH_HAND_SWITCH											(MR_START * 16 + 10)//脚踏HandSwitch 脉冲控制
#define MR_BEEP_TONE																	(MR_START * 16 + 11)//蜂鸣器模式 0:SYNC 1:BEEP
/*****************************************************************************/
#define T100MS_HMI_POWERUP_DELAY											0//HMI启动复位延时
#define T100MS_ENTER_PASSCODE_DELAY										1
#define T100MS_READY_BEEM_DELAY												2//进入READY状态后蜂鸣器响延迟
#define T100MS_PULSE_BEEM_DELAY												3//脉冲模式蜂鸣器延迟
/*****************************************************************************/
#define T10MS_POSWIDTH_ADD_KEYDOWN_DELAY							0
#define T10MS_POSWIDTH_DEC_KEYDOWN_DELAY							1
#define T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY							2
#define T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY							3
#define T10MS_TIMES_ADD_KEYDOWN_DELAY									4
#define T10MS_TIMES_DEC_KEYDOWN_DELAY									5
#define T10MS_GROUP_OFF_ADD_KEYDOWN_DELAY							6
#define T10MS_GROUP_OFF_DEC_KEYDOWN_DELAY							7
#define T10MS_ACOUSTIC_ENERGY_ADD_KEYDOWN_DELAY				8
#define T10MS_ACOUSTIC_ENERGY_DEC_KEYDOWN_DELAY				9
#define T10MS_ACOUSTIC_TIME_ADD_KEYDOWN_DELAY					10
#define T10MS_ACOUSTIC_TIME_DEC_KEYDOWN_DELAY					11	
/*****************************************************************************/
#endif






