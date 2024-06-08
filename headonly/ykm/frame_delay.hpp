#ifndef YKM_FRAME_DELAY_HPP
#define YKM_FRAME_DELAY_HPP

#include <chrono>
#include <thread>

namespace ykm
{

class frame_delay final
{
  public:
    using clock = std::chrono::system_clock;
    using ms = std::chrono::milliseconds;
    using time_point = std::chrono::time_point<clock>;
    frame_delay();
    void frame_begin();
    void frame_end();
    void set_fps(int fps);
    long long time_ms();

  private:
    int fps;
    const time_point begin;
    time_point time;
    ms frame_space;
};

inline frame_delay::frame_delay()
    : //
      fps(60),
      begin(clock::now()),
      time(clock::now()),
      frame_space(ms(1000 / fps)){};

inline void frame_delay::frame_begin() { time = clock::now(); }

inline void frame_delay::frame_end()
{
    auto delta = std::chrono::duration_cast<ms> //
                 (time + frame_space - clock::now()).count();

    if (delta > 0) std::this_thread::sleep_for(ms(delta));
}

inline void frame_delay::set_fps(int fps)
{
    this->fps = fps;
    frame_space = ms(1000 / fps);
}

inline long long frame_delay::time_ms() { return std::chrono::duration_cast<ms>(time - begin).count(); }

} // namespace ykm

#endif
