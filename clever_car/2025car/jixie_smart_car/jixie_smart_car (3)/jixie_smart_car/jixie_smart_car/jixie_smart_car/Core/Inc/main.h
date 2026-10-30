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

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ADC0_Pin GPIO_PIN_0
#define ADC0_GPIO_Port GPIOA
#define ADC1_Pin GPIO_PIN_1
#define ADC1_GPIO_Port GPIOA
#define ADC2_Pin GPIO_PIN_2
#define ADC2_GPIO_Port GPIOA
#define ADC3_Pin GPIO_PIN_3
#define ADC3_GPIO_Port GPIOA
#define key1_Pin GPIO_PIN_0
#define key1_GPIO_Port GPIOB
#define key2_Pin GPIO_PIN_1
#define key2_GPIO_Port GPIOB
#define TB_AIN2_Pin GPIO_PIN_12
#define TB_AIN2_GPIO_Port GPIOB
#define TB_AIN1_Pin GPIO_PIN_13
#define TB_AIN1_GPIO_Port GPIOB
#define TB_BIN1_Pin GPIO_PIN_14
#define TB_BIN1_GPIO_Port GPIOB
#define TB_BIN2_Pin GPIO_PIN_15
#define TB_BIN2_GPIO_Port GPIOB
#define TB_PWMB_Pin GPIO_PIN_8
#define TB_PWMB_GPIO_Port GPIOA
#define TB_PWMA_Pin GPIO_PIN_11
#define TB_PWMA_GPIO_Port GPIOA
#define MG995_PWM_Pin GPIO_PIN_15
#define MG995_PWM_GPIO_Port GPIOA
#define key3_Pin GPIO_PIN_3
#define key3_GPIO_Port GPIOB
#define key4_Pin GPIO_PIN_4
#define key4_GPIO_Port GPIOB
#define MUP_PIN_Pin GPIO_PIN_5
#define MUP_PIN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
