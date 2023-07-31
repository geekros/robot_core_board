/**
 ******************************************************************************
 * @file    rocker.h
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#ifndef MODULE_ROCKER
#define MODULE_ROCKER

#include <stm32f4xx.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "usb.h"
#include "utils.h"

#define ROCKER_BUFFER 128

typedef struct
{
	float left_x;
	float left_y;
	float right_x;
	float right_y;
	int key;
	volatile unsigned char buffer[ROCKER_BUFFER];
} Rocker_Struct;

extern Rocker_Struct Rocker_Data;

Rocker_Struct *Return_Rocker_Address(void);

void Rocker_Init(int baud_rate);

void Rocker_Serial_Callback(cJSON *serial_data);

#endif
