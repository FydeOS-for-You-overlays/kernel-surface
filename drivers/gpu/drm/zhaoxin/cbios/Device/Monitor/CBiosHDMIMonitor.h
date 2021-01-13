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
** HDMI monitor interface function prototype and parameter definition.
**
** NOTE:
** HDMI monitor ONLY parameters SHOULD be added to CBIOS_HDMI_MONITOR_CONTEXT.,
** no matter the monitor is on DP port or MHL port.
******************************************************************************/

#ifndef _CBIOS_HDMI_MONITOR_H_
#define _CBIOS_HDMI_MONITOR_H_

#include "../CBiosDeviceShare.h"

#define CBIOS_AVI_INFO_FRAME_LEN    13

//*************************************************************************************
//   MACROs for CEC
//************************************************************************************/
#define     CEC_UNREGISTERED_DEVICE         0x0F
#define     CEC_BROADCAST_ADDRESS           0x0F
#define     CEC_INVALID_PHYSICAL_ADDR       0xFFFF

typedef enum _CBIOS_CEC_FEATURE_OPCODE
{
    CEC_FEATURE_ABORT       = 0x00,
    CEC_IMAGE_VIEW_ON       = 0x04,
    CEC_TEXT_VIEW_ON        = 0x0D,
    CEC_ACTIVE_SOURCE       = 0x82,
    CEC_GIVE_PHYSICAL_ADDR  = 0x83,
    CEC_REPORT_PHYSCAL_ADDR = 0x84,
    CEC_REPORT_VENDOR_ID    = 0x87,
    CEC_GIVE_VENDOR_ID      = 0x8C,
    CEC_GIVE_POWER_STATUS   = 0x8F,
    CEC_REPORT_POWER_STATUS = 0x90,
    CEC_REPORT_CEC_VERSION  = 0x9E,
    CEC_GET_CEC_VERSION     = 0x9F,
}CBIOS_CEC_FEATURE_OPCODE;

typedef enum _CBIOS_VSIF_HDMI_VIDEO_FORMAT
{
    VSIF_NO_ADDITIONAL_PRESENT = 0,
    VSIF_EXTENDED_FORMAT_PRESENT,
    VSIF_3D_FORMAT_INDICATION_PRESENT,
    VSIF_VIDEO_FORMAT_LAST    
}CBIOS_VSIF_HDMI_VIDEO_FORMAT;


typedef struct _CBIOS_VENDOR_SPECIFIC_INFOFRAME_PARA
{
    CBIOS_VSIF_HDMI_VIDEO_FORMAT    VSIFVideoFormat;
    union
    {
        struct
        {
            CBIOS_U8    VICCode;
        }VSIFExtFormatPara;
        struct
        {
            CBIOS_3D_STRUCTURE Video3DStruct;
        }VSIF3DFormatPara;
    };
}CBIOS_VENDOR_SPECIFIC_INFOFRAME_PARA, *PCBIOS_VENDOR_SPECIFIC_INFOFRAME_PARA;

typedef enum _CBIOS_HF_VSIF_3D_VIEW_DEPENDENCY
{
    HF_VSIF_3D_VIEW_DEPENDENCY_NO_INDICATION = 0,
    HF_VSIF_3D_VIEW_DEPENDENCY_RIGHT,
    HF_VSIF_3D_VIEW_DEPENDENCY_LEFT,
    HF_VSIF_3D_VIEW_DEPENDENCY_BOTH,   
}CBIOS_HF_VSIF_3D_VIEW_DEPENDENCY;

typedef enum _CBIOS_HF_VSIF_3D_PREFERRED_2D_VIEW
{
    HF_VSIF_3D_PREFERRED_2D_VIEW_NO_INDICATION = 0,
    HF_VSIF_3D_PREFERRED_2D_VIEW_RIGHT,
    HF_VSIF_3D_PREFERRED_2D_VIEW_LEFT,
    HF_VSIF_3D_PREFERRED_2D_VIEW_NOT_CARE,   
}CBIOS_HF_VSIF_3D_PREFERRED_2D_VIEW;

