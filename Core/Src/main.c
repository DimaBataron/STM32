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
  *
  * Don't forget to comment   HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
  * IN MX_GPIO_Init()  so as not to disrupt the logic of the work.
  *
  * There is not enough memory for output to UART
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

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
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_tx;

osThreadId ServoHandle;
osThreadId Servo2Handle;
osThreadId EngineTestHandle;
osThreadId LoRaRxHandle;
osThreadId OutUartHandle;
osThreadId RxErrorHandle;
osThreadId VoltMeasHandle;
osThreadId LightSignalHandle;
osThreadId SoundAlarmHandle;
osThreadId ControlTaskHandle;
osSemaphoreId SemDMA_LoRaHandle;
osSemaphoreId SemDMA_UARTHandle;
osSemaphoreId Sem_Time_RxErrHandle;
osSemaphoreId SemDMA_VoltMeasHandle;
osSemaphoreId SemControlTaskHandle;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM2_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM1_Init(void);
static void MX_ADC1_Init(void);
void StartServo(void const * argument);
void StartServo2(void const * argument);
void StartEngineTest(void const * argument);
void StartLoRaRx(void const * argument);
void StartOutUart(void const * argument);
void StartRxError(void const * argument);
void StartVoltMeas(void const * argument);
void StartLightSignal(void const * argument);
void StartSoundAlarm(void const * argument);
void StartControlTask(void const * argument);

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
//  osSemaphoreDef(SemDMA_LoRa);
//  SemDMA_LoRaHandle = osSemaphoreCreate(osSemaphore(SemDMA_LoRa), 1);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM3_Init();
  MX_TIM2_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of SemDMA_LoRa */
  osSemaphoreDef(SemDMA_LoRa);
  SemDMA_LoRaHandle = osSemaphoreCreate(osSemaphore(SemDMA_LoRa), 1);

  /* definition and creation of SemDMA_UART */
  osSemaphoreDef(SemDMA_UART);
  SemDMA_UARTHandle = osSemaphoreCreate(osSemaphore(SemDMA_UART), 1);

  /* definition and creation of Sem_Time_RxErr */
  osSemaphoreDef(Sem_Time_RxErr);
  Sem_Time_RxErrHandle = osSemaphoreCreate(osSemaphore(Sem_Time_RxErr), 1);

  /* definition and creation of SemDMA_VoltMeas */
  osSemaphoreDef(SemDMA_VoltMeas);
  SemDMA_VoltMeasHandle = osSemaphoreCreate(osSemaphore(SemDMA_VoltMeas), 1);

  /* definition and creation of SemControlTask */
  osSemaphoreDef(SemControlTask);
  SemControlTaskHandle = osSemaphoreCreate(osSemaphore(SemControlTask), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  osSemaphoreWait(SemControlTaskHandle, 0);
  osSemaphoreWait(SemDMA_VoltMeasHandle, 0);
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Servo */
  osThreadDef(Servo, StartServo, osPriorityLow, 0, 150);
  ServoHandle = osThreadCreate(osThread(Servo), NULL);

  /* definition and creation of Servo2 */
  osThreadDef(Servo2, StartServo2, osPriorityLow, 0, 150);
  Servo2Handle = osThreadCreate(osThread(Servo2), NULL);

  /* definition and creation of EngineTest */
  osThreadDef(EngineTest, StartEngineTest, osPriorityBelowNormal, 0, 150);
  EngineTestHandle = osThreadCreate(osThread(EngineTest), NULL);

  /* definition and creation of LoRaRx */
  osThreadDef(LoRaRx, StartLoRaRx, osPriorityAboveNormal, 0, 300);
  LoRaRxHandle = osThreadCreate(osThread(LoRaRx), NULL);

  /* definition and creation of OutUart */
//  osThreadDef(OutUart, StartOutUart, osPriorityLow, 0, 512);
//  OutUartHandle = osThreadCreate(osThread(OutUart), NULL);

  /* definition and creation of RxError */
  osThreadDef(RxError, StartRxError, osPriorityNormal, 0, 300);
  RxErrorHandle = osThreadCreate(osThread(RxError), NULL);

  /* definition and creation of VoltMeas */
  osThreadDef(VoltMeas, StartVoltMeas, osPriorityLow, 0, 256);
  VoltMeasHandle = osThreadCreate(osThread(VoltMeas), NULL);

  /* definition and creation of LightSignal */
  osThreadDef(LightSignal, StartLightSignal, osPriorityLow, 0, 128);
  LightSignalHandle = osThreadCreate(osThread(LightSignal), NULL);

  /* definition and creation of SoundAlarm */
  osThreadDef(SoundAlarm, StartSoundAlarm, osPriorityLow, 0, 128);
  SoundAlarmHandle = osThreadCreate(osThread(SoundAlarm), NULL);

  /* definition and creation of ControlTask */
  osThreadDef(ControlTask, StartControlTask, osPriorityHigh, 0, 200);
  ControlTaskHandle = osThreadCreate(osThread(ControlTask), NULL);

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
  sConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;
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
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
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
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
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
  /* DMA1_Channel4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 6, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);

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
  HAL_GPIO_WritePin(GPIOA, P_CONTROL_Pin|LOAD2_Pin|LOAD1_Pin|NSS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, M3_IN2_Pin|M3_IN1_Pin|M4_IN1_Pin|M4_IN2_Pin
                          |STBY_M3_M4_Pin|BOOZER_Pin|Reset_Pin|STBY_M1_M2_Pin
                          |M2_IN2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LIGHT2_GPIO_Port, LIGHT2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LIGHT1_GPIO_Port, LIGHT1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : M2_IN1_Pin M1_IN1_Pin M1_IN2_Pin */
  GPIO_InitStruct.Pin = M2_IN1_Pin|M1_IN1_Pin|M1_IN2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : P_CONTROL_Pin LOAD2_Pin LOAD1_Pin */
  GPIO_InitStruct.Pin = P_CONTROL_Pin|LOAD2_Pin|LOAD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : M3_IN2_Pin M3_IN1_Pin M4_IN1_Pin M4_IN2_Pin
                           STBY_M3_M4_Pin STBY_M1_M2_Pin M2_IN2_Pin */
  GPIO_InitStruct.Pin = M3_IN2_Pin|M3_IN1_Pin|M4_IN1_Pin|M4_IN2_Pin
                          |STBY_M3_M4_Pin|STBY_M1_M2_Pin|M2_IN2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : BOOZER_Pin */
  GPIO_InitStruct.Pin = BOOZER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BOOZER_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LIGHT2_Pin Reset_Pin */
  GPIO_InitStruct.Pin = LIGHT2_Pin|Reset_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LIGHT1_Pin NSS_Pin */
  GPIO_InitStruct.Pin = LIGHT1_Pin|NSS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : DIO0_Pin */
  GPIO_InitStruct.Pin = DIO0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(DIO0_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 0);
//  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
//  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartServo */
/**
  * @brief  Function implementing the Servo thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartServo */
void StartServo(void const * argument)
{
  /* USER CODE BEGIN 5 */
	ServoStartInit(&htim3, TIM_CHANNEL_1);
 	int8_t TurnNum = 0;
	float angle = 0;
	float RotAngle = 1.4111;
	osDelay(2000);
  /* Infinite loop */
  for(;;)
  {
//	  for every degree of rotation 1.4111111111111111111111111111111
	  do {
		  angle += 10;
		  TurnNum = (int8_t)(angle * RotAngle);
		  SteeringWheel(&htim3, TIM_CHANNEL_1, TurnNum);
		  osDelay(1000);
	  }
	  while(angle<90);
	  do {
		  angle -= 10;
		  TurnNum = (int8_t)(angle * RotAngle);
		  SteeringWheel(&htim3, TIM_CHANNEL_1, TurnNum);
		  osDelay(1000);
	  }
	  while(angle>-90);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartServo2 */
/**
* @brief Function implementing the Servo2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartServo2 */
void StartServo2(void const * argument)
{
  /* USER CODE BEGIN StartServo2 */
	ServoStartInit(&htim3, TIM_CHANNEL_2);
	 	int8_t TurnNum = 0;
		double angle = 0;
		double RotAngle = 1.4111;
		osDelay(1000);
  /* Infinite loop */
  for(;;)
  {
	  //	  for every degree of rotation 1.4111111111111111111111111111111
	  	  do {
	  		  angle += 10;
	  		  TurnNum = (int8_t)(angle * RotAngle);
	  		  SteeringWheel(&htim3, TIM_CHANNEL_2, TurnNum);
	  		  osDelay(1000);
	  	  }
	  	  while(angle<90);
	  	  do {
	  		  angle -= 10;
	  		  TurnNum = (int8_t)(angle * RotAngle);
	  		  SteeringWheel(&htim3, TIM_CHANNEL_2, TurnNum);
	  		  osDelay(1000);
	  	  }
	  	  while(angle>-90);
  }
  /* USER CODE END StartServo2 */
}

/* USER CODE BEGIN Header_StartEngineTest */
/**
* @brief Function implementing the EngineTest thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartEngineTest */
void StartEngineTest(void const * argument)
{
  /* USER CODE BEGIN StartEngineTest */
	int8_t acceleration = 5;
  /* Infinite loop */
  for(;;)
  {
//	  ==============================================
//	���� ������ ���������.
	  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	  //�������� � ���� �������.
	  do{
		  Brushed2DC_Control(&htim2, TIM_CHANNEL_1, TIM_CHANNEL_2, acceleration, \
				  	  	  	  DirectRotCW, DirectRotCCW);
		  acceleration += 10;
		  osDelay(1000);
	  }
	  while(acceleration < 66);

	//�������� �������.
	  do{
		  Brushed2DC_Control(&htim2, TIM_CHANNEL_1, TIM_CHANNEL_2, acceleration, \
				  	  	  	  	DirectRotCW, DirectRotCCW);
		  acceleration -= 10;
		  osDelay(1000);
	  }
	  while(acceleration > -66);
	  HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);

//	  =================================================
//	  ���� ������� ���������
	  acceleration = 5;
	  Brushed2DC_Control(&htim2, TIM_CHANNEL_1, TIM_CHANNEL_2, acceleration, \
	  	  				  	  	  	  DirectRotCW, DirectRotCCW);
	  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	  	  do{
	  		  Brushed2DC_Control(&htim2, TIM_CHANNEL_1, TIM_CHANNEL_2, acceleration, \
	  				  	  	  	  DirectRotCW, DirectRotCCW);
	  		  acceleration += 10;
	  		  osDelay(1000);
	  	  }
	  	  while(acceleration < 66);

	  	//�������� �������.
	  	  do{
	  		  Brushed2DC_Control(&htim2, TIM_CHANNEL_1, TIM_CHANNEL_2, acceleration, \
	  				  	  	  	  	DirectRotCW, DirectRotCCW);
	  		  acceleration -= 10;
	  		  osDelay(1000);
	  	  }
	  	  while(acceleration > -66);
	 HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);

//	 ===============================================
//	���� ���� ���������� �����
	 acceleration = 5;
	 Brushed2DC_Control(&htim2, TIM_CHANNEL_1, TIM_CHANNEL_2, acceleration, \
	 	  	  				  	  	  	  DirectRotCW, DirectRotCCW);
	 HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	 HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
 	  do{
 		  Brushed2DC_Control(&htim2, TIM_CHANNEL_1, TIM_CHANNEL_2, acceleration, \
 				  	  	  	  DirectRotCW, DirectRotCCW);
 		  acceleration += 10;
 		  osDelay(1000);
 	  }
 	  while(acceleration < 66);

 	//�������� �������.
 	  do{
 		  Brushed2DC_Control(&htim2, TIM_CHANNEL_1, TIM_CHANNEL_2, acceleration, \
 				  	  	  	  	DirectRotCW, DirectRotCCW);
 		  acceleration -= 10;
 		  osDelay(1000);
 	  }
 	  while(acceleration > -66);
 	 HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
 	 HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
 	 acceleration = 0;
//������� ������
    osDelay(1);
  }
  /* USER CODE END StartEngineTest */
}

/* USER CODE BEGIN Header_StartLoRaRx */
/**
* @brief Function implementing the LoRaRx thread.
* @param argument: Not used
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
  /* USER CODE BEGIN StartLoRaRx */
	SX1276Init();
	InitRxContLoRa();
	StartRxContLoRa();
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
  /* Infinite loop */
  for(;;)
  {		// Waits for semaphore from DMA
	  xSemaphoreTake(SemDMA_LoRaHandle,portMAX_DELAY);

	  // generates an array of commands based on the received data
	  CalcRxCommands();
	  StartRxContLoRa();
  }
  /* USER CODE END StartLoRaRx */
}

