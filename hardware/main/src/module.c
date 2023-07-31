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
        Serial_Read_Data.type = cJSON_GetObjectItem(serial_data, "type")->valuestring;
        if (Serial_Read_Data.type == "version")
        {
            Get_Version();
        }
        if (Serial_Read_Data.type == "board-voltage" || Serial_Read_Data.type == "pwm-voltage" || Serial_Read_Data.type == "low-voltage")
        {
            Adc_Serial_Callback(serial_data);
        }
        if (Serial_Read_Data.type == "cpu-temperature")
        {
            Cpu_Serial_Callback(serial_data);
        }
        if (Serial_Read_Data.type == "hmi-init")
        {
            Hmi_Serial_Callback(serial_data);
        }
        if (Serial_Read_Data.type == "io-mode" || Serial_Read_Data.type == "io-status")
        {
            Io_Serial_Callback(serial_data);
        }
        if (Serial_Read_Data.type == "key-status")
        {
            Key_Serial_Callback(serial_data);
        }
        if (Serial_Read_Data.type == "led-status")
        {
            Led_Serial_Callback(serial_data);
        }
        if (Serial_Read_Data.type == "mpu" || Serial_Read_Data.type == "mpu-attitude")
        {
            Mpu_Serial_Callback(serial_data);
        }
        if (Serial_Read_Data.type == "power-status")
        {
            Power_Serial_Callback(serial_data);
        }
        if (Serial_Read_Data.type == "pwm")
        {
            Pwm_Serial_Callback(serial_data);
        }
        if (Serial_Read_Data.type == "rocker")
        {
            Rocker_Serial_Callback(serial_data);
        }
        if (Serial_Read_Data.type == "wifi-init")
        {
            Wifi_Serial_Callback(serial_data);
        }
    }

    cJSON_Delete(serial_data);
}

void Get_Version(void)
{
    Usb_Write_Data("{\"type\":\"version\",\"version\":%s}\r\n", "1.0.0");
}