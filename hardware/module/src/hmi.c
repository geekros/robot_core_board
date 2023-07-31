/**
 ******************************************************************************
 * @file    hmi.c
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#include "hmi.h"

Hmi_Struct Hmi_Data;

/*******************************************************************************
 * @funtion      : Hmi_Init
 * @description  : 模块初始化，UART8作为HMI串口触摸屏模块专用接口
 * @param         {int baud_rate} 波特率
 * @return        {*}
 *******************************************************************************/
void Hmi_Init(int baud_rate)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8, ENABLE);

    GPIO_PinAFConfig(GPIOE, GPIO_PinSource0, GPIO_AF_UART8);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource1, GPIO_AF_UART8);

    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

    GPIO_Init(GPIOE, &GPIO_InitStructure);

    USART_DeInit(UART8);
    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.USART_BaudRate = baud_rate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(UART8, &USART_InitStructure);
    USART_ITConfig(UART8, USART_IT_RXNE, ENABLE);

    USART_Cmd(UART8, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = UART8_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
 * @funtion      : UART8_IRQHandler
 * @description  : 中断回调函数，接收UART8数据
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void UART8_IRQHandler(void)
{
    volatile static uint8_t data;
    if (USART_GetITStatus(UART8, USART_IT_RXNE) != RESET)
    {
        data = USART_ReceiveData(UART8);
        if (data == '{')
        {
            // 检测到JSON数据起始符后开始记录数据
            Hmi_Data.buffer[0] = data;
            Hmi_Data.len = 1;
        }
        else if (data == '}')
        {
            // 检测到JSON数据结束符后停止数据记录
            Hmi_Data.buffer[Hmi_Data.len] = data;
            // 将完整的JSON数据传入JSON解析函数
            Hmi_Parse_Json((char *)Hmi_Data.buffer);
            Hmi_Data.len = 0;
        }
        else
        {
            // 判断是否检测到JSON数据起始符并记录数据
            if (Hmi_Data.len > 0)
            {
                Hmi_Data.buffer[Hmi_Data.len] = data;
                Hmi_Data.len++;
            }
        }
    }
}

/*******************************************************************************
 * @funtion      : Hmi_Parse_Json
 * @description  : 解析JSON数据
 * @param         {char *json} JSON数据
 * @return        {*}
 *******************************************************************************/
void Hmi_Parse_Json(char *json)
{
    // 回调USB串口任务的JSON通讯协议解析与处理函数
    Serial_Json_Handle(json);
}

/*******************************************************************************
 * @funtion      : Hmi_Usb_Callback
 * @description  : 串口任务回调函数
 * @param         {char *type} 通讯协议类型
 * @param         {int baud_rate} 波特率
 * @return        {*}
 *******************************************************************************/
void Hmi_Usb_Callback(char *type, int baud_rate)
{
    if (memcmp(type, "hmi-rate", 8) == 0)
    {
        Hmi_Init(baud_rate);
    }
}
