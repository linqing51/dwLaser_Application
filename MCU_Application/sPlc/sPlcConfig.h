#ifndef __SPLCCONFIG_H__
#define __SPLCCONFIG_H__
/*****************************************************************************/
#define CONFIG_DEBUG									0//使能调试
#if CONFIG_DEBUG == 1
#define CONFIG_EPROM_DEBUG								0
#define CONFIG_DEBUG_CONSOLE							0//
#else
#define CONFIG_EPROM_DEBUG								0
#define CONFIG_DEBUG_CONSOLE							0//
#endif
/*****************************************************************************/
#define CONFIG_UART0_BAUDRATE									115200//串口0 波特率
#define CONFIG_UART1_BAUDRATE									115200//串口1 波特率
/*****************************************************************************/
#define CONFIG_SPLC_USING_I2C0									1//使能I2C0
#define CONFIG_SPLC_USING_I2C1									1//使能I2C1
#define CONFIG_SPLC_USING_I2C2									1//使能I2C2
#define CONFIG_SPLC_USING_I2C3									1//使能I2C3
/*****************************************************************************/
#define CONFIG_I2C0_FREQ 										1            
#define CONFIG_I2C1_FREQ 										16
#define CONFIG_I2C2_FREQ 										16
#define CONFIG_I2C3_FREQ 										16
#define CONFIG_I2C_WAITACT_TIME									10
/*****************************************************************************/
#define CONFIG_EPROM_SIZE 										CONFIG_AT24C64_SIZE
#define	CONFIG_AT24C02_SIZE 									256
#define	CONFIG_AT24C04_SIZE  									512
#define	CONFIG_AT24C08_SIZE 									1024
#define	CONFIG_AT24C16_SIZE 									2048
#define	CONFIG_AT24C32_SIZE 									4096
#define	CONFIG_AT24C64_SIZE										8192
#define	CONFIG_AT24C128_SIZE 									16384
#define	CONFIG_AT24C256_SIZE 									32768
#define CONFIG_EPROM_ADDRESS									0x50
#define CONFIG_EPROM_FRAM										1//铁电存储体无写入等待
#define CONFIG_EPROM_PAGEWRITE									0//页写入
#define CONFIG_EPROM_NVRAM_START								0x0
#define CONFIG_EPROM_FDRAM_START								0x800//2048
/*****************************************************************************/
#define CONFIG_SPLC_USING_SPWM									0//使了软件PWM功能
/*****************************************************************************/
#define CONFIG_SPLC_FUNTEST										0//功能指令测试
/*****************************************************************************/
#define CONFIG_SPLC_ASSERT										1//检查地址范围
#define CONFIG_SPLC_DEV											0x0A01//设备号
#define CONFIG_SPLC_CLEAR_CODE									0xA58E
#define CONFIG_SOFTPLC_TICK										200L//5mS
#define CONFIG_INPUT_FILTER_TIME								1//输入数字滤波扫描周期 1mS * N
/*****************************************************************************/
#define CONFIG_SPLC_USING_IO_INPUT								1//输入IO刷新启用
/*****************************************************************************/
#define CONFIG_SPLC_USING_IO_OUTPUT								1//输出IO刷新启用
/*****************************************************************************/
#define CONFIG_SPLC_USING_EPROM									1//EPROM
#if CONFIG_SPLC_USING_EPROM == 1
#define CONFIG_SPLC_USING_CLEAR_NVRAM							0//启用清除NVRAM功能
#else
#define CONFIG_SPLC_USING_CLEAR_NVRAM							0//启用清除NVRAM功能
#endif
/*****************************************************************************/
#define CONFIG_SPLC_USING_UART0									1//UART 0串口启用
#define CONFIG_SPLC_USING_UART0_ISR								1
#define UART0													0

