#include "MG995.h"

extern float  angle;
extern uint16_t PWM;

void PWM_limt(int *PWM)
{
	if(*PWM>2000) *PWM=2000;
	if(*PWM<0) *PWM=0;
}

void set_angle(int angle)
{
	  PWM = (angle/180*2000+500);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,PWM);
}
