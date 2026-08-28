#include "main.h"
#include "sPlc.h"
#include "boardConfig.h"
#include "sPlcSPI_LCM3000.h"


/**
 * @brief 软件SPI发送8bit  Mode0 MSB First
 */
static void TPL_SPI_Write8(uint8_t dat)
{
    uint8_t i,j;
    TPL0501_CS_L();
    Delay_us(1);
		j = 0x80;
    for(i = 0; i < 8; i++)
    {
        if((dat & j) == 0x00)
            TPL0501_DIN_L();
        else
            TPL0501_DIN_H();
        j = j >> 1;
        Delay_us(1);
        TPL0501_SCK_H();
        // 通信不稳定打开延时：HAL_Delay_us(1);
        Delay_us(1);
        TPL0501_SCK_L();
    }
    TPL0501_CS_H();
    Delay_us(1000);
}


void TPL0501_SetWiper(uint8_t pos)
{
    TPL_SPI_Write8(pos);
}
