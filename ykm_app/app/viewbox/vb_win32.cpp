/*
windows window Interface encapsulation

version: dev 0.0.2

 TODO: text input with candicate
*/

#include "vb_win32.hpp"

#include "fmt/core.h"
#include "ykm/app.h"
#include "ykm/utils/num_fmt.hpp"
#include "../app_def.h"

#include "debug.hpp"
#include "ykm/viewbox.hpp"

#include <winuser.h>

YKM_APP_VIEWBOX_DEBUG;
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

    switch (msg)
    {
    case WM_ACTIVATE:
        if (LOWORD(wParam) != WA_INACTIVE)
        {
            if (!state[active]) { evts().push_evts(ViewBoxEvt::active); }
            state.set(active);
        }
        else
        {
            if (state[active]) { evts().push_evts(ViewBoxEvt::unactive); }
            state.reset(active);
        }

    case WM_SIZE:

        // check window maximization status

        if (wParam != SIZE_MINIMIZED)
        {
            content_size().x = LOWORD(lParam);
            content_size().y = HIWORD(lParam);
            if (IsZoomed(hWnd))
                state.set(zoomd);
            else
                state.reset(zoomd);
        }

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

    case WM_SYSCOMMAND:
        if (wParam == SC_MINIMIZE)
        {
            if (!state[sleepd]) { evts().push_evts(ViewBoxEvt::sleep); }
            state.set(sleepd);
            state.reset(zoomd);
        }
        else if (wParam == SC_RESTORE)
        {
            if (state[sleepd]) { evts().push_evts(ViewBoxEvt::awake); }
            state.reset(sleepd);
        }
        break;

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

YKM_APP_CAPI
YkmApp_Result YkmApp_ViewBox_Create(YkmApp_ViewBox* vb, int32_t posX, int32_t posY, int32_t sizeX, int32_t sizeY, const char* title)
{

    YkmApp_ViewBox_Destory(vb);
    using PH = ViewBox::PH;

    auto* ph = new PH();
    vb->ph = ph;
    ph->vb = vb;
    ph->hInst = GetModuleHandle(nullptr);
    ph->hWnd = nullptr;

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

    vb->size = {sizeX, sizeY};

    vb->text_title = std::string(title);

    ph->style = WS_OVERLAPPEDWINDOW;

    ph->screen_half.x = GetSystemMetrics(SM_CXSCREEN) / 2;
    ph->screen_half.y = GetSystemMetrics(SM_CYSCREEN) / 2;

    vb->pos = {posX, posY};

    ph->lt_pos = ph->pos_2_ltpos(vb->pos);

    auto& evts = vb->evts;
    evts.clear_evts();
    evts.keyboard.next_frame();
    evts.mouse.next_frame();

    ph->hWnd = CreateWindow(class_name,       //
                            title,            //
                            ph->style,        //
                            ph->lt_pos.x,     //
                            ph->lt_pos.y,     //
                            vb->size.x,       //
                            vb->size.y,       //
                            nullptr, nullptr, //
                            ph->hInst, ph);

    if (ph->hWnd == nullptr)
    {
        ph->GetErrInfo();
        YkmApp_ViewBox_Destory(vb);
        // MessageBox(0, ph.last_err.c_str(), "ykm ViewBox create error", MB_OK);
        return YkmApp_R_InternalError;
    }

    ::ShowWindow(ph->hWnd, SW_SHOWNORMAL);
    RECT rect;
    GetClientRect(ph->hWnd, &rect);
    vb->content_size = {rect.right - rect.left, rect.bottom - rect.top};

    ph->state.set(PH::sleepd);

    // check window maximization status
    if (IsZoomed(ph->hWnd)) { ph->state.set(PH::zoomd); }
    else { ph->state.reset(PH::zoomd); }

    ph->ca_content_size = vb->content_size;
    ph->ca_size = vb->size;
    ph->ca_pos = vb->pos;

    return YkmApp_R_Ok;
}

YKM_APP_CAPI
void YkmApp_ViewBox_Destory(YkmApp_ViewBox* vb)
{
    if (vb->ph)
    {
        auto* ph = (ViewBox::PH*)vb->ph;
        ::DestroyWindow(ph->hWnd);
        delete ph;
        vb->ph = nullptr;
    }
}

YKM_APP_CAPI
YkmApp_Result YkmApp_ViewBox_LoopBegin(YkmApp_ViewBox* vb)
{
    if (!vb->ph) return YkmApp_R_Uninitialized;
    auto& evts = vb->evts;
    evts.clear_evts();
    evts.keyboard.next_frame();
    evts.mouse.clear();
    return YkmApp_R_Ok;
}

YKM_APP_CAPI
YkmApp_Result YkmApp_ViewBox_LoopHandleEvts(YkmApp_ViewBox* vb)
{
    using PH = ViewBox::PH;
    auto& ph = *(PH*)vb->ph;
    auto& state = ph.state;
    auto& size = vb->size;
    auto& pos = vb->pos;
    auto& content_size = vb->content_size;
    auto& evts = vb->evts;
    auto& text_title = vb->text_title;

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
        if(state[PH::d_content_size]){
            ph.ca_size.x = size.x + ph.ca_content_size.x - content_size.x;
            ph.ca_size.y = size.y + ph.ca_content_size.y - content_size.y;
            state.reset(PH::d_content_size);
        }

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

    if (state[PH::d_sleep] && state[PH::ca_sleepd] != state[PH::sleepd])
    {
        if (state[PH::ca_sleepd])
        {
            ::ShowWindow(ph.hWnd, SW_SHOWMINIMIZED);
            evts.push_evts(ViewBoxEvt::sleep);
            state.set(PH::sleepd);
        }
        else
        {
            ::ShowWindow(ph.hWnd, SW_SHOWNORMAL);
            ::MoveWindow(ph.hWnd, ph.lt_pos.x, ph.lt_pos.y, size.x, size.y, true);
            evts.push_evts(ViewBoxEvt::awake);
            state.reset(PH::sleepd);
        }
        state.reset(PH::d_sleep);
    }

    return YkmApp_R_Ok;
}

YKM_APP_CAPI
YkmApp_Result YkmApp_ViewBox_Show(YkmApp_ViewBox* vb)
{
    using PH = ViewBox::PH;
    auto& ph = *(PH*)vb->ph;
    if (!ph.hWnd) return YkmApp_R_Uninitialized;
    ph.state.set(PH::d_sleep);
    ph.state.reset(PH::ca_sleepd);
    return YkmApp_R_Ok;
}

YKM_APP_CAPI
YkmApp_Result YkmApp_ViewBox_Hide(YkmApp_ViewBox* vb)
{
    using PH = ViewBox::PH;
    auto& ph = *(PH*)vb->ph;
    if (!ph.hWnd) return YkmApp_R_Uninitialized;
    ph.state.set(PH::d_sleep);
    ph.state.set(PH::ca_sleepd);
    return YkmApp_R_Ok;
}

YKM_APP_CAPI
YkmApp_Result YkmApp_ViewBox_SetTitle(YkmApp_ViewBox* vb, const char* title)
{
    using PH = ViewBox::PH;
    auto& ph = *(PH*)vb->ph;
    if (!ph.hWnd) return YkmApp_R_Uninitialized;

    vb->text_title = std::string(title);
    ph.state.set(PH::d_title);
    return YkmApp_R_Ok;
}

YKM_APP_CAPI
YkmApp_Result YkmApp_ViewBox_SetPos(YkmApp_ViewBox* vb, int width, int height)
{
    using PH = ViewBox::PH;
    auto& ph = *(PH*)vb->ph;
    if (!ph.hWnd) return YkmApp_R_Uninitialized;

    ph.ca_pos = {width, height};
    ph.state.set(PH::d_size_pos);
    return YkmApp_R_Ok;
}

YKM_APP_CAPI
YkmApp_Result YkmApp_ViewBox_SetSize(YkmApp_ViewBox* vb, int width, int height)
{
    using PH = ViewBox::PH;
    auto& ph = *(PH*)vb->ph;
    if (!ph.hWnd) return YkmApp_R_Uninitialized;

    ph.ca_size = {width, height};
    ph.ca_content_size = {width, height};

    ph.state.set(PH::d_size_pos);
    return YkmApp_R_Ok;
}

YKM_APP_CAPI
YkmApp_Result YkmApp_ViewBox_SetContentSize(YkmApp_ViewBox* vb, int width, int height)
{
    using PH = ViewBox::PH;
    auto& ph = *(PH*)vb->ph;
    if (!ph.hWnd) return YkmApp_R_Uninitialized;

    ph.ca_size = {width, height};
    ph.ca_content_size = {width, height};

    ph.state.set(PH::d_content_size);
    ph.state.set(PH::d_size_pos);
    return YkmApp_R_Ok;
}

YKM_APP_CAPI
YkmApp_Result YkmApp_ViewBox_GetWin32Ptrs(YkmApp_ViewBox* vb, void** hInst, void** hWnd)
{
    using PH = ViewBox::PH;
    auto& ph = *(PH*)vb->ph;
    if (!ph.hWnd) return YkmApp_R_Uninitialized;

    if (hInst) *hInst = ph.hInst;
    if (hWnd) *hWnd = ph.hWnd;

    return YkmApp_R_Ok;
}

} // namespace ykm
