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
static void uint8ToAscii(uint8_t *pchar, uint8_t* pAscii);//UINT8תASCII
static void uint16ToAscii(uint16_t *pchar, uint8_t* pAscii);//UINT16תASCII
static void uint32ToAscii(uint32_t *pchar, uint8_t* pAscii);//UINT32תASCII
static uint8_t  asciiToUint8(uint8_t *pdat);//ASCIIת�޷�����
static uint16_t asciiToUint16(uint8_t *pdat);//ASCIIתΪ�޷���16λ��
static uint32_t asciiToUint32(uint8_t *pdat);//ASCIIתΪ�޷���32λ��
static uint8_t  checkLrc(uint8_t *pdata, uint8_t len);//����LRCУ��ֵ
static uint8_t  mLinkState, sLinkState;//״̬��
/******************************************************************************/
void LINKS(void){//�ӻ�����
	uint8_t id, len, lrc0, lrc1;
	switch(sLinkState){
		case LIKN_STATE_S_IDEL:{
			
			sLinkState = LINK_STATE_S_WAIT_RECE;
			break;
		}
		case LINK_STATE_S_WAIT_RECE:{
			if(LD(SPCOIL_LINK_RECE_DONE)){//�������
				id = asciiToUint8(LKRRAM + 1);
				//fun = asciiToUint8(LKRRAM + 3);
				len = asciiToUint8(LKRRAM + 5);
				lrc0 = asciiToUint8(LKRRAM + 1 + len);
				lrc1 = checkLrc((LKRRAM + 7), (len - 4));
				if(lrc0 == lrc1){//У������
					switch(id){
						case LINK_FUN_01:{
							
							sLinkState = LINK_STATE_S_SEND_REQ;
							break;
						}
						default:break;
					}
				}
				else{//У��ʧ��
				}
			}
			else{
				sLinkState = LINK_STATE_S_WAIT_RECE;
			}
			case LINK_STATE_S_SEND_REQ:{
				
				break;
			}
		}
		default:break;
	}
    
}
static void LINKM(void){//��������
	HAL_StatusTypeDef ret;
	uint16_t sendSize, receSize, temp0, temp1, temp2;
	uint8_t lrc0, lrc1, slaveFun;
	ret = HAL_ERROR;
	switch(mLinkState){
		case LINK_STATE_M_IDEL:{//�������Ϳ���
			RRES(SPCOIL_LINK_SEND_DONE);
			RRES(SPCOIL_LINK_SEND_BUSY);
			RRES(SPCOIL_LINK_SEND_ERR);
			RRES(SPCOIL_LINK_RECE_BUSY);
			RRES(SPCOIL_LINK_RECE_DONE);
			RRES(SPCOIL_LINK_RECE_ERR);
			mLinkState = LINK_STATE_M_SEND_REQ;
			break;
		}
		case LINK_STATE_M_SEND_REQ:{//����������
			sendSize = 0;
			slaveFun = asciiToUint8(LKSRAM + 3);//ASCIIת�޷�����
			switch(slaveFun){//���㷢���ֽ���
				case LINK_FUN_01:{//����Ȧ
					//STX0|ID1|ID2|FUN3|FUN4|ADR5|ADR6|ADR7|ADR8|NUM9|NUM10|NUM11|NUM12|LRC13|LRC14|ETX15|ETX16
					lrc0 = checkLrc((LKSRAM + 3), 10);//����LRCУ��ֵ
					uint8ToAscii(&lrc0, LKSRAM + 13);
					LKSRAM[15] = LINK_ETX0;
					LKSRAM[16] = LINK_ETX1;
					sendSize = 17;
					break;
				}
				case LINK_FUN_02:{//����ɢ������
					//STX0|ID1|ID2|FUN3|FUN4|ADR5|ADR6|ADR7|ADR8|NUM9|NUM10|NUM11|NUM12|LRC13|LRC14|ETX15|ETX16
					lrc0 = checkLrc((LKSRAM + 3), 10);//����LRCУ��ֵ
					uint8ToAscii(&lrc0, LKSRAM + 13);
					LKSRAM[15] = LINK_ETX0;
					LKSRAM[16] = LINK_ETX1;
					sendSize = 17;
					break;
				}
				case LINK_FUN_03:{//�����ּĴ���
					//STX0|ID1|ID2|FUN3|FUN4|ADR5|ADR6|ADR7|ADR8|NUM9|NUM10|NUM11|NUM12|LRC13|LRC14|ETX15|ETX16
					lrc0 = checkLrc((LKSRAM + 3), 10);//����LRCУ��ֵ
					uint8ToAscii(&lrc0, LKSRAM + 13);
					LKSRAM[15] = LINK_ETX0;
					LKSRAM[16] = LINK_ETX1;
					sendSize = 17;
					break;
				}
				case LINK_FUN_04:{//������Ĵ���
					//STX0|ID1|ID2|FUN3|FUN4|ADR5|ADR6|ADR7|ADR8|NUM9|NUM10|NUM11|NUM12|LRC13|LRC14|ETX15|ETX16
					lrc0 = checkLrc((LKSRAM + 3), 10);//����LRCУ��ֵ
					uint8ToAscii(&lrc0, LKSRAM + 13);
					LKSRAM[15] = LINK_ETX0;
					LKSRAM[16] = LINK_ETX1;
					sendSize = 17;
					break;
				}
				case LINK_FUN_05:{//д������Ȧ
					//STX0|ID1|ID2|FUN3|FUN4|ADR5|ADR6|ADR7|ADR8|DAT9|DAT10|DAT11|DAT12|LRC13|LRC14|ETX15|ETX16
					lrc0 = checkLrc((LKSRAM + 3), 10);//����LRCУ��ֵ
					uint8ToAscii(&lrc0, LKSRAM + 13);
					LKSRAM[15] = LINK_ETX0;
					LKSRAM[16] = LINK_ETX1;
					sendSize = 17;
					break;
				}
				case LINK_FUN_06:{//д�����Ĵ���
					//STX0|ID1|ID2|FUN3|FUN4|ADR5|ADR6|ADR7|ADR8|DAT9|DAT10|DAT11|DAT12|LRC13|LRC14|ETX15|ETX16
					lrc0 = checkLrc((LKSRAM + 3), 10);//����LRCУ��ֵ
					uint8ToAscii(&lrc0, LKSRAM + 13);
					LKSRAM[15] = LINK_ETX0;
					LKSRAM[16] = LINK_ETX1;
					sendSize = 17;
					break;
				}
				case LINK_FUN_0F:{//д�����Ȧ
					//STX0|ID1|ID2|FUN3|FUN4|ADR5|ADR6|ADR7|ADR8|NUM9|NUM10|NUM11|NUM12|DAT++++++|LRC13|LRC14|ETX15|ETX16
					temp0 = asciiToUint16(LKSRAM + 9);//��ȡ�������
					if(temp0 % 8){
						temp1 = temp0 / 8 * 2;
					}
					else{
						temp1 = (temp0 /  8 + 1) * 2;
					}
					lrc0 = checkLrc((LKSRAM + 3), temp1 + 12);//����LRCУ��ֵ
					uint8ToAscii(&lrc0, LKSRAM + 13 + temp1);
					LKSRAM[15 + temp1] = LINK_ETX0;
					LKSRAM[16 + temp1] = LINK_ETX1;
					sendSize = 17 + temp1;
					break;
				}
				case LINK_FUN_10:{//д����Ĵ���
					//STX0|ID1|ID2|FUN3|FUN4|ADR5|ADR6|ADR7|ADR8|NUM9|NUM10|NUM11|NUM12|DAT++++++|LRC13|LRC14|ETX15|ETX16
					temp0 = asciiToUint16(LKSRAM + 9);//��ȡ�������
					if(temp0 % 8){
						temp1 = temp0 / 8 * 2;
					}
					else{
						temp1 = (temp0 /  8 + 1) * 2;
					}
					lrc0 = checkLrc((LKSRAM + 3), temp1 + 12);//����LRCУ��ֵ
					uint8ToAscii(&lrc0, LKSRAM + 13 + temp1);
					LKSRAM[15 + temp1] = LINK_ETX0;
					LKSRAM[16 + temp1] = LINK_ETX1;
					sendSize = 17 + temp1;
					break;
				}
				default:{
					break;
				}
			}
			SSET(SPCOIL_LINK_SEND_BUSY);
			RRES(SPCOIL_LINK_SEND_DONE);			
			RRES(SPCOIL_LINK_SEND_ERR);
			NVRAM0[SPREG_LINK_SEND_SIZE] = sendSize;
			ret = HAL_UART_Transmit_DMA(&huart1, LKSRAM, sendSize);//DMA��ʽ����
			NVRAM0[SPREG_LINK_SEND_TCOUNTER] = 0;
			mLinkState = LINK_STATE_M_WAIT_SEND_DONE;
			break;
		}
		case LINK_STATE_M_WAIT_SEND_DONE:{//�ȴ������������
			if(LD(SPCOIL_LINK_SEND_DONE)){
				//�л�RS485 DIR->RX
				//����UART����
				SSET(SPCOIL_LINK_RECE_BUSY);
				RRES(SPCOIL_LINK_RECE_DONE);
				ret = HAL_UART_Receive_DMA(&huart1, LKRRAM, receSize);
				mLinkState = LINK_STATE_M_WAIT_RECE_DONE;	
			}
			else if(NVRAM0[SPREG_LINK_SEND_TCOUNTER] > NVRAM0[SPREG_LINK_SEND_OVERTIME]){
				NVRAM0[SPREG_LINK_STATE] = LINK_RET_SEND_OVERTIME;//д������
				SSET(SPCOIL_LINK_SEND_ERR);//ֹͣ����
				ret = HAL_UART_DMAStop(&huart1);//ֹͣ����
				mLinkState = LINK_STATE_M_IDEL;
			}
			break;
		}
		case LINK_STATE_M_WAIT_RECE_DONE:{//�ȴ������������
			if(LD(SPCOIL_LINK_RECE_DONE)){//�������
				//���LCRУ��
				lrc0 = checkLrc(LKRRAM, (receSize - 2));
				lrc1 = asciiToUint8(LKRRAM + receSize);//ASCIIת�޷����� 
				if(lrc0 == lrc1){//У����ȷ
					NVRAM0[SPREG_LINK_STATE] = LINK_RET_OK;
					RRES(SPCOIL_LINK_RECE_BUSY);	
					SSET(SPCOIL_LINK_RECE_DONE);	
					RRES(SPCOIL_LINK_RECE_ERR);
				}
				else{//У�����
					NVRAM0[SPREG_LINK_STATE] = LINK_RET_LRC_ERR;
					RRES(SPCOIL_LINK_RECE_BUSY);	
					RRES(SPCOIL_LINK_RECE_DONE);	
					SSET(SPCOIL_LINK_RECE_ERR);
				}
			}
			else if(NVRAM0[SPREG_LINK_RECE_TCOUNTER] > NVRAM0[SPREG_LINK_RECE_OVERTIME]){//���ճ�ʱ
				NVRAM0[SPREG_LINK_STATE] = LINK_RET_RECE_OVERTIME;//д������
				RRES(SPCOIL_LINK_RECE_BUSY);	
				RRES(SPCOIL_LINK_RECE_DONE);	
				SSET(SPCOIL_LINK_RECE_ERR);
			}
			break;
		}
		default:break;
	}
}
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
static void uint16ToAscii(uint16_t *pchar, uint8_t* pAscii){//UINT16תASCII
	
	
}
static void uint32ToAscii(uint32_t *pchar, uint8_t* pAscii){//UINT32תASCII
}
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

static uint16_t asciiToUint16(uint8_t *pdat){//ASCIIתΪ�޷���16λ��
	return 0;
}
static uint32_t asciiToUint32(uint8_t *pdat){//ASCIIתΪ�޷���32λ��
	return 0;
}




