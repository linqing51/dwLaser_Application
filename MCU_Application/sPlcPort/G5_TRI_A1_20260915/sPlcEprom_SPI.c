/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "sPlc.h"
#include "sPlcEprom.h"
/*****************************************************************************/
#if defined(CONFIG_EPROM_SPI)
typedef enum {
	WREN    = 0x06,   // 写使能
	WRDI    = 0x04,   // 写禁止
	RDSR    = 0x05,   // 读状态寄存器
	WRSR    = 0x01,   // 写状态寄存器
	READ    = 0x03,   // 读数据
	WRITE   = 0x02,   // 写数据
	FSTRD   = 0x0B,   // 快速读
	RDID    = 0x9F,   // 读设备ID
	SLEEP   = 0xB9    // 进入睡眠
}EPROM_CMD_T;

void epromInit(void){
  uint8_t wtmp, rtmp;
	uint8_t eprom_id[4];
  EPROM_SPI_NSS_DESEL;	
	epromReadDeviceId(eprom_id);
	printf("EPROM ID:%02X%02X%02X%02X\n", eprom_id[0], eprom_id[1], eprom_id[2], eprom_id[3]);
  wtmp = 0;
  wtmp |= 1 << 7;
  wtmp |= 1 << 1;
  epromReadStatusReg(&rtmp);
  printf("OLD STATUS REGISTER:%02X\n", rtmp);
  epromWriteEnable(true);
  epromWriteStatusReg(&wtmp);
  epromReadStatusReg(&rtmp);
  printf("NEW STATUS REGISTER:%02X\n", rtmp);
  EPROM_SPI_NSS_DESEL;
}

__forceinline HAL_StatusTypeDef epromReadStatusReg(uint8_t *status){//读状态寄存器
	HAL_StatusTypeDef ret;
	uint8_t cmd = RDSR;
	EPROM_SPI_NSS_SEL;
	__ASM volatile ("NOP");
	ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, &cmd, 1, CONFIG_EPROM_TIMEOUT);
	ret = HAL_SPI_Receive(&CONFIG_EPROM_BUS_HANDLE, status, 1, CONFIG_EPROM_TIMEOUT);
	__ASM volatile ("NOP");
  EPROM_SPI_NSS_DESEL;
  __ASM volatile ("NOP");
	return ret;
}

__forceinline HAL_StatusTypeDef epromWriteStatusReg(uint8_t *status){//写状态寄存器
  HAL_StatusTypeDef ret;
	uint8_t cmd = WRSR;
	EPROM_SPI_NSS_SEL;
	__ASM volatile ("NOP");
	ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, &cmd, 1, CONFIG_EPROM_TIMEOUT);
	ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, status, 1, CONFIG_EPROM_TIMEOUT);
	__ASM volatile ("NOP");
  EPROM_SPI_NSS_DESEL;
  __ASM volatile ("NOP");
	return ret;
}

__forceinline HAL_StatusTypeDef epromReadDeviceId(uint8_t *id){//读设备ID（4字节：厂商ID+续码+产品ID1+产品ID2）
	HAL_StatusTypeDef ret;
	uint8_t cmd = RDID;
	EPROM_SPI_NSS_SEL;
	__ASM volatile ("NOP");
	ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, &cmd, 1, CONFIG_EPROM_TIMEOUT);
	ret = HAL_SPI_Receive(&CONFIG_EPROM_BUS_HANDLE, id, 4, CONFIG_EPROM_TIMEOUT);
	__ASM volatile ("NOP");
  EPROM_SPI_NSS_DESEL;
  __ASM volatile ("NOP");
	return ret;
}

__forceinline HAL_StatusTypeDef epromWriteEnable(bool en){//写使能（所有写操作前必须调用）
	HAL_StatusTypeDef ret;
  uint8_t cmd;
	EPROM_SPI_NSS_SEL;
	__ASM volatile ("NOP");
	if(en){
		cmd = WREN;
	}
	else{
		cmd = WRDI;
	}
	ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, &cmd, 1, CONFIG_EPROM_TIMEOUT); // 发送写使能指令	
	__ASM volatile ("NOP");
  EPROM_SPI_NSS_DESEL;
  __ASM volatile ("NOP");
  return ret;
}

