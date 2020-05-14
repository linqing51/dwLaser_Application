#ifndef __SPLCDK25L_H__
#define __SPLCDK25L_H__
/*****************************************************************************/
#include "sPlcPort.h"
/*****************************************************************************/
#define DK25L_FWVER												0x12
#define DK25L_HWVER												0x34
/*****************************************************************************/
#define DK25L_STX												0xAA//
//ͨ��ָ��
#define CMD_FIND_CARD_UID										0x01//��ȡ��ƬUID
#define CMD_FIND_CARD_TYPE										0x02//��ȡ��Ƭ����
#define CMD_AUTO_FIND_CARD										0x95//�Զ�Ѱ������
#define CMD_MOD_BAUDRATE										0xA0//�޸�ģ�鲨����
#define CMD_CONFIG_SYS_PARA										0xA1//����ϵͳ����ָ��
#define CMD_READ_SYS_PARA										0xA2//��ȡϵͳ����ָ��
#define CMD_READ_FW_VER											0xB0//��ȡģ��̼��汾��
#define CMD_READ_HW_VER											0xB1//��ȡģ��Ӳ���汾��
//Mifareָ��
#define CMD_MIFARE_SET_KEYA										0x03//��ģ��д����Ҫ��֤����Կ(A��Կ)
#define CMD_MIFARE_READ_BLOCK									0x04//Mifare ������
#define CMD_MIFARE_WRITE_BLOCK									0x05//Mifare ��д��
#define CMD_MIFATE_WALLET_INIT									0x06//Mifare ������ֵ��ʼ��
#define CMD_MIFARE_WALLET_CHARGE								0x07//Mifare ����ֵ
#define CMD_MIFARE_WALLET_CHARGEBACK							0x08//Mifare ����ֵ
#define CMD_MIFARE_SET_KEYB										0x0B//����ģ��д����Ҫ��֤����Կ(B��Կ)
#define CMD_MIFARE_SET_KEY_TYPE									0x0C//����ģ��ʹ����Կ������
//Ultralight ������ָ��
#define CMD_ULTRALIGHT_READ_BLOCK								0x09//Ultralight������
#define CMD_ULTRALIGHT_WRITE_BLOCK								0x0A//Ultralight��д��
#define CMD_ULTRALIGHT_READ_MBLOCK								0x1C//Ultralight���������
#define CMD_ULTRALIGHT_SET_MBLOCK								0x1D//Ultralight��д�����
//ISO14443-A CPU������ָ��
#define CMD_ISO14443A_ACTIVATE									0x15//ISO14443-A CPU��Ƭ����ָ��
#define CMD_ISO14443A_APDU										0x17//ISO14443-A CPU��APDUָ��ӿ�
#define CMD_ISO14443A_POWEROFF									0x18//ISO14443-A CPU��Ƭ�ϵ�ָ��
//ISO14443-B���֤
#define CMD_ISO14443B_ACTIVATE									0x14//���֤����ָ��
#define CMD_ISO14443B_APDU										0x16//���֤APDUָ��ӿ�
#define CMD_ISO14443B_POWEROFF									0x18//��Ƭ�ϵ�ָ��ر�����ָ��ӿ�
//ISO15693
#define CMD_ISO15693_GET_BLOCK									0x09//ISO15693������
#define CMD_ISO15693_GET_MBLOCK									0x1C//ISO15693���������
#define CMD_ISO15693_SET_MBLOCK									0x1D//ISO15693��д�����
//ģ�鷴��
#define CMD_ERR_TAG_TYPE										0xE0//�����ʹ�����ָ��	
#define CMD_ERR_NOT_FIND										0xE1//δѰ�ҿ�������ָ��
#define CMD_ERR_NOT_MACH										0xE2//��Կ��ƥ�������ָ��
#define CMD_ERR_GET												0xE3//����ʧ�ܴ���ָ��
#define CMD_ERR_SET												0xE4//д��ʧ�ܴ���ָ��
#define CMD_ERR_M1_INIT											0xE5//M1��ֵ��ʼ��ʧ�ܴ���ָ��
#define CMD_ERR_M1_ADD											0xE6//M1����ֵʧ�ܴ���ָ��
#define CMD_ERR_M1_DEC											0xE7//M1����ֵʧ�ܴ���ָ��
#define CMD_ACK													0xFE//ACKȷ������
#define CMD_NACK												0xFF//NACK��������
/*****************************************************************************/
#define CARD_UNKNOWN											0x00
#define CARD_MIFARE												0x01
#define CARD_ULTRALIGHT											0x02
#define CARD_ISO14443B											0x03
#define CARD_ISO14443A											0x04
#define CARD_ISO15693											0x05
/*****************************************************************************/
extern uint8_t xdata DK25L_TxBuffer[CONFIG_DK25L_TXBUF_SIZE];//ָ��ͻ�����
extern uint8_t xdata DK25L_RxBuffer[CONFIG_DK25L_RXBUF_SIZE];//ָ����ջ�����
/*****************************************************************************/
void DL25L_Init(void);//DK25L NFCģ���ʼ��
void DK25L_GET_UID(void);//��ȡ��Ƭ UID
void DK25L_GET_TPYE(void);//��ȡ��Ƭ����
void DK25L_GET_FWVER(void);//��ȡģ������汾��
void DK25L_GET_HWVER(void);//��ȡģ��Ӳ���汾��
void DK25L_MIFARE_SET_KEYA(uint8_t *pKey);//д��M1��KEYA��Կ��ģ��
void DK25L_MIFARE_SET_KEYB(uint16_t *pKey);//д��M1��KEYB��Կ��ģ��
void DK25L_MIFARE_WALLET_INIT(uint8_t block);//M1������Ǯ����ʼ��ָ��
void DK25L_MIFARE_WALLET_CHARGE(uint8_t block, uint8_t *pdat);//M1������Ǯ����ֵָ��
void DK25L_MIFARE_WALLET_CHARGEBACK(uint8_t block, uint8_t *pdat);//M1������Ǯ���ۿ�ָ��
void DL25L_MIFARE_WRITE_BLOCK(uint8_t block, uint8_t *pdat);//M1��д��ָ��
void DL25L_MIFARE_READ_BLOCK(uint8_t block);//M1������ָ��
void DL25L_MIFARE_SET_KEY_TYPE(uint8_t type);//����ģ��ʹ����Կ������
void DL25L_ULTRALIGHT_READ_BLOCK(uint8_t block);//UL������ָ��
void DL25L_ULTRALIGHT_WRITE_BLOCK(uint8_t block, uint8_t *pdat);//UL��д��ָ��
void DL25L_ULTRALIGHT_READ_MBLOCK(uint8_t blockStart, uint8_t blockEnd);//UL���������ָ��
void DL25L_ULTRALIGHT_WRITE_MBLOCK(uint8_t blockStart, uint8_t blockEnd, uint8_t *pdat);//UL��д�����ָ��
void DL25L_ISO14443A_ACTIVATE(void);//ISO14443A ������ָ��
void DL25L_ISO14443A_APDU(uint8_t length, uint8_t *pdat);//ISO14443A PDUָ��ӿ�
void DK25L_EnableRx(int8_t ena);
#endif