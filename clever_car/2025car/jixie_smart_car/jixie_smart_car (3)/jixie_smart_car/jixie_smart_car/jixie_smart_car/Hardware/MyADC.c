#include "adc.h"
#include "oled.h"

uint16_t ADC_Value[5] = {0};      //每个电感采集8次
uint16_t ADC_Temp[5] = {0};
uint16_t ADC_Sum[5] = {0};
uint16_t ADC_Final[5] = {0};
uint16_t ADC_Max = 3100;
uint16_t ADC_Min = 300;
uint16_t ADC_L1_Max = 3200;
uint16_t ADC_L2_Max = 3200;
uint16_t ADC_R1_Max = 3200;
uint16_t ADC_R2_Max = 3200;
uint16_t ADC_L1_Min = 300;
uint16_t ADC_L2_Min = 300;
uint16_t ADC_R1_Min = 300;
uint16_t ADC_R2_Min = 300;
int ADC_UP_L1;
uint16_t ADC_DOWN_L1;
int ADC_UP_R1;
uint16_t ADC_DOWN_R1;
uint16_t ADC_DOWN_Min;
double Error;


/*****采集五路电感值并进行滤波*****/
void Get_ADCValue(void)
{
//	uint8_t n,i;
	
	HAL_ADC_Start_DMA(&hadc1,(uint32_t *)ADC_Value,5);
//	for(i = 0;i < 4;i++)
//	{
//		ADC_Max = ADC_Min = ADC_Value[n][i];
//		ADC_Sum[i] = ADC_Value[n][i];
//		for(n = 1;n < 10;n++)
//		{
//			if(ADC_Value[n][i] > ADC_Max)
//			{
//				ADC_Max = ADC_Value[n][i];
//			}
//			if(ADC_Value[n][i] < ADC_Min)
//			{
//				ADC_Min = ADC_Value[n][i];
//			}
//			ADC_Sum[i] += ADC_Value[n][i];
//		}
//		ADC_Temp[i] = (ADC_Sum[i] - ADC_Max - ADC_Min) >> 3;
//		ADC_Final[i] = ADC_Temp[i];
//	}	 
}

/****归一化****/
//void guiyihua(void)
//{
//	ADC_L1 = 100 * (double)(ADC_Value[3] - ADC_Min) / (double)(ADC_Max - ADC_Min);
//	ADC_L2 = 100* (double)(ADC_Value[2] - ADC_Min) / (double)(ADC_Max - ADC_Min);
//	ADC_R1 = 100 * (double)(ADC_Value[0] - ADC_Min) / (double)(ADC_Max - ADC_Min);
//	ADC_R2 = 100 * (double)(ADC_Value[1] - ADC_Min) / (double)(ADC_Max - ADC_Min);
//	
//}

void guiyihua(void)
{
	ADC_UP_L1 = 100 * (double)(ADC_Value[0] - ADC_Min) / (double)(ADC_Max - ADC_Min);
	ADC_DOWN_R1 = 100* (double)(ADC_Value[4] - ADC_Min) / (double)(ADC_Max - ADC_Min);
	ADC_UP_R1 = 100 * (double)(ADC_Value[1] - ADC_Min) / (double)(ADC_Max - ADC_Min);
	ADC_DOWN_L1 = 100 * (double)(ADC_Value[2] - ADC_Min) / (double)(ADC_Max - ADC_Min);
	ADC_DOWN_Min = 100 * (double)(ADC_Value[3] - ADC_Min) / (double)(ADC_Max - ADC_Min);
}


/****差比和****/
void chabihe(void)
{
//	Error = 100 * (ADC_UP_R1 - ADC_UP_L1) / (ADC_UP_R1 + ADC_UP_L1);
	  Error = ADC_Value[0]-ADC_Value[1];
//	Error = 100 * (double)(ADC_Value[2] - ADC_Value[3]) / (double)(ADC_Value[2] + ADC_Value[3]);

}
