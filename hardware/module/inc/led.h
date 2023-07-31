/**
 ******************************************************************************
 * @file    led.h
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#ifndef MODULE_LED
#define MODULE_LED

#include <stm32f4xx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "usb.h"
#include "utils.h"

#define RED_LED_ON() GPIO_ResetBits(GPIOE, GPIO_Pin_11)
#define RED_LED_OFF() GPIO_SetBits(GPIOE, GPIO_Pin_11)
#define RED_LED_TOGGLE() GPIO_ToggleBits(GPIOE, GPIO_Pin_11)

#define GREEN_LED_ON() GPIO_ResetBits(GPIOF, GPIO_Pin_14)
#define GREEN_LED_OFF() GPIO_SetBits(GPIOF, GPIO_Pin_14)
#define GREEN_LED_TOGGLE() GPIO_ToggleBits(GPIOF, GPIO_Pin_14)

#define BLUE_LED_ON() GPIO_ResetBits(GPIOH, GPIO_Pin_13)
#define BLUE_LED_OFF() GPIO_SetBits(GPIOH, GPIO_Pin_13)
#define BLUE_LED_TOGGLE() GPIO_ToggleBits(GPIOH, GPIO_Pin_13)

void Led_Init(void);

void Led_All_Status(char *status);

void Led_Status(char *channel, char *status);

void Led_Serial_Callback(cJSON *serial_data);

#endif
