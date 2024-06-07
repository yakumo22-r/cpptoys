/*
integrate views across multiple platforms and export a set of usable interfaces.
require c++20

version: dev -1
*/
#ifndef YKM_APP_VIEWBOX_HPP
#define YKM_APP_VIEWBOX_HPP

#include "../viewbox/interface.hpp"

#if defined(YKM_VIEWBOX_GLFW)
//#error "the viewbox wrap glfw is not code down, not for use"
#elif defined(_WIN32)

#elif defined(__APPLE__)
#error "viewbox in apple no implemention without glfw yet"
#endif


#endif
