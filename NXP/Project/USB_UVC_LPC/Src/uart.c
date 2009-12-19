/******************** (C) COPYRIGHT 2009 developer.arm7   **********************
* File Name          : uart.c
* Author             : Xu Mingfeng
* Version            : V1.0.0
* Date               : 2009-10-28
* Description        : This file provides uart drivers.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC23xx.H"
#include "type.h"
#include "uart.h"
#include "target.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : UART_Init
* Description    : Init UART
* Input          : baudrate
* Output         : None.
* Return         : 0: SUCCESS.
*******************************************************************************/
int UART_Init(DWORD PortNum,DWORD baudrate)
{
  DWORD Fdiv;

  if(PortNum == 0)
  {
	  PINSEL0 = (PINSEL0 & (~0x0F)) | 0x05; /* RxD0 and TxD0 */
    U0LCR   = 0x83;		                    /* 8 bits, no Parity, 1 Stop bit */
    Fdiv    = ( Fpclk / 16 ) / baudrate ;	/*baud rate */
    U0DLM   = Fdiv / 256;							
    U0DLL   = Fdiv % 256;
	  U0LCR   = 0x03;		                    /* DLAB = 0 */
  }
  else if(PortNum == 1)
  {
	  PINSEL0 |= 0x40000000;	/* Enable TxD1 P0.15 */
	  PINSEL1 |= 0x00000001;	/* Enable RxD1 P0.16 */
    U1LCR    = 0x83;		                    /* 8 bits, no Parity, 1 Stop bit */
    Fdiv     = ( Fpclk / 16 ) / baudrate ;	/*baud rate */
    U1DLM    = Fdiv / 256;							
    U1DLL    = Fdiv % 256;
	  U1LCR    = 0x03;		                    /* DLAB = 0 */	  
  }
  else
    return 1;
  return 0;
}

/*******************************************************************************
* Function Name  : sendchar
* Description    : send char via uart0
* Input          : ch
* Output         : None.
* Return         : None.
*******************************************************************************/
int sendchar(int ch)
{
	U1THR = ch;
	while ((U1LSR & 0x40) == 0); /* 等待数据发送完毕 */
	return 0;
}

/*******************************************************************************
* Function Name  : getkey
* Description    : get key via uart.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int getkey(void)
{
  return 0;
}

/******************* (C) COPYRIGHT 2009 developer.arm7   *******END OF FILE****/
