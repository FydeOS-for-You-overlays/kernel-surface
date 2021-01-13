/*
* Copyright 1998-2014 VIA Technologies, Inc. All Rights Reserved.
* Copyright 2001-2014 S3 Graphics, Inc. All Rights Reserved.
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
** CBios display manager interface prototype and parameter define.
**
** NOTE:
** The hw dependent function or structure SHOULD NOT be added to this file.
******************************************************************************/

#ifndef _CBIOS_DISPLAY_MANAGER_H_
#define _CBIOS_DISPLAY_MANAGER_H_

#include "../Device/CBiosDeviceShare.h"

#define CBIOS_STREAM_16BPP_FMTS  (CBIOS_FMT_R5G6B5 | CBIOS_FMT_CRYCBY422_16BIT | CBIOS_FMT_YCRYCB422_16BIT)

#define CBIOS_STREAM_32BPP_FMTS  (CBIOS_FMT_A8R8G8B8 | CBIOS_FMT_A8B8G8R8 | \
                                   CBIOS_FMT_A2R10G10B10 | CBIOS_FMT_A2B10G10R10 | \
                                   CBIOS_FMT_CRYCBY422_32BIT | CBIOS_FMT_YCRYCB422_32BIT | \
                                   CBIOS_FMT_YCBCR8888_32BIT | CBIOS_FMT_YCBCR2101010_32BIT)

#define  CBIOS_STREAM_FMT_YUV_SPACE  (CBIOS_FMT_CRYCBY422_32BIT | CBIOS_FMT_YCRYCB422_32BIT | \
                                                                         CBIOS_FMT_YCBCR8888_32BIT | CBIOS_FMT_YCBCR2101010_32BIT | \
                                                                         CBIOS_FMT_CRYCBY422_16BIT | CBIOS_FMT_YCRYCB422_16BIT)

typedef enum _CBIOS_TIMING_REG_TYPE {
    TIMING_REG_TYPE_CR = 0,
    TIMING_REG_TYPE_SR,
    TIMING_REG_TYPE_MMIO,
} CBIOS_TIMING_REG_TYPE;

#define STREAM_NUM_CHX                 2
#define STREAM_NUM_ZX3K                  4

typedef struct _CBIOS_MODE_SRC_PARA{
    CBIOS_U32    XRes;
    CBIOS_U32    YRes;
}CBIOS_MODE_SRC_PARA, *PCBIOS_MODE_SRC_PARA;

typedef struct _CBIOS_MODE_TARGET_PARA{
    CBIOS_U32    XRes;
    CBIOS_U32    YRes;
    CBIOS_U32    RefRate;
    CBIOS_U32    bInterlace;         /* =0, Set noninterlace mode; = 1, Set interlace mode; */
    CBIOS_U32    AspectRatioFlag;    /* =0, Default aspect ratio */
                                     /* =1, 4:3 aspect ratio*/
                                     /* =2, 16:9 aspect ratio */
    CSC_FORMAT   DevInColorSpace;    /* device csc input color sapce*/
    CBIOS_U32    OutputSignal;       /* =0x1; RGB signal */
                                     /* =0x2; YCbCr422 signal */
                                     /* =0x4; YCbCr444 signal */
                                     /* DP device will also use this attribute, and is called Color format */
}CBIOS_MODE_TARGET_PARA, *PCBIOS_MODE_TARGET_PARA;

typedef struct _CBIOS_MODE_SCALER_PARA{
    CBIOS_U32    XRes;
    CBIOS_U32    YRes;
}CBIOS_MODE_SCALER_PARA, *PCBIOS_MODE_SCALER_PARA;

typedef enum _CBIOS_SCALER_STATUS
{
    DISABLE_SCALER = 0,
    ENABLE_UPSCALER,
    ENABLE_DOWNSCALER,
    INVALID_SCALER_SETTING
}CBIOS_SCALER_STATUS;

