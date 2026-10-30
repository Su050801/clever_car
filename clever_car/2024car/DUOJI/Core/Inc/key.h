#ifndef __KEY_H
#define __KEY_H
#include "main.h"
#include "stdbool.h"
struct keys
{
	uchar judge_sta;
	bool key_sta;
	bool single_flag;
	bool long_flag;
	uint double_status;
	bool double_flag;
	uint double_time;
	uint key_time;
};

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif
