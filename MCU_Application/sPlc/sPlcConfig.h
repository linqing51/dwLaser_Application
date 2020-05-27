#ifndef __SPLCCONFIG_H__
#define __SPLCCONFIG_H__
/*****************************************************************************/
#define CMD_MUSIC_PLAY											0x01
#define CMD_MUSIC_SUSPEND										0x02
#define CMD_MUSIC_RESUME										0x03
#define CMD_MUSIC_STOP											0x04
/*****************************************************************************/
#define CONFIG_DEBUG_SERIAL_PORT								uart1
#define CONFIG_DEBUG_CHARGE										0//调试充电
#define CONFIG_DEBUG_DAC										0//调试DAC
#define CONFIG_DEBUB_ADC										0//调试ADC
#define CONFIG_DEBUG_EPROM										0//调试EPROM
#define CONFIG_DEBUG_IO											0//调试输入输出IO
#define CONFIG_DEBUG_BEEM										0//调试蜂鸣器
#define CONFIG_DEBUG_MUSIC										0//调试LCD音乐
#define CONFIG_DEBUG_APP										1
/*****************************************************************************/
#define CONFIG_SPLC_USING_MUSIC									1//使能LCD自带音乐播放						
#define CONFIG_SPLC_USING_BEEM									1//使能板载蜂鸣器
#define CONFIG_SPLC_DEFAULT_BEEM_FREQ							4000L//蜂鸣器默认频率
#define CONFIG_SPLC_DEFAULT_BEEM_DUTYCYCLE						127//蜂鸣器默认占空比
/*****************************************************************************/
#define CONFIG_SPLC_USING_LEDAIM								1	
#define CONFIG_SPLC_LEDAIM_FREQ									4000L//LED和AIM闪烁频率
#define CONFIG_SPLC_RLED_DEFAULT_DUTYCYCLE						60//红灯亮度
#define CONFIG_SPLC_GLED_DEFAULT_DUTYCYCLE						60//绿灯亮度
#define CONFIG_SPLC_BLED_DEFAULT_DUTYCYCLE						60//蓝灯亮度
/*****************************************************************************/
#define CONFIG_SPLC_USING_SPWM									1//使了软件PWM功能
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
#define CONFIG_SPLC_USING_EPROM_TEST							1//EPROM自检
#define CONFIG_SPLC_USING_CLEAR_NVRAM							1//启用清除NVRAM功能
#define CONFIG_EPROM_SIZE 										CONFIG_AT24C64_SIZE
#define	CONFIG_AT24C02_SIZE 									256
#define	CONFIG_AT24C04_SIZE  									512
#define	CONFIG_AT24C08_SIZE 									1024
#define	CONFIG_AT24C16_SIZE 									2048
#define	CONFIG_AT24C32_SIZE 									4096
#define	CONFIG_AT24C64_SIZE										8192
#define	CONFIG_AT24C128_SIZE 									16384
#define	CONFIG_AT24C256_SIZE 									32768
#define CONFIG_EPROM_ADDRESS									0x50//EPROM I2C地址
#define CONFIG_EPROM_WIRTE_DELAY								10//EPROM写入时间 10mS
#define CONFIG_EPROM_TIMEOUT									1000//EPROM读写超时
#define CONFIG_EPROM_PAGE_SIZE									32//EPROM 页大小
#define CONFIG_EPROM_NVRAM_START								0x0
#define CONFIG_EPROM_FDRAM_START								0x800//2048
/*****************************************************************************/
#define CONFIG_SPLC_USING_ADC									1//使能ADC模块
#define CONFIG_SPLC_ADC_CHANNEL									10//ADC采集通道
#define CONFIG_SPLC_ADC_AVERAGE_NUM								8//ADC平均值次数
#define CONFIG_ADC_DMA_BUFFER_SIZE								(CONFIG_SPLC_ADC_CHANNEL * CONFIG_SPLC_ADC_AVERAGE_NUM)//ADC DMA采集缓冲
#define CONFIG_ADC_AMBIENT             							25L// Ambient temp in deg C
#define CONFIG_ADC_INTERNAL_VREF     							3300L// ADC Voltage Reference (mV)
#define CONFIG_NTC_RS											3300L
#define CONFIG_NTC_B											3500L
#define CONFIG_NTC_RB											10000L
#define CONFIG_NTC_VREF											3300L
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
#define CONFIG_SPLC_USING_LASER									1
#define CONFIG_SPLC_USING_LASER_TEST							1
/*****************************************************************************/
#define CONFIG_USING_DCHMI_APP									1//广东大彩人机交互应用
/*****************************************************************************/
#define CONFIG_CHECK_DELAY_TIME									10
#define CONFIG_KEY_REPEAT_DELAY_TIME							50
#define CONFIG_STANDBY_BEEM_DELAY_TIME							20
/*****************************************************************************/
#define CONFIG_APP_DIODE_HIGH_TEMP								400
#define CONFIG_APP_DIODE_LOW_TEMP								-100
#define CONFIG_APP_DRIVE_HIGH_TEMP								650
#define CONFIG_APP_ENVI_HIGH_TEMP								750
/*****************************************************************************/
#define CONFIG_USING_SINGLE_WAVE								0//单波长
#define CONFIG_USING_DUAL_WAVE									1//双波长
#define CONFIG_USING_TRIPE_WAVE									0//三波长
#define CONFIG_USING_QUAD_WAVE									0//四波长
#define CONFIG_USING_FIVE_WAVE									0//五波长
#define CONFIG_HMI_SCHEME_NUM									32//方案数
#define CONFIG_HMI_DEFAULT_PASSSWORD0							0x3235//默认密码
#define CONFIG_HMI_DEFAULT_PASSSWORD1							0x3830//默认密码
#define CONFIG_SCHEME_NAME_SIZE									22//12*2
//光斑直径定义
#define DERMA_SPOT_SIZE_0MM5									0x100A//光斑直径0.5					
#define DERMA_SPOT_SIZE_1MM0									0x200B//光斑直径1.0
#define DERMA_SPOT_SIZE_2MM0									0x300C//光斑直径2.0
#define DERMA_SPOT_SIZE_3MM0									0x400D//光斑直径3.0

