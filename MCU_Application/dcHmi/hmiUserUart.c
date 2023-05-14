/*****************************************************************************/
#include "hmiLib.h"
/*****************************************************************************/
extern UART_HandleTypeDef huart4;
/*****************************************************************************/
uint8_t uart4_rxDat;
/*****************************************************************************/
void hmiUartInit(void){	
//  huart4.Instance = UART4;
//  huart4.Init.BaudRate = CONFIG_GDDC_UART_BAUDRATE;
//  huart4.Init.WordLength = UART_WORDLENGTH_8B;
//  huart4.Init.StopBits = UART_STOPBITS_1;
//  huart4.Init.Parity = UART_PARITY_NONE;
//  huart4.Init.Mode = UART_MODE_TX_RX;
//  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
//  if (HAL_UART_Init(&huart4) != HAL_OK){
//    Error_Handler();
//  }
	HAL_UART_Receive_IT(&huart4, &uart4_rxDat, 1);
	printf("%s,%d,%s:start hmi uart init......\n",__FILE__, __LINE__, __func__);
}
void hmiUartSendChar(uint8_t sdat){
	HAL_StatusTypeDef ret;
	ret = HAL_UART_Transmit(&huart4, &sdat, 1, 1000);//·¢ËÍÒ»¸ö×Ö½Ú
	if(ret != HAL_OK){
		printf("%s,%d,%s:hmi uart tx timeout!!!!\n",__FILE__, __LINE__, __func__);
	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == UART4){//´¥ÃþÆÁ´®¿Ú
		queue_push(uart4_rxDat);
		HAL_UART_Receive_IT(&huart4, &uart4_rxDat, 1);
	}	
}
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == UART4){//´¥ÃþÆÁ´®¿Ú
		queue_push(uart4_rxDat);
		HAL_UART_Receive_IT(&huart4, &uart4_rxDat, 1);
	}	
}
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == UART4){
		HAL_UART_Receive_IT(&huart4, &uart4_rxDat, 1);
	}
}

/*****************************************************************************/
