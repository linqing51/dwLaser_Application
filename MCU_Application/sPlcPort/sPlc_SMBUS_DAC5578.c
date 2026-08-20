#include "sPlc_SMBUS.h"
/*****************************************************************************/
// ADDR0 = GND  : 0x48 (1001000)
// ADDR0 = VDD  : 0x4A (1001010)
// ADDR0 = 悬空 : 0x4C (1001100)
#define DAC5578_DEV_ADDR    0x48U
#define DAC5578_WR_ADDR     (DAC5578_DEV_ADDR << 1U)
#define DAC5578_RD_ADDR     ((DAC5578_DEV_ADDR << 1U) | 0x01U)
#define DAC5578_I2C_TIMEOUT 100U
/************************* 私有宏 - 指令码（参考手册CA字节） *************************/
// 命令字节：C3 C2 C1 C0 + A3 A2 A1 A0
#define CMD_WRITE_IN_REG       0x00U    // 写入输入寄存器
#define CMD_WRITE_UPD_SINGLE  0x03U    // 写寄存器并立即更新单通道
#define CMD_WRITE_UPD_ALL     0x02U    // 写寄存器并全局更新所有通道
#define CMD_POWER_CTRL        0x04U    // 电源控制指令
#define CMD_SOFT_RESET        0x07U    // 软件复位指令
#define CMD_READ_IN_REG       0x80U    // 读取输入寄存器

// 通道地址偏移（A~H）
#define CH_ADDR_OFFSET(ch)    ((uint8_t)(ch & 0x07U))


#define CONFIG_MBI2C_BUS  hi2c2
/**
 * @brief  
 * @param  pBuf: 发送缓冲区
 * @param  len: 发送长度
 * @retval 执行状态
 */
static DAC5578_StatusTypeDef DAC5578_I2C_Write(uint8_t *pBuf, uint16_t len){//底层I2C写数据（私有函数）
	HAL_StatusTypeDef hal_sta;
	hal_sta = HAL_I2C_Master_Transmit(&CONFIG_MBI2C_BUS, DAC5578_WR_ADDR, pBuf, len, DAC5578_I2C_TIMEOUT);
	if(hal_sta == HAL_OK){
		return DAC5578_OK;
	}
	else if(hal_sta == HAL_TIMEOUT){
		return DAC5578_TIMEOUT;
	}
	else{
		return DAC5578_ERROR;
	}
}

static DAC5578_StatusTypeDef DAC5578_I2C_Read(uint8_t *pBuf, uint16_t len){//底层I2C读数据（私有函数）
	HAL_StatusTypeDef hal_sta;
	hal_sta = HAL_I2C_Master_Receive(&CONFIG_MBI2C_BUS, DAC5578_RD_ADDR, pBuf, len, DAC5578_I2C_TIMEOUT);
	if(hal_sta == HAL_OK){
		return DAC5578_OK;
	}
	else if(hal_sta == HAL_TIMEOUT){
		return DAC5578_TIMEOUT;
	}
	else{
		return DAC5578_ERROR;
	}
}

DAC5578_StatusTypeDef DAC5578_Init(void){//DAC5578 初始化
	// 1. I2C设备自检
	if(HAL_I2C_IsDeviceReady(&CONFIG_MBI2C_BUS, DAC5578_WR_ADDR, 2U, DAC5578_I2C_TIMEOUT) != HAL_OK){
		return DAC5578_ERROR;
	}
	// 2. 软件复位，恢复默认状态
	if(DAC5578_SoftReset() != DAC5578_OK){
		return DAC5578_ERROR;
	}
	return DAC5578_OK;
}

DAC5578_StatusTypeDef DAC5578_SetChannel(DAC5578_ChannelTypeDef ch, uint8_t data){//设置单通道输出
	uint8_t tx_buf[3] = {0U};
	uint8_t cmd;
	// 非法通道拦截
	if(ch > DAC5578_CH_H){
			return DAC5578_ERROR;
	}
	// 构造命令字节 + 数据（8位DAC：仅LSB有效，MSB填充无效位）
	cmd = CMD_WRITE_UPD_SINGLE | CH_ADDR_OFFSET(ch);
	tx_buf[0] = cmd;
	tx_buf[1] = 0x00U;   // MSB 无效位
	tx_buf[2] = data;    // LSB 有效DAC数据
	return DAC5578_I2C_Write(tx_buf, 3U);
}

/**
 * @brief  批量设置多通道
 */
DAC5578_StatusTypeDef DAC5578_SetMultiChannel(DAC5578_ChannelTypeDef ch, uint8_t *pData, uint8_t len){
	uint8_t tx_buf[25] = {0U};  // 最大8通道 *3字节 =24
	uint8_t i, cmd;
	if((ch + len - 1U) > DAC5578_CH_H || pData == NULL || len == 0U){
		return DAC5578_ERROR;
	}
	// 首包命令
	cmd = CMD_WRITE_IN_REG | CH_ADDR_OFFSET(ch);
	tx_buf[0] = cmd;
	tx_buf[1] = 0x00U;
	tx_buf[2] = pData[0];
	// 后续通道数据
	for(i = 1U; i < len; i++){
		tx_buf[i*2 + 1] = 0x00U;
		tx_buf[i*2 + 2] = pData[i];
	}
	return DAC5578_I2C_Write(tx_buf, (uint16_t)(len * 2U + 1U));
}

DAC5578_StatusTypeDef DAC5578_SetPowerMode(DAC5578_ChannelTypeDef ch, DAC5578_PowerModeTypeDef mode){//电源模式控制
	uint8_t tx_buf[3] = {0U};
	uint8_t ch_mask = 0U;

	if(mode > DAC5578_PWR_DOWN_HIZ){
		return DAC5578_ERROR;
	}

	// 构造通道掩码
	if(ch == DAC5578_CH_ALL){
		ch_mask = 0xFFU;  // 所有通道
	}
	else{
		ch_mask = (1U << ch);
	}
	// 电源控制指令 + PD1 PD0 模式位
	tx_buf[0] = CMD_POWER_CTRL;
	tx_buf[1] = ((uint8_t)mode << 6U) | ch_mask;
	tx_buf[2] = 0x00U;
	return DAC5578_I2C_Write(tx_buf, 3U);
}

DAC5578_StatusTypeDef DAC5578_SoftReset(void){//软件复位
	uint8_t tx_buf[3] = {0U};
	tx_buf[0] = CMD_SOFT_RESET;
	tx_buf[1] = 0x00U;
	tx_buf[2] = 0x00U;
	return DAC5578_I2C_Write(tx_buf, 3U);
}

DAC5578_StatusTypeDef DAC5578_ReadChannel(DAC5578_ChannelTypeDef ch, uint8_t *pData){//读取通道数值
	uint8_t tx_buf[1] = {0U};
	uint8_t rx_buf[2] = {0U};
	if(ch > DAC5578_CH_H || pData == NULL){
			return DAC5578_ERROR;
	}
	// 步骤1：发送读寄存器命令
	tx_buf[0] = CMD_READ_IN_REG | CH_ADDR_OFFSET(ch);
	if(DAC5578_I2C_Write(tx_buf, 1U) != DAC5578_OK){
			return DAC5578_ERROR;
	}
	// 步骤2：读取2字节数据（8位DAC 有效数据在LSB）
	if(DAC5578_I2C_Read(rx_buf, 2U) != DAC5578_OK){
			return DAC5578_ERROR;
	}
	*pData = rx_buf[1];
	return DAC5578_OK;
}
