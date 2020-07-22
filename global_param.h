#ifndef __GLOBAL_PARAM__H
#define __GLOBAL_PARAM__H
#include "Arduino.h"

extern volatile bool g_bIsUpdateWaveDigital;
extern volatile int g_nWaveType ;
extern volatile uint8_t g_nCurrentState;
extern volatile bool g_bEnableLogicAn;
extern volatile uint32_t g_nLogicAnValue;
extern volatile int g_aWavedigital[255];
extern volatile boolean g_tTimer20ms;
#endif

