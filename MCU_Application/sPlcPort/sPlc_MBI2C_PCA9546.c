#include "sPlc_MBI2C_PAC9546.h"
/*****************************************************************************/

/**
 * @brief  PCA9546硬件复位（低电平复位，延时后释放）
 * @param  无
 * @retval HAL_OK（复位完成）
 */
HAL_StatusTypeDef PCA9546_HardwareReset(void){
    // 拉低复位引脚（触发复位）
    PCA9546_RESET_LOW();
    HAL_Delay(10); // 延时10ms，确保芯片完成复位（根据手册要求）
    
    // 释放复位引脚
    PCA9546_RESET_HIGH();
    HAL_Delay(5);  // 延时5ms，等待芯片稳定
    
    return HAL_OK;
}

/**
 * @brief  PCA9546整体初始化（先复位引脚初始化→硬件复位→通道复位）
 * @param  无
 * @retval HAL状态码
 */
HAL_StatusTypeDef PCA9546_Init(void){
    // 1. 初始化复位引脚
    PCA9546_Reset_GPIO_Init();
    
    // 2. 硬件复位芯片
    PCA9546_HardwareReset();
    
    // 3. 复位通道（关闭所有通道）
    return PCA9546_SelectChannel(PCA9546_CHANNEL_NONE);
}

/**
 * @brief  选择PCA9546的指定通道
 * @param  channel: 通道宏（如PCA9546_CHANNEL_0）
 * @retval HAL状态码
 */
HAL_StatusTypeDef PCA9546_SelectChannel(uint8_t channel){
    // 检查通道参数合法性（仅低4位有效）
    if((channel & 0xF0) != 0)
    {
        return HAL_ERROR;
    }

    // I2C写入1字节控制码（A0/A1/A2接地，地址0xE0）
    return HAL_I2C_Master_Transmit(&hi2c3, PCA9546_DEV_ADDR, &channel, 1, 100);
}

/**
 * @brief  读取PCA9546当前选中的通道
 * @param  pChannel: 存储通道状态的指针
 * @retval HAL状态码
 */
HAL_StatusTypeDef PCA9546_ReadChannel(uint8_t *pChannel){
    if(pChannel == NULL)
    {
        return HAL_ERROR;
    }

    // I2C读取1字节通道状态
    return HAL_I2C_Master_Receive(&hi2c3, PCA9546_DEV_ADDR, pChannel, 1, 100);
}





