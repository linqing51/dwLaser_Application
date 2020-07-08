/*****************************************************************************/
#include "hmiUserUart.h"
/*****************************************************************************/
extern UART_HandleTypeDef huart5;
/*****************************************************************************/
uint8_t uart5_rxDat;
/*****************************************************************************/
void hmiUartInit(void){
	HAL_UART_Receive_IT(&huart5, &uart5_rxDat, 1);
}
void hmiUartSendChar(uint8_t sdat){
	HAL_StatusTypeDef ret;
	ret = HAL_UART_Transmit(&huart5, &sdat, 1, 1000);//发送一个字节
	if(ret != HAL_OK){
		__nop();
	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart == &huart5){//触摸屏串口
		queue_push(uart5_rxDat);
	}
	HAL_UART_Receive_IT(&huart5, &uart5_rxDat, 1);
}
/*****************************************************************************/
