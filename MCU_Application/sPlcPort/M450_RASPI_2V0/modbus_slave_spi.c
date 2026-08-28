#include "modbus_slave_spi.h"
#include "boardConfig.h"
#include "main.h"


// 外部句柄（CubeMX生成）
extern SPI_HandleTypeDef hspi2;
extern DMA_HandleTypeDef hdma_spi2_rx;
extern DMA_HandleTypeDef hdma_spi2_tx;

// 全局变量
//SPI_PINGPONG_Typedef spi_slave_buf;
//uint8_t spi_bus_busy = 0;
//uint32_t spi_tick_timeout = 0;



//uint8_t spi_rx_buf[SPI_BUFFER_SIZE];
//uint8_t spi_tx_buf[SPI_BUFFER_SIZE];
//uint16_t spi2_rx_len = 0;
//uint16_t spi2_tx_len = 0;
//uint16_t Holding_Regs[HOLDING_REG_NUM];

// Modbus 功能码
#define READ_HOLDING_REG         0x03
#define WRITE_SINGLE_REG         0x06
#define WRITE_MULTI_REG          0x10

#define  FRAME_TIMEOUT_US  10

uint8_t spi_tx_buffer[SPI_TX_BUF_LEN] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
                                          0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10};
SPI_Slave_TxStateTypeDef spi_slave_tx_state = SPI_SLAVE_TX_IDLE;

// DMA接收缓冲区：存主机下发命令
uint8_t spi_rx_cmd_buf[SPI_RX_CMD_LEN] = {0};
// DMA发送应答缓冲区：解析命令后填充应答数据
uint8_t spi_tx_resp_buf[SPI_TX_RESP_LEN] = {0};



extern uint16_t spi2_tx_len;
//uint16_t recv_crc;
//uint16_t calc_crc;


SPI2_SlaveState_t g_spi2_state = SPI2_STATE_IDLE;
uint16_t   g_spi2_rx_len = 0;
uint8_t    *g_rx_buf_ptr  = NULL;
uint8_t    *g_tx_buf_ptr  = NULL;


SPI_SLAVE_STATE_t spi_slave_state = SPI_SLAVE_STATE_IDLE;












// ===================== CRC16 校验 =====================
uint16_t Modbus_CRC16(uint8_t *buf, uint16_t len)
{
    uint16_t crc = 0xFFFF;
    for(uint16_t i=0; i<len; i++){
        crc ^= buf[i];
        for(uint8_t j=0; j<8; j++){
            if(crc & 1){ crc >>=1; crc ^=0xA001; }
            else crc >>=1;
        }
    }
    return crc;
}

// ===================== SPI 接收完成回调 =====================
//void Modbus_SPI_RxCplt_Callback(void)
//{
//    // 继续接收下一个字节
//    HAL_SPI_Receive_IT(hspi_modbus, spi_rx_buf, 1);

//    // 帧结束判断（SPI空闲>2.5T即Modbus帧间隔）
//    // 这里简化：收到完整帧后直接处理
////    Modbus_Process_Frame();
//}

// ===================== 处理Modbus帧 =====================
//void Modbus_Process_Frame(void)
//{
//    uint8_t slave_addr = spi_rx_buf[0];
//    uint8_t func_code  = spi_rx_buf[1];

//    // 1. 校验从站地址
//    if(slave_addr != MODBUS_SLAVE_ADDR) return;

//    // 2. 校验CRC
//    recv_crc = (spi_rx_buf[spi2_rx_len-1] << 8) | spi_rx_buf[spi2_rx_len-2];
//    calc_crc = Modbus_CRC16(spi_rx_buf, spi2_rx_len-2);
//    if(recv_crc != calc_crc) return;

//    uint16_t resp_len = 0;
//    memset(spi_tx_buf, 0, spi2_rx_len);

//    // ===================== 读保持寄存器 =====================
//    if(func_code == READ_HOLDING_REG)
//    {
//        uint16_t reg_addr = (spi_rx_buf[2]<<8) | spi_rx_buf[3];
//        uint16_t reg_num  = (spi_rx_buf[4]<<8) | spi_rx_buf[5];

//        spi_tx_buf[0] = slave_addr;
//        spi_tx_buf[1] = func_code;
//        spi_tx_buf[2] = reg_num * 2;
//        resp_len = 3;

////        for(int i=0; i<reg_num; i++){
////            spi_tx_buf[resp_len++] = (Holding_Regs[reg_addr+i] >> 8) & 0xFF;
////            spi_tx_buf[resp_len++] = Holding_Regs[reg_addr+i] & 0xFF;
////        }

//        for(int i=0; i<reg_num; i++){
//            spi_tx_buf[resp_len++] = i;
//            spi_tx_buf[resp_len++] = i;
//        }



//    }

//    // ===================== 写单个寄存器 =====================
//    else if(func_code == WRITE_SINGLE_REG)
//    {
//        uint16_t reg_addr = (spi_rx_buf[2]<<8) | spi_rx_buf[3];
//        uint16_t reg_val  = (spi_rx_buf[4]<<8) | spi_rx_buf[5];

//        Holding_Regs[reg_addr] = reg_val;
//        memcpy(spi_tx_buf, spi_rx_buf, 6);
//        resp_len = 6;
//    }

//    // ===================== 写多个寄存器 =====================
//    else if(func_code == WRITE_MULTI_REG)
//    {
//        uint16_t reg_addr = (spi_rx_buf[2]<<8) | spi_rx_buf[3];
//        uint16_t reg_num  = (spi_rx_buf[4]<<8) | spi_rx_buf[5];

//        for(int i=0; i<reg_num; i++){
//            Holding_Regs[reg_addr+i] = (spi_rx_buf[7+i*2]<<8) | spi_rx_buf[8+i*2];
//        }
//        memcpy(spi_tx_buf, spi_rx_buf, 6);
//        resp_len = 6;
//    }

//    // 加入CRC
//    uint16_t resp_crc = Modbus_CRC16(spi_tx_buf, resp_len);
//    spi_tx_buf[resp_len++] = resp_crc & 0xFF;
//    spi_tx_buf[resp_len++] = (resp_crc >> 8) & 0xFF;
//    spi_tx_buf[resp_len] = 0x00;

//		spi2_tx_len = resp_len;
//}
