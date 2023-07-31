/**
  ******************************************************************************
  * @file    servo.h
  * @author  GEEKROS,  site:www.geekros.com
  ******************************************************************************
*/

#ifndef MODULE_SERVO
#define MODULE_SERVO

#include "stm32f4xx.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SERVO_DATA_LEN 128
#define SERVO_LEN 12

#define SERVO_INST_PING 0x01
#define SERVO_INST_READ 0x02
#define SERVO_INST_WRITE 0x03
#define SERVO_INST_REG_WRITE 0x04
#define SERVO_INST_REG_ACTION 0x05
#define SERVO_INST_SYNC_WRITE 0x83

//-------EPROM(ֻ)--------
#define SERVO_MODEL_L 3
#define SERVO_MODEL_H 4

//-------EPROM(д)--------
#define SERVO_ID 5
#define SERVO_BAUD_RATE 6
#define SERVO_MIN_ANGLE_LIMIT_L 9
#define SERVO_MIN_ANGLE_LIMIT_H 10
#define SERVO_MAX_ANGLE_LIMIT_L 11
#define SERVO_MAX_ANGLE_LIMIT_H 12
#define SERVO_CW_DEAD 26
#define SERVO_CCW_DEAD 27
#define SERVO_OFS_L 31
#define SERVO_OFS_H 32
#define SERVO_MODE 33

//-------SRAM(д)--------
#define SERVO_TORQUE_ENABLE 40
#define SERVO_ACC 41
#define SERVO_GOAL_POSITION_L 42
#define SERVO_GOAL_POSITION_H 43
#define SERVO_GOAL_TIME_L 44
#define SERVO_GOAL_TIME_H 45
#define SERVO_GOAL_SPEED_L 46
#define SERVO_GOAL_SPEED_H 47
#define SERVO_SMSBCL_LOCK 55
#define SERVO_SCSCL_LOCK 48

//-------SRAM(ֻ)--------
#define SERVO_PRESENT_POSITION_L 56
#define SERVO_PRESENT_POSITION_H 57
#define SERVO_PRESENT_SPEED_L 58
#define SERVO_PRESENT_SPEED_H 59
#define SERVO_PRESENT_LOAD_L 60
#define SERVO_PRESENT_LOAD_H 61
#define SERVO_PRESENT_VOLTAGE 62
#define SERVO_PRESENT_TEMPERATURE 63
#define SERVO_MOVING 66
#define SERVO_PRESENT_CURRENT_L 69
#define SERVO_PRESENT_CURRENT_H 70

typedef enum
{
	SERVO_NONE = 0,
	SERVO_STS = 1, //STS3032
	SERVO_SCS = 2 //SCS009
}Servo_Type_Struct;

typedef struct{
	uint8_t Servo_Write_Buffer[SERVO_DATA_LEN];
	uint8_t Servo_Write_Len;
	uint8_t Servo_Read_Buffer[SERVO_DATA_LEN];
	int Servo_Read_Len;
	int Servo_Read_Step;
}Servo_Read_Write_Struct;

typedef struct{
	Servo_Type_Struct type;
	uint8_t end;
	int position;
	int voltage;
	int speed;
	int load;
	int temperature;
	int current;
	int motion_state;
}Servo_Struct;

extern Servo_Read_Write_Struct Servo_Read_Write;

extern Servo_Struct Servo_Data[SERVO_LEN];

void Servo_Init(int baud_rate);

void Servo_Send(uint8_t *buf , uint8_t len);

void Servo_Read_Position(int id);

void Servo_Read_Speed(int id);

void Servo_Read_Load(int id);

void Servo_Read_Motion_State(int id);

void Servo_Read_Voltage(int id);

void Servo_Read_Temperature(int id);

void Servo_Read_Current(int id);

void Servo_Type(int id, int type);

void Servo_Read_Data(int id);

void Servo_Write_Position(uint8_t ID[], uint8_t IDN, uint16_t Position[], uint16_t Time[], uint16_t Speed[]);

void Servo_Id_Write_Position(uint8_t ID, uint16_t Position, uint16_t Time, uint16_t Speed);

void Servo_Usb_Callback(char *type, int id, int baud_rate, int servo_type);

#endif
