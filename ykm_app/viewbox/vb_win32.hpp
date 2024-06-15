#ifndef YKM_APP_VIEWBOX_WIN32_H
#define YKM_APP_VIEWBOX_WIN32_H

#ifndef NOMINMAX
#define NOMINMAX
#include <Windows.h>
#undef NOMINMAX
#else
#include <Windows.h>
#endif

#include "ykm/viewbox.hpp"

namespace ykm
{

// impl
struct ViewBox::PH : ViewBox::implbase
{
    HINSTANCE hInst; // win api
    HWND hWnd;       // win api
    DWORD style;
    i32_xy screen_half;   // main screen half size
    i32_xy lt_pos;        // window position in win32 system coordinate system

    i32_xy ca_pos;
    i32_xy ca_size;
    i32_xy ca_content_size;

    i32_xy ltpos_2_pos(i32_xy v)
    {
        return {v.x + size().x / 2 - screen_half.x, //
                -(v.y + size().y / 2 - screen_half.y)};
    };

    i32_xy pos_2_ltpos(i32_xy v)
    {
        return {v.x + screen_half.x - size().x / 2, //
                -v.y + screen_half.y - size().y / 2};
    };

    // rewrite move & resize for window
    WPARAM rw_hithc;
    POINT rw_cursor;

    enum wnd_state : uint32_t
    {
        // clang-format off
        rw_resizing, rw_moving,

        active, alive, zoomd,sleepd,ca_sleepd,

        d_title, d_size_pos,d_sleep,
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

} // namespace ykm

#endif
