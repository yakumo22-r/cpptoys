#include <exception>
#include <iostream>

#include <ykm_app_viewbox.h>

int main()
{
    try
    {
        ykm::viewbox vb;
        vb.create(0, 0, 400, 400, "hello");
        vb.set_content_size(800, 600);
        vb.show();

        int code = 0;
        while (!code)
        {
            //for (auto kc : vb.event().keyboard.buf_press())
            //{
            //    std::cout << std::format("press {} {}", ykm::input::keycode_map[kc], size_t(kc)) << std::endl;
            //}
            code = vb.process_loop();
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
