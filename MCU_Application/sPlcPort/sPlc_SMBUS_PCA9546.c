#include "sPlc_SMBUS.h"
/*****************************************************************************/
// PCA9546 I2C 设备地址（A0/A1/A2接地，7位地址0x70，HAL库左移1位）
#define PCA9546_DEV_ADDR    0x70 << 1  // 最终通信地址：0xE0




HAL_StatusTypeDef PCA9546_HardwareReset(void){//PCA9546硬件复位（低电平复位，延时后释放）
	// 拉低复位引脚（触发复位）
	PCA9546_RESET_LOW();
	HAL_Delay(10); // 延时10ms，确保芯片完成复位（根据手册要求）	
	// 释放复位引脚
	PCA9546_RESET_HIGH();
	HAL_Delay(5);  // 延时5ms，等待芯片稳定
	return HAL_OK;
}


void PCA9546_Reset_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 使能GPIOH时钟
    __HAL_RCC_GPIOD_CLK_ENABLE();

		GPIO_InitStruct.Pin = PCA9546_RESET_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(PCA9546_RESET_GPIO_Port, &GPIO_InitStruct);

    // 初始状态：复位引脚置高（芯片正常工作）
    PCA9546_RESET_HIGH();
}



HAL_StatusTypeDef PCA9546_Init(void){//PCA9546整体初始化（先复位引脚初始化→硬件复位→通道复位）
	// 1. 初始化复位引脚
	PCA9546_Reset_GPIO_Init();
	
	// 2. 硬件复位芯片
	PCA9546_HardwareReset();
	
	// 3. 复位通道（关闭所有通道）
	return PCA9546_SelectChannel(PCA9546_CHANNEL_NONE);
}

HAL_StatusTypeDef PCA9546_SelectChannel(uint8_t channel){//选择PCA9546的指定通道
	// 检查通道参数合法性（仅低4位有效）
	if((channel & 0xF0) != 0){
		return HAL_ERROR;
	}
	// I2C写入1字节控制码（A0/A1/A2接地，地址0xE0）
	return HAL_I2C_Master_Transmit(&hi2c2, PCA9546_DEV_ADDR, &channel, 1, 100);
}

HAL_StatusTypeDef PCA9546_ReadChannel(uint8_t *pChannel){//读取PCA9546当前选中的通道
	if(pChannel == NULL){
		return HAL_ERROR;
	}
	// I2C读取1字节通道状态
	return HAL_I2C_Master_Receive(&hi2c2, PCA9546_DEV_ADDR, pChannel, 1, 100);
}





