#pragma once
#ifndef YKM22_DYLIB_VK_H
#define YKM22_DYLIB_VK_H

#include "dylib_vk_base.h"

// clang-format off

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateInstance,(
    const VkInstanceCreateInfo*                 pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkInstance*                                 pInstance),
(pCreateInfo, pAllocator, pInstance));

YKM22_VULKAN_SYMBOL(
void,vkDestroyInstance,(
    VkInstance                                  instance,
    const VkAllocationCallbacks*                pAllocator),
(instance, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkEnumeratePhysicalDevices,(
    VkInstance                                  instance,
    uint32_t*                                   pPhysicalDeviceCount,
    VkPhysicalDevice*                           pPhysicalDevices),
(instance, pPhysicalDeviceCount, pPhysicalDevices));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceFeatures,(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceFeatures*                   pFeatures),
(physicalDevice, pFeatures));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceFormatProperties,(
    VkPhysicalDevice                            physicalDevice,
    VkFormat                                    format,
    VkFormatProperties*                         pFormatProperties),
(physicalDevice, format, pFormatProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceImageFormatProperties,(
    VkPhysicalDevice                            physicalDevice,
    VkFormat                                    format,
    VkImageType                                 type,
    VkImageTiling                               tiling,
    VkImageUsageFlags                           usage,
    VkImageCreateFlags                          flags,
    VkImageFormatProperties*                    pImageFormatProperties),
(physicalDevice, format, type, tiling, usage, flags, pImageFormatProperties));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceProperties,(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceProperties*                 pProperties),
(physicalDevice, pProperties));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceQueueFamilyProperties,(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pQueueFamilyPropertyCount,
    VkQueueFamilyProperties*                    pQueueFamilyProperties),
(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceMemoryProperties,(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceMemoryProperties*           pMemoryProperties),
(physicalDevice, pMemoryProperties));

YKM22_VULKAN_SYMBOL(
PFN_vkVoidFunction,vkGetInstanceProcAddr,(
    VkInstance                                  instance,
    const char*                                 pName),
(instance, pName));

YKM22_VULKAN_SYMBOL(
PFN_vkVoidFunction,vkGetDeviceProcAddr,(
    VkDevice                                    device,
    const char*                                 pName),
(device, pName));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateDevice,(
    VkPhysicalDevice                            physicalDevice,
    const VkDeviceCreateInfo*                   pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDevice*                                   pDevice),
(physicalDevice, pCreateInfo, pAllocator, pDevice));

