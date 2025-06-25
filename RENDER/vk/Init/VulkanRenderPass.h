#ifndef BLUEPRINT_VULKANRENDERPASS_H
#define BLUEPRINT_VULKANRENDERPASS_H

#include <stdexcept>

#include <vulkan/vulkan.h>

namespace Vulkan::Init {
    class VulkanRenderPass {
    public:
        VulkanRenderPass();

        void Initialize() noexcept;

        void createRenderPass(VkDevice device, VkFormat swapChainImageFormat);

        VkRenderPass GetRenderPass() noexcept;

    private:
        VkRenderPass renderPass;
    };
}

#endif //BLUEPRINT_VULKANRENDERPASS_H
