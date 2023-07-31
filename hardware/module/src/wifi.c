/**
  ******************************************************************************
  * @file    wifi.c
  * @author  GEEKROS,  site:www.geekros.com
  ******************************************************************************
*/

#include "wifi.h"

Wifi_Struct Wifi_Data;

/******************************************************************
  * @ 函数名  ： Wifi_Init
  * @ 功能说明： ESP8266WiFi模块初始化，UART2作为WiFi模块专用接口
  * @ 参数    ： int baud_rate 波特率
  * @ 返回值  ： NULL
  *****************************************************************/
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



/******************************************************************
  * @ 函数名  ： USART2_IRQHandler
  * @ 功能说明： WiFi模块中断函数，接收UART2数据
  * @ 参数    ： NULL
  * @ 返回值  ： NULL
  *****************************************************************/
void USART2_IRQHandler(void)
{
	volatile static uint8_t data;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		data = USART_ReceiveData(USART2);
		// USART_SendData(USART2,data);
		if(data == '{')
		{
			// 检测到JSON数据起始符后开始记录数据
			Wifi_Data.buffer[0] = data;
			Wifi_Data.len = 1;
		}else if(data == '}'){
			// 检测到JSON数据结束符后停止数据记录
			Wifi_Data.buffer[Wifi_Data.len] = data;
			// 将完整的JSON数据传入JSON解析函数
			Wifi_Parse_Json((char*) Wifi_Data.buffer);
			Wifi_Data.len = 0;
		}else{
			// 判断是否检测到JSON数据起始符并记录数据
			if(Wifi_Data.len > 0){
				Wifi_Data.buffer[Wifi_Data.len] = data;
				Wifi_Data.len++;
			}
		}
	}
}

/******************************************************************
  * @ 函数名  ： Wifi_Parse_Json
  * @ 功能说明： 解析JSON数据
  * @ 参数    ： const char *json JSON字符串数据
  * @ 返回值  ： NULL
  *****************************************************************/
void Wifi_Parse_Json(char *json)
{
	// 回调USB串口任务的JSON通讯协议解析与处理函数
	Serial_Json_Handle(json);
}

/******************************************************************
  * @ 函数名  ： Wifi_Usb_Callback
  * @ 功能说明： 串口回调函数
  * @ 参数    ： int baud_rate 波特率
  * @ 返回值  ： NULL
  *****************************************************************/
void Wifi_Usb_Callback(char *type, int baud_rate)
{
	if(memcmp(type, "wifi-rate", 9) == 0)
	{
		Wifi_Init(baud_rate);
	}
}
