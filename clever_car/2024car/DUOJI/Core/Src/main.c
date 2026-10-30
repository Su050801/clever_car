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
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "pwm.h"
#include "badc.h"
#include "pid.h"
#include "oled.h"
#include "key.h"
#include "stdio.h"
extern struct keys key[3];
extern uint16_t adci[10];
extern uint16_t adcj[10];
extern uint16_t adck[10];
extern uint16_t adctmp[10];
extern uint16_t AD_Val[10];
extern uint16_t sum1[10];
extern double position_1;
extern uint16_t AD_left1;
extern uint16_t AD_left2;
extern uint16_t AD_right1;
extern uint16_t AD_right2;
extern uint16_t AD_mid;
uint flag_huandao1=0;
uint flag_huandao2=0;
uint flag_sancha1=0;
uint flag_sancha2=0;
uint flag_sancha3=0;
uint flag_shizi=0;
uchar Value1 = 0;
double num1;
int PWMValue1;
int flag_gan1 = 0;
int flag_gan2 = 0;
char num[30]={0};
extern double  PID_P1;        /*  比例常数 */
extern double  PID_D1;         /*  微分常数 */
extern double  LastError1;          /*  前一项误差 */
extern double  PrevError1;          /*  前第二项误差 */

extern uchar ad_1_sum;
extern uchar ad_1_diff;
extern double count_1;
double  PID_P1 = 26.3;         /*  比例常数 */
double  PID_D1 = 25.4;         /*  微分常数 */
double  LastError1;          /*  前一项误差 */
double  PrevError1;
double dError1, Error1;
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void oled_proc(void);
void keys_flag(void);
void ChaBiHe_ADC(void);
void PID_Vertical (void);
void shizi(void);
void sancha(void);
void gan(void);
void huandao(void);
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
  MX_TIM3_Init();
  MX_ADC1_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	OLED_Init();
	OLED_Clear();
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	HAL_TIM_Base_Start(&htim3);
	HAL_TIM_Base_Start(&htim1);
	HAL_TIM_Base_Start_IT(&htim4);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)		
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//		gan();
		Get_ADC();
		ChaBiHe_ADC();
		PID_Vertical();
		if(PWMValue1 > 350)
		{
			PWMValue1 = 350;
		}
		if(PWMValue1 < -350)
		{
			PWMValue1 = -350;
		}
//		if(flag_gan1==1&&flag_gan2 == 0)
//		{
//			int i;
//			for(i=155;i<280;i++)
//			{
//				left_on();
//				right_on();
////			Value1=1500-i;
//				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,1500+i);
//				HAL_Delay(15);
//			}
//			flag_gan1=0;
//			flag_gan2=!flag_gan2;
//		}
////		if(flag_gan1 == 1&&flag_gan2 == 2)
////		{
//			int i;
//			for(i=155;i<280;i++)
//			{
//				left_on();
//				right_on();
////			Value1=1500-i;
//				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,1500+i);
//				HAL_Delay(15);
//			}
//			flag_gan1 = 0;
//				left_down();
//			  right_down();
//		}
//		if(flag_gan2 > 2)
//		{
//			flag_gan2 = 1;
//		}
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3,1500-PWMValue1);
			left_on();
			right_on();
