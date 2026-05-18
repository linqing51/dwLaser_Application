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
  EPROM_SPI_NSS_DESEL;
  wtmp = 0;
  wtmp |= 1 << 7;
  wtmp |= 1 << 1;
  epromReadStatusReg(&wtmp);
  printf("OLD STATUS REGISTER:%02X\n", wtmp);
  epromWriteStatusReg(&wtmp);
  epromReadStatusReg(&rtmp);
  printf("NEW STATUS REGISTER:%02X\n", rtmp);
}

HAL_StatusTypeDef epromReadStatusReg(uint8_t *status){//读状态寄存器
	HAL_StatusTypeDef ret;
	uint8_t cmd = RDSR;
	EPROM_SPI_NSS_SEL;
	__ASM volatile ("NOP");
	ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, &cmd, 1, 100);
	ret = HAL_SPI_Receive(&CONFIG_EPROM_BUS_HANDLE, status, 1, 100);
	EPROM_SPI_NSS_DESEL;
  __ASM volatile ("NOP");
	return ret;
}

HAL_StatusTypeDef epromWriteStatusReg(uint8_t *status){//写状态寄存器
  HAL_StatusTypeDef ret;
	uint8_t cmd = WRSR;
	EPROM_SPI_NSS_SEL;
	__ASM volatile ("NOP");
	ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, &cmd, 1, 100);
	ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, status, 1, 100);
	EPROM_SPI_NSS_DESEL;
  __ASM volatile ("NOP");
	return ret;
}

HAL_StatusTypeDef epromReadDeviceId(uint8_t *id){//读设备ID（4字节：厂商ID+续码+产品ID1+产品ID2）
	HAL_StatusTypeDef ret;
	uint8_t cmd = RDID;
	EPROM_SPI_NSS_SEL;
	__ASM volatile ("NOP");
	ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, &cmd, 1, 100);
	ret = HAL_SPI_Receive(&CONFIG_EPROM_BUS_HANDLE, id, 4, 100);
	EPROM_SPI_NSS_DESEL;
  __ASM volatile ("NOP");
	return ret;
}

HAL_StatusTypeDef epromWriteEnable(bool en){//写使能（所有写操作前必须调用）
	HAL_StatusTypeDef ret;
  uint8_t cmd;
	EPROM_SPI_NSS_SEL;
	__asm volatile ("nop");
	if(en){
		cmd = WREN;
	}
	else{
		cmd = WRDI;
	}
	ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, &cmd, 1, 100); // 发送写使能指令	
	__asm volatile ("nop");
  EPROM_SPI_NSS_DESEL;
  return ret;
}

HAL_StatusTypeDef epromReadByte(uint32_t addr, uint8_t *rdat){//读1字节 addr: 24位地址（MB85RS2MTA 只用低18位） rdat: 输出1字节
	HAL_StatusTypeDef ret;
	uint8_t tempBuf[4];
	EPROM_SPI_NSS_SEL;
	__ASM volatile ("NOP");
  if(CONFIG_EPROM_SIZE > 0xFFFF){
    tempBuf[0] = READ;
		tempBuf[1] = (addr >> 16) & 0xFF;
		tempBuf[2] = (addr >> 8)  & 0xFF;
		tempBuf[3] =  addr        & 0xFF;
    ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, tempBuf, 4, 100);
	}
	else{
    tempBuf[0] = READ;
    tempBuf[1] = (addr >> 8)  & 0xFF;
    tempBuf[2] =  addr        & 0xFF;
    ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, tempBuf, 3, 100);
	}
	ret = HAL_SPI_Receive(&CONFIG_EPROM_BUS_HANDLE, rdat, 1, 100);
	EPROM_SPI_NSS_DESEL;
  __ASM volatile ("NOP");
	return ret;
}

