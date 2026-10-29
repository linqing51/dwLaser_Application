/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#ifndef __SPLCCONFIG_H__
#define __SPLCCONFIG_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
#define CONFIG_DEBUG_DAC															1//璋冭瘯DAC椹卞姩
#define CONFIG_DEBUG_ADC															1//璋冭瘯ADC椹卞姩
#define CONFIG_DEBUG_RTC															1//璋冭瘯RTC椹卞姩
#define CONFIG_DEBUG_EPROM														1//璋冭瘯EPROM椹卞姩
#define CONFIG_DEBUG_IO																1//璋冭瘯IO
#define CONFIG_DEBUG_SPK															0//璋冭瘯铚傞福鍣ㄩ┍鍔?
#define CONFIG_DEBUG_LED															1//璋冭瘯鎸囩ず鐏┍鍔?
#define CONFIG_DEBUG_AIM															1//璋冭瘯鎸囩ず鍏夐┍鍔?
#define CONFIG_DEBUG_LASER														0//璋冭瘯LASER椹卞姩
#define CONFIG_DEBUG_SPLC															0//璋冭瘯SPLC鍛戒护
#define CONFIG_DEBUG_WSW															0//璋冭瘯鏃犵嚎鑴氳笍
#define CONFIG_DEBUG_IIC_EXPAND												0//璋冭瘯I2C鎬荤嚎鎵╁睍鍣?
#define CONFIG_DEBUG_IIC_HDC1080											0//璋冭瘯I2C 鏉胯浇娓╂箍搴︿紶鎰熷櫒
#define CONFIG_INPUT_FILTER_TIME											10//杈撳叆鏁板瓧婊ゆ尝鎵弿鍛ㄦ湡 1mS * N
/*****************************************************************************/
#define CONFIG_SPLC_USING_ADC													1//浣胯兘ADC妯″潡
#define CONFIG_SPLC_USING_RTC													1//浣胯兘RTC妯″潡
#define CONFIG_SPLC_USING_SPWM												1//浣胯兘杞欢PWM鍔熻兘
#define CONFIG_SPLC_USING_FUNTEST											0//鍔熻兘鎸囦护娴嬭瘯
#define CONFIG_SPLC_USING_EPROM_TEST									0//EPROM 璇诲啓娴嬭瘯
#define CONFIG_SPLC_USING_LASER_TEST									0//婵€鍏夊櫒鑴夊啿妯″紡娴嬭瘯
/*****************************************************************************/
#define CONFIG_SPLC_ASSERT														1//妫€鏌ュ湴鍧€鑼冨洿
#define CONFIG_SPLC_CLEAR_CODE												0xA58E
#define CONFIG_SOFTPLC_TICK														200L//5mS
/*****************************************************************************/
//鍗曚綅byte
#define CONFIG_MR_SIZE																64L//
#define CONFIG_DM_SIZE																1024L
#define CONFIG_R_SIZE																	64L
#define CONFIG_EM_SIZE																1024L
#define CONFIG_T_1MS_SIZE															4L
#define CONFIG_T_10MS_SIZE														4L
#define CONFIG_T_100MS_SIZE														4L
#define CONFIG_T_1MS_ENA_SIZE													CONFIG_T_1MS_SIZE
#define CONFIG_T_10MS_ENA_SIZE												CONFIG_T_10MS_SIZE
#define CONFIG_T_100MS_ENA_SIZE												CONFIG_T_100MS_SIZE
#define CONFIG_TD_1MS_SIZE														(CONFIG_T_1MS_SIZE * 16L)
#define CONFIG_TD_10MS_SIZE														(CONFIG_T_10MS_SIZE * 16L)
#define CONFIG_TD_100MS_SIZE													(CONFIG_T_100MS_SIZE * 16L)
#define CONFIG_X_SIZE																	8L
#define CONFIG_Y_SIZE																	8L
#define CONFIG_SPREG_SIZE															128L
#define CONFIG_SPCOIL_SIZE														16L
#define CONFIG_TMP_SIZE																32L
#define CONFIG_FDRAM_SIZE															2048L
#define CONFIG_BKRAM_SIZE															2048L//BK 2K鍖哄潡(2048*16bit),鏄犲皠纭欢BKSRAM 4K鎺夌數淇濇寔鍖?
/*****************************************************************************/
//绾垮湀 淇濇寔
#define MR_START																			0
#define MR_END   																			(MR_START + CONFIG_MR_SIZE - 1L)
//鏁版嵁瀵勫瓨鍣?淇濇寔
#define DM_START																			(MR_END + 1L)
#define DM_END																				(DM_START + CONFIG_DM_SIZE - 1L)
//绾垮湀瀵勫瓨鍣?闈炰繚鎸?
#define R_START																				(DM_END + 1L)
#define R_END																					(R_START + CONFIG_R_SIZE - 1L)				
//鏁版嵁瀵勫瓨鍣?闈炰繚鎸?
#define EM_START																			(R_END + 1L)
#define EM_END																				(EM_START + CONFIG_EM_SIZE - 1L)
//寤舵椂绾垮湀
//1MS
#define T_1MS_START																		(EM_END + 1L)
#define T_1MS_END																			(T_1MS_START + CONFIG_T_1MS_SIZE - 1L)
//10MS
#define T_10MS_START																	(T_1MS_END + 1L)
#define T_10MS_END																		(T_10MS_START + CONFIG_T_10MS_SIZE - 1L)
//100MS
#define T_100MS_START																	(T_10MS_END + 1L)
#define T_100MS_END																		(T_100MS_START + CONFIG_T_100MS_SIZE - 1L)
//寤舵椂鍣ㄤ娇鑳?
//1MS
#define T_1MS_ENA_START																(T_100MS_END + 1L)
#define T_1MS_ENA_END																	(T_1MS_ENA_START + CONFIG_T_1MS_ENA_SIZE -1L)
//10MS
#define T_10MS_ENA_START															(T_1MS_ENA_END + 1L)
#define T_10MS_ENA_END																(T_10MS_ENA_START + CONFIG_T_10MS_ENA_SIZE -1L)
//100MS
#define T_100MS_ENA_START															(T_10MS_ENA_END + 1L)
#define T_100MS_ENA_END																(T_100MS_ENA_START + CONFIG_T_100MS_ENA_SIZE - 1L)
//寤舵椂璁℃椂鍣?
//1MS
#define TD_1MS_START																	(T_100MS_ENA_END + 1L)
#define TD_1MS_END																		(TD_1MS_START + CONFIG_TD_1MS_SIZE - 1L)
//10MS
#define TD_10MS_START																	(TD_1MS_END + 1L)											
#define TD_10MS_END																		(TD_10MS_START + CONFIG_TD_10MS_SIZE - 1L)
//100MS
#define TD_100MS_START																(TD_10MS_END + 1L)
#define TD_100MS_END																	(TD_100MS_START + CONFIG_TD_100MS_SIZE - 1L)
//杈撳叆浣嶅瘎瀛樺櫒
#define X_START																				(TD_100MS_END + 1L)
#define X_END																					(X_START + CONFIG_X_SIZE - 1L)
//杈撳嚭浣嶅瘎瀛樺櫒
#define Y_START																				(X_END + 1L)
#define Y_END																					(Y_START + CONFIG_Y_SIZE - 1L)
//鐗规畩瀵勫瓨鍣?
#define SPREG_START																		(Y_END + 1L)
#define SPREG_END																			(SPREG_START + CONFIG_SPREG_SIZE - 1L)
//鐗规畩绾垮湀
#define SPCOIL_START																	(SPREG_END + 1L)
#define SPCOIL_END																		(SPCOIL_START + CONFIG_SPCOIL_SIZE - 1L)
//涓存椂瀵勫瓨鍣?
#define TMP_START																			(SPCOIL_END + 1L)
#define TMP_END																				(TMP_START + CONFIG_TMP_SIZE - 1L)
/*****************************************************************************/
#define CONFIG_NVRAM_SIZE 														(TMP_END + 1)
/*****************************************************************************/
//瀛樻。瀵勫瓨鍣?
#define FD_START																			0
#define FD_END																				(CONFIG_FDRAM_SIZE - 1L)
//澶囦唤鎺夌數淇濇寔瀵勫瓨鍣?BK 2K 鏄犲皠纭欢BKSRAM 4K
#define BK_START																			0
#define BK_END																				(CONFIG_BKRAM_SIZE - 1L)
/*****************************************************************************/
#define SPCOIL_ON																			(SPCOIL_START * 16 + 0)//闀块€氱嚎鍦?
#define SPCOIL_START_UP																(SPCOIL_START * 16 + 1)//鍒濇涓婄數
#define SPCOIL_PS10MS																	(SPCOIL_START * 16 + 2)//10mS
#define SPCOIL_PS50MS																	(SPCOIL_START * 16 + 3)//50mS
#define SPCOIL_PS100MS																(SPCOIL_START * 16 + 4)//100mS
#define SPCOIL_PS200MS																(SPCOIL_START * 16 + 5)//200mS
#define SPCOIL_PS500MS																(SPCOIL_START * 16 + 6)//500mS
#define SPCOIL_PS1000MS																(SPCOIL_START * 16 + 7)//1000mS
#define SPCOIL_PS1MINS																(SPCOIL_START * 16 + 8)//1mins
/*****************************************************************************/
#define SPCOIL_LINK_SEND_BUSY													(SPCOIL_START * 16 + 16)//鍙戦€佽繘琛屼腑
#define SPCOIL_LINK_SEND_DONE													(SPCOIL_START * 16 + 17)//鍙戦€佸畬鎴?
#define SPCOIL_LINK_SEND_ERR													(SPCOIL_START * 16 + 18)//鍙戦€侀敊璇?
#define SPCOIL_LINK_RECE_BUSY													(SPCOIL_START * 16 + 19)//鎺ユ敹杩涜涓?
#define SPCOIL_LINK_RECE_DONE													(SPCOIL_START * 16 + 20)//鎺ユ敹瀹屾垚
#define SPCOIL_LINK_RECE_ERR													(SPCOIL_START * 16 + 21)//鍙戦€侀敊璇?
/*****************************************************************************/
#define SPCOIL_BEEM_ENABLE														(SPCOIL_START * 16 + 32)//铚傞福鍣ㄤ娇鑳?
#define SPCOIL_BEEM_BUSY															(SPCOIL_START * 16 + 33)//铚傞福鍣ㄥ伐浣滅姸鎬?
/*****************************************************************************/
#define SPCOIL_WFSWITCH_PLUG													(SPCOIL_START * 16 + 40)//鏃犵嚎鑴氳笍鎻掑叆					
#define SPCOIL_WFSWITCH_NO														(SPCOIL_START * 16 + 41)//鏃犵嚎鑴氳笍鎸変笅
/*****************************************************************************/
#define SPCOIL_SPWM_OUT_0															(SPCOIL_START * 16 + 48)//SPWM0杈撳嚭鐘舵€?
#define SPCOIL_SPWM_RESET_0														(SPCOIL_START * 16 + 49)//SPWM0澶嶄綅
#define SPCOIL_SPWM_OUT_1															(SPCOIL_START * 16 + 50)//SPWM1杈撳嚭鐘舵€?
#define SPCOIL_SPWM_RESET_1														(SPCOIL_START * 16 + 51)//SPWM1澶嶄綅
#define SPCOIL_SPWM_OUT_2															(SPCOIL_START * 16 + 52)//SPWM2杈撳嚭鐘舵€?
#define SPCOIL_SPWM_RESET_2														(SPCOIL_START * 16 + 53)//SPWM2澶嶄綅
#define SPCOIL_SPWM_OUT_3															(SPCOIL_START * 16 + 54)//SPWM3杈撳嚭鐘舵€?
#define SPCOIL_SPWM_RESET_3														(SPCOIL_START * 16 + 55)//SPWM3澶嶄綅
/*****************************************************************************/
#define SPREG_ADC_0																		(SPREG_START + 0)//閲囬泦鍊?CH0 CURRENT
#define SPREG_ADC_1																		(SPREG_START + 1)//閲囬泦鍊?CH1 CURRENT
#define SPREG_ADC_2																		(SPREG_START + 2)//閲囬泦鍊?CH2 CURRENT
#define SPREG_ADC_3																		(SPREG_START + 3)//閲囬泦鍊?CH3 CURRENT
#define SPREG_ADC_4																		(SPREG_START + 4)//閲囬泦鍊?CH4 CURRENT
#define SPREG_ADC_5																		(SPREG_START + 5)//閲囬泦鍊?CH5 CURRENT
#define SPREG_ADC_6																		(SPREG_START + 6)//閲囬泦鍊?CH7 CURRENT
#define SPREG_ADC_7																		(SPREG_START + 7)//閲囬泦鍊?CH8 CURRENT

