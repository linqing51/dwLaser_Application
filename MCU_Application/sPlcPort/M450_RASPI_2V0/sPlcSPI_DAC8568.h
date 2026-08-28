#ifndef __DAC8568_H
#define __DAC8568_H

#include "stm32f4xx_hal.h"  // 根据你的STM32型号修改，如f1xx/f7xx等
/************************** 通道定义 **************************/
typedef enum {
    DAC8568_CH_A = 0x0,  // 通道A
    DAC8568_CH_B = 0x1,  // 通道B
    DAC8568_CH_C = 0x2,  // 通道C
    DAC8568_CH_D = 0x3,  // 通道D
    DAC8568_CH_E = 0x4,  // 通道E
    DAC8568_CH_F = 0x5,  // 通道F
    DAC8568_CH_G = 0x6,  // 通道G
    DAC8568_CH_H = 0x7,  // 通道H
    DAC8568_CH_ALL = 0xF // 所有通道
} DAC8568_ChannelDef;

/************************** 命令定义 **************************/
typedef enum {
    DAC8568_CMD_WRITE_INPUT_REG      = 0x0,  // 写入输入寄存器（无更新）
    DAC8568_CMD_UPDATE_DAC_REG       = 0x1,  // 更新DAC寄存器（从输入寄存器）
    DAC8568_CMD_WRITE_INPUT_REG_UPDATE_ALL = 0x2,  // 写入输入寄存器并更新所有DAC
    DAC8568_CMD_WRITE_INPUT_REG_UPDATE_CH  = 0x3,  // 写入输入寄存器并更新指定DAC
    DAC8568_CMD_POWER_DOWN_UP        = 0x4,  // 掉电/上电控制
    DAC8568_CMD_HW_LDAC_MASK         = 0x5,  // 硬件LDAC屏蔽控制
    DAC8568_CMD_SW_RESET             = 0x6,  // 软件复位
    DAC8568_CMD_SW_LDAC              = 0x7,  // 软件LDAC
    DAC8568_CMD_READ_BACK            = 0x8   // 读回寄存器（仅输入寄存器）
} DAC8568_CmdDef;

/****************************DAC8568命令************************/

#define POWER_DOWN_INTERNAL_REFERENCE 0

#define POWER_UP 1

#define DAC8568_RESET 2


/************************** 函数声明 **************************/
void Delay_us(uint32_t us);
void DAC8568_Init(void);
void DAC8568_SPI_SendByte(uint8_t byte);
void DAC8568_Send32BitData(DAC8568_CmdDef cmd, DAC8568_ChannelDef ch, uint16_t data);
void DAC8568_SetChannelVoltage(DAC8568_ChannelDef ch, uint16_t data);
void DAC8568_ClearAllChannels(void);
void DAC8568_SoftReset(void);





#endif /* __DAC8568_H */

