/**
 ******************************************************************************
 * @file    adc.h
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#ifndef MODULAR_ADC
#define MODULAR_ADC

#include <stm32f4xx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "usb.h"
#include "buzzer.h"
#include "utils.h"

extern float Low_Voltage;

void Adc_Init(void);

void Adc_Task(void);

float Adc_Pwm_Voltage(void);

float Adc_Board_Voltage(void);

void Adc_Low_Voltage(float voltage);

void Adc_Usb_Callback(char *type, float voltage);

#endif
