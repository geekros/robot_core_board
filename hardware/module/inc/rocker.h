/**
 ******************************************************************************
 * @file    rocker.h
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#ifndef MODULAR_REMOTE_CONTROL
#define MODULAR_REMOTE_CONTROL

#include <stm32f4xx.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "usb.h"

#define ROCKER_BUFFER 128

typedef struct
{
	float c0;
	float c1;
	float c2;
	float c3;
	int s1;
	int s2;
	volatile unsigned char buffer[ROCKER_BUFFER];
} Rocker_Struct;

extern Rocker_Struct Rocker_Data;

Rocker_Struct *Return_Rocker_Address(void);

void Rocker_Init(int baud_rate);

void Rocker_Usb_Callback(char *type, int s1, int s2, float c0, float c1, float c2, float c3);

#endif
