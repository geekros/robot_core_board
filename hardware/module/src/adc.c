/**
 ******************************************************************************
 * @file    adc.c
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#include "adc.h"

// 低电压报警阈值
float Low_Voltage = 11.4f;
// 报警间隔
int Low_Voltage_Time = 5000;
int Low_Voltage_Number = 0;

void Adc_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3, ENABLE);
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3, DISABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC3, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC3, ADC_Channel_9, 1, ADC_SampleTime_144Cycles);
	ADC_RegularChannelConfig(ADC3, ADC_Channel_14, 1, ADC_SampleTime_144Cycles);

	ADC_Cmd(ADC3, ENABLE);

	ADC_SoftwareStartConv(ADC3);
}

void Adc_Task(void)
{
	// 低电压报警，红色LED亮起
	float voltage = Adc_Board_Voltage();
	if (Low_Voltage > 0)
	{
		if (voltage < Low_Voltage)
		{
			// 报警声
			if(Low_Voltage_Number == Low_Voltage_Time){
				Low_Voltage_Number = 0;
				Buzzer_Low_Voltage_Music();
			}else{
				Low_Voltage_Number = Low_Voltage_Number + 1;
			}
		}
	}
}

float Adc_Pwm_Voltage(void)
{
	int power_read;
	float Power;
	int pow_sum = 0;
	int i;
	for (i = 0; i < 100; i++)
	{
		ADC_RegularChannelConfig(ADC3, ADC_Channel_14, 1, ADC_SampleTime_144Cycles);
		ADC_SoftwareStartConv(ADC3);
		while (!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC));
		pow_sum += ADC_GetConversionValue(ADC3);
	}
	power_read = pow_sum / 100;
	Power = (float)(power_read * (3.3f / 4096.0f));
	Power = (Power / 10.0f * 110.0f);
	return Power;
}

float Adc_Board_Voltage(void)
{
	int i;
	int pow_sum = 0;
	int power_read;
	float Power;
	for (i = 0; i < 100; i++)
	{
		ADC_RegularChannelConfig(ADC3, ADC_Channel_9, 1, ADC_SampleTime_144Cycles);
		ADC_SoftwareStartConv(ADC3);
		while (!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC));
		pow_sum += ADC_GetConversionValue(ADC3);
	}
	power_read = pow_sum / 100;
	Power = ((float)power_read * (3.3f / 4096.0f));
	Power = (Power / 4.7f * 104.7f);
	return Power;
}

void Adc_Low_Voltage(float voltage)
{
	Low_Voltage = voltage;
}

void Adc_Serial_Callback(cJSON *serial_data)
{
    cJSON *type = cJSON_GetObjectItem(serial_data, "type");
    if (type && cJSON_IsString(type))
    {
        if(strcmp(type->valuestring, "board-voltage") == 0)
        {
            float voltage = Adc_Board_Voltage();
            Usb_Write_Data("{\"type\":\"board-voltage\",\"voltage\":%0.3f}\r\n", voltage);
        }

        if(strcmp(type->valuestring, "pwm-voltage") == 0)
        {
            float voltage = Adc_Pwm_Voltage();
		    Usb_Write_Data("{\"type\":\"pwm-voltage\",\"voltage\":%0.3f}\r\n", voltage);
        }

        if(strcmp(type->valuestring, "low-voltage") == 0)
        {
            cJSON *voltage = cJSON_GetObjectItem(serial_data, "voltage");
            if (voltage && cJSON_IsNumber(voltage))
            {
                float adcVoltage = (float)voltage->valuedouble;
                Adc_Low_Voltage(adcVoltage);
            }
        }
    }
}
