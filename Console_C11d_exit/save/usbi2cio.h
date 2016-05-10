
// the following ifndef is for preventing double includes of this header file
#if !defined(__USBI2CIO_H__)
  #define __USBI2CIO_H__


#define DAPI_MAX_DEVICES      127


#ifdef _DEBUG
  #define DbgWrStr(sDebug) OutputDebugString((sDebug))
#else
  #define DbgWrStr(sDebug)
#endif


//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------
typedef enum {
  // supported transaction types
  I2C_TRANS_NOADR,          // read or write with no address cycle
  I2C_TRANS_8ADR,           // read or write with 8 bit address cycle
  I2C_TRANS_16ADR,          // read or write with 16 bit address cycle
  I2C_TRANS_NOADR_NS        // read or write with no address cycle, stop signaling suppressed
} I2C_TRANS_TYPE;

typedef unsigned char BBYTE;
typedef unsigned short WWORD;
typedef long LLONG;
typedef unsigned long UULONG;
typedef void *HHANDLE;
//-----------------------------------------------------------------------------
// Structure Definitions
//-----------------------------------------------------------------------------
typedef struct _DEVINFO {             // structure for device information
  BBYTE byInstance;
  BBYTE SerialId[9];
} DEVINFO, *LPDEVINFO;

#pragma pack(push, 1)                       // force BBYTE alignment

typedef struct _I2C_TRANS {
  BBYTE byTransType;
  BBYTE bySlvDevAddr;
  WWORD wMemoryAddr;
  WWORD wCount;
  BBYTE Data[256];
} I2C_TRANS, *PI2C_TRANS;

#pragma pack(pop)                          // restore previous alignment

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// API Function Prototypes (exported)
//-----------------------------------------------------------------------------
typedef char *LLPSTR;
typedef int BBOOL;
typedef long *LLPLONG;

// implemented calls
WWORD _stdcall DAPI_GetDllVersion(void);
HHANDLE _stdcall DAPI_OpenDeviceInstance(LLPSTR lpsDevName, BBYTE byDevInstance);
BBOOL _stdcall DAPI_CloseDeviceInstance(HHANDLE hDevInstance);
BBOOL _stdcall DAPI_DetectDevice(HHANDLE hDevInstance);
BBYTE _stdcall DAPI_GetDeviceCount( LLPSTR lpsDevName );
BBYTE _stdcall DAPI_GetDeviceInfo( LLPSTR lpsDevName, LPDEVINFO lpDevInfo);
HHANDLE _stdcall DAPI_OpenDeviceBySerialId(LLPSTR lpsDevName, LLPSTR lpsDevSerialId);
BBOOL _stdcall DAPI_GetSerialId(HHANDLE hDevInstance, LLPSTR lpsDevSerialId);
BBOOL _stdcall DAPI_ConfigIoPorts(HHANDLE hDevInstance, UULONG ulIoPortConfig);
BBOOL _stdcall DAPI_GetIoConfig(HHANDLE hDevInstance, LLPLONG lpulIoPortConfig);
BBOOL _stdcall DAPI_ReadIoPorts(HHANDLE hDevInstance, LLPLONG lpulIoPortData);
BBOOL _stdcall DAPI_WriteIoPorts(HHANDLE hDevInstance, UULONG ulIoPortData, UULONG ulIoPortMask);
LLONG _stdcall DAPI_ReadI2c(HHANDLE hDevInstance, PI2C_TRANS TransI2C);
LLONG _stdcall DAPI_WriteI2c(HHANDLE hDevInstance, PI2C_TRANS TransI2C);
LLONG _stdcall DAPI_ReadDebugBuffer(LLPSTR lpsDebugString, HHANDLE hDevInstance, LLONG ulMaxBYTEs);

// unimplemented calls
WWORD _stdcall DAPI_GetDriverVersion(void);
WWORD _stdcall DAPI_GetFirmwareVersion(void);
void _stdcall DAPI_EnablePolling(void);
void _stdcall DAPI_DisablePolling(void);
void _stdcall DAPI_GetPolledInfo(void);
BBOOL _stdcall DAPI_TransferData(HHANDLE hDevInstance, unsigned char Ep, BBYTE* Buffer, UULONG* Length);

// the following #endif is for preventing double includes of this header file
#endif