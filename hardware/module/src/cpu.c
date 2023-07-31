/**
 ******************************************************************************
 * @file    cpu.c
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#include "cpu.h"

void Cpu_Init(void)
{
	ADC_CommonInitTypeDef ADC_CommonInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);

	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	;
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_TempSensorVrefintCmd(ENABLE);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_18, 1, ADC_SampleTime_15Cycles);

	ADC_Cmd(ADC1, ENABLE);
	ADC_SoftwareStartConv(ADC1);
}

float Cpu_Temperature(void)
{
	int tem_read;
	float Temperature;
	int tem_sum = 0;
	int i;
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	for (i = 0; i < 100; i++)
	{
		ADC_ClearFlag(ADC1, ADC_FLAG_STRT | ADC_FLAG_OVR | ADC_FLAG_EOC);
		ADC_RegularChannelConfig(ADC1, ADC_Channel_18, 1, ADC_SampleTime_15Cycles);
		ADC_SoftwareStartConv(ADC1);
		while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)){}
		tem_sum += ADC_GetConversionValue(ADC1);
	}
	tem_read = tem_sum / 100;
	Temperature = (float)((tem_read * (3300.0f / 4096.0f) - 760.0f) / 2.5f + 25.0f);
	return Temperature;
}

void Cpu_Serial_Callback(cJSON *serial_data)
{
    cJSON *type = cJSON_GetObjectItem(serial_data, "type");
    if (type && cJSON_IsString(type))
    {
        if(strcmp(type->valuestring, "cpu-temperature") == 0)
        {
            float temperature = Cpu_Temperature();
            Usb_Write_Data("{\"type\":\"cpu-temperature\",\"temperature\":%0.2f}\r\n", temperature);
        }
    }
}
