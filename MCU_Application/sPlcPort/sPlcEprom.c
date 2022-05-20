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
HAL_StatusTypeDef epromReadByte(uint16_t ReadAddr, uint8_t *rdat){//��ָ����ַ����8λ����
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����				  
	HAL_StatusTypeDef ret;
#if CONFIG_SPLC_USING_EPROM == 1
	if(ReadAddr > (CONFIG_EPROM_SIZE - 1)){//д��ַ��������
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
		ret = HAL_I2C_DeInit(&hi2c1);//�ͷ�IO��ΪGPIO����λ���״̬��־
		ret = HAL_I2C_Init(&hi2c1);//������³�ʼ��I2C������
#if CONFIG_DEBUG_EPROM == 1
		printf("%s,%d,%s:eprom read byte fail,adr:%d,dat:%d\n", __FILE__, __LINE__, __func__, ReadAddr, *rdat);
#endif
	}
#if CONFIG_DEBUG_EPROM == 1
	printf("%s,%d,%s:eprom read byte done,adr:%d,dat:%d\n", __FILE__, __LINE__, __func__, ReadAddr, *rdat);
#endif
	return ret;
#else
	return HAL_OK;
#endif
}
HAL_StatusTypeDef epromReadHword(uint16_t ReadAddr, uint16_t *rdat){//��ָ����ַ��ʼ����16λ��
//�ú������ڶ���16bit����32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����  	
	HAL_StatusTypeDef ret;
#if CONFIG_SPLC_USING_EPROM == 1
	if((ReadAddr + 1) > (CONFIG_EPROM_SIZE - 1)){//д��ַ��������
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
		ret = HAL_I2C_DeInit(&hi2c1);        //�ͷ�IO��ΪGPIO����λ���״̬��־
		ret = HAL_I2C_Init(&hi2c1);          //������³�ʼ��I2C������
#if CONFIG_DEBUG_EPROM == 1
		printf("%s,%d,%s:eprom read hword fail,adr:%d,dat:%d\n", __FILE__, __LINE__, __func__, ReadAddr, *rdat);
#endif
	}
#if CONFIG_DEBUG_EPROM == 1
	printf("%s,%d,%s:Eprom read hword done,adr:%d,dat:%d\n", __FILE__, __LINE__, __func__, ReadAddr, *rdat);
#endif
	return ret;
#else
	return HAL_OK;
#endif	
}
HAL_StatusTypeDef epromReadDword(uint16_t ReadAddr, uint32_t *rdat){////��ָ����ַ��ʼ����32λ��
//�ú������ڶ���32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����  	
	HAL_StatusTypeDef ret;
#if CONFIG_SPLC_USING_EPROM == 1	
	if((ReadAddr + 3) > (CONFIG_EPROM_SIZE - 1)){//д��ַ��������
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
		ret = HAL_I2C_DeInit(&hi2c1);        //�ͷ�IO��ΪGPIO����λ���״̬��־
		ret = HAL_I2C_Init(&hi2c1);          //������³�ʼ��I2C������
#if CONFIG_DEBUG_EPROM == 1
		printf("%s,%d,%s:eprom read dword fail,adr:%d,dat:%d\n", __FILE__, __LINE__, __func__, ReadAddr, *rdat);
#endif
	}
#if CONFIG_DEBUG_EPROM == 1
	printf("%s,%d,%s:eprom read dword done,adr:%d,dat:%d\n", __FILE__, __LINE__, __func__, ReadAddr, *rdat);
#endif
	return ret;
#else
	return HAL_OK;
#endif
}
HAL_StatusTypeDef epromWriteByte(uint16_t WriteAddr, uint8_t *wdat){//��ָ����ַд��8λ����
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������
	HAL_StatusTypeDef ret;
#if CONFIG_SPLC_USING_EPROM == 1	
	if(WriteAddr > (CONFIG_EPROM_SIZE - 1)){//д��ַ��������
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
		ret = HAL_I2C_DeInit(&hi2c1);//�ͷ�IO��ΪGPIO����λ���״̬��־
		ret = HAL_I2C_Init(&hi2c1);//������³�ʼ��I2C������
#if CONFIG_DEBUG_EPROM == 1
		printf("%s,%d,%s:Eprom write byte fail,adr:%d,dat:%d\n", __FILE__, __LINE__, __func__, WriteAddr, wdat);
#endif
	}
#if CONFIG_DEBUG_EPROM == 1
	printf("%s,%d,%s:eprom write byte done,adr:%d,dat:%d\n", __FILE__, __LINE__, __func__, WriteAddr, wdat);
#endif
	return ret;
#else
	return HAL_OK;
#endif
}
HAL_StatusTypeDef epromWriteHword(uint16_t WriteAddr, uint16_t *wdat){//�ڵ�ָ����ַ��ʼд��16λ��
//�ú�������д��16bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
	HAL_StatusTypeDef ret;
#if CONFIG_SPLC_USING_EPROM == 1	
	if((WriteAddr + 1) > (CONFIG_EPROM_SIZE - 1)){//д��ַ��������
		ret = HAL_ERROR;
		return ret;
	}
	ret = HAL_I2C_Mem_Write(&hi2c1, 
	                        CONFIG_EPROM_WRITE_ADDR, 
	                        WriteAddr, 
	                        I2C_MEMADD_SIZE_16BIT, 
	                        (uint8_t*)(&wdat), 
	                        2, 
	                        CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
		ret = HAL_I2C_DeInit(&hi2c1);//�ͷ�IO��ΪGPIO����λ���״̬��־
		ret = HAL_I2C_Init(&hi2c1);//������³�ʼ��I2C������	
#if CONFIG_DEBUG_EPROM == 1
		printf("%s,%d,%s:Eprom write hword fail,adr:%d,dat:%d\n", __FILE__, __LINE__, __func__, WriteAddr, wdat);
#endif
	}
#if CONFIG_DEBUG_EPROM == 1
	printf("%s,%d,%s:eprom write hword done,adr:%d,dat:%d\n", __FILE__, __LINE__, __func__, WriteAddr, wdat);
#endif
	return ret;
#else
	return HAL_OK;
#endif
}
HAL_StatusTypeDef epromWriteDword(uint16_t WriteAddr, uint32_t *wdat){//�ڵ�ָ����ַ��ʼд��32λ��
//�ú�������д��32bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
	HAL_StatusTypeDef ret;
#if CONFIG_SPLC_USING_EPROM == 1
	if((WriteAddr + 3) >= (CONFIG_EPROM_SIZE - 1)){//д��ַ��������
		ret = HAL_ERROR;
		return ret;
	}
	ret = HAL_I2C_Mem_Write(&hi2c1, 
	                        CONFIG_EPROM_WRITE_ADDR, 
	                        WriteAddr, 
	                        I2C_MEMADD_SIZE_16BIT, 
	                        (uint8_t*)(&wdat), 
	                        4, 
	                        CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
		ret = HAL_I2C_DeInit(&hi2c1);        //�ͷ�IO��ΪGPIO����λ���״̬��־
		ret = HAL_I2C_Init(&hi2c1);          //������³�ʼ��I2C������
#if CONFIG_DEBUG_EPROM == 1
		printf("%s,%d,%s:Eprom write dword fail,adr:%d,dat:%d\n", __FILE__, __LINE__, __func__, WriteAddr, wdat);
#endif
	}
#if CONFIG_DEBUG_EPROM == 1
	printf("%s,%d,%s:eprom write hword done,adr:%d,dat:%d\n", __FILE__, __LINE__, __func__, WriteAddr, wdat);
#endif
	return ret;
#else
	return HAL_OK;
#endif
}   
HAL_StatusTypeDef epromRead(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead){//�ڵ�ָ����ַ��ʼ����ָ������������
//ReadAddr :��ʼ�����ĵ�ַ ��24c02Ϊ0~255
//pBuffer  :���������׵�ַ
//NumToRead:Ҫ�������ݵĸ���
	HAL_StatusTypeDef ret;
#if CONFIG_SPLC_USING_EPROM == 1
	uint16_t rAddr, rBlock, rByte, doBlock;
	uint8_t* rBuffer;
	if((ReadAddr + NumToRead) > CONFIG_EPROM_SIZE){//����ַ��������
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
			ret = HAL_I2C_DeInit(&hi2c1);//�ͷ�IO��ΪGPIO����λ���״̬��־
			ret = HAL_I2C_Init(&hi2c1);//������³�ʼ��I2C������
#if CONFIG_DEBUG_EPROM == 1
			printf("%s,%d,%s:eprom read block fail,adr:%d,num:%d\n", __FILE__, __LINE__, __func__, ReadAddr, NumToRead);
#endif
		}
		rAddr += CONFIG_EPROM_PAGE_SIZE;
		rBuffer += CONFIG_EPROM_PAGE_SIZE;
	}
	if(rByte != 0x0){
		ret = HAL_I2C_Mem_Read(&hi2c1, CONFIG_EPROM_READ_ADDR, rAddr, I2C_MEMADD_SIZE_16BIT, rBuffer, rByte ,CONFIG_EPROM_TIMEOUT);
		if(ret != HAL_OK){
			ret = HAL_I2C_DeInit(&hi2c1);        //�ͷ�IO��ΪGPIO����λ���״̬��־
			ret = HAL_I2C_Init(&hi2c1);          //������³�ʼ��I2C������
#if CONFIG_DEBUG_EPROM == 1
			printf("%s,%d,%s:eprom read rbyte fail,adr:%d,num:%d\n", __FILE__, __LINE__, __func__, ReadAddr, NumToRead);
#endif
		}
		else{
#if CONFIG_DEBUG_EPROM == 1
			printf("%s,%d,%s:eprom read multibyte done,adr:%d,num:%d\n", __FILE__, __LINE__, __func__, ReadAddr, NumToRead);
#endif
		}
	}
	return ret;	
