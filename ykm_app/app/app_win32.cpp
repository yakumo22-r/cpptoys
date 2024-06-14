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
YkmApp_Result YkmApp_HandleEvents()
{
    MSG msg;
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return YkmApp_R_Ok;
}
