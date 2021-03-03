/***********************************************************************************************
                    IIC Message
    COMMAND           ACCESS            DESCRIPTION
    0x00                R               Display Status
    0x01                R               Display Identification
    0x02               R/W              LCD Backlight PWM Value
    0x03               R/W              Display Scanning
    0x04               R/W              Display Enable
    0x05               R/W              Display Shutdown
    0x06               R/W              Button Backlight PWM Value
    0x07                R               Button Status
    0x08                R               Rotary Status
    0x30                R               Interrupt Status Message (ISR)
    0x31                R               Core Assembly
    0x32                R               Delivery Assembly
    0x33                R               Software Ford Part Number
    0x34                R               Serial Number
    0x35                R               Main Calibration Ford Part Number
    0x40               R/W              Image Adjustment 
    0x41                R               Supplier Precalc Low Warping Table
    0x42                R               Supplier Precalc Medium Warping Table
    0x43                R               Supplier Precalc High Warping Table
    0x44                R               Supplier EOL Low Warping Table
    0x45                R               Supplier EOL Medium Warping Table
    0x46                R               Supplier EOL High Warping Table
    0x91               R/W              Light Ambient Sensor RAW Value
    0x92               R/W              Forward Collision Warning Status
    0xB0-0xFF          R/W              Reserved for Supplier


typical write : addr + cmdid + any data         Big-Endian
typical read  : 1、[typical write] 
                2、addr + cmdid + any data
************************************************************************************************/
#include "iic_il.h"

typedef struct IIC_IL_FRAME
{
    UINT8 u8Frame_CmdId;
    void (* pvExecuteFunction)(const UINT8 * const pu8buf);
}IIC_IL_FRAME_ST;

typedef struct
{
    BOOL (*pbGetTouchConnectionError)(void);
    BOOL (*pbGetTouchScreenControllerError)(void);
    BOOL (*pbGetLossOfLock)(void);
    BOOL (*pbGetResetRequest)(void);
    BOOL (*pbGetDisconnectError)(void);
    BOOL (*pbGetTemperatureDerating)(void);
    BOOL (*pbGetLCDBacklightError)(void);
    BOOL (*pbGetLCDError)(void);
    BOOL (*pbGetDisplayInitialized)(void);
    BOOL (*pbGetTouchControllerStatus)(void);
    BOOL (*pbGetDispalyStatus)(void);
}IIC_IL_DISPALY_STATUS_FUNCTION_ST,*IIC_IL_DISPALY_STATUS_FUNCTION_PST;

static const IIC_IL_DISPALY_STATUS_FUNCTION_ST st_IIC_il_Dispaly_Status_Fcuntion = \
    IIC_IL_DISPALY_STATUS_FUNCTION_CFG;

static const IIC_IL_FRAME_ST st_IIC_il_Frame[] =    \
{
    {0x00,  vIIC_IL_RxMsg_0x00_ExecuteFunction},
    {0x01,  vIIC_IL_RxMsg_0x01_ExecuteFunction},
};

