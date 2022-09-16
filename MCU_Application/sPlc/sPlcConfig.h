#ifndef __SPLCCONFIG_H__
#define __SPLCCONFIG_H__
/*****************************************************************************/
//������ʹ��
#define SET_TEC_PWM(b)																HAL_GPIO_WritePin(TEC_OUT_GPIO_Port, TEC_OUT_Pin, b)
#define FLIP_TEC_PWM()																HAL_GPIO_TogglePin(TEC_OUT_GPIO_Port, TEC_OUT_Pin)
#define GET_TEC_PWM()																	HAL_GPIO_ReadPin(TEC_OUT_GPIO_Port, TEC_OUT_Pin)
//ָ��ָʾ��
#define SET_LINK_LED(b)																HAL_GPIO_WritePin(LINK_LED_GPIO_Port, LINK_LED_Pin, b)
#define FLIP_LINK_LED()																HAL_GPIO_TogglePin(LINK_LED_GPIO_Port, LINK_LED_Pin)
#define GET_LINK_LED()																HAL_GPIO_ReadPin(LINK_LED_GPIO_Port, LINK_LED_Pin)
//����ָʾ��
#define SET_ALARM_LED(b)															HAL_GPIO_WritePin(ALARM_LED_OUT_GPIO_Port, ALARM_LED_OUT_Pin, b)
#define FLIP_ALARM_LED()															HAL_GPIO_TogglePin(ALARM_LED_OUT_GPIO_Port, ALARM_LED_OUT_Pin)
#define GET_ALARM_LED()																HAL_GPIO_ReadPin(ALARM_LED_OUT_GPIO_Port, ALARM_LED_OUT_Pin)
//ͨ��1���ⷢ��ָʾ
#define SET_LASER1_LED(b)															HAL_GPIO_WritePin(LASER1_LED_OUT_GPIO_Port, LASER1_LED_OUT_Pin, b)
#define FLIP_LASER1_LED()															HAL_GPIO_TogglePin(LASER1_LED_OUT_GPIO_Port, LASER1_LED_OUT_Pin)
#define GET_LASER1_LED()															HAL_GPIO_ReadPin(LASER1_LED_OUT_GPIO_Port, LASER1_LED_OUT_Pin)
//ͨ��2���ⷢ��ָʾ
#define SET_LASER2_LED(b)															HAL_GPIO_WritePin(LASER2_LED_OUT_GPIO_Port, LASER2_LED_OUT_Pin, b)
#define FLIP_LASER2_LED()															HAL_GPIO_TogglePin(LASER2_LED_OUT_GPIO_Port, LASER2_LED_OUT_Pin)
#define GET_LASER2_LED()															HAL_GPIO_ReadPin(LASER2_LED_OUT_GPIO_Port, LASER2_LED_OUT_Pin)
//��������LED
#define SET_TICK_LED(b)																HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, b)
#define FLIP_TICK_LED()																HAL_GPIO_TogglePin(TICK_LED_GPIO_Port, TICK_LED_Pin)
#define GET_TICK_LED()																HAL_GPIO_ReadPin(TICK_LED_GPIO_Port, TICK_LED_Pin)
//���ش���LED
#define SET_ERR_LED(b)																HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, b)
#define FLIP_ERR_LED(b)																HAL_GPIO_TogglePin(ERR_LED_GPIO_Port, ERR_LED_Pin)
#define GET_ERR_LED()																	HAL_GPIO_ReadPin(ERR_LED_GPIO_Port, ERR_LED_Pin)
//ͨ��1ָʾ��
#define SET_LASER1_AIM(b)															HAL_GPIO_WritePin(LASER1_AIM_GPIO_Port, LASER1_AIM_Pin, b)
#define FLIP_LASER1_AIM()															HAL_GPIO_TogglePin(LASER1_AIM_GPIO_Port, LASER1_AIM_Pin)
#define GET_LASER1_AIM()															HAL_GPIO_ReadPin(LASER1_AIM_GPIO_Port, LASER1_AIM_Pin)
//ͨ��2ָʾ��
#define SET_LASER2_AIM(b)															HAL_GPIO_WritePin(LASER2_AIM_GPIO_Port, LASER2_AIM_Pin, b)
#define FLIP_LASER2_AIM()															HAL_GPIO_TogglePin(LASER2_AIM_GPIO_Port, LASER2_AIM_Pin)
#define GET_LASER2_AIM()															HAL_GPIO_ReadPin(LASER2_AIM_GPIO_Port, LASER2_AIM_Pin)
//����
#define GET_INTERLOCK()																HAL_GPIO_ReadPin(INTERLOCK_IN_GPIO_Port, INTERLOCK_IN_Pin)
//��ͣ
#define GET_ESTOP()																		HAL_GPIO_ReadPin(ESTOP_NC_IN_GPIO_Port, ESTOP_NC_IN_Pin)
//���ʹ��				
#define GET_EXT_ENABLE()															HAL_GPIO_ReadPin(LASER_EXT_ENA_GPIO_Port, LASER_EXT_ENA_Pin)
//��ش���
#define GET_LASER_TRG()																HAL_GPIO_ReadPin(LASER_TRIG_IN_GPIO_Port, LASER_TRIG_IN_Pin)
//ULINK LED
#define SET_ULINK_LED(b)															HAL_GPIO_WritePin(LOCK_LED_GPIO_Port, LOCK_LED_Pin, b)
#define FLIP_ULINK_LED()															HAL_GPIO_TogglePin(LOCK_LED_GPIO_Port, LOCK_LED_Pin)
#define GET_ULINK_LED()																HAL_GPIO_ReadPin(LOCK_LED_GPIO_Port, LOCK_LED_Pin)
//DC-DC�任��ʹ��
#define SET_LASER_PWM(b)															HAL_GPIO_WritePin(LASER_PWM_GPIO_Port, LASER_PWM_Pin, b)
#define FLIP_LASER_PWM()															HAL_GPIO_TogglePin(LASER_PWM_GPIO_Port, LASER_PWM_Pin)
#define GET_LASER_PWM()																HAL_GPIO_ReadPin(LASER_PWM_GPIO_Port, LASER_PWM_Pin)
//SPEAK
#define SET_SPEAK_ENA(b)															HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, b)
#define FLIP_SPEAK_ENA()															HAL_GPIO_TogglePin(SPK_EN_GPIO_Port, SPK_EN_Pin)
#define GET_SPEAK_ENA()																HAL_GPIO_ReadPin(SPK_EN_GPIO_Port, SPK_EN_Pin)
/*****************************************************************************/
#define BEEM_MODE_0																		0x10//����ģʽ
#define BEEM_MODE_1																		0x11//����ͬ��
#define BEEM_MODE_2																		0x12//���ⷢ��̶����
#define BEEM_MODE_3																		0x13//�쳣����
/*****************************************************************************/
#define CONFIG_MORSECODE_SPACE_TIME										3000
#define CONFIG_MORSECODE_LONG_TIME										900
#define CONFIG_MORSECODE_SHORT_TIME										300
/*****************************************************************************/
#define CONFIG_MODBUS_RTU_BAUDRATE										9600//MODBUSͨ�Ų�����
#define CONFIG_RING_BUFFER_SIZE												256//ѭ����������С
#define CONFIG_FREEPROTOCOL_SIZE											64
#define FP_RX_SIZE																		CONFIG_FREEPROTOCOL_SIZE//����Э����ջ���
#define FP_TX_SIZE																		CONFIG_FREEPROTOCOL_SIZE//����Э�鷢�ͻ���
/*****************************************************************************/
#define STM32_UNIQUE_ID_SIZE 													12//MCU���к�  8*12=96Bit
#define DEVID_H																				'1'//�豸ID
#define DEVID_L																				'A'//�豸ID
#define BUFFER_SIZE        														((uint16_t)512*64)//512��������
#define CONFIG_JUMP_DELAY															5000//���U��ʱ��
#define FATFS_ROOT																		"0:"
#define LOG_FIRMWARE_FILENAME													"/log.txt"//������¼�ļ�
#define CFG_FIRMWARE_FILENAME													"/las.cfg"//���������ļ�
#define LMCU_FIRMWARE_FILENAME												"/ld_mcu.bin"//����MCU�̼���ַ
#define LLCD_FIRMWARE_FILENAME												"/ld_lcd.pkg"//����LCD�̼���ַ
#define SAVE_EPROM_FILENAME														"/seprom.bin"//EPROM->UDISK ��������
#define LOAD_EPROM_FILENAME														"/leprom.bin"//UDISK->EPROM �ָ�����
/*****************************************************************************/				
#define CONFIG_SPLC_DEFAULT_SPK_FREQ									1500L//������Ĭ��Ƶ��
#define CONFIG_SPLC_MAX_SPK_FREQ											2000L
#define CONFIG_SPLC_MIN_SPK_FREQ											800L
/*****************************************************************************/
#define CONFIG_INPUT_FILTER_TIME											8//���������˲�ɨ������ 1mS * N
/*****************************************************************************/
#define CONFIG_SPLC_ASSERT														1//����ַ��Χ
#define CONFIG_SPLC_DEV																0x0A01//�豸��
#define CONFIG_SPLC_CLEAR_CODE												0xA58E
#define CONFIG_SOFTPLC_TICK														200L//5mS
/*****************************************************************************/
#define CONFIG_SPLC_USING_EPROM												1//EPROM
#define CONFIG_SPLC_USING_EPROM_TEST									0//EPROM ��д����
//EPROM�Լ�
#define CONFIG_EPROM_SIZE 														CONFIG_AT24C64_SIZE
#define	CONFIG_AT24C64_SIZE														8192
#define	CONFIG_AT24C128_SIZE 													16384
#define	CONFIG_AT24C256_SIZE 													32768//32K*8
#define CONFIG_EPROM_WRITE_ADDR												0xA0//
#define CONFIG_EPROM_READ_ADDR												0xA1//
#define CONFIG_EPROM_TIMEOUT													1000//EPROM��д��ʱ
#define CONFIG_EPROM_PAGE_SIZE												0x08//EPROM ҳ��С
#define CONFIG_EPROM_WRITE_DELAY											0//д��ȴ�ʱ��mS
/*****************************************************************************/
#define CONFIG_EPROM_MR_START													(0x0L)//
#define CONFIG_EPROM_MR_END														(CONFIG_EPROM_MR_START + MR_END - MR_START)
#define CONFIG_EPROM_DM_START													(CONFIG_EPROM_MR_END + 1)//NVRAM��DM��EPROM�����ַ
#define CONFIG_EPROM_DM_END														(CONFIG_EPROM_DM_START + DM_END - DM_START)
#define CONFIG_EPROM_FD_START													(CONFIG_EPROM_DM_END + 1)
#define CONFIG_EPROM_FD_END														(CONFIG_EPROM_FD_START + FD_END - FD_START)

