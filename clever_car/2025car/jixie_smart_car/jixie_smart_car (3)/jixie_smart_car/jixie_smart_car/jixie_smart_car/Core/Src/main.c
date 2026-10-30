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
#include "motor.h"
#include "oled.h"
//#include "MG995.h"
#include "key.h"
#include "MyADC.h"
#include "mpu6050.h"
#include "inv_mpu.h"
//#include "IIC.h"
//#include "inv_mpu_dmp_motion_driver.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
void control(void);
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int MG_out;
extern double Error;
extern uint16_t ADC_Final[5];
extern uint16_t ADC_Value[5];
extern uint16_t ADC_Temp[5];
extern uint16_t ADC_Sum[5];
extern uint16_t ADC_Max;
extern uint16_t ADC_Min;
extern int ADC_UP_L1;
extern uint16_t ADC_DOWN_L1;
extern uint16_t ADC_DOWN_R1;
extern int ADC_DOWN_Min;
//extern int ADC_L2;
extern int ADC_UP_R1;
//extern int ADC_R2;

uint8_t shancha_flag;
uint8_t huandao_flag;
uint8_t shizi_flag;

short Gx,Gy,Gz;
double Error_Last;
//float Kp = -5.5,Kd = 0;//5.5   4.7  4.9  5.05555
float Kp = -4.95,Kd = -3;   // 12V     //4.95   d -3

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	if(htim -> Instance == TIM3)
//	{
//		control();
//	}
//}
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
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
	OLED_Init();
	OLED_Clear();
	mpu_dmp_init();
	MPU_Init();
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_ADCEx_Calibration_Start(&hadc1);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//		Get_ADCValue();
		HAL_ADC_Start_DMA(&hadc1,(uint32_t *)ADC_Value,5);
//		guiyihua();
//		chabihe();
//		control();
		MPU_Get_Gyroscope(&Gx,&Gy,&Gz);
		
//		if(MG_out > 250) MG_out = 250;
//		if(MG_out < -250) MG_out = -250;
//		if(MG_out > -20 && MG_out < 20) MG_out = 0;
//		if(ADC_DOWN_Min <= 50 )
//		{
//			shancha_flag++;
//			if(shancha_flag == 1) MG_out = 100;
//			if(shancha_flag == 2) 
//			{
//				HAL_Delay(200);
//				MG_out = -100;
//				shancha_flag = 0;
//			}
//			
//		}
//		if(ADC_Value[2] > 400 && ADC_Value[4] < 100)
//		{
//			MG_out = -350;
//		}
		
//		Load(7200,7200);
//		if(ADC_Value[3] < 100 && (ADC_Value[2] > 250 && ADC_Value[4] > 250))
//				{
//					Load(0,0);
//					shancha_flag = 1;
//				}
		if(shancha_flag == 0)
		{
			Load(7000,7000);
			if((ADC_Value[1] - ADC_Value[0] > 200) || (ADC_Value[0] - ADC_Value[1] > 200)) Load(5000,5000);  //12V
//			if((ADC_UP_R1 - ADC_UP_L1 > 50) || (ADC_UP_L1 - ADC_UP_R1) > 50) Load(5000, 5000);
		}
//		if(ADC_DOWN_Min < 50 && ADC_DOWN_L1>300 && ADC_DOWN_R1 > 300) 
//		{
//			while(1)
//			{
//				Load(0,0);
//			}
//		}


		
//		if(ADC_Value[3] < 30 ) Load(0,0);  // 12V
//		if(ADC_Value[3] < 30) Load(5000,5000);  // 7.4V
//		if(ADC_Value[3] < 200 && ADC_Value[2] > 200 && ADC_Value[4] > 200)
//		{
//			MG_out = 150;
//		}
//		if(ADC_Value[2] > 400 && ADC_Value[4] < 200)
//		{
//			HAL_Delay(100);
//			TIM2 -> CCR1 = 1150;
//			HAL_Delay(50);
//		}

	
		
//		OLED_ShowNum(1,1,ADC_Value[0],4,OLED_8X16);
//		OLED_ShowNum(1,17,ADC_Value[1],4,OLED_8X16);
//		OLED_ShowNum(1,33,ADC_Value[2],4,OLED_8X16);
//		OLED_ShowNum(1,49,ADC_Value[3],4,OLED_8X16);
//		OLED_ShowNum(41,1,ADC_Value[4],4,OLED_8X16);
//			OLED_ShowNum(41,17,Gz,4,OLED_8X16);
////			OLED_ShowFloatNum(41,17,Gz,2,2,OLED_8X16);
//		OLED_ShowSignedNum(41,17,Gz,3,OLED_8X16);
////	//		OLED_ShowFloatNum(41,33,Error,1,6,OLED_8X16);
//		OLED_Update();
		TIM2 -> CCR1 = 1400;
		OLED_ShowSignedNum(1,1,ADC_Value[0],5,OLED_8X16);
		OLED_ShowSignedNum(1,17,ADC_Value[1],5,OLED_8X16);
//		OLED_ShowSignedNum(1,33,ADC_DOWN_L1,5,OLED_8X16);
//		OLED_ShowSignedNum(1,49,ADC_DOWN_Min,5,OLED_8X16);
//		OLED_ShowSignedNum(49,1,ADC_DOWN_R1,5,OLED_8X16);
////		OLED_ShowFloatNum(41,1,Gz,2,2,OLED_8X16);
//		OLED_ShowSignedNum(49,17,MG_out,3,OLED_8X16);
////		OLED_ShowFloatNum(49,33,Error,1,6,OLED_8X16);
//		OLED_ShowNum(49,49,shancha_flag,1,OLED_8X16);
		OLED_Update();
		
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

/* USER CODE BEGIN 4 */
//void control(void)
//{
//	Error = ADC_Value[0]-ADC_Value[1];
//	MG_out = Kp * Error + Kd * Gz;
//	Error_Last = Error;
//}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_5)
    {
        Error = ADC_Value[0]-ADC_Value[1];
				if(MG_out>300)MG_out=300;
				else if(MG_out<-300)MG_out=-300;
			  else MG_out=MG_out;
				MG_out = Kp*Error + Gz*Kd;
//				TIM2 -> CCR1 = 1500 - MG_out;
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
