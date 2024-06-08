#include <exception>
#include <iostream>

#include <chrono>
#include <thread>

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

        int code = 0;
        ykm::frame_delay FD;
        while (!code)
        {
            FD.frame_begin();
            auto frame_time = std::chrono::system_clock::now();
            for (auto mc : vb.event().mouse.buf_press())
            {
                if (mc == ykm::input::mousecode::move)
                {
                    fmt::println("move {} {}", vb.event().mouse.x(), vb.event().mouse.y()); //
                }
                else{
                    fmt::println("mouse btn {}",ykm::input::mousecode_map[mc]);
                }
            }
            code = vb.process_loop();

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
