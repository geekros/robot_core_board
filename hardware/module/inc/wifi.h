/**
 ******************************************************************************
 * @file    wifi.h
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#ifndef MODULE_WIFI
#define MODULE_WIFI


#include <stm32f4xx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "usb.h"
#include "utils.h"
#include "module.h"

#define WIFI_DATA_LEN 128

typedef struct{
	char buffer[WIFI_DATA_LEN];
	int len;
}Wifi_Struct;

extern Wifi_Struct Wifi_Data;

void Wifi_Init(int baud_rate);

void Wifi_Serial_Callback(cJSON *serial_data);

#endif
