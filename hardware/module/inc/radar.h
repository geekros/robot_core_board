/**
 ******************************************************************************
 * @file    radar.h
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#ifndef MODULAR_RADAR
#define MODULAR_RADAR

#include "stm32f4xx.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define RADAR_DATA_LEN 256

#define FRAME_TYPE 0x61 //帧类型
#define FRAME_MEASURE_INFO 0xAD
#define FRAME_DEVICE_HEALTH_INFO 0xAE

#define TOOTH_NUM 16 //定义雷达齿轮个数

enum SCANSTATE
{
	RIDAR_GRAB_SCAN_FIRST = 0,
	RIDAR_GRAB_SCAN_ELSE_DATA
};

enum SCANRESULT
{
	RIDAR_GRAB_ING = 0, //恢复正在扫描状态
	RIDAR_GRAB_SUCESS,	//扫描到完整一圈
	RIDAR_GRAB_ERRO,
	RIDAR_GRAB_ELSE
};

typedef struct
{
	uint8_t header;
	uint16_t len;
	uint8_t addr;
	uint8_t cmd_type;
	uint8_t cmd_id;
	uint16_t param_len;
	uint8_t *data;
} Radar_Protocol;

typedef struct
{
	u8 buffer[RADAR_DATA_LEN + 20];
	u16 len;
	u8 state;
} Radar_Read_Struct;

typedef struct
{
	float angle;
	float distance;
} Radar_Point;

typedef struct
{
	float rotate_speed;
	float zero_offset;
	float frame_start_angle;
	uint8_t point_num;		//一帧的点数
	Radar_Point point[100]; //一帧 点信息
} Radar_Frame;

typedef struct
{
	uint8_t state;
	uint8_t result;
	float last_scan_angle;
	uint8_t tooth_count;
	uint16_t one_cricle_point_num;		//一圈点数
	Radar_Frame frame_meas_info;		//一帧测量信息
	Radar_Point one_cricle_point[1000]; //一圈测量点信息，从零点开始，由16帧点信息组成
} Radar_Struct;

extern Radar_Read_Struct Radar_Read_Data;

extern Radar_Struct Radar_Data;

void Radar_Init(int baud_rate);

void Ridar_Scan_Init(void);

uint8_t Radar_Frame_Right(Radar_Protocol preq);

uint8_t Radar_First_Grating_Scan(float angle);

void Radar_One_Cricle_Point_Insert(Radar_Frame one_meas_info);

void Radar_First_Grating_Scan_Write(Radar_Frame one_meas_info);

void Radar_Scan_One_Circle(Radar_Frame one_meas_info);

void Radar_Analysis_Measure_Info(Radar_Protocol *preq);

float Radar_Analysis_Device_Health_Info(Radar_Protocol *preq);

void Radar_Frame_Analysis(Radar_Protocol preq);

uint8_t Ridar_Process_Cmd(void);

void Ridar_Process_Data(void);

#endif
