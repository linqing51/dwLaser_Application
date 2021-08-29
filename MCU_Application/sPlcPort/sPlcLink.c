#include "sPlcLink.h"
//SPLC LINKͨ�ų��� �̶����� PORT0Ϊ��Э��
//LINK�Զ���Э����MODBUS ASCII���ݲ���չ�˹���ָ��
/*****************************************************************************/
extern UART_HandleTypeDef huart1;
/*****************************************************************************/
#define LINK_FUN_01												0x01//��ȡ��Ȧ״̬
#define LINK_FUN_02												0x02//��ȡ����״̬
#define LINK_FUN_03												0x03//��ȡ���ּĴ���
#define LINK_FUN_04												0x04//��ȡ����Ĵ���
#define LINK_FUN_05												0x05//ǿ�Ƶ�����Ȧ
#define LINK_FUN_06												0x06//Ԥ�õ����Ĵ���
#define LINK_FUN_0F												0x0F//ǿ�ƶ����Ȧ
#define LINK_FUN_10												0x10//Ԥ�ö���Ĵ���
#define LINK_FUN_14												0x14//��ȡ�ļ���¼
#define LINK_FUN_16												0x16//����д��Ĵ���
#define LINK_FUN_17												0x17//��д����Ĵ���
#define LINK_FUN_2B												0x18//��ȡ�豸ID
#define LINK_FUN_55												0x19//����
/*****************************************************************************/
#define LINK_STX												0x3A//��ʼ�ַ�
#define LINK_ETX0												0x0D//�����ַ�
#define LINK_ETX1												0x0A//�����ַ�
/******************************************************************************/
#define LINK_STATE_M_IDEL										0x00//��������
#define LINK_STATE_M_SEND_REQ									0x01//����������
#define LINK_STATE_M_WAIT_SEND_DONE								0x02//�ȴ������������
#define LINK_STATE_M_WAIT_RECE_DONE								0x03//�ȴ������������
#define LINK_STATE_M_DONE										0x04//�������
#define LINK_STATE_M_FAIL										0xFF//ʧ��
/*****************************************************************************/
#define LIKN_STATE_S_IDEL										0x01
#define LINK_STATE_S_WAIT_RECE									0x02
#define LINK_STATE_S_SEND_REQ									0x03
#define LINK_STATE_S_FAIL										0x04
/*****************************************************************************/
#define LINK_RET_OK												0x01
#define LINK_RET_SEND_OVERTIME									0x02
#define LINK_RET_RECE_OVERTIME									0x03
#define LINK_RET_LRC_ERR										0x04
/*****************************************************************************/
//static void uint8ToAscii(uint8_t *pchar, uint8_t* pAscii);//UINT8תASCII
//static uint8_t  asciiToUint8(uint8_t *pdat);//ASCIIת�޷�����
static uint8_t  checkLrc(uint8_t *pdata, uint8_t len);//����LRCУ��ֵ
static uint8_t  mLinkState, sLinkState;//״̬��
/******************************************************************************/
static uint8_t checkLrc(uint8_t *pdata, uint8_t len){//����LRCУ��ֵ
    /* LRC result */
    uint8_t lrc = 0;
    /* pass through all the data */
    while(len--){
        lrc = lrc + *pdata++;
    }
    /* produce the two's-complement */
    lrc = (0xFF - lrc) + 0x01;
    return lrc;
}
/*
static void uint8ToAscii(uint8_t *pchar, uint8_t* pAscii){//UINT8תASCII
	*pAscii = (uint8_t)(*pchar / 16);
	if(*pAscii < 10){
		*pAscii += 48;
	}
	else{
		*pAscii = *pAscii - 10 + 65;
	}
	*(pAscii + 1) = *pchar % 16;
	if(*(pAscii + 1) < 10){
		*(pAscii + 1) += 48;
	}
	else{
		*(pAscii + 1) = *(pAscii + 1) - 10 + 65;
	}
}
*/
/*
static uint8_t asciiToUint8(uint8_t *pdat){//ASCIIתUINT8
	uint8_t temp0, temp1;
	if (*pdat >= '0' && *pdat <= '9'){
		temp0 = *pdat - '0';
	}
	if (*pdat >= 'A' && *pdat <= 'F'){
		temp0 = 10 + *pdat - 'A';
	}
	if (*(pdat+1) >= '0' && *(pdat+1) <= '9'){
		temp1 = *(pdat+1) - '0';
	}
	if (*(pdat+1) >= 'A' && *(pdat+1) <= 'F'){
		temp1 = 10 + *(pdat+1) - 'A';
	}
		return (temp0 << 4) | temp1;	
}
*/



