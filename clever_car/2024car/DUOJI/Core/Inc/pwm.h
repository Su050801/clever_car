#ifndef __PWM_H
#define __PWM_H

#include "main.h"
#include "tim.h"
#include "gpio.h"

//#define Degrees_0    500  //原点位置
//#define Degrees_22_5 725     //22.5度位置
#define Degrees_left_die	 1100//45度位置
#define Degrees_67_5	 1225//67.5度位置
#define Degrees_90   1500 //90度位置
#define Degrees_112_5  1725 //135度位置
#define Degrees_right_die	 1900//157.5度位置
//#define Degrees_180  2500 //180度位置
void left_on(void);
void right_on(void);
void right_down(void);
void left_down(void);
#endif

