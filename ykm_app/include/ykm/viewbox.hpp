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


#include "app.hpp"
YKM_APP_APP_HPP // include cpp version

namespace ykm
{

class ViewBox final
{
  public:
    using i32_xy = app::i32_xy;

    struct implbase;
    friend implbase;
    struct PH;

    YKM_APP_API ViewBox();
    YKM_APP_API ~ViewBox();

    ViewBox(ViewBox&) = delete;
    ViewBox(ViewBox&&) = delete;
    auto operator=(ViewBox&) = delete;
    auto operator=(ViewBox&&) = delete;

    YKM_APP_API YkmApp_Result Create //
        (int32_t posX, int32_t posY, int32_t sizeX, int32_t sizeY, const char* title);

    YKM_APP_API void Destory();

    YKM_APP_API YkmApp_Result Show();
    YKM_APP_API YkmApp_Result Hide();


    YKM_APP_API YkmApp_Result SetTitle(const char* title);
    YKM_APP_API YkmApp_Result SetPos(int width, int height);
    YKM_APP_API YkmApp_Result SetSize(int width, int height);
    YKM_APP_API YkmApp_Result SetContentSize(int width, int height);

    YKM_APP_API YkmApp_Result LoopBegin();
    YKM_APP_API YkmApp_Result LoopHandleEvts();

    // set get
    PH& GetPH() { return ph; }

    i32_xy position() const { return pos; }
    int32_t width() const { return size.x; }
    int32_t height() const { return size.y; }

    int32_t content_width() const { return content_size.x; }
    int32_t content_height() const { return content_size.y; }

    const std::string& title() const { return text_title; };
    const ViewBoxEvt& event() const { return evts; }

  private:
    ViewBoxEvt evts;
    i32_xy size;
    i32_xy content_size;
    i32_xy pos;
    std::string text_title;
    PH& ph;

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
        ViewBox* vb;
    };
};

} // namespace ykm

#if defined(__APPLE__)
#error "viewbox in apple no implemention yet"
#endif

#endif
