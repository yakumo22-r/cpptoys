#ifndef YKM_APP_SYS_DEF_H
#define YKM_APP_SYS_DEF_H

#include "../global.h"

namespace ykm
{
struct SysData
{
    SysData()
    {
        g.update_err = [](const char*) {};
    }

    AppGlobal g;
};

extern SysData sysData;
} // namespace ykm

inline void YkmApp_SetLastError(const char* str) { ::ykm::sysData.g.update_err(str); }

#endif