__forceinline HAL_StatusTypeDef epromReadByte(uint32_t addr, uint8_t *rdat){//读1字节 addr: 24位地址（MB85RS2MTA 只用低18位） rdat: 输出1字节
	HAL_StatusTypeDef ret;
	uint8_t tempBuf[4], rxBuf[4];//命令+地址一次收发(减少HAL调用)
	uint16_t txLen;
	EPROM_SPI_NSS_SEL;
	__ASM volatile ("NOP");
  if(CONFIG_EPROM_SIZE > 0x10000){
    tempBuf[0] = READ;
		tempBuf[1] = (addr >> 16) & 0xFF;
		tempBuf[2] = (addr >> 8)  & 0xFF;
		tempBuf[3] =  addr        & 0xFF;
		txLen = 4;
	}
	else{
    tempBuf[0] = READ;
    tempBuf[1] = (addr >> 8)  & 0xFF;
    tempBuf[2] =  addr        & 0xFF;
    tempBuf[3] = 0xFF;//占位
		txLen = 3;
	}
	//注意: MB85RS FRAM读时序为"命令+地址移入完成后输出数据":
	//512TPN(16bit地址,txLen=3)数据自第4传输字节起, 2MTA(24bit地址,txLen=4)数据自第5传输字节起,
	//故统一从rxBuf[txLen]取数
	ret = HAL_SPI_TransmitReceive(&CONFIG_EPROM_BUS_HANDLE, tempBuf, rxBuf, (uint16_t)(txLen + 1), CONFIG_EPROM_TIMEOUT);
	*rdat = rxBuf[txLen];
	__ASM volatile ("NOP");
  EPROM_SPI_NSS_DESEL;
  __ASM volatile ("NOP");
	return ret;
}

__forceinline HAL_StatusTypeDef epromWriteByte(uint32_t addr, uint8_t *wdat){//写1字节addr: 24位地址wdat: 输入1字节
	HAL_StatusTypeDef ret;
	uint8_t tempBuf[5];//命令+地址+数据一次发送(减少HAL调用)
  epromWriteEnable(true); 
	EPROM_SPI_NSS_SEL;
	__ASM volatile ("NOP");
  if(CONFIG_EPROM_SIZE > 0x10000){
    tempBuf[0] = WRITE;
		tempBuf[1] = (addr >> 16) & 0xFF;
		tempBuf[2] = (addr >> 8)  & 0xFF;
		tempBuf[3] =  addr        & 0xFF;
		tempBuf[4] = *wdat;
    ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, tempBuf, 5, CONFIG_EPROM_TIMEOUT);
	}
	else{
    tempBuf[0] = WRITE;
    tempBuf[1] = (addr >> 8)  & 0xFF;
    tempBuf[2] =  addr        & 0xFF;
		tempBuf[3] = *wdat;
    ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, tempBuf, 4, CONFIG_EPROM_TIMEOUT);
	}
	__ASM volatile ("NOP");
  EPROM_SPI_NSS_DESEL;
  __ASM volatile ("NOP");
	return ret;
}

