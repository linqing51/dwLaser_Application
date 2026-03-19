#include "hdc1080.h"
#include "delay.h"  // 需确保项目中有延时函数（如HAL_Delay）


hdc1080_TypeDef hdc1080_buf;


/************************模拟I2C底层实现************************/
/**
 * @brief  初始化模拟I2C引脚
 * @param  无
 * @retval 无
 */
void HDC1080_I2C_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 使能GPIO时钟（根据你选择的引脚修改）
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // 配置SCL引脚
    GPIO_InitStruct.Pin = HDC1080_I2C_SCL_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;  // 开漏输出
    GPIO_InitStruct.Pull = GPIO_PULLUP;          // 上拉
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(HDC1080_I2C_SCL_GPIO_PORT, &GPIO_InitStruct);

    // 配置SDA引脚
    GPIO_InitStruct.Pin = HDC1080_I2C_SDA_PIN;
    HAL_GPIO_Init(HDC1080_I2C_SDA_GPIO_PORT, &GPIO_InitStruct);

    // 初始化为高电平
    HDC1080_SCL_HIGH();
    HDC1080_SDA_HIGH();
}

/**
 * @brief  发送I2C起始信号
 * @param  无
 * @retval 无
 */
void HDC1080_I2C_Start(void)
{
    HDC1080_SDA_HIGH();
    HDC1080_SCL_HIGH();
    HAL_Delay(1);
    HDC1080_SDA_LOW();  // SDA在SCL高电平时拉低，产生起始信号
    HAL_Delay(1);
    HDC1080_SCL_LOW();  // 拉低SCL，准备发送数据
}

/**
 * @brief  发送I2C停止信号
 * @param  无
 * @retval 无
 */
void HDC1080_I2C_Stop(void)
{
    HDC1080_SDA_LOW();
    HDC1080_SCL_HIGH();
    HAL_Delay(1);
    HDC1080_SDA_HIGH(); // SDA在SCL高电平时拉高，产生停止信号
    HAL_Delay(1);
}

/**
 * @brief  等待从机应答
 * @param  无
 * @retval 0：应答成功  1：应答失败
 */
uint8_t HDC1080_I2C_WaitAck(void)
{
    uint8_t timeout = 0;

    HDC1080_SDA_HIGH();
    HAL_Delay(1);
    HDC1080_SCL_HIGH();
    HAL_Delay(1);

    // 等待SDA拉低（应答）
    while(HDC1080_SDA_READ())
    {
        timeout++;
        if(timeout > 250)
        {
            HDC1080_I2C_Stop();
            return 1;
        }
    }

    HDC1080_SCL_LOW();
    return 0;
}

/**
 * @brief  发送应答信号
 * @param  ack：0=应答  1=非应答
 * @retval 无
 */
void HDC1080_I2C_SendAck(uint8_t ack)
{
    HDC1080_SCL_LOW();
    if(ack) HDC1080_SDA_HIGH();
    else    HDC1080_SDA_LOW();
    HAL_Delay(1);

    HDC1080_SCL_HIGH();
    HAL_Delay(1);
    HDC1080_SCL_LOW();
    HDC1080_SDA_HIGH();
    HAL_Delay(1);
}

/**
 * @brief  发送一个字节
 * @param  data：要发送的字节
 * @retval 无
 */
void HDC1080_I2C_SendByte(uint8_t data)
{
    uint8_t i;

    HDC1080_SCL_LOW();
    for(i=0; i<8; i++)
    {
        // 发送最高位
        if(data & 0x80) HDC1080_SDA_HIGH();
        else            HDC1080_SDA_LOW();
        data <<= 1;
        HAL_Delay(1);

        HDC1080_SCL_HIGH();
        HAL_Delay(1);
        HDC1080_SCL_LOW();
        HAL_Delay(1);
    }
}

/**
 * @brief  读取一个字节
 * @param  ack：0=发送应答  1=发送非应答
 * @retval 读取到的字节
 */
uint8_t HDC1080_I2C_ReadByte(uint8_t ack)
{
    uint8_t i, data=0;

    HDC1080_SDA_HIGH();
    for(i=0; i<8; i++)
    {
        HDC1080_SCL_LOW();
        HAL_Delay(1);
        HDC1080_SCL_HIGH();

        data <<= 1;
        if(HDC1080_SDA_READ()) data |= 0x01;
        HAL_Delay(1);
    }

    HDC1080_I2C_SendAck(ack);
    return data;
}

/************************HDC1080核心驱动************************/
/**
 * @brief  初始化HDC1080
 * @param  无
 * @retval 0：成功  1：失败
 */
uint8_t HDC1080_Init(void)
{
    uint8_t config = 0x00;

    // 初始化模拟I2C
    HDC1080_I2C_Init();

    // 发送起始信号
    HDC1080_I2C_Start();
    // 发送设备地址+写命令
    HDC1080_I2C_SendByte(HDC1080_ADDR);
    if(HDC1080_I2C_WaitAck()) return 1;

    // 发送配置寄存器地址
    HDC1080_I2C_SendByte(HDC1080_CONFIG_REG);
    HDC1080_I2C_WaitAck();

    // 配置寄存器高字节（14位分辨率，同时测量温湿度）
    config = 0x10;  // BIT4=1：同时测量温度和湿度
    HDC1080_I2C_SendByte(config);
    HDC1080_I2C_WaitAck();

    // 配置寄存器低字节
    HDC1080_I2C_SendByte(0x00);
    HDC1080_I2C_WaitAck();

    // 发送停止信号
    HDC1080_I2C_Stop();

    HAL_Delay(15);  // 等待配置生效
    return 0;
}

/**
 * @brief  读取温湿度数据
 * @param  temp：温度值指针（单位：℃）
 * @param  humi：湿度值指针（单位：%RH）
 * @retval 无
 */
void HDC1080_Read_Temp_Humi(float *temp, float *humi)
{
    uint8_t buf[4];
    uint16_t temp_raw, humi_raw;

    // 发送起始信号
    HDC1080_I2C_Start();
    // 发送设备地址+写命令
    HDC1080_I2C_SendByte(HDC1080_ADDR);
    HDC1080_I2C_WaitAck();
    // 发送温度寄存器地址（触发测量）
    HDC1080_I2C_SendByte(HDC1080_TEMP_REG);
    HDC1080_I2C_WaitAck();
    // 发送停止信号
    HDC1080_I2C_Stop();

    HAL_Delay(20);  // 等待测量完成（HDC1080转换时间最大14ms）

    // 发送起始信号
    HDC1080_I2C_Start();
    // 发送设备地址+读命令
    HDC1080_I2C_SendByte(HDC1080_ADDR | 0x01);
    HDC1080_I2C_WaitAck();

    // 读取温度高字节
    buf[0] = HDC1080_I2C_ReadByte(0);
    // 读取温度低字节
    buf[1] = HDC1080_I2C_ReadByte(0);
    // 读取湿度高字节
    buf[2] = HDC1080_I2C_ReadByte(0);
    // 读取湿度低字节
    buf[3] = HDC1080_I2C_ReadByte(1);

    // 发送停止信号
    HDC1080_I2C_Stop();

    // 转换为实际温度和湿度
    temp_raw = ((uint16_t)buf[0] << 8) | buf[1];
    humi_raw = ((uint16_t)buf[2] << 8) | buf[3];

    *temp = (temp_raw / 65536.0) * 165.0 - 40.0;  // 温度计算公式
    *humi = (humi_raw / 65536.0) * 100.0;         // 湿度计算公式
}
