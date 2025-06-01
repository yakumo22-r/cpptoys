/*
    ViewBox base interface define
    some functions are implemented by different files on different platforms

    version: dev 0.0.2
    date : 2024/5/6

todo: text input and candicate
*/

#ifndef YKM_APP_VIEWBOX_HPP
#define YKM_APP_VIEWBOX_HPP

#include <cstdint>
#include <string>

#include "viewbox/event.hpp"
#include "utils/num.hpp"

#include "ykm/app.h"
#include "ykm/base.h"

struct YkmApp_ViewBox
{
    ykm::ViewBoxEvt evts;
    ykm::app::i32_xy size;
    ykm::app::i32_xy content_size;
    ykm::app::i32_xy pos;
    std::string text_title;
    void* ph;
};

YKM_APP_CAPI
YkmApp_Result YkmApp_ViewBox_Create(YkmApp_ViewBox* vb, int posX, int posY, int sizeX, int sizeY, const char* title);

YKM_APP_CAPI
void YkmApp_ViewBox_Destory(YkmApp_ViewBox* vb);

YKM_APP_CAPI
YkmApp_Result YkmApp_ViewBox_Show(YkmApp_ViewBox* vb);

YKM_APP_CAPI
YkmApp_Result YkmApp_ViewBox_Hide(YkmApp_ViewBox* vb);

YKM_APP_CAPI
YkmApp_Result YkmApp_ViewBox_SetTitle(YkmApp_ViewBox* vb, const char* title);
YKM_APP_CAPI
YkmApp_Result YkmApp_ViewBox_SetPos(YkmApp_ViewBox* vb, int width, int height);
YKM_APP_CAPI
YkmApp_Result YkmApp_ViewBox_SetSize(YkmApp_ViewBox* vb, int width, int height);
YKM_APP_CAPI
YkmApp_Result YkmApp_ViewBox_SetContentSize(YkmApp_ViewBox* vb, int width, int height);

YKM_APP_CAPI
YkmApp_Result YkmApp_ViewBox_LoopBegin(YkmApp_ViewBox* vb);
YKM_APP_CAPI
YkmApp_Result YkmApp_ViewBox_LoopHandleEvts(YkmApp_ViewBox* vb);


#ifdef _WIN32
YKM_APP_CAPI
YkmApp_Result YkmApp_ViewBox_GetWin32Ptrs(YkmApp_ViewBox* vb, void** hInst, void** hWnd);
#endif

namespace ykm
{

class ViewBox final
{
  public:
    using i32_xy = app::i32_xy;

    struct implbase;
    friend implbase;
    struct PH;

    ViewBox():vb() {vb.ph = nullptr;};
    ~ViewBox() { YkmApp_ViewBox_Destory(&vb); }

    ViewBox(ViewBox&) = delete;
    ViewBox(ViewBox&&) = delete;
    auto operator=(ViewBox&) = delete;
    auto operator=(ViewBox&&) = delete;

    YkmApp_Result Create(int32_t posX, int32_t posY, int32_t sizeX, int32_t sizeY, const char* title)
    {
        return YkmApp_ViewBox_Create(&vb, posX, posY, sizeX, sizeY, title);
    }

    void Destory() { YkmApp_ViewBox_Destory(&vb); }

    YkmApp_Result Show() { return YkmApp_ViewBox_Show(&vb); }
    YkmApp_Result Hide() { return YkmApp_ViewBox_Hide(&vb); }

    YkmApp_Result SetTitle(const char* title) { return YkmApp_ViewBox_SetTitle(&vb, title); }
    YkmApp_Result SetPos(int width, int height) { return YkmApp_ViewBox_SetPos(&vb, width, height); }
    YkmApp_Result SetSize(int width, int height) { return YkmApp_ViewBox_SetSize(&vb, width, height); }
    YkmApp_Result SetContentSize(int width, int height) { return YkmApp_ViewBox_SetContentSize(&vb, width, height); }

    YkmApp_Result LoopBegin() { return YkmApp_ViewBox_LoopBegin(&vb); }
    YkmApp_Result LoopHandleEvts() { return YkmApp_ViewBox_LoopHandleEvts(&vb); }

#ifdef _WIN32
    YkmApp_Result GetWin32Ptrs(void** hInst, void** hWnd) { return YkmApp_ViewBox_GetWin32Ptrs(&vb, hInst, hWnd); }
#endif

    // set get
    PH& GetPH() { return *((PH*)vb.ph); }

    i32_xy position() const { return vb.pos; }
    int32_t width() const { return vb.size.x; }
    int32_t height() const { return vb.size.y; }

    int32_t content_width() const { return vb.content_size.x; }
    int32_t content_height() const { return vb.content_size.y; }

    const std::string& title() const { return vb.text_title; };
    const ViewBoxEvt& event() const { return vb.evts; }

  private:
    YkmApp_ViewBox vb; // viewbox data

  public:
    struct implbase
    {
        using i32_xy = app::i32_xy;
        using f_xy = app::f_xy;
        ViewBoxEvt& evts() { return vb->evts; }
        i32_xy& size() { return vb->size; }
        i32_xy& content_size() { return vb->content_size; }
        i32_xy& pos() { return vb->pos; }
        std::string& title() { return vb->text_title; }
        YkmApp_ViewBox* vb;
    };
};

} // namespace ykm

#if defined(__APPLE__)
#error "viewbox in apple no implemention yet"
#endif

#endif
