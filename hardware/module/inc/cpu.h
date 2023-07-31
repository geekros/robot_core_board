/**
 ******************************************************************************
 * @file    cpu.h
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#ifndef MODULAR_CPU
#define MODULAR_CPU

#include <stm32f4xx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "usb.h"

void Cpu_Init(void);

float Cpu_Temperature(void);

void Cpu_Usb_Callback(char *type);

#endif
