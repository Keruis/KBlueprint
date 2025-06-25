#ifndef BLUEPRINT_VULKANCOMMAND_H
#define BLUEPRINT_VULKANCOMMAND_H

#include <stdexcept>

#include <vulkan/vulkan.h>

#include "VulkanFuncUtils.h"

namespace Vulkan::Init {
    class VulkanCommand {
    public:
        VulkanCommand();

        void Initialize() noexcept;

        void createCommandPool(VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surfaceKhr);
        void createCommandBuffer(VkDevice device);

        VkCommandPool GetCommandPool() noexcept;
        VkCommandBuffer& GetCommandBuffer() noexcept;

    private:
        VkCommandPool commandPool;
        VkCommandBuffer commandBuffer;
    };
}

#endif //BLUEPRINT_VULKANCOMMAND_H
