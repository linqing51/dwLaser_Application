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

void listEpromTable(void){//输出EPROM分布表
	int32_t tmp;
	uint8_t eprom_id[4];
	epromReadDeviceId(eprom_id);
	printf("************************EPROM MAP****************************\n\n");
	printf("EPROM ID:%02X%02X%02X%02X\n", eprom_id[0], eprom_id[1], eprom_id[2], eprom_id[3]);
	printf("MR EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_MR_START, (uint32_t)CONFIG_EPROM_MR_END, (uint16_t)CONFIG_MRRAM_SIZE);
	printf("DM EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_DM_START, (uint32_t)CONFIG_EPROM_DM_END, (uint16_t)CONFIG_DMRAM_SIZE);
	printf("FD EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_FD_START, (uint32_t)CONFIG_EPROM_FD_END, (uint16_t)CONFIG_FDRAM_SIZE);
	
	printf("MEDICAL CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_MEDICAL_CRC, (uint32_t)(CONFIG_EPROM_MEDICAL_CRC + 3), 4);
	printf("MR CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_MR_CRC, (uint32_t)(CONFIG_EPROM_MR_CRC + 3), 4);
	printf("DM CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_DM_CRC, (uint32_t)(CONFIG_EPROM_DM_CRC + 3), 4);
	printf("FD CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_FD_CRC, (uint32_t)(CONFIG_EPROM_FD_CRC + 3), 4);	
	printf("MCU FW CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_MCU_FW_CRC, (uint32_t)(CONFIG_EPROM_MCU_FW_CRC + 3), 4);
	printf("LCD FW CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_LCD_FW_CRC, (uint32_t)(CONFIG_EPROM_LCD_FW_CRC + 3), 4);
	
	printf("CONFIG EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_CONFIG_START, (uint32_t)CONFIG_EPROM_CONFIG_END, (uint16_t)(CONFIG_EPROM_CONFIG_END - CONFIG_EPROM_CONFIG_START + 1));
	printf("LOGINFO EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_LOGINFO_START,(uint32_t)CONFIG_EPROM_LOGINFO_END, (uint16_t)(CONFIG_EPROM_LOGINFO_END - CONFIG_EPROM_LOGINFO_START + 1));
		
	printf("deviceConfig size:%d byte\n", sizeof(deviceConfig));
	printf("deviceLogInfo size:%d byte\n", sizeof(deviceLogInfo));
	
	tmp = CONFIG_EPROM_CONFIG_END - CONFIG_EPROM_CONFIG_START + 1;
	if(sizeof(deviceConfig) > tmp){
		printf("WARNING:struce deviceConfig size overflow!!!\n");
	}
	tmp = CONFIG_EPROM_LOGINFO_END - CONFIG_EPROM_LOGINFO_START + 1;
	if(sizeof(deviceLogInfo) > tmp){
		printf("WARNING:struce devideInfo size overflow!!!\n");
	}
}

void clearEprom(clarmEpromCmd_t cmd){//清除EPROM内容
	uint8_t var = 0;
	uint32_t i;	
	switch(cmd){
		case CLEAR_EPROM_ALL:{
			for(i = 0;i < CONFIG_EPROM_SIZE;i ++){
				epromWriteByte(i, &var);
			}
			break;
		}
		case CLEAR_EPROM_NVRAM:{
			for(i = CONFIG_EPROM_MR_START; i <= CONFIG_EPROM_MR_END;i ++){
				epromWriteByte(i, &var);
			}
			for(i = CONFIG_EPROM_DM_START; i <= CONFIG_EPROM_DM_END;i ++){
				epromWriteByte(i, &var);
			}
			
			for(i = CONFIG_EPROM_MR_CRC; i <= (CONFIG_EPROM_MR_CRC + 3);i ++){
				epromWriteByte(i, &var);
			}
			
			for(i = CONFIG_EPROM_DM_CRC; i <= (CONFIG_EPROM_DM_CRC + 3);i ++){
				epromWriteByte(i, &var);
			}
			break;
		}
		case CLEAR_EPROM_FDRAM:{
			for(i = CONFIG_EPROM_FD_START; i <= CONFIG_EPROM_FD_END;i ++){
				epromWriteByte(i, &var);
			}			
			for(i = CONFIG_EPROM_FD_CRC; i <= (CONFIG_EPROM_FD_CRC + 3);i ++){
				epromWriteByte(i, &var);
			}
			break;
		}
		case CLEAR_EPROM_MCU_FIRMWARE_CRC:{
			for(i = CONFIG_EPROM_MCU_FW_CRC;i <= (CONFIG_EPROM_MCU_FW_CRC + 3);i ++){
				epromWriteByte(i, &var);
			}
			break;
		}
		case CLEAR_EPROM_LCD_FIRMWARE_CRC:{
			for(i = CONFIG_EPROM_LCD_FW_CRC;i <= (CONFIG_EPROM_LCD_FW_CRC + 3);i ++){
				epromWriteByte(i, &var);
			}
			break;
		}
		case CLEAR_EPROM_DEVICE_CONFIG:{
			for(i = CONFIG_EPROM_CONFIG_START;i <= CONFIG_EPROM_CONFIG_END;i ++){
				epromWriteByte(i, &var);
			}
			break;
		}
		case CLEAR_EPROM_LOG_INFO:{
			for(i = CONFIG_EPROM_LOGINFO_START;i <= CONFIG_EPROM_LOGINFO_END;i ++){
				epromWriteByte(i, &var);
			}
			break;
		}
		default:break;
	}
}

uint8_t checkBlank(uint32_t adr, uint32_t size){//MCU Flash 查空
	uint8_t val;
	uint32_t i;
	for(i = 0;i < size;i ++){
		val = *(__IO uint8_t*)(adr + i);
		if(val != 0xFF){
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