typedef struct _CBIOS_HF_VENDOR_SPECIFIC_INFOFRAME_PARA
{
    struct
    {
        CBIOS_U8 Valid3D                    :1;
        CBIOS_U8 IsEnable3DOSDDisparity     :1;
        CBIOS_U8 IsEnable3DDualView         :1;
        CBIOS_U8 IsEnable3DIndependentView  :1;
    };
    CBIOS_3D_STRUCTURE          Video3DFStruct;
    CBIOS_3D_DISPARITY_PARA     DisparityPara;
    CBIOS_3D_INDEPENDENT_VIEW   IndependentViewPara;
}CBIOS_HF_VENDOR_SPECIFIC_INFOFRAME_PARA, *PCBIOS_HF_VENDOR_SPECIFIC_INFOFRAME_PARA;


typedef enum _CBIOS_GBD_FORMAT
{
    VERTICES_FACETS_GBD_STRUCT = 0,
    RANGE_GBD_STRUCT
}CBIOS_GBD_FORMAT;

typedef enum _CBIOS_VERTICES_GBD_COLOR_SPACE
{
    GBD_VERTICES_COLOR_SPACE_BT709 = 0,
    GBD_VERTICES_COLOR_SPACE_XVYCC_601,
    GBD_VERTICES_COLOR_SPACE_XVYCC_709,
    GBD_VERTICES_COLOR_SPACE_XYZ
}CBIOS_VERTICES_GBD_COLOR_SPACE;

typedef enum _CBIOS_RANGE_GBD_COLOR_SPACE
{
    GBD_RANGE_COLOR_SPACE_RSVD = 0,
    GBD_RANGE_COLOR_SPACE_XVYCC_601,
    GBD_RANGE_COLOR_SPACE_XVYCC_709
}CBIOS_RANGE_GBD_COLOR_SPACE;

//CEA-861-F Table 5
typedef enum _CBIOS_INFO_FRAME_TYPE
{
    RESERVED_INFO_FRAME_TYPE = 0,
    VENDOR_SPECIFIC_INFO_FRAME_TYPE,
    AVI_INFO_FRAME_TYPE,
    SOURCE_PRODUCT_DESCRIPTION_INFO_FRAME_TYPE,
    AUDIO_INFO_FRAME_TYPE,
    MPEG_SOURCE_INFO_FRAME_TYPE,
    NTSC_VBI_INFO_FRAME_TYPE,
    //0x07-0x1F reserved for future use
    //0x20-0xFF Forbidden
}CBIO_INFO_FRAME_TYPE;


typedef struct _CBIOS_VERTICES_GBD_PARA 
{
    CBIOS_VERTICES_GBD_COLOR_SPACE  ColorSpace;
    CBIOS_U16   VerticesNum;
    CBIOS_BOOL  bFacetMode;
    CBIOS_U16   FacetsNum;  
    CBIOS_U8    *pVerticesData;
    CBIOS_U32   VerticesDataSize;
    CBIOS_U8    *pFacetsData;
    CBIOS_U32   FacetsDataSize;
}CBIOS_VERTICES_GBD_PARA, *PCBIOS_VERTICES_GBD_PARA;

typedef struct _CBIOS_RANGE_GBD_PARA 
{
    CBIOS_RANGE_GBD_COLOR_SPACE ColorSpace;
    CBIOS_U8    *pRangeData;
    CBIOS_U32   RangeDataSize;
}CBIOS_RANGE_GBD_PARA, *PCBIOS_RANGE_GBD_PARA;

typedef union _CBIOS_GBD_DATA
{
    CBIOS_VERTICES_GBD_PARA VerticesGBD;
    CBIOS_RANGE_GBD_PARA    RangeGBD;
}CBIOS_GBD_DATA, *PCBIOS_GBD_DATA;

typedef struct _CBIOS_GAMUT_METADATA_PARA
{
    CBIOS_GBD_FORMAT    FormatFlag;
    CBIOS_U8            GBDColorPrecision;
    CBIOS_GBD_DATA      GBDData;
}CBIOS_GAMUT_METADATA_PARA, *PCBIOS_GAMUT_METADATA_PARA;

