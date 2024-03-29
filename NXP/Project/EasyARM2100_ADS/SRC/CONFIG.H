/****************************************Copyright (c)**************************************************
**                               广州周立功单片机发展有限公司
**                                     研    究    所
**                                        产品一部 
**
**                                 http://www.zlgmcu.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: includes.h
**创   建   人: 陈明计
**最后修改日期: 2004年2月2日
**描        述: 用户配置文件
**
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: 陈明计
** 版  本: 1.0
** 日　期: 2004年2月2日
** 描　述: 原始版本
**
**------------------------------------------------------------------------------------------------------
** 修改人:
** 版  本:
** 日　期:
** 描　述:
**
**--------------当前版本修订------------------------------------------------------------------------------
** 修改人: 
** 日　期:
** 描　述:
**
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
//这一段无需改动
#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef unsigned char  uint8;                   /* 无符号8位整型变量                        */
typedef signed   char  int8;                    /* 有符号8位整型变量                        */
typedef unsigned short uint16;                  /* 无符号16位整型变量                       */
typedef signed   short int16;                   /* 有符号16位整型变量                       */
typedef unsigned int   uint32;                  /* 无符号32位整型变量                       */
typedef signed   int   int32;                   /* 有符号32位整型变量                       */
typedef float          fp32;                    /* 单精度浮点数（32位长度）                 */
typedef double         fp64;                    /* 双精度浮点数（64位长度）                 */


/********************************/
/*      ARM的特殊代码           */
/********************************/
//这一段无需改动

#include    "LPC2294.h"


/********************************/
/*     应用程序配置             */
/********************************/
//以下根据需要改动

/********************************/
/*     本例子的配置             */
/********************************/
/* 系统设置, Fosc、Fcclk、Fcco、Fpclk必须定义*/
#define Fosc            11059200                    //晶振频率,10MHz~25MHz，应当与实际一至
#define Fcclk           (Fosc * 4)                  //系统频率，必须为Fosc的整数倍(1~32)，且<=60MHZ
#define Fcco            (Fcclk * 4)                 //CCO频率，必须为Fcclk的2、4、8、16倍，范围为156MHz~320MHz
#define Fpclk           (Fcclk / 4) * 1             //VPB时钟频率，只能为(Fcclk / 4)的1、2、4倍

#include    "target.h"              //这一句不能删除

/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
