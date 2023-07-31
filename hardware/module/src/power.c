/**
 ******************************************************************************
 * @file    power.c
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#include "power.h"

void Power_Init(void)
{
	Power_24v_Init();
	Power_5v_Init();
}

void Power_24v_Init(void)
{
	GPIO_InitTypeDef gpio;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);

	gpio.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOH, &gpio);

	POWER1_24V_OFF();
	POWER2_24V_OFF();
	POWER3_24V_OFF();
	POWER4_24V_OFF();
}

void Power_5v_Init(void)
{
	GPIO_InitTypeDef gpio;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);

	gpio.GPIO_Pin = GPIO_Pin_15;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_11;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &gpio);

	POWER_5V_A_OFF();
	POWER_5V_B_OFF();
}

void Power_5v_Status(int id, char *status)
{
    if (id == 0)
    {
        if (strcmp(status, "on") == 0)
        {
            POWER_5V_A_ON();
            POWER_5V_B_ON();
        }
        else if (strcmp(status, "off") == 0)
        {
            POWER_5V_A_OFF();
            POWER_5V_B_OFF();
        }
    }
    else if (id == 1)
    {
        if (strcmp(status, "on") == 0)
        {
            POWER_5V_A_ON();
        }
        else if (strcmp(status, "off") == 0)
        {
            POWER_5V_A_OFF();
        }
    }
    else if (id == 2)
    {
        if (strcmp(status, "on") == 0)
        {
            POWER_5V_B_ON();
        }
        else if (strcmp(status, "off") == 0)
        {
            POWER_5V_B_OFF();
        }
    }
}

void Power_24v_Status(int id, char *status)
{
    if (id == 0)
    {
        if (strcmp(status, "on") == 0)
        {
            POWER1_24V_ON();
            POWER2_24V_ON();
            POWER3_24V_ON();
            POWER4_24V_ON();
        }
        else if (strcmp(status, "off") == 0)
        {
            POWER1_24V_OFF();
            POWER2_24V_OFF();
            POWER3_24V_OFF();
            POWER4_24V_OFF();
        }
    }
    else if (id == 1)
    {
        if (strcmp(status, "on") == 0)
        {
            POWER1_24V_ON();
        }
        else if (strcmp(status, "off") == 0)
        {
            POWER1_24V_OFF();
        }
    }
    else if (id == 2)
    {
        if (strcmp(status, "on") == 0)
        {
            POWER2_24V_ON();
        }
        else if (strcmp(status, "off") == 0)
        {
            POWER2_24V_OFF();
        }
    }
    else if (id == 3)
    {
        if (strcmp(status, "on") == 0)
        {
            POWER3_24V_ON();
        }
        else if (strcmp(status, "off") == 0)
        {
            POWER3_24V_OFF();
        }
    }
    else if (id == 4)
    {
        if (strcmp(status, "on") == 0)
        {
            POWER4_24V_ON();
        }
        else if (strcmp(status, "off") == 0)
        {
            POWER4_24V_OFF();
        }
    }
}

void Power_Status(int channel, int id, char *status)
{
	if (channel == 24)
	{
		Power_24v_Status(id, status);
	}
	if (channel == 5)
	{
		Power_5v_Status(id, status);
	}
}

void Power_Serial_Callback(cJSON *serial_data)
{
    cJSON *type = cJSON_GetObjectItem(serial_data, "type");
    if (type && cJSON_IsString(type))
    {
        if(strcmp(type->valuestring, "power-status") == 0)
        {
            cJSON *channel = cJSON_GetObjectItem(serial_data, "channel");
            cJSON *id = cJSON_GetObjectItem(serial_data, "id");
            cJSON *status = cJSON_GetObjectItem(serial_data, "status");
            if (channel && cJSON_IsNumber(channel))
            {
                Power_Status((int)channel->valueint, (int)id->valueint, status->valuestring);
            }
        }
    }
}