typedef struct _CBIOS_AVI_INFO_FRAME_DATA
{
    //Data Byte 1
    CBIOS_U8    ScanInfo                :2;
    CBIOS_U8    BarInfo                 :2;
    CBIOS_U8    ActFormatInfoPreset     :1;
    CBIOS_U8    ColorFormat             :3; // CEA-861-F Version 3 [3 bits]
    //Data Byte 2
    CBIOS_U8    ActFormatAspectRatio    :4;
    CBIOS_U8    PictureAspectRatio      :2;
    CBIOS_U8    Colorimetry             :2;
    //Data Byte 3
    CBIOS_U8    NonUniformScaling       :2;
    CBIOS_U8    RGBQuantRange           :2;
    CBIOS_U8    ExtendedColorimetry     :3;
    CBIOS_U8    ITContent               :1;
    //Data Byte 4
    CBIOS_U8    VICCode                 :8; // CEA-861-F Version 3 [8 bits]
    //Data Byte 5
    CBIOS_U8    PixelRepeatFactor       :4;
    CBIOS_U8    ContentType             :2;
    CBIOS_U8    YCCQuantRange           :2;
    //Data Byte 6-13, bar info
    CBIOS_U8    EndTopBarLineL;         //Line Number of End of Top Bar (lower 8 bits)
    CBIOS_U8    EndTopBarLineH;         //Line Number of End of Top Bar (upper 8 bits)
    CBIOS_U8    StartBottomBarLineL;    //Line Number of Start of Bottom Bar (lower 8 bits)
    CBIOS_U8    StartBottomBarLineH;    //Line Number of Start of Bottom Bar (upper 8 bits)
    CBIOS_U8    EndLeftBarPixelL;       //Pixel Number of End of Left Bar (lower 8 bits)
    CBIOS_U8    EndLeftBarPixelH;       //Pixel Number of End of Left Bar (upper 8 bits)
    CBIOS_U8    StartRightBarPixelL;    //Pixel Number of Start of Right Bar (lower 8 bits)
    CBIOS_U8    StartRightBarPixelH;    //Pixel Number of Start of Right Bar (upper 8 bits)
}CBIOS_AVI_INFO_FRAME_DATA, *PCBIOS_AVI_INFO_FRAME_DATA;

typedef struct _CBIOS_AUDIO_INFO_FRAME_DATA
{
    //Data Byte 1
    CBIOS_U8    ChannelCount            :3;
    CBIOS_U8    Rsvd1                   :1;
    CBIOS_U8    CodingType              :4;
    //Data Byte 2
    CBIOS_U8    SampleSize              :2;
    CBIOS_U8    SampleFrequency         :3;
    CBIOS_U8    Rsvd2                   :3;
    //Data Byte 3
    CBIOS_U8    Format;
    //Data Byte 4
    CBIOS_U8    ChannelAllocation;
    //Data Byte 5
    CBIOS_U8    LEFPlaybackLevel        :2;
    CBIOS_U8    Rsvd3                   :1;
    CBIOS_U8    LevelShiftValue         :4;
    CBIOS_U8    DownmixInhibit          :1;
}CBIOS_AUDIO_INFO_FRAME_DATA, *PCBIOS_AUDIO_INFO_FRAME_DATA;

typedef struct _CBIOS_HDR_INFO_FRAME
{ 
    union
    {
        struct
        {   
            CBIOS_U8    EOTF    :3;
            CBIOS_U8    Reserved_1  :5;
        };
        CBIOS_U8    EOTF_of_STREAM;
    };
    // 0: tradition SDR 1: tradition HDR(max luminance of sink) 
    // 2: SMPTE ST 2084 3:Hybrid Log-Gamma 
    union
    {
        struct
        {   
            CBIOS_U8    Descriptor_ID    :3;
            CBIOS_U8    Reserved_2  :5;
        };
        CBIOS_U8    DescriptorID_of_Metadata;
    };    
    //0: static metadata type 1
    /***
    CBIOS_U8    display_primary_x0_LSB;
    CBIOS_U8    display_primary_x0_MSB;
    CBIOS_U8    display_primary_y0_LSB;
    CBIOS_U8    display_primary_y0_MSB;
    CBIOS_U8    display_primary_x1_LSB;
    CBIOS_U8    display_primary_x1_MSB;
    CBIOS_U8    display_primary_y1_LSB;
    CBIOS_U8    display_primary_y1_MSB;
    CBIOS_U8    display_primary_x2_LSB;
    CBIOS_U8    display_primary_x2_MSB;
    CBIOS_U8    display_primary_y2_LSB;
    CBIOS_U8    display_primary_y2_MSB;

    CBIOS_U8    white_point_x_LSB;
    CBIOS_U8    white_point_x_MSB;
    CBIOS_U8    white_point_y_LSB;
    CBIOS_U8    white_point_y_MSB;

    CBIOS_U8    max_diaplay_master_luminance_LSB;
    CBIOS_U8    max_diaplay_master_luminance_MSB;
    CBIOS_U8    min_diaplay_master_luminance_LSB;
    CBIOS_U8    min_diaplay_master_luminance_MSB;

    CBIOS_U8    max_content_light_LSB;
    CBIOS_U8    max_content_light_MSB;
    CBIOS_U8    average_content_light_LSB;
    CBIOS_U8    average_content_light_MSB;
    ***/
    CBIOS_U8 Metadata[24];
}CBIOS_HDR_INFO_FRAME_DATA, *PCBIOS_HDR_INFO_FRAME_DATA;

typedef struct _CBIOS_HDMI_INFO_FRAME_DATA 
{
    CBIOS_VENDOR_SPECIFIC_INFOFRAME_PARA    VSIFPara;
    CBIOS_HF_VENDOR_SPECIFIC_INFOFRAME_PARA HFVSIFPara;
    CBIOS_GAMUT_METADATA_PARA               GamutMetadata;
    CBIOS_AVI_INFO_FRAME_DATA               AVIInfoFrameData;
    CBIOS_HDR_INFO_FRAME_DATA               HDRInfoFrameData;
    CBIOS_U32                               HDMIMaxPacketNum;
    CBIOS_U32                               FIFO_used;
    CBIOS_U32                               Metadata_enable;
    CBIOS_BOOL                              bIsCEAMode;
}CBIOS_HDMI_INFO_FRAME_DATA, *PCBIOS_HDMI_INFO_FRAME_DATA;

typedef struct _CBIOS_CEC_MESSAGE
{
    CBIOS_U8    SourceAddr;     // Initiator Logical Address
    CBIOS_U8    DestAddr;       // Destination Logical Address
    CBIOS_U32   CmdLen;         // CEC Initiator command length. The valid value is [0:16]
    CBIOS_U8    Command[16];    // Initiator Command sent by CEC
    CBIOS_BOOL  bBroadcast;     // = TRUE: broadcast; = FALSE: direct access  
    CBIOS_U8    RetryCnt;       // CEC Initiator Retry times. Valid values must be 1 to 5.
}CBIOS_CEC_MESSAGE, *PCBIOS_CEC_MESSAGE;

typedef struct _CBIOS_CEC_PARA
{
    CBIOS_BOOL  CECEnable;      // =TRUE: CEC is enabled; = FALSE: CEC is disabled     
    CBIOS_U16   PhysicalAddr;   // physical address of our board
    CBIOS_U8    LogicalAddr;    // logical address of our board
}CBIOS_CEC_PARA, *PCBIOS_CEC_PARA;

typedef struct _CBIOS_SCDC_UPDATE_FLAGS
{
    union
    {
        struct
        {
            struct
            {
                CBIOS_U8    StatusUpdate    :1;
                CBIOS_U8    CEDUpdate       :1;
                CBIOS_U8    RRTest          :1;
                CBIOS_U8    Rsvd            :5;
            }Update_0;
            struct
            {
                CBIOS_U8    Rsvd    :8;
            }Update_1;
        };
        CBIOS_U16 UpdateFlags;
    };
}CBIOS_SCDC_UPDATE_FLAGS,*PCBIOS_SCDC_UPDATE_FLAGS;

typedef struct _CBIOS_SCDC_STATUS_FLAGS
{
    union
    {
        struct
        {
            CBIOS_U8    Scrambling_Status   :1;
            CBIOS_U8    Rsvd                :7;
        };
        CBIOS_U8 ScramblerStatus;
    };
    union
    {
        struct
        {
            struct
            {
                CBIOS_U8    ClockDetected   :1;
                CBIOS_U8    Ch0_Locked      :1;
                CBIOS_U8    Ch1_Locked      :1;
                CBIOS_U8    Ch2_Locked      :1;
                CBIOS_U8    Rsvd            :4;
            }Status_Flags_0;
            struct
            {
                CBIOS_U8    Rsvd    :8;
            }Status_Flags_1;
        };
        CBIOS_U16 Status_Flags;
    };
}CBIOS_SCDC_STATUS_FLAGS,*PCBIOS_SCDC_STATUS_FLAGS;

typedef struct _CBIOS_SCDC_CED_DATA
{
    CBIOS_U8    Ch0_Err_CountBits7To0   :8;
    CBIOS_U8    Ch0_Err_CountBits14To8  :7;
    CBIOS_U8    Ch0_Valid               :1;
    CBIOS_U8    Ch1_Err_CountBits7To0   :8;
    CBIOS_U8    Ch1_Err_CountBits14To8  :7;
    CBIOS_U8    Ch1_Valid               :1;
    CBIOS_U8    Ch2_Err_CountBits7To0   :8;
    CBIOS_U8    Ch2_Err_CountBits14To8  :7;
    CBIOS_U8    Ch2_Valid               :1;
    CBIOS_U8    CHECKSUM                :8;
}CBIOS_SCDC_CED_DATA,*PCBIOS_SCDC_CED_DATA;

typedef struct _CBIOS_HDMI_MONITOR_CONTEXT
{
    PCBIOS_DEVICE_COMMON pDevCommon;
    CBIOS_HDMI_INFO_FRAME_DATA HDMIInfoFrame;
    CBIOS_U8 TMDSBitClockRatio;// =0 means 1:10, =1 means 1:40
    CBIOS_U32 HDMIClock;        // HDMI clock
    CBIOS_BOOL ReadRequestEnable;
    CBIOS_BOOL ScramblingEnable;
}CBIOS_HDMI_MONITOR_CONTEXT, *PCBIOS_HDMI_MONITOR_CONTEXT;

CBIOS_VOID cbHDMIMonitor_SetHDACConnectStatus(PCBIOS_VOID pvcbe, PCBIOS_HDAC_PARA pCbiosHDACPara);
CBIOS_BOOL cbHDMIMonitor_Detect(PCBIOS_VOID pvcbe, PCBIOS_HDMI_MONITOR_CONTEXT pHDMIMonitorContext, CBIOS_BOOL bHardcodeDetected);
CBIOS_VOID cbHDMIMonitor_UpdateModeInfo(PCBIOS_VOID pvcbe, PCBIOS_HDMI_MONITOR_CONTEXT pHDMIMonitorContext, PCBIOS_DISP_MODE_PARAMS pModeParams);
CBIOS_VOID cbHDMIMonitor_SetMode(PCBIOS_VOID pvcbe, PCBIOS_HDMI_MONITOR_CONTEXT pHDMIMonitorContext, PCBIOS_DISP_MODE_PARAMS pModeParams);
CBIOS_VOID cbHDMIMonitor_OnOff(PCBIOS_VOID pvcbe, PCBIOS_HDMI_MONITOR_CONTEXT pHDMIMonitorContext, CBIOS_BOOL bOn);
CBIOS_VOID cbHDMIMonitor_QueryAttribute(PCBIOS_VOID pvcbe, PCBIOS_HDMI_MONITOR_CONTEXT pHDMIMonitorContext, PCBiosMonitorAttribute pMonitorAttribute);
CBIOS_BOOL cbHDMIMonitor_SCDC_Handler(CBIOS_VOID* pvcbe, PCBIOS_DEVICE_COMMON pDevCommon);
CBIOS_VOID cbHDMIMonitor_SetInfoFrame(PCBIOS_VOID pvcbe, PCBIOS_HDMI_INFO_FRAME_DATA pInfoFrameData, CBIOS_ACTIVE_TYPE DeviceType);

#endif
