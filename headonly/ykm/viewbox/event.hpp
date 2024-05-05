/*
   viewbox event defs

    version: dev 0.0.1
    date : 2024/5/6
*/
#ifndef YKM_VIEWBOX_EVENT_HPP
#define YKM_VIEWBOX_EVENT_HPP
#include "../input/def.hpp"
#include <cstdint>
#include <string>
namespace ykm
{
struct viewbox_xy
{
    int32_t x, y;
};
struct viewbox_evt
{
    enum evt : uint32_t
    {
        close /*********/ = 0x00000001,
        sleep /*********/ = close << 1,
        awake /*********/ = close << 2,
        move /**********/ = close << 3,
        resize /********/ = close << 4,
        title /*********/ = close << 5,
        text /**********/ = close << 6,
        pointer /*******/ = close << 8,
        active /********/ = close << 9,
        unactive /******/ = close << 10,
    };

    input::keyboard keyboard;
    input::mouse mouse;

    bool on_close() const /*********/ { return evts & close; }
    bool on_sleep() const /*********/ { return evts & sleep; }
    bool on_awake() const /*********/ { return evts & awake; }
    bool on_move() const /**********/ { return evts & move; }
    bool on_resize() const /********/ { return evts & resize; }
    bool on_title() const /*********/ { return evts & title; }
    bool on_text() const /**********/ { return evts & text; }
    bool on_pointer() const /*******/ { return evts & pointer; }
    bool on_active() const /********/ { return evts & active; }
    bool on_unactive() const /******/ { return evts & unactive; }

    void push_evts(evt e) { evts |= e; }
    void clear_evts() { evts = 0x00000000; }

  private:
    uint32_t evts;
};

} // namespace ykm

#endif
