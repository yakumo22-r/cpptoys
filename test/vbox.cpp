#include <exception>
#include <iostream>

#include <fmt/format.h>

#include <ykm_app_viewbox.h>
#include <ykm/frame_delay.hpp>

int main()
{
    try
    {
        ykm::viewbox vb;
        vb.create(0, 0, 400, 400, "hello");
        vb.set_content_size(800, 600);
        vb.show();

        fmt::println("start");
        int code = 0;
        ykm::frame_delay FD;
        FD.set_fps(2);
        uint32_t frame = 0;
        while (!code)
        {
            fmt::println("\nframe {}", frame++);
            FD.frame_begin();

            code = vb.process_loop();

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
                    fmt::println("mouse btn {}", ykm::input::mouse_evt_map[evt]);
                }
            }

            FD.frame_end();
        }

        std::cout << code << vb.get_internal_errinfo() << std::endl;
        vb.destory();
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
