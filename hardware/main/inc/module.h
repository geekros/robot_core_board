/**
 ******************************************************************************
 * @file    module.h
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#ifndef MODULAR
#define MODULAR

typedef struct
{
    char *type;
} Serial_Data_Struct;

extern Serial_Data_Struct Serial_Read_Data;

void Module_Handle(char *serial_task_buffer);

void Get_Version(void);

#endif
