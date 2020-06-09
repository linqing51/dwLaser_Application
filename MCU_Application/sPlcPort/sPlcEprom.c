#include "sPlcEprom.h"
/*****************************************************************************/
extern I2C_HandleTypeDef hi2c1;
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

HAL_StatusTypeDef epromReadByte(uint16_t ReadAddr, uint8_t *rdat){//在AT24CXX指定地址读出8位数据
//ReadAddr:开始读数的地址  
//返回值  :数据				  
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Read(&hi2c1, CONFIG_EPROM_ADR_READ, ReadAddr, I2C_MEMADD_SIZE_8BIT, rdat, 1, CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
		HAL_I2C_DeInit(&hi2c1);        //释放IO口为GPIO，复位句柄状态标志
		HAL_I2C_Init(&hi2c1);          //这句重新初始化I2C控制器
	}
	return ret;
}
HAL_StatusTypeDef epromReadHword(uint16_t ReadAddr, uint16_t *rdat){//在AT24CXX里面的指定地址开始读出16位数
//该函数用于读出16bit或者32bit的数据.
//ReadAddr   :开始读出的地址 
//返回值     :数据  	
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Read(&hi2c1, CONFIG_EPROM_ADR_READ, ReadAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)rdat, 1, CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
		HAL_I2C_DeInit(&hi2c1);        //释放IO口为GPIO，复位句柄状态标志
		HAL_I2C_Init(&hi2c1);          //这句重新初始化I2C控制器
	}
	return ret;												    
}
HAL_StatusTypeDef epromReadDword(int16_t ReadAddr, uint32_t *rdat){////在AT24CXX里面的指定地址开始读出32位数
//该函数用于读出32bit的数据.
//ReadAddr   :开始读出的地址 
//返回值     :数据  	
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Read(&hi2c1, CONFIG_EPROM_ADR_READ, ReadAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)rdat, 4, CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
		HAL_I2C_DeInit(&hi2c1);        //释放IO口为GPIO，复位句柄状态标志
		HAL_I2C_Init(&hi2c1);          //这句重新初始化I2C控制器
	}
	return ret;	
}
HAL_StatusTypeDef epromWriteByte(uint16_t WriteAddr, uint8_t DataToWrite){//在AT24CXX指定地址写入8位数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据				   	  	    																 
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Write(&hi2c1, CONFIG_EPROM_ADD_WRITE, WriteAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)(&DataToWrite), 1, CONFIG_EPROM_TIMEOUT);
	if(ret == HAL_OK){
#if CONFIG_EPROM_WIRTE_DELAY > 0
		osDelay(CONFIG_EPROM_WIRTE_DELAY);
#endif
	}
	else{
		//printf();
		HAL_I2C_DeInit(&hi2c1);        //释放IO口为GPIO，复位句柄状态标志
		HAL_I2C_Init(&hi2c1);          //这句重新初始化I2C控制器
	}
	return ret;
}
HAL_StatusTypeDef epromWriteHword(uint16_t WriteAddr, uint16_t DataToWrite){//在AT24CXX里面的指定地址开始写入16位数
//该函数用于写入16bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Write(&hi2c1, CONFIG_EPROM_ADD_WRITE, WriteAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)(&DataToWrite), 2, CONFIG_EPROM_TIMEOUT);
	if(ret == HAL_OK){
#if CONFIG_EPROM_WIRTE_DELAY > 0
		osDelay(CONFIG_EPROM_WIRTE_DELAY);
#endif
	}
	else{
		HAL_I2C_DeInit(&hi2c1);        //释放IO口为GPIO，复位句柄状态标志
		HAL_I2C_Init(&hi2c1);          //这句重新初始化I2C控制器	
	}
	return ret;
}
HAL_StatusTypeDef epromWriteDword(uint16_t WriteAddr, uint32_t DataToWrite){//在AT24CXX里面的指定地址开始写入32位数
//该函数用于写入32bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Write(&hi2c1, CONFIG_EPROM_ADD_WRITE, WriteAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)(&DataToWrite), 4, CONFIG_EPROM_TIMEOUT);
	if(ret == HAL_OK){
#if CONFIG_EPROM_WIRTE_DELAY > 0
		osDelay(CONFIG_EPROM_WIRTE_DELAY);
#endif
	}
	else{
		HAL_I2C_DeInit(&hi2c1);        //释放IO口为GPIO，复位句柄状态标志
		HAL_I2C_Init(&hi2c1);          //这句重新初始化I2C控制器
	}
	return ret;
}   
HAL_StatusTypeDef epromRead(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead){//在AT24CXX里面的指定地址开始读出指定个数的数据
//ReadAddr :开始读出的地址 对24c02为0~255
//pBuffer  :数据数组首地址
//NumToRead:要读出数据的个数
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Read(&hi2c1, CONFIG_EPROM_ADR_READ, ReadAddr, I2C_MEMADD_SIZE_8BIT, pBuffer, NumToRead, CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
		HAL_I2C_DeInit(&hi2c1);        //释放IO口为GPIO，复位句柄状态标志
		HAL_I2C_Init(&hi2c1);          //这句重新初始化I2C控制器
	}
	return ret;	
}  
HAL_StatusTypeDef epromWrite(uint16_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite){//在AT24CXX里面的指定地址开始写入指定个数的数据
//WriteAddr :开始写入的地址 对24c02为0~255
//pBuffer   :数据数组首地址
//NumToWrite:要写入数据的个数
	HAL_StatusTypeDef ret;
	uint16_t i, page, pageOutByte;
	page = NumToWrite / CONFIG_EPROM_PAGE_SIZE;//计算页数
	pageOutByte = NumToWrite % CONFIG_EPROM_PAGE_SIZE;//计算剩余字节数
	for(i = 0;i < page;i ++){
		ret = HAL_I2C_Mem_Write(&hi2c1, CONFIG_EPROM_ADD_WRITE, (WriteAddr + (i * CONFIG_EPROM_PAGE_SIZE)), I2C_MEMADD_SIZE_8BIT, (pBuffer + (i * CONFIG_EPROM_PAGE_SIZE)), CONFIG_EPROM_PAGE_SIZE, CONFIG_EPROM_TIMEOUT);
		if(ret == HAL_OK){
#if CONFIG_EPROM_WIRTE_DELAY > 0
			osDelay(CONFIG_EPROM_WIRTE_DELAY);
#endif		
		}
		else{
			HAL_I2C_DeInit(&hi2c1);        //释放IO口为GPIO，复位句柄状态标志
			HAL_I2C_Init(&hi2c1);          //这句重新初始化I2C控制器
			return ret;//错误字节退出
		}
	}
	ret = HAL_I2C_Mem_Write(&hi2c1, CONFIG_EPROM_ADD_WRITE, (WriteAddr + (i * CONFIG_EPROM_PAGE_SIZE)), I2C_MEMADD_SIZE_8BIT, (pBuffer + (i * CONFIG_EPROM_PAGE_SIZE)), pageOutByte, CONFIG_EPROM_TIMEOUT);
	if(ret == HAL_OK){
#if CONFIG_EPROM_WIRTE_DELAY > 0
		osDelay(CONFIG_EPROM_WIRTE_DELAY);
#endif		
	}
	else{
		HAL_I2C_DeInit(&hi2c1);        //释放IO口为GPIO，复位句柄状态标志
		HAL_I2C_Init(&hi2c1);          //这句重新初始化I2C控制器
		return ret;//错误字节退出
	}
	return ret;
}

