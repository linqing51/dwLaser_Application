//������FRAM��������EEPROM
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

HAL_StatusTypeDef epromReadByte(uint16_t ReadAddr, uint8_t rdat){//��ָ����ַ����8λ����
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����				  
	HAL_StatusTypeDef ret;
	if(ReadAddr > (CONFIG_EPROM_SIZE - 1)){//д��ַ��������
		ret = HAL_ERROR;
#if	CONFIG_DEBUG_EPROM == 1
#endif
		return ret;
	}	
	ret = HAL_I2C_Mem_Read(&hi2c1,
	                       CONFIG_EPROM_SLAVE_ADDR,
	                       ReadAddr,
	                       I2C_MEMADD_SIZE_16BIT,
	                       &rdat,
	                       1,
	                       CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
#if	CONFIG_DEBUG_EPROM == 1
#endif
		ret = HAL_I2C_DeInit(&hi2c1);//�ͷ�IO��ΪGPIO����λ���״̬��־
		ret = HAL_I2C_Init(&hi2c1);//������³�ʼ��I2C������
	}
	return ret;
}
HAL_StatusTypeDef epromReadHword(uint16_t ReadAddr, uint16_t rdat){//��ָ����ַ��ʼ����16λ��
//�ú������ڶ���16bit����32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����  	
	HAL_StatusTypeDef ret;
	if((ReadAddr + 1) > (CONFIG_EPROM_SIZE - 1)){//д��ַ��������
		ret = HAL_ERROR;
#if	CONFIG_DEBUG_EPROM == 1
#endif
		return ret;
	}	
	ret = HAL_I2C_Mem_Read(&hi2c1, 
						   CONFIG_EPROM_SLAVE_ADDR,
	                       ReadAddr,
	                       I2C_MEMADD_SIZE_16BIT,
	                       (uint8_t*)(&rdat),
	                       1,
	                       CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
#if	CONFIG_DEBUG_EPROM == 1
#endif
		ret = HAL_I2C_DeInit(&hi2c1);        //�ͷ�IO��ΪGPIO����λ���״̬��־
		ret = HAL_I2C_Init(&hi2c1);          //������³�ʼ��I2C������
	}
	return ret;												    
}
HAL_StatusTypeDef epromReadDword(uint16_t ReadAddr, uint32_t rdat){////��ָ����ַ��ʼ����32λ��
//�ú������ڶ���32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����  	
	HAL_StatusTypeDef ret;
	if((ReadAddr + 3) > (CONFIG_EPROM_SIZE - 1)){//д��ַ��������
		ret = HAL_ERROR;
#if	CONFIG_DEBUG_EPROM == 1
#endif
		return ret;
	}	
	ret = HAL_I2C_Mem_Read(&hi2c1, 
	                       CONFIG_EPROM_SLAVE_ADDR,
	                       ReadAddr,
	                       I2C_MEMADD_SIZE_16BIT,
	                       (uint8_t*)(&rdat),
	                       4,
	                       CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
#if	CONFIG_DEBUG_EPROM == 1
#endif
		ret = HAL_I2C_DeInit(&hi2c1);        //�ͷ�IO��ΪGPIO����λ���״̬��־
		ret = HAL_I2C_Init(&hi2c1);          //������³�ʼ��I2C������
	}
	return ret;	
}
HAL_StatusTypeDef epromWriteByte(uint16_t WriteAddr, uint8_t wdat){//��ָ����ַд��8λ����
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������				   	  	    																 
	HAL_StatusTypeDef ret;
	if(WriteAddr > (CONFIG_EPROM_SIZE - 1)){//д��ַ��������
		ret = HAL_ERROR;
#if	CONFIG_DEBUG_EPROM == 1
		//printf();
#endif
		return ret;
	}
	ret = HAL_I2C_Mem_Write(&hi2c1, 
	                        CONFIG_EPROM_SLAVE_ADDR, 
	                        WriteAddr, 
	                        I2C_MEMADD_SIZE_16BIT, 
	                        &wdat, 
	                        1, 
	                        CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
#if	CONFIG_DEBUG_EPROM == 1
		//printf();
#endif
		ret = HAL_I2C_DeInit(&hi2c1);//�ͷ�IO��ΪGPIO����λ���״̬��־
		ret = HAL_I2C_Init(&hi2c1);//������³�ʼ��I2C������
	}
	return ret;
}
HAL_StatusTypeDef epromWriteHword(uint16_t WriteAddr, uint16_t wdat){//�ڵ�ָ����ַ��ʼд��16λ��
//�ú�������д��16bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
	HAL_StatusTypeDef ret;
	if((WriteAddr + 1) > (CONFIG_EPROM_SIZE - 1)){//д��ַ��������
#if	CONFIG_DEBUG_EPROM == 1
		//printf();
#endif
		ret = HAL_ERROR;
		return ret;
	}
	ret = HAL_I2C_Mem_Write(&hi2c1, 
	                        CONFIG_EPROM_SLAVE_ADDR, 
	                        WriteAddr, 
	                        I2C_MEMADD_SIZE_16BIT, 
	                        (uint8_t*)(&wdat), 
	                        2, 
	                        CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
#if	CONFIG_DEBUG_EPROM == 1
		//printf();
#endif
		ret = HAL_I2C_DeInit(&hi2c1);//�ͷ�IO��ΪGPIO����λ���״̬��־
		ret = HAL_I2C_Init(&hi2c1);//������³�ʼ��I2C������	
	}
	return ret;
}
HAL_StatusTypeDef epromWriteDword(uint16_t WriteAddr, uint32_t wdat){//�ڵ�ָ����ַ��ʼд��32λ��
//�ú�������д��32bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
	HAL_StatusTypeDef ret;
	if((WriteAddr + 3) >= (CONFIG_EPROM_SIZE - 1)){//д��ַ��������
		ret = HAL_ERROR;
		return ret;
	}
	ret = HAL_I2C_Mem_Write(&hi2c1, 
	                        CONFIG_EPROM_SLAVE_ADDR, 
	                        WriteAddr, 
	                        I2C_MEMADD_SIZE_16BIT, 
	                        (uint8_t*)(&wdat), 
	                        4, 
	                        CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
		ret = HAL_I2C_DeInit(&hi2c1);        //�ͷ�IO��ΪGPIO����λ���״̬��־
		ret = HAL_I2C_Init(&hi2c1);          //������³�ʼ��I2C������
	}
	return ret;
}   
HAL_StatusTypeDef epromRead(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead){//�ڵ�ָ����ַ��ʼ����ָ������������
//ReadAddr :��ʼ�����ĵ�ַ ��24c02Ϊ0~255
//pBuffer  :���������׵�ַ
//NumToRead:Ҫ�������ݵĸ���
	HAL_StatusTypeDef ret;
	if(ReadAddr + NumToRead >= (CONFIG_EPROM_SIZE - 1)){//����ַ��������
		ret = HAL_ERROR;
		return ret;
	}
	ret = HAL_I2C_Mem_Read(&hi2c1, 
	                       CONFIG_EPROM_SLAVE_ADDR,
	                       ReadAddr,
						   I2C_MEMADD_SIZE_16BIT,
	                       pBuffer,
						   NumToRead,
	                       CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
		ret = HAL_I2C_DeInit(&hi2c1);        //�ͷ�IO��ΪGPIO����λ���״̬��־
		ret = HAL_I2C_Init(&hi2c1);          //������³�ʼ��I2C������
	}
	return ret;	
}  
HAL_StatusTypeDef epromWrite(uint16_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite){//�ڵ�ָ����ַ��ʼд��ָ������������
//WriteAddr :��ʼд��ĵ�ַ ��24c02Ϊ0~255
//pBuffer   :���������׵�ַ
//NumToWrite:Ҫд�����ݵĸ���
	HAL_StatusTypeDef ret;
	if(WriteAddr + NumToWrite >= (CONFIG_EPROM_SIZE - 1)){//����ַ��������
		ret = HAL_ERROR;
		return ret;
	}
	ret = HAL_I2C_Mem_Write(&hi2c1, 
		                    CONFIG_EPROM_SLAVE_ADDR, 
		                    WriteAddr, 
		                    I2C_MEMADD_SIZE_16BIT, 
		                    pBuffer, 
		                    NumToWrite, 
		                    CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
		ret = HAL_I2C_DeInit(&hi2c1);        //�ͷ�IO��ΪGPIO����λ���״̬��־
		ret = HAL_I2C_Init(&hi2c1);          //������³�ʼ��I2C������
	}
	return ret;
}
/*****************************************************************************/
uint8_t sPlcEpromTest(void){//EPROM ��д�Բ���
	uint32_t i, crc16Read = 0, crc16Write = 0;	
	uint16_t bk, remain;//д���ַ
	uint8_t rblock[32], wblock[32];
	uint8_t temp0, temp1;
	//�ֽ�˳��д��
	crc16Clear();
	for(i = 0;i < CONFIG_EPROM_SIZE;i ++){
		temp0 = rand() % 0xFF;
		crc16Write = crc16CalculateAdd(temp0);
		epromWriteByte(i, temp0);
	}
	crc16Clear();
	for(i = 0;i < CONFIG_EPROM_SIZE;i ++){
		epromReadByte(i, temp1);
		crc16Read = crc16CalculateAdd(temp1);
	}
	if(crc16Read == crc16Write){
		printf("sPlc->Eprom:Byte sequential write pass!\r\n");
	}
	else{
		printf("sPlc->Eprom:Byte sequential wirte fail!\r\n");
		return false;
	}
	//��˳��д��
	bk = CONFIG_EPROM_SIZE / sizeof(wblock);
	remain =  CONFIG_EPROM_SIZE % sizeof(wblock);
	for(i = 0; i < bk;i ++){
		memset(wblock, (i & 0xFF), sizeof(wblock));
		memset(rblock, 0x00, sizeof(rblock));
		epromWrite((bk + i * sizeof(wblock)), wblock, sizeof(wblock));
		epromRead((bk + i * sizeof(wblock)), rblock, sizeof(wblock));
		if(cmpByte(rblock, rblock, sizeof(rblock)) == false){
			printf("sPlc->Eprom:Block sequential Write fail!\r\n");
			return false;
		}
	}
	temp0 = rand() % 0xFF;//��ȡ�������
	memset(wblock, temp0, sizeof(wblock));
	memset(rblock, 0x00, sizeof(rblock));
	epromWrite((CONFIG_EPROM_SIZE - remain), wblock, remain);
	epromRead((CONFIG_EPROM_SIZE - remain), rblock, remain);
	if(cmpByte(rblock, rblock, sizeof(rblock)) == false){
		printf("sPlc->Eprom:Block sequential Write fail!\r\n");
		return false;
	}
	printf("sPlc->Eprom:Block sequential Write pass!\r\n");
	//���д��
	for(i=0;i<10000;i++){
		bk = rand() % CONFIG_EPROM_SIZE;//��ȡ�����ַ
		temp0 = rand() % 0xFF;//��ȡ�������
		epromWrite(bk, &temp0, 1);//д��
		epromRead(bk, &temp1, 1);//��ȡ
		if(temp0 != temp1){
			printf("sPlc->Eprom:Random write fail!\r\n");
			return false;
		}
	}
	printf("sPlc->Eprom:Random write pass!\r\n");
	return true;
}








