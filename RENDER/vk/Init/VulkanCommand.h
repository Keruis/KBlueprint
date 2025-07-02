#ifndef BLUEPRINT_VULKANCOMMAND_H
#define BLUEPRINT_VULKANCOMMAND_H

#include <stdexcept>

#include <vulkan/vulkan.h>

#include "config.h"
#include "VulkanFuncUtils.h"

namespace Vulkan::Init {
    class VulkanCommand {
    public:
        VulkanCommand();

        void Initialize() noexcept;

        void createCommandPool(VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surfaceKhr);
        void createCommandBuffer(VkDevice device);

        VkCommandPool GetCommandPool() noexcept;
        std::vector<VkCommandBuffer>& GetCommandBuffer() noexcept;

    private:
        std::vector<VkCommandBuffer> m_commandBuffers;
        VkCommandPool commandPool;
    };
}

#endif //BLUEPRINT_VULKANCOMMAND_H