YKM22_VULKAN_SYMBOL(
void,vkDestroyDevice,(
    VkDevice                                    device,
    const VkAllocationCallbacks*                pAllocator),
(device, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkEnumerateInstanceExtensionProperties,(
    const char*                                 pLayerName,
    uint32_t*                                   pPropertyCount,
    VkExtensionProperties*                      pProperties),
(pLayerName, pPropertyCount, pProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkEnumerateDeviceExtensionProperties,(
    VkPhysicalDevice                            physicalDevice,
    const char*                                 pLayerName,
    uint32_t*                                   pPropertyCount,
    VkExtensionProperties*                      pProperties),
(physicalDevice, pLayerName, pPropertyCount, pProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkEnumerateInstanceLayerProperties,(
    uint32_t*                                   pPropertyCount,
    VkLayerProperties*                          pProperties),
(pPropertyCount, pProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkEnumerateDeviceLayerProperties,(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pPropertyCount,
    VkLayerProperties*                          pProperties),
(physicalDevice, pPropertyCount, pProperties));

YKM22_VULKAN_SYMBOL(
void,vkGetDeviceQueue,(
    VkDevice                                    device,
    uint32_t                                    queueFamilyIndex,
    uint32_t                                    queueIndex,
    VkQueue*                                    pQueue),
(device, queueFamilyIndex, queueIndex, pQueue));

YKM22_VULKAN_SYMBOL(
VkResult,vkQueueSubmit,(
    VkQueue                                     queue,
    uint32_t                                    submitCount,
    const VkSubmitInfo*                         pSubmits,
    VkFence                                     fence),
(queue, submitCount, pSubmits, fence));

YKM22_VULKAN_SYMBOL(
VkResult,vkQueueWaitIdle,(
    VkQueue                                     queue),
(queue));

YKM22_VULKAN_SYMBOL(
VkResult,vkDeviceWaitIdle,(
    VkDevice                                    device),
(device));

YKM22_VULKAN_SYMBOL(
VkResult,vkAllocateMemory,(
    VkDevice                                    device,
    const VkMemoryAllocateInfo*                 pAllocateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDeviceMemory*                             pMemory),
(device, pAllocateInfo, pAllocator, pMemory));

YKM22_VULKAN_SYMBOL(
void,vkFreeMemory,(
    VkDevice                                    device,
    VkDeviceMemory                              memory,
    const VkAllocationCallbacks*                pAllocator),
(device, memory, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkMapMemory,(
    VkDevice                                    device,
    VkDeviceMemory                              memory,
    VkDeviceSize                                offset,
    VkDeviceSize                                size,
    VkMemoryMapFlags                            flags,
    void**                                      ppData),
(device, memory, offset, size, flags, ppData));

YKM22_VULKAN_SYMBOL(
void,vkUnmapMemory,(
    VkDevice                                    device,
    VkDeviceMemory                              memory),
(device, memory));

YKM22_VULKAN_SYMBOL(
VkResult,vkFlushMappedMemoryRanges,(
    VkDevice                                    device,
    uint32_t                                    memoryRangeCount,
    const VkMappedMemoryRange*                  pMemoryRanges),
(device, memoryRangeCount, pMemoryRanges));

YKM22_VULKAN_SYMBOL(
VkResult,vkInvalidateMappedMemoryRanges,(
    VkDevice                                    device,
    uint32_t                                    memoryRangeCount,
    const VkMappedMemoryRange*                  pMemoryRanges),
(device, memoryRangeCount, pMemoryRanges));

YKM22_VULKAN_SYMBOL(
void,vkGetDeviceMemoryCommitment,(
    VkDevice                                    device,
    VkDeviceMemory                              memory,
    VkDeviceSize*                               pCommittedMemoryInBytes),
(device, memory, pCommittedMemoryInBytes));

YKM22_VULKAN_SYMBOL(
VkResult,vkBindBufferMemory,(
    VkDevice                                    device,
    VkBuffer                                    buffer,
    VkDeviceMemory                              memory,
    VkDeviceSize                                memoryOffset),
(device, buffer, memory, memoryOffset));

YKM22_VULKAN_SYMBOL(
VkResult,vkBindImageMemory,(
    VkDevice                                    device,
    VkImage                                     image,
    VkDeviceMemory                              memory,
    VkDeviceSize                                memoryOffset),
(device, image, memory, memoryOffset));

YKM22_VULKAN_SYMBOL(
void,vkGetBufferMemoryRequirements,(
    VkDevice                                    device,
    VkBuffer                                    buffer,
    VkMemoryRequirements*                       pMemoryRequirements),
(device, buffer, pMemoryRequirements));

YKM22_VULKAN_SYMBOL(
void,vkGetImageMemoryRequirements,(
    VkDevice                                    device,
    VkImage                                     image,
    VkMemoryRequirements*                       pMemoryRequirements),
(device, image, pMemoryRequirements));

YKM22_VULKAN_SYMBOL(
void,vkGetImageSparseMemoryRequirements,(
    VkDevice                                    device,
    VkImage                                     image,
    uint32_t*                                   pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements*            pSparseMemoryRequirements),
(device, image, pSparseMemoryRequirementCount, pSparseMemoryRequirements));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceSparseImageFormatProperties,(
    VkPhysicalDevice                            physicalDevice,
    VkFormat                                    format,
    VkImageType                                 type,
    VkSampleCountFlagBits                       samples,
    VkImageUsageFlags                           usage,
    VkImageTiling                               tiling,
    uint32_t*                                   pPropertyCount,
    VkSparseImageFormatProperties*              pProperties),
(physicalDevice, format, type, samples, usage, tiling, pPropertyCount, pProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkQueueBindSparse,(
    VkQueue                                     queue,
    uint32_t                                    bindInfoCount,
    const VkBindSparseInfo*                     pBindInfo,
    VkFence                                     fence),
(queue, bindInfoCount, pBindInfo, fence));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateFence,(
    VkDevice                                    device,
    const VkFenceCreateInfo*                    pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkFence*                                    pFence),
(device, pCreateInfo, pAllocator, pFence));

YKM22_VULKAN_SYMBOL(
void,vkDestroyFence,(
    VkDevice                                    device,
    VkFence                                     fence,
    const VkAllocationCallbacks*                pAllocator),
(device, fence, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkResetFences,(
    VkDevice                                    device,
    uint32_t                                    fenceCount,
    const VkFence*                              pFences),
(device, fenceCount, pFences));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetFenceStatus,(
    VkDevice                                    device,
    VkFence                                     fence),
(device, fence));

YKM22_VULKAN_SYMBOL(
VkResult,vkWaitForFences,(
    VkDevice                                    device,
    uint32_t                                    fenceCount,
    const VkFence*                              pFences,
    VkBool32                                    waitAll,
    uint64_t                                    timeout),
(device, fenceCount, pFences, waitAll, timeout));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateSemaphore,(
    VkDevice                                    device,
    const VkSemaphoreCreateInfo*                pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSemaphore*                                pSemaphore),
(device, pCreateInfo, pAllocator, pSemaphore));

YKM22_VULKAN_SYMBOL(
void,vkDestroySemaphore,(
    VkDevice                                    device,
    VkSemaphore                                 semaphore,
    const VkAllocationCallbacks*                pAllocator),
(device, semaphore, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateEvent,(
    VkDevice                                    device,
    const VkEventCreateInfo*                    pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkEvent*                                    pEvent),
(device, pCreateInfo, pAllocator, pEvent));

YKM22_VULKAN_SYMBOL(
void,vkDestroyEvent,(
    VkDevice                                    device,
    VkEvent                                     event,
    const VkAllocationCallbacks*                pAllocator),
(device, event, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetEventStatus,(
    VkDevice                                    device,
    VkEvent                                     event),
(device, event));

YKM22_VULKAN_SYMBOL(
VkResult,vkSetEvent,(
    VkDevice                                    device,
    VkEvent                                     event),
(device, event));

YKM22_VULKAN_SYMBOL(
VkResult,vkResetEvent,(
    VkDevice                                    device,
    VkEvent                                     event),
(device, event));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateQueryPool,(
    VkDevice                                    device,
    const VkQueryPoolCreateInfo*                pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkQueryPool*                                pQueryPool),
(device, pCreateInfo, pAllocator, pQueryPool));

YKM22_VULKAN_SYMBOL(
void,vkDestroyQueryPool,(
    VkDevice                                    device,
    VkQueryPool                                 queryPool,
    const VkAllocationCallbacks*                pAllocator),
(device, queryPool, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetQueryPoolResults,(
    VkDevice                                    device,
    VkQueryPool                                 queryPool,
    uint32_t                                    firstQuery,
    uint32_t                                    queryCount,
    size_t                                      dataSize,
    void*                                       pData,
    VkDeviceSize                                stride,
    VkQueryResultFlags                          flags),
(device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateBuffer,(
    VkDevice                                    device,
    const VkBufferCreateInfo*                   pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkBuffer*                                   pBuffer),
(device, pCreateInfo, pAllocator, pBuffer));

YKM22_VULKAN_SYMBOL(
void,vkDestroyBuffer,(
    VkDevice                                    device,
    VkBuffer                                    buffer,
    const VkAllocationCallbacks*                pAllocator),
(device, buffer, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateBufferView,(
    VkDevice                                    device,
    const VkBufferViewCreateInfo*               pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkBufferView*                               pView),
(device, pCreateInfo, pAllocator, pView));

YKM22_VULKAN_SYMBOL(
void,vkDestroyBufferView,(
    VkDevice                                    device,
    VkBufferView                                bufferView,
    const VkAllocationCallbacks*                pAllocator),
(device, bufferView, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateImage,(
    VkDevice                                    device,
    const VkImageCreateInfo*                    pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkImage*                                    pImage),
(device, pCreateInfo, pAllocator, pImage));

YKM22_VULKAN_SYMBOL(
void,vkDestroyImage,(
    VkDevice                                    device,
    VkImage                                     image,
    const VkAllocationCallbacks*                pAllocator),
(device, image, pAllocator));

YKM22_VULKAN_SYMBOL(
void,vkGetImageSubresourceLayout,(
    VkDevice                                    device,
    VkImage                                     image,
    const VkImageSubresource*                   pSubresource,
    VkSubresourceLayout*                        pLayout),
(device, image, pSubresource, pLayout));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateImageView,(
    VkDevice                                    device,
    const VkImageViewCreateInfo*                pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkImageView*                                pView),
(device, pCreateInfo, pAllocator, pView));

YKM22_VULKAN_SYMBOL(
void,vkDestroyImageView,(
    VkDevice                                    device,
    VkImageView                                 imageView,
    const VkAllocationCallbacks*                pAllocator),
(device, imageView, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateShaderModule,(
    VkDevice                                    device,
    const VkShaderModuleCreateInfo*             pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkShaderModule*                             pShaderModule),
(device, pCreateInfo, pAllocator, pShaderModule));

YKM22_VULKAN_SYMBOL(
void,vkDestroyShaderModule,(
    VkDevice                                    device,
    VkShaderModule                              shaderModule,
    const VkAllocationCallbacks*                pAllocator),
(device, shaderModule, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreatePipelineCache,(
    VkDevice                                    device,
    const VkPipelineCacheCreateInfo*            pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkPipelineCache*                            pPipelineCache),
(device, pCreateInfo, pAllocator, pPipelineCache));

YKM22_VULKAN_SYMBOL(
void,vkDestroyPipelineCache,(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    const VkAllocationCallbacks*                pAllocator),
(device, pipelineCache, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPipelineCacheData,(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    size_t*                                     pDataSize,
    void*                                       pData),
(device, pipelineCache, pDataSize, pData));

YKM22_VULKAN_SYMBOL(
VkResult,vkMergePipelineCaches,(
    VkDevice                                    device,
    VkPipelineCache                             dstCache,
    uint32_t                                    srcCacheCount,
    const VkPipelineCache*                      pSrcCaches),
(device, dstCache, srcCacheCount, pSrcCaches));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateGraphicsPipelines,(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    createInfoCount,
    const VkGraphicsPipelineCreateInfo*         pCreateInfos,
    const VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines),
(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateComputePipelines,(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    createInfoCount,
    const VkComputePipelineCreateInfo*          pCreateInfos,
    const VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines),
(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines));

YKM22_VULKAN_SYMBOL(
void,vkDestroyPipeline,(
    VkDevice                                    device,
    VkPipeline                                  pipeline,
    const VkAllocationCallbacks*                pAllocator),
(device, pipeline, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreatePipelineLayout,(
    VkDevice                                    device,
    const VkPipelineLayoutCreateInfo*           pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkPipelineLayout*                           pPipelineLayout),
(device, pCreateInfo, pAllocator, pPipelineLayout));

YKM22_VULKAN_SYMBOL(
void,vkDestroyPipelineLayout,(
    VkDevice                                    device,
    VkPipelineLayout                            pipelineLayout,
    const VkAllocationCallbacks*                pAllocator),
(device, pipelineLayout, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateSampler,(
    VkDevice                                    device,
    const VkSamplerCreateInfo*                  pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSampler*                                  pSampler),
(device, pCreateInfo, pAllocator, pSampler));

YKM22_VULKAN_SYMBOL(
void,vkDestroySampler,(
    VkDevice                                    device,
    VkSampler                                   sampler,
    const VkAllocationCallbacks*                pAllocator),
(device, sampler, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateDescriptorSetLayout,(
    VkDevice                                    device,
    const VkDescriptorSetLayoutCreateInfo*      pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDescriptorSetLayout*                      pSetLayout),
(device, pCreateInfo, pAllocator, pSetLayout));

YKM22_VULKAN_SYMBOL(
void,vkDestroyDescriptorSetLayout,(
    VkDevice                                    device,
    VkDescriptorSetLayout                       descriptorSetLayout,
    const VkAllocationCallbacks*                pAllocator),
(device, descriptorSetLayout, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateDescriptorPool,(
    VkDevice                                    device,
    const VkDescriptorPoolCreateInfo*           pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDescriptorPool*                           pDescriptorPool),
(device, pCreateInfo, pAllocator, pDescriptorPool));

YKM22_VULKAN_SYMBOL(
void,vkDestroyDescriptorPool,(
    VkDevice                                    device,
    VkDescriptorPool                            descriptorPool,
    const VkAllocationCallbacks*                pAllocator),
(device, descriptorPool, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkResetDescriptorPool,(
    VkDevice                                    device,
    VkDescriptorPool                            descriptorPool,
    VkDescriptorPoolResetFlags                  flags),
(device, descriptorPool, flags));

YKM22_VULKAN_SYMBOL(
VkResult,vkAllocateDescriptorSets,(
    VkDevice                                    device,
    const VkDescriptorSetAllocateInfo*          pAllocateInfo,
    VkDescriptorSet*                            pDescriptorSets),
(device, pAllocateInfo, pDescriptorSets));

YKM22_VULKAN_SYMBOL(
VkResult,vkFreeDescriptorSets,(
    VkDevice                                    device,
    VkDescriptorPool                            descriptorPool,
    uint32_t                                    descriptorSetCount,
    const VkDescriptorSet*                      pDescriptorSets),
(device, descriptorPool, descriptorSetCount, pDescriptorSets));

YKM22_VULKAN_SYMBOL(
void,vkUpdateDescriptorSets,(
    VkDevice                                    device,
    uint32_t                                    descriptorWriteCount,
    const VkWriteDescriptorSet*                 pDescriptorWrites,
    uint32_t                                    descriptorCopyCount,
    const VkCopyDescriptorSet*                  pDescriptorCopies),
(device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateFramebuffer,(
    VkDevice                                    device,
    const VkFramebufferCreateInfo*              pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkFramebuffer*                              pFramebuffer),
(device, pCreateInfo, pAllocator, pFramebuffer));

YKM22_VULKAN_SYMBOL(
void,vkDestroyFramebuffer,(
    VkDevice                                    device,
    VkFramebuffer                               framebuffer,
    const VkAllocationCallbacks*                pAllocator),
(device, framebuffer, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateRenderPass,(
    VkDevice                                    device,
    const VkRenderPassCreateInfo*               pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkRenderPass*                               pRenderPass),
(device, pCreateInfo, pAllocator, pRenderPass));

YKM22_VULKAN_SYMBOL(
void,vkDestroyRenderPass,(
    VkDevice                                    device,
    VkRenderPass                                renderPass,
    const VkAllocationCallbacks*                pAllocator),
(device, renderPass, pAllocator));

YKM22_VULKAN_SYMBOL(
void,vkGetRenderAreaGranularity,(
    VkDevice                                    device,
    VkRenderPass                                renderPass,
    VkExtent2D*                                 pGranularity),
(device, renderPass, pGranularity));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateCommandPool,(
    VkDevice                                    device,
    const VkCommandPoolCreateInfo*              pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkCommandPool*                              pCommandPool),
(device, pCreateInfo, pAllocator, pCommandPool));

YKM22_VULKAN_SYMBOL(
void,vkDestroyCommandPool,(
    VkDevice                                    device,
    VkCommandPool                               commandPool,
    const VkAllocationCallbacks*                pAllocator),
(device, commandPool, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkResetCommandPool,(
    VkDevice                                    device,
    VkCommandPool                               commandPool,
    VkCommandPoolResetFlags                     flags),
(device, commandPool, flags));

YKM22_VULKAN_SYMBOL(
VkResult,vkAllocateCommandBuffers,(
    VkDevice                                    device,
    const VkCommandBufferAllocateInfo*          pAllocateInfo,
    VkCommandBuffer*                            pCommandBuffers),
(device, pAllocateInfo, pCommandBuffers));

YKM22_VULKAN_SYMBOL(
void,vkFreeCommandBuffers,(
    VkDevice                                    device,
    VkCommandPool                               commandPool,
    uint32_t                                    commandBufferCount,
    const VkCommandBuffer*                      pCommandBuffers),
(device, commandPool, commandBufferCount, pCommandBuffers));

YKM22_VULKAN_SYMBOL(
VkResult,vkBeginCommandBuffer,(
    VkCommandBuffer                             commandBuffer,
    const VkCommandBufferBeginInfo*             pBeginInfo),
(commandBuffer, pBeginInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkEndCommandBuffer,(
    VkCommandBuffer                             commandBuffer),
(commandBuffer));

YKM22_VULKAN_SYMBOL(
VkResult,vkResetCommandBuffer,(
    VkCommandBuffer                             commandBuffer,
    VkCommandBufferResetFlags                   flags),
(commandBuffer, flags));

YKM22_VULKAN_SYMBOL(
void,vkCmdBindPipeline,(
    VkCommandBuffer                             commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    VkPipeline                                  pipeline),
(commandBuffer, pipelineBindPoint, pipeline));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetViewport,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstViewport,
    uint32_t                                    viewportCount,
    const VkViewport*                           pViewports),
(commandBuffer, firstViewport, viewportCount, pViewports));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetScissor,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstScissor,
    uint32_t                                    scissorCount,
    const VkRect2D*                             pScissors),
(commandBuffer, firstScissor, scissorCount, pScissors));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetLineWidth,(
    VkCommandBuffer                             commandBuffer,
    float                                       lineWidth),
(commandBuffer, lineWidth));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetDepthBias,(
    VkCommandBuffer                             commandBuffer,
    float                                       depthBiasConstantFactor,
    float                                       depthBiasClamp,
    float                                       depthBiasSlopeFactor),
(commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetBlendConstants,(
    VkCommandBuffer                             commandBuffer,
    const float                                 blendConstants[4]),
(commandBuffer, blendConstants));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetDepthBounds,(
    VkCommandBuffer                             commandBuffer,
    float                                       minDepthBounds,
    float                                       maxDepthBounds),
(commandBuffer, minDepthBounds, maxDepthBounds));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetStencilCompareMask,(
    VkCommandBuffer                             commandBuffer,
    VkStencilFaceFlags                          faceMask,
    uint32_t                                    compareMask),
(commandBuffer, faceMask, compareMask));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetStencilWriteMask,(
    VkCommandBuffer                             commandBuffer,
    VkStencilFaceFlags                          faceMask,
    uint32_t                                    writeMask),
(commandBuffer, faceMask, writeMask));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetStencilReference,(
    VkCommandBuffer                             commandBuffer,
    VkStencilFaceFlags                          faceMask,
    uint32_t                                    reference),
(commandBuffer, faceMask, reference));

YKM22_VULKAN_SYMBOL(
void,vkCmdBindDescriptorSets,(
    VkCommandBuffer                             commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    VkPipelineLayout                            layout,
    uint32_t                                    firstSet,
    uint32_t                                    descriptorSetCount,
    const VkDescriptorSet*                      pDescriptorSets,
    uint32_t                                    dynamicOffsetCount,
    const uint32_t*                             pDynamicOffsets),
(commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets));

YKM22_VULKAN_SYMBOL(
void,vkCmdBindIndexBuffer,(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    VkIndexType                                 indexType),
(commandBuffer, buffer, offset, indexType));

YKM22_VULKAN_SYMBOL(
void,vkCmdBindVertexBuffers,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstBinding,
    uint32_t                                    bindingCount,
    const VkBuffer*                             pBuffers,
    const VkDeviceSize*                         pOffsets),
(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets));

YKM22_VULKAN_SYMBOL(
void,vkCmdDraw,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    vertexCount,
    uint32_t                                    instanceCount,
    uint32_t                                    firstVertex,
    uint32_t                                    firstInstance),
(commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance));

YKM22_VULKAN_SYMBOL(
void,vkCmdDrawIndexed,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    indexCount,
    uint32_t                                    instanceCount,
    uint32_t                                    firstIndex,
    int32_t                                     vertexOffset,
    uint32_t                                    firstInstance),
(commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance));

YKM22_VULKAN_SYMBOL(
void,vkCmdDrawIndirect,(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    uint32_t                                    drawCount,
    uint32_t                                    stride),
(commandBuffer, buffer, offset, drawCount, stride));

YKM22_VULKAN_SYMBOL(
void,vkCmdDrawIndexedIndirect,(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    uint32_t                                    drawCount,
    uint32_t                                    stride),
(commandBuffer, buffer, offset, drawCount, stride));

YKM22_VULKAN_SYMBOL(
void,vkCmdDispatch,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    groupCountX,
    uint32_t                                    groupCountY,
    uint32_t                                    groupCountZ),
(commandBuffer, groupCountX, groupCountY, groupCountZ));

YKM22_VULKAN_SYMBOL(
void,vkCmdDispatchIndirect,(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset),
(commandBuffer, buffer, offset));

YKM22_VULKAN_SYMBOL(
void,vkCmdCopyBuffer,(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    srcBuffer,
    VkBuffer                                    dstBuffer,
    uint32_t                                    regionCount,
    const VkBufferCopy*                         pRegions),
(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions));

YKM22_VULKAN_SYMBOL(
void,vkCmdCopyImage,(
    VkCommandBuffer                             commandBuffer,
    VkImage                                     srcImage,
    VkImageLayout                               srcImageLayout,
    VkImage                                     dstImage,
    VkImageLayout                               dstImageLayout,
    uint32_t                                    regionCount,
    const VkImageCopy*                          pRegions),
(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions));

YKM22_VULKAN_SYMBOL(
void,vkCmdBlitImage,(
    VkCommandBuffer                             commandBuffer,
    VkImage                                     srcImage,
    VkImageLayout                               srcImageLayout,
    VkImage                                     dstImage,
    VkImageLayout                               dstImageLayout,
    uint32_t                                    regionCount,
    const VkImageBlit*                          pRegions,
    VkFilter                                    filter),
(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter));

YKM22_VULKAN_SYMBOL(
void,vkCmdCopyBufferToImage,(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    srcBuffer,
    VkImage                                     dstImage,
    VkImageLayout                               dstImageLayout,
    uint32_t                                    regionCount,
    const VkBufferImageCopy*                    pRegions),
(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions));

YKM22_VULKAN_SYMBOL(
void,vkCmdCopyImageToBuffer,(
    VkCommandBuffer                             commandBuffer,
    VkImage                                     srcImage,
    VkImageLayout                               srcImageLayout,
    VkBuffer                                    dstBuffer,
    uint32_t                                    regionCount,
    const VkBufferImageCopy*                    pRegions),
(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions));

YKM22_VULKAN_SYMBOL(
void,vkCmdUpdateBuffer,(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    dstBuffer,
    VkDeviceSize                                dstOffset,
    VkDeviceSize                                dataSize,
    const void*                                 pData),
(commandBuffer, dstBuffer, dstOffset, dataSize, pData));

YKM22_VULKAN_SYMBOL(
void,vkCmdFillBuffer,(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    dstBuffer,
    VkDeviceSize                                dstOffset,
    VkDeviceSize                                size,
    uint32_t                                    data),
(commandBuffer, dstBuffer, dstOffset, size, data));

YKM22_VULKAN_SYMBOL(
void,vkCmdClearColorImage,(
    VkCommandBuffer                             commandBuffer,
    VkImage                                     image,
    VkImageLayout                               imageLayout,
    const VkClearColorValue*                    pColor,
    uint32_t                                    rangeCount,
    const VkImageSubresourceRange*              pRanges),
(commandBuffer, image, imageLayout, pColor, rangeCount, pRanges));

YKM22_VULKAN_SYMBOL(
void,vkCmdClearDepthStencilImage,(
    VkCommandBuffer                             commandBuffer,
    VkImage                                     image,
    VkImageLayout                               imageLayout,
    const VkClearDepthStencilValue*             pDepthStencil,
    uint32_t                                    rangeCount,
    const VkImageSubresourceRange*              pRanges),
(commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges));

YKM22_VULKAN_SYMBOL(
void,vkCmdClearAttachments,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    attachmentCount,
    const VkClearAttachment*                    pAttachments,
    uint32_t                                    rectCount,
    const VkClearRect*                          pRects),
(commandBuffer, attachmentCount, pAttachments, rectCount, pRects));

YKM22_VULKAN_SYMBOL(
void,vkCmdResolveImage,(
    VkCommandBuffer                             commandBuffer,
    VkImage                                     srcImage,
    VkImageLayout                               srcImageLayout,
    VkImage                                     dstImage,
    VkImageLayout                               dstImageLayout,
    uint32_t                                    regionCount,
    const VkImageResolve*                       pRegions),
(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetEvent,(
    VkCommandBuffer                             commandBuffer,
    VkEvent                                     event,
    VkPipelineStageFlags                        stageMask),
(commandBuffer, event, stageMask));

YKM22_VULKAN_SYMBOL(
void,vkCmdResetEvent,(
    VkCommandBuffer                             commandBuffer,
    VkEvent                                     event,
    VkPipelineStageFlags                        stageMask),
(commandBuffer, event, stageMask));

YKM22_VULKAN_SYMBOL(
void,vkCmdWaitEvents,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    eventCount,
    const VkEvent*                              pEvents,
    VkPipelineStageFlags                        srcStageMask,
    VkPipelineStageFlags                        dstStageMask,
    uint32_t                                    memoryBarrierCount,
    const VkMemoryBarrier*                      pMemoryBarriers,
    uint32_t                                    bufferMemoryBarrierCount,
    const VkBufferMemoryBarrier*                pBufferMemoryBarriers,
    uint32_t                                    imageMemoryBarrierCount,
    const VkImageMemoryBarrier*                 pImageMemoryBarriers),
(commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers));

YKM22_VULKAN_SYMBOL(
void,vkCmdPipelineBarrier,(
    VkCommandBuffer                             commandBuffer,
    VkPipelineStageFlags                        srcStageMask,
    VkPipelineStageFlags                        dstStageMask,
    VkDependencyFlags                           dependencyFlags,
    uint32_t                                    memoryBarrierCount,
    const VkMemoryBarrier*                      pMemoryBarriers,
    uint32_t                                    bufferMemoryBarrierCount,
    const VkBufferMemoryBarrier*                pBufferMemoryBarriers,
    uint32_t                                    imageMemoryBarrierCount,
    const VkImageMemoryBarrier*                 pImageMemoryBarriers),
(commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers));

YKM22_VULKAN_SYMBOL(
void,vkCmdBeginQuery,(
    VkCommandBuffer                             commandBuffer,
    VkQueryPool                                 queryPool,
    uint32_t                                    query,
    VkQueryControlFlags                         flags),
(commandBuffer, queryPool, query, flags));

YKM22_VULKAN_SYMBOL(
void,vkCmdEndQuery,(
    VkCommandBuffer                             commandBuffer,
    VkQueryPool                                 queryPool,
    uint32_t                                    query),
(commandBuffer, queryPool, query));

YKM22_VULKAN_SYMBOL(
void,vkCmdResetQueryPool,(
    VkCommandBuffer                             commandBuffer,
    VkQueryPool                                 queryPool,
    uint32_t                                    firstQuery,
    uint32_t                                    queryCount),
(commandBuffer, queryPool, firstQuery, queryCount));

YKM22_VULKAN_SYMBOL(
void,vkCmdWriteTimestamp,(
    VkCommandBuffer                             commandBuffer,
    VkPipelineStageFlagBits                     pipelineStage,
    VkQueryPool                                 queryPool,
    uint32_t                                    query),
(commandBuffer, pipelineStage, queryPool, query));

YKM22_VULKAN_SYMBOL(
void,vkCmdCopyQueryPoolResults,(
    VkCommandBuffer                             commandBuffer,
    VkQueryPool                                 queryPool,
    uint32_t                                    firstQuery,
    uint32_t                                    queryCount,
    VkBuffer                                    dstBuffer,
    VkDeviceSize                                dstOffset,
    VkDeviceSize                                stride,
    VkQueryResultFlags                          flags),
(commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags));

YKM22_VULKAN_SYMBOL(
void,vkCmdPushConstants,(
    VkCommandBuffer                             commandBuffer,
    VkPipelineLayout                            layout,
    VkShaderStageFlags                          stageFlags,
    uint32_t                                    offset,
    uint32_t                                    size,
    const void*                                 pValues),
(commandBuffer, layout, stageFlags, offset, size, pValues));

YKM22_VULKAN_SYMBOL(
void,vkCmdBeginRenderPass,(
    VkCommandBuffer                             commandBuffer,
    const VkRenderPassBeginInfo*                pRenderPassBegin,
    VkSubpassContents                           contents),
(commandBuffer, pRenderPassBegin, contents));

YKM22_VULKAN_SYMBOL(
void,vkCmdNextSubpass,(
    VkCommandBuffer                             commandBuffer,
    VkSubpassContents                           contents),
(commandBuffer, contents));

YKM22_VULKAN_SYMBOL(
void,vkCmdEndRenderPass,(
    VkCommandBuffer                             commandBuffer),
(commandBuffer));

YKM22_VULKAN_SYMBOL(
void,vkCmdExecuteCommands,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    commandBufferCount,
    const VkCommandBuffer*                      pCommandBuffers),
(commandBuffer, commandBufferCount, pCommandBuffers));

YKM22_VULKAN_SYMBOL(
VkResult,vkEnumerateInstanceVersion,(
    uint32_t*                                   pApiVersion),
(pApiVersion));

YKM22_VULKAN_SYMBOL(
VkResult,vkBindBufferMemory2,(
    VkDevice                                    device,
    uint32_t                                    bindInfoCount,
    const VkBindBufferMemoryInfo*               pBindInfos),
(device, bindInfoCount, pBindInfos));

YKM22_VULKAN_SYMBOL(
VkResult,vkBindImageMemory2,(
    VkDevice                                    device,
    uint32_t                                    bindInfoCount,
    const VkBindImageMemoryInfo*                pBindInfos),
(device, bindInfoCount, pBindInfos));

YKM22_VULKAN_SYMBOL(
void,vkGetDeviceGroupPeerMemoryFeatures,(
    VkDevice                                    device,
    uint32_t                                    heapIndex,
    uint32_t                                    localDeviceIndex,
    uint32_t                                    remoteDeviceIndex,
    VkPeerMemoryFeatureFlags*                   pPeerMemoryFeatures),
(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetDeviceMask,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    deviceMask),
(commandBuffer, deviceMask));

YKM22_VULKAN_SYMBOL(
void,vkCmdDispatchBase,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    baseGroupX,
    uint32_t                                    baseGroupY,
    uint32_t                                    baseGroupZ,
    uint32_t                                    groupCountX,
    uint32_t                                    groupCountY,
    uint32_t                                    groupCountZ),
(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ));

YKM22_VULKAN_SYMBOL(
VkResult,vkEnumeratePhysicalDeviceGroups,(
    VkInstance                                  instance,
    uint32_t*                                   pPhysicalDeviceGroupCount,
    VkPhysicalDeviceGroupProperties*            pPhysicalDeviceGroupProperties),
(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties));

YKM22_VULKAN_SYMBOL(
void,vkGetImageMemoryRequirements2,(
    VkDevice                                    device,
    const VkImageMemoryRequirementsInfo2*       pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements),
(device, pInfo, pMemoryRequirements));

YKM22_VULKAN_SYMBOL(
void,vkGetBufferMemoryRequirements2,(
    VkDevice                                    device,
    const VkBufferMemoryRequirementsInfo2*      pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements),
(device, pInfo, pMemoryRequirements));

YKM22_VULKAN_SYMBOL(
void,vkGetImageSparseMemoryRequirements2,(
    VkDevice                                    device,
    const VkImageSparseMemoryRequirementsInfo2* pInfo,
    uint32_t*                                   pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2*           pSparseMemoryRequirements),
(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceFeatures2,(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceFeatures2*                  pFeatures),
(physicalDevice, pFeatures));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceProperties2,(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceProperties2*                pProperties),
(physicalDevice, pProperties));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceFormatProperties2,(
    VkPhysicalDevice                            physicalDevice,
    VkFormat                                    format,
    VkFormatProperties2*                        pFormatProperties),
(physicalDevice, format, pFormatProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceImageFormatProperties2,(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceImageFormatInfo2*     pImageFormatInfo,
    VkImageFormatProperties2*                   pImageFormatProperties),
(physicalDevice, pImageFormatInfo, pImageFormatProperties));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceQueueFamilyProperties2,(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pQueueFamilyPropertyCount,
    VkQueueFamilyProperties2*                   pQueueFamilyProperties),
(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceMemoryProperties2,(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceMemoryProperties2*          pMemoryProperties),
(physicalDevice, pMemoryProperties));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceSparseImageFormatProperties2,(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo,
    uint32_t*                                   pPropertyCount,
    VkSparseImageFormatProperties2*             pProperties),
(physicalDevice, pFormatInfo, pPropertyCount, pProperties));

YKM22_VULKAN_SYMBOL(
void,vkTrimCommandPool,(
    VkDevice                                    device,
    VkCommandPool                               commandPool,
    VkCommandPoolTrimFlags                      flags),
(device, commandPool, flags));

YKM22_VULKAN_SYMBOL(
void,vkGetDeviceQueue2,(
    VkDevice                                    device,
    const VkDeviceQueueInfo2*                   pQueueInfo,
    VkQueue*                                    pQueue),
(device, pQueueInfo, pQueue));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateSamplerYcbcrConversion,(
    VkDevice                                    device,
    const VkSamplerYcbcrConversionCreateInfo*   pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSamplerYcbcrConversion*                   pYcbcrConversion),
(device, pCreateInfo, pAllocator, pYcbcrConversion));