#else
	return HAL_OK;
#endif
}  
HAL_StatusTypeDef epromWrite(uint16_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite){//�ڵ�ָ����ַ��ʼд��ָ������������
//WriteAddr :��ʼд��ĵ�ַ ��24c02Ϊ0~255
//pBuffer   :���������׵�ַ
//NumToWrite:Ҫд�����ݵĸ���
	HAL_StatusTypeDef ret;
#if CONFIG_SPLC_USING_EPROM == 1
	uint16_t wAddr, wBlock, wByte, doBlock;
	uint8_t* wBuffer;
	if((WriteAddr + NumToWrite) > CONFIG_EPROM_SIZE){//����ַ��������
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
			ret = HAL_I2C_DeInit(&hi2c1);        //�ͷ�IO��ΪGPIO����λ���״̬��־
			ret = HAL_I2C_Init(&hi2c1);          //������³�ʼ��I2C������
#if CONFIG_DEBUG_EPROM == 1
			printf("%s,%d,%s:eprom write block fail,adr:%d,num:%d\n", __FILE__, __LINE__, __func__, WriteAddr, NumToWrite);
#endif		
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
			ret = HAL_I2C_DeInit(&hi2c1);        //�ͷ�IO��ΪGPIO����λ���״̬��־
			ret = HAL_I2C_Init(&hi2c1);          //������³�ʼ��I2C������
#if CONFIG_DEBUG_EPROM == 1
			printf("%s,%d,%s:eprom write remain byte fail,adr:%d,num:%d\n", __FILE__, __LINE__, __func__, WriteAddr, NumToWrite);
#endif	
		}
	}
