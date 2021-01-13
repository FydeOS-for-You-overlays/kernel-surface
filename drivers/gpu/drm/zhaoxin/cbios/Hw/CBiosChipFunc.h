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
** CBios chip dependent function prototype.
**
** NOTE:
** This header file CAN be included by sw layer. 
******************************************************************************/

#ifndef _CBIOS_CHIP_FUNC_H_
#define _CBIOS_CHIP_FUNC_H_

#include "../CBios.h"
#include "../Device/CBiosChipShare.h"
#include "../Display/CBiosDisplayManager.h"

typedef CBIOS_VOID 
(*PFN_cbSetTimingReg)(PCBIOS_VOID pvcbe,
                      PCBIOS_TIMING_ATTRIB pTiming,
                      CBIOS_U32 IGAIndex,
                      CBIOS_TIMING_FLAGS Flags);

typedef CBIOS_VOID 
(*PFN_cbGetModeInfoFromReg)(PCBIOS_VOID pvcbe,
                             CBIOS_ACTIVE_TYPE ulDevice,
                             PCBIOS_TIMING_ATTRIB pTiming,
                             PCBIOS_TIMING_FLAGS pFlags,
                             CBIOS_U32  IGAIndex,
                             CBIOS_TIMING_REG_TYPE TimingRegType);

typedef CBIOS_BOOL
(*PFN_cbInitVCP) (PCBIOS_VOID pvcbe, PCBIOS_VOID pVCP, PCBIOS_VOID pRomBase);

typedef CBIOS_VOID 
(*PFN_cbDoHDTVFuncSetting) (PCBIOS_VOID pvcbe, 
                            PCBIOS_DISP_MODE_PARAMS pModeParams,
                            CBIOS_U32 IGAIndex, 
                            CBIOS_ACTIVE_TYPE ulDevices);

typedef CBIOS_VOID
(*PFN_cbLoadSSC) (PCBIOS_VOID pvcbe, CBIOS_U32 CenterFreq, CBIOS_U8 IGAIndex, CBIOS_ACTIVE_TYPE LCDType);

typedef CBIOS_VOID
(*PFN_cbEnableSpreadSpectrum) (PCBIOS_VOID pvcbe, CBIOS_U8 IGAIndex);

typedef CBIOS_VOID 
(*PFN_cbDisableSpreadSpectrum) (PCBIOS_VOID pvcbe, CBIOS_U8 IGAIndex);

typedef  CBIOS_STATUS
(*PFN_cbUpdateFrame)(PCBIOS_VOID pvcbe, PCBIOS_UPDATE_FRAME_PARA pUpdateFrame);

typedef  CBIOS_STATUS
(*PFN_cbDoCSCAdjust)(PCBIOS_VOID pvcbe, CBIOS_ACTIVE_TYPE Device, PCBIOS_CSC_ADJUST_PARA pCSCAdjustPara);

typedef  CBIOS_STATUS
(*PFN_cbCheckSurfaceOnDisplay)(PCBIOS_VOID pvcbe, PCBIOS_CHECK_SURFACE_ON_DISP pChkSurfacePara);

typedef  CBIOS_STATUS
(*PFN_cbGetDispAddr)(PCBIOS_VOID pvcbe, PCBIOS_GET_DISP_ADDR  pGetDispAddr);

typedef  CBIOS_STATUS
(*PFN_cbSetHwCursor)(PCBIOS_VOID pvcbe, PCBIOS_CURSOR_PARA pSetCursor);

typedef CBIOS_STATUS
(*PFN_cbPWMFunctionCtrl)(PCBIOS_VOID pvcbe, PCBIOS_PWM_FUNCTION_CTRL_PARAMS pPWMFuncPara);

typedef CBIOS_STATUS
(*PFN_cbInterruptEnableDisable)(PCBIOS_VOID pvcbe, PCBIOS_INT_ENABLE_DISABLE_PARA pIntPara);

typedef CBIOS_STATUS
(*PFN_cbCECEnableDisable)(PCBIOS_VOID pvcbe, PCBIOS_CEC_ENABLE_DISABLE_PARA pCECEnableDisablePara);

typedef CBIOS_STATUS
(*PFN_cbSetGamma)(CBIOS_VOID* pvcbe, PCBIOS_GAMMA_PARA pGammaParam);

typedef CBIOS_STATUS
(*PFN_cbHpdEnableDisable)(PCBIOS_VOID pvcbe, PCBIOS_HOTPLUG_PARAM  pHotPlugParam);


typedef CBIOS_BOOL
(*PFN_cbUpdateShadowInfo)(PCBIOS_VOID pvcbe, PCBIOS_PARAM_SHADOWINFO pShadowInfo);

