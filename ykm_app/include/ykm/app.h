#ifndef YKM_APP_APP_H
#define YKM_APP_APP_H

#include "base.h"

#ifdef YKM_APP_SHARED_LIB
#if defined(YKM_APP_SHARED_BUILD)
#define YKM_APP_API YKM_APP_EXPORT
#else
#define YKM_APP_API YKM_APP_IMPORT
#endif
#else
#define YKM_APP_API
#endif
#define YKM_APP_CAPI YKM_APP_WRAP_C YKM_APP_API

#include <stdint.h>

typedef void* YkmApp_PH;

struct YkmApp_Info
{
    YkmApp_PH _ph;
    const char* appName;
    uint64_t appVersion;
    const char* versionStr;

    float tickMaxPerSecond;
    int evtsHandlePerTick;

    long long time;
    long deltaTime;

    bool alive;
};

YKM_APP_CAPI
YkmApp_Result YkmApp_GetInfo(const YkmApp_Info** info);

YKM_APP_CAPI
YkmApp_Result YkmApp_SetName(const char* name);

YKM_APP_CAPI
YkmApp_Result YkmApp_SetVersion( //
    uint16_t big, uint16_t ver, uint32_t patch);

YKM_APP_CAPI
YkmApp_Result YkmApp_Quit();

YKM_APP_CAPI
YkmApp_Bool YkmApp_Alive();

YKM_APP_CAPI
void YkmApp_SetTickSleepPerSecond(float fps);

YKM_APP_CAPI
void YkmApp_SetTickEvtsMax(int max);

YKM_APP_CAPI
YkmApp_Result YkmApp_LoopSleep();

YKM_APP_CAPI
YkmApp_Result YkmApp_LoopHandleEvts();

YKM_APP_CAPI
YkmApp_ErrBuffer YkmApp_GetLastErr();

// TODO get working directory
// TODO get binary directory

// TODO async task system

#endif