/* USER CODE BEGIN Header_StartOutUart */
/**
* @brief Function implementing the OutUart thread.
* @param argument: Not used
* @retval None
* PA10 	USART1_RX
* PA9	USART1_TX
* putty.exe -serial COM7 -sercfg 9600,8,n,1,N
*/
/* USER CODE END Header_StartOutUart */
void StartOutUart(void const * argument)
{
  /* USER CODE BEGIN StartOutUart */
//	TransArrayLayout();
    OutStringTask();
  /* Infinite loop */
  for(;;)
  {
	osDelay(3000);
    xSemaphoreTake(SemDMA_UARTHandle,portMAX_DELAY);
    OutStringTask();
  }
  /* USER CODE END StartOutUart */
}

/* USER CODE BEGIN Header_StartRxError */
/**
* @brief Function implementing the RxError thread.
* @param argument: Not used
* @retval None
* LIGHT1 == PA8
* LIGHT2 == PB15
* BOOZER == PB14
*/
/* USER CODE END Header_StartRxError */
void StartRxError(void const * argument)
{
  /* USER CODE BEGIN StartRxError */
	//I turn on the timer
	HAL_TIM_Base_Start_IT(&htim1);
  /* Infinite loop */
  for(;;)
  {
	  // Waits for a signal from an interrupt
	  xSemaphoreTake(Sem_Time_RxErrHandle,portMAX_DELAY);
	  // Zeroes out the array of commands and pauses the receiving task
	  SX1276LoRaSetOpMode( RFLR_OPMODE_STANDBY ); // Stopping receiving packages.
	  ZeroCommArr();	// I reset all commands.
	  vTaskSuspend(LoRaRxHandle);

	  //Start light and sound alarm
	  vTaskResume(SoundAlarmHandle);
	  vTaskResume(LightSignalHandle);

	  osDelay(800);
	  vTaskResume(LoRaRxHandle);
	  StartRxContLoRa();

  }
  /* USER CODE END StartRxError */
}

