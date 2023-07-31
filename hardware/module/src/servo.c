/**
  ******************************************************************************
  * @file    servo.c
  * @author  GEEKROS,  site:www.geekros.com
  ******************************************************************************
*/

#include "servo.h"

int Servo_Time = 2000;

Servo_Read_Write_Struct Servo_Read_Write;

Servo_Struct Servo_Data[SERVO_LEN];

/******************************************************************
  * @ 函数名  ： Servo_Init
  * @ 功能说明： 总线舵机模块初始化，UART3作为总线舵机模块专用接口
  * @ 参数    ： int baud_rate 波特率
  * @ 返回值  ： NULL
  *****************************************************************/
void Servo_Init(int baud_rate)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3); 

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_Init(GPIOD, &GPIO_InitStructure);

	USART_DeInit(USART3);
	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate = baud_rate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART3, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}

/******************************************************************
  * @ 函数名  ： USART3_IRQHandler
  * @ 功能说明： 总线舵机模块中断函数，接收UART3数据
  * @ 参数    ： NULL
  * @ 返回值  ： NULL
  *****************************************************************/
void USART3_IRQHandler(void)
{
	volatile static uint8_t data;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		data = USART_ReceiveData(USART3);
		Servo_Read_Write.Servo_Read_Buffer[Servo_Read_Write.Servo_Read_Len] = data;
		Servo_Read_Write.Servo_Read_Len = (Servo_Read_Write.Servo_Read_Len + 1) % 128;
	}
}

/******************************************************************
  * @ 函数名  ： Servo_SCSToHost
  * @ 功能说明： 2个8位数组合为1个16位数
  * @ 参数    ： NULL
  * @ 返回值  ： NULL
  *****************************************************************/
int Servo_SCSToHost(uint8_t ID, uint8_t DataL, uint8_t DataH)
{
	int Data;
	if(Servo_Data[ID].end)
	{
		Data = DataL;
		Data<<=8;
		Data |= DataH;
	}else{
		Data = DataH;
		Data<<=8;
		Data |= DataL;
	}
	return Data;
}

/******************************************************************
  * @ 函数名  ： Servo_HostToSCS
  * @ 功能说明： 1个16位数拆分为2个8位数
  * @ 参数    ： NULL
  * @ 返回值  ： NULL
  *****************************************************************/
void Servo_HostToSCS(uint8_t ID, uint8_t *DataL, uint8_t *DataH, int Data)
{
	if(Servo_Data[ID].end){
		*DataL = (Data>>8);
		*DataH = (Data&0xff);
	}else{
		*DataH = (Data>>8);
		*DataL = (Data&0xff);
	}
}

/******************************************************************
  * @ 函数名  ： Servo_Read_Flush
  * @ 功能说明： 刷新接收缓冲区
  * @ 参数    ： NULL
  * @ 返回值  ： NULL
  *****************************************************************/
void Servo_Read_Flush(void)
{
	Servo_Read_Write.Servo_Read_Len = 0;
	Servo_Read_Write.Servo_Read_Step = 0;
}

/******************************************************************
  * @ 函数名  ： Servo_Write_Flush
	* @ 功能说明： 刷新发送缓冲区
  * @ 参数    ： NULL
  * @ 返回值  ： NULL
  *****************************************************************/
void Servo_Write_Flush(void)
{
	if(Servo_Read_Write.Servo_Write_Len)
	{
		Servo_Send(Servo_Read_Write.Servo_Write_Buffer, Servo_Read_Write.Servo_Write_Len);
		Servo_Read_Write.Servo_Write_Len = 0;
	}
}

/******************************************************************
  * @ 函数名  ： Servo_Send
	* @ 功能说明： 发送舵机数据
  * @ 参数    ： NULL
  * @ 返回值  ： NULL
  *****************************************************************/
void Servo_Send(uint8_t *buf , uint8_t len)
{
	while (len--)
	{
		while ((USART3->SR & 0x40) == 0);
		USART_SendData(USART3, *buf++);
	}
}

