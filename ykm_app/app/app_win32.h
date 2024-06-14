#ifndef YKM_APP_APP_WIN32_H
#define YKM_APP_APP_WIN32_H

#include "ykm/utils/win.h"

namespace ykm
{

struct App_PH
{
    HINSTANCE hIns;

    App_PH() : hIns(GetModuleHandle(NULL)) {}
};

} // namespace ykm

#endif
