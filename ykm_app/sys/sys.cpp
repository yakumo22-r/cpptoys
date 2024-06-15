#include "ykm/sys.h"

#include "sys_def.h"

ykm::SysData ykm::sysData;

YKM_SYS_CAPI
void YkmSys_SetGPool(YkmApp_GPool gpool)
{
    if (gpool) { ykm::sysData.g = *((ykm::AppGlobal*)gpool); }
};
