/**
 ******************************************************************************
 * @file    module.c
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#include "module.h"

Serial_Data_Struct Serial_Read_Data;

void Module_Handle(char *serial_task_buffer)
{
    cJSON *serial_data;
    serial_data = cJSON_Parse(serial_task_buffer);
    if (serial_data)
    {
        Serial_Read_Data.type = cJSON_GetObjectItem(Serial_Data, "type")->valuestring;
        if (Serial_Read_Data.type == "version")
        {
            Get_Version();
        }
    }

    cJSON_Delete(serial_data);
}

void Get_Version(void)
{
    Usb_Write_Data("{\"type\":\"version\",\"state\":%s}\r\n", "1.0.0");
}