/**
 ******************************************************************************
 * @file    main.c
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#include "main.h"

int main(void)
{
    Delay_Init(configTICK_RATE_HZ);

    Task_Manage();

    vTaskStartScheduler();
}

void System_Task(void)
{
    while (1)
    {
        delay_ms(1);
    }
}

void Serial_Task(void)
{
    while (1)
    {
        Usb_Read_Data((uint8_t *)Serial_Task_Buffer, Serial_Task_Buffer_Len);

        Module_Handle((char *)Serial_Task_Buffer);

        for (int i = 0; i < Serial_Task_Buffer_Len; i++)
        {
            if (Serial_Task_Buffer[i] == NULL)
            {
                break;
            }else{
                Serial_Task_Buffer[i] = NULL;
            }
        }

        delay_ms(5);
    }
}

void User_Task(void)
{
    Setup();
    while (1)
    {
        Loop();
    }
}

void Task_Manage(void)
{
    xTaskCreate((TaskFunction_t)Main_Task, (const char *)"Main_Task", (uint16_t)MAIN_TASK_SIZE, (void *)NULL, (UBaseType_t)MAIN_TASK_PRIO, (TaskHandle_t *)&Main_Task_Handler);
}

void Main_Task(void *pvParameters)
{
    taskENTER_CRITICAL();

    xTaskCreate((TaskFunction_t)System_Task, (const char *)"System_Task", (uint16_t)SYSTEM_TASK_SIZE, (void *)NULL, (UBaseType_t)SYSTEM_TASK_PRIO, (TaskHandle_t *)&System_Task_Handler);

    xTaskCreate((TaskFunction_t)Serial_Task, (const char *)"Serial_Task", (uint16_t)SERIAL_TASK_SIZE, (void *)NULL, (UBaseType_t)SERIAL_TASK_PRIO, (TaskHandle_t *)&Serial_Task_Handler);

    xTaskCreate((TaskFunction_t)User_Task, (const char *)"User_Task", (uint16_t)USER_TASK_SIZE, (void *)NULL, (UBaseType_t)USER_TASK_PRIO, (TaskHandle_t *)&User_Task_Handler);

    vTaskDelete(Start_Task_Handler);

    taskEXIT_CRITICAL();
}
