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

typedef struct
{
    UINT8 (*pbGetDisplayID)(void);
    UINT8 (*pbGetSubrevision)(void);
}IIC_IL_DISPALY_IDENTIFICATION_FUNCTION_ST,*IIC_IL_DISPALY_IDENTIFICATION_FUNCTION_PST;

typedef struct
{
    UINT8 (*pbGetLCDBacklightPwmValue)(void);
}IIC_IL_LCD_BACKLIGHT_PWM_VALUE_FUNCTION_ST,*IIC_IL_LCD_BACKLIGHT_PWM_VALUE_FUNCTION_PST;


static void vIIC_IL_RxMsg_0x00_ExecuteFunction(const UINT8 * const pu8buf);
static void vIIC_IL_RxMsg_0x01_ExecuteFunction(const UINT8 * const pu8buf);
static void vIIC_IL_RxMsg_0x02_ExecuteFunction(const UINT8 * const pu8buf);


static const IIC_IL_DISPALY_STATUS_FUNCTION_ST st_IIC_il_Dispaly_Status_Fcuntion = \
    IIC_IL_DISPALY_STATUS_FUNCTION_CFG;

static const IIC_IL_DISPALY_IDENTIFICATION_FUNCTION_ST st_IIC_il_Dispaly_Identification_Fcuntion = \
    IIC_IL_DISPALY_IDENTIFICATION_FUNCTION_CFG;

static const IIC_IL_LCD_BACKLIGHT_PWM_VALUE_FUNCTION_ST st_IIC_il_LCD_Backlight_Pwm_Value_Fcuntion = \
    IIC_IL_LCD_BACKLIGHT_PWM_VALUE_FUNCTION_CFG;

static const IIC_IL_FRAME_ST st_IIC_il_Frame[] =    \
{
    IIC_IL_FRAME_CFG
    {0xFF, NULL}
};

/* CAN  NOT USE FOR RTOS */
static UINT8 u8TXbuf[IIC_DATA_MAX_SIZE];

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

void vIIC_IL_RxMsg_0x00_UserExecuteFunction(UINT8 * const pu8Statusbuf)
{

}

static void vIIC_IL_RxMsg_0x00_ExecuteFunction(const UINT8 * const pu8buf)
{
    /*
        Determine whether the member function of st_IIC_il_Dispaly_Status_Fcuntion is NULL.
        if is NULL, clear correspoind bit and output message.
    */
    const IIC_IL_DISPALY_STATUS_FUNCTION_PST pstDisplayStatus = &st_IIC_il_Dispaly_Status_Fcuntion;

     /*
        The I2C Slave shall leave SDA undriven resulting in Data = 0xFF when 
        communication abnormal.
    */
    memset(u8TXbuf,0xFF,IIC_DATA_MAX_SIZE);

    /*
        Fill CMDID in buf.
    */
    u8TXbuf[0] = (UINT8)0x00;

    /* @TCERR */
    if( NULL != pstDisplayStatus->pbGetTouchConnectionError )
    {
        u8TXbuf[1] |= IIC_IL_TCERR_CTRL(pstDisplayStatus->pbGetTouchConnectionError());
    }
    else
    {
        u8TXbuf[1] |= IIC_IL_TCERR_CTRL(0);
        /* reserve area for output message. */
        OUTPUT_ERROR_MESSAGE();
    }
    
    /* @TSCERR */
    if( NULL != pstDisplayStatus->pbGetTouchScreenControllerError)
    {
        u8TXbuf[1] |= IIC_IL_TSCERR_CTRL(pstDisplayStatus->pbGetTouchConnectionError());
    }
    else
    {
        u8TXbuf[1] |= IIC_IL_TSCERR_CTRL(0);
        /* reserve area for output message. */
        OUTPUT_ERROR_MESSAGE();
    }

    /* @LLOSS */
    if( NULL != pstDisplayStatus->pbGetLossOfLock)
    {
        u8TXbuf[1] |= IIC_IL_LLOSS_CTRL(pstDisplayStatus->pbGetLossOfLock());
    }
    else
    {
        u8TXbuf[1] |= IIC_IL_LLOSS_CTRL(0);
        /* reserve area for output message. */
        OUTPUT_ERROR_MESSAGE();
    }

    /* @RST_RQ */
    if( NULL != pstDisplayStatus->pbGetResetRequest)
    {
        u8TXbuf[1] |= IIC_IL_RST_RQ_CTRL(pstDisplayStatus->pbGetResetRequest());
    }
    else
    {
        u8TXbuf[1] |= IIC_IL_RST_RQ_CTRL(0);
        /* reserve area for output message. */
        OUTPUT_ERROR_MESSAGE();
    }

    /* @DCERR */
    if( NULL != pstDisplayStatus->pbGetDisconnectError)
    {
        u8TXbuf[1] |= IIC_IL_DCERR_CTRL(pstDisplayStatus->pbGetDisconnectError());
    }
    else
    {
        u8TXbuf[1] |= IIC_IL_DCERR_CTRL(0);
        /* reserve area for output message. */
        OUTPUT_ERROR_MESSAGE();
    }

    /* @TERR */
    if( NULL != pstDisplayStatus->pbGetTemperatureDerating)
    {
        u8TXbuf[1] |= IIC_IL_TERR_CTRL(pstDisplayStatus->pbGetTemperatureDerating());
    }
    else
    {
        u8TXbuf[1] |= IIC_IL_TERR_CTRL(0);
        /* reserve area for output message. */
        OUTPUT_ERROR_MESSAGE();
    }

    /* @BLERR */
    if( NULL != pstDisplayStatus->pbGetLCDBacklightError)
    {
        u8TXbuf[1] |= IIC_IL_BLERR_CTRL(pstDisplayStatus->pbGetLCDBacklightError());
    }
    else
    {
        u8TXbuf[1] |= IIC_IL_BLERR_CTRL(0);
        /* reserve area for output message. */
        OUTPUT_ERROR_MESSAGE();
    }

    /* @LCDERR */
    if( NULL != pstDisplayStatus->pbGetLCDError)
    {
        u8TXbuf[1] |= IIC_IL_LCDERR_CTRL(pstDisplayStatus->pbGetLCDError());
    }
    else
    {
        u8TXbuf[1] |= IIC_IL_LCDERR_CTRL(0);
        /* reserve area for output message. */
        OUTPUT_ERROR_MESSAGE();
    }

    /*@BIT[7-3] RESERVED, clear unused bit */
    u8TXbuf[2] &= (UINT8)0x07;
    /*ADD FUNCTION CALL FOR USER*/
    vIIC_IL_RxMsg_0x00_UserExecuteFunction(&u8TXbuf[2]);

    /* @INIT */
    if( NULL != pstDisplayStatus->pbGetDisplayInitialized)
    {
        u8TXbuf[2] |= IIC_IL_INIT_CTRL(pstDisplayStatus->pbGetDisplayInitialized());
    }
    else
    {
        u8TXbuf[2] |= IIC_IL_INIT_CTRL(0);
        /* reserve area for output message. */
        OUTPUT_ERROR_MESSAGE();
    } 

    /* @TSC_ST */
    if( NULL != pstDisplayStatus->pbGetTouchControllerStatus)
    {
        u8TXbuf[2] |= IIC_IL_TSC_ST_CTRL(pstDisplayStatus->pbGetTouchControllerStatus());
    }
    else
    {
        u8TXbuf[2] |= IIC_IL_TSC_ST_CTRL(0);
        /* reserve area for output message. */
        OUTPUT_ERROR_MESSAGE();
    }

    /* @DISP_ST */
    if( NULL != pstDisplayStatus->pbGetDispalyStatus)
    {
        u8TXbuf[2] |= IIC_IL_DISP_ST_CTRL(pstDisplayStatus->pbGetDispalyStatus());
    }
    else
    {
        u8TXbuf[2] |= IIC_IL_DISP_ST_CTRL(0);
        /* reserve area for output message. */
        OUTPUT_ERROR_MESSAGE();
    }

    IIC_FIFO_gvTxWrite(u8TXbuf);
}

