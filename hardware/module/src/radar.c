/**
 ******************************************************************************
 * @file    radar.c
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#include "radar.h"

Radar_Read_Struct Radar_Read_Data;

Radar_Struct Radar_Data;

/*******************************************************************************
 * @funtion      : Radar_Init
 * @description  : 模块初始化，UART7作为激光雷达模块模块专用接口
 * @param         {int baud_rate} 波特率
 * @return        {*}
 *******************************************************************************/
void Radar_Init(int baud_rate)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7, GPIO_AF_UART7);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_UART7);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	USART_DeInit(UART7);
	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate = baud_rate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(UART7, &USART_InitStructure);

	USART_ITConfig(UART7, USART_IT_RXNE, ENABLE);
	USART_ITConfig(UART7, USART_IT_IDLE, ENABLE);
	USART_Cmd(UART7, ENABLE);

	USART_ClearITPendingBit(UART7, USART_IT_RXNE);
	USART_ClearITPendingBit(UART7, USART_IT_IDLE);

	NVIC_InitStructure.NVIC_IRQChannel = UART7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
 * @funtion      : UART7_IRQHandler
 * @description  : 激光雷达模块中断函数，接收UART7数据
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void UART7_IRQHandler(void)
{
	volatile u8 data;
	if (USART_GetFlagStatus(UART7, USART_FLAG_RXNE) != RESET)
	{
		data = USART_ReceiveData(UART7);
		if (Radar_Read_Data.state == 0)
		{
			Radar_Read_Data.buffer[Radar_Read_Data.len++] = data;
			if (Radar_Read_Data.len >= sizeof(Radar_Read_Data.buffer))
			{
				Radar_Read_Data.state = 1;
			}
		}
		USART_ClearFlag(UART7, USART_FLAG_RXNE);
	}
	if (USART_GetFlagStatus(UART7, USART_FLAG_IDLE) != RESET)
	{
		if ((Radar_Read_Data.state == 0) && (Radar_Read_Data.len > 0))
		{
			if (Radar_Read_Data.len > 3)
			{
				Radar_Read_Data.state = 1;
			}
			else
			{
				Radar_Read_Data.len = 0;
			}
		}
		USART_ClearFlag(UART7, USART_FLAG_IDLE);
	}

	data = UART7->SR;
	data = UART7->DR;
}

/*******************************************************************************
 * @funtion      : Radar_Calc_Check_Sum
 * @description  : 计算校验和
 * @param         {uint8_t *start_byte} 待计算数据存放地址入口
 * @param         {uint16_t num_bytes} 数据长度
 * @return        {*}
 *******************************************************************************/
uint16_t Radar_Calc_Check_Sum(uint8_t *start_byte, uint16_t num_bytes)
{
	uint16_t CheckSum = 0;
	while (num_bytes > 0)
	{
		CheckSum += *start_byte++;
		num_bytes--;
	}
	return CheckSum;
}

/*******************************************************************************
 * @funtion      : LittleCopy_u16、Little2BigEndian_u16、Strto_u16
 * @description  : 一些调用函数
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void LittleCopy_u16(uint8_t *dest, uint8_t *src, uint16_t len)
{
	while (len)
	{
		*dest = *(src + 1);
		*(dest + 1) = *src;
		dest += 2;
		src += 2;
		len--;
	}
}

uint16_t Little2BigEndian_u16(uint16_t dat)
{
	return ((dat >> 8) | (dat << 8));
}

uint16_t Strto_u16(uint8_t *str)
{
	return ((*str << 8) | *(str + 1));
}

/*******************************************************************************
 * @funtion      : Radar_Frame_Right
 * @description  : 判断帧数据是否完整帧函数
 * @param         {Radar_Protocol preq}
 * @return        {*}
 *******************************************************************************/
