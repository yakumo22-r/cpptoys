/*
windows window Interface encapsulation

version: dev 0.0.1
date : 2024/5/6
*/

#ifndef YKM_VIEWBOX_WIN32_HPP
#define YKM_VIEWBOX_WIN32_HPP

#include <Windows.h>
#include <cstdint>
#include <format>
#include <string>

#include "event.hpp"

namespace ykm::viewbox_internal
{
struct win32_plat_h;
}

#define YKM_VIEWBOX_IMPL ::ykm::viewbox_internal::win32_plat_h
#include "interface.hpp"

namespace ykm
{
namespace viewbox_internal
{

// impl
struct win32_plat_h
{
    HINSTANCE hInst;
    HWND hWnd;
    std::string last_err;

    viewbox_xy lt_pos;
    viewbox* vb;

    WPARAM rw_hithc;
    POINT rw_cursor;
    bool rw_resizing;
    bool rw_moving;

    bool active;
    bool alive;

    bool dirty_title;
    bool dirty_size;
    bool dirty_pos;

    LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

    void GetErrInfo() noexcept;

    void reset_rw()
    {
        rw_hithc = 0;
        rw_resizing = false;
        rw_moving = false;
    }
};

inline void win32_plat_h::GetErrInfo() noexcept
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
    last_err = std::format("[Error Code] 0x{:X}({}) \n[Description] {} \n", hr, (unsigned long)hr, err);
}

inline constexpr char const* class_name = "ykm_viewbox_0_0_1";

inline LRESULT HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    win32_plat_h* const pWnd = reinterpret_cast<win32_plat_h*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

inline LRESULT HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
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

inline LRESULT win32_plat_h::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{

    using e = viewbox_evt;
    switch (msg)
    {
    case WM_ACTIVATE:
        vb->evts.push_evts(LOWORD(wParam) != WA_INACTIVE ? e::active : e::unactive);
        if (LOWORD(wParam) != WA_INACTIVE)
            active = true;
        else
            active = false;

    case WM_SIZE:
        vb->evts.push_evts(e::resize);
        vb->size.x = LOWORD(lParam);
        vb->size.y = HIWORD(lParam);
        // std::cout  << "WM_SIZE " << wndWidth << " " << wndHeight << std::endl;
        switch (wParam)
        {
        case 0: // 窗口大小变化
            // bWndMoveable = true;
            break;
        case 2: // 窗口最大化
            // bWndMoveable = false;
            break;
        }
        break;
    case WM_MOVE:
        // std::cout << "WM_MOVE " << LOWORD(lParam) << " " << HIWORD(lParam) << std::endl;
        vb->evts.push_evts(e::move);
        break;

    case WM_MOUSEMOVE:
        vb->evts.mouse.x() = LOWORD(lParam);
        vb->evts.mouse.y() = HIWORD(lParam);
        break;

    case WM_MOUSEWHEEL:
        vb->evts.mouse.scroll() = GET_WHEEL_DELTA_WPARAM(wParam);
        break;

    case WM_KEYDOWN:
        vb->evts.keyboard.press(input::kc_by_win(wParam));

        if (wParam == VK_SHIFT)
        {
            if ((GetAsyncKeyState(VK_LSHIFT) & 0x8000))
                vb->evts.keyboard.press(input::kc_by_win(VK_LSHIFT));
            if ((GetAsyncKeyState(VK_RSHIFT) & 0x8000))
                vb->evts.keyboard.press(input::kc_by_win(VK_RSHIFT));
        }
        else if (wParam == VK_MENU)
        {
            if ((GetAsyncKeyState(VK_LMENU) & 0x8000))
                vb->evts.keyboard.press(input::kc_by_win(VK_LMENU));
            if ((GetAsyncKeyState(VK_RMENU) & 0x8000))
                vb->evts.keyboard.press(input::kc_by_win(VK_RMENU));
        }
        else if (wParam == VK_CONTROL)
        {
            if ((GetAsyncKeyState(VK_LCONTROL) & 0x8000))
                vb->evts.keyboard.press(input::kc_by_win(VK_LCONTROL));
            if ((GetAsyncKeyState(VK_RCONTROL) & 0x8000))
                vb->evts.keyboard.press(input::kc_by_win(VK_RCONTROL));
        }

        break;
    case WM_KEYUP:
        vb->evts.keyboard.release(input::kc_by_win(wParam));
        if (wParam == VK_SHIFT)
        {
            if (!(GetAsyncKeyState(VK_LSHIFT) & 0x8000))
                vb->evts.keyboard.release(input::kc_by_win(VK_LSHIFT));
            if (!(GetAsyncKeyState(VK_RSHIFT) & 0x8000))
                vb->evts.keyboard.release(input::kc_by_win(VK_RSHIFT));
        }
        else if (wParam == VK_MENU)
        {
            if (!(GetAsyncKeyState(VK_LMENU) & 0x8000))
                vb->evts.keyboard.release(input::kc_by_win(VK_LMENU));
            if (!(GetAsyncKeyState(VK_RMENU) & 0x8000))
                vb->evts.keyboard.release(input::kc_by_win(VK_RMENU));
        }
        else if (wParam == VK_CONTROL)
        {
            if (!(GetAsyncKeyState(VK_LCONTROL) & 0x8000))
                vb->evts.keyboard.release(input::kc_by_win(VK_LCONTROL));
            if (!(GetAsyncKeyState(VK_RCONTROL) & 0x8000))
                vb->evts.keyboard.release(input::kc_by_win(VK_RCONTROL));
        }
        break;
    case WM_SYSKEYDOWN:
        vb->evts.keyboard.press(input::kc_by_win(wParam));
        break;
    case WM_SYSKEYUP:
        vb->evts.keyboard.release(input::kc_by_win(wParam));
        break;

    case WM_LBUTTONDOWN:
        vb->evts.mouse.press(input::btncode::left);
        break;
    case WM_LBUTTONUP:
        vb->evts.mouse.release(input::btncode::left);
        break;
    case WM_RBUTTONDOWN:
        vb->evts.mouse.press(input::btncode::right);
        break;
    case WM_RBUTTONUP:
        vb->evts.mouse.release(input::btncode::right);
        break;
    case WM_MBUTTONDOWN:
        vb->evts.mouse.press(input::btncode::middle);
        break;
    case WM_MBUTTONUP:
        vb->evts.mouse.release(input::btncode::middle);
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
            rw_resizing = true;
            rw_hithc = wParam;
            GetCursorPos(&rw_cursor);
        }
        else if (wParam == HTCAPTION)
        {
            rw_moving = true;
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
        rw_resizing = false;
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

inline viewbox::result viewbox::create(int32_t posX, int32_t posY, int32_t sizeX, int32_t sizeY, const char* title)
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
    size.x = sizeY;
    str_title = std::string(title);
    evts.clear_evts();

    ph->hWnd = CreateWindow(class_name, title, 0, 0, 0, sizeX, sizeY, nullptr, nullptr, ph->hInst, this);
    if (ph->hWnd == nullptr)
    {
        ph->GetErrInfo();
        //MessageBox(0, ph->last_err.c_str(), "ykm viewbox create error", MB_OK);
        return r_internal;
    }
    // SetWindowPos(posX, posY);
    return r_ok;
}

inline int viewbox::process_loop()
{
    using namespace ::ykm::viewbox_internal;
    auto ph = YKM_VIEWBOX_WIN32_PH(_ph);

    if (!ph)
        return r_uninitialized;

    MSG msg;

    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0)
    {
        if (msg.message == WM_QUIT)
        {
            ph->alive = false;
            return r_ok;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // resize rewrite
    if (ph->rw_resizing && GetAsyncKeyState(VK_LBUTTON) & 0x8000)
    {
        POINT cursor;
        GetCursorPos(&cursor);
        int16_t deltaWidth;
        int16_t deltaHeight;

        ph->dirty_pos = true;
        ph->dirty_size = true;

        switch (ph->rw_hithc)
        {
        case HTTOP:
            deltaHeight = ph->rw_cursor.y - cursor.y;
            size.x += deltaHeight;
            pos.y = ph->lt_pos.y - deltaHeight + size.y / 2;
            break;

        case HTTOPRIGHT:
            deltaWidth = cursor.x - ph->rw_cursor.x;
            deltaHeight = ph->rw_cursor.y - cursor.y;
            size.x += deltaWidth;
            size.x += deltaHeight;
            pos.y = ph->lt_pos.y - deltaHeight + size.y / 2;
            pos.x = ph->lt_pos.x + size.x / 2;
            break;

        case HTTOPLEFT:
            deltaWidth = ph->rw_cursor.x - cursor.x;
            deltaHeight = ph->rw_cursor.y - cursor.y;
            size.x += deltaWidth;
            size.y += deltaHeight;
            pos.y = ph->lt_pos.y - deltaHeight + size.y / 2;
            pos.x = ph->lt_pos.x - deltaWidth + size.x / 2;
            break;

        case HTRIGHT:
            deltaWidth = cursor.x - ph->rw_cursor.x;
            size.x += deltaWidth;
            pos.x = ph->lt_pos.x + size.x / 2;
            break;

        case HTLEFT:
            deltaWidth = ph->rw_cursor.x - cursor.x;
            size.x += deltaWidth;
            pos.x = ph->lt_pos.x - deltaWidth + size.x / 2;
            break;

        case HTBOTTOMRIGHT:
            deltaWidth = cursor.x - ph->rw_cursor.x;
            deltaHeight = cursor.y - ph->rw_cursor.y;
            size.x += deltaWidth;
            size.y += deltaHeight;
            pos.x = ph->lt_pos.x + size.x / 2;
            pos.y = ph->lt_pos.y + size.y / 2;
            break;

        case HTBOTTOMLEFT:
            deltaWidth = ph->rw_cursor.x - cursor.x;
            deltaHeight = cursor.y - ph->rw_cursor.y;
            size.x += deltaWidth;
            size.y += deltaHeight;
            pos.x = ph->lt_pos.x - deltaWidth + size.x / 2;
            pos.y = ph->lt_pos.y + size.y / 2;
            break;

        case HTBOTTOM:
            deltaHeight = cursor.y - ph->rw_cursor.y;
            size.y += deltaHeight;
            pos.y = ph->lt_pos.y + size.y / 2;
            break;
        }

        ph->rw_cursor = cursor;
    }
    else
    {
        ph->rw_resizing = false;
    }

    if (ph->rw_moving && GetAsyncKeyState(VK_LBUTTON) & 0x8000)
    {
        POINT cursor;
        GetCursorPos(&cursor);

        ph->dirty_pos = true;
        pos.x += cursor.x - ph->rw_cursor.x;
        pos.y += cursor.y - ph->rw_cursor.y;
        ph->rw_cursor = cursor;
    }
    else
    {
        ph->rw_moving = false;
    }

    if (ph->dirty_pos || ph->dirty_size)
    {
        ph->lt_pos.x = pos.x - size.x / 2;
        ph->lt_pos.y = pos.y - size.y / 2;
        ::SetWindowPos(ph->hWnd, HWND_NOTOPMOST, ph->lt_pos.x, ph->lt_pos.y, size.x, size.y, SWP_SHOWWINDOW);

        ph->dirty_pos = false;
        ph->dirty_size = false;
    }

    if (ph->dirty_title)
    {
        ::SetWindowText(ph->hWnd, str_title.c_str());
        ph->dirty_title = false;
        evts.push_evts(viewbox_evt::title);
    }

    return r_ok;
}

inline int viewbox::show()
{
    using namespace ::ykm::viewbox_internal;
    auto ph = YKM_VIEWBOX_WIN32_PH(_ph);
    if (!ph)
        return r_uninitialized;

    evts.push_evts(viewbox_evt::awake);
    ::ShowWindow(ph->hWnd, SW_SHOW);
    return r_ok;
}

inline int viewbox::set_title(const char* title)
{
    using namespace ::ykm::viewbox_internal;
    auto ph = YKM_VIEWBOX_WIN32_PH(_ph);
    if (!ph)
        return r_uninitialized;

    str_title = title;
    ph->dirty_title = true;
    return r_ok;
}
inline int viewbox::set_pos(int x, int y)
{
    using namespace ::ykm::viewbox_internal;
    auto ph = YKM_VIEWBOX_WIN32_PH(_ph);
    if (!ph)
        return r_uninitialized;
    pos.x = x;
    pos.y = y;
    ph->dirty_pos = true;
    return r_ok;
}
inline int viewbox::set_size(int x, int y)
{
    using namespace ::ykm::viewbox_internal;
    auto ph = YKM_VIEWBOX_WIN32_PH(_ph);
    if (!ph)
        return r_uninitialized;
    size.x = x;
    size.y = y;
    ph->dirty_size = true;
    return r_ok;
}

inline int viewbox::hide()
{
    using namespace ::ykm::viewbox_internal;
    auto ph = YKM_VIEWBOX_WIN32_PH(_ph);
    if (!ph)
        return r_uninitialized;

    evts.push_evts(viewbox_evt::sleep);
    ::ShowWindow(ph->hWnd, SW_MINIMIZE);
    return r_ok;
}

inline void viewbox::destory()
{
    using namespace ::ykm::viewbox_internal;
    ::DestroyWindow(YKM_VIEWBOX_WIN32_PH(_ph)->hWnd);
    delete YKM_VIEWBOX_WIN32_PH(_ph);
    _ph = nullptr;
}

std::string viewbox::get_internal_errinfo() const
{
    using namespace ::ykm::viewbox_internal;
    auto ph = YKM_VIEWBOX_WIN32_PH(_ph);
    return ph ? ph->last_err : "view box impl uninitialized";
}

} // namespace ykm

#endif
