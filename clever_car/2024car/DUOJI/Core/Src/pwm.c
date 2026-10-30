#include "pwm.h"
#include "main.h"
void left_on(void)
{
	HAL_GPIO_WritePin(GPIOB , GPIO_PIN_12,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB , GPIO_PIN_13,GPIO_PIN_RESET);
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4,50);
}
void right_on(void)
{
	HAL_GPIO_WritePin(GPIOB , GPIO_PIN_14,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB , GPIO_PIN_15,GPIO_PIN_RESET);
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4,50);
}
void left_down(void)
{
	HAL_GPIO_WritePin(GPIOB , GPIO_PIN_12,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB , GPIO_PIN_13,GPIO_PIN_SET);
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1,50);
}
void right_down(void)
{
	HAL_GPIO_WritePin(GPIOB , GPIO_PIN_14,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB , GPIO_PIN_15,GPIO_PIN_SET);
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1,50);
}
