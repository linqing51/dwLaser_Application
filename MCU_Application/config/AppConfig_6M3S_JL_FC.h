#ifndef __APPCONFIG_6M3S_JL_FC_H__
#define __APPCONFIG_6M3S_JL_FC_H__
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
#define DEVID_L																				'B'//设备ID
#define BUFFER_SIZE        														((uint16_t)512*32)//512的整数倍
#define CONFIG_JUMP_DELAY															5000//检测U盘时间
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
#define SW_VERSION																		"5.0a0b0"
#define HW_VERSION																		"CORE_6M3S_JL_FC_1940_1470_635"
//配置波长
#define APP_CONFIG_WAVE_1940_1470_635//APP为三波长 1940+1470+635
//配置激光器型号
#define MODLE_JL_FC_1470_1940_22W_200_22_1D//1470+1940+650
/*****************************************************************************/
//配置无线脚踏USB接口
#define APP_CONFIG_WFSW_PORT													hUsbHostHS
#define CONFIG_FSWITCH_USB_VID												0x16C0
#define CONFIG_FSWITCH_USB_PID												0x05E2
/*****************************************************************************/
//设置页面配置
#define GDDC_PAGE_POWERUP                             GDDC_PAGE_POWERUP_TRI_1940_1470_635
#define GDDC_PAGE_STANDBY 														GDDC_PAGE_STANDBY_TRI_1940_1470_635
/*****************************************************************************/
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
#define CONFIG_USING_CLASSIC_PID											1
#define CONFIG_USING_FUZZY_PID												0
#define CONFIG_USING_SMART_PID												0

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

#define CONFIG_HDC1080_HUMIDITY_HIGH									9999
#define CONFIG_HDC1080_HUMIDITY_HIGH									9999	
#define CONFIG_HDC1080_HUMIDITY_LOW										-9999
#define CONFIG_HDC1080_HUMIDITY_LOW										-9999

#define CONFIG_HDC1080_TEMP_HIGH                      9999
#define CONFIG_HDC1080_TEMP_LOW                       -9999

#define CONFIG_DHT11_HUMIDITY_HIGH                    9999
#define CONFIG_DHT11_HUMIDITY_LOW                     -9999

#define CONFIG_DHT11_TEMP_HIGH                        9999              
#define CONFIG_DHT11_TEMP_LOW                         -9999

#define CONFIG_MCU_TEMP_HIGH													650//处理器高温标志
#define CONFIG_MCU_TEMP_LOW														-200//处理器低温标志
#define CONFIG_MBAT_TEMP_HIGH													550//主电池高温标志
#define CONFIG_MBAT_TEMP_LOW													-100//主电池低温标志

#define CONFIG_FAN_CURVE_POINTS 											10//定义温度-转速曲线

//配置激光参数
#define CONFIG_MAX_LASER_POWER_CH0						        150//通道1470最大激光功率		
#define CONFIG_MAX_LASER_POWER_CH1						        70//通道1940最大激光功率		
#define CONFIG_MAX_LASER_POWER_CH2						        5//通道2最大激光功率
#define CONFIG_MAX_LASER_POWER_CH3						        0//通道3最大激光功率
#define CONFIG_MAX_LASER_POWER_CH4						        0//通道4最大激光功率
#define CONFIG_MAX_LASER_POWER_CH5						        0//通道5最大激光功率
#define CONFIG_MAX_LASER_POWER_CH6						        0//通道6最大激光功率
#define CONFIG_MAX_LASER_POWER_CH7						        0//通道7最大激光功率	

#define CONFIG_MIN_LASER_POWER_CH0						        1//通道1470最小激光功率		
#define CONFIG_MIN_LASER_POWER_CH1						        1//通道1940最小激光功率		
#define CONFIG_MIN_LASER_POWER_CH2						        1//通道2最小激光功率
#define CONFIG_MIN_LASER_POWER_CH3						        1//通道3最小激光功率
#define CONFIG_MIN_LASER_POWER_CH4						        1//通道4最小激光功率
#define CONFIG_MIN_LASER_POWER_CH5						        1//通道5最小激光功率
#define CONFIG_MIN_LASER_POWER_CH6						        1//通道6最小激光功率
#define CONFIG_MIN_LASER_POWER_CH7						        1//通道7最小激光功率	

#define CONFIG_MAX_LASER_POWER_GAIM										0//绿指示激光最大功率档
#define CONFIG_MAX_LASER_POWER_RAIM                   10//指示激光最大功率 10档

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

//定义指示灯亮度
#define CONFIG_BLUE_LED_MAX_DC												100
#define CONFIG_BLUE_LED_DEFAULT_DC										25
#define CONFIG_RED_LED_MAX_DC													100	
#define CONFIG_RED_LED_DEFAULT_DC											25
#define CONFIG_GREEN_LED_MAX_DC												100
#define CONFIG_GREEN_LED_DEFAULT_DC										25

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
#ifdef __cplusplus
}
#endif
#endif






