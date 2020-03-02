#ifndef		_WD_DASK_H
#define		_WD_DASK_H

#ifdef __cplusplus
extern "C" {
#endif

//DASK Data Types
typedef unsigned char   U8;
typedef short           I16;
typedef unsigned short  U16;
typedef long            I32;
typedef unsigned long   U32;
typedef float           F32;
typedef double          F64;

//ADLink PCI Card Type
#define PCI_9820        1
#define MAX_CARD        32

//Error Number
#define NoError                       0
#define ErrorUnknownCardType         -1
#define ErrorInvalidCardNumber       -2
#define ErrorTooManyCardRegistered   -3
#define ErrorCardNotRegistered       -4
#define ErrorFuncNotSupport          -5
#define ErrorInvalidIoChannel        -6
#define ErrorInvalidAdRange          -7
#define ErrorContIoNotAllowed        -8
#define ErrorDiffRangeNotSupport     -9
#define ErrorLastChannelNotZero      -10
#define ErrorChannelNotDescending    -11
#define ErrorChannelNotAscending     -12
#define ErrorOpenDriverFailed        -13
#define ErrorOpenEventFailed         -14
#define ErrorTransferCountTooLarge   -15
#define ErrorNotDoubleBufferMode     -16
#define ErrorInvalidSampleRate       -17
#define ErrorInvalidCounterMode      -18
#define ErrorInvalidCounter          -19
#define ErrorInvalidCounterState     -20
#define ErrorInvalidBinBcdParam      -21
#define ErrorBadCardType             -22
#define ErrorInvalidDaRefVoltage     -23
#define ErrorAdTimeOut               -24
#define ErrorNoAsyncAI               -25
#define ErrorNoAsyncAO               -26
#define ErrorNoAsyncDI               -27
#define ErrorNoAsyncDO               -28
#define ErrorNotInputPort            -29
#define ErrorNotOutputPort           -30
#define ErrorInvalidDioPort          -31
#define ErrorInvalidDioLine          -32
#define ErrorContIoActive            -33
#define ErrorDblBufModeNotAllowed    -34
#define ErrorConfigFailed            -35
#define ErrorInvalidPortDirection    -36
#define ErrorBeginThreadError        -37
#define ErrorInvalidPortWidth        -38
#define ErrorInvalidCtrSource        -39
#define ErrorOpenFile                -40
#define ErrorAllocateMemory          -41
#define ErrorDaVoltageOutOfRange     -42
#define ErrorDaExtRefNotAllowed      -43
#define ErrorInvalidBufferID         -44
#define ErrorInvalidCNTInterval	     -45
#define ErrorReTrigModeNotAllowed    -46
#define ErrorResetBufferNotAllowed   -47
#define ErrorAnaTriggerLevel         -48
#define ErrorDAQEvent		         -49
#define ErrorInvalidDataSize         -50 
#define ErrorOffsetCalibration       -51
#define ErrorGainCalibration         -52
#define ErrorCountOutofSDRAMSize     -53
#define ErrorNotStartTriggerModule   -54
#define ErrorInvalidRouteLine        -55
#define ErrorInvalidSignalCode       -56
#define ErrorInvalidSignalDirection  -57
#define ErrorTRGOSCalibration        -58
//Error number for driver API 
#define ErrorConfigIoctl			 -201
#define ErrorAsyncSetIoctl			 -202
#define ErrorDBSetIoctl				 -203
#define ErrorDBHalfReadyIoctl		 -204
#define ErrorContOPIoctl			 -205
#define ErrorContStatusIoctl		 -206
#define ErrorPIOIoctl				 -207
#define ErrorDIntSetIoctl			 -208
#define ErrorWaitEvtIoctl			 -209
#define ErrorOpenEvtIoctl			 -210
#define ErrorCOSIntSetIoctl			 -211
#define ErrorMemMapIoctl			 -212
#define ErrorMemUMapSetIoctl		 -213
#define ErrorCTRIoctl			     -214
#define ErrorGetResIoctl		     -215

#define TRUE    1
#define FALSE   0

//Synchronous Mode
#define SYNCH_OP        1
#define ASYNCH_OP       2

//AD Range
#define AD_B_10_V       1
#define AD_B_5_V        2
#define AD_B_2_5_V      3
#define AD_B_1_25_V     4
#define AD_B_0_625_V    5
#define AD_B_0_3125_V   6
#define AD_B_0_5_V      7
#define AD_B_0_05_V     8
#define AD_B_0_005_V    9
#define AD_B_1_V       10
#define AD_B_0_1_V     11
#define AD_B_0_01_V    12
#define AD_B_0_001_V   13
#define AD_U_20_V      14
#define AD_U_10_V      15
#define AD_U_5_V       16
#define AD_U_2_5_V     17
#define AD_U_1_25_V    18
#define AD_U_1_V       19
#define AD_U_0_1_V     20
#define AD_U_0_01_V    21
#define AD_U_0_001_V   22

#define All_Channels   -1

#define WD_AI_ADCONVSRC_TimePacer 0

#define WD_AI_TRGSRC_SOFT      0x00   
#define WD_AI_TRGSRC_ANA       0x01   
#define WD_AI_TRGSRC_ExtD      0x02   
#define WD_AI_TRSRC_SSI_1      0x03
#define WD_AI_TRSRC_SSI_2      0x04
#define WD_AI_TRSRC_PXIStart   0x05           
#define WD_AI_TRGMOD_POST      0x00   //Post Trigger Mode
#define WD_AI_TRGMOD_PRE       0x01   //Pre-Trigger Mode
#define WD_AI_TRGMOD_MIDL      0x02   //Middle Trigger Mode
#define WD_AI_TRGMOD_DELAY     0x03   //Delay Trigger Mode
#define WD_AI_TrgPositive      0x1
#define WD_AI_TrgNegative      0x0

#define WD_AIEvent_Manual      0x80   //AI event manual reset

/* define analog trigger Dedicated Channel */
#define CH0ATRIG			   0x00
#define CH1ATRIG			   0x01
/* Time Base */
#define WD_ExtTimeBase		  0x0
#define WD_SSITimeBase		  0x1
#define	WD_StarTimeBase		  0x2
#define WD_IntTimeBase		  0x3
#define	WD_PLL_REF_PXICLK10	  0x4
#define	WD_PLL_REF_EXT10	  0x5
//SSI signal codes
#define SSI_TIME	   15
#define SSI_TRIG_SRC1   7
#define SSI_TRIG_SRC2   5
#define SSI_TRIG_SRC2_S 5
#define SSI_TRIG_SRC2_T 6 
// signal lines
#define PXI_TRIG_0      0
#define PXI_TRIG_1      1
#define PXI_TRIG_2      2
#define PXI_TRIG_3      3
#define PXI_TRIG_4      4
#define PXI_TRIG_5      5
#define PXI_TRIG_6      6
#define PXI_TRIG_7      7
#define PXI_START_TRIG  8
#define TRG_IO			9
//Software trigger op code
#define SOFTTRIG_AI		0x1
//DAQ Event type for the event message  
#define DAQEnd   0
#define DBEvent  1
//DAQ advanced mode  
#define DAQSTEPPED   0x1   
#define RestartEn	 0x2
#define DualBufEn	 0x4
#define ManualSoftTrg 0x40
#define DMASTEPPED    0x80

/*------------------------------------------------------------------
** PCIS-DASK Function prototype
------------------------------------------------------------------*/
I16 __stdcall WD_Register_Card (U16 CardType, U16 card_num);
I16 __stdcall WD_Get_SDRAMSize  (U16 CardNumber, U32 *sdramsize);
I16 __stdcall WD_SoftTriggerGen(U16 wCardNumber, U8 op);
I16 __stdcall WD_Release_Card  (U16 CardNumber);
I16 __stdcall WD_GetActualRate(U16 wCardNumber, BOOLEAN fdir, F64 Rate, U32* interval, F64 *ActualRate);
I16 __stdcall WD_GetPXIGeographAddr (U16 wCardNumber, U8* geo_addr);
I16 __stdcall WD_GetBaseAddr(U16 wCardNumber, U32 *BaseAddr, U32 *BaseAddr2);
/*---------------------------------------------------------------------------*/
I16 __stdcall WD_AI_Config (U16 wCardNumber, U16 TimeBase, BOOLEAN adDutyRestore, U16 ConvSrc, BOOLEAN doubleEdged, BOOLEAN AutoResetBuf);
I16 __stdcall WD_AI_Trig_Config (U16 wCardNumber, U16 trigMode, U16 trigSrc, U16 trigPol, U16 anaTrigchan, F64 anaTriglevel, U32 postTrigScans, U32 preTrigScans, U32 trigDelayTicks, U32 reTrgCnt);
I16 __stdcall WD_AI_Set_Mode (U16 wCardNumber, U16 modeCtrl, U16 wIter);
I16 __stdcall WD_AI_CH_Config (U16 wCardNumber, U16 wChannel, U16 wAdRange);
I16 __stdcall WD_AI_InitialMemoryAllocated (U16 CardNumber, U32 *MemSize);
I16 __stdcall WD_AI_VoltScale (U16 CardNumber, U16 AdRange, I16 reading, F64 *voltage);
I16 __stdcall WD_AI_ContReadChannel (U16 CardNumber, U16 Channel,
               U16 BufId, U32 ReadScans, U32 ScanIntrv, U32 SampIntrv, U16 SyncMode);
I16 __stdcall WD_AI_ContReadMultiChannels (U16 CardNumber, U16 NumChans, U16 *Chans,
               U16 BufId, U32 ReadScans, U32 ScanIntrv, U32 SampIntrv, U16 SyncMode);
I16 __stdcall WD_AI_ContScanChannels (U16 CardNumber, U16 Channel,
               U16 BufId, U32 ReadScans, U32 ScanIntrv, U32 SampIntrv, U16 SyncMode);
I16 __stdcall WD_AI_ContReadChannelToFile (U16 CardNumber, U16 Channel, U16 BufId,
               U8 *FileName, U32 ReadScans, U32 ScanIntrv, U32 SampIntrv, U16 SyncMode);
I16 __stdcall WD_AI_ContReadMultiChannelsToFile (U16 CardNumber, U16 NumChans, U16 *Chans,
               U16 BufId, U8 *FileName, U32 ReadScans, U32 ScanIntrv, U32 SampIntrv, U16 SyncMode);
I16 __stdcall WD_AI_ContScanChannelsToFile (U16 CardNumber, U16 Channel, U16 BufId,
               U8 *FileName, U32 ReadScans, U32 ScanIntrv, U32 SampIntrv, U16 SyncMode);
I16 __stdcall WD_AI_ContStatus (U16 CardNumber, U32 *Status);
I16 __stdcall WD_AI_ContVScale (U16 wCardNumber, U16 adRange, void *readingArray, F64 *voltageArray, I32 count);
I16 __stdcall WD_AI_AsyncCheck (U16 CardNumber, BOOLEAN *Stopped, U32 *AccessCnt);
I16 __stdcall WD_AI_AsyncClear (U16 CardNumber, U32 *StartPos, U32 *AccessCnt);
I16 __stdcall WD_AI_AsyncDblBufferHalfReady (U16 CardNumber, BOOLEAN *HalfReady, BOOLEAN *StopFlag);
I16 __stdcall WD_AI_AsyncDblBufferMode (U16 CardNumber, BOOLEAN Enable);
I16 __stdcall WD_AI_AsyncDblBufferToFile (U16 CardNumber);
I16 __stdcall WD_AI_ContBufferSetup (U16 wCardNumber, void *pwBuffer, U32 dwReadCount, U16 *BufferId);
I16 __stdcall WD_AI_ContBufferReset (U16 wCardNumber);
I16 __stdcall WD_AI_DMA_Transfer (U16 wCardNumber, U16 BufId);
I16 __stdcall WD_AI_ConvertCheck (U16 wCardNumber, BOOLEAN *bStopped);
I16 __stdcall WD_AI_AsyncReStartNextReady (U16 wCardNumber, BOOLEAN *bReady, BOOLEAN *StopFlag, U16 *RdyDaqCnt);
I16 __stdcall WD_AI_EventCallBack (U16 wCardNumber, I16 mode, I16 EventType, U32 callbackAddr);
I16 __stdcall WD_AI_DMA_TransferBySize (U16 wCardNumber, F32 timeLimit,  U16 BufId, U32 dwReadCount, U32 *numRead, U32 *dataNotTransferred, U8 *complete);
I16 __stdcall WD_AI_ContBufferLock (USHORT wCardNumber, void *pwBuffer, ULONG dwReadCount, USHORT *BufferId);

I16 __stdcall WD_SSI_SourceConn (U16 wCardNumber, U16 sigCode);
I16 __stdcall WD_SSI_SourceDisConn (U16 wCardNumber, U16 sigCode);
I16 __stdcall WD_SSI_SourceClear (U16 wCardNumber);
I16 __stdcall WD_Route_Signal (U16 wCardNumber, U16 signal, U16 Line, U16 dir);
I16 __stdcall WD_Signal_DisConn (U16 wCardNumber, U16 signal, U16 Line);

I16 __stdcall WD_AD_Auto_Calibration_ALL(U16 wCardNumber);
I16 __stdcall WD_EEPROM_CAL_Constant_Update(U16 wCardNumber, U16 bank);
I16 __stdcall WD_Load_CAL_Data(U16 wCardNumber, U16 bank);

#ifdef __cplusplus
}
#endif

#endif		//_WD_DASK_H
