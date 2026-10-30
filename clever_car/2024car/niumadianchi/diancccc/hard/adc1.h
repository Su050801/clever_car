#include "main.h"
#include "tim.h"
#include "adc.h"
#include "dma.h"

#define PWMA   TIM2->CCR1  //PA15
#define PWMB   TIM2->CCR2  //PB3
#define PWMC   TIM3->CCR1
#define AD_left1_max 2
#define AD_left1_min 1
#define AD_left2_max 3000
#define AD_left2_min 10
#define AD_zhong_max 2
#define AD_zhong_min 1
#define AD_right1_max 2800
#define AD_right1_min 200
#define AD_right2_max 2600
#define AD_right2_min 8
#define AIN2   PBout(10)
#define AIN1   PCout(13)
#define BIN1   PBout(11)
#define BIN2   PBout(12)
extern float adc_aaa_1,position_1;
extern float adc_aaa_2,position_2;
extern int pwm_1;
extern int pwm_2;
extern uint16_t adc_val[6];
extern uint16_t adc_vala[6];
extern uint16_t adc_valb[6];
extern uint16_t adc_valc[6];
extern uint16_t adc_vald[6];
extern uint16_t sum[6];
extern float AD_left1,AD_left2,AD_zhong,AD_right1,AD_right2;
extern float err1_1,err2_1,err3_1,derr_1;
extern float err1_2,err2_2,err3_2,derr_2;
void pid_section(void);
void Set_Pwm(int moto1,int moto2,int moto3);
void adc_read(void);
int myabs(int a);
void guiyi_adc (void);
void chabihe_adc_1(void);
void chabihe_adc_2(void);
void pid_1 (void);
int pid_2 (void);
void motor_int(void);