#define SPREG_ADC_8																		(SPREG_START + 8)//閲囬泦鍊?CH0 VOLTAGE
#define SPREG_ADC_9																		(SPREG_START + 9)//閲囬泦鍊?CH1 VOLTAGE
#define SPREG_ADC_10																	(SPREG_START + 10)//閲囬泦鍊?CH2 VOLTAGE
#define SPREG_ADC_11																	(SPREG_START + 11)//閲囬泦鍊?CH3 VOLTAGE
#define SPREG_ADC_12																	(SPREG_START + 12)//閲囬泦鍊?CH4 VOLTAGE
#define SPREG_ADC_13																	(SPREG_START + 13)//閲囬泦鍊?CH5 VOLTAGE
#define SPREG_ADC_14																	(SPREG_START + 14)//閲囬泦鍊?CH7 VOLTAGE
#define SPREG_ADC_15																	(SPREG_START + 15)//閲囬泦鍊?CH8 VOLTAGE

#define SPREG_ADC_16																	(SPREG_START + 16)//閲囬泦鍊?TEC0 CURRENT
#define SPREG_ADC_17																	(SPREG_START + 17)//閲囬泦鍊?TEC1 CURRENT
#define SPREG_ADC_18																	(SPREG_START + 18)//閲囬泦鍊?TEC2 CURRENT
#define SPREG_ADC_19																	(SPREG_START + 19)//閲囬泦鍊?TEC3 CURRENT
#define SPREG_ADC_20																	(SPREG_START + 20)//閲囬泦鍊?TEC4 CURRENT
#define SPREG_ADC_21																	(SPREG_START + 21)//閲囬泦鍊?TEC5 CURRENT
#define SPREG_ADC_22																	(SPREG_START + 22)//閲囬泦鍊?TEC6 CURRENT
#define SPREG_ADC_23																	(SPREG_START + 23)//閲囬泦鍊?TEC7 CURRENT

#define SPREG_ADC_24																	(SPREG_START + 24)//閲囬泦鍊?TEC1 VOLTAGE
#define SPREG_ADC_25																	(SPREG_START + 25)//閲囬泦鍊?TEC2 VOLTAGE
#define SPREG_ADC_26																	(SPREG_START + 26)//閲囬泦鍊?TEC3 VOLTAGE
#define SPREG_ADC_27																	(SPREG_START + 27)//閲囬泦鍊?TEC4 VOLTAGE
#define SPREG_ADC_28																	(SPREG_START + 28)//閲囬泦鍊?TEC5 VOLTAGE
#define SPREG_ADC_29																	(SPREG_START + 29)//閲囬泦鍊?TEC6 VOLTAGE
#define SPREG_ADC_30																	(SPREG_START + 30)//閲囬泦鍊?TEC7 VOLTAGE
#define SPREG_ADC_31																	(SPREG_START + 31)//閲囬泦鍊?TEC8 VOLTAGE

#define SPREG_ADC_32																	(SPREG_START + 32)//閲囬泦鍊?鏁ｇ儹鍣℉T0_NTC 
#define SPREG_ADC_33																	(SPREG_START + 33)//閲囬泦鍊?鏁ｇ儹鍣℉T1_NTC 
#define SPREG_ADC_34																	(SPREG_START + 34)//閲囬泦鍊?鏁ｇ儹鍣℉T2_NTC 
#define SPREG_ADC_35																	(SPREG_START + 35)//閲囬泦鍊?鏁ｇ儹鍣℉T3_NTC
#define SPREG_ADC_36																	(SPREG_START + 36)//閲囬泦鍊?鍐峰嵈娑瞁ATER1_NTC->HOT  
#define SPREG_ADC_37																	(SPREG_START + 37)//閲囬泦鍊?鍐峰嵈娑瞁ATER2_NTC->COOL
#define SPREG_ADC_38																	(SPREG_START + 38)//閲囬泦鍊?鍐峰嵈娑瞁ATER3_NTC 
#define SPREG_ADC_39																	(SPREG_START + 39)//閲囬泦鍊?鍐峰嵈娑瞁ATER4_NTC

#define SPREG_ADC_40																	(SPREG_START + 40)//閲囬泦鍊?婵€鍏夊櫒 A DIODE NTC
#define SPREG_ADC_41																	(SPREG_START + 41)//閲囬泦鍊?婵€鍏夊櫒 B DIODE NTC
#define SPREG_ADC_42																	(SPREG_START + 42)//閲囬泦鍊?婵€鍏夊櫒 A COUPLER NTC
#define SPREG_ADC_43																	(SPREG_START + 43)//閲囬泦鍊?婵€鍏夊櫒 B COUPLER NTC
#define SPREG_ADC_44																	(SPREG_START + 44)//閲囬泦鍊?婵€鍏夊櫒 A CRYST0 NTC
#define SPREG_ADC_45																	(SPREG_START + 45)//閲囬泦鍊?婵€鍏夊櫒 A CRYST1 NTC
#define SPREG_ADC_46																	(SPREG_START + 46)//閲囬泦鍊?婵€鍏夊櫒 B CRYST0 NTC
#define SPREG_ADC_47																	(SPREG_START + 47)//閲囬泦鍊?婵€鍏夊櫒 B CRYST1 NTC

