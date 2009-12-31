/*----------------------------------------------------------------------------
 *      Name:    uvcdemo.c
 *      Purpose: USB video class Demo
 *      Version: V1.00
 *----------------------------------------------------------------------------
 *      This file is part of the uVision/ARM development tools.
 *      This software may only be used under the terms of a valid, current,
 *      end user licence from KEIL for a compatible version of KEIL software
 *      development tools. Nothing else gives you the right to use it.
 *
 *      Copyright (c) 2005-2007 Keil Software.
 *---------------------------------------------------------------------------*/

#include "LPC23xx.H"                                  /* LPC23xx definitions */

#include "type.h"

#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "uvc.h"
#include "uvcuser.h"
#include "uvcdemo.h"
#include "LCD.h"
#include "uart.h"
#include "usbuser.h"

#include <stdio.h>

/*----------------------------------------------------------------------------
  Main Program
 *---------------------------------------------------------------------------*/
int main (void) {

  PINSEL10 = 0;                             /* Disable ETM interface */
  FIO2DIR  = LEDMSK;                        /* LED's defined as Outputs */

#if 0
  LCD_init();                               /* Initialize LCD display module */
  LCD_cur_off();
  LCD_cls();
  LCD_puts("MCB2300 USB UVC");
  LCD_puts(" -=www.keil.com=- ");
#endif

  /* init */
  TestCnt = 0;
  JPG_Cnt = 0;
  PTS_Value = 0;
  PicsToggle = 0;
  UART_Init(_UART_USED,115200);
  printf("\r\n#######################################");
  printf("\r\n# USB Video demo");
  printf("\r\n# NXP,LPC2368,2009-12-21");
  printf("\r\n#######################################");
  USB_Init();                               /* USB Initialization */
  USB_Connect(TRUE);                        /* USB Connect */

  /* Wait host configure */
  printf("\r\nWait host configure...");
  while (!USB_Configuration) ;              /* wait until USB is configured */
  printf("\r\nUSB configure done.\n");

  /* Loop forever */
  while (1)
  {
    printf("\rTestCnt = 0x%08x",TestCnt);
  } // end while											   
} // end main ()
