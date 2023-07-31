/**
 ******************************************************************************
 * @file    key.c
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#include "key.h"

void Key_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void Key_Serial_Callback(cJSON *serial_data)
{
    cJSON *type = cJSON_GetObjectItem(serial_data, "type");
    if (type && cJSON_IsString(type))
    {
        if(strcmp(type->valuestring, "key-status") == 0)
        {
            Usb_Write_Data("{\"type\":\"key-status\",\"status\":%d}\r\n", Key_Status);
        }
    }
}