#define SPREG_ADC_48																	(SPREG_START + 48)//閲囬泦鍊?NC
#define SPREG_ADC_49																	(SPREG_START + 49)//閲囬泦鍊?NC
#define SPREG_ADC_50																	(SPREG_START + 50)//閲囬泦鍊?NC

#define SPREG_ADC_51																	(SPREG_START + 51)//閲囬泦鍊?PWR CURRENT 姣嶇嚎鐢垫祦
#define SPREG_ADC_52																	(SPREG_START + 52)//閲囬泦鍊?VIN VOLTAGE 姣嶇嚎鐢靛帇
#define SPREG_ADC_53																	(SPREG_START + 53)//閲囬泦鍊?BAT NTC
#define SPREG_ADC_54																	(SPREG_START + 54)//閲囬泦鍊?LASER_FPD
#define SPREG_ADC_55																	(SPREG_START + 55)//閲囬泦鍊?LASER_LPD
#define SPREG_ADC_56																	(SPREG_START + 56)//閲囬泦鍊?AMB0_TEMP鐜娓╁害 NTC
#define SPREG_ADC_57																	(SPREG_START + 57)//閲囬泦鍊?AMB1_TEMP鐜娓╁害 NTC
#define SPREG_ADC_58																	(SPREG_START + 58)//CHIP TEMP鐗囧唴娓╁害浼犳劅鍣?
#define SPREG_ADC_59																	(SPREG_START + 59)//CHIP VREFINT鐗囧唴鍩哄噯婧?
#define SPREG_ADC_60																	(SPREG_START + 60)//VBAT 鎺夌數瀛樺偍鐢垫睜 
/*****************************************************************************/
#define SPREG_DAC_0																		(SPREG_START + 70)//DAC璁惧畾鍊?婵€鍏夐€氶亾 CH0 ->1470 1940
#define SPREG_DAC_1																		(SPREG_START + 71)//DAC璁惧畾鍊?婵€鍏夐€氶亾 CH1 ->980
#define SPREG_DAC_2																		(SPREG_START + 72)//DAC璁惧畾鍊?婵€鍏夐€氶亾 CH2 
#define SPREG_DAC_3																		(SPREG_START + 73)//DAC璁惧畾鍊?婵€鍏夐€氶亾 CH3
#define SPREG_DAC_4																		(SPREG_START + 74)//DAC璁惧畾鍊?婵€鍏夐€氶亾 CH4
#define SPREG_DAC_5																		(SPREG_START + 75)//DAC璁惧畾鍊?婵€鍏夐€氶亾 CH5
#define SPREG_DAC_6																		(SPREG_START + 76)//DAC璁惧畾鍊?婵€鍏夐€氶亾 CH6 
#define SPREG_DAC_7																		(SPREG_START + 77)//DAC璁惧畾鍊?婵€鍏夐€氶亾 CH7
/*****************************************************************************/
#define SPREG_DAC_8																		(SPREG_START + 78)//DAC璁惧畾鍊?婵€鍏夐€氶亾 CH8 ->TEC0
#define SPREG_DAC_9																		(SPREG_START + 79)//DAC璁惧畾鍊?婵€鍏夐€氶亾 CH9 ->TEC1
#define SPREG_DAC_10																	(SPREG_START + 80)//DAC璁惧畾鍊?婵€鍏夐€氶亾 CH10 ->TEC2
#define SPREG_DAC_11																	(SPREG_START + 81)//DAC璁惧畾鍊?婵€鍏夐€氶亾 CH11 ->TEC3
#define SPREG_DAC_12																	(SPREG_START + 82)//DAC璁惧畾鍊?婵€鍏夐€氶亾 CH12 ->TEC4
#define SPREG_DAC_13																	(SPREG_START + 83)//DAC璁惧畾鍊?婵€鍏夐€氶亾 CH13 ->TEC5
#define SPREG_DAC_14																	(SPREG_START + 84)//DAC璁惧畾鍊?婵€鍏夐€氶亾 CH14 ->TEC6
#define SPREG_DAC_15																	(SPREG_START + 85)//DAC璁惧畾鍊?婵€鍏夐€氶亾 CH15 ->TEC7
/*****************************************************************************/
#define SPREG_DAC_16																	(SPREG_START + 86)//DAC璁惧畾鍊?婵€鍏夐€氶亾 CH16 -> 635 PWM 鍗犵┖姣?
#define SPREG_DAC_17																	(SPREG_START + 87)//DAC璁惧畾鍊?婵€鍏夐€氶亾 CH17 -> 532 PWM 鍗犵┖姣?
/*****************************************************************************/
#define SPREG_SPWM_POS_0															(SPREG_START + 90)//杞欢PWM0姝ｈ剦瀹借缃?
#define SPREG_SPWM_POS_SHADOW_0												(SPREG_START + 91)//杞欢PWM0姝ｈ剦瀹介槾褰?
#define SPREG_SPWM_CYCLE_0														(SPREG_START + 92)//杞欢PWM0鍛ㄦ湡璁剧疆
#define SPREG_SPWM_CYCLE_SHADOW_0											(SPREG_START + 93)//杞欢PWM0鍛ㄦ湡闃村奖
#define SPREG_SPWM_COUNTER_0													(SPREG_START + 94)//杞欢PWM0璁℃暟鍣?
#define SPREG_SPWM_POS_1															(SPREG_START + 95)//杞欢PWM1姝ｈ剦瀹借缃?
#define SPREG_SPWM_POS_SHADOW_1												(SPREG_START + 96)//杞欢PWM1姝ｈ剦瀹介槾褰?
#define SPREG_SPWM_CYCLE_1														(SPREG_START + 97)//杞欢PWM1鍛ㄦ湡璁剧疆
#define SPREG_SPWM_CYCLE_SHADOW_1											(SPREG_START + 98)//杞欢PWM1鍛ㄦ湡闃村奖
#define SPREG_SPWM_COUNTER_1													(SPREG_START + 99)//杞欢PWM1璁℃暟鍣?
#define SPREG_SPWM_POS_2															(SPREG_START + 100)//杞欢PWM2姝ｈ剦瀹借缃?
#define SPREG_SPWM_POS_SHADOW_2												(SPREG_START + 101)//杞欢PWM2姝ｈ剦瀹介槾褰?
#define SPREG_SPWM_CYCLE_2														(SPREG_START + 102)//杞欢PWM2鍛ㄦ湡璁剧疆
#define SPREG_SPWM_CYCLE_SHADOW_2											(SPREG_START + 103)//杞欢PWM2鍛ㄦ湡闃村奖
#define SPREG_SPWM_COUNTER_2													(SPREG_START + 104)//杞欢PWM2璁℃暟鍣?
#define SPREG_SPWM_POS_3															(SPREG_START + 105)//杞欢PWM3姝ｈ剦瀹借缃?
#define SPREG_SPWM_POS_SHADOW_3												(SPREG_START + 106)//杞欢PWM3姝ｈ剦瀹介槾褰?
#define SPREG_SPWM_CYCLE_3														(SPREG_START + 107)//杞欢PWM3鍛ㄦ湡璁剧疆
#define SPREG_SPWM_CYCLE_SHADOW_3											(SPREG_START + 108)//杞欢PWM3鍛ㄦ湡闃村奖
#define SPREG_SPWM_COUNTER_3													(SPREG_START + 109)//杞欢PWM3璁℃暟鍣?
/*****************************************************************************/
#define SPREG_BEEM_VOLUME											  			(SPREG_START + 110)//铚傞福鍣ㄩ煶閲?0-100% 1320+60=1380
#define SPREG_BEEM_FREQ												  			(SPREG_START + 111)//铚傞福鍣ㄩ鐜?       1320+61=1381
#define SPREG_BEEM_MODE												  			(SPREG_START + 112)//铚傞福鍣ㄦā寮?       1320+62=1382
#define SPREG_BEEM_COUNTER										  			(SPREG_START + 113)//铚傞福鍣ㄨ鏃跺櫒      1320+63=1383
/*****************************************************************************/
//闇€瑕佸瓨鍌ㄧ殑鏂规
#define EM_LASER_SCHEME_NAME													(EM_START + 0)//鏂规鍚嶇О
#define EM_LASER_CHANNEL_SELECT												(EM_START + 51)//婵€鍏夐€氶亾閫夋嫨
#define EM_LASER_PULSE_MODE														(EM_START + 52)//鑴夊啿妯″紡
#define EM_LASER_POWER_CH0														(EM_START + 53)//閫氶亾0->1470/1940鍔熺巼
#define EM_LASER_POWER_CH1														(EM_START + 54)//閫氶亾1->980鍔熺巼
#define EM_LASER_POWER_CH2														(EM_START + 55)//澶囩敤閫氶亾2
#define EM_LASER_POWER_CH3														(EM_START + 56)//澶囩敤閫氶亾3
#define EM_LASER_POWER_CH4														(EM_START + 57)//澶囩敤閫氶亾4
#define EM_LASER_POWER_CH5														(EM_START + 58)//澶囩敤閫氶亾5
#define EM_LASER_POWER_CH6														(EM_START + 59)//澶囩敤閫氶亾6
#define EM_LASER_POWER_CH7														(EM_START + 60)//澶囩敤閫氶亾7
#define EM_LASER_POWER_635														(EM_START + 61)//绾㈡縺鍏夊姛鐜?
#define EM_LASER_POSWIDTH															(EM_START + 62)//澶氳剦鍐叉鑴夊
#define EM_LASER_NEGWIDTH															(EM_START + 63)//澶氳剦鍐茶礋鑴夊
/*****************************************************************************/
#define EM_LASER_AVERAGE_POWER_CH0										(EM_START + 80)//褰撳墠妯″紡骞冲潎鍔熺巼 1470/1940
#define EM_LASER_AVERAGE_POWER_CH1              			(EM_START + 81)//褰撳墠妯″紡骞冲潎鍔熺巼 980
#define EM_LASER_AVERAGE_POWER_CH2										(EM_START + 82)//褰撳墠妯″紡骞冲潎鍔熺巼->澶囩敤閫氶亾2
#define EM_LASER_AVERAGE_POWER_CH3										(EM_START + 83)//褰撳墠妯″紡骞冲潎鍔熺巼->澶囩敤閫氶亾3
#define EM_LASER_AVERAGE_POWER_CH4              			(EM_START + 84)//褰撳墠妯″紡骞冲潎鍔熺巼->澶囩敤閫氶亾4
#define EM_LASER_AVERAGE_POWER_CH5										(EM_START + 85)//褰撳墠妯″紡骞冲潎鍔熺巼->澶囩敤閫氶亾5
#define EM_LASER_AVERAGE_POWER_CH6										(EM_START + 86)//褰撳墠妯″紡骞冲潎鍔熺巼->澶囩敤閫氶亾6
#define EM_LASER_AVERAGE_POWER_CH7              			(EM_START + 87)//褰撳墠妯″紡骞冲潎鍔熺巼->澶囩敤閫氶亾7
#define EM_LASER_AVERAGE_POWER_635              			(EM_START + 88)//褰撳墠妯″紡骞冲潎楂樺姛鐜?635
#define EM_LASER_FREQUENCY														(EM_START + 89)//褰撳墠妯″紡棰戠巼
#define EM_LASER_DUTY_CYCLE														(EM_START + 90)//褰撳墠妯″紡鍗犵┖姣?
/*****************************************************************************/
#define EM_LASER_A_DIODE_TEMP													(EM_START + 100)//婵€鍏変簩鏋佺妯″潡A绠¤姱娓╁害
#define EM_LASER_A_COUPLER_TEMP												(EM_START + 101)//婵€鍏変簩鏋佺妯″潡A鑰﹀悎娓╁害
#define EM_LASER_A_CRYST0_TEMP												(EM_START + 102)//婵€鍏夊櫒A鏅朵綋娓╁害->鍊嶉1
#define EM_LASER_A_CRYST1_TEMP												(EM_START + 103)//婵€鍏夊櫒A鏅朵綋娓╁害->鍊嶉2
#define EM_LASER_B_DIODE_TEMP													(EM_START + 104)//婵€鍏変簩鏋佺妯″潡绠鑺俯搴?
#define EM_LASER_B_COUPLER_TEMP												(EM_START + 105)//婵€鍏変簩鏋佺妯″潡鑰鍚堟俯搴?
#define EM_LASER_B_CRYST0_TEMP												(EM_START + 106)//婵€鍏夊櫒B鏅朵綋娓╁害->鍊嶉1
#define EM_LASER_B_CRYST1_TEMP												(EM_START + 107)//婵€鍏夊櫒B鏅朵綋娓╁害->鍊嶉2
#define EM_HT0_TEMP																		(EM_START + 108)//鏁ｇ儹鍣?娓╁害
#define EM_HT1_TEMP																		(EM_START + 109)//鏁ｇ儹鍣?娓╁害
#define EM_HT2_TEMP																		(EM_START + 110)//鏁ｇ儹鍣?娓╁害
#define EM_HT3_TEMP																		(EM_START + 111)//鏁ｇ儹鍣?娓╁害
#define EM_HWATER_TEMP																(EM_START + 112)//鍐峰嵈姘存俯搴?>鐑按
#define EM_CWATER_TEMP																(EM_START + 113)//鍐峰嵈姘存俯搴?>鍐锋按
#define EM_AMBIENT0_TEMP															(EM_START + 114)//鐜娓╁害 椋庨亾 NTC
#define EM_AMBIENT1_TEMP															(EM_START + 115)//鐜娓╁害 椋庨亾 NTC
#define EM_AMBIENT2_TEMP															(EM_START + 116)//鐜娓╁害 椋庨亾 NTC
#define EM_AMBIENT3_TEMP															(EM_START + 117)//鐜娓╁害 椋庨亾 NTC
#define EM_HDC1080_HUMIDITY														(EM_START + 118)//鏉胯浇HDC1080婀垮害
#define EM_HDC1080_TEMP																(EM_START + 119)//鏉胯浇HDC1080娓╁害