//		oled_proc();
			huandao();	
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
void oled_proc(void)
{
	OLED_ShowString(10,0,(uint8_t *)"Smart",16);
	OLED_ShowString(55,0,(uint8_t *)"Car_MY",16);
	OLED_ShowString(0,2,(uint8_t *)"V1:",12);
	OLED_ShowString(0,3,(uint8_t *)"V2:",12);
	OLED_ShowString(0,4,(uint8_t *)"V3:",12);
	OLED_ShowString(0,5,(uint8_t *)"V4:",12);
//	OLED_ShowString(0,6,(uint8_t *)"V5:",12);
	OLED_ShowString(0,6,(uint8_t *)"Va",12);
	OLED_ShowString(0,7,(uint8_t *)"Er",12);
	OLED_ShowString(55,2,(uint8_t *)"P:",12);
	OLED_ShowString(55,3,(uint8_t *)"D:",12);
	OLED_ShowString(55,4,(uint8_t *)"SHI:",12);
	OLED_ShowString(55,5,(uint8_t *)"San:",12);
	OLED_ShowString(55,6,(uint8_t *)"fl1",12);
	OLED_ShowString(55,7,(uint8_t *)"fl2",12);
	OLED_ShowNum(20,2,AD_Val[3],5,12); 
	
	OLED_ShowNum(20,3,AD_Val[0],5,12); 
	
	OLED_ShowNum(20,4,AD_Val[2],5,12); 
	
	OLED_ShowNum(20,5,AD_Val[1],5,12); 
//	//差与和的动态信息
//	OLED_ShowNum(20,6,AD_Val[4],5,12);
	sprintf(num,"%.2f",Error1);
	OLED_ShowString(20, 7, (uint8_t*)num,12);
//	if(PWMValue1 < 0)
//	{
//		sprintf(num,"%d",PWMValue1);
//		OLED_ShowString(20, 6, (uint8_t*)num,12);
//	}
//	if(PWMValue1 >= 0)
//	{
//		sprintf(num,"%d",(int)num1);
//		OLED_ShowString(20, 6, (uint8_t*)num,12);
//	}
		sprintf(num,"%d",PWMValue1);
		OLED_ShowString(20, 6, (uint8_t*)num,12);

	OLED_ShowNum(90,2,PID_P1,5,12); 
	
	OLED_ShowNum(90,3,PID_D1,5,12); 
	
	OLED_ShowNum(90,4,flag_shizi,5,12); 
	
	OLED_ShowNum(90,5,flag_sancha1,5,12); 
	
	OLED_ShowNum(90,6,flag_gan1,5,12);
	
	OLED_ShowNum(90,7,flag_gan2,5,12);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==GPIO_PIN_2)
	{
		flag_gan2++;
	}
}
//void keys_flag(void)
//{
//	if(key[0].single_flag==1)
//	{
//		PID_P1=PID_P1+1;
//		key[0].single_flag = 0;
//	}
//		if(key[1].single_flag==1)
//	{
//		PID_D1=PID_D1+0.5;
//		key[1].single_flag = 0;
//	}
//		if(key[0].long_flag==1)
//	{
//		PID_P1=PID_P1-1;
//		key[0].long_flag = 0;
//	}
//		if(key[1].long_flag==1)
//	{
//		PID_D1=PID_D1-0.5;
//		key[1].long_flag = 0;
//	}
//} 
void huandao(void)
{
		if(AD_Val[3]>2000&&AD_Val[0]>3500&&AD_Val[2]>1800&&AD_Val[1]>1500)
		{
				flag_huandao1 = 1;
				flag_huandao2 = !flag_huandao2;
		}
		if(flag_huandao1 == 1&&flag_huandao2 == 1)
		{
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3,1300);
			HAL_Delay(300);
			flag_huandao1 = 0;
		}
}
void sancha(void)
{
	if(AD_Val[3]>1000&&AD_Val[0]>2700&&AD_Val[2]>2500&&AD_Val[1]>1000)
	{
		flag_sancha1=1;
//		flag_sancha2=1;
	}
//	if(AD_Val[3]<1400&&AD_Val[0]<500&&AD_Val[1]<500&&AD_Val[2]<500)
//	{
//		flag_sancha2=1;
//	}
	if(flag_sancha1==1&&flag_sancha3==0)
	{
		HAL_GPIO_WritePin(GPIOB , GPIO_PIN_12,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB , GPIO_PIN_14,GPIO_PIN_RESET);
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1,1900);
		HAL_Delay(1000);
		flag_sancha1=0;
		flag_sancha3=1;
	}
	if(flag_sancha1==1&&flag_sancha3==1)
	{
		HAL_GPIO_WritePin(GPIOB , GPIO_PIN_12,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB , GPIO_PIN_14,GPIO_PIN_RESET);
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1,1100);
		HAL_Delay(1000);
		flag_sancha1=0;
		flag_sancha3=0;
	}
}
void shizi(void)
{
	if(AD_Val[0]>2500&&AD_Val[1]>2500&&AD_Val[2]>2500)
	{
		flag_shizi=1;
	}
	if(flag_shizi == 1)
	{
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1,1500);
		HAL_Delay(500);
		flag_shizi=0;
	}  
}
void ChaBiHe_ADC(void)
{
	ad_1_sum = AD_Val[0] + AD_Val[2] +1;
	ad_1_diff = AD_Val[0] - AD_Val[2] ;
	count_1 = (double)(AD_Val[0] - AD_Val[2]) / (AD_Val[0] + AD_Val[2]+1);
//	position_1  = count_1 * 100;
	HAL_Delay(5);
}
 
void PID_Vertical(void)
{
	double num2 = 0;
	Error1 = 100*(double)(AD_Val[0] - AD_Val[2]) / (AD_Val[0] + AD_Val[2]+1);//差比和的值作为error	/*目标值为差比和值为0，所以可以直接将差比和实际所得值作为error*/
	dError1 = LastError1 - PrevError1;
	PrevError1 = LastError1;
  LastError1 = Error1;
	if(Error1>0)
	{
		num2 = Error1/6.85;
		PWMValue1 = PID_P1 * num2 + PID_D1 * dError1;

	}
	else
	{
		PWMValue1 = PID_P1 * Error1 + PID_D1 * dError1;
	}
	
//	err1_1 =position_1;
// derr_1=err1_1-err3_1;
// err3_1=err2_1;
// err1_2=err1_1;
// PWMValue1 = PID_P1*err1_1+PID_D1*derr_1;
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
