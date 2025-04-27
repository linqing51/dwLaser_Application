/*****************************************************************************/
#include "hmiLib.h"
/*****************************************************************************/
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart3;
/*****************************************************************************/
uint8_t dchmi_rxDat;
/*****************************************************************************/
void hmiUartInit(void){	
#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
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
	HAL_UART_Receive_IT(&huart4, &dchmi_rxDat, 1);
#endif

#if defined(MODEL_PVGLS_10W_1940_A1)
  huart3.Instance = USART3;
  huart3.Init.BaudRate = CONFIG_GDDC_UART_BAUDRATE;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK){
    Error_Handler();
  }
	HAL_UART_Receive_IT(&huart3, &dchmi_rxDat, 1);
#endif

	printf("%s,%d,%s:start hmi uart init......\n",__FILE__, __LINE__, __func__);
}
void hmiUartSendChar(uint8_t sdat){
	HAL_StatusTypeDef ret;
#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
	ret = HAL_UART_Transmit(&huart4, &sdat, 1, 1000);//·¢ËÍÒ»¸ö×Ö½Ú
#endif
#if defined(MODEL_PVGLS_10W_1940_A1)
	ret = HAL_UART_Transmit(&huart3, &sdat, 1, 1000);//·¢ËÍÒ»¸ö×Ö½Ú
#endif
	if(ret != HAL_OK){
		printf("%s,%d,%s:hmi uart tx timeout!!!!\n",__FILE__, __LINE__, __func__);
	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
	if(huart->Instance == UART4){//´¥ÃþÆÁ´®¿Ú
		queue_push(dchmi_rxDat);
		HAL_UART_Receive_IT(&huart4, &dchmi_rxDat, 1);
	}	
#endif

#if defined(MODEL_PVGLS_10W_1940_A1)
	if(huart->Instance == USART3){//´¥ÃþÆÁ´®¿Ú
		queue_push(dchmi_rxDat);
		HAL_UART_Receive_IT(&huart3, &dchmi_rxDat, 1);
	}	
#endif

}
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart){
#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
	if(huart->Instance == UART4){//´¥ÃþÆÁ´®¿Ú
		queue_push(dchmi_rxDat);
		HAL_UART_Receive_IT(&huart4, &dchmi_rxDat, 1);
	}	
#endif
#if defined(MODEL_PVGLS_10W_1940_A1)
	if(huart->Instance == USART3){//´¥ÃþÆÁ´®¿Ú
		queue_push(dchmi_rxDat);
		HAL_UART_Receive_IT(&huart3, &dchmi_rxDat, 1);
	}	
#endif
}
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){
#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
	if(huart->Instance == UART4){
		HAL_UART_Receive_IT(&huart4, &dchmi_rxDat, 1);
	}
#endif
#if defined(MODEL_PVGLS_10W_1940_A1)
	if(huart->Instance == USART3){
		HAL_UART_Receive_IT(&huart3, &dchmi_rxDat, 1);
	}
#endif
}

/*****************************************************************************/