#define CONFIG_EPROM_MR_CRC														(7524L)//4B MR NVRAM CRC32 Ӳ������
#define CONFIG_EPROM_DM_CRC														(7528L)//4B DM NVRAM CRC32 Ӳ������
#define CONFIG_EPROM_FD_CRC														(7532L)//4B FD NVRAM CRC32 Ӳ������
#define CONFIG_EPROM_MCU_FW_CRC												(7536L)//4B MCU�̼�CRC32ֵ �������
#define CONFIG_EPROM_LCD_FW_CRC												(7540L)//4B LCD�̼�CRC32ֵ �������
#define CONFIG_EPROM_CFG_CRC													(7544L)//4B deviceConfig CRC32ֵ Ӳ������
#define CONFIG_EPROM_LOG_CRC													(7548L)//4B logInfo CRC32ֵ Ӳ������

#define CONFIG_EPROM_CONFIG_START											(7552L)//512B ������Ϣ��
#define CONFIG_EPROM_CONFIG_END												(8063L)
#define CONFIG_EPROM_LOGINFO_START										(8064L)//128B ��¼��Ϣ�� 
#define CONFIG_EPROM_LOGINFO_END											(8191L)
/*****************************************************************************/
#define CONFIG_SPLC_USING_ADC													1//ʹ��ADCģ��
#define CONFIG_SPLC_ADC_CHANNEL												10//ADC�ɼ�ͨ��
#define CONFIG_SPLC_ADC_AVERAGE_NUM										16//ADCƽ��ֵ����
#define CONFIG_ADC_DMA_BUFFER_SIZE										(CONFIG_SPLC_ADC_CHANNEL * CONFIG_SPLC_ADC_AVERAGE_NUM)//ADC DMA�ɼ�����
#define CONFIG_AMBIENT_TEMP             							25// Ambient temp in deg C
#define CONFIG_VREF_CAL                         			*(__IO uint16_t *)(0x1FFF7A2A)//У����ѹԴ
#define CONFIG_ADC_AVG_SLOPE													2.5F
#define CONFIG_ADC_V25																760.0F//0.76V@25D
#define CONFIG_NTC_RS																	3300L//NTC��ѹ����
#define CONFIG_NTC_B																	3477.0F
#define CONFIG_NTC_R25																10000.0F//25���϶�ʱ����
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
#define CONFIG_DIODE_SET_TEMP													200//�����������¶� 
#define CONFIG_DIODE_DIFF_TEMP												15
#define CONFIG_DIODE_HIGH_TEMP												380//���������¼��� 46.0C
#define CONFIG_DIODE_LOW_TEMP													-100//���������¼��� - 10.0C
#define CONFIG_ENVI_HIGH_TEMP													750//���������¼��� 75.0C
#define CONFIG_DIODE_THRESHOLD												600//���ⷢ����ֵ600mA
#define CONFIG_MAX_LASERPOWER_CH0											150//ͨ��0��󼤹⹦��
#define CONFIG_MAX_LASERPOWER_CH1											150//ͨ��1��󼤹⹦��
#define CONFIG_MAX_LASERPOWER_CH2											100//ͨ��2��󼤹⹦��
#define CONFIG_MAX_LASERPOWER_CH3											100//ͨ��3��󼤹⹦��
#define CONFIG_MIN_LASERPOWER_CH0											1//ͨ��0��С���⹦��
#define CONFIG_MIN_LASERPOWER_CH1											1//ͨ��1��С���⹦��
#define CONFIG_MIN_LASERPOWER_CH2											1//ͨ��2��󼤹⹦��
#define CONFIG_MIN_LASERPOWER_CH3											1//ͨ��3��󼤹⹦��
#define CONFIG_MAX_LASER_POSWIDTH											16000
#define CONFIG_MIN_LASER_POSWIDTH											1
#define CONFIG_MAX_LASER_NEGWIDTH											16000
#define CONFIG_MIN_LASER_NEGWIDTH											1
#define CONFIG_MAX_LASER_TIMES												10//���ɼ���������
#define CONFIG_MIN_LASER_TIMES												1//��С�ɼ���������
#define CONFIG_MAX_LASER_GROUP_OFF										1000
#define CONFIG_MIN_LASER_GROUP_OFF										10
#define CONFIG_MAX_LASER_ENERGY_INTERVAL							200
#define CONFIG_MIN_LASER_ENERGY_INTERVAL							30
#define CONFIG_STEP_LASER_ENERGY_INTERVAL							10
#define CONFIG_BEEM_ENERGY_INTERVAL_TIME							800//��������ʱ��
#define CONFIG_MAX_ACOUSTIC_ENERGY										2000
#define CONFIG_MIN_ACOUSTIC_ENERGY										10
#define CONFIG_MAX_ACOUSTIC_TIME											999
#define CONFIG_MIN_ACOUSTIC_TIME											10
#define CONFIG_BEEM_MAX_VOLUME												100//�������������
#define CONFIG_BEEM_MIN_VOLUME												0//��������С����
/*****************************************************************************/
//��Ȧ ���� 16 * 32 = 512 
#define MR_START																			0
#define MR_END   																			31
//���ݼĴ��� ���� 512
#define DM_START																			32
#define DM_END																				543
//��Ȧ�Ĵ��� �Ǳ��� 16 * 32 = 512
#define R_START																				544
#define R_END																					575						
//���ݼĴ��� �Ǳ��� 512
#define EM_START																			576
#define EM_END																				1087
//��ʱ��Ȧ
//1MS  16 * 4 = 64
#define T_1MS_START																		1088
#define T_1MS_END																			1091
//10MS 16 * 4 = 64
#define T_10MS_START																	1092
#define T_10MS_END																		1095
//100MS 16 * 4 = 64
#define T_100MS_START																	1096
#define T_100MS_END																		1099
//��ʱ��ʹ��
//1MS  16 * 4 = 64
#define T_1MS_ENA_START																1100
#define T_1MS_ENA_END																	1103
//10MS 16 * 4 = 64
#define T_10MS_ENA_START															1104
#define T_10MS_ENA_END																1107
//100MS 16 * 4 = 64
#define T_100MS_ENA_START															1108
#define T_100MS_ENA_END																1111
//��ʱ��ʱ��
//1MS   64
#define TD_1MS_START																	1112
#define TD_1MS_END																		1175
//10MS  64
#define TD_10MS_START																	1176											
#define TD_10MS_END																		1239
//100MS 64
#define TD_100MS_START																1240
#define TD_100MS_END																	1303
//����λ�Ĵ��� 16 * 8 = 128
#define X_START																				1304
#define X_END																					1311
//���λ�Ĵ��� 16 * 8 = 128
#define Y_START																				1312
#define Y_END																					1319
//����Ĵ��� 256
#define SPREG_START																		1320
#define SPREG_END																			1575
//������Ȧ 16 * 16 = 256
#define SPCOIL_START																	1576
#define SPCOIL_END																		1591
//��ʱ�Ĵ��� 64
#define TMP_START																			1592
#define TMP_END																				1655
/*****************************************************************************/
#define CONFIG_NVRAM_SIZE 														(TMP_END + 1)
/*****************************************************************************/
//�浵�Ĵ���
#define FD_START																			0
#define FD_END																				2047
/*****************************************************************************/
#define CONFIG_MRRAM_SIZE															(MR_END - MR_START + 1)									
#define CONFIG_DMRAM_SIZE															(DM_END - DM_START + 1)
#define CONFIG_FDRAM_SIZE															(FD_END - FD_START + 1)
#define CONFIG_LKSRAM_SIZE														1024//����Э�鷢�ͻ���
#define CONFIG_LKRRAM_SIZE														1024//����Э����ջ���
/*****************************************************************************/
#define SPCOIL_ON																			(SPCOIL_START * 16 + 0)//��ͨ��Ȧ
#define SPCOIL_START_UP																(SPCOIL_START * 16 + 1)//�����ϵ�
#define SPCOIL_PS10MS																	(SPCOIL_START * 16 + 2)//10mS
#define SPCOIL_PS50MS																	(SPCOIL_START * 16 + 3)//50mS
#define SPCOIL_PS100MS																(SPCOIL_START * 16 + 4)//100mS
#define SPCOIL_PS200MS																(SPCOIL_START * 16 + 5)//200mS
#define SPCOIL_PS500MS																(SPCOIL_START * 16 + 6)//500mS
#define SPCOIL_PS1000MS																(SPCOIL_START * 16 + 7)//1000mS
#define SPCOIL_PS1MINS																(SPCOIL_START * 16 + 8)//1mins
/*****************************************************************************/
#define SPCOIL_BEEM_ENABLE														(SPCOIL_START * 16 + 32)//������ʹ��
/*****************************************************************************/
#define SPCOIL_SPWM_OUT_0															(SPCOIL_START * 16 + 48)//SPWM0���״̬
#define SPCOIL_SPWM_RESET_0														(SPCOIL_START * 16 + 49)//SPWM0��λ
#define SPCOIL_SPWM_OUT_1															(SPCOIL_START * 16 + 50)//SPWM1���״̬
#define SPCOIL_SPWM_RESET_1														(SPCOIL_START * 16 + 51)//SPWM1��λ
#define SPCOIL_SPWM_OUT_2															(SPCOIL_START * 16 + 52)//SPWM2���״̬
#define SPCOIL_SPWM_RESET_2														(SPCOIL_START * 16 + 53)//SPWM2��λ
#define SPCOIL_SPWM_OUT_3															(SPCOIL_START * 16 + 54)//SPWM3���״̬
#define SPCOIL_SPWM_RESET_3														(SPCOIL_START * 16 + 55)//SPWM3��λ
/*****************************************************************************/
#define SPREG_TICK																		(SPREG_START + 0)//TICK ++
/*****************************************************************************/
#define SPREG_ADC_0																		(SPREG_START + 11)//ADC1-IN0  �ɼ�ֵ LPA_ISMON0
#define SPREG_ADC_1																		(SPREG_START + 12)//ADC1-IN1  �ɼ�ֵ LASER NTC
#define SPREG_ADC_2																		(SPREG_START + 13)//ADC1-IN2  �ɼ�ֵ LASER1_PD
#define SPREG_ADC_3																		(SPREG_START + 14)//ADC1-IN3  �ɼ�ֵ LASER2_PD
#define SPREG_ADC_4																		(SPREG_START + 15)//ADC1-IN10 �ɼ�ֵ LPC_ISMON0
#define SPREG_ADC_5																		(SPREG_START + 16)//ADC1-IN11 �ɼ�ֵ LPB_ISMON1
#define SPREG_ADC_6																		(SPREG_START + 17)//ADC1-IN12 �ɼ�ֵ LPB_ISMON0
#define SPREG_ADC_7																		(SPREG_START + 18)//ADC1-IN13 �ɼ�ֵ LPA_ISMON1
#define SPREG_ADC_8																		(SPREG_START + 19)//ADC1 CHIP TEMPƬ���¶ȴ�����
#define SPREG_ADC_9																		(SPREG_START + 20)//ADC1 CHIP VREFINTƬ�ڻ�׼Դ
/*****************************************************************************/
#define SPREG_DAC_0																		(SPREG_START + 30)//DAC0�趨ֵ ����ͨ��0
#define SPREG_DAC_1																		(SPREG_START + 31)//DAC1�趨ֵ ����ͨ��1
#define SPREG_DAC_2																		(SPREG_START + 32)//DAC2�趨ֵ ����ͨ��2
#define SPREG_DAC_3																		(SPREG_START + 33)//DAC3�趨ֵ ����ͨ��3
#define SPREG_DAC_4																		(SPREG_START + 34)//DAC4�趨ֵ ����ͨ��4
#define SPREG_DAC_5																		(SPREG_START + 35)//DAC5�趨ֵ ����ͨ��5
#define SPREG_DAC_6																		(SPREG_START + 36)//DAC6�趨ֵ ����ͨ��6
#define SPREG_DAC_7																		(SPREG_START + 37)//DAC7�趨ֵ ����ͨ��7
/*****************************************************************************/
#define SPREG_SPWM_POS_0															(SPREG_START + 50)//���PWM0����������
#define SPREG_SPWM_POS_SHADOW_0												(SPREG_START + 51)//���PWM0��������Ӱ
#define SPREG_SPWM_CYCLE_0														(SPREG_START + 52)//���PWM0��������
#define SPREG_SPWM_CYCLE_SHADOW_0											(SPREG_START + 53)//���PWM0������Ӱ
#define SPREG_SPWM_COUNTER_0													(SPREG_START + 54)//���PWM0������
#define SPREG_SPWM_POS_1															(SPREG_START + 55)//���PWM1����������
#define SPREG_SPWM_POS_SHADOW_1												(SPREG_START + 56)//���PWM1��������Ӱ
#define SPREG_SPWM_CYCLE_1														(SPREG_START + 57)//���PWM1��������
#define SPREG_SPWM_CYCLE_SHADOW_1											(SPREG_START + 58)//���PWM1������Ӱ
#define SPREG_SPWM_COUNTER_1													(SPREG_START + 59)//���PWM1������
#define SPREG_SPWM_POS_2															(SPREG_START + 60)//���PWM2����������
#define SPREG_SPWM_POS_SHADOW_2												(SPREG_START + 61)//���PWM2��������Ӱ
#define SPREG_SPWM_CYCLE_2														(SPREG_START + 62)//���PWM2��������
#define SPREG_SPWM_CYCLE_SHADOW_2											(SPREG_START + 63)//���PWM2������Ӱ
#define SPREG_SPWM_COUNTER_2													(SPREG_START + 64)//���PWM2������
#define SPREG_SPWM_POS_3															(SPREG_START + 65)//���PWM3����������
#define SPREG_SPWM_POS_SHADOW_3												(SPREG_START + 66)//���PWM3��������Ӱ
#define SPREG_SPWM_CYCLE_3														(SPREG_START + 67)//���PWM3��������
#define SPREG_SPWM_CYCLE_SHADOW_3											(SPREG_START + 68)//���PWM3������Ӱ
#define SPREG_SPWM_COUNTER_3													(SPREG_START + 69)//���PWM3������
/*****************************************************************************/
#define SPREG_BEEM_VOLUME															(SPREG_START + 70)//���������� 0-100% 1320+55=1375
#define SPREG_BEEM_FREQ																(SPREG_START + 71)//������Ƶ��        1320+56=1376
#define SPREG_BEEM_MODE																(SPREG_START + 72)//������ģʽ        1320+57=1377
#define SPREG_BEEM_COUNTER														(SPREG_START + 73)//��������ʱ��      1320+58=1378
/*****************************************************************************/
#define SPREG_CLEAR_NVRAM															(SPREG_START + 80)//���NVRAM����������
#define SPREG_TICK_L																	(SPREG_START + 81)//�ۼ�����ʱ�� ���λ
#define SPREG_TICK_H																	(SPREG_START + 82)//�ۼ�����ʱ�� ���λ
#define SPREG_SCAN_TIME																(SPREG_START + 83)//ɨ��ʱ��
#define SPREG_IDENTITY																(SPREG_START + 84)//ƽ̨ID��
/*****************************************************************************/
#define SPREG_CHID0_L																	(SPREG_START + 90)//CHIP UUID ������ΨһID
#define SPREG_CHID0_H																	(SPREG_START + 91)//CHIP UUID
#define SPREG_CHID1_L																	(SPREG_START + 92)//CHIP UUID
#define SPREG_CHID1_H																	(SPREG_START + 93)//CHIP UUID
#define SPREG_CHID2_L																	(SPREG_START + 94)//CHIP UUID
#define SPREG_CHID2_H																	(SPREG_START + 95)//CHIP UUID
/*****************************************************************************/
#define DM_ADC_OFFSET_0																(DM_START + 10)//ADC0ƫ����
#define DM_ADC_OFFSET_1																(DM_START + 11)//ADC1ƫ����
#define DM_ADC_OFFSET_2																(DM_START + 12)//ADC2ƫ����
#define DM_ADC_OFFSET_3																(DM_START + 13)//ADC3ƫ����
#define DM_ADC_OFFSET_4																(DM_START + 14)//ADC4ƫ����
#define DM_ADC_OFFSET_5																(DM_START + 15)//ADC5ƫ����
#define DM_ADC_OFFSET_6																(DM_START + 16)//ADC6ƫ����
#define DM_ADC_OFFSET_7																(DM_START + 17)//ADC7ƫ����
#define DM_ADC_OFFSET_8																(DM_START + 18)//ADC8ƫ����
#define DM_ADC_OFFSET_9																(DM_START + 19)//ADC9ƫ����
/*****************************************************************************/
#define EM_LASER_POWER_CH0														(EM_START + 10)//ͨ��0���� 999->99.9%
#define EM_LASER_POWER_CH1														(EM_START + 11)//ͨ��1���� 999->99.9%
#define EM_LASER_PWM_CH0															(EM_START + 12)//ͨ��0ռ�ձ� 100->100%
#define EM_LASER_PWM_CH1															(EM_START + 13)//ͨ��1ռ�ձ� 100->100%
#define EM_LASER_POSWIDTH															(EM_START + 14)//���������� 100->10.0��
#define EM_LASER_TEMP																	(EM_START + 15)//�������¶�
#define EM_MCU_TEMP																		(EM_START + 16)//�������¶�
#define EM_LASER_CURRENT_CH0													(EM_START + 17)//ͨ��0����
#define EM_LASER_CURRENT_CH1													(EM_START + 18)//ͨ��1����
#define EM_LASER_CURRENT_CH2													(EM_START + 19)//ͨ��2����
#define EM_LASER_CURRENT_CH3													(EM_START + 20)//ͨ��3����
#define EM_LASER_CURRENT_CH4													(EM_START + 21)//ͨ��4����
#define EM_LASER_PD_CH0																(EM_START + 22)//ͨ��0 PD
#define EM_LASER_PD_CH1																(EM_START + 23)//ͨ��1 PD
#define EM_SPEAK_VOLUME																(EM_START + 24)//��������
#define EM_LASER_PULSE_MODE														(EM_START + 25)//����ģʽ
#define EM_LASER_TEMP_SET															(EM_START + 26)//������ȴ�¶�
#define EM_COOL_RATE																	(EM_START + 27)//��������ʾ
/*****************************************************************************/
#define R_PARA_LOCK																		(R_START * 16 + 10)//��������
#define R_LASER_START																	(R_START * 16 + 11)//��������
#define R_LASER_STOP																	(R_START * 16 + 12)//����ֹͣ
#define R_AIM_ENABLE_CH0															(R_START * 16 + 13)//ͨ��0 ָʾ������
#define R_AIM_ENABLE_CH1															(R_START * 16 + 14)//ͨ��1 ָʾ������
#define R_ALRAM																				(R_START * 16 + 15)//���ϱ���
#define R_LASER_TEMP_HIGH															(R_START * 16 + 16)//���������±���
#define R_MCU_TEMP_HIGH																(R_START * 16 + 17)//�������±���
#define R_CALIBRATION_MODE														(R_START * 16 + 18)//���ù���У׼
#define R_RETURN_ZERO																	(R_START * 16 + 19)//�ֶ�����
/*****************************************************************************/
#define TMP_REG_0																			(TMP_START + 0)//��ʱ���ƴ�����
#define TMP_REG_1																			(TMP_START + 1)//��ʱ���ƴ�����
#define TMP_REG_2																			(TMP_START + 2)//��ʱ���ƴ�����
#define TMP_REG_3																			(TMP_START + 3)//��ʱ���ƴ�����
#define TMP_REG_4																			(TMP_START + 4)//��ʱ���ƴ�����
#define TMP_REG_5																			(TMP_START + 5)//��ʱ���ƴ�����
#define TMP_REG_6																			(TMP_START + 6)//��ʱ���ƴ�����
#define TMP_REG_7																			(TMP_START + 7)//��ʱ���ƴ�����
#define TMP_REG_8																			(TMP_START + 8)//��ʱ���ƴ�����
#define TMP_REG_9																			(TMP_START + 9)//��ʱ���ƴ�����
#define TMP_REG_10																		(TMP_START + 10)//��ʱ���ƴ�����
#define TMP_REG_11																		(TMP_START + 11)//��ʱ���ƴ�����
#define TMP_REG_12																		(TMP_START + 12)//��ʱ���ƴ�����
#define TMP_REG_13																		(TMP_START + 13)//��ʱ���ƴ�����
#define TMP_REG_14																		(TMP_START + 14)//��ʱ���ƴ�����
#define TMP_REG_15																		(TMP_START + 15)//��ʱ���ƴ�����
#define TMP_REG_16																		(TMP_START + 16)//��ʱ���ƴ�����
#define TMP_REG_17																		(TMP_START + 17)//��ʱ���ƴ�����
#define TMP_REG_18																		(TMP_START + 18)//��ʱ���ƴ�����
#define TMP_REG_19																		(TMP_START + 19)//��ʱ���ƴ�����
#define TMP_REG_20																		(TMP_START + 20)//��ʱ���ƴ�����
#define TMP_REG_21																		(TMP_START + 21)//��ʱ���ƴ�����
#define TMP_REG_22																		(TMP_START + 22)//��ʱ���ƴ�����
#define TMP_REG_23																		(TMP_START + 23)//��ʱ���ƴ�����
#define TMP_REG_24																		(TMP_START + 24)//��ʱ���ƴ�����
#define TMP_REG_25																		(TMP_START + 25)//��ʱ���ƴ�����
#define TMP_REG_26																		(TMP_START + 26)//��ʱ���ƴ�����
#define TMP_REG_27																		(TMP_START + 27)//��ʱ���ƴ�����
#define TMP_REG_28																		(TMP_START + 28)//��ʱ���ƴ�����
#define TMP_REG_29																		(TMP_START + 29)//��ʱ���ƴ�����
#define TMP_REG_30																		(TMP_START + 30)//��ʱ���ƴ�����
#define TMP_REG_31																		(TMP_START + 31)//��ʱ���ƴ�����

#define TMP_REG_32																		(TMP_START + 32)//��ʱ���ƴ�����
#define TMP_REG_33																		(TMP_START + 33)//��ʱ���ƴ�����
#define TMP_REG_34																		(TMP_START + 34)//��ʱ���ƴ�����
#define TMP_REG_35																		(TMP_START + 35)//��ʱ���ƴ�����
#define TMP_REG_36																		(TMP_START + 36)//��ʱ���ƴ�����
#define TMP_REG_37																		(TMP_START + 37)//��ʱ���ƴ�����
#define TMP_REG_38																		(TMP_START + 38)//��ʱ���ƴ�����
#define TMP_REG_39																		(TMP_START + 39)//��ʱ���ƴ�����
#define TMP_REG_40																		(TMP_START + 40)//��ʱ���ƴ�����
#define TMP_REG_41																		(TMP_START + 41)//��ʱ���ƴ�����
#define TMP_REG_42																		(TMP_START + 42)//��ʱ���ƴ�����
#define TMP_REG_43																		(TMP_START + 43)//��ʱ���ƴ�����
#define TMP_REG_44																		(TMP_START + 44)//��ʱ���ƴ�����
#define TMP_REG_45																		(TMP_START + 45)//��ʱ���ƴ�����
#define TMP_REG_46																		(TMP_START + 46)//��ʱ���ƴ�����
#define TMP_REG_47																		(TMP_START + 47)//��ʱ���ƴ�����
#define TMP_REG_48																		(TMP_START + 48)//��ʱ���ƴ�����
#define TMP_REG_49																		(TMP_START + 49)//��ʱ���ƴ�����
#define TMP_REG_50																		(TMP_START + 50)//��ʱ���ƴ�����
#define TMP_REG_51																		(TMP_START + 51)//��ʱ���ƴ�����
#define TMP_REG_52																		(TMP_START + 52)//��ʱ���ƴ�����
#define TMP_REG_53																		(TMP_START + 53)//��ʱ���ƴ�����
#define TMP_REG_54																		(TMP_START + 54)//��ʱ���ƴ�����
#define TMP_REG_55																		(TMP_START + 55)//��ʱ���ƴ�����
#define TMP_REG_56																		(TMP_START + 56)//��ʱ���ƴ�����
#define TMP_REG_57																		(TMP_START + 57)//��ʱ���ƴ�����
#define TMP_REG_58																		(TMP_START + 58)//��ʱ���ƴ�����
#define TMP_REG_59																		(TMP_START + 59)//��ʱ���ƴ�����
#define TMP_REG_60																		(TMP_START + 60)//��ʱ���ƴ�����
#define TMP_REG_61																		(TMP_START + 61)//��ʱ���ƴ�����
#define TMP_REG_62																		(TMP_START + 62)//��ʱ���ƴ�����
#define TMP_REG_63																		(TMP_START + 63)//��ʱ���ƴ�����
/*****************************************************************************/
//1304
#define X_INTERLOCK_NC																(X_START * 16 + 0)//XIN1 ��ȫ����
#define X_EXT_ENABLE																	(X_START * 16 + 1)//XIN2 ���ʹ��	
#define X_LASER_TRIG																	(X_START * 16 + 2)//XIN3 ��ش���
/*****************************************************************************/
#define Y_TICK_LED																		(Y_START * 16 + 0)//YOUT0 ������
#define Y_ERR_LED																			(Y_START * 16 + 1)//YOUT1 �����
#define Y_ALARM_LED																		(Y_START * 16 + 2)//YOUT2 ������
#define Y_ULINK_LED																		(Y_START * 16 + 3)//YOUT3 ͨ��ָ��ִ��ָʾ��
#define Y_LASER1_LED																	(Y_START * 16 + 4)//YOUT4 ͨ��1 ����ָʾ��
#define Y_LASER2_LED																	(Y_START * 16 + 5)//YOUT5 ͨ��2 ����ָʾ��
#define Y_AIM1_ENA																		(Y_START * 16 + 6)//YOUT6 ͨ��1 ָʾ��ʹ��
#define Y_AIM2_ENA																		(Y_START * 16 + 7)//YOUT7 ͨ��2 ָʾ��ʹ��
#define Y_TEC_ENA																			(Y_START * 16 + 8)//YOUT8 ������ʹ��
/*****************************************************************************/


#endif