/* USER CODE BEGIN Header_StartVoltMeas */
/**
* @brief Function implementing the VoltMeas thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartVoltMeas */
void StartVoltMeas(void const * argument)
{
  /* USER CODE BEGIN StartVoltMeas */
	float U = 0;
	// calibration to improve accuracy
	HAL_ADCEx_Calibration_Start(&hadc1);
  /* Infinite loop */
  for(;;)
  {

	  StartMeasure();
	  //Waiting for a semophore indicating that the transformation is complete.
  	  xSemaphoreTake(SemDMA_VoltMeasHandle,portMAX_DELAY);

	   //calculation of the obtained values
  	  U = VoltageCalc();

  	  BatteryStatus = CheckBatVolt(U);

  	  switch (BatteryStatus) {

  	  case VOLT_CAUTION :{ // Unlocking the Low Voltage Alarm Task
  		  vTaskResume(LightSignalHandle);
  		  break;
  	  }
  	  case VOLT_SHUTDOWN :{ // unlock alarm and block all tasks
  		  //turns off the camera
  		  HAL_GPIO_WritePin(P_CONTROL_GPIO_Port, P_CONTROL_Pin, GPIO_PIN_RESET);

  		  vTaskSuspend(ServoHandle);
  		  vTaskSuspend(Servo2Handle);
  		  vTaskSuspend(EngineTestHandle);
  		  //turns off the engines.!!!!


  		  vTaskSuspend(LoRaRxHandle);
//  		  vTaskSuspend(OutUartHandle);
  		  vTaskSuspend(RxErrorHandle);

  		  vTaskResume(LightSignalHandle);
  	  	  vTaskResume(SoundAlarmHandle);
  	  	  vTaskSuspend(NULL);

  		  break;
  	  }

  	  }
  	//Stops itself. So as not to start the measurements again.
	  osDelay(4000);
  }
  /* USER CODE END StartVoltMeas */
}