#define CONFIG_MAX_LASER_DAC_CH0								0xFFF//
#define CONFIG_MAX_LASER_DAC_CH1								0xFFF//
#define CONFIG_MAX_LASER_DAC_CH2								0xFFF
#define CONFIG_MAX_LASER_DAC_CH3								0xFFF

#define CONFIG_MAX_LASERPOWER_CH0								300//通道0最大激光功率
#define CONFIG_MAX_LASERPOWER_CH1								150//通道1最大激光功率
#define CONFIG_MAX_LASERPOWER_CH2								100//通道2最大激光功率
#define CONFIG_MAX_LASERPOWER_CH3								100//通道3最大激光功率

#define CONFIG_MIN_LASERPOWER_CH0								0//通道0最小激光功率
#define CONFIG_MIN_LASERPOWER_CH1								0//通道1最小激光功率
#define CONFIG_MIN_LASERPOWER_CH2								0//通道2最大激光功率
#define CONFIG_MIN_LASERPOWER_CH3								0//通道3最大激光功率

#define CONFIG_MAX_LASER_POSWIDTH								10000
#define CONFIG_MIN_LASER_POSWIDTH								1
#define CONFIG_MAX_LASER_NEGWIDTH								10000
#define CONFIG_MIN_LASER_NEGWIDTH								1
#define CONFIG_MAX_LASER_TIMES									20//最大可计数脉冲数
#define CONFIG_MIN_LASER_TIMES									1//最小可计数脉冲数
#define CONFIG_MAX_LASER_GROUP_OFF								1000
#define CONFIG_MIN_LASER_GROUP_OFF								10
#define CONFIG_MAX_LASER_ENERGY_INTERVAL						200
#define CONFIG_MIN_LASER_ENERGY_INTERVAL						40
#define CONFIG_STEP_LASER_ENERGY_INTERVAL						10
#define CONFIG_BEEM_ENERGY_INTERVAL_TIME						250//变音持续时间

#define CONFIG_MAX_AIM_BRG										100//红光最大调光占空比
#define CONFIG_MIN_AIM_BRG										1//红光最小调光占空比
#define CONFIG_MAX_MUSIC_VOLUME									100//蜂鸣器最大音量
#define CONFIG_MIN_MUSIC_VOLUME									1//蜂鸣器最小音量
#define CONFIG_MAX_LCD_BRG										100//屏幕亮度最大值
#define CONFIG_MIN_LCD_BRG										1//屏幕亮度最小值
#define CONFIG_COOL_SET_TEMP									280//冷却温度
#define CONFIG_COOL_DIFF_TEMP									20//冷却温度变化范围
//功率设定校正系数
#define LASER_CH0_NOTES_INTERCEPT								393.7F	
#define LASER_CH0_NOTES_B1										12.34F
#define LASER_CH0_NOTES_B2										0.0F
#define LASER_CH0_NOTES_B3										0.0F

#define LASER_CH1_NOTES_INTERCEPT								-10.0F	
#define LASER_CH1_NOTES_B1										4.096F
#define LASER_CH1_NOTES_B2										0.0
#define LASER_CH1_NOTES_B3										0.0

#define LASER_CH2_NOTES_INTERCEPT								-0.16355			
#define LASER_CH2_NOTES_B1										1.82066E-5
#define LASER_CH2_NOTES_B2										-2.75859E-13
#define LASER_CH2_NOTES_B3										7.12301E-20

