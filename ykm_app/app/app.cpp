#include "app_def.h"

#include <string>
#include <fmt/format.h>

YKM_APP_CAPI
YkmApp_Result YkmApp_GetInfo(const YkmApp_Info** info)
{
    *info = &ykm::appData.info;
    return YkmApp_R_Ok;
}

YKM_APP_CAPI
YkmApp_Result YkmApp_Quit()
{
    ykm::appData.info.alive = false;
    return YkmApp_R_Ok;
}

YKM_APP_CAPI
YkmApp_Bool YkmApp_Alive() //
{
    return ykm::appData.info.alive ? YkmApp_True : YkmApp_False;
}

YKM_APP_CAPI
YkmApp_Result YkmApp_SetName(const char* name)
{
    static std::string appName;
    if (appName.size() > 0)
    {
        // set error msg
        YkmApp_SetLastError("YkmApp_SetName can only call once");
        return YkmApp_R_Redefined;
    }
    appName = name;
    ykm::appData.info.appName = appName.c_str();
    return YkmApp_R_Ok;
};

YKM_APP_CAPI
YkmApp_Result YkmApp_SetVersion( //
    uint16_t big, uint16_t ver, uint32_t patch)
{
    static std::string versionStr;
    if (versionStr.size() > 0)
    {
        // set error msg
        YkmApp_SetLastError("YkmApp_SetVersion can only call once");
        return YkmApp_R_Redefined;
    }
    versionStr = fmt::format("{}.{}.{}", big, ver, patch);
    ykm::appData.info.versionStr = versionStr.c_str();
    ykm::appData.info.appVersion = (uint64_t(big) << 48) & (uint64_t(ver) << 32) & patch;
    return YkmApp_R_Ok;
}

YKM_APP_CAPI
void YkmApp_SetTickSleepPerSecond(float fps) //
{
    ykm::appData.info.tickMaxPerSecond = fps;
}

YKM_APP_CAPI
void YkmApp_SetTickEvtsMax(int max) //
{
    ykm::appData.info.evtsHandlePerTick = max;
}

thread_local static std::string lastErr;
void YkmApp_SetLastError(const char* msg)
{
    lastErr.clear();
    lastErr.append(msg);
}

YKM_APP_CAPI
YkmApp_ErrBuffer YkmApp_GetLastErr() { return lastErr.c_str(); }
