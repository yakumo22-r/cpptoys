/*
    viewbox base interface define
    some functions are implemented by different files on different platforms

    version: dev 0.0.2
    date : 2024/5/6

todo: text input and candicate
*/
#include "event.hpp"
#include <__iterator/reverse_iterator.h>
#include <cstdint>

#define YKM_VIEWBOX_I(r) r
#define YKM_VIEWBOX_RESULT ::ykm::viewbox::result
#define YKM_VIEWBOX_VOID void

namespace ykm
{

struct viewbox final
{
    inline static constexpr int16_t r_ok = 0;
    inline static constexpr int16_t r_uninitialized = -1;
    inline static constexpr int16_t r_internal = -1;

    using result = int16_t;

    struct implbase;
    friend implbase;

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
    implbase* get_plat_h() { return _ph; }
    viewbox_xy position() const { return pos; }
    int32_t width() const { return size.x; }
    int32_t height() const { return size.y; }

    const std::string& title() const { return text_title; };
    const viewbox_evt& event() const { return evts; }

    ~viewbox()
    {
        if (_ph)
            destory();
    }

  private:
    viewbox_evt evts;
    viewbox_xy size;
    viewbox_xy pos;
    std::string text_title;
    implbase* _ph;

  public:
    struct implbase
    {
        viewbox_evt& evts() { return vb->evts; }
        viewbox_xy& size() { return vb->size; }
        viewbox_xy& pos() { return vb->pos; }
        std::string& title() { return vb->text_title; }
        viewbox* vb;
    };

    struct checker final
    {
        void operator|(result code) const
        {
            switch (code)
            {
            case viewbox::r_ok:
                return;
            case viewbox::r_uninitialized:
                vb->on_fatal_error(code, "call error", "viewbox impl not implementation");
            default:
                vb->on_fatal_error(code, "internal error", vb->get_internal_errinfo().c_str());
            }
        }

        checker(const checker& r) : vb(r.vb){};

        checker operator=(const checker& r)
        {
            vb = r.vb;
            return *this;
        };

      private:
        friend viewbox;
        checker(const viewbox* vb) : vb(vb) {}
        const viewbox* vb;
    };

    checker get_checker() const { return checker(this); }
};

} // namespace ykm
