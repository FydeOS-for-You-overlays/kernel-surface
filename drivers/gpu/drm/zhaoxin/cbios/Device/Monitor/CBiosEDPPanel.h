/* 
* Copyright 2015 VIA Technologies, Inc. All Rights Reserved.
* Copyright 2015 S3 Graphics, Inc. All Rights Reserved.
* Copyright 2015 VIA Alliance(Zhaoxin)Semiconductor Co., Ltd. All Rights Reserved.
*
* This file is part of s3g_core.ko
* 
* This file is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This file is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this file.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _CBIOS_EDP_PANEL_H_
#define _CBIOS_EDP_PANEL_H_

#include "../CBiosShare.h"

#define CBIOS_EDP_VERSION        0x01

typedef struct _CBIOS_EDP_CAPS
{
    CBIOS_U32    LinkSpeed;     // 270 MHz is 2700000
    CBIOS_U32    LaneNum;
    CBIOS_U32    BacklightMax;
    CBIOS_U32    BacklightMin;

    union
    {
        struct
        {
            CBIOS_U32             isBLCtrlSupport    :1;
            CBIOS_U32             isHardcodeLinkPara :1;    // 1: use the LinkSpeed and LaneNum given in CBIOS_EDP_CAPS
            CBIOS_U32             Reserved           :30;
        };
        CBIOS_U32                 Flags;
    };
}CBIOS_EDP_CAPS, *PCBIOS_EDP_CAPS;

typedef CBIOS_STATUS  (*PFN_cbEDPPanel_PreInit)(PCBIOS_VOID pvcbe);
typedef CBIOS_STATUS  (*PFN_cbEDPPanel_Init)(PCBIOS_VOID pvcbe);
typedef CBIOS_STATUS  (*PFN_cbEDPPanel_DeInit)(PCBIOS_VOID pvcbe);
typedef CBIOS_STATUS  (*PFN_cbEDPPanel_PowerOnOff)(PCBIOS_VOID  pvcbe, CBIOS_BOOL bTurnOn);
typedef CBIOS_STATUS  (*PFN_cbEDPPanel_SetBacklight)(PCBIOS_VOID pvcbe, CBIOS_U32 BrightnessValue);
typedef CBIOS_STATUS  (*PFN_cbEDPPanel_GetBacklight)(PCBIOS_VOID pvcbe, CBIOS_U32 *pBrightnessValue);

typedef struct _CBIOS_EDP_PREPARE_CAPS
{
    CBIOS_BOOL                  IsNeedPreInit;
    PFN_cbEDPPanel_PreInit      pFnEDPPanelPreInit;
}CBIOS_EDP_PREPARE_CAPS, *PCBIOS_EDP_PREPARE_CAPS;

typedef struct _CBIOS_EDP_PANEL_DESC
{
    CBIOS_U32                      VersionNum;
    CBIOS_UCHAR                    MonitorID[8];
    CBIOS_EDP_PREPARE_CAPS         EDPPreCaps; 
    CBIOS_EDP_CAPS                 EDPCaps;
    PFN_cbEDPPanel_Init            pFnEDPPanelInit;
    PFN_cbEDPPanel_DeInit          pFnEDPPanelDeInit;
    PFN_cbEDPPanel_PowerOnOff      pFnEDPPanelOnOff;
    PFN_cbEDPPanel_SetBacklight    pFnEDPPanelSetBacklight;
    PFN_cbEDPPanel_GetBacklight    pFnEDPPanelGetBacklight;
}CBIOS_EDP_PANEL_DESC, *PCBIOS_EDP_PANEL_DESC;

typedef struct _CBIOS_EDP_PARA
{
    CBIOS_EDP_PANEL_DESC             EDPPanelDesc;
}CBIOS_EDPPanel_PARAMS, *PCBIOS_EDPPanel_PARAMS;

PCBIOS_EDP_PANEL_DESC cbEDPPanel_GetPanelDescriptor(PCBIOS_VOID pvcbe, PCBIOS_U8 pEdidData);
CBIOS_STATUS cbEDPPanel_PreInit(PCBIOS_VOID pvcbe);
CBIOS_STATUS cbEDPPanel_Init(PCBIOS_VOID pvcbe, PCBIOS_EDP_PANEL_DESC pPanelDesc);
CBIOS_STATUS cbEDPPanel_DeInit(PCBIOS_VOID pvcbe, PCBIOS_EDP_PANEL_DESC pPanelDesc);
CBIOS_STATUS cbEDPPanel_OnOff(PCBIOS_VOID pvcbe, CBIOS_BOOL bTurnOn, PCBIOS_EDP_PANEL_DESC pPanelDesc);
CBIOS_STATUS cbEDPPanel_SetBacklight(PCBIOS_VOID pvcbe, CBIOS_U16 PWMFrequencyCounter, CBIOS_U32 BacklightValue, PCBIOS_EDP_PANEL_DESC pPanelDesc);
CBIOS_STATUS cbEDPPanel_GetBacklight(PCBIOS_VOID pvcbe, CBIOS_U32 *pBacklightValue, PCBIOS_EDP_PANEL_DESC pPanelDesc);
CBIOS_STATUS cbEDPPanel_DisplayOnOff(PCBIOS_VOID pvcbe, CBIOS_BOOL bTurnOn, PCBIOS_EDP_PANEL_DESC pPanelDesc);

#endif