#define EM_DHT11_HUMIDITY															(EM_START + 120)//澶栫疆DHT11婀垮害
#define EM_DHT11_TEMP																	(EM_START + 121)//澶栫疆DHT11娓╁害

#define EM_MCU_TEMP																		(EM_START + 122)//澶勭悊鍣ㄦ俯搴?
#define EM_MBAT_TEMP																	(EM_START + 123)//鐢垫睜娓╁害

#define EM_LD_CH0_CURRENT															(EM_START + 130)//婵€鍏夐€氶亾0->鐢垫祦																
#define EM_LD_CH1_CURRENT															(EM_START + 131)//婵€鍏夐€氶亾1->鐢垫祦
#define EM_LD_CH2_CURRENT															(EM_START + 132)//婵€鍏夐€氶亾2->鐢垫祦
#define EM_LD_CH3_CURRENT															(EM_START + 133)//婵€鍏夐€氶亾3->鐢垫祦
#define EM_LD_CH4_CURRENT															(EM_START + 134)//婵€鍏夐€氶亾4->鐢垫祦
#define EM_LD_CH5_CURRENT															(EM_START + 135)//婵€鍏夐€氶亾5->鐢垫祦
#define EM_LD_CH6_CURRENT															(EM_START + 136)//婵€鍏夐€氶亾6->鐢垫祦
#define EM_LD_CH7_CURRENT															(EM_START + 137)//婵€鍏夐€氶亾7->鐢垫祦

#define EM_LD_CH0_VOLTAGE															(EM_START + 140)//婵€鍏夐€氶亾0-鐢靛帇
#define EM_LD_CH1_VOLTAGE															(EM_START + 141)//婵€鍏夐€氶亾1-鐢靛帇
#define EM_LD_CH2_VOLTAGE															(EM_START + 142)//婵€鍏夐€氶亾2-鐢靛帇
#define EM_LD_CH3_VOLTAGE															(EM_START + 143)//婵€鍏夐€氶亾3-鐢靛帇
#define EM_LD_CH4_VOLTAGE															(EM_START + 144)//婵€鍏夐€氶亾4-鐢靛帇
#define EM_LD_CH5_VOLTAGE															(EM_START + 145)//婵€鍏夐€氶亾5-鐢靛帇
#define EM_LD_CH6_VOLTAGE															(EM_START + 146)//婵€鍏夐€氶亾6-鐢靛帇
#define EM_LD_CH7_VOLTAGE															(EM_START + 147)//婵€鍏夐€氶亾7-鐢靛帇

#define EM_TEC_CH0_CURRENT														(EM_START + 150)//鍒跺喎閫氶亾0->鐢垫祦
#define EM_TEC_CH1_CURRENT														(EM_START + 151)//鍒跺喎閫氶亾1->鐢垫祦
#define EM_TEC_CH2_CURRENT														(EM_START + 152)//鍒跺喎閫氶亾2->鐢垫祦
#define EM_TEC_CH3_CURRENT														(EM_START + 153)//鍒跺喎閫氶亾3->鐢垫祦
#define EM_TEC_CH4_CURRENT														(EM_START + 154)//鍒跺喎閫氶亾4->鐢垫祦
#define EM_TEC_CH5_CURRENT														(EM_START + 155)//鍒跺喎閫氶亾5->鐢垫祦
#define EM_TEC_CH6_CURRENT														(EM_START + 156)//鍒跺喎閫氶亾6->鐢垫祦
#define EM_TEC_CH7_CURRENT														(EM_START + 157)//鍒跺喎閫氶亾7->鐢垫祦

