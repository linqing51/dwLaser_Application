#include "sPlcLink.h"
//SPLC LINK通信程序 固定串口 PORT0为此协议
//LINK自定义协议与MODBUS ASCII兼容并扩展了功能指令
/*****************************************************************************/
extern UART_HandleTypeDef huart1;
/*****************************************************************************/
#define LINK_FUN_01												0x01//读取线圈状态
#define LINK_FUN_02												0x02//读取输入状态
#define LINK_FUN_03												0x03//读取保持寄存器
#define LINK_FUN_04												0x04//读取输入寄存器
#define LINK_FUN_05												0x05//强制单个线圈
#define LINK_FUN_06												0x06//预置单个寄存器
#define LINK_FUN_0F												0x0F//强制多个线圈
#define LINK_FUN_10												0x10//预置多个寄存器
#define LINK_FUN_14												0x14//读取文件记录
#define LINK_FUN_16												0x16//掩码写入寄存器
#define LINK_FUN_17												0x17//读写多个寄存器
#define LINK_FUN_2B												0x18//读取设备ID
#define LINK_FUN_55												0x19//重启
/*****************************************************************************/
#define LINK_STX												0x3A//起始字符
#define LINK_ETX0												0x0D//结束字符
#define LINK_ETX1												0x0A//结束字符
/******************************************************************************/
#define LINK_STATE_M_IDEL										0x00//主机空闲
#define LINK_STATE_M_SEND_REQ									0x01//主机请求发送
#define LINK_STATE_M_WAIT_SEND_DONE								0x02//等待主机发送完成
#define LINK_STATE_M_WAIT_RECE_DONE								0x03//等待主机接收完成
#define LINK_STATE_M_DONE										0x04//传输完成
#define LINK_STATE_M_FAIL										0xFF//失败
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
static void uint8ToAscii(uint8_t *pchar, uint8_t* pAscii);//UINT8转ASCII
static void uint16ToAscii(uint16_t *pchar, uint8_t* pAscii);//UINT16转ASCII
static void uint32ToAscii(uint32_t *pchar, uint8_t* pAscii);//UINT32转ASCII
static uint8_t  asciiToUint8(uint8_t *pdat);//ASCII转无符号数
static uint16_t asciiToUint16(uint8_t *pdat);//ASCII转为无符号16位数
static uint32_t asciiToUint32(uint8_t *pdat);//ASCII转为无符号32位数
static uint8_t  checkLrc(uint8_t *pdata, uint8_t len);//计算LRC校验值
static uint8_t  mLinkState, sLinkState;//状态机
/******************************************************************************/
void LINKS(void){//从机接收
	uint8_t id, len, lrc0, lrc1;
	switch(sLinkState){
		case LIKN_STATE_S_IDEL:{
			
			sLinkState = LINK_STATE_S_WAIT_RECE;
			break;
		}
		case LINK_STATE_S_WAIT_RECE:{
			if(LD(SPCOIL_LINK_RECE_DONE)){//接收完毕
				id = asciiToUint8(LKRRAM + 1);
				//fun = asciiToUint8(LKRRAM + 3);
				len = asciiToUint8(LKRRAM + 5);
				lrc0 = asciiToUint8(LKRRAM + 1 + len);
				lrc1 = checkLrc((LKRRAM + 7), (len - 4));
				if(lrc0 == lrc1){//校验正常
					switch(id){
						case LINK_FUN_01:{
							
							sLinkState = LINK_STATE_S_SEND_REQ;
							break;
						}
						default:break;
					}
				}
				else{//校验失败
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
static void LINKM(void){//主机发送
	HAL_StatusTypeDef ret;
	uint16_t sendSize, receSize, temp0, temp1, temp2;
	uint8_t lrc0, lrc1, slaveFun;
	ret = HAL_ERROR;
	switch(mLinkState){
		case LINK_STATE_M_IDEL:{//主机发送空闲
			RRES(SPCOIL_LINK_SEND_DONE);
			RRES(SPCOIL_LINK_SEND_BUSY);
			RRES(SPCOIL_LINK_SEND_ERR);
			RRES(SPCOIL_LINK_RECE_BUSY);
			RRES(SPCOIL_LINK_RECE_DONE);
			RRES(SPCOIL_LINK_RECE_ERR);
			mLinkState = LINK_STATE_M_SEND_REQ;
			break;
		}
		case LINK_STATE_M_SEND_REQ:{//主机请求发送
			sendSize = 0;
			slaveFun = asciiToUint8(LKSRAM + 3);//ASCII转无符号数
			switch(slaveFun){//计算发送字节数
				case LINK_FUN_01:{//读线圈
					//STX0|ID1|ID2|FUN3|FUN4|ADR5|ADR6|ADR7|ADR8|NUM9|NUM10|NUM11|NUM12|LRC13|LRC14|ETX15|ETX16
					lrc0 = checkLrc((LKSRAM + 3), 10);//计算LRC校验值
					uint8ToAscii(&lrc0, LKSRAM + 13);
					LKSRAM[15] = LINK_ETX0;
					LKSRAM[16] = LINK_ETX1;
					sendSize = 17;
					break;
				}
				case LINK_FUN_02:{//读离散量输入
					//STX0|ID1|ID2|FUN3|FUN4|ADR5|ADR6|ADR7|ADR8|NUM9|NUM10|NUM11|NUM12|LRC13|LRC14|ETX15|ETX16
					lrc0 = checkLrc((LKSRAM + 3), 10);//计算LRC校验值
					uint8ToAscii(&lrc0, LKSRAM + 13);
					LKSRAM[15] = LINK_ETX0;
					LKSRAM[16] = LINK_ETX1;
					sendSize = 17;
					break;
				}
				case LINK_FUN_03:{//读保持寄存器
					//STX0|ID1|ID2|FUN3|FUN4|ADR5|ADR6|ADR7|ADR8|NUM9|NUM10|NUM11|NUM12|LRC13|LRC14|ETX15|ETX16
					lrc0 = checkLrc((LKSRAM + 3), 10);//计算LRC校验值
					uint8ToAscii(&lrc0, LKSRAM + 13);
					LKSRAM[15] = LINK_ETX0;
					LKSRAM[16] = LINK_ETX1;
					sendSize = 17;
					break;
				}
				case LINK_FUN_04:{//读输入寄存器
					//STX0|ID1|ID2|FUN3|FUN4|ADR5|ADR6|ADR7|ADR8|NUM9|NUM10|NUM11|NUM12|LRC13|LRC14|ETX15|ETX16
					lrc0 = checkLrc((LKSRAM + 3), 10);//计算LRC校验值
					uint8ToAscii(&lrc0, LKSRAM + 13);
					LKSRAM[15] = LINK_ETX0;
					LKSRAM[16] = LINK_ETX1;
					sendSize = 17;
					break;
				}
				case LINK_FUN_05:{//写单个线圈
					//STX0|ID1|ID2|FUN3|FUN4|ADR5|ADR6|ADR7|ADR8|DAT9|DAT10|DAT11|DAT12|LRC13|LRC14|ETX15|ETX16
					lrc0 = checkLrc((LKSRAM + 3), 10);//计算LRC校验值
					uint8ToAscii(&lrc0, LKSRAM + 13);
					LKSRAM[15] = LINK_ETX0;
					LKSRAM[16] = LINK_ETX1;
					sendSize = 17;
					break;
				}
				case LINK_FUN_06:{//写单个寄存器
					//STX0|ID1|ID2|FUN3|FUN4|ADR5|ADR6|ADR7|ADR8|DAT9|DAT10|DAT11|DAT12|LRC13|LRC14|ETX15|ETX16
					lrc0 = checkLrc((LKSRAM + 3), 10);//计算LRC校验值
					uint8ToAscii(&lrc0, LKSRAM + 13);
					LKSRAM[15] = LINK_ETX0;
					LKSRAM[16] = LINK_ETX1;
					sendSize = 17;
					break;
				}
				case LINK_FUN_0F:{//写多个线圈
					//STX0|ID1|ID2|FUN3|FUN4|ADR5|ADR6|ADR7|ADR8|NUM9|NUM10|NUM11|NUM12|DAT++++++|LRC13|LRC14|ETX15|ETX16
					temp0 = asciiToUint16(LKSRAM + 9);//获取输出数量
					if(temp0 % 8){
						temp1 = temp0 / 8 * 2;
					}
					else{
						temp1 = (temp0 /  8 + 1) * 2;
					}
					lrc0 = checkLrc((LKSRAM + 3), temp1 + 12);//计算LRC校验值
					uint8ToAscii(&lrc0, LKSRAM + 13 + temp1);
					LKSRAM[15 + temp1] = LINK_ETX0;
					LKSRAM[16 + temp1] = LINK_ETX1;
					sendSize = 17 + temp1;
					break;
				}
				case LINK_FUN_10:{//写多个寄存器
					//STX0|ID1|ID2|FUN3|FUN4|ADR5|ADR6|ADR7|ADR8|NUM9|NUM10|NUM11|NUM12|DAT++++++|LRC13|LRC14|ETX15|ETX16
					temp0 = asciiToUint16(LKSRAM + 9);//获取输出数量
					if(temp0 % 8){
						temp1 = temp0 / 8 * 2;
					}
					else{
						temp1 = (temp0 /  8 + 1) * 2;
					}
					lrc0 = checkLrc((LKSRAM + 3), temp1 + 12);//计算LRC校验值
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
			ret = HAL_UART_Transmit_DMA(&huart1, LKSRAM, sendSize);//DMA方式发送
			NVRAM0[SPREG_LINK_SEND_TCOUNTER] = 0;
			mLinkState = LINK_STATE_M_WAIT_SEND_DONE;
			break;
		}
		case LINK_STATE_M_WAIT_SEND_DONE:{//等待主机发送完毕
			if(LD(SPCOIL_LINK_SEND_DONE)){
				//切换RS485 DIR->RX
				//设置UART接收
				SSET(SPCOIL_LINK_RECE_BUSY);
				RRES(SPCOIL_LINK_RECE_DONE);
				ret = HAL_UART_Receive_DMA(&huart1, LKRRAM, receSize);
				mLinkState = LINK_STATE_M_WAIT_RECE_DONE;	
			}
			else if(NVRAM0[SPREG_LINK_SEND_TCOUNTER] > NVRAM0[SPREG_LINK_SEND_OVERTIME]){
				NVRAM0[SPREG_LINK_STATE] = LINK_RET_SEND_OVERTIME;//写故障码
				SSET(SPCOIL_LINK_SEND_ERR);//停止发送
				ret = HAL_UART_DMAStop(&huart1);//停止接收
				mLinkState = LINK_STATE_M_IDEL;
			}
			break;
		}
		case LINK_STATE_M_WAIT_RECE_DONE:{//等待主机接收完成
			if(LD(SPCOIL_LINK_RECE_DONE)){//接收完成
				//检查LCR校验
				lrc0 = checkLrc(LKRRAM, (receSize - 2));
				lrc1 = asciiToUint8(LKRRAM + receSize);//ASCII转无符号数 
				if(lrc0 == lrc1){//校验正确
					NVRAM0[SPREG_LINK_STATE] = LINK_RET_OK;
					RRES(SPCOIL_LINK_RECE_BUSY);	
					SSET(SPCOIL_LINK_RECE_DONE);	
					RRES(SPCOIL_LINK_RECE_ERR);
				}
				else{//校验错误
					NVRAM0[SPREG_LINK_STATE] = LINK_RET_LRC_ERR;
					RRES(SPCOIL_LINK_RECE_BUSY);	
					RRES(SPCOIL_LINK_RECE_DONE);	
					SSET(SPCOIL_LINK_RECE_ERR);
				}
			}
			else if(NVRAM0[SPREG_LINK_RECE_TCOUNTER] > NVRAM0[SPREG_LINK_RECE_OVERTIME]){//接收超时
				NVRAM0[SPREG_LINK_STATE] = LINK_RET_RECE_OVERTIME;//写故障码
				RRES(SPCOIL_LINK_RECE_BUSY);	
				RRES(SPCOIL_LINK_RECE_DONE);	
				SSET(SPCOIL_LINK_RECE_ERR);
			}
			break;
		}
		default:break;
	}
}
static uint8_t checkLrc(uint8_t *pdata, uint8_t len){//计算LRC校验值
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

static void uint8ToAscii(uint8_t *pchar, uint8_t* pAscii){//UINT8转ASCII
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
static void uint16ToAscii(uint16_t *pchar, uint8_t* pAscii){//UINT16转ASCII
	
	
}
static void uint32ToAscii(uint32_t *pchar, uint8_t* pAscii){//UINT32转ASCII
}
static uint8_t asciiToUint8(uint8_t *pdat){//ASCII转UINT8
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

static uint16_t asciiToUint16(uint8_t *pdat){//ASCII转为无符号16位数
	return 0;
}
static uint32_t asciiToUint32(uint8_t *pdat){//ASCII转为无符号32位数
	return 0;
}




