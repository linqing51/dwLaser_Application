#include "sPlc.h"
/*****************************************************************************/
#define BEEM_MODE_0													0x10//����ģʽ
#define BEEM_MODE_1													0x11//����ͬ��
#define BEEM_MODE_2													0x12//���ⷢ��̶����
#define BEEM_MODE_3													0x13//�쳣����
/*****************************************************************************/
void sPlcBeemLoop(void);//��������ѯ
void sPlcAimLoop(void);//��׼����ѯ
void setBeemFreq(int16_t freq);//���÷�����Ƶ�ʺ�ռ�ձ�
void setBeemVolume(int16_t dc);//���÷�����ռ�ձ�
void setLedAimFreq(int16_t freq);//����LED�ƺ���׼����˸Ƶ��
void setAimDutyCycle(int16_t dc);//������׼������
void setRedLedDutyCycle(int16_t dc);//����R LED����
void setGreenLedDutyCycle(int16_t dc);//����G LED����
void setBlueLedDutyCycle(int16_t dc);//����B LED����
void disableSplcTimer(void);//SPLC�رռ�ʱ��
void enableSplcTimer(void);//SPLC�򿪼�ʱ��
/*****************************************************************************/
uint16_t crc16Calculate(uint8_t *buf, uint32_t len);//CRC16 ��������
uint16_t crc16CalculateAdd(uint8_t dat);//CRC16 ���������ֽ�
void crc16Clear(void);//��վ�CRC16���
void crc16SetCrcOld(uint16_t old);
/*****************************************************************************/
uint32_t crc32Calculate(uint8_t *buf, uint32_t len);//CRC32 ��������
uint32_t crc32CalculateAdd(uint8_t dat);//CRC32 ���������ֽ�
void crc32Clear(void);//��վ�CRC32���
void crc32SetCrcOld(uint32_t old);





