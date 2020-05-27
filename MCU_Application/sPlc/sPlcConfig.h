#ifndef __SPLCCONFIG_H__
#define __SPLCCONFIG_H__
/*****************************************************************************/
#define CMD_MUSIC_PLAY											0x01
#define CMD_MUSIC_SUSPEND										0x02
#define CMD_MUSIC_RESUME										0x03
#define CMD_MUSIC_STOP											0x04
/*****************************************************************************/
#define CONFIG_DEBUG_SERIAL_PORT								uart1
#define CONFIG_DEBUG_CHARGE										0//���Գ��
#define CONFIG_DEBUG_DAC										0//����DAC
#define CONFIG_DEBUB_ADC										0//����ADC
#define CONFIG_DEBUG_EPROM										0//����EPROM
#define CONFIG_DEBUG_IO											0//�����������IO
#define CONFIG_DEBUG_BEEM										0//���Է�����
#define CONFIG_DEBUG_MUSIC										0//����LCD����
#define CONFIG_DEBUG_APP										1
/*****************************************************************************/
#define CONFIG_SPLC_USING_MUSIC									1//ʹ��LCD�Դ����ֲ���						
#define CONFIG_SPLC_USING_BEEM									1//ʹ�ܰ��ط�����
#define CONFIG_SPLC_DEFAULT_BEEM_FREQ							4000L//������Ĭ��Ƶ��
#define CONFIG_SPLC_DEFAULT_BEEM_DUTYCYCLE						127//������Ĭ��ռ�ձ�
/*****************************************************************************/
#define CONFIG_SPLC_USING_LEDAIM								1	
#define CONFIG_SPLC_LEDAIM_FREQ									4000L//LED��AIM��˸Ƶ��
#define CONFIG_SPLC_RLED_DEFAULT_DUTYCYCLE						60//�������
#define CONFIG_SPLC_GLED_DEFAULT_DUTYCYCLE						60//�̵�����
#define CONFIG_SPLC_BLED_DEFAULT_DUTYCYCLE						60//��������
/*****************************************************************************/
#define CONFIG_SPLC_USING_SPWM									1//ʹ�����PWM����
/*****************************************************************************/
#define CONFIG_SPLC_FUNTEST										0//����ָ�����
/*****************************************************************************/
#define CONFIG_SPLC_ASSERT										1//����ַ��Χ
#define CONFIG_SPLC_DEV											0x0A01//�豸��
#define CONFIG_SPLC_CLEAR_CODE									0xA58E
#define CONFIG_SOFTPLC_TICK										200L//5mS
#define CONFIG_INPUT_FILTER_TIME								1//���������˲�ɨ������ 1mS * N
/*****************************************************************************/
#define CONFIG_SPLC_USING_IO_INPUT								1//����IOˢ������
/*****************************************************************************/
#define CONFIG_SPLC_USING_IO_OUTPUT								1//���IOˢ������
/*****************************************************************************/
#define CONFIG_SPLC_USING_EPROM									1//EPROM
#define CONFIG_SPLC_USING_EPROM_TEST							1//EPROM�Լ�
#define CONFIG_SPLC_USING_CLEAR_NVRAM							1//�������NVRAM����
#define CONFIG_EPROM_SIZE 										CONFIG_AT24C64_SIZE
#define	CONFIG_AT24C02_SIZE 									256
#define	CONFIG_AT24C04_SIZE  									512
#define	CONFIG_AT24C08_SIZE 									1024
#define	CONFIG_AT24C16_SIZE 									2048
#define	CONFIG_AT24C32_SIZE 									4096
#define	CONFIG_AT24C64_SIZE										8192
#define	CONFIG_AT24C128_SIZE 									16384
#define	CONFIG_AT24C256_SIZE 									32768
#define CONFIG_EPROM_ADDRESS									0x50//EPROM I2C��ַ
#define CONFIG_EPROM_WIRTE_DELAY								10//EPROMд��ʱ�� 10mS
#define CONFIG_EPROM_TIMEOUT									1000//EPROM��д��ʱ
#define CONFIG_EPROM_PAGE_SIZE									32//EPROM ҳ��С
#define CONFIG_EPROM_NVRAM_START								0x0
#define CONFIG_EPROM_FDRAM_START								0x800//2048
/*****************************************************************************/
#define CONFIG_SPLC_USING_ADC									1//ʹ��ADCģ��
#define CONFIG_SPLC_ADC_CHANNEL									10//ADC�ɼ�ͨ��
#define CONFIG_SPLC_ADC_AVERAGE_NUM								8//ADCƽ��ֵ����
#define CONFIG_ADC_DMA_BUFFER_SIZE								(CONFIG_SPLC_ADC_CHANNEL * CONFIG_SPLC_ADC_AVERAGE_NUM)//ADC DMA�ɼ�����
#define CONFIG_ADC_AMBIENT             							25L// Ambient temp in deg C
#define CONFIG_ADC_INTERNAL_VREF     							3300L// ADC Voltage Reference (mV)
#define CONFIG_NTC_RS											3300L
#define CONFIG_NTC_B											3500L
#define CONFIG_NTC_RB											10000L
#define CONFIG_NTC_VREF											3300L
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
#define CONFIG_SPLC_USING_LASER_TEST							1
/*****************************************************************************/
#define CONFIG_USING_DCHMI_APP									1//�㶫����˻�����Ӧ��
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
#define CONFIG_USING_SINGLE_WAVE								0//������
#define CONFIG_USING_DUAL_WAVE									1//˫����
#define CONFIG_USING_TRIPE_WAVE									0//������
#define CONFIG_USING_QUAD_WAVE									0//�Ĳ���
#define CONFIG_USING_FIVE_WAVE									0//�岨��
#define CONFIG_HMI_SCHEME_NUM									32//������
#define CONFIG_HMI_DEFAULT_PASSSWORD0							0x3235//Ĭ������
#define CONFIG_HMI_DEFAULT_PASSSWORD1							0x3830//Ĭ������
#define CONFIG_SCHEME_NAME_SIZE									22//12*2
//���ֱ������
#define DERMA_SPOT_SIZE_0MM5									0x100A//���ֱ��0.5					
#define DERMA_SPOT_SIZE_1MM0									0x200B//���ֱ��1.0
#define DERMA_SPOT_SIZE_2MM0									0x300C//���ֱ��2.0
#define DERMA_SPOT_SIZE_3MM0									0x400D//���ֱ��3.0

