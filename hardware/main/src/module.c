/**
 ******************************************************************************
 * @file    module.c
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#include "module.h"

Serial_Data_Struct Serial_Read_Data;

void Module_Handle(char *json)
{
    cJSON *serial_data;
    serial_data = cJSON_Parse(json);
    if (serial_data)
    {
        Serial_Read_Data.type = cJSON_GetObjectItem(serial_data, "type")->valuestring;
        if(strcmp(Serial_Read_Data.type, "version") == 0)
        {
            Usb_Write_Data("{\"type\":\"version\",\"version\":%s}\r\n", "1.0.0");
        }

    }

    cJSON_Delete(serial_data);
}

void Get_Version(void)
{
    Usb_Write_Data("{\"type\":\"version\",\"version\":%s}\r\n", "1.0.0");
}