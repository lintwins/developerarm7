/*----------------------------------------------------------------------------
 *      U S B  -  K e r n e l
 *----------------------------------------------------------------------------
 *      Name:    USBUSER.C
 *      Purpose: USB Custom User Module
 *      Version: V1.10
 *----------------------------------------------------------------------------
 *      This file is part of the uVision/ARM development tools.
 *      This software may only be used under the terms of a valid, current,
 *      end user licence from KEIL for a compatible version of KEIL software
 *      development tools. Nothing else gives you the right to use it.
 *
 *      Copyright (c) 2005-2007 Keil Software.
 *---------------------------------------------------------------------------*/

#include <string.h>
#include "LPC23xx.H"                                  /* LPC23xx definitions */

#include "type.h"

#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "usbuser.h"
#include "uvcuser.h"

#define _JPG_GLOBAL_
#include "JGP_Data.h"

volatile DWORD TestCnt;
volatile DWORD JPG_Cnt;
volatile DWORD Buf_Size;
volatile DWORD PTS_Value;
volatile DWORD SCR_Value;
BYTE SOF_Event_Buf[EP3_MAX_PACKET];

/*
 *  USB Power Event Callback
 *   Called automatically on USB Power Event
 *    Parameter:       power: On(TRUE)/Off(FALSE)
 */

#if USB_POWER_EVENT
void USB_Power_Event (BOOL  power) {
}
#endif


/*
 *  USB Reset Event Callback
 *   Called automatically on USB Reset Event
 */

#if USB_RESET_EVENT
void USB_Reset_Event (void) {
  USB_ResetCore();
}
#endif


/*
 *  USB Suspend Event Callback
 *   Called automatically on USB Suspend Event
 */

#if USB_SUSPEND_EVENT
void USB_Suspend_Event (void) {
}
#endif


/*
 *  USB Resume Event Callback
 *   Called automatically on USB Resume Event
 */

#if USB_RESUME_EVENT
void USB_Resume_Event (void) {
}
#endif


/*
 *  USB Remote Wakeup Event Callback
 *   Called automatically on USB Remote Wakeup Event
 */

#if USB_WAKEUP_EVENT
void USB_WakeUp_Event (void) {
}
#endif


/*
 *  USB Start of Frame Event Callback
 *   Called automatically on USB Start of Frame Event
 */
#if USB_SOF_EVENT
void USB_SOF_Event (void)
{
  /* Payload header - SOF_Event_Buf[0~1] */
  if(JPG_Cnt == 0) /* Start of Frame */
  {
    SOF_Event_Buf[0]  = 0x0C; /* Header Length */
    SOF_Event_Buf[1] &= 0x01; /* FID */
    SOF_Event_Buf[1] ^= 0x01; /* FID */
    SOF_Event_Buf[10] = 0x00; /* Reserved */
    SOF_Event_Buf[11] = 0x00; /* Reserved */
  }
  else
  {
    /* The last packet of jpg */
    if((JPG_size - JPG_Cnt) <= (EP3_MAX_PACKET - 2))
      SOF_Event_Buf[1] |= 0x02; /* EOF - End of Frame */
  }

  /* PTS - Presentation Time stamp */
  PTS_Value        += 0xBB84;
  SOF_Event_Buf[2]  = (BYTE)(PTS_Value);
  SOF_Event_Buf[3]  = (BYTE)(PTS_Value >> 8);
  SOF_Event_Buf[4]  = (BYTE)(PTS_Value >> 16);
  SOF_Event_Buf[5]  = (BYTE)(PTS_Value >> 24);

  /* SCR - Source Clock Reference */
  SCR_Value         = PTS_Value + 0x20;
  SOF_Event_Buf[6]  = (BYTE)(SCR_Value);
  SOF_Event_Buf[7]  = (BYTE)(SCR_Value >> 8);
  SOF_Event_Buf[8]  = (BYTE)(SCR_Value >> 16);
  SOF_Event_Buf[9]  = (BYTE)(SCR_Value >> 24);

  /* Copy data and send */
  Write_To_Buf();
  USB_WriteEP(0x83,(BYTE *)SOF_Event_Buf,Buf_Size);
}
#endif


/*
 *  USB Error Event Callback
 *   Called automatically on USB Error Event
 *    Parameter:       error: Error Code
 */

#if USB_ERROR_EVENT
void USB_Error_Event (DWORD error) {
}
#endif


/*
 *  USB Set Configuration Event Callback
 *   Called automatically on USB Set Configuration Request
 */

#if USB_CONFIGURE_EVENT
void USB_Configure_Event (void) {

  if (USB_Configuration) {                  /* Check if USB is configured */
    /* add your code here */
  }
}
#endif


/*
 *  USB Set Interface Event Callback
 *   Called automatically on USB Set Interface Request
 */

#if USB_INTERFACE_EVENT
void USB_Interface_Event (void) {
}
#endif


