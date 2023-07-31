/**
 ******************************************************************************
 * @file    power.c
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#include "power.h"

/*******************************************************************************
 * @funtion      : Power_Init
 * @description  : 模块初始化
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Power_Init(void)
{
	Power_24v_Init();
	Power_5v_Init();
}

/*******************************************************************************
 * @funtion      : Power_24v_Init
 * @description  : 24v可控电源接口初始化，开发板共4组24v可控电源接口
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Power_24v_Init(void)
{
	GPIO_InitTypeDef gpio;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);

	gpio.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOH, &gpio);

	// 默认关闭所有24v电源接口
	POWER1_24V_OFF();
	POWER2_24V_OFF();
	POWER3_24V_OFF();
	POWER4_24V_OFF();
}

/*******************************************************************************
 * @funtion      : Power_5v_Init
 * @description  : 5v可控电源接口初始化，开发板共2组5v可控电源接口
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
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

	// 默认关闭所有5v电源接口
	POWER_5V_A_OFF();
	POWER_5V_B_OFF();
}

/*******************************************************************************
 * @funtion      : Power_5v_State
 * @description  : 5v可控电源状态
 * @param         {int id} ID编号 可选值：0、1、2
 * @param         {char *state} 状态 可选值：on、off
 * @return        {*}
 *******************************************************************************/
void Power_5v_State(int id, char *state)
{
	if (id == 0)
	{
		if (memcmp(state, "on", 2) == 0)
		{
			POWER_5V_A_ON();
			POWER_5V_B_ON();
		}
		if (memcmp(state, "off", 3) == 0)
		{
			POWER_5V_A_OFF();
			POWER_5V_B_OFF();
		}
	}
	if (id == 1)
	{
		if (memcmp(state, "on", 2) == 0)
		{
			POWER_5V_A_ON();
		}
		if (memcmp(state, "off", 3) == 0)
		{
			POWER_5V_A_OFF();
		}
	}
	if (id == 2)
	{
		if (memcmp(state, "on", 2) == 0)
		{
			POWER_5V_B_ON();
		}
		if (memcmp(state, "off", 3) == 0)
		{
			POWER_5V_B_OFF();
		}
	}
}

/*******************************************************************************
 * @funtion      : Power_24v_State
 * @description  : 5v可控电源状态
 * @param         {int id} ID编号 可选值：0、1、2、3、4
 * @param         {char *state} 状态 可选值：on、off
 * @return        {*}
 *******************************************************************************/
void Power_24v_State(int id, char *state)
{
	if (id == 0)
	{
		if (memcmp(state, "on", 2) == 0)
		{
			POWER1_24V_ON();
			POWER2_24V_ON();
			POWER3_24V_ON();
			POWER4_24V_ON();
		}
		if (memcmp(state, "off", 3) == 0)
		{
			POWER1_24V_OFF();
			POWER2_24V_OFF();
			POWER3_24V_OFF();
			POWER4_24V_OFF();
		}
	}
	if (id == 1)
	{
		if (memcmp(state, "on", 2) == 0)
		{
			POWER1_24V_ON();
		}
		if (memcmp(state, "off", 3) == 0)
		{
			POWER1_24V_OFF();
		}
	}
	if (id == 2)
	{
		if (memcmp(state, "on", 2) == 0)
		{
			POWER2_24V_ON();
		}
		if (memcmp(state, "off", 3) == 0)
		{
			POWER2_24V_OFF();
		}
	}
	if (id == 3)
	{
		if (memcmp(state, "on", 2) == 0)
		{
			POWER3_24V_ON();
		}
		if (memcmp(state, "off", 3) == 0)
		{
			POWER3_24V_OFF();
		}
	}
	if (id == 4)
	{
		if (memcmp(state, "on", 2) == 0)
		{
			POWER4_24V_ON();
		}
		if (memcmp(state, "off", 3) == 0)
		{
			POWER4_24V_OFF();
		}
	}
}

/*******************************************************************************
 * @funtion      : Power_State
 * @description  : 可控电源状态
 * @param         {int channel} 通道 可选值：5、24
 * @param         {int id} ID编号 可选值：0、1、2、3、4
 * @param         {char *state} 状态 可选值：on、off
 * @return        {*}
 *******************************************************************************/
void Power_State(int channel, int id, char *state)
{
	if (channel == 24)
	{
		Power_24v_State(id, state);
	}
	if (channel == 5)
	{
		Power_5v_State(id, state);
	}
}

/*******************************************************************************
 * @funtion      : Power_Usb_Callback
 * @description  : 串口任务回调函数
 * @param         {char *type} 通讯协议类型
 * @param         {int channel} 通道 可选值：5、24
 * @param         {int id} ID编号 可选值：0、1、2、3、4
 * @param         {char *state} 状态 可选值：on、off
 * @return        {*}
 *******************************************************************************/
void Power_Usb_Callback(char *type, int channel, int id, char *state)
{
	if (memcmp(type, "power-state", 11) == 0)
	{
		Power_State(channel, id, state);
	}
}
