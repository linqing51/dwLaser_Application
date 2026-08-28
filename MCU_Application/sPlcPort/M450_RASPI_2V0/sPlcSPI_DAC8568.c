#include "sPlcSPI_DAC8568.h"
#include "boardConfig.h"

extern uint32_t SystemCoreClock;



/************************** DAC8568指令定义 **************************/
// 写入并更新指定通道
#define DAC8568_CMD_WRITE_UPDATE_CH(x)  (0x00 + (x))
// 写入指定通道（不更新）
#define DAC8568_CMD_WRITE_CH(x)         (0x08 + (x))
// 更新指定通道
#define DAC8568_CMD_UPDATE_CH(x)        (0x10 + (x))
// 写入并更新所有通道
#define DAC8568_CMD_WRITE_UPDATE_ALL    0x18
// 软件复位
#define DAC8568_CMD_SOFT_RESET          0x20
// 电源控制
#define DAC8568_CMD_POWER_CTRL          0x28
// 清除（CLR）引脚功能配置
#define DAC8568_CMD_CLR_CTRL            0x30





/**
 * @brief  软件微秒阻塞延时，指定循环模板实现
 * @param  us: 需要延时的微秒数
 */
//static void Delay_us(uint32_t us)
void Delay_us(uint32_t us)
{
    volatile uint32_t counter;
    counter = (us * (SystemCoreClock / 1000000U));
    while (counter != 0U)
    {
        counter--;
    }
}


/************************** 公有函数 **************************/
/**
 * @brief 初始化 DAC8568 的所有引脚和初始状态
 * @param 无
 * @retval 无
 */
void DAC8568_Init(void)
{
    // 上电默认电平
    SET_DAC8568_SYNC(GPIO_PIN_SET);
    SET_DAC8568_SCK(GPIO_PIN_SET);
    SET_DAC8568_DOUT(GPIO_PIN_RESET);
    SET_DAC8568_CLR(GPIO_PIN_SET);

    DAC8568_SoftReset();
    HAL_Delay(2);

}

/**
 * @brief  模拟SPI发送一个字节（高位先行）
 * @param  byte: 要发送的字节
 * @retval 无
 */
void DAC8568_SPI_SendByte(uint8_t byte)
{
    uint8_t i;
    // 高位先发送
    for(i = 0; i < 8; i++)
    {
        SET_DAC8568_SCK(GPIO_PIN_SET);  // 时钟拉高，准备输出数据
        Delay_us(1);
        
        // 发送当前位
        if(byte & 0x80)
        {
            SET_DAC8568_DOUT(GPIO_PIN_SET);
        }
        else
        {
            SET_DAC8568_DOUT(GPIO_PIN_RESET);
        }
        
        SET_DAC8568_SCK(GPIO_PIN_RESET); // 时钟拉低，DAC采样数据
        Delay_us(1);
        byte <<= 1;         // 左移一位，准备下一位
    }
    SET_DAC8568_SCK(GPIO_PIN_SET);      // 发送完成后时钟拉高
}

/**
 * @brief  组装32bit数据并通过模拟SPI发送
 *         数据格式：[4bit 0][4bit cmd][4bit addr][16bit data][4bit 0]
 * @param  cmd: 命令字（4bit）
 * @param  ch: 通道地址（4bit）
 * @param  data: 16bit DAC数据
 * @retval 无
 */
void DAC8568_Send32BitData(DAC8568_CmdDef cmd, DAC8568_ChannelDef ch, uint16_t data)
{
    uint32_t tx_data = 0;
    
    // 组装32bit数据
    tx_data |= (0x0UL << 28);          // 前4bit：0
    tx_data |= ((uint32_t)cmd << 24);  // 4bit命令
    tx_data |= ((uint32_t)ch << 20);   // 4bit地址
    tx_data |= ((uint32_t)data << 4);  // 16bit数据
    tx_data |= 0x0UL;                  // 后4bit：0
    
    // 开始发送数据
    SET_DAC8568_SYNC(GPIO_PIN_RESET);  // 拉低SYNC，选通DAC
    Delay_us(1);
	
    // 分4个字节发送32bit数据（高位先行）
    DAC8568_SPI_SendByte((tx_data >> 24) & 0xFF); // 第1字节：0 + cmd
    DAC8568_SPI_SendByte((tx_data >> 16) & 0xFF); // 第2字节：addr + data高8位
    DAC8568_SPI_SendByte((tx_data >> 8) & 0xFF);  // 第3字节：data低8位
    DAC8568_SPI_SendByte(tx_data & 0xFF);         // 第4字节：0
    
    SET_DAC8568_SYNC(GPIO_PIN_SET); // 拉高SYNC，结束发送
    Delay_us(1);
}

/**
 * @brief  设置指定通道的DAC输出值（写入并立即更新）
 * @param  ch: 目标通道
 * @param  data: 16bit DAC数据（0~65535对应0~Vref）
 * @retval 无
 */
void DAC8568_SetChannelVoltage(DAC8568_ChannelDef ch, uint16_t data)
{
    // 命令：写入输入寄存器并更新指定通道
    DAC8568_Send32BitData(DAC8568_CMD_WRITE_INPUT_REG_UPDATE_CH, ch, data);
}

/**
 * @brief  清除所有DAC通道输出（置0）
 * @param  无
 * @retval 无
 */
void DAC8568_ClearAllChannels(void)
{
    SET_DAC8568_CLR(GPIO_PIN_RESET);   // 拉低CLR引脚
    HAL_Delay(1);                     // 保持低电平至少100ns（延时1ms确保稳定）
    SET_DAC8568_CLR(GPIO_PIN_SET);     // 拉高CLR引脚
}

/**
 * @brief  软件复位DAC8568
 * @param  无
 * @retval 无
 */
void DAC8568_SoftReset(void)
{
    // 发送软件复位命令，地址位无意义，数据位填0
    DAC8568_Send32BitData(DAC8568_CMD_SW_RESET, DAC8568_CH_ALL, 0x0000);
    HAL_Delay(1);
}










