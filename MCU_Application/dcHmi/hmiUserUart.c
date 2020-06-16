/*****************************************************************************/
#include "hmiUserUart.h"
/*****************************************************************************/
extern UART_HandleTypeDef huart5;
/*****************************************************************************/
uint8_t gddcHmiRxBuf[256];
/*****************************************************************************/
void hmiUartInit(void){
	HAL_UART_Receive_IT(&huart5, gddcHmiRxBuf, 1);
}
void hmiUartSendChar(uint8_t sdat){
	HAL_StatusTypeDef ret;
	ret = HAL_UART_Transmit(&huart5, &sdat, 1, 1000);//发送一个字节
	if(ret != HAL_OK){
		__nop();
	}
}
/*****************************************************************************/
