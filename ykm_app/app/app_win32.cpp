#include "app_def.h"
#include "app_win32.h"

#include "ykm/app.h"

#include <fmt/format.h>

static ykm::App_PH ph;
ykm::AppData ykm::appData(ph);

YKM_APP_CAPI
YkmApp_Result YkmApp_LoopSleep()
{
    ykm::appData.timer.frame_end();
    ykm::appData.timer.frame_begin();
    ykm::appData.update_time();
    return YkmApp_R_Ok;
}

YKM_APP_CAPI
YkmApp_Result YkmApp_LoopHandleEvts()
{
    MSG msg;
    uint32_t count = 0;
    while (count < ykm::appData.info.evtsHandlePerTick //
           && PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        ++count;
    }
    return YkmApp_R_Ok;
}