void vIIC_IL_RxMsg_0x01_ExecuteFunction(const UINT8 * const pu8buf)
{
    const IIC_IL_DISPALY_IDENTIFICATION_FUNCTION_PST pstDisplayIdentification = &st_IIC_il_Dispaly_Identification_Fcuntion;

     /*
        The I2C Slave shall leave SDA undriven resulting in Data = 0xFF when 
        communication abnormal.
    */
    memset(u8TXbuf,0xFF,IIC_DATA_MAX_SIZE);

    /*
        Fill CMDID in buf.
    */
    u8TXbuf[0] = (UINT8)0x01;

    if( NULL != pstDisplayIdentification->pbGetDisplayID)
    {
        u8TXbuf[1] = pstDisplayIdentification->pbGetDisplayID();
    }
    else
    {
        /* reserve area for output message. */
        OUTPUT_ERROR_MESSAGE();
    }

    if( NULL != pstDisplayIdentification->pbGetSubrevision)
    {
        u8TXbuf[2] = pstDisplayIdentification->pbGetSubrevision();
    }
    else
    {
        /* reserve area for output message. */
        OUTPUT_ERROR_MESSAGE();
    }

    IIC_FIFO_gvTxWrite(u8TXbuf);
}

void vIIC_IL_RxMsg_0x02_ExecuteFunction(const UINT8 * const pu8buf)
{
    /*
        Stroe temp pwm.
    */
    UINT16 tempPWm;

    const IIC_IL_LCD_BACKLIGHT_PWM_VALUE_FUNCTION_PST pstLCDBacklightPwmValue = &st_IIC_il_LCD_Backlight_Pwm_Value_Fcuntion;

     /*
        The I2C Slave shall leave SDA undriven resulting in Data = 0xFF when 
        communication abnormal.
    */
    memset(u8TXbuf,0xFF,IIC_DATA_MAX_SIZE);

    /*
        Fill CMDID in buf.
    */
    u8TXbuf[0] = (UINT8)0x02;

    if( NULL != pstLCDBacklightPwmValue->pbGetLCDBacklightPwmValue)
    {
        tempPWm = (UINT16)(pstLCDBacklightPwmValue->pbGetLCDBacklightPwmValue());

        tempPWm = tempPWm * (UINT8)10;

        u8TXbuf[1] = (UINT8)(tempPWm & (UINT16)(0xFF));    /* store [7:0] */

        u8TXbuf[2] = (UINT8)(tempPWm >> (UINT8)8);         /* store [9:8] */
    }
    else
    {
        /* reserve area for output message. */
        OUTPUT_ERROR_MESSAGE();
    }

}
void vIIC_IL_Determine_Change(void)
{
    //检测变化，先锁存数值，产生中断，读取数据，再检测，在锁存，
    GENERATE_INTERRUPT();
}