#define LASER_CH3_NOTES_INTERCEPT								-0.16355			
#define LASER_CH3_NOTES_B1										1.82066E-5
#define LASER_CH3_NOTES_B2										-2.75859E-13
#define LASER_CH3_NOTES_B3										7.12301E-20

#define LASER_CH4_NOTES_INTERCEPT								-0.16355			
#define LASER_CH4_NOTES_B1										1.82066E-5
#define LASER_CH4_NOTES_B2										-2.75859E-13
#define LASER_CH4_NOTES_B3										7.12301E-20
//功率显示校正系数
#define PD_NOTES_INTERCEPT										-0.16355			
#define PD_NOTES_B1												1.82066E-5
#define PD_NOTES_B2												-2.75859E-13
#define PD_NOTES_B3												7.12301E-20
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
#define FD_END													2047
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
#define SPCOIL_BEEM_ENABLE										(SPCOIL_START * 16 + 10)//蜂鸣器使能
#define SPCOIL_BEEM_BUSY										(SPCOIL_START * 16 + 11)//蜂鸣器工作状态
#define SPCOIL_AIM_ENABEL										(SPCOIL_START * 16 + 12)//瞄准光使能
#define SPCOIL_AIM_BUSY											(SPCOIL_START * 16 + 13)//瞄准光工作状态
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
#define SPREG_MUSIC_VOLUME										(SPREG_START + 40)//音乐播放音量 0-100%
#define SPREG_PLAYING_MUSIC_ID									(SPREG_START + 41)//当前播放音乐ID
#define SPREG_NEXT_MUSIC_ID										(SPREG_START + 42)//下一个播放音乐ID
#define SPREG_CONTROL_MUSIC										(SPREG_START + 43)//音乐播放控制寄存器
/*****************************************************************************/
#define SPREG_RED_LED_DUTYCYCLE									(SPREG_START + 45)//红色LED亮度->故障 0-100%
#define SPREG_GREEN_LED_DUTYCYCLE								(SPREG_START + 46)//绿色LED亮度->电源 0-100%
#define SPREG_BLUE_LED_DUTYCYCLE								(SPREG_START + 47)//蓝色LED亮度->激光指示 0-100%
#define SPREG_AIM_DUTYCYCLE										(SPREG_START + 48)//瞄准光亮度->650红激光 0-100%
/*****************************************************************************/
#define SPREG_BEEM_DUTYCYCLE									(SPREG_START + 50)//蜂鸣器占空比 0-100%
#define SPREG_BEEM_FREQ											(SPREG_START + 51)//蜂鸣器频率
#define SPREG_BEEM_MODE											(SPREG_START + 52)//蜂鸣器模式
#define SPREG_BEEM_COUNTER										(SPREG_START + 53)//蜂鸣器计时器
/*****************************************************************************/
#define SPREG_DK25L_VER											(SPREG_START + 55)//DK25L NFC模块版本
/*****************************************************************************/
#define SPREG_IDENTITY											(SPREG_END + 0)//平台ID号
/*****************************************************************************/
#define EM_LASER_SCHEME_NAME									(EM_START + 0)//方案名称
#define EM_LASER_SELECT											(EM_START + 46)//通道选择
#define EM_LASER_PULSE_MODE										(EM_START + 47)//脉冲模式
#define EM_LASER_POWER_CH0										(EM_START + 48)//通道0功率
#define EM_LASER_POWER_CH1										(EM_START + 49)//通道1功率
#define EM_LASER_POWER_CH2										(EM_START + 50)//通道2功率
#define EM_LASER_POWER_CH3										(EM_START + 51)//通道3功率
#define EM_LASER_POWER_CH4										(EM_START + 52)//通道4功率
#define EM_LASER_SP_POSWIDTH									(EM_START + 53)//单脉冲正脉宽
#define EM_LASER_MP_POSWIDTH									(EM_START + 54)//多脉冲正脉宽
#define EM_LASER_MP_NEGWIDTH									(EM_START + 55)//多脉冲负脉宽
#define EM_LASER_GP_POSWIDTH									(EM_START + 56)//Group脉冲正脉宽
#define EM_LASER_GP_NEGWIDTH									(EM_START + 57)//Group脉冲负脉宽
#define EM_LASER_GP_TIMES										(EM_START + 58)//Group脉冲数
#define EM_LASER_GP_GROUP_OFF									(EM_START + 59)//Group脉冲间隔
#define EM_LASER_SIGNAL_ENERGY_INTERVAL							(EM_START + 60)//SIGNAL能量间隔
#define EM_LASER_DERMA_POSWIDTH									(EM_START + 61)//DERMA正脉宽
#define EM_LASER_DERMA_NEGWIDTH									(EM_START + 62)//DERMA负脉宽
#define EM_LASER_DERMA_SPOT_SIZE								(EM_START + 63)//DERMA光斑直径
/*****************************************************************************/
#define EM_LASER_AVERAGE_POWER									(EM_START + 61//当面模式平均功率
#define EM_LASER_FREQUENCY										(EM_START + 62)//当前模式频率
#define EM_LASER_DUTY_CYCLE										(EM_START + 63)//当前模式占空比 
/*****************************************************************************/
#define EM_DIODE_TEMP0											(EM_START + 64)//二极管温度0
#define EM_DIODE_TEMP1											(EM_START + 65)//二极管温度1
#define EM_DRIVE_TEMP											(EM_START + 66)//驱动器温度
#define EM_ENVI_TEMP											(EM_START + 67)//环境温度
#define EM_DIODE_HIGH_TEMP										(EM_START + 68)//二极管过热阈值
#define EM_DRIVE_HIGH_TEMP										(EM_START + 69)//驱动器过热阈值
#define EM_ENVI_HIGH_TEMP										(EM_START + 70)//环境过热阈值
#define EM_COOL_SET_TEMP										(EM_START + 71)//设定冷却温度
#define EM_COOL_DIFF_TEMP										(EM_START + 72)//设定冷却回差调节
/*****************************************************************************/				
#define EM_TOTAL_POWER											(EM_START + 80)//发射总功率
#define EM_HMI_OPERA_STEP										(EM_START +	81)//操作步骤								
#define EM_ERROR_CODE											(EM_START + 82)//错误码					
#define EM_SCHEME_NUM_TMP										(EM_START + 83)//待确认方案编号			
#define EM_DK25L_VER											(EM_START + 83)//DK25L模块版本
/*****************************************************************************/
#define EM_DC_PAGE												(EM_START + 90)//HMI页面编号 			
#define EM_DC_PASSCODE_INDEX									(EM_START + 91)//密码输入位索引		
#define EM_DC_NEW_PASSCODE0										(EM_START + 92)//输入新密码0			
#define EM_DC_NEW_PASSCODE1										(EM_START + 93)//输入新密码1			
#define EM_DC_NEW_PASSCODE2										(EM_START + 94)//输入新密码0			
#define EM_DC_NEW_PASSCODE3										(EM_START + 95)//输入新密码1			
#define EM_DC_DEFAULT_PASSCODE0									(EM_START + 96)//默认密码0				
#define EM_DC_DEFAULT_PASSCODE1									(EM_START + 97)//默认密码1				
#define EM_DC_DEFAULT_PASSCODE2									(EM_START + 98)//默认密码1	
#define EM_DC_DEFAULT_PASSCODE3									(EM_START + 99)//默认密码1				
#define EM_DC_DISPLAY_RELEASE_TIME								(EM_START + 100)//显示发射时间			
#define EM_DC_DISPLAY_RELEASE_ENERGY							(EM_START + 101)//显示发射能量
/*****************************************************************************/
#define FD_LASER_SCHEME_NAME									(FD_START +  0)//方案名称
#define FD_LASER_SELECT											(FD_START +  46)//通道选择
#define FD_LASER_PULSE_MODE										(FD_START +  47)//脉冲模式
#define FD_LASER_POWER_CH0										(FD_START +  48)//通道0功率
#define FD_LASER_POWER_CH1										(FD_START +  49)//通道1功率
#define FD_LASER_POWER_CH2										(FD_START +  50)//通道2功率
#define FD_LASER_POWER_CH3										(FD_START +  51)//通道3功率
#define FD_LASER_POWER_CH4										(FD_START +  52)//通道4功率
#define FD_LASER_SP_POSWIDTH									(FD_START +  53)//单脉冲正脉宽
#define FD_LASER_MP_POSWIDTH									(FD_START +  54)//多脉冲正脉宽
#define FD_LASER_MP_NEGWIDTH									(FD_START +  55)//多脉冲负脉宽
#define FD_LASER_GP_POSWIDTH									(FD_START +  56)//Group脉冲正脉宽
#define FD_LASER_GP_NEGWIDTH									(FD_START +  57)//Group脉冲负脉宽
#define FD_LASER_GP_TIMES										(FD_START +  58)//Group脉冲数
#define FD_LASER_GP_GROUP_OFF									(FD_START +  59)//Group脉冲间隔
#define FD_LASER_SIGNAL_ENERGY_INTERVAL							(FD_START +  60)//SIGNAL能量间隔
#define FD_LASER_DERMA_POSWIDTH									(FD_START +  61)//DERMA正脉宽
#define FD_LASER_DERMA_NEGWIDTH									(FD_START +  62)//DERMA负脉宽
#define FD_LASER_DERMA_SPOT_SIZE								(FD_START +  63)//DERMA光斑直径