/*
@Display Status
bit       7        6      5      4       3      2     1       0 
[0]     TCERR   TSCERR  LLOSS  RST_RQ  DCERR  TERR  BLERR   LCDERR 
[1]       -        -      -      -       -    INIT  TSC_ST  DISP_ST

-  TCERR: Touch Connection Error (latched) (optional status)  
This bit reports latched status of the flexible printed circuit connecting PCB to Touch Panel.  
0  FPC is connected 
1  FPC is disconnected 

-  TSCERR: Touch Screen Controller Error (latched) (optional status)  
This bit reports latched status of touch panel controller 
0  No Fault 
1  Fault 

-  LLOSS: Loss of Lock (latched) 
This bit reports latched status of loss-of-lock, as indicated by the deserializer LOCK pin.
0  Lock is established 
1  Lock is lost 

-  RST_RQ: Reset Request 
This bit defaults clear, and is set when the display requires a full power-cycle reset to resolve some problem. 
0  Normal operation 
1  Request is requested 

-  DCERR: Disconnect error (latched) 
This bit reports latched status of the flexible printed circuit connecting PCB to LCD Panel. 
0  FPC is connected 
1  FPC is disconnected 

-  TERR: Temperature Derating (latched) 
This bit reports latched status of temperature derating mode. 
0  Inactive 
1  Active 

-  BLERR: LCD Backlight Error (latched) 
This bit reports latched status of LCD backlight. 
0  No Fault 
1  Fault 

-  LCDERR: LCD Error (latched) 
This bit reports latched status of LCD Panel. 
0  No Fault 
1  Fault 

-  INIT: Display Initialized 
This bit defaults clear, and is set after the display has been enabled. 
0  Display has not been enabled during this power-cycle. 
1  Display has been enabled at least once during this power-cycle. 
This bit is used by the host to detect an unexpected reset. Any transition from 1 -> 0 during normal operation 
indicates that the display may need a complete re-initialization. 

-  TSC_ST: Touch Controller Status 
This bit reflects actual status. This may be different, due to delay or an error condition, from commanded value 
(TSC_EN). 
0  Touch Screen Controller is not ready (held in reset). 
1  Touch Screen Controller is ready for use. 
If display has no touch screen controller, report 0. 

-  DISP_ST: Display Status 
This bit reflects actual status. This may be different, due to delay or an error condition, from commanded value 
(DISP_EN). 
0  Display is disabled. 
1  Display is enabled. 
*/



void vIIC_IL_RxMsg_0x00_ExecuteFunction(const UINT8 * const pu8buf)
{
    /*
        The I2C Slave shall leave SDA undriven resulting in Data = 0xFF when 
        communication abnormal.
    */
    UINT8 u8Status[3] = {0x00,0xFF,0xFF};

    /*
        Determine whether the member function of st_IIC_il_Dispaly_Status_Fcuntion is NULL.
        if is NULL, clear correspoind bit and output message.
    */
    const IIC_IL_DISPALY_STATUS_FUNCTION_PST pstDisplayStatus = &st_IIC_il_Dispaly_Status_Fcuntion;
    
    /* @TCERR */
    if( NULL != pstDisplayStatus->pbGetTouchConnectionError )
    {
        u8Status[1] |= IIC_IL_TCERR_CTRL(pstDisplayStatus->pbGetTouchConnectionError());
    }
    else
    {
        u8Status[1] |= IIC_IL_TCERR_CTRL(0);
        /* reserve area for output message. */
    }
    
    /* @TSCERR */
    if( NULL != pstDisplayStatus->pbGetTouchScreenControllerError)
    {
        u8Status[1] |= IIC_IL_TSCERR_CTRL(pstDisplayStatus->pbGetTouchConnectionError());
    }
    else
    {
        u8Status[1] |= IIC_IL_TSCERR_CTRL(0);
        /* reserve area for output message. */
    }

    /* @LLOSS */
    if( NULL != pstDisplayStatus->pbGetLossOfLock)
    {
        u8Status[1] |= IIC_IL_LLOSS_CTRL(pstDisplayStatus->pbGetLossOfLock());
    }
    else
    {
        u8Status[1] |= IIC_IL_LLOSS_CTRL(0);
        /* reserve area for output message. */
    }

    /* @RST_RQ */
    if( NULL != pstDisplayStatus->pbGetResetRequest)
    {
        u8Status[1] |= IIC_IL_RST_RQ_CTRL(pstDisplayStatus->pbGetResetRequest());
    }
    else
    {
        u8Status[1] |= IIC_IL_RST_RQ_CTRL(0);
        /* reserve area for output message. */
    }

    /* @DCERR */
    if( NULL != pstDisplayStatus->pbGetDisconnectError)
    {
        u8Status[1] |= IIC_IL_DCERR_CTRL(pstDisplayStatus->pbGetDisconnectError());
    }
    else
    {
        u8Status[1] |= IIC_IL_DCERR_CTRL(0);
        /* reserve area for output message. */
    }
}


void vIIC_IL_Determine_Change(void)
{
    //检测变化，先锁存数值，产生中断，读取数据，再检测，在锁存，
    GENERATE_INTERRUPT();
}