YKM22_VULKAN_SYMBOL(
void,vkDestroySamplerYcbcrConversion,(
    VkDevice                                    device,
    VkSamplerYcbcrConversion                    ycbcrConversion,
    const VkAllocationCallbacks*                pAllocator),
(device, ycbcrConversion, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateDescriptorUpdateTemplate,(
    VkDevice                                    device,
    const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDescriptorUpdateTemplate*                 pDescriptorUpdateTemplate),
(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate));

YKM22_VULKAN_SYMBOL(
void,vkDestroyDescriptorUpdateTemplate,(
    VkDevice                                    device,
    VkDescriptorUpdateTemplate                  descriptorUpdateTemplate,
    const VkAllocationCallbacks*                pAllocator),
(device, descriptorUpdateTemplate, pAllocator));

YKM22_VULKAN_SYMBOL(
void,vkUpdateDescriptorSetWithTemplate,(
    VkDevice                                    device,
    VkDescriptorSet                             descriptorSet,
    VkDescriptorUpdateTemplate                  descriptorUpdateTemplate,
    const void*                                 pData),
(device, descriptorSet, descriptorUpdateTemplate, pData));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceExternalBufferProperties,(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceExternalBufferInfo*   pExternalBufferInfo,
    VkExternalBufferProperties*                 pExternalBufferProperties),
(physicalDevice, pExternalBufferInfo, pExternalBufferProperties));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceExternalFenceProperties,(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceExternalFenceInfo*    pExternalFenceInfo,
    VkExternalFenceProperties*                  pExternalFenceProperties),
(physicalDevice, pExternalFenceInfo, pExternalFenceProperties));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceExternalSemaphoreProperties,(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo,
    VkExternalSemaphoreProperties*              pExternalSemaphoreProperties),
(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties));

YKM22_VULKAN_SYMBOL(
void,vkGetDescriptorSetLayoutSupport,(
    VkDevice                                    device,
    const VkDescriptorSetLayoutCreateInfo*      pCreateInfo,
    VkDescriptorSetLayoutSupport*               pSupport),
(device, pCreateInfo, pSupport));

YKM22_VULKAN_SYMBOL(
void,vkCmdDrawIndirectCount,(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    VkBuffer                                    countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride),
(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride));

YKM22_VULKAN_SYMBOL(
void,vkCmdDrawIndexedIndirectCount,(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    VkBuffer                                    countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride),
(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateRenderPass2,(
    VkDevice                                    device,
    const VkRenderPassCreateInfo2*              pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkRenderPass*                               pRenderPass),
(device, pCreateInfo, pAllocator, pRenderPass));

YKM22_VULKAN_SYMBOL(
void,vkCmdBeginRenderPass2,(
    VkCommandBuffer                             commandBuffer,
    const VkRenderPassBeginInfo*                pRenderPassBegin,
    const VkSubpassBeginInfo*                   pSubpassBeginInfo),
(commandBuffer, pRenderPassBegin, pSubpassBeginInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdNextSubpass2,(
    VkCommandBuffer                             commandBuffer,
    const VkSubpassBeginInfo*                   pSubpassBeginInfo,
    const VkSubpassEndInfo*                     pSubpassEndInfo),
(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdEndRenderPass2,(
    VkCommandBuffer                             commandBuffer,
    const VkSubpassEndInfo*                     pSubpassEndInfo),
(commandBuffer, pSubpassEndInfo));

YKM22_VULKAN_SYMBOL(
void,vkResetQueryPool,(
    VkDevice                                    device,
    VkQueryPool                                 queryPool,
    uint32_t                                    firstQuery,
    uint32_t                                    queryCount),
(device, queryPool, firstQuery, queryCount));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetSemaphoreCounterValue,(
    VkDevice                                    device,
    VkSemaphore                                 semaphore,
    uint64_t*                                   pValue),
(device, semaphore, pValue));

YKM22_VULKAN_SYMBOL(
VkResult,vkWaitSemaphores,(
    VkDevice                                    device,
    const VkSemaphoreWaitInfo*                  pWaitInfo,
    uint64_t                                    timeout),
(device, pWaitInfo, timeout));

YKM22_VULKAN_SYMBOL(
VkResult,vkSignalSemaphore,(
    VkDevice                                    device,
    const VkSemaphoreSignalInfo*                pSignalInfo),
(device, pSignalInfo));

YKM22_VULKAN_SYMBOL(
VkDeviceAddress,vkGetBufferDeviceAddress,(
    VkDevice                                    device,
    const VkBufferDeviceAddressInfo*            pInfo),
(device, pInfo));

YKM22_VULKAN_SYMBOL(
uint64_t,vkGetBufferOpaqueCaptureAddress,(
    VkDevice                                    device,
    const VkBufferDeviceAddressInfo*            pInfo),
(device, pInfo));

YKM22_VULKAN_SYMBOL(
uint64_t,vkGetDeviceMemoryOpaqueCaptureAddress,(
    VkDevice                                    device,
    const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo),
(device, pInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceToolProperties,(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pToolCount,
    VkPhysicalDeviceToolProperties*             pToolProperties),
(physicalDevice, pToolCount, pToolProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreatePrivateDataSlot,(
    VkDevice                                    device,
    const VkPrivateDataSlotCreateInfo*          pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkPrivateDataSlot*                          pPrivateDataSlot),
(device, pCreateInfo, pAllocator, pPrivateDataSlot));

YKM22_VULKAN_SYMBOL(
void,vkDestroyPrivateDataSlot,(
    VkDevice                                    device,
    VkPrivateDataSlot                           privateDataSlot,
    const VkAllocationCallbacks*                pAllocator),
(device, privateDataSlot, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkSetPrivateData,(
    VkDevice                                    device,
    VkObjectType                                objectType,
    uint64_t                                    objectHandle,
    VkPrivateDataSlot                           privateDataSlot,
    uint64_t                                    data),
(device, objectType, objectHandle, privateDataSlot, data));

YKM22_VULKAN_SYMBOL(
void,vkGetPrivateData,(
    VkDevice                                    device,
    VkObjectType                                objectType,
    uint64_t                                    objectHandle,
    VkPrivateDataSlot                           privateDataSlot,
    uint64_t*                                   pData),
(device, objectType, objectHandle, privateDataSlot, pData));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetEvent2,(
    VkCommandBuffer                             commandBuffer,
    VkEvent                                     event,
    const VkDependencyInfo*                     pDependencyInfo),
(commandBuffer, event, pDependencyInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdResetEvent2,(
    VkCommandBuffer                             commandBuffer,
    VkEvent                                     event,
    VkPipelineStageFlags2                       stageMask),
(commandBuffer, event, stageMask));

YKM22_VULKAN_SYMBOL(
void,vkCmdWaitEvents2,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    eventCount,
    const VkEvent*                              pEvents,
    const VkDependencyInfo*                     pDependencyInfos),
(commandBuffer, eventCount, pEvents, pDependencyInfos));

YKM22_VULKAN_SYMBOL(
void,vkCmdPipelineBarrier2,(
    VkCommandBuffer                             commandBuffer,
    const VkDependencyInfo*                     pDependencyInfo),
(commandBuffer, pDependencyInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdWriteTimestamp2,(
    VkCommandBuffer                             commandBuffer,
    VkPipelineStageFlags2                       stage,
    VkQueryPool                                 queryPool,
    uint32_t                                    query),
(commandBuffer, stage, queryPool, query));

YKM22_VULKAN_SYMBOL(
VkResult,vkQueueSubmit2,(
    VkQueue                                     queue,
    uint32_t                                    submitCount,
    const VkSubmitInfo2*                        pSubmits,
    VkFence                                     fence),
(queue, submitCount, pSubmits, fence));

YKM22_VULKAN_SYMBOL(
void,vkCmdCopyBuffer2,(
    VkCommandBuffer                             commandBuffer,
    const VkCopyBufferInfo2*                    pCopyBufferInfo),
(commandBuffer, pCopyBufferInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdCopyImage2,(
    VkCommandBuffer                             commandBuffer,
    const VkCopyImageInfo2*                     pCopyImageInfo),
(commandBuffer, pCopyImageInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdCopyBufferToImage2,(
    VkCommandBuffer                             commandBuffer,
    const VkCopyBufferToImageInfo2*             pCopyBufferToImageInfo),
(commandBuffer, pCopyBufferToImageInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdCopyImageToBuffer2,(
    VkCommandBuffer                             commandBuffer,
    const VkCopyImageToBufferInfo2*             pCopyImageToBufferInfo),
(commandBuffer, pCopyImageToBufferInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdBlitImage2,(
    VkCommandBuffer                             commandBuffer,
    const VkBlitImageInfo2*                     pBlitImageInfo),
(commandBuffer, pBlitImageInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdResolveImage2,(
    VkCommandBuffer                             commandBuffer,
    const VkResolveImageInfo2*                  pResolveImageInfo),
(commandBuffer, pResolveImageInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdBeginRendering,(
    VkCommandBuffer                             commandBuffer,
    const VkRenderingInfo*                      pRenderingInfo),
(commandBuffer, pRenderingInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdEndRendering,(
    VkCommandBuffer                             commandBuffer),
(commandBuffer));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetCullMode,(
    VkCommandBuffer                             commandBuffer,
    VkCullModeFlags                             cullMode),
(commandBuffer, cullMode));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetFrontFace,(
    VkCommandBuffer                             commandBuffer,
    VkFrontFace                                 frontFace),
(commandBuffer, frontFace));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetPrimitiveTopology,(
    VkCommandBuffer                             commandBuffer,
    VkPrimitiveTopology                         primitiveTopology),
(commandBuffer, primitiveTopology));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetViewportWithCount,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    viewportCount,
    const VkViewport*                           pViewports),
(commandBuffer, viewportCount, pViewports));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetScissorWithCount,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    scissorCount,
    const VkRect2D*                             pScissors),
(commandBuffer, scissorCount, pScissors));

YKM22_VULKAN_SYMBOL(
void,vkCmdBindVertexBuffers2,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstBinding,
    uint32_t                                    bindingCount,
    const VkBuffer*                             pBuffers,
    const VkDeviceSize*                         pOffsets,
    const VkDeviceSize*                         pSizes,
    const VkDeviceSize*                         pStrides),
(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetDepthTestEnable,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthTestEnable),
(commandBuffer, depthTestEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetDepthWriteEnable,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthWriteEnable),
(commandBuffer, depthWriteEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetDepthCompareOp,(
    VkCommandBuffer                             commandBuffer,
    VkCompareOp                                 depthCompareOp),
(commandBuffer, depthCompareOp));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetDepthBoundsTestEnable,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthBoundsTestEnable),
(commandBuffer, depthBoundsTestEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetStencilTestEnable,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    stencilTestEnable),
(commandBuffer, stencilTestEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetStencilOp,(
    VkCommandBuffer                             commandBuffer,
    VkStencilFaceFlags                          faceMask,
    VkStencilOp                                 failOp,
    VkStencilOp                                 passOp,
    VkStencilOp                                 depthFailOp,
    VkCompareOp                                 compareOp),
(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetRasterizerDiscardEnable,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    rasterizerDiscardEnable),
(commandBuffer, rasterizerDiscardEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetDepthBiasEnable,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthBiasEnable),
(commandBuffer, depthBiasEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetPrimitiveRestartEnable,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    primitiveRestartEnable),
(commandBuffer, primitiveRestartEnable));

YKM22_VULKAN_SYMBOL(
void,vkGetDeviceBufferMemoryRequirements,(
    VkDevice                                    device,
    const VkDeviceBufferMemoryRequirements*     pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements),
(device, pInfo, pMemoryRequirements));

YKM22_VULKAN_SYMBOL(
void,vkGetDeviceImageMemoryRequirements,(
    VkDevice                                    device,
    const VkDeviceImageMemoryRequirements*      pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements),
(device, pInfo, pMemoryRequirements));

YKM22_VULKAN_SYMBOL(
void,vkGetDeviceImageSparseMemoryRequirements,(
    VkDevice                                    device,
    const VkDeviceImageMemoryRequirements*      pInfo,
    uint32_t*                                   pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2*           pSparseMemoryRequirements),
(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements));

YKM22_VULKAN_SYMBOL(
void,vkDestroySurfaceKHR,(
    VkInstance                                  instance,
    VkSurfaceKHR                                surface,
    const VkAllocationCallbacks*                pAllocator),
(instance, surface, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceSurfaceSupportKHR,(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    VkSurfaceKHR                                surface,
    VkBool32*                                   pSupported),
(physicalDevice, queueFamilyIndex, surface, pSupported));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceSurfaceCapabilitiesKHR,(
    VkPhysicalDevice                            physicalDevice,
    VkSurfaceKHR                                surface,
    VkSurfaceCapabilitiesKHR*                   pSurfaceCapabilities),
(physicalDevice, surface, pSurfaceCapabilities));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceSurfaceFormatsKHR,(
    VkPhysicalDevice                            physicalDevice,
    VkSurfaceKHR                                surface,
    uint32_t*                                   pSurfaceFormatCount,
    VkSurfaceFormatKHR*                         pSurfaceFormats),
(physicalDevice, surface, pSurfaceFormatCount, pSurfaceFormats));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceSurfacePresentModesKHR,(
    VkPhysicalDevice                            physicalDevice,
    VkSurfaceKHR                                surface,
    uint32_t*                                   pPresentModeCount,
    VkPresentModeKHR*                           pPresentModes),
(physicalDevice, surface, pPresentModeCount, pPresentModes));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateSwapchainKHR,(
    VkDevice                                    device,
    const VkSwapchainCreateInfoKHR*             pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSwapchainKHR*                             pSwapchain),
(device, pCreateInfo, pAllocator, pSwapchain));

YKM22_VULKAN_SYMBOL(
void,vkDestroySwapchainKHR,(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    const VkAllocationCallbacks*                pAllocator),
(device, swapchain, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetSwapchainImagesKHR,(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    uint32_t*                                   pSwapchainImageCount,
    VkImage*                                    pSwapchainImages),
(device, swapchain, pSwapchainImageCount, pSwapchainImages));

YKM22_VULKAN_SYMBOL(
VkResult,vkAcquireNextImageKHR,(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    uint64_t                                    timeout,
    VkSemaphore                                 semaphore,
    VkFence                                     fence,
    uint32_t*                                   pImageIndex),
(device, swapchain, timeout, semaphore, fence, pImageIndex));

YKM22_VULKAN_SYMBOL(
VkResult,vkQueuePresentKHR,(
    VkQueue                                     queue,
    const VkPresentInfoKHR*                     pPresentInfo),
(queue, pPresentInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetDeviceGroupPresentCapabilitiesKHR,(
    VkDevice                                    device,
    VkDeviceGroupPresentCapabilitiesKHR*        pDeviceGroupPresentCapabilities),
(device, pDeviceGroupPresentCapabilities));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetDeviceGroupSurfacePresentModesKHR,(
    VkDevice                                    device,
    VkSurfaceKHR                                surface,
    VkDeviceGroupPresentModeFlagsKHR*           pModes),
(device, surface, pModes));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDevicePresentRectanglesKHR,(
    VkPhysicalDevice                            physicalDevice,
    VkSurfaceKHR                                surface,
    uint32_t*                                   pRectCount,
    VkRect2D*                                   pRects),
(physicalDevice, surface, pRectCount, pRects));

YKM22_VULKAN_SYMBOL(
VkResult,vkAcquireNextImage2KHR,(
    VkDevice                                    device,
    const VkAcquireNextImageInfoKHR*            pAcquireInfo,
    uint32_t*                                   pImageIndex),
(device, pAcquireInfo, pImageIndex));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceDisplayPropertiesKHR,(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pPropertyCount,
    VkDisplayPropertiesKHR*                     pProperties),
(physicalDevice, pPropertyCount, pProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceDisplayPlanePropertiesKHR,(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pPropertyCount,
    VkDisplayPlanePropertiesKHR*                pProperties),
(physicalDevice, pPropertyCount, pProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetDisplayPlaneSupportedDisplaysKHR,(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    planeIndex,
    uint32_t*                                   pDisplayCount,
    VkDisplayKHR*                               pDisplays),
(physicalDevice, planeIndex, pDisplayCount, pDisplays));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetDisplayModePropertiesKHR,(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display,
    uint32_t*                                   pPropertyCount,
    VkDisplayModePropertiesKHR*                 pProperties),
(physicalDevice, display, pPropertyCount, pProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateDisplayModeKHR,(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display,
    const VkDisplayModeCreateInfoKHR*           pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDisplayModeKHR*                           pMode),
(physicalDevice, display, pCreateInfo, pAllocator, pMode));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetDisplayPlaneCapabilitiesKHR,(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayModeKHR                            mode,
    uint32_t                                    planeIndex,
    VkDisplayPlaneCapabilitiesKHR*              pCapabilities),
(physicalDevice, mode, planeIndex, pCapabilities));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateDisplayPlaneSurfaceKHR,(
    VkInstance                                  instance,
    const VkDisplaySurfaceCreateInfoKHR*        pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface),
(instance, pCreateInfo, pAllocator, pSurface));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateSharedSwapchainsKHR,(
    VkDevice                                    device,
    uint32_t                                    swapchainCount,
    const VkSwapchainCreateInfoKHR*             pCreateInfos,
    const VkAllocationCallbacks*                pAllocator,
    VkSwapchainKHR*                             pSwapchains),
(device, swapchainCount, pCreateInfos, pAllocator, pSwapchains));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceVideoCapabilitiesKHR,(
    VkPhysicalDevice                            physicalDevice,
    const VkVideoProfileInfoKHR*                pVideoProfile,
    VkVideoCapabilitiesKHR*                     pCapabilities),
(physicalDevice, pVideoProfile, pCapabilities));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceVideoFormatPropertiesKHR,(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceVideoFormatInfoKHR*   pVideoFormatInfo,
    uint32_t*                                   pVideoFormatPropertyCount,
    VkVideoFormatPropertiesKHR*                 pVideoFormatProperties),
(physicalDevice, pVideoFormatInfo, pVideoFormatPropertyCount, pVideoFormatProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateVideoSessionKHR,(
    VkDevice                                    device,
    const VkVideoSessionCreateInfoKHR*          pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkVideoSessionKHR*                          pVideoSession),
(device, pCreateInfo, pAllocator, pVideoSession));

YKM22_VULKAN_SYMBOL(
void,vkDestroyVideoSessionKHR,(
    VkDevice                                    device,
    VkVideoSessionKHR                           videoSession,
    const VkAllocationCallbacks*                pAllocator),
(device, videoSession, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetVideoSessionMemoryRequirementsKHR,(
    VkDevice                                    device,
    VkVideoSessionKHR                           videoSession,
    uint32_t*                                   pMemoryRequirementsCount,
    VkVideoSessionMemoryRequirementsKHR*        pMemoryRequirements),
(device, videoSession, pMemoryRequirementsCount, pMemoryRequirements));

YKM22_VULKAN_SYMBOL(
VkResult,vkBindVideoSessionMemoryKHR,(
    VkDevice                                    device,
    VkVideoSessionKHR                           videoSession,
    uint32_t                                    bindSessionMemoryInfoCount,
    const VkBindVideoSessionMemoryInfoKHR*      pBindSessionMemoryInfos),
(device, videoSession, bindSessionMemoryInfoCount, pBindSessionMemoryInfos));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateVideoSessionParametersKHR,(
    VkDevice                                    device,
    const VkVideoSessionParametersCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkVideoSessionParametersKHR*                pVideoSessionParameters),
(device, pCreateInfo, pAllocator, pVideoSessionParameters));

YKM22_VULKAN_SYMBOL(
VkResult,vkUpdateVideoSessionParametersKHR,(
    VkDevice                                    device,
    VkVideoSessionParametersKHR                 videoSessionParameters,
    const VkVideoSessionParametersUpdateInfoKHR* pUpdateInfo),
(device, videoSessionParameters, pUpdateInfo));

YKM22_VULKAN_SYMBOL(
void,vkDestroyVideoSessionParametersKHR,(
    VkDevice                                    device,
    VkVideoSessionParametersKHR                 videoSessionParameters,
    const VkAllocationCallbacks*                pAllocator),
(device, videoSessionParameters, pAllocator));

