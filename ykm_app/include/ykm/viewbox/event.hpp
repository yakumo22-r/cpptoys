/*
   ViewBox event defs

    version: dev 0.0.1
    date : 2024/5/6
*/
#ifndef YKM_APP_VIEWBOX_EVENT_HPP
#define YKM_APP_VIEWBOX_EVENT_HPP
#include <cstdint>

#include "../sys/input_def.hpp"

namespace ykm
{

struct ViewBoxEvt
{
    enum evt : uint32_t
    {
        close,
        sleep,
        awake,
        move,
        resize,
        title,
        text,
        pointer,
        active,
        unactive,
        evt_num,
    };

    input::keyboard keyboard;
    input::mouse mouse;
    ykm::enum_set<evt, evt_num> state;

    bool on_close() const /*********/ { return evts[close]; }
    bool on_sleep() const /*********/ { return evts[sleep]; }
    bool on_awake() const /*********/ { return evts[awake]; }
    bool on_move() const /**********/ { return evts[move]; }
    bool on_resize() const /********/ { return evts[resize]; }
    bool on_title() const /*********/ { return evts[title]; }
    bool on_text() const /**********/ { return evts[text]; }
    bool on_pointer() const /*******/ { return evts[pointer]; }
    bool on_active() const /********/ { return evts[active]; }
    bool on_unactive() const /******/ { return evts[unactive]; }

    void push_evts(evt e) { evts.set(e); }
    void push_evts(uint32_t e) { evts.set(e); }
    void clear_evts() { evts.reset(); }

  private:
    ykm::enum_set<evt, evt_num> evts;
};

} // namespace ykm

#endif