uint8_t Radar_Frame_Right(Radar_Protocol preq)
{
	uint16_t temp = 0, calc_crc, len;
	len = Little2BigEndian_u16(preq.len);
	if (preq.header != 0xAA)
	{
		return 0;
	}
	else if (len > Radar_Read_Data.len)
	{
		return 0;
	}
	else if (preq.cmd_type != FRAME_TYPE)
	{
		return 0;
	}
	else
	{
		calc_crc = Radar_Calc_Check_Sum(Radar_Read_Data.buffer, len);
		LittleCopy_u16((uint8_t *)&temp, &Radar_Read_Data.buffer[len], 1);
		if (calc_crc != temp)
		{
			return 0;
		}
	}
	return 1;
}

/*******************************************************************************
 * @funtion      : Radar_Scan_One_Circle
 * @description  : 判断是不是扫描到第一个齿轮函数
 * @param         {float angle}
 * @return        {*}
 *******************************************************************************/
uint8_t Radar_First_Grating_Scan(float angle)
{
	return angle < 0.0001f ? 1 : 0;
}

/*******************************************************************************
 * @funtion      : Radar_One_Cricle_Point_Insert
 * @description  : 一次测量点信息插入到一圈点信息的数据结构中函数
 * @param         {Radar_Frame one_meas_info}
 * @return        {*}
 *******************************************************************************/
void Radar_One_Cricle_Point_Insert(Radar_Frame one_meas_info)
{
	uint8_t i = 0;
	for (i = 0; i < one_meas_info.point_num; i++)
	{
		Radar_Data.one_cricle_point[Radar_Data.one_cricle_point_num].angle = one_meas_info.point[i].angle;
		Radar_Data.one_cricle_point[Radar_Data.one_cricle_point_num].distance = one_meas_info.point[i].distance;
		Radar_Data.one_cricle_point_num++;
	}
}

/*******************************************************************************
 * @funtion      : Radar_First_Grating_Scan_Write
 * @description  : 存储第一个齿轮间扫描的点数函数
 * @param         {Radar_Frame one_meas_info}
 * @return        {*}
 *******************************************************************************/
void Radar_First_Grating_Scan_Write(Radar_Frame one_meas_info)
{
	Radar_Data.state = RIDAR_GRAB_SCAN_ELSE_DATA;
	Radar_Data.tooth_count = 1;
	Radar_Data.last_scan_angle = one_meas_info.frame_start_angle;
	Radar_One_Cricle_Point_Insert(one_meas_info);
}

/*******************************************************************************
 * @funtion      : Radar_Scan_One_Circle
 * @description  : 扫描一圈的过程函数
 * @param         {Radar_Frame one_meas_info}
 * @return        {*}
 *******************************************************************************/
void Radar_Scan_One_Circle(Radar_Frame one_meas_info)
{
	switch (Radar_Data.state)
	{
	case RIDAR_GRAB_SCAN_FIRST:
		if (Radar_First_Grating_Scan(one_meas_info.frame_start_angle))
		{
			Ridar_Scan_Init();
			Radar_First_Grating_Scan_Write(one_meas_info);
		}
		break;
	case RIDAR_GRAB_SCAN_ELSE_DATA:
		if (one_meas_info.frame_start_angle < Radar_Data.last_scan_angle)
		{
			if (Radar_First_Grating_Scan(one_meas_info.frame_start_angle))
			{
				//这次角度小于上一次角度，且角度为零：表示这一圈数据不完整，刚好从零点重新下一圈(这圈数据丢掉)
				Ridar_Scan_Init();
				Radar_First_Grating_Scan_Write(one_meas_info);
			}
			else
			{
				//这次角度小于上一次角度，且角度不为零：表示这一圈和下圈数据都不完整，重新矫正到零点开始扫描，这一圈和下圈数据都丢掉
				Radar_Data.state = RIDAR_GRAB_SCAN_FIRST;
			}
			return;
		}
		Radar_One_Cricle_Point_Insert(one_meas_info);
		Radar_Data.tooth_count++;
		Radar_Data.last_scan_angle = one_meas_info.frame_start_angle;
		if (Radar_Data.tooth_count == TOOTH_NUM)
		{
			Radar_Data.tooth_count = 0;
			Radar_Data.state = RIDAR_GRAB_SCAN_FIRST;
			Radar_Data.result = RIDAR_GRAB_SUCESS;
			return;
		}
		break;
	default:
		break;
	}
}