#define FD_SCHEME_START_0										(FD_START +   0)//方案0存储区起始
#define FD_SCHEME_END_0											(FD_START +  63)//方案0存储区结束		

#define FD_SCHEME_START_1										(FD_START +  64)//方案1存储区起始		
#define FD_SCHEME_END_1											(FD_START +  127)//方案1存储区结束

#define FD_SCHEME_START_2										(FD_START +  128)//方案2存储区起始
#define FD_SCHEME_END_2											(FD_START +  191)//方案2存储区结束

#define FD_SCHEME_START_3										(FD_START +  192)//方案3存储区起始
#define FD_SCHEME_END_3											(FD_START +  255)//方案3存储区结束

#define FD_SCHEME_START_4										(FD_START +  256)//方案4存储区起始
#define FD_SCHEME_END_4											(FD_START +  319)//方案4存储区结束

#define FD_SCHEME_START_5										(FD_START +  320)//方案5存储区起始
#define FD_SCHEME_END_5											(FD_START +  383)//方案5存储区结束

#define FD_SCHEME_START_6										(FD_START +  384)//方案6存储区起始
#define FD_SCHEME_END_6											(FD_START +  447)//方案6存储区结束

#define FD_SCHEME_START_7										(FD_START +  448)//方案7存储区起始
#define FD_SCHEME_END_7											(FD_START +  511)//方案7存储区结束