HAL_StatusTypeDef epromWriteByte(uint32_t addr, uint8_t *wdat){//写1字节addr: 24位地址wdat: 输入1字节
	HAL_StatusTypeDef ret;
	uint8_t tempBuf[4];
  epromWriteEnable(true); 
	EPROM_SPI_NSS_SEL;
	__ASM volatile ("NOP");
  if(CONFIG_EPROM_SIZE > 0xFFFF){
    tempBuf[0] = WRITE;
		tempBuf[1] = (addr >> 16) & 0xFF;
		tempBuf[2] = (addr >> 8)  & 0xFF;
		tempBuf[3] =  addr        & 0xFF;
    ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, tempBuf, 4, 100);
	}
	else{
    tempBuf[0] = WRITE;
    tempBuf[1] = (addr >> 8)  & 0xFF;
    tempBuf[2] =  addr        & 0xFF;
    ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, tempBuf, 3, 100);
	}
	ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, wdat, 1, 100);
	EPROM_SPI_NSS_DESEL;
  __ASM volatile ("NOP");
	return ret;
}

HAL_StatusTypeDef epromRead(uint32_t addr, uint8_t *pBuf, uint16_t len){//批量读addr: 起始地址pBuf: 输出缓冲区len: 字节数
	HAL_StatusTypeDef ret;
	uint8_t tempBuf[4];
  EPROM_SPI_NSS_SEL;
	__ASM volatile ("NOP");
  if(CONFIG_EPROM_SIZE > 0xFFFF){
    tempBuf[0] = READ;
		tempBuf[1] = (addr >> 16) & 0xFF;
		tempBuf[2] = (addr >> 8)  & 0xFF;
		tempBuf[3] =  addr        & 0xFF;
    ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, tempBuf, 4, 100);
	}
	else{
    tempBuf[0] = READ;
    tempBuf[1] = (addr >> 8)  & 0xFF;
    tempBuf[2] =  addr        & 0xFF;
    ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, tempBuf, 3, 100);
	}
	ret = HAL_SPI_Receive(&CONFIG_EPROM_BUS_HANDLE, pBuf, len, 100);	
	EPROM_SPI_NSS_DESEL;
  __ASM volatile ("NOP");
	return ret;
}

HAL_StatusTypeDef epromWrite(uint32_t addr, uint8_t *pBuf, uint16_t len){//批量写
	HAL_StatusTypeDef ret;
	uint8_t tempBuf[4];
  epromWriteEnable(true);
	EPROM_SPI_NSS_SEL;
  __ASM volatile ("NOP");
  if(CONFIG_EPROM_SIZE > 0xFFFF){
    tempBuf[0] = WRITE;
		tempBuf[1] = (addr >> 16) & 0xFF;
		tempBuf[2] = (addr >> 8)  & 0xFF;
		tempBuf[3] =  addr        & 0xFF;
    ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, tempBuf, 4, 100);
	}
	else{
    tempBuf[0] = WRITE;
		tempBuf[1] = (addr >> 8)  & 0xFF;
		tempBuf[2] =  addr        & 0xFF;
    ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, tempBuf, 3, 100);
	}
	ret = HAL_SPI_Transmit(&CONFIG_EPROM_BUS_HANDLE, (uint8_t*)pBuf, len, 100);
	EPROM_SPI_NSS_DESEL;
  __ASM volatile ("NOP");
	return ret;
}

HAL_StatusTypeDef epromReadHword(uint32_t addr, uint16_t *rdat){//16位读/写
	return epromRead(addr, (uint8_t*)rdat, 2);
}

HAL_StatusTypeDef epromWriteHword(uint32_t addr, uint16_t *wdat){
	return epromWrite(addr, (uint8_t*)wdat, 2);
}

HAL_StatusTypeDef epromReadDword(uint32_t addr, uint32_t *rdat){//32位读/写
	return epromRead(addr, (uint8_t*)rdat, 4);
}

HAL_StatusTypeDef epromWriteDword(uint32_t addr, uint32_t *wdat){
	return epromWrite(addr, (uint8_t*)wdat, 4);
}



#endif









