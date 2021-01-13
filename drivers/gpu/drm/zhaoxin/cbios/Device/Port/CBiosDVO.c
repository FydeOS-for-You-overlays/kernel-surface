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
** DVO port interface function implementation.
**
** NOTE:
** DVO port ONLY parameters SHOULD be added to CBIOS_DVO_CONTEXT.
** The daughter card's function and parameter SHOULD be added to corresponding monitor file.
******************************************************************************/

#include "CBiosChipShare.h"
#include "../../Hw/HwBlock/CBiosDIU_DVO.h"

#if DVO_PORT_SUPPORT

CBIOS_VOID  cbDVOPort_GetSupportMonitorType(PCBIOS_VOID pvcbe, PCBIOS_MONITOR_TYPE pMonitorType)
{
    PCBIOS_EXTENSION_COMMON pcbe=(PCBIOS_EXTENSION_COMMON)pvcbe;
    CBIOS_U32 ulDevIndex = 0;
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(&pcbe->DeviceMgr, CBIOS_TYPE_DVO);
    PCBIOS_DVO_CONTEXT pDvoContext = container_of(pDevCommon, PCBIOS_DVO_CONTEXT, Common);

    /*if (pDvoContext->DVODevice.DVOTxType == TX_ADV7511)
    {
        (*pMonitorType) |= CBIOS_MONITOR_TYPE_HDMI | CBIOS_MONITOR_TYPE_DVI;
    }*/
}

//-------------------------------------------------------------------
//cbDVOPort_InitTX
//    initialize TX HW on DVO port
//  
//-------------------------------------------------------------------
static CBIOS_BOOL cbDVOPort_InitTX(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DVO_CONTEXT pDvoContext)
{
    CBIOS_BOOL status = CBIOS_TRUE;

    switch (pDvoContext->DVODevice.DVOTxType)
    {
    /*case TX_ADV7511:
        status = cbADV7511_Init(pcbe);
        break;*/
    default:
        status = CBIOS_FALSE;
        break;
    }

    return status;
}


static CBIOS_VOID cbDVOPort_OnOff(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_COMMON pDevCommon, CBIOS_BOOL bOn)
{
    CBIOS_U8                I2CData = 0;
    PCBIOS_DVO_CONTEXT pDvoContext = container_of(pDevCommon, PCBIOS_DVO_CONTEXT, Common);
    CBIOS_U32  IGAIndex = pDevCommon->DispSource.ModuleList.IGAModule.Index;
    
    if ((pDvoContext == CBIOS_NULL) || (!(pDvoContext->Common.DeviceType & CBIOS_TYPE_DVO)))
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: the 2nd param is invalid!\n", FUNCTION_NAME));
        return;
    }

    cbTraceEnter(GENERIC);

    if(bOn)
    {
        cbDIU_DVO_VideoOnOff(pcbe, bOn, (CBIOS_U8)IGAIndex);

        switch(pDvoContext->DVODevice.DVOTxType)
        {
        /*case TX_ADV7511:
            cbADV7511_OnOff(pcbe, CBIOS_TRUE, IGAIndex);
            break;*/

        default:
            cbDebugPrint((MAKE_LEVEL(GENERIC, WARNING),"%s: unknown DVO daughter card type!\n", FUNCTION_NAME));
            break;
        }
        
        pDevCommon->PowerState = CBIOS_PM_ON;
    }
    else
    {
        switch(pDvoContext->DVODevice.DVOTxType)
        {
        /*case TX_ADV7511:
            cbADV7511_OnOff(pcbe, CBIOS_FALSE, IGAIndex);
            break;*/

        default:
            cbDebugPrint((MAKE_LEVEL(GENERIC, WARNING),"%s: unknown DVO daughter card type!\n", FUNCTION_NAME));
            break;
        }

        cbDIU_DVO_VideoOnOff(pcbe, bOn, (CBIOS_U8)IGAIndex);
        
        pDevCommon->PowerState = CBIOS_PM_OFF;
    }

    cbTraceExit(GENERIC);
}

static CBIOS_VOID cbDVOPort_HW_SetMode(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DISP_MODE_PARAMS pModeParams)
{
    CBIOS_U8 HVPolarity = pModeParams->TargetTiming.HVPolarity;

    cbDIU_DVO_SetHVSync(pcbe, HVPolarity);
}

static CBIOS_VOID cbDVOPort_SetMode(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_COMMON pDevCommon, PCBIOS_DISP_MODE_PARAMS pModeParams)
{
    cbDVOPort_HW_SetMode(pcbe, pModeParams);
}

static CBIOS_VOID cbDVOPort_HwInit(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_COMMON pDevCommon)
{
    PCBIOS_DVO_CONTEXT pDvoContext = container_of(pDevCommon, PCBIOS_DVO_CONTEXT, Common);

    if ((pDvoContext == CBIOS_NULL) || (!(pDvoContext->Common.DeviceType & CBIOS_TYPE_DVO)))
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: the 2nd param is invalid!\n", FUNCTION_NAME));
        return;
    }

    cbDVOPort_InitTX(pcbe, pDvoContext);
}

