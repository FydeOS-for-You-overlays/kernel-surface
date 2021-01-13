/*
* Copyright 1998-2014 VIA Technologies, Inc. All Rights Reserved.
* Copyright 2001-2014 S3 Graphics, Inc. All Rights Reserved.
* Copyright 2013-2017 Shanghai Zhaoxin Semiconductor Co., Ltd. All Rights Reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sub license,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice (including the
* next paragraph) shall be included in all copies or substantial portions
* of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
* THE AUTHOR(S) OR COPYRIGHT HOLDER(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/

/*****************************************************************************
** DESCRIPTION:
** Hw independent and chip independent functions and parameters.
**
** NOTE:
** All outside head files should be included here.
******************************************************************************/

#ifndef _CBIOS_SHARE_H_
#define _CBIOS_SHARE_H_

#ifdef __LINUX__
#define GCC_BUILD_CBIOS 1
#endif

#ifndef GCC_BUILD_CBIOS
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#pragma warning(disable:4311)
#ifndef  inline
#define  inline  __inline
#endif
#ifndef  __func__
#define  __func__  __FUNCTION__
#endif
#else
#ifndef __LINUX__
#include "gcc_stdarg.h"
#endif
#endif

#include "../CBios.h"

#include "CBiosTypes.h"
#include "CBIOSVER.H"

#ifdef __LINUX__
#define FUNCTION_NAME __func__
#else
#define FUNCTION_NAME __FUNCTION__
#endif

#ifdef __LINUX__
#define LINE_NUM __LINE__
#else
#define LINE_NUM __LINE__
#endif

#if defined(DBG) && defined(WIN32)
#ifndef ASSERT
#define ASSERT(x) if(!(x)) __debugbreak()
#endif
#else
#define ASSERT(a)
#endif

typedef enum _CBIOS_BOARD_VERSION
{
    CBIOS_BOARD_VERSION_0 = 0,
    CBIOS_BOARD_VERSION_1 = 1,
    CBIOS_BOARD_VERSION_2 = 2,
    CBIOS_BOARD_VERSION_EVT = 3,
    CBIOS_BOARD_VERSION_MAX,
}CBIOS_BOARD_VERSION;

typedef enum _CBIOS_ACTIVE_TYPE   {
    CBIOS_TYPE_NONE        = 0x00,
    CBIOS_TYPE_CRT         = 0x01,
    CBIOS_TYPE_PANEL       = 0x02,
    CBIOS_TYPE_TV          = 0x04,
    CBIOS_TYPE_HDTV        = 0x08,
    CBIOS_TYPE_DVI2        = 0x10,
    CBIOS_TYPE_DVO         = 0x20,
    CBIOS_TYPE_CRT2        = 0x40,
    CBIOS_TYPE_DUOVIEW     = 0x80,
    CBIOS_TYPE_PANEL2      = 0x100,
    CBIOS_TYPE_HDMI3       = 0x200,
    CBIOS_TYPE_DVI3        = 0x400,
    CBIOS_TYPE_DVI4        = 0x800,
    CBIOS_TYPE_DSI         = 0x1000,
    CBIOS_TYPE_MHL         = 0x2000,
    CBIOS_TYPE_HDMI4       = 0x4000,
    CBIOS_TYPE_DP5         = 0x8000,
    CBIOS_TYPE_DP6         = 0x10000,
    CBIOS_TYPE_PANEL3      = 0x20000,
    CBIOS_TYPE_TV2         = 0x40000,
    CBIOS_TYPE_HDTV2       = 0x80000,
} CBIOS_ACTIVE_TYPE, *PCBIOS_ACTIVE_TYPE;

#define CBIOS_BOARD_VERSION_DEFAULT CBIOS_BOARD_VERSION_1

#ifndef CBIOSDEBUGMESSAGEMAXBYTES
#define CBIOSDEBUGMESSAGEMAXBYTES 256
#endif

#ifndef CALLBACK_cbVsnprintf
#ifdef  __LINUX__
typedef CBIOS_S32     (*CALLBACK_cbVsnprintf)(PCBIOS_CHAR buf, CBIOS_U32 size, PCBIOS_CHAR fmt,...);
#else
typedef CBIOS_S32     (*CALLBACK_cbVsnprintf)(PCBIOS_CHAR buf, CBIOS_U32 size, PCBIOS_CHAR fmt, va_list args);
#endif
#endif

#define ELT2K_HARDCODE_DP5          0
#define ELT2K_HARDCODE_DSI_CMDMODE  0
#define ELT2K_HARDCODE_DSI_MHL      0

/******* these functions must be implemented outside *******/
/* debug print function */

#define     DBG_LEVEL_ERROR         0
#define     DBG_LEVEL_WARNING       1
#define     DBG_LEVEL_INFO          2
#define     DBG_LEVEL_DEBUG         3
#define     DBG_LEVEL_TRACE         4

#define     GENERIC_MODULE          (1 << 8)
#define     MHL_MODULE              (2 << 8)
#define     DSI_MODULE              (4 << 8)
#define     HDMI_MODULE             (8 << 8)
#define     DP_MODULE               (16 << 8)

#define     STD_OUTPUT   (0 << 24)
#define     BACK_OUTPUT  (1<< 24)

#define     MAKE_LEVEL(Module, Level)  (Module##_MODULE + DBG_LEVEL_##Level)
#define     MAKE_LEVEL_EX(Out, Module, Level) (Out##_OUTPUT + Module##_MODULE + DBG_LEVEL_##Level)

