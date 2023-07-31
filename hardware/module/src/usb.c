/**
 ******************************************************************************
 * @file    usb.c
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#include "usb.h"

__ALIGN_BEGIN USB_OTG_CORE_HANDLE USB_OTG_dev __ALIGN_END;

u8 Usb_Write_Buffer[1024];

void Usb_Init(void)
{
    USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &USBD_CDC_cb, &USR_cb);
}

void Usb_Read_Data(uint8_t *pbuf, uint32_t buf_len)
{
    DCD_EP_PrepareRx(&USB_OTG_dev, CDC_OUT_EP, pbuf, buf_len);
}

void Usb_Send_Data(uint8_t *pbuf, uint32_t buf_len)
{
    VCP_SendData(&USB_OTG_dev, pbuf, buf_len);
}

void Usb_Write_Data(char *fmt, ...)
{
    u16 i;
    va_list ap;
    va_start(ap, fmt);
    vsprintf((char *)Usb_Write_Buffer, fmt, ap);
    va_end(ap);
    i = strlen((const char *)Usb_Write_Buffer);
    VCP_SendData(&USB_OTG_dev, Usb_Write_Buffer, i);
}

uint8_t Usb_Read_State(void)
{
    uint8_t status = 5;
    status = USB_OTG_dev.dev.device_state;
    return status;
}
