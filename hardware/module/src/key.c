/**
 ******************************************************************************
 * @file    key.c
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#include "key.h"

/*******************************************************************************
 * @funtion      : Key_Init
 * @description  : 模块初始化
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Key_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*******************************************************************************
 * @funtion      : Key_Usb_Callback
 * @description  : 串口任务回调函数
 * @param         {char *type} 通讯协议类型
 * @return        {*}
 *******************************************************************************/
void Key_Usb_Callback(char *type)
{
    if (memcmp(type, "key-state", 9) == 0)
    {
        Usb_Write_Data("{\"type\":\"key-state\",\"state\":%d}\r\n", Key_State);
    }
}
