/*
 * FreeRTOS Kernel V10.2.1
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/*
	BASIC INTERRUPT DRIVEN SERIAL PORT DRIVER FOR UART0.
*/

/* Demo application includes. */
#include "CLISerial.h"


/*-----------------------------------------------------------*/

/* Misc defines. */
#define serINVALID_QUEUE				( ( QueueHandle_t ) 0 )
#define serNO_BLOCK						( ( TickType_t ) 0 )
#define serTX_BLOCK_TIME				( 40 / portTICK_PERIOD_MS )

/*-----------------------------------------------------------*/

/* The queue used to hold received characters. */
static QueueHandle_t xRxedChars;
static QueueHandle_t xCharsForTx;

/*-----------------------------------------------------------*/

/* UART interrupt handler. */
void vUARTInterruptHandler( void );

/*-----------------------------------------------------------*/
extern UART_HandleTypeDef huart5;
DMA_HandleTypeDef hdma_uart5_rx;


#define CONFIG_DEBUG_UART											huart1//调试串口
#define CONFIG_GDDC_UART											huart2//GDDC串口
#define CONFIG_GDDC_UART_INSTANCE							USART2//GDDC串口中断



uint8_t UART5_Rx_Buf[USART5_RX_BUF_SIZE];
uint16_t UART5_Rx_Len = 0;



#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 




#endif


void xUsart5Init(uint32_t BaudRate)
{
    /* 1. 开启时钟 */
    __HAL_RCC_UART5_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();  // UART5 RX DMA 属于 DMA1 流5 通道4

    /* 2. GPIO 初始化：TX=PC12, RX=PD2 */
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;  // RX 上拉
    GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* 3. DMA 接收配置 */
    hdma_uart5_rx.Instance = DMA1_Stream5;
    hdma_uart5_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_uart5_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_uart5_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_uart5_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_uart5_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_uart5_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_uart5_rx.Init.Mode = DMA_NORMAL;
    hdma_uart5_rx.Init.Priority = DMA_PRIORITY_MEDIUM;
    hdma_uart5_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_uart5_rx) != HAL_OK)
    {
//        Error_Handler();
    }
    __HAL_LINKDMA(&huart5, hdmarx, hdma_uart5_rx);

    /* 4. UART5 初始化 */
    huart5.Instance = UART5;
    huart5.Init.BaudRate = BaudRate;
    huart5.Init.WordLength = UART_WORDLENGTH_8B;
    huart5.Init.StopBits = UART_STOPBITS_1;
    huart5.Init.Parity = UART_PARITY_NONE;
    huart5.Init.Mode = UART_MODE_TX_RX;
    huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart5.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart5) != HAL_OK)
    {
//        Error_Handler();
    }

    /* 5. NVIC 中断配置 */
    HAL_NVIC_SetPriority(UART5_IRQn, 5, 0);  // 适配FreeRTOS优先级
    HAL_NVIC_EnableIRQ(UART5_IRQn);
    HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

    /* 6. 启动 DMA 接收 + 开启 IDLE 中断 */
    HAL_UART_Receive_DMA(&huart5, UART5_Rx_Buf, USART5_RX_BUF_SIZE);
    __HAL_UART_ENABLE_IT(&huart5, UART_IT_IDLE);


				
}





xComPortHandle xSerialPortInitMinimal( unsigned long ulWantedBaud, unsigned portBASE_TYPE uxQueueLength )
{
xComPortHandle xReturn;
GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* Create the queues used to hold Rx/Tx characters. */
	xRxedChars = xQueueCreate( uxQueueLength, ( unsigned portBASE_TYPE ) sizeof( signed char ) );
	xCharsForTx = xQueueCreate( uxQueueLength + 1, ( unsigned portBASE_TYPE ) sizeof( signed char ) );
	
	/* If the queue/semaphore was created correctly then setup the serial port
	hardware. */
	if( ( xRxedChars != serINVALID_QUEUE ) && ( xCharsForTx != serINVALID_QUEUE ) )
	{
    /* 1. 开启时钟 */
    __HAL_RCC_UART5_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();  // UART5 RX DMA 属于 DMA1 流5 通道4

    /* 2. GPIO 初始化：TX=PC12, RX=PD2 */
//    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;  // RX 上拉
    GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* 3. DMA 接收配置 */
    hdma_uart5_rx.Instance = DMA1_Stream0;
    hdma_uart5_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_uart5_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_uart5_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_uart5_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_uart5_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_uart5_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_uart5_rx.Init.Mode = DMA_NORMAL;
    hdma_uart5_rx.Init.Priority = DMA_PRIORITY_MEDIUM;
    hdma_uart5_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_uart5_rx) != HAL_OK)
    {
//        Error_Handler();
    }
    __HAL_LINKDMA(&huart5, hdmarx, hdma_uart5_rx);

    /* 4. UART5 初始化 */
    huart5.Instance = UART5;
    huart5.Init.BaudRate = ulWantedBaud;
    huart5.Init.WordLength = UART_WORDLENGTH_8B;
    huart5.Init.StopBits = UART_STOPBITS_1;
    huart5.Init.Parity = UART_PARITY_NONE;
    huart5.Init.Mode = UART_MODE_TX_RX;
    huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart5.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart5) != HAL_OK)
    {
//        Error_Handler();
    }

    /* 5. NVIC 中断配置 */
    HAL_NVIC_SetPriority(UART5_IRQn, 6, 0);  // 适配FreeRTOS优先级
    HAL_NVIC_EnableIRQ(UART5_IRQn);
    HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

    /* 6. 启动 DMA 接收 + 开启 IDLE 中断 */
    HAL_UART_Receive_DMA(&huart5, UART5_Rx_Buf, USART5_RX_BUF_SIZE);
    __HAL_UART_ENABLE_IT(&huart5, UART_IT_IDLE);
			
			
			xReturn = ( xComPortHandle ) 4;
	}
	else
	{
		xReturn = ( xComPortHandle ) 0;
	}

	/* This demo file only supports a single port but we have to return
	something to comply with the standard demo header file. */
	return xReturn;
}
/*-----------------------------------------------------------*/