YKM22_VULKAN_SYMBOL(
void,vkCmdBeginVideoCodingKHR,(
    VkCommandBuffer                             commandBuffer,
    const VkVideoBeginCodingInfoKHR*            pBeginInfo),
(commandBuffer, pBeginInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdEndVideoCodingKHR,(
    VkCommandBuffer                             commandBuffer,
    const VkVideoEndCodingInfoKHR*              pEndCodingInfo),
(commandBuffer, pEndCodingInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdControlVideoCodingKHR,(
    VkCommandBuffer                             commandBuffer,
    const VkVideoCodingControlInfoKHR*          pCodingControlInfo),
(commandBuffer, pCodingControlInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdDecodeVideoKHR,(
    VkCommandBuffer                             commandBuffer,
    const VkVideoDecodeInfoKHR*                 pDecodeInfo),
(commandBuffer, pDecodeInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdBeginRenderingKHR,(
    VkCommandBuffer                             commandBuffer,
    const VkRenderingInfo*                      pRenderingInfo),
(commandBuffer, pRenderingInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdEndRenderingKHR,(
    VkCommandBuffer                             commandBuffer),
(commandBuffer));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceFeatures2KHR,(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceFeatures2*                  pFeatures),
(physicalDevice, pFeatures));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceProperties2KHR,(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceProperties2*                pProperties),
(physicalDevice, pProperties));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceFormatProperties2KHR,(
    VkPhysicalDevice                            physicalDevice,
    VkFormat                                    format,
    VkFormatProperties2*                        pFormatProperties),
(physicalDevice, format, pFormatProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceImageFormatProperties2KHR,(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceImageFormatInfo2*     pImageFormatInfo,
    VkImageFormatProperties2*                   pImageFormatProperties),
(physicalDevice, pImageFormatInfo, pImageFormatProperties));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceQueueFamilyProperties2KHR,(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pQueueFamilyPropertyCount,
    VkQueueFamilyProperties2*                   pQueueFamilyProperties),
(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceMemoryProperties2KHR,(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceMemoryProperties2*          pMemoryProperties),
(physicalDevice, pMemoryProperties));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceSparseImageFormatProperties2KHR,(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo,
    uint32_t*                                   pPropertyCount,
    VkSparseImageFormatProperties2*             pProperties),
(physicalDevice, pFormatInfo, pPropertyCount, pProperties));

YKM22_VULKAN_SYMBOL(
void,vkGetDeviceGroupPeerMemoryFeaturesKHR,(
    VkDevice                                    device,
    uint32_t                                    heapIndex,
    uint32_t                                    localDeviceIndex,
    uint32_t                                    remoteDeviceIndex,
    VkPeerMemoryFeatureFlags*                   pPeerMemoryFeatures),
(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetDeviceMaskKHR,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    deviceMask),
(commandBuffer, deviceMask));

YKM22_VULKAN_SYMBOL(
void,vkCmdDispatchBaseKHR,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    baseGroupX,
    uint32_t                                    baseGroupY,
    uint32_t                                    baseGroupZ,
    uint32_t                                    groupCountX,
    uint32_t                                    groupCountY,
    uint32_t                                    groupCountZ),
(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ));

YKM22_VULKAN_SYMBOL(
void,vkTrimCommandPoolKHR,(
    VkDevice                                    device,
    VkCommandPool                               commandPool,
    VkCommandPoolTrimFlags                      flags),
(device, commandPool, flags));

YKM22_VULKAN_SYMBOL(
VkResult,vkEnumeratePhysicalDeviceGroupsKHR,(
    VkInstance                                  instance,
    uint32_t*                                   pPhysicalDeviceGroupCount,
    VkPhysicalDeviceGroupProperties*            pPhysicalDeviceGroupProperties),
(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceExternalBufferPropertiesKHR,(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceExternalBufferInfo*   pExternalBufferInfo,
    VkExternalBufferProperties*                 pExternalBufferProperties),
(physicalDevice, pExternalBufferInfo, pExternalBufferProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetMemoryFdKHR,(
    VkDevice                                    device,
    const VkMemoryGetFdInfoKHR*                 pGetFdInfo,
    int*                                        pFd),
(device, pGetFdInfo, pFd));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetMemoryFdPropertiesKHR,(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    int                                         fd,
    VkMemoryFdPropertiesKHR*                    pMemoryFdProperties),
(device, handleType, fd, pMemoryFdProperties));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceExternalSemaphorePropertiesKHR,(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo,
    VkExternalSemaphoreProperties*              pExternalSemaphoreProperties),
(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkImportSemaphoreFdKHR,(
    VkDevice                                    device,
    const VkImportSemaphoreFdInfoKHR*           pImportSemaphoreFdInfo),
(device, pImportSemaphoreFdInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetSemaphoreFdKHR,(
    VkDevice                                    device,
    const VkSemaphoreGetFdInfoKHR*              pGetFdInfo,
    int*                                        pFd),
(device, pGetFdInfo, pFd));

YKM22_VULKAN_SYMBOL(
void,vkCmdPushDescriptorSetKHR,(
    VkCommandBuffer                             commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    VkPipelineLayout                            layout,
    uint32_t                                    set,
    uint32_t                                    descriptorWriteCount,
    const VkWriteDescriptorSet*                 pDescriptorWrites),
(commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites));

YKM22_VULKAN_SYMBOL(
void,vkCmdPushDescriptorSetWithTemplateKHR,(
    VkCommandBuffer                             commandBuffer,
    VkDescriptorUpdateTemplate                  descriptorUpdateTemplate,
    VkPipelineLayout                            layout,
    uint32_t                                    set,
    const void*                                 pData),
(commandBuffer, descriptorUpdateTemplate, layout, set, pData));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateDescriptorUpdateTemplateKHR,(
    VkDevice                                    device,
    const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDescriptorUpdateTemplate*                 pDescriptorUpdateTemplate),
(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate));

YKM22_VULKAN_SYMBOL(
void,vkDestroyDescriptorUpdateTemplateKHR,(
    VkDevice                                    device,
    VkDescriptorUpdateTemplate                  descriptorUpdateTemplate,
    const VkAllocationCallbacks*                pAllocator),
(device, descriptorUpdateTemplate, pAllocator));

YKM22_VULKAN_SYMBOL(
void,vkUpdateDescriptorSetWithTemplateKHR,(
    VkDevice                                    device,
    VkDescriptorSet                             descriptorSet,
    VkDescriptorUpdateTemplate                  descriptorUpdateTemplate,
    const void*                                 pData),
(device, descriptorSet, descriptorUpdateTemplate, pData));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateRenderPass2KHR,(
    VkDevice                                    device,
    const VkRenderPassCreateInfo2*              pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkRenderPass*                               pRenderPass),
(device, pCreateInfo, pAllocator, pRenderPass));

YKM22_VULKAN_SYMBOL(
void,vkCmdBeginRenderPass2KHR,(
    VkCommandBuffer                             commandBuffer,
    const VkRenderPassBeginInfo*                pRenderPassBegin,
    const VkSubpassBeginInfo*                   pSubpassBeginInfo),
(commandBuffer, pRenderPassBegin, pSubpassBeginInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdNextSubpass2KHR,(
    VkCommandBuffer                             commandBuffer,
    const VkSubpassBeginInfo*                   pSubpassBeginInfo,
    const VkSubpassEndInfo*                     pSubpassEndInfo),
(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdEndRenderPass2KHR,(
    VkCommandBuffer                             commandBuffer,
    const VkSubpassEndInfo*                     pSubpassEndInfo),
(commandBuffer, pSubpassEndInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetSwapchainStatusKHR,(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain),
(device, swapchain));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceExternalFencePropertiesKHR,(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceExternalFenceInfo*    pExternalFenceInfo,
    VkExternalFenceProperties*                  pExternalFenceProperties),
(physicalDevice, pExternalFenceInfo, pExternalFenceProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkImportFenceFdKHR,(
    VkDevice                                    device,
    const VkImportFenceFdInfoKHR*               pImportFenceFdInfo),
(device, pImportFenceFdInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetFenceFdKHR,(
    VkDevice                                    device,
    const VkFenceGetFdInfoKHR*                  pGetFdInfo,
    int*                                        pFd),
(device, pGetFdInfo, pFd));

YKM22_VULKAN_SYMBOL(
VkResult,vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR,(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    uint32_t*                                   pCounterCount,
    VkPerformanceCounterKHR*                    pCounters,
    VkPerformanceCounterDescriptionKHR*         pCounterDescriptions),
(physicalDevice, queueFamilyIndex, pCounterCount, pCounters, pCounterDescriptions));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR,(
    VkPhysicalDevice                            physicalDevice,
    const VkQueryPoolPerformanceCreateInfoKHR*  pPerformanceQueryCreateInfo,
    uint32_t*                                   pNumPasses),
(physicalDevice, pPerformanceQueryCreateInfo, pNumPasses));

YKM22_VULKAN_SYMBOL(
VkResult,vkAcquireProfilingLockKHR,(
    VkDevice                                    device,
    const VkAcquireProfilingLockInfoKHR*        pInfo),
(device, pInfo));

YKM22_VULKAN_SYMBOL(
void,vkReleaseProfilingLockKHR,(
    VkDevice                                    device),
(device));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceSurfaceCapabilities2KHR,(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    VkSurfaceCapabilities2KHR*                  pSurfaceCapabilities),
(physicalDevice, pSurfaceInfo, pSurfaceCapabilities));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceSurfaceFormats2KHR,(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    uint32_t*                                   pSurfaceFormatCount,
    VkSurfaceFormat2KHR*                        pSurfaceFormats),
(physicalDevice, pSurfaceInfo, pSurfaceFormatCount, pSurfaceFormats));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceDisplayProperties2KHR,(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pPropertyCount,
    VkDisplayProperties2KHR*                    pProperties),
(physicalDevice, pPropertyCount, pProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceDisplayPlaneProperties2KHR,(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pPropertyCount,
    VkDisplayPlaneProperties2KHR*               pProperties),
(physicalDevice, pPropertyCount, pProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetDisplayModeProperties2KHR,(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display,
    uint32_t*                                   pPropertyCount,
    VkDisplayModeProperties2KHR*                pProperties),
(physicalDevice, display, pPropertyCount, pProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetDisplayPlaneCapabilities2KHR,(
    VkPhysicalDevice                            physicalDevice,
    const VkDisplayPlaneInfo2KHR*               pDisplayPlaneInfo,
    VkDisplayPlaneCapabilities2KHR*             pCapabilities),
(physicalDevice, pDisplayPlaneInfo, pCapabilities));

YKM22_VULKAN_SYMBOL(
void,vkGetImageMemoryRequirements2KHR,(
    VkDevice                                    device,
    const VkImageMemoryRequirementsInfo2*       pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements),
(device, pInfo, pMemoryRequirements));

YKM22_VULKAN_SYMBOL(
void,vkGetBufferMemoryRequirements2KHR,(
    VkDevice                                    device,
    const VkBufferMemoryRequirementsInfo2*      pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements),
(device, pInfo, pMemoryRequirements));

YKM22_VULKAN_SYMBOL(
void,vkGetImageSparseMemoryRequirements2KHR,(
    VkDevice                                    device,
    const VkImageSparseMemoryRequirementsInfo2* pInfo,
    uint32_t*                                   pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2*           pSparseMemoryRequirements),
(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateSamplerYcbcrConversionKHR,(
    VkDevice                                    device,
    const VkSamplerYcbcrConversionCreateInfo*   pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSamplerYcbcrConversion*                   pYcbcrConversion),
(device, pCreateInfo, pAllocator, pYcbcrConversion));

YKM22_VULKAN_SYMBOL(
void,vkDestroySamplerYcbcrConversionKHR,(
    VkDevice                                    device,
    VkSamplerYcbcrConversion                    ycbcrConversion,
    const VkAllocationCallbacks*                pAllocator),
(device, ycbcrConversion, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkBindBufferMemory2KHR,(
    VkDevice                                    device,
    uint32_t                                    bindInfoCount,
    const VkBindBufferMemoryInfo*               pBindInfos),
(device, bindInfoCount, pBindInfos));

YKM22_VULKAN_SYMBOL(
VkResult,vkBindImageMemory2KHR,(
    VkDevice                                    device,
    uint32_t                                    bindInfoCount,
    const VkBindImageMemoryInfo*                pBindInfos),
(device, bindInfoCount, pBindInfos));

YKM22_VULKAN_SYMBOL(
void,vkGetDescriptorSetLayoutSupportKHR,(
    VkDevice                                    device,
    const VkDescriptorSetLayoutCreateInfo*      pCreateInfo,
    VkDescriptorSetLayoutSupport*               pSupport),
(device, pCreateInfo, pSupport));

YKM22_VULKAN_SYMBOL(
void,vkCmdDrawIndirectCountKHR,(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    VkBuffer                                    countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride),
(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride));

YKM22_VULKAN_SYMBOL(
void,vkCmdDrawIndexedIndirectCountKHR,(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    VkBuffer                                    countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride),
(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetSemaphoreCounterValueKHR,(
    VkDevice                                    device,
    VkSemaphore                                 semaphore,
    uint64_t*                                   pValue),
(device, semaphore, pValue));

YKM22_VULKAN_SYMBOL(
VkResult,vkWaitSemaphoresKHR,(
    VkDevice                                    device,
    const VkSemaphoreWaitInfo*                  pWaitInfo,
    uint64_t                                    timeout),
(device, pWaitInfo, timeout));

YKM22_VULKAN_SYMBOL(
VkResult,vkSignalSemaphoreKHR,(
    VkDevice                                    device,
    const VkSemaphoreSignalInfo*                pSignalInfo),
(device, pSignalInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceFragmentShadingRatesKHR,(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pFragmentShadingRateCount,
    VkPhysicalDeviceFragmentShadingRateKHR*     pFragmentShadingRates),
(physicalDevice, pFragmentShadingRateCount, pFragmentShadingRates));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetFragmentShadingRateKHR,(
    VkCommandBuffer                             commandBuffer,
    const VkExtent2D*                           pFragmentSize,
    const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]),
(commandBuffer, pFragmentSize, combinerOps));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetRenderingAttachmentLocationsKHR,(
    VkCommandBuffer                             commandBuffer,
    const VkRenderingAttachmentLocationInfoKHR* pLocationInfo),
(commandBuffer, pLocationInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetRenderingInputAttachmentIndicesKHR,(
    VkCommandBuffer                             commandBuffer,
    const VkRenderingInputAttachmentIndexInfoKHR* pLocationInfo),
(commandBuffer, pLocationInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkWaitForPresentKHR,(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    uint64_t                                    presentId,
    uint64_t                                    timeout),
(device, swapchain, presentId, timeout));

YKM22_VULKAN_SYMBOL(
VkDeviceAddress,vkGetBufferDeviceAddressKHR,(
    VkDevice                                    device,
    const VkBufferDeviceAddressInfo*            pInfo),
(device, pInfo));

YKM22_VULKAN_SYMBOL(
uint64_t,vkGetBufferOpaqueCaptureAddressKHR,(
    VkDevice                                    device,
    const VkBufferDeviceAddressInfo*            pInfo),
(device, pInfo));

YKM22_VULKAN_SYMBOL(
uint64_t,vkGetDeviceMemoryOpaqueCaptureAddressKHR,(
    VkDevice                                    device,
    const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo),
(device, pInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateDeferredOperationKHR,(
    VkDevice                                    device,
    const VkAllocationCallbacks*                pAllocator,
    VkDeferredOperationKHR*                     pDeferredOperation),
(device, pAllocator, pDeferredOperation));

YKM22_VULKAN_SYMBOL(
void,vkDestroyDeferredOperationKHR,(
    VkDevice                                    device,
    VkDeferredOperationKHR                      operation,
    const VkAllocationCallbacks*                pAllocator),
(device, operation, pAllocator));

YKM22_VULKAN_SYMBOL(
uint32_t,vkGetDeferredOperationMaxConcurrencyKHR,(
    VkDevice                                    device,
    VkDeferredOperationKHR                      operation),
(device, operation));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetDeferredOperationResultKHR,(
    VkDevice                                    device,
    VkDeferredOperationKHR                      operation),
(device, operation));

YKM22_VULKAN_SYMBOL(
VkResult,vkDeferredOperationJoinKHR,(
    VkDevice                                    device,
    VkDeferredOperationKHR                      operation),
(device, operation));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPipelineExecutablePropertiesKHR,(
    VkDevice                                    device,
    const VkPipelineInfoKHR*                    pPipelineInfo,
    uint32_t*                                   pExecutableCount,
    VkPipelineExecutablePropertiesKHR*          pProperties),
(device, pPipelineInfo, pExecutableCount, pProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPipelineExecutableStatisticsKHR,(
    VkDevice                                    device,
    const VkPipelineExecutableInfoKHR*          pExecutableInfo,
    uint32_t*                                   pStatisticCount,
    VkPipelineExecutableStatisticKHR*           pStatistics),
(device, pExecutableInfo, pStatisticCount, pStatistics));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPipelineExecutableInternalRepresentationsKHR,(
    VkDevice                                    device,
    const VkPipelineExecutableInfoKHR*          pExecutableInfo,
    uint32_t*                                   pInternalRepresentationCount,
    VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations),
(device, pExecutableInfo, pInternalRepresentationCount, pInternalRepresentations));

YKM22_VULKAN_SYMBOL(
VkResult,vkMapMemory2KHR,(
    VkDevice                                    device,
    const VkMemoryMapInfoKHR*                   pMemoryMapInfo,
    void**                                      ppData),
(device, pMemoryMapInfo, ppData));

YKM22_VULKAN_SYMBOL(
VkResult,vkUnmapMemory2KHR,(
    VkDevice                                    device,
    const VkMemoryUnmapInfoKHR*                 pMemoryUnmapInfo),
(device, pMemoryUnmapInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR,(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceVideoEncodeQualityLevelInfoKHR* pQualityLevelInfo,
    VkVideoEncodeQualityLevelPropertiesKHR*     pQualityLevelProperties),
(physicalDevice, pQualityLevelInfo, pQualityLevelProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetEncodedVideoSessionParametersKHR,(
    VkDevice                                    device,
    const VkVideoEncodeSessionParametersGetInfoKHR* pVideoSessionParametersInfo,
    VkVideoEncodeSessionParametersFeedbackInfoKHR* pFeedbackInfo,
    size_t*                                     pDataSize,
    void*                                       pData),
(device, pVideoSessionParametersInfo, pFeedbackInfo, pDataSize, pData));

YKM22_VULKAN_SYMBOL(
void,vkCmdEncodeVideoKHR,(
    VkCommandBuffer                             commandBuffer,
    const VkVideoEncodeInfoKHR*                 pEncodeInfo),
(commandBuffer, pEncodeInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetEvent2KHR,(
    VkCommandBuffer                             commandBuffer,
    VkEvent                                     event,
    const VkDependencyInfo*                     pDependencyInfo),
(commandBuffer, event, pDependencyInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdResetEvent2KHR,(
    VkCommandBuffer                             commandBuffer,
    VkEvent                                     event,
    VkPipelineStageFlags2                       stageMask),
(commandBuffer, event, stageMask));

YKM22_VULKAN_SYMBOL(
void,vkCmdWaitEvents2KHR,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    eventCount,
    const VkEvent*                              pEvents,
    const VkDependencyInfo*                     pDependencyInfos),
(commandBuffer, eventCount, pEvents, pDependencyInfos));

YKM22_VULKAN_SYMBOL(
void,vkCmdPipelineBarrier2KHR,(
    VkCommandBuffer                             commandBuffer,
    const VkDependencyInfo*                     pDependencyInfo),
(commandBuffer, pDependencyInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdWriteTimestamp2KHR,(
    VkCommandBuffer                             commandBuffer,
    VkPipelineStageFlags2                       stage,
    VkQueryPool                                 queryPool,
    uint32_t                                    query),
(commandBuffer, stage, queryPool, query));

YKM22_VULKAN_SYMBOL(
VkResult,vkQueueSubmit2KHR,(
    VkQueue                                     queue,
    uint32_t                                    submitCount,
    const VkSubmitInfo2*                        pSubmits,
    VkFence                                     fence),
(queue, submitCount, pSubmits, fence));

YKM22_VULKAN_SYMBOL(
void,vkCmdWriteBufferMarker2AMD,(
    VkCommandBuffer                             commandBuffer,
    VkPipelineStageFlags2                       stage,
    VkBuffer                                    dstBuffer,
    VkDeviceSize                                dstOffset,
    uint32_t                                    marker),
(commandBuffer, stage, dstBuffer, dstOffset, marker));

YKM22_VULKAN_SYMBOL(
void,vkGetQueueCheckpointData2NV,(
    VkQueue                                     queue,
    uint32_t*                                   pCheckpointDataCount,
    VkCheckpointData2NV*                        pCheckpointData),
(queue, pCheckpointDataCount, pCheckpointData));

YKM22_VULKAN_SYMBOL(
void,vkCmdCopyBuffer2KHR,(
    VkCommandBuffer                             commandBuffer,
    const VkCopyBufferInfo2*                    pCopyBufferInfo),
(commandBuffer, pCopyBufferInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdCopyImage2KHR,(
    VkCommandBuffer                             commandBuffer,
    const VkCopyImageInfo2*                     pCopyImageInfo),
(commandBuffer, pCopyImageInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdCopyBufferToImage2KHR,(
    VkCommandBuffer                             commandBuffer,
    const VkCopyBufferToImageInfo2*             pCopyBufferToImageInfo),
(commandBuffer, pCopyBufferToImageInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdCopyImageToBuffer2KHR,(
    VkCommandBuffer                             commandBuffer,
    const VkCopyImageToBufferInfo2*             pCopyImageToBufferInfo),
(commandBuffer, pCopyImageToBufferInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdBlitImage2KHR,(
    VkCommandBuffer                             commandBuffer,
    const VkBlitImageInfo2*                     pBlitImageInfo),
(commandBuffer, pBlitImageInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdResolveImage2KHR,(
    VkCommandBuffer                             commandBuffer,
    const VkResolveImageInfo2*                  pResolveImageInfo),
(commandBuffer, pResolveImageInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdTraceRaysIndirect2KHR,(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             indirectDeviceAddress),
(commandBuffer, indirectDeviceAddress));

YKM22_VULKAN_SYMBOL(
void,vkGetDeviceBufferMemoryRequirementsKHR,(
    VkDevice                                    device,
    const VkDeviceBufferMemoryRequirements*     pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements),
(device, pInfo, pMemoryRequirements));

YKM22_VULKAN_SYMBOL(
void,vkGetDeviceImageMemoryRequirementsKHR,(
    VkDevice                                    device,
    const VkDeviceImageMemoryRequirements*      pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements),
(device, pInfo, pMemoryRequirements));

YKM22_VULKAN_SYMBOL(
void,vkGetDeviceImageSparseMemoryRequirementsKHR,(
    VkDevice                                    device,
    const VkDeviceImageMemoryRequirements*      pInfo,
    uint32_t*                                   pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2*           pSparseMemoryRequirements),
(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements));

YKM22_VULKAN_SYMBOL(
void,vkCmdBindIndexBuffer2KHR,(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    VkDeviceSize                                size,
    VkIndexType                                 indexType),
(commandBuffer, buffer, offset, size, indexType));

YKM22_VULKAN_SYMBOL(
void,vkGetRenderingAreaGranularityKHR,(
    VkDevice                                    device,
    const VkRenderingAreaInfoKHR*               pRenderingAreaInfo,
    VkExtent2D*                                 pGranularity),
(device, pRenderingAreaInfo, pGranularity));

YKM22_VULKAN_SYMBOL(
void,vkGetDeviceImageSubresourceLayoutKHR,(
    VkDevice                                    device,
    const VkDeviceImageSubresourceInfoKHR*      pInfo,
    VkSubresourceLayout2KHR*                    pLayout),
(device, pInfo, pLayout));

YKM22_VULKAN_SYMBOL(
void,vkGetImageSubresourceLayout2KHR,(
    VkDevice                                    device,
    VkImage                                     image,
    const VkImageSubresource2KHR*               pSubresource,
    VkSubresourceLayout2KHR*                    pLayout),
(device, image, pSubresource, pLayout));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR,(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pPropertyCount,
    VkCooperativeMatrixPropertiesKHR*           pProperties),
(physicalDevice, pPropertyCount, pProperties));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetLineStippleKHR,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    lineStippleFactor,
    uint16_t                                    lineStipplePattern),
(commandBuffer, lineStippleFactor, lineStipplePattern));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceCalibrateableTimeDomainsKHR,(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pTimeDomainCount,
    VkTimeDomainKHR*                            pTimeDomains),
(physicalDevice, pTimeDomainCount, pTimeDomains));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetCalibratedTimestampsKHR,(
    VkDevice                                    device,
    uint32_t                                    timestampCount,
    const VkCalibratedTimestampInfoKHR*         pTimestampInfos,
    uint64_t*                                   pTimestamps,
    uint64_t*                                   pMaxDeviation),
(device, timestampCount, pTimestampInfos, pTimestamps, pMaxDeviation));

YKM22_VULKAN_SYMBOL(
void,vkCmdBindDescriptorSets2KHR,(
    VkCommandBuffer                             commandBuffer,
    const VkBindDescriptorSetsInfoKHR*          pBindDescriptorSetsInfo),
(commandBuffer, pBindDescriptorSetsInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdPushConstants2KHR,(
    VkCommandBuffer                             commandBuffer,
    const VkPushConstantsInfoKHR*               pPushConstantsInfo),
(commandBuffer, pPushConstantsInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdPushDescriptorSet2KHR,(
    VkCommandBuffer                             commandBuffer,
    const VkPushDescriptorSetInfoKHR*           pPushDescriptorSetInfo),
(commandBuffer, pPushDescriptorSetInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdPushDescriptorSetWithTemplate2KHR,(
    VkCommandBuffer                             commandBuffer,
    const VkPushDescriptorSetWithTemplateInfoKHR* pPushDescriptorSetWithTemplateInfo),
(commandBuffer, pPushDescriptorSetWithTemplateInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetDescriptorBufferOffsets2EXT,(
    VkCommandBuffer                             commandBuffer,
    const VkSetDescriptorBufferOffsetsInfoEXT*  pSetDescriptorBufferOffsetsInfo),
(commandBuffer, pSetDescriptorBufferOffsetsInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdBindDescriptorBufferEmbeddedSamplers2EXT,(
    VkCommandBuffer                             commandBuffer,
    const VkBindDescriptorBufferEmbeddedSamplersInfoEXT* pBindDescriptorBufferEmbeddedSamplersInfo),
(commandBuffer, pBindDescriptorBufferEmbeddedSamplersInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateDebugReportCallbackEXT,(
    VkInstance                                  instance,
    const VkDebugReportCallbackCreateInfoEXT*   pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDebugReportCallbackEXT*                   pCallback),
(instance, pCreateInfo, pAllocator, pCallback));

YKM22_VULKAN_SYMBOL(
void,vkDestroyDebugReportCallbackEXT,(
    VkInstance                                  instance,
    VkDebugReportCallbackEXT                    callback,
    const VkAllocationCallbacks*                pAllocator),
(instance, callback, pAllocator));

YKM22_VULKAN_SYMBOL(
void,vkDebugReportMessageEXT,(
    VkInstance                                  instance,
    VkDebugReportFlagsEXT                       flags,
    VkDebugReportObjectTypeEXT                  objectType,
    uint64_t                                    object,
    size_t                                      location,
    int32_t                                     messageCode,
    const char*                                 pLayerPrefix,
    const char*                                 pMessage),
(instance, flags, objectType, object, location, messageCode, pLayerPrefix, pMessage));

YKM22_VULKAN_SYMBOL(
VkResult,vkDebugMarkerSetObjectTagEXT,(
    VkDevice                                    device,
    const VkDebugMarkerObjectTagInfoEXT*        pTagInfo),
(device, pTagInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkDebugMarkerSetObjectNameEXT,(
    VkDevice                                    device,
    const VkDebugMarkerObjectNameInfoEXT*       pNameInfo),
(device, pNameInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdDebugMarkerBeginEXT,(
    VkCommandBuffer                             commandBuffer,
    const VkDebugMarkerMarkerInfoEXT*           pMarkerInfo),
(commandBuffer, pMarkerInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdDebugMarkerEndEXT,(
    VkCommandBuffer                             commandBuffer),
(commandBuffer));

YKM22_VULKAN_SYMBOL(
void,vkCmdDebugMarkerInsertEXT,(
    VkCommandBuffer                             commandBuffer,
    const VkDebugMarkerMarkerInfoEXT*           pMarkerInfo),
(commandBuffer, pMarkerInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdBindTransformFeedbackBuffersEXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstBinding,
    uint32_t                                    bindingCount,
    const VkBuffer*                             pBuffers,
    const VkDeviceSize*                         pOffsets,
    const VkDeviceSize*                         pSizes),
(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes));

YKM22_VULKAN_SYMBOL(
void,vkCmdBeginTransformFeedbackEXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstCounterBuffer,
    uint32_t                                    counterBufferCount,
    const VkBuffer*                             pCounterBuffers,
    const VkDeviceSize*                         pCounterBufferOffsets),
(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets));

YKM22_VULKAN_SYMBOL(
void,vkCmdEndTransformFeedbackEXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstCounterBuffer,
    uint32_t                                    counterBufferCount,
    const VkBuffer*                             pCounterBuffers,
    const VkDeviceSize*                         pCounterBufferOffsets),
(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets));

YKM22_VULKAN_SYMBOL(
void,vkCmdBeginQueryIndexedEXT,(
    VkCommandBuffer                             commandBuffer,
    VkQueryPool                                 queryPool,
    uint32_t                                    query,
    VkQueryControlFlags                         flags,
    uint32_t                                    index),
(commandBuffer, queryPool, query, flags, index));

YKM22_VULKAN_SYMBOL(
void,vkCmdEndQueryIndexedEXT,(
    VkCommandBuffer                             commandBuffer,
    VkQueryPool                                 queryPool,
    uint32_t                                    query,
    uint32_t                                    index),
(commandBuffer, queryPool, query, index));

YKM22_VULKAN_SYMBOL(
void,vkCmdDrawIndirectByteCountEXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    instanceCount,
    uint32_t                                    firstInstance,
    VkBuffer                                    counterBuffer,
    VkDeviceSize                                counterBufferOffset,
    uint32_t                                    counterOffset,
    uint32_t                                    vertexStride),
(commandBuffer, instanceCount, firstInstance, counterBuffer, counterBufferOffset, counterOffset, vertexStride));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateCuModuleNVX,(
    VkDevice                                    device,
    const VkCuModuleCreateInfoNVX*              pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkCuModuleNVX*                              pModule),
(device, pCreateInfo, pAllocator, pModule));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateCuFunctionNVX,(
    VkDevice                                    device,
    const VkCuFunctionCreateInfoNVX*            pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkCuFunctionNVX*                            pFunction),
(device, pCreateInfo, pAllocator, pFunction));

YKM22_VULKAN_SYMBOL(
void,vkDestroyCuModuleNVX,(
    VkDevice                                    device,
    VkCuModuleNVX                               module,
    const VkAllocationCallbacks*                pAllocator),
(device, module, pAllocator));

YKM22_VULKAN_SYMBOL(
void,vkDestroyCuFunctionNVX,(
    VkDevice                                    device,
    VkCuFunctionNVX                             function,
    const VkAllocationCallbacks*                pAllocator),
(device, function, pAllocator));

YKM22_VULKAN_SYMBOL(
void,vkCmdCuLaunchKernelNVX,(
    VkCommandBuffer                             commandBuffer,
    const VkCuLaunchInfoNVX*                    pLaunchInfo),
(commandBuffer, pLaunchInfo));

YKM22_VULKAN_SYMBOL(
uint32_t,vkGetImageViewHandleNVX,(
    VkDevice                                    device,
    const VkImageViewHandleInfoNVX*             pInfo),
(device, pInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetImageViewAddressNVX,(
    VkDevice                                    device,
    VkImageView                                 imageView,
    VkImageViewAddressPropertiesNVX*            pProperties),
(device, imageView, pProperties));

YKM22_VULKAN_SYMBOL(
void,vkCmdDrawIndirectCountAMD,(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    VkBuffer                                    countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride),
(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride));

YKM22_VULKAN_SYMBOL(
void,vkCmdDrawIndexedIndirectCountAMD,(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    VkBuffer                                    countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride),
(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetShaderInfoAMD,(
    VkDevice                                    device,
    VkPipeline                                  pipeline,
    VkShaderStageFlagBits                       shaderStage,
    VkShaderInfoTypeAMD                         infoType,
    size_t*                                     pInfoSize,
    void*                                       pInfo),
(device, pipeline, shaderStage, infoType, pInfoSize, pInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceExternalImageFormatPropertiesNV,(
    VkPhysicalDevice                            physicalDevice,
    VkFormat                                    format,
    VkImageType                                 type,
    VkImageTiling                               tiling,
    VkImageUsageFlags                           usage,
    VkImageCreateFlags                          flags,
    VkExternalMemoryHandleTypeFlagsNV           externalHandleType,
    VkExternalImageFormatPropertiesNV*          pExternalImageFormatProperties),
(physicalDevice, format, type, tiling, usage, flags, externalHandleType, pExternalImageFormatProperties));

YKM22_VULKAN_SYMBOL(
void,vkCmdBeginConditionalRenderingEXT,(
    VkCommandBuffer                             commandBuffer,
    const VkConditionalRenderingBeginInfoEXT*   pConditionalRenderingBegin),
(commandBuffer, pConditionalRenderingBegin));

YKM22_VULKAN_SYMBOL(
void,vkCmdEndConditionalRenderingEXT,(
    VkCommandBuffer                             commandBuffer),
(commandBuffer));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetViewportWScalingNV,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstViewport,
    uint32_t                                    viewportCount,
    const VkViewportWScalingNV*                 pViewportWScalings),
(commandBuffer, firstViewport, viewportCount, pViewportWScalings));

YKM22_VULKAN_SYMBOL(
VkResult,vkReleaseDisplayEXT,(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display),
(physicalDevice, display));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceSurfaceCapabilities2EXT,(
    VkPhysicalDevice                            physicalDevice,
    VkSurfaceKHR                                surface,
    VkSurfaceCapabilities2EXT*                  pSurfaceCapabilities),
(physicalDevice, surface, pSurfaceCapabilities));

YKM22_VULKAN_SYMBOL(
VkResult,vkDisplayPowerControlEXT,(
    VkDevice                                    device,
    VkDisplayKHR                                display,
    const VkDisplayPowerInfoEXT*                pDisplayPowerInfo),
(device, display, pDisplayPowerInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkRegisterDeviceEventEXT,(
    VkDevice                                    device,
    const VkDeviceEventInfoEXT*                 pDeviceEventInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkFence*                                    pFence),
(device, pDeviceEventInfo, pAllocator, pFence));

YKM22_VULKAN_SYMBOL(
VkResult,vkRegisterDisplayEventEXT,(
    VkDevice                                    device,
    VkDisplayKHR                                display,
    const VkDisplayEventInfoEXT*                pDisplayEventInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkFence*                                    pFence),
(device, display, pDisplayEventInfo, pAllocator, pFence));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetSwapchainCounterEXT,(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    VkSurfaceCounterFlagBitsEXT                 counter,
    uint64_t*                                   pCounterValue),
(device, swapchain, counter, pCounterValue));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetRefreshCycleDurationGOOGLE,(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    VkRefreshCycleDurationGOOGLE*               pDisplayTimingProperties),
(device, swapchain, pDisplayTimingProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPastPresentationTimingGOOGLE,(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    uint32_t*                                   pPresentationTimingCount,
    VkPastPresentationTimingGOOGLE*             pPresentationTimings),
(device, swapchain, pPresentationTimingCount, pPresentationTimings));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetDiscardRectangleEXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstDiscardRectangle,
    uint32_t                                    discardRectangleCount,
    const VkRect2D*                             pDiscardRectangles),
(commandBuffer, firstDiscardRectangle, discardRectangleCount, pDiscardRectangles));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetDiscardRectangleEnableEXT,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    discardRectangleEnable),
(commandBuffer, discardRectangleEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetDiscardRectangleModeEXT,(
    VkCommandBuffer                             commandBuffer,
    VkDiscardRectangleModeEXT                   discardRectangleMode),
(commandBuffer, discardRectangleMode));

YKM22_VULKAN_SYMBOL(
void,vkSetHdrMetadataEXT,(
    VkDevice                                    device,
    uint32_t                                    swapchainCount,
    const VkSwapchainKHR*                       pSwapchains,
    const VkHdrMetadataEXT*                     pMetadata),
(device, swapchainCount, pSwapchains, pMetadata));

YKM22_VULKAN_SYMBOL(
VkResult,vkSetDebugUtilsObjectNameEXT,(
    VkDevice                                    device,
    const VkDebugUtilsObjectNameInfoEXT*        pNameInfo),
(device, pNameInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkSetDebugUtilsObjectTagEXT,(
    VkDevice                                    device,
    const VkDebugUtilsObjectTagInfoEXT*         pTagInfo),
(device, pTagInfo));

YKM22_VULKAN_SYMBOL(
void,vkQueueBeginDebugUtilsLabelEXT,(
    VkQueue                                     queue,
    const VkDebugUtilsLabelEXT*                 pLabelInfo),
(queue, pLabelInfo));

YKM22_VULKAN_SYMBOL(
void,vkQueueEndDebugUtilsLabelEXT,(
    VkQueue                                     queue),
(queue));

YKM22_VULKAN_SYMBOL(
void,vkQueueInsertDebugUtilsLabelEXT,(
    VkQueue                                     queue,
    const VkDebugUtilsLabelEXT*                 pLabelInfo),
(queue, pLabelInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdBeginDebugUtilsLabelEXT,(
    VkCommandBuffer                             commandBuffer,
    const VkDebugUtilsLabelEXT*                 pLabelInfo),
(commandBuffer, pLabelInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdEndDebugUtilsLabelEXT,(
    VkCommandBuffer                             commandBuffer),
(commandBuffer));

YKM22_VULKAN_SYMBOL(
void,vkCmdInsertDebugUtilsLabelEXT,(
    VkCommandBuffer                             commandBuffer,
    const VkDebugUtilsLabelEXT*                 pLabelInfo),
(commandBuffer, pLabelInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateDebugUtilsMessengerEXT,(
    VkInstance                                  instance,
    const VkDebugUtilsMessengerCreateInfoEXT*   pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDebugUtilsMessengerEXT*                   pMessenger),
(instance, pCreateInfo, pAllocator, pMessenger));

YKM22_VULKAN_SYMBOL(
void,vkDestroyDebugUtilsMessengerEXT,(
    VkInstance                                  instance,
    VkDebugUtilsMessengerEXT                    messenger,
    const VkAllocationCallbacks*                pAllocator),
(instance, messenger, pAllocator));

YKM22_VULKAN_SYMBOL(
void,vkSubmitDebugUtilsMessageEXT,(
    VkInstance                                  instance,
    VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT             messageTypes,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData),
(instance, messageSeverity, messageTypes, pCallbackData));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetSampleLocationsEXT,(
    VkCommandBuffer                             commandBuffer,
    const VkSampleLocationsInfoEXT*             pSampleLocationsInfo),
(commandBuffer, pSampleLocationsInfo));

YKM22_VULKAN_SYMBOL(
void,vkGetPhysicalDeviceMultisamplePropertiesEXT,(
    VkPhysicalDevice                            physicalDevice,
    VkSampleCountFlagBits                       samples,
    VkMultisamplePropertiesEXT*                 pMultisampleProperties),
(physicalDevice, samples, pMultisampleProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetImageDrmFormatModifierPropertiesEXT,(
    VkDevice                                    device,
    VkImage                                     image,
    VkImageDrmFormatModifierPropertiesEXT*      pProperties),
(device, image, pProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateValidationCacheEXT,(
    VkDevice                                    device,
    const VkValidationCacheCreateInfoEXT*       pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkValidationCacheEXT*                       pValidationCache),
(device, pCreateInfo, pAllocator, pValidationCache));

YKM22_VULKAN_SYMBOL(
void,vkDestroyValidationCacheEXT,(
    VkDevice                                    device,
    VkValidationCacheEXT                        validationCache,
    const VkAllocationCallbacks*                pAllocator),
(device, validationCache, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkMergeValidationCachesEXT,(
    VkDevice                                    device,
    VkValidationCacheEXT                        dstCache,
    uint32_t                                    srcCacheCount,
    const VkValidationCacheEXT*                 pSrcCaches),
(device, dstCache, srcCacheCount, pSrcCaches));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetValidationCacheDataEXT,(
    VkDevice                                    device,
    VkValidationCacheEXT                        validationCache,
    size_t*                                     pDataSize,
    void*                                       pData),
(device, validationCache, pDataSize, pData));

YKM22_VULKAN_SYMBOL(
void,vkCmdBindShadingRateImageNV,(
    VkCommandBuffer                             commandBuffer,
    VkImageView                                 imageView,
    VkImageLayout                               imageLayout),
(commandBuffer, imageView, imageLayout));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetViewportShadingRatePaletteNV,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstViewport,
    uint32_t                                    viewportCount,
    const VkShadingRatePaletteNV*               pShadingRatePalettes),
(commandBuffer, firstViewport, viewportCount, pShadingRatePalettes));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetCoarseSampleOrderNV,(
    VkCommandBuffer                             commandBuffer,
    VkCoarseSampleOrderTypeNV                   sampleOrderType,
    uint32_t                                    customSampleOrderCount,
    const VkCoarseSampleOrderCustomNV*          pCustomSampleOrders),
(commandBuffer, sampleOrderType, customSampleOrderCount, pCustomSampleOrders));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateAccelerationStructureNV,(
    VkDevice                                    device,
    const VkAccelerationStructureCreateInfoNV*  pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkAccelerationStructureNV*                  pAccelerationStructure),
(device, pCreateInfo, pAllocator, pAccelerationStructure));

YKM22_VULKAN_SYMBOL(
void,vkDestroyAccelerationStructureNV,(
    VkDevice                                    device,
    VkAccelerationStructureNV                   accelerationStructure,
    const VkAllocationCallbacks*                pAllocator),
(device, accelerationStructure, pAllocator));

YKM22_VULKAN_SYMBOL(
void,vkGetAccelerationStructureMemoryRequirementsNV,(
    VkDevice                                    device,
    const VkAccelerationStructureMemoryRequirementsInfoNV* pInfo,
    VkMemoryRequirements2KHR*                   pMemoryRequirements),
(device, pInfo, pMemoryRequirements));

YKM22_VULKAN_SYMBOL(
VkResult,vkBindAccelerationStructureMemoryNV,(
    VkDevice                                    device,
    uint32_t                                    bindInfoCount,
    const VkBindAccelerationStructureMemoryInfoNV* pBindInfos),
(device, bindInfoCount, pBindInfos));

YKM22_VULKAN_SYMBOL(
void,vkCmdBuildAccelerationStructureNV,(
    VkCommandBuffer                             commandBuffer,
    const VkAccelerationStructureInfoNV*        pInfo,
    VkBuffer                                    instanceData,
    VkDeviceSize                                instanceOffset,
    VkBool32                                    update,
    VkAccelerationStructureNV                   dst,
    VkAccelerationStructureNV                   src,
    VkBuffer                                    scratch,
    VkDeviceSize                                scratchOffset),
(commandBuffer, pInfo, instanceData, instanceOffset, update, dst, src, scratch, scratchOffset));

YKM22_VULKAN_SYMBOL(
void,vkCmdCopyAccelerationStructureNV,(
    VkCommandBuffer                             commandBuffer,
    VkAccelerationStructureNV                   dst,
    VkAccelerationStructureNV                   src,
    VkCopyAccelerationStructureModeKHR          mode),
(commandBuffer, dst, src, mode));

YKM22_VULKAN_SYMBOL(
void,vkCmdTraceRaysNV,(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    raygenShaderBindingTableBuffer,
    VkDeviceSize                                raygenShaderBindingOffset,
    VkBuffer                                    missShaderBindingTableBuffer,
    VkDeviceSize                                missShaderBindingOffset,
    VkDeviceSize                                missShaderBindingStride,
    VkBuffer                                    hitShaderBindingTableBuffer,
    VkDeviceSize                                hitShaderBindingOffset,
    VkDeviceSize                                hitShaderBindingStride,
    VkBuffer                                    callableShaderBindingTableBuffer,
    VkDeviceSize                                callableShaderBindingOffset,
    VkDeviceSize                                callableShaderBindingStride,
    uint32_t                                    width,
    uint32_t                                    height,
    uint32_t                                    depth),
(commandBuffer, raygenShaderBindingTableBuffer, raygenShaderBindingOffset, missShaderBindingTableBuffer, missShaderBindingOffset, missShaderBindingStride, hitShaderBindingTableBuffer, hitShaderBindingOffset, hitShaderBindingStride, callableShaderBindingTableBuffer, callableShaderBindingOffset, callableShaderBindingStride, width, height, depth));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateRayTracingPipelinesNV,(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    createInfoCount,
    const VkRayTracingPipelineCreateInfoNV*     pCreateInfos,
    const VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines),
(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetRayTracingShaderGroupHandlesKHR,(
    VkDevice                                    device,
    VkPipeline                                  pipeline,
    uint32_t                                    firstGroup,
    uint32_t                                    groupCount,
    size_t                                      dataSize,
    void*                                       pData),
(device, pipeline, firstGroup, groupCount, dataSize, pData));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetRayTracingShaderGroupHandlesNV,(
    VkDevice                                    device,
    VkPipeline                                  pipeline,
    uint32_t                                    firstGroup,
    uint32_t                                    groupCount,
    size_t                                      dataSize,
    void*                                       pData),
(device, pipeline, firstGroup, groupCount, dataSize, pData));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetAccelerationStructureHandleNV,(
    VkDevice                                    device,
    VkAccelerationStructureNV                   accelerationStructure,
    size_t                                      dataSize,
    void*                                       pData),
(device, accelerationStructure, dataSize, pData));

YKM22_VULKAN_SYMBOL(
void,vkCmdWriteAccelerationStructuresPropertiesNV,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    accelerationStructureCount,
    const VkAccelerationStructureNV*            pAccelerationStructures,
    VkQueryType                                 queryType,
    VkQueryPool                                 queryPool,
    uint32_t                                    firstQuery),
(commandBuffer, accelerationStructureCount, pAccelerationStructures, queryType, queryPool, firstQuery));

YKM22_VULKAN_SYMBOL(
VkResult,vkCompileDeferredNV,(
    VkDevice                                    device,
    VkPipeline                                  pipeline,
    uint32_t                                    shader),
(device, pipeline, shader));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetMemoryHostPointerPropertiesEXT,(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    const void*                                 pHostPointer,
    VkMemoryHostPointerPropertiesEXT*           pMemoryHostPointerProperties),
(device, handleType, pHostPointer, pMemoryHostPointerProperties));

YKM22_VULKAN_SYMBOL(
void,vkCmdWriteBufferMarkerAMD,(
    VkCommandBuffer                             commandBuffer,
    VkPipelineStageFlagBits                     pipelineStage,
    VkBuffer                                    dstBuffer,
    VkDeviceSize                                dstOffset,
    uint32_t                                    marker),
(commandBuffer, pipelineStage, dstBuffer, dstOffset, marker));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceCalibrateableTimeDomainsEXT,(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pTimeDomainCount,
    VkTimeDomainKHR*                            pTimeDomains),
(physicalDevice, pTimeDomainCount, pTimeDomains));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetCalibratedTimestampsEXT,(
    VkDevice                                    device,
    uint32_t                                    timestampCount,
    const VkCalibratedTimestampInfoKHR*         pTimestampInfos,
    uint64_t*                                   pTimestamps,
    uint64_t*                                   pMaxDeviation),
(device, timestampCount, pTimestampInfos, pTimestamps, pMaxDeviation));

YKM22_VULKAN_SYMBOL(
void,vkCmdDrawMeshTasksNV,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    taskCount,
    uint32_t                                    firstTask),
(commandBuffer, taskCount, firstTask));

YKM22_VULKAN_SYMBOL(
void,vkCmdDrawMeshTasksIndirectNV,(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    uint32_t                                    drawCount,
    uint32_t                                    stride),
(commandBuffer, buffer, offset, drawCount, stride));

YKM22_VULKAN_SYMBOL(
void,vkCmdDrawMeshTasksIndirectCountNV,(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    VkBuffer                                    countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride),
(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetExclusiveScissorEnableNV,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstExclusiveScissor,
    uint32_t                                    exclusiveScissorCount,
    const VkBool32*                             pExclusiveScissorEnables),
(commandBuffer, firstExclusiveScissor, exclusiveScissorCount, pExclusiveScissorEnables));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetExclusiveScissorNV,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstExclusiveScissor,
    uint32_t                                    exclusiveScissorCount,
    const VkRect2D*                             pExclusiveScissors),
(commandBuffer, firstExclusiveScissor, exclusiveScissorCount, pExclusiveScissors));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetCheckpointNV,(
    VkCommandBuffer                             commandBuffer,
    const void*                                 pCheckpointMarker),
(commandBuffer, pCheckpointMarker));

YKM22_VULKAN_SYMBOL(
void,vkGetQueueCheckpointDataNV,(
    VkQueue                                     queue,
    uint32_t*                                   pCheckpointDataCount,
    VkCheckpointDataNV*                         pCheckpointData),
(queue, pCheckpointDataCount, pCheckpointData));

YKM22_VULKAN_SYMBOL(
VkResult,vkInitializePerformanceApiINTEL,(
    VkDevice                                    device,
    const VkInitializePerformanceApiInfoINTEL*  pInitializeInfo),
(device, pInitializeInfo));

YKM22_VULKAN_SYMBOL(
void,vkUninitializePerformanceApiINTEL,(
    VkDevice                                    device),
(device));

YKM22_VULKAN_SYMBOL(
VkResult,vkCmdSetPerformanceMarkerINTEL,(
    VkCommandBuffer                             commandBuffer,
    const VkPerformanceMarkerInfoINTEL*         pMarkerInfo),
(commandBuffer, pMarkerInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkCmdSetPerformanceStreamMarkerINTEL,(
    VkCommandBuffer                             commandBuffer,
    const VkPerformanceStreamMarkerInfoINTEL*   pMarkerInfo),
(commandBuffer, pMarkerInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkCmdSetPerformanceOverrideINTEL,(
    VkCommandBuffer                             commandBuffer,
    const VkPerformanceOverrideInfoINTEL*       pOverrideInfo),
(commandBuffer, pOverrideInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkAcquirePerformanceConfigurationINTEL,(
    VkDevice                                    device,
    const VkPerformanceConfigurationAcquireInfoINTEL* pAcquireInfo,
    VkPerformanceConfigurationINTEL*            pConfiguration),
(device, pAcquireInfo, pConfiguration));

YKM22_VULKAN_SYMBOL(
VkResult,vkReleasePerformanceConfigurationINTEL,(
    VkDevice                                    device,
    VkPerformanceConfigurationINTEL             configuration),
(device, configuration));

YKM22_VULKAN_SYMBOL(
VkResult,vkQueueSetPerformanceConfigurationINTEL,(
    VkQueue                                     queue,
    VkPerformanceConfigurationINTEL             configuration),
(queue, configuration));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPerformanceParameterINTEL,(
    VkDevice                                    device,
    VkPerformanceParameterTypeINTEL             parameter,
    VkPerformanceValueINTEL*                    pValue),
(device, parameter, pValue));

YKM22_VULKAN_SYMBOL(
void,vkSetLocalDimmingAMD,(
    VkDevice                                    device,
    VkSwapchainKHR                              swapChain,
    VkBool32                                    localDimmingEnable),
(device, swapChain, localDimmingEnable));

YKM22_VULKAN_SYMBOL(
VkDeviceAddress,vkGetBufferDeviceAddressEXT,(
    VkDevice                                    device,
    const VkBufferDeviceAddressInfo*            pInfo),
(device, pInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceToolPropertiesEXT,(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pToolCount,
    VkPhysicalDeviceToolProperties*             pToolProperties),
(physicalDevice, pToolCount, pToolProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceCooperativeMatrixPropertiesNV,(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pPropertyCount,
    VkCooperativeMatrixPropertiesNV*            pProperties),
(physicalDevice, pPropertyCount, pProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV,(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pCombinationCount,
    VkFramebufferMixedSamplesCombinationNV*     pCombinations),
(physicalDevice, pCombinationCount, pCombinations));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateHeadlessSurfaceEXT,(
    VkInstance                                  instance,
    const VkHeadlessSurfaceCreateInfoEXT*       pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface),
(instance, pCreateInfo, pAllocator, pSurface));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetLineStippleEXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    lineStippleFactor,
    uint16_t                                    lineStipplePattern),
(commandBuffer, lineStippleFactor, lineStipplePattern));

YKM22_VULKAN_SYMBOL(
void,vkResetQueryPoolEXT,(
    VkDevice                                    device,
    VkQueryPool                                 queryPool,
    uint32_t                                    firstQuery,
    uint32_t                                    queryCount),
(device, queryPool, firstQuery, queryCount));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetCullModeEXT,(
    VkCommandBuffer                             commandBuffer,
    VkCullModeFlags                             cullMode),
(commandBuffer, cullMode));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetFrontFaceEXT,(
    VkCommandBuffer                             commandBuffer,
    VkFrontFace                                 frontFace),
(commandBuffer, frontFace));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetPrimitiveTopologyEXT,(
    VkCommandBuffer                             commandBuffer,
    VkPrimitiveTopology                         primitiveTopology),
(commandBuffer, primitiveTopology));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetViewportWithCountEXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    viewportCount,
    const VkViewport*                           pViewports),
(commandBuffer, viewportCount, pViewports));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetScissorWithCountEXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    scissorCount,
    const VkRect2D*                             pScissors),
(commandBuffer, scissorCount, pScissors));

YKM22_VULKAN_SYMBOL(
void,vkCmdBindVertexBuffers2EXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstBinding,
    uint32_t                                    bindingCount,
    const VkBuffer*                             pBuffers,
    const VkDeviceSize*                         pOffsets,
    const VkDeviceSize*                         pSizes,
    const VkDeviceSize*                         pStrides),
(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetDepthTestEnableEXT,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthTestEnable),
(commandBuffer, depthTestEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetDepthWriteEnableEXT,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthWriteEnable),
(commandBuffer, depthWriteEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetDepthCompareOpEXT,(
    VkCommandBuffer                             commandBuffer,
    VkCompareOp                                 depthCompareOp),
(commandBuffer, depthCompareOp));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetDepthBoundsTestEnableEXT,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthBoundsTestEnable),
(commandBuffer, depthBoundsTestEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetStencilTestEnableEXT,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    stencilTestEnable),
(commandBuffer, stencilTestEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetStencilOpEXT,(
    VkCommandBuffer                             commandBuffer,
    VkStencilFaceFlags                          faceMask,
    VkStencilOp                                 failOp,
    VkStencilOp                                 passOp,
    VkStencilOp                                 depthFailOp,
    VkCompareOp                                 compareOp),
(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp));