#define CONFIG_SPLC_USING_UART1									0//UART 1串口启用
#define CONFIG_SPLC_USING_UART1_ISR								0
#define UART1													1
/*****************************************************************************/
#define CONFIG_SPLC_USING_ADC									1//使能ADC模块
#define CONFIG_SPLC_ADC_FILTER_TAP								10//ADC位移滤波次数
#define CONFIG_SPLC_ADC_CHANNLE									9//ADC通道数
#define CONFIG_ADC_TEMP_SENSOR_SLOPE							2.86F
#define CONFIG_ADC_TEMP_SENSOR_OFFSET  							776L// Temp Sensor Offset in mV
#define CONFIG_ADC_INTERNAL_VREF     							2430L// ADC Voltage Reference (mV)
#define CONFIG_ADC_AMBIENT             							25L// Ambient temp in deg C
#define CONFIG_NTC_RS											3300L
#define CONFIG_NTC_B											3500L
#define CONFIG_NTC_RB											10000L
#define CONFIG_NTC_VREF											5000L
/*****************************************************************************/
#define CONFIG_SPLC_USING_DAC									1//是能DAC模块
#define CONFIG_MAX_DAC_CH0										0xFFFF
#define CONFIG_MIN_DAC_CH0										0
#define CONFIG_MAX_DAC_CH1										0xFFFF
#define CONFIG_MIN_DAC_CH1										0
#define CONFIG_MAX_DAC_CH2										0xFFFF
#define CONFIG_MIN_DAC_CH2										0
#define CONFIG_MAX_DAC_CH3										0xFFFF
#define CONFIG_MIN_DAC_CH3										0
#define CONFIG_MAX_DAC_CH4										0xFFFF
#define CONFIG_MIN_DAC_CH4										0
#define CONFIG_MAX_DAC_CH5										0xFFFF
#define CONFIG_MIN_DAC_CH5										0
#define CONFIG_MAX_DAC_CH6										0xFFFF
#define CONFIG_MIN_DAC_CH6										0
#define CONFIG_MAX_DAC_CH7										0xFFFF
#define CONFIG_MIN_DAC_CH7										0
/*****************************************************************************/
#define CONFIG_SPLC_USING_DK25L									0//SPLC使能NFC功能
#define CONFIG_SPLC_USING_DK25L_OVERTIME						500
#define CONFIG_DK25L_RXBUF_SIZE									16
#define CONFIG_DK25L_TXBUF_SIZE									16
/*****************************************************************************/
#define CONFIG_SPLC_USING_ROBATION								0//使能试用期功能
/*****************************************************************************/
#define CONFIG_SPLC_USING_LASER_TIMER							1
#define CONFIG_SPLC_USING_LASER_TIMER_TEST						0
/*****************************************************************************/
#define CONFIG_LASER_TIMER_TICK									1000//1mS
#define CONFIG_USING_USB_APP									0//USB应用
#define CONFIG_USING_DCHMI_APP									0//广东大彩人机交互应用
#define CONFIG_USING_BACKGROUND_APP								0//背景应用
/*****************************************************************************/
#define CONFIG_CHECK_DELAY_TIME									10
#define CONFIG_KEY_REPEAT_DELAY_TIME							50
#define CONFIG_STANDBY_BEEM_DELAY_TIME							20
/*****************************************************************************/
#define POWER_REAL_CH0_5P										200
#define POWER_REAL_CH0_10P										400
#define POWER_REAL_CH0_15P										600
#define POWER_REAL_CH0_20P										800
#define POWER_REAL_CH0_25P										1000
#define POWER_REAL_CH0_30P										1200
#define POWER_REAL_CH0_35P										1400
#define POWER_REAL_CH0_40P										1600
#define POWER_REAL_CH0_45P										1800
#define POWER_REAL_CH0_50P										2000
#define POWER_REAL_CH0_55P										2200
#define POWER_REAL_CH0_60P										2400
#define POWER_REAL_CH0_65P										2600
#define POWER_REAL_CH0_70P										2800
#define POWER_REAL_CH0_75P										3000
#define POWER_REAL_CH0_80P										3200
#define POWER_REAL_CH0_85P										3400
#define POWER_REAL_CH0_90P										3600
#define POWER_REAL_CH0_95P										3800
#define POWER_REAL_CH0_100P										4000
/*****************************************************************************/
#define POWER_REAL_CH1_5P										150
#define POWER_REAL_CH1_10P										300
#define POWER_REAL_CH1_15P										450
#define POWER_REAL_CH1_20P										800
#define POWER_REAL_CH1_25P										1000
#define POWER_REAL_CH1_30P										1200
#define POWER_REAL_CH1_35P										1400
#define POWER_REAL_CH1_40P										1600
#define POWER_REAL_CH1_45P										1800
#define POWER_REAL_CH1_50P										2000
#define POWER_REAL_CH1_55P										2200
#define POWER_REAL_CH1_60P										2400
#define POWER_REAL_CH1_65P										2600
#define POWER_REAL_CH1_70P										2800
#define POWER_REAL_CH1_75P										3000
#define POWER_REAL_CH1_80P										3200
#define POWER_REAL_CH1_85P										3400
#define POWER_REAL_CH1_90P										3600
#define POWER_REAL_CH1_95P										3800
#define POWER_REAL_CH1_100P										4000
/*****************************************************************************/
#define POWER_REAL_CH2_5P										150
#define POWER_REAL_CH2_10P										300
#define POWER_REAL_CH2_15P										450
#define POWER_REAL_CH2_20P										800
#define POWER_REAL_CH2_25P										1000
#define POWER_REAL_CH2_30P										1200
#define POWER_REAL_CH2_35P										1400
#define POWER_REAL_CH2_40P										1600
#define POWER_REAL_CH2_45P										1800
#define POWER_REAL_CH2_50P										2000
#define POWER_REAL_CH2_55P										2200
#define POWER_REAL_CH2_60P										2400
#define POWER_REAL_CH2_65P										2600
#define POWER_REAL_CH2_70P										2800
#define POWER_REAL_CH2_75P										3000
#define POWER_REAL_CH2_80P										3200
#define POWER_REAL_CH2_85P										3400
#define POWER_REAL_CH2_90P										3600
#define POWER_REAL_CH2_95P										3800
#define POWER_REAL_CH2_100P										4000
/*****************************************************************************/
#define POWER_REAL_CH3_5P										150
#define POWER_REAL_CH3_10P										300
#define POWER_REAL_CH3_15P										450
#define POWER_REAL_CH3_20P										800
#define POWER_REAL_CH3_25P										1000
#define POWER_REAL_CH3_30P										1200
#define POWER_REAL_CH3_35P										1400
#define POWER_REAL_CH3_40P										1600
#define POWER_REAL_CH3_45P										1800
#define POWER_REAL_CH3_50P										2000
#define POWER_REAL_CH3_55P										2200
#define POWER_REAL_CH3_60P										2400
#define POWER_REAL_CH3_65P										2600
#define POWER_REAL_CH3_70P										2800
#define POWER_REAL_CH3_75P										3000
#define POWER_REAL_CH3_80P										3200
#define POWER_REAL_CH3_85P										3400
#define POWER_REAL_CH3_90P										3600
#define POWER_REAL_CH3_95P										3800
#define POWER_REAL_CH3_100P										4000
/*****************************************************************************/
#define CONFIG_SPLC_USING_NFC									0
/*****************************************************************************/
//线圈 保持 16 * 32 = 512 
#define MR_START												0
#define MR_END   												31
//数据寄存器 保持 2048
#define DM_START												32
#define DM_END													2079
//线圈寄存器 非保持 16 * 32 = 512
#define R_START													2080
#define R_END													2111						
//数据寄存器 非保持 512
#define EM_START												2112
#define EM_END													2623
//延时线圈
//1MS  16 * 4 = 64
#define T_1MS_START												2624
#define T_1MS_END												2627
//10MS 16 * 4 = 64
#define T_10MS_START											2628
#define T_10MS_END												2631
//100MS 16 * 4 = 64
#define T_100MS_START											2632
#define T_100MS_END												2635
//延时器使能
//1MS  16 * 4 = 64
#define T_1MS_ENA_START											2636
#define T_1MS_ENA_END											2639
//10MS 16 * 4 = 64
#define T_10MS_ENA_START										2640
#define T_10MS_ENA_END											2643
//100MS 16 * 4 = 64
#define T_100MS_ENA_START										2644
#define T_100MS_ENA_END											2647
//延时计时器
//1MS  16 * 4 = 64
#define TD_1MS_START											2648
#define TD_1MS_END												2711
//10MS 16 * 4 = 64
#define TD_10MS_START											2712											
#define TD_10MS_END												2775
//100MS 16 * 4 = 64
#define TD_100MS_START											2776
#define TD_100MS_END											2839
//输入位寄存器 16 * 8 = 128
#define X_START													2840
#define X_END													2847
//输出位寄存器 16 * 8 = 128
#define Y_START													2848
#define Y_END													2855
//特殊寄存器 64
#define SPREG_START												2856
#define SPREG_END												2919
//特殊线圈 16 * 8 = 128
#define SPCOIL_START											2920
#define SPCOIL_END												2927
//临时寄存器 64
#define TM_START												2928
#define TM_END													2991
/*****************************************************************************/
#define CONFIG_NVRAM_SIZE 										(TM_END + 1)
/*****************************************************************************/
//存档寄存器
#define FD_START												0
#define FD_END													1023
/*****************************************************************************/
#define CONFIG_FDRAM_SIZE										(FD_END + 1)
/*****************************************************************************/
#define SPCOIL_ON												(SPCOIL_START * 16 + 0)//长通线圈
#define SPCOIL_START_UP											(SPCOIL_START * 16 + 1)//初次上电
#define SPCOIL_PS10MS											(SPCOIL_START * 16 + 2)//10mS
#define SPCOIL_PS50MS											(SPCOIL_START * 16 + 3)//50mS
#define SPCOIL_PS100MS											(SPCOIL_START * 16 + 4)//100mS
#define SPCOIL_PS1000MS											(SPCOIL_START * 16 + 5)//1000mS
#define SPCOIL_MODBUS_S0_ERROR									(SPCOIL_START * 16 + 6)//Modbus Slave->Uart0 错误
#define SPCOIL_NVRAM_FAIL										(SPCOIL_START * 16 + 7)//NVRAM校验码错误
#define SPCOIL_WATCHDOG_OVERFLOW								(SPCOIL_START * 16 + 8)//看门狗溢出
/*****************************************************************************/
#define SPCOIL_SPWM_OUT_0										(SPCOIL_START * 16 + 34)//SPWM0输出状态
#define SPCOIL_SPWM_RESET_0										(SPCOIL_START * 16 + 35)//SPWM0复位
#define SPCOIL_SPWM_OUT_1										(SPCOIL_START * 16 + 36)//SPWM1输出状态
#define SPCOIL_SPWM_RESET_1										(SPCOIL_START * 16 + 37)//SPWM1复位
#define SPCOIL_SPWM_OUT_2										(SPCOIL_START * 16 + 38)//SPWM2输出状态
#define SPCOIL_SPWM_RESET_2										(SPCOIL_START * 16 + 39)//SPWM2复位
#define SPCOIL_SPWM_OUT_3										(SPCOIL_START * 16 + 40)//SPWM3输出状态
#define SPCOIL_SPWM_RESET_3										(SPCOIL_START * 16 + 41)//SPWM3复位
/*****************************************************************************/
#define SPCOIL_DK25L_INIT_FAIL									(SPCOIL_START * 16 + 51)//NFC模块初始化失败
#define SPCOIL_LASER_DRIVER_INIT_FAIL							(SPCOIL_START * 16 + 53)//激光驱动器初始化失败
#define SPCOIL_WIRELESS_FOOTCONTROL_INIT_FAIL					(SPCOIL_START * 16 + 56)//无线脚踏初始化失败
#define SPCOIL_PROBATION_INIT_FAIL								(SPCOIL_START * 16 + 57)//试用期初始化失败
/*****************************************************************************/
#define SPCOIL_DK25L_RXCMD_DONE									(SPCOIL_START * 16 + 70)//接收指令完成
#define SPCOIL_DK25L_RXCMD_DOING								(SPCOIL_START * 16 + 71)//接收指令进行中
#define SPCOIL_DK25L_RXCMD_OVERFLOW								(SPCOIL_START * 16 + 72)//接收指令溢出
#define SPCOIL_DK25L_RXCMD_ERROR								(SPCOIL_START * 16 + 73)//接收指错误
#define SPCOIL_DK25L_TXCMD_DONE									(SPCOIL_START * 16 + 74)//写指令完成
#define SPCOIL_DK25L_TXCMD_DOING								(SPCOIL_START * 16 + 75)//写指令进行中
#define SPCOIL_DK25L_TXCMD_OVERFLOW								(SPCOIL_START * 16 + 76)//写指令溢出
#define SPCOIL_DK25L_TXCMD_ERROR								(SPCOIL_START * 16 + 77)//写指令错误
/*****************************************************************************/
#define SPREG_CLEAR_NVRAM										(SPREG_START + 0)//清除NVRAM后重新启动
/*****************************************************************************/
#define SPREG_ADC_0												(SPREG_START + 1)//ADC0采集值 PD0
#define SPREG_ADC_1												(SPREG_START + 2)//ADC1采集值 PD1
#define SPREG_ADC_2												(SPREG_START + 3)//ADC2采集值 NTC0
#define SPREG_ADC_3												(SPREG_START + 4)//ADC3采集值 NTC1
#define SPREG_ADC_4												(SPREG_START + 5)//ADC4采集值 ISMON0
#define SPREG_ADC_5												(SPREG_START + 6)//ADC5采集值 IVINMON0
#define SPREG_ADC_6												(SPREG_START + 7)//ADC6采集值 ISMON1
#define SPREG_ADC_7												(SPREG_START + 8)//ADC7采集值 IVINMON1
#define SPREG_ADC_8												(SPREG_START + 9)//ADC8采集值 Temperature Sensor