/*******************************************************************************
 * @funtion      : Radar_Analysis_Measure_Info
 * @description  : 测量信息帧解析函数
 * @param         {Radar_Protocol *preq}
 * @return        {*}
 *******************************************************************************/
void Radar_Analysis_Measure_Info(Radar_Protocol *preq)
{
	uint8_t data_head_offset = 0;
	uint8_t i = 0;
	float per_angle_offset = 0;

	preq->param_len = Little2BigEndian_u16(preq->param_len);

	Radar_Data.frame_meas_info.rotate_speed = (*(preq->data)) * 0.05f;
	data_head_offset += 1;
	Radar_Data.frame_meas_info.zero_offset = Strto_u16(preq->data + data_head_offset) * 0.01f;
	data_head_offset += 2;
	Radar_Data.frame_meas_info.frame_start_angle = Strto_u16(preq->data + data_head_offset) * 0.01f;
	data_head_offset += 2;
	Radar_Data.frame_meas_info.point_num = (preq->param_len - data_head_offset) / 3;

	per_angle_offset = 22.5f / Radar_Data.frame_meas_info.point_num;
	for (i = 0; i < Radar_Data.frame_meas_info.point_num; i++)
	{
		Radar_Data.frame_meas_info.point[i].distance = Strto_u16(preq->data + data_head_offset + 3 * i + 1) * 0.25f;
		Radar_Data.frame_meas_info.point[i].angle = Radar_Data.frame_meas_info.frame_start_angle + i * per_angle_offset;
	}

	Radar_Scan_One_Circle(Radar_Data.frame_meas_info);
}

/*******************************************************************************
 * @funtion      : Radar_Analysis_Device_Health_Info
 * @description  : 健康信息帧解析帧函数
 * @param         {Radar_Protocol *preq}
 * @return        {*}
 *******************************************************************************/
float Radar_Analysis_Device_Health_Info(Radar_Protocol *preq)
{
	float speed = 0;
	speed = *(preq->data) * 0.05f;
	return speed;
}

/*******************************************************************************
 * @funtion      : Radar_Frame_Analysis
 * @description  : 帧数据解析函数
 * @param         {Radar_Protocol preq}
 * @return        {*}
 *******************************************************************************/
void Radar_Frame_Analysis(Radar_Protocol preq)
{
	switch (preq.cmd_id)
	{
	case FRAME_MEASURE_INFO: //雷达测量信息帧
		Radar_Analysis_Measure_Info(&preq);
		break;
	case FRAME_DEVICE_HEALTH_INFO: //雷达设备健康信息帧
		Radar_Analysis_Device_Health_Info(&preq);
		break;
	default:
		return;
	}
}

/*******************************************************************************
 * @funtion      : Ridar_Scan_Init
 * @description  : 初始化雷达扫描信息函数
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Ridar_Scan_Init(void)
{
	Radar_Data.state = RIDAR_GRAB_SCAN_FIRST;
	Radar_Data.tooth_count = 0;
	Radar_Data.last_scan_angle = 0.0;
	Radar_Data.result = RIDAR_GRAB_ING;
	Radar_Data.one_cricle_point_num = 0;
}

/*******************************************************************************
 * @funtion      : Ridar_Process_Cmd
 * @description  : 帧数据处理函数
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
uint8_t Ridar_Process_Cmd(void)
{
	Radar_Protocol preq;
	memcpy((uint8_t *)&preq, (uint8_t *)Radar_Read_Data.buffer, 8);
	preq.data = &Radar_Read_Data.buffer[8];
	if (Radar_Frame_Right(preq) == 0)
	{
		return 0;
	}
	Radar_Frame_Analysis(preq);
	return 1;
}

/*******************************************************************************
 * @funtion      : Ridar_Process_Data
 * @description  : 接收数据处理函数
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Ridar_Process_Data(void)
{
	if (Radar_Read_Data.state == 0)
	{
		return;
	}
	if (Radar_Read_Data.state > 0)
	{
		// 帧数据处理
		Ridar_Process_Cmd();
	}
	Radar_Read_Data.len = 0;
	Radar_Read_Data.state = 0;
}
