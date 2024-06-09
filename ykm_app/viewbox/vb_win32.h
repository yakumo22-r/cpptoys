#ifndef YKM_APP_VIEWBOX_WIN32_H
#define YKM_APP_VIEWBOX_WIN32_H

#ifndef NOMINMAX
#define NOMINMAX
#include <Windows.h>
#undef NOMINMAX
#else
#include <Windows.h>
#endif

#include <string>

#include "interface.hpp"

namespace ykm
{
namespace viewbox_internal
{

// impl
struct win32_plat_h : ykm::viewbox::implbase
{
    HINSTANCE hInst; // win api
    HWND hWnd;       // win api
    DWORD style;
    std::string last_err;   // error info
    i32_xy screen_half; // main screen half size
    i32_xy lt_pos;      // window position in win32 system coordinate system

    // rewrite move & resize for window
    WPARAM rw_hithc;
    POINT rw_cursor;

    enum wnd_state : uint32_t
    {
        // clang-format off
        rw_resizing, rw_moving,

        active, alive, zoomd,

        d_title, d_size, d_pos,
        // clang-format on
        state_num
    };
    using state_t = ykm::enum_set<wnd_state, state_num>;
    // window state
    state_t state;

    LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

    void GetErrInfo() noexcept;

    void reset_rw()
    {
        rw_hithc = 0;
        state.set(rw_moving);
        state.set(rw_resizing);
    }
};

#define YKM_VIEWBOX_PH(_ph) ((::ykm::viewbox_internal::win32_plat_h*)_ph)

} // namespace viewbox_internal
} // namespace ykm

#endif