#define FD_SCHEME_START_8										(FD_START +  512)//方案8存储区起始
#define FD_SCHEME_END_8											(FD_START +  575)//方案8存储区结束

#define FD_SCHEME_START_9										(FD_START +  576)//方案9存储区起始
#define FD_SCHEME_END_9											(FD_START +  639)//方案9存储区结束

#define FD_SCHEME_START_10										(FD_START +  640)//方案10存储区起始
#define FD_SCHEME_END_10										(FD_START +  703)//方案10存储区结束

#define FD_SCHEME_START_11										(FD_START +  704)//方案11存储区起始
#define FD_SCHEME_END_11										(FD_START +  767)//方案11存储区结束

#define FD_SCHEME_START_12										(FD_START +  768)//方案12存储区起始
#define FD_SCHEME_END_12										(FD_START +  831)//方案12存储区结束

#define FD_SCHEME_START_13										(FD_START +  832)//方案13存储区起始
#define FD_SCHEME_END_13										(FD_START +  895)//方案13存储区结束

#define FD_SCHEME_START_14										(FD_START +  896)//方案14存储区起始
#define FD_SCHEME_END_14										(FD_START +  959)//方案14存储区结束

#define FD_SCHEME_START_15										(FD_START +  960)//方案15存储区起始
#define FD_SCHEME_END_15										(FD_START + 1023)//方案15存储区结束
/*****************************************************************************/
#define FD_SCHEME_START_16										(FD_START + 1024)//方案16存储区起始
#define FD_SCHEME_END_16										(FD_START + 1087)//方案16存储区结束

#define FD_SCHEME_START_17										(FD_START + 1088)//方案17存储区起始
#define FD_SCHEME_END_17										(FD_START + 1151)//方案17存储区结束

#define FD_SCHEME_START_18										(FD_START + 1152)//方案18存储区起始
#define FD_SCHEME_END_18										(FD_START + 1215)//方案18存储区结束

#define FD_SCHEME_START_19										(FD_START + 1216)//方案19存储区起始
#define FD_SCHEME_END_19										(FD_START + 1279)//方案19存储区结束

#define FD_SCHEME_START_20										(FD_START + 1280)//方案20存储区起始
#define FD_SCHEME_END_20										(FD_START + 1343)//方案20存储区结束

#define FD_SCHEME_START_21										(FD_START + 1344)//方案21存储区起始
#define FD_SCHEME_END_21										(FD_START + 1407)//方案21存储区结束

#define FD_SCHEME_START_22										(FD_START + 1408)//方案22存储区起始
#define FD_SCHEME_END_22										(FD_START + 1471)//方案22存储区结束

#define FD_SCHEME_START_23										(FD_START + 1472)//方案23存储区起始
#define FD_SCHEME_END_23										(FD_START + 1535)//方案23存储区结束

#define FD_SCHEME_START_24										(FD_START + 1536)//方案24存储区起始
#define FD_SCHEME_END_24										(FD_START + 1599)//方案24存储区结束

#define FD_SCHEME_START_25										(FD_START + 1600)//方案25存储区起始
#define FD_SCHEME_END_25										(FD_START + 1663)//方案25存储区结束

#define FD_SCHEME_START_26										(FD_START + 1664)//方案26存储区起始
#define FD_SCHEME_END_26										(FD_START + 1727)//方案26存储区结束

#define FD_SCHEME_START_27										(FD_START + 1728)//方案27存储区起始
#define FD_SCHEME_END_27										(FD_START + 1791)//方案27存储区结束

#define FD_SCHEME_START_28										(FD_START + 1792)//方案28存储区起始
#define FD_SCHEME_END_28										(FD_START + 1855)//方案28存储区结束