#define EM_TEC_CH0_VOLTAGE														(EM_START + 160)//鍒跺喎閫氶亾0->鐢靛帇
#define EM_TEC_CH1_VOLTAGE														(EM_START + 161)//鍒跺喎閫氶亾1->鐢靛帇
#define EM_TEC_CH2_VOLTAGE														(EM_START + 162)//鍒跺喎閫氶亾2->鐢靛帇
#define EM_TEC_CH3_VOLTAGE														(EM_START + 163)//鍒跺喎閫氶亾3->鐢靛帇
#define EM_TEC_CH4_VOLTAGE														(EM_START + 164)//鍒跺喎閫氶亾3->鐢靛帇
#define EM_TEC_CH5_VOLTAGE														(EM_START + 165)//鍒跺喎閫氶亾4->鐢靛帇
#define EM_TEC_CH6_VOLTAGE														(EM_START + 166)//鍒跺喎閫氶亾5->鐢靛帇
#define EM_TEC_CH7_VOLTAGE														(EM_START + 167)//鍒跺喎閫氶亾7->鐢靛帇

#define EM_PWR_CURRENT																(EM_START + 170)//姣嶇嚎渚涚數鐢垫祦
#define EM_PWR_VOLTAGE																(EM_START + 171)//姣嶇嚎渚涚數鐢靛帇

#define EM_FAN0_SET_SPEED															(EM_START + 180)//椋庢墖0璁惧畾閫熷害 0-100%
#define EM_FAN1_SET_SPEED															(EM_START + 181)//椋庢墖1璁惧畾閫熷害 0-100%
#define EM_FAN2_SET_SPEED															(EM_START + 182)//椋庢墖2璁惧畾閫熷害 0-100%
#define EM_FAN3_SET_SPEED															(EM_START + 183)//椋庢墖3璁惧畾閫熷害 0-100%
#define EM_FAN4_SET_SPEED															(EM_START + 184)//椋庢墖4璁惧畾閫熷害 0-100%
#define EM_FAN5_SET_SPEED															(EM_START + 185)//椋庢墖5璁惧畾閫熷害 0-100%
#define EM_FAN6_SET_SPEED															(EM_START + 186)//椋庢墖6璁惧畾閫熷害 0-100%
#define EM_FAN7_SET_SPEED															(EM_START + 187)//椋庢墖7璁惧畾閫熷害 0-100%

#define EM_FAN0_GET_SPEED															(EM_START + 188)//椋庢墖0瀹為檯閫熷害 杞€?
#define EM_FAN1_GET_SPEED															(EM_START + 189)//椋庢墖1瀹為檯閫熷害 杞€?
#define EM_FAN2_GET_SPEED															(EM_START + 190)//椋庢墖2瀹為檯閫熷害 杞€?
#define EM_FAN3_GET_SPEED															(EM_START + 191)//椋庢墖3瀹為檯閫熷害 杞€?
#define EM_FAN4_GET_SPEED															(EM_START + 192)//椋庢墖4瀹為檯閫熷害 杞€?
#define EM_FAN5_GET_SPEED															(EM_START + 193)//椋庢墖5瀹為檯閫熷害 杞€?
#define EM_FAN6_GET_SPEED															(EM_START + 194)//椋庢墖6瀹為檯閫熷害 杞€?
#define EM_FAN7_GET_SPEED															(EM_START + 195)//椋庢墖7瀹為檯閫熷害 杞€?

#define EM_LASER_FPD																	(EM_START + 196)//鍏夌氦鎺㈡祴PD璁＄畻鍊?
#define EM_LASER_LPD																	(EM_START + 197)//婵€鍏夎兘閲廝D璁＄畻鍊?

#define EM_TPID0_OUT																	(EM_START + 200)//娓╂帶PID-0杈撳嚭鍊?
#define EM_TPID1_OUT																	(EM_START + 201)//娓╂帶PID-1杈撳嚭鍊?
#define EM_TPID2_OUT																	(EM_START + 202)//娓╂帶PID-2杈撳嚭鍊?
#define EM_TPID3_OUT																	(EM_START + 203)//娓╂帶PID-3杈撳嚭鍊?

#define EM_ACOUSTIC_ENERGY														(EM_START + 210)//鎻愮ず闊宠兘閲忛棿闅?16BIT
#define EM_ACOUSTIC_TIME															(EM_START + 211)//鎻愮ず闊虫椂闂撮棿闅?16BIT
#define EM_ACOUSTIC_ENERGY_STEP												(EM_START + 212)//鎻愮ず闊虫杩涜兘閲?
#define EM_ACOUSTIC_TIME_STEP													(EM_START + 213)//鎻愮ず闊虫杩涙椂闂?
#define EM_ACOUSTIC_ENERGY_MAX												(EM_START + 214)//鎻愮ず闊宠兘閲忔渶澶у€?
#define EM_ACOUSTIC_ENERGY_MIN												(EM_START + 215)//鎻愮ず闊宠兘閲忔渶灏忓€?
#define EM_ACOUSTIC_TIME_MAX													(EM_START + 216)//鎻愮ず闊虫椂闂存渶澶у€?
#define EM_ACOUSTIC_TIME_MIN													(EM_START + 217)//鎻愮ず闊虫椂闂存渶灏忓€?
/*****************************************************************************/				
#define EM_LASER_POWER_TOTAL													(EM_START + 220)//鍙戝皠鎬诲姛鐜?
#define EM_HMI_OPERA_STEP															(EM_START +	221)//鎿嶄綔姝ラ								
#define EM_ERROR_CODE																	(EM_START + 222)//閿欒鐮?				
#define EM_SCHEME_NUM_TMP															(EM_START + 223)//涓存椂鏂规缂栧彿	
#define EM_SCHEME_CLASSIFY_TMP												(EM_START + 224)//涓存椂鍒嗙被缂栧彿
/*****************************************************************************/
#define EM_DC_PAGE																		(EM_START + 230)//HMI椤甸潰缂栧彿 			
#define EM_DC_PASSCODE_INDEX													(EM_START + 231)//瀵嗙爜杈撳叆浣嶇储寮?	
#define EM_DC_NEW_PASSCODE0														(EM_START + 232)//杈撳叆鏂板瘑鐮?			
#define EM_DC_NEW_PASSCODE1														(EM_START + 233)//杈撳叆鏂板瘑鐮?			
#define EM_DC_NEW_PASSCODE2														(EM_START + 234)//杈撳叆鏂板瘑鐮?			
#define EM_DC_NEW_PASSCODE3														(EM_START + 235)//杈撳叆鏂板瘑鐮?						
/*****************************************************************************/
#define EM_LASER_RELEASE_TIME													(EM_START + 240)//瀹為檯婵€鍏夊彂灏勭疮璁℃椂闂?2BIT	
#define EM_LASER_RELEASE_ENERGY												(EM_START + 242)//瀹為檯婵€鍏夊彂灏勭疮璁¤兘閲?2BIT
#define EM_LASER_TRIG_TIME														(EM_START + 244)//婵€鍏夎Е鍙戞椂闂?2BIT
/*****************************************************************************/
#define EM_CALI_CUR_SET_CH0														(EM_START + 250)//閫氶亾0鏍″噯璁剧疆鐢垫祦
#define EM_CALI_CUR_SET_CH1														(EM_START + 251)//閫氶亾1鏍″噯璁剧疆鐢垫祦
#define EM_CALI_CUR_SET_CH2														(EM_START + 252)//閫氶亾2鏍″噯璁剧疆鐢垫祦
#define EM_CALI_CUR_SET_CH3														(EM_START + 253)//閫氶亾3鏍″噯璁剧疆鐢垫祦
#define EM_CALI_CUR_SET_CH4														(EM_START + 254)//閫氶亾4鏍″噯璁剧疆鐢垫祦
#define EM_CALI_CUR_SET_CH5														(EM_START + 255)//閫氶亾5鏍″噯璁剧疆鐢垫祦
#define EM_CALI_CUR_SET_CH6														(EM_START + 256)//閫氶亾6鏍″噯璁剧疆鐢垫祦
#define EM_CALI_CUR_SET_CH7														(EM_START + 257)//閫氶亾7鏍″噯璁剧疆鐢垫祦
/*****************************************************************************/
//RTC 鏃堕挓
#define EM_RTC_YEAR																		(EM_START + 300)//
#define EM_RTC_MONTH																	(EM_START + 301)//
#define EM_RTC_DAY																		(EM_START + 302)//
#define EM_RTC_HOURS																	(EM_START + 303)//
#define EM_RTC_MINUTES																(EM_START + 304)//
#define EM_RTC_SECONDS																(EM_START + 305)//
/*****************************************************************************/
#define FD_LASER_SCHEME_NAME													(FD_START +  0)//鏂规鍚嶇О
#define FD_LASER_CHANNEL_SELECT												(FD_START +  51)//婵€鍏夐€氶亾閫夋嫨
#define FD_LASER_PULSE_MODE														(FD_START +  52)//鑴夊啿妯″紡
#define FD_LASER_POWER_CH0														(FD_START +  53)//閫氶亾1470鍔熺巼
#define FD_LASER_POWER_CH1														(FD_START +  54)//閫氶亾980鍔熺巼
#define FD_LASER_POWER_CH2														(FD_START +  55)//澶囩敤閫氶亾
#define FD_LASER_POWER_CH3														(FD_START +  56)//澶囩敤閫氶亾
#define FD_LASER_POWER_CH4														(FD_START +  57)//澶囩敤閫氶亾
#define FD_LASER_POWER_CH5														(FD_START +  58)//澶囩敤閫氶亾
#define FD_LASER_POWER_CH6														(FD_START +  59)//澶囩敤閫氶亾
#define FD_LASER_POWER_CH7														(FD_START +  60)//澶囩敤閫氶亾
#define FD_LASER_POWER_RED														(FD_START +  61)//绾㈡縺鍏夊姛鐜?
#define FD_LASER_POSWIDTH															(FD_START +  62)//澶氳剦鍐叉鑴夊
#define FD_LASER_NEGWIDTH															(FD_START +  63)//澶氳剦鍐茶礋鑴夊
/*****************************************************************************/
#define FD_SCHEME_START_0															(FD_START +  0)//鑷畾涔?瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_0																(FD_START +  63)//鑷畾涔?瀛樺偍鍖虹粨鏉?	

