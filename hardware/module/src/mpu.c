/**
 ******************************************************************************
 * @file    mpu.c
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#include "mpu.h"

uint8_t MPU_BUFF[28];

Bmp280_Data_Struct Bmp280_Data;

Mpu_Offset_Struct Mpu_Offset;

Mpu_Calc_Struct Mpu_Calc;

Mpu_Struct Mpu_Data = {0};

Mpu_Read_Struct Mpu_Read_Data;

volatile float q0 = 1.0f;
volatile float q1 = 0.0f;
volatile float q2 = 0.0f;
volatile float q3 = 0.0f;

volatile float exInt, eyInt, ezInt;
static volatile float gx, gy, gz, ax, ay, az, mx, my, mz;
unsigned long last_update, now_update;

static int32_t pressure = 0;
static int32_t temperature = 0;

/*******************************************************************************
 * @funtion      : Return_Mpu_Address
 * @description  : MPU数据读取地址函数
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
Mpu_Read_Struct *Return_Mpu_Address(void)
{
	return &Mpu_Read_Data;
}

/*******************************************************************************
 * @funtion      : Mpu_Init
 * @description  : 模块初始化
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Mpu_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI5, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

	GPIO_PinAFConfig(GPIOF, GPIO_PinSource7, GPIO_AF_SPI5);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource8, GPIO_AF_SPI5);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource9, GPIO_AF_SPI5);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI5, &SPI_InitStructure);

	SPI_Cmd(SPI5, ENABLE);

	Mpu9250_Init();

	Ak8963_Init();

	Mpu_Offset_Data();

	Bmp280_Init();

	Quaternion_Init();
}

/*******************************************************************************
 * @funtion      : Mpu9250_Init
 * @description  : MPU9250初始化
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
uint8_t id;
void Mpu9250_Init(void)
{
	Mpu_Write_Byte(MPUREG_USER_CTRL, 0x00);
	delay_ms(100);
	id = Mpu_Read_Byte(MPUREG_WHOAMI);
	if (MPU_WHOAMI_9250 != id)
	{
		while (1)
		{
		}
	}
	Mpu_Write_Byte(MPUREG_PWR_MGMT_1, 0x80);
	delay_ms(1);
	Mpu_Write_Byte(MPUREG_PWR_MGMT_1, 0x04);
	delay_ms(1);
	Mpu_Write_Byte(MPUREG_PWR_MGMT_2, 0x00);
	delay_ms(1);
	Mpu_Write_Byte(MPUREG_CONFIG, 0x04);
	delay_ms(1);
	Mpu_Write_Byte(MPUREG_GYRO_CONFIG, 0x00);
	delay_ms(1);
	Mpu_Write_Byte(MPUREG_ACCEL_CONFIG2, 0x02);
	delay_ms(1);
	Mpu_Write_Byte(MPUREG_USER_CTRL, 0x30);
	delay_ms(1);
	Mpu_Write_Byte(MPUREG_GYRO_CONFIG, 3 << 3);
	delay_ms(1);
	Mpu_Write_Byte(MPUREG_ACCEL_CONFIG, 2 << 3);
	delay_ms(1);
}

/*******************************************************************************
 * @funtion      : Ak8963_Init
 * @description  : Ak8963初始化
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Ak8963_Init(void)
{
	Mpu_Write_Byte(MPUREG_USER_CTRL, 0x30);
	delay_ms(10);
	Mpu_Write_Byte(MPUREG_I2C_MST_CTRL, 0x5d);
	delay_ms(10);
	Mpu_Write_Byte(MPUREG_I2C_MST_DELAY_CTRL, 0x80);
	delay_ms(10);
	Mpu_Aux_Write_Data(AK8963_I2C_ADDR, AK8963REG_CNTL2, 0x01);
	delay_ms(50);
	Mpu_Aux_Write_Data(AK8963_I2C_ADDR, AK8963REG_CNTL1, 0x00);
	delay_ms(1);
	Mpu_Aux_Write_Data(AK8963_I2C_ADDR, AK8963REG_CNTL1, 0x1F);
	delay_ms(10);
	Mpu_Offset.mag_x = Mpu_Aux_Read_Data(AK8963_I2C_ADDR, AK8963REG_ASAX);
	delay_ms(1);
	Mpu_Offset.mag_y = Mpu_Aux_Read_Data(AK8963_I2C_ADDR, AK8963REG_ASAY);
	delay_ms(1);
	Mpu_Offset.mag_z = Mpu_Aux_Read_Data(AK8963_I2C_ADDR, AK8963REG_ASAZ);
	delay_ms(1);
	Mpu_Aux_Write_Data(AK8963_I2C_ADDR, AK8963REG_CNTL1, 0x00);
	delay_ms(10);
	Mpu_Aux_Write_Data(AK8963_I2C_ADDR, AK8963REG_CNTL1, 0x16);
	delay_ms(10);
	Mpu_Aux_Config(0, AK8963_I2C_ADDR, AK8963REG_ST1, 8);
}

/*******************************************************************************
 * @funtion      : Bmp280_Init
 * @description  : Bmp280初始化
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Bmp280_Init(void)
{

	int i = 0;
	for (i = 0; i < 24; i++)
	{
		((uint8_t *)&Bmp280_Data)[i] = Mpu_Aux_Read_Data(BMP280_I2C_ADDR, BMP280_TEMPERATURE_CALIB_DIG_T1_LSB_REG + i);
	}
	Mpu_Aux_Write_Data(BMP280_I2C_ADDR, BMP280_CTRL_MEAS_REG, BMP280_MODE);
	Mpu_Aux_Write_Data(BMP280_I2C_ADDR, BMP280_CONFIG_REG, 5 << 2);
	Mpu_Aux_Config(1, BMP280_I2C_ADDR, BMP280_PRESSURE_MSB_REG, 6);
}

/*******************************************************************************
 * @funtion      : Mpu_Read_Byte
 * @description  : Byte数据读取函数
 * @param         {uint8_t const reg}
 * @return        {*}
 *******************************************************************************/
