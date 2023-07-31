/**
  ******************************************************************************
  * @file    wifi.c
  * @author  GEEKROS,  site:www.geekros.com
  ******************************************************************************
*/

#include "wifi.h"

Wifi_Struct Wifi_Data;

void Wifi_Init(int baud_rate)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2); 

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
  	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	USART_DeInit(USART2);
	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate = baud_rate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  	USART_Init(USART2, &USART_InitStructure);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
  	USART_Cmd(USART2, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}

void USART2_IRQHandler(void)
{
	volatile static uint8_t data;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		data = USART_ReceiveData(USART2);
		if(data == '{')
		{
			Wifi_Data.buffer[0] = data;
			Wifi_Data.len = 1;
		}else if(data == '}'){
			Wifi_Data.buffer[Wifi_Data.len] = data;
			Module_Handle((char*) Wifi_Data.buffer);
			Wifi_Data.len = 0;
		}else{
			if(Wifi_Data.len > 0){
				Wifi_Data.buffer[Wifi_Data.len] = data;
				Wifi_Data.len++;
			}
		}
	}
}

void Wifi_Serial_Callback(cJSON *serial_data)
{
    cJSON *type = cJSON_GetObjectItem(serial_data, "type");
    if (type && cJSON_IsString(type))
    {
        if(strcmp(type->valuestring, "wifi-init") == 0)
        {
            cJSON *baud_rate = cJSON_GetObjectItem(serial_data, "baud_rate");
            if (baud_rate && cJSON_IsNumber(baud_rate))
            {
                Wifi_Init((int)baud_rate->valueint);
            }
        }
    }
}
