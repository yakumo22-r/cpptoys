#ifndef YKM_DYLIB_VK_H
#define YKM_DYLIB_VK_H

/*
   some code copy at https://blog.csdn.net/smcnjyddx0623/article/details/134908747
*/

#if defined(WIN32) || defined(_WIN32) || defined(_WIN32_) || defined(WIN64) || defined(_WIN64) || defined(_WIN64_)
#define VULKAN_LIB "vulkan-1.dll"
#define VK_USE_PLATFORM_WIN32_KHR
#elif defined(ANDROID) || defined(_ANDROID_)
#define VULKAN_LIB "libvulkan.so"
#else
#define VULKAN_LIB "libvulkan.so.1"
#endif

#ifdef __APPLE__

#ifdef VK_NO_PROTOTYPES
#undef VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>
#else
#include <vulkan/vulkan.h>
#endif

#define YKM_DYLIB_VK_DEF_LOADER
inline void init_vk_loader() {}

#else

#ifndef VK_NO_PROTOTYPES
#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>
#undef VK_NO_PROTOTYPES
#else
#include <vulkan/vulkan.h>
#endif

#include <dylib.hpp>

#define YKM_VK_FUNC_DEF(name) PFN_##name ##name;
#define YKM_VK_FUNC_EXTREN(name) extern YKM_VK_FUNC_DEF(name);
#define YKM_VK_FUNC_SET(name) ::ykm_vk_pfn::##name = reinterpret_cast<PFN_##name>(lib.get_function<PFN_##name>(#name));

#if defined(WIN32) || defined(_WIN32) || defined(_WIN32_) || defined(WIN64) || defined(_WIN64) || defined(_WIN64_)

#define YKM_VK_FUNC_LIST_PLAT_EXT(YKM_MACRO) \
    YKM_MACRO(vkCreateWin32SurfaceKHR)     \
    YKM_MACRO(vkGetPhysicalDeviceWin32PresentationSupportKHR)

namespace ykm_vk_pfn
{
    YKM_VK_FUNC_LIST_PLAT_EXT(YKM_VK_FUNC_EXTREN)
}

inline VkResult vkCreateWin32SurfaceKHR(VkInstance instance, const VkWin32SurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
    return ::ykm_vk_pfn::vkCreateWin32SurfaceKHR(instance,pCreateInfo,pAllocator,pSurface);
}

inline VkBool32 vkGetPhysicalDeviceWin32PresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex)
{
    return ::ykm_vk_pfn::vkGetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice, queueFamilyIndex);
}

#elif defined(ANDROID) || defined(_ANDROID_)
    
#else

#endif