uint8_t Mpu_Read_Byte(uint8_t const reg)
{
	uint8_t data = 0;
	MPU_ENABLE;
	while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET)
	{
	}
	SPI_I2S_SendData(SPI5, reg | 0x80);
	while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_RXNE) == RESET)
	{
	}
	SPI_I2S_ReceiveData(SPI5);
	while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET)
	{
	}
	SPI_I2S_SendData(SPI5, 0x00);
	while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_RXNE) == RESET)
	{
	}
	data = SPI_I2S_ReceiveData(SPI5);
	MPU_DISABLE;
	return data;
}

/*******************************************************************************
 * @funtion      : Mpu_Read_Bytes
 * @description  : Byte字节数据写入函数
 * @param         {uint8_t const regAddr}
 * @param         {uint8_t *pData}
 * @param         {uint8_t len}
 * @return        {*}
 *******************************************************************************/
uint8_t Mpu_Read_Bytes(uint8_t const regAddr, uint8_t *pData, uint8_t len)
{
	int i = 0;
	MPU_ENABLE;
	while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET)
	{
	}
	SPI_I2S_SendData(SPI5, regAddr | 0x80);
	while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_RXNE) == RESET)
	{
	}
	SPI_I2S_ReceiveData(SPI5);
	for (i = 0; i < len; i++)
	{
		while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET)
		{
		}
		SPI_I2S_SendData(SPI5, 0x00);
		while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_RXNE) == RESET)
		{
		}
		pData[i] = SPI_I2S_ReceiveData(SPI5);
	}
	MPU_DISABLE;
	return 0;
}

/*******************************************************************************
 * @funtion      : Mpu_Write_Byte
 * @description  : Byte数据写入函数
 * @param         {uint8_t const reg}
 * @param         {uint8_t const data}
 * @return        {*}
 *******************************************************************************/
