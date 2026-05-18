#include "sPlc.h"
#include "sPlcEprom.h"
/*****************************************************************************/
#if (CONFIG_EPROM_IIC == 1)
static __forceinline bool I2C_WaitFlag(I2C_TypeDef* I2Cx, uint32_t flag, uint32_t timeout);// 等待I2C标志位的超时函数
static __forceinline void I2C_ReleaseBus(I2C_TypeDef* I2Cx, GPIO_TypeDef* SDA_GPIO, uint16_t SDA_Pin, GPIO_TypeDef* SCL_GPIO, uint16_t SCL_Pin);

__forceinline HAL_StatusTypeDef epromReadByte(uint32_t ReadAddr, uint8_t *rdat){//在指定地址读出8位数据
//ReadAddr:开始读数的地址  
//返回值  :数据  
	HAL_StatusTypeDef ret;
	if(ReadAddr > (CONFIG_EPROM_SIZE - 1)){//写地址超过容量
		ret = HAL_ERROR;
		return ret;
	}	
	ret = HAL_I2C_Mem_Read(&CONFIG_EPROM_BUS_HANDLE, CONFIG_EPROM_READ_ADDR, ReadAddr, I2C_MEMADD_SIZE_16BIT, (uint8_t*)(rdat), 1, CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
		if(!I2C_WaitFlag(CONFIG_EPROM_BUS, I2C_SR1_TXE, 100)) { // 检测到超时（锁死）
			ret = HAL_I2C_DeInit(&CONFIG_EPROM_BUS_HANDLE);//释放IO口为GPIO，复位句柄状态标志
			I2C_ReleaseBus(CONFIG_EPROM_BUS, EPROM_SDA_GPIO_Port, EPROM_SDA_Pin, EPROM_SCL_GPIO_Port, EPROM_SCL_Pin); //释放总线
			ret = HAL_I2C_Init(&CONFIG_EPROM_BUS_HANDLE);//这句重新初始化I2C控制器
		}
	}
	return ret;
}
__forceinline HAL_StatusTypeDef epromReadHword(uint32_t ReadAddr, uint16_t *rdat){//在指定地址开始读出16位数
//该函数用于读出16bit或者32bit的数据.
//ReadAddr   :开始读出的地址 
//返回值     :数据  	
	HAL_StatusTypeDef ret;
	if((ReadAddr + 1) > (CONFIG_EPROM_SIZE - 1)){//写地址超过容量
		ret = HAL_ERROR;
		return ret;
	}	
	ret = HAL_I2C_Mem_Read(&CONFIG_EPROM_BUS_HANDLE, CONFIG_EPROM_READ_ADDR, ReadAddr, I2C_MEMADD_SIZE_16BIT, (uint8_t*)(rdat), 2, CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
		if(!I2C_WaitFlag(CONFIG_EPROM_BUS, I2C_SR1_TXE, 100)) {//检测到超时（锁死）
			ret = HAL_I2C_DeInit(&CONFIG_EPROM_BUS_HANDLE);//释放IO口为GPIO，复位句柄状态标志
			I2C_ReleaseBus(CONFIG_EPROM_BUS, EPROM_SDA_GPIO_Port, EPROM_SDA_Pin, EPROM_SCL_GPIO_Port, EPROM_SCL_Pin); //释放总线
			ret = HAL_I2C_Init(&CONFIG_EPROM_BUS_HANDLE);//这句重新初始化I2C控制器
		}
	}
	return ret;
}
__forceinline HAL_StatusTypeDef epromReadDword(uint32_t ReadAddr, uint32_t *rdat){////在指定地址开始读出32位数
//该函数用于读出32bit的数据.
//ReadAddr   :开始读出的地址 
//返回值     :数据  	
	HAL_StatusTypeDef ret;	
	if((ReadAddr + 3) > (CONFIG_EPROM_SIZE - 1)){//写地址超过容量
		ret = HAL_ERROR;
		return ret;
	}	
	ret = HAL_I2C_Mem_Read(&CONFIG_EPROM_BUS_HANDLE, CONFIG_EPROM_READ_ADDR, ReadAddr, I2C_MEMADD_SIZE_16BIT, (uint8_t*)(rdat), 4, CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
		if(!I2C_WaitFlag(CONFIG_EPROM_BUS, I2C_SR1_TXE, 100)) { // 检测到超时（锁死）
			ret = HAL_I2C_DeInit(&CONFIG_EPROM_BUS_HANDLE);//释放IO口为GPIO，复位句柄状态标志
			I2C_ReleaseBus(CONFIG_EPROM_BUS, EPROM_SDA_GPIO_Port, EPROM_SDA_Pin, EPROM_SCL_GPIO_Port, EPROM_SCL_Pin); //释放总线
			ret = HAL_I2C_Init(&CONFIG_EPROM_BUS_HANDLE);//这句重新初始化I2C控制器
		}
	}
	return ret;
}
__forceinline HAL_StatusTypeDef epromWriteByte(uint32_t WriteAddr, uint8_t *wdat){//在指定地址写入8位数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据
	HAL_StatusTypeDef ret;
	if(WriteAddr > (CONFIG_EPROM_SIZE - 1)){//写地址超过容量
		ret = HAL_ERROR;
		return ret;
	}
	ret = HAL_I2C_Mem_Write(&CONFIG_EPROM_BUS_HANDLE, CONFIG_EPROM_WRITE_ADDR, WriteAddr, I2C_MEMADD_SIZE_16BIT, (uint8_t*)(wdat), 1, CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
		if(!I2C_WaitFlag(CONFIG_EPROM_BUS, I2C_SR1_TXE, 100)) { // 检测到超时（锁死）
			ret = HAL_I2C_DeInit(&CONFIG_EPROM_BUS_HANDLE);//释放IO口为GPIO，复位句柄状态标志
			I2C_ReleaseBus(CONFIG_EPROM_BUS, EPROM_SDA_GPIO_Port, EPROM_SDA_Pin, EPROM_SCL_GPIO_Port, EPROM_SCL_Pin); //释放总线
			ret = HAL_I2C_Init(&CONFIG_EPROM_BUS_HANDLE);//这句重新初始化I2C控制器
		}
	}
	return ret;
}
__forceinline HAL_StatusTypeDef epromWriteHword(uint32_t WriteAddr, uint16_t *wdat){//在的指定地址开始写入16位数
//该函数用于写入16bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址
	HAL_StatusTypeDef ret;
	if((WriteAddr + 1) > (CONFIG_EPROM_SIZE - 1)){//写地址超过容量
		ret = HAL_ERROR;
		return ret;
	}
	ret = HAL_I2C_Mem_Write(&CONFIG_EPROM_BUS_HANDLE, CONFIG_EPROM_WRITE_ADDR, WriteAddr, I2C_MEMADD_SIZE_16BIT, (uint8_t*)(wdat), 2, CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
			if(!I2C_WaitFlag(CONFIG_EPROM_BUS, I2C_SR1_TXE, 100)) { // 检测到超时（锁死）
				ret = HAL_I2C_DeInit(&CONFIG_EPROM_BUS_HANDLE);//释放IO口为GPIO，复位句柄状态标志
				I2C_ReleaseBus(CONFIG_EPROM_BUS, EPROM_SDA_GPIO_Port, EPROM_SDA_Pin, EPROM_SCL_GPIO_Port, EPROM_SCL_Pin); //释放总线
				ret = HAL_I2C_Init(&CONFIG_EPROM_BUS_HANDLE);//这句重新初始化I2C控制器
			}
	}
	return ret;
}
__forceinline HAL_StatusTypeDef epromWriteDword(uint32_t WriteAddr, uint32_t *wdat){//在的指定地址开始写入32位数
//该函数用于写入32bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址
	HAL_StatusTypeDef ret;
	if((WriteAddr + 3) >= (CONFIG_EPROM_SIZE - 1)){//写地址超过容量
		ret = HAL_ERROR;
		return ret;
	}
	ret = HAL_I2C_Mem_Write(&CONFIG_EPROM_BUS_HANDLE, CONFIG_EPROM_WRITE_ADDR, WriteAddr, I2C_MEMADD_SIZE_16BIT, (uint8_t*)(wdat), 4, CONFIG_EPROM_TIMEOUT);
	if(ret != HAL_OK){
			if(!I2C_WaitFlag(CONFIG_EPROM_BUS, I2C_SR1_TXE, 100)) { // 检测到超时（锁死）
				ret = HAL_I2C_DeInit(&CONFIG_EPROM_BUS_HANDLE);//释放IO口为GPIO，复位句柄状态标志
				I2C_ReleaseBus(CONFIG_EPROM_BUS, EPROM_SDA_GPIO_Port, EPROM_SDA_Pin, EPROM_SCL_GPIO_Port, EPROM_SCL_Pin); //释放总线
				ret = HAL_I2C_Init(&CONFIG_EPROM_BUS_HANDLE);//这句重新初始化I2C控制器
			}
	}
	return ret;
}   
__forceinline HAL_StatusTypeDef epromRead(uint32_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead){//在的指定地址开始读出指定个数的数据
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
		ret = HAL_I2C_Mem_Read(&CONFIG_EPROM_BUS_HANDLE, CONFIG_EPROM_READ_ADDR, rAddr, I2C_MEMADD_SIZE_16BIT, rBuffer, CONFIG_EPROM_PAGE_SIZE, CONFIG_EPROM_TIMEOUT);
		if(ret != HAL_OK){
			if(!I2C_WaitFlag(CONFIG_EPROM_BUS, I2C_SR1_TXE, 100)) { // 检测到超时（锁死）
				ret = HAL_I2C_DeInit(&CONFIG_EPROM_BUS_HANDLE);//释放IO口为GPIO，复位句柄状态标志
				I2C_ReleaseBus(CONFIG_EPROM_BUS, EPROM_SDA_GPIO_Port, EPROM_SDA_Pin, EPROM_SCL_GPIO_Port, EPROM_SCL_Pin); //释放总线
				ret = HAL_I2C_Init(&CONFIG_EPROM_BUS_HANDLE);//这句重新初始化I2C控制器
			}
		}
		rAddr += CONFIG_EPROM_PAGE_SIZE;
		rBuffer += CONFIG_EPROM_PAGE_SIZE;
	}
	if(rByte != 0x0){
		ret = HAL_I2C_Mem_Read(&CONFIG_EPROM_BUS_HANDLE, CONFIG_EPROM_READ_ADDR, rAddr, I2C_MEMADD_SIZE_16BIT, rBuffer, rByte ,CONFIG_EPROM_TIMEOUT);
		if(ret != HAL_OK){
			if(!I2C_WaitFlag(CONFIG_EPROM_BUS, I2C_SR1_TXE, 100)) { // 检测到超时（锁死）
				ret = HAL_I2C_DeInit(&CONFIG_EPROM_BUS_HANDLE);//释放IO口为GPIO，复位句柄状态标志
				I2C_ReleaseBus(CONFIG_EPROM_BUS, EPROM_SDA_GPIO_Port, EPROM_SDA_Pin, EPROM_SCL_GPIO_Port, EPROM_SCL_Pin); //释放总线
				ret = HAL_I2C_Init(&CONFIG_EPROM_BUS_HANDLE);//这句重新初始化I2C控制器
			}
		}
	}
	return ret;	
}  
__forceinline HAL_StatusTypeDef epromWrite(uint32_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite){//在的指定地址开始写入指定个数的数据
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
		ret = HAL_I2C_Mem_Write(&CONFIG_EPROM_BUS_HANDLE, CONFIG_EPROM_WRITE_ADDR, wAddr, I2C_MEMADD_SIZE_16BIT, wBuffer, CONFIG_EPROM_PAGE_SIZE, CONFIG_EPROM_TIMEOUT);
		if(ret != HAL_OK){
			if(!I2C_WaitFlag(CONFIG_EPROM_BUS, I2C_SR1_TXE, 100)) { // 检测到超时（锁死）
				ret = HAL_I2C_DeInit(&CONFIG_EPROM_BUS_HANDLE);//释放IO口为GPIO，复位句柄状态标志
				I2C_ReleaseBus(CONFIG_EPROM_BUS, EPROM_SDA_GPIO_Port, EPROM_SDA_Pin, EPROM_SCL_GPIO_Port, EPROM_SCL_Pin); //释放总线
				ret = HAL_I2C_Init(&CONFIG_EPROM_BUS_HANDLE);//这句重新初始化I2C控制器
			}
		}
		wAddr += CONFIG_EPROM_PAGE_SIZE;
		wBuffer += CONFIG_EPROM_PAGE_SIZE;
#if CONFIG_EPROM_WRITE_DELAY > 0
		HAL_Delay(CONFIG_EPROM_WRITE_DELAY);
#endif
	}
	if(wByte != 0x0){		
		ret = HAL_I2C_Mem_Write(&CONFIG_EPROM_BUS_HANDLE, CONFIG_EPROM_WRITE_ADDR, wAddr, I2C_MEMADD_SIZE_16BIT, wBuffer, wByte, CONFIG_EPROM_TIMEOUT);
		if(ret != HAL_OK){
			if(!I2C_WaitFlag(CONFIG_EPROM_BUS, I2C_SR1_TXE, 100)) { // 检测到超时（锁死）
				ret = HAL_I2C_DeInit(&CONFIG_EPROM_BUS_HANDLE);//释放IO口为GPIO，复位句柄状态标志
				I2C_ReleaseBus(CONFIG_EPROM_BUS, EPROM_SDA_GPIO_Port, EPROM_SDA_Pin, EPROM_SCL_GPIO_Port, EPROM_SCL_Pin); //释放总线
				ret = HAL_I2C_Init(&CONFIG_EPROM_BUS_HANDLE);//这句重新初始化I2C控制器
			}
		}
	}
