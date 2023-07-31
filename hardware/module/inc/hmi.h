/**
 ******************************************************************************
 * @file    hmi.h
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#ifndef MODULE_HMI
#define MODULE_HMI

#include <stm32f4xx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "usb.h"
#include "utils.h"
#include "module.h"

#define HMI_DATA_LEN 128

typedef struct
{
	char buffer[HMI_DATA_LEN];
	int len;
} Hmi_Struct;

extern Hmi_Struct Hmi_Data;

void Hmi_Init(int baud_rate);

void Hmi_Serial_Callback(cJSON *serial_data);

#endif
