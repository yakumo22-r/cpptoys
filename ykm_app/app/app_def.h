#ifndef YKM_APP_APP_DEF_H
#define YKM_APP_APP_DEF_H

#include "ykm/app.h"

#include "frame_delay.hpp"

namespace ykm
{

struct App_PH;

struct AppData
{
    YkmApp_Info info;
    frame_delay timer;

    AppData(App_PH& ph)
    {
        timer.frame_begin();
        info._ph = &ph;

        info.appName = nullptr;
        info.appVersion = 0;
        info.versionStr = nullptr;

        info.tickMaxPerSecond = 60;
        info.evtsHandlePerTick = 16;

        info.time = 0;
        info.deltaTime = 0;

        info.alive = true;
        update_time();
    }

    void update_time()
    {
        info.deltaTime = timer.time_ms() - info.time;
        info.time += info.deltaTime;
    }
};


extern AppData appData;

} // namespace ykm

void YkmApp_SetLastError(const char* msg);

#endif
