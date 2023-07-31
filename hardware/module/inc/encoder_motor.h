/**
 ******************************************************************************
 * @file    encoder_motor.h
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#ifndef MODULAR_ENCODER_MOTOR
#define MODULAR_ENCODER_MOTOR

#include <stm32f4xx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pwm.h"

// 圆周率
#define MOTOR_PI 3.1415926535
// 车轮直径,单位毫米
#define WHEEL_DIAMETER 65
// 车轮周长
#define WHEEL_PERIMETER (MOTOR_PI*WHEEL_DIAMETER)
// 电机每周的脉冲数
#define MOTOR_PULSE 330
// 电机闭环控制时间片,单位毫秒
#define MOTOR_TIME_SLICE 20
// 电机PID闭环控制P参数
#define MOTOR_PID_P 20
// 电机PID闭环控制d参数
#define MOTOR_PID_D 15

/*电机状态结构体*/
typedef struct
{
    int16_t left_motor_count; // 左侧电机编码器计数
    int16_t right_motor_count; // 右侧电机编码器计数
	int16_t left_motor_pulse; // 左侧电机编码器在上一个时间片内的脉冲数,即当前脉冲数,每两次采样之间的时间称为1个时间片
	int16_t right_motor_pulse; // 右侧电机编码器在上一个时间片内的脉冲数,即当前脉冲数,每两次采样之间的时间称为1个时间片
    uint16_t left_current_speed; // 左侧电机当前速度,毫米每秒,最高2位含义为, 二进制00:惯性滑行,01:正转,10:反转,11:阻尼刹车,详情参考手册中通信协议部分
    uint16_t right_current_speed; // 右侧电机当前速度,毫米每秒,最高2位含义为, 二进制00:惯性滑行,01:正转,10:反转,11:阻尼刹车,详情参考手册中通信协议部分
    uint16_t left_target_speed; // 左侧电机目标速度,毫米每秒,最高2位含义为, 二进制00:惯性滑行,01:正转,10:反转,11:阻尼刹车,详情参考手册中通信协议部分
    uint16_t right_target_speed; // 右侧电机目标速度,毫米每秒,最高2位含义为, 二进制00:惯性滑行,01:正转,10:反转,11:阻尼刹车,详情参考手册中通信协议部分
}Encoder_Motor_Struct;

extern Encoder_Motor_Struct Encoder_Motor_Data;

void Encoder_Motor_Init(void);

void Encoder_Motor_Stop(void);

void Encoder_Motor_Count(void);

void Encoder_Motor_Speed_Calculate(void);

void Encoder_Left_Motor_Pwm(int16_t motor);

void Encoder_Right_Motor_Pwm(int16_t motor);

void Encoder_Motor_Tim_Init(void);

void Encoder_Motor_Left_Init(void);

void Encoder_Motor_Right_Init(void);

#endif

