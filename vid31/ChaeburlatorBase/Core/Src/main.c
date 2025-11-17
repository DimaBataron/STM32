/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "UART_Outpt.h"
#include "Servo.h"
#include "ADC_LoadCell.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#ifdef TestExecutor
 float Volt = 0; // Battery voltage
#endif

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;

osThreadId LoRaRxHandle;
osThreadId ConsoleHandle;
osThreadId Motor1_2Handle;
osThreadId UARTOutHandle;
osThreadId Serv1_2Handle;
osThreadId Motor3Handle;
osThreadId VoltProtectHandle;
osThreadId LightSignalHandle;
osThreadId SoundAlarmHandle;
osThreadId DataProtectHandle;
osMessageQId UART_Rx_QueHandle;
osSemaphoreId SemDMA_LoRaHandle;
osSemaphoreId SemDMA_VoltMeasHandle;
/* USER CODE BEGIN PV */

EventGroupHandle_t xControlEventGroup;
//int8_t Acceleration;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_SPI1_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM3_Init(void);
void StartLoRaRx(void const * argument);
void StartConsole(void const * argument);
void StartMotor1_2(void const * argument);
void StartUARTOut(void const * argument);
void Servo_Cam_Steer(void const * argument);
void StartMotor3(void const * argument);
void StartVoltProtect(void const * argument);
void StartLightSignal(void const * argument);
void StartSoundAlarm(void const * argument);
void StartDataProtect(void const * argument);

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
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_SPI1_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of SemDMA_LoRa */
  osSemaphoreDef(SemDMA_LoRa);
  SemDMA_LoRaHandle = osSemaphoreCreate(osSemaphore(SemDMA_LoRa), 1);

  /* definition and creation of SemDMA_VoltMeas */
  osSemaphoreDef(SemDMA_VoltMeas);
  SemDMA_VoltMeasHandle = osSemaphoreCreate(osSemaphore(SemDMA_VoltMeas), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  osSemaphoreWait(SemDMA_LoRaHandle, 0);
  osSemaphoreWait(SemDMA_VoltMeasHandle, 0);
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  xControlEventGroup = xEventGroupCreate();
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of UART_Rx_Que */
  osMessageQDef(UART_Rx_Que, 30, uint8_t);
  UART_Rx_QueHandle = osMessageCreate(osMessageQ(UART_Rx_Que), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of LoRaRx */
  osThreadDef(LoRaRx, StartLoRaRx, osPriorityAboveNormal, 0, 90);
  LoRaRxHandle = osThreadCreate(osThread(LoRaRx), NULL);

  /* definition and creation of Console */
//  osThreadDef(Console, StartConsole, osPriorityLow, 0, 180);
//  ConsoleHandle = osThreadCreate(osThread(Console), NULL);

  /* definition and creation of Motor1_2 */
  osThreadDef(Motor1_2, StartMotor1_2, osPriorityBelowNormal, 0, 85);
  Motor1_2Handle = osThreadCreate(osThread(Motor1_2), NULL);

  /* definition and creation of UARTOut */
//  osThreadDef(UARTOut, StartUARTOut, osPriorityLow, 0, 200);
//  UARTOutHandle = osThreadCreate(osThread(UARTOut), NULL);

  /* definition and creation of Serv1_2 */
  osThreadDef(Serv1_2, Servo_Cam_Steer, osPriorityLow, 0, 64);
  Serv1_2Handle = osThreadCreate(osThread(Serv1_2), NULL);

  /* definition and creation of Motor3 */
  osThreadDef(Motor3, StartMotor3, osPriorityBelowNormal, 0, 64);
  Motor3Handle = osThreadCreate(osThread(Motor3), NULL);

  /* definition and creation of VoltProtect */
  osThreadDef(VoltProtect, StartVoltProtect, osPriorityBelowNormal, 0, 70);
  VoltProtectHandle = osThreadCreate(osThread(VoltProtect), NULL);

  /* definition and creation of LightSignal */
  osThreadDef(LightSignal, StartLightSignal, osPriorityLow, 0, 64);
  LightSignalHandle = osThreadCreate(osThread(LightSignal), NULL);

  /* definition and creation of SoundAlarm */
  osThreadDef(SoundAlarm, StartSoundAlarm, osPriorityBelowNormal, 0, 75);
  SoundAlarmHandle = osThreadCreate(osThread(SoundAlarm), NULL);

  /* definition and creation of DataProtect */
  osThreadDef(DataProtect, StartDataProtect, osPriorityNormal, 0, 300);
  DataProtectHandle = osThreadCreate(osThread(DataProtect), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 2;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 9999;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 7199;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

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

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 7199;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
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
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 21;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_9B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_ODD;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, M2_IN1_Pin|M1_IN1_Pin|M1_IN2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, P_CONTROL_Pin|LIGHT1_Pin|NSS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, M3_IN2_Pin|M3_IN1_Pin|STBY_M3_M4_Pin|BOOZER_Pin
                          |LIGHT2_Pin|Reset_Pin|STBY_M1_M2_Pin|M2_IN2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : M2_IN1_Pin M1_IN1_Pin M1_IN2_Pin */
  GPIO_InitStruct.Pin = M2_IN1_Pin|M1_IN1_Pin|M1_IN2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : P_CONTROL_Pin LIGHT1_Pin */
  GPIO_InitStruct.Pin = P_CONTROL_Pin|LIGHT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : M3_IN2_Pin M3_IN1_Pin STBY_M3_M4_Pin STBY_M1_M2_Pin
                           M2_IN2_Pin */
  GPIO_InitStruct.Pin = M3_IN2_Pin|M3_IN1_Pin|STBY_M3_M4_Pin|STBY_M1_M2_Pin
                          |M2_IN2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : BOOZER_Pin LIGHT2_Pin */
  GPIO_InitStruct.Pin = BOOZER_Pin|LIGHT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : NSS_Pin */
  GPIO_InitStruct.Pin = NSS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(NSS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Reset_Pin */
  GPIO_InitStruct.Pin = Reset_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Reset_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : DIO0_Pin */
  GPIO_InitStruct.Pin = DIO0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(DIO0_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartLoRaRx */
/**
  * @brief  Function implementing the LoRaRx thread.
  * @param  argument: Not used
  * @retval None
 * PB7 	DIO0
 * PB6	Reset
 * PB5	SPI1_MOSI
 * PB4	SPII_MISO
 * PB3	SPI1_SCK
 * PA15	NSS
  */
/* USER CODE END Header_StartLoRaRx */
void StartLoRaRx(void const * argument)
{
  /* USER CODE BEGIN 5 */
	ZeroCommArr();
	xEventGroupSetBits(xControlEventGroup, BIT_ACCEPT_PAC);
	SX1276Init();
	InitRxContLoRa();
	StartRxContLoRa();
  /* Infinite loop */
  for(;;)
  {// Waits for semaphore from IT.
	 xSemaphoreTake(SemDMA_LoRaHandle,portMAX_DELAY);
		// generates an array of commands based on the received data
	 xEventGroupWaitBits(xControlEventGroup, BIT_ACCEPT_PAC, pdFALSE, pdFALSE, portMAX_DELAY);
	 StartRxContLoRa();
	 CalcRxCommands();
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartConsole */
/**
* @brief Function implementing the Console thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartConsole */
void StartConsole(void const * argument)
{
  /* USER CODE BEGIN StartConsole */
	MyConsole_Setup();
	uint8_t Buffer[64];
	uint32_t len;
  /* Infinite loop */
  for(;;)
  {
	len = USART1_Receive(0x0D,Buffer,sizeof(Buffer),portMAX_DELAY);
	console_process(Buffer, len);
  }
  /* USER CODE END StartConsole */
}

/* USER CODE BEGIN Header_StartMotor1_2 */
/**
* @brief Function implementing the Motor1_2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMotor1_2 */
void StartMotor1_2(void const * argument)
{
  /* USER CODE BEGIN StartMotor1_2 */
	DC_Motor Motor1 = {0};
	Motor1.PinIn1 = M1_IN1_Pin;
	Motor1.PinIn2 = M1_IN2_Pin;
	Motor1.PortIn1 = M1_IN1_GPIO_Port;
	Motor1.PortIn2 = M1_IN2_GPIO_Port;
	Motor1.StbyPin = STBY_M1_M2_Pin;
	Motor1.StbyPort = STBY_M1_M2_GPIO_Port;
	Motor1.pwm_register_ptr = &(htim2.Instance->CCR1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
//	TestMotor(&Motor1, acceleration);

	DC_Motor Motor2 = {0};
	Motor2.PinIn1 = M2_IN1_Pin;
	Motor2.PinIn2 = M2_IN2_Pin;
	Motor2.PortIn1 = M2_IN1_GPIO_Port;
	Motor2.PortIn2 = M2_IN2_GPIO_Port;
	Motor2.StbyPin = STBY_M1_M2_Pin;
	Motor2.StbyPort = STBY_M1_M2_GPIO_Port;
	Motor2.pwm_register_ptr = &(htim2.Instance->CCR2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);

	xEventGroupSetBits(xControlEventGroup, BIT_ENGIN_START);
  /* Infinite loop */
  for(;;)
  {
	  xEventGroupWaitBits(xControlEventGroup, BIT_ENGIN_START, pdFALSE, pdFALSE, portMAX_DELAY);
	  Engine_Control(Acceleration,&Motor1, &Motor2);
	  osDelay(10);
  }
  /* USER CODE END StartMotor1_2 */
}

/* USER CODE BEGIN Header_StartUARTOut */
/**
* @brief Function implementing the UARTOut thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartUARTOut */
void StartUARTOut(void const * argument)
{
  /* USER CODE BEGIN StartUARTOut */
	ModeOutput = 0;
  /* Infinite loop */
  for(;;)
  {
	  switch (ModeOutput) {

	  case(0) : {
		  osDelay(2000);
		  break;
	  }
	  case(1) : {
		  OutDataRxLoRa(&huart1);
		  osDelay(1000);
		  break;
	  }
	  case(2) : {
		  OurServRotPerc(&huart1);
		  osDelay(1000);
		  break;
	  }
	  case(3) : {
		  // Stops the data protection task when outputting data.
		  // Starts only on reboot?
		  // Can Mtex be used for synchronization?
		  // Does this task take it when it starts working.
		  // and releases it when ModeOutput = 0?
		  NumRxPack(&huart1);
		  osDelay(1000);
		  break;
	  }
	  case(4) : { // output of measured ADC voltages.
		  osDelay(5020);
		  OutMeasVal(&huart1);

	  }
	  default : {
		  osDelay(2000);
		  break;
	  }
	  }
  }
  /* USER CODE END StartUARTOut */
}

/* USER CODE BEGIN Header_Servo_Cam_Steer */
/**
* @brief Function implementing the Serv1_2 thread.
*
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Servo_Cam_Steer */
void Servo_Cam_Steer(void const * argument)
{
  /* USER CODE BEGIN Servo_Cam_Steer */

	ServoStartInit(&htim3, TIM_CHANNEL_2);
	ServoStartInit(&htim3, TIM_CHANNEL_1);
	HAL_GPIO_WritePin(GPIOA, P_CONTROL_Pin, GPIO_PIN_SET);
  /* Infinite loop */
  for(;;)
  {
	  ServRot(&htim3, TIM_CHANNEL_2,  SteerTurn);
	  ServRot(&htim3, TIM_CHANNEL_1,  CamVertical);

    osDelay(20);
  }
  /* USER CODE END Servo_Cam_Steer */
}

/* USER CODE BEGIN Header_StartMotor3 */
/**
* @brief Function implementing the Motor3 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMotor3 */
void StartMotor3(void const * argument)
{
  /* USER CODE BEGIN StartMotor3 */
	DC_Motor Motor3 = {0};
		Motor3.PinIn1 = M3_IN1_Pin;
		Motor3.PinIn2 = M3_IN2_Pin;
		Motor3.PortIn1 = M3_IN1_GPIO_Port;
		Motor3.PortIn2 = M3_IN2_GPIO_Port;
		Motor3.StbyPin = STBY_M3_M4_Pin;
		Motor3.StbyPort = STBY_M3_M4_GPIO_Port;
		Motor3.pwm_register_ptr = &(htim2.Instance->CCR3);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
  /* Infinite loop */
  for(;;)
  {
	Engine1_Control(CamHorizont, &Motor3);
    osDelay(20);
  }
  /* USER CODE END StartMotor3 */
}

/* USER CODE BEGIN Header_StartVoltProtect */
/**
* @brief Function implementing the VoltProtect thread.
* @param argument: Not used
* @retval None
*
*/
/* USER CODE END Header_StartVoltProtect */
void StartVoltProtect(void const * argument)
{
  /* USER CODE BEGIN StartVoltProtect */
	uint8_t BatteryStatus = 0;
	uint8_t NumberDrawd	  = 0;

	float U = 0;

	// calibration to improve accuracy
	HAL_ADCEx_Calibration_Start(&hadc1);
  /* Infinite loop */
  for(;;)
  {
	StartMeasure(&hadc1);
	//Waiting for a semophore indicating that the transformation is complete.
	xSemaphoreTake(SemDMA_VoltMeasHandle,portMAX_DELAY);

	//calculation of the obtained values
	U = VoltageCalc();

	#ifdef TestExecutor
	Volt = U;
	#endif

	BatteryStatus = CheckBatVolt(U);

	switch (BatteryStatus) {
	case VOLT_CAUTION :{
//	  		  vTaskResume(LightSignalHandle);
		Caution();
	  	break;
	}
	case VOLT_SHUTDOWN :{ // unlock alarm and block all tasks
		NumberDrawd++;
		if(NumberDrawd > 2){
			NumberDrawd = 0;
			EmergMode();
		}
		break;
	}
	default :{
		xEventGroupClearBits(xControlEventGroup, BIT_LIGHT_SIGNAL);
		HAL_GPIO_WritePin(LIGHT2_GPIO_Port, LIGHT2_Pin, GPIO_PIN_RESET);
	}

	}
	osDelay(5000);
  }
  /* USER CODE END StartVoltProtect */
}

/* USER CODE BEGIN Header_StartLightSignal */
/**
* @brief Function implementing the LightSignal thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLightSignal */
void StartLightSignal(void const * argument)
{
  /* USER CODE BEGIN StartLightSignal */
  /* Infinite loop */
  for(;;)
  {
	  // The task will be blocked until BIT_LIGHT_SIGNAL is set
	  // will work until reset
	xEventGroupWaitBits(xControlEventGroup, BIT_LIGHT_SIGNAL, pdFALSE, pdFALSE, portMAX_DELAY);
	HAL_GPIO_TogglePin(LIGHT2_GPIO_Port, LIGHT2_Pin);
	osDelay(500);
  }
  /* USER CODE END StartLightSignal */
}

/* USER CODE BEGIN Header_StartSoundAlarm */
/**
* @brief Function implementing the SoundAlarm thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSoundAlarm */
void StartSoundAlarm(void const * argument)
{
  /* USER CODE BEGIN StartSoundAlarm */
  /* Infinite loop */
  for(;;)
  {
	  xEventGroupWaitBits(xControlEventGroup, BIT_SOUND_ALARM, pdFALSE, pdFALSE, portMAX_DELAY);
	  HAL_GPIO_TogglePin(BOOZER_GPIO_Port, BOOZER_Pin);
	  osDelay(150);
	  HAL_GPIO_TogglePin(BOOZER_GPIO_Port, BOOZER_Pin);
	  osDelay(1000);
  }
  /* USER CODE END StartSoundAlarm */
}

/* USER CODE BEGIN Header_StartDataProtect */
/**
* @brief Function implementing the DataProtect thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDataProtect */
void StartDataProtect(void const * argument)
{
  /* USER CODE BEGIN StartDataProtect */
	uint32_t SecRecDemage = 0;
	float PercDem = 0;
  /* Infinite loop */
  for(;;)
  {
	  if(NumSuccessPack>0){
		  PercDem = ((float)PayLoadCRCError/NumSuccessPack);
		  if(PercDem > 0.75){
			  Label:
			  SecRecDemage++;
			  if(SecRecDemage > 0){
				  xEventGroupSetBits(xControlEventGroup, BIT_LIGHT_SIGNAL);
				  xEventGroupSetBits(xControlEventGroup, BIT_SOUND_ALARM);

				  xEventGroupClearBits(xControlEventGroup, BIT_ACCEPT_PAC);
				  ZeroCommArr();
				  osDelay(1000);
				  xEventGroupClearBits(xControlEventGroup, BIT_ENGIN_START);
				  xEventGroupSetBits(xControlEventGroup, BIT_ACCEPT_PAC);
			  }
		  }
		  else {
			  if(SecRecDemage > 0){
				  if(BatteryStatus == BATTERY_OK){
					  // If the battery is OK, turn off the alarm.
					  xEventGroupClearBits(xControlEventGroup, BIT_LIGHT_SIGNAL);
					  xEventGroupClearBits(xControlEventGroup, BIT_SOUND_ALARM);
					  xEventGroupSetBits(xControlEventGroup, BIT_ENGIN_START);
					  SecRecDemage = 0;
				  }
			  }
		  }
	  }
	  else {

		  goto Label;
	  }
	  PayLoadCRCError = 0;
	  NumSuccessPack = 0;

	  osDelay(1000);
  }
  /* USER CODE END StartDataProtect */
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
