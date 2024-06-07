/*
windows window Interface encapsulation

version: dev 0.0.2

TODO: text input with candicate
*/

#ifndef YKM_VIEWBOX_WIN32_HPP
#define YKM_VIEWBOX_WIN32_HPP

#include "vb_win32.h"

#include <winuser.h>

#include "debug.hpp"

namespace ykm
{
namespace viewbox_internal
{
void win32_plat_h::GetErrInfo() noexcept
{
    HRESULT hr = GetLastError();

    LPSTR pMsgBuf = nullptr;
    DWORD nMsgLen = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, hr,
                                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), pMsgBuf, 0, nullptr);
    const char* err;
    if (nMsgLen == 0)
    {
        err = "Unidentified error code";
    }
    else
    {
        LocalFree(pMsgBuf);
        err = pMsgBuf;
    }
    last_err = fmt::format("[Error Code] 0x{:X}({}) \n[Description] {} \n", hr, (unsigned long)hr, err);
}

inline constexpr char const* class_name = "ykm_viewbox_0_0_1";

LRESULT HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    win32_plat_h* const pWnd = reinterpret_cast<win32_plat_h*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    if (msg == WM_NCCREATE)
    {
        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        win32_plat_h* const pWnd = static_cast<win32_plat_h*>(pCreate->lpCreateParams);

        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgThunk));
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT win32_plat_h::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{

    using e = viewbox_evt;
    switch (msg)
    {
    case WM_ACTIVATE:
        evts().push_evts(LOWORD(wParam) != WA_INACTIVE ? e::active : e::unactive);
        if (LOWORD(wParam) != WA_INACTIVE)
            state.set(active);
        else
            state.reset(active);

    case WM_SIZE:
        content_size().x = LOWORD(lParam);
        content_size().y = HIWORD(lParam);

        // check window maximization status
        if (IsZoomed(hWnd))
            state.set(zoomd);
        else
            state.reset(zoomd);

        break;

    case WM_MOVE:

        break;

    case WM_MOUSEMOVE:
        evts().mouse.x() = LOWORD(lParam);
        evts().mouse.y() = HIWORD(lParam);
        break;

    case WM_MOUSEWHEEL:
        evts().mouse.scroll() = GET_WHEEL_DELTA_WPARAM(wParam);
        break;

    case WM_KEYDOWN:
        evts().keyboard.press(input::kc_by_sc(wParam));

        if (wParam == VK_SHIFT)
        {
            if ((GetAsyncKeyState(VK_LSHIFT) & 0x8000))
                evts().keyboard.press(input::kc_by_sc(VK_LSHIFT));
            if ((GetAsyncKeyState(VK_RSHIFT) & 0x8000))
                evts().keyboard.press(input::kc_by_sc(VK_RSHIFT));
        }
        else if (wParam == VK_MENU)
        {
            if ((GetAsyncKeyState(VK_LMENU) & 0x8000))
                evts().keyboard.press(input::kc_by_sc(VK_LMENU));
            if ((GetAsyncKeyState(VK_RMENU) & 0x8000))
                evts().keyboard.press(input::kc_by_sc(VK_RMENU));
        }
        else if (wParam == VK_CONTROL)
        {
            if ((GetAsyncKeyState(VK_LCONTROL) & 0x8000))
                evts().keyboard.press(input::kc_by_sc(VK_LCONTROL));
            if ((GetAsyncKeyState(VK_RCONTROL) & 0x8000))
                evts().keyboard.press(input::kc_by_sc(VK_RCONTROL));
        }

        break;
    case WM_KEYUP:
        evts().keyboard.release(input::kc_by_sc(wParam));
        if (wParam == VK_SHIFT)
        {
            if (!(GetAsyncKeyState(VK_LSHIFT) & 0x8000))
                evts().keyboard.release(input::kc_by_sc(VK_LSHIFT));
            if (!(GetAsyncKeyState(VK_RSHIFT) & 0x8000))
                evts().keyboard.release(input::kc_by_sc(VK_RSHIFT));
        }
        else if (wParam == VK_MENU)
        {
            if (!(GetAsyncKeyState(VK_LMENU) & 0x8000))
                evts().keyboard.release(input::kc_by_sc(VK_LMENU));
            if (!(GetAsyncKeyState(VK_RMENU) & 0x8000))
                evts().keyboard.release(input::kc_by_sc(VK_RMENU));
        }
        else if (wParam == VK_CONTROL)
        {
            if (!(GetAsyncKeyState(VK_LCONTROL) & 0x8000))
                evts().keyboard.release(input::kc_by_sc(VK_LCONTROL));
            if (!(GetAsyncKeyState(VK_RCONTROL) & 0x8000))
                evts().keyboard.release(input::kc_by_sc(VK_RCONTROL));
        }
        break;
    case WM_SYSKEYDOWN:
        evts().keyboard.press(input::kc_by_sc(wParam));
        break;
    case WM_SYSKEYUP:
        evts().keyboard.release(input::kc_by_sc(wParam));
        break;

    case WM_LBUTTONDOWN:
        evts().mouse.press(input::btncode::left);
        break;
    case WM_LBUTTONUP:
        evts().mouse.release(input::btncode::left);
        break;
    case WM_RBUTTONDOWN:
        evts().mouse.press(input::btncode::right);
        break;
    case WM_RBUTTONUP:
        evts().mouse.release(input::btncode::right);
        break;
    case WM_MBUTTONDOWN:
        evts().mouse.press(input::btncode::middle);
        break;
    case WM_MBUTTONUP:
        evts().mouse.release(input::btncode::middle);
        break;

    case WM_MOVING:
        return NULL;

    case WM_NCMOUSEMOVE:
        return NULL;

    case WM_NCLBUTTONDOWN:
        if (wParam == HTCLOSE || wParam == HTMAXBUTTON || wParam == HTMINBUTTON || wParam == HTHELP)
        {
            rw_hithc = wParam;
            PostMessage(hWnd, WM_ACTIVATE, WA_CLICKACTIVE, 0);
        }
        else if (wParam >= HTLEFT && wParam <= HTBOTTOMRIGHT)
        {
            state.set(rw_resizing);
            rw_hithc = wParam;
            GetCursorPos(&rw_cursor);
        }
        else if (wParam == HTCAPTION)
        {
            state.set(rw_moving);
            rw_hithc = wParam;
            GetCursorPos(&rw_cursor);
        }
        return NULL;

    case WM_NCRBUTTONDOWN:
        return NULL;
    case WM_NCRBUTTONUP:
        return NULL;

    case WM_NCLBUTTONUP:
        if (rw_hithc == wParam)
        {
            switch (wParam)
            {
            case HTMAXBUTTON:
            {
                bool wndMaxed = GetWindowLongPtr(hWnd, GWL_STYLE) & WS_MAXIMIZE;
                PostMessage(hWnd, WM_SYSCOMMAND, wndMaxed ? SC_RESTORE : SC_MAXIMIZE, lParam);
                break;
            }
            case HTMINBUTTON:
                PostMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, lParam);
                break;
            case HTCLOSE:
                PostMessage(hWnd, WM_SYSCOMMAND, SC_CLOSE, lParam);
                break;
            case HTHELP:
                break;
            }
        }
        else
        {
            return DefWindowProc(hWnd, msg, wParam, lParam);
        }
        state.reset(rw_resizing);
        rw_hithc = HTNOWHERE;
        return NULL;

    case WM_CLOSE:
        PostQuitMessage(0);
    }

    // if (hmp != nullptr)
    //     hmp(hWnd, msg, wParam, lParam);

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

} // namespace viewbox_internal

