/*****************************************************************************/
#include "hmiUserUart.h"
#include "stdio.h"
/*****************************************************************************/
extern UART_HandleTypeDef huart4;
/*****************************************************************************/
uint8_t uart4_rxDat;
/*****************************************************************************/
void hmiUartInit(void){
	HAL_UART_Receive_IT(&huart4, &uart4_rxDat, 1);
	printf("%s,%d,%s:start hmi uart init......\n",__FILE__, __LINE__, __func__);
}
void hmiUartSendChar(uint8_t sdat){
	HAL_StatusTypeDef ret;
	ret = HAL_UART_Transmit(&huart4, &sdat, 1, 1000);//发送一个字节
	if(ret != HAL_OK){
		printf("%s,%d,%s:hmi uart tx timeout!!!!\n",__FILE__, __LINE__, __func__);
	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart == &huart4){//触摸屏串口
		queue_push(uart4_rxDat);
	}
	HAL_UART_Receive_IT(&huart4, &uart4_rxDat, 1);
}
/*****************************************************************************/