#define FD_SCHEME_START_29										(FD_START + 1856)//方案29存储区起始
#define FD_SCHEME_END_29										(FD_START + 1919)//方案29存储区结束

#define FD_SCHEME_START_30										(FD_START + 1920)//方案30存储区起始
#define FD_SCHEME_END_30										(FD_START + 1983)//方案30存储区结束

#define FD_SCHEME_START_31										(FD_START + 1984)//方案31存储区起始
#define FD_SCHEME_END_31										(FD_START + 2047)//方案31存储区结束
/*****************************************************************************/
#define TMP_NAME_0												(TMP_START + 0)//临时名称储存区
#define TMP_NAME_1												(TMP_START + 15)//临时名称储存区
#define TMP_NAME_2												(TMP_START + 30)//临时名称储存区
#define TMP_NAME_3												(TMP_START + 45)//临时名称储存区
#define TMP_NAME_4												(TMP_START + 60)//临时名称储存区
#define TMP_NAME_5												(TMP_START + 75)//临时名称储存区
#define TMP_NAME_6												(TMP_START + 90)//临时名称储存区
#define TMP_NAME_7												(TMP_START + 105)//临时名称储存区
#define TMP_NAME_8												(TMP_START + 120)//临时名称储存区
#define TMP_NAME_9												(TMP_START + 135)//临时名称储存区
#define TMP_NAME_10												(TMP_START + 150)//临时名称储存区
#define TMP_NAME_11												(TMP_START + 165)//临时名称储存区
#define TMP_NAME_12												(TMP_START + 180)//临时名称储存区
#define TMP_NAME_13												(TMP_START + 195)//临时名称储存区
#define TMP_NAME_14												(TMP_START + 210)//临时名称储存区
#define TMP_NAME_15												(TMP_START + 225)//临时名称储存区
#define TMP_NAME_16												(TMP_START + 240)//临时名称储存区
#define TMP_NAME_17												(TMP_START + 255)//临时名称储存区
#define TMP_NAME_18												(TMP_START + 270)//临时名称储存区
#define TMP_NAME_19												(TMP_START + 285)//临时名称储存区
#define TMP_NAME_20												(TMP_START + 300)//临时名称储存区
#define TMP_NAME_21												(TMP_START + 315)//临时名称储存区
#define TMP_NAME_22												(TMP_START + 330)//临时名称储存区
#define TMP_NAME_23												(TMP_START + 345)//临时名称储存区
#define TMP_NAME_24												(TMP_START + 360)//临时名称储存区
#define TMP_NAME_25												(TMP_START + 375)//临时名称储存区
#define TMP_NAME_26												(TMP_START + 390)//临时名称储存区
#define TMP_NAME_27												(TMP_START + 405)//临时名称储存区
#define TMP_NAME_28												(TMP_START + 420)//临时名称储存区
#define TMP_NAME_29												(TMP_START + 435)//临时名称储存区
#define TMP_NAME_30												(TMP_START + 450)//临时名称储存区
#define TMP_NAME_31												(TMP_START + 465)//临时名称储存区

