/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Servo.h"
#include "BrushedDC.h"
#include "SX1276_Start.h"
#include "ChaeburatorIT_Proc.h"
#include "cmsis_os.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
//#define MoskitoV02
#define Ra_02_AI_Thinker

extern SPI_HandleTypeDef hspi1;
extern osSemaphoreId SemDMA_LoRaHandle;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define M2_IN1_Pin GPIO_PIN_13
#define M2_IN1_GPIO_Port GPIOC
#define M1_IN1_Pin GPIO_PIN_14
#define M1_IN1_GPIO_Port GPIOC
#define M1_IN2_Pin GPIO_PIN_15
#define M1_IN2_GPIO_Port GPIOC
#define M1_PWM_Pin GPIO_PIN_0
#define M1_PWM_GPIO_Port GPIOA
#define M2_PWM_Pin GPIO_PIN_1
#define M2_PWM_GPIO_Port GPIOA
#define M3_PWM_Pin GPIO_PIN_2
#define M3_PWM_GPIO_Port GPIOA
#define M4_PWM_Pin GPIO_PIN_3
#define M4_PWM_GPIO_Port GPIOA
#define Servo1_Pin GPIO_PIN_6
#define Servo1_GPIO_Port GPIOA
#define Servo2_Pin GPIO_PIN_7
#define Servo2_GPIO_Port GPIOA
#define M3_IN2_Pin GPIO_PIN_2
#define M3_IN2_GPIO_Port GPIOB
#define M3_IN1_Pin GPIO_PIN_10
#define M3_IN1_GPIO_Port GPIOB
#define M4_IN1_Pin GPIO_PIN_11
#define M4_IN1_GPIO_Port GPIOB
#define M4_IN2_Pin GPIO_PIN_12
#define M4_IN2_GPIO_Port GPIOB
#define STBY_M3_M4_Pin GPIO_PIN_13
#define STBY_M3_M4_GPIO_Port GPIOB
#define NSS_Pin GPIO_PIN_15
#define NSS_GPIO_Port GPIOA
#define Reset_Pin GPIO_PIN_6
#define Reset_GPIO_Port GPIOB
#define DIO0_Pin GPIO_PIN_7
#define DIO0_GPIO_Port GPIOB
#define DIO0_EXTI_IRQn EXTI9_5_IRQn
#define STBY_M1_M2_Pin GPIO_PIN_8
#define STBY_M1_M2_GPIO_Port GPIOB
#define M2_IN2_Pin GPIO_PIN_9
#define M2_IN2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
