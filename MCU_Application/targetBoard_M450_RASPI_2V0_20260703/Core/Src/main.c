/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "can.h"
#include "crc.h"
#include "dac.h"
#include "dma.h"
#include "fatfs.h"
#include "i2c.h"
#include "rng.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_host.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sPlc.h"
#include "boardConfig.h"
#include "modbus_slave_spi.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
#if defined(LYPE_MCU_2V0_TEST)
uint8_t ret;
int16_t temp_val, humi_val;
uint8_t ch;
uint16_t dac_table[] = {0, 16384, 32768, 49152, 65535};
uint8_t level_idx;
char test_msg[] = "USART 115200 Test\r\n";
uint8_t test_data[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
CAN_TxHeaderTypeDef   TxHeader;
uint32_t tx_mailbox;
uint8_t code0;

#endif
float temp;
DHT11_DataTypeDef dht11_data;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */
HAL_StatusTypeDef SPI_Slave_StartDmaTx(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_CAN1_Init();
  MX_CAN2_Init();
  MX_CRC_Init();
  MX_DAC_Init();
  MX_I2C3_Init();
  MX_RNG_Init();
  MX_SPI2_Init();
  MX_SPI3_Init();
  MX_TIM12_Init();
  MX_UART5_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_USART6_UART_Init();
  MX_TIM5_Init();
  MX_TIM8_Init();
  MX_TIM9_Init();
  MX_FATFS_Init();
  MX_TIM7_Init();
  MX_TIM14_Init();
  MX_RTC_Init();
  MX_I2C2_Init();
  MX_TIM10_Init();
  /* USER CODE BEGIN 2 */

//	__HAL_TIM_SET_COUNTER(&htim10, 0);
////	HAL_TIM_Base_Stop_IT(&htim10);
//	HAL_TIM_Base_Start_IT(&htim10);
//	
//	
////	__HAL_SPI_ENABLE(&hspi2);  // 启用SPI2外设
//  __HAL_SPI_ENABLE_IT(&hspi2, ( SPI_IT_RXNE));
//  __HAL_SPI_DISABLE(&hspi2);
//	
//  HAL_GPIO_WritePin(HDMI_VCC_EA_GPIO_Port, HDMI_VCC_EA_Pin, GPIO_PIN_SET);
//	
//	CAN_Filter_Config();
//	SPI_Slave_WaitMasterCmd();	
//	
//		HAL_Delay(2000); 
//    while (1)
//    {
//        uint8_t ret = DHT11_ReadData(&dht11_data);
//        if(ret == 0)
//        {
//            //读取成功，dht11_data.temp_int 温度；dht11_data.humi_int湿度
//        }
//        HAL_Delay(2000); //DHT11最小采样间隔1s，不可太快
//    }

	

//  while(1)
//	{

//    if(PCA9546_Init() == HAL_OK)
//    {
//        // 选择通道0
//        if(PCA9546_SelectChannel(PCA9546_CHANNEL_0) == HAL_OK)
//        {
//            // 读取当前通道状态，验证是否选择成功
//            uint8_t current_ch;
//            if(PCA9546_ReadChannel(&current_ch) == HAL_OK && current_ch == PCA9546_CHANNEL_0)
//            {
//									LM75A_Init(&hi2c2);
//							
//									temp = LM75A_ReadTemperature(LM75A_A_I2C_ADDR);
//									if(temp > -900.0f)
//									{
//											// 读取成功，temp即为摄氏温度
//									}
//									HAL_Delay(200);							
//									temp = LM75A_ReadTemperature(LM75A_B_I2C_ADDR);
//									if(temp > -900.0f)
//									{
//											// 读取成功，temp即为摄氏温度
//									}
//									HAL_Delay(200);							
//									HAL_Delay(1000);							
//												
//            }
//        }
//        
//    };
//		
//	}


	
//  while(1)
//	{
////								if(spi_slave_state == SPI_SLAVE_STATE_IDLE)
////								{
////										/* 重新进入待命，等待下一次主机NSS拉低 */
////										SPI_Slave_WaitMasterCmd();
////								}
//						

//								/* -------- SPI硬件错误 OVR/MODF/DMA错误处理 -------- */


//								if(spi_err_flag != 0)
//								{
//										spi_err_flag = 0;
//										SPI_StopFrameWatchdog();

//										HAL_SPI_Abort(&hspi2);
//										/* ---------- 第1步：停止DMA，解除HAL状态机锁定 ---------- */
//										HAL_SPI_DMAStop(&hspi2);

//										/* ---------- 第2步：禁用SPI外设 ---------- */
//										__HAL_SPI_DISABLE(&hspi2);

//										/* ---------- 第3步：清除所有错误标志 ---------- */
//										// OVR清除：先读DR，再读SR（HAL库的__HAL_SPI_CLEAR_OVRFLAG宏已封装）
//										__HAL_SPI_CLEAR_OVRFLAG(&hspi2);
//										// MODF清除：先读SR，再写CR1（HAL宏已封装）
//										__HAL_SPI_CLEAR_MODFFLAG(&hspi2);
//										// CRC错误（如果启用了CRC）
//										__HAL_SPI_CLEAR_CRCERRFLAG(&hspi2);
//										// 帧错误（TI模式下）
//										__HAL_SPI_CLEAR_FREFLAG(&hspi2);

//										/* ---------- 第4步：复位DMA流 ---------- */
//										// 这一步非常关键！DMA流如果不复位，重新使能会立即触发DMA错误
//										HAL_DMA_DeInit(hspi2.hdmatx);
//										HAL_DMA_DeInit(hspi2.hdmarx);
//										// 重新初始化DMA（调用你CubeMX生成的MX_DMA_Init()中的对应配置）
//										MX_DMA_Init();
//										// 重新关联DMA句柄到SPI
//										__HAL_LINKDMA(&hspi2, hdmatx, hdma_spi2_tx);  // 根据实际DMA句柄名修改
//										__HAL_LINKDMA(&hspi2, hdmarx, hdma_spi2_rx);

//										/* ---------- 第5步：重新初始化SPI外设 ---------- */
//										HAL_SPI_MspInit(&hspi2);
//										/* ---------- 第6步：重新启动DMA收发 ---------- */
//										// 从机模式必须用 TransmitReceive_DMA，不能只开接收
//										// 因为从机在接收的同时必须发送数据（全双工）
//										g_spi_status = HAL_SPI_TransmitReceive_DMA(&hspi2,  spi_tx_resp_buf, spi_rx_cmd_buf, SPI_RX_CMD_LEN);
////										SPI_StartFrameWatchdog(); /* 应答阶段重新开启帧看门狗 */
//										spi_abort_timeout_cnt++;

//										
//										__HAL_SPI_ENABLE(&hspi2);  // 启用SPI2外设
//										__HAL_SPI_ENABLE_IT(&hspi2, ( SPI_IT_RXNE));
//																						
//													
//										spi_slave_state = SPI_SLAVE_STATE_RX_CMD;
//							}		


//						
//	};		
	
#if defined(LYPE_MCU_2V0_TEST)
	epromInit();
  listEpromTable();
//  sPlcEpromTest();



    // HDC1080初始化
    ret = hdc1080_init();
    if(ret == 0)
    {
        printf("HDC1080 init OK!\r\n");
    }
    else
    {
        printf("HDC1080 init FAIL!!! Check I2C wiring!\r\n");
    }

		// 读取温湿度
		hdc1080_read(&temp_val, &humi_val);

		/*
		 * temp_val = (温度 ×10)   例：253 → 25.3℃
		 * humi_val = (湿度 ×10)   例：452 → 45.2%RH
		 */
		printf("Temp: %d.%d ℃  | Humidity: %d.%d %%RH\r\n",
					 temp_val / 10, abs(temp_val) % 10,
					 humi_val / 10, humi_val % 10);

		HAL_Delay(1000); // 1秒刷新一次



    DAC8568_Init();
    
    // 设置通道A输出半量程（32768对应Vref/2）
    DAC8568_SetChannelVoltage(DAC8568_CH_A, 0x1000);
    DAC8568_SetChannelVoltage(DAC8568_CH_C, 0x2000);
    DAC8568_SetChannelVoltage(DAC8568_CH_E, 0x3000);
    DAC8568_SetChannelVoltage(DAC8568_CH_G, 0x4000);
    // 设置通道B输出满量程（65535对应Vref）
    DAC8568_SetChannelVoltage(DAC8568_CH_B, 0x8000);
    DAC8568_SetChannelVoltage(DAC8568_CH_D, 0x9000);
    DAC8568_SetChannelVoltage(DAC8568_CH_F, 0xa000);
    DAC8568_SetChannelVoltage(DAC8568_CH_H, 0xb000);

    // 清除所有通道输出
    DAC8568_ClearAllChannels();


		DAC_TEC_SetChannel1Voltage(2.5f);  // PA4输出1.5V
		DAC_TEC_SetChannel2Voltage(2.0f);  // PA5输出2.0V
	
		DAC_TEC_SetChannel1Voltage(0.0f); 
		DAC_TEC_SetChannel2Voltage(0.0f); 

    // 初始化PCA9546（自动完成复位引脚配置、硬件复位、通道复位）
    if(PCA9546_Init() == HAL_OK)
    {
        // 选择通道0
        if(PCA9546_SelectChannel(PCA9546_CHANNEL_0) == HAL_OK)
        {
            // 读取当前通道状态，验证是否选择成功
            uint8_t current_ch;
            if(PCA9546_ReadChannel(&current_ch) == HAL_OK && current_ch == PCA9546_CHANNEL_0)
            {
//                // 通道0选择成功，可执行后续I2C设备操作
//								PCA9546_HardwareReset();
									DAC5578_Init();
									HAL_Delay(500);
									code0 = DAC5578_VolToCode(0.50f, 5.0f);
									DAC5578_SetChannel(DAC5578_CH_A, code0);							
									code0 = DAC5578_VolToCode(1.00f, 5.0f);
									DAC5578_SetChannel(DAC5578_CH_B, code0);							
									code0 = DAC5578_VolToCode(1.50f, 5.0f);
									DAC5578_SetChannel(DAC5578_CH_C, code0);							
									code0 = DAC5578_VolToCode(2.00f, 5.0f);
									DAC5578_SetChannel(DAC5578_CH_D, code0);							
									code0 = DAC5578_VolToCode(2.50f, 5.0f);
									DAC5578_SetChannel(DAC5578_CH_E, code0);					
									code0 = DAC5578_VolToCode(3.00f, 5.0f);
									DAC5578_SetChannel(DAC5578_CH_F, code0);							
									code0 = DAC5578_VolToCode(3.50f, 5.0f);
									DAC5578_SetChannel(DAC5578_CH_G, code0);							
									code0 = DAC5578_VolToCode(4.00f, 5.0f);
									DAC5578_SetChannel(DAC5578_CH_H, code0);	


									HAL_Delay(1000);							
									LM75A_Init(&hi2c2);
							
									temp = LM75A_ReadTemperature(LM75A_A_I2C_ADDR);
									if(temp > -900.0f)
									{
											// 读取成功，temp即为摄氏温度
									}
									HAL_Delay(200);							
									temp = LM75A_ReadTemperature(LM75A_B_I2C_ADDR);
									if(temp > -900.0f)
									{
											// 读取成功，temp即为摄氏温度
									}
									HAL_Delay(200);							
            }
        }
    };
		
		//RS232 COM TX
		HAL_UART_Transmit(&huart3, (uint8_t*)test_msg, sizeof(test_msg)-1, 100);
		//RS232 COM TX
		HAL_UART_Transmit(&huart6, (uint8_t*)test_msg, sizeof(test_msg)-1, 100);

		
  /* 发送头配置（标准ID、数据帧、无扩展ID） */
  TxHeader.StdId = 0x123;          // 标准ID（0-0x7FF）
  TxHeader.ExtId = 0;            // 扩展ID禁用
  TxHeader.RTR = CAN_RTR_DATA;      // 数据帧（非远程帧）
  TxHeader.IDE = CAN_ID_STD;        // 标准ID格式
  TxHeader.DLC = 8;               // 数据长度（1-8）
  TxHeader.TransmitGlobalTime = DISABLE;
  do
	{
	 /* 发送数据 */
		if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, test_data, &tx_mailbox) != HAL_OK) {
        printf("can1 FAIL!!!\r\n");
		}

		if (HAL_CAN_AddTxMessage(&hcan2, &TxHeader, test_data, &tx_mailbox) != HAL_OK) {
        printf("can2 FAIL!!!\r\n");
		}
		HAL_Delay(1000); // 1秒刷新一次
	}while(1);


	TPL0501_SetWiper(0xff);
	TPL0501_SetWiper(0xff);
	
  HAL_GPIO_WritePin(HDMI_VCC_EA_GPIO_Port, HDMI_VCC_EA_Pin, GPIO_PIN_SET);





