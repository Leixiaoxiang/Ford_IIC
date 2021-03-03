
typedef unsigned char UINT8;
typedef UINT8 BOOL;
#define NULL    ((void *)0)

/*@IIC_IL_TCERR */
#define IIC_IL_TCERR_MASK           ((UINT8)0x80)
#define IIC_IL_TCERR_SHIFT          ((UINT8)0x07)
#define IIC_IL_TCERR_CTRL(x)        ((UINT8)(((UINT8)(x)) << IIC_IL_TCERR_SHIFT) & IIC_IL_TCERR_MASK)

/*@IIC_IL_TSCERR */
#define IIC_IL_TSCERR_MASK          ((UINT8)0x40)
#define IIC_IL_TSCERR_SHIFT         ((UINT8)0x06)
#define IIC_IL_TSCERR_CTRL(x)       ((UINT8)(((UINT8)(x)) << IIC_IL_TSCERR_SHIFT) & IIC_IL_TSCERR_MASK)


/*@IIC_IL_LLOSS */
#define IIC_IL_LLOSS_MASK           ((UINT8)0x20)
#define IIC_IL_LLOSS_SHIFT          ((UINT8)0x05)
#define IIC_IL_LLOSS_CTRL(x)        ((UINT8)(((UINT8)(x)) << IIC_IL_LLOSS_SHIFT) & IIC_IL_LLOSS_MASK)

/*@IIC_IL_RST_RQ */
#define IIC_IL_RST_RQ_MASK          ((UINT8)0x10)
#define IIC_IL_RST_RQ_SHIFT         ((UINT8)0x04)
#define IIC_IL_RST_RQ_CTRL(x)       ((UINT8)(((UINT8)(x)) << IIC_IL_RST_RQ_SHIFT) & IIC_IL_RST_RQ_MASK)

/*@IIC_IL_DCERR */
#define IIC_IL_DCERR_MASK           ((UINT8)0x08)
#define IIC_IL_DCERR_SHIFT          ((UINT8)0x03)
#define IIC_IL_DCERR_CTRL(x)        ((UINT8)(((UINT8)(x)) << IIC_IL_DCERR_SHIFT) & IIC_IL_DCERR_MASK)

/*@IIC_IL_TERR */
#define IIC_IL_TERR_MASK            ((UINT8)0x04)
#define IIC_IL_TERR_SHIFT           ((UINT8)0x02)
#define IIC_IL_TERR_CTRL(x)         ((UINT8)(((UINT8)(x)) << IIC_IL_TERR_SHIFT) & IIC_IL_TERR_MASK)

/*@IIC_IL_BLERR */
#define IIC_IL_BLERR_MASK           ((UINT8)0x02)
#define IIC_IL_BLERR_SHIFT          ((UINT8)0x01)
#define IIC_IL_BLERR_CTRL(x)        ((UINT8)(((UINT8)(x)) << IIC_IL_BLERR_SHIFT) & IIC_IL_BLERR_MASK)

/*@IIC_IL_LCDERR */
#define IIC_IL_LCDERR_MASK          ((UINT8)0x01)
#define IIC_IL_LCDERR_SHIFT         ((UINT8)0x00)
#define IIC_IL_LCDERR_CTRL(x)       ((UINT8)(((UINT8)(x)) << IIC_IL_LCDERR_SHIFT) & IIC_IL_LCDERR_MASK)

/*@BIT[7-3] RESERVED */

/*@IIC_IL_INIT */
#define IIC_IL_INIT_MASK            ((UINT8)0x04)
#define IIC_IL_INIT_SHIFT           ((UINT8)0x02)
#define IIC_IL_INIT_CTRL(x)         ((UINT8)(((UINT8)(x)) << IIC_IL_INIT_SHIFT) & IIC_IL_INIT_MASK)

/*@IIC_IL_TSC_ST */
#define IIC_IL_TSC_ST_MASK          ((UINT8)0x02)
#define IIC_IL_TSC_ST_SHIFT         ((UINT8)0x01)
#define IIC_IL_TSC_ST_CTRL(x)       ((UINT8)(((UINT8)(x)) << IIC_IL_TSC_ST_SHIFT) & IIC_IL_TSC_ST_MASK)

/*@IIC_IL_DISP_ST */
#define IIC_IL_DISP_ST_MASK         ((UINT8)0x01)
#define IIC_IL_DISP_ST_SHIFT        ((UINT8)0x00)
#define IIC_IL_DISP_ST_CTRL(x)      ((UINT8)(((UINT8)(x)) << IIC_IL_DISP_ST_SHIFT) & IIC_IL_DISP_ST_MASK)

#define IIC_IL_DISPALY_STATUS_FUNCTION_CFG  {   \
    /* BOOL (*pbGetTouchConnectionError)(void); */            NULL,   \
    /* BOOL (*pbGetTouchScreenControllerError)(void); */      NULL,   \
    /* BOOL (*pbGetLossOfLock)(void); */                      NULL,   \
    /* BOOL (*pbGetResetRequest)(void); */                    NULL,   \
    /* BOOL (*pbGetDisconnectError)(void); */                 NULL,   \
    /* BOOL (*pbGetTemperatureDerating)(void); */             NULL,   \
    /* BOOL (*pbGetLCDBacklightError)(void); */               NULL,   \
    /* BOOL (*pbGetLCDError)(void); */                        NULL,   \
    /* BOOL (*pbGetDisplayInitialized)(void); */              NULL,   \
    /* BOOL (*pbGetTouchControllerStatus)(void); */           NULL,   \
    /* BOOL (*pbGetDispalyStatus)(void); */                   NULL    \
}

#define IIC_IL_DISPALY_IDENTIFICATION_FUNCTION_CFG {    \
    /* UINT8 (*pbGetDisplayID)(void); */                      NULL,   \
    /* UINT8 (*pbGetSubrevision)(void); */                    NULL    \
}

#define IIC_IL_LCD_BACKLIGHT_PWM_VALUE_FUNCTION_CFG {   \
    /* UINT8 (*pbGetLCDBacklightPwmValue)(void); */           NULL     \
}

#define IIC_IL_FRAME_CFG    \
    {0x00,  vIIC_IL_RxMsg_0x00_ExecuteFunction},    \
    {0x01,  vIIC_IL_RxMsg_0x01_ExecuteFunction},    \
    {0x02,  vIIC_IL_RxMsg_0x02_ExecuteFunction},    \


#if ( configGENERATE_INTERRUPT == 0)
    #define GENERATE_INTERRUPT()
#else
    #define GENERATE_INTERRUPT() GenerateInterruptFunction()
#endif

#if ( configOUTPUT_ERROR_MESSAGE == 0)
    #define OUTPUT_ERROR_MESSAGE()
#else
    #define OUTPUT_ERROR_MESSAGE() Printf("%S%S",_FILE_,_LINE_)
#endif