signed portBASE_TYPE xSerialGetChar( xComPortHandle pxPort, signed char *pcRxedChar, TickType_t xBlockTime )
{
	/* The port handle is not required as this driver only supports one port. */
	( void ) pxPort;

	/* Get the next character from the buffer.  Return false if no characters
	are available, or arrive before xBlockTime expires. */
	if( xQueueReceive( xRxedChars, pcRxedChar, xBlockTime ) )
	{
		return pdTRUE;
	}
	else
	{
		return pdFALSE;
	}
}
/*-----------------------------------------------------------*/

void vSerialPutString( xComPortHandle pxPort, const signed char * const pcString, unsigned short usStringLength )
{
signed char *pxNext;

	/* A couple of parameters that this port does not use. */
	( void ) usStringLength;
	( void ) pxPort;

	/* NOTE: This implementation does not handle the queue being full as no
	block time is used! */

	/* The port handle is not required as this driver only supports UART1. */
	( void ) pxPort;

	/* Send each character in the string, one at a time. */
	pxNext = ( signed char * ) pcString;
	while( *pxNext )
	{
		xSerialPutChar( pxPort, *pxNext, serNO_BLOCK );
		pxNext++;
	}
}
/*-----------------------------------------------------------*/

signed portBASE_TYPE xSerialPutChar( xComPortHandle pxPort, signed char cOutChar, TickType_t xBlockTime )
{
signed portBASE_TYPE xReturn;

	if( xQueueSend( xCharsForTx, &cOutChar, xBlockTime ) == pdPASS )
	{
		xReturn = pdPASS;
		__HAL_UART_ENABLE_IT(&huart5, UART_IT_TXE);
	}
	else
	{
		xReturn = pdFAIL;
	}

	return xReturn;
}
/*-----------------------------------------------------------*/

void vSerialClose( xComPortHandle xPort )
{
	/* Not supported as not required by the demo application. */
}
/*-----------------------------------------------------------*/



void DMA1_Stream5_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_uart5_rx);
}


void UART5_IDLE_Callback(UART_HandleTypeDef *huart)
{
    uint32_t temp;
    if(huart->Instance == UART5)
    {
        /* 关闭DMA + 清除中断标志 */
        __HAL_UART_DISABLE_IT(huart, UART_IT_IDLE);
        HAL_UART_DMAStop(huart);

        /* 计算接收到的数据长度 */
        temp  =  __HAL_DMA_GET_COUNTER(&hdma_uart5_rx);
				UART5_Rx_Len = USART5_RX_BUF_SIZE - temp;
        /* ============================================== */
        /* 关键：将接收到的数据送入 FreeRTOS+CLI 处理队列 */
        /* ============================================== */
        for(uint16_t i=0; i<UART5_Rx_Len; i++)
        {
            BaseType_t xHigherPriorityTaskWoken = pdFALSE;
            xQueueSendFromISR( xRxedChars, &UART5_Rx_Buf[i], &xHigherPriorityTaskWoken );
//						portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
						portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );					
        }

        /* 重新启动DMA接收，等待下一包数据 */
        HAL_UART_Receive_DMA(&huart5, UART5_Rx_Buf, USART5_RX_BUF_SIZE);
        __HAL_UART_ENABLE_IT(&huart5, UART_IT_IDLE);

        /* 清空接收缓冲区 */
        UART5_Rx_Len = 0;
        memset(UART5_Rx_Buf, 0, USART5_RX_BUF_SIZE);
    }
}






void vUARTInterruptHandler( void )
{
portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
char cChar;

	/* IDLE 空闲中断处理 */
	if(__HAL_UART_GET_FLAG(&huart5, UART_FLAG_IDLE) != RESET)
	{
			UART5_IDLE_Callback(&huart5);
	}	

	if (__HAL_UART_GET_FLAG(&huart5, UART_FLAG_TXE) != RESET)
	{
		/* The interrupt was caused by the THR becoming empty.  Are there any
		more characters to transmit? */
		if( xQueueReceiveFromISR( xCharsForTx, &cChar, &xHigherPriorityTaskWoken ) == pdTRUE )
		{
			/* A character was retrieved from the queue so can be sent to the
			THR now. */
			HAL_UART_Transmit(&huart5,(uint8_t *)&cChar,1,100);
		}
		else
		{
			__HAL_UART_DISABLE_IT(&huart5, UART_IT_TXE);
		};
	}

	portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
	
	
}





	
