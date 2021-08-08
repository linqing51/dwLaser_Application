#ifndef __SPLCCONFIG_H__
#define __SPLCCONFIG_H__
/*****************************************************************************/
#define CONFIG_DEBUG_CHARGE										0//���Գ��
#define CONFIG_DEBUG_DAC										0//����DAC����
#define CONFIG_DEBUB_ADC										0//����ADC����
#define CONFIG_DEBUG_EPROM										0//����EPROM����
#define CONFIG_DEBUG_IO											0//����IO
#define CONFIG_DEBUG_SPK										0//���Է���������
#define CONFIG_DEBUG_LED										0//����ָʾ������
#define CONFIG_DEBUG_AIM										0//����ָʾ������
#define CONFIG_DEBUG_LASER										0//����LASER����
#define CONFIG_DEBUG_SPLC										0//����SPLC����
#define CONFIG_DEBUG_APP										0//����Ӧ�ó���
/*****************************************************************************/
#define STM32_UNIQUE_ID_SIZE 									12//MCU���к�  8*12=96Bit
#define BOOTLOADER_VER											0x00010001//�汾
#define DEVID_H													'0'//�豸ID
#define DEVID_L													'A'//�豸ID
#define BUFFER_SIZE        										((uint16_t)512*64)//512��������
#define CONFIG_JUMP_DELAY										4000//���U��ʱ��
#define FATFS_ROOT												"0:"
#define LOG_FIRMWARE_FILENAME									"/log.txt"//������¼�ļ�
#define CFG_FIRMWARE_FILENAME									"/las.cfg"//���������ļ�
#define LMCU_FIRMWARE_FILENAME									"/ld_mcu.bin"//����MCU�̼���ַ
#define LLCD_FIRMWARE_FILENAME									"/ld_lcd.pkg"//����LCD�̼���ַ
#define SAVE_EPROM_FILENAME										"/seprom.bin"//EPROM->UDISK ��������
#define LOAD_EPROM_FILENAME										"/leprom.bin"//UDISK->EPROM �ָ�����
/*****************************************************************************/
#define CONFIG_SPLC_USING_HW_RNG								0//ʹ��Ӳ�������ģ��
#define CONFIG_SPLC_USING_HW_CRC								0//ʹ��Ӳ��CRCУ��
#define CONFIG_SPLC_USING_LINK_MASTER							0//ʹ������ģʽ
#define CONFIG_SPLC_USING_LINK_SLAVE							0//ʹ�ôӻ�ģʽ
/*****************************************************************************/				
#define CONFIG_SPLC_USING_SPK									1//ʹ�ܰ���������
#define CONFIG_SPLC_MAX_SPK_FREQ								4500L//�������Ƶ��
#define CONFIG_SPLC_MIN_SPL_FREQ								1000L//�������Ƶ��
#define CONFIG_SPLC_DEFAULT_SPK_FREQ							1500L//������Ĭ��Ƶ��
#define CONFIG_SPLC_DEFORM_SPK_FREQ								3000L//����������Ƶ��
/*****************************************************************************/
#define CONFIG_SPLC_USING_IO_INPUT								1//����IOˢ������
#define CONFIG_SPLC_USING_IO_OUTPUT								1//���IOˢ������
#define CONFIG_INPUT_FILTER_TIME								8//���������˲�ɨ������ 1mS * N
/*****************************************************************************/
#define CONFIG_SPLC_USING_LEDAIM								1	
#define CONFIG_SPLC_LEDAIM_FREQ									4000L//LED��AIM��˸Ƶ��
#define CONFIG_SPLC_RLED_ON_DC									15//�������
#define CONFIG_SPLC_RLED_OFF_DC									0//�������
#define CONFIG_SPLC_GLED_ON_DC									15//�̵�����
#define CONFIG_SPLC_GLED_OFF_DC									0//�̵�����
#define CONFIG_SPLC_BLED_ON_DC									15//��������
#define CONFIG_SPLC_BLED_OFF_DC									0//��������
#define CONFIG_SPLC_USING_SPWM									1//ʹ�����PWM����
#define CONFIG_SPLC_FUNTEST										0//����ָ�����
/*****************************************************************************/
#define CONFIG_SPLC_ASSERT										1//����ַ��Χ
#define CONFIG_SPLC_DEV											0x0A01//�豸��
#define CONFIG_SPLC_CLEAR_CODE									0xA58E
#define CONFIG_SOFTPLC_TICK										200L//5mS
/*****************************************************************************/
#define CONFIG_APP_USING_PRESCHEME								1//ʹ��Ԥ��ģʽ
#define CONFIG_APP_USING_PRESCHEME_980							0//ʹ��980nMԤ��
#define CONFIG_APP_USING_PRESCHEME_1470							1//ʹ��1470nMԤ��
/*****************************************************************************/
#define CONFIG_SPLC_USING_EPROM									1//EPROM
#define CONFIG_SPLC_USING_EPROM_TEST							1//EPROM�Լ�
#define CONFIG_SPLC_USING_CLEAR_NVRAM							0//�������NVRAM����
#define CONFIG_EPROM_SIZE 										CONFIG_AT24C256_SIZE
#define	CONFIG_AT24C64_SIZE										8192
#define	CONFIG_AT24C128_SIZE 									16384
#define	CONFIG_AT24C256_SIZE 									32768//32K*8
#define CONFIG_EPROM_WRITE_ADDR									0xA0//
#define CONFIG_EPROM_READ_ADDR									0xA1//
#define CONFIG_EPROM_TIMEOUT									1000//EPROM��д��ʱ
#define CONFIG_EPROM_PAGE_SIZE									0x08//EPROM ҳ��С
#define CONFIG_EPROM_WRITE_DELAY								0//д��ȴ�ʱ��mS
/*****************************************************************************/
#define CONFIG_EPROM_MR_START									(0x0L)//
#define CONFIG_EPROM_DM_START									(CONFIG_MRRAM_SIZE * 2)//NVRAM��DM��EPROM�����ַ
#define CONFIG_EPROM_FD_START									(CONFIG_EPROM_DM_START + (CONFIG_DMRAM_SIZE * 2))

