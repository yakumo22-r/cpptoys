#include <exception>
#include <iostream>

#include <fmt/format.h>

#include <ykm/viewbox.hpp>
#include <ykm/frame_delay.hpp>

int main()
{
    ykm::AppResultChecker check;
    check.error_handler = [](YkmApp_Result code, const char* error) { fmt::println("error {} -> {}", code, error); };

    try
    {
        ykm::ViewBox vb;
        vb.Create(0, 0, 400, 400, "hello");
        vb.SetContentSize(800, 600);
        vb.Show();

        fmt::println("start");
        int code = 0;
        uint32_t frame = 0;
        while (!code)
        {
            // fmt::println("\nframe {}", frame++);

            check > vb.LoopBegin();

            YkmApp_HandleEvents();

            check > vb.LoopHandleEvts();

            for (auto evt : vb.event().mouse.buf_enterd())
            {
                if (evt == ykm::input::mouse_evt::move) //
                {
                    fmt::println("move {} {}", vb.event().mouse.x(), vb.event().mouse.y());
                }
                else if (evt == ykm::input::mouse_evt::scroll) //
                {
                    fmt::println("scroll {} {}", vb.event().mouse.scroll_x(), vb.event().mouse.scroll_y());
                }
                else //
                {
                    fmt::println("mouse btn {}", ykm::input::mouseEvtMap[evt]);
                }
            }
            YkmApp_LoopSleep();
        }

        vb.Destory();
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