uint8_t sPlcEpromTest(void){//EPROM 读写自测试
	uint32_t i, crc16Read = 0, crc16Write = 0;	
	uint16_t index;
	uint8_t rblock[41], wblock[41];
	uint8_t temp;
	uint8_t ret = false;
	crc16Clear();
	//随机按BYTE写入
#if	CONFIG_SPLC_USING_HW_RNG == 1
extern RNG_HandleTypeDef hrng;
#else
	for(i = 0;i < CONFIG_EPROM_SIZE;i ++){
		temp = rand()%0xFF;
		crc16Write = crc16CalculateAdd(temp);
		epromWriteByte(i, temp);
	}
	crc16Clear();
	for(i = 0;i < CONFIG_EPROM_SIZE;i ++){
		epromReadByte(i, &temp);
		crc16Read = crc16CalculateAdd(temp);
	}
#endif
	if(crc16Read == crc16Write){
		printf("sPlc->Eprom:byte fill write pass!\r\n");
	}
	else{
		printf("sPlc->Eprom:byte fill wirte fail!\r\n");
		return ret;
	}
	//随机按块写入
	index = 0;
	do{
		for(i = 0;i < sizeof(wblock);i ++){
			wblock[i] = rand()%0xFF;
		}
		ret = epromWrite(index, wblock, sizeof(wblock));
		ret = epromRead(index, rblock, sizeof(rblock));
		if(cmpByte(wblock, rblock, sizeof(wblock) == false)){
			printf("sPlc->Eprom:Block wirte fail!\r\n");
			return ret;
		}
		if((CONFIG_EPROM_SIZE - index) >= sizeof(wblock)){
			index = index + sizeof(wblock);
		}
		else{
			break;
		}
	}while(1);
}








