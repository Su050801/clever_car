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
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "pic.h"
#include "stdbool.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define		DIRECTION     					 0      //方向选择,0：出库左转  1：出库右转
#define		SPEED     							1100    //直线速度，正常跑的速度1280
/////////////////////////三叉///////////////////////////////
#define		SANCHA_L      					500			//三叉转弯的差速
#define		SANCHA_R      					100

#define		SANCHA_DELAY      			400			//三叉转弯的时间
#define		SANCHA_SPEED      			1000			//三叉速度1200
/////////////////////////环岛///////////////////////////////
#define		HUANDAO_ZHI      				1000		//环岛直线速度
#define		HUANDAO_ZHI_BAIS_R      100			//环岛直线偏移量
#define		HUANDAO_ZHI_BAIS_L      100
#define		HUANDAO_ZHI_DELAY      	500			//环岛直线时间

#define		HUANDAO_TURN_L      		400			//环岛转弯差速
#define		HUANDAO_TURN_R      		1000
#define		HUANDAO_TURN_DELAY      350			//环岛转弯时间
#define		HUANDAO_SPEED      			950			//环岛速度
/////////////////////////入库///////////////////////////////
#define		RUKU_L      						200			//入库差速
#define		RUKU_R      						900
#define		RUKU_DELAY      				600			//转弯时间
////////////////////////////////////////////////////////////

uint8_t STOP_FLAG_HUANDAO=0;
uint8_t STOP_FLAG_SANCHA = 0;
uint8_t OUT_FLAG_SANCHA = 0;
uint16_t TIME_FLAG_SANCHA = 0;
uint16_t TIME_FLAG_SANCHA_1 = 0;
uint8_t CITIE_FLAG_1 = 0;
extern float Turn_Kd,Turn_Kp;
uint16_t count;
uint16_t ADC_Value[5];
uint8_t  show=0;
extern float Turn_Kd,Turn_Kp;
extern float   Turn_Get;
extern short   gyrox, gyroy, gyroz;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
  MX_ADC2_Init();
  MX_TIM1_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
