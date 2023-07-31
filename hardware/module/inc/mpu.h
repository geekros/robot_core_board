/**
 ******************************************************************************
 * @file    mpu.h
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#ifndef MODULAR_MPU
#define MODULAR_MPU

#include <stm32f4xx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utils.h"
#include "usb.h"

#define MPU_ENABLE GPIO_ResetBits(GPIOF, GPIO_Pin_6)
#define MPU_DISABLE GPIO_SetBits(GPIOF, GPIO_Pin_6)
#define MPU_WHOAMI_9250 0x71

#define AK8963_I2C_ADDR 0x0C
#define AK8963REG_CNTL2 0x0B

#define AUX_READ_TIMEOUT (200)

#define MPUREG_WHOAMI 0x75
#define MPUREG_PWR_MGMT_1 0x6B
#define MPUREG_PWR_MGMT_2 0x6C
#define MPUREG_CONFIG 0x1A
#define MPUREG_GYRO_CONFIG 0x1B
#define MPUREG_ACCEL_CONFIG 0x1C
#define MPUREG_ACCEL_CONFIG2 0x1D
#define MPUREG_USER_CTRL 0x6A
#define MPUREG_I2C_MST_CTRL 0x24
#define MPUREG_I2C_MST_DELAY_CTRL 0x67
#define MPUREG_I2C_SLV4_ADDR 0x31
#define MPUREG_I2C_SLV4_REG 0x32
#define MPUREG_I2C_SLV4_DO 0x33
#define MPUREG_I2C_SLV4_CTRL 0x34
#define MPUREG_I2C_SLVx_EN ((uint8_t)0x80)
#define MPUREG_I2C_MST_STATUS 0x36
#define MPUREG_I2C_SLV4_DONE ((uint8_t)0x40)
#define MPUREG_I2C_SLV4_DI 0x35
#define MPUREG_I2C_SLV0_ADDR 0x25
#define MPUREG_I2C_SLV0_REG 0x26
#define MPUREG_I2C_SLV0_CTRL 0x27
#define MPUREG_ACCEL_XOUT_H 0x3B

#define AK8963REG_CNTL1 0x0A
#define AK8963REG_ST1 0x02
#define AK8963REG_ASAX 0x10
#define AK8963REG_ASAY 0x11
#define AK8963REG_ASAZ 0x12

#define BMP280_OVERSAMP_8X (0x04)
#define BMP280_OVERSAMP_16X (0x05)
#define BMP280_PRESSURE_OSR (BMP280_OVERSAMP_8X)
#define BMP280_TEMPERATURE_OSR (BMP280_OVERSAMP_16X)
#define BMP280_MODE (BMP280_PRESSURE_OSR << 2 | BMP280_TEMPERATURE_OSR << 5 | BMP280_NORMAL_MODE)
#define BMP280_I2C_ADDR (0x76)
#define BMP280_TEMPERATURE_CALIB_DIG_T1_LSB_REG (0x88)
#define BMP280_CTRL_MEAS_REG (0xF4)
#define BMP280_CONFIG_REG (0xF5)
#define BMP280_PRESSURE_MSB_REG (0xF7)
#define BMP280_NORMAL_MODE (0x03)

#define FILTER_NUM 5
#define FILTER_A 0.1f
#define CONST_PF 0.1902630958
#define FIX_TEMP 25
#define Kp 2.0f
#define Ki 0.01f

typedef struct
{
	u16 dig_T1;
	s16 dig_T2;
	s16 dig_T3;
	u16 dig_P1;
	s16 dig_P2;
	s16 dig_P3;
	s16 dig_P4;
	s16 dig_P5;
	s16 dig_P6;
	s16 dig_P7;
	s16 dig_P8;
	s16 dig_P9;
	s32 t_fine;
} Bmp280_Data_Struct;

typedef struct
{
	uint8_t mag_x;
	uint8_t mag_y;
	uint8_t mag_z;
	int16_t accel_x;
	int16_t accel_y;
	int16_t accel_z;
	int16_t gyro_x;
	int16_t gyro_y;
	int16_t gyro_z;
} Mpu_Offset_Struct;

typedef struct
{
	int16_t mag_x;
	int16_t mag_y;
	int16_t mag_z;
	int16_t accel_x;
	int16_t accel_y;
	int16_t accel_z;
	float gyro_x;
	float gyro_y;
	float gyro_z;
	float temperature;
} Mpu_Calc_Struct;

typedef struct
{
	int16_t accel_x;
	int16_t accel_y;
	int16_t accel_z;
	int16_t mag_x;
	int16_t mag_y;
	int16_t mag_z;
	int16_t gyro_x;
	int16_t gyro_y;
	int16_t gyro_z;
	float temperature;
} Mpu_Struct;

typedef struct
{
	float pressure;
	float altitude;
	float temperature;
	float rol;
	float pit;
	float yaw;
} Mpu_Read_Struct;

extern Mpu_Read_Struct Mpu_Read_Data;

void Mpu_Init(void);

void Mpu9250_Init(void);

void Ak8963_Init(void);

void Bmp280_Init(void);

uint8_t Mpu_Read_Byte(uint8_t const reg);

uint8_t Mpu_Read_Bytes(uint8_t const regAddr, uint8_t *pData, uint8_t len);

uint8_t Mpu_Write_Byte(uint8_t const reg, uint8_t const data);

void Mpu_Aux_Config(uint8_t slaveNum, uint8_t slaveAddr, uint8_t readAddr, uint8_t readLens);

void Mpu_Aux_Write_Data(uint8_t slaveAddr, uint8_t writeAddr, uint8_t writeData);

uint8_t Mpu_Aux_Read_Data(uint8_t slaveAddr, uint8_t readAddr);

void Mpu_Offset_Data(void);

void Quaternion_Init(void);

u32 Compensate_Temperature(s32 adcT);

u32 Compensate_Pressure(s32 adcP);

void PressureFilter(float *in, float *out);

float Pressure_To_Altitude(float *pressure);

void Mpu_Attitude_Calc(void);

void Mpu_Task(void);

void Mpu_Usb_Callback(char *type);

Mpu_Read_Struct *Return_Mpu_Address(void);

#endif
