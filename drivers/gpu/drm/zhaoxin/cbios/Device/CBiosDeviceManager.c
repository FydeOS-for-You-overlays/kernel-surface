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
** CBios display manager functions. 
** Mainly take charge of device detect, onoff, set/get device caps or attributes.
**
** NOTE:
** The hw dependent function or structure SHOULD NOT be added to this file.
******************************************************************************/

#include "CBiosDeviceManager.h"

CBIOS_STATUS cbDMGetModeTiming(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, PCBIOS_GET_MODE_TIMING_PARAM pGetModeTiming)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, pGetModeTiming->DeviceId);
    return cbDevGetModeTiming(pcbe, pDevCommon, pGetModeTiming);
}

CBIOS_STATUS cbDMGetEdidFromBuffer(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, PCBIOS_PARAM_GET_EDID pCBParamGetEdid)
{
    CBIOS_STATUS bRetStatus = CBIOS_ER_INTERNAL;
    PCBIOS_DEVICE_COMMON pDevCommon = CBIOS_NULL;
    CBIOS_ACTIVE_TYPE Device = pCBParamGetEdid->DeviceId;

    if (Device != CBIOS_TYPE_NONE) //use device type to get EDID
    {
        pDevCommon = cbGetDeviceCommon(pDevMgr, Device);
        bRetStatus = cbDevGetEdidFromBuffer(pcbe, pDevCommon, pCBParamGetEdid);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: no device type assigned!\n", FUNCTION_NAME));
    }

    return bRetStatus;
}

CBIOS_STATUS cbDMSetEdid(PCBIOS_EXTENSION_COMMON pcbe,  PCBIOS_DEVICE_MANAGER pDevMgr, PCBIOS_PARAM_SET_EDID pCBParamSetEdid)
{
    CBIOS_BOOL   bIsDeviceSupport;
    CBIOS_STATUS status  = CBIOS_OK;
    PCBIOS_DEVICE_COMMON pDevCommon = CBIOS_NULL;

    if(pCBParamSetEdid == CBIOS_NULL)
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: the 3rd param is a NULL pointer!\n", FUNCTION_NAME));
        return CBIOS_ER_INVALID_PARAMETER;
    }

    bIsDeviceSupport = pDevMgr->SupportDevices & pCBParamSetEdid->DeviceId ? CBIOS_TRUE: CBIOS_FALSE;

    if(!bIsDeviceSupport)
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: The input device is not supported\n", FUNCTION_NAME));
        return CBIOS_ER_INVALID_PARAMETER;
    }

    pDevCommon = cbGetDeviceCommon(pDevMgr, pCBParamSetEdid->DeviceId);

    status = cbDevSetEdid(pcbe, pDevCommon, pCBParamSetEdid);

    return status;
}

CBIOS_STATUS cbDMGetSupportedMonitorType(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, PCBIOS_QUERY_MONITOR_TYPE_PER_PORT pCBiosQueryMonitorTypePerPort)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, pCBiosQueryMonitorTypePerPort->ActiveDevId);
    return cbDevGetSupportedMonitorType(pcbe, pDevCommon, pCBiosQueryMonitorTypePerPort);
}

CBIOS_STATUS cbDMQueryMonitorAttribute(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, PCBiosMonitorAttribute pMonitorAttribute)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, pMonitorAttribute->ActiveDevId);
    return cbDevQueryMonitorAttribute(pcbe, pDevCommon, pMonitorAttribute);
}

CBIOS_STATUS cbDMQueryMonitor3DCapability(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, PCBIOS_MONITOR_3D_CAPABILITY_PARA p3DCapability)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, p3DCapability->DeviceId);
    return cbDevQueryMonitor3DCapability(pcbe, pDevCommon, p3DCapability);
}

CBIOS_STATUS cbDMGetDeviceModeList(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, CBIOS_ACTIVE_TYPE Device, PCBiosModeInfoExt pModeList, CBIOS_U32 *pBufferSize)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, Device);
    return cbDevGetDeviceModeList(pcbe, pDevCommon, pModeList, pBufferSize);
}

