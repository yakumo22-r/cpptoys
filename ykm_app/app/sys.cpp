#include "ykm/sys.h"

#include "sys_def.h"

ykm::SysData ykm::sysData;

YKM_APP_CAPI
void YkmApp_SetGPool(YkmApp_GPool gpool)
{
    if (gpool) { ykm::sysData.g = *((ykm::AppGlobal*)gpool); }
};