#define CONFIG_EPROM_FWINFO_START								(7424L)//128B �̼���Ϣ��
#define CONFIG_EPROM_FWINFO_END									(7551L)
#define CONFIG_EPROM_CONFIG_START								(7552L)//512B ������Ϣ��
#define CONFIG_EPROM_CONFIG_END									(8063L)
#define CONFIG_EPROM_LOGINFO_START								(8064L)//128B ��¼��Ϣ�� 
#define CONFIG_EPROM_LOGINFO_END								(8191L)
/*****************************************************************************/
#define CONFIG_SPLC_USING_ADC									1//ʹ��ADCģ��
#define CONFIG_SPLC_ADC_CHANNEL									10//ADC�ɼ�ͨ��
#define CONFIG_SPLC_ADC_AVERAGE_NUM								6//ADCƽ��ֵ����
#define CONFIG_ADC_DMA_BUFFER_SIZE								(CONFIG_SPLC_ADC_CHANNEL * CONFIG_SPLC_ADC_AVERAGE_NUM)//ADC DMA�ɼ�����
#define CONFIG_AMBIENT_TEMP             						25// Ambient temp in deg C
#define CONFIG_ADC_VREFINT										1121//STM32 �ڲ���׼��ѹ
#define CONFIG_VREF_CAL                         				*(__IO uint16_t *)(0x1FFF7A2A)//У����ѹԴ
#define CONFIG_ADC_INTERNAL_VREF     							3400// ADC Voltage Reference (mV)
#define CONFIG_ADC_AVG_SLOPE									2.5F
#define CONFIG_ADC_V25											760.0F//0.76V@25D
#define CONFIG_NTC_RS											3300L
#define CONFIG_NTC_B											3477.0F
#define CONFIG_NTC_R25											10000.0F//25���϶�ʱ����
#define CONFIG_NTC_VREF											5000L//
#define CONFIG_FIBER_PD_THRESHOLD								400//���˲���ʱADC��ֵ
/*****************************************************************************/
#define CONFIG_SPLC_USING_DAC									1//����DACģ��
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
#define CONFIG_SPLC_USING_DK25L									0//SPLCʹ��NFC����
#define CONFIG_SPLC_USING_DK25L_OVERTIME						500
#define CONFIG_DK25L_RXBUF_SIZE									16
#define CONFIG_DK25L_TXBUF_SIZE									16
/*****************************************************************************/
#define CONFIG_SPLC_USING_LASER									1
#define CONFIG_SPLC_USING_LASER_TEST							0
/*****************************************************************************/
#define CONFIG_USING_DCHMI_APP									1//�㶫����˻�����Ӧ��
#define CONFIG_DCHMI_DISKBUF_SIZE								0x80//��ʾ��������С
/*****************************************************************************/
#define CONFIG_WAIT_HMI_DELAY_TIME								50
#define CONFIG_WAIT_PASSWORD_DELAY_TIME							5
#define CONFIG_KEY_REPEAT_DELAY_TIME							100
#define CONFIG_STANDBY_BEEM_DELAY_TIME							20
/*****************************************************************************/
#define CONFIG_APP_DIODE_BURN_TEMP								300//�������������¶� 30.0C
#define CONFIG_APP_DIODE_HIGH_TEMP								500//���������¼��� 46.0C
#define CONFIG_APP_DIODE_LOW_TEMP								-100//���������¼��� - 10.0C
#define CONFIG_APP_ENVI_HIGH_TEMP								700//���������¼��� 75.0C
/*****************************************************************************/
#define CONFIG_USING_SINGLE_WAVE								1//������
#define CONFIG_USING_DUAL_WAVE									0//˫����
#define CONFIG_USING_TRIPE_WAVE									0//������
#define CONFIG_USING_QUAD_WAVE									0//�Ĳ���
#define CONFIG_USING_FIVE_WAVE									0//�岨��
#define CONFIG_HMI_SCHEME_NUM									32//������
#define CONFIG_HMI_DEFAULT_PASSWORD0							0x3532//Ĭ������
#define CONFIG_HMI_DEFAULT_PASSWORD1							0x3038//Ĭ������
#define CONFIG_HMI_DEFAULT_PASSWORD2							0x3030//Ĭ������
#define CONFIG_HMI_DEFAULT_PASSWORD3							0x3030//Ĭ������
#define CONFIG_SCHEME_NAME_SIZE									((FD_LASER_SELECT - FD_LASER_SCHEME_NAME -1) * 2)//10*2
//���ֱ������
#define DERMA_SPOT_SIZE_0MM5									0x100A//���ֱ��0.5					
#define DERMA_SPOT_SIZE_1MM0									0x200B//���ֱ��1.0
#define DERMA_SPOT_SIZE_2MM0									0x300C//���ֱ��2.0
#define DERMA_SPOT_SIZE_3MM0									0x400D//���ֱ��3.0

#define CONFIG_MAX_LASER_DAC_CH0								0xFFF//
#define CONFIG_MAX_LASER_DAC_CH1								0xFFF//
#define CONFIG_MAX_LASER_DAC_CH2								0xFFF
#define CONFIG_MAX_LASER_DAC_CH3								0xFFF

#define CONFIG_MAX_LASERPOWER_CH0								150//ͨ��0��󼤹⹦��
#define CONFIG_MAX_LASERPOWER_CH1								150//ͨ��1��󼤹⹦��
#define CONFIG_MAX_LASERPOWER_CH2								100//ͨ��2��󼤹⹦��
#define CONFIG_MAX_LASERPOWER_CH3								100//ͨ��3��󼤹⹦��

#define CONFIG_MIN_LASERPOWER_CH0								1//ͨ��0��С���⹦��
#define CONFIG_MIN_LASERPOWER_CH1								1//ͨ��1��С���⹦��
#define CONFIG_MIN_LASERPOWER_CH2								1//ͨ��2��󼤹⹦��
#define CONFIG_MIN_LASERPOWER_CH3								1//ͨ��3��󼤹⹦��

#define CONFIG_LASER_THRESHOLD_CH0								0010//ͨ��0������ֵ����
#define CONFIG_LASER_THRESHOLD_CH1								9999//ͨ��1������ֵ����
#define CONFIG_LASER_THRESHOLD_CH2								9999//ͨ��2������ֵ����
#define CONFIG_LASER_THRESHOLD_CH3								9999//ͨ��3������ֵ����
#define CONFIG_LASER_THRESHOLD_CH4								9999//ͨ��4������ֵ����

#define CONFIG_MAX_LASER_POSWIDTH								15000
#define CONFIG_MIN_LASER_POSWIDTH								1
#define CONFIG_MAX_LASER_NEGWIDTH								15000
#define CONFIG_MIN_LASER_NEGWIDTH								1
#define CONFIG_MAX_LASER_TIMES									10//���ɼ���������
#define CONFIG_MIN_LASER_TIMES									1//��С�ɼ���������
#define CONFIG_MAX_LASER_GROUP_OFF								1000
#define CONFIG_MIN_LASER_GROUP_OFF								10
#define CONFIG_MAX_LASER_ENERGY_INTERVAL						200
#define CONFIG_MIN_LASER_ENERGY_INTERVAL						30
#define CONFIG_STEP_LASER_ENERGY_INTERVAL						10
#define CONFIG_BEEM_ENERGY_INTERVAL_TIME						300//��������ʱ��

