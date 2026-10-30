#include "badc.h"
#include "adc.h"
#include "main.h"
uint16_t adci[10] = {0};
uint16_t adcj[10] = {0};
uint16_t adck[10] = {0};
uint16_t adctmp[10] = {0};
uint16_t AD_Val[10] = {0};
uint16_t sum1[10] = {0};

void Get_ADC(void)	//得到的ADC电压存储在ADC_Val中
{
	int num = 0,count = 0;
	
	for(num = 0; num < 10; num++)
	{
		HAL_ADCEx_Calibration_Start(&hadc1 );//开启ADC。
		HAL_ADC_Start_DMA (&hadc1 ,(uint32_t *)adci,4);//开启七路DMA
		HAL_ADC_Start_DMA (&hadc1 ,(uint32_t *)adcj,4);
		HAL_ADC_Start_DMA (&hadc1 ,(uint32_t *)adck,4);
		for(count = 0; count < 4;count++)//取中值
		{
			if (adci[count] > adcj[count])
				{
					adctmp[count] = adci[count]; adci[count] = adcj[count]; adcj[count] = adctmp[count];
				 }
				 if (adck[count] > adcj[count]) 
					 adctmp[count] = adcj[count];
				 else if(adck[count] >adci[count]) 
					 adctmp[count] = adck[count]; 
				 else 
					adctmp[count] = adci[count];
				 sum1[count]+=adctmp[count];
		 }
	 }
	for(count = 0; count < 4;count++)
	 {    
			AD_Val[count]=sum1[count]/10; 
			sum1[count]=0;
	 }
}
