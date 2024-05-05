/*
    viewbox base interface define

    version: dev 0.0.1
    date : 2024/5/6

todo: error interface
*/
#include "event.hpp"
#include <cstdint>

#ifndef YKM_VIEWBOX_IMPL
struct __ykm_viewbox_impl_error__
{
};

#define YKM_VIEWBOX_IMPL __ykm_viewbox_impl_error__

static_assert(false, "must define impl");
#endif

namespace ykm
{

struct viewbox final
{
    inline static constexpr int r_ok = 0;
    inline static constexpr int r_uninitialized = -1;
    inline static constexpr int r_internal = -1;

    using result = int;
    viewbox() : _ph(nullptr) {}

    result create(int32_t posX, int32_t posY, int32_t sizeX, int32_t sizeY, const char* title);
    result show();
    result hide();

    void destory();

    result set_title(const char* title);
    result set_pos(int width, int height);
    result set_size(int width, int height);

    std::string get_internal_errinfo() const;

    // void set_resolution(int width, int height);

    result process_loop();

    void* get_plat_h() { return _ph; }

    int32_t posX() const { return pos.x; }
    int32_t posY() const { return pos.y; }

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
    friend YKM_VIEWBOX_IMPL;
    viewbox_evt evts;
    viewbox_xy size;
    viewbox_xy pos;
    std::string str_title;
    void* _ph;
};

} // namespace ykm
