/*
windows window Interface encapsulation

version: dev 0.0.2

TODO: text input with candicate
*/

#ifndef YKM_VIEWBOX_WIN32_HPP
#define YKM_VIEWBOX_WIN32_HPP

#include "vb_win32.hpp"

#include "ykm/utils/num_fmt.hpp"
#include "../app/app_def.h"

#include "debug.hpp"

using namespace ykm::app;

namespace ykm
{

void ViewBox::PH::GetErrInfo() noexcept
{
    HRESULT hr = GetLastError();

    LPSTR pMsgBuf = nullptr;
    DWORD nMsgLen = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, hr,
                                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), pMsgBuf, 0, nullptr);
    const char* err;
    if (nMsgLen == 0) { err = "Unidentified error code"; }
    else
    {
        LocalFree(pMsgBuf);
        err = pMsgBuf;
    }

    YkmApp_SetLastError(                                                                                 //
        fmt::format("[Error Code] 0x{:X}({}) \n[Description] {} \n", hr, (unsigned long)hr, err).c_str() //
    );
}

inline constexpr char const* class_name = "ykm_ViewBox_0_0_1";

LRESULT HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    ViewBox::PH* const pWnd = reinterpret_cast<ViewBox::PH*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    if (msg == WM_NCCREATE)
    {
        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        ViewBox::PH* const pWnd = static_cast<ViewBox::PH*>(pCreate->lpCreateParams);

        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgThunk));
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ViewBox::PH::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{

    using e = ViewBoxEvt;
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
        evts().mouse.push_move_evt();
        break;

    case WM_MOUSEWHEEL:
        // same as glfw version
        // evts().mouse.scroll() = (int)(GET_WHEEL_DELTA_WPARAM(wParam) / ((float)time_dt()) * 10);
        evts().mouse.scroll() = (int)(GET_WHEEL_DELTA_WPARAM(wParam) / 12.0f);
        evts().mouse.push_scroll_evt();
        break;

    case WM_KEYDOWN:
        evts().keyboard.press(input::kc_by_sc(wParam));

        if (wParam == VK_SHIFT)
        {
            if ((GetAsyncKeyState(VK_LSHIFT) & 0x8000)) evts().keyboard.press(input::kc_by_sc(VK_LSHIFT));
            if ((GetAsyncKeyState(VK_RSHIFT) & 0x8000)) evts().keyboard.press(input::kc_by_sc(VK_RSHIFT));
        }
        else if (wParam == VK_MENU)
        {
            if ((GetAsyncKeyState(VK_LMENU) & 0x8000)) evts().keyboard.press(input::kc_by_sc(VK_LMENU));
            if ((GetAsyncKeyState(VK_RMENU) & 0x8000)) evts().keyboard.press(input::kc_by_sc(VK_RMENU));
        }
        else if (wParam == VK_CONTROL)
        {
            if ((GetAsyncKeyState(VK_LCONTROL) & 0x8000)) evts().keyboard.press(input::kc_by_sc(VK_LCONTROL));
            if ((GetAsyncKeyState(VK_RCONTROL) & 0x8000)) evts().keyboard.press(input::kc_by_sc(VK_RCONTROL));
        }

        break;
    case WM_KEYUP:
        evts().keyboard.release(input::kc_by_sc(wParam));
        if (wParam == VK_SHIFT)
        {
            if (!(GetAsyncKeyState(VK_LSHIFT) & 0x8000)) evts().keyboard.release(input::kc_by_sc(VK_LSHIFT));
            if (!(GetAsyncKeyState(VK_RSHIFT) & 0x8000)) evts().keyboard.release(input::kc_by_sc(VK_RSHIFT));
        }
        else if (wParam == VK_MENU)
        {
            if (!(GetAsyncKeyState(VK_LMENU) & 0x8000)) evts().keyboard.release(input::kc_by_sc(VK_LMENU));
            if (!(GetAsyncKeyState(VK_RMENU) & 0x8000)) evts().keyboard.release(input::kc_by_sc(VK_RMENU));
        }
        else if (wParam == VK_CONTROL)
        {
            if (!(GetAsyncKeyState(VK_LCONTROL) & 0x8000)) evts().keyboard.release(input::kc_by_sc(VK_LCONTROL));
            if (!(GetAsyncKeyState(VK_RCONTROL) & 0x8000)) evts().keyboard.release(input::kc_by_sc(VK_RCONTROL));
        }
        break;
    case WM_SYSKEYDOWN:
        evts().keyboard.press(input::kc_by_sc(wParam));
        break;
    case WM_SYSKEYUP:
        evts().keyboard.release(input::kc_by_sc(wParam));
        break;

    case WM_LBUTTONDOWN:
        evts().mouse.press(input::mouse_evt::left);
        break;
    case WM_LBUTTONUP:
        evts().mouse.release(input::mouse_evt::left);
        break;
    case WM_RBUTTONDOWN:
        evts().mouse.press(input::mouse_evt::right);
        break;
    case WM_RBUTTONUP:
        evts().mouse.release(input::mouse_evt::right);
        break;
    case WM_MBUTTONDOWN:
        evts().mouse.press(input::mouse_evt::middle);
        break;
    case WM_MBUTTONUP:
        evts().mouse.release(input::mouse_evt::middle);
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
        else { return DefWindowProc(hWnd, msg, wParam, lParam); }
        state.reset(rw_resizing);
        rw_hithc = HTNOWHERE;
        return NULL;

    case WM_CLOSE:
        evts().push_evts(ViewBoxEvt::close);
        PostQuitMessage(0);
    }

    // if (hmp != nullptr)
    //     hmp(hWnd, msg, wParam, lParam);

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

