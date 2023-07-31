/**
 ******************************************************************************
 * @file    led.c
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#include "led.h"

/*******************************************************************************
 * @funtion      : Led_Init
 * @description  : 模块初始化
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Led_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOH, &GPIO_InitStructure);

	GREEN_LED_OFF();
	RED_LED_OFF();
	BLUE_LED_OFF();
}

/*******************************************************************************
 * @funtion      : Led_All_State
 * @description  : 所有LED状态
 * @param         {char *state} 状态 可选值off、on、switch
 * @return        {*}
 *******************************************************************************/
void Led_All_State(char *state)
{
	if (memcmp(state, "off", 3) == 0)
	{
		GREEN_LED_OFF();
		RED_LED_OFF();
		BLUE_LED_OFF();
	}
	if (memcmp(state, "on", 2) == 0)
	{
		GREEN_LED_ON();
		RED_LED_ON();
		BLUE_LED_ON();
	}
	if (memcmp(state, "switch", 6) == 0)
	{
		GREEN_LED_TOGGLE();
		RED_LED_TOGGLE();
		BLUE_LED_TOGGLE();
	}
}

/*******************************************************************************
 * @funtion      : Led_State
 * @description  : LED状态
 * @param         {char *channel} 通道 可选值green、red、blue
 * @param         {char *state} 状态 可选值off、on、switch
 * @return        {*}
 *******************************************************************************/
void Led_State(char *channel, char *state)
{
	if (memcmp(channel, "green", 5) == 0)
	{
		if (memcmp(state, "switch", 6) == 0)
		{
			GREEN_LED_TOGGLE();
		}
		if (memcmp(state, "off", 3) == 0)
		{
			GREEN_LED_OFF();
		}
		if (memcmp(state, "on", 2) == 0)
		{
			GREEN_LED_ON();
		}
	}
	if (memcmp(channel, "red", 3) == 0)
	{
		if (memcmp(state, "switch", 6) == 0)
		{
			RED_LED_TOGGLE();
		}
		if (memcmp(state, "off", 3) == 0)
		{
			RED_LED_OFF();
		}
		if (memcmp(state, "on", 2) == 0)
		{
			RED_LED_ON();
		}
	}
	if (memcmp(channel, "blue", 4) == 0)
	{
		if (memcmp(state, "switch", 6) == 0)
		{
			BLUE_LED_TOGGLE();
		}
		if (memcmp(state, "off", 3) == 0)
		{
			BLUE_LED_OFF();
		}
		if (memcmp(state, "on", 2) == 0)
		{
			BLUE_LED_ON();
		}
	}
}

/*******************************************************************************
 * @funtion      : Led_Usb_Callback
 * @description  : 串口任务回调函数
 * @param         {char *type} 通讯协议类型
 * @param         {char *channel} 通道 可选值green、red、blue
 * @param         {char *state} 状态 可选值off、on、switch
 * @return        {*}
 *******************************************************************************/
void Led_Usb_Callback(char *type, char *channel, char *state)
{
	if (memcmp(type, "led-state", 9) == 0)
	{
		if (memcmp(channel, "all", 3) == 0)
		{
			Led_All_State(state);
		}
		else
		{
			Led_State(channel, state);
		}
	}
}
