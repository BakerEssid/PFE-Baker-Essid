/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
CAN_HandleTypeDef hcan1;

TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

CAN_HandleTypeDef hcan1;
CAN_FilterTypeDef Filtercan1;
CAN_RxHeaderTypeDef pRxHeader;
CAN_TxHeaderTypeDef pTxHeader;
uint8_t aTxData[8];
uint8_t aRxData[8];
uint8_t test[8];
char Datacheck = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

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
  MX_CAN1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

       // CAN filter
     Filtercan1.FilterIdHigh = 0x00;
     Filtercan1.FilterIdLow = 0x00;
     Filtercan1.FilterMaskIdHigh = 0x00;
     Filtercan1.FilterMaskIdLow = 0x00;
     Filtercan1.FilterFIFOAssignment = CAN_FILTER_FIFO0;
     Filtercan1.FilterBank = 0x00;
     Filtercan1.FilterMode = CAN_FILTERMODE_IDMASK;
     Filtercan1.FilterScale = CAN_FILTERSCALE_32BIT;
     Filtercan1.FilterActivation = CAN_FILTER_ENABLE;
     Filtercan1.SlaveStartFilterBank = 14;
     if (HAL_CAN_ConfigFilter(&hcan1, &Filtercan1)!= HAL_OK)
  		  {
  		    Error_Handler();
  		  }

        // Start CAN
    if (HAL_CAN_Start(&hcan1)!= HAL_OK)
  		  {
  		    Error_Handler();
  		  }
        // Activer la notification de la réception
    if (HAL_CAN_ActivateNotification(&hcan1,CAN_IT_RX_FIFO0_MSG_PENDING)!= HAL_OK)
  		  {
  		    Error_Handler();
  		  }

    if (HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1)!= HAL_OK)
    	 	     {
    	 	    Error_Handler();
    	 	     }

                pTxHeader.DLC=6;
   		   	    pTxHeader.ExtId=0;
   		   	    pTxHeader.IDE=CAN_ID_STD;
   		   	    pTxHeader.StdId=2;
   		   	    pTxHeader.RTR=CAN_RTR_DATA;
   		   	    pTxHeader.TransmitGlobalTime = DISABLE;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if (test[6]==0x41)//if (pRxHeader.StdId == 0x001)
	  {
		       if (test[0] > 200)
		  				        {
		  				  	      HAL_GPIO_WritePin(GPIOD, GREEN_Pin, SET);
		  				  	  	  HAL_GPIO_WritePin(GPIOD, ORANGE_Pin, RESET);
		  				  	  	  HAL_GPIO_WritePin(GPIOD, RED_Pin, RESET);
		  				  	  	}
		  		if (test[0] > 70)
		  				  	  	{
		  				  	  	  HAL_GPIO_WritePin(GPIOD, GREEN_Pin, RESET);
		  				  	  	  HAL_GPIO_WritePin(GPIOD, ORANGE_Pin, SET);
		  				  	  	  HAL_GPIO_WritePin(GPIOD, RED_Pin, RESET);
		  				  	    }
		  		                else
		  				  	  	{
		  				  	  	  HAL_GPIO_WritePin(GPIOD, GREEN_Pin, RESET);
		  				  	  	  HAL_GPIO_WritePin(GPIOD, ORANGE_Pin, RESET);
		  				  	  	  HAL_GPIO_WritePin(GPIOD, RED_Pin, SET);
		  				  	    }
		  		 if (test[1]<20)
		  				 	    {
		  				 	      HAL_GPIO_TogglePin(GPIOD, BLUE_Pin);
		  				 	      HAL_GPIO_WritePin(GPIOB, BUZZER_Pin, GPIO_PIN_SET);
		  				 	    }
		  		 if (test[1]>20)
		  				 	    {
		  				 	      HAL_GPIO_WritePin(GPIOD, BLUE_Pin, GPIO_PIN_SET);
		  				 	      HAL_GPIO_WritePin(GPIOB, BUZZER_Pin, GPIO_PIN_RESET);
		  				 	    }
		  		 if (test[2]>30)
		  		                {
		  			              HAL_GPIO_WritePin(GPIOB, FAN_Pin, GPIO_PIN_SET);
		  		                }
		  		 if (test[2]<30)
		  				        {
		  				  		  HAL_GPIO_WritePin(GPIOB, FAN_Pin, GPIO_PIN_RESET);
		  				  		}
		  		if (test[3] == 0)
		  				  	    {
		  				  		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,750);
		  				  		HAL_Delay(100);
		  				  	    }
		  		if (test[3] == 1)
		  			            {
		  				        __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,750);
		  					    HAL_Delay(700);
		  					    __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,1150);
		  					    HAL_Delay(700);
		  					    __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,750);
		  					    HAL_Delay(700);
		  			            }
		  	    if (test[3] == 2)
		  			            {
		  			            __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,750);
		  			            HAL_Delay(100);
		  			            __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,1150);
		  			            HAL_Delay(100);
		  			            __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,750);
		  			            HAL_Delay(100);
		  			            }
		  	    if (test[4]>150)
		  	    {
		  	    	HAL_GPIO_WritePin(GPIOB, RPM_Pin, GPIO_PIN_SET);
		  	    }
		  	    else
		  	    {
		  	 	    HAL_GPIO_WritePin(GPIOB, RPM_Pin, GPIO_PIN_RESET);
		  	    }
	  }
	  if (test[6]==0x4D)
	  {
		  if (test[5]==0x30)
		  {
			  HAL_GPIO_WritePin(GPIOB, BUZZER_Pin, GPIO_PIN_SET);
		  }

		  if (test[5]==0x31)
		  {
		  	  HAL_GPIO_WritePin(GPIOB, BUZZER_Pin, GPIO_PIN_RESET);
		  }

		  if (test[5]==0x32)
		  {
			  HAL_GPIO_WritePin(GPIOB, FAN_Pin, GPIO_PIN_SET);
		  }

		  if (test[5]==0x33)
		  {
		  	  HAL_GPIO_WritePin(GPIOB, FAN_Pin, GPIO_PIN_RESET);
		  }

		  if (test[5]==0x34)
		  {
			  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,750);
			  HAL_Delay(100);
			  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,1150);
			  HAL_Delay(100);
			  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,750);
			  HAL_Delay(100);
		  }

		  if (test[5]==0x35)
		  {
		  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,750);
		  HAL_Delay(200);
		  }
	  }

	  HAL_Delay(50);
	  if (HAL_CAN_AddTxMessage(&hcan1,&pTxHeader,aTxData,(uint32_t *)CAN_TX_MAILBOX0)!= HAL_OK)
	  			  	  	     {
	  			  	  	    Error_Handler();
	  			  	  	     }
	       HAL_Delay(500);
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 4;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_7TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 144-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 10000-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, FAN_Pin|BUZZER_Pin|RPM_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GREEN_Pin|ORANGE_Pin|RED_Pin|BLUE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : FAN_Pin BUZZER_Pin */
  GPIO_InitStruct.Pin = FAN_Pin|BUZZER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : GREEN_Pin ORANGE_Pin RED_Pin BLUE_Pin */
  GPIO_InitStruct.Pin = GREEN_Pin|ORANGE_Pin|RED_Pin|BLUE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : RPM_Pin */
  GPIO_InitStruct.Pin = RPM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(RPM_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0,&pRxHeader,aRxData)!= HAL_OK)
		  {
		     Error_Handler();
		  }

	if (pRxHeader.StdId == 0x001)
	  {
		// Vérification de l'ID
          Datacheck = 1;

		test[0]=aRxData[0];
		test[1]=aRxData[1];
		test[2]=aRxData[2];
		test[3]=aRxData[3];
		test[4]=aRxData[4];
	  }

	if (pRxHeader.StdId == 0x003)
	  {
		test[5]=aRxData[5];
		test[6]=aRxData[6];
		aTxData[5]=aRxData[5];
	  }

}

/* USER CODE END 4 */

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

#ifdef  USE_FULL_ASSERT
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
