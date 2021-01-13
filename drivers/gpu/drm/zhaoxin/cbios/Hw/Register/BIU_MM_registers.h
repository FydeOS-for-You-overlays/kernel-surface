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


typedef union _REG_MM9340    //GRX_Frame_Buffer_Base_Address_Low_Register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    GFX_FB_BASE_ADDR    :12;
        CBIOS_U32    Reserved    :20;
    };
}REG_MM9340;


typedef union _REG_MM9344    //INT_USS_Address_Low_Register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    INT_USS_ADDR_31to0    :32;
    };
}REG_MM9344;


typedef union _REG_MM9348    //INT_USS_Address_High_Register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    INT_USS_ADDR_63to32    :32;
    };
}REG_MM9348;


typedef union _REG_MM934C    //INT_USS_Data_Low_Register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    INT_USS_DATA_31to0    :32;
    };
}REG_MM934C;


typedef union _REG_MM9350    //INT_USS_Data_High_Register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    INT_USS_DATA_63to32    :32;
    };
}REG_MM9350;


typedef union _REG_MM9358    //BIU_MXU_Subindex_Control_Register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    Reserved    :7;
        CBIOS_U32    BIU_MXU_SUBINDEX_EN    :1;
        CBIOS_U32    RESERVED    :24;
    };
}REG_MM9358;


typedef union _REG_MM935C    //CLK_select_register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    ICLK_SEL    :2;
        CBIOS_U32    SCLK_SEL    :2;
        CBIOS_U32    VCLK_SEL    :2;
        CBIOS_U32    FUNC_PLL_MON_ON    :1;
        CBIOS_U32    FUNC_PLL_MON_SEL    :2;
        CBIOS_U32    FUNC_PLL_MON_DIV    :3;
        CBIOS_U32    Reserved    :20;
    };
}REG_MM935C;


typedef union _REG_MM9360    //Performance_Upstream_Utilization_Counter_Low_Register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    UP_STRM_UTIL_31to0    :32;
    };
}REG_MM9360;


typedef union _REG_MM9364    //Performance_Upstream_Utilization_Counter_High_Register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    UP_STRM_UTIL_47to32    :16;
        CBIOS_U32    RESERVED    :16;
    };
}REG_MM9364;


typedef union _REG_MM9368    //Performance_HDA_ACK_Counter_Low_Register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    HDA_ACK_31to0    :32;
    };
}REG_MM9368;


typedef union _REG_MM936C    //Performance_HDA_ACK_Counter_High_Register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    HDA_ACK_47to32    :16;
        CBIOS_U32    RESERVED    :16;
    };
}REG_MM936C;


typedef union _REG_MM9370    //Performance_Downstream_Utilization_Counter_Low_Register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    DOWN_STRM_UTIL__31to0    :32;
    };
}REG_MM9370;


typedef union _REG_MM9374    //Performance_Downstream_Utilization_Counter_High_Register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    DOWN_STRM_UTIL_47to32    :16;
        CBIOS_U32    RESERVED    :16;
    };
}REG_MM9374;


typedef union _REG_MM9378    //Performance_DZT_MXU_Idle_Counter_Low_Register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    DZT_Idle_Ctr_31to0    :32;
    };
}REG_MM9378;


typedef union _REG_MM937C    //Performance_DZT_MXU_Idle_Counter_High_Register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    DZT_Idle_Ctr_47to32    :16;
        CBIOS_U32    RESERVED    :16;
    };
}REG_MM937C;


typedef union _REG_MM9380    //Performance_DZT_MXU_ACK_Counter_Low_Register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    DZT_ACK_Ctr_31to0    :32;
    };
}REG_MM9380;


typedef union _REG_MM9384    //Performance_DZT_MXU_ACK_Counter_High_Register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    DZT_ACK_Ctr_47to32    :16;
        CBIOS_U32    RESERVED    :16;
    };
}REG_MM9384;


typedef union _REG_MM9388    //Performance_DZT_MXU_Pending_Counter_Low_Register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    DZT_Pending_Ctr_31to0    :32;
    };
}REG_MM9388;


typedef union _REG_MM938C    //Performance_DZT_MXU_Pending_Counter_High_Register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    DZT_Pending_Ctr_47to32    :16;
        CBIOS_U32    RESERVED    :16;
    };
}REG_MM938C;


typedef union _REG_MM9390    //Performance_VPT_Idle_Counter_Low_Register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    VPT_Idle_Ctr_31to0    :32;
    };
}REG_MM9390;


typedef union _REG_MM9394    //Performance_VPT_Idle_Counter_High_Register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    VPT_Idle_Ctr_47to32    :16;
        CBIOS_U32    RESERVED    :16;
    };
}REG_MM9394;


typedef union _REG_MM9398    //Performance_VPT_ACK_CounterLow_Register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    VPT_ACK_Ctr_31to0    :32;
    };
}REG_MM9398;


typedef union _REG_MM939C    //Performance_VPT_ACK_Counter_High_Register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    VPT_ACK_Ctr_47to32    :16;
        CBIOS_U32    RESERVED    :16;
    };
}REG_MM939C;


typedef union _REG_MM93A0    //Performance_VPT_Pending_Counter_Low_Register
{
    CBIOS_U32    Value;
    struct
    {
        CBIOS_U32    VPT_Pending_Ctr_31to0    :32;
    };
}REG_MM93A0;