#define cbTraceEnter(Module)  cbDebugPrint((MAKE_LEVEL(Module, TRACE), "%s: Enter\n", __func__))
#define cbTraceExit(Module)   cbDebugPrint((MAKE_LEVEL(Module, TRACE), "%s: Exit\n", __func__))

//debug print level
#ifdef __LINUX__
#define     DBG_LEVEL_ERROR_MSG     2
#define     DBG_LEVEL_CHIP_INFO     0
#define     DBG_LEVEL_BIOS_VERSION  0
#define     DBG_LEVEL_MODE_INFO     0
#define     DBG_LEVEL_DEVICE_INFO   0
#define     DBG_LEVEL_DEBUG_MSG     1 
#else
#define     DBG_LEVEL_ERROR_MSG     0
#define     DBG_LEVEL_CHIP_INFO     0
#define     DBG_LEVEL_BIOS_VERSION  0
#define     DBG_LEVEL_MODE_INFO     0
#define     DBG_LEVEL_DEVICE_INFO   0
#define     DBG_LEVEL_DEBUG_MSG     1 
#endif

#define sizeofarray(a) (sizeof(a)/sizeof(a[0]))
#define SIZEOF_STRUCT_TILL_MEMBER(MY_STRUCT_VAR, MY_MEMBER_VAR)\
    ((CBIOS_U32)((PCBIOS_CHAR)(&(MY_STRUCT_VAR->MY_MEMBER_VAR)) - (PCBIOS_CHAR)(((MY_STRUCT_VAR))) + (sizeof(MY_STRUCT_VAR->MY_MEMBER_VAR))))

#define container_of(ptr, sample, member) \
    (((PCBIOS_CHAR)(ptr) == CBIOS_NULL) ? CBIOS_NULL : (PCBIOS_VOID)((PCBIOS_CHAR)(ptr) - ((PCBIOS_CHAR)(&(((sample)(0))->member)) - (PCBIOS_CHAR)(0))))

#ifndef MORE_THAN_1BIT
#define MORE_THAN_1BIT(x)       ( (CBIOS_BOOL)( ((x) - 1) & (x) ) )
#endif

typedef enum _CBIOS_ROUND_METHOD
{
    ROUND_DOWN = 0,
    ROUND_UP,
    ROUND_NEAREST
}CBIOS_ROUND_METHOD;

#ifndef  __LINUX__
CBIOS_VOID  cbPrintMessage(CBIOS_U32 DebugPrintLevel, CBIOS_CHAR *DebugMessage, ...);
#endif

CBIOS_U32  cbAddPrefix(CBIOS_U32 Level, CBIOS_UCHAR* pBuffer);
CBIOS_VOID  cbPrintWithDbgFlag(CBIOS_U32 DbgFlag, CBIOS_UCHAR* pBuffer);
CBIOS_STATUS  cbDbgLevelCtl(PCBIOS_DBG_LEVEL_CTRL pDbgLevelCtl);
CBIOS_UCHAR*   cbGetDebugBuffer(CBIOS_U32  DbgFlag);
CBIOS_VOID  cbReleaseDebugBuffer(CBIOS_VOID);
CBIOS_VOID cbDelayMilliSeconds(CBIOS_U32 Milliseconds);
CBIOS_BOOL  cbItoA(CBIOS_U32 ulValue, CBIOS_U8 *pStr, CBIOS_U8 byRadix, CBIOS_U32 ulLength);
CBIOS_U32   cbStrLen(CBIOS_UCHAR * pStrSrc);
PCBIOS_UCHAR cbStrCat(CBIOS_UCHAR *pStrDst, CBIOS_UCHAR * pStrSrc);
CBIOS_U32 cbRound(CBIOS_U32 Dividend, CBIOS_U32 Divisor, CBIOS_ROUND_METHOD RoundMethod);
CBIOS_BOARD_VERSION cbGetBoardVersion(PCBIOS_VOID pvcbe);
CBIOS_STATUS cbGetExtensionSize(CBIOS_U32 *pulExtensionSize);

#ifdef __BIG_ENDIAN__
static inline CBIOS_U16 cb_swab16(CBIOS_U16 x)
{
    CBIOS_U16 temp = ((x & 0x00ffu) << 8) |
                     ((x & 0xff00u) >> 8);
    return temp;
}

static inline CBIOS_U32 cb_swab32(CBIOS_U32 x)
{
    CBIOS_U32 temp = ((x & 0x000000ff) << 24) |
                     ((x & 0x0000ff00) <<  8) |
                     ((x & 0x00ff0000) >>  8) |
                     ((x & 0xff000000) >> 24);
    return temp;
}
#else
#define cb_swab16(x) x
#define cb_swab32(x) x
#endif

#ifdef __LINUX__

#define cbstrcmp(s1, s2)       0
#define cbstrcpy(s1, s2)       CBIOS_NULL
#define cbstrncmp(s1, s2, n)   0
#define cbmemset(s1, v, n)     CBIOS_NULL
#define cbmemcpy(s1, s2, n)    CBIOS_NULL
#define cbmemcmp(s1, s2, n)    0
#define cbdo_div(a, b)         0
#define cbvsprintf(s, f, ...)  0

#else

#define cbstrcmp  strcmp
#define cbstrcpy  strcpy
#define cbstrncmp strncmp
#define cbmemset  memset
#define cbmemcpy  memcpy
#define cbmemcmp  memcmp
#define cbdo_div(a, b) ((a)/(b))

#define cbvsprintf vsprintf

#endif

#endif /* _CBIOS_SHARE_H_ */

