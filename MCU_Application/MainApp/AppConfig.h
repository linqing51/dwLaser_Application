#ifndef __APPCONFIG_H__
#define __APPCONFIG_H__
/*****************************************************************************/
#define CONFIG_APP_DEBUG										1
/*****************************************************************************/
#define CONFIG_APP_DIODE_HIGH_TEMP								400
#define CONFIG_APP_DIODE_LOW_TEMP								-100
#define CONFIG_APP_DRIVE_HIGH_TEMP								650
#define CONFIG_APP_ENVI_HIGH_TEMP								750
/*****************************************************************************/
#define CONFIG_USING_SINGLE_WAVE								1//������
#define CONFIG_USING_DUAL_WAVE									0//˫����
#define CONFIG_HMI_SCHEME_NUM									32//������
#define CONFIG_HMI_DEFAULT_PASSSWORD0							0x3235//Ĭ������
#define CONFIG_HMI_DEFAULT_PASSSWORD1							0x3830//Ĭ������
#define CONFIG_SCHEME_NAME_SIZE									22//12*2
//������
#define ERROR_CODE_EPROM										0x0001//EPRON ����
#define ERROR_CODE_USBHOST										0x0008//USB HOSTģ�����
#define ERROR_CODE_NFC											0x0009//NFCģ�����
#define ERRPR_CODE_NOERR										0xFFFF//�޴���
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
#define CONFIG_MIN_AIM_BRG										0//�����С����ռ�ձ�
#define CONFIG_MAX_BEEM_VOLUME									100//�������������
#define CONFIG_MIN_BEEM_VOLUME									0//��������С����
#define CONFIG_MAX_LCD_BRG										100//��Ļ�������ֵ
#define CONFIG_MIN_LCD_BRG										0//��Ļ������Сֵ
#define CONFIG_COOL_SET_TEMP									280//��ȴ�¶�
#define CONFIG_COOL_DIFF_TEMP									20//��ȴ�¶ȱ仯��Χ

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

#define CONFIG_RELEASE_SECOND_DEF								1000//���ⷢ���ʱ�붨��
#endif