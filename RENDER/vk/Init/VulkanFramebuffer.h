#ifndef BLUEPRINT_VULKANFRAMEBUFFER_H
#define BLUEPRINT_VULKANFRAMEBUFFER_H

#include <vector>
#include <stdexcept>

#include <vulkan/vulkan.h>

namespace Vulkan::Init {
    class VulkanFramebuffer {
    public:
        VulkanFramebuffer();

        void Initialize() noexcept;

        void createFramebuffers(VkDevice device, std::vector<VkImageView>& swapChainImageView, VkRenderPass renderPass, int width, int height);

        std::vector<VkFramebuffer>& GetSwapChainFrameBuffers() noexcept;

    private:
        std::vector<VkFramebuffer> swapChainFramebuffers;
    };
}

#endif //BLUEPRINT_VULKANFRAMEBUFFER_H
