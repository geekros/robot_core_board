/**
 ******************************************************************************
 * @file    io.c
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#include "io.h"

void Io_Model(int channel, char *mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	if (channel > 0 && channel < 19)
	{
		if (channel == 1)
		{
			if (memcmp(mode, "in", 2) == 0)
			{
				RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
				GPIO_Init(GPIOB, &GPIO_InitStructure);
			}
			if (memcmp(mode, "out", 3) == 0)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_Init(GPIOE, &GPIO_InitStructure);
			}
		}
		if (channel == 2)
		{
			if (memcmp(mode, "in", 2) == 0)
			{
				RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
				GPIO_Init(GPIOH, &GPIO_InitStructure);
			}
			if (memcmp(mode, "out", 3) == 0)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_Init(GPIOH, &GPIO_InitStructure);
			}
		}
		if (channel == 3)
		{
			if (memcmp(mode, "in", 2) == 0)
			{
				RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
				GPIO_Init(GPIOE, &GPIO_InitStructure);
			}
			if (memcmp(mode, "out", 3) == 0)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_Init(GPIOE, &GPIO_InitStructure);
			}
		}
		if (channel == 4)
		{
			if (memcmp(mode, "in", 2) == 0)
			{
				RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
				GPIO_Init(GPIOH, &GPIO_InitStructure);
			}
			if (memcmp(mode, "out", 3) == 0)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_Init(GPIOH, &GPIO_InitStructure);
			}
		}
		if (channel == 5)
		{
			if (memcmp(mode, "in", 2) == 0)
			{
				RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
				GPIO_Init(GPIOE, &GPIO_InitStructure);
			}
			if (memcmp(mode, "out", 3) == 0)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_Init(GPIOE, &GPIO_InitStructure);
			}
		}
		if (channel == 6)
		{
			if (memcmp(mode, "in", 2) == 0)
			{
				RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
				GPIO_Init(GPIOI, &GPIO_InitStructure);
			}
			if (memcmp(mode, "out", 3) == 0)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_Init(GPIOI, &GPIO_InitStructure);
			}
		}
		if (channel == 7)
		{
			if (memcmp(mode, "in", 2) == 0)
			{
				RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
				GPIO_Init(GPIOE, &GPIO_InitStructure);
			}
			if (memcmp(mode, "out", 3) == 0)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_Init(GPIOE, &GPIO_InitStructure);
			}
		}
		if (channel == 8)
		{
			if (memcmp(mode, "in", 2) == 0)
			{
				RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
				GPIO_Init(GPIOI, &GPIO_InitStructure);
			}
			if (memcmp(mode, "out", 3) == 0)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_Init(GPIOI, &GPIO_InitStructure);
			}
		}
		if (channel == 9)
		{
			if (memcmp(mode, "in", 2) == 0)
			{
				RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
				GPIO_Init(GPIOF, &GPIO_InitStructure);
			}
			if (memcmp(mode, "out", 3) == 0)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_Init(GPIOF, &GPIO_InitStructure);
			}
		}
		if (channel == 10)
		{
			if (memcmp(mode, "in", 2) == 0)
			{
				RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
				GPIO_Init(GPIOI, &GPIO_InitStructure);
			}
			if (memcmp(mode, "out", 3) == 0)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_Init(GPIOI, &GPIO_InitStructure);
			}
		}
		if (channel == 11)
		{
			if (memcmp(mode, "in", 2) == 0)
			{
				RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
				GPIO_Init(GPIOF, &GPIO_InitStructure);
			}
			if (memcmp(mode, "out", 3) == 0)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_Init(GPIOF, &GPIO_InitStructure);
			}
		}
		if (channel == 12)
		{
			if (memcmp(mode, "in", 2) == 0)
			{
				RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
				GPIO_Init(GPIOI, &GPIO_InitStructure);
			}
			if (memcmp(mode, "out", 3) == 0)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_Init(GPIOI, &GPIO_InitStructure);
			}
		}
		if (channel == 13)
		{
			if (memcmp(mode, "in", 2) == 0)
			{
				RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
				GPIO_Init(GPIOF, &GPIO_InitStructure);
			}
			if (memcmp(mode, "out", 3) == 0)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_Init(GPIOF, &GPIO_InitStructure);
			}
		}
		if (channel == 14)
		{
			if (memcmp(mode, "in", 2) == 0)
			{
				RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
				GPIO_Init(GPIOI, &GPIO_InitStructure);
			}
			if (memcmp(mode, "out", 3) == 0)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_Init(GPIOI, &GPIO_InitStructure);
			}
		}
		if (channel == 15)
		{
			if (memcmp(mode, "in", 2) == 0)
			{
				RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
				GPIO_Init(GPIOF, &GPIO_InitStructure);
			}
			if (memcmp(mode, "out", 3) == 0)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_Init(GPIOF, &GPIO_InitStructure);
			}
		}
		if (channel == 16)
		{
			if (memcmp(mode, "in", 2) == 0)
			{
				RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
				GPIO_Init(GPIOI, &GPIO_InitStructure);
			}
			if (memcmp(mode, "out", 3) == 0)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_Init(GPIOI, &GPIO_InitStructure);
			}
		}
		if (channel == 17)
		{
			if (memcmp(mode, "in", 2) == 0)
			{
				RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
				GPIO_Init(GPIOF, &GPIO_InitStructure);
			}
			if (memcmp(mode, "out", 3) == 0)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_Init(GPIOF, &GPIO_InitStructure);
			}
		}
		if (channel == 18)
		{
			if (memcmp(mode, "in", 2) == 0)
			{
				RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
				GPIO_Init(GPIOI, &GPIO_InitStructure);
			}
			if (memcmp(mode, "out", 3) == 0)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_Init(GPIOI, &GPIO_InitStructure);
			}
		}
		Usb_Write_Data("{\"type\":\"io-mode\",\"channel\":%d,\"mode\":\"%s\"}\r\n", channel, mode);
	}
}

void Io_State(int channel, char *state)
{
	int that_status = 0;
	if (channel > 0 && channel < 19)
	{
		if (channel == 1)
		{
			if (memcmp(state, "high", 4) == 0)
			{
				USER_IO_PE3_HIGH();
			}
			if (memcmp(state, "low", 3) == 0)
			{
				USER_IO_PE3_LOW();
			}
			if (memcmp(state, "switch", 6) == 0)
			{
				USER_IO_PE3_TOGGLE();
			}
			that_status = USER_IO_PE3_READ;
		}
		if (channel == 2)
		{
			if (memcmp(state, "high", 4) == 0)
			{
				USER_IO_PH14_HIGH();
			}
			if (memcmp(state, "low", 3) == 0)
			{
				USER_IO_PH14_LOW();
			}
			if (memcmp(state, "switch", 6) == 0)
			{
				USER_IO_PH14_TOGGLE();
			}
			that_status = USER_IO_PH14_READ;
		}
		if (channel == 3)
		{
			if (memcmp(state, "high", 4) == 0)
			{
				USER_IO_PE9_HIGH();
			}
			if (memcmp(state, "low", 3) == 0)
			{
				USER_IO_PE9_LOW();
			}
			if (memcmp(state, "switch", 6) == 0)
			{
				USER_IO_PE9_TOGGLE();
			}
			that_status = USER_IO_PE9_READ;
		}
		if (channel == 4)
		{
			if (memcmp(state, "high", 4) == 0)
			{
				USER_IO_PH15_HIGH();
			}
			if (memcmp(state, "low", 3) == 0)
			{
				USER_IO_PH15_LOW();
			}
			if (memcmp(state, "switch", 6) == 0)
			{
				USER_IO_PH15_TOGGLE();
			}
			that_status = USER_IO_PH15_READ;
		}
		if (channel == 5)
		{
			if (memcmp(state, "high", 4) == 0)
			{
				USER_IO_PE10_HIGH();
			}
			if (memcmp(state, "low", 3) == 0)
			{
				USER_IO_PE10_LOW();
			}
			if (memcmp(state, "switch", 6) == 0)
			{
				USER_IO_PE10_TOGGLE();
			}
			that_status = USER_IO_PE10_READ;
		}
		if (channel == 6)
		{
			if (memcmp(state, "high", 4) == 0)
			{
				USER_IO_PI1_HIGH();
			}
			if (memcmp(state, "low", 3) == 0)
			{
				USER_IO_PI1_LOW();
			}
			if (memcmp(state, "switch", 6) == 0)
			{
				USER_IO_PI1_TOGGLE();
			}
			that_status = USER_IO_PI1_READ;
		}
		if (channel == 7)
		{
			if (memcmp(state, "high", 4) == 0)
			{
				USER_IO_PE12_HIGH();
			}
			if (memcmp(state, "low", 3) == 0)
			{
				USER_IO_PE12_LOW();
			}
			if (memcmp(state, "switch", 6) == 0)
			{
				USER_IO_PE12_TOGGLE();
			}
			that_status = USER_IO_PE12_READ;
		}
		if (channel == 8)
		{
			if (memcmp(state, "high", 4) == 0)
			{
				USER_IO_PI3_HIGH();
			}
			if (memcmp(state, "low", 3) == 0)
			{
				USER_IO_PI3_LOW();
			}
			if (memcmp(state, "switch", 6) == 0)
			{
				USER_IO_PI3_TOGGLE();
			}
			that_status = USER_IO_PI3_READ;
		}
		if (channel == 9)
		{
			if (memcmp(state, "high", 4) == 0)
			{
				USER_IO_PF2_HIGH();
			}
			if (memcmp(state, "low", 3) == 0)
			{
				USER_IO_PF2_LOW();
			}
			if (memcmp(state, "switch", 6) == 0)
			{
				USER_IO_PF2_TOGGLE();
			}
			that_status = USER_IO_PF2_READ;
		}
		if (channel == 10)
		{
			if (memcmp(state, "high", 4) == 0)
			{
				USER_IO_PI4_HIGH();
			}
			if (memcmp(state, "low", 3) == 0)
			{
				USER_IO_PI4_LOW();
			}
			if (memcmp(state, "switch", 6) == 0)
			{
				USER_IO_PI4_TOGGLE();
			}
			that_status = USER_IO_PI4_READ;
		}
		if (channel == 11)
		{
			if (memcmp(state, "high", 4) == 0)
			{
				USER_IO_PF11_HIGH();
			}
			if (memcmp(state, "low", 3) == 0)
			{
				USER_IO_PF11_LOW();
			}
			if (memcmp(state, "switch", 6) == 0)
			{
				USER_IO_PF11_TOGGLE();
			}
			that_status = USER_IO_PF11_READ;
		}
		if (channel == 12)
		{
			if (memcmp(state, "high", 4) == 0)
			{
				USER_IO_PI8_HIGH();
			}
			if (memcmp(state, "low", 3) == 0)
			{
				USER_IO_PI8_LOW();
			}
			if (memcmp(state, "switch", 6) == 0)
			{
				USER_IO_PI8_TOGGLE();
			}
			that_status = USER_IO_PI8_READ;
		}
		if (channel == 13)
		{
			if (memcmp(state, "high", 4) == 0)
			{
				USER_IO_PF12_HIGH();
			}
			if (memcmp(state, "low", 3) == 0)
			{
				USER_IO_PF12_LOW();
			}
			if (memcmp(state, "switch", 6) == 0)
			{
				USER_IO_PF12_TOGGLE();
			}
			that_status = USER_IO_PF12_READ;
		}
		if (channel == 14)
		{
			if (memcmp(state, "high", 4) == 0)
			{
				USER_IO_PI9_HIGH();
			}
			if (memcmp(state, "low", 3) == 0)
			{
				USER_IO_PI9_LOW();
			}
			if (memcmp(state, "switch", 6) == 0)
			{
				USER_IO_PI9_TOGGLE();
			}
			that_status = USER_IO_PI9_READ;
		}
		if (channel == 15)
		{
			if (memcmp(state, "high", 4) == 0)
			{
				USER_IO_PF13_HIGH();
			}
			if (memcmp(state, "low", 3) == 0)
			{
				USER_IO_PF13_LOW();
			}
			if (memcmp(state, "switch", 6) == 0)
			{
				USER_IO_PF13_TOGGLE();
			}
			that_status = USER_IO_PF13_READ;
		}
		if (channel == 16)
		{
			if (memcmp(state, "high", 4) == 0)
			{
				USER_IO_PI10_HIGH();
			}
			if (memcmp(state, "low", 3) == 0)
			{
				USER_IO_PI10_LOW();
			}
			if (memcmp(state, "switch", 6) == 0)
			{
				USER_IO_PI10_TOGGLE();
			}
			that_status = USER_IO_PI10_READ;
		}
		if (channel == 17)
		{
			if (memcmp(state, "high", 4) == 0)
			{
				USER_IO_PF15_HIGH();
			}
			if (memcmp(state, "low", 3) == 0)
			{
				USER_IO_PF15_LOW();
			}
			if (memcmp(state, "switch", 6) == 0)
			{
				USER_IO_PF15_TOGGLE();
			}
			that_status = USER_IO_PF15_READ;
		}
		if (channel == 18)
		{
			if (memcmp(state, "high", 4) == 0)
			{
				USER_IO_PI11_HIGH();
			}
			if (memcmp(state, "low", 3) == 0)
			{
				USER_IO_PI11_LOW();
			}
			if (memcmp(state, "switch", 6) == 0)
			{
				USER_IO_PI11_TOGGLE();
			}
			that_status = USER_IO_PI11_READ;
		}
		Usb_Write_Data("{\"type\":\"io-status\",\"channel\":%d,\"status\":%d}\r\n", channel, that_status);
	}
}

void Io_Serial_Callback(cJSON *serial_data)
{
    cJSON *type = cJSON_GetObjectItem(serial_data, "type");
    if (type && cJSON_IsString(type))
    {
        if(strcmp(type->valuestring, "io-mode") == 0)
        {
            cJSON *channel = cJSON_GetObjectItem(serial_data, "channel");
            cJSON *mode = cJSON_GetObjectItem(serial_data, "mode");
            if (channel && cJSON_IsNumber(channel))
            {
                int ioChannel = (int)channel->valueint;
                Io_Model(ioChannel, mode->valuestring);
            }
        }

        if(strcmp(type->valuestring, "io-status") == 0)
        {
            cJSON *channel = cJSON_GetObjectItem(serial_data, "channel");
            cJSON *status = cJSON_GetObjectItem(serial_data, "status");
            if (channel && cJSON_IsNumber(channel))
            {
                int ioChannel = (int)channel->valueint;
                Io_State(channel, status->valuestring);
            }
        }
    }
}