uint8_t Mpu_Write_Byte(uint8_t const reg, uint8_t const data)
{
	MPU_ENABLE;
	while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET)
	{
	}
	SPI_I2S_SendData(SPI5, reg & 0x7F);
	while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_RXNE) == RESET)
	{
	}
	SPI_I2S_ReceiveData(SPI5);
	while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET)
	{
	}
	SPI_I2S_SendData(SPI5, data);
	while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_RXNE) == RESET)
	{
	}
	SPI_I2S_ReceiveData(SPI5);
	MPU_DISABLE;
	return 0;
}

/*******************************************************************************
 * @funtion      : Mpu_Aux_Config
 * @description  : 内部I2C Slave配置函数
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Mpu_Aux_Config(uint8_t slaveNum, uint8_t slaveAddr, uint8_t readAddr, uint8_t readLens)
{
	uint8_t reg;
	uint8_t offset = slaveNum * 3;
	delay_ms(1);
	Mpu_Write_Byte(MPUREG_I2C_SLV0_ADDR + offset, slaveAddr | 0x80);
	delay_ms(1);
	Mpu_Write_Byte(MPUREG_I2C_SLV0_REG + offset, readAddr);
	delay_ms(1);
	Mpu_Write_Byte(MPUREG_I2C_SLV0_CTRL + offset, MPUREG_I2C_SLVx_EN | readLens);
	delay_ms(1);
	Mpu_Write_Byte(MPUREG_I2C_SLV4_CTRL, 0x01);
	delay_ms(1);
	reg = Mpu_Read_Byte(MPUREG_I2C_MST_DELAY_CTRL);
	delay_ms(1);
	Mpu_Write_Byte(MPUREG_I2C_MST_DELAY_CTRL, reg | (0x01 << slaveNum));
}

/*******************************************************************************
 * @funtion      : Mpu_Aux_Write_Data
 * @description  : 内部I2C数据写入函数
 * @param         {uint8_t slaveAddr}
 * @param         {uint8_t writeAddr}
 * @param         {uint8_t writeData}
 * @return        {*}
 *******************************************************************************/
void Mpu_Aux_Write_Data(uint8_t slaveAddr, uint8_t writeAddr, uint8_t writeData)
{
	uint8_t status;
	uint32_t timeout = AUX_READ_TIMEOUT;
	delay_ms(1);
	Mpu_Write_Byte(MPUREG_I2C_SLV4_ADDR, slaveAddr);
	delay_ms(1);
	Mpu_Write_Byte(MPUREG_I2C_SLV4_REG, writeAddr);
	delay_ms(1);
	Mpu_Write_Byte(MPUREG_I2C_SLV4_DO, writeData);
	delay_ms(1);
	Mpu_Write_Byte(MPUREG_I2C_SLV4_CTRL, MPUREG_I2C_SLVx_EN);
	do
	{
		delay_ms(1);
		status = Mpu_Read_Byte(MPUREG_I2C_MST_STATUS);
	} while (((status & MPUREG_I2C_SLV4_DONE) == 0) && (timeout--));
	delay_ms(1);
}

/*******************************************************************************
 * @funtion      : Mpu_Aux_Read_Data
 * @description  : 内部I2C数据读取函数
 * @param         {uint8_t slaveAddr}
 * @param         {uint8_t readAddr}
 * @return        {*}
 *******************************************************************************/
uint8_t Mpu_Aux_Read_Data(uint8_t slaveAddr, uint8_t readAddr)
{
	uint8_t status;
	uint8_t readData;
	uint32_t timeout = AUX_READ_TIMEOUT;
	delay_ms(1);
	Mpu_Write_Byte(MPUREG_I2C_SLV4_ADDR, slaveAddr | 0x80);
	delay_ms(1);
	Mpu_Write_Byte(MPUREG_I2C_SLV4_REG, readAddr);
	delay_ms(1);
	Mpu_Write_Byte(MPUREG_I2C_SLV4_CTRL, MPUREG_I2C_SLVx_EN);
	do
	{
		delay_ms(1);
		status = Mpu_Read_Byte(MPUREG_I2C_MST_STATUS);
	} while (((status & MPUREG_I2C_SLV4_DONE) == 0) && (timeout--));
	delay_ms(1);
	readData = Mpu_Read_Byte(MPUREG_I2C_SLV4_DI);
	return readData;
}