#define CONFIG_MAX_LASER_DAC_CH0								0xFFF//
#define CONFIG_MAX_LASER_DAC_CH1								0xFFF//
#define CONFIG_MAX_LASER_DAC_CH2								0xFFF
#define CONFIG_MAX_LASER_DAC_CH3								0xFFF

#define CONFIG_MAX_LASERPOWER_CH0								300//ͨ��0��󼤹⹦��
#define CONFIG_MAX_LASERPOWER_CH1								150//ͨ��1��󼤹⹦��
#define CONFIG_MAX_LASERPOWER_CH2								100//ͨ��2��󼤹⹦��
#define CONFIG_MAX_LASERPOWER_CH3								100//ͨ��3��󼤹⹦��

#define CONFIG_MIN_LASERPOWER_CH0								0//ͨ��0��С���⹦��
#define CONFIG_MIN_LASERPOWER_CH1								0//ͨ��1��С���⹦��
#define CONFIG_MIN_LASERPOWER_CH2								0//ͨ��2��󼤹⹦��
#define CONFIG_MIN_LASERPOWER_CH3								0//ͨ��3��󼤹⹦��

#define CONFIG_MAX_LASER_POSWIDTH								10000
#define CONFIG_MIN_LASER_POSWIDTH								1
#define CONFIG_MAX_LASER_NEGWIDTH								10000
#define CONFIG_MIN_LASER_NEGWIDTH								1
#define CONFIG_MAX_LASER_TIMES									20//���ɼ���������
#define CONFIG_MIN_LASER_TIMES									1//��С�ɼ���������
#define CONFIG_MAX_LASER_GROUP_OFF								1000
#define CONFIG_MIN_LASER_GROUP_OFF								10
#define CONFIG_MAX_LASER_ENERGY_INTERVAL						200
#define CONFIG_MIN_LASER_ENERGY_INTERVAL						40
#define CONFIG_STEP_LASER_ENERGY_INTERVAL						10
#define CONFIG_BEEM_ENERGY_INTERVAL_TIME						250//��������ʱ��

