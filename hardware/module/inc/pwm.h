/**
 ******************************************************************************
 * @file    pwm.h
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#ifndef MODULAR_PWM
#define MODULAR_PWM

#include <stm32f4xx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PWM_PD12_READ GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12)
#define PWM_PD13_READ GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13)
#define PWM_PD14_READ GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_14)
#define PWM_PD15_READ GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_15)
#define PWM_PH10_READ GPIO_ReadInputDataBit(GPIOH, GPIO_Pin_10)
#define PWM_PH11_READ GPIO_ReadInputDataBit(GPIOH, GPIO_Pin_11)
#define PWM_PH12_READ GPIO_ReadInputDataBit(GPIOH, GPIO_Pin_12)
#define PWM_PI0_READ GPIO_ReadInputDataBit(GPIOI, GPIO_Pin_0)
#define PWM_PA0_READ GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)
#define PWM_PA1_READ GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)
#define PWM_PA2_READ GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)
#define PWM_PA3_READ GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)
#define PWM_PI5_READ GPIO_ReadInputDataBit(GPIOI, GPIO_Pin_5)
#define PWM_PI6_READ GPIO_ReadInputDataBit(GPIOI, GPIO_Pin_6)
#define PWM_PI7_READ GPIO_ReadInputDataBit(GPIOI, GPIO_Pin_7)
#define PWM_PI2_READ GPIO_ReadInputDataBit(GPIOI, GPIO_Pin_2)
#define PWM_PA8_READ GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)
#define PWM_PA9_READ GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9)
#define PWM_PE13_READ GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13)
#define PWM_PE14_READ GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14)

#define PWM_PA8_HIGH() GPIO_ResetBits(GPIOA, GPIO_Pin_8)
#define PWM_PA8_LOW() GPIO_SetBits(GPIOA, GPIO_Pin_8)
#define PWM_PA8_TOGGLE() GPIO_ToggleBits(GPIOA, GPIO_Pin_8)

#define PWM_PA9_HIGH() GPIO_ResetBits(GPIOA, GPIO_Pin_9)
#define PWM_PA9_LOW() GPIO_SetBits(GPIOA, GPIO_Pin_9)
#define PWM_PA9_TOGGLE() GPIO_ToggleBits(GPIOA, GPIO_Pin_9)

#define PWM_PE13_HIGH() GPIO_ResetBits(GPIOE, GPIO_Pin_13)
#define PWM_PE13_LOW() GPIO_SetBits(GPIOE, GPIO_Pin_13)
#define PWM_PE13_TOGGLE() GPIO_ToggleBits(GPIOE, GPIO_Pin_13)

#define PWM_PE14_HIGH() GPIO_ResetBits(GPIOE, GPIO_Pin_14)
#define PWM_PE14_LOW() GPIO_SetBits(GPIOE, GPIO_Pin_14)
#define PWM_PE14_TOGGLE() GPIO_ToggleBits(GPIOE, GPIO_Pin_14)

#define PWM_PD12_HIGH() GPIO_ResetBits(GPIOD, GPIO_Pin_12)
#define PWM_PD12_LOW() GPIO_SetBits(GPIOD, GPIO_Pin_12)
#define PWM_PD12_TOGGLE() GPIO_ToggleBits(GPIOD, GPIO_Pin_12)

#define PWM_PD13_HIGH() GPIO_ResetBits(GPIOD, GPIO_Pin_13)
#define PWM_PD13_LOW() GPIO_SetBits(GPIOD, GPIO_Pin_13)
#define PWM_PD13_TOGGLE() GPIO_ToggleBits(GPIOD, GPIO_Pin_13)

#define PWM_PD14_HIGH() GPIO_ResetBits(GPIOD, GPIO_Pin_14)
#define PWM_PD14_LOW() GPIO_SetBits(GPIOD, GPIO_Pin_14)
#define PWM_PD14_TOGGLE() GPIO_ToggleBits(GPIOD, GPIO_Pin_14)

#define PWM_PD15_HIGH() GPIO_ResetBits(GPIOD, GPIO_Pin_15)
#define PWM_PD15_LOW() GPIO_SetBits(GPIOD, GPIO_Pin_15)
#define PWM_PD15_TOGGLE() GPIO_ToggleBits(GPIOD, GPIO_Pin_15)

#define PWM_PH10_HIGH() GPIO_ResetBits(GPIOH, GPIO_Pin_10)
#define PWM_PH10_LOW() GPIO_SetBits(GPIOH, GPIO_Pin_10)
#define PWM_PH10_TOGGLE() GPIO_ToggleBits(GPIOH, GPIO_Pin_10)

#define PWM_PH11_HIGH() GPIO_ResetBits(GPIOH, GPIO_Pin_11)
#define PWM_PH11_LOW() GPIO_SetBits(GPIOH, GPIO_Pin_11)
#define PWM_PH11_TOGGLE() GPIO_ToggleBits(GPIOH, GPIO_Pin_11)

#define PWM_PH12_HIGH() GPIO_ResetBits(GPIOH, GPIO_Pin_12)
#define PWM_PH12_LOW() GPIO_SetBits(GPIOH, GPIO_Pin_12)
#define PWM_PH12_TOGGLE() GPIO_ToggleBits(GPIOH, GPIO_Pin_12)

#define PWM_PI0_HIGH() GPIO_ResetBits(GPIOI, GPIO_Pin_0)
#define PWM_PI0_LOW() GPIO_SetBits(GPIOI, GPIO_Pin_0)
#define PWM_PI0_TOGGLE() GPIO_ToggleBits(GPIOI, GPIO_Pin_0)

#define PWM_PA0_HIGH() GPIO_ResetBits(GPIOA, GPIO_Pin_0)
#define PWM_PA0_LOW() GPIO_SetBits(GPIOA, GPIO_Pin_0)
#define PWM_PA0_TOGGLE() GPIO_ToggleBits(GPIOA, GPIO_Pin_0)

#define PWM_PA1_HIGH() GPIO_ResetBits(GPIOA, GPIO_Pin_1)
#define PWM_PA1_LOW() GPIO_SetBits(GPIOA, GPIO_Pin_1)
#define PWM_PA1_TOGGLE() GPIO_ToggleBits(GPIOA, GPIO_Pin_1)

#define PWM_PA2_HIGH() GPIO_ResetBits(GPIOA, GPIO_Pin_2)
#define PWM_PA2_LOW() GPIO_SetBits(GPIOA, GPIO_Pin_2)
#define PWM_PA2_TOGGLE() GPIO_ToggleBits(GPIOA, GPIO_Pin_2)

#define PWM_PA3_HIGH() GPIO_ResetBits(GPIOA, GPIO_Pin_3)
#define PWM_PA3_LOW() GPIO_SetBits(GPIOA, GPIO_Pin_3)
#define PWM_PA3_TOGGLE() GPIO_ToggleBits(GPIOA, GPIO_Pin_3)

#define PWM_PI5_HIGH() GPIO_ResetBits(GPIOI, GPIO_Pin_5)
#define PWM_PI5_LOW() GPIO_SetBits(GPIOI, GPIO_Pin_5)
#define PWM_PI5_TOGGLE() GPIO_ToggleBits(GPIOI, GPIO_Pin_5)

#define PWM_PI6_HIGH() GPIO_ResetBits(GPIOI, GPIO_Pin_6)
#define PWM_PI6_LOW() GPIO_SetBits(GPIOI, GPIO_Pin_6)
#define PWM_PI6_TOGGLE() GPIO_ToggleBits(GPIOI, GPIO_Pin_6)

#define PWM_PI7_HIGH() GPIO_ResetBits(GPIOI, GPIO_Pin_7)
#define PWM_PI7_LOW() GPIO_SetBits(GPIOI, GPIO_Pin_7)
#define PWM_PI7_TOGGLE() GPIO_ToggleBits(GPIOI, GPIO_Pin_7)

#define PWM_PI2_HIGH() GPIO_ResetBits(GPIOI, GPIO_Pin_2)
#define PWM_PI2_LOW() GPIO_SetBits(GPIOI, GPIO_Pin_2)
#define PWM_PI2_TOGGLE() GPIO_ToggleBits(GPIOI, GPIO_Pin_2)


// 舵机PWM参数
#define PWM_FREQUENCE 50
#define PWM_RESOLUTION 20000
#define SERVO_DEFAULT_DUTY 1500
#define APB1_TIMER_CLOCKS 84000000
#define TIM_PSC_APB1 ((APB1_TIMER_CLOCKS / PWM_FREQUENCE) / PWM_RESOLUTION - 1)
#define APB2_TIMER_CLOCKS 168000000
#define TIM_PSC_APB2 ((APB2_TIMER_CLOCKS / PWM_FREQUENCE) / PWM_RESOLUTION - 1)

// 电机PWM频率
#define MOTOR_PWM_FREQUENCE 1000
// 电机PWM分辨率
#define MOTOR_PWM_RESOLUTION 1000
// 电机PWM默认值
#define MOTOR_DEFAULT_DUTY 0
// 电机TIM8定时器
#define TIM8_PSC_APB2 ((APB2_TIMER_CLOCKS / MOTOR_PWM_FREQUENCE) / MOTOR_PWM_RESOLUTION - 1)

typedef enum
{
	PWM_CounterMode_Up,
	PWM_CounterMode_Down
} PWM_CounterMode_Struct;

typedef enum
{
	PWMO_OCMode_PWM1,
	PWM_OCMode_PWM2
} PWM_OCMode_Struct;

typedef enum
{
	PWM_OCPolarity_High,
	PWM_OCPolarity_Low
} PWM_OCPolarity_Struct;

void Pwm_Init(void);

void TIM1_Config(void);

void TIM8_Config(void);

void TIM2_Config(void);

void TIM4_Config(void);

void TIM5_Config(void);

void Pwm_Control(int channel, uint16_t pwm);

void Pwm_Usb_Callback(char *type, int channel, int width);

#endif
