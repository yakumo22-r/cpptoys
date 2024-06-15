#ifndef YKM_APP_GLOBAL_H
#define YKM_APP_GLOBAL_H

namespace ykm
{
struct AppGlobal
{
    using SetErrorMsg = void (*)(const char*);
    SetErrorMsg update_err;
};
} // namespace ykm

#endif
