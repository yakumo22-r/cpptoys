#ifndef YKM_APP_VIEWBOX_GLFW_H
#define YKM_APP_VIEWBOX_GLFW_H


// wrap the glfw as viewbox in mac|linux|windows

#include <GLFW/glfw3.h>

#include "interface.hpp"
#include "debug.hpp"

namespace ykm
{


enum class wnd_state : uint32_t
{
    // clang-format off
    d_title,d_size,d_pos,
    // clang-format on
    state_num
};

namespace viewbox_internal
{

struct glfw_plat_h : ykm::viewbox::implbase
{
    GLFWwindow* hWnd;

    std::string last_err;   // error info
    viewbox_xy screen_half; // main screen half size
    viewbox_xy lt_pos;      // window position in win32 system coordinate system
    viewbox_xy frame_size;      // window position in win32 system coordinate system

    using state_t = ykm::enum_set<wnd_state, (uint32_t)wnd_state::state_num>;
    // window state
    state_t state;

    void GetErrInfo() noexcept;
};
} // namespace viewbox_internal

} // namespace ykm

#define YKM_VIEWBOX_PH(_ph) ((::ykm::viewbox_internal::glfw_plat_h*)_ph)

#endif
