#include <iostream>
#include <vector>
#include <string>

// #include <GLFW/glfw3.h>

#include "dylib_vk_base.h"
#include "vk/triangle.h"

YKM22_VKLIB_DEFINE;

// std::vector<const char*> get_require_extensions()
// {
//     uint32_t glfwExCount = 0;
//     const char** glfwExs;
//     glfwExs = glfwGetRequiredInstanceExtensions(&glfwExCount);

//     std::vector<const char*> exs(glfwExs, glfwExs + glfwExCount);
//     exs.push_back("VK_KHR_get_physical_device_properties2");
//     return exs;
// }

int main()
{
    Triangle ctx;

    vktest::createInstance(ctx);


    // init_vk_loader();
    // if (!glfwInit()) { return -1; }

    // GLFWwindow* wnd = glfwCreateWindow(600, 400, "hello", NULL, NULL);
    // if (!wnd)
    // {
    //     glfwTerminate();
    //     return -1;
    // }

    // glfwMakeContextCurrent(wnd);
    // while (!glfwWindowShouldClose(wnd))
    // {
    //     glfwPollEvents(); //
    // }
    // glfwTerminate();
    vktest::destory(ctx);

    return 0;
};
