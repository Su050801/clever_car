/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
extern float a1;
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

/* USER CODE BEGIN Private defines */
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x02000000+((addr & 0x00FFFFFF)<<5)+(bitnum<<2)) 
/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 	//输出为高电平		
#define digitalLo(p,i)		 {p->BRR=i;}	 	//输出低电平
#define digitalToggle(p,i) {p->ODR ^=i;} 		//输出反转状态


// 把一个地址转换成一个指针
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 


// 把位带别名区地址转换成指针
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))   


// GPIO ODR 和 IDR 寄存器地址映射 
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C   
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C   
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C   
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C   
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C   
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C      
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C      
  
#define GPIOA_IDR_Addr    (GPIOA_BASE+8)  //0x40010808   
#define GPIOB_IDR_Addr    (GPIOB_BASE+8)  //0x40010C08   
#define GPIOC_IDR_Addr    (GPIOC_BASE+8)  //0x40011008   
#define GPIOD_IDR_Addr    (GPIOD_BASE+8)  //0x40011408   
#define GPIOE_IDR_Addr    (GPIOE_BASE+8)  //0x40011808   
#define GPIOF_IDR_Addr    (GPIOF_BASE+8)  //0x40011A08   
#define GPIOG_IDR_Addr    (GPIOG_BASE+8)  //0x40011E08 



// 单独操作 GPIO的某一个IO口，n(0,1,2...16),n表示具体是哪一个IO口
#define PAout(n)   BIT_ADDR(0x4001080C,n)  //输出   
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入   
  
#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出   
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入   
  
#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出   
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入   
  
#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出   
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入   
  
#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出   
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入  
  
#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出   
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入  
  
#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出   
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
