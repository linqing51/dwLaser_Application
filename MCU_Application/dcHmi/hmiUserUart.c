/*****************************************************************************/
#include "hmiUserUart.h"
/*****************************************************************************/
extern UART_HandleTypeDef huart4;
/*****************************************************************************/
uint8_t uart4_rxDat;
/*****************************************************************************/
void hmiUartInit(void){
	HAL_UART_Receive_IT(&huart4, &uart4_rxDat, 1);
}
void hmiUartSendChar(uint8_t sdat){
	HAL_StatusTypeDef ret;
	ret = HAL_UART_Transmit(&huart4, &sdat, 1, 1000);//����һ���ֽ�
	if(ret != HAL_OK){
		__nop();
	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart == &huart4){//����������
		queue_push(uart4_rxDat);
	}
	HAL_UART_Receive_IT(&huart4, &uart4_rxDat, 1);
}
/*****************************************************************************/
