
typedef unsigned char UINT8;
typedef UINT8 BOOL;
#define NULL    ((void *)0)

/*@IIC_IL_TCERR */
#define IIC_IL_TCERR_CTRL(x)    ((UINT8)(((UINT8)(x)) << IIC_IL_TCERR_SHIFT) & IIC_IL_TCERR_MASK)
#define IIC_IL_TCERR_MASK       ((UINT8)0x80)
#define IIC_IL_TCERR_SHIFT      ((UINT8)0x07)

/*@IIC_IL_TSCERR */
#define IIC_IL_TSCERR_CTRL(x)    ((UINT8)(((UINT8)(x)) << IIC_IL_TSCERR_SHIFT) & IIC_IL_TSCERR_MASK)
#define IIC_IL_TSCERR_MASK       ((UINT8)0x40)
#define IIC_IL_TSCERR_SHIFT      ((UINT8)0x06)

/*@IIC_IL_LLOSS */
#define IIC_IL_LLOSS_CTRL(x)    ((UINT8)(((UINT8)(x)) << IIC_IL_LLOSS_SHIFT) & IIC_IL_LLOSS_MASK)
#define IIC_IL_LLOSS_MASK       ((UINT8)0x20)
#define IIC_IL_LLOSS_SHIFT      ((UINT8)0x05)

/*@IIC_IL_RST_RQ */
#define IIC_IL_RST_RQ_CTRL(x)    ((UINT8)(((UINT8)(x)) << IIC_IL_RST_RQ_SHIFT) & IIC_IL_RST_RQ_MASK)
#define IIC_IL_RST_RQ_MASK       ((UINT8)0x10)
#define IIC_IL_RST_RQ_SHIFT      ((UINT8)0x04)

/*@IIC_IL_DCERR */
#define IIC_IL_DCERR_CTRL(x)    ((UINT8)(((UINT8)(x)) << IIC_IL_DCERR_SHIFT) & IIC_IL_DCERR_MASK)
#define IIC_IL_DCERR_MASK       ((UINT8)0x08)
#define IIC_IL_DCERR_SHIFT      ((UINT8)0x03)

/*@IIC_IL_TERR */
#define IIC_IL_TERR_CTRL(x)    ((UINT8)(((UINT8)(x)) << IIC_IL_TERR_SHIFT) & IIC_IL_TERR_MASK)
#define IIC_IL_TERR_MASK       ((UINT8)0x04)
#define IIC_IL_TERR_SHIFT      ((UINT8)0x02)

/*@IIC_IL_BLERR */
#define IIC_IL_BLERR_CTRL(x)    ((UINT8)(((UINT8)(x)) << IIC_IL_BLERR_SHIFT) & IIC_IL_BLERR_MASK)
#define IIC_IL_BLERR_MASK       ((UINT8)0x02)
#define IIC_IL_BLERR_SHIFT      ((UINT8)0x01)

/*@IIC_IL_LCDERR */
#define IIC_IL_LCDERR_CTRL(x)    ((UINT8)(((UINT8)(x)) << IIC_IL_LCDERR_SHIFT) & IIC_IL_LCDERR_MASK)
#define IIC_IL_LCDERR_MASK       ((UINT8)0x01)
#define IIC_IL_LCDERR_SHIFT      ((UINT8)0x00)

#define IIC_IL_DISPALY_STATUS_FUNCTION_CFG  {   \
    /* .pbGetTouchConnectionError = */                  NULL,   \
    /* .pbGetTouchScreenControllerError = */            NULL,   \
    /* .pbGetLossOfLock = */                            NULL,   \
    /* .pbGetResetRequest = */                          NULL,   \
    /* .pbGetDisconnectError = */                       NULL,   \
    /* .pbGetTemperatureDerating = */                   NULL,   \
    /* .pbGetLCDBacklightError = */                     NULL,   \
    /* .pbGetLCDError = */                              NULL,   \
    /* .pbGetDisplayInitialized = */                    NULL,   \
    /* .pbGetTouchControllerStatus = */                 NULL,   \
    /* .pbGetDispalyStatus = */                         NULL    \
}

#if ( configGENERATE_INTERRUPT == 0)
    #define GENERATE_INTERRUPT()
#else
    #define GENERATE_INTERRUPT() GenerateInterruptFunction()
#endif