#define APPLY_PFN_DEF_VK_FUNCTIONS(PFN_DEF)                 \
    PFN_DEF(vkGetInstanceProcAddr)                          \
    PFN_DEF(vkCreateInstance)                               \
    PFN_DEF(vkEnumerateInstanceExtensionProperties)         \
    PFN_DEF(vkEnumerateInstanceLayerProperties)             \
    PFN_DEF(vkDestroyInstance)                              \
    PFN_DEF(vkEnumeratePhysicalDevices)                     \
    PFN_DEF(vkGetPhysicalDeviceFeatures)                    \
    PFN_DEF(vkGetPhysicalDeviceFormatProperties)            \
    PFN_DEF(vkGetPhysicalDeviceImageFormatProperties)       \
    PFN_DEF(vkGetPhysicalDeviceProperties)                  \
    PFN_DEF(vkGetPhysicalDeviceQueueFamilyProperties)       \
    PFN_DEF(vkGetPhysicalDeviceMemoryProperties)            \
    PFN_DEF(vkGetDeviceProcAddr)                            \
    PFN_DEF(vkCreateDevice)                                 \
    PFN_DEF(vkDestroySurfaceKHR)                            \
    PFN_DEF(vkGetPhysicalDeviceSurfaceSupportKHR)           \
    PFN_DEF(vkGetPhysicalDeviceSurfaceCapabilitiesKHR)      \
    PFN_DEF(vkGetPhysicalDeviceSurfaceFormatsKHR)           \
    PFN_DEF(vkGetPhysicalDeviceSurfacePresentModesKHR)      \
    PFN_DEF(vkCreateSwapchainKHR)                           \
    PFN_DEF(vkDestroySwapchainKHR)                          \
    PFN_DEF(vkGetSwapchainImagesKHR)                        \
    PFN_DEF(vkAcquireNextImageKHR)                          \
    PFN_DEF(vkQueuePresentKHR)                              \
    PFN_DEF(vkDestroyDevice)                                \
    PFN_DEF(vkEnumerateDeviceExtensionProperties)           \
    PFN_DEF(vkEnumerateDeviceLayerProperties)               \
    PFN_DEF(vkGetDeviceQueue)                               \
    PFN_DEF(vkQueueSubmit)                                  \
    PFN_DEF(vkQueueWaitIdle)                                \
    PFN_DEF(vkDeviceWaitIdle)                               \
    PFN_DEF(vkAllocateMemory)                               \
    PFN_DEF(vkFreeMemory)                                   \
    PFN_DEF(vkMapMemory)                                    \
    PFN_DEF(vkUnmapMemory)                                  \
    PFN_DEF(vkFlushMappedMemoryRanges)                      \
    PFN_DEF(vkInvalidateMappedMemoryRanges)                 \
    PFN_DEF(vkGetDeviceMemoryCommitment)                    \
    PFN_DEF(vkBindBufferMemory)                             \
    PFN_DEF(vkBindImageMemory)                              \
    PFN_DEF(vkGetBufferMemoryRequirements)                  \
    PFN_DEF(vkGetImageMemoryRequirements)                   \
    PFN_DEF(vkGetImageSparseMemoryRequirements)             \
    PFN_DEF(vkGetPhysicalDeviceSparseImageFormatProperties) \
    PFN_DEF(vkQueueBindSparse)                              \
    PFN_DEF(vkCreateFence)                                  \
    PFN_DEF(vkDestroyFence)                                 \
    PFN_DEF(vkResetFences)                                  \
    PFN_DEF(vkGetFenceStatus)                               \
    PFN_DEF(vkWaitForFences)                                \
    PFN_DEF(vkCreateSemaphore)                              \
    PFN_DEF(vkDestroySemaphore)                             \
    PFN_DEF(vkCreateEvent)                                  \
    PFN_DEF(vkDestroyEvent)                                 \
    PFN_DEF(vkGetEventStatus)                               \
    PFN_DEF(vkSetEvent)                                     \
    PFN_DEF(vkResetEvent)                                   \
    PFN_DEF(vkCreateQueryPool)                              \
    PFN_DEF(vkDestroyQueryPool)                             \
    PFN_DEF(vkGetQueryPoolResults)                          \
    PFN_DEF(vkCreateBuffer)                                 \
    PFN_DEF(vkDestroyBuffer)                                \
    PFN_DEF(vkCreateBufferView)                             \
    PFN_DEF(vkDestroyBufferView)                            \
    PFN_DEF(vkCreateImage)                                  \
    PFN_DEF(vkDestroyImage)                                 \
    PFN_DEF(vkGetImageSubresourceLayout)                    \
    PFN_DEF(vkCreateImageView)                              \
    PFN_DEF(vkDestroyImageView)                             \
    PFN_DEF(vkCreateShaderModule)                           \
    PFN_DEF(vkDestroyShaderModule)                          \
    PFN_DEF(vkCreatePipelineCache)                          \
    PFN_DEF(vkDestroyPipelineCache)                         \
    PFN_DEF(vkGetPipelineCacheData)                         \
    PFN_DEF(vkMergePipelineCaches)                          \
    PFN_DEF(vkCreateGraphicsPipelines)                      \
    PFN_DEF(vkCreateComputePipelines)                       \
    PFN_DEF(vkDestroyPipeline)                              \
    PFN_DEF(vkCreatePipelineLayout)                         \
    PFN_DEF(vkDestroyPipelineLayout)                        \
    PFN_DEF(vkCreateSampler)                                \
    PFN_DEF(vkDestroySampler)                               \
    PFN_DEF(vkCreateDescriptorSetLayout)                    \
    PFN_DEF(vkDestroyDescriptorSetLayout)                   \
    PFN_DEF(vkCreateDescriptorPool)                         \
    PFN_DEF(vkDestroyDescriptorPool)                        \
    PFN_DEF(vkResetDescriptorPool)                          \
    PFN_DEF(vkAllocateDescriptorSets)                       \
    PFN_DEF(vkFreeDescriptorSets)                           \
    PFN_DEF(vkUpdateDescriptorSets)                         \
    PFN_DEF(vkCreateFramebuffer)                            \
    PFN_DEF(vkDestroyFramebuffer)                           \
    PFN_DEF(vkCreateRenderPass)                             \
    PFN_DEF(vkDestroyRenderPass)                            \
    PFN_DEF(vkGetRenderAreaGranularity)                     \
    PFN_DEF(vkCreateCommandPool)                            \
    PFN_DEF(vkDestroyCommandPool)                           \
    PFN_DEF(vkResetCommandPool)                             \
    PFN_DEF(vkAllocateCommandBuffers)                       \
    PFN_DEF(vkFreeCommandBuffers)                           \
    PFN_DEF(vkBeginCommandBuffer)                           \
    PFN_DEF(vkEndCommandBuffer)                             \
    PFN_DEF(vkResetCommandBuffer)                           \
    PFN_DEF(vkCmdBindPipeline)                              \
    PFN_DEF(vkCmdSetViewport)                               \
    PFN_DEF(vkCmdSetScissor)                                \
    PFN_DEF(vkCmdSetLineWidth)                              \
    PFN_DEF(vkCmdSetDepthBias)                              \
    PFN_DEF(vkCmdSetBlendConstants)                         \
    PFN_DEF(vkCmdSetDepthBounds)                            \
    PFN_DEF(vkCmdSetStencilCompareMask)                     \
    PFN_DEF(vkCmdSetStencilWriteMask)                       \
    PFN_DEF(vkCmdSetStencilReference)                       \
    PFN_DEF(vkCmdBindDescriptorSets)                        \
    PFN_DEF(vkCmdBindIndexBuffer)                           \
    PFN_DEF(vkCmdBindVertexBuffers)                         \
    PFN_DEF(vkCmdDraw)                                      \
    PFN_DEF(vkCmdDrawIndexed)                               \
    PFN_DEF(vkCmdDrawIndirect)                              \
    PFN_DEF(vkCmdDrawIndexedIndirect)                       \
    PFN_DEF(vkCmdDispatch)                                  \
    PFN_DEF(vkCmdDispatchIndirect)                          \
    PFN_DEF(vkCmdCopyBuffer)                                \
    PFN_DEF(vkCmdCopyImage)                                 \
    PFN_DEF(vkCmdBlitImage)                                 \
    PFN_DEF(vkCmdCopyBufferToImage)                         \
    PFN_DEF(vkCmdCopyImageToBuffer)                         \
    PFN_DEF(vkCmdUpdateBuffer)                              \
    PFN_DEF(vkCmdFillBuffer)                                \
    PFN_DEF(vkCmdClearColorImage)                           \
    PFN_DEF(vkCmdClearDepthStencilImage)                    \
    PFN_DEF(vkCmdClearAttachments)                          \
    PFN_DEF(vkCmdResolveImage)                              \
    PFN_DEF(vkCmdSetEvent)                                  \
    PFN_DEF(vkCmdResetEvent)                                \
    PFN_DEF(vkCmdWaitEvents)                                \
    PFN_DEF(vkCmdPipelineBarrier)                           \
    PFN_DEF(vkCmdBeginQuery)                                \
    PFN_DEF(vkCmdEndQuery)                                  \
    PFN_DEF(vkCmdResetQueryPool)                            \
    PFN_DEF(vkCmdWriteTimestamp)                            \
    PFN_DEF(vkCmdCopyQueryPoolResults)                      \
    PFN_DEF(vkCmdPushConstants)                             \
    PFN_DEF(vkCmdBeginRenderPass)                           \
    PFN_DEF(vkCmdNextSubpass)                               \
    PFN_DEF(vkCmdEndRenderPass)                             \
    PFN_DEF(vkCmdExecuteCommands)                           \
    PFN_DEF(vkEnumerateInstanceVersion)                     \

