#pragma once
#ifndef YKM22_DYLIB_VK_BASE_H
#define YKM22_DYLIB_VK_BASE_H

#ifndef VK_NO_PROTOTYPES
#define VK_NO_PROTOTYPES
#endif

#include <dylib.hpp>

#define YKM22_VKLIB_DEFINE                   \
    const dylib& dylib_vk()                    \
    {                                        \
        static dylib lib(VULKAN_LIB, false); \
        return lib;                          \
    }

const dylib& dylib_vk();

#define YKM22_VULKAN_SYMBOL(r, name, p, i)                   \
inline r name p                                          \
{                                                        \
    typedef r(*t) p;                                     \
    static t f = (t)::dylib_vk().get_symbol(#name); \
    return f i;                                          \
}


#if defined(WIN32) || defined(_WIN32) || defined(_WIN32_) || defined(WIN64) || defined(_WIN64) || defined(_WIN64_)
#define VULKAN_LIB "vulkan-1.dll"
#define VK_USE_PLATFORM_WIN32_KHR
#elif defined(ANDROID) || defined(_ANDROID_)
#define VULKAN_LIB "libvulkan.so"
#else
#define VULKAN_LIB "libvulkan.so.1"
#endif

#include <vulkan/vulkan.h>


#endif // YKM22_DYLIB_VK_BASE_H