//	HAL_TIM_Base_Start_IT(&htim6);
	LCD_Init();
	LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
	MPU_Init();
	mpu_dmp_init();
	LCD_ShowString(0,0,(uint8_t*)"1:",GREEN,BLACK,16,1);
	LCD_ShowString(0,16,(uint8_t*)"2:",GREEN,BLACK,16,1);
	LCD_ShowString(0,32,(uint8_t*)"3:",GREEN,BLACK,16,1);
	LCD_ShowString(0,48,(uint8_t*)"4:",GREEN,BLACK,16,1);
	LCD_ShowString(0,64,(uint8_t*)"5:",GREEN,BLACK,16,1);
	Buzzer(1);
	CarInit(0,STOP);
	if(DIRECTION)
	{
		htim1.Instance->CCR1 = 900;
		htim1.Instance->CCR2 = 500;
	}
	else
	{
		htim1.Instance->CCR1 = 500;
		htim1.Instance->CCR2 = 900;
	}	
	HAL_Delay(600);
	HAL_ADC_Start_DMA(&hadc2,(uint32_t *)ADC_Value,sizeof(ADC_Value)/sizeof(ADC_Value[0]));
  CarInit(SPEED,RUN);
	Buzzer(0);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		MPU_Get_Gyroscope(&gyrox, &gyroy, &gyroz);
		
		if(show)
		{
			LCD_ShowIntNum(20,0,ADC_Value[2],4,GREEN,BLACK,16);
			LCD_ShowIntNum(20,16,ADC_Value[1],4,GREEN,BLACK,16);
			LCD_ShowIntNum(20,32,ADC_Value[3],4,GREEN,BLACK,16);
			LCD_ShowIntNum(20,48,ADC_Value[4],4,GREEN,BLACK,16);
			LCD_ShowIntNum(20,64,ADC_Value[0],4,GREEN,BLACK,16);
			LCD_ShowIntNum(60,0,TIME_FLAG_SANCHA_1,4,GREEN,BLACK,16);
			
			if(Turn_Get > 0)
				LCD_ShowIntNum(100,0,Turn_Get,4,GREEN,BLACK,16);
			else
				LCD_ShowIntNum(100,0,-Turn_Get,4,RED,BLACK,16);
		}
		
		if((ADC_Value[0]<10)&&(ADC_Value[1]<10)&&(ADC_Value[2]<10)&&(ADC_Value[3]<100&&(ADC_Value[4]<10)))CarInit(0,STOP);

		else if((ADC_Value[1]<1000)&&(ADC_Value[1]>700)&&(ADC_Value[3]<1500)&&(ADC_Value[3]>800)&&(ADC_Value[4]>700)&&(ADC_Value[4]<1000)&&(STOP_FLAG_SANCHA != 2)&&(TIME_FLAG_SANCHA_1 == 0))
		{
			TIME_FLAG_SANCHA_1 = 0;
			Tricycle.State = STOP;
			htim1.Instance->CCR1 = 0;
			htim1.Instance->CCR2 = 0;
			Buzzer(1);
			HAL_Delay(200);
			Buzzer(0);
			HAL_TIM_Base_Start_IT(&htim6);
			if(STOP_FLAG_SANCHA==0)
			{
				STOP_FLAG_SANCHA=1;
			}
			else if(STOP_FLAG_SANCHA==1)
			{
				STOP_FLAG_SANCHA=2;
			}	
			if(STOP_FLAG_SANCHA == 1)
			{
				Turn_Kp = 0.9;
				htim1.Instance->CCR1 = SANCHA_L;
			  htim1.Instance->CCR2 = SANCHA_R;
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET);
				HAL_Delay(SANCHA_DELAY);
				Tricycle.Speed = SANCHA_SPEED;
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_RESET);
				Tricycle.State = RUN;
				LED_R(1);
				OUT_FLAG_SANCHA = 1;
			}
			else if(STOP_FLAG_SANCHA == 2)
			{
				Turn_Kp = 0.9;
				htim1.Instance->CCR1 = SANCHA_R;
			  htim1.Instance->CCR2 = SANCHA_L;
				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,GPIO_PIN_RESET);
				HAL_Delay(SANCHA_DELAY);
				Tricycle.Speed = SANCHA_SPEED;
				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,GPIO_PIN_SET);
				Tricycle.State = RUN;
				LED_G(1);
				OUT_FLAG_SANCHA = 1;
			}	
		}
		
		else if((ADC_Value[1]>1100)&&(OUT_FLAG_SANCHA==1))
		{
			if(++TIME_FLAG_SANCHA>400)
			{
				Turn_Kp = 0.8;//0.8
				Tricycle.Speed = SPEED;
				OUT_FLAG_SANCHA = 0;
				TIME_FLAG_SANCHA = 0;
			}
		}
		else if((ADC_Value[1]>1800)&&(ADC_Value[3]>1800)&&(ADC_Value[4]>1800)&&(STOP_FLAG_HUANDAO==0)&&(ADC_Value[2]>500)&&(ADC_Value[0]<100))
		{
			HAL_TIM_Base_Start_IT(&htim6);
			Tricycle.State = STOP;
			STOP_FLAG_HUANDAO = 1;
			Buzzer(1);
			htim1.Instance->CCR1 = HUANDAO_ZHI+HUANDAO_ZHI_BAIS_L;
			htim1.Instance->CCR2 = HUANDAO_ZHI;
			HAL_Delay(HUANDAO_ZHI_DELAY);
			Buzzer(0);
			htim1.Instance->CCR1 = HUANDAO_TURN_L;
			htim1.Instance->CCR2 = HUANDAO_TURN_R;
			HAL_Delay(HUANDAO_TURN_DELAY);
			Tricycle.Speed = HUANDAO_SPEED;
			Tricycle.State = RUN;
			LED_R(1);
		}
		else if((ADC_Value[1]>1800)&&(ADC_Value[3]>1800)&&(ADC_Value[4]>1800)&&(STOP_FLAG_HUANDAO==0)&&(ADC_Value[0]>500)&&((ADC_Value[2]<100)))
		{
			HAL_TIM_Base_Start_IT(&htim6);
			Tricycle.State = STOP;
			STOP_FLAG_HUANDAO = 1;
			Buzzer(1);
			htim1.Instance->CCR1 = HUANDAO_ZHI;
			htim1.Instance->CCR2 = HUANDAO_ZHI+HUANDAO_ZHI_BAIS_R;
			HAL_Delay(HUANDAO_ZHI_DELAY);
			Buzzer(0);
			htim1.Instance->CCR1 = HUANDAO_TURN_R;
			htim1.Instance->CCR2 = HUANDAO_TURN_L;
			HAL_Delay(HUANDAO_TURN_DELAY);
			Tricycle.Speed = HUANDAO_SPEED;
			Tricycle.State = RUN;
			LED_R(1);
		}
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_6))
		{
			CITIE_FLAG_1++;
			if(CITIE_FLAG_1 == 2)
			{
				Tricycle.State = STOP;
				
				if(DIRECTION)
				{
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,GPIO_PIN_SET);
					htim1.Instance->CCR1 = RUKU_R;
					htim1.Instance->CCR2 = RUKU_L;
				}
				else
				{
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,GPIO_PIN_RESET);
					htim1.Instance->CCR1 = RUKU_L;
					htim1.Instance->CCR2 = RUKU_R;
				}
				HAL_Delay(RUKU_DELAY);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,GPIO_PIN_RESET);
				htim1.Instance->CCR1 = 600;
				htim1.Instance->CCR2 = 600;
				HAL_Delay(RUKU_DELAY);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,GPIO_PIN_RESET);
			}
			HAL_GPIO_TogglePin(BUZZER_GPIO_Port,BUZZER_Pin);
			HAL_Delay(100);
			HAL_GPIO_TogglePin(BUZZER_GPIO_Port,BUZZER_Pin);
		}
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV2;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