#define CONFIG_MAX_AIM_BRG										100//���������ռ�ձ�
#define CONFIG_MIN_AIM_BRG										1//�����С����ռ�ձ�
#define CONFIG_MAX_MUSIC_VOLUME									100//�������������
#define CONFIG_MIN_MUSIC_VOLUME									1//��������С����
#define CONFIG_MAX_LCD_BRG										100//��Ļ�������ֵ
#define CONFIG_MIN_LCD_BRG										1//��Ļ������Сֵ
#define CONFIG_COOL_SET_TEMP									280//��ȴ�¶�
#define CONFIG_COOL_DIFF_TEMP									20//��ȴ�¶ȱ仯��Χ
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
//���ݼĴ��� ���� 2048
#define DM_START												32
#define DM_END													2079
//��Ȧ�Ĵ��� �Ǳ��� 16 * 32 = 512
#define R_START													2080
#define R_END													2111						
//���ݼĴ��� �Ǳ��� 512
#define EM_START												2112
#define EM_END													2623
//��ʱ��Ȧ
//1MS  16 * 4 = 64
#define T_1MS_START												2624
#define T_1MS_END												2627
//10MS 16 * 4 = 64
#define T_10MS_START											2628
#define T_10MS_END												2631
//100MS 16 * 4 = 64
#define T_100MS_START											2632
#define T_100MS_END												2635
//��ʱ��ʹ��
//1MS  16 * 4 = 64
#define T_1MS_ENA_START											2636
#define T_1MS_ENA_END											2639
//10MS 16 * 4 = 64
#define T_10MS_ENA_START										2640
#define T_10MS_ENA_END											2643
//100MS 16 * 4 = 64
#define T_100MS_ENA_START										2644
#define T_100MS_ENA_END											2647
//��ʱ��ʱ��
//1MS  16 * 4 = 64
#define TD_1MS_START											2648
#define TD_1MS_END												2711
//10MS 16 * 4 = 64
#define TD_10MS_START											2712											
#define TD_10MS_END												2775
//100MS 16 * 4 = 64
#define TD_100MS_START											2776
#define TD_100MS_END											2839
//����λ�Ĵ��� 16 * 8 = 128
#define X_START													2840
#define X_END													2847
//���λ�Ĵ��� 16 * 8 = 128
#define Y_START													2848
#define Y_END													2855
//����Ĵ��� 64
#define SPREG_START												2856
#define SPREG_END												2919
//������Ȧ 16 * 8 = 128
#define SPCOIL_START											2920
#define SPCOIL_END												2927
//��ʱ�Ĵ��� 64
#define TM_START												2928
#define TM_END													2991
/*****************************************************************************/
#define CONFIG_NVRAM_SIZE 										(TM_END + 1)
/*****************************************************************************/
//�浵�Ĵ���
#define FD_START												0
#define FD_END													2047
/*****************************************************************************/
#define CONFIG_FDRAM_SIZE										(FD_END + 1)
/*****************************************************************************/
#define SPCOIL_ON												(SPCOIL_START * 16 + 0)//��ͨ��Ȧ
#define SPCOIL_START_UP											(SPCOIL_START * 16 + 1)//�����ϵ�
#define SPCOIL_PS10MS											(SPCOIL_START * 16 + 2)//10mS
#define SPCOIL_PS50MS											(SPCOIL_START * 16 + 3)//50mS
#define SPCOIL_PS100MS											(SPCOIL_START * 16 + 4)//100mS
#define SPCOIL_PS1000MS											(SPCOIL_START * 16 + 5)//1000mS
#define SPCOIL_MODBUS_S0_ERROR									(SPCOIL_START * 16 + 6)//Modbus Slave->Uart0 ����
#define SPCOIL_NVRAM_FAIL										(SPCOIL_START * 16 + 7)//NVRAMУ�������
#define SPCOIL_WATCHDOG_OVERFLOW								(SPCOIL_START * 16 + 8)//���Ź����
/*****************************************************************************/
#define SPCOIL_BEEM_ENABLE										(SPCOIL_START * 16 + 10)//������ʹ��
#define SPCOIL_BEEM_BUSY										(SPCOIL_START * 16 + 11)//����������״̬
#define SPCOIL_AIM_ENABEL										(SPCOIL_START * 16 + 12)//��׼��ʹ��
#define SPCOIL_AIM_BUSY											(SPCOIL_START * 16 + 13)//��׼�⹤��״̬
/*****************************************************************************/
#define SPCOIL_SPWM_OUT_0										(SPCOIL_START * 16 + 34)//SPWM0���״̬
#define SPCOIL_SPWM_RESET_0										(SPCOIL_START * 16 + 35)//SPWM0��λ
#define SPCOIL_SPWM_OUT_1										(SPCOIL_START * 16 + 36)//SPWM1���״̬
#define SPCOIL_SPWM_RESET_1										(SPCOIL_START * 16 + 37)//SPWM1��λ
#define SPCOIL_SPWM_OUT_2										(SPCOIL_START * 16 + 38)//SPWM2���״̬
#define SPCOIL_SPWM_RESET_2										(SPCOIL_START * 16 + 39)//SPWM2��λ
#define SPCOIL_SPWM_OUT_3										(SPCOIL_START * 16 + 40)//SPWM3���״̬
#define SPCOIL_SPWM_RESET_3										(SPCOIL_START * 16 + 41)//SPWM3��λ
/*****************************************************************************/
#define SPCOIL_DK25L_INIT_FAIL									(SPCOIL_START * 16 + 51)//NFCģ���ʼ��ʧ��
#define SPCOIL_LASER_DRIVER_INIT_FAIL							(SPCOIL_START * 16 + 53)//������������ʼ��ʧ��
#define SPCOIL_WIRELESS_FOOTCONTROL_INIT_FAIL					(SPCOIL_START * 16 + 56)//���߽�̤��ʼ��ʧ��
#define SPCOIL_PROBATION_INIT_FAIL								(SPCOIL_START * 16 + 57)//�����ڳ�ʼ��ʧ��
/*****************************************************************************/
#define SPCOIL_DK25L_RXCMD_DONE									(SPCOIL_START * 16 + 70)//����ָ�����
#define SPCOIL_DK25L_RXCMD_DOING								(SPCOIL_START * 16 + 71)//����ָ�������
#define SPCOIL_DK25L_RXCMD_OVERFLOW								(SPCOIL_START * 16 + 72)//����ָ�����
#define SPCOIL_DK25L_RXCMD_ERROR								(SPCOIL_START * 16 + 73)//����ָ����
#define SPCOIL_DK25L_TXCMD_DONE									(SPCOIL_START * 16 + 74)//дָ�����
#define SPCOIL_DK25L_TXCMD_DOING								(SPCOIL_START * 16 + 75)//дָ�������
#define SPCOIL_DK25L_TXCMD_OVERFLOW								(SPCOIL_START * 16 + 76)//дָ�����
#define SPCOIL_DK25L_TXCMD_ERROR								(SPCOIL_START * 16 + 77)//дָ�����
/*****************************************************************************/
#define SPREG_CLEAR_NVRAM										(SPREG_START + 0)//���NVRAM����������
/*****************************************************************************/
#define SPREG_ADC_0												(SPREG_START + 1)//ADC0�ɼ�ֵ PD0
#define SPREG_ADC_1												(SPREG_START + 2)//ADC1�ɼ�ֵ PD1
#define SPREG_ADC_2												(SPREG_START + 3)//ADC2�ɼ�ֵ NTC0
#define SPREG_ADC_3												(SPREG_START + 4)//ADC3�ɼ�ֵ NTC1
#define SPREG_ADC_4												(SPREG_START + 5)//ADC4�ɼ�ֵ ISMON0
#define SPREG_ADC_5												(SPREG_START + 6)//ADC5�ɼ�ֵ IVINMON0
#define SPREG_ADC_6												(SPREG_START + 7)//ADC6�ɼ�ֵ ISMON1
#define SPREG_ADC_7												(SPREG_START + 8)//ADC7�ɼ�ֵ IVINMON1

