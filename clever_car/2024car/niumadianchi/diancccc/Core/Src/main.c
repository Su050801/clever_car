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
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "adc1.h"
#include "oled.h"
#include <stdio.h>
#include "usart1.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
int key_flag,count,time,moshi;
int huoer_flag=0;
char str[80]={0};
int i=0,b=0,c=0;
int time_flag_h,h;
int pppwww;
int flag_s=0;
int shizhi_flag=0;
int aa,aa1,aa2=0;
int sudu=3000;
int fputc(int ch, FILE *f)
{
HAL_UART_Transmit (&huart1 ,(uint8_t *)&ch,1,0xFFFF);
	return ch;

}
void key(void)
{
   if((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15)==GPIO_PIN_RESET)&&key_flag==0) 
	 {
	     key_flag=1;
	 }
   if((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15)==GPIO_PIN_SET)&&key_flag==1) 
	 {
	     key_flag=0;
		   count=0;
		   time=0;
		   moshi++;
		   if(moshi==3)
			 {
			    moshi=0;
			 }
	 }	 
}
void oled_disp(void)
{
	
	    sprintf(str,"%04d        %04d",adc_val [0], adc_val [4]);
      OLED_ShowString(0,0,(uint8_t*)str,12);
		  sprintf(str,"   %04d  %04d  ",adc_val [1], adc_val [2]);
      OLED_ShowString(0,1,(uint8_t*)str,12);
		  sprintf(str,"      %04d  ", adc_val [3]);
      OLED_ShowString(0,2,(uint8_t*)str,12);
	    sprintf(str,"    %.2f %.2f  ", AD_left2,AD_right2);
      OLED_ShowString(0,3,(uint8_t*)str,12);
      sprintf(str,"    %.2f   ", position_2 );
      OLED_ShowString(0,4,(uint8_t*)str,12);
      sprintf(str,"    %d %d ", b,aa );
      OLED_ShowString(0,5,(uint8_t*)str,12);
}
void huandao (void )
{
if(adc_val [4]>=1800&&adc_val[2]>=2500&&b==0)
{
	b=1;
flag_s=1;
}
if(adc_val [4]>=1800&&adc_val[2]>=2500&&b==2)
{
	c=0;
	b=0;
flag_s=0;
}

}
void sancai(void)
{
	if((adc_val [0]>=600&&adc_val [4]>=600&&adc_val [2]<900&&adc_val [1]<900)&&aa==0)
	{
	flag_s=2;
	}
	if((adc_val [0]>=600&&adc_val [4]>=600&&adc_val [2]<1000&&adc_val [1]<1000)&&aa==1 )
	{
	flag_s=3;
	
	}
	

}
void shizhi(void )
{
if(adc_val [3]>=2000)
{
 flag_s=2;
	shizhi_flag=1;
}
if(adc_val [3]>=2000&&shizhi_flag==1)
{
flag_s=0;
}
}


void huoer (void)
{
	if(HAL_GPIO_ReadPin (GPIOA,GPIO_PIN_12 )==GPIO_PIN_RESET&& huoer_flag ==0)
	{
	huoer_flag =1;
	
	}



}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef*htim)
{
	if(htim->Instance==TIM4)
	{
		time++;
		//adc_read();
		//printf("%lf,%lf,%lf\n",position_2,AD_left2,AD_right2 );
		if(moshi ==1)
		{
				huandao ();
			 sancai();
			if(flag_s ==0)
			{
		  guiyi_adc ();
	    chabihe_adc_2();
		  pppwww=1040+pid_2 ();
		Set_Pwm(sudu,sudu,pppwww);
			}
			else if (flag_s==1)
			{
				if(c<=179)
				{
					c++;
			Set_Pwm(sudu,sudu,1150);
				}
				else if(c>179)
				{
					b=2;
			guiyi_adc ();
	    chabihe_adc_2();
			
		  pppwww=1040+pid_2 ();
		  Set_Pwm(sudu,sudu,pppwww);
					
			}
				
			}
			else if(flag_s==2)
			{
				
					if(aa2<100)
					{
						aa2++;
						aa1++;
						Set_Pwm(sudu,sudu,1210);
					}
					else if(aa2>=100)
					{
						aa1++;
			guiyi_adc ();
	    chabihe_adc_2();
		  pppwww=1040+pid_2 ();
		Set_Pwm(sudu,sudu,pppwww);
					}
					
				if(aa1>=300)
				{
				aa1=0;
			  aa2 =0;
				aa=1;
			 flag_s=0;
				}
			}
				
			
			else if(flag_s ==3)
			{
				if(aa2<100)
					{
						aa2++;
						aa1++;
						Set_Pwm(sudu,sudu,700);
					}
					else if(aa2>=100)
					{
						aa1++;
			guiyi_adc ();
	    chabihe_adc_2();
		  pppwww=1040+pid_2 ();
		Set_Pwm(sudu,sudu,pppwww);
					}
					
				if(aa1>=sudu)
				{
				aa1=0;
			 flag_s=0;
			}
		}
			else if(flag_s ==4)
			{
			
			}
			
//			if(adc_val [0]>1700)
//			{
//			Set_Pwm(5000,5000,760);
//			}
//			if(adc_val [4]>1700)
//			{
//			Set_Pwm(5000,5000,1360);
//			}
		}
		if(moshi ==0)
		{
		Set_Pwm (0,0,1040);
		
		}
		
		if(moshi ==2)
		{
		guiyi_adc ();
	    chabihe_adc_2();
		pid_section();		
		pppwww=1040+pid_2 ();
		Set_Pwm(0,0,pppwww);
		if(adc_val [0]>1700)
			{
			Set_Pwm(0,0,660);
			}
			if(adc_val [4]>1700)
			{
			Set_Pwm(0,0,1460);
			}
		
		
		}
//		if(huoer_flag !=0)
//		{
//			    h++;
//			if(h==1)
//			{
//		        time_flag_h=time;
//			}
//			    Set_Pwm(1000,1000,700);
//				if((time-time_flag_h)>=200)
//				{
//				Set_Pwm(1000,1000,1000);
//				huoer_flag=0;
//					h=0;
//				}
//		 }
//		if(huoer_flag ==0)
//		{
//        adc_read();
//		guiyi_adc ();
//			
//		Set_Pwm(1000,1000,1000);
//			
//		}
		
				     //停车
		
	}
		
		
		
	}


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
  MX_TIM2_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  OLED_Init();
  motor_int ();
  OLED_Clear ();
  HAL_TIM_Base_Start_IT (&htim4 );
  HAL_ADCEx_Calibration_Start (&hadc1);
  //HAL_UART_Receive_IT(&huart1, (uint8_t *)RxBuffer, 1);
  Set_Pwm(0,0,1040);//+420 1460 右转  -380 660 左转 中间 1040
  //HAL_Delay (1000);
  //Set_Pwm(7200,7200,1070);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  //huoer ();
	  adc_read();
		//printf("%lf,%lf,%lf\n",position_2,AD_left2,AD_right2 )
		//huandao ();
		//sancai ();
		//shizhi ();
	  //oled_disp();
	  key();
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