YKM_APP_API
ViewBox::ViewBox() : ph(*new PH())
{
    ph.vb = this;
    ph.hInst = GetModuleHandle(nullptr);
    ph.hWnd = nullptr;
}

YKM_APP_API
ViewBox::~ViewBox()
{
    Destory();
    delete &ph;
}

YKM_APP_API
YkmApp_Result ViewBox::Create(int32_t posX, int32_t posY, int32_t sizeX, int32_t sizeY, const char* title)
{
    Destory();

    static WNDCLASSEX wc = {0};
    static bool wc_reg = false;

    if (!wc_reg)
    {
        wc.cbSize = sizeof(wc);
        wc.style = CS_OWNDC;
        wc.lpfnWndProc = HandleMsgSetup;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = ph.hInst;
        wc.hIcon = nullptr;
        wc.hCursor = nullptr;
        wc.hbrBackground = nullptr;
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = class_name;
        wc.hIconSm = nullptr;
        RegisterClassEx(&wc);
        wc_reg = true;
    }

    size = {sizeX, sizeY};

    text_title = std::string(title);

    ph.style = WS_OVERLAPPEDWINDOW;

    ph.screen_half.x = GetSystemMetrics(SM_CXSCREEN) / 2;
    ph.screen_half.y = GetSystemMetrics(SM_CYSCREEN) / 2;

    pos = {posX, posY};

    ph.lt_pos = ph.pos_2_ltpos(pos);

    evts.clear_evts();
    evts.keyboard.next_frame();
    evts.mouse.next_frame();

    ph.hWnd = CreateWindow(class_name, title, ph.style, ph.lt_pos.x, ph.lt_pos.y, size.x, size.y, nullptr, nullptr, ph.hInst, &ph);

    if (ph.hWnd == nullptr)
    {
        ph.GetErrInfo();
        Destory();
        // MessageBox(0, ph.last_err.c_str(), "ykm ViewBox create error", MB_OK);
        return YkmApp_R_InternalError;
    }

    // check window maximization status
    if (IsZoomed(ph.hWnd)) { ph.state.set(PH::zoomd); }
    else { ph.state.reset(PH::zoomd); }

    RECT rect;
    GetClientRect(ph.hWnd, &rect);
    content_size = {rect.right - rect.left, rect.bottom - rect.top};

    ph.ca_content_size = content_size;
    ph.ca_size = size;
    ph.ca_pos = pos;

    return YkmApp_R_Ok;
}

