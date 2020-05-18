/*****************************************************************************/
#include "hmiUserUart.h"
/*****************************************************************************/
extern UART_HandleTypeDef huart5;
extern uint8_t uart5_rxBuf[64];
/*****************************************************************************/
void hmiUartInit(void){
	HAL_UART_Receive_IT(&huart5, uart5_rxBuf, 1);
}
void hmiUartSendChar(uint8_t sdat){
	HAL_UART_Transmit(&huart5, &sdat, 1, 1000);//发送一个字节
}
/*****************************************************************************/