#define CONFIG_MAX_AIM_BRG										100//���������ռ�ձ�
#define CONFIG_MIN_AIM_BRG										1//�����С����ռ�ձ�
#define CONFIG_MAX_BEEM_VOLUME									100//�������������
#define CONFIG_MIN_BEEM_VOLUME									1//��������С����
#define CONFIG_MAX_LCD_BRG										100//��Ļ�������ֵ
#define CONFIG_MIN_LCD_BRG										1//��Ļ������Сֵ
#define CONFIG_COOL_SET_TEMP									280//��ȴ�¶�
#define CONFIG_COOL_DIFF_TEMP									15//��ȴ�¶ȱ仯��Χ
//�����趨У��ϵ��
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
//������ʾУ��ϵ��
#define PD_NOTES_INTERCEPT										-0.16355			
#define PD_NOTES_B1												1.82066E-5
#define PD_NOTES_B2												-2.75859E-13
#define PD_NOTES_B3												7.12301E-20
/*****************************************************************************/
#define CONFIG_USING_DEFAULT_SCHEME								1//����Ԥ��ģʽ
#define CONFIG_MAX_SCHEME_NAME_SIZE								40//�������Ƴ���
/******************************************************************************/
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
//��Ȧ ���� 16 * 32 = 512 
#define MR_START												0
#define MR_END   												31
//���ݼĴ��� ���� 512
#define DM_START												32
#define DM_END													543
//��Ȧ�Ĵ��� �Ǳ��� 16 * 32 = 512
#define R_START													544
#define R_END													575						
//���ݼĴ��� �Ǳ��� 512
#define EM_START												576
#define EM_END													1087
//��ʱ��Ȧ
//1MS  16 * 4 = 64
#define T_1MS_START												1088
#define T_1MS_END												1091
//10MS 16 * 4 = 64
#define T_10MS_START											1092
#define T_10MS_END												1095
//100MS 16 * 4 = 64
#define T_100MS_START											1096
#define T_100MS_END												1099
//��ʱ��ʹ��
//1MS  16 * 4 = 64
#define T_1MS_ENA_START											1100
#define T_1MS_ENA_END											1103
//10MS 16 * 4 = 64
#define T_10MS_ENA_START										1104
#define T_10MS_ENA_END											1107
//100MS 16 * 4 = 64
#define T_100MS_ENA_START										1108
#define T_100MS_ENA_END											1111
//��ʱ��ʱ��
//1MS   64
#define TD_1MS_START											1112
#define TD_1MS_END												1175
//10MS  64
#define TD_10MS_START											1176											
#define TD_10MS_END												1239
//100MS 64
#define TD_100MS_START											1240
#define TD_100MS_END											1303
//����λ�Ĵ��� 16 * 8 = 128
#define X_START													1304
#define X_END													1311
//���λ�Ĵ��� 16 * 8 = 128
#define Y_START													1312
#define Y_END													1319
//����Ĵ��� 64
#define SPREG_START												1320
#define SPREG_END												1383
//������Ȧ 16 * 16 = 256
#define SPCOIL_START											1384
#define SPCOIL_END												1399
//��ʱ�Ĵ��� 64
#define TMP_START												1400
#define TMP_END													1463
/*****************************************************************************/
#define CONFIG_NVRAM_SIZE 										(TMP_END + 1)
/*****************************************************************************/
//�浵�Ĵ���
#define FD_START												0
#define FD_END													2047
/*****************************************************************************/
#define CONFIG_MRRAM_SIZE										(MR_END - MR_START + 1)									
#define CONFIG_DMRAM_SIZE										(DM_END - DM_START + 1)
#define CONFIG_FDRAM_SIZE										(FD_END - FD_START + 1)
/*****************************************************************************/
#define CONFIG_LKSRAM_SIZE										128//
#define CONFIG_LKRRAM_SIZE										128//
/*****************************************************************************/
#define SPCOIL_ON												(SPCOIL_START * 16 + 0)//��ͨ��Ȧ
#define SPCOIL_START_UP											(SPCOIL_START * 16 + 1)//�����ϵ�
#define SPCOIL_PS10MS											(SPCOIL_START * 16 + 2)//10mS
#define SPCOIL_PS50MS											(SPCOIL_START * 16 + 3)//50mS
#define SPCOIL_PS100MS											(SPCOIL_START * 16 + 4)//100mS
#define SPCOIL_PS200MS											(SPCOIL_START * 16 + 5)//200mS
#define SPCOIL_PS500MS											(SPCOIL_START * 16 + 6)//500mS
#define SPCOIL_PS1000MS											(SPCOIL_START * 16 + 7)//1000mS
#define SPCOIL_PS1MINS											(SPCOIL_START * 16 + 8)//1mins
#define SPCOIL_MODBUS_S0_ERROR									(SPCOIL_START * 16 + 9)//Modbus Slave->Uart0 ����
#define SPCOIL_NVRAM_FAIL										(SPCOIL_START * 16 + 10)//NVRAMУ�������
#define SPCOIL_WATCHDOG_OVERFLOW								(SPCOIL_START * 16 + 11)//���Ź����
/*****************************************************************************/
#define SPCOIL_LINK_SEND_BUSY									(SPCOIL_START * 16 + 16)//���ͽ�����
#define SPCOIL_LINK_SEND_DONE									(SPCOIL_START * 16 + 17)//�������
#define SPCOIL_LINK_SEND_ERR									(SPCOIL_START * 16 + 18)//���ʹ���
#define SPCOIL_LINK_RECE_BUSY									(SPCOIL_START * 16 + 19)//���ս�����
#define SPCOIL_LINK_RECE_DONE									(SPCOIL_START * 16 + 20)//�������
#define SPCOIL_LINK_RECE_ERR									(SPCOIL_START * 16 + 21)//���ʹ���
/*****************************************************************************/
#define SPCOIL_BEEM_ENABLE										(SPCOIL_START * 16 + 32)//������ʹ��
#define SPCOIL_BEEM_BUSY										(SPCOIL_START * 16 + 33)//����������״̬
#define SPCOIL_AIM_ENABEL										(SPCOIL_START * 16 + 34)//��׼��ʹ��
#define SPCOIL_AIM_BUSY											(SPCOIL_START * 16 + 35)//��׼�⹤��״̬
/*****************************************************************************/
#define SPCOIL_SPWM_OUT_0										(SPCOIL_START * 16 + 48)//SPWM0���״̬
#define SPCOIL_SPWM_RESET_0										(SPCOIL_START * 16 + 49)//SPWM0��λ
#define SPCOIL_SPWM_OUT_1										(SPCOIL_START * 16 + 50)//SPWM1���״̬
#define SPCOIL_SPWM_RESET_1										(SPCOIL_START * 16 + 51)//SPWM1��λ
#define SPCOIL_SPWM_OUT_2										(SPCOIL_START * 16 + 52)//SPWM2���״̬
#define SPCOIL_SPWM_RESET_2										(SPCOIL_START * 16 + 53)//SPWM2��λ
#define SPCOIL_SPWM_OUT_3										(SPCOIL_START * 16 + 54)//SPWM3���״̬
#define SPCOIL_SPWM_RESET_3										(SPCOIL_START * 16 + 55)//SPWM3��λ
/*****************************************************************************/
#define SPCOIL_DK25L_INIT_FAIL									(SPCOIL_START * 16 + 64)//NFCģ���ʼ��ʧ��
#define SPCOIL_LASER_DRIVER_INIT_FAIL							(SPCOIL_START * 16 + 65)//������������ʼ��ʧ��
#define SPCOIL_WIRELESS_FOOTCONTROL_INIT_FAIL					(SPCOIL_START * 16 + 66)//���߽�̤��ʼ��ʧ��
#define SPCOIL_PROBATION_INIT_FAIL								(SPCOIL_START * 16 + 67)//�����ڳ�ʼ��ʧ��
/*****************************************************************************/
#define SPCOIL_DK25L_RXCMD_DONE									(SPCOIL_START * 16 + 80)//����ָ�����
#define SPCOIL_DK25L_RXCMD_DOING								(SPCOIL_START * 16 + 81)//����ָ�������
#define SPCOIL_DK25L_RXCMD_OVERFLOW								(SPCOIL_START * 16 + 82)//����ָ�����
#define SPCOIL_DK25L_RXCMD_ERROR								(SPCOIL_START * 16 + 83)//����ָ����
#define SPCOIL_DK25L_TXCMD_DONE									(SPCOIL_START * 16 + 84)//дָ�����
#define SPCOIL_DK25L_TXCMD_DOING								(SPCOIL_START * 16 + 85)//дָ�������
#define SPCOIL_DK25L_TXCMD_OVERFLOW								(SPCOIL_START * 16 + 86)//дָ�����
#define SPCOIL_DK25L_TXCMD_ERROR								(SPCOIL_START * 16 + 87)//дָ�����
/*****************************************************************************/
#define SPREG_LINK_DEVICE_ID									(SPREG_START + 0)//�����豸ID
#define SPREG_LINK_SEND_SIZE									(SPREG_START + 1)//�����ֽ���
#define SPREG_LINK_RECE_SIZE									(SPREG_START + 2)//�����ֽ���
#define SPREG_LINK_SEND_OVERTIME								(SPREG_START + 3)//���ͳ�ʱ����
#define SPREG_LINK_RECE_OVERTIME								(SPREG_START + 4)//���ճ�ʱ����
#define SPREG_LINK_SEND_TCOUNTER								(SPREG_START + 5)//����ʱ���ʱ��
#define SPREG_LINK_RECE_TCOUNTER								(SPREG_START + 6)//����ʱ���ʱ��
#define SPREG_LINK_STATE										(SPREG_START + 7)//״̬
/*****************************************************************************/
#define SPREG_ADC_0												(SPREG_START + 10)//ADC0�ɼ�ֵ LPA_ISMON0     1320
#define SPREG_ADC_1												(SPREG_START + 11)//ADC1�ɼ�ֵ LASER_NTC
#define SPREG_ADC_2												(SPREG_START + 12)//ADC2�ɼ�ֵ LASER_PD
#define SPREG_ADC_3												(SPREG_START + 13)//ADC3�ɼ�ֵ FIBER_PD
#define SPREG_ADC_4												(SPREG_START + 14)//ADC4�ɼ�ֵ LPC_ISMON0
#define SPREG_ADC_5												(SPREG_START + 15)//ADC5�ɼ�ֵ LPB_ISMON1
#define SPREG_ADC_6												(SPREG_START + 16)//ADC6�ɼ�ֵ LPB_ISMON0
#define SPREG_ADC_7												(SPREG_START + 17)//ADC7�ɼ�ֵ LPA_ISMON1
#define SPREG_ADC_8												(SPREG_START + 18)//ADC8�ɼ�ֵ Ƭ���¶ȴ�����
#define SPREG_ADC_9												(SPREG_START + 19)//ADC9�ɼ�ֵ Ƭ�ڻ�׼Դ

