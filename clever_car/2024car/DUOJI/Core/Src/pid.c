#include "pid.h"

/*归一化后每一路ADC的值*/
int16_t AD_left1;
int16_t AD_left2;
int16_t AD_right1;
int16_t AD_right2;
uint16_t AD_mid;
double err1_1,err1_2,err3_1,err2_1,derr_1;
extern uchar AD_Val[10]; 
int AD_left1_min = 300;
int AD_left2_min = 500;
int AD_left1_max = 2500;
int AD_left2_max = 3000;
int AD_right1_min = 500;
int AD_right2_min = 300;
int AD_right1_max = 3000;
int AD_right2_max = 2500;
extern int PWMValue1;
uchar ad_1_sum;
uchar ad_1_diff;
double count_1;
double position_1;
 
/*归一化算法*/
void GuiYi_ADC(void)
{
	AD_left1 = (uint16_t) (100 * (AD_Val[3] - AD_left1_min) / (AD_left1_max - AD_left1_min));
	AD_left2 = (uint16_t) (100 * (AD_Val[0] - AD_left2_min) / (AD_left2_max - AD_left2_min));
	AD_right1 = (uint16_t) (100 * (AD_Val[1] - AD_right1_min) / (AD_right1_max - AD_right1_min));
	AD_right2 = (uint16_t) (100 * (AD_Val[2] - AD_right2_min) / (AD_right2_max - AD_right2_min));
}


/*差比和算法*/