#define YKM_VIEWBOX_WIN32_PH(_ph) ((win32_plat_h*)_ph)

viewbox::result viewbox::create(int32_t posX, int32_t posY, int32_t sizeX, int32_t sizeY, const char* title)
{
    using namespace ::ykm::viewbox_internal;

    if (YKM_VIEWBOX_WIN32_PH(_ph))
        destory();

    auto ph = new win32_plat_h();
    _ph = ph;
    ph->hInst = GetModuleHandle(nullptr);
    ph->vb = this;

    static WNDCLASSEX wc = {0};
    static bool wc_reg = false;

    if (!wc_reg)
    {
        wc.cbSize = sizeof(wc);
        wc.style = CS_OWNDC;
        wc.lpfnWndProc = HandleMsgSetup;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = ph->hInst;
        wc.hIcon = nullptr;
        wc.hCursor = nullptr;
        wc.hbrBackground = nullptr;
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = class_name;
        wc.hIconSm = nullptr;
        RegisterClassEx(&wc);
        wc_reg = true;
    }

    pos.x = posX;
    pos.y = posY;

    size.x = sizeX;
    size.y = sizeY;

    text_title = std::string(title);
    evts.clear_evts();
    evts.keyboard.next_frame();
    evts.mouse.next_frame();

    ph->style = WS_OVERLAPPEDWINDOW;

    ph->screen_half.x = GetSystemMetrics(SM_CXSCREEN) / 2;
    ph->screen_half.y = GetSystemMetrics(SM_CYSCREEN) / 2;

    ph->lt_pos.x = ph->screen_half.x + pos.x - size.x / 2;
    ph->lt_pos.y = ph->screen_half.y - pos.y - size.y / 2;
    ph->hWnd = CreateWindow(class_name, title, ph->style, ph->lt_pos.x, ph->lt_pos.y, size.x, size.y, nullptr, nullptr, ph->hInst, ph);

    // check window maximization status
    if (IsZoomed(ph->hWnd))
    {
        ph->state.set(win32_plat_h::zoomd);
    }
    else
    {
        ph->state.reset(win32_plat_h::zoomd);
    }

    RECT rect;
    GetClientRect(ph->hWnd, &rect);
    content_size.x = rect.right - rect.left;
    content_size.y = rect.bottom - rect.top;

    if (ph->hWnd == nullptr)
    {
        ph->GetErrInfo();
        destory();
        // MessageBox(0, ph->last_err.c_str(), "ykm viewbox create error", MB_OK);
        return r_internal;
    }
    return r_ok;
}

