#include "key.h"
#include "pid.h"
#include "badc.h"
#include "main.h"
extern uchar Value1;
extern int PWMValue1;
extern void ChaBiHe_ADC(void);

extern void PID_Vertical (void);
struct keys key[3]={0,0,0};
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
//	if(htim->Instance == TIM3)
//	{
//		Get_ADC();
//		ChaBiHe_ADC();
//		PID_Vertical();
//		if(PWMValue1 > 350)
//		{
//			PWMValue1 = 350;
//		}
//		if(PWMValue1 < -350)
//		{
//			PWMValue1 = -350;
//		}
//		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_3,1500-PWMValue1);

//	}
////	if(htim->Instance == TIM2)
//	{
//		key[0].key_sta=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7);
//		key[1].key_sta=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8);
//		key[2].key_sta=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9);
//	}
//	for(int i=0; i<3; i++)
//	{
//		switch (key[i].judge_sta)
//		{
//			case 0:
//			{
//				if(key[i].key_sta == 0)
//				{
//					key[i].judge_sta = 1;
//					
//				}
//				break;
//			}
//			case 1:
//			{
//				if(key[i].key_sta == 0)
//				{
//					key[i].judge_sta = 2;
//					key[i].key_time = 0;
//				}
//				else 
//				{
//					key[i].judge_sta = 0;
//				}
//				break;
//			}
//			case 2:
//			{
//				if(key[i].key_sta == 0)
//				{
//					key[i].key_time++;
//				}
//				else if(key[i].key_sta == 1 && key[i].key_time > 70)
//				{
//					key[i].long_flag = 1;
//					key[i].judge_sta = 0;
//				}
//				else if(key[i].key_sta == 1 && key[i].key_time <=70)
//				{
//					switch (key[0].double_status)
//					{
//						case 0:
//							 key[0].double_status = 1;  //跳转到状态1
//               key[0].double_time = 0;    //开始计时			
//								break;
//						case 1:
//							 key[0].double_flag = 1;  //跳转到状态1
//               key[0].double_status = 0;    //开始计时			
//               break;
//					}
//					key[i].judge_sta = 0;
//					
//				}
//				break;
//			}
//			
//		}
//		if (key[0].double_status == 1)              //状态1：第一次松开后未按下按键
//        {
//            key[0].double_time++;                  //若一直未按下第二次按键，则计时增加
//            if (key[0].double_time >= 35)          //若间隔时间大于一定值
//            {
//                key[0].single_flag = 1;            //判定为短按
//                key[0].double_status = 0;          //重置判断双击的状态
//            }
//				}
//	}

	
}