APPLY_PFN_DEF_VK_FUNCTIONS(EXTERN_VK_FUNCTION_MACRO);
void init_vk_loader();

#define YKM_DYLIB_VK_DEF_LOADER                               \
    APPLY_PFN_DEF_VK_FUNCTIONS(DEFINE_VK_FUNCTION_MACRO)      \
    void init_vk_loader()                                     \
    {                                                         \
        static dylib lib(VULKAN_LIB, false);                  \
        APPLY_PFN_DEF_VK_FUNCTIONS(GET_VK_FUNCTION_PROCADDR); \
    }

#endif

#include <vector>

inline void ykm_vk_extension_spec_wrap(std::vector<const char*>& exs, VkInstanceCreateInfo& info, uint32_t sdkVersion)
{
#ifdef __APPLE__
    /*
       If using MacOS with the latest MoltenVK sdk, you may get VK_ERROR_INCOMPATIBLE_DRIVER returned from vkCreateInstance. According to the Getting Start
        Notes. Beginning with the 1.3.216 Vulkan SDK, the VK_KHR_PORTABILITY_subset extension is mandatory.*/
    if (sdkVersion >= VK_MAKE_VERSION(1, 3, 216))
    {
        exs.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
        info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    }
#endif
}

// TAG: vk pfn api wrap
// TODO: all api wrap
inline VkResult vkCreateInstance(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance)
{
    return pfn_vkCreateInstance(pCreateInfo, pAllocator, pInstance);
}
inline void vkDestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator){
    pfn_vkDestroyInstance(instance, pAllocator);
}

inline VkResult vkEnumerateInstanceVersion(uint32_t* pApiVersion) { return pfn_vkEnumerateInstanceVersion(pApiVersion); }

#endif