viewbox::result viewbox::process_loop()
{
    using namespace ::ykm::viewbox_internal;
    auto ph = YKM_VIEWBOX_WIN32_PH(_ph);

    if (!ph)
        return r_uninitialized;

    evts.clear_evts();
    evts.keyboard.next_frame();
    evts.mouse.next_frame();

    MSG msg;

    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0)
    {
        if (msg.message == WM_QUIT)
        {
            ph->state.reset(win32_plat_h::alive);
            return r_quit;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    auto& state = ph->state;

    // window resize rewrite
    if (!state[win32_plat_h::zoomd] && state[win32_plat_h::rw_resizing] && (GetAsyncKeyState(VK_LBUTTON) & 0x8000))
    {
        POINT cursor;
        GetCursorPos(&cursor);
        int16_t deltaWidth;
        int16_t deltaHeight;

        state.set(win32_plat_h::d_pos);
        state.set(win32_plat_h::d_size);

        switch (ph->rw_hithc)
        {
        case HTTOP:
            deltaHeight = ph->rw_cursor.y - cursor.y;
            size.y += deltaHeight;
            ph->lt_pos.y -= deltaHeight;
            pos.y = -(ph->lt_pos.y + size.y / 2 - ph->screen_half.y);
            break;

        case HTTOPRIGHT:
            deltaWidth = cursor.x - ph->rw_cursor.x;
            deltaHeight = ph->rw_cursor.y - cursor.y;
            size.x += deltaWidth;
            size.y += deltaHeight;
            ph->lt_pos.y -= deltaHeight;
            pos.y = -(ph->lt_pos.y + size.y / 2 - ph->screen_half.y);
            pos.x = ph->lt_pos.x + size.x / 2 - ph->screen_half.x;
            break;

        case HTTOPLEFT:
            deltaWidth = ph->rw_cursor.x - cursor.x;
            deltaHeight = ph->rw_cursor.y - cursor.y;
            size.x += deltaWidth;
            size.y += deltaHeight;
            ph->lt_pos.y -= deltaHeight;
            ph->lt_pos.x -= deltaWidth;
            pos.y = -(ph->lt_pos.y + size.y / 2 - ph->screen_half.y);
            pos.x = ph->lt_pos.x + size.x / 2 - ph->screen_half.x;
            break;

        case HTRIGHT:
            deltaWidth = cursor.x - ph->rw_cursor.x;
            size.x += deltaWidth;
            pos.x = ph->lt_pos.x + size.x / 2 - ph->screen_half.x;
            break;

        case HTLEFT:
            deltaWidth = ph->rw_cursor.x - cursor.x;
            size.x += deltaWidth;
            ph->lt_pos.x -= deltaWidth;
            pos.x = ph->lt_pos.x + size.x / 2 - ph->screen_half.x;
            break;

        case HTBOTTOMRIGHT:
            deltaWidth = cursor.x - ph->rw_cursor.x;
            deltaHeight = cursor.y - ph->rw_cursor.y;
            size.x += deltaWidth;
            size.y += deltaHeight;
            pos.x = ph->lt_pos.x + size.x / 2 - ph->screen_half.x;
            pos.y = -(ph->lt_pos.y + size.y / 2 - ph->screen_half.y);
            break;

        case HTBOTTOMLEFT:
            deltaWidth = ph->rw_cursor.x - cursor.x;
            deltaHeight = cursor.y - ph->rw_cursor.y;
            size.x += deltaWidth;
            size.y += deltaHeight;
            ph->lt_pos.x -= deltaWidth;
            pos.x = ph->lt_pos.x + size.x / 2 - ph->screen_half.x;
            pos.y = -(ph->lt_pos.y + size.y / 2 - ph->screen_half.y);
            break;

        case HTBOTTOM:
            deltaHeight = cursor.y - ph->rw_cursor.y;
            size.y += deltaHeight;
            pos.y = -(ph->lt_pos.y + size.y / 2 - ph->screen_half.y);
            break;
        }

        ph->rw_cursor = cursor;
    }
    else
    {
        state.reset(win32_plat_h::rw_resizing);
    }

    // window move rewrite
    if (!state[win32_plat_h::zoomd] && state[win32_plat_h::rw_moving] && (GetAsyncKeyState(VK_LBUTTON) & 0x8000))
    {
        POINT cursor;
        GetCursorPos(&cursor);

        state.set(win32_plat_h::d_pos);
        pos.x += cursor.x - ph->rw_cursor.x;
        pos.y -= cursor.y - ph->rw_cursor.y;
        ph->rw_cursor = cursor;
    }
    else
    {
        state.reset(win32_plat_h::rw_moving);
    }

    // process window resize && move
    if (state[win32_plat_h::d_pos] || state[win32_plat_h::d_size])
    {

        viewbox_xy n_xy;
        n_xy.x = ph->screen_half.x + pos.x - size.x / 2;
        n_xy.y = ph->screen_half.y - pos.y - size.y / 2;

        ::MoveWindow(ph->hWnd, n_xy.x, n_xy.y, size.x, size.y, true);

        if (n_xy != ph->lt_pos)
        {
            ph->lt_pos = n_xy;
            evts.push_evts(viewbox_evt::move);
        }

        RECT rect;
        GetClientRect(ph->hWnd, &rect);
        n_xy.x = rect.right - rect.left;
        n_xy.y = rect.bottom - rect.top;
        if (content_size != n_xy)
        {
            content_size = n_xy;
            evts.push_evts(viewbox_evt::resize);
        }

        state.reset(win32_plat_h::d_pos);
        state.reset(win32_plat_h::d_size);
    }

    if (state[win32_plat_h::d_title])
    {
        ::SetWindowText(ph->hWnd, text_title.c_str());
        state.reset(win32_plat_h::d_title);
        evts.push_evts(viewbox_evt::title);
    }

    return r_ok;
}

YKM_VIEWBOX_RESULT viewbox::show()
{
    using namespace ::ykm::viewbox_internal;
    auto ph = YKM_VIEWBOX_WIN32_PH(_ph);
    if (!ph)
        return r_uninitialized;

    evts.push_evts(viewbox_evt::awake);
    ::ShowWindow(ph->hWnd, SW_SHOW);
    return r_ok;
}

YKM_VIEWBOX_RESULT viewbox::set_title(const char* title)
{
    using namespace ::ykm::viewbox_internal;
    auto ph = YKM_VIEWBOX_WIN32_PH(_ph);
    if (!ph)
        return r_uninitialized;

    text_title = title;
    ph->state.set(win32_plat_h::d_title);
    return r_ok;
}

YKM_VIEWBOX_RESULT viewbox::set_pos(int x, int y)
{
    using namespace ::ykm::viewbox_internal;
    auto ph = YKM_VIEWBOX_WIN32_PH(_ph);
    if (!ph)
        return r_uninitialized;
    pos.x = x;
    pos.y = y;
    ph->state.set(win32_plat_h::d_pos);
    return r_ok;
}

YKM_VIEWBOX_RESULT viewbox::set_size(int x, int y)
{
    using namespace ::ykm::viewbox_internal;
    auto ph = YKM_VIEWBOX_WIN32_PH(_ph);
    if (!ph)
        return r_uninitialized;
    size.x = x;
    size.y = y;
    ph->state.set(win32_plat_h::d_size);
    return r_ok;
}

YKM_VIEWBOX_RESULT viewbox::set_content_size(int x, int y)
{
    using namespace ::ykm::viewbox_internal;
    auto ph = YKM_VIEWBOX_WIN32_PH(_ph);
    if (!ph)
        return r_uninitialized;

    RECT r;
    r.top = 0;
    r.left = 0;
    r.right = x;
    r.bottom = y;
    content_size.x = x;
    content_size.y = y;

    AdjustWindowRect(&r, ph->style, FALSE);

    size.x = r.right - r.left;
    size.y = r.bottom - r.top;
    ph->state.set(win32_plat_h::d_size);
    return r_ok;
}

YKM_VIEWBOX_RESULT viewbox::hide()
{
    using namespace ::ykm::viewbox_internal;
    auto ph = YKM_VIEWBOX_WIN32_PH(_ph);
    if (!ph)
        return r_uninitialized;

    evts.push_evts(viewbox_evt::sleep);
    ::ShowWindow(ph->hWnd, SW_MINIMIZE);
    return r_ok;
}

YKM_VIEWBOX_VOID viewbox::destory()
{
    using namespace ::ykm::viewbox_internal;
    ::DestroyWindow(YKM_VIEWBOX_WIN32_PH(_ph)->hWnd);
    delete YKM_VIEWBOX_WIN32_PH(_ph);
    _ph = nullptr;
}

YKM_VIEWBOX_I(std::string) viewbox::get_internal_errinfo() const
{
    using namespace ::ykm::viewbox_internal;
    auto ph = YKM_VIEWBOX_WIN32_PH(_ph);
    return ph ? ph->last_err : "view box impl uninitialized";
}

YKM_VIEWBOX_VOID viewbox::on_fatal_error(int code, const char* title, const char* what) { MessageBox(0, what, title, MB_OK); }

} // namespace ykm

#endif