YKM_APP_API YkmApp_Result ViewBox::LoopBegin()
{
    if (!ph.hWnd) return YkmApp_R_Uninitialized;
    evts.clear_evts();
    evts.keyboard.next_frame();
    evts.mouse.clear();
    return YkmApp_R_Ok;
}
YKM_APP_API YkmApp_Result ViewBox::LoopHandleEvts()
{
    auto& state = ph.state;

    // window resize rewrite
    if (!state[PH::zoomd] && state[PH::rw_resizing] && (GetAsyncKeyState(VK_LBUTTON) & 0x8000))
    {
        POINT cursor;
        GetCursorPos(&cursor);

        i32_xy v = {cursor.x - ph.rw_cursor.x, cursor.y - ph.rw_cursor.y};

        int32_t left = ph.lt_pos.x;
        int32_t right = left + size.x;

        int32_t top = ph.lt_pos.y;
        int32_t bottom = ph.lt_pos.y + size.y;

        switch (ph.rw_hithc)
        {
        case HTTOP:
            top += v.y;
            break;

        case HTTOPRIGHT:
            top += v.y;
            right += v.x;
            break;

        case HTTOPLEFT:
            top += v.y;
            left += v.x;
            break;

        case HTRIGHT:
            right += v.x;
            break;

        case HTLEFT:
            left += v.x;
            break;

        case HTBOTTOMRIGHT:
            bottom += v.y;
            right += v.x;
            break;

        case HTBOTTOMLEFT:
            bottom += v.y;
            left += v.x;
            break;

        case HTBOTTOM:
            bottom += v.y;
            break;
        }
        ph.lt_pos = {left, top};

        v = ph.ltpos_2_pos(ph.lt_pos);
        if (pos != v) { evts.push_evts(ViewBoxEvt::move); }
        pos = v;
        ph.ca_pos = v;

        v = {right - left, bottom - top};
        if (size != v) { evts.push_evts(ViewBoxEvt::resize); }
        size = v;
        ph.ca_size = v;

        ::MoveWindow(ph.hWnd, ph.lt_pos.x, ph.lt_pos.y, size.x, size.y, true);

        RECT rect;
        GetClientRect(ph.hWnd, &rect);
        v = {rect.right - rect.left, rect.bottom - rect.top};
        content_size = v;
        ph.ca_content_size = v;

        ph.rw_cursor = cursor;
    }
    else { state.reset(PH::rw_resizing); }

    // window move rewrite
    if (!state[PH::zoomd] && state[PH::rw_moving] && (GetAsyncKeyState(VK_LBUTTON) & 0x8000))
    {
        POINT cursor;
        GetCursorPos(&cursor);

        i32_xy v = {cursor.x - ph.rw_cursor.x, ph.rw_cursor.y - cursor.y};
        ph.rw_cursor = cursor;

        ph.ca_pos = pos + v;

        if (pos != ph.ca_pos)
        {
            pos = ph.ca_pos;
            ph.lt_pos = ph.pos_2_ltpos(pos);
            evts.push_evts(ViewBoxEvt::move);
            ::MoveWindow(ph.hWnd, ph.lt_pos.x, ph.lt_pos.y, size.x, size.y, true);
        }
    }
    else { state.reset(PH::rw_moving); }

    // process window resize && move
    if (state[PH::d_size_pos])
    {
        if (size != ph.ca_size)
        {
            evts.push_evts(ViewBoxEvt::resize);
            size = ph.ca_size;
            content_size = ph.ca_content_size;
        }

        ph.lt_pos = ph.pos_2_ltpos(ph.ca_pos);
        if (pos != ph.ca_pos)
        {
            evts.push_evts(ViewBoxEvt::move);
            pos = ph.ca_pos;
        }

        ::MoveWindow(ph.hWnd, ph.lt_pos.x, ph.lt_pos.y, size.x, size.y, true);

        RECT rect;
        GetClientRect(ph.hWnd, &rect);
        i32_xy v = {rect.right - rect.left, rect.bottom - rect.top};
        content_size = v;
        ph.ca_content_size = v;

        state.reset(PH::d_size_pos);
    }

    if (state[PH::d_title])
    {
        ::SetWindowText(ph.hWnd, text_title.c_str());
        state.reset(PH::d_title);
        evts.push_evts(ViewBoxEvt::title);
    }

    return YkmApp_R_Ok;
}

