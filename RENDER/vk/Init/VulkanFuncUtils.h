#ifndef DEMO_VULKANFUNCUTILS_H
#define DEMO_VULKANFUNCUTILS_H

#include "VulkanStruct.h"

#include <vulkan/vulkan.h>

namespace Vulkan::Init::Utils {
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surfaceKhr) noexcept;
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surfaceKhr) noexcept;
}

#endif //DEMO_VULKANFUNCUTILS_H
