#ifndef BLUEPRINT_VULKANRENDERPASS_H
#define BLUEPRINT_VULKANRENDERPASS_H

namespace Vulkan::Init {
    class VulkanRenderPass {
    public:
        VulkanRenderPass();

        void Initialize() noexcept;

        void createRenderPass() noexcept;

    private:

    };
}

#endif //BLUEPRINT_VULKANRENDERPASS_H