// YKM_APP_API
// YkmApp_Result ViewBox::ProcessLoop()
//{
//     if (!ph.hWnd) return YkmApp_R_Uninitailized;

//    evts.clear_evts();
//    evts.keyboard.next_frame();
//    evts.mouse.clear();

//    MSG msg;

//    if (PeekMessage(&msg, ph.hWnd, 0, 0, PM_REMOVE) != 0)
//    {
//        if (msg.message == WM_QUIT)
//        {
//            ph.state.reset(PH::alive);
//            return r_quit;
//        }
//        TranslateMessage(&msg);
//        DispatchMessage(&msg);
//    }

//}

YKM_APP_API
YkmApp_Result ViewBox::Show()
{
    if (!ph.hWnd) return YkmApp_R_Uninitialized;

    evts.push_evts(ViewBoxEvt::awake);
    ::ShowWindow(ph.hWnd, SW_SHOW);
    return YkmApp_R_Ok;
}

YKM_APP_API
YkmApp_Result ViewBox::SetTitle(const char* title)
{
    if (!ph.hWnd) return YkmApp_R_Uninitialized;

    text_title = title;
    ph.state.set(PH::d_title);
    return YkmApp_R_Ok;
}

YKM_APP_API
YkmApp_Result ViewBox::SetPos(int x, int y)
{
    if (!ph.hWnd) return YkmApp_R_Uninitialized;
    ph.ca_pos = {x, y};
    ph.state.set(PH::d_size_pos);
    return YkmApp_R_Ok;
}

YKM_APP_API
YkmApp_Result ViewBox::SetSize(int x, int y)
{
    if (!ph.hWnd) return YkmApp_R_Uninitialized;

    ph.ca_size = {x, y};

    RECT rect;
    GetClientRect(ph.hWnd, &rect);
    ph.ca_content_size = {rect.right - rect.left, rect.bottom - rect.top};

    ph.state.set(PH::d_size_pos);
    return YkmApp_R_Ok;
}

YKM_APP_API
YkmApp_Result ViewBox::SetContentSize(int x, int y)
{
    if (!ph.hWnd) return YkmApp_R_Uninitialized;

    RECT r;
    r.top = 0;
    r.left = 0;
    r.right = x;
    r.bottom = y;

    ph.ca_content_size = {x, y};

    AdjustWindowRect(&r, ph.style, FALSE);

    ph.ca_size = {r.right - r.left, r.bottom - r.top};

    ph.state.set(PH::d_size_pos);
    return YkmApp_R_Ok;
}

YKM_APP_API
YkmApp_Result ViewBox::Hide()
{
    if (!ph.hWnd) return YkmApp_R_Uninitialized;

    evts.push_evts(ViewBoxEvt::sleep);
    ::ShowWindow(ph.hWnd, SW_MINIMIZE);
    return YkmApp_R_Ok;
}

YKM_APP_API
void ViewBox::Destory()
{
    if (!ph.hWnd) return;

    ::DestroyWindow(ph.hWnd);
    ph.hWnd = nullptr;
}

} // namespace ykm

#endif
