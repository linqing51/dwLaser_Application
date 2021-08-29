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
//static void uint8ToAscii(uint8_t *pchar, uint8_t* pAscii);//UINT8转ASCII
//static uint8_t  asciiToUint8(uint8_t *pdat);//ASCII转无符号数
static uint8_t  checkLrc(uint8_t *pdata, uint8_t len);//计算LRC校验值
static uint8_t  mLinkState, sLinkState;//状态机
/******************************************************************************/
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
/*
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
*/
/*
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
*/