#define FD_SCHEME_START_1															(FD_START +  64)//鑷畾涔?瀛樺偍鍖鸿捣濮?	
#define FD_SCHEME_END_1																(FD_START +  127)//鑷畾涔?瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_2															(FD_START +  128)//鑷畾涔?瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_2																(FD_START +  191)//鑷畾涔?瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_3															(FD_START +  192)//鑷畾涔?瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_3																(FD_START +  255)//鑷畾涔?瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_4															(FD_START +  256)//鑷畾涔?瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_4																(FD_START +  319)//鑷畾涔?瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_5															(FD_START +  320)//鑷畾涔?瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_5																(FD_START +  383)//鑷畾涔?瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_6															(FD_START +  384)//鑷畾涔?瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_6																(FD_START +  447)//鑷畾涔?瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_7															(FD_START +  448)//鑷畾涔?瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_7																(FD_START +  511)//鑷畾涔?瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_8															(FD_START +  512)//鑷畾涔?瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_8																(FD_START +  575)//鑷畾涔?瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_9															(FD_START +  576)//鑷畾涔?瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_9																(FD_START +  639)//鑷畾涔?瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_10														(FD_START +  640)//鑷畾涔?0瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_10															(FD_START +  703)//鑷畾涔?0瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_11														(FD_START +  704)//鑷畾涔?1瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_11															(FD_START +  767)//鑷畾涔?1瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_12														(FD_START +  768)//鑷畾涔?2瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_12															(FD_START +  831)//鑷畾涔?2瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_13														(FD_START +  832)//鑷畾涔?3瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_13															(FD_START +  895)//鑷畾涔?3瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_14														(FD_START +  896)//鑷畾涔?4瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_14															(FD_START +  959)//鑷畾涔?4瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_15														(FD_START +  960)//鑷畾涔?5瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_15															(FD_START + 1023)//鑷畾涔?5瀛樺偍鍖虹粨鏉?
/*****************************************************************************/
#define FD_SCHEME_START_16														(FD_START + 1024)//鑷畾涔?6瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_16															(FD_START + 1087)//鑷畾涔?6瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_17														(FD_START + 1088)//鑷畾涔?7瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_17															(FD_START + 1151)//鑷畾涔?7瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_18														(FD_START + 1152)//鑷畾涔?8瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_18															(FD_START + 1215)//鑷畾涔?8瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_19														(FD_START + 1216)//鑷畾涔?9瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_19															(FD_START + 1279)//鑷畾涔?9瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_20														(FD_START + 1280)//鑷畾涔?0瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_20															(FD_START + 1343)//鑷畾涔?0瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_21														(FD_START + 1344)//鑷畾涔?1瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_21															(FD_START + 1407)//鑷畾涔?1瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_22														(FD_START + 1408)//鑷畾涔?2瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_22															(FD_START + 1471)//鑷畾涔?2瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_23														(FD_START + 1472)//鑷畾涔?3瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_23															(FD_START + 1535)//鑷畾涔?3瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_24														(FD_START + 1536)//鑷畾涔?4瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_24															(FD_START + 1599)//鑷畾涔?4瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_25														(FD_START + 1600)//鑷畾涔?5瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_25															(FD_START + 1663)//鑷畾涔?5瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_26														(FD_START + 1664)//鑷畾涔?6瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_26															(FD_START + 1727)//鑷畾涔?6瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_27														(FD_START + 1728)//鑷畾涔?7瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_27															(FD_START + 1791)//鑷畾涔?7瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_28														(FD_START + 1792)//鑷畾涔?8瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_28															(FD_START + 1855)//鑷畾涔?8瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_29														(FD_START + 1856)//鑷畾涔?9瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_29															(FD_START + 1919)//鑷畾涔?9瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_30														(FD_START + 1920)//鑷畾涔?0瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_30															(FD_START + 1983)//鑷畾涔?0瀛樺偍鍖虹粨鏉?

