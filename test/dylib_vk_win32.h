#pragma once
#ifndef YKM22_DYLIB_VK_WIN32_H
#define YKM22_DYLIB_VK_WIN32_H

#include "dylib_vk_base.h"

// clang-format off

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateWin32SurfaceKHR,(
    VkInstance                                  instance,
    const VkWin32SurfaceCreateInfoKHR*          pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface),
(instance, pCreateInfo, pAllocator, pSurface));

YKM22_VULKAN_SYMBOL(
VkBool32,vkGetPhysicalDeviceWin32PresentationSupportKHR,(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex),
(physicalDevice, queueFamilyIndex));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetMemoryWin32HandleKHR,(
    VkDevice                                    device,
    const VkMemoryGetWin32HandleInfoKHR*        pGetWin32HandleInfo,
    HANDLE*                                     pHandle),
(device, pGetWin32HandleInfo, pHandle));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetMemoryWin32HandlePropertiesKHR,(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    HANDLE                                      handle,
    VkMemoryWin32HandlePropertiesKHR*           pMemoryWin32HandleProperties),
(device, handleType, handle, pMemoryWin32HandleProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkImportSemaphoreWin32HandleKHR,(
    VkDevice                                    device,
    const VkImportSemaphoreWin32HandleInfoKHR*  pImportSemaphoreWin32HandleInfo),
(device, pImportSemaphoreWin32HandleInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetSemaphoreWin32HandleKHR,(
    VkDevice                                    device,
    const VkSemaphoreGetWin32HandleInfoKHR*     pGetWin32HandleInfo,
    HANDLE*                                     pHandle),
(device, pGetWin32HandleInfo, pHandle));

YKM22_VULKAN_SYMBOL(
VkResult,vkImportFenceWin32HandleKHR,(
    VkDevice                                    device,
    const VkImportFenceWin32HandleInfoKHR*      pImportFenceWin32HandleInfo),
(device, pImportFenceWin32HandleInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetFenceWin32HandleKHR,(
    VkDevice                                    device,
    const VkFenceGetWin32HandleInfoKHR*         pGetWin32HandleInfo,
    HANDLE*                                     pHandle),
(device, pGetWin32HandleInfo, pHandle));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetMemoryWin32HandleNV,(
    VkDevice                                    device,
    VkDeviceMemory                              memory,
    VkExternalMemoryHandleTypeFlagsNV           handleType,
    HANDLE*                                     pHandle),
(device, memory, handleType, pHandle));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceSurfacePresentModes2EXT,(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    uint32_t*                                   pPresentModeCount,
    VkPresentModeKHR*                           pPresentModes),
(physicalDevice, pSurfaceInfo, pPresentModeCount, pPresentModes));

YKM22_VULKAN_SYMBOL(
VkResult,vkAcquireFullScreenExclusiveModeEXT,(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain),
(device, swapchain));

YKM22_VULKAN_SYMBOL(
VkResult,vkReleaseFullScreenExclusiveModeEXT,(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain),
(device, swapchain));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetDeviceGroupSurfacePresentModes2EXT,(
    VkDevice                                    device,
    const VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    VkDeviceGroupPresentModeFlagsKHR*           pModes),
(device, pSurfaceInfo, pModes));

YKM22_VULKAN_SYMBOL(
VkResult,vkAcquireWinrtDisplayNV,(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display),
(physicalDevice, display));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetWinrtDisplayNV,(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    deviceRelativeId,
    VkDisplayKHR*                               pDisplay),
(physicalDevice, deviceRelativeId, pDisplay));

#endif // YKM22_DYLIB_VK_API_H