/*
 *  USB Set/Clear Feature Event Callback
 *   Called automatically on USB Set/Clear Feature Request
 */

#if USB_FEATURE_EVENT
void USB_Feature_Event (void) {
}
#endif


#define P_EP(n) ((USB_EP_EVENT & (1 << (n))) ? USB_EndPoint##n : NULL)

/* USB Endpoint Events Callback Pointers */
void (* const USB_P_EP[16]) (DWORD event) = {
  P_EP(0),
  P_EP(1),
  P_EP(2),
  P_EP(3),
  P_EP(4),
  P_EP(5),
  P_EP(6),
  P_EP(7),
  P_EP(8),
  P_EP(9),
  P_EP(10),
  P_EP(11),
  P_EP(12),
  P_EP(13),
  P_EP(14),
  P_EP(15),
};


/*
 *  USB Endpoint 1 Event Callback
 *   Called automatically on USB Endpoint 1 Event
 *    Parameter:       event
 */

void USB_EndPoint1 (DWORD event) {
}


/*
 *  USB Endpoint 2 Event Callback
 *   Called automatically on USB Endpoint 2 Event
 *    Parameter:       event
 */

void USB_EndPoint2 (DWORD event) {
}


/*
 *  USB Endpoint 3 Event Callback
 *   Called automatically on USB Endpoint 3 Event
 *    Parameter:       event
 */

void USB_EndPoint3 (DWORD event) {
}


/*
 *  USB Endpoint 4 Event Callback
 *   Called automatically on USB Endpoint 4 Event
 *    Parameter:       event
 */

void USB_EndPoint4 (DWORD event) {
}


/*
 *  USB Endpoint 5 Event Callback
 *   Called automatically on USB Endpoint 5 Event
 *    Parameter:       event
 */

void USB_EndPoint5 (DWORD event) {
}


/*
 *  USB Endpoint 6 Event Callback
 *   Called automatically on USB Endpoint 6 Event
 *    Parameter:       event
 */

void USB_EndPoint6 (DWORD event) {
}


/*
 *  USB Endpoint 7 Event Callback
 *   Called automatically on USB Endpoint 7 Event
 *    Parameter:       event
 */

void USB_EndPoint7 (DWORD event) {
}


/*
 *  USB Endpoint 8 Event Callback
 *   Called automatically on USB Endpoint 8 Event
 *    Parameter:       event
 */

void USB_EndPoint8 (DWORD event) {
}


/*
 *  USB Endpoint 9 Event Callback
 *   Called automatically on USB Endpoint 9 Event
 *    Parameter:       event
 */

void USB_EndPoint9 (DWORD event) {
}


/*
 *  USB Endpoint 10 Event Callback
 *   Called automatically on USB Endpoint 10 Event
 *    Parameter:       event
 */

void USB_EndPoint10 (DWORD event) {
}


/*
 *  USB Endpoint 11 Event Callback
 *   Called automatically on USB Endpoint 11 Event
 *    Parameter:       event
 */

void USB_EndPoint11 (DWORD event) {
}


/*
 *  USB Endpoint 12 Event Callback
 *   Called automatically on USB Endpoint 12 Event
 *    Parameter:       event
 */

void USB_EndPoint12 (DWORD event) {
}


/*
 *  USB Endpoint 13 Event Callback
 *   Called automatically on USB Endpoint 13 Event
 *    Parameter:       event
 */

void USB_EndPoint13 (DWORD event) {
}


/*
 *  USB Endpoint 14 Event Callback
 *   Called automatically on USB Endpoint 14 Event
 *    Parameter:       event
 */

void USB_EndPoint14 (DWORD event) {
}


/*
 *  USB Endpoint 15 Event Callback
 *   Called automatically on USB Endpoint 15 Event
 *    Parameter:       event
 */

void USB_EndPoint15 (DWORD event) {
}

/*
 * Write data to buffer
 */
void Write_To_Buf(void)
{
  if((JPG_size - JPG_Cnt) > (EP3_MAX_PACKET - PAYLOAD_HEADER_SIZE))
  {
    memcpy((void *)(SOF_Event_Buf + PAYLOAD_HEADER_SIZE),(const void *)(JPG_data + JPG_Cnt),EP3_MAX_PACKET - PAYLOAD_HEADER_SIZE);
    JPG_Cnt += (EP3_MAX_PACKET - PAYLOAD_HEADER_SIZE);
    Buf_Size = EP3_MAX_PACKET;
  }
  else
  {
    memcpy((void *)(SOF_Event_Buf + PAYLOAD_HEADER_SIZE),(const void *)(JPG_data + JPG_Cnt),JPG_size - JPG_Cnt);
    JPG_Cnt = 0;
    Buf_Size = JPG_size - JPG_Cnt + PAYLOAD_HEADER_SIZE;
    TestCnt++;
  }
}