#if CONFIG_EPROM_WRITE_DELAY > 0
	HAL_Delay(CONFIG_EPROM_WRITE_DELAY);
#endif
	return ret;
}

static __forceinline bool I2C_WaitFlag(I2C_TypeDef* I2Cx, uint32_t flag, uint32_t timeout) {// 等待I2C标志位的超时函数
  uint32_t tickstart = HAL_GetTick();
  while (!(I2Cx->SR1 & flag)) {
    if ((HAL_GetTick() - tickstart) > timeout) {
      return false; // 超时
    }
  }
  return true;
}

static __forceinline void I2C_ReleaseBus(I2C_TypeDef* I2Cx, GPIO_TypeDef* SDA_GPIO, uint16_t SDA_Pin, GPIO_TypeDef* SCL_GPIO, uint16_t SCL_Pin){
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  // 1. 禁用I2C外设
  I2Cx->CR1 &= ~I2C_CR1_PE;
  
  // 2. 配置SDA/SCL为推挽输出，强制拉高
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // 推挽输出
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  
  // 配置SDA
  GPIO_InitStruct.Pin = SDA_Pin;
  HAL_GPIO_Init(SDA_GPIO, &GPIO_InitStruct);
  HAL_GPIO_WritePin(SDA_GPIO, SDA_Pin, GPIO_PIN_SET); // 输出高电平
  
  // 配置SCL
  GPIO_InitStruct.Pin = SCL_Pin;
  HAL_GPIO_Init(SCL_GPIO, &GPIO_InitStruct);
  HAL_GPIO_WritePin(SCL_GPIO, SCL_Pin, GPIO_PIN_SET); // 输出高电平
  
  // 3. 延时10us，确保总线释放
  HAL_Delay(1); 
  
  // 4. 恢复GPIO为I2C复用开漏模式
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD; // 复用开漏（I2C必需）
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C1; // 根据实际I2C外设选择AF功能（如I2C1对应AF4）
  
  // 恢复SDA
  GPIO_InitStruct.Pin = SDA_Pin;
  HAL_GPIO_Init(SDA_GPIO, &GPIO_InitStruct);
  
  // 恢复SCL
  GPIO_InitStruct.Pin = SCL_Pin;
  HAL_GPIO_Init(SCL_GPIO, &GPIO_InitStruct);
}

#endif











