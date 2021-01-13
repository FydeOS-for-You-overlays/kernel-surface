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
** Defines common function pointer for each device port.
** Defines CBIOS_DEVICE_COMMON.
**
** NOTE:
** 
******************************************************************************/

#ifndef _CBIOS_DEVICE_SHARE_H_
#define _CBIOS_DEVICE_SHARE_H_

#include "CBiosShare.h"
#include "../Display/CBiosMode.h"
#include "../Util/CBiosEDID.h"
#include "Port/CBiosDSI.h"
#include "../Display/CBiosPathManager.h"
#include "Monitor/CBiosEDPPanel.h"

#define CBIOS_MAX_DISPLAY_DEVICES_NUM                  32

typedef CBIOS_VOID 
(*PFN_cbDeviceHwInit)(PCBIOS_VOID pvcbe, PCBIOS_VOID pDevCommon);

typedef CBIOS_BOOL
(*PFN_cbDeviceDetect)(PCBIOS_VOID pvcbe, PCBIOS_VOID pDevCommon, CBIOS_BOOL bHardcodeDetected);

typedef CBIOS_VOID 
(*PFN_cbDeviceOnOff)(PCBIOS_VOID pvcbe, PCBIOS_VOID pDevCommon, CBIOS_BOOL bOn);

typedef CBIOS_VOID 
(*PFN_cbQueryMonitorAttribute)(PCBIOS_VOID pvcbe, PCBIOS_VOID pDevCommon, PCBiosMonitorAttribute pMonitorAttribute);

typedef CBIOS_VOID 
(*PFN_cbUpdateDeviceModeInfo)(PCBIOS_VOID pvcbe, PCBIOS_VOID pDevCommon, PCBIOS_VOID pModeParams);

typedef CBIOS_VOID 
(*PFN_cbDeviceSetMode)(PCBIOS_VOID pvcbe, PCBIOS_VOID pDevCommon, PCBIOS_VOID pModeParams);

typedef struct _CBIOS_DEVICE_SIGNATURE
{
    CBIOS_U8 MonitorID[MONITORIDLENGTH];
    CBIOS_U8 ExtFlagChecksum[CBIOS_EDIDMAXBLOCKCOUNT][EXTFLAGCHECKSUMLENTH];
}CBIOS_DEVICE_SIGNATURE, *PCBIOS_DEVICE_SIGNATURE;

typedef struct _CBIOS_DEVICE_COMMON
{
    //Common attribute with fixed value
    struct
    {
        CBIOS_ACTIVE_TYPE           DeviceType;
        CBIOS_MONITOR_TYPE          SupportMonitorType;
        CBIOS_U32                   I2CBus; // real I2C bus used to read EDID from monitor
        CBIOS_U8                    HPDPin;
        PCBIOS_VOID                 pHDCPContext;                  
    };

    //Common attribute with variable value
    struct
    {
        CBIOS_MONITOR_TYPE          CurrentMonitorType;
        CBIOS_U8                    PowerState;
        CBIOS_UCHAR                 EdidData[CBIOS_EDIDDATABYTE];
        CBIOS_EDID_STRUCTURE_DATA   EdidStruct;
        CBIOS_DEVICE_SIGNATURE      ConnectedDevSignature; // stores the signature of real device.
        CBIOS_DISPLAY_SOURCE        DispSource;
        CBIOS_BOOL                  isFakeEdid;
    };

    union
    {
        CBIOS_DSI_PARAMS            DSIDevice;
        CBIOS_EDPPanel_PARAMS       EDPPanelDevice;
    }DeviceParas;

    //common funcs for each device port
    struct
    {
        PFN_cbDeviceHwInit          pfncbDeviceHwInit;
        PFN_cbDeviceDetect          pfncbDeviceDetect;
        PFN_cbDeviceOnOff           pfncbDeviceOnOff;
        PFN_cbDeviceSetMode         pfncbDeviceSetMode;

        PFN_cbQueryMonitorAttribute pfncbQueryMonitorAttribute;
        PFN_cbUpdateDeviceModeInfo  pfncbUpdateDeviceModeInfo;
    };
}CBIOS_DEVICE_COMMON, *PCBIOS_DEVICE_COMMON;

