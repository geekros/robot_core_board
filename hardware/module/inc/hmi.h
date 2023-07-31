/**
 ******************************************************************************
 * @file    hmi.h
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#ifndef MODULAR_HMI
#define MODULAR_HMI

#include "stm32f4xx.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "serial_task.h"

#define HMI_DATA_LEN 128

typedef struct
{
	char buffer[HMI_DATA_LEN];
	int len;
} Hmi_Struct;

extern Hmi_Struct Hmi_Data;

void Hmi_Init(int baud_rate);

void Hmi_Parse_Json(char *json);

void Hmi_Usb_Callback(char *type, int baud_rate);

#endif