#if CONFIG_EPROM_WRITE_DELAY > 0
	HAL_Delay(CONFIG_EPROM_WRITE_DELAY);
#endif
#if CONFIG_DEBUG_EPROM == 1
	printf("%s,%d,%s:eprom write multibyte done,adr:%d,num:%d\n", __FILE__, __LINE__, __func__, WriteAddr, NumToWrite);
#endif
	return ret;
#else
	return HAL_OK;
#endif
}
/*****************************************************************************/
uint8_t sPlcEpromTest(void){//EPROM ��д�Բ���
	uint32_t i, crc16Read = 0, crc16Write = 0;	
	uint16_t bk, remain;//д���ַ
	uint8_t rblock[32], wblock[32];
	uint8_t temp0, temp1;
	//��д�����
	memset(rblock, 0x0, 32);
	memset(wblock, 0x0, 32);
	sprintf((char*)wblock, "Hello Eprom!,123456789ABCDFEGH\n");
	epromWrite(0, wblock, 32);
	epromRead(0, rblock, 32);
	//�ֽ�˳��д��
	memset(rblock, 0x0, 32);
	memset(wblock, 0x0, 32);
	crc16Clear();
	for(i = 0;i < CONFIG_EPROM_SIZE;i ++){
		temp0 = (uint8_t)(rand() % 0xFF);
		crc16Write = crc16CalculateAdd(temp0);
		epromWriteByte(i, &temp0);
		wblock[(i % 32)] = temp0; 
	}
	crc16Clear();
	for(i = 0;i < CONFIG_EPROM_SIZE;i ++){
		epromReadByte(i, &temp1);
		crc16Read = crc16CalculateAdd(temp1);
		rblock[(i % 32)] = temp1;
	}
	if(crc16Read == crc16Write){
		printf("%s,%d,%s:byte sequential write pass!\r\n", __FILE__, __LINE__, __func__);
	}
	else{
		printf("%s,%d,%s:byte sequential wirte fail!\r\n", __FILE__, __LINE__, __func__);
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
			printf("%s,%d,%s:block sequential Write fail!\r\n", __FILE__, __LINE__, __func__);
			return false;
		}
	}
	temp0 = rand() % 0xFF;//��ȡ�������
	memset(wblock, temp0, sizeof(wblock));
	memset(rblock, 0x00, sizeof(rblock));
	epromWrite((CONFIG_EPROM_SIZE - remain), wblock, remain);
	epromRead((CONFIG_EPROM_SIZE - remain), rblock, remain);
	if(cmpByte(rblock, rblock, sizeof(rblock)) == false){
		printf("%s,%d,%s:block sequential Write fail!\r\n", __FILE__, __LINE__, __func__);
		return false;
	}
	printf("%s,%d,%s:block sequential Write pass!\r\n", __FILE__, __LINE__, __func__);
	//��64byteУ��
	for (i = (CONFIG_EPROM_SIZE - 64 - 1);i < CONFIG_EPROM_SIZE; i++){
		temp0 = rand() % 0xFF;//��ȡ�������
		epromWriteByte(i, &temp0);//д��
		epromReadByte(i, &temp1);//��ȡ
		if(temp0 != temp1){
			printf("%s,%d,%s:last 64byte random write fail!\r\n", __FILE__, __LINE__, __func__);
			return false;
		}
	}
	//���д��
	for(i=0;i<10000;i++){
		bk = rand() % CONFIG_EPROM_SIZE;//��ȡ�����ַ
		temp0 = rand() % 0xFF;//��ȡ�������
		epromWrite(bk, &temp0, 1);//д��
		epromRead(bk, &temp1, 1);//��ȡ
		if(temp0 != temp1){
			printf("%s,%d,%s:random write fail!\r\n", __FILE__, __LINE__, __func__);
			return false;
		}
	}
	printf("%s,%d,%s:random write pass!\r\n", __FILE__, __LINE__, __func__);
	return true;
}








