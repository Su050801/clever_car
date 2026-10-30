#include "gpio.h"

uint8_t KeyNumber;

uint8_t KeyGetState(void)
{
	uint8_t State = 0;
	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0) == GPIO_PIN_RESET){State = 1;}
	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1) == GPIO_PIN_RESET){State = 2;}
	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2) == GPIO_PIN_RESET){State = 3;}
	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12) == GPIO_PIN_RESET){State = 4;}
	return State;
}

void KeyLoop(void)
{
	static uint8_t State;
	static uint8_t LastState;
	LastState = State;
	State = KeyGetState();
	if(State == 0 && LastState ==1){KeyNumber = 1;}
	if(State == 0 && LastState ==2){KeyNumber = 2;}
	if(State == 0 && LastState ==3){KeyNumber = 3;}
	if(State == 0 && LastState ==4){KeyNumber = 4;}
}

uint8_t KeyGetNum(void)
{
	uint8_t temp = 0;
	temp = KeyNumber;
	KeyNumber = 0;
	return temp;
}