/******************************************************************
  * @ 函数名  ： Servo_WriteSCS、Servo_Write_Data
	* @ 功能说明： 发送前数据处理
  * @ 参数    ： NULL
  * @ 返回值  ： NULL
  *****************************************************************/
int Servo_WriteSCS(unsigned char *nDat, int nLen)
{
	while(nLen--){
		if(Servo_Read_Write.Servo_Write_Len < sizeof(Servo_Read_Write.Servo_Write_Buffer)){
			Servo_Read_Write.Servo_Write_Buffer[Servo_Read_Write.Servo_Write_Len] = *nDat;
			Servo_Read_Write.Servo_Write_Len++;
			nDat++;
		}
	}
	return Servo_Read_Write.Servo_Write_Len;
}
void Servo_Write_Data(uint8_t ID, uint8_t MemAddr, uint8_t *nDat, uint8_t nLen, uint8_t Fun)
{
	uint8_t i;
	uint8_t msgLen = 2;
	uint8_t bBuf[6];
	uint8_t CheckSum = 0;
	bBuf[0] = 0xff;
	bBuf[1] = 0xff;
	bBuf[2] = ID;
	bBuf[4] = Fun;
	if(nDat)
	{
		msgLen += nLen + 1;
		bBuf[3] = msgLen;
		bBuf[5] = MemAddr;
		Servo_WriteSCS(bBuf, 6);
	}else{
		bBuf[3] = msgLen;
		Servo_WriteSCS(bBuf, 5);
	}
	CheckSum = ID + msgLen + Fun + MemAddr;
	if(nDat)
	{
		for(i=0; i<nLen; i++)
		{
			CheckSum += nDat[i];
		}
		Servo_WriteSCS(nDat, nLen);
	}
	CheckSum = ~CheckSum;
	Servo_WriteSCS(&CheckSum, 1);
}

/******************************************************************
  * @ 函数名  ： Servo_Read、Servo_ReadSCS、Servo_Check_Head、Servo_Read_Instructions
  * @ 功能说明： 读取前数据处理
  * @ 参数    ： NULL
  * @ 返回值  ： NULL
  *****************************************************************/
uint32_t IOTimeOut = 20000;
int16_t Servo_Read(void)
{
	uint8_t Reback_Data;
	if(Servo_Read_Write.Servo_Read_Step != Servo_Read_Write.Servo_Read_Len)
	{
		Reback_Data = Servo_Read_Write.Servo_Read_Buffer[Servo_Read_Write.Servo_Read_Step];
		Servo_Read_Write.Servo_Read_Step = (Servo_Read_Write.Servo_Read_Step + 1) % 128;
		return Reback_Data;
	}else{
		return -1;
	}
}
int Servo_ReadSCS(unsigned char *nDat, int nLen)
{
	int Size = 0;
	int ComData;
	uint32_t t_begin = 0;
	uint32_t time_Count = 0;
	uint32_t t_user;
	while(1)
	{
		ComData = Servo_Read();
		if(ComData!=-1)
		{
			if(nDat)
			{
				nDat[Size] = ComData;
			}
			Size++;
			t_begin = 0;
		}
		if(Size >= nLen)
		{
			break;
		}
		time_Count++;
		t_user = time_Count - t_begin;
		if(t_user > IOTimeOut)
		{
			break;
		}
	}
	return Size;
}
int Servo_Check_Head(void)
{
	uint8_t bDat;
	uint8_t bBuf[2] = {0, 0};
	uint8_t Cnt = 0;
	while(1)
	{
		if(!Servo_ReadSCS(&bDat, 1))
		{
			return 0;
		}
		bBuf[1] = bBuf[0];
		bBuf[0] = bDat;
		if(bBuf[0] == 0xff && bBuf[1] == 0xff)
		{
			break;
		}
		Cnt++;
		if(Cnt > 10)
		{
			return 0;
		}
	}
	return 1;
}
int Servo_Read_Instructions(uint8_t id, uint8_t MemAddr, uint8_t *nData, uint8_t nLen)
{
	int Size;
	uint8_t bBuf[4];
	uint8_t calSum;
	uint8_t i;
	Servo_Read_Flush();
	Servo_Write_Data(id, MemAddr, &nLen, 1, SERVO_INST_READ);
	Servo_Write_Flush();
	if(!Servo_Check_Head())
	{
		return 0;
	}
	if(Servo_ReadSCS(bBuf, 3) != 3){
		return 0;
	}
	Size = Servo_ReadSCS(nData, nLen);
	if(Size != nLen)
	{
		return 0;
	}
	if(Servo_ReadSCS(bBuf + 3, 1) != 1)
	{
		return 0;
	}
	calSum = bBuf[0] + bBuf[1] + bBuf[2];
	for(i=0; i<Size; i++)
	{
		calSum += nData[i];
	}
	calSum = ~calSum;
	if(calSum != bBuf[3])
	{
		return 0;
	}
	return Size;
}

