#ifndef __SPLC_H__
#define __SPLC_H__
/*****************************************************************************/
#include "cmsis_os.h"
#include "main.h"
#include "arm_math.h"
#include "usbh_core.h"
/*****************************************************************************/
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <LIMITS.H>
#include "stdbool.h"
#include "stdint.h"
/*****************************************************************************/
#include "libcrc.h"
#include "deviceConfig.h"
#include "sPlcConfig.h"
#include "sPlcFun.h"
#include "dcHmiApp.h"
#include "preScheme.h"
/*****************************************************************************/
#if CONFIG_SPLC_FUNTEST == 1
#include "sPlcTest.h"
#endif
/*****************************************************************************/
#define BEEM_MODE_0														0x10//����ģʽ
#define BEEM_MODE_1														0x11//����ͬ��
#define BEEM_MODE_2														0x12//���ⷢ��̶����
#define BEEM_MODE_3														0x13//�쳣����
#define BEEM_MODE_4														0x14//���ⷢ��̶����+��ʾ��
/*****************************************************************************/
#define LASER_CHANNEL_0												0x00//ͨ��0
#define LASER_CHANNEL_1												0x01//ͨ��1
#define LASER_CHANNEL_2												0x02//ͨ��2
#define LASER_CHANNEL_3												0x03//ͨ��3
/*****************************************************************************/
#define LASER_MODE_CW													0x01//����ģʽ
#define LASER_MODE_SP													0x02//������ģʽ
#define LASER_MODE_MP													0x04//������ģʽ
#define LASER_MODE_GP													0x08//Ⱥ����ģʽ
#define LASER_MODE_DERMA											0x10//
#define LASER_MODE_SIGNAL											0x20//
#define LASER_SELECT_CH0											0x01
#define LASER_SELECT_CH1											0x02
#define LASER_SELECT_CH2											0x04
#define LASER_SELECT_CH3											0x08
#define LASER_SELECT_ALL											0x0F
/*****************************************************************************/
#define MCP4821_NSHDN_MASK										(1 << 12)
#define MCP4821_NGA_MASK											(1 << 13)
/*****************************************************************************/
#define SET_EDAC0_CS(b)												HAL_GPIO_WritePin(EDAC0_CS_GPIO_Port, EDAC0_CS_Pin, b)
#define SET_EDAC1_CS(b)												HAL_GPIO_WritePin(EDAC1_CS_GPIO_Port, EDAC1_CS_Pin, b)
#define SET_EDAC2_CS(b)												HAL_GPIO_WritePin(EDAC2_CS_GPIO_Port, EDAC2_CS_Pin, b)
#define SET_EDAC3_CS(b)												HAL_GPIO_WritePin(EDAC3_CS_GPIO_Port, EDAC3_CS_Pin, b)
#define SET_EDAC0_SCK(b)											HAL_GPIO_WritePin(EDAC0_SCK_GPIO_Port, EDAC0_SCK_Pin, b)
#define SET_EDAC1_SCK(b)											HAL_GPIO_WritePin(EDAC1_SCK_GPIO_Port, EDAC1_SCK_Pin, b)
#define SET_EDAC2_SCK(b)											HAL_GPIO_WritePin(EDAC2_SCK_GPIO_Port, EDAC2_SCK_Pin, b)
#define SET_EDAC3_SCK(b)											HAL_GPIO_WritePin(EDAC3_SCK_GPIO_Port, EDAC3_SCK_Pin, b)
#define SET_EDAC0_SDI(b)											HAL_GPIO_WritePin(EDAC0_SDI_GPIO_Port, EDAC0_SDI_Pin, b)
#define SET_EDAC1_SDI(b)											HAL_GPIO_WritePin(EDAC1_SDI_GPIO_Port, EDAC1_SDI_Pin, b)
#define SET_EDAC2_SDI(b)											HAL_GPIO_WritePin(EDAC2_SDI_GPIO_Port, EDAC2_SDI_Pin, b)
#define SET_EDAC3_SDI(b)											HAL_GPIO_WritePin(EDAC3_SDI_GPIO_Port, EDAC3_SDI_Pin, b)
#define GET_ESTOP_NC													HAL_GPIO_ReadPin(ESTOP_NC_GPIO_Port, ESTOP_NC_Pin)
#define GET_INTERLOCK_NC											HAL_GPIO_ReadPin(INTERLOCK_NC_GPIO_Port, INTERLOCK_NC_Pin)
#define GET_FSWITCH_NO												HAL_GPIO_ReadPin(FS_NO_GPIO_Port, FS_NO_Pin)
#define GET_FSWITCH_NC												HAL_GPIO_ReadPin(FS_NC_GPIO_Port, FS_NC_Pin)

