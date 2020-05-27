#include "sPlcEprom.h"
/*****************************************************************************/
extern I2C_HandleTypeDef hi2c1;
/*****************************************************************************/
HAL_StatusTypeDef epromReadByte(uint16_t ReadAddr, uint8_t *rdat){//在AT24CXX指定地址读出8位数据
//ReadAddr:开始读数的地址  
//返回值  :数据				  
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Read(&hi2c1, CONFIG_EPROM_ADDRESS, ReadAddr, I2C_MEMADD_SIZE_8BIT, rdat, 1, CONFIG_EPROM_TIMEOUT);
	return ret;
}
HAL_StatusTypeDef epromReadHword(uint16_t ReadAddr, uint16_t *rdat){//在AT24CXX里面的指定地址开始读出16位数
//该函数用于读出16bit或者32bit的数据.
//ReadAddr   :开始读出的地址 
//返回值     :数据  	
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Read(&hi2c1, CONFIG_EPROM_ADDRESS, ReadAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)rdat, 1, CONFIG_EPROM_TIMEOUT);
	return ret;												    
}
HAL_StatusTypeDef epromReadDword(int16_t ReadAddr, uint32_t *rdat){////在AT24CXX里面的指定地址开始读出32位数
//该函数用于读出32bit的数据.
//ReadAddr   :开始读出的地址 
//返回值     :数据  	
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Read(&hi2c1, CONFIG_EPROM_ADDRESS, ReadAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)rdat, 4, CONFIG_EPROM_TIMEOUT);
	return ret;	
}
HAL_StatusTypeDef epromWriteByte(uint16_t WriteAddr, uint8_t DataToWrite){//在AT24CXX指定地址写入8位数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据				   	  	    																 
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Write(&hi2c1, CONFIG_EPROM_ADDRESS, WriteAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)(&DataToWrite), 1, CONFIG_EPROM_TIMEOUT);
	if(ret == HAL_OK){
#if CONFIG_EPROM_WIRTE_DELAY > 0
		osDelay(CONFIG_EPROM_WIRTE_DELAY);
#endif
	}
	return ret;
}
HAL_StatusTypeDef epromWriteHword(uint16_t WriteAddr, uint16_t DataToWrite){//在AT24CXX里面的指定地址开始写入16位数
//该函数用于写入16bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Write(&hi2c1, CONFIG_EPROM_ADDRESS, WriteAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)(&DataToWrite), 2, CONFIG_EPROM_TIMEOUT);
	if(ret == HAL_OK){
#if CONFIG_EPROM_WIRTE_DELAY > 0
		osDelay(CONFIG_EPROM_WIRTE_DELAY);
#endif
	}
	return ret;
}
HAL_StatusTypeDef epromWriteDword(uint16_t WriteAddr, uint32_t DataToWrite){//在AT24CXX里面的指定地址开始写入32位数
//该函数用于写入32bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Write(&hi2c1, CONFIG_EPROM_ADDRESS, WriteAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)(&DataToWrite), 4, CONFIG_EPROM_TIMEOUT);
	if(ret == HAL_OK){
#if CONFIG_EPROM_WIRTE_DELAY > 0
		osDelay(CONFIG_EPROM_WIRTE_DELAY);
#endif
	}
	return ret;
}   
HAL_StatusTypeDef epromRead(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead){//在AT24CXX里面的指定地址开始读出指定个数的数据
//ReadAddr :开始读出的地址 对24c02为0~255
//pBuffer  :数据数组首地址
//NumToRead:要读出数据的个数
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Read(&hi2c1, CONFIG_EPROM_ADDRESS, ReadAddr, I2C_MEMADD_SIZE_8BIT, pBuffer, NumToRead, CONFIG_EPROM_TIMEOUT);
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
		ret = HAL_I2C_Mem_Write(&hi2c1, CONFIG_EPROM_ADDRESS, (WriteAddr + (i * CONFIG_EPROM_PAGE_SIZE)), I2C_MEMADD_SIZE_8BIT, (pBuffer + (i * CONFIG_EPROM_PAGE_SIZE)), CONFIG_EPROM_PAGE_SIZE, CONFIG_EPROM_TIMEOUT);
		if(ret == HAL_OK){
#if CONFIG_EPROM_WIRTE_DELAY > 0
			osDelay(CONFIG_EPROM_WIRTE_DELAY);
#endif		
		}
		else{
			return ret;//错误字节退出
		}
	}
	ret = HAL_I2C_Mem_Write(&hi2c1, CONFIG_EPROM_ADDRESS, (WriteAddr + (i * CONFIG_EPROM_PAGE_SIZE)), I2C_MEMADD_SIZE_8BIT, (pBuffer + (i * CONFIG_EPROM_PAGE_SIZE)), pageOutByte, CONFIG_EPROM_TIMEOUT);
	if(ret == HAL_OK){
#if CONFIG_EPROM_WIRTE_DELAY > 0
		osDelay(CONFIG_EPROM_WIRTE_DELAY);
#endif		
	}
	else{
		return ret;//错误字节退出
	}
	return ret;
}
#if CONFIG_SPLC_USING_EPROM_TEST == 1 && CONFIG_SPLC_USING_EPROM == 1
uint8_t epromTest(void){//EPROM 读写自测试
	uint32_t i, crc16Read = 0, crc16Write = 0;	
	uint8_t temp;
	crc16Clear();
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
	if(crc16Read == crc16Write){
		return true;
	}
	else{
		return false;
	}
}
#endif