#endif
  HAL_GPIO_WritePin(HDMI_VCC_EA_GPIO_Port, HDMI_VCC_EA_Pin, GPIO_PIN_SET);

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();  /* Call init function for freertos objects (in cmsis_os2.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

//接收中断回调
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  CAN_RxHeaderTypeDef rx_header;
  uint8_t rx_data[8];

  if(HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data) == HAL_OK)
  {
    /* 判断是CAN1还是CAN2 */
    if(hcan->Instance == CAN1)
    {
        //======== CAN1 接收处理 =========
        //rx_header.StdId  标准ID
        //rx_header.ExtId  扩展ID
        //rx_header.IDE    CAN_ID_STD / CAN_ID_EXT
        //rx_header.RTR    CAN_RTR_DATA / CAN_RTR_REMOTE
        //rx_header.DLC    数据长度 0~8
        //rx_data[]        接收数据

        if(rx_header.IDE == CAN_ID_STD)
        {
            uint16_t can1_std_id = rx_header.StdId;
            switch(can1_std_id)
            {
                case 0x123:
                    break;
                default:
                    break;
            }
        }
    }
    else if(hcan->Instance == CAN2)
    {
        //======== CAN2 接收处理 =========
        if(rx_header.IDE == CAN_ID_STD)
        {
            uint16_t can2_std_id = rx_header.StdId;
            switch(can2_std_id)
            {
                case 0x200:
                    break;
                default:
                    break;
            }
        }
    }
  }
}








/**
 * @brief  SPI DMA发送完成中断回调
 * @param  hspi : SPI句柄指针
 */
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
  if(hspi->Instance == SPI2)
  {
  }
}









/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM13 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM13)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
	if(htim->Instance == CONFIG_SPLC_TIM) {
		sPlcTimerIsr();
	}
	if(htim->Instance == CONFIG_LASER_TIM){
		sPlcLaserTimerIsr();
	}
	if(htim->Instance == CONFIG_SPI2_TIM){
/* 看门狗溢出，SPI帧传输超时 */
		__HAL_TIM_SET_COUNTER(&htim10, 0);
		if (spi_frame_timeout_cnt > 0)
		{
			  spi_frame_timeout_cnt = 0;
    }
		else
		{	
			  spi_err_flag = 1;
		};
			

	}

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
