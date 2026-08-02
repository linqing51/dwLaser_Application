#include "sPlc.h"
#include "sPlcEprom.h"
/*****************************************************************************/
static uint8_t cmpByte(uint8_t *psrc, uint8_t *pdist, uint16_t len){
	uint16_t i;
	for(i = 0;i < len;i ++){
		if(*(psrc + i) != *(pdist + i)){
			return false;
		}
	}
	return true;
}

uint8_t sPlcEpromTest(void){//EPROM 读写自测试
	uint32_t i, crcRead = 0, crcWrite = 0;	
	uint32_t bk, remain;//写入地址
	uint8_t rblock[64], wblock[64];
	uint32_t tempRead, tempWrite;
	uint8_t res = 0;  
  
  //字节填充写入0x55
  printf("%s,%d,%s:byte(8bit) start write 0x55\r\n", __FILE__, __LINE__, __func__);
  for(i = 0;i < CONFIG_EPROM_SIZE;i ++){
    tempWrite = 0x55;
    tempRead = 0;
    epromWriteByte(i, (uint8_t*)&tempWrite);
  }
  for(i = 0;i < CONFIG_EPROM_SIZE;i ++){
    epromReadByte(i, (uint8_t*)&tempRead);
    if(tempRead != 0x55){
      printf("%s,%d,%s:byte(8bit) write 0x55 fail at:0x08%X!\r\n", __FILE__, __LINE__, __func__, i);
      break;
    }
  }
  //字节填充写入0xAA
  printf("%s,%d,%s:byte(8bit) start write 0xAA\r\n", __FILE__, __LINE__, __func__);
  for(i = 0;i < CONFIG_EPROM_SIZE;i ++){
    tempWrite = 0xAA;
    epromWriteByte(i, (uint8_t*)&tempWrite);
  }
  for(i = 0;i < CONFIG_EPROM_SIZE;i ++){
    epromReadByte(i, (uint8_t*)&tempRead);
    if(tempRead != 0xAA){
      printf("%s,%d,%s:byte(8bit) write 0xAA fail at:0x08%X!\r\n", __FILE__, __LINE__, __func__, i);
      break;
    }
  }  
	//随机字节顺序写入
	__HAL_CRC_DR_RESET(&hcrc);//清空之前CRC32结果
	for(i = 0;i <CONFIG_EPROM_SIZE ;i += 4){
		tempWrite = HAL_RNG_GetRandomNumber(&hrng);	
		epromWriteByte((i + 0), ((uint8_t*)&tempWrite + 0));
		epromWriteByte((i + 1), ((uint8_t*)&tempWrite + 1));
		epromWriteByte((i + 2), ((uint8_t*)&tempWrite + 2));
		epromWriteByte((i + 3), ((uint8_t*)&tempWrite + 3));
		crcWrite = HAL_CRC_Accumulate(&hcrc, &tempWrite, 1);
	}
	__HAL_CRC_DR_RESET(&hcrc);//清空之前CRC32结果
	for(i = 0;i <CONFIG_EPROM_SIZE;i += 4){
		epromReadByte((i + 0), ((uint8_t*)&tempRead + 0));
		epromReadByte((i + 1), ((uint8_t*)&tempRead + 1));
		epromReadByte((i + 2), ((uint8_t*)&tempRead + 2));
		epromReadByte((i + 3), ((uint8_t*)&tempRead + 3));
		crcRead = HAL_CRC_Accumulate(&hcrc, &tempRead, 1);
	}
	if(crcRead == crcWrite){
		printf("%s,%d,%s:byte(8bit) sequential write pass!\r\n", __FILE__, __LINE__, __func__);
	}
	else{
		printf("%s,%d,%s:byte(8bit) sequential wirte fail!\r\n", __FILE__, __LINE__, __func__);
		res = false;
	}
  //字顺序写入
	__HAL_CRC_DR_RESET(&hcrc);//清空之前CRC32结果
	for(i = 0;i <CONFIG_EPROM_SIZE;i += 4){
		tempWrite = HAL_RNG_GetRandomNumber(&hrng);
		epromWriteHword((i + 0), ((uint16_t*)&tempWrite + 0));
		epromWriteHword((i + 2), ((uint16_t*)&tempWrite + 1));
		crcWrite = HAL_CRC_Accumulate(&hcrc, &tempWrite, 1);
	}
	__HAL_CRC_DR_RESET(&hcrc);//清空之前CRC32结果
	for(i = 0;i <CONFIG_EPROM_SIZE;i += 4){
		epromReadHword((i + 0), ((uint16_t*)&tempRead + 0));
		epromReadHword((i + 2), ((uint16_t*)&tempRead + 1));
		crcRead = HAL_CRC_Accumulate(&hcrc, (uint32_t*)&tempRead, 1);
	}
	if(crcRead == crcWrite){
		printf("%s,%d,%s:hword(16bit) sequential write pass!\r\n", __FILE__, __LINE__, __func__);
	}
	else{
		printf("%s,%d,%s:howrd(16bit) sequential wirte fail!\r\n", __FILE__, __LINE__, __func__);
		res = false;
	}
  
	//双字顺序写入
	__HAL_CRC_DR_RESET(&hcrc);//清空之前CRC32结果
	i =0;
  for(i = 0;i < CONFIG_EPROM_SIZE;i += 4){
		tempWrite = HAL_RNG_GetRandomNumber(&hrng);
		epromWriteDword(i, &tempWrite);
		crcWrite = HAL_CRC_Accumulate(&hcrc, &tempWrite, 1);
	}
	__HAL_CRC_DR_RESET(&hcrc);//清空之前CRC32结果
	for(i = 0;i < CONFIG_EPROM_SIZE;i += 4){
		epromReadDword(i, &tempRead);
		crcRead = HAL_CRC_Accumulate(&hcrc, &tempRead, 1);
	}
	if(crcRead == crcWrite){
		printf("%s,%d,%s:dword(32bit) sequential write pass!\r\n", __FILE__, __LINE__, __func__);
	}
	else{
		printf("%s,%d,%s:dword(32bit) sequential wirte fail!\r\n", __FILE__, __LINE__, __func__);
		res = false;
	}
	//块顺序写入
	bk = CONFIG_EPROM_SIZE / sizeof(wblock);
	remain =  CONFIG_EPROM_SIZE % sizeof(wblock);
	for(i = 0; i < bk;i ++){
		memset(wblock, (i & 0xFF), sizeof(wblock));
		memset(rblock, 0x00, sizeof(rblock));
		epromWrite((bk + i * sizeof(wblock)), wblock, sizeof(wblock));
		epromRead((bk + i * sizeof(wblock)), rblock, sizeof(wblock));
		if(cmpByte(rblock, rblock, sizeof(rblock)) == false){
			printf("%s,%d,%s:block sequential Write fail!\r\n", __FILE__, __LINE__, __func__);
			res = false;
		}
	}
	memset(wblock, (rand() % 0xFF), sizeof(wblock));
	memset(rblock, 0x00, sizeof(rblock));
	epromWrite((CONFIG_EPROM_SIZE - remain), wblock, remain);
	epromRead((CONFIG_EPROM_SIZE - remain), rblock, remain);
	if(cmpByte(rblock, rblock, sizeof(rblock)) == false){
		printf("%s,%d,%s:block sequential Write fail!\r\n", __FILE__, __LINE__, __func__);
		res = false;
	}
	printf("%s,%d,%s:block sequential Write pass!\r\n", __FILE__, __LINE__, __func__);
	//随机写入
	for(i=0;i<10000;i++){
    if(CONFIG_EPROM_SIZE != 0){// 非法值保护    
			HAL_RNG_GenerateRandomNumber(&hrng, &bk);
		}
		bk =  bk % (CONFIG_EPROM_SIZE + 1);//生成 0 ~ A 的随机数（包含两端
		tempWrite = HAL_RNG_GetRandomNumber(&hrng);//获取随机数据
		epromWrite(bk, ((uint8_t*)&tempWrite), 4);//写入
		epromRead(bk, ((uint8_t*)&tempRead), 4);//读取
		if(tempWrite != tempRead){
			printf("%s,%d,%s:random write fail!\r\n", __FILE__, __LINE__, __func__);
			res = false;
		}
	}
	printf("%s,%d,%s:random write pass!\r\n", __FILE__, __LINE__, __func__);
	return res;
}
