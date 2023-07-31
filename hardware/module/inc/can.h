/**
 ******************************************************************************
 * @file    can.h
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#ifndef MODULE_CAN
#define MODULE_CAN

#include <stm32f4xx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "usb.h"
#include "utils.h"

#define CAN_CHANNEL_LEN 2
#define CAN_MOTOR_LEN 12

typedef struct
{
	CanRxMsg Pid[CAN_CHANNEL_LEN][CAN_MOTOR_LEN];
	CanTxMsg Can_Write_Data[CAN_CHANNEL_LEN][CAN_MOTOR_LEN];
} Can_Struct;

extern Can_Struct Can_Data;

void Can_Init(void);

void Can1_Init(void);

void Can2_Init(void);

void CAN_Receive_Callback(CanRxMsg can_read_data, int channel, int motor_id);

void Can_Task(void);

void Can_Serial_Callback(cJSON *serial_data);

#endif