/* USER CODE BEGIN Header_StartLightSignal */
/**
* @brief Function implementing the LightSignal thread.
* @param argument: Not used
* @retval None
* Light signaling
*/
/* USER CODE END Header_StartLightSignal */
void StartLightSignal(void const * argument)
{
  /* USER CODE BEGIN StartLightSignal */
	vTaskSuspend(NULL);
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_WritePin(LIGHT1_GPIO_Port, LIGHT1_Pin, GPIO_PIN_RESET);
	  osDelay(500);
	  HAL_GPIO_WritePin(LIGHT1_GPIO_Port, LIGHT1_Pin, GPIO_PIN_SET);
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
	vTaskSuspend(NULL);
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_WritePin(BOOZER_GPIO_Port, BOOZER_Pin, GPIO_PIN_SET);
	  osDelay(500);
	  HAL_GPIO_WritePin(BOOZER_GPIO_Port, BOOZER_Pin, GPIO_PIN_RESET);
	  osDelay(500);
  }
  /* USER CODE END StartSoundAlarm */
}

/* USER CODE BEGIN Header_StartControlTask */
/**
* @brief Function implementing the ControlTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartControlTask */
void StartControlTask(void const * argument)
{
  /* USER CODE BEGIN StartControlTask */
  /* Infinite loop */
  for(;;)
  {
	  xSemaphoreTake(SemControlTaskHandle,portMAX_DELAY);
	  HAL_GPIO_WritePin(BOOZER_GPIO_Port, BOOZER_Pin, GPIO_PIN_RESET);
	  vTaskSuspend(SoundAlarmHandle);
	  HAL_GPIO_WritePin(LIGHT1_GPIO_Port, LIGHT1_Pin, GPIO_PIN_SET);
	  vTaskSuspend(LightSignalHandle);
  }
  /* USER CODE END StartControlTask */
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
