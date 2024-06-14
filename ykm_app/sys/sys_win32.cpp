#include "ykm/sys.h"

#include "ykm/utils/win.h"
#include <vector>

std::vector<YkmSys_ScreenInfo> screenInfos;
BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
    MONITORINFOEX mInfo;
    mInfo.cbSize = sizeof(MONITORINFOEX);
    if (GetMonitorInfo(hMonitor, &mInfo))
    {
        YkmSys_ScreenInfo info;

        info.x = mInfo.rcMonitor.left;
        info.y = -mInfo.rcMonitor.right;

        DEVMODE dm;
        dm.dmSize = sizeof(dm);

        if (EnumDisplaySettings(mInfo.szDevice, ENUM_CURRENT_SETTINGS, &dm))
        {
            info.width = dm.dmPelsWidth;
            info.height = dm.dmPelsHeight;
            info.rate = dm.dmDisplayFrequency;

            HDC hdc = CreateDC(mInfo.szDevice, NULL, NULL, NULL);
            info.dpiX = GetDeviceCaps(hdc, LOGPIXELSX);
            info.dpiY = GetDeviceCaps(hdc, LOGPIXELSX);
            DeleteDC(hdc);
        }

        DISPLAY_DEVICE dd;
        ZeroMemory(&dd, sizeof(dd));
        dd.cb = sizeof(dd);

        if (EnumDisplayDevices(mInfo.szDevice, 0, &dd, 0))
        {
            if (dd.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE)
            {
                info.id = 0;
                if (screenInfos.size() == 0) { screenInfos.push_back(info); }
                else
                {
                    screenInfos.push_back(screenInfos[0]);
                    screenInfos.back().id = screenInfos.size() - 1;
                    screenInfos[0] = info;
                }
            }
            else
            {
                info.id = screenInfos.size() - 1;
                screenInfos.push_back(info);
            }
        }
    }

    return TRUE;
}

YKM_SYS_CAPI
YkmSys_ScreenInfo* YkmSys_GetScreenInfo(int* num)
{
    screenInfos.clear();
    EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, 0);

    *num = screenInfos.size();
    return screenInfos.data();
}