/******************************************************************
  * @ 函数名  ： Servo_Read_Byte
  * @ 功能说明： 读1字节
  * @ 参数    ： uint8_t ID 舵机ID
  * @ 参数    ： uint8_t MemAddr 内存表地址
  * @ 返回值  ： NULL
  *****************************************************************/
int Servo_Read_Byte(uint8_t ID, uint8_t MemAddr)
{
	uint8_t bDat;
	int Size = Servo_Read_Instructions(ID, MemAddr, &bDat, 1);
	if(Size != 1){
		return -1;
	}else{
		return bDat;
	}
}

/******************************************************************
  * @ 函数名  ： Servo_Read_Word
  * @ 功能说明： 读2字节
  * @ 参数    ： uint8_t ID 舵机ID
  * @ 参数    ： uint8_t MemAddr 内存表地址
  * @ 返回值  ： NULL
  *****************************************************************/
int Servo_Read_Word(uint8_t ID, uint8_t MemAddr)
{
	uint8_t nDat[2];
	int Size;
	uint16_t wDat;
	Size = Servo_Read_Instructions(ID, MemAddr, nDat, 2);
	if(Size != 2)
	{
		return -1;
	}
	wDat = Servo_SCSToHost(ID - 1, nDat[0], nDat[1]);
	return wDat;
}

/******************************************************************
  * @ 函数名  ： Servo_Read_Position
  * @ 功能说明： 读取舵机位置信息
  * @ 参数    ： int id 舵机ID
  * @ 返回值  ： NULL
  *****************************************************************/
void Servo_Read_Position(int id)
{
	int Position = -1;
	Position = Servo_Read_Word(id, SERVO_PRESENT_POSITION_L);
	if(Position != -1 && Position&(1<<15))
	{
		Position = -(Position&~(1<<15));
	}
	Servo_Data[id - 1].position = Position;
}

/******************************************************************
  * @ 函数名  ： Servo_Read_Speed
  * @ 功能说明： 读取舵机速度信息
  * @ 参数    ： int id 舵机ID
  * @ 返回值  ： NULL
  *****************************************************************/
void Servo_Read_Speed(int id)
{
	int Speed = -1;
	Speed = Servo_Read_Word(id, SERVO_PRESENT_SPEED_L);
	if(Speed != -1 && Speed&(1<<15))
	{
		Speed = -(Speed&~(1<<15));
	}
	Servo_Data[id - 1].speed = Speed;
}

/******************************************************************
  * @ 函数名  ： Servo_Read_Load
  * @ 功能说明： 读取舵机输出扭力信息
  * @ 参数    ： int id 舵机ID
  * @ 返回值  ： NULL
  *****************************************************************/
void Servo_Read_Load(int id)
{
	int Load = -1;
	Load = Servo_Read_Word(id, SERVO_PRESENT_LOAD_L);
	if(Load != -1 && Load&(1<<10))
	{
		Load = -(Load&~(1<<10));
	}
	Servo_Data[id - 1].load = Load;
}