static CBIOS_BOOL cbDVOPort_DeviceDetect(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_COMMON pDevCommon, CBIOS_BOOL bHardcodeDetected)
{
    CBIOS_BOOL   bGotEdid      = CBIOS_FALSE;
    CBIOS_BOOL   IsDevChanged  = 0;
    CBIOS_BOOL  bConnected = CBIOS_FALSE;

    PCBIOS_DVO_CONTEXT pDvoContext = container_of(pDevCommon, PCBIOS_DVO_CONTEXT, Common);

    if ((pDvoContext == CBIOS_NULL) || (!(pDvoContext->Common.DeviceType & CBIOS_TYPE_DVO)))
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: the 2nd param is invalid!\n", FUNCTION_NAME));
        return bConnected;
    }

/*    //for ADV7511 , config the EDID slaveaddr (0x43) as a0 
    if(pDvoContext->DvoDevice.DVOTxType == TX_ADV7511)
    {
        cbADV7511_PreDetect(pvcbe);
    }*/

    bGotEdid = cbGetDeviceEDID(pcbe, &pDvoContext->Common, &IsDevChanged);

    if (!((*(pDvoContext->Common.EdidData + EDID_VIDEO_INPUT_DEF_BYTE_OFFSET)) & EDID_VIDEO_INPUT_DEF_DIGITAL))
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: why come here??? Current device is a CRT monitor according to EDID!\n", FUNCTION_NAME));
        bGotEdid = CBIOS_FALSE;
    }

    if (bGotEdid)
    {
        if (IsDevChanged)
        {
            cbEDIDModule_ParseEDID(pDvoContext->Common.EdidData, &(pDvoContext->Common.EdidStruct), CBIOS_EDIDDATABYTE);
        }
        
        if (pDvoContext->Common.EdidStruct.Attribute.IsCEA861HDMI)
        {
            pDvoContext->Common.CurrentMonitorType = CBIOS_MONITOR_TYPE_HDMI;
        }
        else
        {
            pDvoContext->Common.CurrentMonitorType = CBIOS_MONITOR_TYPE_DVI;
        }

        //update monitor type
        if (!(pDvoContext->Common.CurrentMonitorType & cbGetSupportMonitorType(pcbe, pDevCommon->DeviceType)))
        {
            pDvoContext->Common.CurrentMonitorType = cbGetSupportMonitorType(pcbe, pDevCommon->DeviceType);
        }
        
        pDvoContext->Common.isFakeEdid = CBIOS_FALSE;
        bConnected = CBIOS_TRUE;
    }
    else
    {
        cbClearEdidRelatedData(pcbe, &pDvoContext->Common);
    }

    return bConnected;
}

PCBIOS_DEVICE_COMMON cbDVOPort_Init(PCBIOS_VOID pvcbe, PVCP_INFO_chx pVCP, CBIOS_ACTIVE_TYPE DeviceType)
{
    PCBIOS_EXTENSION_COMMON pcbe          = (PCBIOS_EXTENSION_COMMON)pvcbe;
    PCBIOS_DVO_CONTEXT      pDvoContext   = CBIOS_NULL;

    if(DeviceType & ~CBIOS_TYPE_DVO)
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR),"%s: unsupported device type!!!\n", FUNCTION_NAME));
        return CBIOS_NULL;
    }

    pDvoContext = cb_AllocateNonpagedPool(sizeof(CBIOS_DVO_CONTEXT));
    if(pDvoContext == CBIOS_NULL)
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR),"%s: pDvoContext allocate error!!!\n", FUNCTION_NAME));
        return CBIOS_NULL;
    }
	
    pDvoContext->Common.DeviceType = DeviceType;
    pDvoContext->Common.SupportMonitorType = CBIOS_MONITOR_TYPE_NONE;
    pDvoContext->Common.I2CBus = pVCP->DVOCharByte & I2CBUSMASK;
    pDvoContext->Common.HPDPin = pVCP->DVOInterruptPort & HPDPORT_MASK;
    pDvoContext->Common.CurrentMonitorType = CBIOS_MONITOR_TYPE_NONE;
    pDvoContext->Common.PowerState = CBIOS_PM_INVALID;

    cbInitialModuleList(&pDvoContext->Common.DispSource.ModuleList);

    pDvoContext->Common.pfncbDeviceHwInit = (PFN_cbDeviceHwInit)cbDVOPort_HwInit;
    pDvoContext->Common.pfncbDeviceDetect = (PFN_cbDeviceDetect)cbDVOPort_DeviceDetect;
    pDvoContext->Common.pfncbDeviceOnOff = (PFN_cbDeviceOnOff)cbDVOPort_OnOff;
    pDvoContext->Common.pfncbDeviceSetMode = (PFN_cbDeviceSetMode)cbDVOPort_SetMode;

    // pre check if DVO daughter card exists
    cbDIU_DVO_CheckDaughterCardType(pcbe, pVCP, pDvoContext);

    return &pDvoContext->Common;
}

CBIOS_VOID cbDVOPort_DeInit(PCBIOS_VOID pvcbe, PCBIOS_DEVICE_COMMON pDevCommon)
{
    PCBIOS_DVO_CONTEXT pDvoContext = container_of(pDevCommon, PCBIOS_DVO_CONTEXT, Common);
    if ((pDvoContext == CBIOS_NULL) || (!(pDvoContext->Common.DeviceType & CBIOS_TYPE_DVO)))
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: the 2nd param is invalid!\n", FUNCTION_NAME));
        return;
    }

    if (pDvoContext)
    {
        cb_FreePool(pDvoContext);
        pDvoContext = CBIOS_NULL;
    }
}

#endif

