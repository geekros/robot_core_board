/**
 ******************************************************************************
 * @file    module.h
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#ifndef MODULE
#define MODULE

#include "led.h"
#include "usb.h"
#include "buzzer.h"
#include "can.h"
#include "power.h"
#include "key.h"
#include "adc.h"
#include "io.h"
#include "pwm.h"
#include "cpu.h"
#include "flash.h"
#include "mpu.h"
#include "rocker.h"
#include "wifi.h"
#include "servo.h"
#include "hmi.h"
#include "radar.h"
#include "pwm_motor.h"
#include "encoder_motor.h"

typedef struct
{
    char *type;
} Serial_Data_Struct;

extern Serial_Data_Struct Serial_Read_Data;

void Module_Handle(char *serial_task_buffer);

void Get_Version(void);

#endif
