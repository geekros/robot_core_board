/**
 ******************************************************************************
 * @file    can.c
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#include "can.h"

Can_Struct Can_Data;

/*******************************************************************************
 * @funtion      : Can_Init
 * @description  : 模块初始化，依次初始化Can1_Init、Can2_Init
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Can_Init(void)
{
    Can1_Init();
    Can2_Init();
}

/*******************************************************************************
 * @funtion      : Can1_Init
 * @description  : CAN1初始化，开发板共10组CAN1接口
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Can1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    CAN_InitTypeDef CAN_InitStructure;
    CAN_FilterInitTypeDef CAN_FilterInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

    GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_CAN1);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_CAN1);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    CAN_DeInit(CAN1);

    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = DISABLE;
    CAN_InitStructure.CAN_AWUM = DISABLE;
    CAN_InitStructure.CAN_NART = DISABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;

    CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_7tq;
    CAN_InitStructure.CAN_Prescaler = 3;
    CAN_Init(CAN1, &CAN_InitStructure);

    CAN_FilterInitStructure.CAN_FilterNumber = 0;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);

    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
    CAN_ITConfig(CAN1, CAN_IT_TME, ENABLE);
}

/*******************************************************************************
 * @funtion      : Can2_Init
 * @description  : CAN2初始化，开发板共6组CAN2接口
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Can2_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    CAN_InitTypeDef CAN_InitStructure;
    CAN_FilterInitTypeDef CAN_FilterInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_CAN2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_CAN2);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    CAN_DeInit(CAN2);

    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = DISABLE;
    CAN_InitStructure.CAN_AWUM = DISABLE;
    CAN_InitStructure.CAN_NART = DISABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;

    CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_7tq;
    CAN_InitStructure.CAN_Prescaler = 3;
    CAN_Init(CAN2, &CAN_InitStructure);

    CAN_FilterInitStructure.CAN_FilterNumber = 0;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);

    CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);
    CAN_ITConfig(CAN2, CAN_IT_TME, ENABLE);
}

/*******************************************************************************
 * @funtion      : CAN1_RX0_IRQHandler
 * @description  : CAN1中断回调函数
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void CAN1_RX0_IRQHandler(void)
{
    if (CAN_GetITStatus(CAN1, CAN_IT_FMP0) != RESET)
    {
        CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
        for (int i = 0; i < CAN_MOTOR_LEN; i++)
        {
            // 将CAN_Receive的数据存储到变量that_data
            CanRxMsg that_data;
            CAN_Receive(CAN1, CAN_FIFO0, &that_data);
            // 判断CAN_Receive数据中的电机ID值
            if (that_data.StdId == (0x140 + (i + 1)))
            {
                // 将数据传入统一回调函数进行处理
                CAN_Receive_Callback(that_data, 0, i);
            }
        }
    }
}

/*******************************************************************************
 * @funtion      : CAN2_RX0_IRQHandler
 * @description  : CAN2中断回调函数
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void CAN2_RX0_IRQHandler(void)
{
    if (CAN_GetITStatus(CAN2, CAN_IT_FMP0) != RESET)
    {
        CAN_ClearITPendingBit(CAN2, CAN_IT_FMP0);
        for (int i = 0; i < CAN_MOTOR_LEN; i++)
        {
            // 将CAN_Receive的数据存储到变量that_data
            CanRxMsg that_data;
            CAN_Receive(CAN2, CAN_FIFO0, &that_data);
            // 判断CAN_Receive数据中的电机ID值
            if (that_data.StdId == (0x140 + (i + 1)))
            {
                // 将数据传入统一回调函数进行处理
                CAN_Receive_Callback(that_data, 1, i);
            }
        }
    }
}

/*******************************************************************************
 * @funtion      : CAN_Receive_Callback
 * @description  : CAN中断数据统一回调函数
 * @param         {CanRxMsg can_read_data} 中断数据
 * @param         {int channel} 通道 可选值1、2
 * @param         {int motor_id} 电机ID
 * @return        {*}
 *******************************************************************************/
void CAN_Receive_Callback(CanRxMsg can_read_data, int channel, int motor_id)
{
    
}

/*******************************************************************************
 * @funtion      : Can_Task
 * @description  : 任务回调函数
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Can_Task(void)
{
    
}

/*******************************************************************************
 * @funtion      : Can_Motor_Stop
 * @description  : 停止电机
 * @param         {int channel} 通道 可选值1、2
 * @param         {int motor_id} 电机ID
 * @return        {*}
 *******************************************************************************/
void Can_Motor_Stop(int channel, int motor_id)
{
    
}

/*******************************************************************************
 * @funtion      : Can_Motor_Run
 * @description  : 控制电机运动
 * @param         {int channel} 通道 可选值1、2
 * @param         {int motor_id} 电机ID
 * @return        {*}
 *******************************************************************************/
void Can_Motor_Run(int channel, int motor_id)
{
    
}

/*******************************************************************************
 * @funtion      : Can_Usb_Callback
 * @description  : 串口任务回调函数
 * @param         {char *type} 通讯协议类型
 * @param         {int channel} 通道 可选值1、2
 * @param         {int motor_id} 电机ID
 * @return        {*}
 *******************************************************************************/
void Can_Usb_Callback(char *type, int channel, int motor_id)
{
    
}
