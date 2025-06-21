#ifndef BLUEPRINT_VULKANCOMMAND_H
#define BLUEPRINT_VULKANCOMMAND_H

namespace Vulkan::Init {
    class VulkanCommand {
    public:
        VulkanCommand();

        void Initialize() noexcept;

        void createCommandPool() noexcept;

        void createCommandBuffer() noexcept;

    private:

    };
}

#endif //BLUEPRINT_VULKANCOMMAND_H