#define FD_SCHEME_START_31														(FD_START + 1984)//鑷畾涔?1瀛樺偍鍖鸿捣濮?
#define FD_SCHEME_END_31															(FD_START + 2047)//鑷畾涔?1瀛樺偍鍖虹粨鏉?
/*****************************************************************************/
#define TMP_REG_0																			(TMP_START + 0)//涓存椂鍚嶇О鍌ㄥ瓨鍖?
#define TMP_REG_1																			(TMP_START + 1)//涓存椂鍚嶇О鍌ㄥ瓨鍖?
#define TMP_REG_2																			(TMP_START + 2)//涓存椂鍚嶇О鍌ㄥ瓨鍖?
#define TMP_REG_3																			(TMP_START + 3)//涓存椂鍚嶇О鍌ㄥ瓨鍖?
#define TMP_REG_4																			(TMP_START + 4)//涓存椂鍚嶇О鍌ㄥ瓨鍖?
#define TMP_REG_5																			(TMP_START + 5)//涓存椂鍚嶇О鍌ㄥ瓨鍖?
#define TMP_REG_6																			(TMP_START + 6)//涓存椂鍚嶇О鍌ㄥ瓨鍖?
#define TMP_REG_7																			(TMP_START + 7)//涓存椂鍚嶇О鍌ㄥ瓨鍖?
#define TMP_REG_8																			(TMP_START + 8)//涓存椂鍚嶇О鍌ㄥ瓨鍖?
#define TMP_REG_9																			(TMP_START + 9)//涓存椂鍚嶇О鍌ㄥ瓨鍖?
#define TMP_REG_10																		(TMP_START + 10)//涓存椂鍚嶇О鍌ㄥ瓨鍖?
#define TMP_REG_11																		(TMP_START + 11)//涓存椂鍚嶇О鍌ㄥ瓨鍖?
#define TMP_REG_12																		(TMP_START + 12)//涓存椂鍚嶇О鍌ㄥ瓨鍖?
#define TMP_REG_13																		(TMP_START + 13)//涓存椂鍚嶇О鍌ㄥ瓨鍖?
#define TMP_REG_14																		(TMP_START + 14)//涓存椂鍚嶇О鍌ㄥ瓨鍖?
#define TMP_REG_15																		(TMP_START + 15)//涓存椂鍚嶇О鍌ㄥ瓨鍖?
/*****************************************************************************/
#define DM_SCHEME_CLASSIFY														(DM_START + 0)//閫夋嫨鐨勬柟妗堝垎绫?
#define DM_SCHEME_INDEX																(DM_START + 1)//閫夋嫨鐨勬柟妗堢储寮?
#define DM_BEEM_VOLUME																(DM_START + 2)//铚傞福鍣ㄩ煶閲?0-100% 32+3=35
#define DM_RAIM_BRG																		(DM_START + 3)//绾㈡寚绀烘縺鍏変寒搴?
#define DM_GAIM_BRG																		(DM_START + 4)//缁挎寚绀烘縺鍏変寒搴?
#define DM_LCD_BRG																		(DM_START + 5)//灞忓箷浜害
#define DM_DC_OLD_PASSCODE0														(DM_START + 6)//灞忔棫瀵嗙爜0-1
#define DM_DC_OLD_PASSCODE1														(DM_START + 7)//灞忔棫瀵嗙爜2-3
#define DM_DC_OLD_PASSCODE2														(DM_START + 8)//灞忔棫瀵嗙爜0-1
#define DM_DC_OLD_PASSCODE3														(DM_START + 9)//灞忔棫瀵嗙爜2-3
#define DM_LANGUAGE																		(DM_START + 10)//璇█浠ｇ爜
/*****************************************************************************/
#define X_ESTOP_NC																		(X_START * 16 + 0)//XIN0 绱ф€ュ仠姝㈠紑鍏?
#define X_INTERLOCK_NC																(X_START * 16 + 1)//XIN1 瀹夊叏杩為攣
#define X_FOOTSWITCH_NO																(X_START * 16 + 2)//XIN2 鑴氳笍甯稿紑
#define X_FOOTSWITCH_NC																(X_START * 16 + 3)//XIN3 鑴氳笍甯搁棴
#define X_FIBER_PROBE																	(X_START * 16 + 4)//XIN4 鍏夌氦鎺㈡祴
#define X_PWR_KEY																			(X_START * 16 + 5)//XIN5 鐢垫簮寮€鍏?
#define X_PWR_INT																			(X_START * 16 + 6)//XIN6 杞叧鏈轰俊鍙?
/*****************************************************************************/
#define Y_GREEN_LED																		(Y_START * 16 + 0)//YOUT0 缁跨伅寮€鍏?
#define Y_RED_LED																			(Y_START * 16 + 1)//YOUT1 绾㈢伅寮€鍏?
#define Y_YELLOW_LED																	(Y_START * 16 + 2)//YOUT2 钃濈伅寮€鍏?
#define Y_TICK_LED																		(Y_START * 16 + 3)//YOUT3 鏉胯浇杩愯LED鎸囩ず鐏?
#define Y_ERR_LED																			(Y_START * 16 + 4)//YOUT4 鏉胯浇閿欒LED鎸囩ず鐏?
#define Y_BEEM_LED																		(Y_START * 16 + 5)//YOUT5 鏉胯浇閿欒LED鎸囩ず鐏?
#define Y_TEC																					(Y_START * 16 + 6)//YOUT6 TEC杈撳嚭
#define Y_VN5016_INPUT																(Y_START * 16 + 7)//YOUT7 VN5016寮€閫?
#define Y_VN5016_CSDIS																(Y_START * 16 + 8)//YOUT8 鐢垫簮鐢垫祦閲囬泦	
#define Y_PWR_LED																			(Y_START * 16 + 9)//YOUT9 鐢垫簮鎸囩ず鐏?
#define Y_PWR_SOFTKILL																(Y_START * 16 + 10)//YOUT10 鐢垫簮绠＄悊杞叧鏈轰俊鍙?
#define Y_ESTOP_RESET																		(Y_START * 16 + 11)//YOUT11 急停复位输出
typedef enum{//风扇通道
	FAN_CH0 = 0, FAN_CH1, FAN_CH2, FAN_CH3, FAN_CH4, FAN_CH5, FAN_CH6, FAN_CH7
}FAN_CHANNLE_ENMU;

/*****************************************************************************/
#define R_ESTOP																				(R_START * 16 + 0)//鎬ュ仠鏍囧織
#define R_INTERLOCK																		(R_START * 16 + 1)//杩為攣鏍囧織
#define R_FIBER_PROBE																	(R_START * 16 + 2)//鍏夌氦鎻掑叆鏍囧織
#define R_RFID_PASS																		(R_START * 16 + 3)//NFC鍏夌氦鎻掑叆鏍囧織

#define R_LASER_A_DIODE_TEMP_HIGH											(R_START * 16 + 10)//婵€鍏変簩鏋佺A婵€鍏夋ā鍧楅珮娓╂爣蹇?
#define R_LASER_A_DIODE_TEMP_LOW											(R_START * 16 + 11)//婵€鍏変簩鏋佺A婵€鍏夋ā鍧椾綆娓╂爣蹇?
#define R_LASER_B_DIODE_TEMP_HIGH											(R_START * 16 + 12)//婵€鍏変簩鏋佺B婵€鍏夋ā鍧楅珮娓╂爣蹇?
#define R_LASER_B_DIODE_TEMP_LOW											(R_START * 16 + 13)//婵€鍏変簩鏋佺B婵€鍏夋ā鍧椾綆娓╂爣蹇?

#define R_LASER_A_COUPLER_TEMP_HIGH										(R_START * 16 + 14)//婵€鍏変簩鏋佺A鑰﹀悎鍣ㄤ綆娓╂爣蹇?
#define R_LASER_A_COUPLER_TEMP_LOW										(R_START * 16 + 15)//婵€鍏変簩鏋佺A鑰﹀悎鍣ㄤ綆娓╂爣蹇?
#define R_LASER_B_COUPLER_TEMP_HIGH										(R_START * 16 + 16)//婵€鍏変簩鏋佺B鑰﹀悎鍣ㄤ綆娓╂爣蹇?
#define R_LASER_B_COUPLER_TEMP_LOW										(R_START * 16 + 17)//婵€鍏変簩鏋佺B鑰﹀悎鍣ㄤ綆娓╂爣蹇?

#define R_LASER_A_CRYST0_TEMP_HIGH										(R_START * 16 + 18)//婵€鍏変簩鏋佺A鏅朵綋0楂樻俯鏍囧織
#define R_LASER_A_CRYST0_TEMP_LOW											(R_START * 16 + 19)//婵€鍏変簩鏋佺A鏅朵綋0浣庢俯鏍囧織
#define R_LASER_A_CRYST1_TEMP_HIGH										(R_START * 16 + 20)//婵€鍏変簩鏋佺A鏅朵綋1楂樻俯鏍囧織
#define R_LASER_A_CRYST1_TEMP_LOW											(R_START * 16 + 21)//婵€鍏変簩鏋佺A鏅朵綋1浣庢俯鏍囧織

#define R_LASER_B_CRYST0_TEMP_HIGH										(R_START * 16 + 22)//婵€鍏変簩鏋佺B鏅朵綋0楂樻俯鏍囧織
#define R_LASER_B_CRYST0_TEMP_LOW											(R_START * 16 + 23)//婵€鍏変簩鏋佺B鏅朵綋0浣庢俯鏍囧織
#define R_LASER_B_CRYST1_TEMP_HIGH										(R_START * 16 + 24)//婵€鍏変簩鏋佺B鏅朵綋1楂樻俯鏍囧織
#define R_LASER_B_CRYST1_TEMP_LOW											(R_START * 16 + 25)//婵€鍏変簩鏋佺B鏅朵綋1浣庢俯鏍囧織

#define R_HT0_TEMP_HIGH																(R_START * 16 + 26)//鏁ｇ儹鍣?楂樻俯鏍囧織
#define R_HT1_TEMP_HIGH																(R_START * 16 + 27)//鏁ｇ儹鍣?楂樻俯鏍囧織
#define R_HT2_TEMP_HIGH																(R_START * 16 + 28)//鏁ｇ儹鍣?楂樻俯鏍囧織
#define R_HT3_TEMP_HIGH																(R_START * 16 + 29)//鏁ｇ儹鍣?楂樻俯鏍囧織

