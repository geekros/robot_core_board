/**
 ******************************************************************************
 * @file    power.h
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#ifndef MODULE_POWER
#define MODULE_POWER

#include <stm32f4xx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "usb.h"
#include "utils.h"

#define POWER1_24V_OFF() GPIO_ResetBits(GPIOH, GPIO_Pin_2)
#define POWER1_24V_ON() GPIO_SetBits(GPIOH, GPIO_Pin_2)

#define POWER2_24V_OFF() GPIO_ResetBits(GPIOH, GPIO_Pin_4)
#define POWER2_24V_ON() GPIO_SetBits(GPIOH, GPIO_Pin_4)

#define POWER3_24V_OFF() GPIO_ResetBits(GPIOH, GPIO_Pin_3)
#define POWER3_24V_ON() GPIO_SetBits(GPIOH, GPIO_Pin_3)

#define POWER4_24V_OFF() GPIO_ResetBits(GPIOH, GPIO_Pin_5)
#define POWER4_24V_ON() GPIO_SetBits(GPIOH, GPIO_Pin_5)

#define POWER_5V_A_OFF() GPIO_ResetBits(GPIOA, GPIO_Pin_15)
#define POWER_5V_A_ON() GPIO_SetBits(GPIOA, GPIO_Pin_15)
#define POWER_5V_A_TOGGLE() GPIO_ToggleBits(GPIOA, GPIO_Pin_15)

#define POWER_5V_B_OFF() GPIO_ResetBits(GPIOB, GPIO_Pin_11)
#define POWER_5V_B_ON() GPIO_SetBits(GPIOB, GPIO_Pin_11)
#define POWER_5V_B_TOGGLE() GPIO_ToggleBits(GPIOB, GPIO_Pin_11)

void Power_Init(void);

void Power_24v_Init(void);

void Power_5v_Init(void);

void Power_5v_Status(int id, char *status);

void Power_24v_Status(int id, char *status);

void Power_Status(int channel, int id, char *status);

void Power_Serial_Callback(cJSON *serial_data);

#endif
