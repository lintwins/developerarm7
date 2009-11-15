/****************************************************************************
* 文件名：LEDHEX.C
* 功能：LED数码管显示0-F字符，同时控制LED1、LED2、LED3、LED4显示对应的16进行值。
* 说明：将跳线器JP3、JP4、JP7短接。
****************************************************************************/
#include  "config.h"

#define   SPI_CS	(1<<29)			/* P0.29 */
#define   SPI_DATA	(1<<6)			/* P0.6 */
#define   SPI_CLK	(1<<4)			/* P0.4 */

#define   BEEP      (1<<7)      	/* P0.7为蜂鸣器控制 */

#define   SPI_IOCON	(SPI_CS|SPI_DATA|SPI_CLK)		/* SPI接口的I/O设置字 */
#define   LED_IOCON	(0x0F<<22)						/* LED1-4的I/O设置字 */


/****************************************************************************
* 名称：DelayNS()
* 功能：长软件延时
* 入口参数：dly		延时参数，值越大，延时越久
* 出口参数：无
****************************************************************************/
void  DelayNS(uint32  dly)
{  uint32  i;

   for(; dly>0; dly--) 
      for(i=0; i<50000; i++);
}


/****************************************************************************
* 名称：HC595_SendDat()
* 功能：向74HC595发送一字节数据
* 入口参数：dat		要发送的数据
* 出口参数：无
* 说明：发送数据时，高位先发送。
****************************************************************************/
void  HC595_SendDat(uint8 dat)
{  uint8  i;

   IO0CLR = SPI_CS;			    // SPI_CS = 0
   for(i=0; i<8; i++)			// 发送8位数据
   {  IO0CLR = SPI_CLK;			// SPI_CLK = 0
      /* 设置SPI的DATA输出值 */
      if( (dat&0x80)!=0 ) IO0SET = SPI_DATA;
        else IO0CLR = SPI_DATA;
      dat <<= 1;
      IO0SET = SPI_CLK;			// SPI_CLK = 1
   }
   
   IO0SET = SPI_CS;			    // SPI_CS = 1，输出显示数据
}

/* 此表为0--F的字模 */
const uint8  DISP_TAB[16] = { 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90, 
                                 0x88,0x83,0xC6,0xA1,0x86,0x8E };
/****************************************************************************
* 名称：main()
* 功能：控制LED数码管显示，并控制LED1、LED2、LED3、LED4显示。
****************************************************************************/
int  main(void)
{  uint8  i; 		
	
   PINSEL0 = 0x00000000;		// 设置所有管脚连接GPIO
   PINSEL1 = 0x00000000;
   
   DelayNS(10);					// 延时，防止JTAG调试时，芯片复位后蜂鸣器马上蜂鸣(直到重新设置PINSEL0)
   IO0DIR = SPI_IOCON|LED_IOCON|BEEP;	// 设置SPI等控制口为输出
   /* 控制蜂鸣器报警 */
   IO0CLR = BEEP;
   DelayNS(50);					// 延时
   IO0SET = BEEP;		
   while(1)	
   {  for(i=0; i<16; i++)
      {  HC595_SendDat(DISP_TAB[i]);	// 输出LED显示数据
      	 IO0SET = 0x0F<<22;	
      	 IO0CLR = i<<22;		// 设置LED显示输出		 
      	 DelayNS(50);	
      } 
     
   }
   return(0);
}