/*******************************************************************************
 * @funtion      : Mpu_Offset_Data
 * @description  : 获得偏移量
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Mpu_Offset_Data(void)
{
	int i;
	for (i = 0; i < 300; i++)
	{
		Mpu_Read_Bytes(MPUREG_ACCEL_XOUT_H, MPU_BUFF, 14);
		Mpu_Offset.accel_x += MPU_BUFF[0] << 8 | MPU_BUFF[1];
		Mpu_Offset.accel_y += MPU_BUFF[2] << 8 | MPU_BUFF[3];
		Mpu_Offset.accel_z += MPU_BUFF[4] << 8 | MPU_BUFF[5];
		Mpu_Offset.gyro_x += MPU_BUFF[8] << 8 | MPU_BUFF[9];
		Mpu_Offset.gyro_y += MPU_BUFF[10] << 8 | MPU_BUFF[11];
		Mpu_Offset.gyro_z += MPU_BUFF[12] << 8 | MPU_BUFF[13];
		delay_ms(5);
	}
	Mpu_Offset.accel_x = Mpu_Offset.accel_x / 300;
	Mpu_Offset.accel_y = Mpu_Offset.accel_y / 300;
	Mpu_Offset.accel_z = Mpu_Offset.accel_z / 300;
	Mpu_Offset.gyro_x = Mpu_Offset.gyro_x / 300;
	Mpu_Offset.gyro_y = Mpu_Offset.gyro_y / 300;
	Mpu_Offset.gyro_z = Mpu_Offset.gyro_z / 300;
}

/*******************************************************************************
 * @funtion      : Quaternion_Init
 * @description  : 四元数初始化
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Quaternion_Init(void)
{
	int16_t hx, hy;
	hx = Mpu_Calc.mag_x;
	hy = Mpu_Calc.mag_y;
	if (hx < 0 && hy < 0)
	{
		if (fabs((hx / hy)) >= 1)
		{
			q0 = -0.005;
			q1 = -0.199;
			q2 = 0.979;
			q3 = -0.0089;
		}
		else
		{
			q0 = -0.008;
			q1 = -0.555;
			q2 = 0.83;
			q3 = -0.002;
		}
	}
	else if (hx < 0 && hy > 0)
	{
		if (fabs(hx / hy) >= 1)
		{
			q0 = 0.005;
			q1 = -0.199;
			q2 = -0.978;
			q3 = 0.012;
		}
		else
		{
			q0 = 0.005;
			q1 = -0.553;
			q2 = -0.83;
			q3 = -0.0023;
		}
	}
	else if (hx > 0 && hy > 0)
	{
		if (fabs(hx / hy) >= 1)
		{
			q0 = 0.0012;
			q1 = -0.978;
			q2 = -0.199;
			q3 = -0.005;
		}
		else
		{
			q0 = 0.0023;
			q1 = -0.83;
			q2 = -0.553;
			q3 = 0.0023;
		}
	}
	else if (hx > 0 && hy < 0)
	{
		if (fabs(hx / hy) >= 1)
		{
			q0 = 0.0025;
			q1 = 0.978;
			q2 = -0.199;
			q3 = 0.008;
		}
		else
		{
			q0 = 0.0025;
			q1 = 0.83;
			q2 = -0.56;
			q3 = 0.0045;
		}
	}
}

/*******************************************************************************
 * @funtion      : Compensate_Temperature
 * @description  : 温度数据补偿
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
u32 Compensate_Temperature(s32 adcT)
{
	s32 var1, var2, T;
	var1 = ((((adcT >> 3) - ((s32)Bmp280_Data.dig_T1 << 1))) * ((s32)Bmp280_Data.dig_T2)) >> 11;
	var2 = (((((adcT >> 4) - ((s32)Bmp280_Data.dig_T1)) * ((adcT >> 4) - ((s32)Bmp280_Data.dig_T1))) >> 12) * ((s32)Bmp280_Data.dig_T3)) >> 14;
	Bmp280_Data.t_fine = var1 + var2;
	T = (Bmp280_Data.t_fine * 5 + 128) >> 8;
	return T;
}

/*******************************************************************************
 * @funtion      : Compensate_Pressure
 * @description  : 气压数据补偿
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
u32 Compensate_Pressure(s32 adcP)
{
	int64_t var1, var2, p;
	var1 = ((int64_t)Bmp280_Data.t_fine) - 128000;
	var2 = var1 * var1 * (int64_t)Bmp280_Data.dig_P6;
	var2 = var2 + ((var1 * (int64_t)Bmp280_Data.dig_P5) << 17);
	var2 = var2 + (((int64_t)Bmp280_Data.dig_P4) << 35);
	var1 = ((var1 * var1 * (int64_t)Bmp280_Data.dig_P3) >> 8) + ((var1 * (int64_t)Bmp280_Data.dig_P2) << 12);
	var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)Bmp280_Data.dig_P1) >> 33;
	if (var1 == 0)
	{
		return 0;
	}
	p = 1048576 - adcP;
	p = (((p << 31) - var2) * 3125) / var1;
	var1 = (((int64_t)Bmp280_Data.dig_P9) * (p >> 13) * (p >> 13)) >> 25;
	var2 = (((int64_t)Bmp280_Data.dig_P8) * p) >> 19;
	p = ((p + var1 + var2) >> 8) + (((int64_t)Bmp280_Data.dig_P7) << 4);
	return (uint32_t)p;
}

/*******************************************************************************
 * @funtion      : PressureFilter
 * @description  : 气压数据过滤
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void PressureFilter(float *in, float *out)
{
	static u8 i = 0;
	static float filter_buf[FILTER_NUM] = {0.0};
	double filter_sum = 0.0;
	u8 cnt = 0;
	float deta;
	if (filter_buf[i] == 0.0f)
	{
		filter_buf[i] = *in;
		*out = *in;
		if (++i >= FILTER_NUM)
			i = 0;
	}
	else
	{
		if (i)
		{
			deta = *in - filter_buf[i - 1];
		}
		else
		{
			deta = *in - filter_buf[FILTER_NUM - 1];
		}
		if (fabs(deta) < FILTER_A)
		{
			filter_buf[i] = *in;
			if (++i >= FILTER_NUM)
				i = 0;
		}
		for (cnt = 0; cnt < FILTER_NUM; cnt++)
		{
			filter_sum += filter_buf[cnt];
		}
		*out = filter_sum / FILTER_NUM;
	}
}

/*******************************************************************************
 * @funtion      : Pressure_To_Altitude
 * @description  : 气压转海拔数据
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
float Pressure_To_Altitude(float *pressure)
{
	if (*pressure > 0)
	{
		return ((pow((1015.7f / *pressure), CONST_PF) - 1.0f) * (FIX_TEMP + 273.15f)) / 0.0065f;
	}
	else
	{
		return 0;
	}
}

/*******************************************************************************
 * @funtion      : Mpu_Attitude_Calc
 * @description  : 姿态数据计算
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
float inv_sqrt(float x)
{
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long *)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float *)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}

void Mpu_Attitude_Calc(void)
{
	float norm;
	float hx, hy, hz, bx, bz;
	float vx, vy, vz, wx, wy, wz;
	float ex, ey, ez, halfT;
	float tempq0, tempq1, tempq2, tempq3;
	float q0q0 = q0 * q0;
	float q0q1 = q0 * q1;
	float q0q2 = q0 * q2;
	float q0q3 = q0 * q3;
	float q1q1 = q1 * q1;
	float q1q2 = q1 * q2;
	float q1q3 = q1 * q3;
	float q2q2 = q2 * q2;
	float q2q3 = q2 * q3;
	float q3q3 = q3 * q3;

	gx = Mpu_Calc.gyro_x;
	gy = Mpu_Calc.gyro_y;
	gz = Mpu_Calc.gyro_z;
	ax = Mpu_Calc.accel_x;
	ay = Mpu_Calc.accel_y;
	az = Mpu_Calc.accel_z;
	mx = Mpu_Calc.mag_x;
	my = Mpu_Calc.mag_y;
	mz = Mpu_Calc.mag_z;

	now_update = Get_SysTick();

	halfT = ((float)(now_update - last_update) / 1000.0f);
	last_update = now_update;

	norm = inv_sqrt(ax * ax + ay * ay + az * az);

	ax = ax * norm;
	ay = ay * norm;
	az = az * norm;

#ifdef AK8963
	norm = inv_sqrt(mx * mx + my * my + mz * mz);
	mx = mx * norm;
	my = my * norm;
	mz = mz * norm;
#else
	mx = 0;
	my = 0;
	mz = 0;
#endif

	hx = 2.0f * mx * (0.5f - q2q2 - q3q3) + 2.0f * my * (q1q2 - q0q3) + 2.0f * mz * (q1q3 + q0q2);
	hy = 2.0f * mx * (q1q2 + q0q3) + 2.0f * my * (0.5f - q1q1 - q3q3) + 2.0f * mz * (q2q3 - q0q1);
	hz = 2.0f * mx * (q1q3 - q0q2) + 2.0f * my * (q2q3 + q0q1) + 2.0f * mz * (0.5f - q1q1 - q2q2);

	bx = sqrt((hx * hx) + (hy * hy));
	bz = hz;
	vx = 2.0f * (q1q3 - q0q2);
	vy = 2.0f * (q0q1 + q2q3);
	vz = q0q0 - q1q1 - q2q2 + q3q3;
	wx = 2.0f * bx * (0.5f - q2q2 - q3q3) + 2.0f * bz * (q1q3 - q0q2);
	wy = 2.0f * bx * (q1q2 - q0q3) + 2.0f * bz * (q0q1 + q2q3);
	wz = 2.0f * bx * (q0q2 + q1q3) + 2.0f * bz * (0.5f - q1q1 - q2q2);
	ex = (ay * vz - az * vy) + (my * wz - mz * wy);
	ey = (az * vx - ax * vz) + (mz * wx - mx * wz);
	ez = (ax * vy - ay * vx) + (mx * wy - my * wx);
	if (ex != 0.0f && ey != 0.0f && ez != 0.0f)
	{
		exInt = exInt + ex * Ki * halfT;
		eyInt = eyInt + ey * Ki * halfT;
		ezInt = ezInt + ez * Ki * halfT;
		gx = gx + Kp * ex + exInt;
		gy = gy + Kp * ey + eyInt;
		gz = gz + Kp * ez + ezInt;
	}
	tempq0 = q0 + (-q1 * gx - q2 * gy - q3 * gz) * halfT;
	tempq1 = q1 + (q0 * gx + q2 * gz - q3 * gy) * halfT;
	tempq2 = q2 + (q0 * gy - q1 * gz + q3 * gx) * halfT;
	tempq3 = q3 + (q0 * gz + q1 * gy - q2 * gx) * halfT;
	norm = inv_sqrt(tempq0 * tempq0 + tempq1 * tempq1 + tempq2 * tempq2 + tempq3 * tempq3);
	q0 = tempq0 * norm;
	q1 = tempq1 * norm;
	q2 = tempq2 * norm;
	q3 = tempq3 * norm;
}

/*******************************************************************************
 * @funtion      : Mpu_Task
 * @description  : 任务回调函数，数据读取计算（加速度、陀螺仪、磁力计、气温、气压（海拔））
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Mpu_Task(void)
{
	static float this_temperature;
	static float this_pressure;

	Mpu_Read_Bytes(MPUREG_ACCEL_XOUT_H, MPU_BUFF, 28);

	Mpu_Data.accel_x = MPU_BUFF[0] << 8 | MPU_BUFF[1];
	Mpu_Data.accel_y = MPU_BUFF[2] << 8 | MPU_BUFF[3];
	Mpu_Data.accel_z = MPU_BUFF[4] << 8 | MPU_BUFF[5];
	Mpu_Data.temperature = MPU_BUFF[6] << 8 | MPU_BUFF[7];
	Mpu_Data.gyro_x = ((MPU_BUFF[8] << 8 | MPU_BUFF[9]) - Mpu_Offset.gyro_x);
	Mpu_Data.gyro_y = ((MPU_BUFF[10] << 8 | MPU_BUFF[11]) - Mpu_Offset.gyro_y);
	Mpu_Data.gyro_z = ((MPU_BUFF[12] << 8 | MPU_BUFF[13]) - Mpu_Offset.gyro_z);

	if (MPU_BUFF[14] == 1)
	{
		Mpu_Data.mag_x = (MPU_BUFF[16] << 8) | MPU_BUFF[15];
		Mpu_Data.mag_y = (MPU_BUFF[18] << 8) | MPU_BUFF[17];
		Mpu_Data.mag_z = (MPU_BUFF[20] << 8) | MPU_BUFF[19];
	}

	Mpu_Calc.mag_x = Mpu_Data.mag_x * (((Mpu_Offset.gyro_x - 128) * 0.5) / 128 + 1);
	Mpu_Calc.mag_y = Mpu_Data.mag_y * (((Mpu_Offset.gyro_y - 128) * 0.5) / 128 + 1);
	Mpu_Calc.mag_z = Mpu_Data.mag_z * (((Mpu_Offset.gyro_z - 128) * 0.5) / 128 + 1);

	memcpy(&Mpu_Calc.accel_x, &Mpu_Data.accel_x, 3 * sizeof(int16_t));

	Mpu_Calc.temperature = 21 + (Mpu_Data.temperature - 21) / 333.87f;

	Mpu_Calc.gyro_x = Mpu_Data.gyro_x / 16.384f / 57.3f;
	Mpu_Calc.gyro_y = Mpu_Data.gyro_y / 16.384f / 57.3f;
	Mpu_Calc.gyro_z = Mpu_Data.gyro_z / 16.384f / 57.3f;

	pressure = (s32)((((uint32_t)(MPU_BUFF[22])) << 12) | (((uint32_t)(MPU_BUFF[23])) << 4) | ((uint32_t)MPU_BUFF[24] >> 4));

	temperature = (s32)((((uint32_t)(MPU_BUFF[25])) << 12) | (((uint32_t)(MPU_BUFF[26])) << 4) | ((uint32_t)MPU_BUFF[27] >> 4));

	this_temperature = Compensate_Temperature(temperature) / 100.0;

	this_pressure = Compensate_Pressure(pressure) / 25600.0;

	// 最终的气压数据
	PressureFilter(&this_pressure, &Mpu_Read_Data.pressure);

	// 最终的海拔数据
	Mpu_Read_Data.altitude = Pressure_To_Altitude(&this_pressure);

	// 最终的气温数据
	Mpu_Read_Data.temperature = this_temperature;

	Mpu_Attitude_Calc();

	// 最终的姿态数据
	Mpu_Read_Data.yaw = -atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2 * q2 - 2 * q3 * q3 + 1) * 57.3;
	Mpu_Read_Data.rol = -asin(-2 * q1 * q3 + 2 * q0 * q2) * 57.3;
	Mpu_Read_Data.pit = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2 * q2 + 1) * 57.3;
}

/*******************************************************************************
 * @funtion      : Mpu_Usb_Callback
 * @description  : 串口任务回调函数
 * @param         {char *type} 通讯协议类型
 * @return        {*}
 *******************************************************************************/
void Mpu_Usb_Callback(char *type)
{
	if (memcmp(type, "mpu-read", 8) == 0)
	{
		Usb_Write_Data("{\"type\":\"mpu-read\",\"rol\":%0.3f,\"pit\":%0.3f,\"yaw\":%0.3f,\"temperature\":%0.3f,\"altitude\":%0.3f,\"pressure\":%0.3f}\r\n",
					   Mpu_Read_Data.rol, Mpu_Read_Data.pit, Mpu_Read_Data.yaw, Mpu_Read_Data.temperature, Mpu_Read_Data.altitude, Mpu_Read_Data.pressure);
	}
	else if (memcmp(type, "mpu-accel", 9) == 0)
	{
		Usb_Write_Data("{\"type\":\"mpu-accel\",\"x\":%d,\"y\":%d,\"z\":%d}\r\n",
					   Mpu_Calc.accel_x, Mpu_Calc.accel_y, Mpu_Calc.accel_z);
	}
}
