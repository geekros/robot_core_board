/**
  ******************************************************************************
  * @file    flash.c
  * @author  GEEKROS,  site:www.geekros.com
  ******************************************************************************
*/

#include "flash.h"

/******************************************************************
  * @ ������  �� Flash_Get_Sector
  * @ ����˵���� ��ȡĳ����ַ���ڵ�flash����
  * @ ����    �� NULL 
  * @ ����ֵ  �� NULL
  *****************************************************************/
uint16_t Flash_Get_Sector(u32 addr)
{
	if((addr < ADDR_FLASH_SECTOR_1) && (addr >= ADDR_FLASH_SECTOR_0))
	{
		return FLASH_Sector_0;
	}else if((addr < ADDR_FLASH_SECTOR_2) && (addr >= ADDR_FLASH_SECTOR_1)){
		return FLASH_Sector_1;
	}else if((addr < ADDR_FLASH_SECTOR_3) && (addr >= ADDR_FLASH_SECTOR_2)){
		return FLASH_Sector_2;
	}else if((addr < ADDR_FLASH_SECTOR_4) && (addr >= ADDR_FLASH_SECTOR_3)){
		return FLASH_Sector_3;
	}else if((addr < ADDR_FLASH_SECTOR_5) && (addr >= ADDR_FLASH_SECTOR_4)){
		return FLASH_Sector_4;
	}else if((addr < ADDR_FLASH_SECTOR_6) && (addr >= ADDR_FLASH_SECTOR_5)){
		return FLASH_Sector_5;
	}else if((addr < ADDR_FLASH_SECTOR_7) && (addr >= ADDR_FLASH_SECTOR_6)){
		return FLASH_Sector_6;
	}else if((addr < ADDR_FLASH_SECTOR_8) && (addr >= ADDR_FLASH_SECTOR_7)){
		return FLASH_Sector_7;
	}else if((addr < ADDR_FLASH_SECTOR_9) && (addr >= ADDR_FLASH_SECTOR_8)){
		return FLASH_Sector_8;
	}else if((addr < ADDR_FLASH_SECTOR_10) && (addr >= ADDR_FLASH_SECTOR_9)){
		return FLASH_Sector_9;
	}else if((addr < ADDR_FLASH_SECTOR_11) && (addr >= ADDR_FLASH_SECTOR_10)){
		return FLASH_Sector_10;
	}else if((addr < ADDR_FLASH_SECTOR_12) && (addr >= ADDR_FLASH_SECTOR_11)){
		return FLASH_Sector_11;
	}else if((addr < ADDR_FLASH_SECTOR_13) && (addr >= ADDR_FLASH_SECTOR_12)){
		return FLASH_Sector_12;
	}else if((addr < ADDR_FLASH_SECTOR_14) && (addr >= ADDR_FLASH_SECTOR_13)){
		return FLASH_Sector_13;
	}else if((addr < ADDR_FLASH_SECTOR_15) && (addr >= ADDR_FLASH_SECTOR_14)){
		return FLASH_Sector_14;
	}else if((addr < ADDR_FLASH_SECTOR_16) && (addr >= ADDR_FLASH_SECTOR_15)){
		return FLASH_Sector_15;
	}else if((addr < ADDR_FLASH_SECTOR_17) && (addr >= ADDR_FLASH_SECTOR_16)){
		return FLASH_Sector_16;
	}else if((addr < ADDR_FLASH_SECTOR_18) && (addr >= ADDR_FLASH_SECTOR_17)){
		return FLASH_Sector_17;
	}else if((addr < ADDR_FLASH_SECTOR_19) && (addr >= ADDR_FLASH_SECTOR_18)){
		return FLASH_Sector_18;
	}else if((addr < ADDR_FLASH_SECTOR_20) && (addr >= ADDR_FLASH_SECTOR_19)){
		return FLASH_Sector_19;
	}else if((addr < ADDR_FLASH_SECTOR_21) && (addr >= ADDR_FLASH_SECTOR_20)){
		return FLASH_Sector_20;
	}else if((addr < ADDR_FLASH_SECTOR_22) && (addr >= ADDR_FLASH_SECTOR_21)){
		return FLASH_Sector_21;
	}else if((addr < ADDR_FLASH_SECTOR_23) && (addr >= ADDR_FLASH_SECTOR_22)){
		return FLASH_Sector_22;
	}else
		return FLASH_Sector_23;
}

