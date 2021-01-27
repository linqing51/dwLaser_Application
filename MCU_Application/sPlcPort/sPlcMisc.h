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
void setLoudspeakerFreq(int16_t freq);//��������Ƶ��
void setLoudspeakerVolume(int16_t volume);//������������
void setLoudspeakerEnable(void);//������������
void setLoudspeakerDisable(void);//�ر�����������
void initLoudspeaker(void);//���ȳ�ʼ��
void setLedAimFreq(int16_t freq);//����LED�ƺ���׼����˸Ƶ��
void setAimBrightness(int16_t brg);//������׼������
void setRedLedBrightness(int16_t brg);//����R LED����
void setGreenLedBrightness(int16_t brg);//����G LED����
void setBlueLedBrightness(int16_t brg);//����B LED����
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





