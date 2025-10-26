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
#include "22keypadTCA8418.h"
#include "handl_ssd1306.h"
#include "PalenishIT_Proc.h"
#include "ADCStick.h"
#include "stm32f1xx_hal_conf.h"
#include "SX1276_Start.h"
#include "LoRa_MenuV2.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern I2C_HandleTypeDef hi2c1;
extern RTC_HandleTypeDef hrtc;
extern SPI_HandleTypeDef hspi2;
extern ADC_HandleTypeDef hadc1;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
//#define Palenish_Test

// NOTE!!! Moskito V0.3 does not use PABOOST
//So use the directive MOSKITO V0.2
// Maximum power without using this output is 14dBm
#define MoskitoV02
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define NSS_Pin GPIO_PIN_12
#define NSS_GPIO_Port GPIOB
#define Reset_Pin GPIO_PIN_8
#define Reset_GPIO_Port GPIOA
#define DIO0_Pin GPIO_PIN_9
#define DIO0_GPIO_Port GPIOA
#define DIO0_EXTI_IRQn EXTI9_5_IRQn
#define DIO1_Pin GPIO_PIN_10
#define DIO1_GPIO_Port GPIOA
#define DIO2_Pin GPIO_PIN_11
#define DIO2_GPIO_Port GPIOA
#define DIO3_Pin GPIO_PIN_12
#define DIO3_GPIO_Port GPIOA
#define RESET_TCA_Pin GPIO_PIN_4
#define RESET_TCA_GPIO_Port GPIOB
#define INT_TCA_Pin GPIO_PIN_5
#define INT_TCA_GPIO_Port GPIOB
#define INT_TCA_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
