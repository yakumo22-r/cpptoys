/*
integrate views across multiple platforms and export a set of usable interfaces.
require c++17

version: dev -1
*/
#ifndef YKM_APP_VIEWBOX_HPP
#define YKM_APP_VIEWBOX_HPP

#ifdef _WIN32
#if __cplusplus < 202002L
#error "need c++20 or high"
#endif

#include "../viewbox/win32_def.h"

#else
#error "viewbox dose not support on this platform"
#endif

#endif
