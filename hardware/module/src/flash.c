/**
  ******************************************************************************
  * @file    flash.c
  * @author  GEEKROS,  site:www.geekros.com
  ******************************************************************************
*/

#include "flash.h"

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

int Flash_Write(uint32_t len, uint16_t *data)
{
	uint32_t write_addr;
	write_addr = FLASH_SAVE_ADDR;

	FLASH_Unlock();
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
	if (FLASH_COMPLETE != FLASH_EraseSector(Flash_Get_Sector(write_addr), VoltageRange_3))
    {
		return FLASH_ERROR;
	}
	for (int i = 0; i < len; i++)
	{
		if (FLASH_COMPLETE != FLASH_ProgramHalfWord(write_addr, data[i]))
		{
			return FLASH_ERROR;
		}
		write_addr += 2;
	}
	FLASH_Lock();
	return FLASH_SUCCESS;
}

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


int Flash_Erase_Data(void)
{
	FLASH_Unlock();
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
	if (FLASH_COMPLETE != FLASH_EraseSector(Flash_Get_Sector(FLASH_SAVE_ADDR), VoltageRange_3))
    {
		return FLASH_ERROR;
	}
	FLASH_Lock();
	return FLASH_SUCCESS;
}

void Flash_Serial_Callback(cJSON *serial_data)
{

}