/******************************************************************
  * @ 函数名  ： Servo_Read_Voltage
  * @ 功能说明： 读取舵机运动状态信息
  * @ 参数    ： int id 舵机ID
  * @ 返回值  ： NULL
  *****************************************************************/
void Servo_Read_Motion_State(int id)
{
	int Motion_State = -1;
	Motion_State = Servo_Read_Byte(id, SERVO_MOVING);
	Servo_Data[id - 1].motion_state = Motion_State;
}

/******************************************************************
  * @ 函数名  ： Servo_Read_Voltage
  * @ 功能说明： 读取舵机电压信息
  * @ 参数    ： int id 舵机ID
  * @ 返回值  ： NULL
  *****************************************************************/
void Servo_Read_Voltage(int id)
{
	int Voltage = -1;
	Voltage = Servo_Read_Byte(id, SERVO_PRESENT_VOLTAGE);
	Servo_Data[id - 1].voltage = Voltage;
}

/******************************************************************
  * @ 函数名  ： Servo_Read_Current
  * @ 功能说明： 读取舵机电流信息
  * @ 参数    ： int id 舵机ID
  * @ 返回值  ： NULL
  *****************************************************************/
void Servo_Read_Current(int id)
{
	int Current = -1;
	Current = Servo_Read_Word(id, SERVO_PRESENT_CURRENT_L);
	if(Current != -1 && Current&(1<<15))
	{
		Current = -(Current&~(1<<15));
	}
	Servo_Data[id - 1].current = Current;
}

/******************************************************************
  * @ 函数名  ： Servo_Read_Temperature
  * @ 功能说明： 读取舵机温度信息
  * @ 参数    ： int id 舵机ID
  * @ 返回值  ： NULL
  *****************************************************************/
void Servo_Read_Temperature(int id)
{
	int Temperature = -1;
	Temperature = Servo_Read_Byte(id, SERVO_PRESENT_TEMPERATURE);
	Servo_Data[id - 1].temperature = Temperature;
}

/******************************************************************
  * @ 函数名  ： Servo_Type
  * @ 功能说明： 设置舵机类型
  * @ 参数    ： int id 舵机ID 可选值0~12
  * @ 参数    ： int type 舵机类型 可选值 1（飞特STS3032）、2（飞特SCS009）
  * @ 返回值  ： NULL
  *****************************************************************/
void Servo_Type(int id, int type)
{
	if(id == 0)
	{
		for(int i=0; i<SERVO_LEN; i++)
		{
			Servo_Data[i].type = (type == 1) ? SERVO_STS : SERVO_SCS;
			if(type == SERVO_SCS)
			{
				Servo_Data[i].end = 1;
			}
			if(type == SERVO_STS)
			{
				Servo_Data[i].end = 0;
			}
		}
	}else{
		if(id <= 12)
		{
			Servo_Data[id - 1].type = (type == 1) ? SERVO_STS : SERVO_SCS;
			if(type == SERVO_SCS)
			{
				Servo_Data[id - 1].end = 1;
			}
			if(type == SERVO_STS)
			{
				Servo_Data[id - 1].end = 0;
			}
		}
	}
}

/******************************************************************
  * @ 函数名  ： Servo_Read_Data
  * @ 功能说明： 读取舵机数据
  * @ 参数    ： int id 舵机ID 可选值0~12
  * @ 返回值  ： NULL
  *****************************************************************/
void Servo_Read_Data(int id)
{
	if(id == 0)
	{
		for(int i=0; i<SERVO_LEN; i++)
		{
			Servo_Read_Voltage(i + 1);
			Servo_Read_Position(i + 1);
			Servo_Read_Temperature(i + 1);
			Servo_Read_Current(i + 1);
			Servo_Read_Motion_State(i + 1);
			Servo_Read_Load(i + 1);
			Servo_Read_Speed(i + 1);
		}
	}else{
		Servo_Read_Voltage(id);
		Servo_Read_Position(id);
		Servo_Read_Temperature(id);
		Servo_Read_Current(id);
		Servo_Read_Motion_State(id);
		Servo_Read_Load(id);
		Servo_Read_Speed(id);
	}
}

