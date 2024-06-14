#include <exception>
#include <iostream>

#include <fmt/format.h>

#include <ykm/viewbox.hpp>

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

        const YkmApp_Info* appInfo;
        YkmApp_GetInfo(&appInfo);

        while (appInfo->alive)
        {
            check > vb.LoopBegin();

            YkmApp_LoopHandleEvts();

            check > vb.LoopHandleEvts();

            if (vb.event().on_close()) { YkmApp_Quit(); }
            for (auto evt : vb.event().mouse.buf_entered())
            {
                if (evt == ykm::input::mouse_evt::move)
                {
                    //
                    fmt::println("{} move {} {}", frame, vb.event().mouse.x(), vb.event().mouse.y());
                }
                else if (evt == ykm::input::mouse_evt::scroll)
                {
                    //
                    fmt::println("{} scroll {} {}", frame, vb.event().mouse.scroll_x(), vb.event().mouse.scroll_y());
                }
                else
                {
                    //
                    fmt::println("{} mouse btn {}", frame, ykm::input::mouseEvtMap[evt]);
                }
            }
            frame++;
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