typedef struct _CBIOS_CHIP_FUNC_TABLE
{
    PFN_cbSetTimingReg                              pfncbSetCRTimingReg;
    PFN_cbSetTimingReg                              pfncbSetSRTimingReg;
    PFN_cbGetModeInfoFromReg                        pfncbGetModeInfoFromReg;
    PFN_cbInitVCP                                   pfncbInitVCP;
    PFN_cbDoHDTVFuncSetting                         pfncbDoHDTVFuncSetting;
    PFN_cbLoadSSC                                   pfncbLoadSSC;
    PFN_cbEnableSpreadSpectrum                      pfncbEnableSpreadSpectrum;
    PFN_cbDisableSpreadSpectrum                     pfncbDisableSpreadSpectrum;
    PFN_cbUpdateFrame                               pfncbUpdateFrame;
    PFN_cbDoCSCAdjust                               pfncbDoCSCAdjust;
    PFN_cbCheckSurfaceOnDisplay                     pfncbCheckSurfaceOnDisplay;
    PFN_cbGetDispAddr                               pfncbGetDispAddr;
    PFN_cbSetHwCursor                               pfncbSetHwCursor;
    PFN_cbPWMFunctionCtrl                           pfncbPWMFunctionCtrl;
    PFN_cbInterruptEnableDisable                    pfncbInterruptEnableDisable;
    PFN_cbCECEnableDisable                          pfncbCECEnableDisable;
    PFN_cbSetGamma                                  pfncbSetGamma;
    PFN_cbHpdEnableDisable                          pfncbHpdEnableDisable;
    PFN_cbUpdateShadowInfo                      pfncbUpdateShadowInfo;
}CBIOS_CHIP_FUNC_TABLE, *PCBIOS_CHIP_FUNC_TABLE;


CBIOS_VOID   cbSetCRTimingReg(PCBIOS_VOID pvcbe, PCBIOS_TIMING_ATTRIB pTiming, CBIOS_U32 IGAIndex, CBIOS_TIMING_FLAGS Flags);
CBIOS_VOID   cbSetSRTimingReg(PCBIOS_VOID pvcbe, PCBIOS_TIMING_ATTRIB pTiming, CBIOS_U32 IGAIndex, CBIOS_TIMING_FLAGS Flags);
CBIOS_VOID   cbGetModeInfoFromReg(PCBIOS_VOID pvcbe,
                                          CBIOS_ACTIVE_TYPE ulDevice,
                                          PCBIOS_TIMING_ATTRIB pTiming,
                                          PCBIOS_TIMING_FLAGS pFlags,
                                          CBIOS_U32  IGAIndex,
                                          CBIOS_TIMING_REG_TYPE TimingRegType);
CBIOS_BOOL   cbInitVCP(PCBIOS_VOID pvcbe, PCBIOS_VOID pVCPInfo, PCBIOS_VOID pRomBase);
CBIOS_VOID   cbDoHDTVFuncSetting(PCBIOS_VOID pvcbe, PCBIOS_DISP_MODE_PARAMS pModeParams, CBIOS_U32 IGAIndex, CBIOS_ACTIVE_TYPE ulDevices);
CBIOS_VOID   cbLoadSSC(PCBIOS_VOID pvcbe, CBIOS_U32 CenterFreq, CBIOS_U8 IGAIndex, CBIOS_ACTIVE_TYPE LCDType);
CBIOS_VOID   cbEnableSpreadSpectrum(PCBIOS_VOID pvcbe, CBIOS_U8 IGAIndex);
CBIOS_VOID   cbDisableSpreadSpectrum(PCBIOS_VOID pvcbe, CBIOS_U8 IGAIndex);
CBIOS_STATUS cbPWMFunctionCtrl(PCBIOS_VOID pvcbe, PCBIOS_PWM_FUNCTION_CTRL_PARAMS pPWMFuncPara);
CBIOS_STATUS cbInterruptEnableDisable(PCBIOS_VOID pvcbe, PCBIOS_INT_ENABLE_DISABLE_PARA pIntPara);
CBIOS_STATUS cbCECEnableDisable(PCBIOS_VOID pvcbe, PCBIOS_CEC_ENABLE_DISABLE_PARA pCECEnableDisablePara);
CBIOS_STATUS cbSetGamma(PCBIOS_VOID pvcbe, PCBIOS_GAMMA_PARA pGammaParam);
CBIOS_STATUS cbHpdEnableDisable(PCBIOS_VOID pvcbe, PCBIOS_HOTPLUG_PARAM  pHotPlugParam);     
CBIOS_STATUS cbUpdateFrame(PCBIOS_VOID pvcbe, PCBIOS_UPDATE_FRAME_PARA pUpdateFrame);
CBIOS_STATUS cbDoCSCAdjust(PCBIOS_VOID pvcbe, CBIOS_ACTIVE_TYPE Device, PCBIOS_CSC_ADJUST_PARA pCSCAdjustPara);
CBIOS_STATUS cbCheckSurfaceOnDisplay(PCBIOS_VOID pvcbe, PCBIOS_CHECK_SURFACE_ON_DISP pChkSurfacePara);
CBIOS_STATUS cbGetDispAddr(PCBIOS_VOID  pvcbe, PCBIOS_GET_DISP_ADDR pGetDispAddr);
CBIOS_STATUS cbSetHwCursor(PCBIOS_VOID pvcbe, PCBIOS_CURSOR_PARA pSetCursor);
CBIOS_BOOL cbUpdateShadowInfo(PCBIOS_VOID pvcbe, PCBIOS_PARAM_SHADOWINFO pShadowInfo);
#endif//_CBIOS_CHIP_FUNC_H_
