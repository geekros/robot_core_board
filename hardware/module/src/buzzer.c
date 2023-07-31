/**
 ******************************************************************************
 * @file    buzzer.c
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#include "buzzer.h"

void Buzzer_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM12, ENABLE);
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM12, DISABLE);

	GPIO_PinAFConfig(GPIOH, GPIO_PinSource6, GPIO_AF_TIM12);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOH, &GPIO_InitStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC1Init(TIM12, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM12, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM12, ENABLE);

	TIM_TimeBaseInitStructure.TIM_Period = 300 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 900 - 1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Down;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM12, &TIM_TimeBaseInitStructure);
	TIM_Cmd(TIM12, ENABLE);

	// 开发板启动音乐
	Buzzer_Start_Music();
}

void Buzzer_Start_Music(void)
{
	TIM12->PSC = MI_MIDDLE;
	TIM_SetCompare1(TIM12, 5);
	delay_ms(100);
	TIM_SetCompare1(TIM12, 300);
	delay_ms(50);

	TIM12->PSC = DO_MIDDLE;
	TIM_SetCompare1(TIM12, 5);
	delay_ms(100);
	TIM_SetCompare1(TIM12, 300);
	delay_ms(50);

	TIM12->PSC = MI_MIDDLE;
	TIM_SetCompare1(TIM12, 5);
	delay_ms(100);
	TIM_SetCompare1(TIM12, 300);
	delay_ms(50);

	TIM12->PSC = SO_MIDDLE;
	TIM_SetCompare1(TIM12, 5);
	delay_ms(500);
	TIM_SetCompare1(TIM12, 300);
	delay_ms(100);
}

void Buzzer_Low_Voltage_Music(void){
	TIM12->PSC = SO_LOW;
	TIM_SetCompare1(TIM12, 3);
	delay_ms(100);
	TIM_SetCompare1(TIM12, 300);
	delay_ms(50);

	TIM12->PSC = LA_LOW;
	TIM_SetCompare1(TIM12, 3);
	delay_ms(100);
	TIM_SetCompare1(TIM12, 300);
	delay_ms(50);
	
	TIM12->PSC = SI_LOW;
	TIM_SetCompare1(TIM12, 3);
	delay_ms(100);
	TIM_SetCompare1(TIM12, 300);
	delay_ms(50);
}

void Buzzer_Stop(void)
{
	TIM_SetCompare1(TIM12, 300);
	delay_ms(100);
}
