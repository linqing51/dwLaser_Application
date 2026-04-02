#include "drv_usart5.h"
#include "usart.h"

volatile uint8_t USART5RecvBuf[USART5MAXBUFFSIZE] = {0};
volatile uint16_t RecvTop5 = 0;
volatile uint16_t RecvEnd5 = 0;

uint8_t drv_Usart5_GetByte(void);


//void UART5_IRQHandler (void)
//{
//	uint8_t temp = 0;

//	//Receive data register not empty flag
//	if (USART_GetITStatus (UART5, USART_IT_RXNE) != RESET)
//	{
//		temp = USART_ReceiveData (UART5);		//get received data

//		if ( (RecvEnd5 == (RecvTop5 - 1) ) || ( (RecvTop5 == 0) && (RecvEnd5 == (USART5MAXBUFFSIZE - 1) ) ) )
//		{
//			//»º³åÒç³ö
//			RecvTop5 = 0;
//			RecvEnd5 = 0;
//		}
//		else
//		{
//			USART5RecvBuf[RecvEnd5] = temp;
//			RecvEnd5++;

//			if (RecvEnd5 >= USART5MAXBUFFSIZE) RecvEnd5 = 0;
//		}

//		/* Clear the UART1 Recvive interrupt */
//		USART_ClearITPendingBit (UART5, USART_IT_RXNE);
//	}
//	else if (USART_GetITStatus (UART5, USART_IT_NE | USART_IT_PE | USART_IT_FE | USART_IT_ORE) != RESET)
//	{
//		USART_GetITStatus (UART5, USART_IT_NE | USART_IT_PE | USART_IT_FE | USART_IT_ORE);
//		USART_ReceiveData (UART5);
//	}
//}


void drv_Usart5SendOne (const uint8_t dat)
{
	HAL_UART_Transmit_IT(&huart5, (uint8_t *)&dat, 1);
	while (__HAL_UART_GET_FLAG(&huart5, UART_FLAG_TXE) == RESET) {}
	__HAL_UART_CLEAR_FLAG(&huart5, UART_FLAG_TXE);

}


void drv_Usart5SendString (const uint8_t *Buff)
{
	while (*Buff != 0)
	{
		drv_Usart5SendOne (*Buff);
		Buff++;
	}    
}


void drv_Usart5SendData (const uint8_t *Buff, uint16_t SendSize)
{
	while (SendSize != 0)
	{
		drv_Usart5SendOne (*Buff);
		Buff++;
		SendSize--;
	}

}

void drv_Usart5RecvReset (void)
{
	RecvTop5 = 0;
	RecvEnd5 = 0;

	memset((void *)USART5RecvBuf, 0, USART5MAXBUFFSIZE); 
}


uint8_t drv_Usart5RecvOne (uint8_t *Str)
{
	if (RecvTop5 == RecvEnd5) return 0;//read nothing

	*Str = USART5RecvBuf[RecvTop5];
	RecvTop5++;

	if (RecvTop5 >= USART5MAXBUFFSIZE) RecvTop5 = 0;

	return 1;//read one

}


uint16_t drv_Usart5RecvAtTime (uint8_t *Buff, uint16_t RecvSize, uint32_t timeout_MilliSeconds)
{
//	uint16_t RecvLen = 0;
//	uint8_t tmp[1] = {0};

//	if (RecvSize == 0) return 0;

//	g1msTimer5 = timeout_MilliSeconds;

//	while (1)
//	{
//		if (g1msTimer5 == 0) return RecvLen;

//		if (drv_Usart2RecvOne (tmp) == 1) 
//		{
//			Buff[RecvLen++] = tmp[0];
//		}

//		if (RecvLen >= RecvSize) return RecvLen;
//	}
	return 0;
}


uint8_t drv_Usart5Read(uint8_t *Buff, uint16_t len)
{

	uint16_t RecvLen = 0;
	uint8_t tmp[1] = {0};

	if (len == 0 || Buff == NULL) return 0;

	while (len--)
	{
		if (drv_Usart5RecvOne (tmp) == 1)
		{
			Buff[RecvLen++] = tmp[0];
		}

		if (RecvLen >= len) return RecvLen;
	}

	return RecvLen;
    
}

static uint32_t drv_Usart5_ReadByte(uint8_t *key)
{
	if(__HAL_UART_GET_FLAG(&huart5, UART_FLAG_RXNE) != RESET)
  {
    *key = (uint8_t)UART5->DR;
    return 1;
  }
  else
  {
    return 0;
  }
}

uint8_t drv_Usart5_GetByte(void)
{
  uint8_t key = 0;

  /* Waiting for user input */
  while (1)
  {
    if (drv_Usart5_ReadByte((uint8_t*)&key)) break;
    
  }
  return key;

}