typedef struct _CBIOS_DEVICE_MANAGER
{
    CBIOS_ACTIVE_TYPE    SupportDevices;
    CBIOS_U32            ConnectedDevices;
    PCBIOS_DEVICE_COMMON pDeviceArray[CBIOS_MAX_DISPLAY_DEVICES_NUM];
}CBIOS_DEVICE_MANAGER, *PCBIOS_DEVICE_MANAGER;

#define cbGetDeviceCommon(pDevMgr, Device)      ((pDevMgr)->pDeviceArray[cbConvertDeviceBit2Index(Device)])

static inline void cbInitialModuleList(PCBIOS_MODULE_LIST pModuleList)
{
    pModuleList->DPModule.Type = CBIOS_MODULE_TYPE_DP;
    pModuleList->DPModule.Index = CBIOS_MODULE_INDEX_INVALID;
    pModuleList->MHLModule.Type = CBIOS_MODULE_TYPE_MHL;
    pModuleList->MHLModule.Index = CBIOS_MODULE_INDEX_INVALID;
    pModuleList->HDCPModule.Type = CBIOS_MODULE_TYPE_HDCP;
    pModuleList->HDCPModule.Index = CBIOS_MODULE_INDEX_INVALID;
    pModuleList->HDMIModule.Type = CBIOS_MODULE_TYPE_HDMI;
    pModuleList->HDMIModule.Index = CBIOS_MODULE_INDEX_INVALID;
    pModuleList->HDTVModule.Type = CBIOS_MODULE_TYPE_HDTV;
    pModuleList->HDACModule.Index = CBIOS_MODULE_INDEX_INVALID;
    pModuleList->HDACModule.Type = CBIOS_MODULE_TYPE_HDAC;
    pModuleList->HDTVModule.Index = CBIOS_MODULE_INDEX_INVALID;
    pModuleList->IGAModule.Type = CBIOS_MODULE_TYPE_IGA;
    pModuleList->IGAModule.Index = CBIOS_MODULE_INDEX_INVALID;
}

#define IS_SUPPORT_4K_MODE        1

extern CBIOS_U8 FPGAHDMIEdid[256];
#if IS_SUPPORT_4K_MODE
extern CBIOS_U8 Fake4KEdid[256];
#endif

CBIOS_BOOL cbGetDeviceEDID(PCBIOS_VOID pvcbe, PCBIOS_DEVICE_COMMON pDevCommon, CBIOS_BOOL *pIsDevChanged);
CBIOS_BOOL cbIsDeviceChangedByEdid(PCBIOS_VOID pvcbe, PCBIOS_DEVICE_COMMON pDevCommon, PCBIOS_UCHAR pEDIDData);
CBIOS_BOOL cbUpdateDeviceSignature(PCBIOS_VOID pvcbe, PCBIOS_DEVICE_COMMON pDevCommon);
CBIOS_MONITOR_TYPE cbGetSupportMonitorType(PCBIOS_VOID pvcbe, CBIOS_ACTIVE_TYPE devices);
CBIOS_VOID cbClearEdidRelatedData(PCBIOS_VOID pvcbe, PCBIOS_DEVICE_COMMON pDevCommon);
CBIOS_BOOL cbDualModeDetect(PCBIOS_VOID pvcbe, PCBIOS_DEVICE_COMMON pDevCommon);
PCBIOS_VOID cbGetDPMonitorContext(PCBIOS_VOID pvcbe, PCBIOS_DEVICE_COMMON pDevCommon);
PCBIOS_VOID cbGetHDMIMonitorContext(PCBIOS_VOID pvcbe, PCBIOS_DEVICE_COMMON pDevCommon);
#endif