/******************************************************************
  * @ ������  �� Flash_Write_Data
  * @ ����˵���� д������
  * @ ����    �� NULL 
  * @ ����ֵ  �� NULL
  *****************************************************************/
int Flash_Write(uint32_t len, uint16_t *data)
{
	uint32_t write_addr;
	write_addr = FLASH_SAVE_ADDR;
	
	// ����
	FLASH_Unlock();
	// �����û����� (�û�����ָ������û��ʹ�õĿռ䣬�����Զ���)���������FLASH�ı�־λ 
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
	// ������������
	if (FLASH_COMPLETE != FLASH_EraseSector(Flash_Get_Sector(write_addr), VoltageRange_3))
  {		
		return FLASH_ERROR;
	}
	for (int i = 0; i < len; i++)
	{
		// д��16λ����
		if (FLASH_COMPLETE != FLASH_ProgramHalfWord(write_addr, data[i]))
		{
			return FLASH_ERROR;
		}
		write_addr += 2;	//16λ����ƫ������λ��
	}
	// ����
	FLASH_Lock();
	return FLASH_SUCCESS;
}

/******************************************************************
  * @ ������  �� Flash_Read_Data
  * @ ����˵���� ��ȡ����
  * @ ����    �� NULL 
  * @ ����ֵ  �� NULL
  *****************************************************************/
void Flash_Read(uint32_t len, uint16_t *data)
{
	uint32_t read_addr;
	read_addr = FLASH_SAVE_ADDR;
	
	for (int i = 0; i < len; i++)
	{
		data[i] = *(__IO uint16_t*)read_addr;
		if(data[i] == 65535){
			data[i] = 0;
		}
		read_addr += 2;
	}
}

/******************************************************************
  * @ ������  �� Flash_Erase_Data
  * @ ����˵���� �洢����
  * @ ����    �� NULL 
  * @ ����ֵ  �� NULL
  *****************************************************************/
int Flash_Erase_Data(void)
{
	// ����
	FLASH_Unlock();
	// �����û����� (�û�����ָ������û��ʹ�õĿռ䣬�����Զ���)���������FLASH�ı�־λ 
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
	if (FLASH_COMPLETE != FLASH_EraseSector(Flash_Get_Sector(FLASH_SAVE_ADDR), VoltageRange_3))
  {		
		return FLASH_ERROR;
	}
	// ����
	FLASH_Lock();
	
	return FLASH_SUCCESS;
}

/*******************************************************************************
 * @funtion      : Flash_Usb_Callback
 * @description  : ��������ص�����
 * @param         {char *type} ͨѶЭ������
 * @return        {*}
 *******************************************************************************/
void Flash_Usb_Callback(char *type, uint32_t len)
{
	uint16_t Flash_Write_Data[len];
	uint16_t Flash_Read_Data[len];
	
	if (memcmp(type, "flash-write", 11) == 0)
	{
		memset(Flash_Write_Data, 0, sizeof(Flash_Write_Data));
		Flash_Write_Data[0] = 510;
		Flash_Write_Data[1] = 560;
		Flash_Write_Data[2] = 700;
		Flash_Write_Data[3] = 715;
		Flash_Write_Data[4] = 500;
		Flash_Write_Data[5] = 525;
		Flash_Write_Data[6] = 510;
		Flash_Write_Data[7] = 545;
		if(Flash_Write(len, Flash_Write_Data) != FLASH_SUCCESS)
		{
			Usb_Write_Data("{\"type\":\"flash-write-error\"}\r\n");
		}else{
			Usb_Write_Data("{\"type\":\"flash-write-success\"}\r\n");
		}
	}
	if (memcmp(type, "flash-read", 10) == 0)
	{
		memset(Flash_Read_Data, 0, sizeof(Flash_Read_Data));
		Flash_Read(len, Flash_Read_Data);
		Usb_Write_Data("{\"type\":\"flash-read-success\",\"data\":%d}\r\n", Flash_Read_Data[0]);
	}
	if (memcmp(type, "flash-erase", 11) == 0)
	{
		if(Flash_Erase_Data() != FLASH_SUCCESS)
		{
			Usb_Write_Data("{\"type\":\"flash-erase-error\"}\r\n");
		}else{
			Usb_Write_Data("{\"type\":\"flash-erase-success\"}\r\n");
		}
	}
}