CBIOS_STATUS cbDMGetDeviceModeListBufferSize(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, CBIOS_ACTIVE_TYPE Device, CBIOS_U32 *pBufferSize)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, Device);
    return cbDevGetDeviceModeListBufferSize(pcbe, pDevCommon, pBufferSize);
}

CBIOS_U32 cbDMGetHDAFormatList(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, CBIOS_ACTIVE_TYPE Device, PCBIOS_HDMI_AUDIO_INFO pHDAFormatList)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, Device);
    return cbDevGetHDAFormatList(pcbe, pDevCommon, pHDAFormatList);
}

CBIOS_U32 cbDMDevicesDetectPerPort(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, CBIOS_U32 DevicesToDetect)
{
    CBIOS_U32       Devices = 0, tmpDev = 0, ulDevIndex = 0;
    CBIOS_ACTIVE_TYPE CurDevice = CBIOS_TYPE_NONE, CurPort = CBIOS_TYPE_NONE;
    PCBIOS_DEVICE_COMMON    pDevCommon = CBIOS_NULL;
    CBIOS_BOOL bHardcodeDetected[CBIOS_MAX_DISPLAY_DEVICES_NUM] = {CBIOS_FALSE};

    //Note: pcbe->FeatureSwitch.IsFakeHDMIEdid is a patch for Elite2000 A2 Board,it will be deleted !
    if(pcbe->bRunOnQT)
    {
        Devices = (CBIOS_TYPE_CRT | CBIOS_TYPE_DP5) & pDevMgr->SupportDevices;

        if(Devices & CBIOS_TYPE_CRT)
        {
            ulDevIndex = cbConvertDeviceBit2Index(CBIOS_TYPE_CRT);
            bHardcodeDetected[ulDevIndex] = CBIOS_TRUE;
        }

        if(Devices & CBIOS_TYPE_DP5)
        {
            ulDevIndex = cbConvertDeviceBit2Index(CBIOS_TYPE_DP5);
            bHardcodeDetected[ulDevIndex] = CBIOS_TRUE;
        }
    }
    
    // Detection per I2C bus, detect all devices per one call.
    if(DevicesToDetect == 0)
    {
        DevicesToDetect = pDevMgr->SupportDevices;
    }
    else
    {
        DevicesToDetect &= pDevMgr->SupportDevices;
    }

    tmpDev = DevicesToDetect;

    while (tmpDev)
    {
        CurPort = GET_LAST_BIT(tmpDev);

        //clear port attribute
        pDevMgr->ConnectedDevices &= (~CurPort);

        //clear last detected result
        CurDevice = CBIOS_TYPE_NONE;

        ulDevIndex = cbConvertDeviceBit2Index(CurPort);
        pDevCommon = cbGetDeviceCommon(pDevMgr, CurPort);

        CurDevice = cbDevDeviceDetect(pcbe, pDevCommon, bHardcodeDetected[ulDevIndex]);

        if (CurDevice != CBIOS_TYPE_NONE)
        {
            pDevMgr->ConnectedDevices |= CurDevice;
            Devices |= CurDevice;
        }

        tmpDev &= (~CurPort);
    }

    return Devices;
}

CBIOS_STATUS cbDMSetDisplayDevicePowerState(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, CBIOS_ACTIVE_TYPE Devices, CBIOS_PM_STATUS PMState)
{
    CBIOS_ACTIVE_TYPE CurDev = CBIOS_TYPE_NONE;
    PCBIOS_DEVICE_COMMON pDevCommon = CBIOS_NULL;
    CBIOS_U8  IGAIndex = 0;
    CBIOS_U32 i = 0;
    
#ifdef CHECK_CHIPENABLE
    if (!cbHWIsChipEnable(pcbe))
        return CBIOS_ER_CHIPDISABLE;
#endif

    if ((pcbe->ChipID == CHIPID_ZX2K) && (Devices & CBIOS_TYPE_DP5))
    {
        Devices |= CBIOS_TYPE_HDTV;
    }
    
    while (Devices)
    {
        CurDev = GET_LAST_BIT(Devices);
        pDevCommon = cbGetDeviceCommon(pDevMgr, CurDev);
        Devices &= (~CurDev);

        for (i = IGA1; i < pcbe->DispMgr.IgaCount; i++)
        {
            if (CurDev & pcbe->DispMgr.ActiveDevices[i])
            {
                IGAIndex = (CBIOS_U8)i;
                break;
            }
        }

        if (i == pcbe->DispMgr.IgaCount)
        {
            cbDebugPrint((MAKE_LEVEL(GENERIC, WARNING), "%s: device 0x%x is not active device!\n", FUNCTION_NAME, CurDev));
            continue;
        }

        cbDevSetDisplayDevicePowerState(pcbe, pDevCommon, PMState, IGAIndex);
    }

    return CBIOS_OK;
}

CBIOS_STATUS cbDMGetDisplayDevicePowerState(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, CBIOS_ACTIVE_TYPE Device, PCBIOS_PM_STATUS pPMState)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, Device);
    return cbDevGetDisplayDevicePowerState(pcbe, pDevCommon, pPMState);
}

CBIOS_STATUS cbDMDSISendWriteCmd(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, CBIOS_ACTIVE_TYPE Device, PCBIOS_DSI_WRITE_PARA_INTERNAL pDSIWriteParams)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, Device);
    return cbDevDSISendWriteCmd(pcbe, pDevCommon, pDSIWriteParams);
}

CBIOS_STATUS cbDMDSISendReadCmd(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, CBIOS_ACTIVE_TYPE Device, PCBIOS_DSI_READ_PARA_INTERNAL pDSIReadParams)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, Device);
    return cbDevDSISendReadCmd(pcbe, pDevCommon, pDSIReadParams);
}

CBIOS_STATUS cbDMDSIDisplayUpdate(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, CBIOS_ACTIVE_TYPE Device, PCBIOS_DSI_UPDATE_PARA pDSIUpdatePara)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, Device);
    return cbDevDSIDisplayUpdate(pcbe, pDevCommon, pDSIUpdatePara);
}

CBIOS_STATUS cbDMDSIPanelSetCabc(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, CBIOS_ACTIVE_TYPE Device, CBIOS_U32 CabcValue)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, Device);
    return cbDevDSIPanelSetCabc(pcbe, pDevCommon, CabcValue);
}

CBIOS_STATUS cbDMDSIPanelSetBacklight(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, CBIOS_ACTIVE_TYPE Device, CBIOS_U32 BacklightValue)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, Device);
    return cbDevDSIPanelSetBacklight(pcbe, pDevCommon, BacklightValue);
}

CBIOS_STATUS cbDMDSIPanelGetBacklight(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, CBIOS_ACTIVE_TYPE Device, CBIOS_U32 *pBacklightValue)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, Device);
    return cbDevDSIPanelGetBacklight(pcbe, pDevCommon, pBacklightValue);
}

CBIOS_STATUS cbDMSetHDACodecPara(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, PCBIOS_HDAC_PARA pCbiosHDACPara)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, pCbiosHDACPara->DeviceId);
    return cbDevSetHDACodecPara(pcbe, pDevCommon, pCbiosHDACPara);
}

CBIOS_STATUS cbDMSetHDACConnectStatus(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, PCBIOS_HDAC_PARA pCbiosHDACPara)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, pCbiosHDACPara->DeviceId);
    return cbDevSetHDACConnectStatus(pcbe, pDevCommon, pCbiosHDACPara);
}

CBIOS_STATUS cbDMAccessDpcdData(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, PCBiosAccessDpcdDataParams pAccessDpcdDataParams)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, pAccessDpcdDataParams->RequestConnectedDevId);
    return cbDevAccessDpcdData(pcbe, pDevCommon, pAccessDpcdDataParams);
}

CBIOS_STATUS cbDMContentProtectionOnOff(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, PCBiosContentProtectionOnOffParams pContentProtectionOnOffParams)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, pContentProtectionOnOffParams->DevicesId);
    CBIOS_U8 IGAIndex = IGA1, i = 0;

    for (i = IGA1; i < pcbe->DispMgr.IgaCount; i++)
    {
        if (pContentProtectionOnOffParams->DevicesId & pcbe->DispMgr.ActiveDevices[i])
        {
            IGAIndex = i;
            break;
        }
    }

    return cbDevContentProtectionOnOff(pcbe, pDevCommon, IGAIndex, pContentProtectionOnOffParams);
}

CBIOS_STATUS cbDMGetHDCPStatus(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, PCBIOS_HDCP_STATUS_PARA pCBiosHdcpStatusParams)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, pCBiosHdcpStatusParams->DevicesId);
    CBIOS_U8 IGAIndex = IGA1, i = 0;

    for (i = IGA1; i < pcbe->DispMgr.IgaCount; i++)
    {
        if (pCBiosHdcpStatusParams->DevicesId & pcbe->DispMgr.ActiveDevices[i])
        {
            IGAIndex = i;
            break;
        }
    }

    return cbDevGetHDCPStatus(pcbe, pDevCommon, IGAIndex, pCBiosHdcpStatusParams);
}

CBIOS_STATUS cbDMHDCPWorkThread(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, PCBIOS_HDCP_WORK_PARA pCBiosHdcpWorkParams)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, pCBiosHdcpWorkParams->DevicesId);
    CBIOS_U8 IGAIndex = IGA1, i = 0;

    for (i = IGA1; i < pcbe->DispMgr.IgaCount; i++)
    {
        if (pCBiosHdcpWorkParams->DevicesId & pcbe->DispMgr.ActiveDevices[i])
        {
            IGAIndex = i;
            break;
        }
    }

    return cbDevHDCPWorkThread(pcbe, pDevCommon, IGAIndex, pCBiosHdcpWorkParams);
}

CBIOS_STATUS cbDMHDCPIsr(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, PCBIOS_HDCP_ISR_PARA pHdcpIsrParam)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, pHdcpIsrParam->DevicesId);
    return cbDevHDCPIsr(pcbe, pDevCommon, pHdcpIsrParam);
}

CBIOS_STATUS cbDMSyncDataWithUBoot(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, PCBIOS_DISPLAY_MANAGER pDispMgr, PCBIOS_UBOOT_DATA_PARAM pDataParam)
{
    CBIOS_GETTING_MODE_PARAMS ModeParams;
    CBIOS_U32 ActiveDevices = 0, i = 0;
    PCBIOS_DEVICE_COMMON pDevCommon = CBIOS_NULL;
    CBIOS_GET_DEV_COMB      GetDevComb = {0};
    CBIOS_DEVICE_COMB       DeviceComb = {0};

#ifdef CHECK_CHIPENABLE
    if (!cbHWIsChipEnable(pcbe))
        return CBIOS_ER_CHIPDISABLE;
#endif

    if(pDataParam != CBIOS_NULL)
    {
        //update active device from hibernation using CR6B,CR6C
        ActiveDevices = cbHwGetActDeviceFromReg(pcbe);
        ActiveDevices &= (~CBIOS_TYPE_DUOVIEW);
        
        GetDevComb.Size = sizeof(CBIOS_GET_DEV_COMB);
        GetDevComb.pDeviceComb = &DeviceComb;
        DeviceComb.Devices = ActiveDevices;
        cbPathMgrGetDevComb(pcbe, &GetDevComb);
        pcbe->DispMgr.ActiveDevices[IGA1] = DeviceComb.Iga1Dev;
        pcbe->DispMgr.ActiveDevices[IGA2] = DeviceComb.Iga2Dev;
        pcbe->DispMgr.ActiveDevices[IGA3] = DeviceComb.Iga3Dev;

        // update device power state from UBOOT
        for (i = 0; i < CBIOS_MAX_DEVICE_BITS; i++)
        {
            if ((1 << i) & ActiveDevices)
            {
                pDevCommon = cbGetDeviceCommon(pDevMgr, ((1 << i) & ActiveDevices));
                pDevCommon->PowerState = CBIOS_PM_ON;
            }
        }

        for (i = 0; i < pcbe->DispMgr.IgaCount; i++)
        {
            if (pDispMgr->ActiveDevices[i] != CBIOS_TYPE_NONE)
            {
                cb_memset(&ModeParams, 0, sizeof(CBIOS_GETTING_MODE_PARAMS));
                ModeParams.Device = pDispMgr->ActiveDevices[i];

                pDevCommon = cbGetDeviceCommon(pDevMgr, ModeParams.Device);
                cbDevGetModeFromReg(pcbe, pDevCommon, &ModeParams);

                pDataParam->IGAModeParams[i].DeviceId = pDispMgr->ActiveDevices[i];
                pDataParam->IGAModeParams[i].IGAIndex = i;

                pDataParam->IGAModeParams[i].SourcModeParams.XRes = ModeParams.DestModeParams.XRes;
                pDataParam->IGAModeParams[i].SourcModeParams.YRes = ModeParams.DestModeParams.YRes;

                pDataParam->IGAModeParams[i].DestModeParams.XRes = ModeParams.DestModeParams.XRes;
                pDataParam->IGAModeParams[i].DestModeParams.YRes = ModeParams.DestModeParams.YRes;
                pDataParam->IGAModeParams[i].DestModeParams.RefreshRate = ModeParams.DestModeParams.RefreshRate;
                pDataParam->IGAModeParams[i].DestModeParams.InterlaceFlag = ModeParams.DestModeParams.InterlaceFlag;
                pDataParam->IGAModeParams[i].DestModeParams.AspectRatioFlag = 0;

                pDataParam->IGAModeParams[i].ScalerSizeParams.XRes = ModeParams.DestModeParams.XRes;
                pDataParam->IGAModeParams[i].ScalerSizeParams.YRes = ModeParams.DestModeParams.YRes;

                pDataParam->IGAModeParams[i].BitPerComponent = 8;
            }
        }
        return CBIOS_OK;
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: null pointer is transfered!\n", FUNCTION_NAME));
        return CBIOS_ER_NULLPOINTER;
    }
}

CBIOS_BOOL cbDMHdmiSCDCWorkThreadMainFunc(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr)
{
    PCBIOS_DEVICE_COMMON pDevCommon;
    CBIOS_BOOL    bRet = CBIOS_FALSE;
    CBIOS_ACTIVE_TYPE SupportDevices = pcbe->DeviceMgr.SupportDevices;
    CBIOS_U32 CurDev = 0;
    
    while (SupportDevices)
    {
        CurDev = GET_LAST_BIT(SupportDevices);
        pDevCommon = cbGetDeviceCommon(&pcbe->DeviceMgr, CurDev);
        
        if(pDevCommon->EdidStruct.Attribute.HFVSDBData.IsSCDCPresent)
        {
            bRet = cbDevHdmiSCDCWorkThreadMainFunc(pcbe, pDevCommon);
        }
        
        SupportDevices &= (~CurDev);
    }
    
    return bRet;
}

CBIOS_STATUS cbDMDPIsr(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, PCBIOS_DP_ISR_PARA pDPIsrPara)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, pDPIsrPara->DeviceId);
    return cbDevDPIsr(pcbe, pDevCommon, pDPIsrPara);
}

CBIOS_BOOL cbDMDPWorkThreadMainFunc(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, PCBIOS_DP_WORKTHREAD_PARA pDPWorkThreadPara)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, pDPWorkThreadPara->DeviceId);
    return cbDevDPWorkThreadMainFunc(pcbe, pDevCommon, pDPWorkThreadPara);
}

CBIOS_STATUS cbDMDPSetNotifications(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, PCBIOS_DP_NOTIFICATIONS pDPNotifications)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, pDPNotifications->DeviceId);
    return cbDevDPSetNotifications(pcbe, pDevCommon, pDPNotifications);
}

CBIOS_STATUS cbDMDPGetCustomizedTiming(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_MANAGER pDevMgr, PCBIOS_DP_CUSTOMIZED_TIMING pDPCustomizedTiming)
{
    PCBIOS_DEVICE_COMMON pDevCommon = cbGetDeviceCommon(pDevMgr, pDPCustomizedTiming->DeviceId);
    return cbDevDPGetCustomizedTiming(pcbe, pDevCommon, pDPCustomizedTiming);
}