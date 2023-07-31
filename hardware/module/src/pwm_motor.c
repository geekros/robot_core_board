/**
 ******************************************************************************
 * @file    pwm_motor.c
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#include "pwm_motor.h"

/*******************************************************************************
 * @funtion      : Pwm_Motor_Init
 * @description  : 电机初始化
 * @param         {int Motor_Num} 电机编号
 * @param         {int Motor_Init_Frequency} 电机初始化频率
 * @param         {int Motor_Init_Time} 电机初始化控制行程
 * @return        {*}
 *******************************************************************************/
void Pwm_Motor_Init(int Motor_Num, int Motor_Init_Frequency, int Motor_Init_Time)
{
    if ((Motor_Num >= 1) && (Motor_Num <= 4))
    {
        //TIM4_Config(PWM_RESOLUTION, TIM_PSC_APB1, SERVO_DEFAULT_DUTY, PWM_CounterMode_Down, PWMO_OCMode_PWM1, PWM_OCPolarity_High);
    }
    if ((Motor_Num >= 5) && (Motor_Num <= 8))
    {
        //TIM5_Config(PWM_RESOLUTION, TIM_PSC_APB1, SERVO_DEFAULT_DUTY, PWM_CounterMode_Down, PWMO_OCMode_PWM1, PWM_OCPolarity_High);
    }
    if ((Motor_Num >= 9) && (Motor_Num <= 12))
    {
        //TIM2_Config(PWM_RESOLUTION, TIM_PSC_APB1, SERVO_DEFAULT_DUTY, PWM_CounterMode_Down, PWMO_OCMode_PWM1, PWM_OCPolarity_High);
    }
    if ((Motor_Num >= 13) && (Motor_Num <= 16))
    {
        //TIM8_Config(PWM_RESOLUTION, TIM_PSC_APB1, SERVO_DEFAULT_DUTY, PWM_CounterMode_Down, PWMO_OCMode_PWM1, PWM_OCPolarity_High);
    }
    //Pwm_Control(Motor_Num, Motor_Init_Frequency, Motor_Init_Time);
}

/*******************************************************************************
 * @funtion      : Pwm_Motor_Usb_Callback
 * @description  : 串口任务回调函数
 * @param         {int Motor_Num} 电机编号
 * @param         {int Motor_Init_Frequency} 电机频率
 * @param         {int Motor_Speed} 电机转速
 * @return        {*}
 *******************************************************************************/
void Pwm_Motor_Usb_Callback(char *type, int Motor_Num, int Motor_Frequency, int Motor_Speed)
{
    if (memcmp(type, "pwm-motor", 9) == 0)
    {
        //Pwm_Control(Motor_Num, Motor_Frequency, Motor_Speed);
    }
}