YKM22_VULKAN_SYMBOL(
VkResult,vkCopyMemoryToImageEXT,(
    VkDevice                                    device,
    const VkCopyMemoryToImageInfoEXT*           pCopyMemoryToImageInfo),
(device, pCopyMemoryToImageInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkCopyImageToMemoryEXT,(
    VkDevice                                    device,
    const VkCopyImageToMemoryInfoEXT*           pCopyImageToMemoryInfo),
(device, pCopyImageToMemoryInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkCopyImageToImageEXT,(
    VkDevice                                    device,
    const VkCopyImageToImageInfoEXT*            pCopyImageToImageInfo),
(device, pCopyImageToImageInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkTransitionImageLayoutEXT,(
    VkDevice                                    device,
    uint32_t                                    transitionCount,
    const VkHostImageLayoutTransitionInfoEXT*   pTransitions),
(device, transitionCount, pTransitions));

YKM22_VULKAN_SYMBOL(
void,vkGetImageSubresourceLayout2EXT,(
    VkDevice                                    device,
    VkImage                                     image,
    const VkImageSubresource2KHR*               pSubresource,
    VkSubresourceLayout2KHR*                    pLayout),
(device, image, pSubresource, pLayout));

YKM22_VULKAN_SYMBOL(
VkResult,vkReleaseSwapchainImagesEXT,(
    VkDevice                                    device,
    const VkReleaseSwapchainImagesInfoEXT*      pReleaseInfo),
(device, pReleaseInfo));

YKM22_VULKAN_SYMBOL(
void,vkGetGeneratedCommandsMemoryRequirementsNV,(
    VkDevice                                    device,
    const VkGeneratedCommandsMemoryRequirementsInfoNV* pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements),
(device, pInfo, pMemoryRequirements));

YKM22_VULKAN_SYMBOL(
void,vkCmdPreprocessGeneratedCommandsNV,(
    VkCommandBuffer                             commandBuffer,
    const VkGeneratedCommandsInfoNV*            pGeneratedCommandsInfo),
(commandBuffer, pGeneratedCommandsInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdExecuteGeneratedCommandsNV,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    isPreprocessed,
    const VkGeneratedCommandsInfoNV*            pGeneratedCommandsInfo),
(commandBuffer, isPreprocessed, pGeneratedCommandsInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdBindPipelineShaderGroupNV,(
    VkCommandBuffer                             commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    VkPipeline                                  pipeline,
    uint32_t                                    groupIndex),
(commandBuffer, pipelineBindPoint, pipeline, groupIndex));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateIndirectCommandsLayoutNV,(
    VkDevice                                    device,
    const VkIndirectCommandsLayoutCreateInfoNV* pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkIndirectCommandsLayoutNV*                 pIndirectCommandsLayout),
(device, pCreateInfo, pAllocator, pIndirectCommandsLayout));

YKM22_VULKAN_SYMBOL(
void,vkDestroyIndirectCommandsLayoutNV,(
    VkDevice                                    device,
    VkIndirectCommandsLayoutNV                  indirectCommandsLayout,
    const VkAllocationCallbacks*                pAllocator),
(device, indirectCommandsLayout, pAllocator));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetDepthBias2EXT,(
    VkCommandBuffer                             commandBuffer,
    const VkDepthBiasInfoEXT*                   pDepthBiasInfo),
(commandBuffer, pDepthBiasInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkAcquireDrmDisplayEXT,(
    VkPhysicalDevice                            physicalDevice,
    int32_t                                     drmFd,
    VkDisplayKHR                                display),
(physicalDevice, drmFd, display));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetDrmDisplayEXT,(
    VkPhysicalDevice                            physicalDevice,
    int32_t                                     drmFd,
    uint32_t                                    connectorId,
    VkDisplayKHR*                               display),
(physicalDevice, drmFd, connectorId, display));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreatePrivateDataSlotEXT,(
    VkDevice                                    device,
    const VkPrivateDataSlotCreateInfo*          pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkPrivateDataSlot*                          pPrivateDataSlot),
(device, pCreateInfo, pAllocator, pPrivateDataSlot));

YKM22_VULKAN_SYMBOL(
void,vkDestroyPrivateDataSlotEXT,(
    VkDevice                                    device,
    VkPrivateDataSlot                           privateDataSlot,
    const VkAllocationCallbacks*                pAllocator),
(device, privateDataSlot, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkSetPrivateDataEXT,(
    VkDevice                                    device,
    VkObjectType                                objectType,
    uint64_t                                    objectHandle,
    VkPrivateDataSlot                           privateDataSlot,
    uint64_t                                    data),
(device, objectType, objectHandle, privateDataSlot, data));

YKM22_VULKAN_SYMBOL(
void,vkGetPrivateDataEXT,(
    VkDevice                                    device,
    VkObjectType                                objectType,
    uint64_t                                    objectHandle,
    VkPrivateDataSlot                           privateDataSlot,
    uint64_t*                                   pData),
(device, objectType, objectHandle, privateDataSlot, pData));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateCudaModuleNV,(
    VkDevice                                    device,
    const VkCudaModuleCreateInfoNV*             pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkCudaModuleNV*                             pModule),
(device, pCreateInfo, pAllocator, pModule));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetCudaModuleCacheNV,(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    size_t*                                     pCacheSize,
    void*                                       pCacheData),
(device, module, pCacheSize, pCacheData));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateCudaFunctionNV,(
    VkDevice                                    device,
    const VkCudaFunctionCreateInfoNV*           pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkCudaFunctionNV*                           pFunction),
(device, pCreateInfo, pAllocator, pFunction));

YKM22_VULKAN_SYMBOL(
void,vkDestroyCudaModuleNV,(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    const VkAllocationCallbacks*                pAllocator),
(device, module, pAllocator));

YKM22_VULKAN_SYMBOL(
void,vkDestroyCudaFunctionNV,(
    VkDevice                                    device,
    VkCudaFunctionNV                            function,
    const VkAllocationCallbacks*                pAllocator),
(device, function, pAllocator));

YKM22_VULKAN_SYMBOL(
void,vkCmdCudaLaunchKernelNV,(
    VkCommandBuffer                             commandBuffer,
    const VkCudaLaunchInfoNV*                   pLaunchInfo),
(commandBuffer, pLaunchInfo));

YKM22_VULKAN_SYMBOL(
void,vkGetDescriptorSetLayoutSizeEXT,(
    VkDevice                                    device,
    VkDescriptorSetLayout                       layout,
    VkDeviceSize*                               pLayoutSizeInBytes),
(device, layout, pLayoutSizeInBytes));

YKM22_VULKAN_SYMBOL(
void,vkGetDescriptorSetLayoutBindingOffsetEXT,(
    VkDevice                                    device,
    VkDescriptorSetLayout                       layout,
    uint32_t                                    binding,
    VkDeviceSize*                               pOffset),
(device, layout, binding, pOffset));

YKM22_VULKAN_SYMBOL(
void,vkGetDescriptorEXT,(
    VkDevice                                    device,
    const VkDescriptorGetInfoEXT*               pDescriptorInfo,
    size_t                                      dataSize,
    void*                                       pDescriptor),
(device, pDescriptorInfo, dataSize, pDescriptor));

YKM22_VULKAN_SYMBOL(
void,vkCmdBindDescriptorBuffersEXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    bufferCount,
    const VkDescriptorBufferBindingInfoEXT*     pBindingInfos),
(commandBuffer, bufferCount, pBindingInfos));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetDescriptorBufferOffsetsEXT,(
    VkCommandBuffer                             commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    VkPipelineLayout                            layout,
    uint32_t                                    firstSet,
    uint32_t                                    setCount,
    const uint32_t*                             pBufferIndices,
    const VkDeviceSize*                         pOffsets),
(commandBuffer, pipelineBindPoint, layout, firstSet, setCount, pBufferIndices, pOffsets));

YKM22_VULKAN_SYMBOL(
void,vkCmdBindDescriptorBufferEmbeddedSamplersEXT,(
    VkCommandBuffer                             commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    VkPipelineLayout                            layout,
    uint32_t                                    set),
(commandBuffer, pipelineBindPoint, layout, set));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetBufferOpaqueCaptureDescriptorDataEXT,(
    VkDevice                                    device,
    const VkBufferCaptureDescriptorDataInfoEXT* pInfo,
    void*                                       pData),
(device, pInfo, pData));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetImageOpaqueCaptureDescriptorDataEXT,(
    VkDevice                                    device,
    const VkImageCaptureDescriptorDataInfoEXT*  pInfo,
    void*                                       pData),
(device, pInfo, pData));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetImageViewOpaqueCaptureDescriptorDataEXT,(
    VkDevice                                    device,
    const VkImageViewCaptureDescriptorDataInfoEXT* pInfo,
    void*                                       pData),
(device, pInfo, pData));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetSamplerOpaqueCaptureDescriptorDataEXT,(
    VkDevice                                    device,
    const VkSamplerCaptureDescriptorDataInfoEXT* pInfo,
    void*                                       pData),
(device, pInfo, pData));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT,(
    VkDevice                                    device,
    const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo,
    void*                                       pData),
(device, pInfo, pData));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetFragmentShadingRateEnumNV,(
    VkCommandBuffer                             commandBuffer,
    VkFragmentShadingRateNV                     shadingRate,
    const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]),
(commandBuffer, shadingRate, combinerOps));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetDeviceFaultInfoEXT,(
    VkDevice                                    device,
    VkDeviceFaultCountsEXT*                     pFaultCounts,
    VkDeviceFaultInfoEXT*                       pFaultInfo),
(device, pFaultCounts, pFaultInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetVertexInputEXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    vertexBindingDescriptionCount,
    const VkVertexInputBindingDescription2EXT*  pVertexBindingDescriptions,
    uint32_t                                    vertexAttributeDescriptionCount,
    const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions),
(commandBuffer, vertexBindingDescriptionCount, pVertexBindingDescriptions, vertexAttributeDescriptionCount, pVertexAttributeDescriptions));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI,(
    VkDevice                                    device,
    VkRenderPass                                renderpass,
    VkExtent2D*                                 pMaxWorkgroupSize),
(device, renderpass, pMaxWorkgroupSize));

YKM22_VULKAN_SYMBOL(
void,vkCmdSubpassShadingHUAWEI,(
    VkCommandBuffer                             commandBuffer),
(commandBuffer));

YKM22_VULKAN_SYMBOL(
void,vkCmdBindInvocationMaskHUAWEI,(
    VkCommandBuffer                             commandBuffer,
    VkImageView                                 imageView,
    VkImageLayout                               imageLayout),
(commandBuffer, imageView, imageLayout));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetMemoryRemoteAddressNV,(
    VkDevice                                    device,
    const VkMemoryGetRemoteAddressInfoNV*       pMemoryGetRemoteAddressInfo,
    VkRemoteAddressNV*                          pAddress),
(device, pMemoryGetRemoteAddressInfo, pAddress));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPipelinePropertiesEXT,(
    VkDevice                                    device,
    const VkPipelineInfoEXT*                    pPipelineInfo,
    VkBaseOutStructure*                         pPipelineProperties),
(device, pPipelineInfo, pPipelineProperties));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetPatchControlPointsEXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    patchControlPoints),
(commandBuffer, patchControlPoints));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetRasterizerDiscardEnableEXT,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    rasterizerDiscardEnable),
(commandBuffer, rasterizerDiscardEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetDepthBiasEnableEXT,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthBiasEnable),
(commandBuffer, depthBiasEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetLogicOpEXT,(
    VkCommandBuffer                             commandBuffer,
    VkLogicOp                                   logicOp),
(commandBuffer, logicOp));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetPrimitiveRestartEnableEXT,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    primitiveRestartEnable),
(commandBuffer, primitiveRestartEnable));

YKM22_VULKAN_SYMBOL(
void                                   ,vkCmdSetColorWriteEnableEXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    attachmentCount,
    const VkBool32*                             pColorWriteEnables),
(commandBuffer, attachmentCount, pColorWriteEnables));

YKM22_VULKAN_SYMBOL(
void,vkCmdDrawMultiEXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    drawCount,
    const VkMultiDrawInfoEXT*                   pVertexInfo,
    uint32_t                                    instanceCount,
    uint32_t                                    firstInstance,
    uint32_t                                    stride),
(commandBuffer, drawCount, pVertexInfo, instanceCount, firstInstance, stride));

YKM22_VULKAN_SYMBOL(
void,vkCmdDrawMultiIndexedEXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    drawCount,
    const VkMultiDrawIndexedInfoEXT*            pIndexInfo,
    uint32_t                                    instanceCount,
    uint32_t                                    firstInstance,
    uint32_t                                    stride,
    const int32_t*                              pVertexOffset),
(commandBuffer, drawCount, pIndexInfo, instanceCount, firstInstance, stride, pVertexOffset));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateMicromapEXT,(
    VkDevice                                    device,
    const VkMicromapCreateInfoEXT*              pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkMicromapEXT*                              pMicromap),
(device, pCreateInfo, pAllocator, pMicromap));

YKM22_VULKAN_SYMBOL(
void,vkDestroyMicromapEXT,(
    VkDevice                                    device,
    VkMicromapEXT                               micromap,
    const VkAllocationCallbacks*                pAllocator),
(device, micromap, pAllocator));

YKM22_VULKAN_SYMBOL(
void,vkCmdBuildMicromapsEXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    infoCount,
    const VkMicromapBuildInfoEXT*               pInfos),
(commandBuffer, infoCount, pInfos));

YKM22_VULKAN_SYMBOL(
VkResult,vkBuildMicromapsEXT,(
    VkDevice                                    device,
    VkDeferredOperationKHR                      deferredOperation,
    uint32_t                                    infoCount,
    const VkMicromapBuildInfoEXT*               pInfos),
(device, deferredOperation, infoCount, pInfos));

YKM22_VULKAN_SYMBOL(
VkResult,vkCopyMicromapEXT,(
    VkDevice                                    device,
    VkDeferredOperationKHR                      deferredOperation,
    const VkCopyMicromapInfoEXT*                pInfo),
(device, deferredOperation, pInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkCopyMicromapToMemoryEXT,(
    VkDevice                                    device,
    VkDeferredOperationKHR                      deferredOperation,
    const VkCopyMicromapToMemoryInfoEXT*        pInfo),
(device, deferredOperation, pInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkCopyMemoryToMicromapEXT,(
    VkDevice                                    device,
    VkDeferredOperationKHR                      deferredOperation,
    const VkCopyMemoryToMicromapInfoEXT*        pInfo),
(device, deferredOperation, pInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkWriteMicromapsPropertiesEXT,(
    VkDevice                                    device,
    uint32_t                                    micromapCount,
    const VkMicromapEXT*                        pMicromaps,
    VkQueryType                                 queryType,
    size_t                                      dataSize,
    void*                                       pData,
    size_t                                      stride),
(device, micromapCount, pMicromaps, queryType, dataSize, pData, stride));

YKM22_VULKAN_SYMBOL(
void,vkCmdCopyMicromapEXT,(
    VkCommandBuffer                             commandBuffer,
    const VkCopyMicromapInfoEXT*                pInfo),
(commandBuffer, pInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdCopyMicromapToMemoryEXT,(
    VkCommandBuffer                             commandBuffer,
    const VkCopyMicromapToMemoryInfoEXT*        pInfo),
(commandBuffer, pInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdCopyMemoryToMicromapEXT,(
    VkCommandBuffer                             commandBuffer,
    const VkCopyMemoryToMicromapInfoEXT*        pInfo),
(commandBuffer, pInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdWriteMicromapsPropertiesEXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    micromapCount,
    const VkMicromapEXT*                        pMicromaps,
    VkQueryType                                 queryType,
    VkQueryPool                                 queryPool,
    uint32_t                                    firstQuery),
(commandBuffer, micromapCount, pMicromaps, queryType, queryPool, firstQuery));

YKM22_VULKAN_SYMBOL(
void,vkGetDeviceMicromapCompatibilityEXT,(
    VkDevice                                    device,
    const VkMicromapVersionInfoEXT*             pVersionInfo,
    VkAccelerationStructureCompatibilityKHR*    pCompatibility),
(device, pVersionInfo, pCompatibility));

YKM22_VULKAN_SYMBOL(
void,vkGetMicromapBuildSizesEXT,(
    VkDevice                                    device,
    VkAccelerationStructureBuildTypeKHR         buildType,
    const VkMicromapBuildInfoEXT*               pBuildInfo,
    VkMicromapBuildSizesInfoEXT*                pSizeInfo),
(device, buildType, pBuildInfo, pSizeInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdDrawClusterHUAWEI,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    groupCountX,
    uint32_t                                    groupCountY,
    uint32_t                                    groupCountZ),
(commandBuffer, groupCountX, groupCountY, groupCountZ));

YKM22_VULKAN_SYMBOL(
void,vkCmdDrawClusterIndirectHUAWEI,(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset),
(commandBuffer, buffer, offset));

YKM22_VULKAN_SYMBOL(
void,vkSetDeviceMemoryPriorityEXT,(
    VkDevice                                    device,
    VkDeviceMemory                              memory,
    float                                       priority),
(device, memory, priority));

YKM22_VULKAN_SYMBOL(
void,vkGetDescriptorSetLayoutHostMappingInfoVALVE,(
    VkDevice                                    device,
    const VkDescriptorSetBindingReferenceVALVE* pBindingReference,
    VkDescriptorSetLayoutHostMappingInfoVALVE*  pHostMapping),
(device, pBindingReference, pHostMapping));

YKM22_VULKAN_SYMBOL(
void,vkGetDescriptorSetHostMappingVALVE,(
    VkDevice                                    device,
    VkDescriptorSet                             descriptorSet,
    void**                                      ppData),
(device, descriptorSet, ppData));

YKM22_VULKAN_SYMBOL(
void,vkCmdCopyMemoryIndirectNV,(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             copyBufferAddress,
    uint32_t                                    copyCount,
    uint32_t                                    stride),
(commandBuffer, copyBufferAddress, copyCount, stride));

YKM22_VULKAN_SYMBOL(
void,vkCmdCopyMemoryToImageIndirectNV,(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             copyBufferAddress,
    uint32_t                                    copyCount,
    uint32_t                                    stride,
    VkImage                                     dstImage,
    VkImageLayout                               dstImageLayout,
    const VkImageSubresourceLayers*             pImageSubresources),
(commandBuffer, copyBufferAddress, copyCount, stride, dstImage, dstImageLayout, pImageSubresources));

YKM22_VULKAN_SYMBOL(
void,vkCmdDecompressMemoryNV,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    decompressRegionCount,
    const VkDecompressMemoryRegionNV*           pDecompressMemoryRegions),
(commandBuffer, decompressRegionCount, pDecompressMemoryRegions));

YKM22_VULKAN_SYMBOL(
void,vkCmdDecompressMemoryIndirectCountNV,(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             indirectCommandsAddress,
    VkDeviceAddress                             indirectCommandsCountAddress,
    uint32_t                                    stride),
(commandBuffer, indirectCommandsAddress, indirectCommandsCountAddress, stride));

YKM22_VULKAN_SYMBOL(
void,vkGetPipelineIndirectMemoryRequirementsNV,(
    VkDevice                                    device,
    const VkComputePipelineCreateInfo*          pCreateInfo,
    VkMemoryRequirements2*                      pMemoryRequirements),
(device, pCreateInfo, pMemoryRequirements));

YKM22_VULKAN_SYMBOL(
void,vkCmdUpdatePipelineIndirectBufferNV,(
    VkCommandBuffer                             commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    VkPipeline                                  pipeline),
(commandBuffer, pipelineBindPoint, pipeline));

YKM22_VULKAN_SYMBOL(
VkDeviceAddress,vkGetPipelineIndirectDeviceAddressNV,(
    VkDevice                                    device,
    const VkPipelineIndirectDeviceAddressInfoNV* pInfo),
(device, pInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetDepthClampEnableEXT,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthClampEnable),
(commandBuffer, depthClampEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetPolygonModeEXT,(
    VkCommandBuffer                             commandBuffer,
    VkPolygonMode                               polygonMode),
(commandBuffer, polygonMode));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetRasterizationSamplesEXT,(
    VkCommandBuffer                             commandBuffer,
    VkSampleCountFlagBits                       rasterizationSamples),
(commandBuffer, rasterizationSamples));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetSampleMaskEXT,(
    VkCommandBuffer                             commandBuffer,
    VkSampleCountFlagBits                       samples,
    const VkSampleMask*                         pSampleMask),
(commandBuffer, samples, pSampleMask));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetAlphaToCoverageEnableEXT,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    alphaToCoverageEnable),
(commandBuffer, alphaToCoverageEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetAlphaToOneEnableEXT,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    alphaToOneEnable),
(commandBuffer, alphaToOneEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetLogicOpEnableEXT,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    logicOpEnable),
(commandBuffer, logicOpEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetColorBlendEnableEXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstAttachment,
    uint32_t                                    attachmentCount,
    const VkBool32*                             pColorBlendEnables),
(commandBuffer, firstAttachment, attachmentCount, pColorBlendEnables));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetColorBlendEquationEXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstAttachment,
    uint32_t                                    attachmentCount,
    const VkColorBlendEquationEXT*              pColorBlendEquations),
