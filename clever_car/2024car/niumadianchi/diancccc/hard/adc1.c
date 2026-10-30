#include "adc1.h"
uint16_t adc_val[6]; //adc[0] 左一 ,adc[1] 左二 ,adc[2]右二 ,adc[3]中 ,adc[4]右一
uint16_t adc_vala[6];
uint16_t adc_valb[6];
uint16_t adc_valc[6];
uint16_t adc_vald[6];
uint16_t sum[6];
float  AD_left1,AD_left2,AD_zhong,AD_right1,AD_right2;
float pp_1,dd_1;
float err1_1,err2_1,err3_1,derr_1;
float pp_2=-2.8,dd_2=0.1;
float err1_2,err2_2,err3_2,derr_2;
float adc_aaa_1,position_1;
float adc_aaa_2,position_2;
int pwm_1;
int pwm_2;
int Section;
float adc_1_sum,adc_1_diff;
float adc_2_sum,adc_2_diff;
void adc_read(void)
{
	
    //HAL_ADCEx_Calibration_Start (&hadc1);
	int a = 0,b=0;
	for(a=0;a<10;a++)
	{
	HAL_ADC_Start_DMA (&hadc1,(uint32_t *)adc_vala ,5);
	HAL_ADC_Start_DMA (&hadc1,(uint32_t *)adc_valb ,5);
    HAL_ADC_Start_DMA (&hadc1,(uint32_t *)adc_valc ,5);
		for(b=0;b<5;b++)
		{
		if(adc_vala [b]>adc_valb[b] )
		{
		adc_vald[b]=adc_vala [b];
		adc_vala [b]=adc_valb [b];	
		adc_valb [b]=adc_vald[b];			
		}
		if(adc_valc[b]>adc_valb[b])
		{
		adc_vald[b]=adc_valb[b];
		}
		else if(adc_valc[b]>adc_vala[b])
		{
		adc_vald[b]=adc_valc[b];
		}
		else
		{
		adc_vald [b]=adc_vala [b];
		}
		sum[b]+=adc_vald [b];
		
		}
		
		
    }
	for(b=0;b<5;b++)
	{
	adc_val [b]=sum[b]/10;
	sum[b]=0;	
	}
	 
}
void guiyi_adc (void)
{
//AD_left1=(100*(adc_val[0]-AD_left1_min) / (double )(AD_left1_max-AD_left1_min));
AD_left2=(100*(adc_val[1]-AD_left2_min) / (double )(AD_left2_max-AD_left2_min));
//AD_zhong=(100*(adc_val[3]-AD_zhong_min) / (double )(AD_zhong_max-AD_zhong_min));
AD_right2=(100*(adc_val[2]-AD_right2_min) /(double ) (AD_right2_max-AD_right2_min));
//AD_right1=(100*(adc_val[4]-AD_right1_min) / (double )(AD_right1_max-AD_right1_min));

}
void chabihe_adc_1(void)
{
	adc_1_sum =AD_left1 +AD_right1 +1;
	adc_1_diff =AD_left1 -AD_right1 ;
    adc_aaa_1 =  adc_1_diff / adc_1_sum ;
	position_1= adc_aaa_1*100;
}
void chabihe_adc_2(void)
{
	adc_2_sum =AD_left2 +AD_right2 +1;
	adc_2_diff =AD_left2 -AD_right2 ;
    adc_aaa_2=  adc_2_diff / adc_2_sum ;
	position_2= adc_aaa_2*100;
}

void pid_1 (void)
{
 err1_1 =position_1;
 derr_1=err1_1-err3_1;
 err3_1=err2_1;
 err1_2=err1_1;
 pwm_1=pp_1*err1_1+dd_1*derr_1;
 PWMC=pwm_1;

}
int pid_2 (void)
{
err1_2 =position_2;
 derr_2=err1_2-err3_2;
 err3_2=err2_2;
 err1_2=err1_2;
 pwm_2=pp_2*err1_2+dd_2*derr_2;
return pwm_2;
}
void pid_section(void)
{
    if(err1_2  < 10 && err1_2  > -10) // section1
        Section = 1;
    else if(err1_2  < 20 &&err1_2  > -20) // section2
        Section = 2;
    else if(err1_2  < 35 && err1_2  > -35) //3
        Section = 3;
    else if(err1_2  < 45 && err1_2  > -45)
        Section = 4;
    else if(err1_2  <60 && err1_2  > -60)
        Section = 5;
    else if(err1_2  < 70 && err1_2  > -70)
        Section = 6;
    else if(err1_2  < 80 && err1_2  > -80)
        Section = 7;
    else if(err1_2  < 90 && err1_2  > -90)
        Section = 8;
//    else if(err1_2  < 45 && err1_2  > -45)
//        Section = 9;
//    else if(err1_2  < 50 && err1_2  > -50)
//        Section = 10;
//    else if(err1_2  < 55 && err1_2  > -55)
//        Section = 11;
//    else if(err1_2  < 60 && err1_2  > -60)
//        Section = 12;
    switch(Section)
    {
    case 1:
//        pid_steer.KP = 200;
        pp_2 = -3;
//        speed_rate = 1;
        break;
    case 2:
//        pid_steer.KP = 400;
        pp_2 = -3;
//        speed_rate = 1;
        break;
    case 3:
        pp_2 = -4.5;
        break;
    case 4:
        pp_2 = -4.5;
        break;
    case 5:
        pp_2 = -4.5;
        break;
    case 6:
       pp_2 = -4.5;
        break;
    case 7:
        pp_2 = -4.5;
        break;
    case 8:
        pp_2 = -4.5;
//        break;
//    case 9:
//        pp_2 = -6;
//        break;
//    case 10:
//        pp_2 = -6;
//        break;
//    case 11:
//        pp_2 = -7;
//        break;
//    case 12:
//        pp_2 = -7;
//        break;
    }
}








void Set_Pwm(int moto1,int moto2,int moto3)
{
			
	
			if(moto1<0)			AIN2=0,			AIN1=1;
			else 	          AIN2=1,			AIN1=0;
			PWMA=myabs(moto1);
		    if(moto2<0)	BIN1=1,			BIN2=0;
			else        BIN1=0,			BIN2=1;
			PWMB=myabs(moto2);	
			if(moto3<=660)
			{
				moto3=660;
			}
			if(moto3>=1460)
			{
				moto3=1460;
			}
	        PWMC=myabs(moto3);
}




int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
void motor_int(void)
{
		
	HAL_TIM_PWM_Start_IT(&htim2,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start_IT(&htim2,TIM_CHANNEL_2);	
	HAL_TIM_PWM_Start_IT(&htim3,TIM_CHANNEL_1);
}

