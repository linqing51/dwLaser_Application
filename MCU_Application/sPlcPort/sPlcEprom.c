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

HAL_StatusTypeDef epromReadByte(uint16_t ReadAddr, uint8_t *rdat){//��AT24CXXָ����ַ����8λ����
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����				  
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Read(&hi2c1, CONFIG_EPROM_ADR_READ, ReadAddr, I2C_MEMADD_SIZE_8BIT, rdat, 1, CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
		HAL_I2C_DeInit(&hi2c1);        //�ͷ�IO��ΪGPIO����λ���״̬��־
		HAL_I2C_Init(&hi2c1);          //������³�ʼ��I2C������
	}
	return ret;
}
HAL_StatusTypeDef epromReadHword(uint16_t ReadAddr, uint16_t *rdat){//��AT24CXX�����ָ����ַ��ʼ����16λ��
//�ú������ڶ���16bit����32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����  	
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Read(&hi2c1, CONFIG_EPROM_ADR_READ, ReadAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)rdat, 1, CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
		HAL_I2C_DeInit(&hi2c1);        //�ͷ�IO��ΪGPIO����λ���״̬��־
		HAL_I2C_Init(&hi2c1);          //������³�ʼ��I2C������
	}
	return ret;												    
}
HAL_StatusTypeDef epromReadDword(int16_t ReadAddr, uint32_t *rdat){////��AT24CXX�����ָ����ַ��ʼ����32λ��
//�ú������ڶ���32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����  	
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Read(&hi2c1, CONFIG_EPROM_ADR_READ, ReadAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)rdat, 4, CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
		HAL_I2C_DeInit(&hi2c1);        //�ͷ�IO��ΪGPIO����λ���״̬��־
		HAL_I2C_Init(&hi2c1);          //������³�ʼ��I2C������
	}
	return ret;	
}
HAL_StatusTypeDef epromWriteByte(uint16_t WriteAddr, uint8_t DataToWrite){//��AT24CXXָ����ַд��8λ����
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������				   	  	    																 
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Write(&hi2c1, CONFIG_EPROM_ADD_WRITE, WriteAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)(&DataToWrite), 1, CONFIG_EPROM_TIMEOUT);
	if(ret == HAL_OK){
#if CONFIG_EPROM_WIRTE_DELAY > 0
		osDelay(CONFIG_EPROM_WIRTE_DELAY);
#endif
	}
	else{
		//printf();
		HAL_I2C_DeInit(&hi2c1);        //�ͷ�IO��ΪGPIO����λ���״̬��־
		HAL_I2C_Init(&hi2c1);          //������³�ʼ��I2C������
	}
	return ret;
}
HAL_StatusTypeDef epromWriteHword(uint16_t WriteAddr, uint16_t DataToWrite){//��AT24CXX�����ָ����ַ��ʼд��16λ��
//�ú�������д��16bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Write(&hi2c1, CONFIG_EPROM_ADD_WRITE, WriteAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)(&DataToWrite), 2, CONFIG_EPROM_TIMEOUT);
	if(ret == HAL_OK){
#if CONFIG_EPROM_WIRTE_DELAY > 0
		osDelay(CONFIG_EPROM_WIRTE_DELAY);
#endif
	}
	else{
		HAL_I2C_DeInit(&hi2c1);        //�ͷ�IO��ΪGPIO����λ���״̬��־
		HAL_I2C_Init(&hi2c1);          //������³�ʼ��I2C������	
	}
	return ret;
}
HAL_StatusTypeDef epromWriteDword(uint16_t WriteAddr, uint32_t DataToWrite){//��AT24CXX�����ָ����ַ��ʼд��32λ��
//�ú�������д��32bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Write(&hi2c1, CONFIG_EPROM_ADD_WRITE, WriteAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)(&DataToWrite), 4, CONFIG_EPROM_TIMEOUT);
	if(ret == HAL_OK){
#if CONFIG_EPROM_WIRTE_DELAY > 0
		osDelay(CONFIG_EPROM_WIRTE_DELAY);
#endif
	}
	else{
		HAL_I2C_DeInit(&hi2c1);        //�ͷ�IO��ΪGPIO����λ���״̬��־
		HAL_I2C_Init(&hi2c1);          //������³�ʼ��I2C������
	}
	return ret;
}   
HAL_StatusTypeDef epromRead(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead){//��AT24CXX�����ָ����ַ��ʼ����ָ������������
//ReadAddr :��ʼ�����ĵ�ַ ��24c02Ϊ0~255
//pBuffer  :���������׵�ַ
//NumToRead:Ҫ�������ݵĸ���
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Read(&hi2c1, CONFIG_EPROM_ADR_READ, ReadAddr, I2C_MEMADD_SIZE_8BIT, pBuffer, NumToRead, CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
		HAL_I2C_DeInit(&hi2c1);        //�ͷ�IO��ΪGPIO����λ���״̬��־
		HAL_I2C_Init(&hi2c1);          //������³�ʼ��I2C������
	}
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
		ret = HAL_I2C_Mem_Write(&hi2c1, CONFIG_EPROM_ADD_WRITE, (WriteAddr + (i * CONFIG_EPROM_PAGE_SIZE)), I2C_MEMADD_SIZE_8BIT, (pBuffer + (i * CONFIG_EPROM_PAGE_SIZE)), CONFIG_EPROM_PAGE_SIZE, CONFIG_EPROM_TIMEOUT);
		if(ret == HAL_OK){
#if CONFIG_EPROM_WIRTE_DELAY > 0
			osDelay(CONFIG_EPROM_WIRTE_DELAY);
#endif		
		}
		else{
			HAL_I2C_DeInit(&hi2c1);        //�ͷ�IO��ΪGPIO����λ���״̬��־
			HAL_I2C_Init(&hi2c1);          //������³�ʼ��I2C������
			return ret;//�����ֽ��˳�
		}
	}
	ret = HAL_I2C_Mem_Write(&hi2c1, CONFIG_EPROM_ADD_WRITE, (WriteAddr + (i * CONFIG_EPROM_PAGE_SIZE)), I2C_MEMADD_SIZE_8BIT, (pBuffer + (i * CONFIG_EPROM_PAGE_SIZE)), pageOutByte, CONFIG_EPROM_TIMEOUT);
	if(ret == HAL_OK){
#if CONFIG_EPROM_WIRTE_DELAY > 0
		osDelay(CONFIG_EPROM_WIRTE_DELAY);
#endif		
	}
	else{
		HAL_I2C_DeInit(&hi2c1);        //�ͷ�IO��ΪGPIO����λ���״̬��־
		HAL_I2C_Init(&hi2c1);          //������³�ʼ��I2C������
		return ret;//�����ֽ��˳�
	}
	return ret;
}

uint8_t sPlcEpromTest(void){//EPROM ��д�Բ���
	uint32_t i, crc16Read = 0, crc16Write = 0;	
	uint16_t index;
	uint8_t rblock[41], wblock[41];
	uint8_t temp;
	uint8_t ret = false;
	crc16Clear();
	//�����BYTEд��
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
	//�������д��
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








