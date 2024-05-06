/*
    viewbox base interface define
    some functions are implemented by different files on different platforms

    version: dev 0.0.1
    date : 2024/5/6

todo: text input
*/
#include "event.hpp"
#include <cstdint>

#define YKM_VIEWBOX_I(r) r
#define YKM_VIEWBOX_RESULT ::ykm::viewbox::result
#define YKM_VIEWBOX_VOID void

namespace ykm
{

struct viewbox final
{
    inline static constexpr int r_ok = 0;
    inline static constexpr int r_uninitialized = -1;
    inline static constexpr int r_internal = -1;

    struct result
    {
        viewbox* vb;
        int code;
    };

    viewbox() : _ph(nullptr) {}

    // These functions that macros return values will be implemented in other files

    YKM_VIEWBOX_RESULT create(int32_t posX, int32_t posY, int32_t sizeX, int32_t sizeY, const char* title);
    YKM_VIEWBOX_RESULT show();
    YKM_VIEWBOX_RESULT hide();

    YKM_VIEWBOX_VOID destory();

    YKM_VIEWBOX_RESULT set_title(const char* title);
    YKM_VIEWBOX_RESULT set_pos(int width, int height);
    YKM_VIEWBOX_RESULT set_size(int width, int height);

    YKM_VIEWBOX_RESULT process_loop();

    YKM_VIEWBOX_I(std::string) get_internal_errinfo() const;


    static YKM_VIEWBOX_VOID on_fatal_error(int code, const char* title, const char* what);
    // set get
    void* get_plat_h() { return _ph; }
    viewbox_xy position() const { return pos; }
    int32_t width() const { return size.x; }
    int32_t height() const { return size.y; }
    const std::string& title() const { return str_title; };
    const viewbox_evt& event() const { return evts; }

    ~viewbox()
    {
        if (_ph)
            destory();
    }

  private:
// this macro should be defined before include this file
#ifdef YKM_VIEWBOX_IMPL
    friend YKM_VIEWBOX_IMPL;
#endif

    viewbox_evt evts;
    viewbox_xy size;
    viewbox_xy pos;
    std::string str_title;
    void* _ph;
};

struct viewbox_errcheck
{
    void operator|(YKM_VIEWBOX_RESULT r)
    {
        switch (r.code)
        {
        case viewbox::r_ok:
            return;
        case viewbox::r_uninitialized:
            r.vb->on_fatal_error(r.code, "call error", "viewbox impl not implementation");
        default:
            r.vb->on_fatal_error(r.code, "internal error", r.vb->get_internal_errinfo().c_str());
        }
        return;
    }
};

} // namespace ykm
