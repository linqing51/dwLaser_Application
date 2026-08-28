#ifndef __MODBUS_SLAVE_SPI_H
#define __MODBUS_SLAVE_SPI_H

#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdint.h>

/* ========== 收发状态 ========== */
typedef enum {
    SPI2_STATE_IDLE = 0,      /* 空闲，可启动新一次收发 */
    SPI2_STATE_BUSY,           /* DMA 传输进行中 */
    SPI2_STATE_CPLT,           /* 本次传输完成（待应用读取） */
    SPI2_STATE_ERROR           /* 传输错误 */
} SPI2_SlaveState_t;

/* ========== 函数声明 ========== */
void SPI2_Slave_DMA_Init(void);                         /* 初始化 SPI2+DMA+GPIO+NVIC */




extern SPI2_SlaveState_t g_spi2_state;
extern uint16_t   g_spi2_rx_len;
extern uint8_t    *g_rx_buf_ptr;
extern uint8_t    *g_tx_buf_ptr;






// DMA发送缓冲区
#define SPI_TX_BUF_LEN 16U
extern uint8_t spi_tx_buffer[SPI_TX_BUF_LEN];

// 发送状态标记
typedef enum
{
  SPI_SLAVE_TX_IDLE    = 0,  // 空闲，可以启动下一次DMA发送
  SPI_SLAVE_TX_BUSY    = 1,  // DMA发送进行中
}SPI_Slave_TxStateTypeDef;

extern SPI_Slave_TxStateTypeDef spi_slave_tx_state;





//----------配置参数----------
#define SPI_RX_CMD_LEN     10U      // 主站下发命令长度：4字节命令帧
#define SPI_TX_RESP_LEN    10U      // 从站应答返回数据长度：8字节

// DMA接收缓冲区：存主机下发命令
extern uint8_t spi_rx_cmd_buf[SPI_RX_CMD_LEN];
// DMA发送应答缓冲区：解析命令后填充应答数据
extern uint8_t spi_tx_resp_buf[SPI_TX_RESP_LEN];

// 状态机
typedef enum
{
    SPI_SLAVE_STATE_IDLE,        // 空闲，等待主站下发命令
    SPI_SLAVE_STATE_RX_CMD,      // DMA接收主站命令中
    SPI_SLAVE_STATE_PARSE_CMD,   // 命令接收完成，解析命令
    SPI_SLAVE_STATE_TX_RESP,     // DMA发送应答给主站
}SPI_SLAVE_STATE_t;

extern SPI_SLAVE_STATE_t spi_slave_state;














// ===================== 配置 =====================
#define MODBUS_SLAVE_ADDR        0x01    // 从站地址（必须和树莓派一致）
#define HOLDING_REG_NUM          50      // 保持寄存器数量
#define SPI_BUFFER_SIZE          512     // SPI缓冲区大小

#define SPI2_FRAME_MAX_LEN   512



//// 通信参数统一配置
//#define SPI_MAX_PACKET_LEN      1024U       // 最大单包长度
//#define SPI_FRAME_HEAD          0xAAU       // 帧头
//#define SPI_FRAME_TAIL          0x55U       // 帧尾
//#define SPI_TIMEOUT_US          50U         // 传输超时时间
//#define SPI_CRC_ENABLE          1U          // 开启CRC校验

//// 乒乓缓存结构体
//typedef struct
//{
//    uint8_t bufA[SPI_MAX_PACKET_LEN];
//    uint8_t bufB[SPI_MAX_PACKET_LEN];
//    uint8_t *txBuf;
//    uint8_t *rxBuf;
//    uint16_t dataLen;
//    uint8_t bufSwitchFlag;   // 0:A缓存,1:B缓存
//}SPI_PINGPONG_Typedef;



// ===================== 外部函数 =====================

uint16_t Modbus_CRC16(uint8_t *buf, uint16_t len);


//void Modbus_Process_Frame(void);
void Modbus_SPI_RxCplt_Callback(void);  // SPI接收完成回调

//// 外部变量：保持寄存器
//extern uint16_t Holding_Regs[HOLDING_REG_NUM];


//extern uint8_t spi_rx_buf[SPI_BUFFER_SIZE];
//extern uint8_t spi_tx_buf[SPI_BUFFER_SIZE];
//extern uint16_t spi2_rx_len;
//extern uint16_t spi2_tx_len;
//extern TIM_HandleTypeDef htim3;










#endif
