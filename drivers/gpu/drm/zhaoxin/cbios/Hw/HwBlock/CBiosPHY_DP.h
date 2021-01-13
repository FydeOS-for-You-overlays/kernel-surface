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
** DP PHY interface function prototype and parameter definition.
**
** NOTE:
**
******************************************************************************/

#ifndef _CBIOS_PHY_DP_H_
#define _CBIOS_PHY_DP_H_

#include "../../Device/CBiosDeviceShare.h"

#define DP5_EPHYINITIALIZED  0x0A
#define DP6_EPHYINITIALIZED  0xA0

typedef enum _DP_EPHY_MODE
{
    DP_EPHY_MODE_UNINITIALIZED = 0,
    DP_EPHY_TMDS_MODE,
    DP_EPHY_DP_MODE,
    DP_EHPY_MODE_LAST
}DP_EPHY_MODE;

CBIOS_BOOL cbPHY_DP_IsEPHYInitialized(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX DPModuleIndex);
CBIOS_VOID cbPHY_DP_SetEPHYInitialized(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX DPModuleIndex);
CBIOS_VOID cbPHY_DP_InitEPHY(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX DPModuleIndex);
CBIOS_VOID cbPHY_DP_DeInitEPHY(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX DPModuleIndex);
CBIOS_VOID cbPHY_DP_SelectPhySource(PCBIOS_VOID pvcbe, DP_EPHY_MODE DPEphyMode, PCBIOS_DISPLAY_SOURCE pDispSource, CBIOS_MONITOR_TYPE MonitorType);
CBIOS_VOID cbPHY_DP_SelectEphyMode(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX DPModuleIndex, DP_EPHY_MODE DPEphyMode);
DP_EPHY_MODE cbPHY_DP_GetEphyMode(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX DPModuleIndex);
CBIOS_VOID cbPHY_DP_DPModeOnOff(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX DPModuleIndex,  CBIOS_U32 LinkSpeed, CBIOS_BOOL status);
CBIOS_VOID cbPHY_DP_DualModeOnOff(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX DPModuleIndex, CBIOS_U32 ClockFreq, CBIOS_BOOL bTurnOn);
CBIOS_VOID cbPHY_DP_AuxPowerOn(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX DPModuleIndex);
#endif
