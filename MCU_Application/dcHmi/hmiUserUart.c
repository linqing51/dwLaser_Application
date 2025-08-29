/*****************************************************************************/
#include "hmiLib.h"
/*****************************************************************************/
uint8_t dchmi_rxDat;
/*****************************************************************************/
void hmiUartInit(void){	
  CONFIG_GDDC_UART.Init.BaudRate = CONFIG_GDDC_UART_BAUDRATE;
  CONFIG_GDDC_UART.Init.WordLength = UART_WORDLENGTH_8B;
  CONFIG_GDDC_UART.Init.StopBits = UART_STOPBITS_1;
  CONFIG_GDDC_UART.Init.Parity = UART_PARITY_NONE;
  CONFIG_GDDC_UART.Init.Mode = UART_MODE_TX_RX;
  CONFIG_GDDC_UART.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  CONFIG_GDDC_UART.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&CONFIG_GDDC_UART) != HAL_OK){
    Error_Handler();
  }
	HAL_UART_Receive_IT(&CONFIG_GDDC_UART, &dchmi_rxDat, 1);
	printf("%s,%d,%s:start hmi uart init......\n",__FILE__, __LINE__, __func__);
}

void hmiUartSendChar(uint8_t sdat){
	HAL_StatusTypeDef ret;
	ret = HAL_UART_Transmit(&CONFIG_GDDC_UART, &sdat, 1, 1000);//发送一个字节
	if(ret != HAL_OK){
		printf("%s,%d,%s:hmi uart tx timeout!!!!\n",__FILE__, __LINE__, __func__);
	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == CONFIG_GDDC_UART_INSTANCE){//触摸屏串口
		queue_push(dchmi_rxDat);
		HAL_UART_Receive_IT(&CONFIG_GDDC_UART, &dchmi_rxDat, 1);
	}	
}
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == CONFIG_GDDC_UART_INSTANCE){//触摸屏串口
		queue_push(dchmi_rxDat);
		HAL_UART_Receive_IT(&CONFIG_GDDC_UART, &dchmi_rxDat, 1);
	}	
}
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == CONFIG_GDDC_UART_INSTANCE){
		HAL_UART_Receive_IT(&CONFIG_GDDC_UART, &dchmi_rxDat, 1);
	}
}
void hmiUartErrorReset(void){
	//检测串口发生错误重新启动接收
	if(CONFIG_GDDC_UART.RxState == HAL_UART_STATE_READY){
		HAL_UART_Receive_IT(&CONFIG_GDDC_UART, &dchmi_rxDat, 1);
	}
}


