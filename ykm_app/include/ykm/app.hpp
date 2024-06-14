#ifndef YKM_APP_APP_HPP
#define YKM_APP_APP_HPP

#include "app.h"
#include <functional>

namespace ykm
{

class AppResultChecker final
{
  public:
    std::function<void(YkmApp_Result, const char*)> error_handler;
    // @return: is fatal error?
    void operator>(YkmApp_Result r) const
    {
        if (r == YkmApp_R_Ok) return;
        error_handler(r, YkmApp_GetLastErr());
    }
};

}; // namespace ykm

#endif