/******************************************************************
  * @ 函数名  ： Servo_Sync_Write
  * @ 功能说明： 同步写指令
  * @ 参数    ： NULL
  * @ 返回值  ： NULL
  *****************************************************************/
void Servo_Sync_Write(uint8_t ID[], uint8_t IDN, uint8_t MemAddr, uint8_t *nDat, uint8_t nLen)
{
	uint8_t mesLen = ((nLen+1)*IDN+4);
	uint8_t Sum = 0;
	uint8_t bBuf[7];
	uint8_t i, j;
	
	bBuf[0] = 0xff;
	bBuf[1] = 0xff;
	bBuf[2] = 0xfe;
	bBuf[3] = mesLen;
	bBuf[4] = SERVO_INST_SYNC_WRITE;
	bBuf[5] = MemAddr;
	bBuf[6] = nLen;
	
	Servo_Read_Flush();
	Servo_WriteSCS(bBuf, 7);
	
	Sum = 0xfe + mesLen + SERVO_INST_SYNC_WRITE + MemAddr + nLen;
	
	for(i=0; i<IDN; i++){
		Servo_WriteSCS(&ID[i], 1);
		Servo_WriteSCS(nDat+i*nLen, nLen);
		Sum += ID[i];
		for(j=0; j<nLen; j++){
			Sum += nDat[i*nLen+j];
		}
	}
	
	Sum = ~Sum;
	Servo_WriteSCS(&Sum, 1);
	Servo_Write_Flush();
}

/******************************************************************
  * @ 函数名  ： Servo_Write_Position
  * @ 功能说明： 控制多个舵机到达指定位置
  * @ 参数    ： NULL
  * @ 返回值  ： NULL
  *****************************************************************/
void Servo_Write_Position(uint8_t ID[], uint8_t IDN, uint16_t Position[], uint16_t Time[], uint16_t Speed[])
{
    uint8_t offbuf[32 * 6];
    uint8_t i;
    for(i = 0; i<IDN; i++)
    {
        uint16_t T, V;
        if(Time)
        {
            T = Time[i];
        }else{
            T = 0;
        }
        if(Speed)
        {
            V = Speed[i];
        }else{
            V = 0;
        }
        Servo_HostToSCS(i, offbuf + i*6 + 0, offbuf + i*6 + 1, Position[i]);
        Servo_HostToSCS(i, offbuf + i*6 + 2, offbuf + i*6 + 3, T);
        Servo_HostToSCS(i, offbuf + i*6 + 4, offbuf + i*6 + 5, V);
    }
    Servo_Sync_Write(ID, IDN, SERVO_GOAL_POSITION_L, offbuf, 6);
}

/******************************************************************
  * @ 函数名  ： Servo_Write_Position
  * @ 功能说明： 控制指定舵机到达指定位置
  * @ 参数    ： NULL
  * @ 返回值  ： NULL
  *****************************************************************/
void Servo_Id_Write_Position(uint8_t ID, uint16_t Position, uint16_t Time, uint16_t Speed)
{
	uint8_t bBuf[6];
	Servo_HostToSCS(ID-1, bBuf+0, bBuf+1, Position);
	Servo_HostToSCS(ID-1, bBuf+2, bBuf+3, Time);
	Servo_HostToSCS(ID-1, bBuf+4, bBuf+5, Speed);
	Servo_Read_Flush();
	Servo_Write_Data(ID, SERVO_GOAL_POSITION_L, bBuf, 6, SERVO_INST_WRITE);
	Servo_Write_Flush();
}

/*******************************************************************************
 * @funtion      : Servo_Usb_Callback
 * @description  : 串口任务回调函数
 * @param         {char *type} 通讯协议类型
 * @return        {*}
 *******************************************************************************/
void Servo_Usb_Callback(char *type, int id, int baud_rate, int servo_type)
{
	
}