(commandBuffer, firstAttachment, attachmentCount, pColorBlendEquations));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetColorWriteMaskEXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstAttachment,
    uint32_t                                    attachmentCount,
    const VkColorComponentFlags*                pColorWriteMasks),
(commandBuffer, firstAttachment, attachmentCount, pColorWriteMasks));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetTessellationDomainOriginEXT,(
    VkCommandBuffer                             commandBuffer,
    VkTessellationDomainOrigin                  domainOrigin),
(commandBuffer, domainOrigin));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetRasterizationStreamEXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    rasterizationStream),
(commandBuffer, rasterizationStream));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetConservativeRasterizationModeEXT,(
    VkCommandBuffer                             commandBuffer,
    VkConservativeRasterizationModeEXT          conservativeRasterizationMode),
(commandBuffer, conservativeRasterizationMode));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetExtraPrimitiveOverestimationSizeEXT,(
    VkCommandBuffer                             commandBuffer,
    float                                       extraPrimitiveOverestimationSize),
(commandBuffer, extraPrimitiveOverestimationSize));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetDepthClipEnableEXT,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthClipEnable),
(commandBuffer, depthClipEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetSampleLocationsEnableEXT,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    sampleLocationsEnable),
(commandBuffer, sampleLocationsEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetColorBlendAdvancedEXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstAttachment,
    uint32_t                                    attachmentCount,
    const VkColorBlendAdvancedEXT*              pColorBlendAdvanced),
(commandBuffer, firstAttachment, attachmentCount, pColorBlendAdvanced));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetProvokingVertexModeEXT,(
    VkCommandBuffer                             commandBuffer,
    VkProvokingVertexModeEXT                    provokingVertexMode),
(commandBuffer, provokingVertexMode));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetLineRasterizationModeEXT,(
    VkCommandBuffer                             commandBuffer,
    VkLineRasterizationModeEXT                  lineRasterizationMode),
(commandBuffer, lineRasterizationMode));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetLineStippleEnableEXT,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    stippledLineEnable),
(commandBuffer, stippledLineEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetDepthClipNegativeOneToOneEXT,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    negativeOneToOne),
(commandBuffer, negativeOneToOne));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetViewportWScalingEnableNV,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    viewportWScalingEnable),
(commandBuffer, viewportWScalingEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetViewportSwizzleNV,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstViewport,
    uint32_t                                    viewportCount,
    const VkViewportSwizzleNV*                  pViewportSwizzles),
(commandBuffer, firstViewport, viewportCount, pViewportSwizzles));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetCoverageToColorEnableNV,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    coverageToColorEnable),
(commandBuffer, coverageToColorEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetCoverageToColorLocationNV,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    coverageToColorLocation),
(commandBuffer, coverageToColorLocation));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetCoverageModulationModeNV,(
    VkCommandBuffer                             commandBuffer,
    VkCoverageModulationModeNV                  coverageModulationMode),
(commandBuffer, coverageModulationMode));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetCoverageModulationTableEnableNV,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    coverageModulationTableEnable),
(commandBuffer, coverageModulationTableEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetCoverageModulationTableNV,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    coverageModulationTableCount,
    const float*                                pCoverageModulationTable),
(commandBuffer, coverageModulationTableCount, pCoverageModulationTable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetShadingRateImageEnableNV,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    shadingRateImageEnable),
(commandBuffer, shadingRateImageEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetRepresentativeFragmentTestEnableNV,(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    representativeFragmentTestEnable),
(commandBuffer, representativeFragmentTestEnable));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetCoverageReductionModeNV,(
    VkCommandBuffer                             commandBuffer,
    VkCoverageReductionModeNV                   coverageReductionMode),
(commandBuffer, coverageReductionMode));

YKM22_VULKAN_SYMBOL(
void,vkGetShaderModuleIdentifierEXT,(
    VkDevice                                    device,
    VkShaderModule                              shaderModule,
    VkShaderModuleIdentifierEXT*                pIdentifier),
(device, shaderModule, pIdentifier));

YKM22_VULKAN_SYMBOL(
void,vkGetShaderModuleCreateInfoIdentifierEXT,(
    VkDevice                                    device,
    const VkShaderModuleCreateInfo*             pCreateInfo,
    VkShaderModuleIdentifierEXT*                pIdentifier),
(device, pCreateInfo, pIdentifier));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetPhysicalDeviceOpticalFlowImageFormatsNV,(
    VkPhysicalDevice                            physicalDevice,
    const VkOpticalFlowImageFormatInfoNV*       pOpticalFlowImageFormatInfo,
    uint32_t*                                   pFormatCount,
    VkOpticalFlowImageFormatPropertiesNV*       pImageFormatProperties),
(physicalDevice, pOpticalFlowImageFormatInfo, pFormatCount, pImageFormatProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateOpticalFlowSessionNV,(
    VkDevice                                    device,
    const VkOpticalFlowSessionCreateInfoNV*     pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkOpticalFlowSessionNV*                     pSession),
(device, pCreateInfo, pAllocator, pSession));

YKM22_VULKAN_SYMBOL(
void,vkDestroyOpticalFlowSessionNV,(
    VkDevice                                    device,
    VkOpticalFlowSessionNV                      session,
    const VkAllocationCallbacks*                pAllocator),
(device, session, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkBindOpticalFlowSessionImageNV,(
    VkDevice                                    device,
    VkOpticalFlowSessionNV                      session,
    VkOpticalFlowSessionBindingPointNV          bindingPoint,
    VkImageView                                 view,
    VkImageLayout                               layout),
(device, session, bindingPoint, view, layout));

YKM22_VULKAN_SYMBOL(
void,vkCmdOpticalFlowExecuteNV,(
    VkCommandBuffer                             commandBuffer,
    VkOpticalFlowSessionNV                      session,
    const VkOpticalFlowExecuteInfoNV*           pExecuteInfo),
(commandBuffer, session, pExecuteInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateShadersEXT,(
    VkDevice                                    device,
    uint32_t                                    createInfoCount,
    const VkShaderCreateInfoEXT*                pCreateInfos,
    const VkAllocationCallbacks*                pAllocator,
    VkShaderEXT*                                pShaders),
(device, createInfoCount, pCreateInfos, pAllocator, pShaders));

YKM22_VULKAN_SYMBOL(
void,vkDestroyShaderEXT,(
    VkDevice                                    device,
    VkShaderEXT                                 shader,
    const VkAllocationCallbacks*                pAllocator),
(device, shader, pAllocator));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetShaderBinaryDataEXT,(
    VkDevice                                    device,
    VkShaderEXT                                 shader,
    size_t*                                     pDataSize,
    void*                                       pData),
(device, shader, pDataSize, pData));

YKM22_VULKAN_SYMBOL(
void,vkCmdBindShadersEXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    stageCount,
    const VkShaderStageFlagBits*                pStages,
    const VkShaderEXT*                          pShaders),
(commandBuffer, stageCount, pStages, pShaders));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetFramebufferTilePropertiesQCOM,(
    VkDevice                                    device,
    VkFramebuffer                               framebuffer,
    uint32_t*                                   pPropertiesCount,
    VkTilePropertiesQCOM*                       pProperties),
(device, framebuffer, pPropertiesCount, pProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetDynamicRenderingTilePropertiesQCOM,(
    VkDevice                                    device,
    const VkRenderingInfo*                      pRenderingInfo,
    VkTilePropertiesQCOM*                       pProperties),
(device, pRenderingInfo, pProperties));

YKM22_VULKAN_SYMBOL(
VkResult,vkSetLatencySleepModeNV,(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    const VkLatencySleepModeInfoNV*             pSleepModeInfo),
(device, swapchain, pSleepModeInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkLatencySleepNV,(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    const VkLatencySleepInfoNV*                 pSleepInfo),
(device, swapchain, pSleepInfo));

YKM22_VULKAN_SYMBOL(
void,vkSetLatencyMarkerNV,(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    const VkSetLatencyMarkerInfoNV*             pLatencyMarkerInfo),
(device, swapchain, pLatencyMarkerInfo));

YKM22_VULKAN_SYMBOL(
void,vkGetLatencyTimingsNV,(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    VkGetLatencyMarkerInfoNV*                   pLatencyMarkerInfo),
(device, swapchain, pLatencyMarkerInfo));

YKM22_VULKAN_SYMBOL(
void,vkQueueNotifyOutOfBandNV,(
    VkQueue                                     queue,
    const VkOutOfBandQueueTypeInfoNV*           pQueueTypeInfo),
(queue, pQueueTypeInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetAttachmentFeedbackLoopEnableEXT,(
    VkCommandBuffer                             commandBuffer,
    VkImageAspectFlags                          aspectMask),
(commandBuffer, aspectMask));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateAccelerationStructureKHR,(
    VkDevice                                    device,
    const VkAccelerationStructureCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkAccelerationStructureKHR*                 pAccelerationStructure),
(device, pCreateInfo, pAllocator, pAccelerationStructure));

YKM22_VULKAN_SYMBOL(
void,vkDestroyAccelerationStructureKHR,(
    VkDevice                                    device,
    VkAccelerationStructureKHR                  accelerationStructure,
    const VkAllocationCallbacks*                pAllocator),
(device, accelerationStructure, pAllocator));

YKM22_VULKAN_SYMBOL(
void,vkCmdBuildAccelerationStructuresKHR,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos),
(commandBuffer, infoCount, pInfos, ppBuildRangeInfos));

YKM22_VULKAN_SYMBOL(
void,vkCmdBuildAccelerationStructuresIndirectKHR,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkDeviceAddress*                      pIndirectDeviceAddresses,
    const uint32_t*                             pIndirectStrides,
    const uint32_t* const*                      ppMaxPrimitiveCounts),
(commandBuffer, infoCount, pInfos, pIndirectDeviceAddresses, pIndirectStrides, ppMaxPrimitiveCounts));

YKM22_VULKAN_SYMBOL(
VkResult,vkBuildAccelerationStructuresKHR,(
    VkDevice                                    device,
    VkDeferredOperationKHR                      deferredOperation,
    uint32_t                                    infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos),
(device, deferredOperation, infoCount, pInfos, ppBuildRangeInfos));

YKM22_VULKAN_SYMBOL(
VkResult,vkCopyAccelerationStructureKHR,(
    VkDevice                                    device,
    VkDeferredOperationKHR                      deferredOperation,
    const VkCopyAccelerationStructureInfoKHR*   pInfo),
(device, deferredOperation, pInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkCopyAccelerationStructureToMemoryKHR,(
    VkDevice                                    device,
    VkDeferredOperationKHR                      deferredOperation,
    const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo),
(device, deferredOperation, pInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkCopyMemoryToAccelerationStructureKHR,(
    VkDevice                                    device,
    VkDeferredOperationKHR                      deferredOperation,
    const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo),
(device, deferredOperation, pInfo));

YKM22_VULKAN_SYMBOL(
VkResult,vkWriteAccelerationStructuresPropertiesKHR,(
    VkDevice                                    device,
    uint32_t                                    accelerationStructureCount,
    const VkAccelerationStructureKHR*           pAccelerationStructures,
    VkQueryType                                 queryType,
    size_t                                      dataSize,
    void*                                       pData,
    size_t                                      stride),
(device, accelerationStructureCount, pAccelerationStructures, queryType, dataSize, pData, stride));

YKM22_VULKAN_SYMBOL(
void,vkCmdCopyAccelerationStructureKHR,(
    VkCommandBuffer                             commandBuffer,
    const VkCopyAccelerationStructureInfoKHR*   pInfo),
(commandBuffer, pInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdCopyAccelerationStructureToMemoryKHR,(
    VkCommandBuffer                             commandBuffer,
    const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo),
(commandBuffer, pInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdCopyMemoryToAccelerationStructureKHR,(
    VkCommandBuffer                             commandBuffer,
    const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo),
(commandBuffer, pInfo));

YKM22_VULKAN_SYMBOL(
VkDeviceAddress,vkGetAccelerationStructureDeviceAddressKHR,(
    VkDevice                                    device,
    const VkAccelerationStructureDeviceAddressInfoKHR* pInfo),
(device, pInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdWriteAccelerationStructuresPropertiesKHR,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    accelerationStructureCount,
    const VkAccelerationStructureKHR*           pAccelerationStructures,
    VkQueryType                                 queryType,
    VkQueryPool                                 queryPool,
    uint32_t                                    firstQuery),
(commandBuffer, accelerationStructureCount, pAccelerationStructures, queryType, queryPool, firstQuery));

YKM22_VULKAN_SYMBOL(
void,vkGetDeviceAccelerationStructureCompatibilityKHR,(
    VkDevice                                    device,
    const VkAccelerationStructureVersionInfoKHR* pVersionInfo,
    VkAccelerationStructureCompatibilityKHR*    pCompatibility),
(device, pVersionInfo, pCompatibility));

YKM22_VULKAN_SYMBOL(
void,vkGetAccelerationStructureBuildSizesKHR,(
    VkDevice                                    device,
    VkAccelerationStructureBuildTypeKHR         buildType,
    const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo,
    const uint32_t*                             pMaxPrimitiveCounts,
    VkAccelerationStructureBuildSizesInfoKHR*   pSizeInfo),
(device, buildType, pBuildInfo, pMaxPrimitiveCounts, pSizeInfo));

YKM22_VULKAN_SYMBOL(
void,vkCmdTraceRaysKHR,(
    VkCommandBuffer                             commandBuffer,
    const VkStridedDeviceAddressRegionKHR*      pRaygenShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR*      pMissShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR*      pHitShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR*      pCallableShaderBindingTable,
    uint32_t                                    width,
    uint32_t                                    height,
    uint32_t                                    depth),
(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, width, height, depth));

YKM22_VULKAN_SYMBOL(
VkResult,vkCreateRayTracingPipelinesKHR,(
    VkDevice                                    device,
    VkDeferredOperationKHR                      deferredOperation,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    createInfoCount,
    const VkRayTracingPipelineCreateInfoKHR*    pCreateInfos,
    const VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines),
(device, deferredOperation, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines));

YKM22_VULKAN_SYMBOL(
VkResult,vkGetRayTracingCaptureReplayShaderGroupHandlesKHR,(
    VkDevice                                    device,
    VkPipeline                                  pipeline,
    uint32_t                                    firstGroup,
    uint32_t                                    groupCount,
    size_t                                      dataSize,
    void*                                       pData),
(device, pipeline, firstGroup, groupCount, dataSize, pData));

YKM22_VULKAN_SYMBOL(
void,vkCmdTraceRaysIndirectKHR,(
    VkCommandBuffer                             commandBuffer,
    const VkStridedDeviceAddressRegionKHR*      pRaygenShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR*      pMissShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR*      pHitShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR*      pCallableShaderBindingTable,
    VkDeviceAddress                             indirectDeviceAddress),
(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, indirectDeviceAddress));

YKM22_VULKAN_SYMBOL(
VkDeviceSize,vkGetRayTracingShaderGroupStackSizeKHR,(
    VkDevice                                    device,
    VkPipeline                                  pipeline,
    uint32_t                                    group,
    VkShaderGroupShaderKHR                      groupShader),
(device, pipeline, group, groupShader));

YKM22_VULKAN_SYMBOL(
void,vkCmdSetRayTracingPipelineStackSizeKHR,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    pipelineStackSize),
(commandBuffer, pipelineStackSize));

YKM22_VULKAN_SYMBOL(
void,vkCmdDrawMeshTasksEXT,(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    groupCountX,
    uint32_t                                    groupCountY,
    uint32_t                                    groupCountZ),
(commandBuffer, groupCountX, groupCountY, groupCountZ));

YKM22_VULKAN_SYMBOL(
void,vkCmdDrawMeshTasksIndirectEXT,(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    uint32_t                                    drawCount,
    uint32_t                                    stride),
(commandBuffer, buffer, offset, drawCount, stride));

YKM22_VULKAN_SYMBOL(
void,vkCmdDrawMeshTasksIndirectCountEXT,(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    VkBuffer                                    countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride),
(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride));

#ifdef VK_USE_PLATFORM_WIN32_KHR
#include "dylib_vk_win32.h"
#endif

#endif // YKM22_DYLIB_VK_H
