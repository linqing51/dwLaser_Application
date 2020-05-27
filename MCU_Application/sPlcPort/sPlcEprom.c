#include "sPlcEprom.h"
/*****************************************************************************/
extern I2C_HandleTypeDef hi2c1;
/*****************************************************************************/
HAL_StatusTypeDef epromReadByte(uint16_t ReadAddr, uint8_t *rdat){//��AT24CXXָ����ַ����8λ����
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����				  
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Read(&hi2c1, CONFIG_EPROM_ADDRESS, ReadAddr, I2C_MEMADD_SIZE_8BIT, rdat, 1, CONFIG_EPROM_TIMEOUT);
	return ret;
}
HAL_StatusTypeDef epromReadHword(uint16_t ReadAddr, uint16_t *rdat){//��AT24CXX�����ָ����ַ��ʼ����16λ��
//�ú������ڶ���16bit����32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����  	
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Read(&hi2c1, CONFIG_EPROM_ADDRESS, ReadAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)rdat, 1, CONFIG_EPROM_TIMEOUT);
	return ret;												    
}
HAL_StatusTypeDef epromReadDword(int16_t ReadAddr, uint32_t *rdat){////��AT24CXX�����ָ����ַ��ʼ����32λ��
//�ú������ڶ���32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����  	
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Read(&hi2c1, CONFIG_EPROM_ADDRESS, ReadAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)rdat, 4, CONFIG_EPROM_TIMEOUT);
	return ret;	
}
HAL_StatusTypeDef epromWriteByte(uint16_t WriteAddr, uint8_t DataToWrite){//��AT24CXXָ����ַд��8λ����
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������				   	  	    																 
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Write(&hi2c1, CONFIG_EPROM_ADDRESS, WriteAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)(&DataToWrite), 1, CONFIG_EPROM_TIMEOUT);
	if(ret == HAL_OK){
#if CONFIG_EPROM_WIRTE_DELAY > 0
		osDelay(CONFIG_EPROM_WIRTE_DELAY);
#endif
	}
	return ret;
}
HAL_StatusTypeDef epromWriteHword(uint16_t WriteAddr, uint16_t DataToWrite){//��AT24CXX�����ָ����ַ��ʼд��16λ��
//�ú�������д��16bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Write(&hi2c1, CONFIG_EPROM_ADDRESS, WriteAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)(&DataToWrite), 2, CONFIG_EPROM_TIMEOUT);
	if(ret == HAL_OK){
#if CONFIG_EPROM_WIRTE_DELAY > 0
		osDelay(CONFIG_EPROM_WIRTE_DELAY);
#endif
	}
	return ret;
}
HAL_StatusTypeDef epromWriteDword(uint16_t WriteAddr, uint32_t DataToWrite){//��AT24CXX�����ָ����ַ��ʼд��32λ��
//�ú�������д��32bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Write(&hi2c1, CONFIG_EPROM_ADDRESS, WriteAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)(&DataToWrite), 4, CONFIG_EPROM_TIMEOUT);
	if(ret == HAL_OK){
#if CONFIG_EPROM_WIRTE_DELAY > 0
		osDelay(CONFIG_EPROM_WIRTE_DELAY);
#endif
	}
	return ret;
}   
HAL_StatusTypeDef epromRead(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead){//��AT24CXX�����ָ����ַ��ʼ����ָ������������
//ReadAddr :��ʼ�����ĵ�ַ ��24c02Ϊ0~255
//pBuffer  :���������׵�ַ
//NumToRead:Ҫ�������ݵĸ���
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Read(&hi2c1, CONFIG_EPROM_ADDRESS, ReadAddr, I2C_MEMADD_SIZE_8BIT, pBuffer, NumToRead, CONFIG_EPROM_TIMEOUT);
	return ret;	
}  
HAL_StatusTypeDef epromWrite(uint16_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite){//��AT24CXX�����ָ����ַ��ʼд��ָ������������
//WriteAddr :��ʼд��ĵ�ַ ��24c02Ϊ0~255
//pBuffer   :���������׵�ַ
//NumToWrite:Ҫд�����ݵĸ���
	HAL_StatusTypeDef ret;
	uint16_t i, page, pageOutByte;
	page = NumToWrite / CONFIG_EPROM_PAGE_SIZE;//����ҳ��
	pageOutByte = NumToWrite % CONFIG_EPROM_PAGE_SIZE;//����ʣ���ֽ���
	for(i = 0;i < page;i ++){
		ret = HAL_I2C_Mem_Write(&hi2c1, CONFIG_EPROM_ADDRESS, (WriteAddr + (i * CONFIG_EPROM_PAGE_SIZE)), I2C_MEMADD_SIZE_8BIT, (pBuffer + (i * CONFIG_EPROM_PAGE_SIZE)), CONFIG_EPROM_PAGE_SIZE, CONFIG_EPROM_TIMEOUT);
		if(ret == HAL_OK){
#if CONFIG_EPROM_WIRTE_DELAY > 0
			osDelay(CONFIG_EPROM_WIRTE_DELAY);
#endif		
		}
		else{
			return ret;//�����ֽ��˳�
		}
	}
	ret = HAL_I2C_Mem_Write(&hi2c1, CONFIG_EPROM_ADDRESS, (WriteAddr + (i * CONFIG_EPROM_PAGE_SIZE)), I2C_MEMADD_SIZE_8BIT, (pBuffer + (i * CONFIG_EPROM_PAGE_SIZE)), pageOutByte, CONFIG_EPROM_TIMEOUT);
	if(ret == HAL_OK){
#if CONFIG_EPROM_WIRTE_DELAY > 0
		osDelay(CONFIG_EPROM_WIRTE_DELAY);
#endif		
	}
	else{
		return ret;//�����ֽ��˳�
	}
	return ret;
}
#if CONFIG_SPLC_USING_EPROM_TEST == 1 && CONFIG_SPLC_USING_EPROM == 1
uint8_t epromTest(void){//EPROM ��д�Բ���
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







