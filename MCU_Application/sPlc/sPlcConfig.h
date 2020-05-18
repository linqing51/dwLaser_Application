#ifndef __SPLCCONFIG_H__
#define __SPLCCONFIG_H__
/*****************************************************************************/
#define CONFIG_DEBUG									0//ʹ�ܵ���
#if CONFIG_DEBUG == 1
#define CONFIG_EPROM_DEBUG								0
#define CONFIG_DEBUG_CONSOLE							0//
#else
#define CONFIG_EPROM_DEBUG								0
#define CONFIG_DEBUG_CONSOLE							0//
#endif
/*****************************************************************************/
#define CONFIG_UART0_BAUDRATE									115200//����0 ������
#define CONFIG_UART1_BAUDRATE									115200//����1 ������
/*****************************************************************************/
#define CONFIG_SPLC_USING_I2C0									1//ʹ��I2C0
#define CONFIG_SPLC_USING_I2C1									1//ʹ��I2C1
#define CONFIG_SPLC_USING_I2C2									1//ʹ��I2C2
#define CONFIG_SPLC_USING_I2C3									1//ʹ��I2C3
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
#define CONFIG_EPROM_FRAM										1//����洢����д��ȴ�
#define CONFIG_EPROM_PAGEWRITE									0//ҳд��
#define CONFIG_EPROM_NVRAM_START								0x0
#define CONFIG_EPROM_FDRAM_START								0x800//2048
/*****************************************************************************/
#define CONFIG_SPLC_USING_SPWM									0//ʹ�����PWM����
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
#if CONFIG_SPLC_USING_EPROM == 1
#define CONFIG_SPLC_USING_CLEAR_NVRAM							0//�������NVRAM����
#else
#define CONFIG_SPLC_USING_CLEAR_NVRAM							0//�������NVRAM����
#endif
/*****************************************************************************/
#define CONFIG_SPLC_USING_UART0									1//UART 0��������
#define CONFIG_SPLC_USING_UART0_ISR								1
#define UART0													0

#define CONFIG_SPLC_USING_UART1									0//UART 1��������
#define CONFIG_SPLC_USING_UART1_ISR								0
#define UART1													1
/*****************************************************************************/
#define CONFIG_SPLC_USING_ADC									1//ʹ��ADCģ��
#define CONFIG_SPLC_ADC_FILTER_TAP								10//ADCλ���˲�����
#define CONFIG_SPLC_ADC_CHANNLE									9//ADCͨ����
#define CONFIG_ADC_TEMP_SENSOR_SLOPE							2.86F
#define CONFIG_ADC_TEMP_SENSOR_OFFSET  							776L// Temp Sensor Offset in mV
#define CONFIG_ADC_INTERNAL_VREF     							2430L// ADC Voltage Reference (mV)
#define CONFIG_ADC_AMBIENT             							25L// Ambient temp in deg C
#define CONFIG_NTC_RS											3300L
#define CONFIG_NTC_B											3500L
#define CONFIG_NTC_RB											10000L
#define CONFIG_NTC_VREF											5000L
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
#define CONFIG_SPLC_USING_ROBATION								0//ʹ�������ڹ���
/*****************************************************************************/
#define CONFIG_SPLC_USING_LASER_TIMER							1
#define CONFIG_SPLC_USING_LASER_TIMER_TEST						0
/*****************************************************************************/
#define CONFIG_LASER_TIMER_TICK									1000//1mS
#define CONFIG_USING_USB_APP									0//USBӦ��
#define CONFIG_USING_DCHMI_APP									0//�㶫����˻�����Ӧ��
#define CONFIG_USING_BACKGROUND_APP								0//����Ӧ��
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
#define FD_END													1023
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
#define SPREG_ADC_8												(SPREG_START + 9)//ADC8�ɼ�ֵ Temperature Sensor

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
#define SPREG_DK25L_VER											(SPREG_START + 50)//DK25L NFCģ��汾
/*****************************************************************************/
#define SPREG_IDENTITY											(SPREG_END + 0)//ƽ̨ID��
/*****************************************************************************/
#endif
