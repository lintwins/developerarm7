/******************** (C) COPYRIGHT 2009 developer.arm7   **********************
* File Name          : uart.h
* Author             : Xu Mingfeng
* Version            : V1.0.0
* Date               : 2009-10-28
* Description        : uart driver.
*
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H
#define __UART_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
int UART_Init(DWORD PortNum,DWORD baudrate);

#endif /* __UART_H */
/******************* (C) COPYRIGHT 2009 developer.arm7   *******END OF FILE****/