#define SPREG_DAC_0												(SPREG_START + 10)//DAC0�趨ֵ LSET0
#define SPREG_DAC_1												(SPREG_START + 11)//DAC1�趨ֵ LSET1
#define SPREG_DAC_2												(SPREG_START + 12)//DAC2�趨ֵ LSET2
#define SPREG_DAC_3												(SPREG_START + 13)//DAC3�趨ֵ LSET3
#define SPREG_DAC_4												(SPREG_START + 14)//DAC3�趨ֵ LSET4
#define SPREG_DAC_5												(SPREG_START + 15)//DAC3�趨ֵ LSET5
#define SPREG_DAC_6												(SPREG_START + 16)//DAC3�趨ֵ LSET6
#define SPREG_DAC_7												(SPREG_START + 17)//DAC3�趨ֵ LSET7
/*****************************************************************************/
#define SPREG_SPWM_POS_0										(SPREG_START + 20)//���PWM0����������
#define SPREG_SPWM_POS_SHADOW_0									(SPREG_START + 21)//���PWM0��������Ӱ
#define SPREG_SPWM_CYCLE_0										(SPREG_START + 22)//���PWM0��������
#define SPREG_SPWM_CYCLE_SHADOW_0								(SPREG_START + 23)//���PWM0������Ӱ
#define SPREG_SPWM_COUNTER_0									(SPREG_START + 24)//���PWM0������
#define SPREG_SPWM_POS_1										(SPREG_START + 25)//���PWM1����������
#define SPREG_SPWM_POS_SHADOW_1									(SPREG_START + 26)//���PWM1��������Ӱ
#define SPREG_SPWM_CYCLE_1										(SPREG_START + 27)//���PWM1��������
#define SPREG_SPWM_CYCLE_SHADOW_1								(SPREG_START + 28)//���PWM1������Ӱ
#define SPREG_SPWM_COUNTER_1									(SPREG_START + 29)//���PWM1������
#define SPREG_SPWM_POS_2										(SPREG_START + 30)//���PWM2����������
#define SPREG_SPWM_POS_SHADOW_2									(SPREG_START + 31)//���PWM2��������Ӱ
#define SPREG_SPWM_CYCLE_2										(SPREG_START + 32)//���PWM2��������
#define SPREG_SPWM_CYCLE_SHADOW_2								(SPREG_START + 33)//���PWM2������Ӱ
#define SPREG_SPWM_COUNTER_2									(SPREG_START + 34)//���PWM2������
#define SPREG_SPWM_POS_3										(SPREG_START + 35)//���PWM3����������
#define SPREG_SPWM_POS_SHADOW_3									(SPREG_START + 36)//���PWM3��������Ӱ
#define SPREG_SPWM_CYCLE_3										(SPREG_START + 37)//���PWM3��������
#define SPREG_SPWM_CYCLE_SHADOW_3								(SPREG_START + 38)//���PWM3������Ӱ
#define SPREG_SPWM_COUNTER_3									(SPREG_START + 39)//���PWM3������
/*****************************************************************************/
#define SPREG_MUSIC_VOLUME										(SPREG_START + 40)//���ֲ������� 0-100%
#define SPREG_PLAYING_MUSIC_ID									(SPREG_START + 41)//��ǰ��������ID
#define SPREG_NEXT_MUSIC_ID										(SPREG_START + 42)//��һ����������ID
#define SPREG_CONTROL_MUSIC										(SPREG_START + 43)//���ֲ��ſ��ƼĴ���
/*****************************************************************************/
#define SPREG_RED_LED_DUTYCYCLE									(SPREG_START + 45)//��ɫLED����->���� 0-100%
#define SPREG_GREEN_LED_DUTYCYCLE								(SPREG_START + 46)//��ɫLED����->��Դ 0-100%
#define SPREG_BLUE_LED_DUTYCYCLE								(SPREG_START + 47)//��ɫLED����->����ָʾ 0-100%
#define SPREG_AIM_DUTYCYCLE										(SPREG_START + 48)//��׼������->650�켤�� 0-100%
/*****************************************************************************/
#define SPREG_BEEM_DUTYCYCLE									(SPREG_START + 50)//������ռ�ձ� 0-100%
#define SPREG_BEEM_FREQ											(SPREG_START + 51)//������Ƶ��
#define SPREG_BEEM_MODE											(SPREG_START + 52)//������ģʽ
#define SPREG_BEEM_COUNTER										(SPREG_START + 53)//��������ʱ��
/*****************************************************************************/
#define SPREG_DK25L_VER											(SPREG_START + 55)//DK25L NFCģ��汾
/*****************************************************************************/
#define SPREG_IDENTITY											(SPREG_END + 0)//ƽ̨ID��
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
#define EM_LASER_AVERAGE_POWER									(EM_START + 61//����ģʽƽ������
#define EM_LASER_FREQUENCY										(EM_START + 62)//��ǰģʽƵ��
#define EM_LASER_DUTY_CYCLE										(EM_START + 63)//��ǰģʽռ�ձ� 
/*****************************************************************************/
#define EM_DIODE_TEMP0											(EM_START + 64)//�������¶�0
#define EM_DIODE_TEMP1											(EM_START + 65)//�������¶�1
#define EM_DRIVE_TEMP											(EM_START + 66)//�������¶�
#define EM_ENVI_TEMP											(EM_START + 67)//�����¶�
#define EM_DIODE_HIGH_TEMP										(EM_START + 68)//�����ܹ�����ֵ
#define EM_DRIVE_HIGH_TEMP										(EM_START + 69)//������������ֵ
#define EM_ENVI_HIGH_TEMP										(EM_START + 70)//����������ֵ
#define EM_COOL_SET_TEMP										(EM_START + 71)//�趨��ȴ�¶�
#define EM_COOL_DIFF_TEMP										(EM_START + 72)//�趨��ȴ�ز����
/*****************************************************************************/				
#define EM_TOTAL_POWER											(EM_START + 80)//�����ܹ���
#define EM_HMI_OPERA_STEP										(EM_START +	81)//��������								
#define EM_ERROR_CODE											(EM_START + 82)//������					
#define EM_SCHEME_NUM_TMP										(EM_START + 83)//��ȷ�Ϸ������			
#define EM_DK25L_VER											(EM_START + 83)//DK25Lģ��汾
/*****************************************************************************/
#define EM_DC_PAGE												(EM_START + 90)//HMIҳ���� 			
#define EM_DC_PASSCODE_INDEX									(EM_START + 91)//��������λ����		
#define EM_DC_NEW_PASSCODE0										(EM_START + 92)//����������0			
#define EM_DC_NEW_PASSCODE1										(EM_START + 93)//����������1			
#define EM_DC_NEW_PASSCODE2										(EM_START + 94)//����������0			
#define EM_DC_NEW_PASSCODE3										(EM_START + 95)//����������1			
#define EM_DC_DEFAULT_PASSCODE0									(EM_START + 96)//Ĭ������0				
#define EM_DC_DEFAULT_PASSCODE1									(EM_START + 97)//Ĭ������1				
#define EM_DC_DEFAULT_PASSCODE2									(EM_START + 98)//Ĭ������1	
#define EM_DC_DEFAULT_PASSCODE3									(EM_START + 99)//Ĭ������1				
#define EM_DC_DISPLAY_RELEASE_TIME								(EM_START + 100)//��ʾ����ʱ��			
#define EM_DC_DISPLAY_RELEASE_ENERGY							(EM_START + 101)//��ʾ��������
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
#define TMP_NAME_0												(TMP_START + 0)//��ʱ���ƴ�����
#define TMP_NAME_1												(TMP_START + 15)//��ʱ���ƴ�����
#define TMP_NAME_2												(TMP_START + 30)//��ʱ���ƴ�����
#define TMP_NAME_3												(TMP_START + 45)//��ʱ���ƴ�����
#define TMP_NAME_4												(TMP_START + 60)//��ʱ���ƴ�����
#define TMP_NAME_5												(TMP_START + 75)//��ʱ���ƴ�����
#define TMP_NAME_6												(TMP_START + 90)//��ʱ���ƴ�����
#define TMP_NAME_7												(TMP_START + 105)//��ʱ���ƴ�����
#define TMP_NAME_8												(TMP_START + 120)//��ʱ���ƴ�����
#define TMP_NAME_9												(TMP_START + 135)//��ʱ���ƴ�����
#define TMP_NAME_10												(TMP_START + 150)//��ʱ���ƴ�����
#define TMP_NAME_11												(TMP_START + 165)//��ʱ���ƴ�����
#define TMP_NAME_12												(TMP_START + 180)//��ʱ���ƴ�����
#define TMP_NAME_13												(TMP_START + 195)//��ʱ���ƴ�����
#define TMP_NAME_14												(TMP_START + 210)//��ʱ���ƴ�����
#define TMP_NAME_15												(TMP_START + 225)//��ʱ���ƴ�����
#define TMP_NAME_16												(TMP_START + 240)//��ʱ���ƴ�����
#define TMP_NAME_17												(TMP_START + 255)//��ʱ���ƴ�����
#define TMP_NAME_18												(TMP_START + 270)//��ʱ���ƴ�����
#define TMP_NAME_19												(TMP_START + 285)//��ʱ���ƴ�����
#define TMP_NAME_20												(TMP_START + 300)//��ʱ���ƴ�����
#define TMP_NAME_21												(TMP_START + 315)//��ʱ���ƴ�����
#define TMP_NAME_22												(TMP_START + 330)//��ʱ���ƴ�����
#define TMP_NAME_23												(TMP_START + 345)//��ʱ���ƴ�����
#define TMP_NAME_24												(TMP_START + 360)//��ʱ���ƴ�����
#define TMP_NAME_25												(TMP_START + 375)//��ʱ���ƴ�����
#define TMP_NAME_26												(TMP_START + 390)//��ʱ���ƴ�����
#define TMP_NAME_27												(TMP_START + 405)//��ʱ���ƴ�����
#define TMP_NAME_28												(TMP_START + 420)//��ʱ���ƴ�����
#define TMP_NAME_29												(TMP_START + 435)//��ʱ���ƴ�����
#define TMP_NAME_30												(TMP_START + 450)//��ʱ���ƴ�����
#define TMP_NAME_31												(TMP_START + 465)//��ʱ���ƴ�����

