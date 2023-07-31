/**
 ******************************************************************************
 * @file    rocker.c
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#include "rocker.h"

Rocker_Struct Rocker_Data;

/*******************************************************************************
 * @funtion      : Return_Rocker_Address
 * @description  : 遥控器信号读取地址函数
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
Rocker_Struct *Return_Rocker_Address(void)
{
	return &Rocker_Data;
}

/*******************************************************************************
 * @funtion      : Rocker_Init
 * @description  : 模块初始化，SBUS、UART1作为遥控器专用接口
 * @param         {int baud_rate} 波特率
 * @return        {*}
 *******************************************************************************/
void Rocker_Init(int baud_rate)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_DMA2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	USART_DeInit(USART1);
	USART_InitStructure.USART_BaudRate = baud_rate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_Even;
	USART_InitStructure.USART_Mode = USART_Mode_Rx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &USART_InitStructure);

	USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
	USART_Cmd(USART1, ENABLE);

	USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	DMA_Cmd(DMA2_Stream5, DISABLE);
	
	while (DMA2_Stream5->CR & DMA_SxCR_EN);

	DMA_DeInit(DMA2_Stream5);
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (USART1->DR);
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Rocker_Data.buffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = 18;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_Mode_Normal;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream5, &DMA_InitStructure);

	DMA_ITConfig(DMA2_Stream5, DMA_IT_TC, ENABLE);
	DMA_Cmd(DMA2_Stream5, ENABLE);
}

/*******************************************************************************
 * @funtion      : DMA2_Stream5_IRQHandler
 * @description  : DMA中断函数，处理遥控器信号数据
 * @param         {int baud_rate} 波特率
 * @return        {*}
 *******************************************************************************/
void DMA2_Stream5_IRQHandler(void)
{
	if (DMA_GetITStatus(DMA2_Stream5, DMA_IT_TCIF5))
	{
		DMA_ClearFlag(DMA2_Stream5, DMA_FLAG_TCIF5);
		DMA_ClearITPendingBit(DMA2_Stream5, DMA_IT_TCIF5);
        
        //右侧摇杆左右
        Rocker_Data.c0 = (Rocker_Data.buffer[0]| (Rocker_Data.buffer[1] << 8)) & 0x07ff;
        //右侧摇杆上下
        Rocker_Data.c1 = ((Rocker_Data.buffer[1] >> 3) | (Rocker_Data.buffer[2] << 5)) & 0x07ff;
        //左侧摇杆左右
        Rocker_Data.c2 = ((Rocker_Data.buffer[2] >> 6) | (Rocker_Data.buffer[3] << 2) | (Rocker_Data.buffer[4] << 10)) & 0x07ff;
        //左侧摇杆上下
        Rocker_Data.c3 = ((Rocker_Data.buffer[4] >> 1) | (Rocker_Data.buffer[5] << 7)) & 0x07ff;
        //左侧拨杆
        Rocker_Data.s1  = ((Rocker_Data.buffer[5] >> 4)& 0x000C) >> 2;
        //右侧拨杆
        Rocker_Data.s2  = ((Rocker_Data.buffer[5] >> 4)& 0x0003);
        
        Rocker_Data.c0 -= ((uint16_t)1024);
        Rocker_Data.c1 -= ((uint16_t)1024);
        Rocker_Data.c2 -= ((uint16_t)1024);
        Rocker_Data.c3 -= ((uint16_t)1024);
	}
}

/*******************************************************************************
 * @funtion      : Rocker_Usb_Callback
 * @description  : 串口任务回调函数
 * @param         {char *type} 通讯协议类型
 * @param         {int rate} 波特率
 * @return        {*}
 *******************************************************************************/
void Rocker_Usb_Callback(char *type, int s1, int s2, float c0, float c1, float c2, float c3)
{
	if (memcmp(type, "rocker", 6) == 0)
	{
		// 虚拟遥控器数据映射，数值全部放大10倍
        Rocker_Data.s1 = s1;
        Rocker_Data.s2 = s2;
        Rocker_Data.c0 = c0;
        Rocker_Data.c1 = c1;
        Rocker_Data.c2 = c2;
        Rocker_Data.c3 = c3;
        
        // 发送反馈数据
        //Usb_Write_Data("{\"type\":\"rocker-data\",\"s1\":%d,\"s2\":%d,\"c0\":%0.2f,\"c1\":%0.2f,\"c2\":%0.2f,\"c3\":%0.2f}\r\n", Rocker_Data.s1, Rocker_Data.s2, Rocker_Data.c0, Rocker_Data.c1, Rocker_Data.c2, Rocker_Data.c3);
	}
}
