#ifndef BLUEPRINT_VULKANFRAMEBUFFER_H
#define BLUEPRINT_VULKANFRAMEBUFFER_H

namespace Vulkan::Init {
    class VulkanFramebuffer {
    public:
        VulkanFramebuffer();

        void Initialize() noexcept;

        void createFramebuffers() noexcept;

    private:

    };
}

#endif //BLUEPRINT_VULKANFRAMEBUFFER_H
