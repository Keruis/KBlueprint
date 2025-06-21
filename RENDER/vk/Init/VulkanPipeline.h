#ifndef BLUEPRINT_VULKANPIPELINE_H
#define BLUEPRINT_VULKANPIPELINE_H

namespace Vulkan::Init {
    class VulkanPipeline {
    public:
        VulkanPipeline();

        void Initialize() noexcept;

        void createGraphicsPipeline() noexcept;

    private:

    };
}

#endif //BLUEPRINT_VULKANPIPELINE_H