#define SPREG_DAC_0												(SPREG_START + 20)//DAC0�趨ֵ LSET0
#define SPREG_DAC_1												(SPREG_START + 21)//DAC1�趨ֵ LSET1
#define SPREG_DAC_2												(SPREG_START + 22)//DAC2�趨ֵ LSET2
#define SPREG_DAC_3												(SPREG_START + 23)//DAC3�趨ֵ LSET3
#define SPREG_DAC_4												(SPREG_START + 24)//DAC3�趨ֵ LSET4
#define SPREG_DAC_5												(SPREG_START + 25)//DAC3�趨ֵ LSET5
#define SPREG_DAC_6												(SPREG_START + 26)//DAC3�趨ֵ LSET6
#define SPREG_DAC_7												(SPREG_START + 27)//DAC3�趨ֵ LSET7
/*****************************************************************************/
#define SPREG_SPWM_POS_0										(SPREG_START + 30)//���PWM0����������
#define SPREG_SPWM_POS_SHADOW_0									(SPREG_START + 31)//���PWM0��������Ӱ
#define SPREG_SPWM_CYCLE_0										(SPREG_START + 32)//���PWM0��������
#define SPREG_SPWM_CYCLE_SHADOW_0								(SPREG_START + 33)//���PWM0������Ӱ
#define SPREG_SPWM_COUNTER_0									(SPREG_START + 34)//���PWM0������
#define SPREG_SPWM_POS_1										(SPREG_START + 35)//���PWM1����������
#define SPREG_SPWM_POS_SHADOW_1									(SPREG_START + 36)//���PWM1��������Ӱ
#define SPREG_SPWM_CYCLE_1										(SPREG_START + 37)//���PWM1��������
#define SPREG_SPWM_CYCLE_SHADOW_1								(SPREG_START + 38)//���PWM1������Ӱ
#define SPREG_SPWM_COUNTER_1									(SPREG_START + 39)//���PWM1������
#define SPREG_SPWM_POS_2										(SPREG_START + 40)//���PWM2����������
#define SPREG_SPWM_POS_SHADOW_2									(SPREG_START + 41)//���PWM2��������Ӱ
#define SPREG_SPWM_CYCLE_2										(SPREG_START + 42)//���PWM2��������
#define SPREG_SPWM_CYCLE_SHADOW_2								(SPREG_START + 43)//���PWM2������Ӱ
#define SPREG_SPWM_COUNTER_2									(SPREG_START + 44)//���PWM2������
#define SPREG_SPWM_POS_3										(SPREG_START + 45)//���PWM3����������
#define SPREG_SPWM_POS_SHADOW_3									(SPREG_START + 46)//���PWM3��������Ӱ
#define SPREG_SPWM_CYCLE_3										(SPREG_START + 47)//���PWM3��������
#define SPREG_SPWM_CYCLE_SHADOW_3								(SPREG_START + 48)//���PWM3������Ӱ
#define SPREG_SPWM_COUNTER_3									(SPREG_START + 49)//���PWM3������
/*****************************************************************************/
#define SPREG_BEEM_VOLUME										(SPREG_START + 55)//���������� 0-100% 1320+55=1375
#define SPREG_BEEM_FREQ											(SPREG_START + 56)//������Ƶ��        1320+56=1376
#define SPREG_BEEM_MODE											(SPREG_START + 57)//������ģʽ        1320+57=1377
#define SPREG_BEEM_COUNTER										(SPREG_START + 58)//��������ʱ��      1320+58=1378
/*****************************************************************************/
#define SPREG_DK25L_VER											(SPREG_START + 59)//DK25L NFCģ��汾
/*****************************************************************************/
#define SPREG_CLEAR_NVRAM										(SPREG_END - 4)//���NVRAM����������
#define SPREG_TICK_L											(SPREG_END - 3)//�ۼ�����ʱ�� ���λ
#define SPREG_TICK_H											(SPREG_END - 2)//�ۼ�����ʱ�� ���λ
#define SPREG_SCAN_TIME											(SPREG_END - 1)//ɨ��ʱ��
#define SPREG_IDENTITY											(SPREG_END - 0)//ƽ̨ID��
/*****************************************************************************/
#define EM_LASER_SCHEME_NAME									(EM_START + 0)//��������
#define EM_LASER_SELECT											(EM_START + 46)//ͨ��ѡ��
#define EM_LASER_PULSE_MODE										(EM_START + 47)//����ģʽ
#define EM_LASER_POWER_CH0										(EM_START + 48)//ͨ��0����
#define EM_LASER_POWER_CH1										(EM_START + 49)//ͨ��1����
#define EM_LASER_POWER_CH2										(EM_START + 50)//ͨ��2����
#define EM_LASER_POWER_CH3										(EM_START + 51)//ͨ��3����
#define EM_LASER_POWER_CH4										(EM_START + 52)//ͨ��4����
#define EM_LASER_SP_POSWIDTH									(EM_START + 53)//������������
#define EM_LASER_MP_POSWIDTH									(EM_START + 54)//������������
#define EM_LASER_MP_NEGWIDTH									(EM_START + 55)//�����帺����
#define EM_LASER_GP_POSWIDTH									(EM_START + 56)//Group����������
#define EM_LASER_GP_NEGWIDTH									(EM_START + 57)//Group���帺����
#define EM_LASER_GP_TIMES										(EM_START + 58)//Group������
#define EM_LASER_GP_GROUP_OFF									(EM_START + 59)//Group������
#define EM_LASER_SIGNAL_ENERGY_INTERVAL							(EM_START + 60)//SIGNAL�������
#define EM_LASER_DERMA_POSWIDTH									(EM_START + 61)//DERMA������
#define EM_LASER_DERMA_NEGWIDTH									(EM_START + 62)//DERMA������
#define EM_LASER_DERMA_SPOT_SIZE								(EM_START + 63)//DERMA���ֱ��
/*****************************************************************************/
#define EM_LASER_AVERAGE_POWER									(EM_START + 64)//����ģʽƽ������
#define EM_LASER_FREQUENCY										(EM_START + 65)//��ǰģʽƵ��
#define EM_LASER_DUTY_CYCLE										(EM_START + 66)//��ǰģʽռ�ձ� 
/*****************************************************************************/
#define EM_LASER_TEMP											(EM_START + 67)//���������ģ���¶�
#define EM_MCU_TEMP												(EM_START + 68)//�������¶�
#define EM_LASER_CURRENT_CH0									(EM_START + 69)//���������ģ�����
#define EM_LASER_CURRENT_CH1									(EM_START + 70)//���������ģ�����
#define EM_LASER_CURRENT_CH2									(EM_START + 71)//���������ģ�����
#define EM_LASER_CURRENT_CH3									(EM_START + 72)//���������ģ�����
#define EM_LASER_CURRENT_CH4									(EM_START + 73)//���������ģ�����
#define EM_LASER_PHOTODIODE										(EM_START + 74)//���������ģ�鹦��
/*****************************************************************************/				
#define EM_TOTAL_POWER											(EM_START + 80)//�����ܹ���
#define EM_HMI_OPERA_STEP										(EM_START +	81)//��������								
#define EM_ERROR_CODE											(EM_START + 82)//������					
#define EM_SCHEME_NUM_TMP										(EM_START + 83)//��ȷ�Ϸ������			
#define EM_DK25L_VER											(EM_START + 84)//DK25Lģ��汾
/*****************************************************************************/
#define EM_DC_PAGE												(EM_START + 90)//HMIҳ���� 			
#define EM_DC_PASSCODE_INDEX									(EM_START + 91)//��������λ����		
#define EM_DC_NEW_PASSCODE0										(EM_START + 92)//����������0			
#define EM_DC_NEW_PASSCODE1										(EM_START + 93)//����������1			
#define EM_DC_NEW_PASSCODE2										(EM_START + 94)//����������2			
#define EM_DC_NEW_PASSCODE3										(EM_START + 95)//����������3			
#define EM_DC_DEFAULT_PASSCODE0									(EM_START + 96)//Ĭ������0				
#define EM_DC_DEFAULT_PASSCODE1									(EM_START + 97)//Ĭ������1				
#define EM_DC_DEFAULT_PASSCODE2									(EM_START + 98)//Ĭ������2	
#define EM_DC_DEFAULT_PASSCODE3									(EM_START + 99)//Ĭ������3				
#define EM_DC_DISPLAY_RELEASE_TIME								(EM_START + 100)//��ʾ����ʱ��			
#define EM_DC_DISPLAY_RELEASE_ENERGY							(EM_START + 101)//��ʾ��������

