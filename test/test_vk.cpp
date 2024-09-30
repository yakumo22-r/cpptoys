#include <iostream>
#include <vector>

// #include <GLFW/glfw3.h>

#include "ykm_dylib_vk.hpp"

YKM_DYLIB_VK_DEF_LOADER;

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
    init_vk_loader();

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "hello triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "no engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t sdkVersion;
    vkEnumerateInstanceVersion(&sdkVersion);

    std::string vk_sdk_ver;
    vk_sdk_ver //
        .append(std::to_string(VK_VERSION_MAJOR(sdkVersion)))
        .append(".")
        .append(std::to_string(VK_VERSION_MINOR(sdkVersion)))
        .append(".")
        .append(std::to_string(VK_VERSION_PATCH(sdkVersion)));

    std::cout << "Vulkan SDK Version: " << vk_sdk_ver << std::endl;

    // auto reqExs = get_require_extensions();

    // ykm_vk_extension_spec_wrap(reqExs, createInfo, sdkVersion);

    // createInfo.enabledExtensionCount = (uint32_t)reqExs.size();
    // createInfo.ppEnabledExtensionNames = reqExs.data();

    VkInstance instance;
    if (auto code = vkCreateInstance(&createInfo, nullptr, &instance); code != VK_SUCCESS)
    {
        std::cout << "create instance failed:" << code << std::endl; //
        return -1;
    }

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
    vkDestroyInstance(instance, nullptr);

    return 0;
};
