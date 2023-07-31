/**
 ******************************************************************************
 * @file    io.h
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#ifndef MODULAR_IO
#define MODULAR_IO

#include <stm32f4xx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "usb.h"

#define USER_IO_PE3_READ GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)
#define USER_IO_PH14_READ GPIO_ReadInputDataBit(GPIOH, GPIO_Pin_14)
#define USER_IO_PE9_READ GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9)
#define USER_IO_PH15_READ GPIO_ReadInputDataBit(GPIOH, GPIO_Pin_15)
#define USER_IO_PE10_READ GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10)
#define USER_IO_PI1_READ GPIO_ReadInputDataBit(GPIOI, GPIO_Pin_1)
#define USER_IO_PE12_READ GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12)
#define USER_IO_PI3_READ GPIO_ReadInputDataBit(GPIOI, GPIO_Pin_3)
#define USER_IO_PF2_READ GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_2)
#define USER_IO_PI4_READ GPIO_ReadInputDataBit(GPIOI, GPIO_Pin_4)
#define USER_IO_PF11_READ GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_11)
#define USER_IO_PI8_READ GPIO_ReadInputDataBit(GPIOI, GPIO_Pin_8)
#define USER_IO_PF12_READ GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_12)
#define USER_IO_PI9_READ GPIO_ReadInputDataBit(GPIOI, GPIO_Pin_9)
#define USER_IO_PF13_READ GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_13)
#define USER_IO_PI10_READ GPIO_ReadInputDataBit(GPIOI, GPIO_Pin_10)
#define USER_IO_PF15_READ GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_15)
#define USER_IO_PI11_READ GPIO_ReadInputDataBit(GPIOI, GPIO_Pin_11)

#define USER_IO_PE3_LOW() GPIO_ResetBits(GPIOE, GPIO_Pin_3)
#define USER_IO_PE3_HIGH() GPIO_SetBits(GPIOE, GPIO_Pin_3)
#define USER_IO_PE3_TOGGLE() GPIO_ToggleBits(GPIOE, GPIO_Pin_3)

#define USER_IO_PH14_LOW() GPIO_ResetBits(GPIOH, GPIO_Pin_14)
#define USER_IO_PH14_HIGH() GPIO_SetBits(GPIOH, GPIO_Pin_14)
#define USER_IO_PH14_TOGGLE() GPIO_ToggleBits(GPIOH, GPIO_Pin_14)

#define USER_IO_PE9_LOW() GPIO_ResetBits(GPIOE, GPIO_Pin_9)
#define USER_IO_PE9_HIGH() GPIO_SetBits(GPIOE, GPIO_Pin_9)
#define USER_IO_PE9_TOGGLE() GPIO_ToggleBits(GPIOE, GPIO_Pin_9)

#define USER_IO_PH15_LOW() GPIO_ResetBits(GPIOH, GPIO_Pin_15)
#define USER_IO_PH15_HIGH() GPIO_SetBits(GPIOH, GPIO_Pin_15)
#define USER_IO_PH15_TOGGLE() GPIO_ToggleBits(GPIOH, GPIO_Pin_15)

#define USER_IO_PE10_LOW() GPIO_ResetBits(GPIOE, GPIO_Pin_10)
#define USER_IO_PE10_HIGH() GPIO_SetBits(GPIOE, GPIO_Pin_10)
#define USER_IO_PE10_TOGGLE() GPIO_ToggleBits(GPIOE, GPIO_Pin_10)

#define USER_IO_PI1_LOW() GPIO_ResetBits(GPIOI, GPIO_Pin_1)
#define USER_IO_PI1_HIGH() GPIO_SetBits(GPIOI, GPIO_Pin_1)
#define USER_IO_PI1_TOGGLE() GPIO_ToggleBits(GPIOI, GPIO_Pin_1)

#define USER_IO_PE12_LOW() GPIO_ResetBits(GPIOE, GPIO_Pin_12)
#define USER_IO_PE12_HIGH() GPIO_SetBits(GPIOE, GPIO_Pin_12)
#define USER_IO_PE12_TOGGLE() GPIO_ToggleBits(GPIOE, GPIO_Pin_12)

#define USER_IO_PI3_LOW() GPIO_ResetBits(GPIOI, GPIO_Pin_3)
#define USER_IO_PI3_HIGH() GPIO_SetBits(GPIOI, GPIO_Pin_3)
#define USER_IO_PI3_TOGGLE() GPIO_ToggleBits(GPIOI, GPIO_Pin_3)

#define USER_IO_PF2_LOW() GPIO_ResetBits(GPIOF, GPIO_Pin_2)
#define USER_IO_PF2_HIGH() GPIO_SetBits(GPIOF, GPIO_Pin_2)
#define USER_IO_PF2_TOGGLE() GPIO_ToggleBits(GPIOF, GPIO_Pin_2)

#define USER_IO_PI4_LOW() GPIO_ResetBits(GPIOI, GPIO_Pin_4)
#define USER_IO_PI4_HIGH() GPIO_SetBits(GPIOI, GPIO_Pin_4)
#define USER_IO_PI4_TOGGLE() GPIO_ToggleBits(GPIOI, GPIO_Pin_4)

#define USER_IO_PF11_LOW() GPIO_ResetBits(GPIOF, GPIO_Pin_11)
#define USER_IO_PF11_HIGH() GPIO_SetBits(GPIOF, GPIO_Pin_11)
#define USER_IO_PF11_TOGGLE() GPIO_ToggleBits(GPIOF, GPIO_Pin_11)

#define USER_IO_PI8_LOW() GPIO_ResetBits(GPIOI, GPIO_Pin_8)
#define USER_IO_PI8_HIGH() GPIO_SetBits(GPIOI, GPIO_Pin_8)
#define USER_IO_PI8_TOGGLE() GPIO_ToggleBits(GPIOI, GPIO_Pin_8)

#define USER_IO_PF12_LOW() GPIO_ResetBits(GPIOF, GPIO_Pin_12)
#define USER_IO_PF12_HIGH() GPIO_SetBits(GPIOF, GPIO_Pin_12)
#define USER_IO_PF12_TOGGLE() GPIO_ToggleBits(GPIOF, GPIO_Pin_12)

#define USER_IO_PI9_LOW() GPIO_ResetBits(GPIOI, GPIO_Pin_9)
#define USER_IO_PI9_HIGH() GPIO_SetBits(GPIOI, GPIO_Pin_9)
#define USER_IO_PI9_TOGGLE() GPIO_ToggleBits(GPIOI, GPIO_Pin_9)

#define USER_IO_PF13_LOW() GPIO_ResetBits(GPIOF, GPIO_Pin_13)
#define USER_IO_PF13_HIGH() GPIO_SetBits(GPIOF, GPIO_Pin_13)
#define USER_IO_PF13_TOGGLE() GPIO_ToggleBits(GPIOF, GPIO_Pin_13)

#define USER_IO_PI10_LOW() GPIO_ResetBits(GPIOI, GPIO_Pin_10)
#define USER_IO_PI10_HIGH() GPIO_SetBits(GPIOI, GPIO_Pin_10)
#define USER_IO_PI10_TOGGLE() GPIO_ToggleBits(GPIOI, GPIO_Pin_10)

#define USER_IO_PF15_LOW() GPIO_ResetBits(GPIOF, GPIO_Pin_15)
#define USER_IO_PF15_HIGH() GPIO_SetBits(GPIOF, GPIO_Pin_15)
#define USER_IO_PF15_TOGGLE() GPIO_ToggleBits(GPIOF, GPIO_Pin_15)

#define USER_IO_PI11_LOW() GPIO_ResetBits(GPIOI, GPIO_Pin_11)
#define USER_IO_PI11_HIGH() GPIO_SetBits(GPIOI, GPIO_Pin_11)
#define USER_IO_PI11_TOGGLE() GPIO_ToggleBits(GPIOI, GPIO_Pin_11)

void Io_Model(int channel, char *mode);

void Io_State(int channel, char *state);

void Io_Usb_Callback(char *type, int channel, char *mode, char *state);

#endif
