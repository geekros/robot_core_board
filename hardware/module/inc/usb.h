/**
 ******************************************************************************
 * @file    usb.h
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#ifndef MODULE_USB
#define MODULE_USB

#include <stm32f4xx.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <usbd_cdc_vcp.h>
#include <usbd_cdc_core.h>
#include <usbd_usr.h>
#include <usb_conf.h>
#include <usbd_desc.h>
#include <usbd_cdc_vcp.h>

#include "usb.h"
#include "utils.h"

void Usb_Init(void);

void Usb_Read_Data(uint8_t *pbuf, uint32_t buf_len);

void Usb_Send_Data(uint8_t *pbuf, uint32_t buf_len);

void Usb_Write_Data(char *fmt, ...);

uint8_t Usb_Read_State(void);

#endif
