/**
 ******************************************************************************
 * @file    wifi.h
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#ifndef MODULE_WIFI
#define MODULE_WIFI

#include "stm32f4xx.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "serial_task.h"

#define WIFI_DATA_LEN 128

typedef struct{
	char buffer[WIFI_DATA_LEN];
	int len;
}Wifi_Struct;

extern Wifi_Struct Wifi_Data;

void Wifi_Init(int baud_rate);

void Wifi_Parse_Json(char *json);

void Wifi_Usb_Callback(char *type, int baud_rate);

#endif
