#ifndef BLUEPRINT_VULKANSWAPCHAIN_H
#define BLUEPRINT_VULKANSWAPCHAIN_H

namespace Vulkan::Init {
    class VulkanSwapChain {
    public:
        VulkanSwapChain();

        void Initialize() noexcept;

        void createSwapChain() noexcept;

        void createImageViews() noexcept;

    private:

    };
}

#endif //BLUEPRINT_VULKANSWAPCHAIN_H
