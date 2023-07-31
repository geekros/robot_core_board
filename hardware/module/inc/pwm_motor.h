/**
 ******************************************************************************
 * @file    pwm_motor.h
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#ifndef MODULAR_PWM_MOTOR
#define MODULAR_PWM_MOTOR

#include <stm32f4xx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pwm.h"

void Pwm_Motor_Init(int Motor_Num, int Motor_Init_Frequency, int Motor_Init_Time);

void Pwm_Motor_Usb_Callback(char *type, int Motor_Num, int Motor_Frequency, int Motor_Speed);

#endif
