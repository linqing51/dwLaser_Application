//适用于FRAM不适用于EEPROM
#include "sPlc.h"
/*****************************************************************************/
extern I2C_HandleTypeDef hi2c1;
extern CRC_HandleTypeDef hcrc;
extern RNG_HandleTypeDef hrng;
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
HAL_StatusTypeDef epromReadByte(uint16_t ReadAddr, uint8_t *rdat){//在指定地址读出8位数据
//ReadAddr:开始读数的地址  
//返回值  :数据				  
	HAL_StatusTypeDef ret;
	if(ReadAddr > (CONFIG_EPROM_SIZE - 1)){//写地址超过容量
		ret = HAL_ERROR;
		return ret;
	}	
	ret = HAL_I2C_Mem_Read(&hi2c1,
	                       CONFIG_EPROM_READ_ADDR,
	                       ReadAddr,
	                       I2C_MEMADD_SIZE_16BIT,
	                       (uint8_t*)(rdat),
	                       1,
	                       CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
		ret = HAL_I2C_DeInit(&hi2c1);//释放IO口为GPIO，复位句柄状态标志
		ret = HAL_I2C_Init(&hi2c1);//这句重新初始化I2C控制器
	}
	return ret;
}
HAL_StatusTypeDef epromReadHword(uint16_t ReadAddr, uint16_t *rdat){//在指定地址开始读出16位数
//该函数用于读出16bit或者32bit的数据.
//ReadAddr   :开始读出的地址 
//返回值     :数据  	
	HAL_StatusTypeDef ret;
	if((ReadAddr + 1) > (CONFIG_EPROM_SIZE - 1)){//写地址超过容量
		ret = HAL_ERROR;
		return ret;
	}	
	ret = HAL_I2C_Mem_Read(&hi2c1, 
						   CONFIG_EPROM_READ_ADDR,
	                       ReadAddr,
	                       I2C_MEMADD_SIZE_16BIT,
	                       (uint8_t*)(rdat),
	                       2,
	                       CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
		ret = HAL_I2C_DeInit(&hi2c1);        //释放IO口为GPIO，复位句柄状态标志
		ret = HAL_I2C_Init(&hi2c1);          //这句重新初始化I2C控制器
	}
	return ret;
}
HAL_StatusTypeDef epromReadDword(uint16_t ReadAddr, uint32_t *rdat){////在指定地址开始读出32位数
//该函数用于读出32bit的数据.
//ReadAddr   :开始读出的地址 
//返回值     :数据  	
	HAL_StatusTypeDef ret;	
	if((ReadAddr + 3) > (CONFIG_EPROM_SIZE - 1)){//写地址超过容量
		ret = HAL_ERROR;
		return ret;
	}	
	ret = HAL_I2C_Mem_Read(&hi2c1, 
	                       CONFIG_EPROM_READ_ADDR,
	                       ReadAddr,
	                       I2C_MEMADD_SIZE_16BIT,
	                       (uint8_t*)(rdat),
	                       4,
	                       CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
		ret = HAL_I2C_DeInit(&hi2c1);        //释放IO口为GPIO，复位句柄状态标志
		ret = HAL_I2C_Init(&hi2c1);          //这句重新初始化I2C控制器
	}
	return ret;
}
HAL_StatusTypeDef epromWriteByte(uint16_t WriteAddr, uint8_t *wdat){//在指定地址写入8位数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据
	HAL_StatusTypeDef ret;
	if(WriteAddr > (CONFIG_EPROM_SIZE - 1)){//写地址超过容量
		ret = HAL_ERROR;
		return ret;
	}
	ret = HAL_I2C_Mem_Write(&hi2c1, 
	                        CONFIG_EPROM_WRITE_ADDR,
	                        WriteAddr, 
	                        I2C_MEMADD_SIZE_16BIT, 
	                        (uint8_t*)(wdat), 
	                        1, 
	                        CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
		ret = HAL_I2C_DeInit(&hi2c1);//释放IO口为GPIO，复位句柄状态标志
		ret = HAL_I2C_Init(&hi2c1);//这句重新初始化I2C控制器
	}
	return ret;
}
HAL_StatusTypeDef epromWriteHword(uint16_t WriteAddr, uint16_t *wdat){//在的指定地址开始写入16位数
//该函数用于写入16bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址
	HAL_StatusTypeDef ret;
	if((WriteAddr + 1) > (CONFIG_EPROM_SIZE - 1)){//写地址超过容量
		ret = HAL_ERROR;
		return ret;
	}
	ret = HAL_I2C_Mem_Write(&hi2c1, 
	                        CONFIG_EPROM_WRITE_ADDR, 
	                        WriteAddr, 
	                        I2C_MEMADD_SIZE_16BIT, 
	                        (uint8_t*)(wdat), 
	                        2, 
	                        CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
		ret = HAL_I2C_DeInit(&hi2c1);//释放IO口为GPIO，复位句柄状态标志
		ret = HAL_I2C_Init(&hi2c1);//这句重新初始化I2C控制器	
	}
	return ret;
}
HAL_StatusTypeDef epromWriteDword(uint16_t WriteAddr, uint32_t *wdat){//在的指定地址开始写入32位数
//该函数用于写入32bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址
	HAL_StatusTypeDef ret;
	if((WriteAddr + 3) >= (CONFIG_EPROM_SIZE - 1)){//写地址超过容量
		ret = HAL_ERROR;
		return ret;
	}
	ret = HAL_I2C_Mem_Write(&hi2c1, 
	                        CONFIG_EPROM_WRITE_ADDR, 
	                        WriteAddr, 
	                        I2C_MEMADD_SIZE_16BIT, 
	                        (uint8_t*)(wdat), 
	                        4, 
	                        CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
		ret = HAL_I2C_DeInit(&hi2c1);        //释放IO口为GPIO，复位句柄状态标志
		ret = HAL_I2C_Init(&hi2c1);          //这句重新初始化I2C控制器
	}
	return ret;
}   
HAL_StatusTypeDef epromRead(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead){//在的指定地址开始读出指定个数的数据
//ReadAddr :开始读出的地址 对24c02为0~255
//pBuffer  :数据数组首地址
//NumToRead:要读出数据的个数
	HAL_StatusTypeDef ret;
	__IO uint16_t rAddr, rBlock, rByte, doBlock;
	uint8_t* rBuffer;
	if((ReadAddr + NumToRead) > CONFIG_EPROM_SIZE){//读地址超过限制
		ret = HAL_ERROR;
		return ret;
	}
	rBlock = NumToRead / CONFIG_EPROM_PAGE_SIZE;
	rByte = NumToRead % CONFIG_EPROM_PAGE_SIZE;
	rAddr = ReadAddr;
	rBuffer = pBuffer;
	for(doBlock = 0;doBlock < rBlock;doBlock ++){
		ret = HAL_I2C_Mem_Read(&hi2c1, CONFIG_EPROM_READ_ADDR, rAddr, I2C_MEMADD_SIZE_16BIT, rBuffer, CONFIG_EPROM_PAGE_SIZE, CONFIG_EPROM_TIMEOUT);
		if(ret != HAL_OK){
			ret = HAL_I2C_DeInit(&hi2c1);//释放IO口为GPIO，复位句柄状态标志
			ret = HAL_I2C_Init(&hi2c1);//这句重新初始化I2C控制器
		}
		rAddr += CONFIG_EPROM_PAGE_SIZE;
		rBuffer += CONFIG_EPROM_PAGE_SIZE;
	}
	if(rByte != 0x0){
		ret = HAL_I2C_Mem_Read(&hi2c1, CONFIG_EPROM_READ_ADDR, rAddr, I2C_MEMADD_SIZE_16BIT, rBuffer, rByte ,CONFIG_EPROM_TIMEOUT);
		if(ret != HAL_OK){
			ret = HAL_I2C_DeInit(&hi2c1);        //释放IO口为GPIO，复位句柄状态标志
			ret = HAL_I2C_Init(&hi2c1);          //这句重新初始化I2C控制器
		}
	}
	return ret;	
}  
HAL_StatusTypeDef epromWrite(uint16_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite){//在的指定地址开始写入指定个数的数据
//WriteAddr :开始写入的地址 对24c02为0~255
//pBuffer   :数据数组首地址
//NumToWrite:要写入数据的个数
	HAL_StatusTypeDef ret;
	uint16_t wAddr, wBlock, wByte, doBlock;
	uint8_t* wBuffer;
	if((WriteAddr + NumToWrite) > CONFIG_EPROM_SIZE){//读地址超过限制
		ret = HAL_ERROR;
		return ret;
	}
	wBlock = NumToWrite / CONFIG_EPROM_PAGE_SIZE;
	wByte = NumToWrite % CONFIG_EPROM_PAGE_SIZE;
	wAddr = WriteAddr;
	wBuffer = pBuffer;
	for(doBlock = 0;doBlock < wBlock;doBlock ++){
		ret = HAL_I2C_Mem_Write(&hi2c1, CONFIG_EPROM_WRITE_ADDR, wAddr, I2C_MEMADD_SIZE_16BIT, wBuffer, CONFIG_EPROM_PAGE_SIZE, CONFIG_EPROM_TIMEOUT);
		if(ret != HAL_OK){
			ret = HAL_I2C_DeInit(&hi2c1);        //释放IO口为GPIO，复位句柄状态标志
			ret = HAL_I2C_Init(&hi2c1);          //这句重新初始化I2C控制器
		}
		wAddr += CONFIG_EPROM_PAGE_SIZE;
		wBuffer += CONFIG_EPROM_PAGE_SIZE;
#if CONFIG_EPROM_WRITE_DELAY > 0
		HAL_Delay(CONFIG_EPROM_WRITE_DELAY);
#endif
	}
	if(wByte != 0x0){		
		ret = HAL_I2C_Mem_Write(&hi2c1, CONFIG_EPROM_WRITE_ADDR, wAddr, I2C_MEMADD_SIZE_16BIT, wBuffer, wByte, CONFIG_EPROM_TIMEOUT);
		if(ret != HAL_OK){
			ret = HAL_I2C_DeInit(&hi2c1);        //释放IO口为GPIO，复位句柄状态标志
			ret = HAL_I2C_Init(&hi2c1);          //这句重新初始化I2C控制器
		}
	}
#if CONFIG_EPROM_WRITE_DELAY > 0
	HAL_Delay(CONFIG_EPROM_WRITE_DELAY);
#endif
	return ret;
}
/*****************************************************************************/
void listEpromTable(void){//输出EPROM分布表
	printf("MR EPROM:0x%04X---0x%04X(size:%d)\n", (uint32_t)CONFIG_EPROM_MR_START, (uint32_t)CONFIG_EPROM_MR_END, (uint16_t)CONFIG_MRRAM_SIZE);
	printf("DM EPROM:0x%04X---0x%04X(size:%d)\n", (uint32_t)CONFIG_EPROM_DM_START, (uint32_t)CONFIG_EPROM_DM_END, (uint16_t)CONFIG_DMRAM_SIZE);
	printf("FD EPROM:0x%04X---0x%04X(size:%d)\n", (uint32_t)CONFIG_EPROM_FD_START, (uint32_t)CONFIG_EPROM_FD_END, (uint16_t)CONFIG_FDRAM_SIZE);
	
	printf("MR CRC EPROM:0x%04X---0x%04X\n", (uint32_t)CONFIG_EPROM_MR_CRC, (uint32_t)(CONFIG_EPROM_MR_CRC + 3));
	printf("DM CRC EPROM:0x%04X---0x%04X\n", (uint32_t)CONFIG_EPROM_DM_CRC, (uint32_t)(CONFIG_EPROM_DM_CRC + 3));
	printf("FD CRC EPROM:0x%04X---0x%04X,(unuse)\n", (uint32_t)CONFIG_EPROM_FD_CRC, (uint32_t)(CONFIG_EPROM_FD_CRC + 3));	
	printf("MCU CRC EPROM:0x%04X---0x%04X\n", (uint32_t)CONFIG_EPROM_MCU_FW_CRC, (uint32_t)(CONFIG_EPROM_MCU_FW_CRC + 3));
	printf("LCD CRC EPROM:0x%04X---0x%04X\n", (uint32_t)CONFIG_EPROM_LCD_FW_CRC, (uint32_t)(CONFIG_EPROM_LCD_FW_CRC + 3));
	
	printf("CONFIG EPROM:0x%04X---0x%04X(size:%d)\n", (uint32_t)CONFIG_EPROM_CONFIG_START, (uint32_t)CONFIG_EPROM_CONFIG_END, (uint16_t)(CONFIG_EPROM_CONFIG_END - CONFIG_EPROM_CONFIG_START + 1));
	printf("LOGINFO EPROM:0x%04X---0x%04X(size:%d)\n", (uint32_t)CONFIG_EPROM_LOGINFO_START,(uint32_t)CONFIG_EPROM_LOGINFO_END, (uint16_t)(CONFIG_EPROM_LOGINFO_END - CONFIG_EPROM_LOGINFO_START + 1));
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
		case CLEAR_EPROM_FIRMWARE_CRC:{
			for(i = CONFIG_EPROM_MCU_FW_CRC;i <= (CONFIG_EPROM_MCU_FW_CRC + 3);i ++){
				epromWriteByte(i, &var);
			}
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
	uint16_t bk, remain;//写入地址
	uint8_t rblock[64], wblock[64];
	uint32_t tempRead, tempWrite;
	uint8_t res = 0;
	//字节顺序写入
	__HAL_CRC_DR_RESET(&hcrc);//清空之前CRC32结果
	for(i = 0;i < CONFIG_EPROM_SIZE;i += 4){
		tempWrite = HAL_RNG_GetRandomNumber(&hrng);	
		epromWriteByte((i + 0), ((uint8_t*)&tempWrite + 0));
		epromWriteByte((i + 1), ((uint8_t*)&tempWrite + 1));
		epromWriteByte((i + 2), ((uint8_t*)&tempWrite + 2));
		epromWriteByte((i + 3), ((uint8_t*)&tempWrite + 3));
		crcWrite = HAL_CRC_Accumulate(&hcrc, &tempWrite, 1);
	}
	__HAL_CRC_DR_RESET(&hcrc);//清空之前CRC32结果
	for(i = 0;i < CONFIG_EPROM_SIZE;i += 4){
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
	for(i = 0;i < CONFIG_EPROM_SIZE;i += 4){
		tempWrite = HAL_RNG_GetRandomNumber(&hrng);
		epromWriteHword((i + 0), ((uint16_t*)&tempWrite + 0)); 
		epromWriteHword((i + 2), ((uint16_t*)&tempWrite + 1));
		crcWrite = HAL_CRC_Accumulate(&hcrc, &tempWrite, 1);
	}
	__HAL_CRC_DR_RESET(&hcrc);//清空之前CRC32结果
	for(i = 0;i < CONFIG_EPROM_SIZE;i += 4){
		epromReadHword((i + 0), ((uint16_t*)&tempRead + 0));
		epromReadHword((i + 2), ((uint16_t*)&tempRead + 1));
		crcRead = HAL_CRC_Accumulate(&hcrc, &tempRead, 1);
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
	for(i = 0;i < (CONFIG_EPROM_SIZE - 4);i += 4){
		tempWrite = HAL_RNG_GetRandomNumber(&hrng);
		epromWriteDword(i, &tempWrite);
		crcWrite = HAL_CRC_Accumulate(&hcrc, &tempWrite, 1);
	}
	__HAL_CRC_DR_RESET(&hcrc);//清空之前CRC32结果
	for(i = 0;i < (CONFIG_EPROM_SIZE - 4);i += 4){
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
		tempWrite = HAL_RNG_GetRandomNumber(&hrng)%(CONFIG_EPROM_SIZE- 5 -0+1 ) + 0;;//获取随机数据
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