__forceinline HAL_StatusTypeDef epromRead(uint32_t addr, uint8_t *pBuf, uint16_t len){//批量读addr: 起始地址pBuf: 输出缓冲区len: 字节数
	HAL_StatusTypeDef ret;
	uint8_t tempBuf[4], rxBuf[8];//小批量(≤4B)命令+地址+数据合并收发缓冲
	uint16_t txLen;
  EPROM_SPI_NSS_SEL;
	__ASM volatile ("NOP");
  if(CONFIG_EPROM_SIZE > 0x10000){
    tempBuf[0] = READ;
		tempBuf[1] = (addr >> 16) & 0xFF;
		tempBuf[2] = (addr >> 8)  & 0xFF;
		tempBuf[3] =  addr        & 0xFF;
		txLen = 4;
	}
	else{
    tempBuf[0] = READ;
    tempBuf[1] = (addr >> 8)  & 0xFF;
    tempBuf[2] =  addr        & 0xFF;
		txLen = 3;
	}
	if(len <= 4){//小批量: 命令+地址与数据一次TransmitReceive完成
		//注意: MB85RS FRAM读时序为"命令+地址移入完成后输出数据":
		//512TPN(16bit地址,txLen=3)数据自第4传输字节起, 2MTA(24bit地址,txLen=4)数据自第5传输字节起,
		//故统一从rxBuf[txLen]取数
		memset(&tempBuf[txLen], 0xFF, len);
		ret = HAL_SPI_TransmitReceive(&CONFIG_EPROM_BUS_HANDLE, tempBuf, rxBuf, (uint16_t)(txLen + len), CONFIG_EPROM_TIMEOUT);
		memcpy(pBuf, &rxBuf[txLen], len);
	}
	else{//大批量: 命令/地址与数据分两次(传输大头在数据,合并需大缓冲无收益)
		ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, tempBuf, txLen, CONFIG_EPROM_TIMEOUT);
		ret = HAL_SPI_Receive(&CONFIG_EPROM_BUS_HANDLE, pBuf, len, 100);
	}
	__ASM volatile ("NOP");
  EPROM_SPI_NSS_DESEL;
  __ASM volatile ("NOP");
	return ret;
}

__forceinline HAL_StatusTypeDef epromWrite(uint32_t addr, uint8_t *pBuf, uint16_t len){//批量写
	HAL_StatusTypeDef ret;
	uint8_t tempBuf[8];//小批量(≤4B)命令+地址+数据合并缓冲
	uint16_t txLen;
  epromWriteEnable(true);
	EPROM_SPI_NSS_SEL;
  __ASM volatile ("NOP");
  if(CONFIG_EPROM_SIZE > 0x10000){
    tempBuf[0] = WRITE;
		tempBuf[1] = (addr >> 16) & 0xFF;
		tempBuf[2] = (addr >> 8)  & 0xFF;
		tempBuf[3] =  addr        & 0xFF;
		txLen = 4;
	}
	else{
    tempBuf[0] = WRITE;
    tempBuf[1] = (addr >> 8)  & 0xFF;
    tempBuf[2] =  addr        & 0xFF;
		txLen = 3;
	}
	if(len <= 4){//小批量: 命令+地址+数据一次Transmit完成
		memcpy(&tempBuf[txLen], pBuf, len);
		ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, tempBuf, (uint16_t)(txLen + len), CONFIG_EPROM_TIMEOUT);
	}
	else{//大批量: 命令/地址与数据分两次(传输大头在数据,合并需大缓冲无收益)
		ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, tempBuf, txLen, CONFIG_EPROM_TIMEOUT);
		ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, (uint8_t*)pBuf, len, CONFIG_EPROM_TIMEOUT);
	}
	__ASM volatile ("NOP");
  EPROM_SPI_NSS_DESEL;
  __ASM volatile ("NOP");
	return ret;
}

__forceinline HAL_StatusTypeDef epromReadHword(uint32_t addr, uint16_t *rdat){//16位读/写
	return epromRead(addr, (uint8_t*)rdat, 2);
}

__forceinline HAL_StatusTypeDef epromWriteHword(uint32_t addr, uint16_t *wdat){
	return epromWrite(addr, (uint8_t*)wdat, 2);
}

__forceinline HAL_StatusTypeDef epromReadDword(uint32_t addr, uint32_t *rdat){//32位读/写
	return epromRead(addr, (uint8_t*)rdat, 4);
}

__forceinline HAL_StatusTypeDef epromWriteDword(uint32_t addr, uint32_t *wdat){
	return epromWrite(addr, (uint8_t*)wdat, 4);
}



#endif