#define TMP_NAME_32												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_33												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_34												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_35												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_36												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_37												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_38												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_39												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_40												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_41												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_42												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_43												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_44												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_45												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_46												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_47												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_48												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_49												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_50												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_51												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_52												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_53												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_54												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_55												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_56												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_57												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_58												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_59												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_60												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_61												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_62												(TMP_START + 465)//临时名称储存区
#define TMP_NAME_63												(TMP_START + 465)//临时名称储存区
/*****************************************************************************/
#define DM_SCHEME_NUM											(DM_START + 0)//选择的方案编号 低8位方案号 高8位方案使能
#define DM_LANGUAGE												(DM_START + 1)//语言ID
#define DM_MUSIC_VOLUME											(DM_START + 2)//音乐音量 0-100%
#define DM_BEEM_VOLUME											(DM_START + 3)//蜂鸣器音量 0-100%
#define DM_AIM_BRG												(DM_START + 4)//指示激光亮度
#define DM_LCD_BRG												(DM_START + 5)//屏幕亮度
#define DM_LED_RED_BRG											(DM_START + 6)//红灯亮度
#define DM_LED_GREEN_BRG										(DM_START + 7)//绿灯亮度
#define DM_LED_BLUE_BRG											(DM_START + 8)//蓝灯亮度
#define DM_DC_OLD_PASSCODE0										(DM_START + 9)//屏旧密码0-1
#define DM_DC_OLD_PASSCODE1										(DM_START + 10)//屏旧密码2-3
#define DM_DC_OLD_PASSCODE2										(DM_START + 11)//屏旧密码0-1
#define DM_DC_OLD_PASSCODE3										(DM_START + 12)//屏旧密码2-3
/*****************************************************************************/
#define X_FOOTSWITCH_NC											(X_START * 16 + 1)//XIN0 脚踏常闭
#define X_ESTOP													(X_START * 16 + 0)//XIN1 紧急停止开关
#define X_FOOTSWITCH_NO											(X_START * 16 + 2)//XIN2 脚踏常开
#define X_INTERLOCK												(X_START * 16 + 3)//XIN0 安全连锁
#define X_FIBER_PROBE											(X_START * 16 + 7)//XIN6 光纤探测0
/*****************************************************************************/
#define Y_LED_POWERON											(Y_START * 16 + 0)//YOUT0 电源灯
#define Y_LED_EMIT												(Y_START * 16 + 1)//YOUT1 激光指示灯
#define Y_LED_ALARM												(Y_START * 16 + 2)//YOUT2 故障指示灯
#define Y_OUT3													(Y_START * 16 + 3)//YOUT3 保留
#define Y_OUT4													(Y_START * 16 + 4)//YOUT4 保留
#define Y_OUT5													(Y_START * 16 + 5)//YOUT5 保留
#define Y_OUT6													(Y_START * 16 + 6)//YOUT6 保留
#define Y_OUT7													(Y_START * 16 + 7)//YOUT7 保留
#define Y_FAN0													(Y_START * 16 + 8)//YOUT8 风扇开关0
#define Y_FAN1													(Y_START * 16 + 9)//YOUT9 风扇开关1
#define Y_TEC0													(Y_START * 16 + 10)//YOUT10 制冷开关0
#define Y_TEC1													(Y_START * 16 + 11)//YOUT11 制冷开关1
/*****************************************************************************/
#define R_FOOTSWITCH_NC											(R_START * 16 + 0)//脚踏常开
#define R_FOOTSWITCH_NO											(R_START * 16 + 0)//脚踏常闭
#define R_ESTOP													(R_START * 16 + 1)//
#define R_INTERLOCK												(R_START * 16 + 2)//
#define R_FIBER_PROBE											(R_START * 16 + 3)//
#define R_RFID_PASS												(R_START * 16 + 4)
#define R_DIODE_TEMP_HIGH										(R_START * 16 + 5)//通道0二极管高温标志
#define R_DIODE_TEMP_LOW										(R_START * 16 + 6)//通道0二极管高温标志
#define R_DRIVE_TEMP_HIGH										(R_START * 16 + 7)//驱动器高温标志
#define R_DRIVE_TEMP_LOW										(R_START * 16 + 8)//通道0二极管高温标志
#define R_ENVI_TEMP_HIGH										(R_START * 16 + 9)//环境温度标度
#define R_ENVI_TEMP_LOW											(R_START * 16 + 10)//通道0二极管高温标志
#define R_FAULT													(R_START * 16 + 11)//故障标志
#define R_FAN_ENABLE											(R_START * 16 + 12)//风扇使能
#define R_DISABLE_RFID											(R_START * 16 + 13)//屏蔽NFC检测
#define R_DISABLE_FIBER_PROBE									(R_START * 16 + 14)//屏蔽光纤探测
#define R_DISABLE_FAN_SPEED										(R_START * 16 + 15)//屏蔽风扇控制
#define R_CLEAR_EPROM											(R_START * 16 + 16)//完全清空EPROM
#define R_ENGINEER_MODE											(R_START * 16 + 17)//工程师模式
//HMI相关状态
#define R_DCHMI_RESET_REQ										(R_START * 16 + 20)//HMI复位请求
#define R_DCHMI_RESET_DOING										(R_START * 16 + 21)//HMI复位中
#define R_DCHMI_RESET_DONE										(R_START * 16 + 22)//HMI复位完成	
#define R_DCHMI_UPDATEUI_REQ									(R_START * 16 + 23)//HMI内容更新请求
#define R_DCHMI_UPDATEUI_DOING									(R_START * 16 + 24)//HMI内容更新中
#define R_DCHMI_UPDATEUI_DONE									(R_START * 16 + 25)//HMI内容更新请求完成
#define R_DCHMI_RESTORE_REQ										(R_START * 16 + 26)//HMI从FLASH中恢复设置请求
#define R_DCHMI_RESTORE_DOING									(R_START * 16 + 27)//HMI从FLASH中恢复中
#define R_DCHMI_RESTORE_DONE									(R_START * 16 + 28)//HMI从FLASH中恢复设置完成	
#define R_DCHMI_DISPLAY_WARN									(R_START * 16 + 30)//HMI显示报警信息
#define R_DCHMI_KEY_STANDBY_ENABLE								(R_START * 16 + 40)//STANDBY 使能
/*****************************************************************************/
#define R_STANDBY_KEY_POSWIDTH_ADD_DOWN							(R_START * 16 + 80)
#define R_STANDBY_KEY_POSWIDTH_DEC_DOWN							(R_START * 16 + 81)
#define R_STANDBY_KEY_NEGWIDTH_ADD_DOWN							(R_START * 16 + 82)
#define R_STANDBY_KEY_NEGWIDTH_DEC_DOWN							(R_START * 16 + 83)
#define R_STANDBY_KEY_TIMES_ADD_DOWN							(R_START * 16 + 84)
#define R_STANDBY_KEY_TIMES_DEC_DOWN							(R_START * 16 + 85)
#define R_STANDBY_KEY_GROUP_OFF_ADD_DOWN						(R_START * 16 + 86)
#define R_STANDBY_KEY_GROUP_OFF_DEC_DOWN						(R_START * 16 + 87)
#define R_STANDBY_KEY_ENERGY_INTERVAL_ADD_DOWN					(R_START * 16 + 88)
#define R_STANDBY_KEY_ENERGY_INTERVAL_DEC_DOWN					(R_START * 16 + 89)
#define R_STANDBY_KEY_STNADBY_DOWN								(R_START * 16 + 90)
#define R_STANDBY_KEY_STNADBY_UP								(R_START * 16 + 91)
#define R_STANDBY_KEY_ENTER_OPTION_DOWN							(R_START * 16 + 92)
#define R_STANDBY_KEY_ENTER_SCHEME_DOWN							(R_START * 16 + 93)
#define R_STANDBY_KEY_SCHEME_SAVE_DOWN							(R_START * 16 + 94)
/*****************************************************************************/
#define R_OPTION_KEY_ENTER_CORRECTION_DOWN						(R_START * 16 + 100)
#define R_OPTION_KEY_ENTER_INFORMATION_DOWN						(R_START * 16 + 101)
#define R_OPTION_KEY_ENTER_OK_DOWN								(R_START * 16 + 102)
#define R_OPTION_KEY_ENTER_DIAGNOSIS_DOWN						(R_START * 16 + 103)
/*****************************************************************************/
#define R_INFORMATION_KEY_OK_DOWN								(R_START * 16 + 110)
#define R_INFORMATION_KEY_OK_UP									(R_START * 16 + 111)
/*****************************************************************************/
#define R_SCHEME_KEY_RENAME_DOWN								(R_START * 16 + 120)
#define R_SCHEME_KEY_OK_DOWN									(R_START * 16 + 121)
#define R_SCHEME_KEY_CANCEL_DOWN								(R_START * 16 + 122)
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
#define R_SCHEME_KEY_SCHEME_SELECT_10_DOWN						(R_START * 16 + 133)
#define R_SCHEME_KEY_SCHEME_SELECT_11_DOWN						(R_START * 16 + 134)
#define R_SCHEME_KEY_SCHEME_SELECT_12_DOWN						(R_START * 16 + 135)
#define R_SCHEME_KEY_SCHEME_SELECT_13_DOWN						(R_START * 16 + 136)
#define R_SCHEME_KEY_SCHEME_SELECT_14_DOWN						(R_START * 16 + 137)
#define R_SCHEME_KEY_SCHEME_SELECT_15_DOWN						(R_START * 16 + 138)
#define R_SCHEME_KEY_NEXT_SCHEME								(R_START * 16 + 139)
#define R_SCHEME_KEY_LAST_SCHEME								(R_START * 16 + 140)
/*****************************************************************************/
#define R_DIAGNOSIS_OK_DOWN										(R_START * 16 + 160)
#define R_DIAGNOSIS_OK_UP										(R_START * 16 + 161)
/*****************************************************************************/
#define R_RENAME_KEY_ENTER_DOWN									(R_START * 16 + 170)
#define R_RENAME_KEY_EXIT_DOWN									(R_START * 16 + 171)
#define R_RENAME_TEXTDISPLAY_READ_DONE							(R_START * 16 + 172)
/*****************************************************************************/
#define MR_FOOSWITCH_HAND_SWITCH								(MR_START * 16 + 10)//脚踏HandSwitch 脉冲控制
#define MR_BEEM_TONE											(MR_START * 16 + 11)//蜂鸣器模式
/*****************************************************************************/
#define T100MS_HMI_POWERUP_DELAY								0//HMI启动复位延时
#define T100MS_ENTER_PASSCODE_DELAY								1
#define T100MS_READY_BEEM_DELAY									2//进入READY状态后蜂鸣器响延迟
#define T100MS_PULSE_BEEM_DELAY									3//脉冲模式蜂鸣器延迟
/*****************************************************************************/
#define T10MS_POSWIDTH_ADD_KEYDOWN_DELAY						3
#define T10MS_POSWIDTH_DEC_KEYDOWN_DELAY						4
#define T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY						5
#define T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY						6
#define T10MS_TIMES_ADD_KEYDOWN_DELAY							7
#define T10MS_TIMES_DEC_KEYDOWN_DELAY							8
#define T10MS_GROUP_OFF_ADD_KEYDOWN_DELAY						9
#define T10MS_GROUP_OFF_DEC_KEYDOWN_DELAY						10
/*****************************************************************************/
#endif






