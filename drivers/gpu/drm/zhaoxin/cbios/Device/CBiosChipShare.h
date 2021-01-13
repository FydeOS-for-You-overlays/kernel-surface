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
** CBios function prototypes in Init/Utility files
** Defines CBIOS_EXTENSION_COMMON and VCP_INFO
** Defines macro for sharing used. 
**
** NOTE:
** The sharing used structure is SUGGESTED to be add to CBiosTypes.h
******************************************************************************/

#ifndef _CBIOS_CHIPSHARE_H_
#define _CBIOS_CHIPSHARE_H_

#include "CBiosTypes.h"
#include "CBiosShare.h"
#include "CBiosReg.h"
#include "../Callback/CBiosCallbacks.h"
#include "../Display/CBiosDisplayManager.h"
#include "../Display/CBiosPathManager.h"
#include "../Util/CBiosEDID.h"
#include "CBiosDevice.h"
#include "Port/CBiosDVO.h"
#include "Monitor/CBiosHDMIMonitor.h"
#include "Monitor/CBiosDPMonitor.h"
#include "CBiosCompile.h"
#include "Port/CBiosDSI.h"
#include "Port/CBiosCRT.h"
#include "Port/CBiosDP.h"
#include "../Hw/HwInterface/CBiosHwInterface.h"
#include "../Hw/HwBlock/CBiosDIU_CSC.h"


#define CBIOS_NOIGAENCODERINDEX                       0xFF

// I2C
#define I2C_DELAY_DEFAULT       20    //default I2C delay time, 8us, I2C speed up to 125kbps
#define I2CBUSMASK              0x07
#define I2CBUS_INVALID          0xFF


//for Debug Chip Enable/Disable
#define CHECK_CHIPENABLE        1

//for HPD
#define HPDPORT_MASK            0x07
#define CBIOS_ANALOG_HPD_VIRTUAL_GPIO     10

// for invalid GPIO
#define INVALID_GPIO            0x07

// clock reference frequency
#define RefFreq24               240000  //Reference frequency for E2UMA
#define RefFreq27               270000  //Reference frequency for matrix

#define S3_POST_TYPE_MASK       0x7F
#define MAPMASK_EXIT            0xE000

// the max size of data dump to log file
#define CBIOS_MAX_DUMP_DATA_SIZE    2 * 1024

// VCP define
#define VCP_OFFSET              0x30
#define VCP_TAG                 0x66BB

// for memory type definition
#define Default_Mem_Type          0x00

// MACRO for set mode invalid flags
#define SKIP_MODE_REG_SETTING           0x8000

#define AUTO_TIMING_PAL     20
#define AUTO_TIMING_NTSC    21

// For calculate the mode timing according to CVT algrithm
#define    CPRIME                    30
#define    CLOCKSTEP                 25    /* Muliplied by 100 */
#define    HSYNCPERCENT              8     
#define    MPRIME                    300
#define    MINVFPORCH                3
#define    MINVBPORCH                6
#define    MINVBLANKINGPERIOD        550      /* unit is us */
#define    CELLGRAN                  8 

/* from S3.h */
#define SEQREGSNUM  256
#define CRTCREGSNUM 256

// callback return status
#define NO_ERROR                                            0L      // dderror
#define ERROR_INVALID_PARAMETER                             87L     // dderror

// H/V sync Polarity
#define HorNEGATIVE         0x40
#define HorPOSITIVE         0x00
#define VerNEGATIVE         0x80
#define VerPOSITIVE         0x00

// Hotplug port, defined in CBIOS.
#define CBIOS_GPIO0       0
#define CBIOS_GPIO1       1
#define CBIOS_GPIO2       2
#define CBIOS_GPIO3       3
#define CBIOS_GPIO4       4
#define CBIOS_GPIO5       5

// MM8504's interrupt bits
#define CBIOS_GPIO0_BIT_MASK   (BIT18)
#define CBIOS_GPIO1_BIT_MASK   (BIT21)

// MM8504's interrupt bits
#define CBIOS_GPIO3_BIT_MASK  (BIT20)
#define CBIOS_GPIO4_BIT_MASK  (BIT19)

#define cb_max(a,b)            (((a) > (b)) ? (a) : (b))
#define cb_min(a,b)            (((a) < (b)) ? (a) : (b))

#define IS_ONE_BIT(N)       ((((N)-1)&(N))==0)
#define GET_LAST_BIT(N)     ((~((N)-1))&(N))

typedef struct _CBIOS_HDMI_FORMAT_MTX
{
   CBIOS_U16   FormatNum;
   CBIOS_U16   XRes;
   CBIOS_U16   YRes;
   CBIOS_UCHAR Interlace;
   CBIOS_U16   RefRate[2];
   CBIOS_UCHAR AspectRatio;
   CBIOS_UCHAR DefaultRefRateIndex; 
   CBIOS_U32   PixelClock;
   /*CBIOS_U32 IsRealHDMIDevice; */ /* Evevy bit relate with device bit is used to judge if it a read HDMI device.*/
}CBIOS_HDMI_FORMAT_MTX, *PCBIOS_HDMI_FORMAT_MTX;

typedef struct _CBIOS_EXTENSION_COMMON
{
    /* driver&hardware info */
    PCBIOS_VOID  pAdapterContext;
    CBIOS_S32    bMAMMPrimaryAdapter;
    CBIOS_U32    PCIDeviceID;
    CBIOS_U32    ChipID;
    CBIOS_U32    SVID; //sub vendor ID
    CBIOS_U32    SSID; //sub system ID
    CBIOS_U32    ChipRevision;
    CBIOS_BOARD_VERSION BoardVersion;

    /* Just for video memory validation */
    PCBIOS_VOID  FBVirtualLinearAddress;
    CBIOS_U32    MappedBufferSize;     
    CBIOS_U32    bRunOnQT;

    //---------------------------------------------------
    // CBIOS Chip Related Speciality
    //--------------------------------------------------
    struct {
        CBIOS_U32 bNoMemoryControl             :1;      // UMA product don't need to do memory control
        CBIOS_U32 IsSupportDownScaling         :1;      // E2UMA support down scaling
        CBIOS_U32 Is24MReferenceClock          :1;      // E2UMA use 24MHz reference clock
        CBIOS_U32 IsSupport3DVideo             :1;      // E2UMA support 3D video
        CBIOS_U32 IsSupportDeepColor           :1;      // E2UMA support deep color
        CBIOS_U32 IsSupportCEC                 :1;      // E2UMA support CEC
        CBIOS_U32 bSupportConfigEclkByEfuse    :1;      // E2UMA use Efuse bit 158 to specify ECLK
        CBIOS_U32 bSupportScrambling           :1;      //HDMI scrambling
        CBIOS_U32 bSupportReadRequest          :1;      //HDMI read request
        CBIOS_U32 bSupportPanelScaling         :1;      //panel scaler
        CBIOS_U32 bHWsupportAutoRatio          :1;
        CBIOS_U32 reserved                     :21;
    } ChipCaps;
    struct {
        //for scaler
        //upscaler
        CBIOS_U32 ulMaxPUHorSrc[CBIOS_IGACOUNTS];
        CBIOS_U32 ulMaxPUHorDst[CBIOS_IGACOUNTS];
        CBIOS_U32 ulMaxPUVerSrc[CBIOS_IGACOUNTS];
        CBIOS_U32 ulMaxPUVerDst[CBIOS_IGACOUNTS];
        //downscaler
        //effective only when ChipCaps.IsSupportDownScaling == 1
        CBIOS_U32 ulMaxPDHorSrc;
        CBIOS_U32 ulMaxPDVerSrc;
        //HDMI
        CBIOS_U32 ulMaxHDMIClock;
        //MHL
        CBIOS_U32 ulMaxMHLClock;
        CBIOS_U32 ulMaxIGAClock;
        }ChipLimits;

    /* from VCP */
    CBIOS_BOOL   bUseVCP;        //whether we use VCP or not
    CBIOS_U32    BiosVersion;
    CBIOS_U32    EClock;
    CBIOS_U32    IClock;
    CBIOS_U32    VClock;
    CBIOS_U32    VCPClock;
    CBIOS_U32    ClkSelValue;
    CBIOS_U32    EClock2;
    CBIOS_U32    IClock2;
    CBIOS_U32    VClock2;
    CBIOS_U32    VCPClock2;
    CBIOS_U32    ClkSelValue2;
    CBIOS_U32    EVcoLow;
    CBIOS_U32    DVcoLow;
    CBIOS_U32    sizeofBootDevPriority;
    PCBIOS_U16   pBootDevPriority;
    CBIOS_FEATURE_SWITCH FeatureSwitch;

    /* data tables */
    PCBIOS_HDMI_FORMAT_MTX pHDMIFormatTable;
    CBIOS_BOOL*        pHDMISupportedFormatTable;    

    CBIOS_UCHAR        SavedReg[128];
    
    CBIOS_POST_REGISTER_TABLE PostRegTable[POST_TABLE_MAX];
    CBIOS_POST_TABLE_TYPE     PostTableId;

    PCBIOS_VOID       pSpinLock;    

    PCBIOS_VOID       pAuxMutex;

    PCBIOS_VOID       pI2CMutex[CBIOS_MAX_I2CBUS];
    
    CBIOS_U32 HPDDeviceMasks;

    CBiosSpecifyDstTimingSrc SpecifyDestTimingSrc[CBIOS_IGACOUNTS];

    CBIOS_U32          CbiosFlags;

    Shadow_Info         SysBiosInfo;

    CBIOS_UCHAR        EdidFromRegistry[CBIOS_EDIDDATABYTE];
    CBIOS_ACTIVE_TYPE  DevicesHardcodedEdid;
    CBIOS_U8           MemoryType;
    
    CBIOS_U32          PortSplitSupport;//bit definition is the same as CBIOS_ACTIVE_TYPE, 
                                         //:corresponding device port can be split
                                         //0: corresponding device port can not be split
    
    CBIOS_BOOL      bFilterUnsupportedModeFunction;
    CBIOS_U8        FilterUnsupportedModeCount;

    CBIOS_U8            I2CDelay;

    CBIOS_CHIP_FUNC_TABLE   ChipFuncTbl;

    //For CEC
    CBIOS_CEC_PARA      CECPara[CBIOS_CEC_INDEX_COUNT];

    // Buffer for debug data dump to a log file
    CBIOS_U32    DbgDataToFile[CBIOS_MAX_DUMP_DATA_SIZE];

    // Flag to indicate whether use default VCP data or the VCP get from uboot
    CBIOS_BOOL   bUseDefaultVCP;

    CBIOS_DEVICE_MANAGER       DeviceMgr;

    CBIOS_DISPLAY_MANAGER      DispMgr;

} CBIOS_EXTENSION_COMMON, *PCBIOS_EXTENSION_COMMON;


//************************* CBios sw utility functions ***************************//
CBIOS_BOOL cbCalcCustomizedTiming(PCBIOS_EXTENSION_COMMON pcbe, CBIOS_U32 XRes, CBIOS_U32 YRes, CBIOS_U32 RefreshRate, PCBIOS_TIMING_ATTRIB pTimingReg);
CBIOS_VOID cbConvertEdidTimingToTableTiming(PCBIOS_EXTENSION_COMMON pcbe, CBIOS_MODE_INFO_EXT* pEDIDDetailTiming, PCBIOS_TIMING_ATTRIB pTimingReg);
CBIOS_U32  cbConvertCBiosDevBit2VBiosDevBit(CBIOS_U32 CBiosDevices);
CBIOS_U32  cbConvertVBiosDevBit2CBiosDevBit(CBIOS_U32 VBiosDevices);
CBIOS_U16  cbCalcRefreshRate(CBIOS_U32 PixelClock, CBIOS_U16 HActive, CBIOS_U16 HBlank, CBIOS_U16 VActive, CBIOS_U16 VBlank);
CBIOS_U32  cbGetHwDacMode(PCBIOS_EXTENSION_COMMON pcbe, CBIOS_FORMAT Format);
CBIOS_U32  cbGetHw3DVideoMode(CBIOS_3D_STRUCTURE VideoFormat);
CBIOS_VOID cbGetStreamAttribute(PCBIOS_STREAM_ATTRIBUTE pStreamAttr);
CBIOS_VOID cbMulti_Matrix_CSC(CBIOS_S64 Multi_A[][3],CBIOS_S64 Multi_B[][3],CBIOS_S64 Multi_C[][3]);
CBIOS_U32  cbTran_CSCm_to_coef_fx(CBIOS_S64 coefX);
CBIOS_BOOL cbGetCscCoefMatrix(PCBIOS_CSC_ADJUST_PARA pAdajust,CBIOS_U32 informat, CBIOS_U32 outformat,CBIOS_S64 CSCm[][3]);
CBIOS_U32  cbGetHwColorKey(PCBIOS_OVERLAY_INFO pOverlayInfo, PCBIOS_U16 pKeyMode, PCBIOS_U16 pKs, PCBIOS_U16 pKp);
CBIOS_BOOL cbCECAllocateLogicalAddr(PCBIOS_VOID pvcbe, CBIOS_CEC_INDEX CECIndex);
CBIOS_U32  cbConvertDeviceBit2Index(CBIOS_U32 DeviceBit);
CBIOS_U8   cbGetBitsNum(CBIOS_U32 N);
CBIOS_U32  cbGetLastBitIndex(CBIOS_U32 i);
CBIOS_VOID cbDumpBuffer(PCBIOS_EXTENSION_COMMON pcbe, CBIOS_U8 Buffer[], CBIOS_U32 ulLen);
CBIOS_BOOL cbIsSameMonitor(CBIOS_U8 *pCurDeviceEDID, CBIOS_U8 *pMonitorID);
CBIOS_BOOL cbPrintU8String(CBIOS_U8 *Src,CBIOS_U32 Len,CBIOS_U16 Start);
CBIOS_BOOL cbPrintU32String(CBIOS_U32 *Src,CBIOS_U32 Len,CBIOS_U16 Start);
CBIOS_VOID cbDbgPrintNull(CBIOS_U32 DebugPrintLevel, PCBIOS_CHAR DebugMessage, ...);
CBIOS_STATUS cbGetVersion(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_VERSION pCbiosVersion);
CBIOS_BOOL cbGetFakeEdidFlag(PCBIOS_VOID pvcbe);
//************************* End sw utility functions ***************************//


//************************* CBios sw Init functions ***************************//
CBIOS_BOOL cbInitialize(PCBIOS_VOID pvcbe, PCBIOS_PARAM_INIT pCBParamInit);
//************************* End sw Init functions ***************************//

#endif //_CBIOS_CHIPSHARE_H_