#define TMP_NAME_32												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_33												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_34												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_35												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_36												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_37												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_38												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_39												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_40												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_41												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_42												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_43												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_44												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_45												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_46												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_47												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_48												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_49												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_50												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_51												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_52												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_53												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_54												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_55												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_56												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_57												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_58												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_59												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_60												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_61												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_62												(TMP_START + 465)//��ʱ���ƴ�����
#define TMP_NAME_63												(TMP_START + 465)//��ʱ���ƴ�����
/*****************************************************************************/
#define DM_SCHEME_NUM											(DM_START + 0)//ѡ��ķ������ ��8λ������ ��8λ����ʹ��
#define DM_LANGUAGE												(DM_START + 1)//����ID
#define DM_MUSIC_VOLUME											(DM_START + 2)//�������� 0-100%
#define DM_BEEM_VOLUME											(DM_START + 3)//���������� 0-100%
#define DM_AIM_BRG												(DM_START + 4)//ָʾ��������
#define DM_LCD_BRG												(DM_START + 5)//��Ļ����
#define DM_LED_RED_BRG											(DM_START + 6)//�������
#define DM_LED_GREEN_BRG										(DM_START + 7)//�̵�����
#define DM_LED_BLUE_BRG											(DM_START + 8)//��������
#define DM_DC_OLD_PASSCODE0										(DM_START + 9)//��������0-1
#define DM_DC_OLD_PASSCODE1										(DM_START + 10)//��������2-3
#define DM_DC_OLD_PASSCODE2										(DM_START + 11)//��������0-1
#define DM_DC_OLD_PASSCODE3										(DM_START + 12)//��������2-3
/*****************************************************************************/
#define X_FOOTSWITCH_NC											(X_START * 16 + 1)//XIN0 ��̤����
#define X_ESTOP													(X_START * 16 + 0)//XIN1 ����ֹͣ����
#define X_FOOTSWITCH_NO											(X_START * 16 + 2)//XIN2 ��̤����
#define X_INTERLOCK												(X_START * 16 + 3)//XIN0 ��ȫ����
#define X_FIBER_PROBE											(X_START * 16 + 7)//XIN6 ����̽��0
/*****************************************************************************/
#define Y_LED_POWERON											(Y_START * 16 + 0)//YOUT0 ��Դ��
#define Y_LED_EMIT												(Y_START * 16 + 1)//YOUT1 ����ָʾ��
#define Y_LED_ALARM												(Y_START * 16 + 2)//YOUT2 ����ָʾ��
#define Y_OUT3													(Y_START * 16 + 3)//YOUT3 ����
#define Y_OUT4													(Y_START * 16 + 4)//YOUT4 ����
#define Y_OUT5													(Y_START * 16 + 5)//YOUT5 ����
#define Y_OUT6													(Y_START * 16 + 6)//YOUT6 ����
#define Y_OUT7													(Y_START * 16 + 7)//YOUT7 ����
#define Y_FAN0													(Y_START * 16 + 8)//YOUT8 ���ȿ���0
#define Y_FAN1													(Y_START * 16 + 9)//YOUT9 ���ȿ���1
#define Y_TEC0													(Y_START * 16 + 10)//YOUT10 ���俪��0
#define Y_TEC1													(Y_START * 16 + 11)//YOUT11 ���俪��1
/*****************************************************************************/
#define R_FOOTSWITCH_NC											(R_START * 16 + 0)//��̤����
#define R_FOOTSWITCH_NO											(R_START * 16 + 0)//��̤����
#define R_ESTOP													(R_START * 16 + 1)//
#define R_INTERLOCK												(R_START * 16 + 2)//
#define R_FIBER_PROBE											(R_START * 16 + 3)//
#define R_RFID_PASS												(R_START * 16 + 4)
#define R_DIODE_TEMP_HIGH										(R_START * 16 + 5)//ͨ��0�����ܸ��±�־
#define R_DIODE_TEMP_LOW										(R_START * 16 + 6)//ͨ��0�����ܸ��±�־
#define R_DRIVE_TEMP_HIGH										(R_START * 16 + 7)//���������±�־
#define R_DRIVE_TEMP_LOW										(R_START * 16 + 8)//ͨ��0�����ܸ��±�־
#define R_ENVI_TEMP_HIGH										(R_START * 16 + 9)//�����¶ȱ��
#define R_ENVI_TEMP_LOW											(R_START * 16 + 10)//ͨ��0�����ܸ��±�־
#define R_FAULT													(R_START * 16 + 11)//���ϱ�־
#define R_FAN_ENABLE											(R_START * 16 + 12)//����ʹ��
#define R_DISABLE_RFID											(R_START * 16 + 13)//����NFC���
#define R_DISABLE_FIBER_PROBE									(R_START * 16 + 14)//���ι���̽��
#define R_DISABLE_FAN_SPEED										(R_START * 16 + 15)//���η��ȿ���
#define R_CLEAR_EPROM											(R_START * 16 + 16)//��ȫ���EPROM
#define R_ENGINEER_MODE											(R_START * 16 + 17)//����ʦģʽ
//HMI���״̬
#define R_DCHMI_RESET_REQ										(R_START * 16 + 20)//HMI��λ����
#define R_DCHMI_RESET_DOING										(R_START * 16 + 21)//HMI��λ��
#define R_DCHMI_RESET_DONE										(R_START * 16 + 22)//HMI��λ���	
#define R_DCHMI_UPDATEUI_REQ									(R_START * 16 + 23)//HMI���ݸ�������
#define R_DCHMI_UPDATEUI_DOING									(R_START * 16 + 24)//HMI���ݸ�����
#define R_DCHMI_UPDATEUI_DONE									(R_START * 16 + 25)//HMI���ݸ����������
#define R_DCHMI_RESTORE_REQ										(R_START * 16 + 26)//HMI��FLASH�лָ���������
#define R_DCHMI_RESTORE_DOING									(R_START * 16 + 27)//HMI��FLASH�лָ���
#define R_DCHMI_RESTORE_DONE									(R_START * 16 + 28)//HMI��FLASH�лָ��������	
#define R_DCHMI_DISPLAY_WARN									(R_START * 16 + 30)//HMI��ʾ������Ϣ
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