#define R_HWATER_TEMP_HIGH														(R_START * 16 + 30)//鐑按楂樻俯鎶ヨ鏍囧織
#define R_HWATER_TEMP_LOW															(R_START * 16 + 31)//鐑按浣庢俯鎶ヨ鏍囧織
#define R_CWATER_TEMP_HIGH														(R_START * 16 + 32)//鍐锋按楂樻俯鎶ヨ鏍囧織
#define R_CWATER_TEMP_LOW															(R_START * 16 + 33)//鍐锋按浣庢俯鎶ヨ鏍囧織
#define R_AMBIENT0_TEMP_HIGH													(R_START * 16 + 34)//鐜0楂樻俯鎶ヨ鏍囧織
#define R_AMBIENT0_TEMP_LOW														(R_START * 16 + 35)//鐜0浣庢俯鎶ヨ鏍囧織
#define R_AMBIENT1_TEMP_HIGH													(R_START * 16 + 36)//鐜1楂樻俯鎶ヨ鏍囧織
#define R_AMBIENT1_TEMP_LOW														(R_START * 16 + 37)//鐜1浣庢俯鎶ヨ鏍囧織
#define R_AMBIENT2_TEMP_HIGH													(R_START * 16 + 38)//鐜0楂樻俯鎶ヨ鏍囧織
#define R_AMBIENT2_TEMP_LOW														(R_START * 16 + 39)//鐜0浣庢俯鎶ヨ鏍囧織
#define R_AMBIENT3_TEMP_HIGH													(R_START * 16 + 40)//鐜1楂樻俯鎶ヨ鏍囧織
#define R_AMBIENT3_TEMP_LOW														(R_START * 16 + 41)//鐜1浣庢俯鎶ヨ鏍囧織
#define R_HDC1080_TEMP_HIGH														(R_START * 16 + 42)//鏉胯浇鐜楂樻俯鎶ヨ鏍囧織
#define R_HDC1080_TEMP_LOW														(R_START * 16 + 43)//鏉胯浇鐜浣庢俯鎶ヨ鏍囧織
#define R_HDC1080_HUMIDITY_HIGH												(R_START * 16 + 44)//鏉胯浇鐜楂樻箍搴︽姤璀︽爣蹇?
#define R_HDC1080_HUMIDITY_LOW												(R_START * 16 + 45)//鏉胯浇鐜浣庢俯鎶ヨ鏍囧織
#define R_DHT11_TEMP_HIGH															(R_START * 16 + 46)//杩滅▼鐜楂樻俯鎶ヨ鏍囧織			
#define R_DHT11_TEMP_LOW															(R_START * 16 + 47)//杩滅▼鐜浣庢俯鎶ヨ鏍囧織
#define R_DHT11_HUMIDITY_HIGH													(R_START * 16 + 48)//杩滅▼楂樻箍搴︽姤璀︽爣蹇?
#define R_DHT11_HUMIDITY_LOW													(R_START * 16 + 49)//杩滅▼浣庢箍搴︽姤璀︽爣蹇?
#define R_MCU_TEMP_HIGH																(R_START * 16 + 50)//澶勭悊鍣ㄩ珮娓╂爣蹇?
#define R_MCU_TEMP_LOW																(R_START * 16 + 51)//澶勭悊鍣ㄤ綆娓╂爣蹇?
#define R_MBAT_TEMP_HIGH															(R_START * 16 + 52)//涓荤數姹犻珮娓╂爣蹇?
#define R_MBAT_TEMP_LOW																(R_START * 16 + 53)//涓荤數姹犱綆娓╂爣蹇?
#define R_HWATER_FLOW_LOW															(R_START * 16 + 54)//鐑按浣庢祦閲忔姤璀?
#define R_CWATER_FLOW_LOW															(R_START * 16 + 55)//鍐锋按浣庢祦閲忔姤璀?

#define R_FOOTSWITCH_PLUG															(R_START * 16 + 56)//鑴氳笍鎻掑叆鏍囧織
#define R_FOOTSWITCH_PRESS														(R_START * 16 + 57)//鑴氳笍鎸変笅鏍囧織
#define R_HMI_FOOTSWITCH_PRESS												(R_START * 16 + 58)//灞忓箷妯℃嫙鑴氳笍鎸変笅鏍囧織
#define R_FAULT																				(R_START * 16 + 59)//鏁呴殰鏍囧織
#define R_TEMP_FAULT																	(R_START * 16 + 60)//娓╁害鏁呴殰鏍囧織
#define R_FLOW_FAULT																	(R_START * 16 + 61)//娴侀噺鏁呴殰鏍囧織
#define R_HUMIDITY_FALUT															(R_START * 16 + 62)//婀垮害鏁呴殰鏍囧織
#define R_DISABLE_ESTOP_CHECK													(R_START * 16 + 63)//灞忚斀鎬ュ仠寮€鍏虫娴?
#define R_DISABLE_TEMPERATURE_CHECK										(R_START * 16 + 64)//灞忚斀娓╁害妫€娴?
#define R_DISABLE_FLOW_CHECK													(R_START * 16 + 65)//灞忚斀娴侀噺妫€娴?
#define R_DISABLE_HUMIDITY_CHECK											(R_START * 16 + 66)//灞忚斀婀垮害妫€娴?
#define	R_DISABLE_FOOTSWITCH_CHECK										(R_START * 16 + 67)//灞忚斀鑴氳笍寮€鍏虫娴?
#define R_DISABLE_RFID_CHECK													(R_START * 16 + 68)//灞忚斀NFC妫€娴?
#define R_DISABLE_FIBER_PROBE_CHECK										(R_START * 16 + 69)//灞忚斀鍏夌氦鎺㈡祴
#define R_DISABLE_AUTO_FAN														(R_START * 16 + 70)//灞忚斀鑷姩椋庢墖鎺у埗
#define R_DISABLE_INTERLOCK_CHECK											(R_START * 16 + 71)//灞忚斀瀹夊叏杩為攣
#define R_CLEAR_EPROM																	(R_START * 16 + 72)//瀹屽叏娓呯┖EPROM
#define R_SAVE_EPROM																	(R_START * 16 + 73)//鍌ㄥ瓨SAVE
#define R_ENGINEER_MODE																(R_START * 16 + 74)//宸ョ▼甯堟ā寮?
#define R_ACOUSTIC_ENABLE															(R_START * 16 + 75)//浣胯兘鎻愮ず闊?
#define R_CLEAR_CRC																		(R_START * 16 + 76)//娓呴櫎鍥轰欢CRC
#define R_UPDATE_BOOTLOAD_REQ													(R_START * 16 + 77)//璇锋眰鏇存柊寮曞鍥轰欢
#define R_UPDATE_BOOTLOAD_YES													(R_START * 16 + 78)//鍚屾剰鏇存柊鍥轰欢
#define R_UPDATE_BOOTLOAD_NO													(R_START * 16 + 79)//鍚﹀畾鏇存柊鍥轰欢
//HMI鐩稿叧鐘舵€?
#define R_DCHMI_RESET_REQ															(R_START * 16 + 80)//HMI澶嶄綅璇锋眰
#define R_DCHMI_RESET_DOING														(R_START * 16 + 81)//HMI澶嶄綅涓?
#define R_DCHMI_RESET_DONE														(R_START * 16 + 82)//HMI澶嶄綅瀹屾垚	
#define R_DCHMI_UPDATEUI_REQ													(R_START * 16 + 83)//HMI鍐呭鏇存柊璇锋眰
#define R_DCHMI_UPDATEUI_DOING												(R_START * 16 + 84)//HMI鍐呭鏇存柊涓?
#define R_DCHMI_UPDATEUI_DONE													(R_START * 16 + 85)//HMI鍐呭鏇存柊璇锋眰瀹屾垚
#define R_DCHMI_RESTORE_REQ														(R_START * 16 + 86)//HMI浠嶧LASH涓仮澶嶈缃姹?
#define R_DCHMI_RESTORE_DOING													(R_START * 16 + 87)//HMI浠嶧LASH涓仮澶嶄腑
#define R_DCHMI_RESTORE_DONE													(R_START * 16 + 88)//HMI浠嶧LASH涓仮澶嶈缃畬鎴?
#define R_DCHMI_DISPLAY_WARN													(R_START * 16 + 89)//HMI鏄剧ず鎶ヨ淇℃伅
#define R_DCHMI_KEY_STANDBY_ENABLE										(R_START * 16 + 90)//STANDBY 浣胯兘
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
#define R_STANDBY_KEY_SAVE_TREATMENT_DOWN							(R_START * 16 + 124)
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
#define R_DIAGNOSIS_GOTO_CORRECTION_DOWN							(R_START * 16 + 204)
/*****************************************************************************/
#define R_DIAGNOSIS_RAW_RETURN_DOWN										(R_START * 16 + 210)
#define R_DIAGNOSIS_RAW_RETURN_UP											(R_START * 16 + 211)
/*****************************************************************************/
#define R_DIAGNOSIS_CORRECTION_RETURN_DOWN						(R_START * 16 + 220)
/*****************************************************************************/
#define R_RENAME_KEY_ENTER_DOWN												(R_START * 16 + 300)
#define R_RENAME_KEY_EXIT_DOWN												(R_START * 16 + 301)
#define R_RENAME_TEXTDISPLAY_READ_DONE								(R_START * 16 + 302)
/*****************************************************************************/
#define MR_FOOSWITCH_HAND_SWITCH											(MR_START * 16 + 10)//鑴氳笍HandSwitch 鑴夊啿鎺у埗
#define MR_BEEP_TONE																	(MR_START * 16 + 11)//铚傞福鍣ㄦā寮?0:SYNC 1:BEEP
/*****************************************************************************/
#define T100MS_HMI_POWERUP_DELAY											0//HMI鍚姩澶嶄綅寤舵椂
#define T100MS_ENTER_PASSCODE_DELAY										1
#define T100MS_READY_BEEM_DELAY												2//杩涘叆READY鐘舵€佸悗铚傞福鍣ㄥ搷寤惰繜
#define T100MS_PULSE_BEEM_DELAY												3//鑴夊啿妯″紡铚傞福鍣ㄥ欢杩?
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
#ifdef __cplusplus
}
#endif
#endif






