/**
  ******************************************************************************
  * @file    main.h
  * @author  GEEKROS,  site:www.geekros.com
  ******************************************************************************
*/

#ifndef MAIN
#define MAIN

#include "app.h"
#include "module.h"
#include "utils.h"

uint32_t Serial_Task_Buffer_Len = 1024;
uint8_t Serial_Task_Buffer[1024];

void System_Task(void);

void Serial_Task(void);

void User_Task(void);

void Task_Manage(void);

void Main_Task(void *pvParameters);

#endif
