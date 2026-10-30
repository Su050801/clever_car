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
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "lcd_init.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "CarSys.h"
#include "gpio.h"
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
#define SPEED_FAST 1100;

#define KEY1_Pin GPIO_PIN_13
#define KEY1_GPIO_Port GPIOC
#define KEY1_EXTI_IRQn EXTI15_10_IRQn
#define KEY2_Pin GPIO_PIN_14
#define KEY2_GPIO_Port GPIOC
#define KEY2_EXTI_IRQn EXTI15_10_IRQn
#define KEY3_Pin GPIO_PIN_15
#define KEY3_GPIO_Port GPIOC
#define KEY3_EXTI_IRQn EXTI15_10_IRQn
#define MPU_SDA_Pin GPIO_PIN_0
#define MPU_SDA_GPIO_Port GPIOB
#define MPU_SCL_Pin GPIO_PIN_1
#define MPU_SCL_GPIO_Port GPIOB
#define MPU_INT_Pin GPIO_PIN_2
#define MPU_INT_GPIO_Port GPIOB
#define MPU_INT_EXTI_IRQn EXTI2_IRQn
#define LED_G_Pin GPIO_PIN_10
#define LED_G_GPIO_Port GPIOB
#define BUZZER_Pin GPIO_PIN_11
#define BUZZER_GPIO_Port GPIOB
#define LED_B_Pin GPIO_PIN_12
#define LED_B_GPIO_Port GPIOB
#define LED_R_Pin GPIO_PIN_13
#define LED_R_GPIO_Port GPIOB
#define AIN2_Pin GPIO_PIN_14
#define AIN2_GPIO_Port GPIOB
#define AIN1_Pin GPIO_PIN_15
#define AIN1_GPIO_Port GPIOB
#define STOP_Pin GPIO_PIN_6
#define STOP_GPIO_Port GPIOC
#define STOP_EXTI_IRQn EXTI9_5_IRQn
#define BIN2_Pin GPIO_PIN_10
#define BIN2_GPIO_Port GPIOC
#define BIN1_Pin GPIO_PIN_11
#define BIN1_GPIO_Port GPIOC
#define LCD_CS_Pin GPIO_PIN_3
#define LCD_CS_GPIO_Port GPIOB
#define LCD_SCL_Pin GPIO_PIN_4
#define LCD_SCL_GPIO_Port GPIOB
#define LCD_SDA_Pin GPIO_PIN_5
#define LCD_SDA_GPIO_Port GPIOB
#define LCD_RS_Pin GPIO_PIN_6
#define LCD_RS_GPIO_Port GPIOB
#define LCD_RST_Pin GPIO_PIN_7
#define LCD_RST_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
