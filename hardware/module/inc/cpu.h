/**
 ******************************************************************************
 * @file    cpu.h
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#ifndef MODULE_CPU
#define MODULE_CPU

#include <stm32f4xx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "usb.h"
#include "utils.h"

void Cpu_Init(void);

float Cpu_Temperature(void);

void Cpu_Serial_Callback(cJSON *serial_data);

#endif