#define SPREG_DAC_0												(SPREG_START + 10)//DAC0设定值 LSET0
#define SPREG_DAC_1												(SPREG_START + 11)//DAC1设定值 LSET1
#define SPREG_DAC_2												(SPREG_START + 12)//DAC2设定值 LSET2
#define SPREG_DAC_3												(SPREG_START + 13)//DAC3设定值 LSET3
#define SPREG_DAC_4												(SPREG_START + 14)//DAC3设定值 LSET4
#define SPREG_DAC_5												(SPREG_START + 15)//DAC3设定值 LSET5
#define SPREG_DAC_6												(SPREG_START + 16)//DAC3设定值 LSET6
#define SPREG_DAC_7												(SPREG_START + 17)//DAC3设定值 LSET7
/*****************************************************************************/
#define SPREG_SPWM_POS_0										(SPREG_START + 20)//软件PWM0正脉宽设置
#define SPREG_SPWM_POS_SHADOW_0									(SPREG_START + 21)//软件PWM0正脉宽阴影
#define SPREG_SPWM_CYCLE_0										(SPREG_START + 22)//软件PWM0周期设置
#define SPREG_SPWM_CYCLE_SHADOW_0								(SPREG_START + 23)//软件PWM0周期阴影
#define SPREG_SPWM_COUNTER_0									(SPREG_START + 24)//软件PWM0计数器
#define SPREG_SPWM_POS_1										(SPREG_START + 25)//软件PWM1正脉宽设置
#define SPREG_SPWM_POS_SHADOW_1									(SPREG_START + 26)//软件PWM1正脉宽阴影
#define SPREG_SPWM_CYCLE_1										(SPREG_START + 27)//软件PWM1周期设置
#define SPREG_SPWM_CYCLE_SHADOW_1								(SPREG_START + 28)//软件PWM1周期阴影
#define SPREG_SPWM_COUNTER_1									(SPREG_START + 29)//软件PWM1计数器
#define SPREG_SPWM_POS_2										(SPREG_START + 30)//软件PWM2正脉宽设置
#define SPREG_SPWM_POS_SHADOW_2									(SPREG_START + 31)//软件PWM2正脉宽阴影
#define SPREG_SPWM_CYCLE_2										(SPREG_START + 32)//软件PWM2周期设置
#define SPREG_SPWM_CYCLE_SHADOW_2								(SPREG_START + 33)//软件PWM2周期阴影
#define SPREG_SPWM_COUNTER_2									(SPREG_START + 34)//软件PWM2计数器
#define SPREG_SPWM_POS_3										(SPREG_START + 35)//软件PWM3正脉宽设置
#define SPREG_SPWM_POS_SHADOW_3									(SPREG_START + 36)//软件PWM3正脉宽阴影
#define SPREG_SPWM_CYCLE_3										(SPREG_START + 37)//软件PWM3周期设置
#define SPREG_SPWM_CYCLE_SHADOW_3								(SPREG_START + 38)//软件PWM3周期阴影
#define SPREG_SPWM_COUNTER_3									(SPREG_START + 39)//软件PWM3计数器
/*****************************************************************************/
#define SPREG_DK25L_VER											(SPREG_START + 50)//DK25L NFC模块版本
/*****************************************************************************/
#define SPREG_IDENTITY											(SPREG_END + 0)//平台ID号
/*****************************************************************************/
#endif
