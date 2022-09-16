#include "sPlcModbus.h"
/*****************************************************************************/
extern UART_HandleTypeDef huart5;
uint8_t uart5_rxDat;
uint8_t uart6_rxDat;
/*****************************************************************************/
void modbusUartInit(uint32_t baudrate){
	huart5.Instance = UART5;
  huart5.Init.BaudRate = baudrate;
  huart5.Init.WordLength = UART_WORDLENGTH_8B;
  huart5.Init.StopBits = UART_STOPBITS_1;
  huart5.Init.Parity = UART_PARITY_NONE;
  huart5.Init.Mode = UART_MODE_TX_RX;
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart5.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart5) != HAL_OK)
  {
    Error_Handler();
  }
	HAL_UART_Receive_IT(&huart5, &uart5_rxDat, 1);
}

void modbusPutChar(uint8_t c){// This is used for send one character
	HAL_UART_Transmit(&huart5, &c, 1, 1000);
}
uint8_t modbusPutString(uint8_t *s, uint16_t  Length){// This is used for send string, better to use DMA for it ;)
    uint16_t DummyCounter;
    for(DummyCounter=0; DummyCounter < Length; DummyCounter ++){
        modbusPutChar(s[DummyCounter]);
    }
    return true;
}
void modbusGetChar(uint8_t Data){//Call this function into your UART Interrupt. Collect data from it!
    modbusReceiveBuffer[modbusReceiveCounter] = Data;
    modbusReceiveCounter ++;
    if(modbusReceiveCounter > CONFIG_MB_RX_BUFFER_SIZE){  
        modbusReceiveCounter = 0;
	}
	modbusTimerValue = 0;
}