#define EM_TPID_START											(EM_START + 128)//
#define EM_TPID_END												(EM_START + 128 + 32)//
/*****************************************************************************/
#define FD_LASER_SCHEME_NAME									(FD_START +  0)//��������
#define FD_LASER_SELECT											(FD_START +  46)//ͨ��ѡ��
#define FD_LASER_PULSE_MODE										(FD_START +  47)//����ģʽ
#define FD_LASER_POWER_CH0										(FD_START +  48)//ͨ��0����
#define FD_LASER_POWER_CH1										(FD_START +  49)//ͨ��1����
#define FD_LASER_POWER_CH2										(FD_START +  50)//ͨ��2����
#define FD_LASER_POWER_CH3										(FD_START +  51)//ͨ��3����
#define FD_LASER_POWER_CH4										(FD_START +  52)//ͨ��4����
#define FD_LASER_SP_POSWIDTH									(FD_START +  53)//������������
#define FD_LASER_MP_POSWIDTH									(FD_START +  54)//������������
#define FD_LASER_MP_NEGWIDTH									(FD_START +  55)//�����帺����
#define FD_LASER_GP_POSWIDTH									(FD_START +  56)//Group����������
#define FD_LASER_GP_NEGWIDTH									(FD_START +  57)//Group���帺����
#define FD_LASER_GP_TIMES										(FD_START +  58)//Group������
#define FD_LASER_GP_GROUP_OFF									(FD_START +  59)//Group������
#define FD_LASER_SIGNAL_ENERGY_INTERVAL							(FD_START +  60)//SIGNAL�������
#define FD_LASER_DERMA_POSWIDTH									(FD_START +  61)//DERMA������
#define FD_LASER_DERMA_NEGWIDTH									(FD_START +  62)//DERMA������
#define FD_LASER_DERMA_SPOT_SIZE								(FD_START +  63)//DERMA���ֱ��

#define FD_SCHEME_START_0										(FD_START +   0)//����0�洢����ʼ
#define FD_SCHEME_END_0											(FD_START +  63)//����0�洢������		

#define FD_SCHEME_START_1										(FD_START +  64)//����1�洢����ʼ		
#define FD_SCHEME_END_1											(FD_START +  127)//����1�洢������

#define FD_SCHEME_START_2										(FD_START +  128)//����2�洢����ʼ
#define FD_SCHEME_END_2											(FD_START +  191)//����2�洢������

#define FD_SCHEME_START_3										(FD_START +  192)//����3�洢����ʼ
#define FD_SCHEME_END_3											(FD_START +  255)//����3�洢������

#define FD_SCHEME_START_4										(FD_START +  256)//����4�洢����ʼ
#define FD_SCHEME_END_4											(FD_START +  319)//����4�洢������

#define FD_SCHEME_START_5										(FD_START +  320)//����5�洢����ʼ
#define FD_SCHEME_END_5											(FD_START +  383)//����5�洢������

#define FD_SCHEME_START_6										(FD_START +  384)//����6�洢����ʼ
#define FD_SCHEME_END_6											(FD_START +  447)//����6�洢������

#define FD_SCHEME_START_7										(FD_START +  448)//����7�洢����ʼ
#define FD_SCHEME_END_7											(FD_START +  511)//����7�洢������

#define FD_SCHEME_START_8										(FD_START +  512)//����8�洢����ʼ
#define FD_SCHEME_END_8											(FD_START +  575)//����8�洢������

#define FD_SCHEME_START_9										(FD_START +  576)//����9�洢����ʼ
#define FD_SCHEME_END_9											(FD_START +  639)//����9�洢������

#define FD_SCHEME_START_10										(FD_START +  640)//����10�洢����ʼ
#define FD_SCHEME_END_10										(FD_START +  703)//����10�洢������

#define FD_SCHEME_START_11										(FD_START +  704)//����11�洢����ʼ
#define FD_SCHEME_END_11										(FD_START +  767)//����11�洢������

#define FD_SCHEME_START_12										(FD_START +  768)//����12�洢����ʼ
#define FD_SCHEME_END_12										(FD_START +  831)//����12�洢������

#define FD_SCHEME_START_13										(FD_START +  832)//����13�洢����ʼ
#define FD_SCHEME_END_13										(FD_START +  895)//����13�洢������

#define FD_SCHEME_START_14										(FD_START +  896)//����14�洢����ʼ
#define FD_SCHEME_END_14										(FD_START +  959)//����14�洢������

#define FD_SCHEME_START_15										(FD_START +  960)//����15�洢����ʼ
#define FD_SCHEME_END_15										(FD_START + 1023)//����15�洢������
/*****************************************************************************/
#define FD_SCHEME_START_16										(FD_START + 1024)//����16�洢����ʼ
#define FD_SCHEME_END_16										(FD_START + 1087)//����16�洢������

#define FD_SCHEME_START_17										(FD_START + 1088)//����17�洢����ʼ
#define FD_SCHEME_END_17										(FD_START + 1151)//����17�洢������

#define FD_SCHEME_START_18										(FD_START + 1152)//����18�洢����ʼ
#define FD_SCHEME_END_18										(FD_START + 1215)//����18�洢������

#define FD_SCHEME_START_19										(FD_START + 1216)//����19�洢����ʼ
#define FD_SCHEME_END_19										(FD_START + 1279)//����19�洢������

#define FD_SCHEME_START_20										(FD_START + 1280)//����20�洢����ʼ
#define FD_SCHEME_END_20										(FD_START + 1343)//����20�洢������

#define FD_SCHEME_START_21										(FD_START + 1344)//����21�洢����ʼ
#define FD_SCHEME_END_21										(FD_START + 1407)//����21�洢������

#define FD_SCHEME_START_22										(FD_START + 1408)//����22�洢����ʼ
#define FD_SCHEME_END_22										(FD_START + 1471)//����22�洢������

#define FD_SCHEME_START_23										(FD_START + 1472)//����23�洢����ʼ
#define FD_SCHEME_END_23										(FD_START + 1535)//����23�洢������

#define FD_SCHEME_START_24										(FD_START + 1536)//����24�洢����ʼ
#define FD_SCHEME_END_24										(FD_START + 1599)//����24�洢������

