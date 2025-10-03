#pragma once
#include <cassert>
#include <iostream>
#include <vector>
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "VulkanCommon.h"

struct Triangle{
public:
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice device;

    VkDebugReportCallbackEXT debugReport;

    VkSurfaceKHR surface;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkPipeline graphicsPipeline;
    VkPipelineLayout pipelineLayout;
    VkRenderPass renderPass;
    VkFramebuffer framebuffer;
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;
};

const DriverFeature validation_layers[] = {
    {"VK_LAYER_KHRONOS_validation", false, true},
};

const DriverFeature validation_extensions[] = {
    {"VK_KHR_surface", false, true},
    {"VK_KHR_win32_surface", false, true},
    {"VK_EXT_debug_report", false, true},
};

namespace vktest {

inline VkBool32 debugReportCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData) {
    switch (flags) {
        case VK_DEBUG_REPORT_ERROR_BIT_EXT:
            Error("{} VK_DEBUG_REPORT_ERROR_BIT_EXT({}) Msg: {}", pLayerPrefix, messageCode, pMessage);
            break;
        case VK_DEBUG_REPORT_WARNING_BIT_EXT:
            Warn("{} VK_DEBUG_REPORT_WARNING_BIT_EXT({}) Msg: {}", pLayerPrefix, messageCode, pMessage);
            break;
        default:
            Warn("{} Code({}) Msg: {}", pLayerPrefix, messageCode, pMessage);
            break;

    
    }

    return VK_FALSE;
}

inline void createInstance(Triangle& ctx){

    uint32_t avaliableLayerCount = 0;
    CALL_VK(vkEnumerateInstanceLayerProperties(&avaliableLayerCount, nullptr));
    std::vector<VkLayerProperties> avaliableLayerProps;
    avaliableLayerProps.resize(avaliableLayerCount);
    CALL_VK(vkEnumerateInstanceLayerProperties(&avaliableLayerCount, avaliableLayerProps.data()));
    Print("-----------------------------");
    const char* enabledLayerNames[32] = {};
    uint32_t enabledLayerCount = 0;
    checkFeatures("Instance Layers", true, false, validation_layers, ARRAY_SIZE(validation_layers), avaliableLayerProps.data(), avaliableLayerCount, enabledLayerNames, &enabledLayerCount);

    uint32_t avaliableExtensionCount = 0;
    CALL_VK(vkEnumerateInstanceExtensionProperties(nullptr, &avaliableExtensionCount, nullptr));
    std::vector<VkExtensionProperties> avaliableExtensionProps;
    avaliableExtensionProps.resize(avaliableExtensionCount);
    CALL_VK(vkEnumerateInstanceExtensionProperties(nullptr, &avaliableExtensionCount, avaliableExtensionProps.data()));
    Print("-----------------------------");
    const char* enabledExtensionNames[32] = {};
    uint32_t enabledExtensionCount = 0;
    checkFeatures("Instance Extensions", true, true, validation_extensions, ARRAY_SIZE(validation_extensions), avaliableExtensionProps.data(), avaliableExtensionCount, enabledExtensionNames, &enabledExtensionCount);
    Print("-----------------------------");

    VkDebugReportCallbackCreateInfoEXT debugCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT,
        .pNext = nullptr,
        .flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT,
        .pfnCallback = debugReportCallback,
        .pUserData = nullptr,
    };


    VkApplicationInfo appInfo={
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pNext = nullptr,
        .pApplicationName = "hello triangle",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "no engine",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_0,
    };

    VkInstanceCreateInfo createInfo={
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pNext = &debugCreateInfo,
        .flags = 0,
        .pApplicationInfo = &appInfo,
        .enabledLayerCount = enabledLayerCount,
        .ppEnabledLayerNames = enabledLayerCount == 0 ? nullptr : enabledLayerNames,
        .enabledExtensionCount = enabledExtensionCount,
        .ppEnabledExtensionNames = enabledExtensionCount == 0 ? nullptr : enabledExtensionNames,
    };

    uint32_t sdkVersion;
    vkEnumerateInstanceVersion(&sdkVersion);

    std::string vk_sdk_ver;
    vk_sdk_ver //
        .append(std::to_string(VK_VERSION_MAJOR(sdkVersion)))
        .append(".")
        .append(std::to_string(VK_VERSION_MINOR(sdkVersion)))
        .append(".")
        .append(std::to_string(VK_VERSION_PATCH(sdkVersion)));

    Print("Vulkan SDK Version: {}{}",YELLOW, vk_sdk_ver.c_str());

    // auto reqExs = get_require_extensions();

    // ykm_vk_extension_spec_wrap(reqExs, createInfo, sdkVersion);

    // createInfo.enabledExtensionCount = (uint32_t)reqExs.size();
    // createInfo.ppEnabledExtensionNames = reqExs.data();

    if (auto code = vkCreateInstance(&createInfo, nullptr, &ctx.instance); code != VK_SUCCESS)
    {
        std::cout << "create instance failed:" << code << std::endl; //
        // assert(false);
    }
}

inline void createSurface(Triangle& ctx, HWND hwnd) {
    VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
        .pNext = nullptr,
        .flags = 0,
        .hinstance = GetModuleHandle(nullptr),
        .hwnd = hwnd,
    };

    CALL_VK(vkCreateWin32SurfaceKHR(ctx.instance, &surfaceCreateInfo, nullptr, &ctx.surface));
}

inline void destory(Triangle& ctx) {
    vkDestroyInstance(ctx.instance, nullptr);
    Print("Destroyed Vulkan resources");
}

} // namespace vktest

#endif // TRIANGLE_H