#define SET_RED_LED_ON												HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2)
#define SET_RED_LED_OFF												HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2)
#define SET_GREEN_LED_ON											HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1)
#define SET_GREEN_LED_OFF											HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1)
#define SET_BLUE_LED_ON												HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3)
#define SET_BLUE_LED_OFF											HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3)

#define SET_BLUE_LED_DC(b)										__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, b);
#define SET_RED_LED_DC(b)											__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, b);
#define SET_GREEN_LED_DC(b)										__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, b);

#define SET_ERR_LED_ON												HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_SET)
#define SET_ERR_LED_OFF												HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_RESET)
#define GET_ERR_LED														HAL_GPIO_ReadPin(ERR_LED_GPIO_Port, ERR_LED_Pin)
#define FLIP_ERR_LED													HAL_GPIO_TogglePin(ERR_LED_GPIO_Port, ERR_LED_Pin)
#define SET_TICK_LED_ON												HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, GPIO_PIN_SET)
#define SET_TICK_LED_OFF											HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, GPIO_PIN_RESET)
#define GET_TICK_LED													HAL_GPIO_ReadPin(TICK_LED_GPIO_Port, TICK_LED_Pin)
#define FLIP_TICK_LED													HAL_GPIO_TogglePin(TICK_LED_GPIO_Port, TICK_LED_Pin)
#define SET_LASER_CH0_ON											HAL_GPIO_WritePin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin, GPIO_PIN_SET)
#define SET_LASER_CH0_OFF											HAL_GPIO_WritePin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin, GPIO_PIN_RESET)
#define SET_LASER_CH1_ON											HAL_GPIO_WritePin(LAS_PWM1_GPIO_Port, LAS_PWM1_Pin, GPIO_PIN_SET)
#define SET_LASER_CH1_OFF											HAL_GPIO_WritePin(LAS_PWM1_GPIO_Port, LAS_PWM1_Pin, GPIO_PIN_RESET)
#define SET_LASER_CH2_ON											HAL_GPIO_WritePin(LAS_PWM2_GPIO_Port, LAS_PWM2_Pin, GPIO_PIN_SET)
#define SET_LASER_CH2_OFF											HAL_GPIO_WritePin(LAS_PWM2_GPIO_Port, LAS_PWM2_Pin, GPIO_PIN_RESET)
#define SET_LASER_CH3_ON											HAL_GPIO_WritePin(LAS_PWM3_GPIO_Port, LAS_PWM3_Pin, GPIO_PIN_SET)
#define SET_LASER_CH3_OFF											HAL_GPIO_WritePin(LAS_PWM3_GPIO_Port, LAS_PWM3_Pin, GPIO_PIN_RESET)
#define FLIP_LASER_CH0												HAL_GPIO_TogglePin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin)
#define FLIP_LASER_CH1												HAL_GPIO_TogglePin(LAS_PWM1_GPIO_Port, LAS_PWM1_Pin)
#define FLIP_LASER_CH2												HAL_GPIO_TogglePin(LAS_PWM2_GPIO_Port, LAS_PWM2_Pin)
#define FLIP_LASER_CH3												HAL_GPIO_TogglePin(LAS_PWM3_GPIO_Port, LAS_PWM3_Pin)
#define GET_LASER_CH0													HAL_GPIO_ReadPin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin)
#define GET_LASER_CH1													HAL_GPIO_ReadPin(LAS_PWM1_GPIO_Port, LAS_PWM1_Pin)
#define GET_LASER_CH2													HAL_GPIO_ReadPin(LAS_PWM2_GPIO_Port, LAS_PWM2_Pin)
#define GET_LASER_CH3													HAL_GPIO_ReadPin(LAS_PWM3_GPIO_Port, LAS_PWM3_Pin)
#define SET_SPEAKER_ON												HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_RESET)
#define SET_SPEAKER_OFF												HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_SET)
#define SET_AIM_ON										   			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1)
#define SET_AIM_OFF														HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1)
#define SET_FAN_ON														HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2)
#define SET_FAN_OFF														HAL_TIM_PWM_Stop(&htim12, TIM_CHANNEL_2)
#define SET_TEC_ON														HAL_GPIO_WritePin(LAS_TEC_GPIO_Port, LAS_TEC_Pin, GPIO_PIN_SET)
#define SET_TEC_OFF														HAL_GPIO_WritePin(LAS_TEC_GPIO_Port, LAS_TEC_Pin, GPIO_PIN_RESET)
/*****************************************************************************/
typedef enum {
	CLEAR_EPROM_ALL 														= 0x01,
	CLEAR_EPROM_NVRAM														= 0x02,
	CLEAR_EPROM_FDRAM														= 0x03,
	CLEAR_EPROM_FIRMWARE_CRC										= 0x04,
	CLEAR_EPROM_DEVICE_CONFIG										= 0x05,
	CLEAR_EPROM_LOG_INFO												= 0x06
}clarmEpromCmd_t;
/*****************************************************************************/
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart4;
extern USBH_HandleTypeDef hUsbHostFS;
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
extern CRC_HandleTypeDef hcrc;
extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim2;//AIM PWM
extern TIM_HandleTypeDef htim3;//LED PWM
extern TIM_HandleTypeDef htim7;//DAC DMA ��ʱ��
extern TIM_HandleTypeDef htim10;//Laser Timer
extern TIM_HandleTypeDef htim12;//FAN PWM
extern TIM_HandleTypeDef htim14;//sPlc Timer
extern RNG_HandleTypeDef hrng;
/*****************************************************************************/
extern int16_t NVRAM0[CONFIG_NVRAM_SIZE];//���籣�ּĴ��� ��ǰ �����浵�Ĵ���
extern int16_t NVRAM1[CONFIG_NVRAM_SIZE];//���籣�ּĴ��� ��һ��
extern int16_t FDRAM0[CONFIG_FDRAM_SIZE];//�浵�Ĵ���
extern int16_t FDRAM1[CONFIG_FDRAM_SIZE];//�浵�Ĵ���
extern uint16_t TimerCounter_10mS;//10����
extern uint16_t TimerCounter_100mS;//100����
extern uint16_t TimerCounter_200mS;//200����
extern uint16_t TimerCounter_500mS;//500����
extern uint16_t TimerCounter_1000mS;//1��
extern uint16_t TimerCounter_60000mS;//1����
extern uint8_t TD_10MS_SP;
extern uint8_t TD_100MS_SP;
extern uint8_t TD_200MS_SP;
extern uint8_t TD_500MS_SP;
extern uint8_t TD_1000MS_SP;
extern uint8_t TD_60000MS_SP;
extern uint32_t sPlcTick;
/*****************************************************************************/
extern int8_t LaserTimer_Mode;
extern int8_t LaserTimer_Select;
extern int16_t LaserTimer_TCounter;
extern int16_t LaserTimer_TMate;
extern int16_t LaserTimer_TOvertime;
extern int16_t LaserTimer_PCounter;
extern int16_t LaserTimer_PMate;
extern int16_t LaserTimer_POvertime;
extern int16_t LaserTimer_ReleaseTime;
extern int16_t LaserTimer_ReleaseCounter;
extern int8_t  LaserFlag_Emiting;//���ⷢ���б�־
extern int8_t LaserFlag_Emitover;//���ⷢ����ϱ�־
/*****************************************************************************/
extern void sPlcInit(void);//���߼���ʼ��
extern void sPlcProcessStart(void);//sPLC��ѯ��ʼ
extern void sPlcProcessEnd(void);//sPLC��ѯ����
extern void sPlcPortProcess(void);//sPLCƽ̨����
extern void sPlcAssertCoilAddress(uint16_t adr);
extern void sPlcAssertRegisterAddress(uint16_t adr);
/*****************************************************************************/
extern void sPlcInputInit(void);
extern void sPlcInputRefresh(void);
extern void sPlcOutputInit(void);
extern void sPlcOutputRefresh(void);
extern void sPlcloadDefault(void);
extern void sPlcIsrDisable(void);
extern void sPlcIsrEnable(void);
extern void sPlcTimerInit(void);//Ӳ��sTimer��ʱ����ʼ��
extern void sPlcTimerIsr(void);//Ӳ��sTimer��ʱ���ж� 1mS
extern void sPlcTimerDisalbe(void);//SPLC�رռ�ʱ��
extern void sPlcTimerEnable(void);//SPLC�򿪼�ʱ��
extern void sPlcDacInit(void);//DAC��ʼ��
extern void sPlcDacRefresh(void);//ˢ��DAC
extern void sPlcAdcInit(void);
extern void sPlcAdcProcess(void);
extern void sPlcSpeakerFreq(int16_t freq);//��������Ƶ��
extern void sPlcSpeakerVolume(int16_t volume);//������������
extern void sPlcSpeakerEnable(void);//������������
extern void sPlcSpeakerDisable(void);//�ر�����������
extern void sPlcSpeakerInit(void);//���ȳ�ʼ��
extern void sPlcLaserInit(void);
extern void sPlcLaserTimerIsr(void);//�ж� ���ⷢ��
extern void sPlcLaserTimerTestBench(uint8_t st);//LASER���ⷢ�����
extern void sPlcNvramUpdate(void);//����NVRAM->EPROM	
extern void sPlcNvramLoad(void);
extern void sPlcNvramSave(void);
extern void sPlcNvramClear(void);//���NVRAM����
extern void sPlcFdramLoad(void);
extern void sPlcFdramSave(void);
extern void sPlcFdramClear(void);
extern void sPlcDeviceConfigClear(void);
extern void sPlcDeviceLogClear(void);
extern void delayMs(uint32_t delayMs);//SPLC ������ʱ
extern void mucReboot(void);//�����λ
extern void resetInit(void);
extern void SystemClock_Reset(void);//��λϵͳʱ��
extern void UsbGpioReset(void);
extern void setAimBrightness(int8_t brg);//������׼������
extern void setFanSpeed(int16_t speed);//���÷���ת��
extern void morseCodeDiag(uint8_t diag);//�����
extern HAL_StatusTypeDef epromReadByte(uint16_t ReadAddr, uint8_t *rdat);//��AT24CXXָ����ַ����һ������
extern HAL_StatusTypeDef epromReadHword(uint16_t ReadAddr, uint16_t *rdat);//��AT24CXX�����ָ����ַ��ʼ����16λ��
extern HAL_StatusTypeDef epromReadDword(uint16_t ReadAddr, uint32_t *rdat);////��AT24CXX�����ָ����ַ��ʼ����32λ��
extern HAL_StatusTypeDef epromWriteByte(uint16_t WriteAddr, uint8_t *wdat);//��AT24CXXָ����ַд��8λ����
extern HAL_StatusTypeDef epromWriteHword(uint16_t WriteAddr, uint16_t *wdat);//��AT24CXX�����ָ����ַ��ʼд��16λ��
extern HAL_StatusTypeDef epromWriteDword(uint16_t WriteAddr, uint32_t *wdat);//��AT24CXX�����ָ����ַ��ʼд��32λ��
extern HAL_StatusTypeDef epromRead(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead);
extern HAL_StatusTypeDef epromWrite(uint16_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite);
extern uint8_t sPlcEpromTest(void);
extern uint8_t checkBlank(uint32_t adr, uint32_t size);//MCU Flash ���
void clearEprom(clarmEpromCmd_t cmd);//���EPROM����
void listEpromTable(void);
void softDelayMs(uint16_t ms);//�����ʱ
/*****************************************************************************/
extern void REBOOT(void) ;//��λ
//λָ��
extern void SSET(uint16_t A);//��Ȧ��λ
extern void RRES(uint16_t A);//��Ȧ��λ
extern void FLIP(uint16_t A) ;//��ת
extern uint8_t LD(uint16_t A) ;//����
extern uint8_t LDB(uint16_t A) ;//��������
extern uint8_t LDP(uint16_t A) ;//����������
extern uint8_t LDN(uint16_t A) ;//�����½���
//��ʱ��ָ��
extern void T10MS(uint8_t A, uint8_t start, uint16_t value) ;//10mS��ʱ������
extern void T100MS(uint8_t A, uint8_t start, uint16_t value) ;//100mS��ʱ������
//����ָ��
extern void CLR(uint16_t A) ;//�Ĵ�������
extern void CLRD(uint16_t A) ;//32λ�Ĵ�������
extern void MOV(uint16_t dist, uint16_t src) ;//16λ�Ĵ�������
extern void MOVD(uint16_t dist, uint16_t src) ;//32λ�Ĵ�������
extern void SWAP(uint16_t dist, uint16_t src) ;//����A�ĸߵ��ֽ�
extern void ABS16(uint16_t dist, uint16_t src) ;//16λ�������ֵ
extern void ABS32(uint16_t dist, uint16_t src) ;//32λ�������ֵ
extern void SMIN16(uint16_t index, uint16_t length, uint16_t min) ;//16λ�з�����������Сֵ
extern void SMAX16(uint16_t index, uint16_t length, uint16_t max) ;//16λ�з������������ֵ
extern void UMIN16(uint16_t index, uint16_t length, uint16_t min) ;//16λ�޷�����������Сֵ
extern void UMAX16(uint16_t index, uint16_t length, uint16_t max) ;//16λ�޷������������ֵ
extern void SUM16(uint16_t index, uint16_t length, uint16_t sum) ;//16BIT�����->32BIT
extern void MULT32(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16*16->32�Ǳ��ͳ˷� D = Sa * Sb
extern void MULTS16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16*16->16���ͳ˷� D = Sa * Sb
extern void MULT16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16*16->16�Ǳ��ͳ˷� D = Sa * Sb
extern void SUB32(uint16_t Sa, uint16_t Sb, uint16_t D) ;//32λ�Ǳ��ͼ��� D = Sa - Sb
extern void SUBS16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16λ���ͼ��� D = Sa - Sb
extern void SUB16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16λ�Ǳ��ͼ��� D = Sa - Sb
extern void ADD32(uint16_t Sa, uint16_t Sb, uint16_t D) ;//32λ�Ǳ��ӷ� D = Sa + Sb
extern void ADDS32(uint16_t Sa, uint16_t Sb, uint16_t D) ;//32λ���ͼӷ� D = Sa + Sb
extern void ADDS16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16λ���ͼӷ� D = Sa + Sb
extern void ADD16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16λ�Ǳ��ͼӷ� D = Sa + Sb
extern void ADD1(uint16_t Sa) ;//16λ�Ǳ����Լ�
extern void ADDS1(uint16_t Sa) ;//16λ�����Լ�
extern void DEC1(uint16_t Sa) ;//16λ�Ǳ����Լ�
extern void DECS1(uint16_t Sa) ;//16λ�����Լ�
extern void ADL1(uint16_t Sa) ;//32λ�Ǳ����Լ�
extern void ADLS1(uint16_t Sa) ;//32λ�����Լ�
extern void DEL1(uint16_t Sa) ;//32λ�Ǳ����Լ�
extern void DELS1(uint16_t Sa) ;//32λ�����Լ�
extern void TNTC(uint16_t dist, uint16_t src);//CODEת��Ϊ�����¶�
extern void TENV(uint16_t dist, uint16_t src);//CODEת��ΪNTC�����¶��¶�
extern void BCPY(uint16_t dist, uint16_t src, uint16_t length);//�鸴��
extern void LIMS16(uint16_t src, uint16_t min, uint16_t max);//�з���16λ�����Ʒ���ָ��
extern void UPDAC0(void);//��������DAC0
extern void UPDAC1(void);//��������DAC1
extern void UPDAC2(void);
extern void UPDAC3(void);
extern void CLDAC(void);//�������DAC0��DAC1
extern void IMDIO(void) ;//��������IO��״̬���������
extern void NVSAVE(void);//ǿ����������NVRAM
extern void NVFSAVE(void);//NVRAMȫ��д��EPROM
extern void NVLOAD(void);
extern void FDSAV(void);
extern void FDLAD(void);
extern void FDSAV_ONE(int16_t cn);
extern void FDLAD_ONE(int16_t cn);
extern void PRTM(uint16_t adr, uint8_t len);
extern void LINKS(void);//�ӻ�����
extern void LINKM(void);//��������
extern void EDLAR(void);//ֹͣ��������
extern void STLAR(void);//��ʼ��������
/*****************************************************************************/
#endif
