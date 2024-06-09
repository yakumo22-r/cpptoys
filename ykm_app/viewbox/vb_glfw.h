#ifndef YKM_APP_VIEWBOX_GLFW_H
#define YKM_APP_VIEWBOX_GLFW_H

// wrap the glfw as viewbox in mac|linux|windows

#include <GLFW/glfw3.h>

#include "event.hpp"
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

    std::string last_err; // error info
    i32_xy screen_half;   // main screen half size
    i32_xy lt_pos;        // window position in win32 system coordinate system
    i32_xy frame_size;    // window position in win32 system coordinate system

    f_xy pt_ratio;

    i32_xy pt2px(i32_xy v) { return {(int)(v.x * pt_ratio.x), (int)(v.y * pt_ratio.y)}; }
    i32_xy px2pt(i32_xy v) { return {(int)(v.x / pt_ratio.x), (int)(v.y / pt_ratio.y)}; }

    i32_xy pos_2_ltpos(i32_xy pos)
    {
        return {pos.x + screen_half.x - (content_size().x / 2), //
                screen_half.y - pos.y - (content_size().y / 2)};
    }

    i32_xy ltpos_2_pos(i32_xy lt_pos)
    {
        return {lt_pos.x - screen_half.x + (content_size().x / 2), //
                lt_pos.y + screen_half.y - (content_size().y / 2)};
    }
    using state_t = ykm::enum_set<wnd_state, (uint32_t)wnd_state::state_num>;
    // window state
    state_t state;

    void GetErrInfo() noexcept;
};
} // namespace viewbox_internal

} // namespace ykm

#define YKM_VIEWBOX_PH(_ph) ((::ykm::viewbox_internal::glfw_plat_h*)_ph)

#endif
