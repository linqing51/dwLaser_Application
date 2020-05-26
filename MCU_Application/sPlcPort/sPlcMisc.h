#include "sPlc.h"
/*****************************************************************************/
#define BEEM_MODE_0													0x10//����ģʽ
#define BEEM_MODE_1													0x11//����ͬ��
#define BEEM_MODE_2													0x12//���ⷢ��̶����
#define BEEM_MODE_3													0x13//�쳣����
#define BEEM_FREQ_0													0xF2//����Ƶ��
#define BEEM_FREQ_1													0xF1//���
/*****************************************************************************/
void sPlcBeemLoop(void);//��������ѯ
void sPlcAimLoop(void);//��׼����ѯ
void setBeemFreq(uint32_t freq);//���÷�����Ƶ�ʺ�ռ�ձ�
void setBeemDutyCycle(uint8_t dc);//���÷�����ռ�ձ�
void setLedAimFreq(uint32_t freq);//����LED�ƺ���׼����˸Ƶ��
void setAimDutyCycle(uint8_t dc);//������׼������
void setRedLedDutyCycle(uint8_t dc);//����R LED����
void setGreenLedDutyCycle(uint8_t dc);//����G LED����
void setBlueLedDutyCycle(uint8_t dc);//����B LED����
void initWatchDog(void);
void enableWatchDog(void);
void disableWatchDog(void);
void feedWatchDog(void);
void mucReboot(void);
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