#define FD_SCHEME_START_25										(FD_START + 1600)//����25�洢����ʼ
#define FD_SCHEME_END_25										(FD_START + 1663)//����25�洢������

#define FD_SCHEME_START_26										(FD_START + 1664)//����26�洢����ʼ
#define FD_SCHEME_END_26										(FD_START + 1727)//����26�洢������

#define FD_SCHEME_START_27										(FD_START + 1728)//����27�洢����ʼ
#define FD_SCHEME_END_27										(FD_START + 1791)//����27�洢������

#define FD_SCHEME_START_28										(FD_START + 1792)//����28�洢����ʼ
#define FD_SCHEME_END_28										(FD_START + 1855)//����28�洢������

#define FD_SCHEME_START_29										(FD_START + 1856)//����29�洢����ʼ
#define FD_SCHEME_END_29										(FD_START + 1919)//����29�洢������

#define FD_SCHEME_START_30										(FD_START + 1920)//����30�洢����ʼ
#define FD_SCHEME_END_30										(FD_START + 1983)//����30�洢������

#define FD_SCHEME_START_31										(FD_START + 1984)//����31�洢����ʼ
#define FD_SCHEME_END_31										(FD_START + 2047)//����31�洢������
/*****************************************************************************/
#define TMP_REG_0												(TMP_START + 0)//��ʱ���ƴ�����
#define TMP_REG_1												(TMP_START + 1)//��ʱ���ƴ�����
#define TMP_REG_2												(TMP_START + 2)//��ʱ���ƴ�����
#define TMP_REG_3												(TMP_START + 3)//��ʱ���ƴ�����
#define TMP_REG_4												(TMP_START + 4)//��ʱ���ƴ�����
#define TMP_REG_5												(TMP_START + 5)//��ʱ���ƴ�����
#define TMP_REG_6												(TMP_START + 6)//��ʱ���ƴ�����
#define TMP_REG_7												(TMP_START + 7)//��ʱ���ƴ�����
#define TMP_REG_8												(TMP_START + 8)//��ʱ���ƴ�����
#define TMP_REG_9												(TMP_START + 9)//��ʱ���ƴ�����
#define TMP_REG_10												(TMP_START + 10)//��ʱ���ƴ�����
#define TMP_REG_11												(TMP_START + 11)//��ʱ���ƴ�����
#define TMP_REG_12												(TMP_START + 12)//��ʱ���ƴ�����
#define TMP_REG_13												(TMP_START + 13)//��ʱ���ƴ�����
#define TMP_REG_14												(TMP_START + 14)//��ʱ���ƴ�����
#define TMP_REG_15												(TMP_START + 15)//��ʱ���ƴ�����
#define TMP_REG_16												(TMP_START + 16)//��ʱ���ƴ�����
#define TMP_REG_17												(TMP_START + 17)//��ʱ���ƴ�����
#define TMP_REG_18												(TMP_START + 18)//��ʱ���ƴ�����
#define TMP_REG_19												(TMP_START + 19)//��ʱ���ƴ�����
#define TMP_REG_20												(TMP_START + 20)//��ʱ���ƴ�����
#define TMP_REG_21												(TMP_START + 21)//��ʱ���ƴ�����
#define TMP_REG_22												(TMP_START + 22)//��ʱ���ƴ�����
#define TMP_REG_23												(TMP_START + 23)//��ʱ���ƴ�����
#define TMP_REG_24												(TMP_START + 24)//��ʱ���ƴ�����
#define TMP_REG_25												(TMP_START + 25)//��ʱ���ƴ�����
#define TMP_REG_26												(TMP_START + 26)//��ʱ���ƴ�����
#define TMP_REG_27												(TMP_START + 27)//��ʱ���ƴ�����
#define TMP_REG_28												(TMP_START + 28)//��ʱ���ƴ�����
#define TMP_REG_29												(TMP_START + 29)//��ʱ���ƴ�����
#define TMP_REG_30												(TMP_START + 30)//��ʱ���ƴ�����
#define TMP_REG_31												(TMP_START + 31)//��ʱ���ƴ�����

#define TMP_REG_32												(TMP_START + 32)//��ʱ���ƴ�����
#define TMP_REG_33												(TMP_START + 33)//��ʱ���ƴ�����
#define TMP_REG_34												(TMP_START + 34)//��ʱ���ƴ�����
#define TMP_REG_35												(TMP_START + 35)//��ʱ���ƴ�����
#define TMP_REG_36												(TMP_START + 36)//��ʱ���ƴ�����
#define TMP_REG_37												(TMP_START + 37)//��ʱ���ƴ�����
#define TMP_REG_38												(TMP_START + 38)//��ʱ���ƴ�����
#define TMP_REG_39												(TMP_START + 39)//��ʱ���ƴ�����
#define TMP_REG_40												(TMP_START + 40)//��ʱ���ƴ�����
#define TMP_REG_41												(TMP_START + 41)//��ʱ���ƴ�����
#define TMP_REG_42												(TMP_START + 42)//��ʱ���ƴ�����
#define TMP_REG_43												(TMP_START + 43)//��ʱ���ƴ�����
#define TMP_REG_44												(TMP_START + 44)//��ʱ���ƴ�����
#define TMP_REG_45												(TMP_START + 45)//��ʱ���ƴ�����
#define TMP_REG_46												(TMP_START + 46)//��ʱ���ƴ�����
#define TMP_REG_47												(TMP_START + 47)//��ʱ���ƴ�����
#define TMP_REG_48												(TMP_START + 48)//��ʱ���ƴ�����
#define TMP_REG_49												(TMP_START + 49)//��ʱ���ƴ�����
#define TMP_REG_50												(TMP_START + 50)//��ʱ���ƴ�����
#define TMP_REG_51												(TMP_START + 51)//��ʱ���ƴ�����
#define TMP_REG_52												(TMP_START + 52)//��ʱ���ƴ�����
#define TMP_REG_53												(TMP_START + 53)//��ʱ���ƴ�����
#define TMP_REG_54												(TMP_START + 54)//��ʱ���ƴ�����
#define TMP_REG_55												(TMP_START + 55)//��ʱ���ƴ�����
#define TMP_REG_56												(TMP_START + 56)//��ʱ���ƴ�����
#define TMP_REG_57												(TMP_START + 57)//��ʱ���ƴ�����
#define TMP_REG_58												(TMP_START + 58)//��ʱ���ƴ�����
#define TMP_REG_59												(TMP_START + 59)//��ʱ���ƴ�����
#define TMP_REG_60												(TMP_START + 60)//��ʱ���ƴ�����
#define TMP_REG_61												(TMP_START + 61)//��ʱ���ƴ�����
#define TMP_REG_62												(TMP_START + 62)//��ʱ���ƴ�����
#define TMP_REG_63												(TMP_START + 63)//��ʱ���ƴ�����
/*****************************************************************************/
#define DM_SCHEME_NUM											(DM_START + 0)//ѡ��ķ������ ��8λ������ ��8λ����ʹ��
#define DM_LANGUAGE												(DM_START + 1)//����ID
#define DM_BEEM_VOLUME											(DM_START + 2)//���������� 0-100% 32+3=35
#define DM_AIM_BRG												(DM_START + 3)//ָʾ��������
#define DM_LCD_BRG												(DM_START + 4)//��Ļ����
#define DM_DC_OLD_PASSCODE0										(DM_START + 5)//��������0-1
#define DM_DC_OLD_PASSCODE1										(DM_START + 6)//��������2-3
#define DM_DC_OLD_PASSCODE2										(DM_START + 7)//��������0-1
#define DM_DC_OLD_PASSCODE3										(DM_START + 8)//��������2-3
/*****************************************************************************/
#define X_ESTOP													(X_START * 16 + 0)//XIN0 ����ֹͣ����
#define X_INTERLOCK												(X_START * 16 + 1)//XIN1 ��ȫ����
#define X_FOOTSWITCH_NO											(X_START * 16 + 2)//XIN2 ��̤����
#define X_FOOTSWITCH_NC											(X_START * 16 + 3)//XIN3 ��̤����
#define X_PWR_KEY												(X_START * 16 + 4)//XIN4 ��Դ����
#define X_FIBER_PROBE											(X_START * 16 + 5)//XIN5 ����̽��
/*****************************************************************************/
#define Y_FAN_SP												(Y_START * 16 + 0)//YOUT0 ��Դ���ȿ���
#define Y_FAN_LD												(Y_START * 16 + 1)//YOUT1 ������ȿ���
#define Y_TEC													(Y_START * 16 + 2)//YOUT1 ���俪��
#define Y_GLED													(Y_START * 16 + 3)//YOUT2 �̵ƿ���
#define Y_RLED													(Y_START * 16 + 4)//YOUT3 ��ƿ���
#define Y_BLED													(Y_START * 16 + 5)//YOUT4 ���ƿ���
#define Y_LCDPWR												(Y_START * 16 + 6)//YOUT5 LCD��Դ����
#define Y_RUN_LED												(Y_START * 16 + 7)//YOUT7 ��������LEDָʾ��
#define Y_ERR_LED												(Y_START * 16 + 8)//YOUT8 ���ش���LEDָʾ��
/*****************************************************************************/
#define R_ESTOP													(R_START * 16 + 0)//��ͣ��־
#define R_INTERLOCK												(R_START * 16 + 1)//������־
#define R_FIBER_PROBE											(R_START * 16 + 2)//���˲����־
#define R_RFID_PASS												(R_START * 16 + 3)//NFC���˲����־
#define R_LASER_TEMP_HIGH										(R_START * 16 + 4)//��������ܼ���ģ����±�־
#define R_LASER_TEMP_LOW										(R_START * 16 + 5)//��������ܼ���ģ����±�־
#define R_MCU_TEMP_HIGH											(R_START * 16 + 6)//���������±�־
#define R_MCU_TEMP_LOW											(R_START * 16 + 7)//���������±�־
#define R_FOOTSWITCH_PLUG										(R_START * 16 + 8)//��̤�����־
#define R_FOOTSWITCH_PRESS										(R_START * 16 + 9)//��̤���±�־
#define R_HMI_FOOTSWITCH_PRESS									(R_START * 16 + 10)//��Ļģ���̤���±�־
#define R_FAULT													(R_START * 16 + 11)//���ϱ�־
#define R_DISABLE_ESTOP											(R_START * 16 + 12)//���μ�ͣ���ؼ��
#define R_DISABLE_TEMPERATURE									(R_START * 16 + 13)//�����¶ȼ��
#define	R_DISABLE_FOOTSWITCH									(R_START * 16 + 14)//���ν�̤���ؼ��
#define R_DISABLE_RFID											(R_START * 16 + 15)//����NFC���
#define R_DISABLE_FIBER_PROBE									(R_START * 16 + 16)//���ι���̽��
#define R_DISABLE_FAN_SPEED										(R_START * 16 + 17)//���η��ȿ���
#define R_DISABLE_INTERLOCK										(R_START * 16 + 18)//���ΰ�ȫ����
#define R_CLEAR_EPROM											(R_START * 16 + 19)//��ȫ���EPROM
#define R_ENGINEER_MODE											(R_START * 16 + 20)//����ʦģʽ
//HMI���״̬
#define R_DCHMI_RESET_REQ										(R_START * 16 + 30)//HMI��λ����
#define R_DCHMI_RESET_DOING										(R_START * 16 + 31)//HMI��λ��
#define R_DCHMI_RESET_DONE										(R_START * 16 + 32)//HMI��λ���	
#define R_DCHMI_UPDATEUI_REQ									(R_START * 16 + 33)//HMI���ݸ�������
#define R_DCHMI_UPDATEUI_DOING									(R_START * 16 + 34)//HMI���ݸ�����
#define R_DCHMI_UPDATEUI_DONE									(R_START * 16 + 35)//HMI���ݸ����������
#define R_DCHMI_RESTORE_REQ										(R_START * 16 + 36)//HMI��FLASH�лָ���������
#define R_DCHMI_RESTORE_DOING									(R_START * 16 + 37)//HMI��FLASH�лָ���
#define R_DCHMI_RESTORE_DONE									(R_START * 16 + 38)//HMI��FLASH�лָ��������	
#define R_DCHMI_DISPLAY_WARN									(R_START * 16 + 39)//HMI��ʾ������Ϣ
#define R_DCHMI_KEY_STANDBY_ENABLE								(R_START * 16 + 40)//STANDBY ʹ��
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
#define MR_FOOSWITCH_HAND_SWITCH								(MR_START * 16 + 10)//��̤HandSwitch �������
#define MR_BEEM_TONE											(MR_START * 16 + 11)//������ģʽ
/*****************************************************************************/
#define T100MS_HMI_POWERUP_DELAY								0//HMI������λ��ʱ
#define T100MS_ENTER_PASSCODE_DELAY								1
#define T100MS_READY_BEEM_DELAY									2//����READY״̬����������ӳ�
#define T100MS_PULSE_BEEM_DELAY									3//����ģʽ�������ӳ�
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






