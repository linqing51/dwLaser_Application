#include "sPlc.h"
/*****************************************************************************/
#define BEEM_MODE_0													0x10//����ģʽ
#define BEEM_MODE_1													0x11//����ͬ��
#define BEEM_MODE_2													0x12//���ⷢ��̶����
#define BEEM_MODE_3													0x13//�쳣����
/*****************************************************************************/
void resetInit(void);
void bootLoadInit(void);
/*****************************************************************************/
void sPlcLoudspeakerLoop(void);//��������ѯ
void sPlcAimLoop(void);//��׼����ѯ
void sPlcAutoFanLoop(void);//��������ѯ����
void setLoudspeakerFreq(int16_t freq);//��������Ƶ��
void setLoudspeakerVolume(int16_t volume);//������������
void setLoudspeakerEnable(void);//������������
void setLoudspeakerDisable(void);//�ر�����������
void initLoudspeaker(void);//���ȳ�ʼ��
void setAimFreq(int16_t freq);//����AIM PWMƵ��
void setLedFreq(int16_t freq);//����LED PWMƵ��
void setFanFreq(int16_t freq);//����FAN PWMƵ��
void setAimBrightness(int16_t brg);//������׼������
void setRedLedBrightness(int16_t brg);//����R LED����
void setGreenLedBrightness(int16_t brg);//����G LED����
void setYellowLedBrightness(int16_t brg);//����Y LED����
/*****************************************************************************/







