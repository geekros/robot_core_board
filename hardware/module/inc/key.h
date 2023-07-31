/**
 ******************************************************************************
 * @file    key.h
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#ifndef MODULAR_KEY
#define MODULAR_KEY

#include <stm32f4xx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "usb.h"

#define Key_State GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2)

void Key_Init(void);

void Key_Usb_Callback(char *type);

#endif