typedef struct _CBIOS_DISP_MODE_PARAMS
{
    CBIOS_U32              IGAIndex;
    CBIOS_MODE_SRC_PARA    SrcModePara;
    CBIOS_MODE_TARGET_PARA TargetModePara;
    CBIOS_MODE_SCALER_PARA ScalerPara; 
    CBIOS_SCALER_STATUS    ScalerStatusToUse;
    CBIOS_TIMING_ATTRIB    TargetTiming;
    CSC_FORMAT             IGAOutColorSpace;
    struct
    {
        CBIOS_BOOL IsEnable3DVideo              :1;     // = 1: enable 3D video, = 0: normal 2D mode
        CBIOS_BOOL IsxvYCC                      :1;
        CBIOS_BOOL IsAdobe                      :1;
        CBIOS_BOOL IsBT2020                     :1;
        CBIOS_BOOL IsSingleBuffer               :1;     /* = 1: 3D video data is in a single buffer; =0: 3D video data is in separate two buffers */
        CBIOS_BOOL IsSkipModeSet                :1;
        CBIOS_BOOL IsEnable3DOSDDisparity       :1;     // = 1: 3D OSD Disparity data present
        CBIOS_BOOL IsEnable3DDualView           :1;
        CBIOS_BOOL IsEnable3DIndependentView    :1;
        CBIOS_BOOL Reserved                     :23;    // Reserved for futrue use
    };

    //for HDMI
    CBIOS_3D_STRUCTURE                  Video3DStruct;
    CBIOS_3D_DISPARITY_PARA             Video3DDisparity;
    CBIOS_3D_INDEPENDENT_VIEW           Viedo3DIndependentCaps;
    CBIOS_U8                            VICCode;  
    CBIOS_U8                            PixelRepitition;
    CBIOS_U32                           BitPerComponent;
    CBIOS_COLORIMETRY_DATA              ColorimetryCaps;
    CBIOS_VIDEO_CAPABILITY_DATA         VideoCapability;
}CBIOS_DISP_MODE_PARAMS, *PCBIOS_DISP_MODE_PARAMS;

typedef struct _CBIOS_DISPLAY_MANAGER
{
    CBIOS_U32               IgaCount;
    CBIOS_U32               UpScaleSupport;
    CBIOS_U32               DownScaleIGAMask;
    CBIOS_U32               StreamCount[CBIOS_IGACOUNTS];
    CBIOS_U32               UpScaleStreamMask[CBIOS_IGACOUNTS];
    CBIOS_U32               DownScaleStreamMask[CBIOS_IGACOUNTS];
    CBIOS_ACTIVE_TYPE       ActiveDevices[CBIOS_IGACOUNTS];
    PCBIOS_DISP_MODE_PARAMS pModeParams[CBIOS_IGACOUNTS];
}CBIOS_DISPLAY_MANAGER, *PCBIOS_DISPLAY_MANAGER;

CBIOS_STATUS cbDispMgrInit(PCBIOS_VOID pvcbe);
CBIOS_STATUS cbDispMgrGetActiveDevice(PCBIOS_VOID pvcbe, PCBIOS_DISPLAY_MANAGER pDispMgr, PCIP_ACTIVE_DEVICES pActiveDevices);
CBIOS_STATUS cbDispMgrSetActiveDevice(PCBIOS_VOID pvcbe, PCBIOS_DISPLAY_MANAGER pDispMgr, PCIP_ACTIVE_DEVICES pActiveDevices);
CBIOS_STATUS cbDispMgrGetMode(PCBIOS_VOID pvcbe, PCBIOS_DISPLAY_MANAGER pDispMgr, PCBiosSettingModeParams pModeParams);
CBIOS_STATUS cbDispMgrGetHwCounter(PCBIOS_VOID pvcbe, PCBIOS_GET_HW_COUNTER  pGetCounter);
CBIOS_STATUS cbDispMgrGetModeFromReg(PCBIOS_VOID pvcbe, PCBIOS_DISPLAY_MANAGER pDispMgr, PCBiosSettingModeParams pModeParams);
CBIOS_STATUS cbDispMgrSetMode(PCBIOS_VOID pvcbe, PCBIOS_DEVICE_MANAGER pDevMgr, PCBIOS_DISPLAY_MANAGER pDispMgr, PCBiosSettingModeParams pSettingModeParams);
CBIOS_STATUS cbDispMgrGetDispResource(PCBIOS_VOID pvcbe, PCBIOS_GET_DISP_RESOURCE pGetDispRes);
CBIOS_STATUS cbDispMgrGetDisplayCaps(PCBIOS_VOID pvcbe, PCBIOS_DISPLAY_CAPS pDispCaps);
CBIOS_STATUS cbDispMgrUpdateFrame(PCBIOS_VOID pvcbe, PCBIOS_UPDATE_FRAME_PARA pUpdateFrame);
CBIOS_STATUS cbDispDoCSCAdjust(PCBIOS_VOID pvcbe, PCBIOS_DISPLAY_MANAGER pDispMgr, PCBIOS_CSC_ADJUST_PARA pCSCAdjustPara);
CBIOS_STATUS cbDispMgrCheckSurfaceOnDisplay(PCBIOS_VOID pvcbe, PCBIOS_CHECK_SURFACE_ON_DISP pChkSurfacePara);
CBIOS_STATUS cbDispMgrGetDispAddr(PCBIOS_VOID  pvcbe,  PCBIOS_GET_DISP_ADDR  pGetDispAddr);
CBIOS_STATUS cbDispMgrSetHwCursor(PCBIOS_VOID pvcbe, PCBIOS_CURSOR_PARA pSetCursor);
CBIOS_STATUS cbDispMgrDeInit(PCBIOS_VOID pvcbe);


#endif
